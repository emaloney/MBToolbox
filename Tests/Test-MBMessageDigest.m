//
//  Test-MBMessageDigest.m
//  MockingbirdTests
//
//  Created by Evan Coyne Maloney on 4/14/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "MBMessageDigest.h"
#import "NSData+MBMessageDigest.h"
#import "NSString+MBMessageDigest.h"

/******************************************************************************/
#pragma mark -
#pragma mark Tests
/******************************************************************************/

@interface MBMessageDigestTests : XCTestCase
@end

@implementation MBMessageDigestTests

- (void) _testMD5String:(NSString*)toHash expectingString:(NSString*)expectedHash
{
    NSString* testOne = [toHash MD5];
    XCTAssertEqualObjects(testOne, expectedHash, @"unexpected message hash");

    NSString* testTwo = [MBMessageDigest MD5ForString:toHash];
    XCTAssertEqualObjects(testOne, testTwo, @"hashes don't match");
}

- (void) _testMD5Data:(NSData*)toHash expectingString:(NSString*)expectedHash
{
    NSString* testOne = [toHash MD5];
    XCTAssertEqualObjects(testOne, expectedHash, @"unexpected message hash");

    NSString* testTwo = [MBMessageDigest MD5ForData:toHash];
    XCTAssertEqualObjects(testOne, testTwo, @"hashes don't match");
}

- (void) _testSHA1String:(NSString*)toHash expectingString:(NSString*)expectedHash
{
    NSString* testOne = [toHash SHA1];
    XCTAssertEqualObjects(testOne, expectedHash, @"unexpected message hash");

    NSString* testTwo = [MBMessageDigest SHA1ForString:toHash];
    XCTAssertEqualObjects(testOne, testTwo, @"hashes don't match");
}

- (void) _testSHA1Data:(NSData*)toHash expectingString:(NSString*)expectedHash
{
    NSString* testOne = [toHash SHA1];
    XCTAssertEqualObjects(testOne, expectedHash, @"unexpected message hash");

    NSString* testTwo = [MBMessageDigest SHA1ForData:toHash];
    XCTAssertEqualObjects(testOne, testTwo, @"hashes don't match");
}

- (void) _testMD5String:(NSString*)toHash expectingData:(NSData*)expectedHash
{
    NSData* testHash = [MBMessageDigest MD5DataForString:toHash];
    XCTAssertEqualObjects(expectedHash, testHash, @"unexpected message hash");
}

- (void) _testSHA1String:(NSString*)toHash expectingData:(NSData*)expectedHash
{
    NSData* testHash = [MBMessageDigest SHA1DataForString:toHash];
    XCTAssertEqualObjects(expectedHash, testHash, @"unexpected message hash");
}

- (void) testHashStringToString
{
    [self _testMD5String:@"this is a test"
         expectingString:@"54b0c58c7ce9f2a8b551351102ee0938"];

    [self _testMD5String:@"this is a not a test\nbut maybe it should be\n"
         expectingString:@"a752ea5c60926f1f18419ac806969e4b"];

    [self _testSHA1String:@"this is a test"
          expectingString:@"fa26be19de6bff93f70bc2308434e4a440bbad02"];

    [self _testSHA1String:@"this is a not a test\nbut maybe it should be\n"
          expectingString:@"8d2f164edadeadace439d9069bcd4bfd69897f6d"];
}

- (void) testHashDataToString
{
    // the base64 encoding of the string "this is a test" is dGhpcyBpcyBhIHRlc3Q=
    NSData* testData1 = [[NSData alloc] initWithBase64EncodedString:@"dGhpcyBpcyBhIHRlc3Q=" options:0];

    // the base64 encoding of the string "this is a not a test\nbut maybe it should be\n"
    // is dGhpcyBpcyBhIG5vdCBhIHRlc3QKYnV0IG1heWJlIGl0IHNob3VsZCBiZQo=
    NSData* testData2 = [[NSData alloc] initWithBase64EncodedString:@"dGhpcyBpcyBhIG5vdCBhIHRlc3QKYnV0IG1heWJlIGl0IHNob3VsZCBiZQo=" options:0];

    [self _testMD5Data:testData1
       expectingString:@"54b0c58c7ce9f2a8b551351102ee0938"];

    [self _testMD5Data:testData2
       expectingString:@"a752ea5c60926f1f18419ac806969e4b"];

    [self _testSHA1Data:testData1
        expectingString:@"fa26be19de6bff93f70bc2308434e4a440bbad02"];

    [self _testSHA1Data:testData2
        expectingString:@"8d2f164edadeadace439d9069bcd4bfd69897f6d"];
}

- (void) testHashDataToData
{
    NSData* md5Data1 = [[NSData alloc] initWithBase64EncodedString:@"VLDFjHzp8qi1UTURAu4JOA==" options:0];

    NSData* md5Data2 = [[NSData alloc] initWithBase64EncodedString:@"p1LqXGCSbx8YQZrIBpaeSw==" options:0];

    NSData* sha1Data1 = [[NSData alloc] initWithBase64EncodedString:@"+ia+Gd5r/5P3C8IwhDTkpEC7rQI=" options:0];

    NSData* sha1Data2 = [[NSData alloc] initWithBase64EncodedString:@"jS8WTtrerazkOdkGm81L/WmJf20=" options:0];

    [self _testMD5String:@"this is a test"
           expectingData:md5Data1];

    [self _testMD5String:@"this is a not a test\nbut maybe it should be\n"
           expectingData:md5Data2];

    [self _testSHA1String:@"this is a test"
            expectingData:sha1Data1];

    [self _testSHA1String:@"this is a not a test\nbut maybe it should be\n"
            expectingData:sha1Data2];
}

@end
