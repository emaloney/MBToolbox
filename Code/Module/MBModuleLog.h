//
//  MBModuleLog.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/30/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "Mockingbird-Toolbox.h"

@protocol MBModule;

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleLog class
/******************************************************************************/

/*!
 Instances of this class are used to issue log messages associated with a 
 given `MBModule`.
 */
@interface MBModuleLog : NSObject

/*******************************************************************************
 @name Object lifecycle
 ******************************************************************************/

/*!
 Creates and returns a new `MBModuleLog` instance for the specified module
 implementation class.

 @note      This method is intended to be used only by `MBModule` 
            implementations themselves. To retrieve the `MBModuleLog` for
            a given module, acquire it from the module itself.

 @param     moduleCls The implementing class of the `MBModule` for which a
            log is being created.

 @return    A new `MBModuleLog`.
 */
+ (instancetype) logForModuleClass:(Class)moduleCls;

/*!
 Creates and returns a new `MBModuleLog` instance for the specified module.

 @note      This method is intended to be used only by `MBModule` 
            implementations themselves. To retrieve the `MBModuleLog` for
            a given module, acquire it from the module itself.

 @param     module The `MBModule` for which a log is being created.

 @return    A new `MBModuleLog`.
 */
+ (instancetype) logForModule:(NSObject<MBModule>*)module;

/*******************************************************************************
 @name Warnings & Errors
 ******************************************************************************/

/*!
 Issues a deprecation warning from the module associated with the receiver.

 @param     warning The warning message.

 @note      The warning will be written to the console, possibly asynchronously.
            Repeated issuances of the same warning may be squelched.
 */
- (void) issueDeprecationWarning:(NSString*)warning;

/*!
 Issues a deprecation warning from the module associated with the receiver.

 @param     format The format for the warning message, followed by zero or more
            format parameters.
 
 @param     ... A variable argument list of zero or more values referenced
            within the `format` string.

 @note      The warning will be written to the console, possibly asynchronously.
            Repeated issuances of the same warning may be squelched.
 */
- (void) issueDeprecationWarningWithFormat:(NSString*)format, ...;

/*!
 Issues a not supported error from the module associated with the receiver.

 @param     error The error message.

 @note      The error will be written to the console, possibly asynchronously.
            Repeated issuances of the same error may be squelched.
 */
- (void) issueNotSupportedError:(NSString*)error;

/*!
 Issues a not supported error from the module associated with the receiver.

 @param     format The format for the error message, followed by zero or more
            format parameters.

 @param     ... A variable argument list of zero or more values referenced
            within the `format` string.

 @note      The error will be written to the console, possibly asynchronously.
            Repeated issuances of the same error may be squelched.
 */
- (void) issueNotSupportedErrorWithFormat:(NSString*)format, ...;

@end
