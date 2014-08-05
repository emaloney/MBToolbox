//
//  Test-NSString+MBIndentation.m
//  MockingbirdTests
//
//  Created by Evan Coyne Maloney on 4/11/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "NSString+MBIndentation.h"

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

NSString* const kMBStringIndentationTestInput = @""
"this\n"
"is\n"
"a\n"
"test\n"
"of the emergency\n"
"broadcast\n"
"system\n";

NSString* const kMBStringIndentationTestOutputOneTab = @""
"\tthis\n"
"\tis\n"
"\ta\n"
"\ttest\n"
"\tof the emergency\n"
"\tbroadcast\n"
"\tsystem\n"
"\t";

NSString* const kMBStringIndentationTestLinePrefix = @"-=[X]=-";

NSString* const kMBStringIndentationTestOutputPrefix = @""
"-=[X]=- this\n"
"-=[X]=- is\n"
"-=[X]=- a\n"
"-=[X]=- test\n"
"-=[X]=- of the emergency\n"
"-=[X]=- broadcast\n"
"-=[X]=- system\n"
"-=[X]=-";

/******************************************************************************/
#pragma mark -
#pragma mark Tests
/******************************************************************************/

@interface MBStringIndentationTests : XCTestCase
@end

@implementation MBStringIndentationTests

- (void) testIndentingWithSingleTab
{
    NSString* indented = [kMBStringIndentationTestInput stringByIndentingEachLineWithTab];
    XCTAssertEqualObjects(indented, kMBStringIndentationTestOutputOneTab, @"unexpected result from stringByIndentingEachLineWithTab");

    indented = [kMBStringIndentationTestInput stringByIndentingEachLineWithTabs:1];
    XCTAssertEqualObjects(indented, kMBStringIndentationTestOutputOneTab, @"unexpected result from stringByIndentingEachLineWithTabs:1");

    indented = [kMBStringIndentationTestInput stringByIndentingEachLineWithPrefix:@"\t"];
    XCTAssertEqualObjects(indented, kMBStringIndentationTestOutputOneTab, @"unexpected result from stringByIndentingEachLineWithPrefix:@\"\\t\"");
}

- (void) _testIndentingString:(NSString*)string withNumberOfTabs:(NSUInteger)tabCount
{
    NSArray* inputLines = [string componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];

    NSString* indented = [string stringByIndentingEachLineWithTabs:tabCount];
    NSArray* indentedLines = [indented componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];

    XCTAssertEqual(inputLines.count, indentedLines.count, @"Expected inputLines and indentedLines to have same number of lines");

    NSString* prefix = [@"" stringByPaddingToLength:tabCount withString:@"\t" startingAtIndex:0];

    for (NSUInteger i=0; i<inputLines.count; i++) {
        NSString* indentedLine = indentedLines[i];
        NSString* shouldBeLine = [prefix stringByAppendingString:inputLines[i]];
        XCTAssertEqualObjects(shouldBeLine, indentedLine, @"unexpected value for a line");
    }
}

- (void) testIndentingWithArbitraryTabs
{
    for (NSUInteger i=0; i<100; i++) {
        [self _testIndentingString:kMBStringIndentationTestInput withNumberOfTabs:i];
    }
}

- (void) testPrefixingString
{
    NSArray* inputLines = [kMBStringIndentationTestInput componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];

    NSString* prefixed = [kMBStringIndentationTestInput stringByIndentingEachLineWithPrefix:kMBStringIndentationTestLinePrefix];
    NSArray* prefixedLines = [prefixed componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];

    XCTAssertEqual(inputLines.count, prefixedLines.count, @"Expected inputLines and prefixedLines to have same number of lines");

    for (NSUInteger i=0; i<inputLines.count; i++) {
        NSString* prefixedLine = prefixedLines[i];
        NSString* shouldBeLine = [kMBStringIndentationTestLinePrefix stringByAppendingString:inputLines[i]];
        XCTAssertEqualObjects(shouldBeLine, prefixedLine, @"unexpected value for a line");
    }
}

@end
