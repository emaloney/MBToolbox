//
//  MBAvailability.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/24/15.
//  Copyright (c) 2015 Gilt Groupe. All rights reserved.
//

#import <TargetConditionals.h>

#define MB_BUILD_IOS        0
#define MB_BUILD_WATCHOS    0
#define MB_BUILD_OSX        0

#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR

#if TARGET_OS_WATCH

#ifdef MB_BUILD_WATCHOS
#undef MB_BUILD_WATCHOS
#endif

#define MB_BUILD_WATCHOS    1

#else                   // #if TARGET_OS_WATCH

#ifdef MB_BUILD_IOS
#undef MB_BUILD_IOS
#endif

#define MB_BUILD_IOS        1

#endif                  // #else from #if TARGET_OS_WATCH

#elif TARGET_OS_MAC     // #if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR

#ifdef MB_BUILD_OSX
#undef MB_BUILD_OSX
#endif

#define MB_BUILD_OSX        1

#endif                  // #elif TARGET_OS_MAC from #if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
