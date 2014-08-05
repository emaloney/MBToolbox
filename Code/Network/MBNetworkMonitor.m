//
//  MBNetworkMonitor.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/23/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import <SystemConfiguration/SystemConfiguration.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <CoreTelephony/CTCarrier.h>
#import <netinet/in.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <netinet6/in6.h>
#import <arpa/inet.h>
#import <ifaddrs.h>
#import <netdb.h>

#import "MBNetworkMonitor.h"
#import "MBServiceManager.h"
#import "MBEvents.h"

#define DEBUG_LOCAL		0

/******************************************************************************/
#pragma mark Constants - Public
/******************************************************************************/

NSString* const kMBNetworkDidGoOnlineEvent                  = @"MBNetwork:didGoOnline";
NSString* const kMBNetworkDidGoOfflineEvent                 = @"MBNetwork:didGoOffline";
NSString* const kMBNetworkWifiConnectedEvent                = @"MBNetwork:wifiConnected";
NSString* const kMBNetworkWifiDisconnectedEvent             = @"MBNetwork:wifiDisconnected";
NSString* const kMBNetworkCarrierConnectionChangedEvent     = @"MBNetwork:carrierConnectionChanged";

NSString* const kMBNetworkNoCarrierStatusDescription        = @"no carrier";

/******************************************************************************/
#pragma mark Constants - private
/******************************************************************************/

NSString* const kMBNetworkRadioAccessTechnologyPrefix       = @"CTRadioAccessTechnology";

/******************************************************************************/
#pragma mark -
#pragma mark MBNetworkMonitor implementation
/******************************************************************************/

@implementation MBNetworkMonitor
{
    SCNetworkReachabilityRef _networkReach;
    CTTelephonyNetworkInfo* _carrierNetworkInfo;
    BOOL _wasOnline;
    BOOL _wasOnWifi;
}

MBImplementSingleton();

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

- (id) init
{
    self = [super init];
    if (self) {
        struct sockaddr_in zeroAddress;
        bzero(&zeroAddress, sizeof(zeroAddress));
        zeroAddress.sin_len = sizeof(zeroAddress);
        zeroAddress.sin_family = AF_INET;
        _networkReach = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr*)&zeroAddress);
        if (!_networkReach) {
            errorLog(@"%@ failed to create SCNetworkReachabilityRef", [self class]);
        }

        _carrierNetworkInfo = [CTTelephonyNetworkInfo new];

        debugLog(@"Current carrier info: %@", self.carrierStatusDescription);
    }
    return (self);
}

- (void) dealloc
{
    SCNetworkReachabilityUnscheduleFromRunLoop(_networkReach, CFRunLoopGetMain(), kCFRunLoopDefaultMode);

    CFRelease(_networkReach);

    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

/******************************************************************************/
#pragma mark Handling network & carrier changes
/******************************************************************************/

static void NetworkMonitorReachabilityCallback(SCNetworkReachabilityRef target, SCNetworkReachabilityFlags flags, void* info)
{
    [[MBNetworkMonitor instance] _processNetworkReachabilityFlags:flags];
}

- (MBNetworkAvailabilityFlags) _networkAvailabilityForReachabilityFlags:(SCNetworkReachabilityFlags)flags
{
    // assume we're offline until proven otherwise
    MBNetworkAvailabilityFlags retVal = MBNetworkAvailabilityOffline;
    
    if (flags & kSCNetworkReachabilityFlagsReachable) {
        retVal |= MBNetworkAvailabilityOnline;
        if (flags & kSCNetworkReachabilityFlagsIsWWAN) {
            retVal |= MBNetworkAvailabilityViaCarrier;
        }
        else {
            retVal |= MBNetworkAvailabilityViaWifi;
        }
    }
    
    return retVal;
}

- (void) _processNetworkReachabilityFlags:(SCNetworkReachabilityFlags)flags
{
    MBNetworkAvailabilityFlags availability = [self _networkAvailabilityForReachabilityFlags:flags];
    [self _processNetworkAvailability:availability];
}

- (void) _processNetworkAvailability:(MBNetworkAvailabilityFlags)flags
{
    [self _networkIsNow:(flags & MBNetworkAvailabilityOnline) != 0];
    [self _wifiIsNow:(flags & MBNetworkAvailabilityViaWifi) != 0];
}

- (void) _networkIsNow:(BOOL)available
{
    debugLog(@"Network status is now %s", (available ? "ONLINE" : "OFFLINE"));

    if (_wasOnline != available) {
        _wasOnline = available;
        [MBEvents postEvent:(available ? kMBNetworkDidGoOnlineEvent : kMBNetworkDidGoOfflineEvent)
                           fromSender:self];
    }
}

- (void) _wifiIsNow:(BOOL)available
{
    debugLog(@"Wifi status is now %s", (available ? "CONNECTED" : "DISCONNECTED"));

    if (_wasOnWifi != available) {
        _wasOnWifi = available;
        [MBEvents postEvent:(available ? kMBNetworkWifiConnectedEvent : kMBNetworkWifiDisconnectedEvent)
                           fromSender:self];
    }
}

- (void) _carrierRadioChanged
{
    debugLog(@"Carrier info changed to: %@", self.carrierStatusDescription);

    [MBEvents postEvent:kMBNetworkCarrierConnectionChangedEvent fromSender:self];
}

/******************************************************************************/
#pragma mark Property handling
/******************************************************************************/

- (BOOL) isOnline
{
    if ([self _serviceIsRunning]) {
        return _wasOnline;
    }
    else {
        return ((self.networkAvailability & MBNetworkAvailabilityOnline) != 0);
    }
}

- (BOOL) isWifiConnected
{
    if ([self _serviceIsRunning]) {
        return _wasOnWifi;
    }
    else {
        return ((self.networkAvailability & MBNetworkAvailabilityViaWifi) != 0);
    }
}

- (BOOL) hasCellularCarrier
{
    return _carrierNetworkInfo.subscriberCellularProvider != nil;
}

- (NSString*) cellularCarrierName
{
    return _carrierNetworkInfo.subscriberCellularProvider.carrierName;
}

- (NSString*) cellularCarrierCountry
{
    return _carrierNetworkInfo.subscriberCellularProvider.isoCountryCode;
}

- (NSString*) cellularConnectionType
{
    NSString* radioType = _carrierNetworkInfo.currentRadioAccessTechnology;
    if ([radioType hasPrefix:kMBNetworkRadioAccessTechnologyPrefix]) {
        return [radioType substringFromIndex:kMBNetworkRadioAccessTechnologyPrefix.length];
    }
    return nil;
}

- (NSString*) carrierStatusDescription
{
    if (self.hasCellularCarrier) {
        NSString* connectionType = self.cellularConnectionType;
        NSString* carrierCountry = self.cellularCarrierCountry;
        if (carrierCountry && carrierCountry.length) {
            carrierCountry = [NSString stringWithFormat:@" (%@)", carrierCountry];
        } else {
            carrierCountry = @"";
        }
        if (connectionType) {
            return [NSString stringWithFormat:@"%@ %@%@", self.cellularCarrierName, connectionType, carrierCountry];
        }
        else {
            return [NSString stringWithFormat:@"%@%@", self.cellularCarrierName, carrierCountry];
        }
    }
    return kMBNetworkNoCarrierStatusDescription;
}

- (MBNetworkAvailabilityFlags) networkAvailability
{
    SCNetworkReachabilityFlags flags = 0;
	if (SCNetworkReachabilityGetFlags(_networkReach, &flags)) {
        return [self _networkAvailabilityForReachabilityFlags:flags];
    }
    else {
        errorLog(@"%@ couldn't determine current network availability", [self class]);
        return MBNetworkAvailabilityOffline;
    }
}

- (NSString*) networkAvailabilityDescription
{
    MBNetworkAvailabilityFlags flags = self.networkAvailability;
    if (flags == MBNetworkAvailabilityOffline) {
        return @"offline";
    }
    if (flags & MBNetworkAvailabilityOnline) {
        if (flags & MBNetworkAvailabilityViaWifi) {
            return @"online via WiFi";
        }
        if (flags & MBNetworkAvailabilityViaCarrier) {
            return @"online via cellular carrier";
        }
    }
    return @"unknown";
}

- (NSString*) reachabilityFlagsDescription
{
    SCNetworkReachabilityFlags flags = 0;
	if (SCNetworkReachabilityGetFlags(_networkReach, &flags)) {
        NSMutableString* flagStr = [NSMutableString new];
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsTransientConnection)  ? 'T' : '-')];     // T = Transient connection
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsReachable)            ? 'U' : '-')];     // U = network is Up
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsConnectionRequired)   ? 'Q' : '-')];     // Q = connection reQuired
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsConnectionOnTraffic)  ? 'A' : '-')];     // A = will make automatic connection on traffic
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsInterventionRequired) ? 'I' : '-')];     // I = intervention required
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsConnectionOnDemand)   ? 'O' : '-')];     // O = On demand
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsIsLocalAddress)       ? 'L' : '-')];     // L = is local address
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsIsDirect)             ? 'D' : '-')];     // D = direct connection
        [flagStr appendFormat:@"%C", (unichar)((flags & kSCNetworkReachabilityFlagsIsWWAN)               ? 'C' : '-')];     // C = carrier cell network
        return flagStr;
    }
    return nil;
}

/******************************************************************************/
#pragma mark Service API
/******************************************************************************/

- (BOOL) _serviceIsRunning
{
    return [[MBServiceManager instance] isServiceRunning:self];
}

- (void) startService
{
    debugTrace();
    
    // listen to network reachability changes
    if (SCNetworkReachabilitySetCallback(_networkReach, NetworkMonitorReachabilityCallback, nil)) {
        if (!SCNetworkReachabilityScheduleWithRunLoop(_networkReach, CFRunLoopGetMain(), kCFRunLoopDefaultMode)) {
            errorLog(@"%@ failed to schedule reachability callbacks", [self class]);
        }
        [self _processNetworkAvailability:self.networkAvailability];
    }
    else {
        errorLog(@"%@ failed to set reachability callback", [self class]);
    }

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(_carrierRadioChanged) name:CTRadioAccessTechnologyDidChangeNotification object:nil];
}

- (void) stopService
{
    debugTrace();

    // stop listening for network reachability changes
    SCNetworkReachabilityUnscheduleFromRunLoop(_networkReach, CFRunLoopGetMain(), kCFRunLoopDefaultMode);

    // stop listening for carrier radio status changes
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
