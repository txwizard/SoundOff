#ifndef _FORMAT_BINARY_FOR_DISPLAY_WW
#define _FORMAT_BINARY_FOR_DISPLAY_WW

/*
    ============================================================================

    File Name:          BinToHex_WW.H

    Function Name:      BinToHex_WW

    Library Header:     P6CStringLib1.H

    Library Names:      P6CLib1.lib (static)
                        P6CStringLib1.lib (dynamic)

    Synopsis:           Given a void pointer to a block of memory and its size,
                        return a pointer to a buffer containing a printable
                        representation of the data.

    Arguments:          plpBinaryData       = Pointer to a block of memory. See
                                              item 1 in the Remarks section.

                        pulngBufferSize     = Size, in bytes, of the binary data
                                              to which plpBinaryData points. See
                                              item 1 in the Remarks section.

                        puintInterval       = Unnsigned integer which specifies
                                              the interval (number of bytes)
                                              between insertions of a spacer
                                              character.

                                              See Note 4 in the Remarks section.

                        plpchrSpacer        = Pointer to a single TCHAR which is
                                              used as a spacer character if the
                                              value of puintInterval is greater
                                              than zero.

                                              See Note 4 in the Remarks section.

                        penmWhichTable      = Use enumeration B2H_XLATE_TABLE to
                                              specify whether tu use upper case
                                              or lower case for the six glyphs
                                              that are represented by letters of
                                              the Roman alphabet.

                                                B2H_LCASE      = Use lower case.
                                                B2H_UCASE      = Use upper case.
                                                B2H_USE_MALLOC = Use malloc().

                                              Lower case glyphs were added on
                                              Tuesday, 26 August 2014, to meet a
                                              FIPS 180-2 requirement, so that I
                                              can use this routine in the test
                                              program for a SHAx series message
                                              digest implementation.

                                              The B2H_USE_MALLOC was added, as a
                                              bit maskable value, so that the
                                              aforementioned test program and
                                              the VBA wrapper functions can use
                                              the CRT free() routine to discard
                                              them.

                                              IMPORTANT: You MUST use free() to
                                                         discard the memory that
                                                         holds the translated
                                                         bytes if you specify
                                                         the B2H_USE_MALLOC bit.

                                                         Otherwise, you MUST use
                                                         call HeapFree() with a
                                                         handle to the default
                                                         process heap to discard
                                                         the buffer containing
                                                         the translated bytes.

    Returns:            The return value is a pointer to a string containing the
                        formatted representation of the first pulntBufferSize
                        bytes of memory, starting at the address to which
                        plpBinaryData points.

                        If either value is invalid, the return value is NULL.
                        For extended information, call GetLastError and see
                        items 2 and 3 in Remarks.

                        See Note 5 in the Remarks section.

    Remarks:            1)  Argument plpBinaryData is cast to a pointer to an
                            unsigned char, in both versions, because the input
                            buffer is always treated as a byte array, regardless
                            of the desired output format. Likewise, argument
                            pulngBufferSize is always expressed in bytes.

                        2)  WARNING: You should terminate immediately if this
                            function returns NULL and you are certain that
                            plpBinaryData and plpBinaryData are both valid,
                            although you may be able to coax an error message
                            from Windows, by calling GetLastError,
                            EM_ShowMsgOnConsoleW_WW, for console applications,
                            or EM_FormatMsgForMsgbox_WW, for graphical Windows
                            applications.

                        3)  The returned pointer refers to a block that was
                            allocated from the application's default heap,
                            which the caller is responsible for releasing, by
                            passing it to the HeapFree Windows API function,
                            either directly, or through FreeHeapMem_WW, which is
                            declared in WWKernelLibWrapper.H and exported by
                            WWKernelLibWrapper.dll.

                        4)  There are three possible outcomes with respect to
                            insertion of spacers into the output.

                            a)  If puintInterval is zero, no spacers are
                                inserted.

                            b)  If puintInterval is nonzero and plpchrSpacer is
                                NULL, a space is inserted between the text
                                representation of every puintInterval bytes.

                            c)  If puintInterval is nonzero and plpchrSpacer is
                                non-null, the character to which it points is
                                inserted between the text representation of
                                every puintInterval bytes.

                        5)  The character type of the output depends on whether
                            you call the ANSI or Unicode entry point.

    Dependencies:       The host module must define externally linked handle
                        m_hDfltHeap. Although my standard practice is for the
                        DllMain (for DLLs), WinMain (for graphical Windows
                        programs), or Main (for character mode programs) to call
                        GetProcessHeap, these routines trust, but verify, and
                        and do so if its value on entry is NULL.

    References:         None.

    Author:             David A. Gray

    Date Written:       Tuesday, 18 August 2009 and Wednesday, 19 August 2009

	License:            Copyright (C) 2009-2016, David A. Gray. All rights reserved.

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

    Date       Author Synopsis
    ---------- ------ ----------------------------------------------------------
    2008/08/19 DAG/WW First working version, tested and used with HMAC_SHAx,dll.

    2010/03/08 DAG/WW Remove version numbers, which have no practical meaning
                      when applied to modules that are part of a static library.

    2010/04/25 DAG/WW Reinstate direct inclusion of windows.h, since, as of this
                      date, CommonConstants_P6C.H works just fine either way.

    2010/06/04 DAG/WW 1) Correct the sprintf format string to eliminate the
                         leading 0x, which is inappropriate in this context.

                      2) Move the #pragma once preprocessor directive outside
                         the scope of the preprocessor variable which performs
                         the same function for other C compilers.

    2011/10/02 DAG/WW Rewrite, using a translation table in place of sprintf,
                      and consolidate the implementation code for the ANSI and
                      Unicode versions into a single inline source code file, as
                      has become my practice for most of my dual character set
                      routines.

    2011/10/11 DAG/WW Swap the last two arguments, so that they occur in their
                      order of importance and probable use.

    2012/02/05 DAG/WW Implement a new calling convention that enables callers to
                      eliminate an unconditional jump from the Import Address
                      Table to the real entry entry point.

    2012/06/30 DAG/WW Based on recently gained knowledge of how various guard
                      code schemes work, move the #pragma once block inside the
                      block protected by the preprocessor guard variable.

    2013/06/18 DAG/WW Eliminate an overlooked reference to CommonConstants_P6C.H
                      and substitute Const_Typedefs_WW.H, which is plenty for a
                      public interface. This update is built into P6CStringLib1,
                      version 2,8,1,0.

    2014/08/27 DAG/WW Add a flag to specify which of two tables to use, so that
                      the library can generate FIPS 180-2 compliant hexadecimal
                      strings.

    2015/01/03 DAG/WW Extend B2H_XLATE_TABLE with another value that can be
                      combined with the existing value to allocate memory for
                      the output buffer via malloc, rather than HeapAlloc, so
                      that my Secure Hash Algorithm library can break free of a
                      direct dependency on the Windows Platform SDK.

    2016/01/10 DAG/WW Extend B2H_XLATE_TABLE with another value that can be
    ============================================================================
*/

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif  /* #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

#include <windows.h>

//  ----------------------------------------------------------------------------
//  This include fills some perceived gaps in the typedefs defined by the
//  Windows Platform SDK.
//  ----------------------------------------------------------------------------

#include <Const_Typedefs_WW.H>

#if !defined ( LIBSPEC_P6CSTRINGLIB1_API )
    #ifdef  _BUILDING_P6CSTRINGLIB1
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
    #else
        #ifdef _P6CSTRINGLIB1
            #define LIBSPEC_P6CSTRINGLIB1_API extern
        #else   /*  #ifdef _P6CSTRINGLIB1 */
            #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
        #endif  /*  #ifdef _P6CSTRINGLIB1 */
    #endif  /*  _BUILDING_P6CSTRINGLIB1 */
#endif  /* #if !defined ( LIBSPEC_P6CSTRINGLIB1_API ) */

//	----------------------------------------------------------------------------
//  Define error codes, sent to SetLastError().
//	----------------------------------------------------------------------------

#define FMTBIN_ERR_NULL_DATA_PTR_WW     ( 0x00000021 | APPLICATION_ERROR_MASK )
#define FMTBIN_ERR_ZERO_DATA_SIZE_WW    ( 0x00000022 | APPLICATION_ERROR_MASK )
#define FMTBIN_ERR_NO_MEMORY_WW         ( 0x00000001 | APPLICATION_ERROR_MASK )

typedef enum _B2H_XLATE_TABLE
{
    B2H_LCASE      = 0 ,    // Since this value didn't originally have an explicit value, its implicit value was zero.
    B2H_UCASE      = 1 ,    // Since this value didn't originally have an explicit value, its implicit value was one.
    B2H_USE_MALLOC = 4 ,    // The default memory allocator is HeapAlloc. Add this flag to 
} B2H_XLATE_TABLE ;

typedef const B2H_XLATE_TABLE   CB2H_XLATE_TABLE ;
typedef unsigned char *         LPUCHAR ;
typedef const LPUCHAR           CLPUCHAR ;

//  ----------------------------------------------------------------------------
//  Enforce C linkage if compiling into a C++ translation unit.
//  ----------------------------------------------------------------------------

#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */

LPTSTR LIBSPEC_P6CSTRINGLIB1_API BinToHexA_WW
(
    CLPUCHAR         plpBinaryData ,
    CULONG           pulngBufferSize ,
    CUINT            puintInterval ,
    CLPTCHAR         plpchrSpacer ,
    CB2H_XLATE_TABLE penmWhichTable
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API BinToHexW_WW
(
    CLPUCHAR         plpBinaryData ,
    CULONG           pulngBufferSize ,
    CUINT            puintInterval ,
    CLPTCHAR         plpchrSpacer ,
    CB2H_XLATE_TABLE penmWhichTable
) ;

#ifdef UNICODE
    #define BinToHex_WW BinToHexW_WW
#else
    #define BinToHex_WW BinToHexA_WW
#endif  /* #ifdef UNICODE */

//  ----------------------------------------------------------------------------
//  Close the block of code that has "C" linkage.
//  ----------------------------------------------------------------------------

#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /* _FORMAT_BINARY_FOR_DISPLAY_WW */