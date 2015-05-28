//
//  NSString+MBIndentation.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 9/4/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "NSString+MBIndentation.h"

/******************************************************************************/
#pragma mark -
#pragma mark NSString extensions for indenting lines
/******************************************************************************/

@implementation NSString (MBIndentation)

- (nonnull NSString*) stringByIndentingEachLineWithPrefix:(nonnull NSString*)prefix
{
    //
    // you may ask yourself, how do I work this?
    //
    // we use a scanner and this seemingly more-complicated mechanism instead of
    // [self componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]]
    // because the latter will use more memory and generally be less efficient since
    // we'll be creating twice as many strings.
    //
    // also, you'll note that we're paying attention to '\r\n' line endings used
    // by some platforms, so data loaded from the web (for example) will work
    // correctly.
    //
    NSMutableString* indented = [NSMutableString new];
    NSCharacterSet* nl = [NSCharacterSet newlineCharacterSet];
    NSScanner* scan = [NSScanner scannerWithString:self];
    [scan setCharactersToBeSkipped:nil];    // scanner normally skips newlines; don't!

    NSString* line = nil;
    NSString* lineEnding = nil;
    while (![scan isAtEnd]) {
        if ([scan scanUpToCharactersFromSet:nl intoString:&line]) {
            [indented appendString:prefix];
            [indented appendString:line];
        }

        if ([scan scanCharactersFromSet:nl intoString:&lineEnding]) {
            BOOL didLine = NO;
            BOOL didLastPrefix = NO;
            NSUInteger endLen = lineEnding.length;
            for (NSUInteger i=0; i<endLen; i++) {
                unichar c0 = [lineEnding characterAtIndex:i];
                unichar c1 = 0x0;
                if (i<endLen-1) {
                    c1 = [lineEnding characterAtIndex:i+1];
                }
                if (didLine) {
                    [indented appendString:prefix];
                    didLastPrefix = YES;
                }
                else {
                    didLastPrefix = NO;
                }

                // preserve any platform-specific newlines
                if (c0 == '\r' && c1 == '\n') {
                    [indented appendString:@"\r\n"];
                    i++;
                    didLine = YES;
                }
                else {
                    [indented appendFormat:@"%C", c0];
                    didLine = YES;
                }
            }
            if ([scan isAtEnd] && didLine && !didLastPrefix) {
                [indented appendString:prefix];
            }
        }
    }
    return indented;
}

- (nonnull NSString*) stringByIndentingEachLineWithTab
{
    return [self stringByIndentingEachLineWithPrefix:@"\t"];
}

- (nonnull NSString*) stringByIndentingEachLineWithTabs:(NSUInteger)numberOfTabs
{
    NSString* indentStr = [@"" stringByPaddingToLength:numberOfTabs
                                            withString:@"\t"
                                       startingAtIndex:0];

    return [self stringByIndentingEachLineWithPrefix:indentStr];
}

@end
