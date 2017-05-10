#ifndef _ISLEAPYEAR_WW
#define _ISLEAPYEAR_WW

/*
    ============================================================================

    Module Name:        IsLeapYear_WW.H

    Synopsis:           Declare function IsLeapYear_WW and its associated
                        constants.

    Dependencies:       If your development platform supports it, IsLeapYear_WW
                        reports out of range years through SetLastError.

                        Otherwise, out of range years are reported through a
                        global CRT variable, errno.

    References:         1)  "9. Boolean Expressions and Variables,
                            comp.lang.c FAQ list · Question 9.1,"
                            See also question 9.2, the next question in the FAQ.
                            http://c-faq.com/~scs/cgi-bin/faqcat.cgi?sec=bool

                        2)  "Online C++ Tutorial< Section 3.4: Operators",
                            http://www.intap.net/~drw/cpp/cpp03_04.htm

                        3)  "Variables," in "C Basics," at
                            http://www.cs.cf.ac.uk/Dave/C/node4.html#SECTION00440000000000000000

    Author:             David A. Gray, of Simple Soft Services, Inc.,
                        d/b/a WizardWrx, Irving, Texas, USA.

    Date Written:       Monday, 07 December 2009.

    Copyright:          Copyright 2009, David A. Gray,
                        Irving, Texas, USA.
                        All rights reserved world wide.

    Licensing:          This code is licensed under the FreBSD license.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Author Synopsis
    ---------- ------ ----------------------------------------------------------
    2009/12/10 DAG/WW First working version.

    2010/03/08 DAG/WW Remove version numbers, which have no practical meaning
                      when applied to functions that are part of a static link
                      library, which has no discernable version number.

    2010/03/30 DAG/WW Change calling convention decoration from _stdcall to
                      WINAPI, to be consistent with my other public functions.

    2010/06/04 DAG/WW Add a #pragma once preprocessor directive outside the
                      scope of the preprocessor variable which performs the same
                      function for other C compilers.

    2011/09/20 DAG/WW 1) Substitute const unsigned int for const int in both
                         function prototypes, by way of a typedef, CYEAR.

                      2) Separate IsValidGregorianYear_WW and IsLeapYear_WW into
                         individual source files. This separation enables
                         statically linked code to call IsValidGregorianYear_WW
                         independently, if that's all it needs, without bringing
                         IsLeapYear_WW along for the ride. The opposite is not
                         true, since IsLeapYear_WW calls IsValidGregorianYear_WW
                         to exclue out of range years from consideration.

                      3) Substitute APPLICATION_ERROR_MASK for CUSTOMER_FLAG and
                         the literal 0x20000000. Having discovered this standard
                         symbol, APPLICATION_ERROR_MASK replaces CUSTOMER_FLAG.

    2015/03/18 DAG/WW Undefine WIN32_LEAN_AND_MEAN, which has no business being
                      being in a library header, although it may be safely
                      removed without requiring the associated source code to be
                      recompiled.
    ============================================================================
*/

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /* #if defined (_MSC_VER) && (_MSC_VER >= 1020) */



//  ----------------------------------------------------------------------------
//  Declare special symbolic constants and typedefs used by the functions
//  delcared in this header, starting with the typedef for their arguments.
//  ----------------------------------------------------------------------------

#ifndef CYEAR
typedef const unsigned int    CYEAR ;
#endif  /* #ifndef CYEAR */


/*
    ----------------------------------------------------------------------------
    When processing straight C source files, most C/C++ compilers don't natively
    support the bool data type, which didn't make its way into the ANSI C
    standard until C99, . However, since the values returned by some functions
    beg for treatment as Boolean types, I elected to define and use a Boolean
    type that corresponds to the c++ bool type.

    Along the same lines, I defined symbolic true and false values, neither of
    which is defined unless bool is also defined.

    These three definitions reflect the outcome of research that solved a puzzle
    that had bothered me for the last five years. Since every syntax higlighting
    text editor that I've ever used with C or C++ source code highlights bool,
    true, and false as if they were keywords, I was puzzled by the fact that, if
    you dared to actually use them in straight C code, the compiler flagged them
    as an undefined. Now, I know why; the editors assume C++ keywords. Nobody
    bothered to develop a keyword file that is purely C; now that it's in the
    ANSI standard, it doesn't matter.
    ----------------------------------------------------------------------------
*/

#ifndef __cplusplus
#ifndef bool
typedef int     bool ;
#endif  /*  #ifndef bool */

#ifndef true
#define true    1
#endif  /*  #ifndef true */

#ifndef false
#define false   0
#endif  /*  #ifndef false */
#endif  /*  #ifndef __cplusplus */


/*
    ----------------------------------------------------------------------------
    The Gregorian calendar came into existence in 1582, when it was authorized
    by Pope Gregory. However, it was not widely adopted for amother 150 years or
    so. Nevertheless, since this leap year formula applies only to the Gregorian
    calendar, and differs from the formula that applied to its predecessor, the
    Julian calendar, this algorithm cannot be applied to years prior to 1582.

    Note that 1582 is NOT a leap year in either calendar.

    As a practical matter, we also exclude dates after 9999 A. D., on principle.
    There is no such limit built into the Gregorian calendar or its algorithm to
    identify leap years. Nevertheless, I think it's reasonable to establish such
    an upper limit, because most software breaks if you feed it a year of more
    than four decimal digits.
    ----------------------------------------------------------------------------
*/

#define GRGORIAN_CALENDAR_ADOPTION_YEAR_WW  1582
#define GREGORIAN_YEAR_TOO_HIGH_WW          10000

#define CENTURY_YEAR_DIVISOR                100
#define LEAP_YEAR_MODULUS                   0
#define LEAP_YEAR_SKIPPED_CENTURY_YEAR      400
#define LEAP_YEAR_DIVISOR                   4


/*
    ----------------------------------------------------------------------------
    If your compiler and development environment support Win32 programming, they
    should define the WIN32 preprocessor variable. If so, the following block of
    code incorporates windows.h, so that we can call GetLastError if the year is
    out of range.

    Otherwise, we include errno.h, which defines the standard (documented) error
    constants, for use with the global CRT error variable, errno, a standard CRT
    global variable, which should be available on all platforms that have a C
    compiler. We also define ENONE_WW, to substitute for ERROR_SUCCESS on the
    Win32 platform, since there is nothing equivalent to it in errno.h.

    Given the small number of defined error codes, I suppose the expectation is
    that a program will test for the one or two errors that might occur in the
    situation at hand, and assume success if execution falls through the tests.
    That being the case, I did the same thing with LastError, so that both code
    branches follow identical patterns.

    To ensure consistency, I mapped INVALID_GREGORIAN_YEAR_WW to EINVAL for non-
    Win32 builds. So, all you really need in order to make the caller totally
    transparent is a pair of surrogates for SetLastError and GetLastError, which
    I leave as an exercise for the reader.
    ----------------------------------------------------------------------------
*/

#ifdef WIN32

#include <windows.h>

#define INVALID_GREGORIAN_YEAR_WW           ( 7 | APPLICATION_ERROR_MASK )

#else   /*  #ifdef WIN32 - Win32 platform support ends here. */
#include <stdlib.h>
#include <errno.h>

#define ENONE_WW                            0
#define INVALID_GREGORIAN_YEAR_WW           EINVAL
#endif  /*  #ifdef WIN32 - Support for other platforms, including Unix, ends here. */


//  ----------------------------------------------------------------------------
//  Declare functions exported by this library, as always, with C linkage.
//  ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/*
    ============================================================================

    Function Name:      IsValidGregorianYear_WW

    Synopsis:           Determine whether an integer which is supposed to
                        represent a year in the Gregorian calendar falls between
                        the year when it was adopted and 9999 A. D.

    Arguments:          pintYear        = An unsigned integer containing a year,
                                          which must be between 1682 and 9999.

                                          See notes above the definition of
                                          GRGORIAN_CALENDAR_ADOPTION_YEAR_WW for
                                          further explanation.

                                          CYEAR is a typedef for const unsigned
                                          int.

    Returns:            true            = pintYear a valid Gregorian year.

                        false           = pintYear is NOT a valid Gregorian year
                                          or is greater than 9999. See Note 1.

    Notes:              1)  The end date of the Gregorian calendar is undefuned.
                            However, since most reports and screens that display
                            years allow a maximum of 4 digits, values above 9999
                            are treated as invalid.

                        2)  If the year is out of bounds, and the function is
                            compiled by a C compiler that supports the Win32
                            platform SDK, it reports an out of range value for
                            pintYear by calling SetLastError.

                            If it returns FALSE, you should call GetLastError
                            before you blindly trust the return value, unless
                            you know, by other means, that the value of pintYear
                            is greater than 1681 and less than 10000.

                        3)  If you build without Win32 support, out of bounds
                            year values are reported through the errno global
                            variable, which is exported by the C runtime library
                            and defined in errno.h. For your convenience, you
                            errno.h is included by this header, so that calling
                            code automatically has access to errno.

                        4)  This function is derived from working Visual C# code
                            in the static IsLeapYear method of my PureDate class,
                            See C:\Documents and Settings\David\My Documents\
                            Visual Studio 2005\Projects\WizardWrx_Libs\DateMath\
                            DateMath\PureDate.cs (note the line wrap.).

                        5)  Since it is implemnted in straight C, if the year is
                            out of range, and the development platform defines
                            the WIN32 preprocessor directive, Windows API
                            function SetLastError is called. (The original C#
                            implementation throws a System.ArgumentOutOfRange
                            exception.

    References:         Article 2.2 What is the Gregorian calendar?, in the Calendar FAQ.
                        http://www.tondering.dk/claus/cal/node3.html#SECTION00320000000000000000

                        XL: Method to Determine Whether a Year Is a Leap Year
                        http://support.microsoft.com/kb/214019

    Calls:              The following external functions are called, in the
                        order listed, if, and only if, your build
                        environment defines WIN32 as a preprocessor
                        variable, to indicate that it supports calls into the
                        Windows API.

                        -------------------------------------------------
                        Function        Header          Library
                        --------------- --------------- -----------------
                        SetLastError    Winbase.h       Kernel32.lib
                        -------------------------------------------------

                        In the absence of Win32 support, this program and its
                        test harness rely entirely on the CRT library.

    Date Written:       Monday, 07 December 2009 - Thursday, 10 December 2008.

    ============================================================================
*/

bool WINAPI IsValidGregorianYear_WW ( CYEAR ) ;


/*
    ============================================================================

    Function Name:      IsLeapYear_WW

    Synopsis:           Given a date that falls within the years covered by the
                        Gregorian calendar, return TRUE if it is a leap year,
                        and FALSE if not.

    Arguments:          pintYear        = An unsigned integer containing a year,
                                          which must be between 1682 and 9999.

                                          See notes above the definition of
                                          GRGORIAN_CALENDAR_ADOPTION_YEAR_WW for
                                          further explanation.

                                          CYEAR is a typedef for const unsigned
                                          int.

    Returns:            true            = pintYear is a leap year.

                        false           = pintYear is NOT a leap year. Please
                                          see Note 1.

    Remarks:            1)  The end date of the Gregorian calendar is undefuned.
                            However, since most reports and screens that display
                            years allow a maximum of 4 digits, values above 9999
                            are treated as invalid.

                        2)  If the year is out of bounds, and the function is
                            compiled by a C compiler that supports the Win32
                            platform SDK, it reports an out of range value for
                            pintYear by calling SetLastError.

                            If it returns FALSE, you should call GetLastError
                            before you blindly trust the return value, unless
                            you know, by other means, that the value of pintYear
                            is greater than 1681 and less than 10000.

                        3)  If you build without Win32 support, out of bounds
                            year values are reported through the errno global
                            variable, which is exported by the C runtime library
                            and defined in errno.h. For your convenience, you
                            errno.h is included by this header, so that calling
                            code automatically has access to errno.

                        4)  This function is derived from working Visual C# code
                            in the static IsLeapYear method of my PureDate class,
                            See C:\Documents and Settings\David\My Documents\
                            Visual Studio 2005\Projects\WizardWrx_Libs\DateMath\
                            DateMath\PureDate.cs (note the line wrap.).

                        5)  Since it is implemnted in straight C, if the year is
                            out of range, and the development platform defines
                            the WIN32 preprocessor directive, Windows API
                            function SetLastError is called. (The original C#
                            implementation throws a System.ArgumentOutOfRange
                            exception.

    References:         Article 2.2 What is the Gregorian calendar?, in the Calendar FAQ.
                        http://www.tondering.dk/claus/cal/node3.html#SECTION00320000000000000000

                        XL: Method to Determine Whether a Year Is a Leap Year
                        http://support.microsoft.com/kb/214019

    Calls:              The following external functions are called, in the
                        order listed, if, and only if, your build
                        environment defines WIN32 as a preprocessor
                        variable, to indicate that it supports calls into the
                        Windows API.

                        -------------------------------------------------
                        Function        Header          Library
                        --------------- --------------- -----------------
                        SetLastError    Winbase.h       Kernel32.lib
                        -------------------------------------------------

                        In the absence of Win32 support, this program and its
                        test harness rely entirely on the CRT library.

    Date Written:       Monday, 07 December 2009 - Thursday, 10 December 2008.

    ============================================================================
*/

bool    WINAPI IsLeapYear_WW ( CYEAR ) ;

#ifdef  __WWDATELIB_TEST_HARNESS
int     _stdcall    LeapYearTestHarness ( ) ;
#endif  /*  __WWDATELIB_TEST_HARNESS */


#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /*  _ISLEAPYEAR_WW */