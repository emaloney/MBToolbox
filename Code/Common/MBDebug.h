//
//  MBDebug.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 9/1/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#ifndef DEBUG_MASTER
#if DEBUG
#define DEBUG_MASTER        1
#else
#define DEBUG_MASTER        0
#endif
#endif

// for testing DEBUG_* flags declared locally (in the .m files)
#define DEBUG_FLAG(x)                   (DEBUG_MASTER && x)

// will evaluate to YES if DEBUG_LOCAL is set AND if this is a debug build
#define DEBUG_MODE                      DEBUG_FLAG(DEBUG_LOCAL)

// will evaluate to YES if DEBUG_LOCAL and DEBUG_VERBOSE are set, AND
// if this is a debug build
#define DEBUG_MODE_VERBOSE              DEBUG_FLAG(DEBUG_LOCAL && DEBUG_VERBOSE)

/******************************************************************************/
#pragma mark Logging (low-level)
/******************************************************************************/

#if defined(__OBJC__)
// applies when compiled into an Objective-C app
#import "MBModuleLog.h"
#define MBLog(severity, ...)        [[MBModuleLog loggerClass] logMessage:[NSString stringWithFormat:__VA_ARGS__] \
                                                               atSeverity:severity \
                                                            callingObject:self \
                                                         callingSignature:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                                                          callingFilePath:[NSString stringWithUTF8String:__FILE__] \
                                                          callingFileLine:__LINE__]
#else
// applies when compiled into a C/C++ app
#define MBLog(severity, ...)        NSLog(@"(%@:%u) %@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, [NSString stringWithFormat:__VA_ARGS__])
#endif

#define MBLogTrace(severity)        MBLog(severity, @"%s", __PRETTY_FUNCTION__)

#define MBLogObject(severity, x)    MBLog(severity, @"%@ = %@@%p: %@", @"" # x, [x class], x, [x description])

#define MBLogString(severity, x)    MBLog(severity, @"\"%@\" (length: %lu)", x, (unsigned long)[x length])

/******************************************************************************/
#pragma mark Logging (high-level)
/******************************************************************************/

#define MBLogVerbose(...)           MBLog(MBModuleLogSeverityVerbose, __VA_ARGS__)
#define MBLogDebug(...)             MBLog(MBModuleLogSeverityDebug, __VA_ARGS__)
#define MBLogInfo(...)              MBLog(MBModuleLogSeverityInfo, __VA_ARGS__)
#define MBLogWarning(...)           MBLog(MBModuleLogSeverityWarning, __VA_ARGS__)
#define MBLogError(...)             MBLog(MBModuleLogSeverityError, __VA_ARGS__)

#define MBLogTraceVerbose()         MBLogTrace(MBModuleLogSeverityVerbose)
#define MBLogTraceDebug()           MBLogTrace(MBModuleLogSeverityDebug)
#define MBLogTraceInfo()            MBLogTrace(MBModuleLogSeverityInfo)
#define MBLogTraceWarning()         MBLogTrace(MBModuleLogSeverityWarning)
#define MBLogTraceError()           MBLogTrace(MBModuleLogSeverityError)

#define MBLogObjectVerbose(x)       MBLogObject(MBModuleLogSeverityVerbose, x)
#define MBLogObjectDebug(x)         MBLogObject(MBModuleLogSeverityDebug, x)
#define MBLogObjectInfo(x)          MBLogObject(MBModuleLogSeverityInfo, x)
#define MBLogObjectWarning(x)       MBLogObject(MBModuleLogSeverityWarning, x)
#define MBLogObjectError(x)         MBLogObject(MBModuleLogSeverityError, x)

#define MBLogStringVerbose(x)       MBLogString(MBModuleLogSeverityVerbose, x)
#define MBLogStringDebug(x)         MBLogString(MBModuleLogSeverityDebug, x)
#define MBLogStringInfo(x)          MBLogString(MBModuleLogSeverityInfo, x)
#define MBLogStringWarning(x)       MBLogString(MBModuleLogSeverityWarning, x)
#define MBLogStringError(x)         MBLogString(MBModuleLogSeverityError, x)

/******************************************************************************/
#pragma mark Legacy logging macros (deprecated)
/******************************************************************************/

#define consoleLog(...)             MBLogInfo(__VA_ARGS__)
#define consoleTrace()              MBLogTraceInfo()
#define consoleObj(x)               MBLogObjectInfo(x)
#define consoleStr(x)               MBLogStringInfo(x)

#define errorLog(...)               MBLogError(__VA_ARGS__)
#define errorObj(x)                 MBLogObjectError(x)
#define errorStr(x)                 MBLogStringError(x)

#define debugLog(...)               if (DEBUG_MODE) MBLogDebug(__VA_ARGS__)
#define debugTrace()                if (DEBUG_MODE) MBLogTraceDebug()
#define debugObj(x)                 if (DEBUG_MODE) MBLogObjectDebug(x)
#define debugStr(x)                 if (DEBUG_MODE) MBLogStringDebug(x)

#define verboseDebugLog(...)        if (DEBUG_MODE_VERBOSE) MBLogVerbose(__VA_ARGS__)
#define verboseDebugTrace()         if (DEBUG_MODE_VERBOSE) MBLogTraceVerbose()
#define verboseDebugObj(x)          if (DEBUG_MODE_VERBOSE) MBLogObjectVerbose(x)
#define verboseDebugStr(x)          if (DEBUG_MODE_VERBOSE) MBLogStringverbose(x)

/******************************************************************************/
#pragma mark Triggering the debugger
/******************************************************************************/

#define __triggerDebugBreakMsg(f, m)    if (DEBUG_MASTER) { consoleLog(@"Breakpoint hit!\n\nEntering debugger due to %@%@\n\n\t• Type 'up 2' to see breakpoint position\n\t• Type 'fin' and then 'fin' again to select calling stack frame\n\t• Type 'c' to continue execution\n\n", f, (m ? [NSString stringWithFormat:@" -- %@", m] : @"")); kill(getpid(), SIGSTOP); }

#define triggerDebugBreak()             __triggerDebugBreakMsg(@"triggerDebugBreak()", nil)

#define triggerDebugBreakIf(x)          if (DEBUG_MASTER && x) { NSString* call = [NSString stringWithFormat:@"triggerDebugBreakIf(%s)", #x]; __triggerDebugBreakMsg(call, nil); }

#define triggerDebugBreakMsg(m)         __triggerDebugBreakMsg(@"triggerDebugBreakMsg()", m)

/******************************************************************************/
#pragma mark Code profiling
/******************************************************************************/

/*
 When in debug mode (via DEBUG_MASTER) provides a simple mechanism to profile
 a chunk of code. Start by doing:

     MBProfilingTimerStart(@"critical path 1");

         ...code you want to profile...

     MBProfilingTimerEnd();

 When the code is run, check the console for output.

 Note that you can only call MBProfilingTimerStart() once within a given
 scope. If you want to profile a different section of code within the same
 code scope, you must use MBProfilingTimerRestart(), eg.:

     MBProfilingTimerRestart(@"critical path 2");

         ...other code you want to profile...

     MBProfilingTimerEnd();
 */
#if (DEBUG_MASTER)
#define MBProfilingTimerStart(x) \
NSTimeInterval __MBProfilingTimerEnd = 0; \
NSTimeInterval __MBProfilingTimerStart = [NSDate timeIntervalSinceReferenceDate]; \
NSString* __MBProfilingTimerName = x; \
consoleLog(@"Profiling timer:\t%@ starting", __MBProfilingTimerName);

#define MBProfilingTimerEnd() \
__MBProfilingTimerEnd = [NSDate timeIntervalSinceReferenceDate]; \
consoleLog(@"Profiling timer:\t%@\t%g\tseconds elapsed", __MBProfilingTimerName, (__MBProfilingTimerEnd - __MBProfilingTimerStart));

#define MBProfilingTimerRestart(x) \
__MBProfilingTimerEnd = 0; \
__MBProfilingTimerStart = [NSDate timeIntervalSinceReferenceDate]; \
__MBProfilingTimerName = x;
#else
#define MBProfilingTimerStart(x)
#define MBProfilingTimerEnd()
#define MBProfilingTimerRestart(x)
#endif
