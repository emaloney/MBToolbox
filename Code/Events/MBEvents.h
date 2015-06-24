//
//  MBEvents.h
//  Mockingbird Toolbox
//
//  Created by Jesse Boyes on 7/13/09.
//  Copyright (c) 2009 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MBAvailability.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBEvents class
/******************************************************************************/

/*!
 Provides a simple interface for posting `NSNotification` events of various
 types.
 */
@interface MBEvents : NSObject

/*----------------------------------------------------------------------------*/
#pragma mark Posting events
/*!    @name Posting events                                                   */
/*----------------------------------------------------------------------------*/

/*!
 Posts a notification event.
 
 @param     event The name of the event to post.
 */
+ (void) postEvent:(nonnull NSString*)event;

/*!
 Posts a notification event by constructing the event name
 "`event`:`suffix`".
 
 @param     event The prefix of the event name to post.
 
 @param     suffix The suffix of the event name to post.
 */
+ (void) postEvent:(nonnull NSString*)event withSuffix:(nullable NSString*)suffix;

/*!
 Posts a notification event containing the given object parameter.
 
 @param     event The name of the event to post.

 @param     obj The object to post with the event. This value will be
            available in the `object` property of the `NSNotification`
            created for the event.
 */
+ (void) postEvent:(nonnull NSString*)event withObject:(nullable id)obj;

/*!
 Posts a notification event containing the given userInfo parameter.

 @param     event The name of the event to post.

 @param     userInfo The user info dictionary to post with the event. This 
            value will be available in the `userInfo` property of the
            `NSNotification` created for the event.
 */
+ (void) postEvent:(nonnull NSString*)event withUserInfo:(nullable NSDictionary*)userInfo;

/*!
 Posts a notification event along with the object instance sending the event.
 
 @param     event The name of the event to post.
 
 @param     sender The sender of the event. This object will be available in
            the `object` property of the `NSNotification` created for the event.
 */
+ (void) postEvent:(nonnull NSString*)event fromSender:(nullable id)sender;

/*----------------------------------------------------------------------------*/
#pragma mark Constructing event-related names
/*!    @name Constructing event-related names                                 */
/*----------------------------------------------------------------------------*/

/*!
 Constructs a string for an event-related name with the given suffix.
 
 @param     name The name to use for the root of the returned string. If
            `nil`, this method returns `nil`.
 
 @param     suffix The optional suffix to apply to `name`. If `nil`, this
            method returns `name`.

 @return    If `name` and `suffix` are both non-`nil`, the concatenation of
            `name`, `:` and `suffix` is returned. Otherwise, the value of the
            `name` parameter is returned.

 Some notification names are parameterized, based on the name of components (or
 other objects) at runtime. These methods return construct and return event
 names.
 */
+ (nullable NSString*) name:(nullable NSString*)name withSuffix:(nullable NSString*)suffix;

/*----------------------------------------------------------------------------*/
#pragma mark Posting memory warnings
/*!    @name Posting memory warnings                                          */
/*----------------------------------------------------------------------------*/

#if MB_BUILD_IOS
/*!
 Posts an artificial memory warning using the event name contained in the
 `UIApplicationDidReceiveMemoryWarningNotification` constant.
 
 This can be used to cause various application-wide caches to reduce their
 non-persistent memory footprints.
 */
+ (void) postMemoryWarning;
#endif

@end
