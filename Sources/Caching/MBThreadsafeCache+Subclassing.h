//
//  MBThreadsafeCache+Subclassing.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/3/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

/******************************************************************************/
#pragma mark -
#pragma mark MBThreadsafeCache subclassing interface
/******************************************************************************/

/*!
 The class extensions in this header file are intended for internal use only by
 `MBThreadsafeCache` implementations.

 Code external to `MBThreadsafeCache` should never call these methods directly.
 */
@interface MBThreadsafeCache (ForSubclassEyesOnly)

/*----------------------------------------------------------------------------*/
#pragma mark Acquiring the memory cache
/*!    @name Acquiring the memory cache                                       */
/*----------------------------------------------------------------------------*/

/*!
 Returns the internal `NSMutableDictionary` where in-memory cached objects are
 stored.

 @note      The cache is locked when this method is called by the
            `MBThreadsafeCache` superclass implementation; subclasses that call
            this method directly or perform mutations on the returned
            dictionary must only do so when the cache is locked.
 */
- (nonnull NSMutableDictionary*) internalCache;

/*----------------------------------------------------------------------------*/
#pragma mark Accessing cached items
/*!    @name Accessing cached items                                           */
/*----------------------------------------------------------------------------*/

/*!
 Called internally to determine whether a given key has a corresponding value 
 in the cache.

 @param     key The key.

 @return    `YES` if there is a value for the given key in the cache; `NO`
            otherwise.

 @note      The cache is locked when this method is called by the
            `MBThreadsafeCache` superclass implementation; subclasses that call
            this method directly must only do so when the cache is locked.
 */
- (BOOL) internalIsKeyInCache:(nonnull id)key;

/*!
 Called internally to retrieve a cached object value given its key.

 @param     key The key whose associated value is to be retrieved.
 
 @return    The value associated with `key`. May be `nil`.

 @note      The cache is locked when this method is called by the
            `MBThreadsafeCache` superclass implementation; subclasses that call
            this method directly must only do so when the cache is locked.
 */
- (nullable id) internalObjectForKey:(nonnull id)key;

/*----------------------------------------------------------------------------*/
#pragma mark Modifying the cache
/*!    @name Modifying the cache                                              */
/*----------------------------------------------------------------------------*/

/*!
 Called internally to set a cached object value and associates it with the 
 given key.
 
 @param     obj The new cached value.

 @param     key The key whose associated value is to be set.

 @note      The cache is locked when this method is called by the
            `MBThreadsafeCache` superclass implementation; subclasses that call
            this method directly must only do so when the cache is locked.
 */
- (void) internalSetObject:(nonnull id)obj forKey:(nonnull id)key;

/*!
 Called internally to remove from the cache the object associated with the given
 key.

 @param     key The key whose associated value is to be removed.

 @note      The cache is locked when this method is called by the
            `MBThreadsafeCache` superclass implementation; subclasses that call
            this method directly must only do so when the cache is locked.
 */
- (void) internalRemoveObjectForKey:(nonnull id)key;

/*!
 Called internally to empty the in-memory object cache.

 Depending on how the cache instance was initialized, this method may be called
 automatically in response to memory warnings.

 @note      The cache is locked when this method is called by the
            `MBThreadsafeCache` superclass implementation; subclasses that call
            this method directly must only do so when the cache is locked.
 */
- (void) internalClearMemoryCache;

@end
