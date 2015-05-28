//
//  MBModuleLog.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/30/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MBModule;

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleLogSeverity protocol
/******************************************************************************/

/*!
 Specifies the relative importance of a log message.
 */
typedef NS_ENUM(NSUInteger, MBModuleLogSeverity) {
    /*! The lowest severity, used for detailed or frequently occurring 
        debugging and diagnostic information. Not intended for use in
        production code. */
    MBModuleLogSeverityVerbose  = 1,

    /*! Used for debugging and diagnostic information. Not intended for 
        use in production code. */
    MBModuleLogSeverityDebug    = 2,

    /*! Used to indicate something of interest that is not problematic. */
    MBModuleLogSeverityInfo     = 3,

    /*! Used to indicate that something appears amiss and potentially 
        problematic. The situation bears looking into before a larger
        problem arises. */
    MBModuleLogSeverityWarning  = 4,

    /*! The highest severity, used to indicate that something has gone wrong; 
        a fatal error may be imminent. */
    MBModuleLogSeverityError    = 5
};

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleLogRecorder protocol
/******************************************************************************/

/*!
 This protocol is adopted by classes that wish to be used as loggers by the
 `MBModuleLog`.
 */
@protocol MBModuleLogRecorder <NSObject>

/*!
 Records the log message to the underlying logging subsystem. 
 
 @param     msg The message to record.
 
 @param     severity The severity level of the log message.

 @param     caller The object responsible for issuing this request to
            log `msg`. May be `nil` if not called from an object scope.
 
 @param     signature The signature of the calling method or function.
 
 @param     filePath The filesystem path of the source code file containing
            the calling method or function.
 
 @param     fileLine The line number within `filePath` specifying the
            location of the code responsible for this request to log `msg`.
 */
+ (void) logMessage:(nonnull NSString*)msg
         atSeverity:(MBModuleLogSeverity)severity
      callingObject:(nullable id)caller
   callingSignature:(nonnull NSString*)signature
    callingFilePath:(nonnull NSString*)filePath
    callingFileLine:(NSUInteger)fileLine;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleLog class
/******************************************************************************/

/*!
 Instances of this class are used to issue log messages associated with a 
 given `MBModule`.
 */
@interface MBModuleLog : NSObject < MBModuleLogRecorder >

/*******************************************************************************
 @name MBModuleLogRecorder support
 ******************************************************************************/

/*!
 Sets the logger class used to log messages through `MBModuleLog`. By
 default, `MBModuleLog` is the logger class, unless overridden by a call
 to this method.
 
 @param     logRecorderClass The `Class` implementing `MBModuleLogRecorder` that
            should be used as the logger. If `nil` is passed, the value is
            reset to the default of `MBModuleLog`.
 */
+ (void) setLogRecorderClass:(nullable Class<MBModuleLogRecorder>)logRecorderClass;

/*!
 Returns the logger class used to log messages through `MBModuleLog`.
 */
+ (nonnull Class<MBModuleLogRecorder>) logRecorderClass;

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
+ (nonnull instancetype) logForModuleClass:(nonnull Class)moduleCls;

/*!
 Creates and returns a new `MBModuleLog` instance for the specified module.

 @note      This method is intended to be used only by `MBModule` 
            implementations themselves. To retrieve the `MBModuleLog` for
            a given module, acquire it from the module itself.

 @param     module The `MBModule` for which a log is being created.

 @return    A new `MBModuleLog`.
 */
+ (nonnull instancetype) logForModule:(nonnull NSObject<MBModule>*)module;

/*******************************************************************************
 @name Warnings & Errors
 ******************************************************************************/

/*!
 Issues a deprecation warning from the module associated with the receiver.

 @param     warning The warning message.

 @note      The warning will be written to the console, possibly asynchronously.
            Repeated issuances of the same warning may be squelched.
 */
- (void) issueDeprecationWarning:(nonnull NSString*)warning;

/*!
 Issues a deprecation warning from the module associated with the receiver.

 @param     format The format for the warning message, followed by zero or more
            format parameters.
 
 @param     ... A variable argument list of zero or more values referenced
            within the `format` string.

 @note      The warning will be written to the console, possibly asynchronously.
            Repeated issuances of the same warning may be squelched.
 */
- (void) issueDeprecationWarningWithFormat:(nonnull NSString*)format, ...;

/*!
 Issues a not supported error from the module associated with the receiver.

 @param     error The error message.

 @note      The error will be written to the console, possibly asynchronously.
            Repeated issuances of the same error may be squelched.
 */
- (void) issueNotSupportedError:(nonnull NSString*)error;

/*!
 Issues a not supported error from the module associated with the receiver.

 @param     format The format for the error message, followed by zero or more
            format parameters.

 @param     ... A variable argument list of zero or more values referenced
            within the `format` string.

 @note      The error will be written to the console, possibly asynchronously.
            Repeated issuances of the same error may be squelched.
 */
- (void) issueNotSupportedErrorWithFormat:(nonnull NSString*)format, ...;

@end
