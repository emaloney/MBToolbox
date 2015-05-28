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
 Returns the name of the module.
 
 @return    The module name.
 */
+ (nonnull NSString*) moduleName;

/*!
 Returns the `MBModuleLog` associated with the receiving module.
 
 @return    The module log.
 */
+ (nonnull MBModuleLog*) log;

@optional

/*!
 Returns an `NSBundle` instance representing the resource bundle of the module.

 @return    The module's resource bundle, or `nil` if one doesn't exist.
 */
+ (nullable NSBundle*) resourceBundle;

/*!
 This optional method is implemented by modules that participate in the
 environment loading process. When the module is activated, its associated 
 environment loaders will be used to populate the current environment.
 
 @return    The environment loader classes used by the module. `nil` is
            an acceptable return value to indicate that the module
            has no associated environment loaders.
 */
+ (nullable NSArray*) environmentLoaderClasses;

/*!
 This optional method is implemented by modules that need a specific
 environment file included whenever a new environment is loaded. If the
 method is not implemented or if it returns `nil`, no attempt will
 be made to load an environment file for the module.
 
 @return    The name of the environment file to load. Note that this is
            a filename and not a full pathname.
 */
+ (nullable NSString*) moduleEnvironmentFilename;

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
@property(nonnull, nonatomic, readonly) MBModuleLog* log;

@end
