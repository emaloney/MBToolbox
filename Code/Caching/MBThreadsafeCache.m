//
//  MBThreadsafeCache.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 12/28/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#import "MBThreadsafeCache.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark MBThreadsafeCache implementation
/******************************************************************************/

@implementation MBThreadsafeCache
{
    NSRecursiveLock* _lock;
    BOOL _exceptionProtection;
    BOOL _clearOnMemoryWarning;
    NSMutableDictionary* _cache;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

- (id) init
{
    return [self initWithExceptionProtection:NO ignoreMemoryWarnings:NO];
}

- (id) initWithExceptionProtection:(BOOL)protect
              ignoreMemoryWarnings:(BOOL)ignore
{
    self = [super init];
    if (self) {
        _exceptionProtection = protect;
        _clearOnMemoryWarning = !ignore;
                
        _lock = [NSRecursiveLock new];
        _cache = [NSMutableDictionary new];
        
        if (_clearOnMemoryWarning) {
            [[NSNotificationCenter defaultCenter] addObserver:self
                                                     selector:@selector(memoryWarning)
                                                         name:UIApplicationDidReceiveMemoryWarningNotification
                                                       object:nil];
        }        
    }
    return self;
}

- (void) dealloc
{
    if (_clearOnMemoryWarning) {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
    }            
}

/******************************************************************************/
#pragma mark Memory management
/******************************************************************************/

- (void) memoryWarning
{
	debugTrace();
	
	[self clearMemoryCache];
}

/******************************************************************************/
#pragma mark Locking & unlocking (for external use)
/******************************************************************************/

- (void) lock
{
    debugTrace();
    
    [_lock lock];
}

- (void) unlock
{
    debugTrace();

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
    debugTrace();
    
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
    debugTrace();
    
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
	debugTrace();
	
    if (_exceptionProtection) {
        [self _clearCacheProtected];
    }
    else {
        [self _clearCacheUnprotected];
    }
}

- (BOOL) isKeyInCache:(id)key
{
    debugTrace();
    
    if (_exceptionProtection) {
        return [self _isKeyInCacheProtected:key];
    }
    else {
        return [self _isKeyInCacheUnprotected:key];
    }
}

- (id) objectForKey:(id)key
{
	debugTrace();

    if (_exceptionProtection) {
        return [self _objectForKeyProtected:key];
    }
    else {
        return [self _objectForKeyUnprotected:key];
    }
}

- (void) setObject:(id)obj forKey:(id)key
{
	debugTrace();
    
    if (_exceptionProtection) {
        [self _setObjectProtected:obj forKey:key];
    }
    else {
        [self _setObjectUnprotected:obj forKey:key];
    }
}

- (void) removeObjectForKey:(id)key
{
	debugTrace();

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

- (id) objectForKeyedSubscript:(id)key
{
    return [self objectForKey:key];
}

- (void) setObject:(id)obj forKeyedSubscript:(id)key
{
    [self setObject:obj forKey:key];
}

@end
