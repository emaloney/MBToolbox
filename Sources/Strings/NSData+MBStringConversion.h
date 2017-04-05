//
//  NSData+MBStringConversion.h
//  Mockingbird Toolbox
//
//  Created by Jesse Boyes on 8/16/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

/******************************************************************************/
#pragma mark -
#pragma mark NSData extensions for string conversion
/******************************************************************************/

/*!
 An `NSData` class extension that adds methods for converting between
 `NSString` and `NSData` instances.
 */
@interface NSData (MBStringConversion)

/*----------------------------------------------------------------------------*/
#pragma mark Converting to and from hexadecimal representation
/*!    @name Converting to and from hexadecimal representation                */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new `NSData` instance by interpreting the passed-in string as
 a hexadecimal-encoded byte array.
 
 @param     hexString The string to interpret as a hexadecimal representation
            of byte data.

 @return    An `NSData` instance, or `nil` if `hexString` could not be
            intepreted as hexadecimal.
 */
+ (nullable NSData*) dataWithHexString:(nonnull NSString*)hexString;

/*!
 Returns a string containing a hexadecimal representation of the bytes
 contained in the receiver.
 
 @return    A hex string.
 */
- (nonnull NSString*) toStringHex;

/*----------------------------------------------------------------------------*/
#pragma mark Interpreting bytes as strings
/*!    @name Interpreting bytes as strings                                    */
/*----------------------------------------------------------------------------*/

/*!
 Interprets the receiver as a byte-encoded string using the given encoding.
 
 @param     encoding The `NSStringEncoding` to use for interpreting the
            receiver.

 @return    An `NSString` containing the receiver's bytes interpreted
            as the specified encoding, or `nil` if the receiver could
            not be interpreted using that encoding.
 */
- (nullable NSString*) toStringUsingEncoding:(NSStringEncoding)encoding;

/*!
 Interprets the receiver as a byte-encoded ASCII string.

 @return    An `NSString` containing the receiver's bytes interpreted
            in ASCII format.
 */
- (nullable NSString*) toStringASCII;

/*!
 Interprets the receiver as a byte-encoded UTF-8 string.

 @return    An `NSString` containing the receiver's bytes interpreted
            in UTF-8 format.
 */
- (nullable NSString*) toStringUTF8;

/*!
 An alias for the `toStringUTF8` method.
 
 @return    An `NSString` containing the receiver's bytes interpreted
            in UTF-8 format.
 */
- (nullable NSString*) toString;

@end
