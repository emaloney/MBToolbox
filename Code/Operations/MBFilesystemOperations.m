//
//  MBFilesystemOperations.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 12/29/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#import "MBFilesystemOperations.h"
#import "NSError+MBToolbox.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark MBFilesystemOperationQueue implementation
/******************************************************************************/

@implementation MBFilesystemOperationQueue
MBImplementSingleton();
@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFileReadOperation implementation
/******************************************************************************/

@implementation MBFileReadOperation
{
    NSString* _filePath;
    NSObject<MBFileReadOperationDelegate>* _delegate;          
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

+ (nonnull instancetype) operationForReadingFromFile:(nonnull NSString*)path
                                            delegate:(nonnull NSObject<MBFileReadOperationDelegate>*)del
{
    return [[self alloc] initForFilePath:path delegate:del];
}

- (nonnull instancetype) initForFilePath:(nonnull NSString*)path
                                delegate:(nonnull NSObject<MBFileReadOperationDelegate>*)del
{
    self = [super init];
    if (self) {
        _filePath = path;
        _delegate = del;
    }
    return self;
}

/******************************************************************************/
#pragma mark Private - Delegate calls
/******************************************************************************/

- (void) _delegateReadCompletedWithObject:(nonnull id)readObj
{
    [_delegate readCompletedWithObject:readObj forOperation:self];
}

- (void) _delegateReadFailedWithError:(nonnull NSError*)err
{
    [_delegate readFailedWithError:err forOperation:self];
}

/******************************************************************************/
#pragma mark Subclass hooks
/******************************************************************************/

- (nullable id) readObjectFromFile:(nonnull NSString*)path error:(inout NSError**)err
{
    MBLogDebugTrace();
    
    NSData* fileData = [NSData dataWithContentsOfFile:path options:NSDataReadingMapped error:err];
    if (fileData) {
        MBLogDebug(@"Successfully read %lu bytes from file: %@", (unsigned long)[fileData length], path);
        [self readCompletedWithObject:fileData];
    }
    return fileData;
}

- (void) readCompletedWithObject:(nonnull id)readObj
{
    MBLogDebugTrace();
    
    if ([_delegate respondsToSelector:@selector(readCompletedWithObject:forOperation:)]) {
        [self performSelectorOnMainThread:@selector(_delegateReadCompletedWithObject:) withObject:readObj waitUntilDone:NO];
    }
}

- (void) readFailedWithError:(nonnull NSError*)err
{
    MBLogDebugTrace();
    
    if ([_delegate respondsToSelector:@selector(readFailedWithError:forOperation:)]) {
        [self performSelectorOnMainThread:@selector(_delegateReadFailedWithError:) withObject:err waitUntilDone:NO];
    }
}

/******************************************************************************/
#pragma mark Operation implementation
/******************************************************************************/

- (void) main
{
    MBLogDebugTrace();
    
    @autoreleasepool {
        @try {
            NSError* err = nil;
            id readObj = [self readObjectFromFile:_filePath error:&err];
            if (readObj) {
                [self readCompletedWithObject:readObj];
            }
            else {
                if (!err) {
                    err = [NSError mockingbirdErrorWithCode:kMBErrorCouldNotLoadFile
                                                userInfoKey:kMBErrorUserInfoKeyFilePath
                                                      value:_filePath];
                }
                MBLogError(@"%@ error while trying to load file at %@: %@", [self class], _filePath, [err localizedDescription]);
                [self readFailedWithError:err];
            }
        }
        @catch (NSException* ex) {
            MBLogError(@"%@ caught %@: %@", [self class], [ex name], [ex reason]);
        }
    }
}

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFileWriteOperation implementation
/******************************************************************************/

@implementation MBFileWriteOperation
{
    NSString* _filePath;
    NSData* _fileData;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

+ (nonnull instancetype) operationForWritingData:(nullable NSData*)data
                                          toFile:(nonnull NSString*)path
{
    return [[self alloc] initWithData:data forFilePath:path];
}

- (nonnull instancetype) initWithData:(nullable NSData*)data
                          forFilePath:(nonnull NSString*)path
{
    self = [super init];
    if (self) {
        _fileData = data;
        _filePath = path;
    }
    return self;
}

- (nonnull instancetype) initForWritingToFile:(nonnull NSString*)path
{
    self = [super init];
    if (self) {
        _filePath = path;
    }
    return self;
}

/******************************************************************************/
#pragma mark Operation implementation
/******************************************************************************/

- (nonnull NSData*) dataForOperation
{
    return _fileData;
}

- (void) main
{
    MBLogDebugTrace();

    @autoreleasepool {
        @try {
            NSError* err = nil;
            NSData* data = [self dataForOperation];
            NSDataWritingOptions options = NSDataWritingAtomic;
#if TARGET_OS_IPHONE
            options |= NSDataWritingFileProtectionNone;
#endif
            if (![data writeToFile:_filePath options:options error:&err]) {
                MBLogError(@"%@ error while trying to write the file at %@: %@", [self class], _filePath, [err localizedDescription]);
            }
            else {
                MBLogDebug(@"Successfully wrote %lu bytes to file: %@", (unsigned long)[data length], _filePath);
            }
        }
        @catch (NSException* ex) {
            MBLogError(@"%@ caught %@: %@", [self class], [ex name], [ex reason]);
        }
    }
}

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFileDeleteOperation class
/******************************************************************************/

@implementation MBFileDeleteOperation
{
    NSFileManager* _fileMgr;
    NSString* _pathToDelete;
    BOOL _pathExists;
    NSString* _filePath;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

+ (nonnull instancetype) operationForDeletingFile:(nonnull NSString*)path
{
    return [[self alloc] initWithFilePath:path moveImmediately:YES];
}

- (nonnull instancetype) initWithFilePath:(nonnull NSString*)path
{
    return [self initWithFilePath:path moveImmediately:YES];
}

- (nonnull instancetype) initWithFilePath:(nonnull NSString*)path
                          moveImmediately:(BOOL)moveNow
{
    self = [super init];
    if (self) {
        _filePath = path;
        _fileMgr = [NSFileManager new];

        _pathExists = [_fileMgr fileExistsAtPath:path];
        if (_pathExists) {
            if (!moveNow) {
                _pathToDelete = path;
            }
            else {
                NSString* guid = [[NSProcessInfo processInfo] globallyUniqueString];
                NSString* tempPath = [NSTemporaryDirectory() stringByAppendingPathComponent:guid];
                
                NSError* err = nil;
                if (![_fileMgr moveItemAtPath:_filePath toPath:tempPath error:&err]) {
                    MBLogError(@"%@ error while trying to move-before-delete the file at %@ to %@: %@", [self class], _filePath, tempPath, [err localizedDescription]);
                    _pathToDelete = path;
                }
                else {
                    _pathToDelete = tempPath;
                }
            }
        }
    }
    return self;
}

/******************************************************************************/
#pragma mark Operation implementation
/******************************************************************************/

- (void) main
{
    MBLogDebugTrace();
    
    if (_pathExists) {
        @autoreleasepool {
            @try {
                NSError* err = nil;
                if (![_fileMgr removeItemAtPath:_pathToDelete error:&err]) {
                    if (_pathToDelete == _filePath) {
                        MBLogError(@"%@ error while trying to delete the file at %@: %@", [self class], _filePath, [err localizedDescription]);
                    } else {
                        MBLogError(@"%@ error while trying to delete the file at %@ (originally at %@): %@", [self class], _pathToDelete, _filePath, [err localizedDescription]);
                    }
                }
                else {
                    MBLogDebug(@"Successfully deleted file: %@", _filePath);
                }
            }
            @catch (NSException* ex) {
                MBLogError(@"%@ caught %@: %@", [self class], [ex name], [ex reason]);
            }
        }
    }
    else {
        MBLogDebug(@"Silently ignoring request to delete nonexistent file at %@", _filePath);
    }
}

@end