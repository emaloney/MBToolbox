//
//  MBThreadsafeCache.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 12/28/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#import "Mockingbird-Toolbox.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBThreadsafeCache class
/******************************************************************************/

/*!
 This class implements in-memory object cache that can be safely shared
 among multiple threads simultaneously.
 
 The cache provides an accessor/mutator interface similar to `NSDictionary` and
 `NSMutableDictionary`, and supports keyed subscripting.

 @note      Classes that wish to subclass `MBThreadsafeCache` should refer
            to the internal `MBThreadsafeCache(ForSubclassEyesOnly)` methods
            declared in the header file `MBThreadsafeCache+Subclassing.h`.
 */
@interface MBThreadsafeCache : NSObject

/*----------------------------------------------------------------------------*/
#pragma mark Object lifecycle
/*!    @name Object lifecycle                                                 */
/*----------------------------------------------------------------------------*/

/*!
 Initializes a new `MBThreadsafeCache` instance.
 
 @param     protect If `YES`, the cache will ensure that internal exceptions
            do not leave locks in an inconsistent state. This adds overhead,
            and is generally not needed unless subclasses override primitive
            hooks that may throw exceptions.
 
 @param     ignore If `YES`, the cache will not automatically clear itself when
            a memory warning occurs.
 */
- (id) initWithExceptionProtection:(BOOL)protect
              ignoreMemoryWarnings:(BOOL)ignore;

/*!
 The default initializer for `MBThreadsafeCache` instances.

 Equivalent to calling `initWithExceptionProtection:NO ignoreMemoryWarnings:NO`.
 */
- (id) init;

/*----------------------------------------------------------------------------*/
#pragma mark Accessing cached items
/*!    @name Accessing cached items                                           */
/*----------------------------------------------------------------------------*/

/*!
 Determines whether a given key has a corresponding value in the cache.
 
 @param     key The key.
 
 @return    `YES` if there is a value for the given key in the cache; `NO`
            otherwise.
 */
- (BOOL) isKeyInCache:(id)key;

/*!
 Retrieves a cached object value given its key.

 @param     key The key whose associated value is to be retrieved.
 
 @return    The value associated with `key`. May be `nil`.
 */
- (id) objectForKey:(id)key;

/*----------------------------------------------------------------------------*/
#pragma mark Modifying the cache
/*!    @name Modifying the cache                                              */
/*----------------------------------------------------------------------------*/

/*!
 Sets a cached object value and associates it with the given key.
 
 @param     obj The new cached value.

 @param     key The key whose associated value is to be set.
 */
- (void) setObject:(id)obj forKey:(id)key;

/*!
 Removes from the cache the object associated with the given key.

 @param     key The key whose associated value is to be removed.
 */
- (void) removeObjectForKey:(id)key;

/*----------------------------------------------------------------------------*/
#pragma mark Keyed subscripting support
/*!    @name Keyed subscripting support                                       */
/*----------------------------------------------------------------------------*/

/*!
 Allows accessing a cached value using the Objective-C keyed subscripting
 notation.

 @param     key The key whose associated value is to be retrieved.
 
 @return    The value associated with `key`. May be `nil`.
 */
- (id) objectForKeyedSubscript:(id)key;

/*!
 Allows setting a cached value using the Objective-C keyed subscripting
 notation.

 @param     obj The new cached value.

 @param     key The key whose associated value is to be set.
 */
- (void) setObject:(id)obj forKeyedSubscript:(id)key;

/*----------------------------------------------------------------------------*/
#pragma mark Memory management
/*!    @name Memory management                                                */
/*----------------------------------------------------------------------------*/

/*!
 Empties the in-memory object cache.
 
 Depending on how the cache instance was initialized, the memory cache may
 be cleared automatically in response to memory warnings.
 */
- (void) clearMemoryCache;

/*!
 This method is called automatically when a memory warning occurs, unless the
 cache was explicitly initialized to ignore memory warnings.
 
 The default implementation simply calls `clearMemoryCache`; however, subclasses
 may override this to perform additional cleanup when a memory warning occurs.
 */
- (void) memoryWarning;

/*----------------------------------------------------------------------------*/
#pragma mark Manipulating the cache lock
/*!    @name Manipulating the cache lock                                      */
/*----------------------------------------------------------------------------*/

/*!
 Locks the cache.
 
 Used internally by the `MBThreadsafeCache` implementation and subclasses.

 @note      You will generally not need to call this directly unless you want
            to make multiple changes to the cache atomically.
 */
- (void) lock;

/*!
 Unlocks the cache.

 Used internally by the `MBThreadsafeCache` implementation and subclasses.

 @note      You will generally not need to call this directly unless you want
            to make multiple changes to the cache atomically.
 */
- (void) unlock;

@end
