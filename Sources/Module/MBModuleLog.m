//
//  MBModuleLog.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/30/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBAvailability.h"

#if MB_BUILD_UIKIT
#import <UIKit/UIKit.h>
#endif

#import "MBModuleLog.h"
#import "MBModule.h"
#import "NSString+MBIndentation.h"
#import "MBConcurrentReadWriteCoordinator.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

static Class<MBModuleLogRecorder> s_logger = nil;

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleLog implementation
/******************************************************************************/

@implementation MBModuleLog
{
    NSString* _name;
    NSMutableSet* _issuedMessages;
}

+ (void) initialize
{
    if (self == [MBModuleLog class]) {
        s_logger = self;
    }
}

+ (void) enable
{
    // we don't do anything; this hook is intended for subclasses
}

+ (void) setLogRecorderClass:(nullable Class<MBModuleLogRecorder>)logRecorderClass
{
    return [self setLogRecorderClass:logRecorderClass completion:nil];
}

+ (void) setLogRecorderClass:(nullable Class<MBModuleLogRecorder>)logRecorderClass
                  completion:(nullable void (^)(void))completion
{
    if (logRecorderClass) {
        s_logger = logRecorderClass;
    } else {
        s_logger = [MBModuleLog class];
    }
    [s_logger enable];
}

+ (nonnull Class<MBModuleLogRecorder>) logRecorderClass
{
    return s_logger;
}

+ (nonnull NSString*) logTagForSeverity:(MBLogSeverity)severity
{
    switch (severity) {
        case MBLogSeverityVerbose:
            return @"VERBOSE";

        case MBLogSeverityDebug:
            return @"  DEBUG";

        case MBLogSeverityInfo:
            return @"   INFO";

        case MBLogSeverityWarning:
            return @"WARNING";

        case MBLogSeverityError:
            return @"  ERROR";

        default:
            return @"unknown";
    }
}

+ (void) logMessage:(nonnull NSString*)msg
         atSeverity:(MBLogSeverity)severity
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
        _issuedMessages = [NSMutableSet new];

#if MB_BUILD_UIKIT
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(_memoryWarning)
                                                     name:UIApplicationDidReceiveMemoryWarningNotification
                                                   object:nil];
#endif
    }
    return self;
}

#if MB_BUILD_UIKIT
- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}
#endif

/******************************************************************************/
#pragma mark Memory management
/******************************************************************************/

- (void) _memoryWarning
{
    [_issuedMessages removeAllObjects];
}

/******************************************************************************/
#pragma mark Warnings & Errors
/******************************************************************************/

- (void) _issueMessage:(NSString*)message atSeverity:(MBLogSeverity)severity
{
    if (![NSThread isMainThread]) {
        dispatch_sync(dispatch_get_main_queue(), ^{
            [self _issueMessage:message atSeverity:severity];
        });
    }
    else {
        if (![_issuedMessages containsObject:message]) {
            MBLog(severity, @"%@", message);
            [_issuedMessages addObject:message];
        }
    }
}

- (void) issueDeprecationWarning:(NSString*)warning
{
    NSString* msg = [NSString stringWithFormat:@"\n\nDEPRECATED FEATURE IN USE: Support for this will be dropped from a future version of the %@ module for Mockingbird:\n\n%@\n\n", _name, [warning stringByIndentingEachLineWithTab]];

    [self _issueMessage:msg atSeverity:MBLogSeverityWarning];
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
    NSString* msg = [NSString stringWithFormat:@"The %@ module for Mockingbird does not support the following feature:\n\n%@\n\n", _name, [error stringByIndentingEachLineWithTab]];

    [self _issueMessage:msg atSeverity:MBLogSeverityError];
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
