//
//  MBThreadsafeCache.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 12/28/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#import "MBThreadsafeCache.h"

#if MB_BUILD_IOS
#import <UIKit/UIKit.h>
#endif

#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark MBThreadsafeCache implementation
/******************************************************************************/

@implementation MBThreadsafeCache
{
    NSRecursiveLock* _lock;
    BOOL _exceptionProtection;
#if MB_BUILD_IOS
    BOOL _clearOnMemoryWarning;
#endif
    NSMutableDictionary* _cache;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

- (nonnull instancetype) init
{
#if MB_BUILD_IOS
    return [self initWithExceptionProtection:NO ignoreMemoryWarnings:NO];
#else
    return [self initWithExceptionProtection:NO];
#endif
}

- (nonnull instancetype) initWithExceptionProtection:(BOOL)protect
#if MB_BUILD_IOS
                                ignoreMemoryWarnings:(BOOL)ignore
#endif
{
    self = [super init];
    if (self) {
        _exceptionProtection = protect;

        _lock = [NSRecursiveLock new];
        _cache = [NSMutableDictionary new];

#if MB_BUILD_IOS
        _clearOnMemoryWarning = !ignore;
        if (_clearOnMemoryWarning) {
            [[NSNotificationCenter defaultCenter] addObserver:self
                                                     selector:@selector(memoryWarning)
                                                         name:UIApplicationDidReceiveMemoryWarningNotification
                                                       object:nil];
        }        
#endif
    }
    return self;
}

#if MB_BUILD_IOS
- (void) dealloc
{
    if (_clearOnMemoryWarning) {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
    }            
}
#endif

/******************************************************************************/
#pragma mark Memory management
/******************************************************************************/

#if MB_BUILD_IOS
- (void) memoryWarning
{
	MBLogDebugTrace();
	
	[self clearMemoryCache];
}
#endif

/******************************************************************************/
#pragma mark Locking & unlocking (for external use)
/******************************************************************************/

- (void) lock
{
    MBLogDebugTrace();
    
    [_lock lock];
}

- (void) unlock
{
    MBLogDebugTrace();

    [_lock unlock];
}

/******************************************************************************/
#pragma mark Subclass hooks/primitive methods for internal use
/******************************************************************************/

- (NSMutableDictionary*) internalCache
{
    return _cache;
}

- (void) internalClearMemoryCache
{
    [_cache removeAllObjects];
}

- (BOOL) internalIsKeyInCache:(id)key
{
    return (_cache[key] != nil);
}

- (id) internalObjectForKey:(id)key
{
    return _cache[key];
}

- (void) internalSetObject:(id)obj forKey:(id)key
{
    _cache[key] = obj;
}

- (void) internalRemoveObjectForKey:(id)key
{
    [_cache removeObjectForKey:key];
}

/******************************************************************************/
#pragma mark Exception-protected implementation
/******************************************************************************/

- (void) _clearCacheProtected
{
    [_lock lock];
    @try {
        [self internalClearMemoryCache];
    }
    @finally {
        [_lock unlock];
    }
}

- (BOOL) _isKeyInCacheProtected:(id)key
{
    MBLogDebugTrace();
    
    [_lock lock];
    @try {
        return [self internalIsKeyInCache:key];
    }
    @finally {
        [_lock unlock];
    }
}

- (id) _objectForKeyProtected:(id)key
{
    [_lock lock];
    @try {
        return [self internalObjectForKey:key];
    }
    @finally {
        [_lock unlock];
    }
}

- (void) _setObjectProtected:(id)obj forKey:(id)key
{
    [_lock lock];
    @try {
        [self internalSetObject:obj forKey:key];
    }
    @finally {
        [_lock unlock];
    }
}

- (void) _removeObjectForKeyProtected:(id)key
{
    [_lock lock];
    @try {
        [self internalRemoveObjectForKey:key];
    }
    @finally {
        [_lock unlock];
    }
}

/******************************************************************************/
#pragma mark Exception-unprotected implementation
/******************************************************************************/

- (void) _clearCacheUnprotected
{
    [_lock lock];
    [self internalClearMemoryCache];
    [_lock unlock];
}

- (BOOL) _isKeyInCacheUnprotected:(id)key
{
    MBLogDebugTrace();
    
    [_lock lock];
    BOOL inCache = [self internalIsKeyInCache:key];
    [_lock unlock];
    return inCache;
}

- (id) _objectForKeyUnprotected:(id)key
{
    if (!key) {
        // this would throw an exception if we passed it on
        // to _cache. it would defeat our avoidance of exception
        // protection around the locking/unlocking
        [NSException raise:NSInvalidArgumentException format:@"illegal argument: nil key"];
    }
    
    [_lock lock];
    id obj = [self internalObjectForKey:key];
    [_lock unlock];
    return obj;
}

- (void) _setObjectUnprotected:(id)obj forKey:(id)key
{
    if (!key || !obj) {
        // this would throw an exception if we passed it on
        // to _cache. it would defeat our avoidance of exception
        // protection around the locking/unlocking
        [NSException raise:NSInvalidArgumentException format:@"illegal argument: nil %@", (!key ? @"key" : @"value")];
    }
    
    [_lock lock];
    [self internalSetObject:obj forKey:key];
    [_lock unlock];
}

- (void) _removeObjectForKeyUnprotected:(id)key
{
    if (!key) {
        // this would throw an exception if we passed it on
        // to _cache. it would defeat our avoidance of exception
        // protection around the locking/unlocking
        [NSException raise:NSInvalidArgumentException format:@"illegal argument: nil key"];
    }
    
    [_lock lock];
    [self internalRemoveObjectForKey:key];
    [_lock unlock];
}

/******************************************************************************/
#pragma mark Public accessor/mutation interface
/******************************************************************************/

- (void) clearMemoryCache
{
	MBLogDebugTrace();
	
    if (_exceptionProtection) {
        [self _clearCacheProtected];
    }
    else {
        [self _clearCacheUnprotected];
    }
}

- (BOOL) isKeyInCache:(nonnull id)key
{
    MBLogDebugTrace();
    
    if (_exceptionProtection) {
        return [self _isKeyInCacheProtected:key];
    }
    else {
        return [self _isKeyInCacheUnprotected:key];
    }
}

- (nullable id) objectForKey:(nonnull id)key
{
	MBLogDebugTrace();

    if (_exceptionProtection) {
        return [self _objectForKeyProtected:key];
    }
    else {
        return [self _objectForKeyUnprotected:key];
    }
}

- (void) setObject:(nonnull id)obj forKey:(nonnull id)key
{
	MBLogDebugTrace();
    
    if (_exceptionProtection) {
        [self _setObjectProtected:obj forKey:key];
    }
    else {
        [self _setObjectUnprotected:obj forKey:key];
    }
}

- (void) removeObjectForKey:(nonnull id)key
{
	MBLogDebugTrace();

    if (_exceptionProtection) {
        [self _removeObjectForKeyProtected:key];
    }
    else {
        [self _removeObjectForKeyUnprotected:key];
    }
}

/******************************************************************************/
#pragma mark Keyed subscripting support
/******************************************************************************/

- (nullable id) objectForKeyedSubscript:(nonnull id)key
{
    return [self objectForKey:key];
}

- (void) setObject:(nonnull id)obj forKeyedSubscript:(nonnull id)key
{
    [self setObject:obj forKey:key];
}

@end
