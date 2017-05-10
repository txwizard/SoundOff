#if !defined ( AFX_FIXEDSTRINGBUFFERS_H__6D76DBB8_4AC2_4F5E_B45E_E009EB638A29__INCLUDED_ )
#define AFX_FIXEDSTRINGBUFFERS_H__6D76DBB8_4AC2_4F5E_B45E_E009EB638A29__INCLUDED_

/*
    ============================================================================

    File Name:          FixedStringBuffers.H

    Library Name:       FixedStringBuffers.dll (FixedStringBuffers.lib)

    File Synopsis:      This file declares a handful of functions that operate
                        independently of the named argument parsing engine that
                        is the chief export of this library. I segregated them
                        so that they can be applied in other contexts, some of
                        which may require "C" linkage and/or support for the
                        legacy ANSI character encoding.

    Date Created:       Tuesday, 03 February 2015  - Wednesday, 11 March 2015

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

    Date       Version By  Synopsis
    ---------- ------- --- -----------------------------------------------------
    2015/03/11 1.0.0.1 DAG Class completed, tested, and documented as part of
                           ELALogger.

    2015/03/31 1.2.0.1 DAG Merge into FixedStringBuffers.dll, a new library.

    2015/04/12 1.3.0.1 DAG Add routines for retrieving the address of a string
                           buffer for initializing a pointer in the caller's
                           scope.

    2015/07/09 1.4.0.1 DAG 1) Add function FB_FormatMessage2 as a companion to
                              FB_FormatMessage that takes its hint in the form
                              of a resource ID number.

                           2) Define FB_ERRMSG_SUPPRESS_MSGBOX for use by a
                              character mode programs as the value of argument
                              puintType to FB_ReportErrorViaStaticBuffer.

                              NOTE: I have no plans to create a companion to
                                    FB_ReportErrorViaStaticBuffer along the
                                    lines of what I did for FB_FormatMessage,
                                    because that is more work than I want to do
                                    right now.

    2015/08/28 1.5.0.1 DAG 1) Add FB_GetSprintFBufferTCHARs, implemented for
                              ANSI and wide character (Unicode) strings.

                           2) Implement FB_ERR_STRNG_NOT_FOUND_FOR_ID.

                           3) Implement a process-global flag that, when set,
                              causes FB_LoadString to raise an exception to be
                              caught by a Structured Exception Handler. Use
                              FB_SEN_Disable, FB_SEN_Enable, and FB_SEN_Toggle
                              to control it, and program your exception handler
                              to expect a FB_PVT_EXCEPTION_INFO structure filled
                              containing the argument list.

                           4) Implement pointer swaps in the error message token
                              replacement routine, replacing memory copies for
                              all but the last iteration.

                           5) FB_ReportErrorViaStaticBuffer no longer attempts
                              to deallocate the memory to which its argument,
                              plpAdditionalInfo, points. A routine should never,
                              ever deallocate memory, unless it was the routine
                              that allocated it, in which case, it MUST DO SO,
                              unless the contract it has with its callers says
                              otherwise.

    2015/09/26 1.6.0.1 DAG 1) Add function FB_FormatMessage3 as a companion to
                              FB_FormatMessage2, adding an instance handle, to
                              override the behavior of FB_FormatMessage2, by
                              directing the routine to a specific DLL that has
                              an instance handle.

                           2) Change FB_FormatMessage, FB_FormatMessage2, and
                              FB_FormatMessage3 to call GetLastError when
                              pdwLastError is ERROR_SUCCESS (zero).

                           3) Define a new macro, FB_LoadFixedString_AnyLib, as
                              a companion to FB_LoadFixedString_AnyBuf, adding
                              the instance handle to the exposed parameters. The
                              unused fourth parameter is kept out of sight, as
                              it is in FB_LoadFixedString_AnyBuf and the others.

                           4) Correct typographical and spelling errors flagged
                              by the new spelling checker add-in.

    2015/09/29 1.6.0.2 DAG Define symbolic constant macros for the other four
                           reserved buffers.

    2015/10/08 1.7.0.3 DAG Decorate all FB_ReportErrorViaStaticBuffer arguments
                           with a const storage class modifier. Only the LPTSTR,
                           plpAdditionalInfo, which becomes LPCTSTR, is affected
                           by this change, since the others are already constant
                           storage class. Along the same lines, replace LPUINT
                           with CLPUINT, a constant pointer, meaning that the
                           address is fixed, and the callee cannot change it,
                           but the callee may store things in the location to
                           which it points.

    2015/10/15 1.7.0.3 DAG Document the value returned by error reporting
                           routine FB_ReportErrorViaStaticBuffer.

                           NOTE:    This is a documentation change, affecting
                                    only comments embedded in this header. The
                                    code and its interfaces are unchanged.

    2015/10/27 1.8.0.1 DAG Extract the code that evaluates the status code fed
                           into the FormatMessage wrappers, replacing it with a
                           short function, defined in the private header, and
                           marked as a candidate for inline generation. The goal
                           of the function is to ensure consistency between the
                           status code stored internally and the one stored in
                           the process space maintained by Windows, and fix an
                           error in FB_FromatMessage that caused it to display
                           too much text.

    2017/02/04 1.8.0.2 DAG 1) Adjust the order in which headers are included to
                              compensate for changes discovered in the way the
                              Windows SDK headers are organized. These changes
                              adversely affected my CPP flag tests. This change
                              is entirely internal; no dependents need linking.

                           2) Correct the behavior of LoadStringFromDLL when the
                              requested string is not found.

                           3) Replace the public FB_PVT_EXCEPTION_INFO structure
                              with a private FB_PVT_EXCEPTION_INFO structure
                              filled with copies of the memory blocks to which
                              the two EXCEPTION_POINTERS structure point,
                              followed by copies of the argument list and key
                              local variables from the failing routine. To keep
                              the structure private, the exception handler is
                              implemented by a new routine, FB_SEH_Report, that
                              parses the data into a report, returning the
                              status code for use by the calling process.

                          4) Implement a new function, FB_etUnicodeStringPointer
                             that supports using null terminated string
                             resources in situ.

                           ToDo: Investigate the behavior of FB_FormatMessage
                                 with the decimal format string. I think the
                                 problem is in the lookup table, but I am in no
                                 hurry to fix it, since i never use this option.

                                 Replace ProcessInfo.dll with ProcessInfo32.dll.
    ============================================================================
*/

#if _MSC_VER > 1000
    #pragma once
#endif // _MSC_VER > 1000

#include <windows.h>                    // Core Windows stuff
#include <Const_Typedefs_WW.H>          // Add typedefs that I haven't found in the Platform SDK.

#include <WWStandardErrorMessages.H>    // Define the standard application defined status codes and associated messages.

//  ----------------------------------------------------------------------------
//  The following ifdef block is the standard way of creating macros which make
//  exporting from a DLL simpler. All files within this DLL are compiled with
//  the FIXEDSTRINGBUFFERS_EXPORTS symbol defined on the command line.
//
//  This symbol should not be defined on any project that uses this DLL. This
//  way, any other project whose source files include this file see
//  FIXEDSTRINGBUFFERS_API functions as being imported from a DLL, wheras this
//  DLL sees symbols defined with this macro as being exported.
//  ----------------------------------------------------------------------------

#if defined ( FIXEDSTRINGBUFFERS_EXPORTS )
    #define FIXEDSTRINGBUFFERS_API      __declspec(dllexport)
#else
    #define FIXEDSTRINGBUFFERS_API      __declspec(dllimport)
#endif  /* #if defined ( FIXEDSTRINGBUFFERS_EXPORTS ) */


//  ----------------------------------------------------------------------------
//  Define status codes that may be returned by the library routines.
//  ----------------------------------------------------------------------------

//  ---------------------------------------------------
//  Exceptions raised by FB_LoadString:
//  ---------------------------------------------------

#define FB_LOADSTRING_ERRORS            ( 0x00020000 | APPLICATION_ERROR_MASK      )

#define FB_ERR_LS_INVALID_BUF_IDX       ( 0x00000001 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_LS_STD_MSG_DLLNAME       ( 0x00000002 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_LS_NO_STRING_DLLNAME     ( 0x00000003 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_PATHREMOVEFILESPEC       ( 0x00000004 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_STRNG_NOT_FOUND_FOR_ID   ( 0x00000010 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_ABANDONED_MUTEX          ( 0x00000041 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_MUTEX_WAIT_TIMEOUT       ( 0x00000042 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_MUTEX_INTERNAL_ERROR_1   ( 0x00000043 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_MUTEX_INTERNAL_ERROR_2   ( 0x00000044 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_MUTEX_INTERNAL_ERROR_3   ( 0x00000045 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_MUTEX_INTERNAL_ERROR_4   ( 0x00000081 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_MUTEX_INTERNAL_ERROR_5   ( 0x00000082 | FB_LOADSTRING_ERRORS        )
#define FB_ERR_MUTEX_INTERNAL_ERROR_6   ( 0x00000083 | FB_LOADSTRING_ERRORS        )

//  ---------------------------------------------------
//  Exceptions raised by FB_Replace:
//  ---------------------------------------------------

#define FB_REPLACE_ERRORS               ( 0x00040000 | APPLICATION_ERROR_MASK      )

#define FB_ERR_REPL_SRCH_CANNOT_BE_NULL ( 0x00000001 | FB_REPLACE_ERRORS           )
#define FB_ERR_REPL_FIND_CANNOT_BE_NULL ( 0x00000002 | FB_REPLACE_ERRORS           )
#define FB_ERR_REPL_BUFFER_TOO_SMALL    ( 0x00000003 | FB_REPLACE_ERRORS           )

//  ---------------------------------------------------
//  Exceptions raised by FB_ReportErrorViaStaticBuffer:
//  ---------------------------------------------------

#define FB_REPORT_VIA_STATIC_BUFFER     ( 0x00080000 | APPLICATION_ERROR_MASK      )
#define FB_ERR_INCONSISTENT_ARRAYS      ( 0x00000001 | FB_REPORT_VIA_STATIC_BUFFER )

//  ----------------------------------------------------------------------------
//  Define specialized symbols used in these routines, rather than waste the
//  overhead of two whole header files, one of which is very large, for four
//  symbols. To prevent them being redefined and raising a benign, but annoying,
//  compiler warning if either of those headers has already entered the compiler
//  input stream, I posted guards around them.
//  ----------------------------------------------------------------------------

#if !defined ( __STANDARDFIXEDSTORAGE_WW_INCLUDED__ )
    #ifdef UNICODE
        typedef unsigned short *        LPSFSBUF ;
    #else
        typedef char *                  LPSFSBUF ;
    #endif  /* #ifdef UNICODE */
#endif  /* #if !defined ( __STANDARDFIXEDSTORAGE_WW_INCLUDED__ ) */

#define FB_INVALID_RES_ID               ZERO_WW
#define FB_NO_STRING                    ZERO_WW

//  ----------------------------------------------------------------------------
//  Define specialized typedefs for use as resource ID argument types.
//  ----------------------------------------------------------------------------

typedef const unsigned int              FB_RES_STRING_ID ;

//  ----------------------------------------------------------------------------
//  Define specialized constants for use as arguments.
//
//  NOTE:   A console program has a null instance handle, I use a NULL instance
//          handle as a signal to GetAnyResource_WW() to look for the requested
//          resource string in the EXE that was first loaded into the process.
//  ----------------------------------------------------------------------------

#define FB_LOOK_IN_THIS_EXE            0x00000000  // See note above.

//  ----------------------------------------------------------------------------
//  If string resource buffers are configured, FB_FIRST_BUFFER_INDEX is always
//  valid.
//  ----------------------------------------------------------------------------

#if !defined ( ARRAY_NEXT_ELEMENT_P6C )
    #define ARRAY_NEXT_ELEMENT_P6C      0x00000001
#endif  /* ARRAY_NEXT_ELEMENT_P6C */

#define FB_FIRST_BUFFER_INDEX           0x00000000
#define FB_GUARANTEED_BUFFER            FB_FIRST_BUFFER_INDEX
#define FB_ERRMSG_SUPPRESS_MSGBOX       0x00000000

#define FB_STRING_BUFFER_INDEX_1_OF_5   FB_FIRST_BUFFER_INDEX
#define FB_STRING_BUFFER_INDEX_2_OF_5   ( FB_STRING_BUFFER_INDEX_1_OF_5  + ARRAY_NEXT_ELEMENT_P6C )
#define FB_STRING_BUFFER_INDEX_3_OF_5   ( FB_STRING_BUFFER_INDEX_2_OF_5  + ARRAY_NEXT_ELEMENT_P6C )
#define FB_STRING_BUFFER_INDEX_4_OF_5   ( FB_STRING_BUFFER_INDEX_3_OF_5  + ARRAY_NEXT_ELEMENT_P6C )
#define FB_STRING_BUFFER_INDEX_5_OF_5   ( FB_STRING_BUFFER_INDEX_4_OF_5  + ARRAY_NEXT_ELEMENT_P6C )

#define FB_SPRINTF_BUFFER_INDEX_1_OF_5  FB_FIRST_BUFFER_INDEX
#define FB_SPRINTF_BUFFER_INDEX_2_OF_5  ( FB_SPRINTF_BUFFER_INDEX_1_OF_5 + ARRAY_NEXT_ELEMENT_P6C )
#define FB_SPRINTF_BUFFER_INDEX_3_OF_5  ( FB_SPRINTF_BUFFER_INDEX_2_OF_5 + ARRAY_NEXT_ELEMENT_P6C )
#define FB_SPRINTF_BUFFER_INDEX_4_OF_5  ( FB_SPRINTF_BUFFER_INDEX_3_OF_5 + ARRAY_NEXT_ELEMENT_P6C )
#define FB_SPRINTF_BUFFER_INDEX_5_OF_5  ( FB_SPRINTF_BUFFER_INDEX_4_OF_5 + ARRAY_NEXT_ELEMENT_P6C )

#if !defined ( FB_HIDE_LENGTH )
    #define FB_HIDE_LENGTH              0x00000000
#endif  /* #if !defined ( FB_HIDE_LENGTH ) */

#if defined ( WWSTANDARDERRORMESSAGES_DEFINED )
    #define RESERVED_FOR_WW_STD_ERRORS  ( IDS_STD_ERRMSG_BAD_HEAP - 1 )
#else
    #define RESERVED_FOR_WW_STD_ERRORS  0x00007D00
#endif  /* #if defined ( WWSTANDARDERRORMESSAGES_DEFINED ) */


//  ----------------------------------------------------------------------------
//  Call FB_ReportErrorViaStaticBuffer, passing the following symbolic constant
//  as your pdwLastError value to let it call GetLastError for you, and return
//  the result as its own return value.
//  ----------------------------------------------------------------------------

#define FB_REVSB_CALL_GETLASTERROR      ERROR_SUCCESS

//  ----------------------------------------------------------------------------
//  The following macros expand to the substitution tokens defined and used by
//  FB_ReportErrorViaStaticBuffer. Substitutions are performed by a case
//  sensitive string substitution routine imported from the C runtime library.
//  ----------------------------------------------------------------------------

#define FB_ADDL_INFO_TOKEN              ( _T ( "$$ADDL_INFO$$" ) )
#define FB_LAST_ERROR_DEC_TOKEN         ( _T ( "$$LAST_ERROR_DEC$$" ) )
#define FB_LAST_ERROR_HEX_TOKEN         ( _T ( "$$LAST_ERROR_HEX$$" ) )

//  ----------------------------------------------------------------------------
//  Use members of this enumeration to specify the penmCodeFormat argument to
//  FB_FormatMessage, FB_FormatMessage2, and FB_ReportErrorViaStaticBuffer.
//  ----------------------------------------------------------------------------

typedef enum _STATUS_CODE_FORMAT2
{
    SCF2_HEXADECIMAL ,   // 0
    SCF2_DECIMAL ,       // 1
    SCF2_OCTAL           // 2
} STATUS_CODE_FORMAT2 ;

#define FB_SCF2_HEXADECIMAL             SCF2_HEXADECIMAL
#define FB_SCF2_DECIMAL                 SCF2_DECIMAL
#define FB_SCF2_OCTAL                   SCF2_OCTAL

typedef       STATUS_CODE_FORMAT2       FB_STATUS_CODE_FORMAT2 ;
typedef const STATUS_CODE_FORMAT2       CSTATUS_CODE_FORMAT2 ;
typedef const FB_STATUS_CODE_FORMAT2    CFB_STATUS_CODE_FORMAT2 ;

//  ----------------------------------------------------------------------------
//  Use these macros to invoke FB_LoadString with its third and fourth arguments
//  set to default values.
//  ----------------------------------------------------------------------------

#define FB_LoadFixedString_DfltBuf(pnID)                    \
FB_LoadString ( FB_LOOK_IN_THIS_EXE ,                       \
                pnID ,                                      \
                FB_GUARANTEED_BUFFER ,                      \
                FB_HIDE_LENGTH )

#define FB_LoadFixedString_AnyBuf(pnID, pBufIdx)            \
FB_LoadString ( FB_LOOK_IN_THIS_EXE ,                       \
                pnID ,                                      \
                pBufIdx ,                                   \
                FB_HIDE_LENGTH )

#define FB_LoadFixedString_AnyLib(pHInst, pnID, pBufIdx)    \
FB_LoadString ( pHInst ,                                    \
                pnID ,                                      \
                pBufIdx ,                                   \
                FB_HIDE_LENGTH )

#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */
    //  ------------------------------------------------------------------------
    //  Function Name:  FB_FindLineEnd
    //
    //  Abstract:       Return a pointer to the first line break character found
    //                  in a string.
    //
    //  In:             plpString is a pointer to the beginning of the string to
    //                  evaluate for line ending characters. The memory to which
    //                  plpString points is assumed to be null terminated.
    //
    //                  pintPosEnd is the position of the last character in the
    //                  input string.
    //
    //  Out:            If the last character of the string matches ANY valid
    //                  line ending character (CR or LF), the return value
    //                  points to it. Otherwise, the return value is NULL.
    //
    //  Remarks:        I stopped short of chopping it off, for three reasons.
    //
    //                  1) The function is more versatile if it confines itself
    //                     to the single task of finding the line break.
    //
    //                  2) Chopping it off is a single statement that generates
    //                     two machine instructions, wherever it happens.
    //
    //                  3) I want to write a real chopper, in assembler.
    //  ------------------------------------------------------------------------

    LPTSTR   FIXEDSTRINGBUFFERS_API __stdcall FB_FindLineEndA
        (
            LPCTSTR             plpString ,
            CINT                pintPosEnd
        ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API __stdcall FB_FindLineEndW
        (
            PCTSTR              plpString ,
            CINT                pintPosEnd
        ) ;


    //  ------------------------------------------------------------------------
    //  Function Name:  FB_SEH_Report
    //
    //  Abstract:       Format and display a message that fully describes the
    //                  error reported by one of the LoadString functions.
    //
    //  In:             plpMessageTemplate  = Pointer to a tokenized string
    //                                        to display after it is filled from
    //                                        the data in a private structure
    //                                        that is filled by the private
    //                                        routine that is called when an
    //                                        exception is raised. Please see
    //                                        the Remarks section for details.
    //
    //                  puintType           = This CUINT (a const UINT, via a
    //                                        typedef defined herein) is either
    //                                        of the following.
    //
    //                                        1) To display the message in a
    //                                           MessageBox, specify a Valid,
    //                                           nonzero UTYPE.
    //
    //                                        2) To display the message in the
    //                                           standard error stream, set this
    //                                           value to zero.
    //
    //  Out:            The return value is the original status code that was
    //                  sent to the exception handler, which may be a system or
    //                  application defined status code.
    //
    //  Remarks:        Input string plpMessageTemplate is an ordinary text
    //                  string, such as one might expect to find in a string
    //                  table, except that it employs the tokens shown in the
    //                  following table to indicate where parameters should be
    //                  inserted.
    //
    //                      ----------------------------------------------
    //                      Token String            Replacement Value
    //                      ----------------------  ----------------------
    //                      $$SourceDLLName$$       plpSourceDLLName
    //                      $$StringID$$            puintStringID
    //                      $$BufferID$$            puintBufferID
    //                      $$LengthReceptor$$      plpuintLength
    //                      $$SatelliteDLLHandle$$  phSatelliteDLL
    //                      ----------------------------------------------
    //
    //                  All of the above tokens are arguments to one or another
    //                  of the LoadString functions, although phSatelliteDLL is
    //                  internally generated and used by LoadStringFromDLL when
    //                  it loads the named DLL.
    //
    //                  Since it deals in strings, there are ANSI and Unicode
    //                  (wide character) implementations that behave identically
    //                  in all other respects.
    //  ------------------------------------------------------------------------

    DWORD    FIXEDSTRINGBUFFERS_API __stdcall FB_SEH_ReportA
        (
            LPCTSTR             plpMessageTemplate ,                            // Pointer to string containing a tokenized template from which to construct the message.
            CUINT               puintType                                       // Valid UTYPE nonzero for a MessageBox - see Remarks above
        ) ;
    DWORD    FIXEDSTRINGBUFFERS_API __stdcall FB_SEH_ReportW
        (
            LPCTSTR             plpMessageTemplate ,                            // Pointer to string containing a tokenized template from which to construct the message.
            CUINT               puintType                                       // Valid UTYPE nonzero for a MessageBox - see Remarks above
        ) ;

    //  ------------------------------------------------------------------------
    //  Function Names: FB_FormatMessage    Takes its hint as a string pointer
    //                  FB_FormatMessage2   Takes its hint as a resource ID
    //                  FB_FormatMessage3   Takes its hint as a module handle
    //                                      and resource ID
    //
    //  Abstract:       Format a message that fully describes the error reported
    //                  by one of the LoadString functions in this library, or a
    //                  system status code from a Windows API function.
    //
    //  In:             plpHint             = Pointer to a "hint" string with
    //                                        which to prefix the message
    //
    //                  phSourceModule      = CHMODULE (const HMODULE), handle
    //                                        to the module from which to load
    //                                        the string identified by the
    //                                        puintHintStringID argument
    //
    //                  puintHintStringID   = FB_RES_STRING_ID Resource ID of
    //                                        the string to display at the
    //                                        beginning of the message, offering
    //                                        hints to direct the investigator
    //                                        to the source of the error
    //
    //                  pdwLastError        = DWORD of message number to format
    //
    //                  penmCodeFormat      = CFB_STATUS_CODE_FORMAT2, a const
    //                                        member of the STATUS_CODE_FORMAT2
    //                                        enumeration to specify the desired
    //                                        format to use for the result code
    //
    //  Out:            The return value is a string, suitable for use as the
    //                  Prompt argument of a MessageBox, or, when followed by a
    //                  newline, as the output of a console print message.
    //
    //  Remarks:        The objective of these three routines is to make the
    //                  thankless task of reporting a system status code and its
    //                  message as effortless as possible.
    //
    //                  These routines use the FormatMessage system routine to
    //                  generate a printable message from the status code
    //                  reported by a system routine.
    //
    //                  The difference between them is the form taken by the
    //                  argument(s) that specify the hint that becomes the
    //                  message prefix. FB_FormatMessage has the same arguments
    //                  as its predecessor, EM_ShowMsgOnConsole_WW, and behaves
    //                  identically, except that it returns a string for use by
    //                  its caller to render the report in the desired manner.
    //                  The other two routines accept a string resource ID and,
    //                  in the third case, a module handle, which they use to
    //                  load the hint string.
    //
    //  ToDo:           Investigate the behavior of FB_FormatMessage with the
    //                  decimal format string. I think the problem is in the
    //                  lookup table , but I am in no hurry to fix it , since I
    //                  have never used this option.
    //  ------------------------------------------------------------------------

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_FormatMessageA
    (
        LPCTSTR                 plpHint ,                                       // String to display at beginning of message, offering hints to direct the investigator to the source of the error
        CDWORD                  pdwLastError ,                                  // Result returned by GetLastError, from which to format a SYSTEM error message. If set to NO_ERROR (zero), GetLastError is called.
        CFB_STATUS_CODE_FORMAT2 penmCodeFormat                                  // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
    ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_FormatMessageW
    (
        LPCTSTR                 plpHint ,                                       // String to display at beginning of message, offering hints to direct the investigator to the source of the error
        CDWORD                  pdwLastError ,                                  // Result returned by GetLastError, from which to format a SYSTEM error message. If set to NO_ERROR (zero), GetLastError is called.
        CFB_STATUS_CODE_FORMAT2 penmCodeFormat                                  // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
    ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_FormatMessage2A
    (
        FB_RES_STRING_ID        puintHintStringID ,                             // Resource ID of string to display at beginning of message, offering hints to direct the investigator to the source of the error
        CDWORD                  pdwLastError ,                                  // Result returned by GetLastError, from which to format a SYSTEM error message. If set to NO_ERROR (zero), GetLastError is called.
        CFB_STATUS_CODE_FORMAT2 penmCodeFormat                                  // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
    ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_FormatMessage2W
    (
        FB_RES_STRING_ID        puintHintStringID ,                             // Resource ID of string to display at beginning of message, offering hints to direct the investigator to the source of the error
        CDWORD                  pdwLastError ,                                  // Result returned by GetLastError, from which to format a SYSTEM error message. If set to NO_ERROR (zero), GetLastError is called.
        CFB_STATUS_CODE_FORMAT2 penmCodeFormat                                  // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
    ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_FormatMessage3A
    (
        CHMODULE                phSourceModule ,                                // HINSTANCE of module containing the string, per LoadLibraryEx or DLLMain
        FB_RES_STRING_ID        puintHintStringID ,                             // Resource ID of string to display at beginning of message, offering hints to direct the investigator to the source of the error
        CDWORD                  pdwLastError ,                                  // Result returned by GetLastError, from which to format a SYSTEM error message. If set to NO_ERROR (zero), GetLastError is called.
        CFB_STATUS_CODE_FORMAT2 penmCodeFormat                                  // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
    ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_FormatMessage3W
    (
        CHMODULE                phSourceModule ,                                // HINSTANCE of module containing the string, per LoadLibraryEx or DLLMain
        FB_RES_STRING_ID        puintHintStringID ,                             // Resource ID of string to display at beginning of message, offering hints to direct the investigator to the source of the error
        CDWORD                  pdwLastError ,                                  // Result returned by GetLastError, from which to format a SYSTEM error message. If set to NO_ERROR (zero), GetLastError is called.
        CFB_STATUS_CODE_FORMAT2 penmCodeFormat                                  // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
    ) ;

    //  ------------------------------------------------------------------------
    //  Returns TRUE if the ErrorReported flag has been set, meaning that the
    //  last error has been returned to the caller.
    //  ------------------------------------------------------------------------

    BOOL     FIXEDSTRINGBUFFERS_API FB_GetfErrorReported ( ) ;

    //  ------------------------------------------------------------------------
    //  Return TRUE if the ErrorGenerated flag has been set, meaning that the
    //  last error message has been generated, but not yet returned to the
    //  caller.
    //  ------------------------------------------------------------------------

    BOOL     FIXEDSTRINGBUFFERS_API FB_GetfErrorGenerated ( ) ;

    //  ------------------------------------------------------------------------
    //  Retrieve the error message from the emergency resource string buffer
    //  (ANSI and Unicode versions).
    //  ------------------------------------------------------------------------

    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_GetlpErrMsgResStrA ( ) ;
    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_GetlpErrMsgResStrW ( ) ;

    //  ------------------------------------------------------------------------
    //  Retrieve the error message from the emergency sprintf buffer (ANSI and
    //  Unicode versions).
    //  ------------------------------------------------------------------------

    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_GetlpErrMsgSprintfA ( ) ;
    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_GetlpErrMsgSprintfW ( ) ;

    //  ------------------------------------------------------------------------
    //  Retrieve the address of one of the standard buffers reserved for use by
    //  the sprintf family of CRT routines. Use this convenience routine to get
    //  an address for use as the first argument to a sprintf function or to get
    //  the resulting string for subsequent use.
    //
    //  Note:   LPSFSBUF is cast to the appropriate type, depending on whether
    //          UNICODE is defined. Therefore, there are two entry points, and a
    //          macro to map the correct entry point to FB_GetSprintFBuffer.
    //
    //          The size of the returned buffer is the maximum supported by the
    //          sprintf routines, which is 1024 bytes.
    //  ------------------------------------------------------------------------

    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_GetSprintFBufferA
    (
        CUINT                   puintBufferID                                   // Specify the zero based index of the buffer whose address you need. The shipping version supports values from 0 to 4, inclusive
    ) ;

    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_GetSprintFBufferW
    (
        CUINT                   puintBufferID                                   // Specify the zero based index of the buffer whose address you need. The shipping version supports values from 0 to 4, inclusive
    ) ;

    //  ------------------------------------------------------------------------
    //  Get the number of sprintf buffers. Your index must be less than the
    //  returned value.
    //  ------------------------------------------------------------------------

    int      FIXEDSTRINGBUFFERS_API FB_GetSprintFBufferCount ( ) ;

    //  ------------------------------------------------------------------------
    //  Get the number of resource string buffers. Your index (puintBufferID)
    //  must be less than the returned value.
    //  ------------------------------------------------------------------------

    int      FIXEDSTRINGBUFFERS_API FB_GetResourceBufferCount ( ) ;

    //  ------------------------------------------------------------------------
    //  Get the size, in bytes, of each sprintf buffer. This is mostly FYI,
    //  since the sprintf family of routines don't ask how much room they have,
    //  and won't use more than 1024 bytes, which happens to be how big these
    //  buffers are.
    //  ------------------------------------------------------------------------

    int      FIXEDSTRINGBUFFERS_API FB_GetSprintFBufferBytes ( ) ;

    //  ------------------------------------------------------------------------
    //  Get the size, in TCHARs, of each sprintf buffer. This is required by the
    //  new "secure" sprintf family of routines add a parameter, sizeOfBuffer,
    //  which expects the maximum number of characters to store. Since the size
    //  of a TCHAR is dependent upon the character encoding, there are two of
    //  these, both mapped to symbolic entry point FB_GetSprintFBufferTCHARs.
    //  ------------------------------------------------------------------------

    int      FIXEDSTRINGBUFFERS_API FB_GetSprintFBufferTCHARsA ( ) ;
    int      FIXEDSTRINGBUFFERS_API FB_GetSprintFBufferTCHARsW ( ) ;

    //  ------------------------------------------------------------------------
    //  Get the size, in TCHARs, of each resource string buffer. This is mostly
    //  FYI, since these routines supply the information to LoadString, and the
    //  buffers accommodate the maximum supported length of a string resource,
    //  4097 characters.
    //  ------------------------------------------------------------------------

    int      FIXEDSTRINGBUFFERS_API FB_GetResourceBufferTChars ( ) ;

    //  ------------------------------------------------------------------------
    //  Retrieve the address of one of the standard buffers reserved for use by
    //  the FB_LoadString family of LoadString wrappers. Use this convenience
    //  routine to get an address when you need a locally scoped pointer to one
    //  of the fixed buffers.
    //
    //  These functions arose to provide a mechanism to simplify retrofitting an
    //  existing application to use these buffers and their associated routines.
    //
    //  Note:   LPSFSBUF is cast to the appropriate type, depending on whether
    //          UNICODE is defined. Therefore, there are two entry points, and a
    //          macro to map the correct entry point to FB_GetSprintFBuffer.
    //
    //          The size of the returned buffer is the maximum supported by the
    //          LoadString routines, which is 4097 characters (TCHARs).
    //  ------------------------------------------------------------------------

    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_GetlpResourceBufferA
    (
        CUINT                   puintBufferID                                   // Specify the zero based index of the buffer whose address you need. The shipping version supports values from 0 to 4, inclusive
    ) ;

    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_GetlpResourceBufferW
    (
        CUINT                   puintBufferID                                   // Specify the zero based index of the buffer whose address you need. The shipping version supports values from 0 to 4, inclusive
    ) ;

    //  ------------------------------------------------------------------------
    //  Use the LoadString system routine to load a string resource into a fixed
    //  buffer. The routine returns the address of the buffer, which is owned by
    //  the DLL that exports this function. The point of this routine is to be
    //  able to use LoadString without having to manage the required buffer.
    //
    //  This routine loads strings from a module that is already loaded into the
    //  current process, including the startup module. Since console programs
    //  don't have a designated HMODULE, specify LOOK_IN_THIS_EXE (NULL) to load
    //  from the console program image.
    //
    //  If the string is coming from a module that isn't loaded into the current
    //  process, use FB_LoadStringFromDLL, which lets you name a file from which
    //  to load the string.
    //  ------------------------------------------------------------------------

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_LoadStringA
    (
        CHMODULE                phSourceModule ,                                // HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
        FB_RES_STRING_ID        puintStringID ,                                 // Resource ID of string to load
        CUINT                   puintBufferID ,                                 // Zero based index of buffer to use - The shipping version supports values from 0 to 4, inclusive
        CLPUINT                 plpuintLength                                   // Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
    ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_LoadStringW
    (
        CHMODULE                phSourceModule ,                                // HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
        FB_RES_STRING_ID        puintStringID ,                                 // Resource ID of string to load
        CUINT                   puintBufferID ,                                 // Zero based index of buffer to use - The shipping version supports values from 0 to 4, inclusive.
        CLPUINT                 plpuintLength                                   // Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
    ) ;

    LPWSTR FIXEDSTRINGBUFFERS_API FB_etUnicodeStringPointer
    (
        CHMODULE                phSourceModule ,                                // HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
        FB_RES_STRING_ID        puintStringID ,                                 // Resource ID of string to load
        CLPUINT                 plpuintLength                                   // Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
    ) ;

    //  ------------------------------------------------------------------------
    //  Use the LoadString system routine to load a string resource into a fixed
    //  buffer. The routine returns the address of the buffer, which is owned by
    //  the DLL that exports this function. The point of this routine is to be
    //  able to use LoadString without having to manage the required buffer.
    //
    //  This routine loads strings from a module that is not currently loaded
    //  into the current process. The module named in plpSourceDLLName is loaded
    //  into the process, the string is copied into the fixed buffer, and the
    //  module is unloaded.
    //
    //  If the string is coming from a module that is already loaded into the
    //  current process, use FB_LoadString, which lets you specify the HMODULE
    //  handle from which to load the string.
    //  ------------------------------------------------------------------------

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_LoadStringFromDLLA
    (
        LPCTSTR                 plpSourceDLLName ,                              // Name of DLL, preferably fully qualified, must be reachable
        FB_RES_STRING_ID        puintStringID ,                                 // Resource ID of string to load
        CUINT                   puintBufferID ,                                 // Zero based index of buffer to use - The shipping version supports values from 0 to 4.
        CLPUINT                 plpuintLength                                   // Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
    ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_LoadStringFromDLLW
    (
        LPCTSTR                 plpSourceDLLName ,                              // Name of DLL, preferably fully qualified, must be reachable
        FB_RES_STRING_ID        puintStringID ,                                 // Resource ID of string to load
        CUINT                   puintBufferID ,                                 // Zero based index of buffer to use - The shipping version supports values from 0 to 4.
        CLPUINT                 plpuintLength                                   // Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
    ) ;

    //  ------------------------------------------------------------------------
    //  This routine implements a robust string replace function, which I first
    //  implemented in 2005, using dynamically allocated memory. In contrast,
    //  this routine uses a dedicated string resource buffer, and has provisions
    //  for returning the length of the new string through a pointer to simplify
    //  copying the returned string into your own buffer for further processing.
    //  ------------------------------------------------------------------------

    LPTSTR  FIXEDSTRINGBUFFERS_API  FB_ReplaceA
    (
        LPCTSTR                 plpStrData ,                                    // String into which to make substitutions
        LPCTSTR                 plpToFind ,                                     // Substring in plpStrData to replace
        LPCTSTR                 plpToReplace ,                                  // String to substitute into plpStrData for plpToFind - may be NULL or the empty string to remove plpToFind from plpStrData
        PUINT                   puintNewLength                                  // Pointer to unsigned integer to receive the length of the new string
    ) ;

    LPTSTR   FIXEDSTRINGBUFFERS_API FB_ReplaceW
    (
        LPCTSTR                 plpStrData ,                                    // String into which to make substitutions
        LPCTSTR                 plpToFind ,                                     // Substring in plpStrData to replace
        LPCTSTR                 plpToReplace ,                                  // String to substitute into plpStrData for plpToFind - may be NULL or the empty string to remove plpToFind from plpStrData
        PUINT                   puintNewLength                                  // Pointer to unsigned integer to receive the length of the new string
    ) ;

    //  ------------------------------------------------------------------------
    //  Use this routine to substitute your own caption for the default caption,
    //  which is the base name of the executable program that was first loaded
    //  into the current process. Pass in a NULL to use the default caption.
    //
    //  WARNING:    This routine is NOT thread-safe. Since I envision its usual
    //              application being in the startup code of the first thread, I
    //              dispensed with the complexity required to make it so.
    //
    //  IMPORTANT:  Specifying the default caption is semi-permanent; it cannot
    //              be subsequently changed except by calling this routine again
    //              with a new value. This approach pushes the overhead of
    //              getting the process EXE base name into this routine,
    //              whereas, if this routine is never called, the base name is
    //              retrieved as needed whenever a message box is displayed.
    //  ------------------------------------------------------------------------

    VOID     FIXEDSTRINGBUFFERS_API FB_SetMessageBoxCaptionA
    (
        LPCTSTR                 plpErrorMessageCaption                          // String to use as alternative caption when an error message is displayed in a MessageBox
    ) ;

    VOID     FIXEDSTRINGBUFFERS_API FB_SetMessageBoxCaptionW
    (
        LPCTSTR                 plpErrorMessageCaption                          // String to use as alternative caption when an error message is displayed in a MessageBox
    ) ;

    //  ------------------------------------------------------------------------
    //  Use this routine to translate the status codes reported by the other
    //  routines in this library, and signaled by returning NULL.
    //  ------------------------------------------------------------------------

    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_XlateFBStatusCodeA ( DWORD pdwStatusCode ) ;
    LPSFSBUF FIXEDSTRINGBUFFERS_API FB_XlateFBStatusCodeW ( DWORD pdwStatusCode ) ;

    //  ------------------------------------------------------------------------
    //  Use these routines to control whether the FB_LoadString routines raise
    //  structured exceptions when they call SetLastError to report one. The
    //  first two unconditionally set or clear the flag, while the third toggles
    //  it, and returns its previous value. All three return the previous value.
    //  ------------------------------------------------------------------------

    BOOL     FIXEDSTRINGBUFFERS_API FB_SEH_Disable ( ) ;
    BOOL     FIXEDSTRINGBUFFERS_API FB_SEH_Enable ( ) ;
    BOOL     FIXEDSTRINGBUFFERS_API FB_SEH_Query  ( ) ;
    BOOL     FIXEDSTRINGBUFFERS_API FB_SEH_Toggle ( ) ;
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */

#if defined ( UNICODE )
    #define FB_FindLineEnd              FB_FindLineEndW
    #define FB_FormatMessage            FB_FormatMessageW
    #define FB_FormatMessage2           FB_FormatMessage2W
    #define FB_FormatMessage3           FB_FormatMessage3W
    #define FB_GetlpErrMsgResStr        FB_GetlpErrMsgResStrW
    #define FB_GetlpErrMsgSprintf       FB_GetlpErrMsgSprintfW
    #define FB_GetlpResourceBuffer      FB_GetlpResourceBufferW
    #define FB_GetSprintFBuffer         FB_GetSprintFBufferW
    #define FB_GetSprintFBufferTCHARs   FB_GetSprintFBufferTCHARsW
    #define FB_LoadString               FB_LoadStringW
    #define FB_LoadStringFromDLL        FB_LoadStringFromDLLW
    #define FB_Replace                  FB_ReplaceW
    #define FB_SEH_Report               FB_SEH_ReportW
    #define FB_SetMessageBoxCaption     FB_SetMessageBoxCaptionW
    #define FB_XlateFBStatusCode        FB_XlateFBStatusCodeW
#else
    #define FB_FindLineEnd              FB_FindLineEndA
    #define FB_FormatMessage            FB_FormatMessageA
    #define FB_FormatMessage2           FB_FormatMessage2A
    #define FB_FormatMessage3           FB_FormatMessage3A
    #define FB_GetlpErrMsgResStr        FB_GetlpErrMsgResStrA
    #define FB_GetlpErrMsgSprintf       FB_GetlpErrMsgSprintfA
    #define FB_GetlpResourceBuffer      FB_GetlpResourceBufferA
    #define FB_GetSprintFBuffer         FB_GetSprintFBufferA
    #define FB_GetSprintFBufferTCHARs   FB_GetSprintFBufferTCHARsA
    #define FB_LoadString               FB_LoadStringA
    #define FB_LoadStringFromDLL        FB_LoadStringFromDLLA
    #define FB_Replace                  FB_ReplaceA
    #define FB_SEH_Report               FB_SEH_ReportA
    #define FB_SetMessageBoxCaption     FB_SetMessageBoxCaptionA
    #define FB_XlateFBStatusCode        FB_XlateFBStatusCodeA
#endif  /* #if defined ( UNICODE ) */

    //  ------------------------------------------------------------------------
    //  Function Name:  FB_ReportErrorViaStaticBuffer_CPP - C++ ONLY
    //                  FB_ReportErrorViaStaticBuffer     - Standard C
    //
    //  Synopsis:       Use the emergency static buffers allocated to the DLL
    //                  that exports this function to construct and display an
    //                  error message.
    //
    //  Arguments:      pnID                = This FB_RES_STRING_ID (const
    //                                        unsigned int, via typedef
    //                                        defined herein) is used in one of
    //                                        two ways.
    //
    //                                        1) If the APPLICATION_ERROR_MASK
    //                                           bit is set in the status code,
    //                                           whether it is passed in as
    //                                           pdwLastError or obtained from
    //                                           GetLastError, it is expected to
    //                                           resolve to a tokenized string
    //                                           from which the entire error
    //                                           message is constructed.
    //
    //                                        2) If the APPLICATION_ERROR_MASK
    //                                           bit is OFF in the status code,
    //                                           whether it is passed in as
    //                                           pdwLastError or obtained from
    //                                           GetLastError, it is expected to
    //                                           resolve to a ready-to-use
    //                                           string, which is handed off to
    //                                           routine FB_FormatMessage, which
    //                                           incorporates it into the
    //                                           message displayed about a
    //                                           system status code.
    //
    //                                        Please see the first two numbered
    //                                        items in the Remarks section for
    //                                        further details about this value.
    //
    //                  pdwLastError        = This CDWORD (const DWORD, via
    //                                        typedef, defined herein, is either
    //                                        the status code returned by
    //                                        GetLastError, or returned directly
    //                                        by a system routine, or by an
    //                                        application routine that failed.
    //
    //                                        If its value is ERROR_SUCCES or
    //                                        FB_REVSB_CALL_GETLASTERROR, this
    //                                        routine calls GetLastError, on the
    //                                        assumption that you called this
    //                                        routine to report an error. Please
    //                                        see numbered item 3 in the Remarks
    //                                        for an important reminder.
    //
    //                                        Regardless of how the status code
    //                                        is obtained, it becomes the return
    //                                        value of this function, which you
    //                                        may use, in turn, as your own exit
    //                                        code.
    //
    //                  plpAdditionalInfo   = Unless NULL, This LPTSTR points to
    //                                        the text to substitute for token
    //                                        $$ADDL_INFO$$ in the string loaded
    //                                        in response to argument pnID. If
    //                                        the APPLICATION_ERROR_MASK bit in
    //                                        the status code is OFF, this value
    //                                        is ignored.
    //
    //                                        If this value is NULL or the empty
    //                                        string, and the string loaded in
    //                                        response to argument pnID contains
    //                                        one or more $$ADDL_INFO$$ tokens,
    //                                        all are removed.
    //
    //                  penmCodeFormat      = This CFB_STATUS_CODE_FORMAT2 (a
    //                                        const STATUS_CODE_FORMAT2
    //                                        enumerated type, defined herein)
    //                                        governs the format in which the
    //                                        status code is reported. Supported
    //                                        formats are hexadecimal, decimal,
    //                                        and octal.
    //
    //                  puintType           = This CUINT (a const UINT, via a
    //                                        typedef defined herein) is either
    //                                        of the following.
    //
    //                                        1) To display the message in a
    //                                           MessageBox, specify a Valid,
    //                                           nonzero UTYPE.
    //
    //                                        2) To display the message in the
    //                                           standard error stream, set this
    //                                           value to zero.
    //
    //  Returns:        If pdwLastError is nonzero, its value is returned.
    //                  Otherwise, the value returned from the internal call to
    //                  GetLastError is returned.
    //
    //  Remarks:        Since this routine returns the final status code, you
    //                  really can get away with letting it call GetLastError
    //                  for you, yet use it as your own status or exit code.
    //
    //                  A slightly modified set of macros extends the typical
    //                  generic text mapping macros to map two identical C++
    //                  pass-through routines to the same symbolic name, so that
    //                  C++ code can treat all but the first argument as
    //                  optional, while C code sees four required arguments.
    //
    //                  1)  If pnID is greater than RESERVED_FOR_WW_STD_ERRORS
    //                      AND either pdwLastError or GetLastError matches bit
    //                      mask WW_STD_ERROR_MASK, the string is assumed to be
    //                      stored in WWStandardErrorMessages.dll, which is
    //                      expected to be stored alongside (in the directory
    //                      with) FixedStringBuffers.dll.
    //
    //                      Otherwise, the string is expected to be stored in
    //                      the first program that was loaded into the process.
    //
    //                  2)  The string identified by pnID may contain up to two
    //                      numeric substitution tokens, $$LAST_ERROR_HEX$$ and
    //                      $$LAST_ERROR_DEC$$. If present, both are replaced by
    //                      pdwLastError; hence, you can display the status code
    //                      in both hexadecimal and decimal notation.
    //
    //                      $$LAST_ERROR_HEX$$ renders the status code as a hex
    //                                         value of 8 hexadecimal "digits,"
    //                                         as 0xnnnnnnnn.
    //
    //                      $$LAST_ERROR_DEC$$ renders the status code as a long
    //                                         decimal integer using the numeric
    //                                         format settings in the active
    //                                         region and nationality profile.
    //
    //                  3)  You cannot set pdwLastError to ERROR_SUCCES or
    //                      FB_REVSB_CALL_GETLASTERROR when the system code came
    //                      from a specialized library, such as netapi.dll, that
    //                      implements the Microsoft LAN Manager subsystem, and
    //                      has its own reporting mechanism.
    //
    //                  4)  The C++ implementation defaults argument puintType
    //                      to MB_ICONASTERISK, causing this routine to display
    //                      a MessageBox bearing the Information icon if the
    //                      calling program runs in the graphical (Windows)
    //                      subsystem.
    //
    //                  5)  The straight C implementation behaves as described
    //                      herein if the values indicated as defaults for the
    //                      C++ implementation are specified.
    //
    //                  6)  If puintType matches bit mask MB_ICONMASK and the
    //                      calling program runs in the graphical (Windows)
    //                      subsystem, the completed message is rendered in a
    //                      standard message box with the specified icon. Other-
    //                      wise, the message box is suppressed.
    //
    //                  7)  If the calling program runs in the character mode
    //                      subsystem, puintType is ignored, and the message is
    //                      displayed on the console via CRT library routine
    //                      _tprintf. You may also use FB_ERRMSG_SUPPRESS_MSGBOX
    //                      to document that your console program ignores this
    //                      parameter.
    //
    //                  8)  Since plpAdditionalInfo is a LPTSTR, there are ANSI
    //                      and wide character (Unicode) implementations for
    //                      both C and C++, all of which follow the conventional
    //                      method of mapping entry point names, so that your
    //                      code can call FB_ReportErrorViaStaticBuffer, and the
    //                      compiler maps the call to the correct routine.
    //  ------------------------------------------------------------------------

#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */
    //  ------------------------------------------------------------------------
    //  Since they must be visible to both C and C++ compilers, these routines
    //  must be wrapped in a standard extern "C" block.
    //  ------------------------------------------------------------------------

    int      FIXEDSTRINGBUFFERS_API FB_ReportErrorViaStaticBufferA
    (
        FB_RES_STRING_ID        pnID ,                                          // Resource ID of tokenized string to load & use - see Remarks above
        CDWORD                  pdwLastError ,                                  // Result returned by GetLastError - see Remarks above
        LPCTSTR                 plpAdditionalInfo ,                             // Pointer to string containing additional information to incorporate into the message
        CSTATUS_CODE_FORMAT2    penmCodeFormat ,                                // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
        CUINT                   puintType                                       // Valid UTYPE nonzero for a MessageBox - see Remarks above
    ) ;

    int      FIXEDSTRINGBUFFERS_API FB_ReportErrorViaStaticBufferW
    (
        FB_RES_STRING_ID        pnID ,                                          // Resource ID of tokenized string to load & use - see Remarks above
        CDWORD                  pdwLastError ,                                  // Result returned by GetLastError - see Remarks above
        LPCTSTR                 plpAdditionalInfo ,                             // Pointer to string containing additional information to incorporate into the message
        CSTATUS_CODE_FORMAT2    penmCodeFormat ,                                // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
        CUINT                   puintType                                       // Valid UTYPE nonzero for a MessageBox - see Remarks above
    ) ;
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */

#if defined ( __cplusplus )
    //  ------------------------------------------------------------------------
    //  Due to their optional arguments, these two declarations must be hidden
    //  from C compilers.
    //  ------------------------------------------------------------------------

    int FIXEDSTRINGBUFFERS_API      FB_ReportErrorViaStaticBufferA_CPP
    (
        FB_RES_STRING_ID        pnID ,                                          // Resource ID of string to load & use - see Remarks above
        CDWORD                  pdwLastError      = NO_ERROR ,                  // Result returned by GetLastError - see Remarks above
        LPCTSTR                 plpAdditionalInfo = NULL ,                      // Pointer to string containing additional information to incorporate into the message
        CSTATUS_CODE_FORMAT2    penmCodeFormat    = FB_SCF2_HEXADECIMAL ,       // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
        CUINT                   puintType         = MB_ICONASTERISK             // Valid UTYPE nonzero for a MessageBox - see Remarks above
    ) ;

    int FIXEDSTRINGBUFFERS_API      FB_ReportErrorViaStaticBufferW_CPP
    (
        FB_RES_STRING_ID        pnID ,                                          // Resource ID of string to load & use - see Remarks above
        CDWORD                  pdwLastError      = NO_ERROR ,                  // Result returned by GetLastError - see Remarks above
        LPCTSTR                 plpAdditionalInfo = NULL ,                      // Pointer to string containing additional information to incorporate into the message
        CSTATUS_CODE_FORMAT2    penmCodeFormat    = FB_SCF2_HEXADECIMAL ,       // STATUS_CODE_FORMAT2 enumeration member to specify whether the status code should be displayed in decimal or hexadecimal
        CUINT                   puintType         = MB_ICONASTERISK             // Valid UTYPE nonzero for a MessageBox - see Remarks above
    ) ;

    //  ------------------------------------------------------------------------
    //  None of these macros can be used by the C++ wrappers, which is no foul,
    //  since they are simple pass-through routines that should never change,
    //  unless the argument list does so.
    //  ------------------------------------------------------------------------

    #if defined ( UNICODE )
        #define FB_ReportErrorViaStaticBuffer   FB_ReportErrorViaStaticBufferW_CPP
    #else
        #define FB_ReportErrorViaStaticBuffer   FB_ReportErrorViaStaticBufferA_CPP
    #endif  /* #if defined ( UNICODE ) */
#else
    //  ------------------------------------------------------------------------
    //  Due to their tight coupling, I kept all of the generic text and compiler
    //  mapping macros together. The two macros immediately above this box cover
    //  C++ translations, while the following two cover straight C translations.
    //  ------------------------------------------------------------------------

    #if defined ( UNICODE )
        #define FB_ReportErrorViaStaticBuffer   FB_ReportErrorViaStaticBufferW
    #else
        #define FB_ReportErrorViaStaticBuffer   FB_ReportErrorViaStaticBufferA
    #endif  /* #if defined ( UNICODE ) */
#endif  /* #if defined ( __cplusplus ) */
#endif  /* #if !defined ( AFX_FIXEDSTRINGBUFFERS_H__6D76DBB8_4AC2_4F5E_B45E_E009EB638A29__INCLUDED_ ) */