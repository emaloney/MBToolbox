//
//  MBThreadLocalStorage.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/7/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

/******************************************************************************/
#pragma mark -
#pragma mark MBThreadLocalStorage class
/******************************************************************************/

/*!
 Provides a mechanism for storing thread-specific data in a way that's designed
 to avoid key naming clashes.
 
 Under the hood, values are stored using the `threadDictionary` of the calling
 `NSThread`.

 ### Avoiding key clashes

 To prevent clashes between different code using thread-local storage, values
 are accessed by specifying the requesting `Class`.
 
 Classes that wish to store multiple values can also provide a unique key
 string for each value.
 
 ### Lock-free caching

 The `MBThreadLocalStorage` class also provides methods that allow treating
 thread-local storage as a lock-free cache. Objects that are expensive to 
 create, such as `NSDateFormatter` instances, can be cached in thread-local 
 storage without incurring the locking overhead that would be required by an
 object cache shared among multiple threads.

 Of course, the flipside to this is that a new cached object instance will be
 created for each individual `NSThread` that attempts to access the value.

 This mechanism is best suited for cases where the long-term expense of
 acquiring read locks every time the object is accessed is greater than the
 expense of creating a new instance multiplied by the number of unique threads 
 that will access the value.

 For example, an ideal use-case would be for caching values that are only
 accessed from the main thread.

 @note      As the class name implies, values set using `MBThreadLocalStorage`
            are only visible to the thread that set those values.
 */
@interface MBThreadLocalStorage : NSObject

/*----------------------------------------------------------------------------*/
#pragma mark Accessing thread-local values
/*!    @name Accessing thread-local values                                    */
/*----------------------------------------------------------------------------*/

/*!
 Returns the thread-local value associated with the specified class.
 
 @param     cls The `Class` responsible for the thread-local value. Must
            not be `NULL`.
 
 @return    The thread-local value, or `nil` if one was not previously set
            on the calling thread for the specified class.
 */
+ (nullable id) valueForClass:(nonnull Class)cls;

/*!
 Returns the thread-local value associated with the specified class and key.
 
 @param     cls The `Class` responsible for the thread-local value. Must
            not be `NULL`.

 @param     key The key associated with the value to retrieve. If `nil`, the
            effect is the same as calling `valueForClass:`.
 
 @return    The thread-local value, or `nil` if one was not previously set
            on the calling thread for the specified class.
 */
+ (nullable id) valueForClass:(nonnull Class)cls withKey:(nullable NSString*)key;

/*----------------------------------------------------------------------------*/
#pragma mark Setting thread-local values
/*!    @name Setting thread-local values                                      */
/*----------------------------------------------------------------------------*/

/*!
 Sets a thread-local value for the given class.
 
 @param     val The value to store. Passing `nil` will remove a value stored
            previously.

 @param     cls The `Class` responsible for the thread-local value. Must
            not be `NULL`.
 */
+ (void) setValue:(nullable id)val forClass:(nonnull Class)cls;

/*!
 Sets a thread-local value for the given class.
 
 @param     val The value to store. Passing `nil` will remove a value stored
            previously.

 @param     cls The `Class` responsible for the thread-local value. Must
            not be `NULL`.

 @param     key The key associated with the value being set. If `nil`, the
            effect is the same as calling `setValue:forClass:`.
 */
+ (void) setValue:(nullable id)val forClass:(nonnull Class)cls withKey:(nullable NSString*)key;

/*----------------------------------------------------------------------------*/
#pragma mark Using thread-local storage as a cache
/*!    @name Using thread-local storage as a cache                            */
/*----------------------------------------------------------------------------*/

/*!
 Allows use of thread-local storage as a lock-free cache. If the requested
 value is not in the cache, the block provided will be executed to create a
 new instance.

 If there is already a thread-local value associated with the given class,
 it is returned.

 If there is no thread-local value already set for the given class, the
 instantiator block is called to create a new object instance. That object
 is then placed in thread-local storage and returned.
 
 @param     cls The `Class` responsible for the thread-local value. Must
            not be `NULL`.
 
 @param     instantiator A block used to create a new cached object instance.
            This block will be executed only when there is not an existing
            cached value in thread-local storage. It is considered an error
            for the instantiator block to return `nil`.

 @return    The cached object, which should not be `nil` unless there is a
            programming error within the instantiator block.
 */
+ (nonnull id) cachedValueForClass:(nonnull Class)cls
                 usingInstantiator:(__nonnull id (^ __nonnull)())instantiator;

/*!
 Allows use of thread-local storage as a lock-free cache. If the requested
 value is not in the cache, the block provided will be executed to create a
 new instance.
 
 If there is already a thread-local value associated with the given class
 and key, it is returned.

 If there is no thread-local value already set for the given class and key,
 the instantiator block is called to create a new object instance. That object
 is then placed in thread-local storage and returned.
 
 @param     cls The `Class` responsible for the thread-local value. Must
            not be `NULL`.

 @param     key The key associated with the cached value. If `nil`, the effect
            is the same as calling `cachedValueForClass:usingInstantiator:`.

 @param     instantiator A block used to create a new cached object instance.
            This block will be executed only when there is not an existing
            cached value in thread-local storage. It is considered an error
            for the instantiator block to return `nil`.

 @return    The cached object, which should not be `nil` unless there is a
            programming error within the instantiator block.
 */
+ (nonnull id) cachedValueForClass:(nonnull Class)cls
                           withKey:(nullable NSString*)key
                 usingInstantiator:(__nonnull id (^ __nonnull)())instantiator;

@end


