//
//  MBToolbox.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 3/18/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#ifndef __OBJC__

#error Mockingbird Toolbox requires Objective-C

#else

#import <Foundation/Foundation.h>

//! Project version number for MBToolbox.
FOUNDATION_EXPORT double MBToolboxVersionNumber;

//! Project version string for MBToolbox.
FOUNDATION_EXPORT const unsigned char MBToolboxVersionString[];

//
// NOTE: This header file is indended for external use. It should *not* be
//       included from within code in the Mockingbird Toolbox itself.
//

// import the public headers

#import <MBToolbox/MBAvailability.h>

#if MB_BUILD_IOS
#import <MBToolbox/MBBatteryMonitor.h>
#import <MBToolbox/MBNetworkIndicator.h>
#import <MBToolbox/UIColor+MBToolbox.h>
#import <MBToolbox/UIImage+MBImageScaling.h>
#import <MBToolbox/UIView+MBSnapshotImage.h>
#import <MBToolbox/UIFont+MBStringSizing.h>
#endif

#import <MBToolbox/MBCacheOperations.h>
#import <MBToolbox/MBFilesystemCache+Subclassing.h>
#import <MBToolbox/MBFilesystemCache.h>
#import <MBToolbox/MBThreadsafeCache+Subclassing.h>
#import <MBToolbox/MBThreadsafeCache.h>
#import <MBToolbox/MBAssert.h>
#import <MBToolbox/MBDebug.h>
#import <MBToolbox/MBRuntime.h>
#import <MBToolbox/MBConcurrentReadWriteCoordinator.h>
#import <MBToolbox/NSError+MBToolbox.h>
#import <MBToolbox/MBEvents.h>
#import <MBToolbox/MBFieldListFormatter.h>
#import <MBToolbox/MBFormattedDescriptionObject.h>
#import <MBToolbox/MBBitmapPixelPlane.h>
#import <MBToolbox/MBRoundedRectTools.h>
#import <MBToolbox/MBMessageDigest.h>
#import <MBToolbox/NSData+MBMessageDigest.h>
#import <MBToolbox/NSString+MBMessageDigest.h>
#import <MBToolbox/MBModule.h>
#import <MBToolbox/MBModuleLog.h>
#import <MBToolbox/MBModuleLogMacros.h>
#import <MBToolbox/MBNetworkMonitor.h>
#import <MBToolbox/MBFilesystemOperations.h>
#import <MBToolbox/MBOperationQueue.h>
#import <MBToolbox/MBRegexCache.h>
#import <MBToolbox/NSString+MBRegex.h>
#import <MBToolbox/MBService.h>
#import <MBToolbox/MBServiceManager.h>
#import <MBToolbox/MBSingleton.h>
#import <MBToolbox/MBStringFunctions.h>
#import <MBToolbox/NSData+MBStringConversion.h>
#import <MBToolbox/NSString+MBIndentation.h>
#import <MBToolbox/MBThreadLocalStorage.h>

#endif

