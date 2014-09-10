//
//  UIFont+MBStringSizing.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 9/5/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <UIKit/UIKit.h>

/******************************************************************************/
#pragma mark -
#pragma mark UIFont extensions for sizing strings
/******************************************************************************/

/*!
 A `UIFont` class extension that adds an API for performing common string
 measurement tasks.
 */
@interface UIFont (MBStringSizing)

/*----------------------------------------------------------------------------*/
#pragma mark Measuring whole pixels with word wrapping
/*!    @name Measuring whole pixels with word wrapping                        */
/*----------------------------------------------------------------------------*/

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it will be wrapped according
            to the line break mode `NSLineBreakByWordWrapping`.
 
 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it will be wrapped according
            to the line break mode `NSLineBreakByWordWrapping`.
 
 @param     maxHeight The maximum height allowed for the text.
 
 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxSize The maximum size allowed for the text. If `str` would
            not fit within `maxSize.width` on a single line, it will be wrapped
            according to the line break mode `NSLineBreakByWordWrapping`.
 
 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
              maxSize:(CGSize)maxSize;

/*----------------------------------------------------------------------------*/
#pragma mark Measuring fractional pixels with word wrapping
/*!    @name Measuring fractional pixels with word wrapping                   */
/*----------------------------------------------------------------------------*/

/*!
 Calculates the size of the bounding rectangle required to draw a given text
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it will be wrapped according
            to the line break mode `NSLineBreakByWordWrapping`.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.

 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
           fractional:(BOOL)allowFractionalSize;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it will be wrapped according
            to the line break mode `NSLineBreakByWordWrapping`.
 
 @param     maxHeight The maximum height allowed for the text.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.

 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
           fractional:(BOOL)allowFractionalSize;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxSize The maximum size allowed for the text. If `str` would
            not fit within `maxSize.width` on a single line, it will be wrapped
            according to the line break mode `NSLineBreakByWordWrapping`.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.

 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
              maxSize:(CGSize)maxSize
           fractional:(BOOL)allowFractionalSize;

/*----------------------------------------------------------------------------*/
#pragma mark Measuring whole pixels with a specific line break mode
/*!    @name Measuring whole pixels with a specific line break mode           */
/*----------------------------------------------------------------------------*/

/*!
 Calculates the size of the bounding rectangle required to draw a given text
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it may be wrapped according
            to the specified line break mode.
 
 @param     lineMode The line break mode to use for measuring the text.
 
 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
        lineBreakMode:(NSLineBreakMode)lineMode;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it may be wrapped according
            to the specified line break mode.
 
 @param     maxHeight The maximum height allowed for the text.
 
 @param     lineMode The line break mode to use for measuring the text.

 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
        lineBreakMode:(NSLineBreakMode)lineMode;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxSize The maximum size allowed for the text. If `str` would
            not fit within `maxSize.width` on a single line, it will be wrapped
            according to the line break mode `NSLineBreakByWordWrapping`.
 
 @param     lineMode The line break mode to use for measuring the text.
 
 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
              maxSize:(CGSize)maxSize
        lineBreakMode:(NSLineBreakMode)lineMode;

/*----------------------------------------------------------------------------*/
#pragma mark Measuring fractional pixels with a specific line break mode
/*!    @name Measuring fractional pixels with a specific line break mode      */
/*----------------------------------------------------------------------------*/

/*!
 Calculates the size of the bounding rectangle required to draw a given text
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it may be wrapped according
            to the specified line break mode.
 
 @param     lineMode The line break mode to use for measuring the text.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 
 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
        lineBreakMode:(NSLineBreakMode)lineMode
           fractional:(BOOL)allowFractionalSize;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it may be wrapped according
            to the specified line break mode.

 @param     maxHeight The maximum height allowed for the text.

 @param     lineMode The line break mode to use for measuring the text.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 
 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
        lineBreakMode:(NSLineBreakMode)lineMode
           fractional:(BOOL)allowFractionalSize;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxSize The maximum size allowed for the text. If `str` would
            not fit within `maxSize.width` on a single line, it may be wrapped
            according to the specified line break mode.

 @param     lineMode The line break mode to use for measuring the text.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 
 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
              maxSize:(CGSize)maxSize
        lineBreakMode:(NSLineBreakMode)lineMode
           fractional:(BOOL)allowFractionalSize;

/*----------------------------------------------------------------------------*/
#pragma mark Measuring whole pixels with a specific paragraph style
/*!    @name Measuring whole pixels with a specific paragraph style           */
/*----------------------------------------------------------------------------*/

/*!
 Calculates the size of the bounding rectangle required to draw a given text
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it may be wrapped according
            to the specified paragraph style.
 
 @param     style The paragraph style for the text.
 
 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
       paragraphStyle:(NSParagraphStyle*)style;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it may be wrapped according
            to the specified paragraph style.

 @param     maxHeight The maximum height allowed for the text.

 @param     style The paragraph style for the text.
 
 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
       paragraphStyle:(NSParagraphStyle*)style;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxSize The maximum size allowed for the text. If `str` would
            not fit within `maxSize.width` on a single line, it may be wrapped
            according to the specified paragraph style.

 @param     style The paragraph style for the text.
 
 @return    The size required to draw the text string, with the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 */
- (CGSize) sizeString:(NSString*)str
              maxSize:(CGSize)maxSize
       paragraphStyle:(NSParagraphStyle*)style;

/*----------------------------------------------------------------------------*/
#pragma mark Measuring fractional pixels with a specific paragraph style
/*!    @name Measuring fractional pixels with a specific paragraph style      */
/*----------------------------------------------------------------------------*/

/*!
 Calculates the size of the bounding rectangle required to draw a given text
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it may be wrapped according
            to the specified paragraph style.
 
 @param     style The paragraph style for the text.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 
 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
       paragraphStyle:(NSParagraphStyle*)style
           fractional:(BOOL)allowFractionalSize;

/*!
 Calculates the size of the bounding rectangle required to draw a given text
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxWidth The maximum width allowed for the text. If `str` would not
            fit within `maxWidth` on a single line, it may be wrapped according
            to the specified paragraph style.
 
 @param     maxHeight The maximum height allowed for the text.
 
 @param     style The paragraph style for the text.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 
 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
             maxWidth:(CGFloat)maxWidth
            maxHeight:(CGFloat)maxHeight
       paragraphStyle:(NSParagraphStyle*)style
           fractional:(BOOL)allowFractionalSize;

/*!
 Calculates the size of the bounding rectangle required to draw a given text 
 string in the font represented by the receiver.
 
 @param     str The text string to measure.
 
 @param     maxSize The maximum size allowed for the text. If `str` would
            not fit within `maxSize.width` on a single line, it may be wrapped
            according to the specified paragraph style.

 @param     style The paragraph style for the text.
 
 @param     allowFractionalSize If `YES`, the returned size may contain
            fractional (sub-pixel) values. If `NO`, the width and
            height components rounded up to the nearest integer (whole-pixel)
            value.
 
 @return    The size required to draw the text string.
 */
- (CGSize) sizeString:(NSString*)str
              maxSize:(CGSize)maxSize
       paragraphStyle:(NSParagraphStyle*)style
           fractional:(BOOL)allowFractionalSize;

@end
