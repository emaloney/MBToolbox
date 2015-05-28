//
//  NSError+MBToolbox.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/2/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "NSError+MBToolbox.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark Constants (public)
/******************************************************************************/

NSString* const kMBErrorDomain             = @"MockingbirdErrorDomain";

NSString* const kMBErrorUserInfoKeyURL              = @"URL";
NSString* const kMBErrorUserInfoKeyFilePath         = @"filePath";
NSString* const kMBErrorUserInfoKeyException        = @"exception";
NSString* const kMBErrorUserInfoKeyExceptionName    = @"exceptionName";
NSString* const kMBErrorUserInfoKeyExceptionReason  = @"exceptionReason";

const NSInteger kMBErrorException                   = 100;
const NSInteger kMBErrorCouldNotLoadFile            = 101;
const NSInteger kMBErrorInvalidArgument             = 102;
const NSInteger kMBErrorParseFailed                 = 103;
const NSInteger kMBErrorRequestCancelled        	= 104;
const NSInteger kMBErrorNotCompleted            	= 105;
const NSInteger kMBErrorAmbiguousFrame            	= 106;
const NSInteger kMBErrorInvalidImageData            = 107;
const NSInteger kMBErrorMessageInDescription    	= 999;

/******************************************************************************/
#pragma mark Creating Mockingbird errors
/******************************************************************************/

@implementation NSError (MBToolbox)

+ (nonnull NSError*) mockingbirdErrorWithCode:(NSInteger)code
{
    MBLogDebugTrace();

    return [NSError errorWithDomain:kMBErrorDomain code:code userInfo:nil];
}

+ (nonnull NSError*) mockingbirdErrorWithCode:(NSInteger)code userInfo:(nullable NSDictionary*)dict
{
    MBLogDebugTrace();
    
    return [NSError errorWithDomain:kMBErrorDomain code:code userInfo:dict];
}

+ (nonnull NSError*) mockingbirdErrorWithCode:(NSInteger)code userInfoKey:(nonnull NSString*)key value:(nonnull id)val
{
    MBLogDebugTrace();
    
    return [NSError errorWithDomain:kMBErrorDomain
                               code:code
                           userInfo:@{key: val}];
}

+ (nonnull NSError*) mockingbirdErrorWithDescription:(nonnull NSString*)desc
{
    return [self mockingbirdErrorWithDescription:desc code:kMBErrorMessageInDescription];
}

+ (nonnull NSError*) mockingbirdErrorWithDescription:(nonnull NSString*)desc code:(NSInteger)code
{
    MBLogDebugTrace();
    
    return [NSError errorWithDomain:kMBErrorDomain
                               code:code
                           userInfo:@{NSLocalizedDescriptionKey: desc}];
}

+ (nonnull NSError*) mockingbirdErrorWithDescription:(nonnull NSString*)desc code:(NSInteger)code userInfoKey:(nonnull NSString*)key value:(id)val
{
    MBLogDebugTrace();

    return [NSError errorWithDomain:kMBErrorDomain
                               code:code
                           userInfo:@{NSLocalizedDescriptionKey: desc,
                                      key: val}];
}

+ (nonnull NSError*) mockingbirdErrorWithException:(nonnull NSException*)ex
{
    MBLogDebugTrace();
    
    NSMutableDictionary* userInfo = [NSMutableDictionary dictionary];
    userInfo[kMBErrorUserInfoKeyException] = ex;
    userInfo[kMBErrorUserInfoKeyExceptionName] = [ex name];
    userInfo[kMBErrorUserInfoKeyExceptionReason] = [ex reason];
    userInfo[NSLocalizedDescriptionKey] = [ex reason];
    
    return [NSError errorWithDomain:kMBErrorDomain
                               code:kMBErrorException
                           userInfo:userInfo];
}

- (nonnull NSError*) errorByAddingOrRemovingUserInfoKey:(nonnull NSString*)key value:(nullable id)val
{
    MBLogDebugTrace();

    NSMutableDictionary* userInfo = [self.userInfo mutableCopy];
    if (!userInfo) {
        userInfo = [NSMutableDictionary new];
    }
    if (val) {
        userInfo[key] = val;
    } else {
        [userInfo removeObjectForKey:key];
    }

    return [[self class] errorWithDomain:self.domain code:self.code userInfo:userInfo];
}

@end
