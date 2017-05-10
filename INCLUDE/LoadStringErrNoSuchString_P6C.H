#ifndef _LOADSTRINGERRNOSUCHSTRING_P6C_INCLUDED
#define _LOADSTRINGERRNOSUCHSTRING_P6C_INCLUDED

/*
    ============================================================================

    File Name:          LoadStringErrNoSuchString_P6C.H

    Libraries:          P6VersionInfo.dll, via P6VersionInfo.lib (dynamic link)
						P6CStringLib1.dll, (private)
						P6CLIB1.lib (static link)

    Synopsis:           Declare functions LoadStringErrNoSuchString_P6C, which
                        is used internally by P6CStringLib1.dll and any module
                        that statically links a GetVersionInfo_P6C function, and
                        exported by P6CStringLib1.dll, for use with any of its
                        resource string loader functions.

    Limiatations:      	A call to this function must immediately follow the call
                        to LoadString or the wrapper function in which the last
                        Windows API function called was LoadString, so that no
                        subsequent function has a chance to call SetLastError.

    Remarks:			A wrapper function can get around the above limitation
    					by saving and restoring the LastError set by LoadString.

    References:         None.

    Author:             David A. Gray, of Simple Soft Services, Inc.,
                        d/b/a WizardWrx, Irving, Texas, USA

    Date Written:       Sunday, 06 November 2011

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
	2011/11/06 DAG First working version.

    2012/06/30 DAG 1) Based on recently gained knowledge of how various guard
                      code schemes work, move the #pragma once block inside
                      the block protected by the preprocessor guard variable.

                   2) The LIBSPEC_P6CSTRINGLIB1_API calling convention is now
                      fully implemented.

	2016/01/10 DAG Incorporate the standard three-clause BSD license.
    ============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
#pragma once
#endif	/* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

#include <windows.h>

//	----------------------------------------------------------------------------
//	If this header is included on its own, LIBSPEC_P6CSTRINGLIB1_API, defined in
//	P6CStringLib1.H, must be defined in order for thefollowing declarations to
//	compile correctly.
//	----------------------------------------------------------------------------

#ifndef LIBSPEC_P6CSTRINGLIB1_API
    #ifdef  _BUILDING_P6CSTRINGLIB1
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
    #else
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
    #endif  /* _BUILDING_P6CSTRINGLIB1 */
#endif  /* #ifndef	LIBSPEC_P6CSTRINGLIB1_API */


//	Disable the C++ name mangler.
#if defined(__cplusplus)
extern "C"
{
#endif  /*	#if defined(__cplusplus) */

/*
    ============================================================================

    Function Name:      LoadStringErrNoSuchString_P6C

    Synopsis:           Evaluate the code returned by GetLastError() following a
    					LoadString() call that returns FALSE.

    Arguments:          None.

    Returns:            This function returns TRUE if the value returned by
    					GetLastError() is one of the documented resource error
    					codes, which are listed in the remarks.

    					If GetLastError() returns any other code, this function
    					returns FALSE.

    Remarks:            This function simplifies the logic of its caller by
    					simplifying a test for four possible return codes into a
    					single test.

    					The table below lists the four codes documented in
    					WinError.h.

    					-----------------------------------------------------------------------------------------------------------------
														 MessageId
    					MessageId Symbolic Name	        Decimal Hex	MessageText
    					-----------------------------	----	---	---------------------------------------------------------------------
    					ERROR_RESOURCE_DATA_NOT_FOUND	1812	714	The specified image file did not contain a resource section.
						ERROR_RESOURCE_TYPE_NOT_FOUND	1813	715	The specified resource type cannot be found in the image file.
						ERROR_RESOURCE_NAME_NOT_FOUND	1814	716	The specified resource name cannot be found in the image file.
						ERROR_RESOURCE_LANG_NOT_FOUND	1815	717	The specified resource language ID cannot be found in the image file.
    					-----------------------------------------------------------------------------------------------------------------

    References:         WinError.h (Microsoft Platform SDK)

    ============================================================================
*/

BOOL LIBSPEC_P6CSTRINGLIB1_API LoadStringErrNoSuchString_P6C ( void ) ;

// Close the block of code that has "C" linkage.
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /* #ifndef _LOADSTRINGERRNOSUCHSTRING_P6C_INCLUDED */