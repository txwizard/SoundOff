#ifndef __STOREADDRESSINARRAY_WW_DEFINED
#define __STOREADDRESSINARRAY_WW_DEFINED

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
	#pragma once
#endif  /* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

/*
    ============================================================================

    File Name:          StoreAddressInArray_WW.H

    Function Name:      StoreAddressInArray_WW

    Synopsis:           Store an address, or some other DWORD value, into a
                        designated element of an array.

    Arguments:          plpAddress      = DWORD pointer (address) to store into
                                          array, passed by value (cast to LPVOID
                                          for C/C++ callers)

                        pdwWhichItem    = DWORD subscript (offset) into list of
                                          desired item, passed by value

                        plpArray        = LPVOID pointer to first item in list

                        pdwNItems       = DWORD number of items in list, passed
                                          by value

    Remarks:            A default compilation of a call to this routine yields
                        warning C4047: 'identifier1' : 'operator' : different
                        levels of indirection from 'identifier2' against the
                        second argument, plpArray. Since the warning may safely
                        be ignored, you can safely suppress the warning, as
                        shown in the following example.

                            #pragma warning ( push )
                            #pragma warning ( disable:4047 )
                            lpCurrStr   = StoreAddressInArray_WW ( dwSubscript ,
                                                                   alpTestStrings ,
                                                                   TEST_STRING_COUNT ) ;
                            #pragma warning ( pop )

                        This is the least disruptive way to suppress the warning
                        around this single statement.

                        This routine and its inverse, GetItemFromArray_WW, are
                        implemented in assembly language, and the object file
                        was generated by the Microsoft Macro Assembler, Version
                        6.11.

    Returns:            Contents of DWORD at offset pdwWhichItem in pdwNItems

    Author:             David A. Gray

    Date Written:       Friday, 13 January 2012 - Sunday, 15 January 2012

	License:            Copyright (C) 2012-2016, David A. Gray. All rights reserved.

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
	2012/07/03 DAG Initial implementation and testing.

    2013/06/18 DAG Eliminate an overlooked reference to CommonConstants_P6C.H
                   and substitute Const_Typedefs_WW.H, which is plenty for a
                   public interface. This update is built into P6CStringLib1,
                   version 2,8,1,0.

    2015/01/15 DAG Change the calling convention from APIENTRY to __stdcall.
                   The effect of this change is confined to this header file.
                   This update is built into P6CStringLib1, version 2,9,0,4.

	2016/01/10 DAG Incorporate the standard three-clause BSD license.
    ============================================================================
*/

#include <windows.h>

#include <Const_Typedefs_WW.H>

    #if defined(__cplusplus)
    extern "C"
    {
    #endif
        DWORD __stdcall StoreAddressInArray_WW
        (
            LPVOID plpAddress ,     // Address to store into slot pdwWhichItem of array plpArray
            CDWORD pdwWhichItem ,   // subscript (offset) into list of desired item, passed by value
            LPVOID plpArray ,       // pointer to first item in list
            CDWORD pdwNItems        // number of items in list, passed by value
        ) ;
    #ifdef __cplusplus
    }
    #endif  /*  __cplusplus */
#endif  /*  __STOREADDRESSINARRAY_WW_DEFINED */