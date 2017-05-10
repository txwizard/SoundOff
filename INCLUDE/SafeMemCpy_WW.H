#ifndef _SAFEMEMCPY_WW_INCLUDED
#define _SAFEMEMCPY_WW_INCLUDED

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /*  #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

/*
    ============================================================================

    Name:               SafeMemCpy_WW.H

    Library:            SafeMemCpy.dll (SafeMemCpy.lib)

    Synopsis:           This is the header file for a library of safe (from a
                        security perspective) routines for copying bytes and
                        strings into various parts of buffers allocated ffrom a
                        heap.

    Remarks:            These functions differ from similar routines in the CRT
                        library, which they overlay, because they take steps to
                        ensure that the destination buffer acommodates the copy
                        operation. If the buffer is too small, they attempt to
                        enlarge it. If the buffer cannot be enlarges, these
                        routines set a status code and fail.

    Author:             David A. Gray

    Copyright:          2013, David A. Gray. All rights reserved world wide.

    Date Written:       Sunday, 21 April 2013 - Monday, 06 May 2013

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version    Author Synopsis
    ---------- ---------- ------ ----------------------------------------------
    2013/05/06 1, 0, 0, 1 DAG    First working native Win32 implementation.

    2013/05/12 1, 1, 0, 2 DAG    1) Return the length of the completed string as
                                    an OUT parameter.

                                 2) Replace _WIN32_SAFEMEMCPY as a default with
                                    _ANSI_SAFEMEMCPY as an alternative, to build
                                    the ANSI implementation of the library. This
                                    has the effect of making a native Win32
                                    build the default.

    2013/10/13 1, 1, 0, 2 DAG    This is a documentation and formatting update.
                                 Since the code is unchanged, and I see no good
                                 reason to increment the version number, I left
                                 the version number unchanged from the value to
                                 which it was set for the last update,
                                 on 2013/05/12 (5 months and 1 day ago).

                                 1) Correct the name of the import library, to
                                    SafeMemCpy.lib, from SafeMemCpy_WW.lib,
                                    which has the temerity to not exist!

                                 2) Correct a couple of other typographical
                                    errors found in the course of incorporating
                                    SafeMemCpyTchars_WW into a major upgrade of
                                    an old program.

    2017/04/16 1, 1, 0, 2 DAG    Insert spaces between several words that ran
                                 together. I discovered these errors during a
                                 review of the specifications. Since this change
                                 is confined to comments, nothing needs to be
                                 rebuilt, and the version is unchanged.
    ============================================================================
*/


//  ----------------------------------------------------------------------------
//  Define macros used in selected function declarations.
//
//  Note:   For this to work correctly, the source file in which the function is
//          defined MUST define the preprocessor constant, _BUILDING_SAFEMEMCPY.
//          Otherwise, the wrong calling scheme, __declspec(dllimport), is
//          generated.
//
//          Calling routines MUST NOT define _BUILDING_SAFEMEMCPY. They will see
//          the calling convention as __declspec(dllimport).
//
//          By default, the library is built to rely on a mix of native Win32
//          memory management routines and the memory copy routines defined in
//          the C runtime library.
//
//          To build a version that relies exclusively on C runtime library
//          routines, define _ANSI_SAFEMEMCPY.
//
//          Undefine _ANSI_SAFEMEMCPY to build a library that calls the Windows
//          memory management routines directly, rather than through their CRT
//          wrappers. By eliminating the overhead and extra layer of function
//          calls, the Win32 library runs more efficiently on a Win32 platform.
//          Specifically, since the CRT routines (malloc and msize) call
//          HeapAlloc and HeapSize, respectively, eliminating them from a Win32
//          build eliminates a stack frame and some duplicated activities.
//  ----------------------------------------------------------------------------

#ifdef  _ANSI_SAFEMEMCPY
    #pragma message("Compiling a pure ANSI C version.")
    #define LIBSPEC_SAFEMEMCPY_API __stdcall
#else
    #pragma message("Compiling a native Win32 version.")
    #ifdef  _BUILDING_SAFEMEMCPY
        #pragma message("Compiling a module of the SafeMemCpy_WW library.")
        #define LIBSPEC_SAFEMEMCPY_API __declspec(dllexport)
    #else
        #define LIBSPEC_SAFEMEMCPY_API __declspec(dllimport)
    #endif  /* _BUILDING_SAFEMEMCPY */
#endif  /*  #ifdef  _ANSI_SAFEMEMCPY */


//  ----------------------------------------------------------------------------
//  The native Win32 version needs windows.h. Otherwise, omit it.
//  ----------------------------------------------------------------------------

#ifndef  _ANSI_SAFEMEMCPY
    #include <windows.h>
#endif  /*  #ifndef  _ANSI_SAFEMEMCPY */


//  ----------------------------------------------------------------------------
//  All configurations need stdlib.h.
//  ----------------------------------------------------------------------------

#include <STDLIB.H>

//  ----------------------------------------------------------------------------
//  These typedefs simplify building native Win32 and ANSI C configurations from
//  the same source code.
//  ----------------------------------------------------------------------------

#ifdef  _ANSI_SAFEMEMCPY
    typedef const TCHAR *                   SAFEMEMCPY_LPSZIN ;
    typedef       TCHAR *                   SAFEMEMCPY_LPSZOUT ;
    typedef const unsigned int              SAFEMEMCPY_N_TCHARS_IN ;
    typedef       unsigned int              SAFEMEMCPY_N_TCHARS_WORK ;
    typedef       unsigned int              SAFEMEMCPY_N_BYTES ;
    typedef       unsigned int              SAFEMEMCPY_N_TCHARS_OUT ;
    typedef       SAFEMEMCPY_N_TCHARS_OUT * LPSAFEMEMCPY_N_TCHARS_OUT ;
#else
    typedef LPCTSTR                         SAFEMEMCPY_LPSZIN ;
    typedef LPTSTR                          SAFEMEMCPY_LPSZOUT ;
    typedef const DWORD                     SAFEMEMCPY_N_TCHARS_IN ;
    typedef       DWORD                     SAFEMEMCPY_N_TCHARS_WORK ;
    typedef       DWORD                     SAFEMEMCPY_N_BYTES ;
    typedef       unsigned int              SAFEMEMCPY_N_TCHARS_OUT ;
    typedef       SAFEMEMCPY_N_TCHARS_OUT * LPSAFEMEMCPY_N_TCHARS_OUT ;
#endif  /*  #ifdef  _ANSI_SAFEMEMCPY */


//  ----------------------------------------------------------------------------
//  The following constants simplify documenting specifying buffer offsets.
//  ----------------------------------------------------------------------------

#define SAFEMEMCPY_START_OF_BUFFER          0x00000000
#define SAFEMEMCPY_STRLEN_UNKNOWN           0x00000000
#define SAFEMEMCPY_STRLEN_EMPTY             0x00000000

//  ----------------------------------------------------------------------------
//  To differentiate them from system error codes, status codes returned by the
//  routines defined in this library are assigned from the range of application
//  defined error codes. The value of 0x00000500 reserves a range of 256 codes
//  for this library.
//  ----------------------------------------------------------------------------

#ifdef  _ANSI_SAFEMEMCPY
    #define SAFEMEMCPY_SC_ERROR_WW          ( 0x00000500 )
#else
    #define SAFEMEMCPY_SC_ERROR_WW          ( 0x00000500 | APPLICATION_ERROR_MASK )
#endif  /*  ifdef   _ANSI_SAFEMEMCPY */

#define SAFEMEMCPY_SC_NULL_OUTBUF_WW        ( 0x00000001 | SAFEMEMCPY_SC_ERROR_WW )
#define SAFEMEMCPY_SC_NULL_INBUF_WW         ( 0x00000002 | SAFEMEMCPY_SC_ERROR_WW )
#define SAFEMEMCPY_SC_EMPTY_INBUF_WW        ( 0x00000003 | SAFEMEMCPY_SC_ERROR_WW )
#define SAFEMEMCPY_SC_INVALID_INBUF_WW      ( 0x00000004 | SAFEMEMCPY_SC_ERROR_WW )


#if defined(__cplusplus)
extern "C"
{
#endif  /*  #if defined(__cplusplus) */


/*
    ============================================================================

    Name:       SafeMemCpyTchars_WW

    Synopsis:   Sefely copy a string of arbitrary length into the middle of a
                buffer. See Remarks.

    Arguments:  plpBuf          = Pointer to beginning of destination buffer.
                                  See Remarks for essential information.

                plpString       = Pointer to string to copy into plpBuf. See
                                  Remarks for important information.

                pdwOffset       = Offset, in TCHARS, where copying should begin.
                                  Se Remarks for important information.

                pdwStrLen       = Length of string plpString. See Remarks for
                                  essential imformation.

                plpNewLen       = Pointer to a LPSAFEMEMCPY_N_TCHARS_OUT (long
                                  pointer to an unsigned integer) that receives
                                  the total length of the complete string. See
                                  Remarks for essential information.

    Returns:    If the function succeeds, the return value is a pointer to the
                buffer. Note that the return value may differ from plpBuf. See
                Remarks for an important explanation of this, including its
                consequences for callers.

    Remarks:    1)  Output buffer plpBuf is expected to point to an addres that
                    was allocated from the default process heap. This is an
                    essential requirement, because the buffer may be expanded to
                    acommodate a copy that would otherwise run off the end,
                    causing a buffer overflow.

                    See item 5 for additional critical information related to
                    plpBuf.

                2)  String plpString may be allocated anwywhere. If the string
                    is empty, the function returns without doing anything,
                    setting a status code of SAFEMEMCPY_SC_EMPTY_INBUF_WW, which
                    is intended to call attention to the empty string, but is a
                    benign exception, which may be safely ignored unless it
                    matters to you that plpString is empty.

                3)  The offset specified by dwOffset MUST be specified in TCHARS
                    from the start of the buffer, and is taken at face value. As
                    a degenerate case, you may call this routine with a value of
                    zero to start copying at the beginning of the buffer. This
                    requirement is the result of the way the C compiler handles
                    offsets when it generates a call to memcpy, which requires
                    both of its pointer arguments to be cast to something other
                    than VOID.

                    The compiler adjusts the offsets based on the width of the
                    type to which the pointers are cast. Since this routine
                    casts its pointers to TCHAR, the widths are self-adjusting.
                    A benefit of this is that both ANSI and unicode routines
                    specify identical offsets, and the compiler fixes them up
                    for you.

                4)  Length dwStrLen is specified in TCHARs, a convenience which
                    eaables callers to pass a value returned by _tcslen() and
                    other intrinsic string length functions supported by other
                    programming languages (e. g., Basic, Fortran, Visual Basic).
                    If dwStrLen is zero, this routine calls _tcslen() to compute
                    it.

                5)  If the buffer to which plpBuf points can acommodate the copy
                    operation, the return value is also plpBuf. However, if the
                    buffer must be moved to enlarge it, the return value will
                    differ from the input value.

                    When this happens, pointer plpBuf is invalid, and may never
                    again be referenced without producing a memory access
                    violation.

                    To avoid this, do one of two things in your routine.

                    a)  Use the same variable name for both argument plpBuf and
                        the return value.

                        Since arguments to routines that adhere to the __stdcall
                        calling convention are passed by value, this practice is
                        completely safe, and is legal in most programming
                        languages.

                    b)  If your programming language forbids using the same name
                        for an argument to a function and its return value, do
                        one of the following.

                        i)  if your programming language understands pointers,
                            test the equality of the two values, and, if they
                            differ, assign the return value to the argument.

                        ii) Even if your language understands pointers, you may
                            safely assign the return value to the variable that
                            you used for the first argument, preferably as soon
                            as the function returns.

                6)  This routine makes no guarantees about the integrity of a
                    string. However, if the buffer contained a null terminated
                    string on entry AND the terminating null character is at the
                    location to which pdwOffset points, the returned buffer is
                    guaranteed to hold a longer null terminated string.

                7)  In connection with the above, the value returned through the
                    lpNewLen pointer is the overall length of a string that
                    starts at the beginning of the buffer and ends at the end of
                    the copied string. This will be true if:

                    a)  The offset is zero, which means that copying begins at
                        the start of the buffer, and ends at the end of input
                        string plpString.

                    b)  The offset is greater than zero, and the buffer contains
                        valid characters (non NULL) from its beginning up to at
                        least the offset specified by dwOffset.

                7)  There are both Unicode (wide character) and ANSI (narrow
                    character) versions of this function.

    Created:    Sunday, 21 April 2013 - Sunday, 28 April 2013

    ============================================================================
*/

SAFEMEMCPY_LPSZOUT LIBSPEC_SAFEMEMCPY_API SafeMemCpyTcharsA_WW
(
    SAFEMEMCPY_LPSZIN         plpBuf ,
    SAFEMEMCPY_LPSZIN         plpString ,
    SAFEMEMCPY_N_TCHARS_IN    pdwOffset ,
    SAFEMEMCPY_N_TCHARS_IN    pdwStrLen ,
    LPSAFEMEMCPY_N_TCHARS_OUT plpNewLen
) ;

SAFEMEMCPY_LPSZOUT LIBSPEC_SAFEMEMCPY_API SafeMemCpyTcharsW_WW
(
    SAFEMEMCPY_LPSZIN         plpBuf ,
    SAFEMEMCPY_LPSZIN         plpString ,
    SAFEMEMCPY_N_TCHARS_IN    pdwOffset ,
    SAFEMEMCPY_N_TCHARS_IN    pdwStrLen ,
    LPSAFEMEMCPY_N_TCHARS_OUT plpNewLen
) ;

#ifdef UNICODE
    #define SafeMemCpyTchars_WW   SafeMemCpyTcharsW_WW
#else
    #define SafeMemCpyTchars_WW   SafeMemCpyTcharsA_WW
#endif  /*  #ifdef UNICODE */


#ifdef __cplusplus
}
#endif  /* #ifdef __cplusplus */
#endif  /*  _SAFEMEMCPY_WW_INCLUDED */