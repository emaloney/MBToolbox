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
#define MBLogVerboseTrace()         if (DEBUG_MODE_VERBOSE) MBLogTrace(MBModuleLogSeverityVerbose)
#define MBLogVerboseObject(x)       if (DEBUG_MODE_VERBOSE) MBLogObject(MBModuleLogSeverityVerbose, x)
#define MBLogVerboseString(x)       if (DEBUG_MODE_VERBOSE) MBLogString(MBModuleLogSeverityVerbose, x)

#define MBLogDebug(...)             if (DEBUG_MODE) MBLog(MBModuleLogSeverityDebug, __VA_ARGS__)
#define MBLogDebugTrace()           if (DEBUG_MODE) MBLogTrace(MBModuleLogSeverityDebug)
#define MBLogDebugObject(x)         if (DEBUG_MODE) MBLogObject(MBModuleLogSeverityDebug, x)
#define MBLogDebugString(x)         if (DEBUG_MODE) MBLogString(MBModuleLogSeverityDebug, x)

#define MBLogInfo(...)              MBLog(MBModuleLogSeverityInfo, __VA_ARGS__)
#define MBLogInfoTrace()            MBLogTrace(MBModuleLogSeverityInfo)
#define MBLogInfoObject(x)          MBLogObject(MBModuleLogSeverityInfo, x)
#define MBLogInfoString(x)          MBLogString(MBModuleLogSeverityInfo, x)

#define MBLogWarning(...)           MBLog(MBModuleLogSeverityWarning, __VA_ARGS__)
#define MBLogWarningTrace()         MBLogTrace(MBModuleLogSeverityWarning)
#define MBLogWarningObject(x)       MBLogObject(MBModuleLogSeverityWarning, x)
#define MBLogWarningString(x)       MBLogString(MBModuleLogSeverityWarning, x)

#define MBLogError(...)             MBLog(MBModuleLogSeverityError, __VA_ARGS__)
#define MBLogErrorTrace()           MBLogTrace(MBModuleLogSeverityError)
#define MBLogErrorObject(x)         MBLogObject(MBModuleLogSeverityError, x)
#define MBLogErrorString(x)         MBLogString(MBModuleLogSeverityError, x)
