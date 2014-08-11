//
//  MBStringFunctions.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 7/24/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

/******************************************************************************/
#pragma mark -
#pragma mark Mockingbird string functions
/******************************************************************************/

//!< given any object, outputs a string; nil or NSNull yields empty strings
static inline NSString* MBForceString(id x)
{
    NSString* retVal = @"";
    if (x && x != [NSNull null]) {
        NSString* desc = [x description];
        if (desc) {
            retVal = desc;
        }
    }
    return retVal;
}

//!< given any object, forces it to a string and trims whitespace from the ends
static inline NSString* MBTrimString(id x)
{
    NSString* retVal = MBForceString(x);
    if (retVal.length > 0) {
        retVal = [retVal stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    }
    return retVal;
}

/******************************************************************************/
#pragma mark Stringification
/******************************************************************************/

// create compile-time string objects
#define MBStringify(x)  [NSString stringWithFormat:@"%s", #x]
