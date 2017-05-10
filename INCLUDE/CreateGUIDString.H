#if !defined ( _CREATE_GUID_STRING )
#define _CREATE_GUID_STRING

/*
    ============================================================================

    Module Name:        CreateGUIDString.H

    Synopsis:           Header for my GUID/UUID module, which generates GUIDs as
                        strings

    Remarks:            None

    References:			1)	"Standard library header <cstdint>"
                            http://en.cppreference.com/w/cpp/header/cstdint

                        2)	"Build Failed With (cstdio and cstdlib files) errors in visual studio 2010"
                            http://stackoverflow.com/questions/6086656/build-failed-with-cstdio-and-cstdlib-files-errors-in-visual-studio-2010

                        3)	"<cstdint> vs <stdint.h>"
                            http://stackoverflow.com/questions/13642827/cstdint-vs-stdint-h

                        4)	"Can not get size of static array defined in class template" - by sbauer23
                            https://connect.microsoft.com/VisualStudio/feedback/details/759407/can-not-get-size-of-static-array-defined-in-class-template

    Date Written:       Thursday, 02 November 2006.

    Author:             David A. Gray

    License:            Copyright (C) 2005-2016, David A. Gray. All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    *   Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    *   Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    *   Neither the name of David A. Gray nor the names of his contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- ----------------------------------------------------------
    2006/11/03 DAG First working version.

    2010/03/08 DAG Remove version numbers, which have no practical meaning
                   when applied to functions that are part of a static link
                   library.

    2010/06/04 DAG Move the #pragma once preprocessor directive outside the
                   scope of the preprocessor variable which performs the same
                   function for other C compilers.

    2016/01/21 DAG This is a complete rewrite, with more formatting options, and
                   a new name that comports with my latest naming scheme.
    ============================================================================
*/

#include <windows.h>
#include <objbase.h>

#include <Const_Typedefs_WW.H>

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */


//  ----------------------------------------------------------------------------
//  Define macros used in selected function declarations.
//
//  Note:   For this to work correctly, the module that defines a function must
//          define preprocessor constant _BUILDING_P6CSTRINGLIB1. Otherwise, the
//          wrong calling scheme, __declspec(dllimport), is generated.
//
//          There are no such special considerations for calling routines.
//  ----------------------------------------------------------------------------

#if defined ( _BUILDING_P6CSTRINGLIB1 )
    #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
#else   /* #if defined ( _BUILDING_P6CSTRINGLIB1 ) */
    #if defined ( _P6CSTRINGLIB1 )
        #define LIBSPEC_P6CSTRINGLIB1_API extern
    #else
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
    #endif  /* #if defined ( _P6CSTRINGLIB1 ) */

    #include <StringCompareRobust.H>
#endif  /* #if defined ( _BUILDING_P6CSTRINGLIB1 ) */

#define GUID_STRING_ERRORS              ( 0x00001000 | APPLICATION_ERROR_MASK )
#define GUID_STRING_ERR_INVALID_BITMASK ( 0x00000001 | GUID_STRING_ERRORS )

//  ----------------------------------------------------------------------------
//  Use these as values for pdwFlags.
//  ----------------------------------------------------------------------------

#define GUID_STRING_INSERT_NOTHING			0x00000000L		// All bits OFF, decimal value = 0
#define GUID_STRING_INSERT_HYPHENS			0x00000001L		// Bit 0, decimal value = 1
#define GUID_STRING_INSERT_UNDERSCORES		0x00000002L		// Bit 1, decimal value = 2
#define GUID_STRING_INSERT_BRACES			0x00000004L		// Bit 2, decimal value = 4
#define GUID_STRING_UPPER_CASE				0x00000008L		// Bit 3, decimal value = 8
#define GUID_STRING_MASK_OUT_OF_BOUNDS		0x00000010L		// Bit 4, decimal value = 16
#define GUID_STRING_REGISTRY_FORMAT			0x0000000DL		// Bits 0, 2, and 3 ON, decimal value = 13

//  ----------------------------------------------------------------------------
//  These bit masks determine the length of the returned string.
//  ----------------------------------------------------------------------------

#define GUID_STRING_SHORT					0x00000000L		// All bits OFF, decimal value = 0
#define GUID_STRING_MEDIUM					0x00000003L		// Bits 0 and 1 ON, decimal value = 3
#define GUID_STRING_LONG					0x00000007L		// Bits 1, 2, and 3 ON, decimal value = 7

//  ----------------------------------------------------------------------------
//  The returned string will have one of these lengths.
//  ----------------------------------------------------------------------------

#define GUID_STRING_UNFORMATTED_LENGTH		0x00000020L		// String length, in TCHARS, excluding terminal null = 32
#define GUID_STRING_UNBRACKETED_LENGTH		0x00000024L		// String length, in TCHARS, excluding terminal null = 36
#define GUID_STRING_REGISTRY_LENGTH			0x00000026L		// String length, in TCHARS, excluding terminal null = 38

#if defined ( __cplusplus )
extern "C" {
#endif /* #if defined ( __cplusplus ) */

/*
   ============================================================================

   Function Name:       CreateGUIDString

   Synopsis:            Use the CoCreateGuid function in the COM subsystem to
                        generate a secure GUID/UUID.

   Arguments:           pdwFlags    = Bit mask composed of one or more of the
                                      flags defined by GUID_STRING_ constants,
                                      type CDWORD defined in Const_Typedefs_WW.H
                                      as const DWORD

   Returns:             String representation of a GUID.

   Remarks:             1) This function generates a secure GUID, which is one
                           that cannot be associated with the machine on which
                           it was generated.

                        2) The formatted GUID looks like this.

                               {c200e360-38c5-11ce-ae62-08002b2b79ef}.

                        3) This string abandons the original intent of creating
                           a Basic String directly, in favor of creating the raw
                           GUID, formatting it internally, and delegating the
                           conversion to BSTR to a wrapper function.

    References:         Please see the module flower box above.

    Date Written:       Sunday, 08 October 2006
    Date Rewritten:     Saturday, 09 January 2016 - Saturday, 23 January 2016

   ============================================================================
*/

LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall CreateGUIDStringA ( CDWORD pdwFlags ) ;
    
//  ----------------------------------------------------------------------------
//  Anticipating such a need, Microsoft provided a proprietary stack onto which
//  macro definitions can be pushed, so that they can be temporarily redefined.
//  Of necessity, this header must do exactly so, to coerce the linker into
//  importing the CreateGUIDStringW function, so that CreateGUIDStringVB can
//	call it.
//
//  An alternative, which I have applied in numerous other cases, is to list the
//  exported functions in a module definition file. Having discovered certain
//  shortcomings of module definition files, this is my attempt to avoid using
//  one.
//  ----------------------------------------------------------------------------

#if defined (__BUILDING_CREATEGUIDSTRINGVB__ )
    #pragma push_macro ( "LIBSPEC_P6CSTRINGLIB1_API" )
    #undef LIBSPEC_P6CSTRINGLIB1_API
    #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
#endif  /* #if defined (__BUILDING_CREATEGUIDSTRINGVB__ ) */


LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall CreateGUIDStringW  ( CDWORD pdwFlags ) ;

//  ----------------------------------------------------------------------------
//  Once the CreateGUIDStringW declaration gets into the compilation stream,
//	revert to the original definition of LIBSPEC_P6CSTRINGLIB1_API, by popping
//	it off the stack.
//  ----------------------------------------------------------------------------

#if defined (__BUILDING_CREATEGUIDSTRINGVB__ )
    #pragma pop_macro ( "LIBSPEC_P6CSTRINGLIB1_API" )
#endif /* #if defined (__BUILDING_CREATEGUIDSTRINGVB__ ) */

LIBSPEC_P6CSTRINGLIB1_API BSTR   __stdcall CreateGUIDStringVB ( CDWORD pdwFlags ) ;

#if defined UNICODE
    #define CreateGUIDString    CreateGUIDStringW
#else
    #define CreateGUIDString    CreateGUIDStringA
#endif  /* #if defined UNICODE */

#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /* #if !defined ( _CREATE_GUID_STRING ) */