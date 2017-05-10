#ifndef _GETMYRESOURCE_WW
#define _GETMYRESOURCE_WW

/*
    ============================================================================

    File Name:          GetMyResource_WW.H

    Library Header:     P6CStringLib1.H

    Library Names:      P6CLib1.lib (static)
                        P6CStringLib1.lib (dynamic)

    Synopsis:           Define constants and functions exported by six library
                        modules that provide efficient access to Win32 resource
                        string to code in all classes of Portable Executable
                        program files.

    Arguments:          Please see individual function definitions.

    Returns:            Please see individual function definitions.

    IMPORTANT:          This header MUST follow CommonConstants_P6C.H if both
                        appear in the same source file.

    Remarks:            1)  This header defines three pairs of functions (one
                            each for returning ANSI and Unicode strings) for
                            extracting Windows resource strings. Each pair is
                            intended for a specific set of circumstances.

                            Function Name         Intended Use
                            --------------------- ------------------------------
                            GetConsoleResource_WW Extract a resource from a
                                                  console mode program that was
                                                  loaded into a new process when
                                                  that process was created.

                                                  These programs run without an
                                                  instance handle, and require a
                                                  slightly different method for
                                                  extracting their resources.

                            GetDLLResource_WW     Extract a resource string from
                                                  the DLL or EXE that contains
                                                  it, using its own instance
                                                  handle.

												  This routine is effective only
												  when called from a DLL or EXE
												  into which GetDLLResource_WW
												  is statically linked.

                                                  For this function to succeed 
												  with an EXE, the EXE must run
												  in the GUI subsystem. Us
												  GetConsoleResource_WW for
												  console mode programs.

                            GetAnyResource_WW     Extract a resource string from
                                                  ANY executable (DLL or EXE)
                                                  file whose instance handle is
                                                  known to the caller. The
                                                  function and the resource may
                                                  be in different files, so long
                                                  as you know the instance
                                                  handle of the file that
                                                  contains the desired resource
                                                  string.
                            ----------------------------------------------------

                            All functions return long pointers to strings
                            (LPTSTR), using memory allocated from the default
                            process heap to hold the strings, and return a
                            handle (pointer), which MUST be subsequently freed
                            by calling Windows function HeapFree, passing a
                            handle to the process heap, and the pointer.

                        2)  A return value of zero from LoadString means only
                            that no string was returned, or that the returned
                            string is empty. This means that an invalid string
                            ID won't get reported!

                            Should this happen, GetLastError will return a new
                            status code, VER_INVALID_RESOURCE_ID_P6C.

                        Please see Reference 4.

    References:         "LoadString Function," Windows User Interface, MSDN.
                        http://msdn.microsoft.com/en-us/library/ms647486(VS.85).aspx
                        Pay close attention to the first community comment,
                        titled, "Return value 0 or -1."

                        Please see individual function definitions for
                        additional references.

    Calls:              Please see individual function definitions.

    Author:             David A. Gray, of Simple Soft Services, Inc., d/b/a
                        WizardWrx, Irving, Texas, USA.

    Date Written:       Saturday, 18 March 2007 through Saturday, 28 April 2007.

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
	2007/04/29 DAG First working version.

    2009/02/19 DAG Fix buffer sizing error in the Unicode version of
                   GetConsoleResource_WW, to prevent a buffer overrun, and fix
                   the ANSI version to match it.

    2009/08/20 DAG 1) Tidy up the comments, fixing several typographical errors
                      that I discovered while reviewing the documentation of
                      function GetDLLResource_WW.

                      NOTE: Although this is strictly a documentation change,
                            since the same change must be made in the source
                            files of the affected functions, I recompiled both
                            the debug and release builds.

    2010/03/08 DAG 1) Correct mapping of GetConsoleResource_WW.

                   2) Include windows.h, in case this header is ever the
                      first included in a source code stream, and #pragma
                      once, as a redundant method of ensuring that
                      GetMyResource_WW.H is processed one time only within a
                      translation unit.

                   3) Add symbolic constants INVALID_RES_ID and NO_STRING.

    2010/04/10 DAG Adjust all functions to compensate for the fact that
                   LoadString returns zero, without setting LastError when the
                   specified string is empty or absent.

    2010/06/04 DAG Move the #pragma once preprocessor directive outside the
                   scope of the preprocessor variable which performs the same
                   function for other C compilers.

    2011/09/17 DAG 1) On error, set the variable that holds the return value,
                      rlpMyString, to NULL. As it was, rlpMyString held the
                      pointer returned by HeapAlloc, which is invalidated when
                      the function fails. This change affects all six functions.

                   2) Implement separate return codes for invalid resource ID
                      (ID < 1) and string resource not found.

                   3) Change the argument type for the resource ID from int to
                      const unsigned int, which is the type defined in the
					  prototype of LoadString.

                   4) Substitute APPLICATION_ERROR_MASK, which is defined in
                      WinNT.H, for CUSTOMER_FLAG.

    2011/10/02 DAG Ensure that all result codes returned by this library are
                   unique within the scope of this library.

    2011/11/06 DAG Add ANSI and Unicode implementations of a new function,
                   GetMyResource_ErrMsg_WW, to translate error messages about
                   invalid resource string requests.

    2012/05/26 DAG Define a new constant, LOOK_IN_THIS_EXE, for use when you
                   call GetAnyResource_WW() from a console program.

                   NOTE: Since this is the only change, neither the DLL where
                         the functions defined in this library live, nor any
                         consuming code, requires recompilation, although I
                         shall build a new DLL, along with the underlying
                         static link library, later today.

    2012/06/02 DAG 1) Remove the conditional inclusion block that surrounded
                      symbolic constants INVALID_RES_ID and NO_STRING, which
                      have uses outside the private code for which I defined
					  them.

                   2) Eliminate private constant MSGBUFSIZE_BYTES_WW, which is
                      unreferenced. (This is confirmed by a series of text file
					  searches, by way of P6Grep.PL.)

                   The same statements made about the 2012/05/26 update apply to
                   this update, too.

    2012/06/30 DAG 1) Based on recently gained knowledge of how various guard
                      code schemes work, move the #pragma once block inside
                      the block protected by the preprocessor guard variable.

                   2) The LIBSPEC_P6CSTRINGLIB1_API calling convention is now
                      fully implemented.

    2013/06/18 DAG Eliminate an overlooked reference to CommonConstants_P6C.H
                   and substitute Const_Typedefs_WW.H, which is plenty for a
                   public interface. This update is built into P6CStringLib1,
                   version 2,8,1,0.

    2013/09/02 DAG GetDLLResource_WW works better if it uses the right
                   instance handle, which is m_hinstMyInstance. Global
                   instance handle m_hinstMyInstance is an unused spare. This
                   update is built into P6CStringLib1, version 2,8,5,0.

	2016/01/10 DAG Incorporate the standard three-clause BSD license.

	2016/07/08 DAG Implement GetConsoleResource_WW and GetDLLResource_WW as CPP
	               macros, using the same technique that I did two years ago to
				   effectively eliminate DllLoadAsData_WW.
    ============================================================================
*/

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /* #if defined (_MSC_VER) && (_MSC_VER >= 1020) */


#include <windows.h>
#include <Const_Typedefs_WW.H>

//  ----------------------------------------------------------------------------
//  Define specialized symbols used in these routines, rather than waste the
//  overhead of a whole header file for three symbols.
//  ----------------------------------------------------------------------------

#define INVALID_RES_ID                      ZERO_WW
#define NO_STRING                           ZERO_WW

//  ----------------------------------------------------------------------------
//  Define specialized typedefs for use as resource ID argument types.
//  ----------------------------------------------------------------------------

typedef const unsigned int                  RES_STRING_ID ;

//  ----------------------------------------------------------------------------
//  Define specialized constants for use as arguments.
//
//  NOTE:   Only a console program has a null instance handle, but I use a NULL
//          instance handle as a signal to GetAnyResource_WW() to look for the
//          requested resource string in the EXE that was first loaded into the
//          process.
//  ----------------------------------------------------------------------------

#define LOOK_IN_THIS_EXE                    0x00000000  // See note above.


//  ----------------------------------------------------------------------------
//  Define error codes set by these routines.
//  ----------------------------------------------------------------------------

#define GETMYRESOURCE_ERR_INVALID_ID_P6C    ( 0x00000051 | APPLICATION_ERROR_MASK )
#define GETMYRESOURCE_ERR_ID_NOT_FOUND_P6C  ( 0x00000052 | APPLICATION_ERROR_MASK )
#define GETMYRESOURCE_ERR_MALLOC_ERROR_P6C  ( 0x00000001 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  If this header is included on its own, LIBSPEC_P6CSTRINGLIB1_API, defined in
//  P6CStringLib1.H, must be defined in order for thefollowing declarations to
//  compile correctly.
//  ----------------------------------------------------------------------------

#ifndef LIBSPEC_P6CSTRINGLIB1_API
    #ifdef  _BUILDING_P6CSTRINGLIB1
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
    #else
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
    #endif  /* _BUILDING_P6CSTRINGLIB1 */
#endif  /* #ifndef  LIBSPEC_P6CSTRINGLIB1_API */


//  Enforce C linkage.
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
    ============================================================================

    Function Name:      GetAnyResource_WW

    Synopsis:           Given an integer containing the ID of a resource stored
                        in a dynamic link library (DLL) or GUI mode (Windows)
                        program (EXE) file, return a string containing the
                        requested resource string.

    Arguments:          pcuintResourceID = A const unsigned integer
                                           (RES_STRING_ID) containing the ID of
                                           the desired Windows resource string
                                           to be returned from the module that
                                           was loaded into the process at
                                           startup.

                        phInstance       = A HINSTANCE (actually, a 32 bit
                                           integer) containing the instance
                                           handle of the executable file (EXE or
                                           DLL) that contains the desired
                                           resource string.

    Returns:            rlpMyString      = A long pointer to a string containing
                                           the requested resource string, or
                                           NULL if the string is not found. See
                                           Remarks.

    Remarks:            1) If the function returns a NULL pointer AND
                           GetLastError returns ERROR_SUCCESS (zero), there is
                           no string with an ID of pcuintResourceID in the DLL
                           or EXE file.

                        2) All errors are reported through kernel library
                           function SetLastError.

                        3) All resource strings to be returned by this function
                           must reside in the same DLL or Windows GUI mode EXE
                           that calls it. Use function GetConsoleResource_WW to
                           extract resources from console mode EXE programs.

                        4) This function is intended for retrieving resources
                           from ANY Portable Executable (PE) file for which the
                           calling function has an instance handle. The EXE file
                           that is loaded into a process when the process is
                           created has its own instance handle, which is passed
                           into its WinMain procedure. Likewise, any DLL has an
                           instance handle, which is passed into its DLLMain
                           function, which Windows calls when the library is
                           loaded.

                           - To retrieve resource strings from a DLL, you must
                             obtain its instance handle. The simplest way to get
                             resource strings from a DLL is to include function
                             GetDLLResource_WW in it, and have its DLLMain
                             function satisfy its requirements by saving the
                             instance handle into a module variable, where it is
                             visible to GetDLLResource_WW.

                           - Since console mode applications lack an instance
                             handle, use GetConsoleResource_WW to extract their
                             resources.

                           - A DLL that is called by a console mode program has
                             an instance handle.

                        5) As is the case with all of my functions that return a
                           long pointer to a string, that pointer points to a
                           memory block allocated from the default process heap.
                           You can free the memory by calling HeapFree, passing
                           a handle to the default process heap, and the pointer
                           that you received from this function.

                        5) The buffer returned by this function is the minimum
                           size required to contain the string and its terminal
                           null character.

    References:         None.

    Calls:              The following functions are called, in the order listed.

                        Function        Header          Library
                        --------------- --------------- -----------------
                        SetLastError    Winbase.h       Kernel32.lib.
                        GetProcessHeap  Winbase.h       Kernel32.lib.
                        HeapAlloc       Winbase.h       Kernel32.lib.
                        LoadString      Winbase.h       User32.lib.
                        --------------------------------------------------

    Date Written:       Saturday, 14 April 2007 and Sunday, 15 April 2007.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version  Author Synopsis
    ---------- -------- ------ -------------------------------------------------
    2007/04/28 1,0,0,1  DAG/WW First working version.
    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API GetAnyResourceA_WW
(
    RES_STRING_ID pcuintResourceID ,
    HINSTANCE     phInstance
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API GetAnyResourceW_WW
(
    RES_STRING_ID pcuintResourceID ,
    HINSTANCE     phInstance
) ;

#ifdef UNICODE
    #define GetAnyResource_WW   GetAnyResourceW_WW
#else
    #define GetAnyResource_WW   GetAnyResourceA_WW
#endif  /* #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      GetConsoleResource_WW

    Synopsis:           Given an integer containing the ID of a resource stored
                        in a console mode program (EXE) file, return a string
                        containing the requested resource string.

    Arguments:          pcuintResourceID = A const unsigned integer
                                           (RES_STRING_ID) containing the ID of
                                           the desired Windows resource string
                                           to be returned from the module that
                                           was loaded into the process at
                                           startup.

    Returns:            rlpMyString      = A long pointer to a string containing
                                           the requested resource string, or
                                           NULL if the string is not found. See
                                           Remarks.

    Remarks:            1) If the function returns a NULL pointer AND
                           GetLastError returns ERROR_SUCCESS (zero), there is
                           no string with an ID of pcuintResourceID in the DLL
                           or EXE file.

                        2) All errors are reported through kernel library
                           function SetLastError.

                        3) All resource strings to be returned by this function
                           must reside in the same DLL or Windows GUI mode EXE
                           that calls it. Use function GetConsoleResource_WW to
                           extract resources from console mode EXE programs.

                        4) This function is intended for retrieving resources
                           from console mode programs, which come WITHOUT an
                           instance handle.

                        5) As is the case with all of my functions that return a
                           long pointer to a string, that pointer points to a
                           memory block allocated from the default process heap.
                           You can free the memory by calling HeapFree, passing
                           a handle to the default process heap, and the pointer
                           that you received from this function.

                        6) The buffer returned by this function is the minimum
                           size required to contain the string and its terminal
                           null character.

    References:         None.

    Calls:              The following functions are called, in the order listed.

                        Function        Header          Library
                        --------------- --------------- -----------------
                        SetLastError    Winbase.h       Kernel32.lib.
                        GetProcessHeap  Winbase.h       Kernel32.lib.
                        HeapAlloc       Winbase.h       Kernel32.lib.
                        LoadString      Winbase.h       Kernel32.lib.
                        --------------------------------------------------

    Date Written:       Saturday, 14 April 2007 and Sunday, 15 April 2007.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version  Author Synopsis
    ---------- -------- ------ -------------------------------------------------
    2007/04/29 1,0,0,16 DAG/WW First working version.

    2009/02/19 1,0,0,19 DAG/WW Fix buffer sizing error in the Unicode version, to
                               prevent an overrun, and fix the ANSI version to
                               match it.

    2009/08/20 1,0,0,22 DAG/WW 1) Tidy up the comments, fixing several
                                  typographical errors that I discovered while
                                  reviewing the documentation of function
                                  GetDLLResource_WW.

                                  NOTE: Although this is strictly a
                                        documentation change, since the same
                                        change must be made in the source files
                                        of the affected functions, I recompiled
                                        both the debug and release builds.

    2010/03/06 1,0,0,25 DAG/WW  Correct mapping of GetConsoleResource_WW.
    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API GetConsoleResourceA_WW
(
    RES_STRING_ID pcuintResourceID
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API GetConsoleResourceW_WW
(
    RES_STRING_ID pcuintResourceID
) ;

//  ----------------------------------------------------------------------------
//  This mapping effectively substitutes a CPP macro for this function, which
//  is just syntactic sugar that hides an argument that has a fixed value in the
//	scenarios in which it is appropriate.
//  ----------------------------------------------------------------------------

#if defined ( __GETCONSOLERESOURCE_WW_FUNCTION )
	#if defined ( UNICODE )
		#define GetConsoleResource_WW   GetConsoleResourceW_WW
	#else
	    #define GetConsoleResource_WW   GetConsoleResourceA_WW
	#endif  /*#if defined ( UNICODE ) */
#else
	#define GetConsoleResource_WW(pcuintResourceID)  ( GetAnyResource_WW ( pcuintResourceID , LOOK_IN_THIS_EXE ) )
#endif	/* #if defined ( __GETCONSOLERESOURCE_WW_FUNCTION ) */


/*
    ============================================================================

    Function Name:      GetMyResource_ErrMsg_WW

    Synopsis:           Augment the basic information supplied by the Microsoft
                        Windows API with enough details to give debuggers a clue
                        about how to correct the reported error.

    Arguments:          plpcHint         = A const pointer to a string to add to
                                           the beginning of the message. Please
                                           see the remarks.

    Arguments:          pcuintResourceID = An unsigned integer (RES_STRING_ID)
                                           containing the ID of the desired
                                           Windows resource string.

                        phInstance       = A HINSTANCE (actually, a 32 bit
                                           integer) containing the instance
                                           handle of the executable file (EXE or
                                           DLL) that is expected to contain the
                                           resource string.

    Returns:            rlpMessage      = A long pointer to a string containing
                                           the message to display or log. Please
                                           see the remarks.

    Remarks:            1) The objective of argument plpcHint is to supply some
                           context, to identify where in the source code tree to
                           look for the call that caused the exception.

                        2) For a console program, phInstance is always NULL.

                        3) This function supports the other functions defined in
                           this header, in addition to calls to LoadString from
                           other routines.

                        4) As is the case with all of my functions that return a
                           long pointer to a string, that pointer points to a
                           memory block allocated from the default process heap.
                           You can free the memory by calling HeapFree, passing
                           a handle to the default process heap, and the pointer
                           that you received from this function.

                        5) The buffer returned by this function is the minimum
                           size required to contain the string and its terminal
                           null character.

    References:         None.

    Calls:              The following functions are called, in the order listed.

                        Function        Header          Library
                        --------------- --------------- -----------------
                        SetLastError    Winbase.h       Kernel32.lib.
                        GetProcessHeap  Winbase.h       Kernel32.lib.
                        HeapAlloc       Winbase.h       Kernel32.lib.
                        LoadString      Winbase.h       User32.lib.
                        --------------------------------------------------

    Date Written:       Saturday, 05 November 2011 and Sunday, 06 November 2011

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version Author Synopsis
    ---------- ------- ------ --------------------------------------------------
    2011/11/06 2,5,3,0 DAG/WW First working version.
    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API GetMyResource_ErrMsgA_WW
(
    LPCTSTR       plpcHint ,
    RES_STRING_ID pcuintResourceID ,
    HINSTANCE     phInstance
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API GetMyResource_ErrMsgW_WW
(
    LPCTSTR       plpcHint ,
    RES_STRING_ID pcuintResourceID ,
    HINSTANCE     phInstance
) ;

#ifdef UNICODE
    #define GetMyResource_ErrMsg_WW   GetMyResource_ErrMsgW_WW
#else
    #define GetMyResource_ErrMsg_WW   GetMyResource_ErrMsgA_WW
#endif  /*  #ifdef UNICODE */


// Close the block of code that has "C" linkage.
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /* _GETMYRESOURCE_WW */