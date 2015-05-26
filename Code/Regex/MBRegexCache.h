//
//  MBRegexCache.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 11/29/11.
//  Copyright (c) 2011 Gilt Groupe. All rights reserved.
//

#import "MBSingleton.h"
#import "MBThreadsafeCache.h"
#import "NSError+MBToolbox.h"

/******************************************************************************/
#pragma mark -
#pragma mark MBRegexCache class
/******************************************************************************/

/*!
 Regular expressions can be expensive to instantiate, so we implement our
 own thread-safe singleton `MBRegexCache`. The cache is automatically populated
 as you call the methods for getting regular expressions, and it also empties
 itself when memory warnings occur.
 
 You can retrieve `NSRegularExpression` instances from the cache by calling 
 instance methods on the singleton. Or, as a convenience to avoid having 
 to acquire the singleton, you can also get `NSRegularExpression`s by calling
 class-level methods as well. It is more efficient to get the singleton
 instance and call instance-level methods when you expect to do many calls to
 the `MBRegexCache`.
 
 @warning   You *must not* create instances of this class yourself; this class
            is a singleton. Call the `instance` class method (declared by the
            `MBSingleton` protocol) to acquire the singleton instance.
 */
@interface MBRegexCache : MBThreadsafeCache <MBSingleton>

/*----------------------------------------------------------------------------*/
#pragma mark Class-level methods, for convenience
/*!    @name Class-level methods, for convenience                             */
/*----------------------------------------------------------------------------*/

/*!
 Returns an `NSRegularExpression` instance for the given regular 
 expression pattern and options. 
 
 @param     pattern The regular expression pattern
 
 @param     options The `NSRegularExpressionOptions` specifying
            the regular expression options
 
 @param     errPtr If this method returns `nil` and this parameter is non-`nil`,
            `*errPtr` will be updated to point to an `NSError` instance
            containing further information about the error. If `nil` and an
            error occurs, a message will be logged to the console.
 
 @return    A pointer to an `NSRegularExpression` instance, or 
            `nil` if the passed-in pattern could not be interpreted 
            as a valid regular expression.
 */
+ (nullable NSRegularExpression*) regularExpressionWithPattern:(nonnull NSString*)pattern
                                                       options:(NSRegularExpressionOptions)options
                                                         error:(NSErrorPtrPtr)errPtr;

/*!
 Returns an `NSRegularExpression` instance for the given regular 
 expression pattern and options. 
 
 @param     pattern The regular expression pattern
 
 @param     options The `NSRegularExpressionOptions` specifying
            the regular expression options
 
 @return    A pointer to an `NSRegularExpression` instance, or 
            `nil` if the passed-in pattern could not be interpreted 
            as a valid regular expression. If an error occurs causing 
            `nil` to be returned, a message will be logged to the
            console.
 */
+ (nullable NSRegularExpression*) regularExpressionWithPattern:(nonnull NSString*)pattern 
                                                       options:(NSRegularExpressionOptions)options;

/*!
 Returns an `NSRegularExpression` instance for the given regular 
 expression pattern. 
 
 @param     pattern The regular expression pattern
 
 @return    A pointer to an `NSRegularExpression` instance, or 
            `nil` if the passed-in pattern could not be interpreted 
            as a valid regular expression. If an error occurs causing 
            `nil` to be returned, a message will be logged to the
            console.
 */
+ (nullable NSRegularExpression*) regularExpressionWithPattern:(nonnull NSString*)pattern;

/*----------------------------------------------------------------------------*/
#pragma mark Instance-level methods, for efficiency
/*!    @name Instance-level methods, for efficiency                           */
/*----------------------------------------------------------------------------*/

/*!
 Returns an `NSRegularExpression` instance for the given regular 
 expression pattern and options. 
 
 @param     pattern The regular expression pattern

 @param     options The `NSRegularExpressionOptions` specifying
            the regular expression options

 @param     errPtr If this method returns `nil` and this parameter is non-`nil`,
            `*errPtr` will be updated to point to an `NSError` instance
            containing further information about the error. If `nil` and an
            error occurs, a message will be logged to the console.

 @return    A pointer to an `NSRegularExpression` instance, or 
            `nil` if the passed-in pattern could not be interpreted 
            as a valid regular expression.
 */
- (nullable NSRegularExpression*) regularExpressionWithPattern:(nonnull NSString*)pattern
                                                       options:(NSRegularExpressionOptions)options
                                                         error:(NSErrorPtrPtr)errPtr;

/*!
 Returns an `NSRegularExpression` instance for the given regular 
 expression pattern and options. 
 
 @param     pattern The regular expression pattern
 
 @param     options The `NSRegularExpressionOptions` specifying
            the regular expression options
 
 @return    A pointer to an `NSRegularExpression` instance, or 
            `nil` if the passed-in pattern could not be interpreted 
            as a valid regular expression. If an error occurs causing 
            `nil` to be returned, a message will be logged to the
            console.
 */
- (nullable NSRegularExpression*) regularExpressionWithPattern:(nonnull NSString*)pattern 
                                                       options:(NSRegularExpressionOptions)options;

/*!
 Returns an `NSRegularExpression` instance for the given regular 
 expression pattern. 
 
 @param     pattern The regular expression pattern
 
 @return    A pointer to an `NSRegularExpression` instance, or 
            `nil` if the passed-in pattern could not be interpreted 
            as a valid regular expression. If an error occurs causing 
            `nil` to be returned, a message will be logged to the
            console.
 */
- (nullable NSRegularExpression*) regularExpressionWithPattern:(nonnull NSString*)pattern;

@end
