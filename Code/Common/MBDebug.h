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

/******************************************************************************/
#pragma mark Console logging
/******************************************************************************/

#if defined(__OBJC__)
// applies when compiled into an Objective-C app
#define consoleLog(...)                 NSLog(@"(%@:%u) <%p> %@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, self, [NSString stringWithFormat:__VA_ARGS__])
#else
// applies when compiled into a C/C++ app
#define consoleLog(...)                 NSLog(@"(%@:%u) %@", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, [NSString stringWithFormat:__VA_ARGS__])
#endif

#define consoleTrace()                  consoleLog(@"%s", __PRETTY_FUNCTION__)

#define consoleObj(x)                   consoleLog(@"%@ = %@@%p: %@", @"" # x, [x class], x, [x description]);

#define consoleStr(x)                   consoleLog(@"\"%@\" (length: %lu)", x, (unsigned long)[x length]);

/******************************************************************************/
#pragma mark Exception logging
/******************************************************************************/

#define exceptionLog(x)                 NSLog(@"\n%@", x);

/******************************************************************************/
#pragma mark Error logging
/******************************************************************************/

#define errorLog(...)                   consoleLog(@"\n\n+++ %@ +++\n\n", [NSString stringWithFormat:__VA_ARGS__]);

#define errorStr(x)                     errorLog(@"%@", x);

#define errorObj(x)                     errorLog(@"%@: %@", [x class], [x description]);

/******************************************************************************/
#pragma mark Debug logging
/******************************************************************************/

#define debugLog(...)                   if (DEBUG_MODE) consoleLog(__VA_ARGS__)

#define debugStr(x)                     if (DEBUG_MODE) consoleStr(x)

#define debugObj(x)                     if (DEBUG_MODE) consoleObj(x)

#define debugTrace()                    if (DEBUG_MODE) consoleTrace()

/******************************************************************************/
#pragma mark Verbose debug logging
/******************************************************************************/

#define DEBUG_MODE_VERBOSE              DEBUG_FLAG(DEBUG_LOCAL && DEBUG_VERBOSE)

#define verboseDebugLog(...)            if (DEBUG_MODE_VERBOSE) consoleLog(__VA_ARGS__)

#define verboseDebugStr(x)              if (DEBUG_MODE_VERBOSE) consoleStr(x)

#define verboseDebugObj(x)              if (DEBUG_MODE_VERBOSE) consoleObj(x)

#define verboseDebugTrace()             if (DEBUG_MODE_VERBOSE) consoleTrace()

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
