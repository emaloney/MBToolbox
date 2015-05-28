//
//  UIImage+MBImageScaling.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/17/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/******************************************************************************/
#pragma -
#pragma mark UIImage class additions
/******************************************************************************/

/*!
 A class extension for `UIImage` that provides methods for resizing images.
 */
@interface UIImage (MBImageScaling)

/*----------------------------------------------------------------------------*/
#pragma mark Scaling images to a specific size
/*!    @name Scaling images to a specific size                                */
/*----------------------------------------------------------------------------*/

/*!
 Scales the receiver to the specified size.

 @param     newSize The size of the `UIImage` to be returned. If this is the
            same size as the receiver, no scaling is performed and `self` is
            returned.
 
 @param     quality The interpolation quality to use for scaling the image.
 
 @return    The resulting image.
 */
- (nonnull UIImage*) imageScaledToSize:(CGSize)newSize quality:(CGInterpolationQuality)quality;

/*!
 Scales the receiver to the specified size.
 
 Scaling will be performed using the `kCGInterpolationDefault` interpolation 
 quality.

 @param     newSize The size of the `UIImage` to be returned. If this is the
            same size as the receiver, no scaling is performed and `self` is
            returned.

 @return    The resulting image.
 */
- (nonnull UIImage*) imageScaledToSize:(CGSize)newSize;

/*----------------------------------------------------------------------------*/
#pragma mark Scaling images by a percentage of the original
/*!    @name Scaling images by a percentage of the original                   */
/*----------------------------------------------------------------------------*/

/*!
 Scales the receiver to a new size by applying the specified scale factor.
 
 The new size is determined by multiplying the width and height by the
 scale factor.

 @param     scale The scale factor that determines the size of the returned
            image. Numbers less than `1.0` result in a smaller image; numbers
            greater than `1.0` result in a larger image. If this value is
            `1.0` exactly, no scaling is performed and `self` is returned.

 @param     quality The interpolation quality to use for scaling the image.

 @return    The resulting image.
 */
- (nonnull UIImage*) imageScaledByFactor:(CGFloat)scale quality:(CGInterpolationQuality)quality;

/*!
 Scales the receiver to a new size by applying the specified scale factor.
 
 The new size is determined by multiplying the width and height by the
 scale factor.
 
 Scaling will be performed using the `kCGInterpolationDefault` interpolation 
 quality.

 @param     scale The scale factor that determines the size of the returned
            image. Numbers less than `1.0` result in a smaller image; numbers
            greater than `1.0` result in a larger image. If this value is
            `1.0` exactly, no scaling is performed and `self` is returned.

 @return    The resulting image.
 */
- (nonnull UIImage*) imageScaledByFactor:(CGFloat)scale;

@end
