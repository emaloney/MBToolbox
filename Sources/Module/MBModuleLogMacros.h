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

#define MBLogObject(severity, x)    MBLog(severity, @"%@ = %@@%p: %@", @"" # x, [x class], (void*)x, [x description])

#define MBLogString(severity, x)    MBLog(severity, @"\"%@\" (length: %lu)", x, (unsigned long)[x length])

/******************************************************************************/
#pragma mark Logging macros (high-level)
/******************************************************************************/

#define MBLogVerbose(...)           if (DEBUG_MODE_VERBOSE) MBLog(MBLogSeverityVerbose, __VA_ARGS__)
#define MBLogVerboseTrace()         if (DEBUG_MODE_VERBOSE) MBLogTrace(MBLogSeverityVerbose)
#define MBLogVerboseObject(x)       if (DEBUG_MODE_VERBOSE) MBLogObject(MBLogSeverityVerbose, x)
#define MBLogVerboseString(x)       if (DEBUG_MODE_VERBOSE) MBLogString(MBLogSeverityVerbose, x)

#define MBLogDebug(...)             if (DEBUG_MODE) MBLog(MBLogSeverityDebug, __VA_ARGS__)
#define MBLogDebugTrace()           if (DEBUG_MODE) MBLogTrace(MBLogSeverityDebug)
#define MBLogDebugObject(x)         if (DEBUG_MODE) MBLogObject(MBLogSeverityDebug, x)
#define MBLogDebugString(x)         if (DEBUG_MODE) MBLogString(MBLogSeverityDebug, x)

#define MBLogInfo(...)              MBLog(MBLogSeverityInfo, __VA_ARGS__)
#define MBLogInfoTrace()            MBLogTrace(MBLogSeverityInfo)
#define MBLogInfoObject(x)          MBLogObject(MBLogSeverityInfo, x)
#define MBLogInfoString(x)          MBLogString(MBLogSeverityInfo, x)

#define MBLogWarning(...)           MBLog(MBLogSeverityWarning, __VA_ARGS__)
#define MBLogWarningTrace()         MBLogTrace(MBLogSeverityWarning)
#define MBLogWarningObject(x)       MBLogObject(MBLogSeverityWarning, x)
#define MBLogWarningString(x)       MBLogString(MBLogSeverityWarning, x)

#define MBLogError(...)             MBLog(MBLogSeverityError, __VA_ARGS__)
#define MBLogErrorTrace()           MBLogTrace(MBLogSeverityError)
#define MBLogErrorObject(x)         MBLogObject(MBLogSeverityError, x)
#define MBLogErrorString(x)         MBLogString(MBLogSeverityError, x)
