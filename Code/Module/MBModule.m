//
//  MBModule.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/24/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBModule.h"
#import "MBModuleLog.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleBase implementation
/******************************************************************************/

@implementation MBModuleBase
{
    MBModuleLog* _log;
}

MBImplementSingleton();

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

- (instancetype) init
{
    self = [super init];
    if (self) {
        _log = [MBModuleLog logForModule:self];
    }
    return self;
}

/******************************************************************************/
#pragma mark Implementation
/******************************************************************************/

+ (MBModuleLog*) log
{
    return [[[self class] instance] log];
}

- (MBModuleLog*) log
{
    return _log;
}

+ (NSArray*) environmentLoaderClasses
{
    return nil;
}

@end
