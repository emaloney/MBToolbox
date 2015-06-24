//
//  MBModuleLog.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/30/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBAvailability.h"

#if MB_BUILD_IOS
#import <UIKit/UIKit.h>
#endif

#import "MBModuleLog.h"
#import "MBModule.h"
#import "NSString+MBIndentation.h"
#import "MBConcurrentReadWriteCoordinator.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

static Class<MBModuleLogRecorder> s_logger = nil;
static MBConcurrentReadWriteCoordinator* s_readerWriter = nil;

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
        s_readerWriter = [MBConcurrentReadWriteCoordinator new];
        s_logger = self;
    }
}

+ (void) setLogRecorderClass:(nullable Class<MBModuleLogRecorder>)logRecorderClass
{
    [s_readerWriter enqueueWrite:^{
        if (logRecorderClass) {
            s_logger = logRecorderClass;
        } else {
            s_logger = [MBModuleLog class];
        }
    }];
}

+ (nonnull Class<MBModuleLogRecorder>) logRecorderClass
{
    __block Class<MBModuleLogRecorder> logger = nil;
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
        _issuedMessages = [NSMutableSet new];

#if MB_BUILD_IOS
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(_memoryWarning)
                                                     name:UIApplicationDidReceiveMemoryWarningNotification
                                                   object:nil];
#endif
    }
    return self;
}

#if MB_BUILD_IOS
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

- (void) _issueMessage:(NSString*)message atSeverity:(MBModuleLogSeverity)severity
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

    [self _issueMessage:msg atSeverity:MBModuleLogSeverityWarning];
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

    [self _issueMessage:msg atSeverity:MBModuleLogSeverityError];
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
