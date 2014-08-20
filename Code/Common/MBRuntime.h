//
//  MBRuntime.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/29/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

/******************************************************************************/
#pragma mark Class detection
/******************************************************************************/

// this macro will allow us to change over to [ClassName class] != nil checks
// once the full iOS SDK supports it (requires support for NS_CLASS_AVAILABLE)
#define MBRuntimeClassExists(x)           (NSClassFromString([NSString stringWithFormat:@"%s", #x]) != nil)

/******************************************************************************/
#pragma mark Operating system version detection
/******************************************************************************/

#define MBRuntimeOSEqualToVersion(versionString)              ([[[UIDevice currentDevice] systemVersion] compare:versionString options:NSNumericSearch] == NSOrderedSame)
#define MBRuntimeOSGreaterThanVersion(versionString)          ([[[UIDevice currentDevice] systemVersion] compare:versionString options:NSNumericSearch] == NSOrderedDescending)
#define MBRuntimeOSGreaterThanEqualToVersion(versionString)   ([[[UIDevice currentDevice] systemVersion] compare:versionString options:NSNumericSearch] != NSOrderedAscending)
#define MBRuntimeOSLessThanVersion(versionString)             ([[[UIDevice currentDevice] systemVersion] compare:versionString options:NSNumericSearch] == NSOrderedAscending)
#define MBRuntimeOSLessThanEqualToVersion(versionString)      ([[[UIDevice currentDevice] systemVersion] compare:versionString options:NSNumericSearch] != NSOrderedDescending)
