//
//  MBBatteryMonitor.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 1/18/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBService.h"

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

extern NSString* const kMBBatteryMonitorUpdateEvent;    //!< @"MBBatteryMonitor:update"

/******************************************************************************/
#pragma mark -
#pragma mark MBBatteryState class
/******************************************************************************/

/*!
 When the `MBBatteryMonitor` service posts a `MBBatteryMonitor:update` event
 to the default `NSNotificationCenter`, the `object` of the `NSNotification`
 will contain an `MBBatteryState` object describing the state of the battery.
 */
@interface MBBatteryState : NSObject

/*! `YES` if the device is currently plugged in to wall power. */
@property(nonatomic, readonly) BOOL isPluggedIn;

/*! `YES` if the device is currently plugged in and charging. */
@property(nonatomic, readonly) BOOL isCharging;

/*! `YES` if the device is currently plugged in and fully charged. */
@property(nonatomic, readonly) BOOL isFullyCharged;

/*! `YES` if the device is currently unplugged and draining the battery. */
@property(nonatomic, readonly) BOOL isDraining;

/*! A number between `0.0` and `1.0` (inclusive) indicating the percent of
    battery charge remaining. A value of `0.0` indicates that the device
    has no battery charge remaining, while `1.0` indicates that the battery
    is fully charged. */
@property(nonatomic, readonly) float batteryLevel;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBBatteryMonitor class
/******************************************************************************/

/*!
 The `MBBatteryMonitor` is a service that fires event notifications when
 there are changes to device's battery state, battery level, and plugged-in 
 status.
 
 When the `MBBatteryMonitor` service is running, the service will periodically 
 fire `NSNotification` events with the name "`MBBatteryMonitor:update`" whenever
 there are status updates to report.
 
 The `object` method of the `NSNotification` for the "`MBBatteryMonitor:update`"
 event will return an `MBBatteryState` object providing details about the
 battery and power state of the device. (Within an MBML `<Listener>`, the
 `MBBatteryState` can be accessed through the expression "`$Event.object`".)

 @note      Notification events are posted *only* when the `MBBatteryMonitor`
            service is running. Use the interface provided by the
            `MBServiceManager` to ensure that the service is running when
            needed.
 */
@interface MBBatteryMonitor : NSObject <MBService>

/*!
 Determines the current battery state when the `MBBatteryMonitor` service
 is running.

 @return    An `MBBatteryState` instance whose properties reflect the
            current state of the device's battery. Will be `nil` if the
            `MBBatteryMonitor` service is not running.
 */
- (MBBatteryState*) currentBatteryState;

@end
