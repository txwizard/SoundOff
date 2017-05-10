/*
    ============================================================================

    File Name:          FNReplacReservedChars.H

    Function Name:      FNReplacReservedChars

    Library:            P6CStringLib1.dll (P6CStringLib1.lib)

    Synopsis:           Remove or replace reserved characters in a proposed file
                        name.

    Arguments:          plpProposedName = Pointer to string containing the file
                                          name to fix up.

                        pchrChar2Subst  = Character to substitute, which MAY be
                                          null.

    Returns:            If the function succeeds, the return value is the
                        length of the string, in TCHARs, excluding the terminal
                        null character. This is comparable to the value returned
                        by CRT function _tcslen.

                        For C and C++ callers, the return value is cast to
                        DWORD.

    Remarks:            A companion function, FNReplacReservedCharsW, implements
                        this function for wide characters.

                        Te simplify using these routines to clean up real file
                        names in real programs, the following convenience
                        constants are defined.

                            -----------------------------------------------
                            Name                Application
                            ------------------- ---------------------------
                            HYPHEN_CHAR_WW      Replace with a hyphen.
                            NULL_CHARACTER_DAG  Substitute nothing. Strip
                                                invalid characters.
                            SPACE_TCHAR_DAG     Replace with a space.
                            UNDERSCORE_CHAR_DAG Replace with an underscore.
                            -----------------------------------------------

                        Any of the above constants may be substituted for the
                        pchrChar2Subst argument.

    Date Written:       Sunday, 20 April 2014

	License:            Copyright (C) 2014-2016, David A. Gray. All rights reserved.

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
	2014/04/23 DAG/WW Initial implementation and testing.
    2014/12/11 DAG/WW Incorporate into P6CStringLib1.H and P6CStringLib1.dll.
    2015/01/15 DAG/WW Change the calling convention from APIENTRY to __stdcall.
                      The effect of this change is confined to this header file.
                      This update is built into P6CStringLib1, version 2,9,0,4.
	2016/01/10 DAG Incorporate the standard three-clause BSD license.
    ============================================================================
*/

#ifndef __FNREPLACRESERVEDCHARS_DEFINED
    #define __FNREPLACRESERVEDCHARS_DEFINED

    #if defined (_MSC_VER) && (_MSC_VER >= 1020)
        #pragma once
    #endif  /*  #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

    #include <windows.h>

    #ifndef HYPHEN_CHAR_WW
        #define HYPHEN_CHAR_WW              ( ( TCHAR ) '-' )
    #endif  /* #ifndef HYPHEN_CHAR_WW */

    #ifndef NULL_CHARACTER_DAG
        #define NULL_CHARACTER_DAG          ( ( TCHAR ) '\0' )
    #endif  /* #ifndef NULL_CHARACTER_DAG */

    #ifndef SPACE_TCHAR_DAG
        #define SPACE_TCHAR_DAG             ( ( TCHAR ) ' ' )
    #endif  /* #ifndef SPACE_TCHAR_DAG */

    #ifndef UNDERSCORE_CHAR_DAG
        #define UNDERSCORE_CHAR_DAG         ( ( TCHAR ) '_' )
    #endif  /* #ifndef UNDERSCORE_CHAR_DAG */

    #if defined(__cplusplus)
        extern "C"
        {
    #endif
        DWORD __stdcall FNReplacReservedCharsA
        (
            LPTSTR  plpProposedName ,   // Pointer to string containing the file name to fix up.
            TCHAR   pchrChar2Subst      // Character to substitute, which MAY be NULL.
        ) ;

        DWORD __stdcall FNReplacReservedCharsW
        (
            LPTSTR  plpProposedName ,   // Pointer to string containing the file name to fix up.
            TCHAR   pchrChar2Subst      // Character to substitute, which MAY be NULL.
        ) ;

        #ifdef UNICODE
            #define FNReplacReservedChars   FNReplacReservedCharsW
        #else
            #define FNReplacReservedChars   FNReplacReservedCharsA
        #endif  /* #ifdef UNICODE */
    #ifdef __cplusplus
        }
    #endif  /*  __cplusplus */
#endif  /*  __FNREPLACRESERVEDCHARS_DEFINED */