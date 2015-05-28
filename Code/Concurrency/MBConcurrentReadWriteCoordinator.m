//
//  MBConcurrentReadWriteCoordinator.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 1/13/15.
//  Copyright (c) 2015 Gilt Groupe. All rights reserved.
//

#import "MBConcurrentReadWriteCoordinator.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBConcurrentReadWriteCoordinator implementation
/******************************************************************************/

@implementation MBConcurrentReadWriteCoordinator
{
    dispatch_queue_t _queue;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

- (instancetype) init
{
    self = [super init];
    if (self) {
        NSString* queueName = [NSString stringWithFormat:@"com.gilt.%@", [self class]];
        _queue = dispatch_queue_create(queueName.UTF8String, DISPATCH_QUEUE_CONCURRENT);
    }
    return self;
}

/******************************************************************************/
#pragma mark Reading
/******************************************************************************/

- (void) read:(nonnull void (^)())op
{
    dispatch_sync(_queue, op);
}

/******************************************************************************/
#pragma mark Writing
/******************************************************************************/

- (void) enqueueWrite:(nonnull void (^)())op
{
    dispatch_barrier_async(_queue, op);
}

@end
