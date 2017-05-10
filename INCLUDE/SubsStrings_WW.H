#if !defined ( _SUBSSTRINGS_WW__39746269_37A7_4DDB_A4C1_6D7DD5720CA8__INCLUDED_ )
#define _SUBSSTRINGS_WW__39746269_37A7_4DDB_A4C1_6D7DD5720CA8__INCLUDED_

/*
    ============================================================================

    Name:               SubsStrings_WW.H

    Library Header:     P6CStringLib1.H

    Library:            P6CStringLib1.dll (P6CStringLib1.lib)

    Synopsis:           This header declares a set of related substring routines
                        that are defined and exported by P6CStringLib1.dll and
                        listed in import library P6CStringLib1.lib.

    Remarks:            The functions declared herein are a small subset of the
                        routines exported by P6CStringLib1.dll. This header
                        joins a fairly long list of headers that declare other
                        related groups of routines exported by this ever-growing
                        library.

                        In this case, they were separated because the static
                        methods of a class that is exported by a new library use
                        some of them, and that method is defined in the header
                        that defines the class.

                        Since the local storage used by these functions is
                        allocated on the stack, and the functions that use the
                        printf family of functions use the multithreaded version
                        of the CRT library, I believe they are thread-safe.
                        However, since I have not tested them in a multithreaded
                        application, I cannot guarantee them to be so.

                        Functions Returning LPTSTRs
                        ---------------------------

                        All functions that return long pointers to strings
                        (LPTSTR) allocate memory to hold the strings from the
                        process heap.  The memory can be subsequently freed in
                        one of four ways.

                        1)  Call FreeDfltHeapBuf_P6C, which happens to be one of
                            the functions exported by WWKernelLibWrapper.dll.
                            C programmers may consult CopyStringToNewBuf_P6C.H
                            for its prototype, and should include this header,
                            as you include windows.h to avail yourself of the
                            functions in winbase.h.

                        2)  Call the Windows API HeapFree function directly,
                            passing the pointer, along with a handle to your
                            default process heap.

                        3)  Call macro FreeProcHeapMem_WW, which is defined in header
                            TcharMacros_WW.H, and expects an externally linked
                            variable named m_hProcHeap, which is of type HANDLE.

                        4)  Call macro FreeBuffer_WW, which is defined in header
                            TcharMacros_WW.H, and expects an externally linked
                            variable named m_hProcHeap, which is of type HANDLE.

                            However, if preprocessor symbol _HMAC_SHAX_MALLOC or
                            _MALLOC_AS_MEMORY_ALLOCATOR is defined, it calls
                            routine free, in the Standard C Runtime Library, and
                            expects a pointer to memory that was allocated by
                            malloc, realloc, or calloc, all of which also belong
                            to the Standard C Runtime Library.

                        The first method incurs slightly more overhead, because
                        it adds another frame to the call stack, and consumes
                        another small chunk of your stack, but it permits any
                        program that can call this library to discard the memory
                        with just one more call, rather than up to two calls to
                        the Windows API to use the second method.

                        Except as noted above, the third and fourth methods
                        generate code that expands into calls that implement the
                        second method.

                        Combined with symbol _MALLOC_AS_MEMORY_ALLOCATOR and the
                        companion macros listed in the table below cover many
                        use cases, using CRT functions from the malloc family.

                        --------------------------------------------------------
                        Name of Macro   Action Performed by Macro Code
                        --------------- ----------------------------------------
                        AllocBytes_WW   Allocate pCount bytes of memory.

                        AllocCString_WW Allocate enough memory to hold a
                                        null terminated string (a. k. a., a
                                        C string) of pCount chracters, null
                                        character and all.

                        AllocTchars_WW  Allocate enough memory to hold pCount
                                        characters.
                        --------------------------------------------------------

                        If you keep a handle to the default process heap handy
                        at all times, as I usually do, any of these methods
                        requires just one call, giving the second, third, and
                        fourth methods a slight performance edge.

    Author:             David A. Gray

    Created:            Wednesday, 07 September 2005

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
	2015/03/13 3.1.0.4 DAG Segregate the substring functions into a new self
                           contained header, SubsStrings_WW.H.

    2016/01/10 3.1.0.4 DAG Wrap the code that defines LIBSPEC_P6CSTRINGLIB1_API
                           in guard code, and incorporate my three-clause BSD
						   license.
    ============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

#include <windows.h>

//  ----------------------------------------------------------------------------
//  Define macros used in selected function declarations.
//
//  Note:   For this to work correctly, the module that defines a function must
//          define preprocessor constant _BUILDING_P6CSTRINGLIB1. Otherwise, the
//          wrong calling scheme, __declspec(dllimport), is generated.
//
//          There are no such special considerations for calling routines.
//  ----------------------------------------------------------------------------

#if defined ( _P6CSTRINGLIB1_DEFINED )
    #pragma message ( "SubsStrings_WW.H: Calling convention in this translation unit was established by P6CStringLib1.H." )
#else
    #if defined ( _BUILDING_P6CSTRINGLIB1 )
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
    #else
        #if defined ( _P6CSTRINGLIB1 )
            #define LIBSPEC_P6CSTRINGLIB1_API extern
        #else
            #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
        #endif  /* #if defined ( _P6CSTRINGLIB1 ) */
    #endif  /* #if defined ( _BUILDING_P6CSTRINGLIB1 ) */
#endif  /* #if defined ( _P6CSTRINGLIB1_DEFINED ) */

//  ----------------------------------------------------------------------------
//  Errors returned by StrReplace functions:
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_SR_ERROR_WW           ( 0x00000500 | APPLICATION_ERROR_MASK )

#define P6CSTRINGLIB1_SR_NULL_SOURCE_STR    ( 0x00000011 | P6CSTRINGLIB1_SR_ERROR_WW )
#define P6CSTRINGLIB1_SR_EMPTY_SOURCE_STR   ( 0x00000012 | P6CSTRINGLIB1_SR_ERROR_WW )

#define P6CSTRINGLIB1_SR_NULL_SEARCH_STR    ( 0x00000021 | P6CSTRINGLIB1_SR_ERROR_WW )
#define P6CSTRINGLIB1_SR_EMPTY_SEARCH_STR   ( 0x00000022 | P6CSTRINGLIB1_SR_ERROR_WW )


//  ----------------------------------------------------------------------------
//  Define required constants that may not yet be defined.
//  ----------------------------------------------------------------------------

#if !defined ( TWO_TO_THE_POWER_OF_16_P6C )
    #define TWO_TO_THE_POWER_OF_16_P6C       65536
#endif  /* #if !defined ( TWO_TO_THE_POWER_OF_16_P6C ) */

#if !defined ( STRREPLACE_MAX_TCHARS_P6C )
    #define STRREPLACE_MAX_TCHARS_P6C       ( TWO_TO_THE_POWER_OF_16_P6C - 1 )
#endif  /* #if !defined ( STRREPLACE_MAX_TCHARS_P6C ) */

#if !defined ( STRREPLACE_MAX_BYTES_P6C )
    #define STRREPLACE_MAX_BYTES_P6C        ( STRREPLACE_MAX_TCHARS_P6C + 1 ) * sizeof ( TCHAR )
#endif  /* #if !defined ( STRREPLACE_MAX_BYTES_P6C ) */

#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */

/*
    ============================================================================

    Name:				StrLeft_P6C

    Synopsis:			Return a new string containing the left-most (first N)
						characters of the input string.

    Arguments:			plpStrinput     = Pointer to string to be searched.

						plngNChars      = Number of characters to copy from 
										  plpStrinput.

    Returns:			If it succeeds, StrLeft_P6C returns a pointer to a new
						string containing the first plngNChars characters of
						input string plpStrinput.

    Remarks:			1)  There are both Unicode (wide character) and ANSI 
							(narrow character) versions of this function.

						2)  This function ALWAYS returns a pointer to a buffer
							allocated from the default process heap, that is
							exactly large enough to hold the returned string and
							its terminal null character.

    Created:			Thursday, 08 September 2005

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API StrLeftA_P6C
(
    LPCTSTR     plpStrinput ,
    const long  plngNChars
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API StrLeftW_P6C
(
    LPCTSTR     plpStrinput ,
    const long  plngNChars
) ;

#if defined ( UNICODE )
    #define StrLeft_P6C StrLeftW_P6C
#else
    #define StrLeft_P6C StrLeftA_P6C
#endif  /* #if defined ( UNICODE ) */


/*
    ============================================================================

    Name:				StrReplace_P6C

    Synopsis:			Given an input string to search, a substring to replace,
						and a replacement substring, replace all occurrences of
						the first substring with the second, returning a new
						string.

    Arguments:			plpStrData      = Pointer to string to search

						plpToFind       = String to replace wherever it exists
										  in string plpStrData

						plpToReplace    = String to substitute in place of every
								          occurrence of string plpToFind

    Returns:			If it succeeds, StrReplace_P6C returns a pointer to a
						new string containing a copy of the string to which
						plpStrData points with every instance of the string to
						which plpToFind points replaced with a copy of the
						string to which plpToReplace points.

    Remarks:			1)  There are both ANSI (OEM/DBCS) and Unicode (wide
							character) versions of this function.

						2)  This function depends upon two assumptions about
							plpStrData both being true.

							a)  plpStrData points to a null terminated ASCII
								string (a C string).

							b)  The returned string will be less than or equal 
								to STRREPLACE_MAX_TCHARS_P6C TCHARS long,
								excluding the terminating null character. This
								is the upper limit of both the input and output
								string lengths.

						3)  This function ALWAYS returns a pointer to a buffer
							allocated from the default process heap, that is
							exactly large enough to hold the returned string and
							its terminal null character.

    Created:    Saturday, 10 December 2005 - Sunday, 11 December 2005

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API StrReplaceA_P6C
(
    LPCTSTR plpStrData ,
    LPCTSTR plpToFind ,
    LPCTSTR plpToReplace
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API StrReplaceW_P6C
(
    LPCTSTR plpStrData ,
    LPCTSTR plpToFind ,
    LPCTSTR plpToReplace
) ;

#if defined ( UNICODE )
    #define StrReplace_P6C  StrReplaceW_P6C
#else
    #define StrReplace_P6C  StrReplaceA_P6C
#endif  /* #if defined ( UNICODE ) */


/*
    ============================================================================

    Name:				StrRight_P6C

    Synopsis:			Return a new string containing the right-most (last N)
						characters of the input string.

    Arguments:			plpStrinput     = Pointer to string to be extracted.

						plngNChars      = Number of characters to copy from
										  plpStrinput.

    Returns:			If it succeeds, StrRight_P6C returns a pointer to a new
						string containing the last plngNChars characters of
						input string plpStrinput.

    Remarks:			1)  There are both Unicode (wide character) and ANSI
							(narrow character) versions of this function.

						2)  This function ALWAYS returns a pointer to a buffer
							allocated from the default process heap, that is
							exactly large enough to hold the returned string and
							its terminal null character.

    Created:			Saturday, 10 September 2005

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API StrRightA_P6C
(
    LPCTSTR     plpStrinput ,
    const long  plngNChars
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API StrRightW_P6C
(
    LPCTSTR     plpStrinput ,
    const long  plngNChars
) ;

#if defined ( UNICODE )
    #define StrRight_P6C    StrRightW_P6C
#else
    #define StrRight_P6C    StrRightA_P6C
#endif  /* #if defined ( UNICODE ) */


/*
    ============================================================================

    Name:				StrSub_P6C

    Synopsis:			Return a new string containing the specified number of
						characters, starting at a specified position in the input
						string.

    Arguments:			plpStrinput     = Pointer to string to be extracted.

						plngStartPos    = Position (1 based) of first character.

						plngNChars      = Number of characters to copy from
										  plpStrinput.

    Returns:			If it succeeds, StrSub_P6C returns a pointer to a new
						string containing no more than plngNChars characters
						extracted from input string plpStrinput. If there are
						fewer than plngNChars between the character at position
						plngStartPos and the end of the string, all characters,
						starting with that character, are copied into the output
						buffer.

    Remarks:			1)  There are both Unicode (wide character) and ANSI
							(narrow character) versions of this function.

						2)  This function ALWAYS returns a pointer to a buffer
							allocated from the default process heap, that is
							exactly large enough to hold the returned string and
							its terminal null character.

    Created:			Saturday, 10 September 2005

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API StrSubA_P6C
(
    LPCTSTR    plpStrinput ,
    const long plngStartPos ,
    const long plngNChars
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API StrSubW_P6C
(
    LPCTSTR    plpStrinput ,
    const long plngStartPos ,
    const long plngNChars
) ;

#if defined ( UNICODE )
    #define StrSub_P6C  StrSubW_P6C
#else
    #define StrSub_P6C  StrSubA_P6C
#endif  /* #if defined ( UNICODE ) */

#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /* #if !defined ( _SUBSSTRINGS_WW__39746269_37A7_4DDB_A4C1_6D7DD5720CA8__INCLUDED_ ) */