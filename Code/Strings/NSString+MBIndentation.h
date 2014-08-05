//
//  NSString+MBIndentation.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 9/4/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "Mockingbird-Toolbox.h"

/******************************************************************************/
#pragma mark -
#pragma mark NSString class additions
/******************************************************************************/

/*!
 An `NSString` class extension that provides methods for indenting 
 individual lines within a string.
 */
@interface NSString (MBIndentation)

/*----------------------------------------------------------------------------*/
#pragma mark Indenting lines within a string
/*!    @name Indenting lines within a string                                  */
/*----------------------------------------------------------------------------*/

/*!
 Creates a new string by prefixing each line in the receiver with the tab
 (`0x09`) character.

 @return    The indented string.
 */
- (NSString*) stringByIndentingEachLineWithTab;

/*!
 Creates a new string by prefixing each line in the receiver with the 
 specified number of tab (`0x09`) characters.

 @param     numberOfTabs The number of tab characters to use for intenting
            lines.

 @return    The indented string.
 */
- (NSString*) stringByIndentingEachLineWithTabs:(NSUInteger)numberOfTabs;

/*!
 Creates a new string by prefixing each line in the receiver with the given
 string.

 @param     prefix The prefix to use for indenting lines.
 
 @return    The indented string.
 */
- (NSString*) stringByIndentingEachLineWithPrefix:(NSString*)prefix;

@end
