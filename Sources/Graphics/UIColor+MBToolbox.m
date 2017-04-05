//
//  UIColor+MBToolbox.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/28/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "UIColor+MBToolbox.h"

#if MB_BUILD_UIKIT

#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL         0

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

const CGFloat kHiliteColorBrightnessAdjust = 0.35;

/******************************************************************************/
#pragma -
#pragma mark UIColor class additions
/******************************************************************************/

@implementation UIColor (MBToolbox)

- (BOOL) isOpaque
{
    CGFloat alpha = 1.0;
    [self getRed:nil green:nil blue:nil alpha:&alpha];
    return (alpha == 1.0);
}

- (BOOL) isDark
{
    CGFloat brightness = 0.0;
    [self getHue:nil saturation:nil brightness:&brightness alpha:nil];
    return brightness < 0.5;
}

- (nonnull UIColor*) highlightColor
{
    MBLogDebugTrace();
    
    CGFloat h, s, b, a;
    [self getHue:&h saturation:&s brightness:&b alpha:&a];
    b += (b < 0.5 ? kHiliteColorBrightnessAdjust : -kHiliteColorBrightnessAdjust);
    
    return [UIColor colorWithHue:h saturation:s brightness:b alpha:a];
}

- (nonnull UIColor*) colorWithBrightnessAdjustedByFactor:(CGFloat)adjustFactor
{
    MBLogDebugTrace();
    
    if (adjustFactor == 1.0)
        return self;
    
    CGFloat h, s, b, a;
    [self getHue:&h saturation:&s brightness:&b alpha:&a];
    b *= adjustFactor;
    
    return [UIColor colorWithHue:h saturation:s brightness:b alpha:a];
}

@end

#endif
