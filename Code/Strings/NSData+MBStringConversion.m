//
//  NSData+MBStringConversion.m
//  Mockingbird Toolbox
//
//  Created by Jesse Boyes on 8/16/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

#import "MBDebug.h"
#import "NSData+MBStringConversion.h"

#define DEBUG_LOCAL     0

/******************************************************************************/
#pragma mark -
#pragma mark NSData extensions for string conversion
/******************************************************************************/

@implementation NSData (MBStringConversion)

+ (NSData*) dataWithHexString:(NSString*) hexString
{
    debugTrace();

    NSData *data;
    if (hexString) {
        const char *inputBytes = [hexString cStringUsingEncoding:NSASCIIStringEncoding];
        if (inputBytes) {
            size_t bytesLength = sizeof(char) * (strlen(inputBytes) / 2);
            char *buf = malloc(bytesLength);    // buffer to place the output data

            for (int i = 0; i < bytesLength; i++, inputBytes+=2) {
                sscanf(inputBytes, "%2hhx", buf+i);
            }

            // We could use NSMutableData and -[appendBytes] for this method, but it
            // is a bit slower and not much less code.
            data = [NSData dataWithBytes:buf length:bytesLength];
            free(buf);
        } else {
            data = [NSData data];
        }
    }
    return data;
}

- (NSString*) hexString
{
    debugTrace();

    const unsigned char *input = [self bytes];
    long buflen = [self length] * 2;                // Each char is 1b or 0-255 which is hex '00'-'FF'
    char *buf = malloc(sizeof(char) * buflen + 1);  // buffer to place the output string
    buf[sizeof(char) * buflen] = '\0';
    char *stop = buf + buflen;                      // end marker (last index + 1)

    for (char *cur = buf; cur < stop; cur+=2, input++) {
        sprintf(cur, "%02x", *input);
    }

    // We could use NSMutableString and -[appendFormat] for this method, but it
    // is twice as slow on armv7
    NSString *string = [NSString stringWithCString:buf encoding:NSASCIIStringEncoding];
    free(buf);
    return string;
}

- (NSString*) toStringUsingEncoding:(NSStringEncoding)encoding
{
    debugTrace();
    
    return [[NSString alloc] initWithData:self encoding:encoding];
}

- (NSString*) toStringASCII
{
    return [self toStringUsingEncoding:NSASCIIStringEncoding];
}

- (NSString*) toStringUTF8
{
    return [self toStringUsingEncoding:NSUTF8StringEncoding];
}

- (NSString*) toString
{
    return [self toStringUsingEncoding:NSUTF8StringEncoding];
}

@end

