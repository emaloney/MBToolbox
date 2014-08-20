//
//  MBFieldListFormatter.m
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 3/20/14.
//  Copyright (c) 2014 Gilt Groupe. All rights reserved.
//

#import "MBFieldListFormatter.h"

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
- (NSString*) debugDescriptor;
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

+ (instancetype) formatterForObject:(id)obj
{
    MBFieldListFormatter* fields = [self new];

    [fields setField:[[obj class] description]
               value:[NSString stringWithFormat:@"%p", obj]];

    return fields;
}

- (id) init
{
    self = [super init];
    if (self) {
        _fieldsToValues = [NSMutableDictionary new];
        _fieldOrder = [NSMutableArray new];
    }
    return self;
}

- (void) setField:(NSString*)fieldName value:(id)val
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

- (void) setField:(NSString*)fieldName byTruncating:(NSString*)val
{
    [self setField:fieldName
      byTruncating:val
       atCharacter:kMBFieldListDefaultTruncateAtCharacter];
}

+ (NSString*) truncateString:(NSString*)val atCharacter:(NSUInteger)truncateAt
{
    if (val) {
        NSUInteger len = val.length;
        if (len > truncateAt) {
            return [NSString stringWithFormat:@"%@... (%u more chars)", [val substringToIndex:truncateAt], (unsigned int)(len - truncateAt)];
        }
    }
    return val;
}

- (void) setField:(NSString*)fieldName byTruncating:(NSString*)val atCharacter:(NSUInteger)truncateAt
{
    MBArgNonNil(fieldName);

    [self setField:fieldName value:[[self class] truncateString:val atCharacter:truncateAt]];
}

- (void) setField:(NSString*)fieldName instance:(id)obj
{
    if (obj) {
        [self setField:fieldName
                 value:[NSString stringWithFormat:@"<%@: %p>", [obj class], obj]];
    }
}

- (void) setField:(NSString*)fieldName debug:(id)obj
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

- (void) setField:(NSString*)fieldName pointer:(void*)ptr
{
    if (ptr) {
        [self setField:fieldName
                 value:[NSString stringWithFormat:@"<(void*): %p>", ptr]];
    }
}

- (void) setField:(NSString*)fieldName boolean:(BOOL)val
{
    [self setField:fieldName value:(val ? @"YES" : @"NO")];
}

- (void) setField:(NSString*)fieldName container:(id)container
{
    if (container) {
        MBExpect([container respondsToSelector:@selector(count)]);

        NSUInteger count = [container count];
        [self setField:fieldName
                 value:[NSString stringWithFormat:@"<%@: %p; %lu entr%s>", [container class], container, (unsigned long)count, (count == 1 ? "y" : "ies")]];
    }
}

- (void) setFields:(NSDictionary*)fields
{
    MBArgNonNil(fields);

    for (NSString* key in fields) {
        [self setField:key value:fields[key]];
    }
}

- (NSString*) asString
{
    return [self asStringWithIndentation:@""];
}

- (NSString*) asStringWithIndentation:(NSString*)indentation
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

- (NSString*) asStringWithIndentation
{
    return [self asStringWithIndentation:@"\t"];
}

- (NSString*) asDescription
{
    return [NSString stringWithFormat:@"\n\n%@\n", [self asStringWithIndentation]];
}

- (NSString*) description
{
    NSMutableString* desc = [NSMutableString stringWithFormat:@"<%@: %p;\n", [self class], self];
    [desc appendString:[self asStringWithIndentation:@"\t"]];
    [desc appendFormat:@">"];
    return desc;
}

@end
