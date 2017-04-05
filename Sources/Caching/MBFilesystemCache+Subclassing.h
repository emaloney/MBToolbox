//
//  MBFilesystemCache+Subclassing.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/7/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBFilesystemCache.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBFilesystemCache class
/******************************************************************************/

/*!
 The class extensions in this header file are intended for internal use only by
 `MBFilesystemCache` implementations.

 Code external to `MBFilesystemCache` should never call these methods directly.
 */
@interface MBFilesystemCache (ForSubclassEyesOnly)

/*----------------------------------------------------------------------------*/
#pragma mark File management
/*!    @name File management                                                  */
/*----------------------------------------------------------------------------*/

/*!
 Accesses the `NSFileManager` instance used internally by the cache.
 
 @return    The file manager.
 */
- (nonnull NSFileManager*) fileManager;

/*!
 Ensures that the cache directory used by the receiver exists. If the directory
 does not exist, it will be created.
 */
- (void) ensureCacheDirectory;

/*!
 Returns the file extension that should be used for the file associated with
 the given cache key.
 
 @param     key The cache key for which the file extension is sought.
 
 @return    The file extension.
 */
- (nonnull NSString*) fileExtensionForCacheKey:(nonnull id)key;

/*!
 Returns the file path that should be used for the file associated with
 the given cache key.

 @param     key The cache key for which the file path is sought.

 @return    The file path.
 */
- (nonnull NSString*) filePathForCacheKey:(nonnull id)key;

/*----------------------------------------------------------------------------*/
#pragma mark Loading cache objects
/*!    @name Loading cache objects                                            */
/*----------------------------------------------------------------------------*/

/*!
 Loads the cache object contained in the specified file.
 
 The default implementation reads the file into an `NSData` instance and then
 returns the result of calling `objectFromCacheData:` with that `NSData`.

 Subclasses may override this method to provide a more efficient mechanism
 for reconstituting objects from files.
 
 @param     path The path of the file to read.
 
 @return    The cache object, or `nil` if it couldn't be read..
 */
- (nullable id) objectFromCacheFile:(nonnull NSString*)path;

/*!
 Notifies the cache that a cache object has been loaded into memory for the
 given key.
 
 Subclasses should call this method if they provide another mechanism for
 loading cache objects. For example, a cache that fetches objects via HTTP
 can call this method when an HTTP request has completed.
 
 @param     cacheObj The cache object that was loaded.
 
 @param     key The cache key associated with the cache object.
 */
- (void) objectLoaded:(nonnull id)cacheObj
               forKey:(nonnull id)key;

/*----------------------------------------------------------------------------*/
#pragma mark Storing objects in the cache
/*!    @name Storing objects in the cache                                     */
/*----------------------------------------------------------------------------*/

/*!
 Consults the delegate's `shouldStoreObject:forKey:inMemoryCache:` method
 to determine whether the specified object should be stored in the memory cache.
 
 If the delegate method returns `YES`, the object will be stored in the cache
 and associated with the specified key.
 
 @param     cacheObj The object that may be stored in the cache.
 
 @param     key The cache key to associate with `cacheObj` if the delegate
            permits storage in the cache.
 */
- (void) storeObjectInMemoryCacheIfAppropriate:(nonnull id)cacheObj forKey:(nonnull id)key;

/*!
 Consults the delegate's `shouldStoreObject:forKey:inFilesystemCache:` method
 to determine whether the specified object should be stored in the filesystem
 cache.
 
 If the delegate method returns `YES`, the object will be stored in the cache
 and associated with the specified key.
 
 @param     cacheObj The object that may be stored in the cache.
 
 @param     key The cache key to associate with `cacheObj` if the delegate
            permits storage in the cache.
 */
- (void) storeObjectInFilesystemCacheIfAppropriate:(nonnull id)cacheObj forKey:(nonnull id)key;

@end
