//
//  MBServiceManager.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/14/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBSingleton.h"
#import "MBService.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBServiceManager class
/******************************************************************************/

/*!
 This class manages the lifecycle of various runtime services that adopt the
 `MBService` protocol.
 
 Services are shared resources that need to be available any time at least one
 client is using the service.

 ### Attaching & detaching services

 Rather than starting and stopping services directly, clients coordinate 
 through the `MBServiceManager` singleton, which provides an interface allowing
 users to _attach_ to and _detach_ from various services.

 Attaching a service signals that a client of that service wishes to keep it
 running. The first time a client attaches a service, the `MBServiceManager`
 will start the service. As long as there is at least one client attached to
 a service, the service will remain running.
 
 Once a client no longer requires the use of a service, it should detach. When
 the last remaining client detaches, the `MBServiceManager` will stop the
 service.
 
 Note that some services do not support being stopped, in which case detaching
 has no effect.
 
 ### Services within MBML

 Within MBML, the `<AttachService>` and `<DetachService>` listener
 actions can be used. See `MBAttachServiceAction` and `MBDetachServiceAction`
 for additional information.
 
 @warning   You *must not* create instances of this class yourself; this class
            is a singleton. Call the `instance` class method (declared by the
            `MBSingleton` protocol) to acquire the singleton instance.
 */
@interface MBServiceManager : NSObject <MBSingleton>

/*----------------------------------------------------------------------------*/
#pragma mark Acquiring service instances
/*!    @name Acquiring service instances                                      */
/*----------------------------------------------------------------------------*/

/*!
 Returns the singleton instance of the service implemented by the class with
 the specified name.
 
 @param     serviceClassName The name of the class implementing the
            `MBService` protocol.
 
 @return    A pointer to the singleton `MBService` with the specified class 
            name, or `nil` if there isn't one.
 */
- (id) serviceForClassName:(NSString*)serviceClassName;

/*!
 Returns the singleton instance of the service implemented the specified class.
 
 @param     serviceClass The `Class` implementing the `MBService` protocol.
 
 @return    A pointer to the singleton `MBService` of the specified class,
            or `nil` if there isn't one.
 */
- (id) serviceForClass:(Class)serviceClass;

/*----------------------------------------------------------------------------*/
#pragma mark Attaching to services
/*!    @name Attaching to services                                            */
/*----------------------------------------------------------------------------*/

/*!
 Attaches to the specified service, incrementing its attach count by one.

 Services with an attach count greater than zero will be kept running by the
 `MBServiceManager`.

 @note      When the service is no longer needed, the caller should be sure to
            detach the service.

 @param     service The service being attached.
 */
- (void) attachToService:(MBService*)service;

/*!
 Attaches to the service with the given class name, incrementing its attach
 count by one.
 
 Services with an attach count greater than zero will be kept running by the
 `MBServiceManager`.

 @note      When the service is no longer needed, the caller should be sure to
            detach the service.

 @param     serviceClass The implementing class of the service class to attach.
 
 @return    If successful, the `MBService` instance that was attached. Will
            return `nil` on failure.
 */
- (id) attachToServiceClass:(Class)serviceClass;

/*!
 Attaches to the service with the given class name, incrementing its attach
 count by one.
 
 Services with an attach count greater than zero will be kept running by the
 `MBServiceManager`.

 @note      When the service is no longer needed, the caller should be sure to
            detach the service.

 @param     serviceClassName The name of the service class to attach.

 @return    If successful, the `MBService` instance that was attached. Will
            return `nil` on failure.
 */
- (id) attachToServiceClassNamed:(NSString*)serviceClassName;

/*----------------------------------------------------------------------------*/
#pragma mark Detaching from services
/*!    @name Detaching from services                                          */
/*----------------------------------------------------------------------------*/

/*!
 Detaches from the specified service, decrementing its attach count by one.

 Services are stopped by the `MBServiceManager` when their attach count
 decreases to zero.

 @note      Code should only detach from a service if it previously attached
            to the same service.

 @param     service The service being attached.
 */
- (void) detachFromService:(MBService*)service;

/*!
 Detaches from the service with the given class name, decrementing its attach
 count by one.
 
 Services are stopped by the `MBServiceManager` when their attach count
 decreases to zero.

 @note      Code should only detach from a service if it previously attached
            to the same service. Detach requests are ignored if the service
            isn't already running.

 @param     serviceClass The implementing class of the service class to detach.

 @return    If successful, the `MBService` instance that was attached. Will
            return `nil` on failure.
 */
- (void) detachFromServiceClass:(Class)serviceClass;

/*!
 Detaches from the service with the given class name, decrementing its attach
 count by one.
 
 Services are stopped by the `MBServiceManager` when their attach count
 decreases to zero.

 @note      Code should only detach from a service if it previously attached
            to the same service. Detach requests are ignored if the service
            isn't already running.

 @param     serviceClassName The name of the service class to attach.

 @return    If successful, the `MBService` instance that was attached. Will
            return `nil` on failure.
 */
- (void) detachFromServiceClassNamed:(NSString*)serviceClassName;

/*----------------------------------------------------------------------------*/
#pragma mark Querying the status of services
/*!    @name Querying the status of services                                  */
/*----------------------------------------------------------------------------*/

/*!
 Determines whether the specified service is running.
 
 A service will remain running as long as its attach count is greater than zero.
 
 @param     service The service whose status is sought.
 
 @return    `YES` if the service is running; `NO` if it is not.
 */
- (BOOL) isServiceRunning:(MBService*)service;

/*!
 Determines the current attach count of a service.
  
 @param     service The service whose attach count is sought.

 @return    The service's current attach count.
 */
- (NSUInteger) attachCountForService:(MBService*)service;

@end
