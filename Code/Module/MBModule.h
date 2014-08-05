//
//  MBModule.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/24/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBSingleton.h"
#import "MBModuleLog.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBModule class
/******************************************************************************/

/*!
 Modules are the mechanism by which functionality is added to Mockingbird.
 
 Related sets of code are exposed as modules, each of which is represented
 by an `MBModule` singleton instance.
 
 Each module has an associated logger, which can be used to report
 module-specific information to the console.
 */
@protocol MBModule <MBInstanceVendor>

/*!
 Returns the `MBModuleLog` associated with the receiving module.
 
 @return    The module log.
 */
+ (MBModuleLog*) log;

@optional

/*!
 This optional method is implemented by modules that participate in the
 environment loading process. When the module is activated, its associated 
 environment loaders will be used to populate the current environment.
 
 @return    The environment loader classes used by the module. `nil` is
            an acceptable return value to indicate that the module
            has no associated environment loaders.
 */
+ (NSArray*) environmentLoaderClasses;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBModuleBase class
/******************************************************************************/

/*!
 Modules are the mechanism by which functionality is added to Mockingbird.

 Related sets of code are exposed as modules, each of which is represented
 by an `MBModule` singleton instance.

 Each module has an associated logger, which can be used to report
 module-specific information to the console.
 */
@interface MBModuleBase : NSObject <MBModule>

/*!
 Returns the `MBModuleLog` associated with the receiver.

 The log can be used to record notable runtime occurrances to the console.
 */
@property(nonatomic, readonly) MBModuleLog* log;

/*!
 Modules that participate in the environment loading process may override this
 method to indicate the environment loaders it uses. When the module is
 activated, its associated environment loaders will be used to populate the
 current environment.
 
 @return    The environment loader classes used by the module. The default
            implementation returns `nil` to indicate that the module
            has no associated environment loaders.
 */
+ (NSArray*) environmentLoaderClasses;

@end
