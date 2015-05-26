//
//  MBModuleLog.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/30/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "MBModuleLog.h"
#import "MBModule.h"
#import "NSString+MBIndentation.h"
#import "MBThreadLocalStorage.h"
#import "MBConcurrentReadWriteCoordinator.h"
#import "MBDebug.h"

#define DEBUG_LOCAL     0

static Class<MBModuleLogger> s_logger = nil;
static MBConcurrentReadWriteCoordinator* s_readerWriter = nil;

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleLog implementation
/******************************************************************************/

@implementation MBModuleLog
{
    NSString* _name;
    BOOL _registeredForMemoryWarnings;
}

+ (void) initialize
{
    if (self == [MBModuleLog class]) {
        s_readerWriter = [MBConcurrentReadWriteCoordinator new];
        s_logger = self;
    }
}

+ (void) setLoggerClass:(nullable Class<MBModuleLogger>)loggerClass
{
    [s_readerWriter enqueueWrite:^{
        if (loggerClass) {
            s_logger = loggerClass;
        } else {
            s_logger = [MBModuleLog class];
        }
    }];
}

+ (nonnull Class<MBModuleLogger>) loggerClass
{
    __block Class<MBModuleLogger> logger = nil;
    [s_readerWriter read:^{
        logger = s_logger;
    }];
    return logger;
}

+ (nonnull NSString*) logTagForSeverity:(MBModuleLogSeverity)severity
{
    switch (severity) {
        case MBModuleLogSeverityVerbose:
            return @"VERBOSE";

        case MBModuleLogSeverityDebug:
            return @"  DEBUG";

        case MBModuleLogSeverityInfo:
            return @"   INFO";

        case MBModuleLogSeverityWarning:
            return @"WARNING";

        case MBModuleLogSeverityError:
            return @"  ERROR";

        default:
            return @"unknown";
    }
}

+ (void) logMessage:(nonnull NSString*)msg
         atSeverity:(MBModuleLogSeverity)severity
      callingObject:(nullable id)caller
   callingSignature:(nonnull NSString*)signature
    callingFilePath:(nonnull NSString*)filePath
    callingFileLine:(NSUInteger)fileLine
{
    NSString* logTag = [self logTagForSeverity:severity];
    if (caller) {
        NSLog(@"%@ | (%@:%lu) <%p> %@", logTag, [filePath lastPathComponent], (unsigned long)fileLine, caller, msg);
    } else {
        NSLog(@"%@ | (%@:%lu) %@", logTag, [filePath lastPathComponent], (unsigned long)fileLine, msg);
    }
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

+ (instancetype) logForModuleClass:(Class)moduleCls
{
    return [[self alloc] initWithName:[moduleCls moduleName]];
}

+ (instancetype) logForModule:(NSObject<MBModule>*)module
{
    return [[self alloc] initWithName:[[module class] moduleName]];
}

- (instancetype) initWithName:(NSString*)moduleName
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
