//
//  MBFilesystemOperations.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 12/29/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#import "MBSingleton.h"
#import "MBOperationQueue.h"
#import "NSError+MBToolbox.h"

@class MBFileReadOperation;

/******************************************************************************/
#pragma mark -
#pragma mark MBFilesystemOperationQueue class
/******************************************************************************/

/*!
 A singleton `NSOperationQueue` intended to be used for performing general 
 filesystem operations.

 @warning   You *must not* create instances of this class yourself; this class
            is a singleton. Call the `instance` class method (declared by the
            `MBSingleton` protocol) to acquire the singleton instance.
 */
@interface MBFilesystemOperationQueue : MBOperationQueue <MBSingleton>
@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFileReadOperationDelegate protocol
/******************************************************************************/

/*!
 This protocol is adopted by classes that wish to be notified about the
 completion status of `MBFileReadOperation`s.
 
 @note      Delegate methods will always be called on the main thread.
 */
@protocol MBFileReadOperationDelegate

/*!
 Called when an `MBFileReadOperation` completes successfully.

 @param     readObj The object that was read from the filesystem. Typically,
            this is an `NSData` object containing the byte data of the file.
            However, `MBFileReadOperation` subclasses are free to construct any
            type of object. For example, an implementation for an image cache
            may pass `UIImage` instances.

 @param     op The operation that completed.
 */
- (void) readCompletedWithObject:(nonnull id)readObj
                    forOperation:(nonnull MBFileReadOperation*)op;

/*!
 Called when an `MBFileReadOperation` fails.

 @param     err An `NSError` instance describing the error that occurred.

 @param     op The operation that failed.
 */
- (void) readFailedWithError:(nonnull NSError*)err
                forOperation:(nonnull MBFileReadOperation*)op;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFileReadOperation class
/******************************************************************************/

/*!
 An `NSOperation` subclass that can be used to read file data.
 
 `MBFileReadOperation` instances are added to `NSOperationQueue`s to be
 performed, and the `MBFileReadOperationDelegate` associated with the
 operation is notified on the main thread when the operation completes
 successfully or fails.
 
 The `MBFilesystemOperationQueue` singleton is available as a convenience
 for performing filesystem operations such as this.
 */
@interface MBFileReadOperation : NSOperation

/*----------------------------------------------------------------------------*/
#pragma mark Object lifecycle
/*!    @name Object lifecycle                                                 */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new `MBFileReadOperation` instance that can be used to read the
 contents of the file specified.
 
 @param     path The filesystem path of the file to be read by the returned
            operation.
 
 @param     delegate The delegate that will be notified upon completion of
            the returned operation.
 
 @return    The newly-created `MBFileReadOperation` instance.
 */
+ (nonnull instancetype) operationForReadingFromFile:(nonnull NSString*)path
                                            delegate:(nonnull NSObject<MBFileReadOperationDelegate>*)delegate;

/*!
 Initializes the receiver so it can be used to read from the specified file.

 @param     path The filesystem path of the file to be read by the receiver.

 @param     delegate The delegate that will be notified upon completion of
            the operation.
 
 @return    The receiver.
 */
- (nonnull instancetype) initForFilePath:(nonnull NSString*)path
                                delegate:(nonnull NSObject<MBFileReadOperationDelegate>*)delegate;

/*----------------------------------------------------------------------------*/
#pragma mark Getting information about the operation
/*!    @name Getting information about the operation                          */
/*----------------------------------------------------------------------------*/

/*! Returns the filesystem path of the file to be read by the operation. */
@property(nonnull, nonatomic, readonly) NSString* filePath;

/*! Returns the `MBFileReadOperationDelegate` that will be notified when the
    operation completes. */
@property(nonnull, nonatomic, readonly) NSObject<MBFileReadOperationDelegate>* delegate;

/*----------------------------------------------------------------------------*/
#pragma mark Subclassing hooks
/*!    @name Subclassing hooks                                                */
/*----------------------------------------------------------------------------*/

/*!
 Called internally to read the file and convert its data into an object.
 
 The default implementation returns an `NSData` instance. Subclasses may
 override this method to return other types of objects.
 
 @param     path The filesystem path of the file to read.

 @param     errPtr If this method returns `nil` and this parameter is
            non-`nil`, `*errPtr` will be updated to point to an `NSError`
            instance containing further information about the error.
 
 @return    The object that was read from the file.
 */
- (nullable id) readObjectFromFile:(nonnull NSString*)path error:(NSErrorPtrPtr)errPtr;

/*!
 Called internally when `readObjectFromFile:error:` completes successfully.

 @warning   Subclasses may override this method to perform additional work when
            the operation completes, but *must* call `super` to ensure that
            the operation's delegate is notified.
 
 @param     readObj The object that was read from the filesystem, as returned
            by `readObjectFromFile:error:`.
 */
- (void) readCompletedWithObject:(nonnull id)readObj;

/*!
 Called internally when `readObjectFromFile:error:` fails.

 @warning   Subclasses may override this method to perform additional work when
            the operation completes, but *must* call `super` to ensure that
            the operation's delegate is notified.
 
 @param     err The error describing the reason that `readObjectFromFile:error:`
            failed.
 */
- (void) readFailedWithError:(nonnull NSError*)err;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFileWriteOperation class
/******************************************************************************/

/*!
 An `NSOperation` subclass that can be used to write data to a file.
 
 `MBFileWriteOperation` instances are added to `NSOperationQueue`s to be
 performed.
 
 The `MBFilesystemOperationQueue` singleton is available as a convenience
 for performing filesystem operations such as this.
 
 @note      This operation does not provide a mechanism to be notified of its
            success or failure.
 */
@interface MBFileWriteOperation : NSOperation

/*----------------------------------------------------------------------------*/
#pragma mark Object lifecycle
/*!    @name Object lifecycle                                                 */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new `MBFileWriteOperation` instance that can be used to write
 data to a file.

 @param     data The data to be written to the file. Passing `nil` is
            permissible for subclasses override the `dataForOperation` method.

 @param     path The filesystem path of the file to be written by the returned
            operation.

 @return    The newly-created `MBFileWriteOperation` instance.
 */
+ (nonnull instancetype) operationForWritingData:(nullable NSData*)data
                                          toFile:(nonnull NSString*)path;

/*!
 Initializes the receiver so it can be used to write to the specified file.

 @param     data The data to be written to the file. Passing `nil` is
            permissible for subclasses override the `dataForOperation` method.

 @param     path The filesystem path of the file to be written.

 @return    The receiver.
 */
- (nonnull instancetype) initWithData:(nullable NSData*)data forFilePath:(nonnull NSString*)path;

/*----------------------------------------------------------------------------*/
#pragma mark Getting information about the operation
/*!    @name Getting information about the operation                          */
/*----------------------------------------------------------------------------*/

/*! Returns the filesystem path of the file to be written by the operation. */
@property(nonnull, nonatomic, readonly) NSString* filePath;

/*! Returns the data that will be written to the file by the operation. */
@property(nonnull, nonatomic, readonly) NSData* fileData;

/*----------------------------------------------------------------------------*/
#pragma mark Subclassing hooks
/*!    @name Subclassing hooks                                                */
/*----------------------------------------------------------------------------*/

/*!
 Returns the data that will be written to the file.
 
 The default implementation returns the `NSData` instance used when the
 receiver was initialized. Subclasses may override this to provide an
 alternate mechanism for supplying the data to be written.
 
 @return    The data to write to the file.
 */
- (nonnull NSData*) dataForOperation;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFileDeleteOperation class
/******************************************************************************/

/*!
 An `NSOperation` subclass that can be used to delete a file from the
 filesystem.
 
 `MBFileDeleteOperation` instances are added to `NSOperationQueue`s to be
 performed.
 
 The `MBFilesystemOperationQueue` singleton is available as a convenience
 for performing filesystem operations such as this.
 
 @note      This operation does not provide a mechanism to be notified of its
            success or failure.
 */
@interface MBFileDeleteOperation : NSOperation

/*----------------------------------------------------------------------------*/
#pragma mark Object lifecycle
/*!    @name Object lifecycle                                                 */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new `MBFileDeleteOperation` instance that can be used to delete a
 file from the filesystem.

 @note      The file at the specified path will be moved out-of-place
            immediately on the calling thread, but the deletion won't occur
            until the operation is executed by the `NSOperationQueue` to which
            it was added.

 @param     path The filesystem path of the file to be deleted by the returned
            operation.

 @return    The newly-created `MBFileDeleteOperation` instance.
 */
+ (nonnull instancetype) operationForDeletingFile:(nonnull NSString*)path;

/*!
 Initializes the receiver so it can be used to delete the specified file.

 @note      The file at the specified path will be moved out-of-place
            immediately on the calling thread, but the deletion won't occur
            until the operation is executed by the `NSOperationQueue` to which
            it was added.

 @param     path The filesystem path of the file to be deleted.

 @return    The receiver.
 */
- (nonnull instancetype) initWithFilePath:(nonnull NSString*)path;

/*!
 Initializes the receiver so it can be used to delete the specified file.

 @param     path The filesystem path of the file to be deleted.
 
 @param     moveNow If `YES`, the file at the specified path will be moved
            out-of-place immediately on the calling thread. Regardless of the
            value of this parameter, the actual file deletion won't occur
            until the operation is executed by the `NSOperationQueue` to which
            it was added.

 @return    The receiver.
 */
- (nonnull instancetype) initWithFilePath:(nonnull NSString*)path moveImmediately:(BOOL)moveNow;

/*----------------------------------------------------------------------------*/
#pragma mark Getting information about the operation
/*!    @name Getting information about the operation                          */
/*----------------------------------------------------------------------------*/

/*! Returns the filesystem path of the file to be deleted by the operation. */
@property(nonnull, nonatomic, readonly) NSString* filePath;

@end
