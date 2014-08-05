//
//  MBMessageDigest.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 4/4/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "NSString+MBMessageDigest.h"
#import "MBMessageDigest.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark NSString MD5 Category
/******************************************************************************/

@implementation NSString (MBMessageDigest)

- (NSString*) MD5
{
    debugTrace();

    return [MBMessageDigest MD5ForString:self];
}

- (NSString*) SHA1
{
    debugTrace();

    return [MBMessageDigest SHA1ForString:self];
}

@end

