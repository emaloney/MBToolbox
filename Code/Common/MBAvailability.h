//
//  MBAvailability.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/24/15.
//  Copyright (c) 2015 Gilt Groupe. All rights reserved.
//

#import <TargetConditionals.h>

#ifdef MB_BUILD_IOS
#undef MB_BUILD_IOS
#endif

#ifdef MB_BUILD_MACOS
#undef MB_BUILD_MACOS
#endif

#ifdef MB_BUILD_WATCHOS
#undef MB_BUILD_WATCHOS
#endif

#ifdef MB_BUILD_TVOS
#undef MB_BUILD_TVOS
#endif

#if     TARGET_OS_IOS

#define MB_BUILD_IOS        1
#define MB_BUILD_MACOS      0
#define MB_BUILD_TVOS       0
#define MB_BUILD_WATCHOS    0

#elif   TARGET_OS_TV

#define MB_BUILD_IOS        0
#define MB_BUILD_MACOS      0
#define MB_BUILD_TVOS       1
#define MB_BUILD_WATCHOS    0

#elif   TARGET_OS_WATCH

#define MB_BUILD_IOS        0
#define MB_BUILD_MACOS      0
#define MB_BUILD_TVOS       0
#define MB_BUILD_WATCHOS    1

#elif   TARGET_OS_OSX

#define MB_BUILD_IOS        0
#define MB_BUILD_MACOS      1
#define MB_BUILD_TVOS       0
#define MB_BUILD_WATCHOS    0

#endif

#define MB_BUILD_UIKIT      (MB_BUILD_IOS || MB_BUILD_TVOS)
