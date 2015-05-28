//
//  MBRoundedRectTools.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 6/28/12.
//  Copyright (c) 2012 Gilt Groupe. All rights reserved.
//

#import "MBRoundedRectTools.h"
#import "MBModuleLogMacros.h"

#define DEBUG_LOCAL         0

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

#define kCornerRadiusMinimum                3
#define kCornerRadiusMaximum                15
#define kCornerRadiusSizeThresholdMaximum   150

/******************************************************************************/
#pragma mark -
#pragma mark MBRoundedRectTools implementation
/******************************************************************************/

@implementation MBRoundedRectTools

/******************************************************************************/
#pragma mark Corner radius utilities
/******************************************************************************/

+ (CGFloat) cornerRadiusSizedForRect:(CGRect)rect
{
    CGFloat sizeForRadiusCalc = MIN(rect.size.width, rect.size.height);
    CGFloat radius = kCornerRadiusMinimum + ((sizeForRadiusCalc / kCornerRadiusSizeThresholdMaximum) * (kCornerRadiusMaximum - kCornerRadiusMinimum));
    return MIN(kCornerRadiusMaximum, radius);
}

+ (CGFloat) adjustCornerRadius:(CGFloat)radius fromRect:(CGRect)rect withInset:(CGFloat)inset
{
    if (inset == 0.0)
        return radius;
    
    if (radius <= 0.0)
        return radius;
    
    CGFloat size = MIN(rect.size.width, rect.size.height);
    if (size <= 0.0)
        return radius;
    
    CGFloat newSize = size - (inset * 2);
    
    CGFloat radiusPctOfSize = radius / size;
    CGFloat newRadius = radiusPctOfSize * newSize;
    
    return newRadius;
}

+ (CGFloat) adjustCornerRadius:(CGFloat)radius fromRect:(CGRect)fromRect toRect:(CGRect)toRect
{
    CGFloat diff = MIN(fromRect.size.width, fromRect.size.height) - MIN(toRect.size.width, toRect.size.height);
    
    return [self adjustCornerRadius:radius fromRect:fromRect withInset:(diff / 2)];
}

/******************************************************************************/
#pragma mark Rounded rectangle creation
/******************************************************************************/

+ (nonnull CGPathRef) newRoundedPathForRectangle:(CGRect)rect withRadius:(CGFloat)radius 
{
    return [self newRoundedPathForRectangle:rect withRadius:radius forStrokeWidth:0.0];
}

+ (nonnull CGPathRef) newRoundedPathForRectangle:(CGRect)rect withRadius:(CGFloat)radius forStrokeWidth:(CGFloat)width
{
    return [self newRoundedPathForRectangle:rect withRadius:radius insetBy:(width/2)];
}

+ (nonnull CGPathRef) newRoundedPathForRectangle:(CGRect)rect withRadius:(CGFloat)radius insetBy:(CGFloat)inset
{
    MBLogDebugTrace();
    
    if (inset) {
        rect = CGRectInset(rect, inset, inset);
    }
    
    CGMutablePathRef path = CGPathCreateMutable();
    
    CGPathMoveToPoint(path, NULL, CGRectGetMidX(rect), CGRectGetMinY(rect));
    CGPathAddArcToPoint(path, NULL, CGRectGetMaxX(rect), CGRectGetMinY(rect), CGRectGetMaxX(rect), CGRectGetMaxY(rect), radius);
    CGPathAddArcToPoint(path, NULL, CGRectGetMaxX(rect), CGRectGetMaxY(rect), CGRectGetMinX(rect), CGRectGetMaxY(rect), radius);
    CGPathAddArcToPoint(path, NULL, CGRectGetMinX(rect), CGRectGetMaxY(rect), CGRectGetMinX(rect), CGRectGetMinY(rect), radius);
    CGPathAddArcToPoint(path, NULL, CGRectGetMinX(rect), CGRectGetMinY(rect), CGRectGetMaxX(rect), CGRectGetMinY(rect), radius);
    CGPathCloseSubpath(path);
    
    return path;                // ignore static analyzer complaint
}

@end
