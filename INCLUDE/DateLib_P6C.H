#if !defined ( __DATELIB_P6C_INCLUDED__ )
#define __DATELIB_P6C_INCLUDED__

/*
    ============================================================================

    Module Name:        DateLib_P6C.H

    Libraries:          Include WWDateLib.lib or P6CLib1.lib. See Remarks (2).

    Synopsis:           Provide a richer set of date functions than the ones
                        that return the standard SYSTEMTIME structure, or those
                        supplied by the National Language Support libraries.

    Dependencies:       If you use function LoadFormatStringLibrary_P6C, its
                        satellite library, ReformatSysDate_P6C.dll must be
                        stored in the directory from which WWDateLib.dll was
                        loaded. If you store it elsewhere, you must use the
                        regular Windows API function, LoadLibraryEx, to load
                        it.

    Arguments:          Please see individual function definitions.

    Returns:            Please see individual function definitions.

    Remarks:            1)  All functions that return long pointers to strings
                            (LPTSTR) allocate memory to hold the strings from
                            the process heap, and return a handle, which can be
                            subsequently freed by calling Windows API function
                            HeapFree, passing a handle to the process heap and
                            the pointer.

                        2)  Most of the modules declared in this header are
                            defined in a static link library P6CLib1, so that
                            they can be linked statically into a standalone
                            utility program or merged into a dynamic link
                            library from which they are exported to client
                            modules (EXE files or other DLLs). This requires
                            three definitions of LIBSPEC_WWDATELIB_API and two
                            mutually exclusive preprocessor variables,
                            __DATELIB_PVT_P6C__ and __DATELIB_STATIC_P6C__, to
                            specify which one is to be used in the current
                            translation unit.

                            a)  Define __DATELIB_PVT_P6C__ when building the
                                static link library, P6CLIB1.LIB.

                            b)  Define __DATELIB_STATIC_P6C__ when building a
                                program of any kind that imports these functions
                                as statically linked routines. This rule applies
                                equally to dynamic link libraries and regular
                                executable programs.

                            c)  Define neither of the above to import these
                                functions from a DLL.

                            The additional requirements extend the concept
                            discussed in the first reference and elsewhere, and
                            implement the concept of an extern dllimport, which
                            is the subject of the second article.

    References:         1)  The Ultimate (DLL) Header File
                            http://www.flounder.com/ultimateheaderfile.htm

                        2)  Definitions and Declarations (Visual Studio 6.0),
                            Microsoft Specific
                            http://msdn.microsoft.com/en-us/library/aa243266(v=VS.60).aspx

                        3)  How can I handle DLL_EXPORT when compiling dll to a static library?
                            http://stackoverflow.com/questions/6259022/how-can-i-handle-dll-export-when-compiling-dll-to-a-static-library

                        Please see individual function definitions, some of
                        which contain additional references that apply solely to
                        them.

    Calls:              Please see individual function definitions.

    Author:             David A. Gray, of Simple Soft Services, Inc.,
                        D/B/A WizardWrx, Irving, Texas, USA.

    Date Written:       Friday, 09 December 2005 - Saturday, 10 December 2005.

    Copyright:          Copyright 2005-2016, David A. Gray,Irving, Texas, USA.
                        All rights reserved world wide.

                        This code may be freely reproduced, so long as it
                        remains intact, including this copyright notice and
                        license.

                        However, since it is in the public domain, it is
                        unsupported in any way and carries no warranty. Use it
                        at your own risk.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Author Synopsis
    ---------- ------ ----------------------------------------------------------
    2005/12/10 DAG    First working version.

    2005/12/23 DAG    First feature complete version, including ANSI and Unicode
                      versions and optimizations of such things as data movement
                      (minimization of string copying, use of pointers to
                      structures, and saving of pointers to the process heap, to
                      minimize context switches).

    2007/12/08 DAG    1) Substitute externally linked handle m_hDfltHeap for
                         locally defined hDefaultHeap, so that most, if not all,
                         code that uses the process heap can share a single copy
                         of the handle.

                      2) Investigate a potential memory leak in the main parsing
                         loop. For a program, such as one that creates time
                         stamped log records, which might call this routine
                         thousands of times, such a leak could be significant.

                         On further investigation, the leak proved to be a false
                         alarm, because I anticipated the leak in 2005, when I
                         wrote this routine, and, amazingly, got it right.
                         However, in the interest of efficiency, I did skip the
                         usual safety measure of invalidating the pointer.

                         This I did fix.

                         I also made sure that all points where the code returns
                         an empty string also call SetLastError, either directly
                         or indirectly.

    2010/02/27 DAG    1) Correct a typo in RFD_CAL_MIN_WEEKDAY_IDX, mislabeled
                         as RFT_CAL_MIN_WEEKDAY_IDX, and was, therefore,
                         inconsistent with other symbolic constants defined in
                         this header.

                      2) Define standard, as in commonly used, date and time
                         format strings as symbolic constants, and infuse them
                         into library functions that have literal strings.

                      3) Rationalize internal field validation between ANSI and
                         Unicode implementations.

    2010/03/09 DAG    Remove headers that are pulled into the source code stream
                      by CommonConstants_P6C.H, after CPP flags are set as they
                      must be to ensure that they are interpreted as requured by
                      this module.

                      The affected headers are as follows.

                            windows.h    - In CommonConstants_P6C.H
                            Winnls.h     - Rather be safe than sorry.

                      This change affects only the definitions of the functions
                      declared in this header. The header, itself, is alrady
                      correct.

    2010/04/25 DAG    Reinstate direct inclusion of windows.h, since, as of this
                      date, CommonConstants_P6C.H works just fine without it.

    2010/05/20 DAG    Add support for archaic two digit years, still useful with
                      such programs as DataEase 4.53, and eliminate redundant
                      function revision histories.

    2010/06/04 DAG    Move the #pragma once preprocessor directive outside the
                      scope of the preprocessor variable which performs the same
                      function for other C compilers.

    2010/09/26 DAG    1) Correct an error in the token tables used by function
                         ReformatSysDate_P6C, which must process longer runs of
                         the same character before shorter runs of the same
                         character.

                         The tokens that were out of order are ^YYYY and ^YY.

                      2) Move the token substitution tables into this header,
                         inside a #ifdef  __DATELIB_PVT_P6C__ block, and correct
                         an error in the symbolic constants which drive a switch
                         block in function InsertDateField_P6C.

                      3) Replace APIENTRY calling convention macro with
                         __declspec(dllexport), which allows the linkage editor
                         to generate a more efficient import address table for a
                         program that calls these functions.

                      4) Take function InsertDateField_P6C private.

    2011/06/04 DAG    Substitute the LIBSPEC_WWDATELIB macro for
                      __declspec(dllexport) in the definitions of functions
                      ReformatSysDateA_P6C and ReformatSysDateW_P6C.

                      Note: This change affects only the source code files, but
                            the change is necessary to implement the fully
                            flexible header file discussed in "The Ultimate
                            Header File." See Reference, above.

                            Any code that calls a routine that is converted from
                            WINAPI or APIENTRY to LIBSPEC_WWDATELIBT must be
                            re-linked, to have its Input Address Table rebuilt
                            without the short jump instruction.

    2011/06/09 DAG    1) Rename the LIBSPEC macro as LIBSPEC_WWDATELIB, to get
                         past a macro redefinition warning when the static
                         library is built all at once.

                      2) Add a const qualifier to the first (SYSTEMTIME)
                         argument to ReformatSysDate_P6C and GetDateInfo_P6C.

    2011/06/11 DAG    Change the LIBSPEC macro name from LIBSPEC_WWDATELIB to
                      LIBSPEC_WWDATELIB_API, to be consistent with names being
                      assigned in other headers that define a LIBSPEC macro.

                      The name used in this header is LIBSPEC_WWDATELIB_API.

    2011/08/16 DAG    Move the definition of LIBSPEC_WWDATELIB_API below (after)
                      windows.h is included.

    2011/08/20 DAG    1) Implement the extern declspec(dllimport) discussed in
                         the second item in the Remarks section above and the
                         second and third of the references cited above.

                      2) Add the following string constants, used in most of my
                         freestanding console programs.

                                RFD_FORMAT_WDDMMMYYYYHHMMSS_UTC
                                RFD_FORMAT_WDDMMMYYYYHHMMSS_LOCAL
                                RFD_FORMAT_WDDMMMYYYYHHMMSS_EITHER

                         The first two of these are used in WWSleep.exe, which
                         motivated their migration to this header.

    2012/02/05 DAG    1) Declare a new routine for loading the satellite DLL of
                         format strings for use with ReformatSysDate_P6C.

                      2) Remove the hard coded strings, which are superseded by
                         the above mentioned resource strings.

                      3) Move the #pragma once preprocessor directive outside
                         the __DATELIB_P6C_INCLUDED__ block.

                      4) Add missing documentation of the second argument to
                         ReformatSysDate_P6C.

    2012/05/13 DAG    Library version 2,1,129,0:

                      Add function WWDateLibErrorReported_P6C, for signaling
                      callers that an error caught in one of the routines
                      exported by this library has been reported to the user, to
                      prevent repetitive reporting of the same error.

    2012/05/29 DAG    Library version 2,2,130,0:

                      Properly document function LoadFormatStringLibrary_P6C,
                      for loading the satellite library of date format strings,
                      and significantly improve its efficiency.

    2012/06/02 DAG    Library version 2,2,131,2:

                      Account for renaming of ReformatSysDate_P6C.H as
                      ReformatSysDate_P6C_FormatStrings.H, to firmly associate
                      its name with that of the associated resource-only DLL.

    2013/05/14 DAG    Library version 2,2,132,0:

                      In private header WWDateLib_P6C_Pvt.H, append a NULL to
                      the last token in arrays achrTokens and achrFmtStrs, so
                      that, when the compiler lays them out, both arrays are
                      terminated by double nulls, as is required by function
                      GetTokenByIndex_P6C, which ReformatSysDate_P6C uses to
                      extract individual tokens as needed.

    2013/05/19 DAG    Library version 3,0,133,0:

                      In private header WWDateLib_P6C_Pvt.H, create a table of
                      offsets into the achrTokens and achrFmtStrs arrays so that
                      the calls to GetTokenByIndex_P6C can be replaced by simple
                      subscripted array references, signifincantly improving the
                      performance of ReformatSysDate_P6C, which gets called many
                      times in certain situations in which those calls should be
                      as fast as possible.

    2013/06/19 DAG    Library version 3,0,134,0:

                      Eliminate CommonConstants_P6C.H in favor of the much more
                      focused Const_Typedefs_WW.H.

    2013/06/30 DAG    Library version 3,0,135,0:

                      1) Eliminate CommonConstants_P6C.H from subsidiary header
                         Weekdays_WW.H, in favor of the much more focused
                         Const_Typedefs_WW.H.

                      2) In SpellWeekDay_WW, substitute LIBSPEC_WWDATELIB_API
                         for APIENTRY, which decorates the external API with
                         __declspec(dllimport).

                      3) Consolidate the source code of the ANSI and Unicode
                         implementations of SpellWeekDay_WW into a new inline
                         source code file, SpellWeekDay_WW.INL.

    2015/02/24 DAG    Library version 3,1,136,0:

                      Add a new function, FormatTimeNowP6C, which uses the same
                      format strings as ReformatSysDate_P6C, returning the time
                      per the system clock.

    2016/05/21 DAG    Library version 3,1,136,0:

                      DOCUMENTATION CHANGE ONLY

                      Correct typographical errors caught by the new spelling
					  checker add-in for Visual Studio 2013, which I discovered
					  during a code review related to repair work on WWLogger.
					  Since the changes are confined entirely to comments, the
					  library need not be rebuilt, nor is any other program that
					  calls into it affected.

    2016/07/09 DAG    Library version 3,1,136,0:

					  Compensate for reinstatement of the requirement that my
					  CommonConstants_P6C.H header must again be the first to be
					  included in the translation stream, to accommodate changes
					  in the organization of the core Windows API headers that
					  affect the evaluation of preprocessor symbols, and require
					  that CommonConstants_P6C.H must include windows.h after
					  certain preprocessor symbols are defined, so that the CRT
					  headers that are now included by windows.h resolve to the
					  expected declarations of the generic TCHAR functions.

					  Since these changes have no tangible effect on the code or
					  the interface definition, the library need not be rebuilt.
					  However, the changes had to be made now to get static link
					  library P6CLib1.lib to build, because some of its routines
					  go into P6CStringLib1, to which I am adding two functions.
    ============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /*  #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |         * * *    R E Q U I R E D   I N C L U D E   F I L E S   * * *         |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

#include <windows.h>
#include <Oleauto.h>
#include <Const_Typedefs_WW.H>

//  ----------------------------------------------------------------------------
//  2011/08/20 - See item 2 under Remarks, and references 2 and 3. The third one
//               provided the final solution.
//
//               IMPORTANT: Leave the messages; they will be useful in the event
//                          that you have difficulties with linkage.
//  ----------------------------------------------------------------------------

#pragma message ( "processing DateLib_P6C.H, defining LIBSPEC_WWDATELIB_API:" )

#if defined ( __DATELIB_PVT_VB_P6C__ )
    #define LIBSPEC_WWDATELIB_API extern
    #pragma message ( "     Both __DATELIB_PVT_P6C__ and __DATELIB_PVT_VB_P6C__ are defined. Hence, LIBSPEC_WWDATELIB_API maps to extern, for local import." )
#elif defined ( __DATELIB_PVT_P6C__ )
    #define LIBSPEC_WWDATELIB_API __declspec(dllexport)
    #pragma message ( "     __DATELIB_PVT_P6C__ is defined. Hence, LIBSPEC_WWDATELIB_API maps to __declspec(dllexport)." )
#elif defined ( __DATELIB_STATIC_P6C__ )
    #define LIBSPEC_WWDATELIB_API extern
    #pragma message ( "     __DATELIB_STATIC_P6C__ is defined. Hence, LIBSPEC_WWDATELIB_API maps to extern." )
#else
    #define LIBSPEC_WWDATELIB_API __declspec(dllimport)
    #pragma message ( "     Neither __DATELIB_PVT_P6C__, nor __DATELIB_STATIC_P6C__ is defined. Hence, LIBSPEC_WWDATELIB_API maps to __declspec(dllimport)." )
#endif  /*  #if defined ( __DATELIB_PVT_P6C__ ) */

#if defined ( LIBSPEC_WWDATELIB_API )
    #pragma message ( "     LIBSPEC_WWDATELIB_API was defined successfully." )
#else
    #pragma message ( "     LIBSPEC_WWDATELIB_API remains UNDEFINED." )
#endif  /*  #if defined ( LIBSPEC_WWDATELIB_API ) */

#pragma message ( "processing DateLib_P6C.H, defining LIBSPEC_WWDATELIB_API completed." )

//  ----------------------------------------------------------------------------
//  The following headers define additional date/time functions that I developed
//  as independent modules, and a table of standard date formatting strings. All
//	three must enter the translation stream after LIBSPEC_WWDATELIB_API is 
//	defined.
//  ----------------------------------------------------------------------------

#include <Weekdays_WW.H>
#include <IsLeapYear_WW.H>
#include <ReformatSysDate_P6C_FormatStrings.H>

/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |                * * *    D A T A   S T R U C T U R E S   * * *                |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

//	----------------------------------------------------------------------------
//	Since it declares routines that use take pointers to TIME_P6C structures as
//	arguments, WWDateLib_P6C_Pvt.H defines it; since WWDateLib_P6C_Pvt.H must 
//	be included ahead of this file to satisfy preprocessor symbol prerequisites
//	for including windows.h, if guard variable __WWDATELIB_P6C_PVT_INCLUDED__ is
//	defined, so is TIME_P6C, and redefinition is a compiler error.
//
//	Consumer code must never define __WWDATELIB_P6C_PVT_INCLUDED__, and has no
//	good reason to do so. Hence, for consumers, this bit of preprocessor magic
//	is moot.
//	----------------------------------------------------------------------------

typedef struct _tagTIME_P6C
{
	SYSTEMTIME  *	SysTime ;
	LPTSTR			MonthAbbr ;
	LPTSTR			MonthName ;
	LPTSTR			WeekdayAbbr ;
	LPTSTR			WeekdayName ;
} TIMEP6C , FAR *LPTIMEP6C ;

typedef const LPTIMEP6C					CLPTIMEP6C ;
typedef const LPSYSTEMTIME              CLPSYSTEMTIME ;
/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |                    * * *    E R R O R   C O D E S   * * *                    |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

/*
    ----------------------------------------------------------------------------
    For additional information about the APPLICATION_ERROR_MASK bit, see
    WinError.h, WinNT.h, and the documentation for Windows API function
    GetLastError.
    ----------------------------------------------------------------------------
*/

#define DATEINFO_INVALID_MONTH_P6C          (  1 | APPLICATION_ERROR_MASK )
#define DATEINFO_INVALID_WEEKDAY_P6C        (  2 | APPLICATION_ERROR_MASK )
#define DATEINFO_MALLOC_ERROR_P6C           (  3 | APPLICATION_ERROR_MASK )
#define REFORMATSYSDATE_MALLOC_ERROR_P6C    (  4 | APPLICATION_ERROR_MASK )
#define REFORMATSYSDATE_NULL_FMT_P6C        (  5 | APPLICATION_ERROR_MASK )
#define REFORMATSYSDATE_EMPTY_FMT_P6C       (  6 | APPLICATION_ERROR_MASK )

#define REFORMATSYSDATE_NO_SATELLITE_P6C    ( 17 | APPLICATION_ERROR_MASK )
#define REFORMATSYSDATE_LOAD_SATELLITE_P6C  ( 18 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  Originally considered private, I decided that these constants have uses
//  beyond the scope of the GetDateInfo_P6C functions for which I created them.
//  ----------------------------------------------------------------------------

#define RFD_CAL_MIN_MONTH_NBR               1
#define RFD_CAL_MAX_MONTHS                  13
#define RFD_CAL_MAX_MONTH_INDX              ( RFD_CAL_MAX_MONTHS - 1 )

#define RFD_CAL_MIN_WEEKDAY_IDX             0
#define RFD_CAL_MAX_WEEKDAYS                7
#define RFD_CAL_MAX_WEEKDAY_IDX             ( RFD_CAL_MAX_WEEKDAYS - 1 )

//  ----------------------------------------------------------------------------
//  I moved the embedded string literals to a resource-only satellite DLL, and
//  defined their resource ID numbers in ReformatSysDate_P6C_FormatStrings.H.
//  ----------------------------------------------------------------------------

/*
  +------------------------------------------------------------------------------+
  |                                                                              |
  |      * * *    B E G I N   F U N C T I O N   P R O T O T Y P E S   * * *      |
  |                                                                              |
  +------------------------------------------------------------------------------+
*/

#if defined ( __cplusplus )
extern "C" {
#endif /* #if defined ( __cplusplus ) */

/*
    ============================================================================

    Function Name:      FormatTimeNowP6C and FormatTimeNowP6C_VB

    Synopsis:           Given a pointer to a format string, format the CURRENT 
                        date for display. Use the Windows NLS (National Language 
                        Support) functions to retrieve the corresponding month
                        and weekday name and abbreviation strings for use in the
                        displayed date.

    Arguments:          plpFormatString = The tokens embedded in this string
                                          indicate which parts of the SYSTEMTIME
                                          structure to include, and where.

                        pfUTC           = Set this Boolean value to TRUE to get
                                          the system time as UTC. Otherwise, the
                                          time in the local time zone, per the
                                          user's regional settings, is reported.

    Returns:            If it succeeds, the function returns the current system
                        time, formatted as specified by the format string. If it
                        fails, the return value is NULL. To get details about
                        the failure, call GetLastError, expecting a system error
                        code.

    Remarks:            Since this function returns through ReformatSysDate_P6C,
                        it adheres to the same formatting rules.

                        FormatTimeNowP6C_VB is a wrapper, to make this function
                        accessible to Visual Basic for Applications, which was
                        the motivation for creating the whole set.

    Date Written:       Tuesday, 24 February 2015
    ============================================================================
*/

LPTSTR LIBSPEC_WWDATELIB_API FormatTimeNowAP6C
(
    LPCTSTR         plpFormatString ,
    CBOOL           pfUTC
) ;

LPTSTR LIBSPEC_WWDATELIB_API FormatTimeNowWP6C
(
    LPCTSTR         plpFormatString ,
    CBOOL           pfUTC
) ;

#if defined ( UNICODE )
    #define FormatTimeNowP6C FormatTimeNowWP6C
#else
    #define FormatTimeNowP6C FormatTimeNowAP6C
#endif  /* #if defined ( UNICODE ) */

BSTR __stdcall FormatTimeNowP6C_VB
(
    LPCTSTR         plpFormatString ,
    CBOOL           pfUTC
) ;


/*
    ============================================================================

    Function Name:      GetDateInfo_P6C

    Synopsis:           Given a populated SYSTEMTIME structure, use the Windows
                        NLS (National Language Support) functions to retrieve
                        the corresponding month and weekday abbreviation and
                        name strings.

    Arguments:          pSysTime        = A populated SYSTEMTIME, returned by
                                          functions GetSystemTime, GetLocalTime,
                                          GetFileTime, and others supplied by
                                          either the Windows API, another API,
                                          or a caller.

    Returns:            rutpTimeInfo    = A TIMEP6C structure containing a
                                          SYSTEMTIME structure, augmented by
                                          pointers to strings containing the
                                          full and abbreviated names of the
                                          month and weekday that correspond to
                                          the date in the SYSTEMTIME structure.

    Remarks:            1) If this function, or any of the Windows API functions
                           that it calls, fails, you can expect kernel function
                           SetLastError to  have been called.

                        2) All but the SysTime element of the TIMEP6C structure
                           is initialized to NULL, and the last element 
                           populated is the WeekdayName element. Therefore, if 
                           this element is NULL when the function returns, an 
                           error has occurred, and you can call GetLastError for
                           details.

                        3) To avoid a memory leak of 256 TCHARS (256 bytes, in
                           this case), the memory to which the following
                           elements point should be freed by calling HeapFree
                           against the default process heap.

                                rutpTimeInfo.MonthAbbr
                                rutpTimeInfo.MonthName
                                rutpTimeInfo.WeekdayAbbr
                                rutpTimeInfo.WeekdayName

    References:         http://msdn.microsoft.com/library/en-us/intl/nls_3hf3. asp
                        Documents function GetCalendarInfo.

                        http://msdn.microsoft.com/library/en-us/intl/nls_808e.asp
                        Documents Calendar Type Information constants used with
                        GetCalendarInfo.

                        http://msdn.microsoft.com/library/en-us/sysinfo/base/systemtime_str.asp
                        Documents the SYSTEMTIME data structure that is used as
                        input, and incorporated into the output, of this
                        function.

    Calls:              The following functions are called, in the order listed.

                        -------------------------------------------------
                        Function        Header          Library
                        --------------- --------------- -----------------
                        SetLastError    Winbase.h       Kernel32.lib
                        GetProcessHeap  Winbase.h       Kernel32.lib
                        HeapAlloc       Winbase.h       Kernel32.lib
                        GetCalendarInfo Winnls.h        Kernel32.lib
                        -------------------------------------------------

    Date Written:       Friday, 09 December 2005 - Sunday, 11 December 2005.

    ============================================================================
*/

TIMEP6C LIBSPEC_WWDATELIB_API GetDateInfoA_P6C
(
    CLPSYSTEMTIME	pSysTime
) ;

TIMEP6C LIBSPEC_WWDATELIB_API GetDateInfoW_P6C
(
    CLPSYSTEMTIME	pSysTime
) ;

#ifdef UNICODE
    #define GetDateInfo_P6C GetDateInfoW_P6C
#else
    #define GetDateInfo_P6C GetDateInfoA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      ReformatSysDate_P6C

    Synopsis:           Given a pointer to a populated SYSTEMTIME structure and
                        a pointer to a format string, format the date for
                        display. Use the Windows NLS (National Language Support)
                        functions to retrieve the corresponding month and
                        weekday name and abbreviation strings for use in the
                        displayed date.

    Arguments:          pSysTime        = A populated SYSTEMTIME, returned by
                                          functions GetSystemTime, GetLocalTime
                                          GetFileTime, and others supplied by
                                          either the Windows API, another API,
                                          or a programmer.

                        plpFormatString = The tokens embedded in this string
                                          indicate which parts of the SYSTEMTIME
                                          structure to include, and where.

    Returns:            rlpDateString   = A long pointer to a null terminated
                                          string containing the formatted date
                                          The returned string is empty if there
                                          is an error.

    Remarks:            1) If this function, or any of the Windows API functions
                           that it calls, fails, you can expect kernel function
                           SetLastError to have been called.

                        2) All but the SysTime element of the TIMEP6C structure
                           is initialized to NULL, and the last element 
                           populated is the WeekdayName element. Therefore, if
                           this element is NULL when the function returns, an
                           error has occurred, and you can call GetLastError for
                           details.

                        3) To avoid a memory leak of 256 TCHARS (256 bytes, in
                           the ANSI version, 512 bytes in the Unicode build),
                           the memory to which the following elements point
                           should be freed by calling HeapFree against the
                           default process heap.

                                rutpTimeInfo.MonthAbbr
                                rutpTimeInfo.MonthName
                                rutpTimeInfo.WeekdayAbbr
                                rutpTimeInfo.WeekdayName

                        4) The groups of similar tokens for hour, month, and
                           weekday must be in the order shown, longest first, so
                           that, if the longest token appears in the format, it
                           will be found and consumed before the search for the
                           shorter tokens, which may also be present, begins
                           Otherwise, the first token found will be consumed.
                           leaving a partial token, which will either generate
                           an invalid match, or be left in the final string

    References:         http://msdn.microsoft.com/library/en-us/intl/nls_3hf3.asp
                        documents function GetCalendarInfo.

                        http://msdn.microsoft.com/library/en-us/intl/nls_808e.asp
                        documents Calendar Type Information constants used with
                        GetCalendarInfo.

                        http://msdn.microsoft.com/library/en-us/sysinfo/base/systemtime_str.asp
                        documents the SYSTEMTIME data structure that is used as
                        input, and incorporated into the output, of this function.

    Calls:              The following functions are called, in the order listed.

                        -------------------------------------------------
                        Function        Header          Library
                        --------------- --------------- -----------------
                        SetLastError    Winbase.h       Kernel32.lib
                        GetProcessHeap  Winbase.h       Kernel32.lib
                        HeapAlloc       Winbase.h       Kernel32.lib
                        GetCalendarInfo Winnls.h        Kernel32.lib
                        -------------------------------------------------

    Date Written:       Friday, 09 December 2005 - Monday, 12 December 2005.

    ============================================================================
*/

LPTSTR LIBSPEC_WWDATELIB_API ReformatSysDateA_P6C
(
    CLPSYSTEMTIME	pSysTime ,
    LPCTSTR         plpFormatString
) ;

LPTSTR LIBSPEC_WWDATELIB_API ReformatSysDateW_P6C
(
    CLPSYSTEMTIME	pSysTime ,
    LPCTSTR			plpFormatString
) ;

#if defined ( UNICODE )
    #define ReformatSysDate_P6C ReformatSysDateW_P6C
#else
    #define ReformatSysDate_P6C ReformatSysDateA_P6C
#endif  /* #if defined ( UNICODE ) */


/*
    ============================================================================

    Function Name:      LoadFormatStringLibrary_P6C

    Synopsis:           Load the library of format strings, for use with
                        ReformatSysDate_P6C. Please see Remarks.

    Arguments:          None.

    Returns:            rhInstance  = The instance handle returned by the call
                                      to LoadLibraryEx.

    Dependencies:       Satellite library ReformatSysDate_P6C.dll must be stored
                        in the directory from which WWDateLib.dll was loaded.

    Remarks:            The library which this function loads is a data-only
                        library, ReformatSysDate_P6C.dll. The resource IDs of
                        the strings defined in it are defined in C header
                        ReformatSysDate_P6C_FormatStrings.H, which may be
                        included and treated as if it were the resource.h file
                        that Visual Studio generates for the default resource
                        script in a C/C++ project.

                        ReformatSysDate_P6C_FormatStrings.H is included by this
                        header.

                        Although this library supports both ANSI and Unicode
                        operations, loading it into a process is indifferent to
                        whether it is used to retrieve ANSI strings, Unicode
                        strings, or both.

    References:         None.

    Date Written:       Tuesday, 31 January 2012

    ============================================================================
*/

HINSTANCE LIBSPEC_WWDATELIB_API LoadFormatStringLibrary_P6C ( void ) ;


/*
    ============================================================================

    Function Name:      WWDateLibErrorReported_P6C
    Defining Source:    WWDateLibErrorReported_P6C.C

    Synopsis:           Return TRUE if the last routine that caught an exception
                        reported it to the user via the console, a message box,
                        or the event log.

    Arguments:          None.

    Returns:            The return value is TRUE (nonzero) if the last exception
                        caught a routine in this library has been reported. Once
                        called, the flag is also reset, saving another call.

    Dependencies:       The main module (e. g. WWDateLib.C) must allocate and
                        initialize a BOOL, m_fErrorReported at fule scope, so
                        that it has external linkage.

    Remarks:            This routine is the first of a new class, which is
                        intended to prevent repetitively reporting the same
                        exception, usually with decreasing amounts of contextual
                        detail.

                        Usage is straightforward.

                        1)  The initial value of the flag, m_fErrorReported, is
                            FALSE. When a routine catches an exception and exits
                            without making a full report to the user, the flag
                            remains off, so the caller is expected to report the
                            error.

                        2)  When a library routine catches an exception AND
                            reports it to the user, via the console, a message
                            box, or a system event log, it sets m_fErrorReported
                            to TRUE, indicating that the error has been reported
                            to the user.

                        3)  When a calling routine is signaled that an error has
                            occurred, it calls WWDateLibErrorReported_P6C, which
                            returns the current state of flag m_fErrorReported,
                            and clears it. If WWDateLibErrorReported_P6C returns
                            TRUE, the calling program follows the appropriate
                            protocol for this type of exception, but refrains
                            from reporting it (again).

    References:         None.

    Date Written:       Sunday, 13 May 2012

    ============================================================================
*/

BOOL LIBSPEC_WWDATELIB_API WWDateLibErrorReported_P6C ( void ) ;

// Close the block of code that has "C" linkage.
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /* #if !defined ( __DATELIB_P6C_INCLUDED__ ) */