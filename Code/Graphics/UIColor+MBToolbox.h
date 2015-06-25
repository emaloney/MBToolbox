//
//  UIColor+MBToolbox.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/28/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/******************************************************************************/
#pragma mark Macros for creating UIColor instances
/******************************************************************************/

/*!
 Returns a `UIColor` instance from three individual byte values
 (i.e., `0-255` the specifying red, green and blue color components.
 */
#define UIColorFromRGBBytes(r,g,b) [UIColor \
colorWithRed:   ((CGFloat)(r)/255.0) \
green:          ((CGFloat)(g)/255.0) \
blue:           ((CGFloat)(b)/255.0) \
alpha:          1.0]

/*!
 Same as `UIColorFromRGBBytes()` but returns a `CGColorRef`
 instance instead.
 */
#define CGColorFromRGBBytes(r,g,b) UIColorFromRGBBytes(r,g,b).CGColor

/*!
 Returns a `UIColor` instance from three individual byte values
 (i.e., `0-255` the specifying red, green, blue and alpha color
 components.
 */
#define UIColorFromRGBABytes(r,g,b,a) [UIColor \
colorWithRed:   ((CGFloat)(r)/255.0) \
green:          ((CGFloat)(g)/255.0) \
blue:           ((CGFloat)(b)/255.0) \
alpha:          ((CGFloat)(a)/255.0)]

/*!
 Same as `UIColorFromRGBABytes()` but returns a `CGColorRef`
 instance instead.
 */
#define CGColorFromRGBABytes(r,g,b,a) UIColorFromRGBABytes(r,g,b,a).CGColor

/*!
 Returns a `UIColor` instance from a single 3-byte numeric value
 specifying red, green and blue color components, respectively. Typically, the
 RGB value is specified in hexadecimal notation, allowing colors to be defined
 in a manner similar to "web colors". For example, a `UIColor`
 matching the web color #f4cf51 can be created using the macro:
 `UIColorFromRGBHex(0xf4cf51)`.
 */
#define UIColorFromRGBHex(rgbValue) [UIColor \
colorWithRed:   ((CGFloat)(((rgbValue) & 0xFF0000) >> 16))/255.0 \
green:          ((CGFloat)(((rgbValue) & 0xFF00) >> 8))/255.0 \
blue:           ((CGFloat) ((rgbValue) & 0xFF))/255.0 \
alpha:          1.0]

/*!
 Same as `UIColorFromRGBHex()` but returns a `CGColorRef`
 instance instead.
 */
#define CGColorFromRGBHex(rgbValue) UIColorFromRGBHex(rgbValue).CGColor

/*!
 Returns a `UIColor` instance from a single 4-byte numeric value
 specifying red, green, blue and alpha color components, respectively. Typically,
 the RGBA value is specified in hexadecimal notation, allowing colors to be
 defined in a manner similar to "web colors". For example, a `UIColor`
 matching the web color #f4cf51 with a 50% transparency can be created using the
 macro: `UIColorFromRGBHex(0xf4cf517f)`.
 */
#define UIColorFromRGBAHex(rgbaValue) [UIColor \
colorWithRed:   ((CGFloat)(((rgbaValue) & 0xFF000000) >> 24))/255.0 \
green:          ((CGFloat)(((rgbaValue) & 0xFF0000) >> 16))/255.0 \
blue:           ((CGFloat)(((rgbaValue) & 0xFF00) >> 8))/255.0 \
alpha:          ((CGFloat) ((rgbaValue) & 0xFF))/255.0]

/*!
 Same as `UIColorFromRGBAHex()` but returns a `CGColorRef`
 instance instead.
 */
#define CGColorFromRGBAHex(rgbaValue) UIColorFromRGBAHex(rgbaValue).CGColor

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
- (nonnull UIColor*) highlightColor;

/*!
 Returns a new `UIColor` instance by adjusting the brightness value of the
 receiver by a given factor.

 The returned color will match the hue, saturation and alpha of the
 receiver, but the brightness value will be multiplied by the 
 adjustment factor.
 
 @param     adjustFactor The adjustment factor.
 
 @return    The adjusted color.
 */
- (nonnull UIColor*) colorWithBrightnessAdjustedByFactor:(CGFloat)adjustFactor;

@end

