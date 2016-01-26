//
//  Test-MBStringFunctions.m
//  MockingbirdTests
//
//  Created by Evan Coyne Maloney on 8/8/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

@import MBToolbox;

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

//#import "MBStringFunctions.h"

/******************************************************************************/
#pragma mark -
#pragma mark Tests
/******************************************************************************/

@interface MBDataStringConversionTests : XCTestCase
@end

@implementation MBDataStringConversionTests
{
    NSData* _testData;
    NSData* _testDataASCII;
    NSString* _testStringHex;
}

- (void) setUp
{
    char cData[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE,
                     0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE };

    _testData = [NSData dataWithBytes:(void*)cData length:16];

    char asciiData[] = { 0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 0x63, 0x61, 0x66, 0x65, 0x62, 0x61, 0x62, 0x65,
                         0x64, 0x65, 0x61, 0x64, 0x62, 0x65, 0x65, 0x66, 0x63, 0x61, 0x66, 0x65, 0x62, 0x61, 0x62, 0x65 };

    _testDataASCII = [NSData dataWithBytes:(void*)asciiData length:32];

    _testStringHex = @"deadbeefcafebabedeadbeefcafebabe";
}

- (void) testDataWithHexString
{
    NSData* test = [NSData dataWithHexString:_testStringHex];
    XCTAssertNotNil(test);
    XCTAssertEqualObjects(_testData, test);
}

- (void) testToStringHex
{
    NSString* hexStr = [_testData toStringHex];
    XCTAssertNotNil(hexStr);
    XCTAssertEqualObjects([hexStr lowercaseString], _testStringHex);
}

- (void) testToStringUsingEncoding
{
    NSString* asciiStr = [_testDataASCII toStringUsingEncoding:NSASCIIStringEncoding];
    XCTAssertNotNil(asciiStr);
    XCTAssertEqualObjects(asciiStr, _testStringHex);

    NSString* utf8Str = [_testDataASCII toStringUsingEncoding:NSUTF8StringEncoding];
    XCTAssertNotNil(utf8Str);
    XCTAssertEqualObjects(utf8Str, _testStringHex);
}

- (void) testToStringASCII
{
    NSString* asciiStr = [_testDataASCII toStringASCII];
    XCTAssertNotNil(asciiStr);
    XCTAssertEqualObjects(asciiStr, _testStringHex);
}

- (void) testToStringUTF8
{
    NSString* utf8Str = [_testDataASCII toStringUTF8];
    XCTAssertNotNil(utf8Str);
    XCTAssertEqualObjects(utf8Str, _testStringHex);
}

- (void) testToString
{
    NSString* str = [_testDataASCII toString];
    XCTAssertNotNil(str);
    XCTAssertEqualObjects(str, _testStringHex);
}

@end
