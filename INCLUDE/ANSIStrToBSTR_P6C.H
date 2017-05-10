/*
    ============================================================================

    Module Name:        ANSIStrToBSTR_P6C.H

    Library Header:     P6CStringLib1.H

    Library Names:      P6CLib1.lib (static)
                        P6CStringLib1.lib (dynamic)

    Synopsis:           This module contains a pair of functions for converting
                        ANSI strings to BSTR and Unicode strings.

    Remarks:            Code that calls this module must include P6CLIB1.H
                        or ANSIStrToBSTR_P6C.H.

    Author:             David A. Gray, of Simple Soft Services, Inc., d/b/a
                        WizardWrx, Irving, Texas, USA.

    Date Written:       Wednesday, 17 August 2005

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
    ---------- --- -------------------------------------------------------------
    2005/08/17 DAG First working version.

    2005/10/13 DAG Reorganize prototypes and rationalize preprocessor
                   directives so that code which includes this header 
				   indirectly, via P6CUtilLib1.H compiles correctly.

    2006/10/12 DAG Replace GetLastError_P6LIB1 with GetLastError, in the
                   Windows API, as the method of getting error information.
                   Likewise, calls to SetLastError replace SetLastError_P6LIB1.
                   These changes align the code with the accepted method of
                   error reporting for libraries that follow the WINAPI
                   calling conventions.

    2010/03/09 DAG 1) Add #pragma once, and move extern "C" to the top of the
                      function prototypes block.

                   2) Include this header within P6CStringLib1.H, since it is
                      already in the exports listed in P6CStringLib1.DEF.

    2010/04/25 DAG Reinstate direct inclusion of windows.h, since, as of this
                   date, CommonConstants_P6C.H works just fine without it.

    2010/06/04 DAG Move the #pragma once preprocessor directive outside the
                   scope of the preprocessor variable which performs the same
                   function for other C compilers.

    2011/08/28 DAG Include oleauto.h, required for function prototypes that
                   accept and return Basic String (BSTR) objects.

    2011/08/28 DAG Separate the two functions defined herein into individual
                   source code files.

    2011/10/02 DAG Ensure that all result codes returned by this library are
                   unique within the scope of this library.

    2011/10/30 DAG Eliminate a redundant copy of P6CStringLib1_Pvt.H in the
                   source tree of static link library P6CLIB1, which I
                   discovered in the course of adding two STRREPLACE_
                   constants that appear in both versions of function
                   StrReplace_P6C, which is defined in P6CLib1, and
                   incorporated into that DLL.

    2012/06/30 DAG 1) Based on recently gained knowledge of how various guard
                      code schemes work, move the #pragma once block inside
                      the block protected by the preprocessor guard variable.

                   2) The LIBSPEC_P6CSTRINGLIB1_API calling convention is now
                      fully implemented.

    2013/06/18 DAG Eliminate an overlooked reference to CommonConstants_P6C.H
                   and substitute Const_Typedefs_WW.H, which is plenty for a
                   public interface. This update is built into P6CStringLib1,
                   version 2,8,1,0.

	2016/01/10 DAG Incorporate the standard three-clause BSD license.
    ============================================================================
*/


#ifndef _ANSISTRTOBSTR_P6C_INCLUDED
#define _ANSISTRTOBSTR_P6C_INCLUDED

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /* #if defined (_MSC_VER) && (_MSC_VER >= 1020) */


#include <windows.h>
#include <oleauto.h>

#include <Const_Typedefs_WW.H>


//  ----------------------------------------------------------------------------
//  Define error codes.
//  ----------------------------------------------------------------------------

#define A2B_INPUT_IS_NULL_P6C               ( 0x00000031 | APPLICATION_ERROR_MASK )
#define A2B_INPUT_IS_EMPTY_P6C              ( 0x00000032 | APPLICATION_ERROR_MASK )
#define A2B_MALLOC_ERROR_P6C                ( 0x00000033 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  If this header is included on its own, LIBSPEC_P6CSTRINGLIB1_API, defined in
//  P6CStringLib1.H, must be defined in order for thefollowing declarations to
//  compile correctly.
//  ----------------------------------------------------------------------------

#ifndef LIBSPEC_P6CSTRINGLIB1_API
    #ifdef  _BUILDING_P6CSTRINGLIB1
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
    #else
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
    #endif  /* _BUILDING_P6CSTRINGLIB1 */
#endif  /* #ifndef  LIBSPEC_P6CSTRINGLIB1_API */

//  ============================================================================
//  Declare functions, with C linkage for all.
//  ============================================================================


#if defined(__cplusplus)
extern "C"
{
#endif  /*  #if defined(__cplusplus) */

/*
    ============================================================================

    Function Name:      ANSIStrToBSTR_P6C

    Synopsis:           Given an ANSI string, convert it to a wide character, or
                        Unicode, string, then convert that to a BSTR.

    Arguments:          plpANSIString   = Long pointer to null terminated ANSI
                                          string to convert.

                        pfNeedXlate     = Boolean to control ANSI to wide char-
                                          acter translation.

                                          TRUE  = Call MultiByteToWideChar to
                                                  translate from ANSI to Unicode
                                                  characters.

                                          FALSE = Convert the string as is; the
                                                  caller will handle the mapping
                                                  from ANSI to Unicode.

    Returns:            rBSTRBasicStr   = A BSTR containing the Unicode mapping
                                          of input string lpANSIString.

                                          If lpANSIString is a null pointer, an
                                          empty string is returned and the error
                                          code is set to A2B_INPUT_IS_NULL_P6C.

                                          If lpANSIString is an empty pointer,
                                          an empty string is returned and the
                                          error code is  A2B_INPUT_IS_EMPTY_P6C.

    Remarks:            1) If preprocessor variable _P6CLIB1_PRIVATE_INCLUDED is
                           defined, this module is built without its own error
                           return mechanism and calls the Windows API directly
                           for a handle to the default process heap.

                        2) It seems that, when you return an ANSI string via the
                           SysAllocString function to a Visual Basic program, it
                           gets converted from ANSI to Unicode in the interface.
                           Therefore, if you call MultiByteToWideChar on an ANSI
                           string, the string will have alternating spaces in it
                           when it arrives in your Visual Basic program. Go
                           figure.

                        3) If this module is built as part of P6CLIB1.DLL, error
                           codes are returned through SetLastError_P6LIB1, and
                           are accessible to the calling program through
                           library function GetLastError. Otherwise, the
                           error code is stored locally and made accessible
                           through companion function GetLastError_AtoB, which
                           is built as part of this module, along with module
                           level storage for the result code.

    References:         http://blogs.msdn.com/ericlippert/archive/2003/09/12/52976.aspx,
                        "Eric's Complete Guide To BSTR Semantics" got me pointed
                        in the right direction.

    Date Written:       Wednesday, 17 August 2005

    ----------------------------------------------------------------------------
    Revison History
    ----------------------------------------------------------------------------

    Date       Version    Author Synopsis
    ---------- ---------- ------ -----------------------------------------------
    2005/08/17 1, 0, 0, 4 DAG/WW First working version.
    ============================================================================
*/

BSTR LIBSPEC_P6CSTRINGLIB1_API ANSIStrToBSTR_P6C
(
    LPCTSTR plpANSIString ,
    BOOL    pfNeedXlate
) ;


/*
    ============================================================================

    Function Name:      ANSIStrToWCSTR_P6C

    Synopsis:           Given an ANSI string, convert it to a wide character, or
                        Unicode, string, returning a pointer to the WCSTR.

    Arguments:          plpANSIString   = Long pointer to null terminated ANSI
                                          string to convert.

    Returns:            rlpWCStr        = A WCSTR containing the Unicode mapping
                                          of input string lpANSIString.

                                          If lpANSIString is a null pointer, an
                                          empty string is returned and the error
                                          code is set to A2B_INPUT_IS_NULL_P6C.

                                          If lpANSIString is an empty pointer,
                                          an empty string is returned and the
                                          error code is  A2B_INPUT_IS_EMPTY_P6C.

    Remarks:            1) If preprocessor variable _P6CLIB1_PRIVATE_INCLUDED is
                           defined, this module is built without its own error
                           return mechanism and calls the Windows API directly
                           for a handle to the default process heap.

                        2) Unlike companion function ANSIStrToBSTR_P6C, this one
                           always performs the character string mapping, and it
                           returns the resulting Unicode string.

    References:         http://blogs.msdn.com/ericlippert/archive/2003/09/12/52976.aspx,
                        "Eric's Complete Guide To BSTR Semantics" got me pointed
                        in the right direction.

    Calls:              The following Windows API functions are called in the
                        order named.

                        Function             Library       Header
                        -------------------  ------------  ---------------------
                        SetLastError         Kernel32.lib  Winbase.h
                        GetProcessHeap       Kernel32.lib  Winbase.h
                        strlen               C Run-Time    string.h
                        HeapAlloc            Kernel32.lib  Winbase.h
                        MultiByteToWideChar  Kernel32.lib  Winnls.h
                        HeapFree             Kernel32.lib  Winbase.h
                        --------------------------------------------------------

    Date Written:       Wednesday, 17 August 2005

    ----------------------------------------------------------------------------
    Revison History
    ----------------------------------------------------------------------------

    Date       Version    Author Synopsis
    ---------- ---------- ------ -----------------------------------------------
    2005/08/17 1, 0, 0, 4 DAG/WW First working version.
    ============================================================================
*/

LPWSTR LIBSPEC_P6CSTRINGLIB1_API ANSIStrToWCSTR_P6C
(
    LPCTSTR plpANSIString
) ;

// Close the block of code that has "C" linkage.
#if defined(__cplusplus)
}
#endif  /* __cplusplus */
#endif  /*_ANSISTRTOBSTR_P6C_INCLUDED */