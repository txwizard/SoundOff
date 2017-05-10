#ifndef _FORMATMSGS_WW
#define _FORMATMSGS_WW

/*
    ============================================================================

    Module Name:        FormatMsgs_WW.H

    Synopsis:           Header file for my C interface to the FormatMessage
                        function in the Windows API.

    Arguments:          Please see individual function definitions.

    Returns:            Please see individual function definitions.

    Remarks:            Any module that includes one or more of the functions
                        declared in this header must define a public variable,
                        m_hDfltHeap, of type HANDLE.

                        1) If the function is statically linked from an object
                           file or from P6CLIB1.LIB or P6CLIB1D.LIB (the Debug
                           version), the source file that includes function Main
                           should define m_hDfltHeap, and call GetProcessHeap to
                           initialize it, or initialize it to NULL, and let the
                           first function that needs a handle to the default
                           process heap call GetProcessHeap, saving the handle
                           into m_hDfltHeap.

                        2) If the function is statically linked into a DLL, the
                           source file that includes function DLLMain should
                           define m_hDfltHeap, and call GetProcessHeap to
                           initialize it, or initialize it to NULL, and let the
                           first function that needs a handle to the default
                           process heap call GetProcessHeap, saving the handle
                           into m_hDfltHeap.

    References:         None.

    Calls:              Please see individual function definitions.

    Date Written:       Sunday, 26 August 2007 - Monday, 10 September 2007.

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
    2007/09/10 DAG First working version.

    2008/10/15 DAG 1) Function EM_FormatMsgForMsgbox_WW: Fix inverted test for
                      successful memory allocation that invariably caused the
                      function to silently fail, replace hard coded literals
                      with symbolic constants defined in CommonConstants_P6C.H,
                      and improve internal documentation.

                   2) Function EM_ShowMsgOnConsole_WW: Replace hard coded
                      literals with symbolic constants defined in
                      CommonConstants_P6C.H and improve internal
                      documentation. Emitted code should be identical.

                   3) EM_FormatMsgForMsgbox_WW: Fix off by one error in the
                      calculation of the amount of memory that can be safely
                      released from the message buffer.

    2008/10/17 DAG Function EM_FormatMsgForMsgbox_WW: Truncate the trailing
                   newline, which contribute nothing useful to a message that
                   is intended for display in a message box.

    2009/12/21 DAG Function EM_FormatMsgForMsgbox_WW: Correct erroneous
                   information about its return type. The prototype is
                   correct; it returns a LPTSTR.

    2010/03/08 DAG Remove version numbers, which have no practical meaning
                   when applied to functions that are part of a static link
                   library.

    2010/04/25 DAG Reinstate direct inclusion of windows.h, since, as of this
                   date, CommonConstants_P6C.H works just fine without it.

    2010/06/04 DAG Add a #pragma once preprocessor directive outside the
                   scope of the preprocessor variable which performs the same
                   function for other C compilers.

    2012/06/30 DAG Based on recently gained knowledge of how various guard
                   code schemes work, move the #pragma once block inside the
                   block protected by the preprocessor guard variable.

    2013/06/18 DAG Eliminate an overlooked reference to CommonConstants_P6C.H
                   and substitute Const_Typedefs_WW.H, which is plenty for a
                   public interface. This update is built into P6CStringLib1,
                   version 2,8,1,0.

    2016/01/10 DAG Incorporate the standard three-clause BSD license.

    2016/05/21 DAG Correct typographical errors discovered during a code review.
                   Since the changes are confined to comments, nothing needs to
                   be rebuilt.

    2016/07/01 DAG Mark these functions as deprecated, preceding declarations
                   with a reference to FixedStringBuffers.H.
    ============================================================================
*/

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /* #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |         * * *    R E Q U I R E D   I N C L U D E   F I L E S   * * *         |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

#include <windows.h>

#include <Const_Typedefs_WW.H>


/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |    * * *    E N U M E R A T I O N S   A N D   S T R U C T U R E S   * * *    |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

typedef enum _STATUS_CODE_FORMAT_WW
{
    STATUS_CODE_HEXADECIMAL ,   // 0
    STATUS_CODE_DECIMAL ,       // 1
    STATUS_CODE_OCTAL           // 2
} STATUS_CODE_FORMAT_WW ;


/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |               * * *    P U B L I C   F U N C T I O N S   * * *               |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

#pragma message ( __FILE__ "The functions declared in this header are deprected. They are being retired in favor of the FB_FormatMessage* constellation of functions declared in FixedStringBuffers.H." )
#pragma message ( __FILE__ "    Not only are the new functions more robust, since they work exclusively with static buffers that are baked into the code of the library, but their options afford a great deal more flexibility, and allow them to take on more of the work for you." )

#pragma deprecated (EM_ShowMsgOnConsole_WW) 
#pragma deprecated (EM_FormatMsgForMsgbox_WW)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
    ============================================================================

    Function Name:      EM_ShowMsgOnConsole_WW

    Synopsis:           Format a message and display it on the console.

    Arguments:          plpHint         = Pointer to a "hint" string to prefix
                                          the message.

                        pdwLastError    = DWORD of message number to format.

                        penmCodeFormat  = STATUS_CODE_FORMAT_WW enumeration, to
                                          specify the desired format to use for
                                          the result code.

    Returns:            fResult         = Boolean result flag.

                                          TRUE  = Message was successfully for-
                                                  matted and displayed, and the
                                                  local buffer used to format it
                                                  was successfully freed.

                                          FALSE = Message was successfully for-
                                                  matted and displayed, but the
                                                  local buffer used to format it
                                                  could not be freed.

    Remarks:            1) This function assumes that pdwLastError contains the
                           ID of a system message, and passes it to the
                           FormatMessage Windows API function, which looks up
                           the corresponding text, and returns a pointer to a
                           local buffer containing the text.

                        2) Unless argument plpHint is NULL, it is expected to
                           point to a null terminated string that contains text
                           to display before the error code and error message
                           text.

                        3) This function is much more robust than function
                           ShowErrorOnConsole_WW, in 2007TXFIX.C, from which it
                           is derived.

    References:         Please see the module flower box above.

    Calls:              The following Windows API functions are called in the
                        order named.

                             Function               Library      Header
                             ---------------------- ------------ ---------
                             FormatMessage          kernel32.dll Winbase.h
                             printf                 C Runtime    stdio.h
                             ---------------------------------------------

    Date Written:       Sunday, 26 August 2007 - Monday, 10 September 2007.

    ============================================================================
*/

BOOL WINAPI EM_ShowMsgOnConsoleA_WW
(
    LPCTSTR               plpHint ,
    DWORD                 pdwLastError ,
    STATUS_CODE_FORMAT_WW penmCodeFormat
) ;

BOOL WINAPI EM_ShowMsgOnConsoleW_WW
(
    LPCTSTR               plpHint ,
    DWORD                 pdwLastError ,
    STATUS_CODE_FORMAT_WW penmCodeFormat
) ;

#ifdef UNICODE
    #define EM_ShowMsgOnConsole_WW  EM_ShowMsgOnConsoleW_WW
#else
    #define EM_ShowMsgOnConsole_WW  EM_ShowMsgOnConsoleA_WW
#endif


/*
    ============================================================================

    Function Name:      EM_FormatMsgForMsgbox_WW

    Synopsis:           Return a formatted message, substantially identical to
                        the one displayed on the console by its companion,
                        EM_ShowMsgOnConsole_WW, adapted for display as the text
                        of a MessageBox.

    Arguments:          plpHint         = Pointer to a "hint" string to prefix
                                          the message.

                        pdwLastError    = DWORD of message number to format.

                        penmCodeFormat  = STATUS_CODE_FORMAT_WW enumeration, to
                                          specify the desired format to use for
                                          the result code.

    Returns:            rlpMessage      = Pointer (LPTSTR) to message text.

                                          If the pointer is NULL, a serious
                                          error prevented it being formatted.

    Remarks:            1) This function assumes that pdwLastError contains the
                           ID of a system message, and passes it to the
                           FormatMessage Windows API function, which looks up
                           the corresponding text, and returns a pointer to a
                           local buffer containing the text.

                        2) Unless argument plpHint is NULL, it is expected to
                           point to a null terminated string that contains text
                           to display before the error code and error message
                           text.

                        3) I make no assumptions about the contents of external
                           variable m_hDfltHeap, other than that it is linked
                           into the final binary. Instead, its value is tested, 
                           and GetProcessHeap is called only if necessary.

                        4) As with all of my functions that return pointers to
                           null terminated strings, this one releases unused
                           memory.

    References:         Please see the module flower box above.

    Calls:              The following Windows API functions are called in the
                        order shown.

                             Function               Library      Header
                             ---------------------- ------------ ---------
                             GetProcessHeap         kernel32.dll Winbase.h
                             HeapAlloc               kernel32.dll Winbase.h
                             FormatMessage          kernel32.dll Winbase.h
                             _tsprintf_s            C Runtime    stdio.h
                             HeapReAlloc            kernel32.dll Winbase.h
                             ---------------------------------------------

    Date Written:       Sunday, 26 August 2007 - Monday, 10 September 2007.

    ============================================================================
*/

LPTSTR WINAPI EM_FormatMsgForMsgboxA_WW
(
    LPCTSTR               plpHint ,
    DWORD                 pdwLastError ,
    STATUS_CODE_FORMAT_WW penmCodeFormat
) ;

LPTSTR WINAPI EM_FormatMsgForMsgboxW_WW
(
    LPCTSTR               plpHint ,
    DWORD                 pdwLastError ,
    STATUS_CODE_FORMAT_WW penmCodeFormat
) ;

#ifdef UNICODE
    #define EM_FormatMsgForMsgbox_WW    EM_FormatMsgForMsgboxW_WW
#else
    #define EM_FormatMsgForMsgbox_WW    EM_FormatMsgForMsgboxA_WW
#endif

// Close the block of code that has "C" linkage.
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /* _FORMATMSGS_WW */