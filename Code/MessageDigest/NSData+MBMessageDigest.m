//
//  NSData+MBMessageDigest.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/4/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "NSData+MBMessageDigest.h"
#import "MBMessageDigest.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark NSData MD5 Category
/******************************************************************************/

@implementation NSData (MBMessageDigest)

- (NSString*) MD5
{
    debugTrace();

    return [MBMessageDigest MD5ForData:self];
}

- (NSString*) SHA1
{
    debugTrace();

    return [MBMessageDigest SHA1ForData:self];
}

@end

