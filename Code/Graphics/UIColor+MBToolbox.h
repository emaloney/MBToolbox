//
//  UIColor+MBToolbox.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/28/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "Mockingbird-Toolbox.h"

/******************************************************************************/
#pragma -
#pragma mark UIColor class additions
/******************************************************************************/

/*!
 A class extension for `UIColor` that exposes additional color information.
 */
@interface UIColor (MBToolbox)

/*!
 Determines whether the receiver represents an opaque color.
 
 A color is opaque if it has an alpha channel value of `1.0`. A color with an
 alpha value less than `1.0` requires alpha blending and is not opaque.
 
 @return    `YES` if the receiver is an opaque color; `NO` otherwise.
 */
- (BOOL) isOpaque;

/*!
 Determines whether the receiver represents a dark color.
 
 A color is considered dark if its brightness value is less than `0.5`.

 @return    `YES` if the receiver is a dark color; `NO` otherwise.
 */
- (BOOL) isDark;

/*!
 Returns a new `UIColor` instance containing an appropriate highlight color
 for the receiver by adjusting the receiver's brightness.
 
 The highlight color will be a brighter version of the receiver if the
 receiver is a dark color; if the receiver is not a dark color, the highlight
 color will be a darker version of the receiver.
 
 @return    A highlight color based on the receiver.
 */
- (UIColor*) highlightColor;

/*!
 Returns a new `UIColor` instance by adjusting the brightness value of the
 receiver by a given factor.

 The returned color will match the hue, saturation and alpha of the
 receiver, but the brightness value will be multiplied by the 
 adjustment factor.
 
 @param     adjustFactor The adjustment factor.
 
 @return    The adjusted color.
 */
- (UIColor*) colorWithBrightnessAdjustedByFactor:(CGFloat)adjustFactor;

@end

