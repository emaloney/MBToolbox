//
//  MBService.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/13/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBSingleton.h"

/******************************************************************************/
#pragma mark Forward declarations
/******************************************************************************/

@protocol MBService;

/******************************************************************************/
#pragma mark Types
/******************************************************************************/

typedef NSObject<MBService, MBSingleton> MBService;

/******************************************************************************/
#pragma mark -
#pragma mark MBService protocol
/******************************************************************************/

/*!
 The `MBService` protocol is implemented by classes that provide runtime 
 services that might not need to be running during the entire lifetime of the 
 application.

 For example, an application might not want to start the `MBGeolocationService`
 until the user takes an action that requires location information. This will
 ensure that the user isn't prompted by iOS for Location Services permission 
 until absolutely necessary.
 
 Also, because the use of Location Services can increase battery drain, by
 being implemented as a service, `MBGeolocationService` can be turned off when
 not in need.
 
 This is more respectful of the user's resources.

 @warning This protocol declares methods that are intended to be called *only*
 by the `MBServiceManager`. Do not call these methods directly. To make use of
 a service, you should use methods provided by the `MBServiceManager` singleton.
 */
@protocol MBService <MBSingleton>

/*!
 Requests that the service start running.
 
 @warning This method is called as needed by the `MBServiceManager` and must
 not be called directly.
 */
- (void) startService;

/*!
 Requests that the service stop running.
 
 This method is optional; services that do not support stopping do not need
 to implement.

 @warning This method is called as needed by the `MBServiceManager` and must
 not be called directly.
 */
@optional
- (void) stopService;

/*!
 Configures the service according to the keys and values contained in the
 specified dictionary.

 This method is optional; services that do not support configuration do not need
 to implement.
 
 @param     params The configuration parameters for the service. Acceptable 
            configuration values are service-specific.
 
 @note Services should log a console error but otherwise ignore any unrecognized
 keys or unsupported values passed to this method.
*/
@optional
- (void) configureService:(NSDictionary*)params;

@end

