//
//  UIFont+MBStringSizing.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 9/5/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "UIFont+MBStringSizing.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL         0
#define DEBUG_VERBOSE       0

/******************************************************************************/
#pragma mark -
#pragma mark UIFont extensions for sizing strings
/******************************************************************************/

@implementation UIFont (MBStringSizing)

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
{
    MBLogVerboseTrace();

    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, CGFLOAT_MAX}
              lineBreakMode:NSLineBreakByWordWrapping
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
{
    MBLogVerboseTrace();

    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, maxHeight}
              lineBreakMode:NSLineBreakByWordWrapping
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
              maxSize:(CGSize)maxSize
{
    MBLogVerboseTrace();

    return [self sizeString:str
                    maxSize:maxSize
              lineBreakMode:NSLineBreakByWordWrapping
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
           fractional:(BOOL)allowFractionalSize
{
    MBLogVerboseTrace();

    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, CGFLOAT_MAX}
              lineBreakMode:NSLineBreakByWordWrapping
                 fractional:allowFractionalSize];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
           fractional:(BOOL)allowFractionalSize
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, maxHeight}
              lineBreakMode:NSLineBreakByWordWrapping
                 fractional:allowFractionalSize];
}

- (CGSize) sizeString:(nonnull NSString*)str
              maxSize:(CGSize)maxSize
           fractional:(BOOL)allowFractionalSize
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:maxSize
              lineBreakMode:NSLineBreakByWordWrapping
                 fractional:allowFractionalSize];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
        lineBreakMode:(NSLineBreakMode)lineMode
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, CGFLOAT_MAX}
              lineBreakMode:lineMode
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
        lineBreakMode:(NSLineBreakMode)lineMode
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, maxHeight}
              lineBreakMode:lineMode
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
              maxSize:(CGSize)maxSize
        lineBreakMode:(NSLineBreakMode)lineMode
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:maxSize
              lineBreakMode:lineMode
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
        lineBreakMode:(NSLineBreakMode)lineMode
           fractional:(BOOL)allowFractionalSize
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, CGFLOAT_MAX}
              lineBreakMode:lineMode
                 fractional:allowFractionalSize];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
        lineBreakMode:(NSLineBreakMode)lineMode
           fractional:(BOOL)allowFractionalSize
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, maxHeight}
              lineBreakMode:lineMode
                 fractional:allowFractionalSize];
}

- (CGSize) sizeString:(nonnull NSString*)str
              maxSize:(CGSize)maxSize
        lineBreakMode:(NSLineBreakMode)lineMode
           fractional:(BOOL)allowFractionalSize
{
    MBLogVerboseTrace();
    
    NSMutableParagraphStyle* style = [[NSParagraphStyle defaultParagraphStyle] mutableCopy];
    style.lineBreakMode = NSLineBreakByWordWrapping;
    
    return [self sizeString:str
                    maxSize:maxSize
             paragraphStyle:style
                 fractional:allowFractionalSize];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
       paragraphStyle:(nonnull NSParagraphStyle*)style
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, CGFLOAT_MAX}
             paragraphStyle:style
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
       paragraphStyle:(nonnull NSParagraphStyle*)style
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, maxHeight}
             paragraphStyle:style
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
              maxSize:(CGSize)maxSize
       paragraphStyle:(nonnull NSParagraphStyle*)style
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:maxSize
             paragraphStyle:style
                 fractional:NO];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
       paragraphStyle:(nonnull NSParagraphStyle*)style
           fractional:(BOOL)allowFractionalSize
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, CGFLOAT_MAX}
             paragraphStyle:style
                 fractional:allowFractionalSize];
}

- (CGSize) sizeString:(nonnull NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
       paragraphStyle:(nonnull NSParagraphStyle*)style
           fractional:(BOOL)allowFractionalSize
{
    MBLogVerboseTrace();
    
    return [self sizeString:str
                    maxSize:(CGSize){maxWidth, maxHeight}
             paragraphStyle:style
                 fractional:allowFractionalSize];
}

- (CGSize) sizeString:(nonnull NSString*)str
              maxSize:(CGSize)maxSize
       paragraphStyle:(nonnull NSParagraphStyle*)style
           fractional:(BOOL)allowFractionalSize
{
    MBLogDebugTrace();
    
    CGRect rect = [str boundingRectWithSize:maxSize
                                    options:(NSStringDrawingUsesFontLeading
                                             | NSStringDrawingUsesLineFragmentOrigin
                                             | NSStringDrawingTruncatesLastVisibleLine)
                                 attributes:@{NSFontAttributeName: self,
                                              NSParagraphStyleAttributeName: style}
                                    context:nil];
    
    CGSize size = rect.size;
    if (!allowFractionalSize) {
        size = (CGSize){ceil(size.width), ceil(size.height)};
    }
    return size;
}

@end
