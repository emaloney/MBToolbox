//
//  NSString+MBRegex.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 11/29/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSError+MBToolbox.h"

/******************************************************************************/
#pragma mark -
#pragma mark NSMutableString regular expression category
/******************************************************************************/

/*!
 An `NSMutableString` class extension that provides regular expression
 replacement methods.
 
 To improve performance, these methods utilize the `MBRegexCache` when
 possible.

 For additional information on the workings of regular expressions, see the
 Apple documentation for `NSRegularExpression`.
 */
@interface NSMutableString (MBRegex)

/*----------------------------------------------------------------------------*/
#pragma mark Performing regex replacements in a mutable string
/*!    @name Performing regex replacements in a mutable string                */
/*----------------------------------------------------------------------------*/

/*!
 Performs a regular expression string replacement on the receiver.
 
 If the receiver contains any matches for the specified regular expression
 pattern, the receiver will be modified so that those matches are replaced
 according to the template provided.
 
 @param     pattern The regular expression pattern to match.
 
 @param     templ The template to use for performing replacements of any 
            matches found in the receiver.
 
 @return    The number of matches performed.
 */
- (NSUInteger) replaceRegexMatches:(nonnull NSString*)pattern
                      withTemplate:(nonnull NSString*)templ;

/*!
 Performs a regular expression string replacement on the receiver.
 
 If the receiver contains any matches for the specified regular expression
 pattern, the receiver will be modified so that those matches are replaced
 according to the template provided.
 
 @param     pattern The regular expression pattern to match.
 
 @param     templ The template to use for performing replacements of any 
            matches found in the receiver.

 @param     options The options that govern the behavior of the returned
            regular expression.

 @return    The number of matches performed.
 */
- (NSUInteger) replaceRegexMatches:(nonnull NSString*)pattern
                      withTemplate:(nonnull NSString*)templ
                           options:(NSRegularExpressionOptions)options;

/*!
 Performs a regular expression string replacement on the receiver.
 
 If the receiver contains any matches for the specified regular expression
 pattern, the receiver will be modified so that those matches are replaced
 according to the template provided.
 
 Matching is constrained to the given range within the receiver.

 @param     pattern The regular expression pattern to match.
 
 @param     templ The template to use for performing replacements of any 
            matches found in the receiver.

 @param     options The options that govern the behavior of the returned
            regular expression.

 @param     range The range of characters in the receiver within which matching
            will occur. Characters outside this range will not be affected.

 @return    The number of matches performed.
 */
- (NSUInteger) replaceRegexMatches:(nonnull NSString*)pattern
                      withTemplate:(nonnull NSString*)templ
                           options:(NSRegularExpressionOptions)options
                             range:(NSRange)range;

/*!
 Performs a regular expression string replacement on the receiver.
 
 If the receiver contains any matches for the specified regular expression
 pattern, the receiver will be modified so that those matches are replaced
 according to the template provided.
 
 Matching is constrained to the given range within the receiver.

 @param     pattern The regular expression pattern to match.
 
 @param     templ The template to use for performing replacements of any 
            matches found in the receiver.

 @param     options The options that govern the behavior of the returned
            regular expression.

 @param     range The range of characters in the receiver within which matching
            will occur. Characters outside this range will not be affected.

 @param     errPtr An optional pointer to storage for an `NSError` instance.
            If this parameter is non-`nil` and an error occurs, `*errPtr`
            will be updated to point to an `NSError` describing the problem.

 @return    The number of matches performed.
 */
- (NSUInteger) replaceRegexMatches:(nonnull NSString*)pattern
                      withTemplate:(nonnull NSString*)templ
                           options:(NSRegularExpressionOptions)options
                             range:(NSRange)range
                             error:(NSErrorPtrPtr)errPtr;
@end

/******************************************************************************/
#pragma mark -
#pragma mark NSString regular expression category
/******************************************************************************/

/*!
 An `NSString` class extension that provides various methods for creating
 and utilizing regular expressions.
 
 To improve performance, these methods utilize the `MBRegexCache` when
 possible.

 For additional information on the workings of regular expressions, see the
 Apple documentation for `NSRegularExpression`.
 */
@interface NSString (MBRegex)

/*----------------------------------------------------------------------------*/
#pragma mark Creating regular expressions
/*!    @name Creating regular expressions                                     */
/*----------------------------------------------------------------------------*/

/*!
 Returns an `NSRegularExpression` instance by treating the receiver as a
 regular expression pattern string.

 @return    The regular expression, or `nil` if the receiver could not be
            interpreted as a valid regular expression.
 */
- (nullable NSRegularExpression*) regularExpression;

/*!
 Returns an `NSRegularExpression` instance by treating the receiver as a
 regular expression pattern string.

 @param     options The options that govern the behavior of the returned
            regular expression.

 @return    The regular expression, or `nil` if the receiver could not be
            interpreted as a valid regular expression.
 */
- (nullable NSRegularExpression*) regularExpressionWithOptions:(NSRegularExpressionOptions)options;

/*!
 Returns an `NSRegularExpression` instance by treating the receiver as a
 regular expression pattern string.

 @param     options The options that govern the behavior of the returned
            regular expression.
 
 @param     errPtr An optional pointer to storage for an `NSError` instance.
            If this parameter is non-`nil` and an error occurs, `*errPtr`
            will be updated to point to an `NSError` describing the problem.

 @return    The regular expression, or `nil` if the receiver could not be
            interpreted as a valid regular expression.
 */
- (nullable NSRegularExpression*) regularExpressionWithOptions:(NSRegularExpressionOptions)options
                                                         error:(NSErrorPtrPtr)errPtr;

/*----------------------------------------------------------------------------*/
#pragma mark Escaping
/*!    @name Escaping                                                         */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new regular expression pattern string by escaping metacharacters
 contained in the receiver.

 Affected characters are escaped by prefixing them with backslashes.
 
 @return    The escaped pattern string.
 */
- (nonnull NSString*) escapedRegexPattern;

/*!
 Creates a new regular expression template string by escaping metacharacters
 contained in the receiver.
 
 Affected characters are escaped by prefixing them with backslashes.
 
 @return    The escaped template string.
 */
- (nonnull NSString*) escapedRegexTemplate;

/*----------------------------------------------------------------------------*/
#pragma mark Finding all pattern matches
/*!    @name Finding all pattern matches                                      */
/*----------------------------------------------------------------------------*/

/*!
 Matches the specified regular expression against the receiver.

 @param     pattern The regular expression pattern to match.
 
 @return    An array of `NSTextCheckingResult` objects representing the regular
            expression pattern matches found within the receiver, or `nil`
            if an error occurred.
 */
- (nullable NSArray*) matchesWithRegex:(nonnull NSString*)pattern;

/*!
 Matches the specified regular expression against the receiver.

 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @return    An array of `NSTextCheckingResult` objects representing the regular
            expression pattern matches found within the receiver, or `nil`
            if an error occurred.
 */
- (nullable NSArray*) matchesWithRegex:(nonnull NSString*)pattern
                               options:(NSRegularExpressionOptions)options;

/*!
 Matches the specified regular expression against the receiver.

 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @return    An array of `NSTextCheckingResult` objects representing the regular
            expression pattern matches found within the receiver, or `nil`
            if an error occurred.
 */
- (nullable NSArray*) matchesWithRegex:(nonnull NSString*)pattern
                               options:(NSRegularExpressionOptions)options
                                 range:(NSRange)range;

/*!
 Matches the specified regular expression against the receiver.

 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @param     errPtr An optional pointer to storage for an `NSError` instance.
            If this parameter is non-`nil` and an error occurs, `*errPtr`
            will be updated to point to an `NSError` describing the problem.

 @return    An array of `NSTextCheckingResult` objects representing the regular
            expression pattern matches found within the receiver, or `nil`
            if an error occurred.
 */
- (nullable NSArray*) matchesWithRegex:(nonnull NSString*)pattern
                               options:(NSRegularExpressionOptions)options
                                 range:(NSRange)range
                                 error:(NSErrorPtrPtr)errPtr;

/*----------------------------------------------------------------------------*/
#pragma mark Testing for pattern matches
/*!    @name Testing for pattern matches                                      */
/*----------------------------------------------------------------------------*/

/*!
 Determines if the receiver contains at least one match of the given
 regular expression pattern.

 @param     pattern The regular expression pattern to match.

 @return    `YES` if the receiver contained at least one match of `pattern`;
            `NO` if there were no matches.
 */
- (BOOL) isMatchedByRegex:(nonnull NSString*)pattern;

/*!
 Determines if the receiver contains at least one match of the given
 regular expression pattern.

 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @return    `YES` if the receiver contained at least one match of `pattern`;
            `NO` if there were no matches.
 */
- (BOOL) isMatchedByRegex:(nonnull NSString*)pattern
                  options:(NSRegularExpressionOptions)options;

/*!
 Determines if the receiver contains at least one match of the given
 regular expression pattern within the specified range.

 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @return    `YES` if the receiver contained at least one match of `pattern`;
            `NO` if there were no matches.
 */
- (BOOL) isMatchedByRegex:(nonnull NSString*)pattern
                  options:(NSRegularExpressionOptions)options
                    range:(NSRange)range;

/*!
 Determines if the receiver contains at least one match of the given
 regular expression pattern within the specified range.

 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @param     errPtr An optional pointer to storage for an `NSError` instance.
            If this parameter is non-`nil` and an error occurs, `*errPtr`
            will be updated to point to an `NSError` describing the problem.

 @return    `YES` if the receiver contained at least one match of `pattern`;
            `NO` if there were no matches.
 */
- (BOOL) isMatchedByRegex:(nonnull NSString*)pattern
                  options:(NSRegularExpressionOptions)options
                    range:(NSRange)range
                    error:(NSErrorPtrPtr)errPtr;

/*----------------------------------------------------------------------------*/
#pragma mark Counting pattern matches
/*!    @name Counting pattern matches                                         */
/*----------------------------------------------------------------------------*/

/*!
 Returns the number of matches found in the receiver of the given regular
 expression pattern.
 
 @param     pattern The regular expression pattern to match.
 
 @return    The number of matches.
 */
- (NSUInteger) numberOfRegexMatches:(nonnull NSString*)pattern;

/*!
 Returns the number of matches found in the receiver of the given regular
 expression pattern.
 
 @param     pattern The regular expression pattern to match.

 @param     options The regular expression options that govern how matching
            will occur.

 @return    The number of matches.
 */
- (NSUInteger) numberOfRegexMatches:(nonnull NSString*)pattern
                            options:(NSRegularExpressionOptions)options;

/*!
 Returns the number of matches found in the receiver of the given regular
 expression pattern.
 
 @param     pattern The regular expression pattern to match.

 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @return    The number of matches.
 */
- (NSUInteger) numberOfRegexMatches:(nonnull NSString*)pattern
                            options:(NSRegularExpressionOptions)options
                              range:(NSRange)range;

/*!
 Returns the number of matches found in the receiver of the given regular
 expression pattern.
 
 @param     pattern The regular expression pattern to match.

 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @param     errPtr An optional pointer to storage for an `NSError` instance.
            If this parameter is non-`nil` and an error occurs, `*errPtr`
            will be updated to point to an `NSError` describing the problem.

 @return    The number of matches.
 */
- (NSUInteger) numberOfRegexMatches:(nonnull NSString*)pattern
                            options:(NSRegularExpressionOptions)options
                              range:(NSRange)range
                              error:(NSErrorPtrPtr)errPtr;

/*----------------------------------------------------------------------------*/
#pragma mark Finding the first pattern match
/*!    @name Finding the first pattern match                                  */
/*----------------------------------------------------------------------------*/

/*!
 Returns the first occurrence of the specified regular expression pattern
 found within the receiver.
 
 @param     pattern The regular expression pattern to match.
 
 @return    An `NSTextCheckingResult` instance containing the results of the
            match, or `nil` if an error occurred.
 */
- (nullable NSTextCheckingResult*) firstRegexMatch:(nonnull NSString*)pattern;

/*!
 Returns the first occurrence of the specified regular expression pattern
 found within the receiver.
 
 @param     pattern The regular expression pattern to match.

 @param     options The regular expression options that govern how matching
            will occur.

 @return    An `NSTextCheckingResult` instance containing the results of the
            match, or `nil` if an error occurred.
 */
- (nullable NSTextCheckingResult*) firstRegexMatch:(nonnull NSString*)pattern
                                           options:(NSRegularExpressionOptions)options;

/*!
 Returns the first occurrence of the specified regular expression pattern
 found within the receiver.
 
 @param     pattern The regular expression pattern to match.

 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @return    An `NSTextCheckingResult` instance containing the results of the
            match, or `nil` if an error occurred.
 */
- (nullable NSTextCheckingResult*) firstRegexMatch:(nonnull NSString*)pattern
                                           options:(NSRegularExpressionOptions)options
                                             range:(NSRange)range;

/*!
 Returns the first occurrence of the specified regular expression pattern
 found within the receiver.
 
 @param     pattern The regular expression pattern to match.

 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @param     errPtr An optional pointer to storage for an `NSError` instance.
            If this parameter is non-`nil` and an error occurs, `*errPtr`
            will be updated to point to an `NSError` describing the problem.

 @return    An `NSTextCheckingResult` instance containing the results of the
            match, or `nil` if an error occurred.
 */
- (nullable NSTextCheckingResult*) firstRegexMatch:(nonnull NSString*)pattern
                                           options:(NSRegularExpressionOptions)options
                                             range:(NSRange)range
                                             error:(NSErrorPtrPtr)errPtr;

/*----------------------------------------------------------------------------*/
#pragma mark Getting the range of the first pattern match
/*!    @name Getting the range of the first pattern match                     */
/*----------------------------------------------------------------------------*/

/*!
 Determines the range of the first match of the given regular expression within
 the receiver.
 
 @param     pattern The regular expression pattern to match.
 
 @return    The range of the first match. Will be {`NSNotFound`, `0`} if there
            is no match.
 */
- (NSRange) rangeOfFirstRegexMatch:(nonnull NSString*)pattern;

/*!
 Determines the range of the first match of the given regular expression within
 the receiver.
 
 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @return    The range of the first match. Will be {`NSNotFound`, `0`} if there
            is no match.
 */
- (NSRange) rangeOfFirstRegexMatch:(nonnull NSString*)pattern
                           options:(NSRegularExpressionOptions)options;

/*!
 Determines the range of the first match of the given regular expression within
 the receiver.
 
 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @return    The range of the first match. Will be {`NSNotFound`, `0`} if there
            is no match.
 */
- (NSRange) rangeOfFirstRegexMatch:(nonnull NSString*)pattern
                           options:(NSRegularExpressionOptions)options
                             range:(NSRange)range;

/*!
 Determines the range of the first match of the given regular expression within
 the receiver.
 
 @param     pattern The regular expression pattern to match.
 
 @param     options The regular expression options that govern how matching
            will occur.

 @param     range The range of characters in the receiver within which matching
            will occur.

 @param     errPtr An optional pointer to storage for an `NSError` instance.
            If this parameter is non-`nil` and an error occurs, `*errPtr`
            will be updated to point to an `NSError` describing the problem.

 @return    The range of the first match. Will be {`NSNotFound`, `0`} if there
            is no match.
 */
- (NSRange) rangeOfFirstRegexMatch:(nonnull NSString*)pattern
                           options:(NSRegularExpressionOptions)options
                             range:(NSRange)range
                             error:(NSErrorPtrPtr)errPtr;

/*----------------------------------------------------------------------------*/
#pragma mark Creating a new string by replacing pattern matches
/*!    @name Creating a new string by replacing pattern matches               */
/*----------------------------------------------------------------------------*/

/*!
 Returns a new string by replacing each match of the specified regular 
 expression pattern with the replacement template provided.

 @param     pattern The regular expression pattern to match.
 
 @param     templ The template to use for replacing the regular expression
            matches.
 
 @return    The resulting string, or `nil` if an error occurred.
 */
- (nullable NSString*) stringByReplacingRegexMatches:(nonnull NSString*)pattern
                                        withTemplate:(nonnull NSString*)templ;

/*!
 Returns a new string by replacing each match of the specified regular 
 expression pattern with the replacement template provided.

 @param     pattern The regular expression pattern to match.
 
 @param     templ The template to use for replacing the regular expression
            matches.
 
 @param     options The regular expression options that govern how matching
            will occur.
 
 @return    The resulting string, or `nil` if an error occurred.
 */
- (nullable NSString*) stringByReplacingRegexMatches:(nonnull NSString*)pattern
                                        withTemplate:(nonnull NSString*)templ
                                             options:(NSRegularExpressionOptions)options;

/*!
 Returns a new string by replacing each match of the specified regular 
 expression pattern with the replacement template provided.
 
 Matching is constrained to the given range within the receiver.

 @param     pattern The regular expression pattern to match.
 
 @param     templ The template to use for replacing the regular expression
            matches.
 
 @param     options The regular expression options that govern how matching
            will occur.
 
 @param     range The range of characters in the receiver within which matching
            will occur.

 @return    The resulting string, or `nil` if an error occurred.
 */
- (nullable NSString*) stringByReplacingRegexMatches:(nonnull NSString*)pattern
                                        withTemplate:(nonnull NSString*)templ
                                             options:(NSRegularExpressionOptions)options
                                               range:(NSRange)range;

/*!
 Returns a new string by replacing each match of the specified regular 
 expression pattern with the replacement template provided.
 
 Matching is constrained to the given range within the receiver.

 @param     pattern The regular expression pattern to match.
 
 @param     templ The template to use for replacing the regular expression
            matches.
 
 @param     options The regular expression options that govern how matching
            will occur.
 
 @param     range The range of characters in the receiver within which matching
            will occur.

 @param     errPtr An optional pointer to storage for an `NSError` instance.
            If this parameter is non-`nil` and an error occurs, `*errPtr`
            will be updated to point to an `NSError` describing the problem.

 @return    The resulting string, or `nil` if an error occurred.
 */
- (nullable NSString*) stringByReplacingRegexMatches:(nonnull NSString*)pattern
                                        withTemplate:(nonnull NSString*)templ
                                             options:(NSRegularExpressionOptions)options
                                               range:(NSRange)range
                                               error:(NSErrorPtrPtr)errPtr;

@end
