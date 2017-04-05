//
//  MBFieldListFormatter.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 3/20/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBFieldListFormatter.h"
#import "MBAssert.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark Constants
/******************************************************************************/

const NSUInteger kMBFieldListDefaultTruncateAtCharacter    = 70;

/******************************************************************************/
#pragma mark -
#pragma mark MBFieldListFormatterDebugDescriptor protocol
/******************************************************************************/

// declaration needed to get our reference to it in setField:debug: to compile
// without ugly #pragmas or a dependency on MBFormattedDescriptionObject
@protocol MBFieldListFormatterDebugDescriptor <NSObject>
- (nonnull NSString*) debugDescriptor;
@end

/******************************************************************************/
#pragma mark -
#pragma mark MBFieldListFormatter implementation
/******************************************************************************/

@implementation MBFieldListFormatter
{
    NSMutableDictionary* _fieldsToValues;
    NSMutableArray* _fieldOrder;
    NSUInteger _longestFieldName;
}

+ (nonnull instancetype) formatterForObject:(nonnull id)obj
{
    MBFieldListFormatter* fields = [self new];

    [fields setField:[[obj class] description]
               value:[NSString stringWithFormat:@"%p", obj]];

    return fields;
}

- (nonnull instancetype) init
{
    self = [super init];
    if (self) {
        _fieldsToValues = [NSMutableDictionary new];
        _fieldOrder = [NSMutableArray new];
    }
    return self;
}

- (void) setField:(nonnull NSString*)fieldName value:(nullable id)val
{
    MBArgNonNil(fieldName);

    if (val) {
        fieldName = [fieldName copy];
        _longestFieldName = MAX(_longestFieldName, fieldName.length);
        _fieldsToValues[fieldName] = [val description];
        if (![_fieldOrder containsObject:fieldName]) {
            [_fieldOrder addObject:fieldName];
        }
    }
}

- (void) setField:(nonnull NSString*)fieldName byTruncating:(nonnull NSString*)val
{
    [self setField:fieldName
      byTruncating:val
       atCharacter:kMBFieldListDefaultTruncateAtCharacter];
}

+ (nonnull NSString*) truncateString:(nonnull NSString*)val atCharacter:(NSUInteger)truncateAt
{
    if (val) {
        NSUInteger len = val.length;
        if (len > truncateAt) {
            return [NSString stringWithFormat:@"%@... (%u more chars)", [val substringToIndex:truncateAt], (unsigned int)(len - truncateAt)];
        }
    }
    return val;
}

- (void) setField:(nonnull NSString*)fieldName
     byTruncating:(nonnull NSString*)val
      atCharacter:(NSUInteger)truncateAt
{
    MBArgNonNil(fieldName);

    [self setField:fieldName value:[[self class] truncateString:val atCharacter:truncateAt]];
}

- (void) setField:(nonnull NSString*)fieldName instance:(nullable id)obj
{
    if (obj) {
        [self setField:fieldName
                 value:[NSString stringWithFormat:@"<%@: %p>", [obj class], obj]];
    }
}

- (void) setField:(nonnull NSString*)fieldName debug:(nullable id)obj
{
    if (obj) {
        NSString* debug = nil;
        if ([obj respondsToSelector:@selector(debugDescriptor)]) {
            debug = [obj debugDescriptor];
        }

        if (debug) {
            [self setField:fieldName
                     value:[NSString stringWithFormat:@"<%@: %p> — %@", [obj class], obj, debug]];
        }
        else {
            [self setField:fieldName
                     value:[NSString stringWithFormat:@"<%@: %p>", [obj class], obj]];
        }
    }
}

- (void) setField:(nonnull NSString*)fieldName pointer:(nullable void*)ptr
{
    if (ptr) {
        [self setField:fieldName
                 value:[NSString stringWithFormat:@"<(void*): %p>", ptr]];
    }
    else {
        [self setField:fieldName
                 value:@"<(void*): NULL>"];
    }
}

- (void) setField:(nonnull NSString*)fieldName boolean:(BOOL)val
{
    [self setField:fieldName value:(val ? @"YES" : @"NO")];
}

- (void) setField:(nonnull NSString*)fieldName container:(nullable id)val
{
    if (val) {
        MBExpect([val respondsToSelector:@selector(count)]);

        NSUInteger count = [val count];
        [self setField:fieldName
                 value:[NSString stringWithFormat:@"<%@: %p; %lu entr%s>", [val class], val, (unsigned long)count, (count == 1 ? "y" : "ies")]];
    }
}

- (void) setFields:(nonnull NSDictionary*)fields
{
    MBArgNonNil(fields);

    for (NSString* key in fields) {
        [self setField:key value:fields[key]];
    }
}

- (nonnull NSString*) asString
{
    return [self asStringWithIndentation:@""];
}

- (nonnull NSString*) asStringWithIndentation:(NSString*)indentation
{
    MBArgNonNil(indentation);

    NSMutableString* string = [NSMutableString new];
    for (NSString* field in _fieldOrder) {
        NSUInteger padLen = _longestFieldName - field.length;
        NSString* padding = [@"" stringByPaddingToLength:padLen
                                              withString:@" "
                                         startingAtIndex:0];

        [string appendFormat:@"%@%@%@: %@\n", indentation, padding, field, _fieldsToValues[field]];
    }
    return string;
}

- (nonnull NSString*) asStringWithIndentation
{
    return [self asStringWithIndentation:@"\t"];
}

- (nonnull NSString*) asDescription
{
    return [NSString stringWithFormat:@"\n\n%@\n", [self asStringWithIndentation]];
}

- (nonnull NSString*) description
{
    NSMutableString* desc = [NSMutableString stringWithFormat:@"<%@: %p;\n", [self class], self];
    [desc appendString:[self asStringWithIndentation:@"\t"]];
    [desc appendFormat:@">"];
    return desc;
}

@end
