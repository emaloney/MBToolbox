//
//  MBFilesystemCache.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 1/28/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBThreadsafeCache.h"

@class MBFilesystemCache;
@class MBCacheReadQueue;
@class MBCacheWriteQueue;

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

// default value for maxAgeOfCacheFiles property (36 hours)
extern const NSTimeInterval kMBFilesystemCacheDefaultMaxAge;

/******************************************************************************/
#pragma mark -
#pragma mark MBFilesystemCacheDelegate protocol
/******************************************************************************/

/*!
 This protocol is adopted by classes that wish to control the behavior of an
 `MBFilesystemCache` instance.
 */
@protocol MBFilesystemCacheDelegate

/*!
 Called by the `MBFilesystemCache` to create a filename for a given cache
 key.
 
 The cache object associated with the given key will be stored in a file
 with the name returned by this method.
 
 @param     key The cache key for which the filename is sought.
 
 @return    The filename for the given cache key.
 */
- (nonnull NSString*) filenameForCacheKey:(nonnull id)key;

@optional

/*----------------------------------------------------------------------------*/
#pragma mark Converting cache objects to and from raw data
/*!    @name Converting cache objects to and from raw data                    */
/*----------------------------------------------------------------------------*/

/*!
 Converts the specified cache object into an `NSData` instance that can be
 written to a file.

 @note      If cache objects are stored as `NSData` instances directly,
            the delegate does not need to implement this method.

 @param     cacheObj The cache object for which the raw data should be
            returned.

 @return    An `NSData` representation of the given cache object, or `nil` if
            it could not be created.
 */
- (nullable NSData*) cacheDataFromObject:(nonnull id)cacheObj;

/*!
 Converts raw data representing a cache object into the cache object itself.
 Used to convert a file into an object.

 @note      If cache objects are stored as `NSData` instances directly,
            the delegate does not need to implement this method.

 @param     cacheData The raw data representing the cache object.

 @return    The cache object created from the raw cache data, or `nil`
            if it could not be created.
 */
- (nullable id) objectFromCacheData:(nonnull NSData*)cacheData;

/*----------------------------------------------------------------------------*/
#pragma mark Controlling what gets stored in the cache
/*!    @name Controlling what gets stored in the cache                        */
/*----------------------------------------------------------------------------*/

/*!
 Asks the delegate whether or not the specified object should be stored in the
 memory cache.

 @note      If the delegate does not implement this method, objects will
            always be stored in the memory cache.

 @param     cacheObj The object that may be stored in the memory cache.
 
 @param     key The cache key associated with `cacheObj`.
 
 @param     cache The `MBFilesystemCache` in which the object may be cached.
 
 @return    `YES` if the `cacheObj` should be stored in the memory cache of
            `cache`; `NO` otherwise.
 */
- (BOOL) shouldStoreObject:(nonnull id)cacheObj
                    forKey:(nonnull id)key
             inMemoryCache:(nonnull MBFilesystemCache*)cache;

/*!
 Asks the delegate whether or not the specified object should be stored in the
 filesystem cache.

 @note      If the delegate does not implement this method, objects will
            always be stored in the filesystem cache.

 @param     cacheObj The object that may be stored in the filesystem cache.
 
 @param     key The cache key associated with `cacheObj`.
 
 @param     cache The `MBFilesystemCache` in which the object may be cached.
 
 @return    `YES` if the `cacheObj` should be stored in the filesystem cache of
            `cache`; `NO` otherwise.
 */
- (BOOL) shouldStoreObject:(nonnull id)cacheObj
                    forKey:(nonnull id)key
         inFilesystemCache:(nonnull MBFilesystemCache*)cache;

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFilesystemCache class
/******************************************************************************/

/*!
 An object cache implementation capable of persisting cache objects to the
 filesystem.
 
 Utilize the methods provided by the `MBThreadsafeCache` superclass to access
 data stored in an `MBFilesystemCache` if you do not care whether or not a
 cache object is loaded into memory when it is requested.
 
 @note      Classes that wish to subclass `MBFilesystemCache` should refer
            to the internal `MBFilesystemCache(ForSubclassEyesOnly)` methods
            declared in the header file `MBFilesystemCache+Subclassing.h`.
 */
@interface MBFilesystemCache : MBThreadsafeCache < MBFilesystemCacheDelegate >

/*----------------------------------------------------------------------------*/
#pragma mark Object lifecycle
/*!    @name Object lifecycle                                                 */
/*----------------------------------------------------------------------------*/

/*!
 Initializes the receiver with the given name.
 
 The receiver will act as its own delegate unless the `cacheDelegate` property
 is explicitly set.
 
 @warning   Do not use the same cache name for more than one `MBFilesystemCache`
            at any given time. Unpredictable results will occur if you do.

 @param     name The name of the filesystem cache. Must not be `nil`, and must
            not contain any characters that are illegal filename characters
            in the local filesystem. This name will be used in the path of
            the directory in which the receiver's files will be stored.
 
 @return    The receiver.
 */
- (nonnull instancetype) initWithName:(nonnull NSString*)name;

/*!
 Initializes the receiver with the given name.
 
 @warning   Do not use the same cache name for more than one `MBFilesystemCache`
            at any given time. Unpredictable results will occur if you do.

 @param     name The name of the filesystem cache. Must not be `nil`, and must
            not contain any characters that are illegal filename characters
            in the local filesystem. This name will be used in the path of
            the directory in which the receiver's files will be stored.
 
 @param     delegate The `MBFilesystemCacheDelegate` that will be used as
            the receiver's delegate. Must not be `nil`.
 
 @return    The receiver.
 */
- (nonnull instancetype) initWithName:(nonnull NSString*)name
                        cacheDelegate:(nonnull id)delegate;

/*----------------------------------------------------------------------------*/
#pragma mark Cache properties
/*!    @name Cache properties                                                 */
/*----------------------------------------------------------------------------*/

/*! Returns the operation queue that will be used for performing filesystem
    cache read operations. */
@property(nonnull, nonatomic, readonly) MBCacheReadQueue* readQueue;

/*! Returns the operation queue that will be used for performing filesystem
    cache write operations. */
@property(nonnull, nonatomic, readonly) MBCacheWriteQueue* writeQueue;

/*! Returns the name of the cache, which is used to determine the directory
    in which cache files are stored. This is name provided when the receiver
    is initialized. */
@property(nonnull, nonatomic, readonly) NSString* cacheName;

/*! Returns the `MBFilesystemCacheDelegate` used by the receiver. */
@property(nullable, nonatomic, weak) id cacheDelegate;

/*! Returns the maximum age of the files in the cache, in seconds. Files that
    are older than this value will not be used by the cache and will
    eventually be deleted. This defaults to the value of the constant 
    `kMBFilesystemCacheDefaultMaxAge` (currently, 36 hours). */
@property(nonatomic, assign) NSTimeInterval maxAgeOfCacheFiles;

/*----------------------------------------------------------------------------*/
#pragma mark Checking for objects in the cache
/*!    @name Checking for objects in the cache                                */
/*----------------------------------------------------------------------------*/

/*!
 Determines whether the specified cache key represents an object currently
 in the cache.
 
 The filesystem cache and memory cache are both checked for the presence of
 an object with the specified key.
 
 @param     key The cache key to check.
 
 @return    `YES` if there is an object associated with `key` in either the
            filesystem or the memory cache; `NO` otherwise.
 */
- (BOOL) isKeyInCache:(nonnull id)key;

/*!
 Determines whether the specified cache key represents an object currently
 in the memory cache.
 
 @param     key The cache key to check.
 
 @return    `YES` if there is an object associated with `key` in the memory
            cache; `NO` otherwise.
 */
- (BOOL) isKeyInMemoryCache:(nonnull id)key;

/*!
 Determines whether the specified cache key represents an object currently
 in the filesystem cache.

 @param     key The cache key to check.
 
 @return    `YES` if there is an object associated with `key` in the filesystem
            cache; `NO` otherwise.
 */
- (BOOL) isKeyInFilesystemCache:(nonnull id)key;

/*----------------------------------------------------------------------------*/
#pragma mark Retrieving objects from the cache
/*!    @name Retrieving objects from the cache                                */
/*----------------------------------------------------------------------------*/

/*!
 Retrieves an object from the memory cache, if it is there.
 
 @note      This method *does not* attempt to load an object from the 
            filesystem cache. Use the `objectForKey:` method (declared by
            the `MBThreadsafeCache` superclass) to retrieve objects regardless
            of whether they're in the memory or filesystem caches.
 
 @param     key The cache key of the object to retrieve.
 
 @return    The object instance, or `nil` if it was not in the cache.
 */
- (nullable id) objectForKeyInMemoryCache:(nonnull id)key;

/*----------------------------------------------------------------------------*/
#pragma mark Managing the filesystem cache
/*!    @name Managing the filesystem cache                                    */
/*----------------------------------------------------------------------------*/

/*!
 Deletes all of the cache objects currently in the filesystem cache.
 
 The memory cache is not affected by calls to this method.
 */
- (void) clearFilesystemCache;

/*!
 Deletes all cache files older than a certain age.

 The memory cache is not affected by calls to this method.
 
 @param     ageInSeconds The maximum age allowed for cache files. Files older
            than this age will be deleted.
 */
- (void) purgeCacheFilesOlderThan:(NSTimeInterval)ageInSeconds;

/*!
 Deletes all cache files older than the number of seconds specified by the
 `maxAgeOfCacheFiles` property.

 The memory cache is not affected by calls to this method.
 */
- (void) purgeOutOfDateCacheFiles;

@end
