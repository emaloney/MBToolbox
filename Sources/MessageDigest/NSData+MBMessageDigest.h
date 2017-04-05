//
//  NSData+MBMessageDigest.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/4/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>

/******************************************************************************/
#pragma -
#pragma mark NSData MD5 category
/******************************************************************************/

/*!
 Extends the `NSData` class by adding methods for computing secure, one-way
 message digest hashes.
 */
@interface NSData (MBMessageDigest)

/*!
 Computes an MD5 hash from the contents of the receiver.
 
 @return    the MD5 hash, as a lowercase hexadecimal string
 */
- (nonnull NSString*) MD5;

/*!
 Computes an SHA-1 hash from the contents of the receiver.

 @return    the SHA-1 hash, as a lowercase hexadecimal string
 */
- (nonnull NSString*) SHA1;

@end
