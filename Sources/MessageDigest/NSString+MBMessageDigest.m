//
//  MBMessageDigest.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/4/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "NSString+MBMessageDigest.h"
#import "MBMessageDigest.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark NSString MD5 Category
/******************************************************************************/

@implementation NSString (MBMessageDigest)

- (nonnull NSString*) MD5
{
    return [MBMessageDigest MD5ForString:self];
}

- (nonnull NSString*) SHA1
{
    return [MBMessageDigest SHA1ForString:self];
}

@end
