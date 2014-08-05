//
//  MBCacheOperations.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 2/1/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBCacheOperations.h"

#define DEBUG_LOCAL     0
#define DEBUG_VERBOSE   0

/******************************************************************************/
#pragma mark -
#pragma mark MBCacheReadQueue implementation
/******************************************************************************/

@implementation MBCacheReadQueue

MBImplementSingleton();

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBCacheWriteQueue implementation
/******************************************************************************/

@implementation MBCacheWriteQueue

MBImplementSingleton();

@end

/******************************************************************************/
#pragma mark -
#pragma mark MBCacheWriteOperation implementation
/******************************************************************************/

@implementation MBCacheWriteOperation
{
    MBFilesystemCache* _cache;
    id _cacheObject;
}

/******************************************************************************/
#pragma mark Object lifecycle
/******************************************************************************/

+ (instancetype) operationForWritingObject:(id)obj
                                    toFile:(NSString*)path
                                  forCache:(MBFilesystemCache*)fc
{
    return [[self alloc] initWithObject:obj inCache:fc forFilePath:path];
}

- (id) initWithObject:(id)obj 
              inCache:(MBFilesystemCache*)fc
          forFilePath:(NSString*)path
{
    self = [super initWithData:nil forFilePath:path];
    if (self) {
        _cache = fc;
        _cacheObject = obj;
    }
    return self;
}

/******************************************************************************/
#pragma mark Implementation
/******************************************************************************/

- (NSData*) dataForOperation
{
    debugTrace();
    
    return [_cache cacheDataFromObject:_cacheObject];
}

@end
