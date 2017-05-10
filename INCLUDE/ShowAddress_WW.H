#ifndef _SHOWADDRESS_WW_INCLUDED
#define _SHOWADDRESS_WW_INCLUDED

/*
    ============================================================================
    File Name:          ShowAddress_WW.H

    Library Header:     P6CStringLib1.H

    Library Name:       P6CStringLib1.lib (dynamic)

	NOTICE:				These functions are deprecated. Use "%#08x" or "0x%08x"
						with _tprintf instead.

    Remarks:            Since this routine returns a pointer to its own private,
                        static buffer, it is NOT thread-safe.

                        This code has been around for quite a while, in ANSI and
                        Unicode implementations that were part of the test
                        program for P6CStringLib1.dll, into which they are being
                        moved, to make them available to other programs.

    Dependencies:       The host module must define externally linked handle
                        m_hProcHeap. Although my standard practice is for the
                        DllMain (for DLLs), WinMain (for graphical Windows
                        programs), or Main (for character mode programs) to call
                        GetProcessHeap, these routines trust, but verify, and
                        and do so if its value on entry is NULL.

    References:         None

    Date Written:       Sunday, 30 October 2011 and Monday, 31 October 2011

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
	2011/10/31 DAG First working version in its own module, tested and used with
                   all three test harnesses for P6CStringLib1.dll, to which it
				   was moved.

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

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /* #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

#include <windows.h>

//  ----------------------------------------------------------------------------
//  This include fills some perceived gaps in the Windows Platform SDK.
//  ----------------------------------------------------------------------------

#include <Const_Typedefs_WW.H>


//  ----------------------------------------------------------------------------
//  Define error codes, sent to SetLastError().
//  ----------------------------------------------------------------------------

#define SHOWADDR_ERR_NULL_DATA_PTR_WW     ( 0x00000061 | APPLICATION_ERROR_MASK )
#define SHOWADDR_ERR_INVALID_DATA_SIZE_WW ( 0x00000062 | APPLICATION_ERROR_MASK )
#define SHOWADDR_ERR_NO_MEMORY_WW         ( 0x00000001 | APPLICATION_ERROR_MASK )

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


//  Enforce C linkage if compiling into a C++ translation unit.
#if defined ( __cplusplus )
extern "C"
{
#endif	/* #if defined ( __cplusplus ) */

/*
    ============================================================================

    Function Name:      ShowAddress_WW

    Synopsis:           Given a void pointer to a memory location, format its
                        machine address for display.


    Arguments:          plpAddressOfThis    = Pointer to the address to format.

    Returns:            rlpFormattedData    = Pointer to a string containing the
                                              formatted representation of the
                                              address to which plpAddressOfThis
                                              points.

                                              If plpAddressOfThis is NULL, the
                                              return value is also NULL.

    Remarks:            1)  Argument plpAddressOfThis is cast to const LPVOID,
                            so that it can point to any address accessible to
                            calling process.

                        2)  WARNING: You should terminate immediately if this
                            function returns NULL and you are certain that
                            plpAddressOfThis is valid, although you may be able
                            to coax an error message from Windows, by calling
                            GetLastError, EM_ShowMsgOnConsoleW_WW, for console
                            applications, or EM_FormatMsgForMsgbox_WW, for
                            graphical Windows applications.

                        3)  The returned pointer refers to a block that was
                            allocated from the application's default heap,
                            which the caller is responsible for releasing, by
                            passing it to the HeapFree Windows API function,
                            either directly, or through FreeHeapMem_WW, which is
                            declared in WWKernelLibWrapper.H and exported by
                            WWKernelLibWrapper.dll.

                        4)  The character type of the output depends on whether
                            you call the ANSI or Unicode entry point.

    ============================================================================
*/

LPTSTR _declspec( deprecated( "Function ShowAddressA_WW is deprecated. Use _tprintf." ) ) LIBSPEC_P6CSTRINGLIB1_API ShowAddressA_WW
(
    const LPVOID plpAddressOfThis
) ;

LPTSTR _declspec( deprecated( "Function ShowAddressA_WW is deprecated. Use _tprintf." ) ) LIBSPEC_P6CSTRINGLIB1_API ShowAddressW_WW
(
    const LPVOID plpAddressOfThis
) ;

#ifdef UNICODE
    #define ShowAddress_WW ShowAddressW_WW
#else
    #define ShowAddress_WW ShowAddressA_WW
#endif  /*  #ifdef UNICODE */


// Close the block of code that has "C" linkage.
#if defined ( __cplusplus )
}
#endif  /* #if defined( __cplusplus ) */
#endif  /* _SHOWADDRESS_WW_INCLUDED */