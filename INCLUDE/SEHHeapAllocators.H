#if !defined ( _SEHHEAPALLOCATORS_DEFINED )
#define _SEHHEAPALLOCATORS_DEFINED

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /*  #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

/*
    ============================================================================

    Name:               SEHHeapAllocators.H

    Library:            WWKernelLibWrapper32.dll (WWKernelLibWrapper32.lib)

    Synopsis:           Header file for the SEH guarded heap allocators defined
                        in a Windows DLL, WWKernelLibWrapper.DLL, which provides
                        convenience wrappers for a few frequently used functions
                        exported by Kernel32.dll.

    Remarks:            I moved these out of WWKernelLibWrapper.H to meet a long
                        established dependency in TcharMacros_WW.H without
                        pulling windows.h into the translation stream ahead of
                        CommonConstants_P6C.H which includes TcharMacros_WW.H.
                        Independent guard macros allow WWKernelLibWrapper.H and
                        this header to be imported if you need the functions
                        declared therein.

    Author:             David A. Gray, of Simple Soft Services, Inc.,
                        d/b/a WizardWrx.

    License:            Copyright (C) 2009-2017, David A. Gray. All rights reserved.

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

    Date       Version    Author Synopsis
    ---------- ---------- ------ -----------------------------------------------
    2016/05/07 1, 9, 2, 8 DAG    Move the memory allocator declarations into a
                                 dedicated header.

    2016/05/21 1, 9, 2, 8 DAG    Delete the line that said when the original
                                 header was created, since that information is
                                 ireelevant.

                                 Since this is a documentation change, nothing
                                 requires building, although I am about to build
                                 a project that includes and depends upon this
                                 header.

    2017/02/14 2, 0, 0, 2 DAG    Relocating some routines from P6VersionInfo.dll
                                 to this library, which requires them to import
                                 the memory allocators defined herein exposed an
                                 oversight that arose from duplicated definition
                                 of the original memory allocator wrappers. This
                                 is corrected, once and for all, by moving these
                                 declarations into this header, and completely
                                 removing them from WWKernelLibWrapper.H.
    ============================================================================
*/

#include <windows.h>
#include <Const_Typedefs_WW.H>

//  ----------------------------------------------------------------------------
//  Define symbolic constants that may be returned by GetLastError following a
//  call to one of these functions.
//  ----------------------------------------------------------------------------

#if !defined ( HEAP_ALLOC_SEH_INVALID_SIZE_P6C )
    #define HEAP_ALLOC_SEH_INVALID_SIZE_P6C ( 0x00000081 | APPLICATION_ERROR_MASK )
#endif  /* #if !defined ( HEAP_ALLOC_SEH_INVALID_SIZE_P6C ) */

#if !defined ( FREEBUF_NULL_POINTER_P6C )
    #define FREEBUF_NULL_POINTER_P6C        ( 0x00000011 | APPLICATION_ERROR_MASK )
#endif  /* #if !defined ( FREEBUF_NULL_POINTER_P6C ) */

#if !defined ( HEAP_SIZE_ERROR_P6C )
    #define HEAP_SIZE_ERROR_P6C             ( 0x00000003 | APPLICATION_ERROR_MASK )
#endif  /* #if !defined ( HEAP_SIZE_ERROR_P6C ) */

#if !defined ( OUTPUT_PTR_IS_INVALID_WW )
    #define OUTPUT_PTR_IS_INVALID_WW        ( 0x00000071 | APPLICATION_ERROR_MASK )
#endif  /* #if !defined ( OUTPUT_PTR_IS_INVALID_WW ) */

//  ---------------------------
//  0xFFFFFFFF = Minus one (-1)
//  ---------------------------

#if !defined ( MINUS_ONE_WW )
    #define MINUS_ONE_WW                    0xFFFFFFFF
#endif  /* #if !defined ( MINUS_ONE_WW ) */

#if !defined ( HEAP_SIZE_IS_INVALID_WW )
    #define HEAP_SIZE_IS_INVALID_WW         MINUS_ONE_WW
#endif  /* #if !defined ( HEAP_SIZE_IS_INVALID_WW ) */

#if !defined ( PLUS_ONE_WW )
    #define PLUS_ONE_WW                     0x00000001
#endif  /* #if !defined ( PLUS_ONE_WW ) */

//  ----------------------------------------------------------------------------
//  Define the decoration for the functions declared herein. These definitions
//  extend to WWKernelLibWrapper.H, which includes this header before it needs
//  LIBSPEC_WWKERNELLIBWRAPPER_API.
//
//	Immediately above the opening brace of each of the routines declared herein,
//	there is a pragma directive to suppress compiler warning C4273, which would
//	usually justify its classification as a Level 1 warning. In this case, the
//	inconsistency is the result of a carefully considered design choice.
//
//	1)	SEHHeapAllocators.H is read into the translation stream by macro header
//		TcharMacros_WW.H, so that it can generate the macros required to fulfill
//		the objective of defining symbol _TCHAR_MACROS_SEH_ALLOCATORS_.
//
//	2)	WWKernelLibWrapper.H is subsequently read into the translation stream by
//		WWKernelLibWrapper_Pvt.H under conditions that cause SEHHeapAllocators.H
//		to be included again, with symbol LIBSPEC_WWKERNELLIBWRAPPER_API defined
//		as __declspec(dllimport) __stdcall, so that several of the other
//		routines declared in WWKernelLibWrapper.H  can import one or more of the
//		routines first declared when SEHHeapAllocators.H was independently
//		included by TcharMacros_WW.H.
//
//	Importing routines exported by a library for local use is fairly common, but
//	it is usually achieved by way of a plain vanilla extern linkage. I chose the
//	__declspec (dllimport) __stdcall to make the local import explicit. Since it
//	brings the local usage into sharper focus, I stand by that decision.
//  ----------------------------------------------------------------------------

#if defined ( _BUILDING_WWKERNELLIBWRAPPER )
    #if defined ( __WWKERNELLIBWRAPPER_LOCAL_CONSUMER__ )
        #define LIBSPEC_WWKERNELLIBWRAPPER_API  __declspec(dllimport) __stdcall
    #else
        #define LIBSPEC_WWKERNELLIBWRAPPER_API  __declspec(dllexport) __stdcall
    #endif  /* #if defined ( __WWKERNELLIBWRAPPER_LOCAL_CONSUMER__ ) */
#else
	#pragma message ( __FILE__ " You must link against WWKernelLibWrapper32.lib, and WWKernelLibWrapper32.dll is a dependent DLL." )
    #define LIBSPEC_WWKERNELLIBWRAPPER_API      __declspec(dllimport) __stdcall
#endif  /* #if defined ( _BUILDING_WWKERNELLIBWRAPPER ) */

//  ----------------------------------------------------------------------------
//  Declare functions exported by this library. All are declared with C linkage,
//  so that they work with callers written in C, C++, Visual Basic, or whatever.
//  ----------------------------------------------------------------------------

#if defined ( __cplusplus )
extern "C"
{
#endif  /* __cplusplus */
/*
    ----------------------------------------------------------------------------

    Function Name:      AllocDfltHeapBufSEH_P6C

    Defined In File:    AllocDfltHeapBufSEH_P6C.C

    Synopsis:           Wrap a call to HeapAlloc against the default process
                        heap in a structured exception handling block.

    In:                 pintNBytes  = Integer (to enforce a limit of 2 GB) bytes
                                      to allocate. See Remarks for restrictions.

    Out:                If the function succeeds, the return value is a pointer
                        to the allocated buffer, which has been initialized with
                        NULL bytes. Since it reports through SetLastError, it is
                        safe to call HeapFree directly to discard the memory.

                        If the function fails, the return value is NULL, and you
                        can call GetLastError for additional information.

    Remarks:            Argument pintNBytes is a signed integer by design, to
                        impose a limit of 2 GB on the block size. If pintNBytes
                        is less than or equal to zero, the function returns a
                        null pointer, and GetLastError returns
                        HEAP_ALLOC_SEH_INVALID_SIZE_P6C.

                        Use ReAllocDfltHeapBufSEH_P6C to enlarge or shrink the
                        buffer.

                        Use this function to allocate and zero fill a block of
                        memory from your default process heap. This routine is
                        preferable to directly calling HeapAlloc because it is
                        wrapped in a Structured Exception Handling (SEH) block,
                        so that it reports more precisely the reason for a
                        failure.

                        Your code should not call SetLastError, which would mask
                        the status code recorded by this routine. However, it
                        should report the system status code and recover, if
                        possible, from the memory allocation error.

    Date Written:       Sunday, 01 February 2015

    ----------------------------------------------------------------------------
*/

LPVOID LIBSPEC_WWKERNELLIBWRAPPER_API AllocDfltHeapBufSEH_P6C
(
    CINT pintNBytes
) ;

/*
    ----------------------------------------------------------------------------

    Function Name:      AllocAnyHeapBufSEH_P6C

    Defined In File:    AllocAnyHeapBufSEH_P6C.C

    Synopsis:           Wrap a call to HeapAlloc against any process heap in a
                        structured exception handling block.

    In:                 pintNBytes  = Integer (to enforce a limit of 2 GB) bytes
                                      to allocate. See Remarks for restrictions.

                        phHeap      = Handle of the heap upon which to perform
                                      the operation.

    Out:                If the function succeeds, the return value is a pointer
                        to the allocated buffer, which has been initialized with
                        NULL bytes. Since it reports through SetLastError, it is
                        safe to call HeapFree directly to discard the memory, or
                        use FreeAnyHeapBuf_P6C, which wraps the call to HePFree
                        in a Structured Exception Handling block.

                        If the function fails, the return value is NULL, and you
                        can call GetLastError for additional information.

    ----------------------------------------------------------------------------
*/

LPVOID LIBSPEC_WWKERNELLIBWRAPPER_API AllocAnyHeapBufSEH_P6C
(
    CINT pintNBytes ,
    HANDLE phHeap
) ;



/*
    ----------------------------------------------------------------------------

    Function Name:      FreeDfltHeapBuf_P6C

    Defined In File:    FreeDfltHeapBuf_P6C.C

    Synopsis:           Free a buffer that was allocated from the default
                        process heap.

    Arguments:          plpvBuf = Long pointer to the buffer to be freed. See
                                  Remarks.

    Returns:            If the function succeeds, the return value is zero.
                        If the function fails, the return value is the code
                        returned by GetLastError, which is most likely to be
                        ERROR_INVALID_PARAMETER, indicating that the plpvBuf
                        points to static memory.

                        Since a production program should never attempt to free
                        static memory, ERROR_INVALID_PARAMETER, system status
                        code 0x00000057 (87 decimal), is a reportable error.
                        The system message is, "The parameter is incorrect."

                        Please see the Remarks for implementation suggestions.

    Remarks:            Use this function to discard a block of memory that was
                        allocated from the default process heap.

                        IMPORTANT:  Unless plpvBuf is the address of a memory
                                    block that was allocated from the default
                                    process heap, this routine generate the
                                    following message, when the routine runs in
                                    a debugger.

                                        User breakpoint called from code

                                    This message cannot be suppressed. However,
                                    when you acknowledge the message box, your
                                    code continues to execute normally.

                                    Outside a debugger, there is no outward sign
                                    of this first-chance exception, and the code
                                    behaves as expected and intended on Windows
                                    XP and older.

                                    Newer Windows platforms always raise an
                                    exception AND report the heap as corrupted.
                                    I suspect the reason behind this is to call
                                    attention to rogue programs that attempt to
                                    free memory that should not be freed.

                                    Valid pointers work silently, without rasing
                                    any exceptions.

                        By assigning the return value to plpvBuf, you accomplish
                        two things at once.

                        1)  The buffer is discarded, returning the memory to the
                            default process heap.

                        2)  The pointer is invalidated, so that your code cannot
                            accidentally refer to the freed memory, thus closing
                            a potential attack vector.

                        Having discovered that LastError is getting clobbered, I
                        changed the return from LPVOID to DWORD, and use it to
                        return LastError, if HeapFree fails.

                        Since this function is intended to gracefully handle an
                        invalid pointer, it uses structured exception handling,
                        and passes the pointer to HeapSize before attempting to
                        discard it via HeapFree.

                        1)  If the pointer is valid, HeapSize returns its size,
                            in bytes.

                        2)  If the pointer is invalid, HeapSize returns -1, and
                            this function returns the address of the pointer, as
                            a signal to the caller that it cannot discard the
                            memory.

                        The purpose of the structured exception handling is to
                        enable our code to intercept and handle the hardware
                        exception raised by an attempt to get the size of an
                        invalid pointer.

                        Structured exception handling is similar to the standard
                        try/catch/finally blocks used in C++, C#, and VB.NET.
                        However, there are significant differences, including a
                        different set of keywords that are supported by the pure
                        C compiler.

    References:         None.

    Date Written:       Wednesday, 18 November 2009.

    ============================================================================
*/

DWORD LIBSPEC_WWKERNELLIBWRAPPER_API FreeDfltHeapBuf_P6C
(
    LPVOID plpvBuf
) ;

#define FreeHeapMem_WW  FreeDfltHeapBuf_P6C


/*
    ----------------------------------------------------------------------------

    Function Name:      FreeAnyHeapBuf_P6C

    Defined In File:    FreeAnyHeapBuf_P6C.C

    Synopsis:           Free a buffer that was allocated from the default
                        process heap.

    In:                 plpvBuf     = Long pointer to the buffer to be freed.
                                      See the Remarks section of documentation
                                      of companion function FreeDfltHeapBuf_P6C.

                        phHeap      = Handle of the heap upon which to perform
                                      the operation.

    Out:                If the function succeeds, the return value is zero.
                        If the function fails, the return value is the code
                        returned by GetLastError, which is most likely to be
                        ERROR_INVALID_PARAMETER, indicating that the plpvBuf
                        points to static memory.

    Remarks:            See the Remarks section of documentation of companion
                        function FreeDfltHeapBuf_P6C.

    ----------------------------------------------------------------------------
*/

DWORD LIBSPEC_WWKERNELLIBWRAPPER_API FreeAnyHeapBuf_P6C ( LPVOID plpvBuf , HANDLE phHeap ) ;


/*
    ----------------------------------------------------------------------------

    Function Name:      ReAllocDfltHeapBufSEH_P6C

    Defined In File:    ReAllocDfltHeapBufSEH_P6C.C

    Synopsis:           Wrap a call to HeapReAlloc against the default process
                        heap in a structured exception handling block.

    In:                 plpCurrBuff = Void pointer to the buffer to reallocate.

                        pintNBytes  = Integer (to enforce a limit of 2 GB) bytes
                                      to allocate. See Remarks for restrictions.

    Out:                If the function succeeds, the return value is a pointer
                        to the reallocated buffer, which has had its additional
                        bytes, if any, initialized with NULL bytes. Since it
                        reports through SetLastError, it is safe to call
                        HeapFree directly to discard the memory.

                        If the function fails, the return value is NULL, and you
                        can call GetLastError for additional information.

    Remarks:            Argument pintNBytes is a signed integer by design, to
                        impose a limit of 2 GB on the block size. If pintNBytes
                        is less than or equal to zero, the function returns a
                        null pointer, and GetLastError returns
                        HEAP_ALLOC_SEH_INVALID_SIZE_P6C.

                        Use AllocDfltHeapBufSEH_P6C to allocate a new buffer; it
                        is more robust than calling HeapAlloc directly, and more
                        efficient than calling malloc followed by memset.

                        Use this function to reallocate and zero fill the bytes
                        added to a block of memory on your default process heap.
                        This routine is preferable to calling HeapReAlloc
                        directly because it is wrapped in a Structured Exception
                        Handling (SEH) block, so that it reports more precisely
                        the reason for a failure.

                        Your code should not call SetLastError, which would mask
                        the status code recorded by this routine. However, it
                        should report the system status code and recover, if
                        possible, from the memory allocation error.

    Date Written:       Sunday, 01 February 2015

    ----------------------------------------------------------------------------
*/

LPVOID LIBSPEC_WWKERNELLIBWRAPPER_API ReAllocDfltHeapBufSEH_P6C
(
    LPVOID  plpCurrBuff ,
    CINT    pintNBytes
) ;


/*
    ----------------------------------------------------------------------------

    Function Name:      ReAllocAnyHeapBufSEH_P6C

    Defined In File:    ReAllocAnyHeapBufSEH_P6C.C

    Synopsis:           Wrap a call to HeapReAlloc against the default process
                        heap in a structured exception handling block.

    In:                 plpCurrBuff = Void pointer to the buffer to reallocate.

                        pintNBytes  = Integer (to enforce a limit of 2 GB) bytes
                                      to allocate. See Remarks for restrictions.


                        phHeap      = Handle of the heap upon which to perform
                                      the operation.

    Out:                If the function succeeds, the return value is a pointer
                        to the reallocated buffer, which has had its additional
                        bytes, if any, initialized with NULL bytes. Since it
                        reports through SetLastError, it is safe to call
                        HeapFree directly to discard the memory.
    ----------------------------------------------------------------------------
*/

LPVOID LIBSPEC_WWKERNELLIBWRAPPER_API ReAllocAnyHeapBufSEH_P6C
(
    LPVOID  plpCurrBuff ,
    CINT    pintNBytes ,
    HANDLE  phHeap
) ;

#if defined ( __cplusplus )
}
#endif  /* __cplusplus */
#endif  /* #if! defined ( _SEHHEAPALLOCATORS_DEFINED ) */