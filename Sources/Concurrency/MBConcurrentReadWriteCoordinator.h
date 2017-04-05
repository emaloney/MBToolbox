//
//  MBConcurrentReadWriteCoordinator.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 1/13/15.
//  Copyright (c) 2015 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

/******************************************************************************/
#pragma mark -
#pragma mark MBConcurrentReadWriteCoordinator class
/******************************************************************************/

/*!
 The `MBConcurrentReadWriteCoordinator` uses Grand Central Dispatch to provide
 an efficient mechanism for enforcing orderly read/write access to a shared
 resource.

 The coordinator ensures that concurrent access to the shared resource
 follows these rules:

 * A *read operation* never executes at the same time as a *write operation*

 * Multiple *read operations* may execute simultaneously

 * Only one *write operation* may be executing at any given time

 * *Read operations* occur synchronously

 * *Write operations* occur asynchronously

 Because of the underlying GCD mechanism used, when used properly, the
 implementation ensures serial order with respect to reads and writes.
 That is, a call to perform a read operation will always return the results
 of the most-recently enqueued write operation.
 */
@interface MBConcurrentReadWriteCoordinator : NSObject

/*!
 Synchronously executes the read operation contained in the passed-in block.
 If a writer is executing when this method is called, the calling thread will
 be blocked until writing finishes. Multiple readers may execute simultaneously.

 @param     readOperation The read operation.
 */
- (void) read:(nonnull void (^)())readOperation;

/*!
 Enqueues a write operation for eventual execution. The passed-in block will be
 executed only when there are no other readers or writers.

 Any calls to the receiver's `read:` method that are issued after a call
 to `enqueueWrite:` are guaranteed to execute after its `writeOperation`
 block finishes executing. This ensures that reads and writes can occur in
 a predictable order.

 @param     writeOperation The write operation.
 */
- (void) enqueueWrite:(nonnull void (^)())writeOperation;

@end

