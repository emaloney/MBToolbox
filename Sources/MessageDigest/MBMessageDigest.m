//
//  MBMessageDigest.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 10/11/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import <CommonCrypto/CommonDigest.h>

#import "MBMessageDigest.h"
#import "NSError+MBToolbox.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

#define DEFAULT_FILE_BUFFER_SIZE        8192

/******************************************************************************/
#pragma mark -
#pragma mark MD5 implementation
/******************************************************************************/

@implementation MBMessageDigest

/******************************************************************************/
#pragma mark Private methods
/******************************************************************************/

+ (id) _processError:(inout NSError**)err code:(NSInteger)errCode infoKey:(NSString*)key value:(id)val
{
    if (err) {
        if (key && val) {
            *err = [NSError mockingbirdErrorWithCode:errCode userInfoKey:key value:val];
        }
        else {
            *err = [NSError mockingbirdErrorWithCode:errCode];
        }
    }
    return nil;     // always return nil to indicate error
}

+ (id) _processError:(inout NSError**)err code:(NSInteger)errCode
{
    return [self _processError:err code:errCode infoKey:nil value:nil];
}

+ (NSString*) _hexStringForDigest:(unsigned char*)digest ofLength:(NSUInteger)numBytes
{
    NSMutableString* hex = [NSMutableString stringWithCapacity:numBytes*2];
    for (NSUInteger i=0; i<numBytes; i++) {
        [hex appendFormat:@"%02x", digest[i]];
    }
    return hex;
}

+ (NSString*) _hexStringForMD5:(unsigned char*)md5
{
    return [self _hexStringForDigest:md5 ofLength:CC_MD5_DIGEST_LENGTH];
}

+ (NSString*) _hexStringForSHA1:(unsigned char*)md5
{
    return [self _hexStringForDigest:md5 ofLength:CC_SHA1_DIGEST_LENGTH];
}

/******************************************************************************/
#pragma mark Creating MD5 message digests
/******************************************************************************/

+ (nonnull NSData*) MD5DataForString:(nonnull NSString*)src
{
    const char* data = [src UTF8String];
    CC_LONG dataSize = (CC_LONG) strlen(data);

    unsigned char hash[CC_MD5_DIGEST_LENGTH];
    CC_MD5(data, (CC_LONG)dataSize, hash);

    return [NSData dataWithBytes:hash length:CC_MD5_DIGEST_LENGTH];
}

+ (nonnull NSString*) MD5ForString:(nonnull NSString*)src
{
    const char* data = [src UTF8String];
    CC_LONG dataSize = (CC_LONG) strlen(data);
    return [self MD5ForBytes:data length:dataSize];
}

+ (nonnull NSString*) MD5ForData:(nonnull NSData*)src
{
    const void* data = [src bytes];
    CC_LONG dataSize = (CC_LONG) [src length];
    return [self MD5ForBytes:data length:dataSize];
}

+ (nonnull NSString*) MD5ForBytes:(nonnull const void*)bytes length:(size_t)len;
{
    unsigned char hash[CC_MD5_DIGEST_LENGTH];
    CC_MD5(bytes, (CC_LONG)len, hash);
    
    return [self _hexStringForMD5:hash];
}

+ (NSString*) MD5ForFileAtPath:(NSString*)path error:(inout NSError**)err
{
    // make sure our path looks legit
    if (!path || path.length == 0) {
        return [self _processError:err code:kMBErrorInvalidArgument];
    }
    
    // convert path into filesystem URL
    CFURLRef url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, (CFStringRef)path, kCFURLPOSIXPathStyle, (Boolean)NO);
    if (!url) {
        return [self _processError:err code:kMBErrorCouldNotLoadFile infoKey:kMBErrorUserInfoKeyFilePath value:path];
    }

    // attempt to open the file
    CFReadStreamRef stream = CFReadStreamCreateWithFile(kCFAllocatorDefault, url);
    if (!stream) {
        CFRelease(url);
        return [self _processError:err code:kMBErrorCouldNotLoadFile infoKey:kMBErrorUserInfoKeyFilePath value:path];
    }

    NSError* streamError = nil;
    if (!CFReadStreamOpen(stream)) {
        streamError = (NSError*) CFBridgingRelease(CFReadStreamCopyError(stream));
    }

    // compute the MD5 by loading file in chunks
    NSString* hexHash = nil;
    if (!streamError) {
        CC_MD5_CTX md5;
        CC_MD5_Init(&md5);
        
        CFIndex readCnt = 0;
        uint8_t buffer[DEFAULT_FILE_BUFFER_SIZE];

        BOOL done = NO;
        while (!done) {
            readCnt = CFReadStreamRead(stream, buffer, DEFAULT_FILE_BUFFER_SIZE);

            if (readCnt == -1) {
                streamError = (NSError*) CFBridgingRelease(CFReadStreamCopyError(stream));
                break;
            }

            done = (readCnt == 0);
            if (done) {
                continue;
            }
            
            CC_MD5_Update(&md5, (const void*)buffer, (CC_LONG)readCnt);
        }
        
        if (done) {
            unsigned char hash[CC_MD5_DIGEST_LENGTH];
            CC_MD5_Final(hash, &md5);
            
            hexHash = [self _hexStringForMD5:hash];
        }
    }
    
    // close up shop
    CFReadStreamClose(stream);
    CFRelease(stream);
    CFRelease(url);
    
    // handle errors
    if (streamError) {
        if (err) {
            *err = streamError;
        }
    }

    return hexHash;
}

+ (nullable NSString*) MD5ForFileAtPath:(nonnull NSString*)path
{
    NSError* err = nil;
    NSString* md5 = [self MD5ForFileAtPath:path error:&err];
    if (err) {
        MBLogError(@"Error while attempting to compute MD5 hash for file <%@>: %@", path, err);
    }
    return md5;
}

/******************************************************************************/
#pragma mark Creating SHA-1 message digests
/******************************************************************************/

+ (nonnull NSData*) SHA1DataForString:(nonnull NSString*)src
{
    const char* data = [src UTF8String];
    CC_LONG dataSize = (CC_LONG) strlen(data);

    unsigned char hash[CC_SHA1_DIGEST_LENGTH];
    CC_SHA1(data, (CC_LONG)dataSize, hash);

    return [NSData dataWithBytes:hash length:CC_SHA1_DIGEST_LENGTH];
}

+ (nonnull NSString*) SHA1ForString:(nonnull NSString*)src
{
    const char* data = [src UTF8String];
    CC_LONG dataSize = (CC_LONG) strlen(data);
    return [self SHA1ForBytes:data length:dataSize];
}

+ (nonnull NSString*) SHA1ForData:(nonnull NSData*)src
{
    const void* data = [src bytes];
    CC_LONG dataSize = (CC_LONG) [src length];
    return [self SHA1ForBytes:data length:dataSize];
}

+ (nonnull NSString*) SHA1ForBytes:(nonnull const void*)bytes length:(size_t)len
{
    unsigned char hash[CC_SHA1_DIGEST_LENGTH];
    CC_SHA1(bytes, (CC_LONG)len, hash);

    return [self _hexStringForSHA1:hash];
}

+ (NSString*) SHA1ForFileAtPath:(NSString*)path error:(inout NSError**)err
{
    // make sure our path looks legit
    if (!path || path.length == 0) {
        return [self _processError:err code:kMBErrorInvalidArgument];
    }

    // convert path into filesystem URL
    CFURLRef url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, (CFStringRef)path, kCFURLPOSIXPathStyle, (Boolean)NO);
    if (!url) {
        return [self _processError:err code:kMBErrorCouldNotLoadFile infoKey:kMBErrorUserInfoKeyFilePath value:path];
    }

    // attempt to open the file
    CFReadStreamRef stream = CFReadStreamCreateWithFile(kCFAllocatorDefault, url);
    if (!stream) {
        CFRelease(url);
        return [self _processError:err code:kMBErrorCouldNotLoadFile infoKey:kMBErrorUserInfoKeyFilePath value:path];
    }

    NSError* streamError = nil;
    if (!CFReadStreamOpen(stream)) {
        streamError = (NSError*) CFBridgingRelease(CFReadStreamCopyError(stream));
    }

    // compute the MD5 by loading file in chunks
    NSString* hexHash = nil;
    if (!streamError) {
        CC_SHA1_CTX sha1;
        CC_SHA1_Init(&sha1);

        CFIndex readCnt = 0;
        uint8_t buffer[DEFAULT_FILE_BUFFER_SIZE];

        BOOL done = NO;
        while (!done) {
            readCnt = CFReadStreamRead(stream, buffer, DEFAULT_FILE_BUFFER_SIZE);

            if (readCnt == -1) {
                streamError = (NSError*) CFBridgingRelease(CFReadStreamCopyError(stream));
                break;
            }

            done = (readCnt == 0);
            if (done) {
                continue;
            }

            CC_SHA1_Update(&sha1, (const void*)buffer, (CC_LONG)readCnt);
        }

        if (done) {
            unsigned char hash[CC_SHA1_DIGEST_LENGTH];
            CC_SHA1_Final(hash, &sha1);

            hexHash = [self _hexStringForSHA1:hash];
        }
    }

    // close up shop
    CFReadStreamClose(stream);
    CFRelease(stream);
    CFRelease(url);

    // handle errors
    if (streamError) {
        if (err) {
            *err = streamError;
        }
    }

    return hexHash;
}

+ (nullable NSString*) SHA1ForFileAtPath:(nonnull NSString*)path;
{
    NSError* err = nil;
    NSString* sha1 = [self SHA1ForFileAtPath:path error:&err];
    if (err) {
        MBLogError(@"Error while attempting to compute SHA-1 hash for file <%@>: %@", path, err);
    }
    return sha1;
}

@end
