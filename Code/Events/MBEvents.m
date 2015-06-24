//
//  MBEvents.m
//  Mockingbird Toolbox
//
//  Created by Jesse Boyes on 7/13/09.
//  Copyright (c) 2009 Gilt Groupe. All rights reserved.
//

#import "MBEvents.h"

#if MB_BUILD_IOS
#import <UIKit/UIKit.h>
#endif

#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL         0

/******************************************************************************/
#pragma mark -
#pragma mark MBEvents implementation
/******************************************************************************/

@implementation MBEvents

/******************************************************************************/
#pragma mark Posting events
/******************************************************************************/

+ (void) postEvent:(nonnull NSString*)event
{
    MBLogDebug(@"Posting event: %@", event);

    assert(event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:nil];
}

+ (void) postEvent:(nonnull NSString*)event withSuffix:(nullable NSString*)suffix
{
    assert(event);
    
    if (suffix) {
        event = [self name:event withSuffix:suffix];
    }

    MBLogDebug(@"Posting event: %@", event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:nil];
}

+ (void) postEvent:(nonnull NSString*)event withObject:(nullable id)obj
{
    MBLogDebug(@"Posting event: %@ (with object parameter: %@)", event, obj);

    assert(event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:obj];
}

+ (void) postEvent:(nonnull NSString*)event withUserInfo:(nullable NSDictionary*)userInfo
{
    MBLogDebug(@"Posting event: %@ (with userInfo parameter: %@)", event, userInfo);

    assert(event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:nil userInfo:userInfo];
}

+ (void) postEvent:(nonnull NSString*)event fromSender:(nullable id)sender
{
    MBLogDebug(@"Posting event: %@ (from sender: %@)", event, sender);

    assert(event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:sender];
}

/******************************************************************************/
#pragma mark Constructing event-related names
/******************************************************************************/

+ (nullable NSString*) name:(nullable NSString*)name withSuffix:(nullable NSString*)suffix
{
    if (name && suffix) {
        return [NSString stringWithFormat:@"%@:%@", name, suffix];
    }
    return name;
}

/******************************************************************************/
#pragma mark Posting memory warnings
/******************************************************************************/

#if MB_BUILD_IOS
+ (void) postMemoryWarning
{
    [self postEvent:UIApplicationDidReceiveMemoryWarningNotification];
}
#endif

@end
