#ifndef _WEEKDAYS_WW
#define _WEEKDAYS_WW

/*
    ============================================================================

    Module Name:        Weekdays_WW.H

    Synopsis:           Add spelled weekday function to applications that lack
                        native function for delivering spelled weekdays. This
                        includes Microsoft Office and Visual Basic 6.

    Notes:              All functions that return long pointers to strings
                        (LPTSTR) allocate memory to hold the strings from the
                        process heap, and return a pointer. The memory can be
                        subsequently freed by calling Windows function HeapFree,
                        passing a handle to the process heap and the pointer.

    Author:             David A. Gray, of Simple Soft Services, Inc.,
                        d/b/a WizardWrx, Irving, Texas, USA.

    Date Written:       Saturday, 14 April 2007 and Sunday, 15 April 2007.

	License:            Copyright (C) 2007-2016, David A. Gray. All rights reserved.

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
    2007/04/15 DAG First working version.

    2009/12/08 DAG Modernize the documentation and organization of this file.

    2010/03/08 DAG Remove version numbers, which have no practical meaning
                      when applied to functions that are part of a static
                      library, since there is no apparent way to version stamp a
                      static link library.

    2010/04/25 DAG Reinstate direct inclusion of windows.h, since, as of this
                      date, CommonConstants_P6C.H works just fine without it.

    2010/06/04 DAG Move the #pragma once preprocessor directive outside the
                      scope of the preprocessor variable which performs the same
                      function for other C compilers.

    2013/06/30 DAG 1) Eliminate CommonConstants_P6C.H in favor of the much
                         more focused Const_Typedefs_WW.H.

                   2) Substitute LIBSPEC_WWDATELIB_API for APIENTRY, which
                      decorates the external API with __declspec(dllimport).

                      Since SpellWeekDay_WW is currently unused, apart from a
                      test stand routine, for all practical matters, this
                      change breaks nothing.

                   3) Consolidate the source code of the ANSI and Unicode
                      implementations of SpellWeekDay_WW into a new inline
                      source code file, SpellWeekDay_WW.INL.

    2015/02/24 DAG Use __DATELIB_P6C_INCLUDED__ to impose the definition of
                   LIBSPEC_WWDATELIB_API established by DateLib_P6C.H.

    2016/03/06 DAG Replace all references to preprocessor symbol CUSTOMER_FLAG,
                   a custom symbol, with APPLICATION_ERROR_MASK, defined in
                   WinNT.h. Since both resolve to the same value, nothing needs
                   to be recompiled.
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
  |                   * * *    E N U M E R A T I O N S   * * *                   |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

typedef enum _CALENDAR_TEXT_TYPE_WW
{
    CALTEXT_LONG ,                                  // 0
    CALTEXT_SHORT ,                                 // 1
    CALTEXT_LONG_UC ,                               // 2
    CALTEXT_SHORT_UC                                // 3
} CALENDAR_TEXT_TYPE_WW ;

typedef const CALENDAR_TEXT_TYPE_WW CCALENDAR_TEXT_TYPE_WW ;

/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |             * * *    S Y M B O L I C   C O N S T A N T S   * * *             |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/


/*
    ----------------------------------------------------------------------------
    Begin definitions of error code constants, all of whic use the Customer Flag
    bit. The corresponding symbolic constant, APPLICATION_ERROR_MASK, is defined
    in WinNT.h.
    ----------------------------------------------------------------------------
*/

#define WDAYINFO_SETLOCALE_ERROR_WW         ( 1 | APPLICATION_ERROR_MASK )
#define WDAYINFO_INVALID_WEEKDAY_NBR_WW     ( 2 | APPLICATION_ERROR_MASK )
#define WDAYINFO_INVALID_WEEKDAY_FMT_WW     ( 3 | APPLICATION_ERROR_MASK )
#define WDAYINFO_MALLOC_ERROR_P6C           ( 4 | APPLICATION_ERROR_MASK )


/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |      * * *    B E G I N   F U N C T I O N   P R O T O T Y P E S   * * *      |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

#if !defined ( __DATELIB_P6C_INCLUDED__ )
    #ifdef __DATELIB_PVT_P6C__
        #define LIBSPEC_WWDATELIB_API __declspec(dllexport)
        #pragma message("     __DATELIB_PVT_P6C__ is defined. Hence, LIBSPEC_WWDATELIB_API maps to __declspec(dllexport).")
    #else   /*  #ifdef __DATELIB_PVT_P6C__ */
        #ifdef __DATELIB_STATIC_P6C__
            #define LIBSPEC_WWDATELIB_API extern
            #pragma message("     __DATELIB_STATIC_P6C__ is defined. Hence, LIBSPEC_WWDATELIB_API maps to extern.")
        #else   /*  #ifdef __DATELIB_STATIC_P6C__ */
            #define LIBSPEC_WWDATELIB_API __declspec(dllimport)
            #pragma message("     Neither __DATELIB_PVT_P6C__, nor __DATELIB_STATIC_P6C__ is defined. Hence, LIBSPEC_WWDATELIB_API maps to __declspec(dllimport).")
        #endif  /*  #ifdef __DATELIB_STATIC_P6C__ */
    #endif  /*  #ifdef __DATELIB_PVT_P6C__ */
#endif  /* #if !defined ( __DATELIB_P6C_INCLUDED__ ) */


#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */


/*
    ============================================================================

    Function Name:      SpellWeekDay_WW

    Synopsis:           Given a weekday index, where 0=Sunday and 6=Saturday,
                        use the NLS (National Language Support) functions to
                        retrieve the corresponding weekday name or abbreviation
                        strings.

    Arguments:          pintWeekDayNbr  = An integer, between 0 and 6, which
                                          represents the weekday number. See
                                          Remarks (1).
                        putpWDayStrType = A member of the CALENDAR_TEXT_TYPE_WW
                                          enumeration (defined above), which
                                          determines whether the long (spelled
                                          out) or short (abbreviated) weekday
                                          name is returned, and whether the name
                                          is returned in upper or mixed case.
                                          See Remarks (1).

    Returns:            rlpWeekdayName  = A long pointer to a string containing
                                          the requested weekday name.

    Remarks:            1) Both arguments are marked with the const modifier, to
                           signal the compiler to treat them as read only data.

                        2) All errors are reported through kernel library
                           function SetLastError.

                        2) This function works only on Windows 2000 and later,
                           and there are no plans to back-port it.

    References:         None.

    Calls:              The following functions are called, in the order listed.

                        -------------------------------------------------
                        Function        Header          Library
                        --------------- --------------- -----------------
                        SetLastError    Winbase.h       Kernel32.lib
                        GetProcessHeap  Winbase.h       Kernel32.lib
                        HeapAlloc       Winbase.h       Kernel32.lib
                        GetCalendarInfo Winnls.h        Kernel32.lib
                        -------------------------------------------------

                        The call to GetCalendarInfo creates the dependency on
                        Windows 2000.

    ============================================================================
*/

LPTSTR LIBSPEC_WWDATELIB_API SpellWeekDayA_WW
(
    CINT                   pintWeekDayNbr ,
    CCALENDAR_TEXT_TYPE_WW putpWDayStrType
) ;
LPTSTR LIBSPEC_WWDATELIB_API SpellWeekDayW_WW
(
    CINT                   pintWeekDayNbr ,
    CCALENDAR_TEXT_TYPE_WW putpWDayStrType
) ;

#ifdef UNICODE
    #define SpellWeekDay_WW SpellWeekDayW_WW
#else
    #define SpellWeekDay_WW SpellWeekDayA_WW
#endif  /* #ifdef UNICODE */


// Close the block of code that has "C" linkage.
#ifdef __cplusplus
}
#endif  /* #ifdef __cplusplus */
#endif  /* #ifndef _WEEKDAYS_WW */