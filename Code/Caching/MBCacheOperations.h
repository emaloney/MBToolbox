//
//  MBCacheOperations.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/1/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBFilesystemCache.h"
#import "MBFilesystemOperations.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBCacheReadQueue class
/******************************************************************************/

/*!
 A singleton `NSOperationQueue` intended to be used for performing cache
 read operations.

 @warning   You *must not* create instances of this class yourself; this class
            is a singleton. Call the `instance` class method (declared by the
            `MBSingleton` protocol) to acquire the singleton instance.
 */
@interface MBCacheReadQueue : MBOperationQueue <MBSingleton>
@end

/******************************************************************************/
#pragma mark -
#pragma mark MBCacheWriteQueue class
/******************************************************************************/

/*!
 A singleton `NSOperationQueue` intended to be used for performing cache
 write operations.

 @warning   You *must not* create instances of this class yourself; this class
            is a singleton. Call the `instance` class method (declared by the
            `MBSingleton` protocol) to acquire the singleton instance.
 */
@interface MBCacheWriteQueue : MBOperationQueue <MBSingleton>
@end

/******************************************************************************/
#pragma mark -
#pragma mark MBCacheWriteOperation class
/******************************************************************************/

/*!
 An `NSOperation` subclass used by `MBFilesystemCache`s to handle persistence
 for cache objects.

 `MBCacheWriteOperation` instances are typically added to the
 `MBCacheWriteQueue` singleton for performing cache operations such as this.
 */
@interface MBCacheWriteOperation : MBFileWriteOperation

/*----------------------------------------------------------------------------*/
#pragma mark Object lifecycle
/*!    @name Object lifecycle                                                 */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new `MBCacheWriteOperation` instance that can be used to write
 a cache object to a file.

 @param     obj The cache object to be written to a file.
 
 @param     path The filesystem path of the file to be written by the returned
            operation.

 @param     fc The `MBFilesystemCache` responsible for managing the cached
            object `obj`.

 @return    The newly-created `MBFileWriteOperation` instance.
 */
+ (nonnull instancetype) operationForWritingObject:(nonnull id)obj
                                            toFile:(nonnull NSString*)path
                                          forCache:(nonnull MBFilesystemCache*)fc;

/*!
 Initializes the receiver so it can be used to write to the specified file.

 @param     obj The cache object to be written to a file.

 @param     fc The `MBFilesystemCache` responsible for managing the cached
            object `obj`.

 @param     path The filesystem path of the file to be written by the returned
            operation.

 @return    The receiver.
 */
- (nonnull instancetype) initWithObject:(nonnull id)obj
                                inCache:(nonnull MBFilesystemCache*)fc
                            forFilePath:(nonnull NSString*)path;

/*----------------------------------------------------------------------------*/
#pragma mark Getting information about the operation
/*!    @name Getting information about the operation                          */
/*----------------------------------------------------------------------------*/

/*! Returns the cache object to be written to the filesystem by this 
    operation. */
@property(nonnull, nonatomic, readonly) id cacheObject;

/*! Returns the `MBFilesystemCache` instance responsible for managing the
    cache object associated with this operation. */
@property(nonnull, nonatomic, readonly) MBFilesystemCache* cache;

@end
