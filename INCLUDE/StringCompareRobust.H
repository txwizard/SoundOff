#if !defined ( AFX_STRINGCOMPAREROBUST_H__C7FA4C13_2A0C_4C58_B92F_3E0F1D31BF2E__INCLUDED_ )
#define AFX_STRINGCOMPAREROBUST_H__C7FA4C13_2A0C_4C58_B92F_3E0F1D31BF2E__INCLUDED_

//  ============================================================================
//
//  File Name:          StringCompareRobust.H
//
//  Class Name:         StringCompareRobust
//
//  File Synopsis:      This header declares the ANSI and Unicode versions of a
//                      robust general purpose string comparer.
//
//  Remarks:            This function is a null_safe wrapper around the two CRT
//                      library routines that do the real work.
//
//  Author:             David A. Gray
//
//  Copyright:          2015 David A. Gray.
//                      All rights reserved world wide.
//
//  Date Created:       Thursday, 12 February 2015
//
//  ____________________________________________________________________________
//  Revision History
//  ____________________________________________________________________________
//
//  Date       Version By  Synopsis
//  __________ _______ ___ _____________________________________________________
//  2015/02/12 1.0.0.1 DAG Routines, tested, and documented.
//
//  2015/02/14 3.1.0.3 DAG Routines incorporated into P6CStringLib1.
//
//  2015/02/16 3.1.0.3 DAG 1) Add warning status codes.
//
//                         2) Implement case sensitive and insensitive plug-in
//                            replacements for _tcscmp and _tcsicmp,
//                            respectively, as preprocessor macros.
//
//  2015/03/18 1.2.0.2 DAG Undefine WIN32_LEAN_AND_MEAN, which has no business
//                         being in a library header, although it may be safely
//                         removed without requiring the associated source code
//                         to be recompiled.
//  ============================================================================

#if defined ( _MSC_VER ) && ( _MSC_VER > 1000 )
    #pragma once
#endif /* #if defined ( _MSC_VER ) && ( _MSC_VER > 1000 ) */

//  ============================================================================
//  When this is the first, or only header pulled into the translation unit, as
//  it is when the routines declared herein are translated (compiled), _UNICODE
//  must be defined, ideally in a way that won't raise a macro redefinition
//  warning if a preceding header already did so. More pertinent, the definition
//  must precede the CRT library headers (stdlib.h, stdio.h, tchar.h).
//
//  However, the typedefs must follow the CRT library headers, so that wchar_t
//  is defined before it is named in the typedef.
//  ============================================================================

#if defined UNICODE
    #if !defined ( _UNICODE )
        #define _UNICODE
    #endif /* #if !defined ( _UNICODE ) */
#endif  /* #if defined UNICODE */

#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

#include <windows.h>                        // GetLastError and APPLICATION_ERROR_MASK.

#if defined UNICODE
    typedef wchar_t *                       LPCOMPARAND ;
    typedef const wchar_t *                 CLPCOMPARAND ;
    #pragma message ( "StringCompareRobust.H: Both UNICODE and _UNICODE are defined, LPCOMPARAND maps to wchar_t *, and TCHAR should map to wchar_t." )
#else
    typedef char *                          LPCOMPARAND ;
    typedef const char *                    CLPCOMPARAND ;
    #pragma message ( "StringCompareRobust.H: Neither UNICODE, nor _UNICODE is defined, LPCOMPARAND maps to char *, and TCHAR should map to char." )
#endif  /* #if defined UNICODE */

#if defined ( _P6CSTRINGLIB1_DEFINED )
    #pragma message ( "StringCompareRobust.H: Calling convention in this translation unit was established by P6CStringLib1.H." )
#else
    #if defined ( _BUILDING_P6CSTRINGLIB1 )
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
        #pragma message ( "StringCompareRobust.H: Calling convention in this translation unit is __declspec(dllexport)." )
    #else
        #if defined ( _P6CSTRINGLIB1 )
            #define LIBSPEC_P6CSTRINGLIB1_API extern
            #pragma message ( "StringCompareRobust.H: Calling convention in this translation unit is extern." )
        #else
            #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
            #pragma message ( "StringCompareRobust.H: Calling convention in this translation unit is __declspec(dllimport)." )
        #endif  /* #if defined ( _P6CSTRINGLIB1 ) */
    #endif  /* #if defined ( _BUILDING_P6CSTRINGLIB1 ) */
#endif  /* #if defined ( _P6CSTRINGLIB1_DEFINED ) */

typedef enum _STRCMP_CASE
{
    STRCMP_CASE_SENSITIVE ,                         // Comparison is case sensitive; value is 0 by default.
    STRCMP_CASE_COUNTS                      = 0 ,   //      Synonymn for STRCMP_CASE_SENSITIVE
    STRCMP_CASE_MATTERS                     = 0 ,   //      Synonymn for STRCMP_CASE_SENSITIVE
    STRCMP_CASE_SIGNIFICANT                 = 0 ,   //      Synonymn for STRCMP_CASE_SENSITIVE

    STRCMP_CASE_INSENSITIVE ,                       // Comparison is case INsensitive; value is 1 by default.
    STRCMP_CASE_BLIND                       = 1 ,   //      Synonymn for STRCMP_CASE_INSENSITIVE
    STRCMP_CASE_IGNORED                     = 1 ,   //      Synonymn for STRCMP_CASE_INSENSITIVE
    STRCMP_CASE_DOESNT_MATTER               = 1 ,   //      Synonymn for STRCMP_CASE_INSENSITIVE
    STRCMP_CASE_INSIGNIFICANT               = 1 ,   //      Synonymn for STRCMP_CASE_INSENSITIVE
    STRCMP_CASE_INDIFFERENT                 = 1     //      Synonymn for STRCMP_CASE_INSENSITIVE
} STRCMP_CASE ;

typedef const enum _STRCMP_CASE CSTRCMP_CASE ;

#define STRCMP_EQUAL                        0x00000000
#define STRCMP_STR1_GT_STR2                 0x00000001
#define STRCMP_STR1_LT_STR2                 0xFFFFFFFF

#define STRCMP_BOTH_SAME                    STRCMP_EQUAL
#define STRCMP_IDENTICAL                    STRCMP_EQUAL

//  ----------------------------------------------------------------------------
//  Warning status codes returned by StringCompareRobust functions:
//
//  1)  These are designed so that they may be combined to report one or both of
//      the input strings as null.
//
//  2)  These are identified as warnings because this routine was designed to
//      cover cases in which null null references are legal. However, since they
//      are drop-in replacements for the underlying CRT routines, which throw an
//      exception when fed a null reference, I used the system status code as an
//      alternative reporting mechanism, which the caller is free to ignore if
//      null references as inputs are legal in its context.
//
//  3)  These strings are defined in StringCompareRobust.H and P6CStringLib1.H,
//      so that StringCompareRobust.H can be used independently.
//  ----------------------------------------------------------------------------

#if !defined ( P6CSTRINGLIB1_RSC_ERROR_WW )
    #define P6CSTRINGLIB1_RSC_ERROR_WW      ( 0x00000900 | APPLICATION_ERROR_MASK )

    #define P6CSTRINGLIB1_RSC_NULL_STRING1  ( 0x00000001 | P6CSTRINGLIB1_RSC_ERROR_WW )
    #define P6CSTRINGLIB1_RSC_NULL_STRING2  ( 0x00000002 | P6CSTRINGLIB1_RSC_ERROR_WW )

    #define P6CSTRINGLIB1_RSC_NULL_STRINGS  ( P6CSTRINGLIB1_RSC_NULL_STRING1 | P6CSTRINGLIB1_RSC_NULL_STRING2 )
#endif  /* #if !defined ( P6CSTRINGLIB1_RSC_ERROR_WW ) */

#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */

LIBSPEC_P6CSTRINGLIB1_API int StringCompareRobustA
(
    CLPCOMPARAND string1 ,
    CLPCOMPARAND string2 ,
    CSTRCMP_CASE penmCaseSensitve
) ;

LIBSPEC_P6CSTRINGLIB1_API int StringCompareRobustW
(
    CLPCOMPARAND string1 ,
    CLPCOMPARAND string2 ,
    CSTRCMP_CASE penmCaseSensitve
) ;

#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */

#if defined UNICODE
    #define StringCompareRobust             StringCompareRobustW
#else
    #define StringCompareRobust             StringCompareRobustA
#endif  /* #if defined UNICODE */

#define StringCompareRobustCS(string1, string2)                                                 \
                                            ( StringCompareRobust ( string1 ,                   \
                                                                    string2 ,                   \
                                                                    STRCMP_CASE_SENSITIVE ) )

#define StringCompareRobustCI(string1, string2)                                                 \
                                            ( StringCompareRobust ( string1 ,                   \
                                                                    string2 ,                   \
                                                                    STRCMP_CASE_INSENSITIVE ) )

#endif /* #if !defined ( AFX_STRINGCOMPAREROBUST_H__C7FA4C13_2A0C_4C58_B92F_3E0F1D31BF2E__INCLUDED_ ) */