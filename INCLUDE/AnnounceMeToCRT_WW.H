/*
    ============================================================================

    File Name:          AnnounceMeToCRT_WW.H

    Included in:        P6VersionInfo.H

    Library:            P6VersionInfo.dll (P6VersionInfo.lib)

    Author:             David A. Gray, of Simple Soft Services, Inc.,
                        d/b/a WizardWrx
                        http://www.wizardwrx.com/

    Date Written:       Tuesday, 20 November 2007

    License:            Copyright (C) 2007-2017, David A. Gray. All rights reserved.

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

    Date       Version Author Synopsis
    ---------- ------- ------ --------------------------------------------------
    2007/11/20         DAG/WW First working version.

    2008/06/18         DAG/WW Define preprocessor variable _ANNOUNCEMETOCRT_WW,
                              to prevent accidental redefinition.

                              Change to display VER_INTERNALNAME instead of
                              VER_PRODUCTNAME.

                              Add function AnnounceMeToCRTPN_WW which returns a
                              string containing VER_INTERNALNAME.

    2010/03/08         DAG/WW Add an optional Boolean argument which, if TRUE,
                              indicates that the caller should look to the
                              externally linked HINSTANCE, m_hinstMe, and use it
                              to extract the string resources to use for labels
                              from the DLL that contains the executing copy of
                              this function.

                              Eliminate the redundant inclusion of windows.h.
                              Since P6VersionInfo.H includes it, by way of
                              CommonConstants_P6C.H, including it here is
                              unnecessary.

                              Eliminate inclusion of P6VersionInfo.H, which
                              runs the risk of creating a circular inclusion
                              loop.

    2010/03/09         DAG/WW 1) Add constants to simplify use of the new
                                 pfGetLabelsFromDLL argument,

                              2) Remove the version numbers, which are out of
                                 place in a header that defines modules that
                                 live in a static library, which is devoid of a
                                 version number.

    2010/04/25         DAG/WW Reinstate direct inclusion of windows.h, since, as
                              of this date, CommonConstants_P6C.H works fine
                              without it.

    2010/06/04         DAG/WW Move the #pragma once preprocessor directive
                              outside the scope of the preprocessor variable
                              which performs the same function for other C
                              compilers.

    2011/09/04 1,1,2,1 DAG/WW This version upgrades internal documentation,
                              copyright notices, etc., and firmly places the
                              functions declared in this header into
                              P6VersionInfo.dll.

                              However, there are substantial structural changes
                              in the test harness, which wasn't differentiating
                              ANSI test from Unicode tests correctly.

    2012/02/05 1,4,5,1 DAG/WW 1) Implement LIBSPEC_VERSIONINFOLIB_P6C_API CPP
                                 macro, which generates more efficient dynamic
                                 link libraries, by eliminating a short jump
                                 from the Import Address Table when a routine is
                                 called.

                              2) Move the numeric version routines to the static
                                 link library, to simplify implementation of a
                                 private header file.

                              3) Move the private preprocessor variable
                                 definitions and function declarations into
                                 P6VersionInfo_P6C_Pvt.H, a private header,
                                 which lives in the source code tree of the
                                 static link library that houses the source
                                 code of everything but DLLMain.

                              4) Make GetDLLModuleName_WW public.

    2012/05/18 1,5,6,1 DAG/WW Items 1, 4, and 5 are implemented in this header.
                              Items 2 and 3 are implemented in another header,
                              P6VersionInfo_P6C_Pvt.H, which is private, used
                              only to build the routines declared here.

                              1) Generate code that can be statically linked
                                 when _GETVERSININFO_STATIC_P6C is defined.

                              2) Shorten constant VER_GETVERSIONINFO_ERRMSG, and
                                 make it compatible with EM_ShowMsgOnConsole_WW.

                              3) Define a new string, ABBREV_VER_DISP_MSG_TPL,
                                 which is similar to VER_DISP_MSG_TPL, but has
                                 one fewer lines and substitution tokens.

                              4) Implement LIBSPEC_VERSIONINFOLIB_P6C_API
                                 locally, so that the subsidiary include works
                                 independently of include P6VersionInfo.H.

                              5) Define string constants VER_FULL_BANNER and
                                 VER_BRIEF_BANNER for use with the new
                                 pfShowFullBanner argument.

                              6) Change functions AnnounceMeToCRT_WW and
                                 AnnounceMeToCRTPN_WW so that the first
                                 argument, pintFrstRsrcStrID, is ignored
                                 when pfGetLabelsFromDLL is TRUE, by taking
                                 advantage of the fact that the DLL knows the
                                 IDs of its own resource strings.

                              7) Ensure that the reported local and UTC time
                                 are always in sync by deriving the local time
                                 from the UTC time.

    2012/06/12 1,6,9,1 DAG/WW Insert a carriage return in front of every bare
                              newline character, so that Windows programs see
                              print files as proper DOS/Windows text files. This
                              change affects static strings VER_DISP_MSG_TPL and
                              ABBREV_VER_DISP_MSG_TPL.

                              This change is implemented entirely within
                              P6VersionInfo_P6C_Pvt.H

    2013/04/21 1,6,9,1 DAG/WW Define a new symbol, VER_USING_LABELS_IN_DLL_P6C,
                              for use with argument pintFrstRsrcStrID to any of
                              the functions in this library.

                              Since the underlying library is unaffected,
                              neither is the version number shown here.

    2013/06/20 1,8,0,0 DAG/WW Eliminate CommonConstants_P6C.H in favor of the
                              much more focused Const_Typedefs_WW.H.

    2014/08/21 1,9,0,0 DAG/WW Add a new function, AnnounceMeToCRTPN2_WW, which
                              is a superset of AnnounceMeToCRTPN_WW that offers
                              greater control over the output.

    2017/01/14 1,9,0,2 DAG    1) Upgrade to Visual Studio 2013, building against
                                 its version of the CRT library, confining code
                                 changes to the absolute minimum required for a
                                 successful upgrade.

                              2) Replace the original free software license,
                                 which was never used to cover a source code
                                 distribution, with a 3-clause BSD license.

    2017/01/15 1,9,1,3 DAG    1) Make macros VER_LABELS_FROM_DLL_P6C and
                                 VER_LABELS_FROM_EXE_P6C work with OR without
                                 CommonConstants_P6C.H being in the compilation
                                 stream.

    2017/01/15 2,0,0,1 DAG    Rename the library from WWKernelLibWrapper to
                              WWKernelLibWrapper32 and synchronize the name of
                              its library header, so that I can make a wholesale
                              calling convention change, from __cdecl, which I
                              didn't fully understand in 2005, to __stdcall, a
                              slightly more efficient calling convention,
                              including slightly less code bloat.

    2017/02/14 2,0,0,2 DAG    Move the routines that get the program file name
	                          and its directory to WWKernelLibeWrapper32. This
							  change affects only the master library header,
							  though this one got some cosmetic adjustments.
    ============================================================================
*/


#ifndef _ANNOUNCEMETOCRT_WW_INCLUDED_
#define _ANNOUNCEMETOCRT_WW_INCLUDED_

#if defined ( _MSC_VER) && (_MSC_VER >= 1020 )
    #pragma once
#endif  /* #if defined ( _MSC_VER) && (_MSC_VER >= 1020 ) */


#include <windows.h>
#include <Const_Typedefs_WW.H>

//  ----------------------------------------------------------------------------
//  The following block is adapted from CommonConstants_P6C.H, and its goal is
//  the same; define the C++ symbolic constants true and false, and the bool
//  typedef.
//  ----------------------------------------------------------------------------

#if !defined ( __cplusplus )
    #if !defined ( bool )
        typedef int                     bool ;
    #endif  /* #if !defined ( bool ) */

    #if !defined ( true )
        #define true                    1
    #endif  /* #if !defined ( true ) */

    #if !defined ( false )
        #define false                   0
    #endif  /* #if !defined ( false ) */
#endif  /* #if !defined ( __cplusplus ) */

//  ----------------------------------------------------------------------------
//  Use the following constant to specify that argument pintFrstRsrcStrID is
//  ignored because pfGetLabelsFromDLL is VER_LABELS_FROM_DLL_P6C. its value of
//  zero is an invalid resource ID.
//  ----------------------------------------------------------------------------

#define VER_USING_LABELS_IN_DLL_P6C     0

//  ----------------------------------------------------------------------------
//  Use these to simplify specifying argument pfGetLabelsFromDLL.
//  ----------------------------------------------------------------------------

#define VER_LABELS_FROM_DLL_P6C         true
#define VER_LABELS_FROM_EXE_P6C         false

//  ----------------------------------------------------------------------------
//  Use these to simplify specifying argument pfShowFullBanner.
//
//      pfShowFullBanner    Banner format string
//      ----------------    -----------------------
//      VER_FULL_BANNER     VER_DISP_MSG_TPL
//      VER_BRIEF_BANNER    ABBREV_VER_DISP_MSG_TPL
//
//  String constants VER_DISP_MSG_TPL and ABBREV_VER_DISP_MSG_TPL are defined in
//  P6VersionInfo_P6C_Pvt.H, which is private.
//  ----------------------------------------------------------------------------

#define VER_FULL_BANNER             true
#define VER_BRIEF_BANNER            false

typedef enum _VER_BANNER_DETAIL {
    VER_BANNER_VERSION        = 0x01 ,    // Version
    VER_BANNER_BOJ_TIME_LOCAL = 0x02 ,    // BOJ Time Local
    VER_BANNER_BOJ_TIME_UTC   = 0x04 ,    // BOJ Time UTC
    VER_BANNER_COPYRIGHT      = 0x08 ,    // Copyright
    VER_BANNER_FULL           = 0x0F ,    // Full
    VER_BANNER_BRIEF          = 0x07 ,    // Brief
    VER_BANNER_NO_UTC_TIME    = 0x03 ,    // No UTC Time
    VER_BANNER_NO_TIME        = 0x01 ,    // No Time
    VER_BANNER_NONE           = 0x00 ,    // None
} VER_BANNER_DETAIL ;

//  ----------------------------------------------------------------------------
//  Unless this header is included indirectly through P6VersionInfo.H,
//  LIBSPEC_VERSIONINFOLIB_P6C_API is undefined.
//  ----------------------------------------------------------------------------

#ifdef LIBSPEC_VERSIONINFOLIB_P6C_API
    #pragma message (  __FILE__  "processing AnnounceMeToCRT_WW.H, LIBSPEC_VERSIONINFOLIB_P6C_API already defined")
#else
    #pragma message (  __FILE__  "processing AnnounceMeToCRT_WW.H, defining LIBSPEC_VERSIONINFOLIB_P6C_API:")

    #ifdef __VERSIONINFOLIB_PVT_P6C__
        #define LIBSPEC_VERSIONINFOLIB_P6C_API __declspec(dllexport) __stdcall
        #pragma message (  __FILE__  "     __VERSIONINFOLIB_PVT_P6C__ is defined. Hence, LIBSPEC_VERSIONINFOLIB_P6C_API maps to __declspec(dllexport).")
    #else   /*  #ifdef __VERSIONINFOLIB_PVT_P6C__ */
        #ifdef _GETVERSININFO_STATIC_P6C
            #define LIBSPEC_VERSIONINFOLIB_P6C_API extern __stdcall
            #pragma message (  __FILE__  "     _GETVERSININFO_STATIC_P6C is defined. Hence, LIBSPEC_VERSIONINFOLIB_P6C_API maps to extern.")
        #else   /*  #ifdef __DATELIB_STATIC_P6C__ */
            #define LIBSPEC_VERSIONINFOLIB_P6C_API __declspec(dllimport) __stdcall
            #pragma message (  __FILE__  "     Neither __VERSIONINFOLIB_PVT_P6C__, nor __DATELIB_STATIC_P6C__ is defined. Hence, LIBSPEC_VERSIONINFOLIB_P6C_API maps to __declspec(dllimport).")
        #endif  /*  #ifdef _GETVERSININFO_STATIC_P6C */
    #endif  /*  #ifdef __VERSIONINFOLIB_PVT_P6C__ */
#endif  /*  #ifdef LIBSPEC_VERSIONINFOLIB_P6C_API */

//  ============================================================================
//                   F u n c t i o n   D e c l a r a t i o n s
//  ============================================================================

#if defined(__cplusplus)
extern "C"
{
#endif  /*  #if defined(__cplusplus) */

/*
    ============================================================================

    Function Name:      AnnounceMeToCRT_WW

    Synopsis:           Use my library functions to assemble and display the
                        name and version of the executing program and the start
                        time, expressed as both UTC and local time.

    Arguments:          pintFrstRsrcStrID   = Integer, containing the ID of the
                                              first resource string.

                                              If pfGetLabelsFromDLL, this
                                              parameter is ignored.

                        pfGetLabelsFromDLL  = Boolean flag, which identifies the
                                              source from which to extract the
                                              label strings.

                                              true  = Extract label strings from
                                                      the DLL from which this
                                                      function is exported, and
                                                      ignore pintFrstRsrcStrID.

                                              false = Extract label strings from
                                                      the executable program
                                                      that started the process.

                                              CommonConstants_P6C.H defines the
                                              lower case symbols true and false,
                                              neither of which is defined in the
                                              ANSI C standard, so that they can
                                              be used in C programs with any
                                              compiler.

                                              To simplify using this function,
                                              two symbolic constants are defined
                                              in AnnounceMeToCRT_WW.H.

                                              VER_LABELS_FROM_DLL_P6C   = TRUE
                                              VER_LABELS_FROM_EXE_P6C   = FALSE

                        pfShowFullBanner    = Boolean flag, which indicates
                                              whether to use the full legacy
                                              banner or the abbrieviated banner.

                                              CommonConstants_P6C.H defines the
                                              lower case symbols true and false,
                                              neither of which is defined in the
                                              ANSI C standard, so that they can
                                              be used in C programs with any
                                              compiler.

                                              To simplify using this function,
                                              two symbolic constants are defined
                                              in AnnounceMeToCRT_WW.H.

                                              VER_FULL_BANNER   = TRUE
                                              VER_BRIEF_BANNER  = FALSE

    Returns:            rdwStatusCode       = DWORD Status code, which is
                                              normally ERROR_SUCCESS.

    Remarks:            1)  To recover the program name, you can get the same
                            same banner by calling AnnounceMeToCRTPN_WW, which
                            returns a pointer to a string that contains the
                            program name in place of the exit code, which is
                            expected to be zero.

                        2)  Call AnnounceMeToCRTPN2_WW if you want more control
                            over the output. You don't have to store the program
                            name unless you need it; it's stored in a static
                            memory block that belongs to P6VersionInfo.dll.

    Remarks:            WARNING: You should terminate immediately if this
                                 function returns NULL, although you may be able
                                 to coax an error message from Windows, by
                                 calling GetLastError, EM_ShowMsgOnConsole_WW,
                                 for console applications, or
                                 EM_FormatMsgForMsgbox_WW, for Windows
                                 applications.

    References:         None.

    Calls:              ReformatSysDate_P6C   = Custom date formatting function.

                        InitVerInfo_P6C       = Initialize library code that
                                                assembles the version strins for
                                                display in the console window or
                                                a message box.

                        GetVersionInfo_P6C    = This is called, repeatedly, to
                                                add the desired version
                                                information to the display
                                                string.

                        _tprintf              = Called to display the assembled
                                                version string, and, if
                                                necessary, to display error
                                                messages.

                        GetVerInfoCleanup_P6C = Called once, just before normal
                                                exit, to free memory acquired by
                                                functions InitVerInfo_P6C and
                                                GetVersionInfo_P6C.

    ============================================================================
*/

DWORD LIBSPEC_VERSIONINFOLIB_P6C_API AnnounceMeToCRTA_WW
(
    int  pintFrstRsrcStrID ,
    BOOL pfGetLabelsFromDLL ,
    BOOL pfShowFullBanner
) ;

DWORD LIBSPEC_VERSIONINFOLIB_P6C_API AnnounceMeToCRTW_WW
(
    int  pintFrstRsrcStrID ,
    BOOL pfGetLabelsFromDLL ,
    BOOL pfShowFullBanner
) ;

#ifdef UNICODE
    #define AnnounceMeToCRT_WW  AnnounceMeToCRTW_WW
#else
    #define AnnounceMeToCRT_WW  AnnounceMeToCRTA_WW
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      AnnounceMeToCRTPN_WW

    Synopsis:           Use my library functions to assemble and display the
                        name and version of the executing program and the start
                        time, expressed as both UTC and local time, and return
                        the internal name of the program file.

    Arguments:          pintFrstRsrcStrID   = Integer, containing the ID of the
                                              first resource string.

                                              If pfGetLabelsFromDLL, this
                                              parameter is ignored.

                        pfGetLabelsFromDLL  = Boolean flag, which identifies the
                                              source from which to extract the
                                              label strings.

                                              true  = Extract label strings from
                                                      the DLL from which this
                                                      function is exported, and
                                                      ignore pintFrstRsrcStrID.

                                              false = Extract label strings from
                                                      the executable program
                                                      that started the process.

                                              CommonConstants_P6C.H defines the
                                              lower case symbols true and false,
                                              neither of which is defined in the
                                              ANSI C standard, so that they can
                                              be used in C programs with any
                                              compiler.

                                              To simplify using this function,
                                              two symbolic constants are defined
                                              in AnnounceMeToCRT_WW.H.

                                              VER_LABELS_FROM_DLL_P6C   = TRUE
                                              VER_LABELS_FROM_EXE_P6C   = FALSE

                        pfShowFullBanner    = Boolean flag, which indicates
                                              whether to use the full legacy
                                              banner or the abbrieviated banner.

                                              CommonConstants_P6C.H defines the
                                              lower case symbols true and false,
                                              neither of which is defined in the
                                              ANSI C standard, so that they can
                                              be used in C programs with any
                                              compiler.

                                              To simplify using this function,
                                              two symbolic constants are defined
                                              in AnnounceMeToCRT_WW.H.

                                              VER_FULL_BANNER   = TRUE
                                              VER_BRIEF_BANNER  = FALSE

    Returns:            The return value is a long pointer to a string that
                        contains the internal name of the program file. The
                        block points to memory allocated from the default heap,
                        which the caller should discard when it is no longer
                        needed. However, if the last use is to print the final
                        banner, discarding it is moot, because Windows it about
                        to discard the entire heap.

    Remarks:            1)  If you don't need the program name, you can get the
                            same banner by calling AnnounceMeToCRTP_WW.

                        2)  Call AnnounceMeToCRTPN2_WW if you want more control
                            over the output. You don't have to store the program
                            name unless you need it; it's stored in a static
                            memory block that belongs to P6VersionInfo.dll.

                        WARNING: You should terminate immediately if this
                                 function returns NULL, although you may be able
                                 to coax an error message from Windows, by
                                 calling GetLastError, EM_ShowMsgOnConsoleW_WW,
                                 for console applications, or
                                 EM_FormatMsgForMsgbox_WW, for Windows
                                 applications.

                                 Companion function AnnounceMeToCRT_WW displays
                                 the same message on the console, but returns a
                                 status code instead of a pointer to a string
                                 containing the internal program name.

                                 Both functions are defined in this header, and
                                 this library, and both have ANSI and Unicode
                                 versions. However, each is emitted as a
                                 separately linkable object, because a program
                                 never needs but one of them.

    ============================================================================
*/

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API AnnounceMeToCRTPNA_WW
(
    int  pintFrstRsrcStrID ,
    BOOL pfGetLabelsFromDLL ,
    BOOL pfShowFullBanner
) ;

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API AnnounceMeToCRTPNW_WW
(
    int  pintFrstRsrcStrID ,
    BOOL pfGetLabelsFromDLL ,
    BOOL pfShowFullBanner
) ;

#ifdef UNICODE
    #define AnnounceMeToCRTPN_WW    AnnounceMeToCRTPNW_WW
#else
    #define AnnounceMeToCRTPN_WW    AnnounceMeToCRTPNA_WW
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      AnnounceMeToCRTPN2_WW

    Synopsis:           Use my library functions to assemble and display some or
                        all of the following items, and return the internal name
                        of the program file.

                        1) Name and version of the executing program
                        2) Copyright notice
                        3) Program startup time, with optional UTC equivalent

    Arguments:          pintFrstRsrcStrID   = Integer, containing the ID of the
                                              first resource string.

                                              If pfGetLabelsFromDLL, this
                                              parameter is ignored.

                        pfGetLabelsFromDLL  = Boolean flag, which identifies the
                                              source from which to extract the
                                              label strings.

                                              true  = Extract label strings from
                                                      the DLL from which this
                                                      function is exported, and
                                                      ignore pintFrstRsrcStrID.

                                              false = Extract label strings from
                                                      the executable program
                                                      that started the process.

                                              CommonConstants_P6C.H defines the
                                              lower case symbols true and false,
                                              neither of which is defined in the
                                              ANSI C standard, so that they can
                                              be used in C programs with any
                                              compiler.

                                              To simplify using this function,
                                              two symbolic constants are defined
                                              in AnnounceMeToCRT_WW.H

                                              VER_LABELS_FROM_DLL_P6C   = TRUE
                                              VER_LABELS_FROM_EXE_P6C   = FALSE

                        penmBannerDetail    = Use this enumeration to specify
                                              which of the items listed in the
                                              synopsis to display.

    Returns:            The return value is a long pointer to a string that
                        contains the internal name of the program file. The
                        block points to memory allocated from the default heap,
                        which the caller should discard when it is no longer
                        needed. However, if the last use is to print the final
                        banner, discarding it is moot, because Windows it about
                        to discard the entire heap.

    Remarks:            1)  If you don't need the program name, you can get the
                            same banner, although it offers fewer choices over
                            what is included in the outupt, by calling
                            AnnounceMeToCRTP_WW.

                        2)  Alternatively, you can call this routine, but skip
                            saving the return value, although you should test it
                            and abort if it is NULL. Testing the value returned
                            by a function is easily accomplished in any language
                            with which this library is likely to be employed.

                        WARNING: You should terminate immediately if this
                                 function returns NULL, although you may be able
                                 to coax an error message from Windows, by
                                 calling GetLastError, EM_ShowMsgOnConsole_WW,
                                 for console applications, or
                                 EM_FormatMsgForMsgbox_WW, for Windows
                                 applications.

    References:         None.

    Calls:              ReformatSysDate_P6C   = Custom date formatting function.

                        InitVerInfo_P6C       = Initialize library code that
                                                assembles the version strins for
                                                display in the console window or
                                                a message box.

                        GetVersionInfo_P6C    = This is called, repeatedly, to
                                                add the desired version
                                                information to the display
                                                string.

                        _tprintf              = Called to display the assembled
                                                version string, and, if
                                                necessary, to display error
                                                messages.

                        GetVerInfoCleanup_P6C = Called once, just before normal
                                                exit, to free memory acquired by
                                                functions InitVerInfo_P6C and
                                                GetVersionInfo_P6C.

    ============================================================================
*/

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API AnnounceMeToCRTPN2A_WW
(
    int               pintFrstRsrcStrID ,
    BOOL              pfGetLabelsFromDLL ,
    VER_BANNER_DETAIL penmBannerDetail
) ;

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API AnnounceMeToCRTPN2W_WW
(
    int               pintFrstRsrcStrID ,
    BOOL              pfGetLabelsFromDLL ,
    VER_BANNER_DETAIL penmBannerDetail
) ;

#ifdef UNICODE
    #define AnnounceMeToCRTPN2_WW  AnnounceMeToCRTPN2W_WW
#else
    #define AnnounceMeToCRTPN2_WW  AnnounceMeToCRTPN2A_WW
#endif  /*  #ifdef UNICODE */

// Close the block of code that has "C" linkage.
#if defined(__cplusplus)
}
#endif  /*  #if defined(__cplusplus) */
#endif  /* _ANNOUNCEMETOCRT_WW_INCLUDED_ */