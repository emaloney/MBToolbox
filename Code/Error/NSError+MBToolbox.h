//
//  NSError+MBToolbox.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/2/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

/*! To avoid the pain of this declaration, we'll use `NSErrorPtrPtr` for
 specifying the `NSError**` type. */
typedef NSError *__autoreleasing  __nullable * __nullable NSErrorPtrPtr;

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

extern NSString* const __nonnull kMBErrorDomain;                      //!< @"MockingbirdErrorDomain"

// NSError user info keys
extern NSString* const __nonnull kMBErrorUserInfoKeyURL;              //!< @"URL"
extern NSString* const __nonnull kMBErrorUserInfoKeyFilePath;         //!< @"filePath"
extern NSString* const __nonnull kMBErrorUserInfoKeyException;        //!< @"exception"
extern NSString* const __nonnull kMBErrorUserInfoKeyExceptionName;    //!< @"exceptionName"
extern NSString* const __nonnull kMBErrorUserInfoKeyExceptionReason;  //!< @"exceptionReason"

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
+ (nonnull NSError*) mockingbirdErrorWithCode:(NSInteger)code;

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.
 
 @param     code The error code.
 
 @param     dict The user info dictionary for the returned error.
 
 @return    A new `NSError` instance with the specified settings.
 */
+ (nonnull NSError*) mockingbirdErrorWithCode:(NSInteger)code userInfo:(nullable NSDictionary*)dict;

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
+ (nonnull NSError*) mockingbirdErrorWithCode:(NSInteger)code userInfoKey:(nonnull NSString*)key value:(nonnull id)val;

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.
 
 The error's code will be `kMBErrorMessageInDescription`.

 @param     desc The description of the error, which will be available through
            the user info key `NSLocalizedDescriptionKey` as well as the
            error's `localizedDescription` method.

 @return    A new `NSError` instance with the specified settings.
 */
+ (nonnull NSError*) mockingbirdErrorWithDescription:(nonnull NSString*)desc;

/*!
 Constructs a new `NSError` instance in the error domain specified by the 
 `kMBErrorDomain` constant.

 @param     desc The description of the error, which will be available through
            the user info key `NSLocalizedDescriptionKey` as well as the
            error's `localizedDescription` method.

 @param     code The error code.

 @return    A new `NSError` instance with the specified settings.
 */
+ (nonnull NSError*) mockingbirdErrorWithDescription:(nonnull NSString*)desc code:(NSInteger)code;

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
+ (nonnull NSError*) mockingbirdErrorWithDescription:(nonnull NSString*)desc code:(NSInteger)code userInfoKey:(nonnull NSString*)key value:(nonnull id)val;

/*!
 Constructs a new `NSError` instance in the error domain specified by the
 `kMBErrorDomain` constant.
 
 The error will encapsulate the passed-in exception.
 
 @param     ex The `NSException` to wrap in the returned error.

 @return    A new `NSError` instance with the specified settings.
 */
+ (nonnull NSError*) mockingbirdErrorWithException:(nonnull NSException*)ex;

/*----------------------------------------------------------------------------*/
#pragma mark Creating derived errors
/*!    @name Creating derived errors                                          */
/*----------------------------------------------------------------------------*/

/*!
 Creates and returns a new `NSError` instance based on the receiver by adding
 or removing the user info dictionary value for the given key.
 
 @param     key The key whose corresponding value will be stored in the
            returned error's user info dictionary.

 @param     val The value that will be associated with `key`. If `nil`, any
            existing value for `key` will be removed instead.

 @return    A new `NSError` instance with the same settings as the receiver,
            but with the specified user info value added.
 */
- (nonnull NSError*) errorByAddingOrRemovingUserInfoKey:(nonnull NSString*)key value:(nullable id)val;

@end
