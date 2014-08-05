//
//  MBThreadLocalStorage.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/7/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "MBThreadLocalStorage.h"

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

+ (id) valueForClass:(Class)cls
{
    return [self valueForClass:cls withKey:nil];
}

+ (id) valueForClass:(Class)cls withKey:(NSString*)key
{
    debugTrace();
    
    NSString* storageKey = [self _storageKeyForClass:cls withUserKey:key];
    
    return [[NSThread currentThread] threadDictionary][storageKey];
}

+ (void) setValue:(id)val forClass:(Class)cls
{
    return [self setValue:val forClass:cls withKey:nil];
}

+ (void) setValue:(id)val forClass:(Class)cls withKey:(NSString*)key
{
    debugTrace();
    
    NSString* storageKey = [self _storageKeyForClass:cls withUserKey:key];
    
    NSMutableDictionary* threadLocal = [[NSThread currentThread] threadDictionary];
    if (val) {
        threadLocal[storageKey] = val;
    }
    else {
        [threadLocal removeObjectForKey:storageKey];
    }
}

+ (id) cachedValueForClass:(Class)cls usingInstantiator:(id (^)())instantiator
{
    return [self cachedValueForClass:cls withKey:nil usingInstantiator:instantiator];
}

+ (id) cachedValueForClass:(Class)cls withKey:(NSString*)key usingInstantiator:(id (^)())instantiator
{
    debugTrace();
    
    NSString* storageKey = [self _storageKeyForClass:cls withUserKey:key];
    
    NSMutableDictionary* threadLocal = [[NSThread currentThread] threadDictionary];
    id val = threadLocal[storageKey];
    if (!val) {
        val = instantiator();
        if (val) {
            threadLocal[storageKey] = val;
        }
        else {
            errorLog(@"Cached object instantiator block unexpectedly returned a nil value");
        }
    }
    return val;
}

@end
