//
//  NSData+MBMessageDigest.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/4/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "NSData+MBMessageDigest.h"
#import "MBMessageDigest.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark NSData MD5 Category
/******************************************************************************/

@implementation NSData (MBMessageDigest)

- (nonnull NSString*) MD5
{
    return [MBMessageDigest MD5ForData:self];
}

- (nonnull NSString*) SHA1
{
    return [MBMessageDigest SHA1ForData:self];
}

@end
