//
//  MBBitmapPixelPlane.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/18/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "MBBitmapPixelPlane.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL         0
#define DEBUG_VERBOSE       0

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

#define kBitmapDefaultBitsPerChannel    8
#define kBitmapDefaultBitmapInfo        (kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Little)
#define kBitmapColorChannelMaximumValue 0xFF
#define kBitmapDefaultAlphaValue        kBitmapColorChannelMaximumValue

/******************************************************************************/
#pragma mark -
#pragma mark MBBitmapPixelPlane implementation
/******************************************************************************/

@implementation MBBitmapPixelPlane
{
    CGContextRef _bitmap;
    void* _data;
    BOOL _bigEndian;
    BOOL _usesAlphaChannel;
    BOOL _alphaFirst;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

- (nullable instancetype) initWithBitmapContext:(CGContextRef)bitmap
{
    self = [super init];
    if (self) {
        NSString* errorMsg = nil;
        void* bitmapData = CGBitmapContextGetData(bitmap);
        if (bitmapData) {
            CGBitmapInfo info = CGBitmapContextGetBitmapInfo(bitmap);
            CGColorSpaceRef colorSpace = CGBitmapContextGetColorSpace(bitmap);
            [[self class] _extractChannelCount:&_channelsPerPixel
                                 bytesPerPixel:&_bytesPerPixel
                                     bigEndian:&_bigEndian
                                      hasAlpha:&_usesAlphaChannel
                                    alphaFirst:&_alphaFirst
                                  andPixelType:&_pixelType
                                 forColorSpace:colorSpace
                               usingBitmapInfo:info];
            
            if (_pixelType == MBBitmapPixelTypeUnknown) {
                errorMsg = [NSString stringWithFormat:@"%@ got a bitmap with an unknown pixel type", [self class]];
            }
            else if (_pixelType == MBBitmapPixelTypeIncompatible) {
                errorMsg = [NSString stringWithFormat:@"%@ got a bitmap with an unsupported pixel type", [self class]];
            }
            else {
                _bitmap = (CGContextRef) CFRetain(bitmap);
                _data = bitmapData;     // bitmap data should stick around until containing bitmap context is destroyed
                
                _rowCount = CGBitmapContextGetHeight(bitmap);
                _columnCount = CGBitmapContextGetWidth(bitmap);
                _pixelCount = _rowCount * _columnCount;
                _sizeInBytes = _pixelCount * _bytesPerPixel;
                _channelMaximumValue = kBitmapColorChannelMaximumValue;
                
                MBLogDebug(@"pixelCount: %lu", (unsigned long)_pixelCount);
                MBLogDebug(@"columnCount: %lu", (unsigned long)_columnCount);
                MBLogDebug(@"rowCount: %lu", (unsigned long)_rowCount);
                MBLogDebug(@"channelsPerPixel: %lu", (unsigned long)_channelsPerPixel);
                MBLogDebug(@"channelMaximumValue: 0x%X", _channelMaximumValue);
                MBLogDebug(@"bytesPerPixel: %lu", (unsigned long)_bytesPerPixel);
                MBLogDebug(@"sizeInBytes: %lu", (unsigned long)_sizeInBytes);
                MBLogDebug(@"usesAlphaChannel: %s", (_usesAlphaChannel ? "YES" : "NO"));
                MBLogDebug(@"alphaFirst: %s", (_alphaFirst ? "YES" : "NO"));
                MBLogDebug(@"bigEndian: %s", (_bigEndian ? "YES" : "NO"));
            }
        }
        else {
            errorMsg = [NSString stringWithFormat:@"Parameter passed to %@ initializer does not appear to be a bitmap context", [self class]];
        }
        if (errorMsg) {
            MBLogError(@"%@", errorMsg);
            return nil;
        }
    }
    return self;
}

- (void) dealloc
{
    CGContextRelease(_bitmap);
}

/******************************************************************************/
#pragma mark Instantiation
/******************************************************************************/

+ (nullable instancetype) bitmapWithColumns:(NSUInteger)cols rows:(NSUInteger)rows
{
    MBLogDebugTrace();
    
    return [self bitmapWithSize:(CGSize){cols, rows}];
}

+ (nullable instancetype) bitmapWithSize:(CGSize)size
{
    MBLogDebugTrace();
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    
    MBBitmapPixelPlane* plane = [self bitmapWithSize:size
                                      bitsPerChannel:kBitmapDefaultBitsPerChannel
                                          colorSpace:colorSpace
                                          bitmapInfo:kBitmapDefaultBitmapInfo];
    
    CGColorSpaceRelease(colorSpace);
    
    return plane;
}

+ (nullable instancetype) bitmapWithSize:(CGSize)size
                          bitsPerChannel:(NSUInteger)bits
                              colorSpace:(nonnull CGColorSpaceRef)space
                              bitmapInfo:(CGBitmapInfo)info
{
    MBLogDebugTrace();
    
    NSUInteger channelCount = 0;
    NSUInteger bytesPerPixel = 0;
    [self _extractChannelCount:&channelCount
                 bytesPerPixel:&bytesPerPixel
                     bigEndian:nil
                      hasAlpha:nil
                    alphaFirst:nil
                  andPixelType:nil
                 forColorSpace:space
               usingBitmapInfo:info];
      
    NSUInteger rows = ceil(size.height);
    NSUInteger cols = ceil(size.width);
    NSUInteger bytesPerRow = (cols * bytesPerPixel);
    
    MBBitmapPixelPlane* plane = nil;
    CGContextRef bitmap = CGBitmapContextCreate(NULL, cols, rows, bits, bytesPerRow, space, info);
    if (bitmap) {
        plane = [[self alloc] initWithBitmapContext:bitmap];
    }
    else {
        MBLogError(@"CGBitmapContextCreate failed for %@", [self class]);
    }
    CGContextRelease(bitmap);

    return plane;
}

#if MB_BUILD_IOS

+ (nullable instancetype) bitmapWithUIImage:(nonnull UIImage*)image
{
    MBLogDebugTrace();
    
    return [self bitmapWithCGImage:image.CGImage];
}

#elif MB_BUILD_OSX

+ (nullable instancetype) bitmapWithNSImage:(nonnull NSImage*)image
{
    MBLogDebugTrace();

    CGImageRef cgImage = [image CGImageForProposedRect:nil context:nil hints:nil];
    return [self bitmapWithCGImage:cgImage];
}

#endif

+ (nullable instancetype) bitmapWithCGImage:(nonnull CGImageRef)image
{
    MBLogDebugTrace();
    
    NSUInteger rows = CGImageGetHeight(image);
    NSUInteger cols = CGImageGetWidth(image);
    NSUInteger bitsPerComponent = CGImageGetBitsPerComponent(image);
    NSUInteger bytesPerRow = CGImageGetBytesPerRow(image);
    CGColorSpaceRef space = CGImageGetColorSpace(image);
    CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(image);
    CGImageAlphaInfo alphaInfo = bitmapInfo & kCGBitmapAlphaInfoMask;
    if (alphaInfo == kCGImageAlphaFirst) {          // CGBitmapContextCreate doesn't support kCGImageAlphaFirst
        alphaInfo = kCGImageAlphaPremultipliedFirst;
    }
    else if (alphaInfo == kCGImageAlphaLast) {      // CGBitmapContextCreate doesn't support kCGImageAlphaLast
        alphaInfo = kCGImageAlphaPremultipliedLast;
    }
    bitmapInfo = (bitmapInfo & ~kCGBitmapAlphaInfoMask) | alphaInfo;
        
    MBBitmapPixelPlane* plane = nil;
    CGContextRef bitmap = CGBitmapContextCreate(NULL, cols, rows, bitsPerComponent, bytesPerRow, space, bitmapInfo);
    if (bitmap) {
        CGContextDrawImage(bitmap, (CGRect){0, 0, cols, rows}, image);
        
        plane = [[self alloc] initWithBitmapContext:bitmap];
    }
    else {
        MBLogError(@"CGBitmapContextCreate failed for %@", [self class]);
    }
    CGContextRelease(bitmap);
    
    return plane;
}

+ (nullable instancetype) bitmapWithBitmapContext:(nonnull CGContextRef)bitmap
{
    MBLogDebugTrace();
    
    return [[self alloc] initWithBitmapContext:bitmap];
}

/******************************************************************************/
#pragma mark Getting pixel information
/******************************************************************************/

+ (void) _extractChannelCount:(nullable inout NSUInteger*)channelsPtr
                bytesPerPixel:(nullable inout NSUInteger*)bytesPerPixelPtr
                    bigEndian:(nullable inout BOOL*)isBigEndianPtr
                     hasAlpha:(nullable inout BOOL*)hasAlphaPtr
                   alphaFirst:(nullable inout BOOL*)alphaFirstPtr
                 andPixelType:(nullable inout MBBitmapPixelType*)pixelTypePtr
                forColorSpace:(nonnull CGColorSpaceRef)colorSpace
              usingBitmapInfo:(CGBitmapInfo)bitmapInfo
{
    MBLogVerboseTrace();
    
    MBBitmapPixelType type = MBBitmapPixelTypeUnknown;
    NSUInteger channels = 0;
    CGColorSpaceModel colorModel = CGColorSpaceGetModel(colorSpace);
    switch (colorModel) {
        case kCGColorSpaceModelMonochrome:
            type = MBBitmapPixelTypeMonochrome;
            channels = 1;
            break;
            
        case kCGColorSpaceModelRGB:
            type = MBBitmapPixelTypeRGB;
            channels = 3;
            break;
            
        case kCGColorSpaceModelCMYK:
        case kCGColorSpaceModelLab:
        case kCGColorSpaceModelDeviceN:
        case kCGColorSpaceModelIndexed:
        case kCGColorSpaceModelPattern:
            type = MBBitmapPixelTypeIncompatible;
            break;

        default:        // empty default needed to silence -Wswitch warning
            break;      // generated when compiling this as a cocoapod
    }
    if (bitmapInfo & kCGBitmapFloatComponents) {
        type = MBBitmapPixelTypeIncompatible;
    }
    
    if (type != MBBitmapPixelTypeUnknown && type != MBBitmapPixelTypeIncompatible) {
        BOOL hasAlpha = NO;
        BOOL alphaFirst = NO;
        BOOL suppressAlpha = NO;
        CGImageAlphaInfo alphaInfo = (bitmapInfo & kCGBitmapAlphaInfoMask);
        switch (alphaInfo) {
            case kCGImageAlphaOnly:
                type = MBBitmapPixelTypeAlpha;
                // deliberately fall through
                
            case kCGImageAlphaFirst:
            case kCGImageAlphaLast:
            case kCGImageAlphaPremultipliedFirst:
            case kCGImageAlphaPremultipliedLast:
                hasAlpha = YES;
                channels++;
                break;
                
            case kCGImageAlphaNone:
                suppressAlpha = YES;
                break;

            default:        // empty default needed to silence -Wswitch warning
                break;      // generated when compiling this as a cocoapod
        }
        switch (alphaInfo) {
            case kCGImageAlphaFirst:
            case kCGImageAlphaPremultipliedFirst:
            case kCGImageAlphaNoneSkipFirst:
                alphaFirst = YES;
                break;

            default:        // empty default needed to silence -Wswitch warning
                break;      // generated when compiling this as a cocoapod
        }
        
        NSUInteger bytesPerPixel = 0;
        CGBitmapInfo byteOrder = (bitmapInfo & kCGBitmapByteOrderMask);
        BOOL sixteenBit = (byteOrder == kCGBitmapByteOrder16Little || byteOrder == kCGBitmapByteOrder16Big);
        BOOL bigEndian = (byteOrder == kCGBitmapByteOrder16Big || byteOrder == kCGBitmapByteOrder32Big);
        switch (type) {
            case MBBitmapPixelTypeAlpha:
                bytesPerPixel = 1;
                break;
                
            case MBBitmapPixelTypeMonochrome:
                bytesPerPixel = (hasAlpha ? 2 : 1);
                break;
                
            case MBBitmapPixelTypeRGB:
                bytesPerPixel = (sixteenBit ? 2 : (!suppressAlpha ? 4 : 3));
                break;

            default:        // empty default needed to silence -Wswitch warning
                break;      // generated when compiling this as a cocoapod
        }
        
        if (channelsPtr)
            *channelsPtr = channels;
        
        if (bytesPerPixelPtr)
            *bytesPerPixelPtr = bytesPerPixel;
        
        if (isBigEndianPtr)
            *isBigEndianPtr = bigEndian;
        
        if (hasAlphaPtr)
            *hasAlphaPtr = hasAlpha;
        
        if (alphaFirstPtr)
            *alphaFirstPtr = alphaFirst;
    }
    
    if (pixelTypePtr)
        *pixelTypePtr = type;
}

/******************************************************************************/
#pragma mark Translating byte offsets
/******************************************************************************/

- (nullable void*) _locationOfPixelAtColumn:(NSUInteger)col row:(NSUInteger)row
{
    if (row >= _rowCount || col >= _columnCount) {
        MBLogError(@"%@ got out-of-bounds coordinate (%lu,%lu); must be less than (%lu,%lu)", [self class], (unsigned long)col, (unsigned long)row, (unsigned long)_columnCount, (unsigned long)_rowCount);
        return nil;
    }
    
    NSUInteger offset = _bytesPerPixel * ((row * _columnCount) + col);
    void* dataStart = _data;
    dataStart += offset;
    return dataStart;
}

- (nullable void*) _locationOfPixelAtIndex:(NSUInteger)index
{
    if (index >= _pixelCount) {
        MBLogError(@"%@ got out-of-bounds pixel index (%lu); must be less than (%lu)", [self class], (unsigned long)index, (unsigned long)_pixelCount);
        return nil;
    }
    
    NSUInteger offset = _bytesPerPixel * index;
    void* dataStart = _data;
    dataStart += offset;
    return dataStart;
}

/******************************************************************************/
#pragma mark Accessing pixels
/******************************************************************************/

- (BOOL) _getPixel:(nonnull inout MBBitmapPixel*)pixel atLocation:(void*)loc
{
    if (!pixel || !loc)
        return NO;
        
    switch (_pixelType) {
        case MBBitmapPixelTypeAlpha:
            assert(_channelsPerPixel == 1);
            assert(_bytesPerPixel == 1);
            (*pixel).channel1 = 0;
            (*pixel).channel2 = 0;
            (*pixel).channel3 = 0;
            (*pixel).alpha = ((MBColorComponent*)loc)[0];
            break;
            
        case MBBitmapPixelTypeMonochrome:
            assert(_channelsPerPixel == 1 || _channelsPerPixel == 2);
            assert(_bytesPerPixel == 1 || _bytesPerPixel == 2);
            MBColorComponent val = ((MBColorComponent*)loc)[0];
            (*pixel).red = val;     // to make developing filters and such a little
            (*pixel).green = val;   // simpler, we report all channels for monochrome;
            (*pixel).blue = val;    // callers may also access via .white channel
            (*pixel).alpha = (_usesAlphaChannel ? ((MBColorComponent*)loc)[1] : kBitmapDefaultAlphaValue);
            break;
            
        case MBBitmapPixelTypeRGB:
            assert(_channelsPerPixel == 3 || _channelsPerPixel == 4);
            assert(_bytesPerPixel >= 2 && _bytesPerPixel <= 4);
            if (_bytesPerPixel == 2) {
                uint16_t pixVal = 0;
                memcpy(&pixVal, loc, sizeof(uint16_t));
                if (_bigEndian) {
                    pixVal = CFSwapInt16BigToHost(pixVal);
                } else {
                    pixVal = CFSwapInt16LittleToHost(pixVal);
                }
                (*pixel).red   = ((pixVal & 0b0111110000000000) >> 10) * 8;
                (*pixel).green = ((pixVal & 0b0000001111100000) >> 5) * 8;
                (*pixel).blue  =  (pixVal & 0b0000000000011111) * 8;
                if (_usesAlphaChannel) {
                    (*pixel).alpha = ((pixVal & 0b1000000000000000) ? kBitmapDefaultAlphaValue : 0);
                } else {
                    (*pixel).alpha = kBitmapDefaultAlphaValue;
                }
            }
            else {
                MBColorComponent* ptr = loc;
                if (_alphaFirst && _usesAlphaChannel) {
                    (*pixel).alpha = *ptr++;
                }
                if (!_bigEndian) {
                    (*pixel).red = *ptr++;
                    (*pixel).green = *ptr++;
                    (*pixel).blue = *ptr++;
                } else {
                    (*pixel).blue = *ptr++;
                    (*pixel).green = *ptr++;
                    (*pixel).red = *ptr++;
                }
                if (!_alphaFirst && _usesAlphaChannel) {
                    (*pixel).alpha = *ptr++;
                }
                if (!_usesAlphaChannel) {
                    (*pixel).alpha = kBitmapDefaultAlphaValue;
                }
            }
            
            break;
            
        default:
            return NO;
    }
    
    return YES;
}

- (BOOL) _setPixel:(MBBitmapPixel)pixel atLocation:(nonnull MBColorComponent*)loc
{
    if (!loc)
        return NO;
    
    switch (_pixelType) {
        case MBBitmapPixelTypeAlpha:
            assert(_channelsPerPixel == 1);
            assert(_bytesPerPixel == 1);
            loc[0] = pixel.alpha;
            break;
            
        case MBBitmapPixelTypeMonochrome:
            assert(_channelsPerPixel == 1 || _channelsPerPixel == 2);
            assert(_bytesPerPixel == 1 || _bytesPerPixel == 2);
            assert(!_usesAlphaChannel || _bytesPerPixel == 2);
            loc[0] = pixel.white;
            if (_usesAlphaChannel && _bytesPerPixel == 2) {
                loc[1] = pixel.alpha;
            }
            break;
            
        case MBBitmapPixelTypeRGB:
            assert(_channelsPerPixel == 3 || _channelsPerPixel == 4);
            assert(_bytesPerPixel >= 2 && _bytesPerPixel <= 4);
            if (_bytesPerPixel == 2) {
                uint16_t pixVal = 0;
                pixVal |= ((pixel.red / 8) & 0b11111) << 10;
                pixVal |= ((pixel.green / 8) & 0b11111) << 5;
                pixVal |= ((pixel.blue / 8) & 0b11111);
                if (_usesAlphaChannel && pixel.alpha > 0) {
                    pixVal |= 0b1000000000000000;
                }
                if (_bigEndian) {
                    pixVal = CFSwapInt16HostToBig(pixVal);
                } else {
                    pixVal = CFSwapInt16HostToLittle(pixVal);
                }
                memcpy(loc, &pixVal, sizeof(uint16_t));
            }
            else {
                MBColorComponent* ptr = loc;
                if (_alphaFirst && _usesAlphaChannel) {
                    *ptr++ = pixel.alpha;
                }
                if (!_bigEndian) {
                    *ptr++ = pixel.red;
                    *ptr++ = pixel.green;
                    *ptr++ = pixel.blue;
                } else {
                    *ptr++ = pixel.blue;
                    *ptr++ = pixel.green;
                    *ptr++ = pixel.red;
                }
                if (!_alphaFirst && _usesAlphaChannel) {
                    *ptr++ = pixel.alpha;
                }
            }
            break;
            
        default:
            return NO;
    }
    
    return YES;
}

- (BOOL) getPixel:(nonnull inout MBBitmapPixel*)pixel atColumn:(NSUInteger)col row:(NSUInteger)row
{
    MBLogVerboseTrace();

    return [self _getPixel:pixel atLocation:[self _locationOfPixelAtColumn:col row:row]];
}

- (BOOL) getPixel:(nonnull inout MBBitmapPixel*)pixel atPoint:(CGPoint)point
{
    MBLogVerboseTrace();

    return [self _getPixel:pixel atLocation:[self _locationOfPixelAtColumn:(NSUInteger)round(point.x)
                                                                       row:(NSUInteger)round(point.y)]];
}

- (BOOL) getPixel:(nonnull inout MBBitmapPixel*)pixel atIndex:(NSUInteger)index
{
    MBLogVerboseTrace();

    return [self _getPixel:pixel atLocation:[self _locationOfPixelAtIndex:index]];
}

- (BOOL) setPixel:(MBBitmapPixel)pixel atColumn:(NSUInteger)col row:(NSUInteger)row
{
    MBLogVerboseTrace();

    return [self _setPixel:pixel atLocation:[self _locationOfPixelAtColumn:col row:row]];
}

- (BOOL) setPixel:(MBBitmapPixel)pixel atPoint:(CGPoint)point
{
    MBLogVerboseTrace();

    return [self _setPixel:pixel atLocation:[self _locationOfPixelAtColumn:(NSUInteger)round(point.x)
                                                                       row:(NSUInteger)round(point.y)]];
}

- (BOOL) setPixel:(MBBitmapPixel)pixel atIndex:(NSUInteger)index
{
    MBLogVerboseTrace();

    return [self _setPixel:pixel atLocation:[self _locationOfPixelAtIndex:index]];
}

/******************************************************************************/
#pragma mark Getting images
/******************************************************************************/

#if TARGET_OS_IPHONE

- (nonnull UIImage*) image
{
    MBLogDebugTrace();
    
    CGImageRef imageRef = CGBitmapContextCreateImage(_bitmap);
    UIImage* image = [UIImage imageWithCGImage:imageRef];
    CFRelease(imageRef);
    return image;
}

#elif TARGET_OS_MAC

- (nonnull NSImage*) image
{
    MBLogDebugTrace();

    CGImageRef imageRef = CGBitmapContextCreateImage(_bitmap);
    NSImage* image = [[NSImage alloc] initWithCGImage:imageRef size:NSZeroSize];
    CFRelease(imageRef);
    return image;
}

#endif

@end
