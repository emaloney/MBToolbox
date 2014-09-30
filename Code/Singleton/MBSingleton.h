//
//  MBSingleton.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 11/11/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

/******************************************************************************/
#pragma mark MBSingleton protocols
/******************************************************************************/

/*!
 Adopted by classes that provide `instance` accessors but that don't 
 necessarily abide by singleton behavior.
 
 Singletons will only ever return a single object pointer over the running
 lifetime of an application. Such classes should adopt the `MBSingleton`
 protocol.
 
 Implementations that may return different object pointers over the lifetime
 of an application should adopt the `MBInstanceVendor` protocol.

 If a class explicitly adopts `MBInstanceVendor` instead of `MBSingleton`, it
 serves as a signal that callers should not hold long-term references to the
 return value of the `instance` method.
 */
@protocol MBInstanceVendor <NSObject>

/*!
 Retreives the object instance currently vended by the receiver.

 @return    The current instance. Callers should not assume that the return
            value will be the same every time this method is invoked.
 */
+ (instancetype) instance;

@end

/*!
 Adopted by classes that act as singletons.
 
 Singletons will only ever return a single object pointer over the running
 lifetime of an application.

 Because the singleton is guaranteed not to change, it is safe for callers to
 store long-term references to it. This way, the overhead incurred by 
 unnecessary repeat calls to the singleton's `instance` method can be avoided.

 If a class implementation might return more than one distinct object pointer
 over the lifetime of an application, it should adopt the `MBInstanceVendor`
 protocol instead of `MBSingleton`.

 ### Automatic singleton implementation
 
 Mockingbird provides the `MBImplementSingleton()` macro for classes that do
 not wish to provide their own implementation of the `instance` method.

 `MBImplementSingleton()` expands to a thread-safe, lazily-instantiated 
 implementation of the `instance` method.
 
 To use, place the macro between the `@implementation`...`@end` keywords of the
 singleton class's implementation.

 @note      Singleton implementations should strive to be thread-safe. If a
            class adopting this protocol is not thread-safe, that fact should
            be noted prominently in the class's documentation.
 */
@protocol MBSingleton <NSObject>

/*!
 Retreives the singleton instance of the receiving class.

 @return    The singleton instance. This value should never change during
            the running lifetime of the application.
 */
+ (instancetype) instance;

@end

/******************************************************************************/
#pragma mark -
#pragma mark Singleton implementation macro
/******************************************************************************/

#define MBImplementSingleton() \
\
+ (instancetype) instance \
{ \
    static dispatch_once_t s_once; \
    static id s_singleton; \
    dispatch_once(&s_once, ^{ \
        s_singleton = [self new]; \
    }); \
    return s_singleton; \
} \

