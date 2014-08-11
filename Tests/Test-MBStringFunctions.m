//
//  Test-MBStringFunctions.m
//  MockingbirdTests
//
//  Created by Evan Coyne Maloney on 8/8/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

#import "MBStringFunctions.h"

/******************************************************************************/
#pragma mark -
#pragma mark Tests
/******************************************************************************/

@interface MBStringFunctionTests : XCTestCase
@end

@implementation MBStringFunctionTests

- (void) testForceStringFunction
{
    NSString* str = MBForceString(nil);
    XCTAssertNotNil(str, @"MBForceString() should never return nil");
    XCTAssertTrue([str isKindOfClass:[NSString class]], @"MBForceString() should always return an NSString instance");
    XCTAssertTrue(str.length == 0, @"MBForceString() should return an empty string with nil input");

    str = MBForceString([NSNull null]);
    XCTAssertNotNil(str, @"MBForceString() should never return nil");
    XCTAssertTrue([str isKindOfClass:[NSString class]], @"MBForceString() should always return an NSString instance");
    XCTAssertTrue(str.length == 0, @"MBForceString() should return an empty string with an NSNull as input");

    NSString* inputStr = @"this is my input";
    str = MBForceString(inputStr);
    XCTAssertNotNil(str, @"MBForceString() should never return nil");
    XCTAssertTrue([str isKindOfClass:[NSString class]], @"MBForceString() should always return an NSString instance");
    XCTAssertTrue([str isEqualToString:inputStr], @"MBForceString() should return the string provided as input");

    str = MBForceString(@(2.4));
    XCTAssertNotNil(str, @"MBForceString() should never return nil");
    XCTAssertTrue([str isKindOfClass:[NSString class]], @"MBForceString() should always return an NSString instance");
    XCTAssertTrue([str isEqualToString:@"2.4"], @"MBForceString() should return the string version of the input provided");
}

- (void) testTrimStringFunction
{
    NSString* str = MBTrimString(nil);
    XCTAssertNotNil(str, @"MBTrimString() should never return nil");
    XCTAssertTrue([str isKindOfClass:[NSString class]], @"MBTrimString() should always return an NSString instance");
    XCTAssertTrue(str.length == 0, @"MBTrimString() should return an empty string with nil input");

    str = MBTrimString([NSNull null]);
    XCTAssertNotNil(str, @"MBTrimString() should never return nil");
    XCTAssertTrue([str isKindOfClass:[NSString class]], @"MBTrimString() should always return an NSString instance");
    XCTAssertTrue(str.length == 0, @"MBTrimString() should return an empty string with an NSNull as input");

    NSString* testStr = @"   \n   this is my test string. there are many like it but this one is mine\n\n\t\n  ";
    str = MBTrimString(testStr);
    XCTAssertNotNil(str, @"MBTrimString() should never return nil");
    XCTAssertTrue([str isKindOfClass:[NSString class]], @"MBTrimString() should always return an NSString instance");
    XCTAssertTrue([str isEqualToString:@"this is my test string. there are many like it but this one is mine"], @"MBTrimString() should return the trimmed version of the input provided");
}

- (void) testStringifyMacro
{
    NSString* str = MBStringify(NSUTF8StringEncoding);
    XCTAssertNotNil(str, @"MBStringify() should never return nil");
    XCTAssertTrue([str isKindOfClass:[NSString class]], @"MBStringify() should always return an NSString instance");
    XCTAssertTrue([str isEqualToString:@"NSUTF8StringEncoding"], @"MBStringify() should a string version of the input provided");
}

@end
