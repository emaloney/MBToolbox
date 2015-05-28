//
//  MBModuleLogMacros.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 5/28/15.
//  Copyright (c) 2015 Gilt Groupe. All rights reserved.
//

#import "MBDebug.h"
#import "MBModuleLog.h"

/******************************************************************************/
#pragma mark Logging macros (low-level)
/******************************************************************************/

#define MBLog(severity, ...)        [[MBModuleLog logRecorderClass] logMessage:[NSString stringWithFormat:__VA_ARGS__] \
                                                               atSeverity:severity \
                                                            callingObject:self \
                                                         callingSignature:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                                                          callingFilePath:[NSString stringWithUTF8String:__FILE__] \
                                                          callingFileLine:__LINE__]

#define MBLogTrace(severity)        MBLog(severity, @"%s", __PRETTY_FUNCTION__)

#define MBLogObject(severity, x)    MBLog(severity, @"%@ = %@@%p: %@", @"" # x, [x class], x, [x description])

#define MBLogString(severity, x)    MBLog(severity, @"\"%@\" (length: %lu)", x, (unsigned long)[x length])

/******************************************************************************/
#pragma mark Logging macros (high-level)
/******************************************************************************/

#define MBLogVerbose(...)           if (DEBUG_MODE_VERBOSE) MBLog(MBModuleLogSeverityVerbose, __VA_ARGS__)
#define MBLogDebug(...)             if (DEBUG_MODE) MBLog(MBModuleLogSeverityDebug, __VA_ARGS__)
#define MBLogInfo(...)              MBLog(MBModuleLogSeverityInfo, __VA_ARGS__)
#define MBLogWarning(...)           MBLog(MBModuleLogSeverityWarning, __VA_ARGS__)
#define MBLogError(...)             MBLog(MBModuleLogSeverityError, __VA_ARGS__)

#define MBLogTraceVerbose()         if (DEBUG_MODE_VERBOSE) MBLogTrace(MBModuleLogSeverityVerbose)
#define MBLogTraceDebug()           if (DEBUG_MODE) MBLogTrace(MBModuleLogSeverityDebug)
#define MBLogTraceInfo()            MBLogTrace(MBModuleLogSeverityInfo)
#define MBLogTraceWarning()         MBLogTrace(MBModuleLogSeverityWarning)
#define MBLogTraceError()           MBLogTrace(MBModuleLogSeverityError)

#define MBLogObjectVerbose(x)       if (DEBUG_MODE_VERBOSE) MBLogObject(MBModuleLogSeverityVerbose, x)
#define MBLogObjectDebug(x)         if (DEBUG_MODE) MBLogObject(MBModuleLogSeverityDebug, x)
#define MBLogObjectInfo(x)          MBLogObject(MBModuleLogSeverityInfo, x)
#define MBLogObjectWarning(x)       MBLogObject(MBModuleLogSeverityWarning, x)
#define MBLogObjectError(x)         MBLogObject(MBModuleLogSeverityError, x)

#define MBLogStringVerbose(x)       if (DEBUG_MODE_VERBOSE) MBLogString(MBModuleLogSeverityVerbose, x)
#define MBLogStringDebug(x)         if (DEBUG_MODE) MBLogString(MBModuleLogSeverityDebug, x)
#define MBLogStringInfo(x)          MBLogString(MBModuleLogSeverityInfo, x)
#define MBLogStringWarning(x)       MBLogString(MBModuleLogSeverityWarning, x)
#define MBLogStringError(x)         MBLogString(MBModuleLogSeverityError, x)
