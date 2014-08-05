//
//  MBNetworkIndicator.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/22/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import <libkern/OSAtomic.h>

#import "MBNetworkIndicator.h"
#import "MBEvents.h"
#import "MBSingleton.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

NSString* const kMBNetworkActivityStartedEvent   = @"MBNetwork:activityStarted";
NSString* const kMBNetworkActivityFinishedEvent  = @"MBNetwork:activityFinished";
NSString* const kMBNetworkOperationStartedEvent  = @"MBNetwork:operationStarted";
NSString* const kMBNetworkOperationFinishedEvent = @"MBNetwork:operationFinished";

/******************************************************************************/
#pragma mark -
#pragma mark MBNetworkIndicatorCoordinator private class
/******************************************************************************/

@interface MBNetworkIndicatorCoordinator : NSObject <MBSingleton>
{
    volatile int32_t _operationCount;
}

- (void) operationStarted;
- (void) operationFinished;
- (void) operationsFinished:(int32_t)count;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBNetworkIndicatorCoordinator implementation
/******************************************************************************/

@implementation MBNetworkIndicatorCoordinator

MBImplementSingleton();

- (void) operationStarted
{
    debugTrace();

    OSAtomicIncrement32Barrier(&_operationCount);

    if (_operationCount > 0) {
        UIApplication* app = [UIApplication sharedApplication];
        if (!app.networkActivityIndicatorVisible) {
            app.networkActivityIndicatorVisible = YES;
        }
    }
    if (_operationCount == 1) {
        [MBEvents postEvent:kMBNetworkActivityStartedEvent fromSender:self];
    }
    [MBEvents postEvent:kMBNetworkOperationStartedEvent fromSender:self];

    debugLog(@"Current operation count: %d", _operationCount);
}

- (void) operationFinished
{
    [self operationsFinished:1];
}

- (void) operationsFinished:(int32_t)count
{
    debugTrace();
    
    OSAtomicAdd32Barrier(-count, &_operationCount);
    
    [MBEvents postEvent:kMBNetworkOperationFinishedEvent fromSender:self];
    
    if (_operationCount == 0) {
        [MBEvents postEvent:kMBNetworkActivityFinishedEvent fromSender:self];

        UIApplication* app = [UIApplication sharedApplication];
        if (app.networkActivityIndicatorVisible) {
            app.networkActivityIndicatorVisible = NO;
        }
    }

    debugLog(@"Current operation count: %d", _operationCount);
}

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBNetworkIndicator class
/******************************************************************************/

@implementation MBNetworkIndicator
{
    int32_t _operationCount;
}

- (void) dealloc
{
    [self cancelOperations];
}

- (void) operationStarted
{
    debugTrace();
    
    _operationCount++;

    [[MBNetworkIndicatorCoordinator instance] operationStarted];
}

- (void) operationFinished
{
    debugTrace();

    if (_operationCount > 0) {
        _operationCount--;

        [[MBNetworkIndicatorCoordinator instance] operationFinished];
    }
}

- (void) cancelOperations
{
    debugTrace();
    
    if (_operationCount > 0) {
        [[MBNetworkIndicatorCoordinator instance] operationsFinished:_operationCount];
    }
    _operationCount = 0;
}

@end

