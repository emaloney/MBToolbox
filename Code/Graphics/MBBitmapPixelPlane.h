//
//  MBBitmapPixelPlane.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/18/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MBAvailability.h"

#if MB_BUILD_IOS
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

/******************************************************************************/
#pragma mark Types
/******************************************************************************/

/*!
 Indicates how an `MBBitmapPixelPlane` represents the color and alpha
 channels within the pixel data.
 
 These values govern how pixel channel data within the `MBBitmapPixel`
 struct should be interpreted.
 */
typedef NS_ENUM(NSUInteger, MBBitmapPixelType) {
    /*! The pixel type of the underlying bitmap is not known. `MBBitmapPixel`
        data is undefined and should not be relied upon. */
    MBBitmapPixelTypeUnknown,

    /*! The pixel type of the underlying bitmap is not compatible with the
        `MBBitmapPixelPlane` class. `MBBitmapPixel` data is undefined and 
        should not be relied upon. */
    MBBitmapPixelTypeIncompatible,

    /*! The bitmap uses the `alpha` channel (`channel4`) component of the
        `MBBitmapPixel` and no others. */
    MBBitmapPixelTypeAlpha,

    /*! The bitmap uses the `white` channel (`channel1`) and potentially the
        `alpha` channel (`channel4`) of the `MBBitmapPixel`. */
    MBBitmapPixelTypeMonochrome,
     
    /*! The bitmap uses the `red` (`channel1`), `green` (`channel2`) and `blue`
        (`channel3`) channels and potentially the `alpha` channel
        (`channel4`) of the `MBBitmapPixel`. */
    MBBitmapPixelTypeRGB
};

//!< use the `MBColorComponent` type for variables expressing color/alpha channel values
typedef unsigned char MBColorComponent;

/*!
 Provides a mechanism for accessing the color data for a single pixel.
 Correctly interpreting the color data requires knowing the associated
 `MBBitmapPixelPlane`'s `pixelType`.
 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
typedef struct {
    union
    {
        MBColorComponent red;
        MBColorComponent white;
        MBColorComponent channel1;
    };
    union
    {
        MBColorComponent green;
        MBColorComponent channel2;
    };
    union
    {
        MBColorComponent blue;
        MBColorComponent channel3;
    };
    union
    {
        MBColorComponent alpha;
        MBColorComponent channel4;
    };
} MBBitmapPixel;
#pragma clang diagnostic pop

/******************************************************************************/
#pragma mark -
#pragma mark MBBitmapPixelPlane class
/******************************************************************************/

/*!
 Represents a plane of pixels that can be accessed individually, regardless of
 the underlying pixel format. This allows code to access and manipulate bitmaps
 without needing to worry about the internal representation of the pixels.
 
 **Important:**
 
 * This class supports only integral pixels.
 * This class does not currently support floating-point channel values.
 * This class is only intended for use with iOS-compatible bitmaps.
 */
@interface MBBitmapPixelPlane : NSObject

/*----------------------------------------------------------------------------*/
#pragma mark Accessing bitmap information
/*!    @name Accessing bitmap information                                     */
/*----------------------------------------------------------------------------*/

/*! Returns the number of pixels in the bitmap. */
@property(nonatomic, readonly) NSUInteger pixelCount;

/*! Returns the number of columns in the bitmap. */
@property(nonatomic, readonly) NSUInteger columnCount;

/*! Returns the number of rows in the bitmap. */
@property(nonatomic, readonly) NSUInteger rowCount;

/*! Returns the number of color channels for each pixel in the bitmap. */
@property(nonatomic, readonly) NSUInteger channelsPerPixel;

/*! Returns the maximum value of an individual color component in the
    bitmap. */
@property(nonatomic, readonly) MBColorComponent channelMaximumValue;

/*! Returns the number of bytes required to represent each pixel in the
    bitmap. */
@property(nonatomic, readonly) NSUInteger bytesPerPixel;

/*! Returns the number of bytes required to represent the bitmap. */
@property(nonatomic, readonly) NSUInteger sizeInBytes;

/*! Returns a `MBBitmapPixelType` value indicating how the bitmap
    interprets pixel data. */
@property(nonatomic, readonly) MBBitmapPixelType pixelType;

/*----------------------------------------------------------------------------*/
#pragma mark Creating empty bitmaps
/*!    @name Creating empty bitmaps                                           */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new `MBBitmapPixelPlane` containing the specified number of
 rows and columns.
 
 The bitmap will use the device color space with 4 channel pixels (RGBA) 
 having 8 bits per channel using the device's native byte ordering.

 @param     cols The number of pixel columns in the returned bitmap.

 @param     rows The number of pixel rows in the returned bitmap.
 
 @return    A new `MBBitmapPixelPlane` instance with the specified settings.
            Returns `nil` if an error occurred.
 */
+ (nullable instancetype) bitmapWithColumns:(NSUInteger)cols rows:(NSUInteger)rows;

/*!
 Creates a new `MBBitmapPixelPlane` containing the specified number of
 rows and columns.
 
 The bitmap will use the device color space with 4 channel pixels (RGBA) 
 having 8 bits per channel using the device's native byte ordering.

 @param     size The size, in pixels, of the returned bitmap. Only integral
            values are used; fractional values encountered for the width or
            height will be rounded up to the next integer value.

 @return    A new `MBBitmapPixelPlane` instance with the specified settings.
            Returns `nil` if an error occurred.
 */
+ (nullable instancetype) bitmapWithSize:(CGSize)size;

/*!
 Creates a new `MBBitmapPixelPlane` having the specified settings.

 @param     size The size, in pixels, of the returned bitmap. Only integral
            values are used; fractional values encountered for the width or
            height will be rounded up to the next integer value.
 
 @param     bits The number of bits per color channel.
 
 @param     space The color space that will be used by the bitmap.
 
 @param     info The `CGBitmapInfo` flags describing the memory layout of the
            color channels.

 @return    A new `MBBitmapPixelPlane` instance with the specified settings.
            Returns `nil` if an error occurred.
 */
+ (nullable instancetype) bitmapWithSize:(CGSize)size
                          bitsPerChannel:(NSUInteger)bits
                              colorSpace:(nonnull CGColorSpaceRef)space
                              bitmapInfo:(CGBitmapInfo)info;

/*----------------------------------------------------------------------------*/
#pragma mark Creating bitmaps from images
/*!    @name Creating bitmaps from images                                     */
/*----------------------------------------------------------------------------*/

#if TARGET_OS_IPHONE

/*!
 Creates a new `MBBitmapPixelPlane` populated using the content of the image
 data contained in the `UIImage` instance provided.

 @param     image An image that will be used as the source content of the
            returned `MBBitmapPixelPlane`.

 @return    A new `MBBitmapPixelPlane` instance containing the image specified.
            Returns `nil` if an error occurred.
 */
+ (nullable instancetype) bitmapWithUIImage:(nonnull UIImage*)image;

#elif TARGET_OS_MAC

/*!
 Creates a new `MBBitmapPixelPlane` populated using the content of the image
 data contained in the `NSImage` instance provided.

 @param     image An image that will be used as the source content of the
            returned `MBBitmapPixelPlane`.

 @return    A new `MBBitmapPixelPlane` instance containing the image specified.
            Returns `nil` if an error occurred.
 */
+ (nullable instancetype) bitmapWithNSImage:(nonnull NSImage*)image;

#endif

/*!
 Creates a new `MBBitmapPixelPlane` populated using the content of the image
 data contained in the `CGImageRef` provided.

 @param     image An image that will be used as the source content of the
            returned `MBBitmapPixelPlane`.

 @return    A new `MBBitmapPixelPlane` instance containing the image specified.
            Returns `nil` if an error occurred.
 */
+ (nullable instancetype) bitmapWithCGImage:(nonnull CGImageRef)image;

/*! Creates a `MBBitmapPixelPlane` using the specified bitmap-based
    `CGContext` as a source. */

/*!
 Creates a new `MBBitmapPixelPlane` populated using the content of the bitmap
 image data contained in the `CGContextRef` provided.

 @param     bitmap A CoreGraphics context that will be used as the source 
            content of the returned `MBBitmapPixelPlane`. This context must
            be bitmap-based.

 @return    A new `MBBitmapPixelPlane` instance containing the image specified.
            Returns `nil` if an error occurred.
 */
+ (nullable instancetype) bitmapWithBitmapContext:(nonnull CGContextRef)bitmap;

/*----------------------------------------------------------------------------*/
#pragma mark Getting individual pixel data
/*!    @name Getting individual pixel data                                    */
/*----------------------------------------------------------------------------*/

/*!
 Retrieves the color channel values for the pixel at the specified column
 (x coordinate) and row (y coordinate).
 
 @param     pixelPtr A pointer to an `MBBitmapPixel` structure that will receive
            color data for the specified pixel if the method succeeds.

 @param     col The column of the pixel whose color data is being retrieved.

 @param     row The row of the pixel whose color data is being retrieved.

 @return    `YES` on success. `NO` will be returned if `pixel` is `nil` or if
            the specified pixel falls outside the bounds of the bitmap.
 */
- (BOOL) getPixel:(nonnull inout MBBitmapPixel*)pixelPtr atColumn:(NSUInteger)col row:(NSUInteger)row;

/*!
 Retrieves the color channel values for the pixel at the specified point.
 
 @param     pixelPtr A pointer to an `MBBitmapPixel` structure that will receive
            color data for the specified pixel if the method succeeds.

 @param     point The point specifying the x and y coordinates of the pixel
            whose color data is being retrieved. Only integral values are used;
            fractional values encountered for the x or y coordinate will be
            rounded to the closest integer value.

 @return    `YES` on success. `NO` will be returned if `pixel` is `nil` or if
            the specified pixel falls outside the bounds of the bitmap.
 */
- (BOOL) getPixel:(nonnull inout MBBitmapPixel*)pixelPtr atPoint:(CGPoint)point;

/*!
 Retrieves the color channel values for the pixel at the specified index.
 
 @param     pixelPtr A pointer to an `MBBitmapPixel` structure that will receive
            color data for the specified pixel if the method succeeds.

 @param     index The index of the pixel in the bitmap. The top-left pixel
            is index `0`, and the indices proceed from left-to-right then
            top-to-bottom.

 @return    `YES` on success. `NO` will be returned if `pixel` is `nil` or if
            the specified pixel falls outside the bounds of the bitmap.
 */
- (BOOL) getPixel:(nonnull inout MBBitmapPixel*)pixelPtr atIndex:(NSUInteger)index;

/*----------------------------------------------------------------------------*/
#pragma mark Setting individual pixel data
/*!    @name Setting individual pixel data                                    */
/*----------------------------------------------------------------------------*/

/*!
 Sets the color channel values for the pixel at the specified column (x
 coordinate) and row (y coordinate).
 
 Values provided in channels not supported by the underlying bitmap will be
 ignored.
 
 @param     pixel The `MBBitmapPixel` structure that specifies the new color
            channel values for the pixel.

 @param     col The column of the pixel whose color data is being retrieved.

 @param     row The row of the pixel whose color data is being retrieved.

 @return    `YES` on success. `NO` will be returned if the specified pixel
            falls outside the bounds of the bitmap.
 */
- (BOOL) setPixel:(MBBitmapPixel)pixel atColumn:(NSUInteger)col row:(NSUInteger)row;

/*!
 Sets the color channel values for the pixel at the specified point. 

 Values provided in channels not supported by the underlying bitmap will be
 ignored.
 
 @param     pixel The `MBBitmapPixel` structure that specifies the new color
            channel values for the pixel.

 @param     point The point specifying the x and y coordinates of the pixel
            whose color data is being set. Only integral values are used;
            fractional values encountered for the x or y coordinate will be
            rounded to the closest integer value.

 @return    `YES` on success. `NO` will be returned if the specified pixel
            falls outside the bounds of the bitmap.
 */
- (BOOL) setPixel:(MBBitmapPixel)pixel atPoint:(CGPoint)point;

/*!
 Sets the color channel values for the pixel at the specified index.

 Values provided in channels not supported by the underlying bitmap will be
 ignored.
 
 @param     pixel The `MBBitmapPixel` structure that specifies the new color
            channel values for the pixel.

 @param     index The index of the pixel in the bitmap. The top-left pixel
            is index `0`, and the indices proceed from left-to-right then
            top-to-bottom.

 @return    `YES` on success. `NO` will be returned if the specified pixel
            falls outside the bounds of the bitmap.
 */
- (BOOL) setPixel:(MBBitmapPixel)pixel atIndex:(NSUInteger)index;

/*----------------------------------------------------------------------------*/
#pragma mark Creating an image representation of the bitmap
/*!    @name Creating an image representation of the bitmap                   */
/*----------------------------------------------------------------------------*/

#if MB_BUILD_IOS

/*!
 Creates a `UIImage` instance containing a visual representation of the current
 contents of the receiver.

 @return        A new `UIImage`.
 */
- (nonnull UIImage*) image;

#elif MB_BUILD_MAC

/*!
 Creates an `NSImage` instance containing a visual representation of the current
 contents of the receiver.

 @return        A new `NSImage`.
 */
- (nonnull NSImage*) image;

#endif

@end
