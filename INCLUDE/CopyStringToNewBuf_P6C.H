#if !defined ( _COPYSTRINGTONEWBUF_P6C )              
#define _COPYSTRINGTONEWBUF_P6C

#if defined ( _MSC_VER)  && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /* #if defined ( _MSC_VER)  && ( _MSC_VER >= 1020 ) */

/*
    ============================================================================

    Module Name:        CopyStringToNewBuf_P6C.H

    Library Header:     WWKernelLibWrapper.H

    Library:            WWKernelLibWrapper32.dll (WWKernelLibWrapper32.lib)

    Defined in Files:   All functions are declared in this header are defined in
                        Visual Studio project P6CLIB1, and may be statically
                        linked, although I am rapidly moving away from static
                        linking, because it causes more problems than it solves,
                        and creates executable files that are bigger than they
                        need to be, especially given that most installations
                        have two or more.

                        See individual function declarations for the name of the
                        source file in which it is defined.

    Synopsis:           Declare functions used to allocate memory and copy a
                        string into it, so that the copy can be modified without
                        disturbing the original, or the memory occupied by the
                        original, which may belong to another module, thread, or
                        process, can be discarded without depriving the caller
                        of access to the string.

    Dependencies:       The input string must be properly terminated with a null
                        character, so that its length can be computed.

    Remarks:            Since the memory occupied by the new string is allocated
                        from the default process heap, the caller can use a call
                        to HeapFree, directly, or through FreeDfltHeapBuf_P6C,
                        to discard it. If you use FreeDfltHeapBuf_P6C, you won't
                        need to provide your own handle to the default process
                        heap, and the return value can be used to invalidate the
                        pointer.

                        Since a pointer to void has the same meaning in both
                        ANSI and Unicode builds, there is no Unicode version of
                        FreeDfltHeapBuf_P6C.

    References:         None

    Author:             David A. Gray, Irving, Texas, USA

    Date Written:       Sunday, 10 July 2005

    License:            Copyright (C) 2005-2017, David A. Gray. All rights reserved.

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
    2009/12/07 DAG    First working version.

    2010/03/08 DAG    Add #pragma once, and document its required order of
                      appearance in relation to CommonConstants_P6C.H and
                      #define _COPYSTRINGTONEWBUF_P6C.

    2010/03/11 DAG    Fix an error that caused a false negative on any call that
                      followed a call with a pointer to memory elsewhere than on
                      the default process heap, because its internal copy of the
                      last DLL error was left as it was from the last call.

                      The fix consists of making its initializer executable.
                      This change was applied to both FreeDfltHeapBuf_P6C and
                      IsBufFromHeap_WW.

    2010/04/25 DAG    Reinstate direct inclusion of windows.h, since, as of this
                      date, CommonConstants_P6C.H works just fine without it.

    2010/06/04 DAG    Move the #pragma once preprocessor directive outside the
                      scope of the preprocessor variable which performs the same
                      function for other C compilers.

    2011/09/05 DAG    1) Move FreeDfltHeapBuf_P6C IsBufFromHeap_WW into header
                         file WWKernelLibWrapper.H, along with related heap
                         management routines. This relocation more clearly
                         separates the code that interacts directly with the
                         Windows kernel library functions from the higher level
                         code that does things with the allocated memory.

                      2) Surround symbolic constant FREEBUF_NULL_POINTER_P6C
                         with preprocessor guard code.

    2011/10/02 DAG    Ensure that all result codes returned by this library are
                      unique within the scope of this library.

    2012/02/05 DAG    1) Implement the streamlined DllExport calling convention,
                         which eliminates an unconditional jump from the address
                         in the Import Address Table to the actual entry point,

                      2) Move this routine from P6CStringLib1.dll to
                         WWKernelLibWrapper.dll.

    2012/05/13 DAG    Correct the internal documentation to reflect relocation
                      of the routine defined in this module to a different DLL.
    2012/05/13 DAG    Correct the internal documentation to reflect relocation
                      of the routine defined in this module to a different DLL.

    2012/07/14 DAG    Move the #pragma once directive inside the guard code, and
                      move both above this text block.

    2013/06/19 DAG    Eliminate CommonConstants_P6C.H in favor of the much more
                      focused Const_Typedefs_WW.H. This change is incorporated
                      into version 1, 7,10, 0 of WWKernelLibWrapper.dll.

    2017/01/15 DAG    Rename the library, from WWKernelLibWrapper to
                      WWKernelLibWrapper32, and synchronize the name of its
                      library header, so that I can make a wholesale calling
                      convention change, from __cdecl, which I didn't fully
                      understand in 2005, to __stdcall, a slightly more
                      efficient calling convention, including slightly less code
                      bloat.

    2017/02/14 DAG    Correct the interpretation of preprocessor symbols that
                      govern the value of LIBSPEC_COPYSTRINGTONEWBUF_P6C_API, so
                      that these routines are automatically exported by the DLL.

                      Since I had the source code open, I decided to replace the
                      HeapAlloc call with one to AllocDfltHeapBufSEH_P6C, my SEH
                      guarded HeapAlloc wrapper.

                      Substitute my BSD license for the free software license
                      that I originally put into many of my early C and C++
                      source files.
    ============================================================================
*/

#include <windows.h>
#include <Const_Typedefs_WW.H>

//  ----------------------------------------------------------------------------
//  Establish the streamlined DLL API.
//  ----------------------------------------------------------------------------

#if !defined ( _SEHHEAPALLOCATORS_DEFINED )
    #pragma message ( __FILE__ " You must link against WWKernelLibWrapper32.lib, and WWKernelLibWrapper32.dll is a dependent DLL." )
#endif	/* #if !defined ( _SEHHEAPALLOCATORS_DEFINED ) */

#pragma message ( __FILE__ ": processing CopyStringToNewBuf_P6C.H, defining LIBSPEC_COPYSTRINGTONEWBUF_P6C_API:" )

#if defined ( __COPYSTRINGTONEWBUF_P6C_PVT__ )
    #define LIBSPEC_COPYSTRINGTONEWBUF_P6C_API __declspec(dllexport) __stdcall
    #pragma message ( __FILE__ ":     __COPYSTRINGTONEWBUF_P6C_PVT__ is defined. Hence, LIBSPEC_COPYSTRINGTONEWBUF_P6C_API maps to __declspec(dllexport)." )
#else   /*#if !defined ( __COPYSTRINGTONEWBUF_P6C_PVT__ ) */
    #if !defined ( __COPYSTRINGTONEWBUF_P6C_STATIC__ )
        #define LIBSPEC_COPYSTRINGTONEWBUF_P6C_API extern __stdcall
        #pragma message ( __FILE__ ":     __DATELIB_STATIC_P6C__ is defined. Hence, LIBSPEC_COPYSTRINGTONEWBUF_P6C_API maps to extern." )
    #else   /* #if !defined ( __COPYSTRINGTONEWBUF_P6C_STATIC__ ) */
        #define LIBSPEC_COPYSTRINGTONEWBUF_P6C_API __declspec(dllimport) __stdcall
        #pragma message ( __FILE__ ":     Neither __COPYSTRINGTONEWBUF_P6C__, nor __DATELIB_STATIC_P6C__ is defined. Hence, LIBSPEC_COPYSTRINGTONEWBUF_P6C_API maps to __declspec(dllimport)." )
    #endif  /* #if !defined ( __COPYSTRINGTONEWBUF_P6C_STATIC__ ) */
#endif  /* #if !defined ( __COPYSTRINGTONEWBUF_P6C_PVT__ ) */

#if defined ( LIBSPEC_COPYSTRINGTONEWBUF_P6C_API )
    #pragma message ( __FILE__ ":     LIBSPEC_COPYSTRINGTONEWBUF_P6C_API was defined successfully." )
#else
    #pragma message ( __FILE__ ":     LIBSPEC_COPYSTRINGTONEWBUF_P6C_API remains UNDEFINED." )
#endif  /* #if defined ( LIBSPEC_COPYSTRINGTONEWBUF_P6C_API ) */

#pragma message ( __FILE__ ": processing CopyStringToNewBuf_P6C.H, defining LIBSPEC_COPYSTRINGTONEWBUF_P6C_API completed." )


//  ----------------------------------------------------------------------------
//  Define error code constants, using the APPLICATION_ERROR_MASK, defined in
//  WinNT.h. For additional information about this bit, see WinError.h, WinNT.h,
//  and the documentation of Windows API function GetLastError.
//  ----------------------------------------------------------------------------

#define COPYSTR_NULL_STRING_P6C             ( 0x00000041 | APPLICATION_ERROR_MASK )
#define COPYSTR_EMPTY_STRING_P6C            ( 0x00000042 | APPLICATION_ERROR_MASK )
#define COPYSTR_ALLOC_ERROR_P6C             ( 0x00000043 | APPLICATION_ERROR_MASK )

#ifndef FREEBUF_NULL_POINTER_P6C
#define FREEBUF_NULL_POINTER_P6C            ( 0x00000044 | APPLICATION_ERROR_MASK )
#endif  /*  #ifndef FREEBUF_NULL_POINTER_P6C */

//  ----------------------------------------------------------------------------
//  Define module level constants that should be public.
//  ----------------------------------------------------------------------------

//  Enforce C linkage.
#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */

/*
    ============================================================================

    Function Name:      CopyStringToNewBuf_P6C

    Defined In Files:   CopyStringToNewBufA_P6C.C  - ANSI Implementation
                        CopyStringToNewBufW_P6C.C  - Unicode Implementation
                        CopyStringToNewBuf_P6C.INL - Implementations of both

    Synopsis:           Create a new buffer, exactly big enough to hold the
                        input string, including its terminating null character,
                        and copy the string into it.

    Arguments:          plpInputString      = Constant pointer to the null
                                              terminated string to copy. See
                                              Remarks.

    Returns:            rlpNewCopy          = Pointer to a copy of the null
                                              terminated string. See Remarks.

    Remarks:            Use this function to meet one or both of the following
                        requirements.

                        1)  Make a copy of a string that can be modified without
                            disturbing the original.

                        2)  Make a copy of a string into memory that will remain
                            under your control, so that, when the routine that
                            created the original string can release the memory
                            that held it, leaving the copy in your local storage
                            untouched.

                        A new buffer is allocated from the default process heap,
                        by calling HeapAlloc, specifying that the buffer must be
                        zero filled. Next, memcpy is called to copy the string
                        into the new buffer.

                        To prevent a memory leak, your routine should call
                        FreeDfltHeapBuf_P6C, declared below, to release the
                        memory before the returned pointer goes out of scope.

    References:         None.

    Date Written:       Wednesday, 18 November 2009.

    ============================================================================
*/


LPTSTR LIBSPEC_COPYSTRINGTONEWBUF_P6C_API CopyStringToNewBufA_P6C
(
    LPCTSTR plpInputString
) ;

LPTSTR LIBSPEC_COPYSTRINGTONEWBUF_P6C_API CopyStringToNewBufW_P6C
(
    LPCTSTR plpInputString
) ;

#if defined ( UNICODE )
    #define CopyStringToNewBuf_P6C      CopyStringToNewBufW_P6C
#else
    #define CopyStringToNewBuf_P6C      CopyStringToNewBufA_P6C
#endif  /* #if defined ( UNICODE ) */


// Close the block of code that has "C" linkage.
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /*#if defined ( _COPYSTRINGTONEWBUF_P6C ) */