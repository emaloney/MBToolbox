//
//  MBModuleLog.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/30/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBModuleLog.h"
#import "MBModule.h"
#import "NSString+MBIndentation.h"
#import "MBThreadLocalStorage.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleLog implementation
/******************************************************************************/

@implementation MBModuleLog
{
    NSString* _name;
    BOOL _registeredForMemoryWarnings;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

+ (instancetype) logForModuleClass:(Class)moduleCls
{
    return [[self alloc] initWithName:[moduleCls description]];
}

+ (instancetype) logForModule:(NSObject<MBModule>*)module
{
    return [[self alloc] initWithName:[[module class] description]];
}

- (id) initWithName:(NSString*)moduleName
{
    self = [super init];
    if (self) {
        _name = moduleName;
    }
    return self;
}

- (void) dealloc
{
    if (_registeredForMemoryWarnings) {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
    }
}

/******************************************************************************/
#pragma mark Memory management
/******************************************************************************/

- (void) _memoryWarning
{
    debugTrace();

    [MBThreadLocalStorage setValue:nil forClass:[self class]];
}

/******************************************************************************/
#pragma mark Warnings & Errors
/******************************************************************************/

- (void) _outputNotice:(NSString*)notice
{
    if (!_registeredForMemoryWarnings) {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(_memoryWarning)
                                                     name:UIApplicationDidReceiveMemoryWarningNotification
                                                   object:nil];

        _registeredForMemoryWarnings = YES;
    }

    NSMutableSet* issuedSet = [MBThreadLocalStorage cachedValueForClass:[self class]
                                                      usingInstantiator:^(){ return [NSMutableSet set]; }];
    
    if (![issuedSet containsObject:notice]) {
        NSLog(@"%@", notice);
        [issuedSet addObject:notice];
    }
}

- (void) _issueNotice:(NSString*)notice
{
    [self performSelectorOnMainThread:@selector(_outputNotice:)
                           withObject:notice
                        waitUntilDone:NO];
}

- (void) issueDeprecationWarning:(NSString*)warning
{
    [self _issueNotice:[NSString stringWithFormat:@"\n\nDEPRECATION WARNING: Support will be dropped from a future version of the %@ module for Mockingbird:\n\n%@\n\n", _name, [warning stringByIndentingEachLineWithTab]]];
}

- (void) issueDeprecationWarningWithFormat:(NSString*)format, ...
{
    va_list args;
    va_start(args, format);
    NSString* warning = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);

    [self issueDeprecationWarning:warning];
}

- (void) issueNotSupportedError:(NSString*)error
{
    [self _issueNotice:[NSString stringWithFormat:@"\n\nERROR: The %@ module for Mockingbird does not support the following feature:\n\n%@\n\n", _name, [error stringByIndentingEachLineWithTab]]];
}

- (void) issueNotSupportedErrorWithFormat:(NSString*)format, ...
{
    va_list args;
    va_start(args, format);
    NSString* error = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    
    [self issueNotSupportedError:error];
}

@end
