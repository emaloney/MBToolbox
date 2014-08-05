//
//  MBBatteryMonitor.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 1/18/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBBatteryMonitor.h"
#import "MBEvents.h"

#define DEBUG_LOCAL		0

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

NSString* const kMBBatteryMonitorUpdateEvent    = @"MBBatteryMonitor:update";

/******************************************************************************/
#pragma mark -
#pragma mark MBBatteryState private interface
/******************************************************************************/

@interface MBBatteryState ()
@property(nonatomic, readwrite) BOOL isPluggedIn;
@property(nonatomic, readwrite) BOOL isCharging;
@property(nonatomic, readwrite) BOOL isFullyCharged;
@property(nonatomic, readwrite) BOOL isDraining;
@property(nonatomic, readwrite) float batteryLevel;
@end

@implementation MBBatteryState
@end

/******************************************************************************/
#pragma mark -
#pragma mark MBBatteryMonitor implementation
/******************************************************************************/

@implementation MBBatteryMonitor

MBImplementSingleton();

/******************************************************************************/
#pragma mark MBService implementation
/******************************************************************************/

- (void) startService
{
    debugTrace();
    
    [UIDevice currentDevice].batteryMonitoringEnabled = YES;
    
    NSNotificationCenter* notif = [NSNotificationCenter defaultCenter];
    [notif addObserver:self
              selector:@selector(_batteryStateUpdated)
                  name:UIDeviceBatteryLevelDidChangeNotification
                object:nil];
    
    [notif addObserver:self
              selector:@selector(_batteryStateUpdated)
                  name:UIDeviceBatteryStateDidChangeNotification
                object:nil];
}

- (void) stopService
{
    debugTrace();
    
    [UIDevice currentDevice].batteryMonitoringEnabled = NO;

    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

/******************************************************************************/
#pragma mark Battery state monitoring
/******************************************************************************/

- (MBBatteryState*) currentBatteryState
{
    UIDevice* device = [UIDevice currentDevice];
    UIDeviceBatteryState batteryState = device.batteryState;
    float batteryLevel = device.batteryLevel;
    if (batteryState != UIDeviceBatteryStateUnknown && batteryLevel != -1.0) {
        MBBatteryState* state = [MBBatteryState new];
        state.batteryLevel = batteryLevel;
        state.isPluggedIn = (batteryState == UIDeviceBatteryStateCharging || batteryState == UIDeviceBatteryStateFull);
        state.isCharging = (batteryState == UIDeviceBatteryStateCharging);
        state.isFullyCharged = (batteryState == UIDeviceBatteryStateFull);
        state.isDraining = (batteryState == UIDeviceBatteryStateUnplugged);
        return state;
    }
    return nil;
}

- (void) _batteryStateUpdated
{
    debugTrace();

    MBBatteryState* state = [self currentBatteryState];
    if (state) {
        [MBEvents postEvent:kMBBatteryMonitorUpdateEvent withObject:state];
    }
    else {
        errorLog(@"Won't post %@ notification because the battery state or level is an unexpected value", kMBBatteryMonitorUpdateEvent);
    }
}

@end
