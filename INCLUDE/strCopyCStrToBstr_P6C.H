#ifndef _STRCOPYCSTRTOBSTR
#define _STRCOPYCSTRTOBSTR

/*
    ============================================================================

    File Name:          strCopyCStrToBstr_P6C.H

    Synopsis:           C header for library function strCopyCStrToBstr_P6C

    Date Completed:     Friday, 27 October 2006

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
    2006/10/27 DAG Initial release.

    2009/11/21 DAG Modernize and simplify internal documentation, and change
                   from locally allocated storage for a handle to the default
                   process heap to a shared handle.

    2010/03/06 DAG 1) Eliminate direct inclusion of Windows.h, because it
                      cannot be parsed according to our requirements until
                      some preprocessor variables are defined in our include
                      file, CommonConstants_P6C.H.

                      CommonConstants_P6C.H includes windows.h after they are
                      defined.

                    2) Define a new constant, COMPUTE_LENGTH_P6C.

    2010/06/04 DAG Move the #pragma once preprocessor directive outside the
                   scope of the preprocessor variable which performs the same
                   function for other C compilers.

    2010/06/04 DAG Move strCopyCStrToBstr_P6C from P6CUtilLib1.

    2012/06/30 DAG Based on recently gained knowledge of how various guard
                   code schemes work, move the #pragma once block inside the
                   block protected by the preprocessor guard variable.

    2013/07/05 DAG Correct an error that cased an access denied error when it
                   attempted to free a static block, as it is designed to do
                   when a block was allocated from the default process heap.
                   The original test didn't work correctly with the DWORD
                   returned by the HeapSize function.

                   Since I had the routine open, I replaced memset with
                   RtlZeroMemory, to prevent the compiler from optimizing
                   away this security measure.

    2016/01/10 DAG Incorporate the standard three-clause BSD license.
                   
    2016/01/23 DAG Replace RtlZeroMemory with SecureZeroMemory, a C macro that
                   cannot be optimized away by the compiler, and replace the IF
                   block that determines the length of the source string with a
                   ternary expression, and thoroughly document the code.
    ============================================================================
*/

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /*  #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

#include <windows.h>                        // Standard Windows API stuff
#include <Const_Typedefs_WW.H>              // Typedefs for const arguments omitted from the Windows API

#ifndef HEAP_SIZE_ERROR_P6C
    #define HEAP_SIZE_ERROR_P6C             ( 0x00000003 | APPLICATION_ERROR_MASK )
#endif  /* #ifndef HEAP_SIZE_ERROR_P6C */

#ifndef MIN_HEAP_BLOCK_PADDING_P6C
    #define MIN_HEAP_BLOCK_PADDING_P6C      0x10000004
#endif	/* #ifndef MIN_HEAP_BLOCK_PADDING_P6C */

#ifndef ZERO_P6C
    #define ZERO_P6C                        0x00000000
#endif  /*  #ifndef ZERO_P6C */

#ifndef COMPUTE_LENGTH_P6C
    #define COMPUTE_LENGTH_P6C              ZERO_P6C
#endif  /* #ifndef COMPUTE_LENGTH_P6C */

//  ----------------------------------------------------------------------------
//  Define macros used in selected function declarations.
//
//  Note:   For this to work correctly, the associated module must define the
//          preprocessor constant, _BUILDING_P6CSTRINGLIB1. Otherwise, the wrong
//          calling scheme, __declspec(dllimport), will be generated.
//  ----------------------------------------------------------------------------

#ifndef LIBSPEC_P6CSTRINGLIB1_API
    #ifdef  _BUILDING_P6CSTRINGLIB1
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
    #else
        #ifdef _P6CSTRINGLIB1
            #define LIBSPEC_P6CSTRINGLIB1_API extern
        #else   /*  #ifdef _P6CSTRINGLIB1 */
            #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
        #endif  /*  #ifdef _P6CSTRINGLIB1 */
    #endif  /* _BUILDING_P6CSTRINGLIB1 */
#endif  /*  #ifndef LIBSPEC_P6CSTRINGLIB1_API */

//  Disable the C++ name mangler.
#if defined ( __cplusplus )
extern "C" {
#endif /* #if defined ( __cplusplus ) */

/*
    ============================================================================

    Function Name:      strCopyCStrToBstr_P6C

    Synopsis:           Given a pointer to a character string, copy the string
                        into a BSTR, then clear (zero) and free the heap block
                        that contained the string.

    Arguments:          plpResult           = Long pointer to input string to be
                                              copied.

                        pdwBufSizeoIn       = DWORD containing the size, in
                                              bytes, of the buffer to which
                                              plpResult points. If this is zero,
                                              the function calls strlen to
                                              calculate the size.

    Returns:            If the function succeeds, its return value is a pointer
                        to a BSTR that has been initialized with the contents of
                        the input string, plpResult.

    Remarks:            This function is called by VB/VBA wrapper functions, to
                        convert the C strings returned by their worker code into
                        a Basic String (BSTR) that can be returned to a VB or
                        VBA program, or to a COM interface.

                        Before this function frees the heap block allocated to
                        the input C string, it zero fills the block, thus making
                        this function suitable for secure applications.

    References:         None

    Date Completed:     Friday, 27 October 2006

    ============================================================================
*/

BSTR LIBSPEC_P6CSTRINGLIB1_API strCopyCStrToBstr_P6C
(
    LPTSTR plpResult ,
    CDWORD pdwBufSizeoIn
) ;
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /* #ifndef _STRCOPYCSTRTOBSTR */