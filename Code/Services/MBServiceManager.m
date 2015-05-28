//
//  MBServiceManager.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/14/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBServiceManager.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL         0

/******************************************************************************/
#pragma mark -
#pragma mark MBServiceManager implementation
/******************************************************************************/

@implementation MBServiceManager
{
    NSMutableDictionary* _classNamesToAttachCounts;
}

MBImplementSingleton();

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

- (instancetype) init
{
    self = [super init];
    if (self) {
        _classNamesToAttachCounts = [NSMutableDictionary new];
    }
    return self;
}

/******************************************************************************/
#pragma mark Acquiring service instances
/******************************************************************************/

- (id) serviceForClassName:(NSString*)serviceClassName
{
    Class cls = NSClassFromString(serviceClassName);
    if (!cls) {
        MBLogError(@"Couldn't get Class for Service: %@", serviceClassName);
        return nil;
    }
    return [self serviceForClass:cls];
}

- (id) serviceForClass:(Class)serviceClass
{
    MBLogDebugTrace();
    
    if (![serviceClass respondsToSelector:@selector(instance)]) {
        MBLogError(@"The %@ class must respond to +[%@ instance] to be a valid Service", serviceClass, serviceClass);
        return nil;
    }
    
    if (![serviceClass conformsToProtocol:@protocol(MBService)]) {
        MBLogError(@"The %@ class must implement the Service protocol", serviceClass);
        return nil;
    }
    
    id instance = [serviceClass instance];
    if (!instance) {
        MBLogError(@"The +[%@ instance] method for the Service returned nil", serviceClass);
    }
    
    return instance;
}

/******************************************************************************/
#pragma mark Attaching to services
/******************************************************************************/

- (void) attachToService:(MBService*)service
{
    MBLogDebugTrace();

    if (service) {
        NSString* canonicalServiceName = [[service class] description];
        BOOL shouldStartService = NO;

        @synchronized (self) {
            NSUInteger attachCnt = [_classNamesToAttachCounts[canonicalServiceName] unsignedIntegerValue];
            shouldStartService = (attachCnt == 0);
            _classNamesToAttachCounts[canonicalServiceName] = @(attachCnt + 1);
        }

        if (shouldStartService) {
            [service startService];
        }
    }
}

- (id) attachToServiceClass:(Class)serviceClass
{
    MBService* service = [self serviceForClass:serviceClass];
    if (service) {
        [self attachToService:service];
    }
    return service;
}

- (id) attachToServiceClassNamed:(NSString*)serviceClassName
{
    MBService* service = [self serviceForClassName:serviceClassName];
    if (service) {
        [self attachToService:service];
    }
    return service;
}

/******************************************************************************/
#pragma mark Detaching from services
/******************************************************************************/

- (void) detachFromService:(MBService*)service
{
    MBLogDebugTrace();

    if (service && [service respondsToSelector:@selector(stopService)]) {
        NSString* canonicalServiceName = [[service class] description];
        BOOL shouldStopService = NO;

        @synchronized (self) {
            NSUInteger attachCnt = [_classNamesToAttachCounts[canonicalServiceName] unsignedIntegerValue];
            if (attachCnt > 0) {
                shouldStopService = (attachCnt == 1);
                _classNamesToAttachCounts[canonicalServiceName] = @(attachCnt - 1);
            }
        }

        if (shouldStopService) {
            [service stopService];
        }
    }
}

- (void) detachFromServiceClass:(Class)serviceClass
{
    MBService* service = [self serviceForClass:serviceClass];
    if (service) {
        [self detachFromService:service];
    }
}

- (void) detachFromServiceClassNamed:(NSString*)serviceClassName
{
    MBService* service = [self serviceForClassName:serviceClassName];
    if (service) {
        [self detachFromService:service];
    }
}

/******************************************************************************/
#pragma mark Querying the status of services
/******************************************************************************/

- (BOOL) isServiceRunning:(MBService*)service
{
    return ([self attachCountForService:service] > 0);
}

- (NSUInteger) attachCountForService:(MBService*)service
{
    NSString* canonicalServiceName = [[service class] description];
    NSUInteger attachCnt = 0;
    @synchronized (self) {
        attachCnt = [_classNamesToAttachCounts[canonicalServiceName] unsignedIntegerValue];
    }
    return attachCnt;
}

@end
