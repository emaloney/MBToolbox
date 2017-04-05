//
//  MBOperationQueue.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/7/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBOperationQueue.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark MBOperationQueue implementation
/******************************************************************************/

@implementation MBOperationQueue

- (nonnull instancetype) init
{
    return [self initWithMaxConcurrentOperationCount:NSOperationQueueDefaultMaxConcurrentOperationCount];
}

- (nonnull instancetype) initWithMaxConcurrentOperationCount:(NSInteger)cnt
{
    self = [super init];
    if (self) {
        [self setMaxConcurrentOperationCount:cnt];

		[self setName:[[self class] description]];
    }
    return self;
}

@end
