//
//  MBNetworkIndicator.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/22/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "Mockingbird-Toolbox.h"

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

//!< Fired when there are no active operations and a new operation starts
extern NSString* const kMBNetworkActivityStartedEvent;       // "MBNetwork:activityStarted"

//!< Fired when there is only one active operation and it completes
extern NSString* const kMBNetworkActivityFinishedEvent;      // "MBNetwork:activityFinished"

//!< Fired when a network operation starts
extern NSString* const kMBNetworkOperationStartedEvent;      // "MBNetwork:operationStarted"

//!< Fired when a network operation completes
extern NSString* const kMBNetworkOperationFinishedEvent;     // "MBNetwork:operationFinished"

/******************************************************************************/
#pragma mark -
#pragma mark MBNetworkIndicator class
/******************************************************************************/

/*!
 This class provides a mechanism that coordinates the use of the network
 activity indicator, so network-based client code can indicate when activity
 is occurring.
 
 Classes wishing to make use of the device's network activity indicator
 should do so by instantiating a new `MBNetworkIndicator` object and sending it
 `operationStarted`, `operationFinished`, and `cancelOperations` messages as
 needed.
 
 The network activity indicator is turned on whenever there is at least one
 `MBNetworkIndicator` instance that has at least one operation in progress.

 When a `MBNetworkIndicator` instance is deallocated, if there are any
 started operations that have not yet finished, the `cancelOperations`
 method is called.
 
 @note      Instances of the `MBNetworkIndicator` class are not thread-safe.
            However, the underlying mechanism for managing the network activity
            indicator is thread-safe.
*/
@interface MBNetworkIndicator : NSObject

/*!
 Indicates that a new network operation has begun.
 */
- (void) operationStarted;

/*!
 Indicates that an in-progress network operation has completed.
 */
- (void) operationFinished;

/*!
 Cancels all in-progress network operations associated with the receiver.
 */
- (void) cancelOperations;

@end
