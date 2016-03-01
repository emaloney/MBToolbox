//
//  MBAssert.h
//  Mockingbird Toolbox
//
//  Created by Evan Coyne Maloney on 9/1/10.
//  Copyright (c) 2010 Gilt Groupe. All rights reserved.
//

/******************************************************************************/
#pragma mark Preconditions & argument validation
/******************************************************************************/

#define MBArgNonNil(x)              { if (!(x)) { [[NSException exceptionWithName:@"Argument must not be nil" reason:[NSString stringWithFormat:@"The argument variable '%s' was nil, but it must not be. (%@:%u)", #x, [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__] userInfo:nil] raise]; } }

#define MBExpect(x)                 { if (!(x)) { [[NSException exceptionWithName:@"Expectation not satisfied" reason:[NSString stringWithFormat:@"The expectation '%s' was false; it must be true. (%@:%u)", #x, [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__] userInfo:nil] raise]; } }

/******************************************************************************/
#pragma mark Unimplemented code exceptions
/******************************************************************************/

#define MBErrorNotImplemented()           {[[NSException exceptionWithName:@"Not Implemented" reason:[NSString stringWithFormat:@"An unimplemented interface was called: %s", __PRETTY_FUNCTION__] userInfo:@{@"file": [NSString stringWithUTF8String:__FILE__], @"line": @(__LINE__)}] raise];}

#define MBErrorNotImplementedReturn(x)    {MBErrorNotImplemented(); return ((x)0);}
