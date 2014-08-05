//
//  MBEvents.m
//  Mockingbird Toolbox
//
//  Created by Jesse Boyes on 7/13/09.
//  Copyright (c) 2009 Gilt Groupe. All rights reserved.
//

#import "MBEvents.h"

#define DEBUG_LOCAL         0

/******************************************************************************/
#pragma mark -
#pragma mark MBEvents implementation
/******************************************************************************/

@implementation MBEvents

/******************************************************************************/
#pragma mark Posting events
/******************************************************************************/

+ (void) postEvent:(NSString*)event
{
    debugLog(@"Posting event: %@", event);

    assert(event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:nil];
}

+ (void) postEvent:(NSString*)event withSuffix:(NSString*)suffix
{
    assert(event);
    
    if (suffix) {
        event = [self name:event withSuffix:suffix];
    }

    debugLog(@"Posting event: %@", event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:nil];
}

+ (void) postEvent:(NSString*)event withObject:(id)obj
{
    debugLog(@"Posting event: %@ (with object parameter: %@)", event, obj);

    assert(event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:obj];
}

+ (void) postEvent:(NSString*)event withUserInfo:(NSDictionary*)userInfo
{
    debugLog(@"Posting event: %@ (with userInfo parameter: %@)", event, userInfo);

    assert(event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:nil userInfo:userInfo];
}

+ (void) postEvent:(NSString*)event fromSender:(id)sender
{
    debugLog(@"Posting event: %@ (from sender: %@)", event, sender);

    assert(event);
    [[NSNotificationCenter defaultCenter] postNotificationName:event object:sender];
}

/******************************************************************************/
#pragma mark Constructing event-related names
/******************************************************************************/

+ (NSString*) name:(NSString*)name withSuffix:(NSString*)suffix
{
    if (name && suffix) {
        return [NSString stringWithFormat:@"%@:%@", name, suffix];
    }
    return name;
}

/******************************************************************************/
#pragma mark Posting memory warnings
/******************************************************************************/

+ (void) postMemoryWarning
{
    [self postEvent:UIApplicationDidReceiveMemoryWarningNotification];
}

@end
