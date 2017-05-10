#ifndef _STRESCAPE_INCLUDED
#define _STRESCAPE_INCLUDED

/*
    ============================================================================

    File Name:          strEscape_P6C.H

	Library Header:		P6CStringLib1.H

    Function Name:      strEscape_P6C

	Libraries:			P6CStringLib1.dll (link against P6CStringLib1.lib)
						P6CLib1.lib (static link)

    Synopsis:           Given a pointer to a character string containing a match
                        string that is intended to become the match string for a
                        regular expression, escape all the metacharacters.

    Arguments:          pstrStringIn        = Long pointer to input string to be
                                              escaped.

                        pstrMetaChars       = Long pointer to optional string of
                                              metacharacters, which may be NULL
                                              or an empty string, in which case
                                              a default list of metacharacters
                                              is used.

    Returns:            rstrEscaped         = Long pointer to string of escaped
                                              characters.

    Notes:              There are ANSI and Unicode versions of this function.

    References:         None

    Calls:              This function uses only library functions and operators.

    Author:             David A. Gray, of Simple Soft Services, Inc., d/b/a
                        WizardWrx, Irving, Texas, USA.

    Date Completed:     Tuesday, 24 October 2006

	License:            Copyright (C) 2006-2016, David A. Gray. All rights reserved.

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
	---------- --- -------------------------------------------------------------
	2006/10/26 DAG Initial release.

    2010/03/08 DAG Enclose expressions involving CUSTOMER_FLAG in
                   parentheses, to ensure their treatment as atoms when they
                   are, themselves, used in expressions.

    2010/04/26 DAG Include windows.h.

    2010/06/04 DAG Add a #pragma once preprocessor directive outside the
                   scope of the preprocessor variable which performs the same
                   function for other C compilers.

    2012/01/07 DAG Substitute APPLICATION_ERROR_MASK, which I finally found in
                   the Platform SDK, for CUSTOMER_FLAG.

    2012/02/05 DAG 1) Implement a new calling convention that enables callers to
                      eliminate an unconditional jump from the Import
                      Address Table to the real entry entry point.

                   2) Export this routine from its logical dynamic link
                      library, P6CStringLib1.dll.

    2012/05/20 DAG Along with the relocation of the Visual Basic wrapper,
                   strEscape_VB_P6C, to P6CStringLib1, all traces of the two
                   underlying C-string functions have been removed from
                   P6CUtilLib1, so that P6CStringLib1 is now the only DLL that
                   exports them (along with their VB wrapper).

    2012/06/30 DAG Based on recently gained knowledge of how various guard code
                   schemes work, move the #pragma once block inside the block
				   protected by the preprocessor guard variable.

	2016/01/10 DAG Incorporate the standard three-clause BSD license.
    ============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif  /* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */


#ifndef LIBSPEC_P6CSTRINGLIB1_API
    #ifdef  _BUILDING_P6CSTRINGLIB1
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
    #else   /*	#ifdef  _BUILDING_P6CSTRINGLIB1 */
        #ifdef __P6CSTRINGLIB1_STATIC__
            #define LIBSPEC_P6CSTRINGLIB1_API extern
        #else   /*	#ifdef __P6CSTRINGLIB1_STATIC__ */
            #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
        #endif  /*	#ifdef __P6CSTRINGLIB1_STATIC__ */
    #endif  /*	#ifdef  _BUILDING_P6CSTRINGLIB1 */
#endif  /*	#ifndef	LIBSPEC_P6CSTRINGLIB1_API */


#include <windows.h>

//  ----------------------------------------------------------------------------
//  Define character range constants
//  ----------------------------------------------------------------------------

#define LOWEST_NORMAL_ALPHA_P6C             0x00000020
#define HIGHEST_NORMAL_ALPHA_P6C            0x0000007E

//  ----------------------------------------------------------------------------
//  Define error code constants, beginning with the Customer Flag bit (strictly
//	speaking, APPLICATION_ERROR_MASK).
//
//  For additional information about this bit, see WinError.h and the
//  documentation  Windows API function GetLastError.
//  ----------------------------------------------------------------------------

#define STRESCAPE_NULL_INPUT_STRING_P6C     ( 1 | APPLICATION_ERROR_MASK )
#define STRESCAPE_EMPTY_INPUT_STRING_P6C    ( 2 | APPLICATION_ERROR_MASK )
#define STRESCAPE_MALLOC_ERROR              ( 3 | APPLICATION_ERROR_MASK )
#define STRESCAPE_SPRINTF_ERROR             ( 4 | APPLICATION_ERROR_MASK )

//	Disable the C++ name mangler.
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

//  ----------------------------------------------------------------------------
//  Declare functions.
//  ----------------------------------------------------------------------------


LPTSTR LIBSPEC_P6CSTRINGLIB1_API strEscapeA_P6C
(
    LPCTSTR pstrStringIn ,
    LPCTSTR pstrMetaChars
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API strEscapeW_P6C
(
    LPCTSTR pstrStringIn ,
    LPCTSTR pstrMetaChars
) ;

#ifdef UNICODE
    #define strEscape_P6C   strEscapeW_P6C
#else
    #define strEscape_P6C   strEscapeA_P6C
#endif  /*	#ifdef UNICODE */

// Close the block of code that has "C" linkage.
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /* _STRESCAPE_INCLUDED */