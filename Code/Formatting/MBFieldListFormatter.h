//
//  MBFieldListFormatter.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 3/20/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

extern const NSUInteger kMBFieldListDefaultTruncateAtCharacter;

/******************************************************************************/
#pragma mark -
#pragma mark MBFieldListFormatter class
/******************************************************************************/

/*!
 An object that, for monospaced fonts, outputs a list of fields in an 
 easy-to-read format. This class is typically used in debugging.

 Instances can be created directly via `new` or, when being used to represent
 a particular object instance, using the `formatterForObject:` factory method.

 @note Classes can also inherit from `MBFormattedDescriptionObject` to allow its
 `description` method to be driven by an `MBFieldListFormatter`. This makes
 it easy for a class to create nicely-formatted output for use in the console
 when debugging.
 */
@interface MBFieldListFormatter : NSObject

/*----------------------------------------------------------------------------*/
#pragma mark Acquiring instances
/*!    @name Acquiring instances                                              */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new formatter to use for generating a debugging description for
 the specified object.
 
 The passed-in object is used to set the first field of the returned
 formatter. The field name will be the name of the class of `obj`, and
 the value will be a hexadecimal representation of the object's memory
 address.

 Using a `MBFieldListFormatter` in this way is typically done to implement
 an object's `description` method.
 
 @param     obj The object whose fields are being formatted.
 
 @return    A new `MBFieldListFormatter`.
 */
+ (nonnull instancetype) formatterForObject:(nonnull id)obj;

/*----------------------------------------------------------------------------*/
#pragma mark Adding field values
/*!    @name Adding field values                                              */
/*----------------------------------------------------------------------------*/

/*!
 Sets an object instance field on the formatter.

 The object `val` is represented by the return value of its `description` 
 method.

 @param     fieldName The name of the field to add.

 @param     val An object instance representing the field value.
 */
- (void) setField:(nonnull NSString*)fieldName value:(nullable id)val;

/*!
 Sets a string field on the formatter. The string is truncated if it is
 longer than the number of characters specified by the value of the constant
 `kMBFieldListDefaultTruncateAtCharacter`.

 If the field value is truncated, it is represented with the appended string
 "`... (# more chars)`" where *#* represents the number of characters
 that were removed by the truncation process.

 @param     fieldName The name of the field to add.
 
 @param     val A string representing the field value.
 */
- (void) setField:(nonnull NSString*)fieldName byTruncating:(nonnull NSString*)val;

/*!
 Sets a string field on the formatter. The string is truncated if it is
 longer than `truncateAt` characters.
 
 If the field value is truncated, it is represented with the appended string
 "`... (# more chars)`" where *#* represents the number of characters
 that were removed by the truncation process.
 
 @param     fieldName The name of the field to add.
 
 @param     val A string representing the field value.
 
 @param     truncateAt The index of the character at which `val` will be
            truncated. The portion of the string `val` starting with the
            character at index `truncatAt` will not be included in the
            value stored in the formatter.
 */
- (void) setField:(nonnull NSString*)fieldName
     byTruncating:(nonnull NSString*)val
      atCharacter:(NSUInteger)truncateAt;

/*!
 Sets an object instance field on the formatter.
 
 The object `val` is represented with its class name and memory address.

 @param     fieldName The name of the field to add.
 
 @param     obj An object instance representing the field value.
 */
- (void) setField:(nonnull NSString*)fieldName instance:(nullable id)obj;

/*!
 Sets an debug object instance field on the formatter.

 The object `val` is represented with its class name, memory address
 and an optional debug descriptor. The debug descriptor is included if 
 `obj` responds to the `debugDescriptor` selector.

 @param     fieldName The name of the field to add.

 @param     obj An object instance representing the field value.
 */
- (void) setField:(nonnull NSString*)fieldName debug:(nullable id)obj;

/*!
 Sets a memory pointer field on the formatter.

 @param     fieldName The name of the field to add.
 
 @param     ptr A pointer representing the field value.
 */
- (void) setField:(nonnull NSString*)fieldName pointer:(nullable void*)ptr;

/*!
 Sets a boolean field on the formatter.

 @param     fieldName The name of the field to add.

 @param     val The boolean field value.
 */
- (void) setField:(nonnull NSString*)fieldName boolean:(BOOL)val;

/*!
 Sets a container field on the formatter. Containers are objects such as
 `NSArray`, `NSSet`, and `NSDictionary` that respond to the selector `count`.

 A container is represented with its class name, memory address and the
 count of its contents.

 @param     fieldName The name of the field to add.
 
 @param     val A container object instance representing the field value.
 */
- (void) setField:(nonnull NSString*)fieldName container:(nullable id)val;

/*!
 Sets a field on the receiver for each key/value pair contained in the
 passed-in dictionary.
 
 @param     fields The dictionary whose key/value pairs will be added as
            fields.
 */
- (void) setFields:(nonnull NSDictionary*)fields;

/*----------------------------------------------------------------------------*/
#pragma mark Truncating strings
/*!    @name Truncating strings                                               */
/*----------------------------------------------------------------------------*/

/*!
 Truncates the string `val` at the character index `truncateAt` if `val` the
 length of the string is greater than `truncateAt`.

 @note      This is intended to be used for visual formatting, not for
            ensuring that `val` is a specified length. Truncated strings
            will have some additional information appended, to make it clear
            that the string was truncated. As a result, if a string is truncated
            by this method, the returned string will be longer than 
            `truncateAt`.

 @param     val The value to (possibly) truncate.
 
 @param     truncateAt The index of the character at which `val` should be
            truncated.
 */
+ (nonnull NSString*) truncateString:(nonnull NSString*)val atCharacter:(NSUInteger)truncateAt;

/*----------------------------------------------------------------------------*/
#pragma mark Converting the fields into strings
/*!    @name Converting the fields into strings                               */
/*----------------------------------------------------------------------------*/

/*!
 Converts the fields in the receiver into a string representation.

 @return    The string representation of the receiver's fields.
 */
- (nonnull NSString*) asString;

/*!
 Converts the fields in the receiver into a string representation.
 
 The passed-in string `indentation` will appear before each line in the
 returned string.

 @param     indentation The indentation prefix to use for the output.

 @return    The string representation of the receiver's fields.
 */
- (nonnull NSString*) asStringWithIndentation:(nonnull NSString*)indentation;

/*!
 Converts the fields in the receiver into a string representation.

 Each line in the returned string is prefixed with a tab (`0x09`) character.

 @return    The string representation of the receiver's fields.
 */
- (nonnull NSString*) asStringWithIndentation;

/*----------------------------------------------------------------------------*/
#pragma mark Debugging output
/*!    @name Debugging output                                                 */
/*----------------------------------------------------------------------------*/

/*!
 Returns the field list in a format suitable for the implementation of
 an object's `description` method.
 
 This method returns a string containing the output of `asStringWithIndentation`
 prefixed and suffixed with carriage returns to make it stand out more in 
 console output.

 @return    The description.
 */
- (nonnull NSString*) asDescription;

@end
