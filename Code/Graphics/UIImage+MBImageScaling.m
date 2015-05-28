//
//  UIImage+MBImageScaling.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/17/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "UIImage+MBImageScaling.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL             0

/******************************************************************************/
#pragma -
#pragma mark UIImage additions implementation
/******************************************************************************/

@implementation UIImage (MBImageScaling)

/******************************************************************************/
#pragma mark Scaling images to specific sizes
/******************************************************************************/

- (nonnull UIImage*) imageScaledToSize:(CGSize)newSize quality:(CGInterpolationQuality)quality
{
    MBLogDebugTrace();
    
    if (CGSizeEqualToSize(self.size, newSize)) {
        // do nothing if size isn't different
        return self;
    }
    
    UIGraphicsBeginImageContext(newSize);
    CGContextSetInterpolationQuality(UIGraphicsGetCurrentContext(), quality);
    [self drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return newImage;
}

- (nonnull UIImage*) imageScaledToSize:(CGSize)newSize
{
    MBLogDebugTrace();

    return [self imageScaledToSize:newSize quality:kCGInterpolationDefault];
}

/******************************************************************************/
#pragma mark Scaling images by a percentage of the original
/******************************************************************************/

- (nonnull UIImage*) imageScaledByFactor:(CGFloat)scale quality:(CGInterpolationQuality)quality
{
    MBLogDebugTrace();
    
    if (scale == 1.0) {
        // do nothing if scale wouldn't change image size
        return self;
    }

    CGSize curSize = self.size;
    return [self imageScaledToSize:CGSizeMake(curSize.width * scale, curSize.height * scale)
                           quality:quality];
}

- (nonnull UIImage*) imageScaledByFactor:(CGFloat)scale
{
    MBLogDebugTrace();

    return [self imageScaledByFactor:scale quality:kCGInterpolationDefault];
}

@end
