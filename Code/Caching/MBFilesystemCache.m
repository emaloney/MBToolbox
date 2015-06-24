//
//  MBFilesystemCache.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 1/28/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBAvailability.h"

#if MB_BUILD_IOS
#import <UIKit/UIKit.h>
#endif

#import "MBFilesystemCache.h"
#import "MBCacheOperations.h"
#import "NSString+MBMessageDigest.h"
#import "MBThreadsafeCache+Subclassing.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

const NSTimeInterval kMBFilesystemCacheDefaultMaxAge    = 129600;       // 36 hours

#define kFilesystemCacheStorageVersion                  0
#define kFilesystemCacheBaseExtension                   @"cache"

#define kCacheDelegateSelectorObjectFromCacheData       @selector(objectFromCacheData:)
#define kCacheDelegateSelectorCacheDataFromObject       @selector(cacheDataFromObject:)
#define kCacheDelegateSelectorShouldStoreInMemory       @selector(shouldStoreObject:forKey:inMemoryCache:)
#define kCacheDelegateSelectorShouldStoreInFilesystem   @selector(shouldStoreObject:forKey:inFilesystemCache:)

/******************************************************************************/
#pragma mark -
#pragma mark MBCachePruneOperation interface
/******************************************************************************/

@interface MBCachePruneOperation : NSOperation
#if MB_BUILD_IOS
{
    UIBackgroundTaskIdentifier _taskID;
}
#endif

@property(nonnull, nonatomic, strong) NSString* cacheDir;
@property(nonatomic, assign) NSTimeInterval maxAge;

+ (nonnull MBCachePruneOperation*) operationForCacheDirectory:(nonnull NSString*)cacheDir
                                                       maxAge:(NSTimeInterval)ageInSeconds;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFilesystemCache class
/******************************************************************************/

@implementation MBFilesystemCache
{
    NSFileManager* _fm;
    NSString* _cacheDir;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

- (instancetype) initWithName:(NSString*)name cacheDelegate:(id)delegate
{
    self = [super init];
    if (self) {
        _cacheName = name;
        _fm = [NSFileManager new];
        _cacheDir = [self _directoryPathForCacheNamed:name];
        MBLogDebug(@"%@ named %@ will use directory: %@", [self class], name, _cacheDir);
        _cacheDelegate = delegate;
        
        _maxAgeOfCacheFiles = kMBFilesystemCacheDefaultMaxAge;
        
        _readQueue = [MBCacheReadQueue instance];
        _writeQueue = [MBCacheWriteQueue instance];
    }
    return self;
}

- (instancetype) initWithName:(NSString*)name
{
    return [self initWithName:name cacheDelegate:self];
}

/******************************************************************************/
#pragma mark Memory management
/******************************************************************************/

#if MB_BUILD_IOS
- (void) memoryWarning
{
	MBLogDebugTrace();
	
    // freeing up pending cache writes
    // will help us release more memory
    [_writeQueue cancelAllOperations];
    
	[super memoryWarning];
}
#endif

/******************************************************************************/
#pragma mark MBFilesystemCacheDelegate implementation
/******************************************************************************/
 
- (nonnull NSString*) filenameForCacheKey:(nonnull id)key
{
    NSString* md5 = [[key description] MD5];
    return [NSString stringWithFormat:@"%@.%@", md5, [self fileExtensionForCacheKey:key]];
}

/******************************************************************************/
#pragma mark File handling
/******************************************************************************/

- (NSFileManager*) fileManager
{
    return _fm;
}

- (NSString*) _directoryPathForCacheNamed:(NSString*)name
{
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString* cacheDirPath = [paths firstObject];
    cacheDirPath = [cacheDirPath stringByAppendingPathComponent:name];
    return cacheDirPath;
}

- (void) ensureCacheDirectory
{
    NSError* err = nil;
    if (![_fm createDirectoryAtPath:_cacheDir
        withIntermediateDirectories:YES
                         attributes:nil
                              error:&err])
    {
        MBLogError(@"%@ error while trying to create cache directory at %@: %@", [self class], _cacheDir, [err localizedDescription]);
    }
}

- (NSString*) _pathForCacheFilename:(NSString*)cacheFile
{
    return [_cacheDir stringByAppendingPathComponent:cacheFile];
}

- (NSString*) fileExtensionForCacheKey:(id)key
{
    return [NSString stringWithFormat:@"%@%u", kFilesystemCacheBaseExtension, kFilesystemCacheStorageVersion];
}

- (NSString*) filePathForCacheKey:(id)key
{
    NSString* filename = [_cacheDelegate filenameForCacheKey:key];
    return [self _pathForCacheFilename:filename];
}

- (id) objectFromCacheFile:(NSString*)path
{
    MBLogDebugTrace();
    
    NSError* err = nil;
    NSData* fileData = [NSData dataWithContentsOfFile:path options:NSDataReadingMapped error:&err];
    if (!fileData) {
        MBLogError(@"%@ error while trying to load the cache file at %@: %@", [self class], path, [err localizedDescription]);
        return nil;
    }
    
    // we got our file data; use it to reconstitute our object
    return [self objectFromCacheData:fileData];
}

/******************************************************************************/
#pragma mark Delegate hooks
/******************************************************************************/

- (BOOL) shouldStoreObjectInMemoryCache:(id)cacheObj forKey:(id)key
{
    if (cacheObj) {
        if ([_cacheDelegate respondsToSelector:kCacheDelegateSelectorShouldStoreInMemory]) {
            return [_cacheDelegate shouldStoreObject:cacheObj forKey:key inMemoryCache:self];
        }
        return YES;
    }
    return NO;
}

- (BOOL) shouldStoreObjectInFilesystemCache:(id)cacheObj forKey:(id)key
{
    if (cacheObj) {
        if ([_cacheDelegate respondsToSelector:kCacheDelegateSelectorShouldStoreInFilesystem]) {
            return [_cacheDelegate shouldStoreObject:cacheObj forKey:key inFilesystemCache:self];
        }
        return YES;
    }
    return NO;
}

- (void) storeObjectInMemoryCacheIfAppropriate:(id)cacheObj forKey:(id)key
{
    if ([self shouldStoreObjectInMemoryCache:cacheObj forKey:key]) {
        [self objectLoaded:cacheObj forKey:key];
    }
}

- (void) storeObjectInFilesystemCacheIfAppropriate:(id)cacheObj forKey:(id)key
{
    if ([self shouldStoreObjectInFilesystemCache:cacheObj forKey:key]) {
        // make sure we have a valid cache directory
        [self ensureCacheDirectory];
        
        NSString* cacheFile = [_cacheDelegate filenameForCacheKey:key];
        NSString* path = [self _pathForCacheFilename:cacheFile];

        MBCacheWriteOperation* op = [MBCacheWriteOperation operationForWritingObject:cacheObj
                                                                          toFile:path
                                                                        forCache:self];
        
        [_writeQueue addOperation:op];
    }
}

/******************************************************************************/
#pragma mark Primitive methods for subclass use
/******************************************************************************/

- (BOOL) internalIsKeyInCache:(id)key
{
    NSString* cacheFile = [_cacheDelegate filenameForCacheKey:key];
    return [super internalIsKeyInCache:cacheFile];
}

- (id) internalObjectForKey:(id)key
{
    NSString* cacheFile = [_cacheDelegate filenameForCacheKey:key];

    id obj = [super internalObjectForKey:cacheFile];
    if (obj) {
        // fetched from memory cache
        return obj;
    }
    
    // not in memory cache; try to load from filesystem
    NSString* path = [self _pathForCacheFilename:cacheFile];
    id cacheObj = [self objectFromCacheFile:path];
    if (cacheObj) {
        [self storeObjectInMemoryCacheIfAppropriate:cacheObj forKey:key];
    }
    return cacheObj;
}

- (void) internalSetObject:(id)obj forKey:(id)key
{
    [self storeObjectInMemoryCacheIfAppropriate:obj forKey:key];

    [self storeObjectInFilesystemCacheIfAppropriate:obj forKey:key];
}

- (void) internalRemoveObjectForKey:(id)key
{
    NSString* cacheFile = [_cacheDelegate filenameForCacheKey:key];

    // remove from memory cache
    [super internalRemoveObjectForKey:cacheFile];
    
    // if the cache entry has an associated file...
    NSString* path = [self _pathForCacheFilename:cacheFile];
    if ([_fm isReadableFileAtPath:path]) {
        // ...then remove the file
        MBFileDeleteOperation* op = [MBFileDeleteOperation operationForDeletingFile:path];

        [[MBFilesystemOperationQueue instance] addOperation:op];
    }
}

- (void) objectLoaded:(id)cacheObj forKey:(id)key
{
    MBLogDebugTrace();

    NSString* cacheFile = [_cacheDelegate filenameForCacheKey:key];

    if (cacheFile) {
        [self lock];
        [self internalCache][cacheFile] = cacheObj;
        [self unlock];
    }
    else {
        MBLogError(@"%@ couldn't create cache filename for key: %@", [self class], key);
    }
}

/******************************************************************************/
#pragma mark Converting cache objects to/from NSData
/******************************************************************************/

- (nullable NSData*) cacheDataFromObject:(nonnull id)cacheObj
{
    NSData* cacheData = nil;
    if ([_cacheDelegate respondsToSelector:kCacheDelegateSelectorCacheDataFromObject]) {
        cacheData = [_cacheDelegate cacheDataFromObject:cacheObj];
    }
    else {
        if ([cacheObj isKindOfClass:[NSData class]]) {
            cacheData = (NSData*) cacheObj;
        }
    }
    return cacheData;
}

- (nullable id) objectFromCacheData:(nonnull NSData*)cacheData
{
    if ([_cacheDelegate respondsToSelector:kCacheDelegateSelectorObjectFromCacheData]) {
        return [_cacheDelegate objectFromCacheData:cacheData];
    }
    return cacheData;
}

/******************************************************************************/
#pragma mark Public API - Clearing cache
/******************************************************************************/

- (void) clearFilesystemCache
{
    MBLogDebugTrace();
    
    MBFileDeleteOperation* op = [MBFileDeleteOperation operationForDeletingFile:_cacheDir];
    
    [[MBFilesystemOperationQueue instance] addOperation:op];
}

- (void) purgeCacheFilesOlderThan:(NSTimeInterval)ageInSeconds
{
    MBLogDebugTrace();

    MBCachePruneOperation* op = [MBCachePruneOperation operationForCacheDirectory:_cacheDir
                                                                           maxAge:ageInSeconds];

    [[MBFilesystemOperationQueue instance] addOperation:op];
}

- (void) purgeOutOfDateCacheFiles
{
    [self purgeCacheFilesOlderThan:_maxAgeOfCacheFiles];
}

/******************************************************************************/
#pragma mark Public API - Querying cache contents
/******************************************************************************/

- (BOOL) isKeyInCache:(id)key
{
    MBLogDebugTrace();

    NSString* cacheFile = [_cacheDelegate filenameForCacheKey:key];
    if ([super isKeyInCache:cacheFile]) {
        return YES;
    }
    
    NSString* path = [self _pathForCacheFilename:cacheFile];
    return [_fm isReadableFileAtPath:path];
}

- (BOOL) isKeyInFilesystemCache:(id)key
{
    MBLogDebugTrace();
    
    // first, check to see if there's a file
    NSString* cacheFile = [_cacheDelegate filenameForCacheKey:key];
    NSString* path = [self _pathForCacheFilename:cacheFile];
    if (![_fm isReadableFileAtPath:path]) {
        return NO;
    }
    
    // there is a file, make sure it's recent enough
    NSError* err = nil;
    NSDictionary* fileAttr = [_fm attributesOfItemAtPath:path error:&err];
    if (!fileAttr) {
        MBLogError(@"%@ error while trying to determine attributes of cache file at %@: %@", [self class], path, [err localizedDescription]);
        return NO;  // couldn't get attributes; act as though file doesn't exist
    }
    else {
        NSDate* modDate = [fileAttr fileModificationDate];
        if (modDate) {
            MBLogDebug(@"Mod date of file %@: %@", path, modDate);
            
            NSTimeInterval now = [NSDate timeIntervalSinceReferenceDate];
            NSTimeInterval fileWrittenAt = [modDate timeIntervalSinceReferenceDate];
            if ((fileWrittenAt + _maxAgeOfCacheFiles) > now) {
                MBLogDebug(@"Cache file %@ is recent enough to use", path);
                return YES; // we have a file, and it is recent enough to use
            }
            else {
                MBLogDebug(@"Cache file %@ is TOO OLD to use (it is %g seconds old)", path, (now - fileWrittenAt));
                return NO;  // file too old; pretend it doesn't exist
            }
        }
        else {
            MBLogError(@"%@ couldn't determine modification date of file: %@", [self class], path);
            return NO;  // coudn't determine mod date; pretend file doesn't exist
        }
    }
}

- (BOOL) isKeyInMemoryCache:(id)key
{
    MBLogDebugTrace();
    
    return [super isKeyInCache:key];
}

/******************************************************************************/
#pragma mark Public API - Accessing cache contents
/******************************************************************************/

- (id) objectForKeyInMemoryCache:(id)key
{
    MBLogDebugTrace();
    
    [self lock];
    id obj = [self internalCache][key];
    [self unlock];
    return obj;
}

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBCachePruneOperation class
/******************************************************************************/

@implementation MBCachePruneOperation

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

+ (MBCachePruneOperation*) operationForCacheDirectory:(NSString*)cacheDir
                                             maxAge:(NSTimeInterval)ageInSeconds
{
    MBCachePruneOperation* cpo = [self new];
    cpo.cacheDir = cacheDir;
    cpo.maxAge = ageInSeconds;
    return cpo;
}

- (instancetype) init
{
    self = [super init];
#if MB_BUILD_IOS
    if (self) {
        _taskID = UIBackgroundTaskInvalid;
    }
#endif
    return self;
}

/******************************************************************************/
#pragma mark Operation implementation
/******************************************************************************/

- (void) main
{
    MBLogDebugTrace();
    
    @autoreleasepool {
        @try {
#if MB_BUILD_IOS
            UIApplication* app = [UIApplication sharedApplication];
            _taskID = [app beginBackgroundTaskWithExpirationHandler:^{
                [app endBackgroundTask:_taskID];
                _taskID = UIBackgroundTaskInvalid;
            }];
#endif

            NSFileManager* fileMgr = [NSFileManager new];
            dispatch_queue_t q = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
            dispatch_async(q, ^{
                NSError* err = nil;
                NSArray* files = [fileMgr contentsOfDirectoryAtPath:_cacheDir error:&err];
                if (err) {
                    MBLogError(@"Error enumerating directory at path <%@>: %@ ", _cacheDir, err);
                    return;
                }
                
                NSTimeInterval now = [NSDate timeIntervalSinceReferenceDate];
                
                NSUInteger i=0;
                NSUInteger fileCnt = files.count;
#if MB_BUILD_IOS
                while (i < fileCnt && _taskID != UIBackgroundTaskInvalid) {
#else
                while (i < fileCnt) {
#endif
                    NSString* path = [_cacheDir stringByAppendingPathComponent:files[i]];
                    
                    NSDictionary* fileAttr = [fileMgr attributesOfItemAtPath:path error:&err];
                    if (err) {
                        MBLogError(@"%@ error while trying to determine attributes of cache file at %@: %@", [self class], path, [err localizedDescription]);
                    }
                    else {
                        NSDate* modDate = [fileAttr fileModificationDate];
                        if (modDate) {
                            MBLogDebug(@"Mod date of file %@: %@", path, modDate);
                            
                            NSTimeInterval fileWrittenAt = [modDate timeIntervalSinceReferenceDate];
                            if ((fileWrittenAt + _maxAge) > now) {
                                MBLogDebug(@"Cache file %@ is recent enough to keep", path);
                            }
                            else {
                                MBLogDebug(@"Cache file %@ is TOO OLD to keep (it is %g seconds old); deleting", path, (now - fileWrittenAt));
                                
                                [fileMgr removeItemAtPath:path error:&err];
                                if (err) {
                                    MBLogError(@"%@ error while deleting obsolete cache file at %@: %@", [self class], path, [err localizedDescription]);
                                }
                            }
                        }
                        else {
                            MBLogError(@"%@ couldn't determine modification date of file: %@", [self class], path);
                        }
                    }
                    
                    i++;
                }
                
#if MB_BUILD_IOS
                if (_taskID != UIBackgroundTaskInvalid) {
                    [app endBackgroundTask:_taskID];
                }
#endif
            });
        }
        @catch (NSException* ex) {
            MBLogError(@"%@ caught %@: %@", [self class], [ex name], [ex reason]);
        }
    }
}


@end

