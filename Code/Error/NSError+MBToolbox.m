//
//  NSError+MBToolbox.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/2/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "NSError+MBToolbox.h"

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

+ (NSError*) mockingbirdErrorWithCode:(NSInteger)code
{
    debugTrace();

    return [NSError errorWithDomain:kMBErrorDomain code:code userInfo:nil];
}

+ (NSError*) mockingbirdErrorWithCode:(NSInteger)code userInfo:(NSDictionary*)dict
{
    debugTrace();
    
    return [NSError errorWithDomain:kMBErrorDomain code:code userInfo:dict];
}

+ (NSError*) mockingbirdErrorWithCode:(NSInteger)code userInfoKey:(NSString*)key value:(id)val
{
    debugTrace();
    
    return [NSError errorWithDomain:kMBErrorDomain
                               code:code
                           userInfo:@{key: val}];
}

+ (NSError*) mockingbirdErrorWithDescription:(NSString*)desc
{
    return [self mockingbirdErrorWithDescription:desc code:kMBErrorMessageInDescription];
}

+ (NSError*) mockingbirdErrorWithDescription:(NSString*)desc code:(NSInteger)code
{
    debugTrace();
    
    return [NSError errorWithDomain:kMBErrorDomain
                               code:code
                           userInfo:@{NSLocalizedDescriptionKey: desc}];
}

+ (NSError*) mockingbirdErrorWithDescription:(NSString*)desc code:(NSInteger)code userInfoKey:(NSString*)key value:(id)val
{
    debugTrace();

    if (!key || !val) {
        return [self mockingbirdErrorWithDescription:desc code:code];
    }

    return [NSError errorWithDomain:kMBErrorDomain
                               code:code
                           userInfo:@{NSLocalizedDescriptionKey: desc,
                                      key: val}];
}

+ (NSError*) mockingbirdErrorWithException:(NSException*)ex
{
    debugTrace();
    
    NSMutableDictionary* userInfo = [NSMutableDictionary dictionary];
    userInfo[kMBErrorUserInfoKeyException] = ex;
    userInfo[kMBErrorUserInfoKeyExceptionName] = [ex name];
    userInfo[kMBErrorUserInfoKeyExceptionReason] = [ex reason];
    userInfo[NSLocalizedDescriptionKey] = [ex reason];
    
    return [NSError errorWithDomain:kMBErrorDomain
                               code:kMBErrorException
                           userInfo:userInfo];
}

- (NSError*) errorByAddingUserInfoKey:(NSString*)key value:(id)val
{
    debugTrace();

    if (key) {
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
    return self;
}

@end
