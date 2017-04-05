//
//  MBMessageDigest.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 10/11/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSError+MBToolbox.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBMessageDigest class
/******************************************************************************/

/*!
 Provides a mechanism for computing secure one-way hashes from various data
 sources.
 
 For convenience, extensions are provided for the `NSString` and `NSData`
 classes allowing message digests to be computed on such instances directly.
 
 See `NSString(MBMessageDigest)` and `NSData(MBMessageDigest)` for details.
 */
@interface MBMessageDigest : NSObject

/*----------------------------------------------------------------------------*/
#pragma mark Creating MD5 message digests
/*!    @name Creating MD5 message digests                                     */
/*----------------------------------------------------------------------------*/

/*!
 Computes an MD5 hash given an input string.
 
 @param     src the string for which the MD5 will be computed
 
 @return    the MD5 hash, as binary NSData
 */
+ (nonnull NSData*) MD5DataForString:(nonnull NSString*)src;

/*!
 Computes an MD5 hash given an input string.
 
 @param     src the string for which the MD5 will be computed
 
 @return    the MD5 hash, as a lowercase hexadecimal string
 */
+ (nonnull NSString*) MD5ForString:(nonnull NSString*)src;

/*!
 Computes an MD5 hash from an `NSData` instance.
 
 @param     src the data for which the MD5 will be computed
 
 @return    the MD5 hash, as a lowercase hexadecimal string
 */
+ (nonnull NSString*) MD5ForData:(nonnull NSData*)src;

/*!
 Computes an MD5 hash from an array of bytes.
 
 @param     bytes the byte array for which the MD5 will be computed
 
 @param     len the length of the byte array
 
 @return    the MD5 hash, as a lowercase hexadecimal string
 */
+ (nonnull NSString*) MD5ForBytes:(nonnull const void*)bytes length:(size_t)len;

/*!
 Computes an MD5 hash for the contents of a file.
 
 @param     path the filesystem path of the file for which the MD5 will
            be computed
 
 @param     errPtr If an error occurs and this parameter is non-`nil`,
             `*errPtr` will be updated to point to an `NSError` instance
            containing further information about the error.

 @return    the MD5 hash, as a lowercase hexadecimal string; if an error
            occurs while attempting to read the file, `nil`
            is returned
 */
+ (nullable NSString*) MD5ForFileAtPath:(nonnull NSString*)path error:(NSErrorPtrPtr)errPtr;

/*!
 Computes an MD5 hash for the contents of a file.
 
 @param     path the filesystem path of the file for which the MD5 will
            be computed
 
 @return    the MD5 hash, as a lowercase hexadecimal string; if an error
            occurs while attempting to read the file, `nil`
            is returned
 */
+ (nullable NSString*) MD5ForFileAtPath:(nonnull NSString*)path;

/*----------------------------------------------------------------------------*/
#pragma mark Creating SHA-1 message digests
/*!    @name Creating SHA-1 message digests                                   */
/*----------------------------------------------------------------------------*/

/*!
 Computes an SHA-1 hash given an input string.
 
 @param     src the string for which the SHA-1 will be computed
 
 @return    the SHA-1 hash, as binary NSData
 */
+ (nonnull NSData*) SHA1DataForString:(nonnull NSString*)src;

/*!
 Computes an SHA-1 hash given an input string.
 
 @param     src the string for which the SHA-1 will be computed
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string
 */
+ (nonnull NSString*) SHA1ForString:(nonnull NSString*)src;

/*!
 Computes an SHA-1 hash from an `NSData` instance.
 
 @param     src the data for which the SHA-1 will be computed
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string
 */
+ (nonnull NSString*) SHA1ForData:(nonnull NSData*)src;

/*!
 Computes an SHA-1 hash from an array of bytes.
 
 @param     bytes the byte array for which the SHA-1 will be computed
 
 @param     len the length of the byte array
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string
 */
+ (nonnull NSString*) SHA1ForBytes:(nonnull const void*)bytes length:(size_t)len;

/*!
 Computes an SHA-1 hash for the contents of a file.
 
 @param     path the filesystem path of the file for which the SHA-1 will
            be computed
 
 @param     errPtr If an error occurs and this parameter is non-`nil`,
             `*errPtr` will be updated to point to an `NSError` instance
            containing further information about the error.
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string; if an error
            occurs while attempting to read the file, `nil`
            is returned
 */
+ (nullable NSString*) SHA1ForFileAtPath:(nonnull NSString*)path error:(NSErrorPtrPtr)errPtr;

/*!
 Computes an SHA-1 hash for the contents of a file.
 
 @param     path the filesystem path of the file for which the SHA-1 will
            be computed
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string; if an error
            occurs while attempting to read the file, `nil`
            is returned
 */
+ (nullable NSString*) SHA1ForFileAtPath:(nonnull NSString*)path;

@end
