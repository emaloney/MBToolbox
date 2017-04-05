//
//  MBRoundedRectTools.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/28/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/******************************************************************************/
#pragma mark -
#pragma mark MBRoundedRectTools class
/******************************************************************************/

/*!
 A few tools for creating rounded rectangle paths and managing corner radii.
 */
@interface MBRoundedRectTools : NSObject

/*----------------------------------------------------------------------------*/
#pragma mark Corner radius utilities
/*!    @name Corner radius utilities                                          */
/*----------------------------------------------------------------------------*/

/*!
 Returns a corner radius sized appropriately for the given rectangle.

 @param     rect The rectangle for which a corner radius is desired.
 
 @return    A corner radius that should look good when used with `rect`.
            (Or, since "good" is subjective, a corner radius that shouldn't
            look ridiculous when used with `rect`.)
 */
+ (CGFloat) cornerRadiusSizedForRect:(CGRect)rect;

/*!
 Returns a corner radius that approximates the curvature of the corner
 radius supplied for the given rectangle when that rectangle is inset by the
 specified amount.
 
 This can be used to create nested rounded rectangles of different sizes
 whose corner arcs look related.
 
 @param     radius The radius used with `rect`.
 
 @param     rect The rectangle to be adjusted by `inset`.
 
 @param     inset The number of points each edge of `rect` will be inset
            to create the rectangle used for calculating the returned corner
            radius. The width and height dimensions of `rect` are each reduced
            by `2 ✕ inset`; a positive inset results in a rectangle smaller
            than `rect`, while a negative inset results in a larger rectangle.
 
 @return    A corner radius for the adjusted rectangle.
 */
+ (CGFloat) adjustCornerRadius:(CGFloat)radius fromRect:(CGRect)rect withInset:(CGFloat)inset;

/*!
 Returns a corner radius for a rectangle that approximates the curvature of
 a corner radius used for a rectangle of a different size.

 This can be used to create nested rounded rectangles of different sizes
 whose corner arcs look related.
 
 @param     radius The radius used with `fromRect`.
 
 @param     fromRect The rectangle that uses the corner radius `radius`.
 
 @param     toRect The rectangle for which the corner radius will be returned.

 @return    A corner radius for `toRect` that approximates the curvature
            of the corner arc resulting from using `radius` with `fromRect`.
 */
+ (CGFloat) adjustCornerRadius:(CGFloat)radius fromRect:(CGRect)fromRect toRect:(CGRect)toRect;

/*----------------------------------------------------------------------------*/
#pragma mark Creating rounded rectangle paths
/*!    @name Creating rounded rectangle paths                                 */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new path for a rounded rectangle. The path will be adjusted to ensure
 that on non-Retina displays, subpixel rendering will not occur.
 
 @note      The caller takes ownership of the returned path and is responsible
            for ensuring its release.
 
 @param     rect The rectangle for which a rounded rectangle path is desired.
 
 @param     radius The corner radius to be used by the returned path.
 
 @return    A new `CGPathRef` usable for drawing the rounded rectangle path.
 */
+ (nonnull CGPathRef) newRoundedPathForRectangle:(CGRect)rect withRadius:(CGFloat)radius;

/*!
 Creates a new path for a rounded rectangle. The rectangle is adjusted to ensure
 that the stroke falls entirely within the bounds of the path, and that odd
 stroke widths do not result in subpixel rendering on non-Retina displays.
 
 This variant ensures that the returned path is adjusted to account for the
 stroke width that will be used to draw it.

 @note      The caller takes ownership of the returned path and is responsible
            for ensuring its release.
 
 @param     rect The rectangle for which a rounded rectangle path is desired.

 @param     radius The corner radius to be used by the returned path.
 
 @param     width The stroke width that will be used when drawing the returned
            path.

 @return    A new `CGPathRef` usable for drawing the rounded rectangle path.
 */
+ (nonnull CGPathRef) newRoundedPathForRectangle:(CGRect)rect withRadius:(CGFloat)radius forStrokeWidth:(CGFloat)width;

/*!
 Creates a new path for a rounded rectangle. The rectangle is adjusted by the
 specified inset, but is not otherwise adjusted to account for stroke widths
 or subpixel rendering on non-Retina displays.

 @note      The caller takes ownership of the returned path and is responsible
            for ensuring its release.
 
 @param     rect The rectangle for which a rounded rectangle path is desired.

 @param     radius The corner radius to be used by the returned path.
 
 @param     inset The number of points each edge of `rect` will be inset
            to create the rounded rectangle path. The width and height
            dimensions of `rect` are each reduced by `2 ✕ inset`; a positive 
            inset results in a rectangle smaller than `rect`, while a negative
            inset results in a larger rectangle.

 @return    A new `CGPathRef` usable for drawing the rounded rectangle path.
 */
+ (nonnull CGPathRef) newRoundedPathForRectangle:(CGRect)rect withRadius:(CGFloat)radius insetBy:(CGFloat)inset;

@end

