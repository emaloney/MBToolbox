//
//  MBMessageDigest.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 10/11/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "Mockingbird-Toolbox.h"

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
+ (NSData*) MD5DataForString:(NSString*)src;

/*!
 Computes an MD5 hash given an input string.
 
 @param     src the string for which the MD5 will be computed
 
 @return    the MD5 hash, as a lowercase hexadecimal string
 */
+ (NSString*) MD5ForString:(NSString*)src;

/*!
 Computes an MD5 hash from an `NSData` instance.
 
 @param     src the data for which the MD5 will be computed
 
 @return    the MD5 hash, as a lowercase hexadecimal string
 */
+ (NSString*) MD5ForData:(NSData*)src;

/*!
 Computes an MD5 hash from an array of bytes.
 
 @param     bytes the byte array for which the MD5 will be computed
 
 @param     len the length of the byte array
 
 @return    the MD5 hash, as a lowercase hexadecimal string
 */
+ (NSString*) MD5ForBytes:(const void*)bytes length:(size_t)len;

/*!
 Computes an MD5 hash for the contents of a file.
 
 @param     path the filesystem path of the file for which the MD5 will
            be computed
 
 @param     errPtr if an error occurs and this parameter is non-`nil`,
            the error will be stored here upon return
 
 @return    the MD5 hash, as a lowercase hexadecimal string; if an error
            occurs while attempting to read the file, `nil`
            is returned
 */
+ (NSString*) MD5ForFileAtPath:(NSString*)path error:(NSError**)errPtr;

/*!
 Computes an MD5 hash for the contents of a file.
 
 @param     path the filesystem path of the file for which the MD5 will
            be computed
 
 @return    the MD5 hash, as a lowercase hexadecimal string; if an error
            occurs while attempting to read the file, `nil`
            is returned
 */
+ (NSString*) MD5ForFileAtPath:(NSString*)path;

/*----------------------------------------------------------------------------*/
#pragma mark Creating SHA-1 message digests
/*!    @name Creating SHA-1 message digests                                   */
/*----------------------------------------------------------------------------*/

/*!
 Computes an SHA-1 hash given an input string.
 
 @param     src the string for which the SHA-1 will be computed
 
 @return    the SHA-1 hash, as binary NSData
 */
+ (NSData*) SHA1DataForString:(NSString*)src;

/*!
 Computes an SHA-1 hash given an input string.
 
 @param     src the string for which the SHA-1 will be computed
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string
 */
+ (NSString*) SHA1ForString:(NSString*)src;

/*!
 Computes an SHA-1 hash from an `NSData` instance.
 
 @param     src the data for which the SHA-1 will be computed
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string
 */
+ (NSString*) SHA1ForData:(NSData*)src;

/*!
 Computes an SHA-1 hash from an array of bytes.
 
 @param     bytes the byte array for which the SHA-1 will be computed
 
 @param     len the length of the byte array
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string
 */
+ (NSString*) SHA1ForBytes:(const void*)bytes length:(size_t)len;

/*!
 Computes an SHA-1 hash for the contents of a file.
 
 @param     path the filesystem path of the file for which the SHA-1 will
            be computed
 
 @param     errPtr if an error occurs and this parameter is non-`nil`,
            the error will be stored here upon return
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string; if an error
            occurs while attempting to read the file, `nil`
            is returned
 */
+ (NSString*) SHA1ForFileAtPath:(NSString*)path error:(NSError**)errPtr;

/*!
 Computes an SHA-1 hash for the contents of a file.
 
 @param     path the filesystem path of the file for which the SHA-1 will
            be computed
 
 @return    the SHA-1 hash, as a lowercase hexadecimal string; if an error
            occurs while attempting to read the file, `nil`
            is returned
 */
+ (NSString*) SHA1ForFileAtPath:(NSString*)path;

@end
