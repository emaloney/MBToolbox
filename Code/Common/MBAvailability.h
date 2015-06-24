//
//  MBAvailability.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/24/15.
//  Copyright (c) 2015 Gilt Groupe. All rights reserved.
//

#import <AvailabilityMacros.h>

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR

#ifndef MB_BUILD_IOS
#define MB_BUILD_IOS    1
#endif

#elif TARGET_OS_MAC

#ifndef MB_BUILD_OSX
#define MB_BUILD_OSX    1
#endif

#endif
