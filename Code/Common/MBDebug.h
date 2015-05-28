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
#pragma mark Legacy logging macros (deprecated)
/******************************************************************************/

#import "MBLog.h"

// we're keeping these in this .h file instead of moving them to
// MBLog.h to avoid giving people the pain of having to shuffle
// around their #imports as a result of that change.
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
#define verboseDebugStr(x)          if (DEBUG_MODE_VERBOSE) MBLogStringVerbose(x)

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
