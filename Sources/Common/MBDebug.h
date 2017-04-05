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
#pragma mark Triggering the debugger
/******************************************************************************/

#define __MBTriggerDebugBreakMsg(f, m)    if (DEBUG_MASTER) { NSLog(@"Breakpoint hit!\n\nEntering debugger due to %@%@\n\n\t• Type 'up 2' to see breakpoint position\n\t• Type 'fin' and then 'fin' again to select calling stack frame\n\t• Type 'c' to continue execution\n\n", f, (m ? [NSString stringWithFormat:@" -- %@", m] : @"")); kill(getpid(), SIGSTOP); }

#define MBTriggerDebugBreak()             __MBTriggerDebugBreakMsg(@"triggerDebugBreak()", nil)

#define MBTriggerDebugBreakIf(x)          if (DEBUG_MASTER && x) { NSString* call = [NSString stringWithFormat:@"triggerDebugBreakIf(%s)", #x]; __MBTriggerDebugBreakMsg(call, nil); }

#define MBTriggerDebugBreakMsg(m)         __MBTriggerDebugBreakMsg(@"triggerDebugBreakMsg()", m)
