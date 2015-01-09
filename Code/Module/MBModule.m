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
#pragma mark Getting module information
/******************************************************************************/

+ (NSString*) moduleName
{
    NSString* name = [self description];
    if ([name hasSuffix:@"Module"]) {
        return [name substringToIndex:name.length - 6];
    }
    return name;
}

+ (NSBundle*) resourceBundle
{
    NSBundle* containingBundle = [NSBundle bundleForClass:self];
    NSString* moduleBundlePath = [containingBundle pathForResource:[self moduleName] ofType:@"bundle"];
    return [NSBundle bundleWithPath:moduleBundlePath];
}

/******************************************************************************/
#pragma mark Accessing the module log
/******************************************************************************/

+ (MBModuleLog*) log
{
    return [[[self class] instance] log];
}

- (MBModuleLog*) log
{
    return _log;
}

@end
