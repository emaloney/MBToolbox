//
//  MBThreadLocalStorage.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/7/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "MBThreadLocalStorage.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark MBThreadLocalStorage implementation
/******************************************************************************/

@implementation MBThreadLocalStorage

/******************************************************************************/
#pragma mark Private 
/******************************************************************************/

+ (NSString*) _storageKeyForClass:(Class)cls withUserKey:(NSString*)userKey
{
    assert(cls);
    
    if (!userKey) {
        return [NSString stringWithFormat:@"%@.%@", self, cls];
    } else {
        return [NSString stringWithFormat:@"%@.%@.%@", self, cls, userKey];
    }
}

/******************************************************************************/
#pragma mark Memory management
/******************************************************************************/

+ (nullable id) valueForClass:(nonnull Class)cls
{
    return [self valueForClass:cls withKey:nil];
}

+ (nullable id) valueForClass:(nonnull Class)cls withKey:(nullable NSString*)key
{
    MBLogDebugTrace();
    
    NSString* storageKey = [self _storageKeyForClass:cls withUserKey:key];
    
    return [[NSThread currentThread] threadDictionary][storageKey];
}

+ (void) setValue:(nullable id)val forClass:(nonnull Class)cls
{
    return [self setValue:val forClass:cls withKey:nil];
}

+ (void) setValue:(nullable id)val forClass:(nonnull Class)cls withKey:(nullable NSString*)key
{
    MBLogDebugTrace();
    
    NSString* storageKey = [self _storageKeyForClass:cls withUserKey:key];
    
    NSMutableDictionary* threadLocal = [[NSThread currentThread] threadDictionary];
    if (val) {
        threadLocal[storageKey] = val;
    }
    else {
        [threadLocal removeObjectForKey:storageKey];
    }
}

+ (nonnull id) cachedValueForClass:(nonnull Class)cls
                 usingInstantiator:(__nonnull id (^ __nonnull)())instantiator
{
    return [self cachedValueForClass:cls withKey:nil usingInstantiator:instantiator];
}

+ (nonnull id) cachedValueForClass:(nonnull Class)cls
                           withKey:(nullable NSString*)key
                 usingInstantiator:(__nonnull id (^ __nonnull)())instantiator
{
    MBLogDebugTrace();
    
    NSString* storageKey = [self _storageKeyForClass:cls withUserKey:key];
    
    NSMutableDictionary* threadLocal = [[NSThread currentThread] threadDictionary];
    id val = threadLocal[storageKey];
    if (!val) {
        val = instantiator();
        if (val) {
            threadLocal[storageKey] = val;
        }
        else {
            MBLogError(@"Cached object instantiator block unexpectedly returned a nil value");
        }
    }
    return val;
}

@end
