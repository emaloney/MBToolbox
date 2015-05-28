//
//  NSString+MBRegex.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 11/29/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "NSString+MBRegex.h"
#import "MBRegexCache.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark NSMutableString regular expression implementation
/******************************************************************************/

@implementation NSMutableString (MBRegex)

/******************************************************************************/
#pragma mark Performing regex replacements in a mutable string
/******************************************************************************/

- (NSUInteger) replaceRegexMatches:(nonnull NSString*)pattern
                      withTemplate:(nonnull NSString*)templ
                           options:(NSRegularExpressionOptions)options
                             range:(NSRange)range
                             error:(NSErrorPtrPtr)errPtr
{
    MBLogDebugTrace();
    
    NSError* err = nil;
    NSRegularExpression* regex = [MBRegexCache regularExpressionWithPattern:pattern 
                                                                    options:options
                                                                      error:&err];
    if (err) {
        if (errPtr) {
            *errPtr = err;
        } else {
            MBLogError(@"Error attempting to create regular expression: %@", err);
        }
        return 0;
    }
    
    return [regex replaceMatchesInString:self options:0 range:range withTemplate:templ];
}

- (NSUInteger) replaceRegexMatches:(nonnull NSString*)pattern
                      withTemplate:(nonnull NSString*)templ
                           options:(NSRegularExpressionOptions)options
                             range:(NSRange)range
{
    return [self replaceRegexMatches:pattern withTemplate:templ options:options range:NSMakeRange(0, self.length) error:nil];
}

- (NSUInteger) replaceRegexMatches:(nonnull NSString*)pattern
                      withTemplate:(nonnull NSString*)templ
                           options:(NSRegularExpressionOptions)options
{
    return [self replaceRegexMatches:pattern withTemplate:templ options:options range:NSMakeRange(0, self.length) error:nil];
}

- (NSUInteger) replaceRegexMatches:(nonnull NSString*)pattern
                      withTemplate:(nonnull NSString*)templ
{
    return [self replaceRegexMatches:pattern withTemplate:templ options:0 range:NSMakeRange(0, self.length) error:nil];
}

@end

/******************************************************************************/
#pragma mark -
#pragma mark NSString regular expression implementation
/******************************************************************************/

@implementation NSString (MBRegex)

/******************************************************************************/
#pragma mark Creating regular expressions
/******************************************************************************/

- (nullable NSRegularExpression*) regularExpression
{
    return [MBRegexCache regularExpressionWithPattern:self];
}

- (nullable NSRegularExpression*) regularExpressionWithOptions:(NSRegularExpressionOptions)options
{
    return [MBRegexCache regularExpressionWithPattern:self options:options];
}

- (nullable NSRegularExpression*) regularExpressionWithOptions:(NSRegularExpressionOptions)options
                                                         error:(NSErrorPtrPtr)errPtr
{
    return [MBRegexCache regularExpressionWithPattern:self options:options error:errPtr];
}

/******************************************************************************/
#pragma mark Escaping
/******************************************************************************/

- (nonnull NSString*) escapedRegexPattern
{
    MBLogDebugTrace();
    
    return [NSRegularExpression escapedPatternForString:self];
}

- (nonnull NSString*) escapedRegexTemplate
{
    MBLogDebugTrace();
    
    return [NSRegularExpression escapedTemplateForString:self];
}

/******************************************************************************/
#pragma mark Getting all matches in the receiver
/******************************************************************************/

- (nullable NSArray*) matchesWithRegex:(nonnull NSString*)pattern
                               options:(NSRegularExpressionOptions)options
                                 range:(NSRange)range
                                 error:(NSErrorPtrPtr)errPtr
{
    MBLogDebugTrace();
    
    NSError* err = nil;
    NSRegularExpression* regex = [MBRegexCache regularExpressionWithPattern:pattern 
                                                                    options:options
                                                                      error:&err];
    if (err) {
        if (errPtr) {
            *errPtr = err;
        } else {
            MBLogError(@"Error attempting to create regular expression: %@", err);
        }
        return nil;
    }
    
    return [regex matchesInString:self options:0 range:range];
}

- (nullable NSArray*) matchesWithRegex:(nonnull NSString*)pattern
                               options:(NSRegularExpressionOptions)options
                                 range:(NSRange)range
{
    MBLogDebugTrace();

    return [self matchesWithRegex:pattern options:options range:NSMakeRange(0, self.length) error:nil];
}

- (nullable NSArray*) matchesWithRegex:(nonnull NSString*)pattern
                               options:(NSRegularExpressionOptions)options
{
    return [self matchesWithRegex:pattern options:options range:NSMakeRange(0, self.length) error:nil];
}

- (nullable NSArray*) matchesWithRegex:(nonnull NSString*)pattern
{
    return [self matchesWithRegex:pattern options:0 range:NSMakeRange(0, self.length) error:nil];
}

/******************************************************************************/
#pragma mark Testing whether the pattern matches the receiver
/******************************************************************************/

- (BOOL) isMatchedByRegex:(nonnull NSString*)pattern
                  options:(NSRegularExpressionOptions)options
                    range:(NSRange)range
                    error:(NSErrorPtrPtr)errPtr
{
    return ([self numberOfRegexMatches:pattern options:options range:range error:errPtr] > 0);
}

- (BOOL) isMatchedByRegex:(nonnull NSString*)pattern
                  options:(NSRegularExpressionOptions)options
                    range:(NSRange)range
{
    return ([self numberOfRegexMatches:pattern options:options range:range error:nil] > 0);
}

- (BOOL) isMatchedByRegex:(nonnull NSString*)pattern
                  options:(NSRegularExpressionOptions)options
{
    return ([self numberOfRegexMatches:pattern options:options range:NSMakeRange(0, self.length) error:nil] > 0);
}

- (BOOL) isMatchedByRegex:(nonnull NSString*)pattern
{
    return ([self numberOfRegexMatches:pattern options:0 range:NSMakeRange(0, self.length) error:nil] > 0);
}

/******************************************************************************/
#pragma mark Counting the matches in the receiver
/******************************************************************************/

- (NSUInteger) numberOfRegexMatches:(nonnull NSString*)pattern
                            options:(NSRegularExpressionOptions)options
                              range:(NSRange)range
                              error:(NSErrorPtrPtr)errPtr
{
    MBLogDebugTrace();
    
    NSError* err = nil;
    NSRegularExpression* regex = [MBRegexCache regularExpressionWithPattern:pattern 
                                                                  options:options
                                                                    error:&err];
    if (err) {
        if (errPtr) {
            *errPtr = err;
        } else {
            MBLogError(@"Error attempting to create regular expression: %@", err);
        }
        return 0;
    }
    
    return [regex numberOfMatchesInString:self options:0 range:range];
}

- (NSUInteger) numberOfRegexMatches:(nonnull NSString*)pattern
                            options:(NSRegularExpressionOptions)options
                              range:(NSRange)range
{
    return [self numberOfRegexMatches:pattern options:options range:range error:nil];
}

- (NSUInteger) numberOfRegexMatches:(nonnull NSString*)pattern
                            options:(NSRegularExpressionOptions)options
{
    return [self numberOfRegexMatches:pattern options:options range:NSMakeRange(0, self.length) error:nil];
}

- (NSUInteger) numberOfRegexMatches:(nonnull NSString*)pattern
{
    return [self numberOfRegexMatches:pattern options:0 range:NSMakeRange(0, self.length) error:nil];
}

/******************************************************************************/
#pragma mark Getting the first match in the receiver
/******************************************************************************/

- (nullable NSTextCheckingResult*) firstRegexMatch:(nonnull NSString*)pattern
                                           options:(NSRegularExpressionOptions)options
                                             range:(NSRange)range
                                             error:(NSErrorPtrPtr)errPtr
{
    MBLogDebugTrace();
    
    NSError* err = nil;
    NSRegularExpression* regex = [MBRegexCache regularExpressionWithPattern:pattern 
                                                                  options:options
                                                                    error:&err];
    if (err) {
        if (errPtr) {
            *errPtr = err;
        } else {
            MBLogError(@"Error attempting to create regular expression: %@", err);
        }
        return nil;
    }
    
    return [regex firstMatchInString:self options:0 range:range];
}

- (nullable NSTextCheckingResult*) firstRegexMatch:(nonnull NSString*)pattern
                                           options:(NSRegularExpressionOptions)options
                                             range:(NSRange)range
{
    return [self firstRegexMatch:pattern options:options range:range error:nil];
}

- (nullable NSTextCheckingResult*) firstRegexMatch:(nonnull NSString*)pattern
                                           options:(NSRegularExpressionOptions)options
{
    return [self firstRegexMatch:pattern options:options range:NSMakeRange(0, self.length) error:nil];
}

- (nullable NSTextCheckingResult*) firstRegexMatch:(nonnull NSString*)pattern
{
    return [self firstRegexMatch:pattern options:0 range:NSMakeRange(0, self.length) error:nil];
}

/******************************************************************************/
#pragma mark Getting the NSRange of the first match in the receiver
/******************************************************************************/

- (NSRange) rangeOfFirstRegexMatch:(nonnull NSString*)pattern
                           options:(NSRegularExpressionOptions)options
                             range:(NSRange)range
                             error:(NSErrorPtrPtr)errPtr
{
    MBLogDebugTrace();
    
    NSError* err = nil;
    NSRegularExpression* regex = [MBRegexCache regularExpressionWithPattern:pattern 
                                                                  options:options
                                                                    error:&err];
    if (err) {
        if (errPtr) {
            *errPtr = err;
        } else {
            MBLogError(@"Error attempting to create regular expression: %@", err);
        }
        return NSMakeRange(NSNotFound, 0);
    }
    
    return [regex rangeOfFirstMatchInString:self options:0 range:range];
}

- (NSRange) rangeOfFirstRegexMatch:(nonnull NSString*)pattern
                           options:(NSRegularExpressionOptions)options
                             range:(NSRange)range
{
    return [self rangeOfFirstRegexMatch:pattern options:options range:range error:nil];
}

- (NSRange) rangeOfFirstRegexMatch:(nonnull NSString*)pattern
                           options:(NSRegularExpressionOptions)options
{
    return [self rangeOfFirstRegexMatch:pattern options:options range:NSMakeRange(0, self.length) error:nil];
}

- (NSRange) rangeOfFirstRegexMatch:(nonnull NSString*)pattern
{
    return [self rangeOfFirstRegexMatch:pattern options:0 range:NSMakeRange(0, self.length) error:nil];
}

/******************************************************************************/
#pragma mark Creating a new string by replacing the matches in the receiver
/******************************************************************************/

- (nullable NSString*) stringByReplacingRegexMatches:(nonnull NSString*)pattern
                                        withTemplate:(nonnull NSString*)templ
                                             options:(NSRegularExpressionOptions)options
                                               range:(NSRange)range
                                               error:(NSErrorPtrPtr)errPtr
{
    MBLogDebugTrace();
    
    NSError* err = nil;
    NSRegularExpression* regex = [MBRegexCache regularExpressionWithPattern:pattern 
                                                                    options:options
                                                                      error:&err];
    if (err) {
        if (errPtr) {
            *errPtr = err;
        } else {
            MBLogError(@"Error attempting to create regular expression: %@", err);
        }
        return nil;
    }
    
    return [regex stringByReplacingMatchesInString:self options:0 range:range withTemplate:templ];
}

- (nullable NSString*) stringByReplacingRegexMatches:(nonnull NSString*)pattern
                                        withTemplate:(nonnull NSString*)templ
                                             options:(NSRegularExpressionOptions)options
                                               range:(NSRange)range
{
    return [self stringByReplacingRegexMatches:pattern withTemplate:templ options:options range:range error:nil];
}

- (nullable NSString*) stringByReplacingRegexMatches:(nonnull NSString*)pattern
                                        withTemplate:(nonnull NSString*)templ
                                             options:(NSRegularExpressionOptions)options
{
    return [self stringByReplacingRegexMatches:pattern withTemplate:templ options:options range:NSMakeRange(0, self.length) error:nil];
}

- (nullable NSString*) stringByReplacingRegexMatches:(nonnull NSString*)pattern
                                        withTemplate:(nonnull NSString*)templ
{
    return [self stringByReplacingRegexMatches:pattern withTemplate:templ options:0 range:NSMakeRange(0, self.length) error:nil];
}

@end
