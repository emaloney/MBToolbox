//
//  MBLog.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 5/28/15.
//  Copyright (c) 2015 Gilt Groupe. All rights reserved.
//

#import "MBModuleLog.h"

/******************************************************************************/
#pragma mark Logging macros (low-level)
/******************************************************************************/

#define MBLog(severity, ...)        [[MBModuleLog loggerClass] logMessage:[NSString stringWithFormat:__VA_ARGS__] \
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
