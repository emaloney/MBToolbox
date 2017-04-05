//
//  MBFormattedDescriptionObject.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/17/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBFieldListFormatter.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBFormattedDescription protocol
/******************************************************************************/

/*!
 Adopted by classes that utilize an `MBFieldListFormatter` instance to create
 formatted output for an object's `description` method.
 */
@protocol MBFormattedDescription <NSObject>

/*!
 Asks the receiver to add any relevant fields to the passed-in
 `MBFieldListFormatter` instance.
 
 @param     fmt The formatter to which description fields should be added.
 */
- (void) addDescriptionFieldsTo:(nonnull MBFieldListFormatter*)fmt;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFormattedDescriptionObject class
/******************************************************************************/

/*!
 Provides support for basing an object's `description` method on the
 `MBFieldListFormatter`, for giving objects a way to create more legible
 console log output.
 
 Intended to make debugging more efficient by making it easier to see
 what's inside an object.
 */
@interface MBFormattedDescriptionObject : NSObject <MBFormattedDescription>

/*----------------------------------------------------------------------------*/
#pragma mark Constructing the description
/*!    @name Constructing the description                                     */
/*----------------------------------------------------------------------------*/

/*!
Asks the receiver to add any relevant fields to the passed-in
`MBFieldListFormatter` instance.
 
 @note      Subclasses should call `super` prior to adding their own fields.

 @param     fmt The formatter to which description fields should be added.
*/
- (void) addDescriptionFieldsTo:(nonnull MBFieldListFormatter*)fmt;

/*----------------------------------------------------------------------------*/
#pragma mark Debugging output
/*!    @name Debugging output                                                 */
/*----------------------------------------------------------------------------*/

/*!
 Implemented by subclasses that wish to provide an additional means of 
 identifying an object instance within the debug console.

 The default implementation returns `nil`.
 
 @return    If a non-`nil` value is returned by this method, a field named
            "`debugDescriptor`" will be added to the `consoleDescription`.
 */
- (nullable NSString*) debugDescriptor;

/*!
 Uses an `MBFieldListFormatter` instance in conjunction with the
 `addDescriptionFieldsTo:` method to construct a description of the
 receiver intended for output to the console.
 
 @return    The console description.
 */
- (nonnull NSString*) consoleDescription;

/*!
 Writes the output of the receiver's `consoleDescription` method to the console
 log.
 */
- (void) dump;

/*----------------------------------------------------------------------------*/
#pragma mark Object description
/*!    @name Object description                                               */
/*----------------------------------------------------------------------------*/

/*!
 Overrides the `NSObject` implementation to return the output of 
 `consoleDescription`.
 
 @return    The return value of calling the `consoleDescription`
 */
- (nonnull NSString*) description;

@end
