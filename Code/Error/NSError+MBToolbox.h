//
//  NSError+MBToolbox.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/2/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "Mockingbird-Toolbox.h"

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

extern NSString* const kMBErrorDomain;                      //!< @"MockingbirdErrorDomain"

// NSError user info keys
extern NSString* const kMBErrorUserInfoKeyURL;              //!< @"URL"
extern NSString* const kMBErrorUserInfoKeyFilePath;         //!< @"filePath"
extern NSString* const kMBErrorUserInfoKeyException;        //!< @"exception"
extern NSString* const kMBErrorUserInfoKeyExceptionName;    //!< @"exceptionName"
extern NSString* const kMBErrorUserInfoKeyExceptionReason;  //!< @"exceptionReason"

// error codes
extern const NSInteger kMBErrorException;                   //!< 100
extern const NSInteger kMBErrorCouldNotLoadFile;            //!< 101
extern const NSInteger kMBErrorInvalidArgument;             //!< 102
extern const NSInteger kMBErrorParseFailed;                 //!< 103
extern const NSInteger kMBErrorRequestCancelled;            //!< 104
extern const NSInteger kMBErrorNotCompleted;                //!< 105
extern const NSInteger kMBErrorAmbiguousFrame;              //!< 106
extern const NSInteger kMBErrorInvalidImageData;            //!< 107
extern const NSInteger kMBErrorMessageInDescription;        //!< 999 - generic error code indicating the error's details are in the localized description

/******************************************************************************/
#pragma mark Mockingbird NSError category
/******************************************************************************/

/*!
 An `NSError` class extension that provides Mockingbird-specific functionality.
 */
@interface NSError (MBToolbox)

/*----------------------------------------------------------------------------*/
#pragma mark Creating errors in the Mockingbird error domain
/*!    @name Creating errors in the Mockingbird error domain                  */
/*----------------------------------------------------------------------------*/

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.
 
 @param     code The error code.
 
 @return    A new `NSError` instance with the specified settings.
 */
+ (NSError*) mockingbirdErrorWithCode:(NSInteger)code;

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.
 
 @param     code The error code.
 
 @param     dict The user info dictionary for the returned error.
 
 @return    A new `NSError` instance with the specified settings.
 */
+ (NSError*) mockingbirdErrorWithCode:(NSInteger)code userInfo:(NSDictionary*)dict;

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.
 
 The error's user info dictionary will contain the specified key and value.

 @param     code The error code.
 
 @param     key The key whose corresponding value will be stored in the
            returned error's user info dictionary.

 @param     val The value that will be associated with `key`.

 @return    A new `NSError` instance with the specified settings.
 */
+ (NSError*) mockingbirdErrorWithCode:(NSInteger)code userInfoKey:(NSString*)key value:(id)val;

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.
 
 The error's code will be `kMBErrorMessageInDescription`.

 @param     desc The description of the error, which will be available through
            the user info key `NSLocalizedDescriptionKey` as well as the
            error's `localizedDescription` method.

 @return    A new `NSError` instance with the specified settings.
 */
+ (NSError*) mockingbirdErrorWithDescription:(NSString*)desc;

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.

 @param     desc The description of the error, which will be available through
            the user info key `NSLocalizedDescriptionKey` as well as the
            error's `localizedDescription` method.

 @param     code The error code.

 @return    A new `NSError` instance with the specified settings.
 */
+ (NSError*) mockingbirdErrorWithDescription:(NSString*)desc code:(NSInteger)code;

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.

 The error's user info dictionary will contain the specified key and value.

 @param     desc The description of the error, which will be available through
            the user info key `NSLocalizedDescriptionKey` as well as the
            error's `localizedDescription` method.

 @param     code The error code.

 @param     key The key whose corresponding value will be stored in the
            returned error's user info dictionary.

 @param     val The value that will be associated with `key`.

 @return    A new `NSError` instance with the specified settings.
 */
+ (NSError*) mockingbirdErrorWithDescription:(NSString*)desc code:(NSInteger)code userInfoKey:(NSString*)key value:(id)val;

/*!
 Constructs a new `NSError` instance in the error domain specified by the
 `kMBErrorDomain` constant.
 
 The error will encapsulate the passed-in exception.
 
 @param     ex The `NSException` to wrap in the returned error.

 @return    A new `NSError` instance with the specified settings.
 */
+ (NSError*) mockingbirdErrorWithException:(NSException*)ex;

/*----------------------------------------------------------------------------*/
#pragma mark Creating derived errors
/*!    @name Creating derived errors                                          */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new `NSError` instance by adding the specified user info 
 dictionary value to that of the receiver.
 
 @param     key The key whose corresponding value will be stored in the
            returned error's user info dictionary.

 @param     val The value that will be associated with `key`.

 @return    A new `NSError` instance with the same settings as the receiver,
            but with the specified user info value added.
 */
- (NSError*) errorByAddingUserInfoKey:(NSString*)key value:(id)val;

@end
