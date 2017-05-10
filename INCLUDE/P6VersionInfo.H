/*
    ============================================================================

    Module Name:        P6VersionInfo32.H

    Library:            P6VersionInfo32.dll (Use P6VersionInfo32.lib.) (dynamic)
                        P6CLib1.lib (static, deprecated)

    Synopsis:           Declare functions used to retrieve version info strings,
                        and related constants and enumerations.

    Dependencies:       Code that calls any of these routines depends indirectly
                        upon Version.dll and Shlwapi.dll. Both are available on
                        Windows 2000 and later, which is the oldest version of
                        Windows with which I can guarantee this library to work.

    Remarks:            This is the upgrade of library GetVersionInfo_P6C and
						its header, to support a breaking change in the calling
						convention used by all of its exported routines, as well
						as a new dependency on WWKernelLibWrapper.

						Due to their length and the diversity of subjects, the
						following comments are divided into sections, each of
						which is preceded by a heading that is formatted like
						the one immediately following this paragraph.

	                    ---------------------
	                    PRAGMA ONCE DIRECTIVE
	                    ---------------------

                        Placement of the #pragma once directive following the
                        #ifndef _GETVERSIONINFO_P6C, #define _GETVERSIONINFO_P6C
                        pair mirrors its placement in windows.h, which works as
                        expected every time.

                        Beginning with version 1.23 of the modules associated
                        with this header, the redundant documentation in the C
                        source files is being removed, to further simplify their
                        maintenance burden.

						----------------------------------
						STATIC CONST TCHAR STRING LITERALS
						----------------------------------

                        Function GetVersionInfoW_P6C uses several constant
                        string literals, which I saved as static const TCHAR
                        arrays, and placed at the beginning of the working
                        storage for this module.

                        This adaptation eliminated all of the cast warnings "the
                        right way," by employing the generic text macro _T(),
                        the TCHAR generic character typedef, and the const and
                        static storage class modifiers, while retaining 
                        consistency between Unicode and ANSI implementations.

                        The critical factor, required to make this code work, is
                        that it must be compiled with preprocessor variables
                        _UNICODE and UNICODE defined. The former makes the
                        generic text mappings behave as documented in reference
                        2, while the latter makes the Win32 API symbolic mapping
                        behave as documented and intended.

                        Until today, the need for the _UNICODE preprocessor
                        variable had eluded me.

                        Though this implementation is unnecessary for the ANSI
                        version, I used it, anyway, to keep the two versions as
                        consistent as possible.

						-------------------------------------
						INCLUSION OF STANDARD WINDOWS HEADERS
						-------------------------------------

                        By way of CommonConstants_P6C.H, this header pulls the
                        following standard Windows headers into your compilation
                        unit.

                        windows.h   - Windows constants and preprocessor
                                      variables, subject to WIN32_LEAN_AND_MEAN

                        malloc.h    - Required by macro ZeroFillBuffer

                        TCHAR.H     - Generic text mappings

                        This arrangement is required, because these must be
                        included in a specific order, and none may be included
                        at all until specific preprocessor symbols are defined.

						---------------------------------
						LOADSTRING AND INVALID STRING IDS
						---------------------------------

                        A return value of zero from LoadString means only that
                        no string was returned, or that the returned string is
                        empty. This means that an invalid string ID won't get
                        reported. Hence, these routines return a custom result
                        code.

                        Please see Reference 4.

    References:         1)  "UNICODE conversions? : c++,"
                            http://objectmix.com/c/311310-unicode-conversions.html

                        2)  "Generic-Text Mappings in TCHAR.H,"
                            http://msdn.microsoft.com/en-us/library/aa269775(VS.60).aspx

                        3)  "What Static Const Variable Do,"
                            http://www.cplusplus.com/forum/beginner/2912/

                        4)  "LoadString Function," Windows User Interface, MSDN.
                            http://msdn.microsoft.com/en-us/library/ms647486(VS.85).aspx
                            Pay close attention to the first community comment,
                            titled, "Return value 0 or -1."

    Author:             David A. Gray, of Simple Soft Services, Inc.,
                        d/b/a WizardWrx, Irving, Texas, USA

    Date Written:       Friday, 08 July 2005 - Sunday, 10 July 2005

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

    Date       Version Author Synopsis
    ---------- ------- ------ --------------------------------------------------
    2005/07/10         DAG    This is the first working version.

    2005/11/06         DAG    Add function to identify first resource string ID.

    2005/12/07         DAG    Change GetVerInfo_P6C to GetVersionInfo_P6C.

    2005/12/08         DAG    1) Eliminate custom error reporting code in favor
                                 of standard Windows API function SetLastError.

                              2) Eliminate _stdcall function signatures, which
                                 are identical to APIENTRY. Specification of
                                 static and dynamic libraries in the link step
                                 is enough to get the right code included. This
                                 change also eliminates the need for directive
                                 _GETVERSIONINFO_STATIC_P6C.

    2006/04/02         DAG    1) Change test for CUSTOMER_FLAG to conform to the
                                 test used in CommonConstants_P6C.H, which
                                 contains the official definition, to avoid a
                                 macro redefinition warning.

                              2) Wrap parentheses around the error code
                                 definitions to ensure that they work in all
                                 expressions.

    2008/06/18         DAG    Define preprocessor variable _GETVERSIONINFO_P6C,
                              to prevent accidental redefinition.

    2009/12/04         DAG    1) Simplify formatting of internal documentation
                                 to decrease the maintenance burden.

                              2) Fix a self-limiting memory leak in function
                                 GetVersionInfo_P6C(), which also causes some
                                 code to be executed on every pass, rather
                                 than once per process as was intended.

                                 Since no process makes more than a handful of
                                 calls to GetVersionInfoA_P6C, the leak is never
                                 greater than a few hundred bytes - enough to
                                 hold a copy of the fully qualified name of the
                                 program file for each call. Typically, this
                                 routine is called no more than 12 times, once
                                 per version string.

                              3) Add the following new functions, to expose data
                                 gathered for internal use, and previously
                                 discarded, which the calling application can
                                 use to eliminate API calls to get it again.

                                    GetProgramFQFN_P6C
                                    GetProgramUQFN_P6C
                                    GetProgramDir_P6C

                              4) Remove definition of CUSTOMER_FLAG, which is
                                 already defined in CommonConstants_P6C.H, which
                                 I just added, in case this header is included
                                 in a source module that doesn't already include
                                 it.

                              5) Substitute externally linked handle m_hProcHeap
                                 for locally defined md_hProcHeap, so that most,
                                 if not all, code that uses the process heap can
                                 share a single copy of the handle.

                              6) Move symbolic constant VER_END_OF_ITEMS_P6C to
                                 the public section.

    2010/03/08         DAG    Change GetProgramUQFN_P6C and GetProgramFQFN_P6C,
                              so that they return usable strings, whether or not
                              GetVersionInfo_P6C has yet been called.

    2010/04/10         DAG    Add GetLastError and appropriate tests following a
                              LoadString failure.

                              The remedy for this is our own status code,
                              VER_RESOURCE_STRING_NOT_FOUND_P6C, because
                              LoadString fails silently if the specified string
                              is missing.

                              Please see LOADSTRING AND INVALID STRING IDS, in
                              the Remarks section, above.

    2010/04/25         DAG    Reinstate direct inclusion of windows.h, since, as
                              of this date, CommonConstants_P6C.H works without
                              it.

    2010/06/04         DAG    Move the #pragma once preprocessor directive
                              outside the scope of the preprocessor variable
                              which performs the same function for other C
                              compilers.

    2010/08/23         DAG    Amend the signature for GetNumericFileVersion_P6C,
                              and add its companion, GetNumericProdVersion_P6C.

    2010/09/26         DAG    Straighten out the tangled names of the following
                              new functions.

                                    GetDLLModuleName_WW    Symbolic name.
                                    GetModuleFQFNA_WW   ANSI implementation.
                                    GetModuleFQFNW_WW   Unicode implementation.

    2011/08/28 1.1.1.0 DAG    Fix memory leaks in function GetVersionInfo_P6C,
                              which has its own revision history, which I have
                              chosen to keep for now, and unwind the BakeString
                              macros embedded in the two functions that return
                              numeric version information.

    2011/09/04 1,1,2,1 DAG    This version upgrades internal documentation,
                              copyright notices, etc.

                              However, there are substantial structural changes
                              in the test harness, which wasn't differentiating
                              ANSI test from Unicode tests correctly.

    2011/10/30 1,1,2,1 DAG    (Version number not incremented)

                              Add symbolic constant IDS_COMMENTS_IN_DLL, for use
                              by calling programs that use the string reources
                              in the DLL as labels.

                              Replace CUSTOMER_FLAG with APPLICATION_ERROR_MASK,
                              defined in WinNT.h.

                              Since neither change affects the generated code, I
                              forgo building a new version of the library.
                              Hence, the reuse of the version number.

    2011/11/06 1,3,4,1 DAG    Change interpretation of a NULL third argument to
                              function GetVersionInfo_P6C. See function
                              documentation below.

    2012/02/05 1,4,5,1 DAG    1) Implement the LIBSPEC_VERSIONINFOLIB_P6C_API
                                 CPP macro, which generates more efficient
                                 dynamic link libraries, by eliminating a short
                                 jump from the Import Address Table when a
                                 routine is called.

                              2) Move the numeric version routines to the static
                                 link library, to simplify implementation of a
                                 private header file.

                              3) Move private preprocessor variable definitions
                                 and function declarations into private header
                                 P6VersionInfo_P6C_Pvt.H,  which lives in the
                                 source code tree of the static link library
                                 that houses the source code of everything but
                                 DLLMain.

                              4) Make GetDLLModuleName_WW public.

    2012/05/18 1,5,6,1 DAG    Item 1 is implemented in this header. Items 2 and
                              3 are implemented in P6VersionInfo_P6C_Pvt.H, a
                              private header. Item 4 is implemented in routines
                              AnnounceMeToCRT_WW and AnnounceMeToCRTPN_WW, which
                              are defined in inline AnnounceMeToCRTP.INL and
                              AnnounceMeToCRTPN.INL, respectively.

                              1) Generate code that can be statically linked
                                 when _GETVERSININFO_STATIC_P6C is defined.

                              2) Shorten string VER_GETVERSIONINFO_ERRMSG, and
                                 make it compatible with EM_ShowMsgOnConsole_WW.

                              3) Define a new string, ABBREV_VER_DISP_MSG_TPL,
                                 which is similar to VER_DISP_MSG_TPL, but has
                                 one fewer lines and string substitution tokens.

                              4) Change functions AnnounceMeToCRT_WW and
                                 AnnounceMeToCRTPN_WW so that their first
                                 argument, pintFrstRsrcStrID, is ignored
                                 when pfGetLabelsFromDLL is TRUE, by taking
                                 advantage of the fact that the DLL knows the
                                 IDs of its own resource strings.

    2012/05/28 1,5,7,0 DAG    Fix coding errors in the ANSI and Unicode
                              implementations of GetProgramDir_P6C, which are
                              defined in source files GetVersionInfoA_P6C.C and
                              GetVersionInfoW_P6C.C, respectively. To expedite
                              matters, move the body of the ANSI implementation
                              into inline include file, GetVersionInfo_P6C.INL,
                              and adjust it as needed to run in ANSI and Unicode
                              contexts.

                              Affected source files: GetVersionInfoA_P6C.C
                                                     GetVersionInfoW_P6C.C
                                                     GetVersionInfo_P6C.INL (new)

    2012/06/11 1,6,9,0 DAG    Add GetFileVersionInfo_P6C, which has ANSI and
                              Unicode versions, and GetFileVersionInfo_VB_P6C, a
                              Visual Basic and Visual Basic for Applications
                              wrapper.

    2012/06/13 1,6,9,1 DAG    Insert a carriage return in front of every bare
                              newline character, so that Windows programs see
                              print files as proper DOS/Windows text files. This
                              change affects static strings VER_DISP_MSG_TPL and
                              ABBREV_VER_DISP_MSG_TPL.

                              Only the private header, P6VersionInfo_P6C_Pvt.H,
                              is changed.

    2012/06/18 1,6,9,2 DAG    Work around an uninitialized private heap pointer,
                              found during testing of GetFileVersionInfo_VB_P6C.
                              The error is in GetFileVersionInfo_P6C, and its
                              cause is a failure to call the initialization and
                              cleanup routines that maintain the private heap
                              used by most of the routines in this library.

                              Though found while testing a Visual Basic wrapper,
                              this error could arise at any time, depending on
                              the order of function calls into the DLL.

    2012/06/19 1,6,9,3 DAG    Unroll GetFileVersionInfo_P6C, so that its errors
                              can be trapped. As currently configured, when an
                              error occurs, CopyStringToNewBuf_P6C overwrites it
                              with its own status code. CopyStringToNewBuf_P6C
                              should also be fixed, but I'll get to that later.

    2012/06/22 1,7,0,0 DAG    Using the new VER_LANG_NEUTRAL_CODE_WW constant,
                              defined in P6VersionInfo_P6C_Pvt.H, as are the
                              other two symbols used in the language table
                              parser, add two new capabilities.

                              1) Extract language neutral version strings from a
                                 Microsoft .NET assembly.

                              2) Establish the following hierarchy for selecting
                                 a language.

                                 a) The UI language

                                 b) EN-US

                                 c) Invariant (language neutral)

                              Due to this additional complexity, language ID
                              testing gets its own function, UseThisLang_P6C.
                              Since these tests focus entirely on a pair of WORD
                              values, there is but one version, which is defined
                              in GetVersionInfoA_P6C.C, as a private routine.

                              As of this version, the routines defined in source
                              files GetVersionInfoA_P6C and GetVersionInfoW_P6C
                              that have ANSI and Unicode implementations share a
                              set of inline include files that contain the code,
                              so that changes made to fix or improve one affect
                              both.

    2013/03/09 1,7,0,3 DAG    Correct an internal processing error that causes
                              the Windows ANSI code page (0x04E4) to be ignored.

                              The changes in this version are externally
                              transparent. No code that references
                              P6VersionInfo.dll (P6VersionInfo.lib) needs
                              recompilation, although doing so is harmless.

    2013/06/20 1,8,0,0 DAG    Eliminate CommonConstants_P6C.H in favor of the
                              much more focused Const_Typedefs_WW.H.

    2014/08/21 1,9,0,0 DAG    Add a new function, AnnounceMeToCRTPN2_WW, which
                              is a superset of AnnounceMeToCRTPN_WW that offers
                              greater control over the output. The declaration
                              is in subsidiary include file AnnounceMeToCRT_WW.H.

    2015/01/24 1,9,0,1 DAG    Map the following symbolic constants to WinNT.H
                              macros, so that both are properly documented.

                                --------------------------------------------
                                Constant                    WinNT.h Mapping
                                ------------------------    ----------------
                                LCID_INVARIANT              LOCALE_INVARIANT
                                VER_LANG_NEUTRAL_CODE_WW    LOCALE_NEUTRAL
                                --------------------------------------------

                              LCID_INVARIANT is new today, and its creation was
                              behind the review and updating of this header.

                              Wrap all of the language and code page macros in
                              guard blocks, and copy the whole set into
                              CommonConstants_P6C.H.

                              Other than these changes to the header, the only
                              change to the library is removal of the redundant
                              version statement from the .DEF file.

    2016/05/21         DAG	  Correct typographical errors discovered during a 
                              code review. Since the changes are confined to
							  comments, nothing needs to be rebuilt.

    2017/01/14 1,9,0,2 DAG    1) Upgrade to Visual Studio 2013, building against
	                             its version of the CRT library, confining code
								 changes to the absolute minimum required for a 
								 successful upgrade.

						      2) Replace the original free software license, 
							     which was never used to cover a source code
								 distribution, with a 3-clause BSD license.

    2017/01/15 2,0,0,1 DAG    Rename the underlying library, from P6VersionInfo
							  to P6VersionInfo32, and synchronize the name of
							  its library header, so that I can make a wholesale
							  calling convention change, from __cdecl, which I
							  didn't fully understand in 2005, to __stdcall, a
							  slightly more efficient calling convention that
							  happens also to decrease code bloat.

							  Replace unguarded calls to HeapAlloc and HeapFree
							  with custom wrappers that implement Structured
							  Exception Handling.

    2017/02/14 2,0,0,2 DAG    Move the routines that get the program file name
	                          and its directory to WWKernelLibeWrapper32.
    ============================================================================
*/


#ifndef _GETVERSIONINFO_P6C_INCLUDED
#define _GETVERSIONINFO_P6C_INCLUDED

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /*  #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */


#include <windows.h>

//  ----------------------------------------------------------------------------
//  Since oleauto.h defines the BSTR type, it must be included. (If a previous
//  header already pulled it into the source stream, the compiler ignores the
//  redundant inclusion.)
//  ----------------------------------------------------------------------------

#include <oleauto.h>

//  ----------------------------------------------------------------------------
//  Define a few extra CONST typedefs.
//  ----------------------------------------------------------------------------

#include <Const_Typedefs_WW.H>

//  ----------------------------------------------------------------------------
//  2011/08/20 - See item 2 under Remarks, in DateLib_P6C.H, and references 2
//               and 3. The third one provided the final solution.
//
//               IMPORTANT: Leave the pragma messages; they will be useful in 
//                          the event that you have difficulties with linkage.
//  ----------------------------------------------------------------------------

#pragma message ( __FILE__ " defining LIBSPEC_VERSIONINFOLIB_P6C_API:" )

#ifdef __VERSIONINFOLIB_PVT_P6C__
    #define LIBSPEC_VERSIONINFOLIB_P6C_API __declspec(dllexport) __stdcall
    #pragma message (  __FILE__  "     __VERSIONINFOLIB_PVT_P6C__ is defined. Hence, LIBSPEC_VERSIONINFOLIB_P6C_API maps to __declspec(dllexport)." )
#else   /*  #ifdef __VERSIONINFOLIB_PVT_P6C__ */
    #ifdef _GETVERSININFO_STATIC_P6C
        #define LIBSPEC_VERSIONINFOLIB_P6C_API extern __stdcall
        #pragma message (  __FILE__  "     _GETVERSININFO_STATIC_P6C is defined. Hence, LIBSPEC_VERSIONINFOLIB_P6C_API maps to extern." )
    #else   /*  #ifdef __DATELIB_STATIC_P6C__ */
        #define LIBSPEC_VERSIONINFOLIB_P6C_API __declspec(dllimport) __stdcall
        #pragma message (  __FILE__  "     Neither __VERSIONINFOLIB_PVT_P6C__, nor __DATELIB_STATIC_P6C__ is defined. Hence, LIBSPEC_VERSIONINFOLIB_P6C_API maps to __declspec(dllimport)." )
    #endif  /*  #ifdef _GETVERSININFO_STATIC_P6C */
#endif  /*  #ifdef __VERSIONINFOLIB_PVT_P6C__ */

#define LIBSPEC_VERSIONINFOLIB_VBA_P6C_API  __stdcall

//  ----------------------------------------------------------------------------
//  Declare several newer functions that use these primitives to further
//  simplify access to the version resources in EXE, DLL, and other PE files.
//  ----------------------------------------------------------------------------

#include <AnnounceMeToCRT_WW.H>

//  ----------------------------------------------------------------------------
//  Define error code constants.
//  ----------------------------------------------------------------------------

#define VER_SUCCESS_P6C                     ERROR_SUCCESS           // Defined in WinError.H, which is pulled into the source code by Windows.H.
#define VER_INVALID_RESOURCE_ID_P6C         (  1 | APPLICATION_ERROR_MASK )
#define VER_HINSTANCE_IS_NULL_P6C           (  2 | APPLICATION_ERROR_MASK )
#define VER_HEAP_CREATE_FAILED_P6C          (  3 | APPLICATION_ERROR_MASK )
#define VER_GET_PROC_HEAP_FAILED_P6C        (  4 | APPLICATION_ERROR_MASK )
#define VER_HEAP_ALLOC_FAILED_P6C           (  5 | APPLICATION_ERROR_MASK )
#define VER_HEAP_REALLOC_FAILED_P6C         (  6 | APPLICATION_ERROR_MASK )
#define VER_INVALID_PENMSTRINGNAME_P6C      (  7 | APPLICATION_ERROR_MASK )
#define VER_NO_ACCEPTABLE_LANGUAGE_P6C      (  8 | APPLICATION_ERROR_MASK )
#define VER_LSTRCPY_ERROR_P6C               (  9 | APPLICATION_ERROR_MASK )
#define VER_NO_INTERNAL_NAME_P6C            ( 10 | APPLICATION_ERROR_MASK )
#define VER_RESOURCE_STRING_NOT_FOUND_P6C   ( 11 | APPLICATION_ERROR_MASK )
#define VER_TOO_MANY_LANGINFO_RECORDS_P6C   ( 12 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  Define module level constants that should be public.
//  ----------------------------------------------------------------------------

#define VER_END_OF_ITEMS_P6C                MINUS_ONE_WW

//  ----------------------------------------------------------------------------
//  The following symbolic constant corresponds to the ID of the first string
//  resource defined in P6VersionInfo.DLL. See IDS_COMMENTS, in Visual studio
//  generated include file C:\Documents and Settings\David\My Documents\
//  Programming\Visual Studio 6\DLL\P6VersionInfo\resource.h.
//  ----------------------------------------------------------------------------

#define IDS_COMMENTS_IN_DLL                 3

//  ----------------------------------------------------------------------------
//  String and version resources are always stored as Unicode little-endian
//  text. For backward compatibility, Microsoft assigned a corresponding code
//  page, along with one for its Alpha Power PC cousin, Unicode big-endian text.
//
//  Although version resources shouldn't need both, I defined constants for both
//  code pages. Though these constants were intended for internal use, I decided
//  that it would be a good idea to formally document them in a public header.
//
//  While I was at it, I defined the ANSI Western European (Latin-1) code page,
//  too. However, beware: GetACP means business; on a Western European Windows
//  installation, it returns CP_ANSI_LATIN1_WW, 1252, and code accordingly.
//
//  References:         1)  "Code Pages and Unicode Strings,"
//                          http://msdn.microsoft.com/en-us/library/windows/desktop/aa378923(v=vs.85).aspx
//
//                      2)  "Code Page Identifiers"
//                          http://msdn.microsoft.com/en-us/library/dd317756(VS.85).aspx
//
//                      3)  "Microsoft code page numbers for various other character encodings," in "Code page" article on Wikipedia
//                          http://en.wikipedia.org/wiki/Code_page
//
//                      4)  "Locale IDs Assigned by Microsoft"
//                          http://msdn.microsoft.com/en-us/goglobal/bb964664
//
//                      5)  "Locales in Windows XP,"
//                          https://msdn.microsoft.com/en-us/goglobal/bb964663#E4
//  ----------------------------------------------------------------------------

#ifndef CP_UTF_16_LITTLE_ENDIAN_WW
    #define CP_UTF_16_LITTLE_ENDIAN_WW      0x04b0              // 1200 = UTF-16LE - Microsoft assigns this code page to all Unicode language resources. (See references 1 and 2.
#endif  /* #ifndef CP_UTF_16_LITTLE_ENDIAN_WW */

#ifndef CP_UTF_16_BIG_ENDIAN_WW
    #define CP_UTF_16_BIG_ENDIAN_WW         0x04B1              // 1201 = UTF-16BE - Microsoft reserved this for the big-endian format of UTF-16, and, presumabily, for the PowerPC. (See references 1 and 2.
#endif  /* #ifndef CP_UTF_16_BIG_ENDIAN_WW */

#ifndef CP_ANSI_LATIN1_WW
    #define CP_ANSI_LATIN1_WW               0x04E4              // 1252 = West European Latin (Latin-1) - Defined onoy in a couple of obscure headers, e. g., mimeole.h
#endif  /* #ifndef CP_ANSI_LATIN1_WW */

//  ----------------------------------------------------------------------------
//  LOCALE_NEUTRAL is defined in WinNt.h, where it expands function-style macro
//  MAKELCID with the following arguments:
//
//      LANG_NEUTRAL    via nested expansion of MAKELANGID
//      SUBLANG_NEUTRAL via nested expansion of MAKELANGID
//      SORT_DEFAULT
//
//  This works out to 0x0000 = 0.
//  ----------------------------------------------------------------------------

#ifndef VER_LANG_NEUTRAL_CODE_WW
    #define VER_LANG_NEUTRAL_CODE_WW        LOCALE_NEUTRAL
#endif /* #ifndef VER_LANG_NEUTRAL_CODE_WW */

//  ----------------------------------------------------------------------------
//  Locale ID 0x0409 = 1033 = English - United States is everywhere EXCEPT in 
//  the Platform SDK header files. (Ser reference 4.)
//  ----------------------------------------------------------------------------

#ifndef VER_LOCALE_ID_ENGLISH_USA_WW
    #define VER_LOCALE_ID_ENGLISH_USA_WW    0x0409
#endif  /* #ifndef VER_LOCALE_ID_ENGLISH_USA_WW */

//  ----------------------------------------------------------------------------
//  1142 = Latin - Assigned by Microsoft, but currently unused. See reference 4.
//
//  Although they reserved a locale ID for Latin, Microsoft hasn't used it, and
//  they probably won't. Nevertheless, I decided that it would be fun to have it
//  documented with the other locale IDs and such that I really use.
//  ----------------------------------------------------------------------------

#ifndef LCID_LATIN_ASSIGNED_UNUSED_WW
    #define LCID_LATIN_ASSIGNED_UNUSED_WW   0x0476
#endif  /* LCID_LATIN_ASSIGNED_UNUSED_WW */

//  ----------------------------------------------------------------------------
//  The Invariant Locale (Locale ID = 0x007f) is a locale that can be used by
//  applications when a consistent and locale–independent result is required.
//  The invariant locale can be used, for example, when comparing character
//  strings using the CompareString() API and a consistent result regardless of
//  the User Locale is expected. LOCALE_INVARIANT is defined in WinNT.h as a 
//  function style macro. See Reference 5 and WinNT.h in the Platform SDK.
//
//  This works out to 0x007f = 127.
//  ----------------------------------------------------------------------------

#ifndef LCID_INVARIANT
    #define LCID_INVARIANT                  LOCALE_INVARIANT
#endif  /* LCID_INVARIANT */

//  ----------------------------------------------------------------------------
//  Declare other module level constants that can be kept private.
//  ----------------------------------------------------------------------------

#ifdef _UNICODE
    #pragma message (  __FILE__  "    CPP variable _UNICODE is defined." )
#else
    #pragma message (  __FILE__  "    CPP variable _UNICODE is UNdefined." )
#endif  /*  #ifdef _UNICODE */

#ifdef UNICODE
    #pragma message (  __FILE__  "    CPP variable UNICODE is defined." )
#else
    #pragma message (  __FILE__  "    CPP variable UNICODE is UNdefined." )
#endif  /*  #ifdef UNICODE */

//  ----------------------------------------------------------------------------
//  The following enumerator was initially declared in P6CStringLib1.H, for use
//  as the pAddOrRemove argument to function PathStringFixup_P6C, exported by
//  P6CStringLib1.dll. Since GetProgramDir_P6C calls the same routines in the
//  Lightweight Shell API, for the same purpose, the same enumeration is defined
//  in this header, unless P6CStringLib1.H entered the source code stream ahead
//  of it.
//  ----------------------------------------------------------------------------

#ifndef __PATHSTRINGFIXUP_HOW_P6C_DEFINED
#define __PATHSTRINGFIXUP_HOW_P6C_DEFINED
typedef enum _tagPATHSTRINGFIXUP_HOW_P6C
{
    PATHSTRINGFIXUP_INVALID ,           // 0
    PATHSTRINGFIXUP_ADD_P6C ,           // 1
    PATHSTRINGFIXUP_REMOVE_P6C ,        // 2
}   PATHSTRINGFIXUP_HOW_P6C ;
#endif  /*  #ifndef __PATHSTRINGFIXUP_HOW_P6C_DEFINED */

//  ----------------------------------------------------------------------------
//  The following enumerator maps items of version information to module
//  resource strings that identify them in the version information data block.
//
//  Functions GetFileVersionInfo_P6C and GetFileVersionInfo_VB_P6C cast their
//  penmStringName argument to this type.
//
//  Although GetVersionInfo_P6C casts its penmStringName argument to DWORD, you
//  may pass a member of this enumeration without a peep from the compiler. This
//  works because the underlying type of an enumeration is unsigned integer. In
//  a 32 bit machine, an unsigned integer is equivalent to a DWORD. Hence, all
//  three types are interchangeable.
//  ----------------------------------------------------------------------------

typedef enum _VER_STRING_NAME_P6C
{
    VER_COMMENTS ,                      //  0
    VER_COMPANYNAME ,                   //  1
    VER_FILEDESCRIPTION ,               //  2
    VER_FILEVERSION ,                   //  3
    VER_INTERNALNAME ,                  //  4
    VER_LEGALCOPYRIGHT ,                //  5
    VER_LEGALTRADEMARKS ,               //  6
    VER_ORIGINALFILENAME ,              //  7
    VER_PRIVATEBUILD ,                  //  8
    VER_PRODUCTNAME ,                   //  9
    VER_PRODUCTVERSION ,                // 10
    VER_SPECIALBUILD                    // 11
} VER_STRING_NAME_P6C ;

#pragma pack(push,1)
typedef struct _NUMERIC_VERSION_INFO_WW
{
    WORD    Major ;
    WORD    Minor ;
    WORD    Build ;
    WORD    Revision ;
    __int64 uint64Version ;
}   NUMERIC_VERSION_INFO_WW, FAR *LPNUMERIC_VERSION_INFO_WW ;
#pragma pack(pop)


#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */

/*
    ============================================================================

    Function Name:      GetNumericFileVersion_P6C

    Synopsis:           Return the file version from the 64 bit integer which was
                        intended to be mathematically compared to other version
                        numbers.

    Arguments:          plpNumericVersionInfo   = Long pointer to a
                                                  NUMERIC_VERSION_INFO_WW data
                                                  structure, which, on return,
                                                  is filled with version numbers
                                                  as outlined in the remarks.

                        plpszFileName           = Pointer to the name of the
                                                  file from which to get version
                                                  information. If NULL, the file
                                                  version of the program from
                                                  which the current process was
                                                  created is returned.

                        phInstVersion           = Instance handle (HINSTANCE) of
                                                  a module for which to retrieve
                                                  the version. If NULL, the file
                                                  version of the program from
                                                  which the current process was
                                                  created is returned.

    Returns:            If the function succeeds, the return value is TRUE, and
                        the NUMERIC_VERSION_INFO_WW members are populated.

                        Otherwise, the return value is FALSE, and you may call
                        GetLastError for additional information.

    Remarks             1)  This function is independent of the others declared
                            in this header, although, if possible, it takes
                            advantage of their shared data to expedite its work.

                        2)  This function returns the four numerical values that
                            comprise a standard Product Version string. These
                            are commonly identified as follows.

                                Major
                                Minor
                                Build
                                Revision

                            The rules governing assignment of these values vary
                            by compiler and platform. Generally, the first three
                            are of the most interest, since the fourth,
                            Revision, is often a time stamp, especially in the
                            case of Microsoft .NET assemblies.

                        3)  Internally, the four version numbers are packed into
                            four unsigned WORD (16 bit integer) values, which
                            accounts for the upper limit of 65535 (2**16 - 1) on
                            the value of a version.

                        4)  This routine unpacks the four numbers, and returns
                            them as four appropriately named members of a
                            NUMERIC_VERSION_INFO_WW data structure. To simplify
                            access from other programming languages, the members
                            are packed as tightly as possible.

    References:         None

    Date Written:       Thursday, 25 February 2010 and Sunday, 22 August 2010.
                        Documentation was completed just after Midnight on
                        Monday, 23 August 2010. Hence, the revision date is
                        actually 23 August 2010.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2010/08/23 DAG First fully functioning version.
    ============================================================================
*/

BOOL LIBSPEC_VERSIONINFOLIB_P6C_API GetNumericFileVersionA_P6C
(
    LPNUMERIC_VERSION_INFO_WW plpNumericVersionInfo ,
    LPCTSTR                   plpszFileName ,
    HINSTANCE                 phInstVersion
) ;

BOOL LIBSPEC_VERSIONINFOLIB_P6C_API GetNumericFileVersionW_P6C
(
    LPNUMERIC_VERSION_INFO_WW plpNumericVersionInfo ,
    LPCTSTR                   plpszFileName ,
    HINSTANCE                 phInstVersion
) ;

#ifdef UNICODE
    #define GetNumericFileVersion_P6C   GetNumericFileVersionW_P6C
#else
    #define GetNumericFileVersion_P6C   GetNumericFileVersionA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      GetNumericProdVersion_P6C

    Synopsis:           Return the product version from the 64 bit integer which
                        was intended to be mathematically compared to other
                        version numbers.

    Arguments:          plpNumericVersionInfo   = Long pointer to a
                                                  NUMERIC_VERSION_INFO_WW data
                                                  structure, which, on return,
                                                  is filled with version numbers
                                                  as outlined in the remarks.

                        plpszFileName           = Pointer to the name of the
                                                  file from which to get version
                                                  information. If NULL, the file
                                                  version of the program from
                                                  which the current process was
                                                  created is returned.

                        phInstVersion           = Instance handle (HINSTANCE) of
                                                  a module for which to retrieve
                                                  the version. If NULL, the file
                                                  version of the program from
                                                  which the current process was
                                                  created is returned.

    Returns:            If the function succeeds, the return value is TRUE, and
                        the NUMERIC_VERSION_INFO_WW members are populated.

                        Otherwise, the return value is FALSE, and you may call
                        GetLastError for additional information.

    Remarks             1)  This function is independent of the others declared
                            in this header, although, if possible, it takes
                            advantage of their shared data to expedite its work.

                        2)  This function returns the four numerical values that
                            comprise a standard Product Version string. These
                            are commonly identified as follows.

                                Major
                                Minor
                                Build
                                Revision

                            The rules governing assignment of these values vary
                            by compiler and platform. Generally, the first three
                            are of the most interest, since the fourth,
                            Revision, is often a time stamp, especially in the
                            case of Microsoft .NET assemblies.

                        3)  Internally, the four version numbers are packed into
                            four unsigned WORD (16 bit integer) values, which
                            accounts for the upper limit of 65535 (2**16 - 1) on
                            the value of a version.

                        4)  This routine unpacks the four numbers, and returns
                            them as four appropriately named members of a
                            NUMERIC_VERSION_INFO_WW data structure. To simplify
                            access from other programming languages, the members
                            are packed as tightly as possible.

    References:         None

    Date Written:       Thursday, 25 February 2010 and Sunday, 22 August 2010.
                        Documentation was completed just after Midnight on
                        Monday, 23 August 2010. Hence, the revision date is
                        actually 23 August 2010.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version Author Synopsis
    ---------- ------- ------ --------------------------------------------------
    2010/08/23 1,1,0,6 DAG    First fully functioning version.
    ============================================================================
*/

BOOL LIBSPEC_VERSIONINFOLIB_P6C_API GetNumericProdVersionA_P6C
(
    LPNUMERIC_VERSION_INFO_WW plpNumericVersionInfo ,
    LPCTSTR                   plpszFileName ,
    HINSTANCE                 phInstVersion
) ;

BOOL LIBSPEC_VERSIONINFOLIB_P6C_API GetNumericProdVersionW_P6C
(
    LPNUMERIC_VERSION_INFO_WW plpNumericVersionInfo ,
    LPCTSTR                   plpszFileName ,
    HINSTANCE                 phInstVersion
) ;

#ifdef UNICODE
    #define GetNumericProdVersion_P6C   GetNumericProdVersionW_P6C
#else
    #define GetNumericProdVersion_P6C   GetNumericProdVersionA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      InitVerInfo_P6C

    Defining Source:    GetVersionInfoA_P6C.C   - ANSI implementation
                        GetVersionInfoW_P6C.C   - Unicode implementation

    Synopsis:           Create a small private heap to store resource strings,
                        so that the whole lot can be discarded with a single API
                        call. See Remarks.

    Arguments:          pintFrstRsrcStrID = Integer ID of first resource string.

    Returns:            VER_SUCCESS_P6C if the resource ID is greater than zero,
                        or VER_INVALID_RESOURCE_ID_P6C otherwise.

    Remarks:            Call this function to initialize some data structures
                        before you call other functions in this module.

                        Originally, this function stored the ID of the resource
                        string to use for the first version string label. This
                        value adjusted the index that drove the switch statement
                        in function GetVersionInfo_P6C.

    References:         None

    Date Written:       Saturday, 05 November 2005 - Sunday, 06 November 2005.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2005/11/06 DAG First working version.

    2009/11/19 DAG 1) Simplify formatting of internal documentation, to decrease
                      the maintenance burden.

                   2) Remove code that discards the buffer reserved for the 
                      module name, so that the new functions can return it, in
                      whole and in part.
    ============================================================================
*/

long LIBSPEC_VERSIONINFOLIB_P6C_API InitVerInfoA_P6C
(
    int pintUnused
) ;

long LIBSPEC_VERSIONINFOLIB_P6C_API InitVerInfoW_P6C
(
    int pintUnused
) ;

#ifdef UNICODE
    #define InitVerInfo_P6C     InitVerInfoW_P6C
#else
    #define InitVerInfo_P6C     InitVerInfoA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      GetFileVersionInfo_P6C

    Defining Source:    GetFileVersionInfoA_P6C.C   - ANSI implementation
                        GetFileVersionInfoW_P6C.C   - Unicode implementation
                        GetFileVersionInfo_P6C.INL  - Body of both of the above
                        GetFileVersionInfo_VB_P6C.C - Wrapper for Visual Basic

    Synopsis:           Given an enumeration describing the desired string, call
                        the VerQueryValue function. On first pass, call the two
                        functions required to set up the call.

    Arguments:          plpVerForFile   = Name of file from which to retrieve a
                                          version string. See Remarks.

                        penmStringName  = Member of the VER_STRING_NAME_P6C
                                          enumeration. See Remarks.

                        phInstLabels    = Alternate instance handle from which
                                          to retrieve strings to use as labels.

                                          If phInstLabels is NULL, phInstVersion
                                          is substituted.

                                          If the module to which phInstVersion
                                          points is devoid of resource strings,
                                          the strings stored in the DLL into
                                          which this routine is linked are used.

    Returns:            lpszVersionInfo = Pointer to desired version string
                                          extracted from program file.

    Limitations:        The pointers returned by calls to this function are
                        rendered invalid by a call to companion function
                        GetVerInfoCleanup_P6C. If you intend to make subsequent
                        use of them, you must copy them into storage controlled
                        by the calling routine.

                        An easy way to do so is to pass each pointer to function
                        CopyStringToNewBuf_P6C, storing the return value in a
                        LPTSTR pointer that belongs to your calling code.

                        Though I could easily have coded GetFileVersionInfo_P6C
                        to return through CopyStringToNewBuf_P6C, I didn't,
                        because doing so wastes storage that isn't usually
                        needed after the splash message has been shown. Since I
                        created this separate function (CopyStringToNewBuf_P6C),
                        you have the option of selectively saving the return 
                        values that you need to keep.

    Remarks:            Use this routine to get version information from an EXE
                        or DLL that isn't necessarily loaded into the process.

                        Unlike GetVersionInfo_P6C, which assumes that its caller
                        knows the instance handle of the program file whose
                        version is sought, this function relaxes the requirement
                        because it gets an instance handle by loading the named
                        file as data, by way of the LoadLibraryEx Windows API
                        function. Hence, phInstVersion is replaced by
                        plpVerForFile.

                        Function GetVersionInfo_P6C defines its penmStringName
                        argument as a DWORD, which is described as "integer
                        specifying string to retrieve." Based on lessons learned
                        since that function came into being seven years ago,
                        this function makes the association explicit by casting
                        its like named argument to VER_STRING_NAME_P6C.

    Date Written:       Saturday, 09 June 2012 and Sunday, 10 June 2012
    ============================================================================
*/

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API GetFileVersionInfoA_P6C
(
    LPCTSTR             plpVerForFile ,
    VER_STRING_NAME_P6C penmStringName ,
    HINSTANCE           phInstLabels
) ;

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API GetFileVersionInfoW_P6C
(
    LPCTSTR             plpVerForFile ,
    VER_STRING_NAME_P6C penmStringName ,
    HINSTANCE           phInstLabels
) ;

BSTR   __stdcall GetFileVersionInfo_VB_P6C
(
    LPCTSTR             plpVerForFile ,
    VER_STRING_NAME_P6C penmStringName ,
    HINSTANCE           phInstLabels
) ;

#ifdef UNICODE
    #define GetFileVersionInfo_P6C      GetFileVersionInfoW_P6C
#else
    #define GetFileVersionInfo_P6C      GetFileVersionInfoA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      GetVersionInfo_P6C

    Defining Source:    GetVersionInfoA_P6C.C   - ANSI implementation
                        GetVersionInfoW_P6C.C   - Unicode implementation
                        GetVersionInfo_P6C.INL  - Body of both of the above

    Synopsis:           Given an enumeration describing the desired string, call
                        the VerQueryValue function. On first pass, call the two
                        functions required to set up the call.

    Arguments:          phInstVersion   = Instance handle, used to retrieve
                                          resources, such as version resources
                                          For console applications, pass NULL,
                                          as the instance handle that Windows
                                          provides to console applications is
                                          useless, and a NULL tells the resource
                                          functions to use the module that was
                                          loaded when the process was created.

                        penmStringName  = Integer specifying string to retrieve.

                        phInstLabels    = Alternate instance handle from which
                                          to retrieve strings to use as labels.

                                          If phInstLabels is NULL, phInstVersion
                                          is substituted.

                                          If the module to which phInstVersion
                                          points is devoid of resource strings,
                                          the strings stored in the DLL into
                                          which this routine is linked are used.

    Returns:            lpszVersionInfo = Pointer to desired version string
                                          extracted from program file.

    Limitations:        The pointers returned by calls to this function are
                        rendered invalid by a call to companion function
                        GetVerInfoCleanup_P6C. If you intend to make subsequent
                        use of them, you must copy them into storage controlled
                        by the calling routine.

                        An easy way to do so is to pass each pointer to function
                        CopyStringToNewBuf_P6C, storing the return value in a
                        LPTSTR pointer that belongs to your calling code.

                        Although I could easily have coded GetVersionInfo_P6C to
                        return through CopyStringToNewBuf_P6C, I didn't, because
                        doing so wastes storage that isn't usually needed after
                        the splash message has been shown. Since I created this
                        separate function (CopyStringToNewBuf_P6C), you have the
                        option of selectively saving the return values that you
                        need to keep.

    Remarks:            For console applications, pass a NULL for phInstVersion.
                        This signals the code that loads resource strings to use
                        a NULL instance handle, signaling the Windows kernel
                        library to look for the resources in the program file
                        that was loaded to create the process. Quoting from the
                        documentation of function FindResource:

                            "A value of NULL specifies the module handle
                            associated with the image file that the operating
                            system used to create the current process."

                        Although the LoadString documentation omits this remark,
                        testing in console application WWLOGGER, which was used
                        to test the November 2005 version of this function,
                        confirms that this statement applies to it, too.

                        Further, these tests confirm that the instance handle
                        returned by GetWindowLongPtr is useless for this purpose
                        in console applications.

                        The function uses internal static variables to preserve
                        data to expedite multiple calls.

    References:         http://msdn.microsoft.com/library/en-us/winui/winui/windowsuserinterface/resources/versioninformation/versioninformationreference/versioninformationfunctions/verqueryvalue.asp
                        (VERY LONG URL) for the official definition of the
                        VerQueryValue Windows API function, for which this
                        function is a general purpose wrapper.

    Date Written:       Friday, 08 July 2005 - Saturday, 09 July 2005.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Author Synopsis
    ---------- ------ ----------------------------------------------------------
    2005/07/09 DAG    First working version.

    2009/11/19 DAG    1) Simplify formatting of internal documentation, to
                         decrease the associated maintenance burden.

                      2) Fix a self-limiting memory leak in GetVersionInfo_P6C()
                         which also causes some code to be executed on every
                         pass, rather than once per process.

                         Since no process makes more than a handful of calls to
                         GetVersionInfoA_P6C, the leak is never greater than a
                         few hundred bytes - enough to hold a copy of the fully
                         qualified name of the program file for each call.
                         Typically, this routine is called no more than 12
                         times, once per version string.

                      3) Add the following new functions to expose data gathered
                         for internal use, and discarded, which the calling
                         application can use to eliminate API calls to get it
                         again.

                            GetProgramFQFN_P6C
                            GetProgramUQFN_P6C
                            GetProgramDir_P6C

                      4) Remove definition of CUSTOMER_FLAG, which is defined in
                         CommonConstants_P6C.H, which I just added, in case this
                         header is included in a source module that doesn't
                         include it.

                      5) Substitute externally linked handle m_hProcHeap for
                         locally defined md_hProcHeap, so that most, if not all,
                         code that uses the process heap can share a handle.

    2010/02/27 DAG    Add an optional phInstLabels argument, to provide an
                      alternate instance handle, to be used in place of the
                      renamed phInstVersion instance handle for the PE file from
                      which to extract version strings.

    2010/03/02 DAG    Change GetProgramUQFN_P6C and GetProgramFQFN_P6C so that
                      they return usable strings, regardless of whether routine
                      GetVersionInfo_P6C has been called.

    2010/03/05 DAG    Fix an allocation math error in the Unicode version of
                      GetProgramUQFN_P6C and GetProgramFQFN_P6C.

    2010/04/10 DAG    Add GetLastError and appropriate tests following a failure
                      of LoadString.

                            The remedy for this is our own status code,
                            VER_RESOURCE_STRING_NOT_FOUND_P6C.

                            Please see LOADSTRING AND INVALID STRING IDS, in
                            the Remarks section of P6VersionInfo.H.

    2011/08/20 DAG    1) Fix memory leaks in functions GetProgramUQFN_P6C and
                         GetProgramFQFN_P6C, both of which stash pointers to the
                         strings they construct in static module variables. The
                         pointers were not being tested before being assigned to
                         a new pointer (returned by HeapAlloc), which caused the
                         previous string to become orphaned - a classic memory'
                         leak.

                      2) Consolidate the revision history in this header.
    ============================================================================
*/

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API GetVersionInfoA_P6C
(
    HINSTANCE phInstVersion ,
    DWORD     penmStringName ,
    HINSTANCE phInstLabels
) ;

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API GetVersionInfoW_P6C
(
    HINSTANCE phInstVersion ,
    DWORD     penmStringName ,
    HINSTANCE phInstLabels
) ;

#ifdef UNICODE
    #define GetVersionInfo_P6C      GetVersionInfoW_P6C
#else
    #define GetVersionInfo_P6C      GetVersionInfoA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      GetVerInfoCleanup_P6C

    Defining Source:    GetVersionInfoA_P6C.C   - ANSI implementation
                        GetVersionInfoW_P6C.C   - Unicode implementation

    Synopsis:           Deallocate storage used by function GetVersionInfo_P6C,
                        the only function in this module that does real work.

    Arguments:          None

    Returns:            Nothing. Sets m_dwLstErrFV if there was an error. There
                                 are no errors worth worrying about, though,
                                 unless the calling program needs lots of core.

    Limitations:        Calls to this function render all pointers returned by
                        calls to companion function GetVersionInfo_P6C invalid.
                        If you intend to make subsequent use of them, you must
                        copy them into storage controlled by the calling routine
                        before you call this function.

                        An easy way to do so is to pass each pointer to function
                        CopyStringToNewBuf_P6C, storing the return value in a
                        LPTSTR pointer that belongs to your calling code.

                        Although I could easily have coded GetVersionInfo_P6C to
                        return through CopyStringToNewBuf_P6C, I didn't, because
                        doing so wastes storage that isn't usually needed after
                        the splash message has been shown. Since I created this
                        separate function (CopyStringToNewBuf_P6C), you have the
                        option of selectively saving the return values that you
                        really need.

    Remarks:            Call this function to free the memory allocated to hold
                        version information, for constructing About Boxes or log
                        messages. However, you must make a copy of the data into
                        memory that you, the caller, own, before you do so, to
                        avoid access violations, because the return value from
                        GetVersionInfo_P6C are pointers to areas within the
                        largest of these buffers.

                        There are ANSI and Unicode implementations of this
                        function because the ANSI and Unicode implementations of
                        the other functions use separate sets of module level
                        storage, and may live in different libraries.

    References:         None

    Date Written:       Saturday, 08 July 2005.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2005/07/09 DAG First working version.

    2009/12/03 DAG Simplify formatting of internal documentation, to decrease
                   the maintenance burden.
    ============================================================================
*/

void LIBSPEC_VERSIONINFOLIB_P6C_API GetVerInfoCleanupA_P6C ( void ) ;

void LIBSPEC_VERSIONINFOLIB_P6C_API GetVerInfoCleanupW_P6C ( void ) ;

#ifdef UNICODE
    #define GetVerInfoCleanup_P6C       GetVerInfoCleanupW_P6C
#else
    #define GetVerInfoCleanup_P6C       GetVerInfoCleanupA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      GetAllVerInfo_P6C

    Defining Source:    GetVersionInfoA_P6C.C   - ANSI implementation
                        GetVersionInfoW_P6C.C   - Unicode implementation

    Synopsis:           Given a list of version data values to retrieve, call
                        GetVersionInfo_P6C repeatedly for each, returning a list
                        of pointers to the requested items.

    Arguments:          phInstVersion   = Instance handle, used to retrieve
                                          resources, such as version resources.
                                          For console applications, pass NULL,
                                          as the instance handle that Windows
                                          provides to console applications is
                                          useless, and a NULL tells the resource
                                          functions to use the module that was
                                          loaded when the process was created.

                        paintVerItems   = Array of integers specifying version
                                          strings to retrieve.

                                          A value of -1 terminates the list.

                        phInstLabels    = Alternate instance handle from which
                                          to retrieve strings to use as labels.

                                          If phInstLabels is NULL, phInstVersion
                                          is substituted.

    Returns:            lpszVersionInfo = Array of long pointers to desired
                                          version string extracted from program
                                          file and held in module variable
                                          m_lpVersionData.

                                          A value of NULL terminates the list,
                                          which also has the same number of
                                          items as input list paenmVerItems.

    Remarks:            For console applications, pass a NULL for phInstVersion.
                        This signals the code that loads resource strings to use
                        a NULL instance handle, to signal the Windows kernel to
                        look for the resources in the program file that was used
                        to create the process. Quoting from the documentation of
                        function FindResource:

                            "A value of NULL specifies the module handle
                            associated with the image file that the operating
                            system used to create the current process."

                        Although the LoadString documentation omits this remark,
                        testing in console application WWLOGGER, which was used
                        to test the November 2005 version of this function,
                        confirms that this statement applies to it, too.

                        Further, these tests confirm that the instance handle
                        returned by GetWindowLongPtr is useless for this purpose
                        in console applications.

                        Call this function once with a list of items to extract
                        from the version resource table in a program.

                        You must process the entire list before calling function
                        GetVerInfoCleanup_P6C to free the memory occupied by the
                        version strings.

                        I chose the value of -1, symbolically represented by
                        VER_END_OF_ITEMS_P6C, to terminate the list to which
                        argument paintVerItems points because the list is
                        composed of resource string IDs, which must be positive
                        integers.

    References:         None

    Date Written:       Saturday, 08 July 2005 - Sunday, 10 July 2005.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2005/07/09 DAG First working version.

    2009/11/19 DAG 1) Simplify formatting of internal documentation,to
                      decrease the maintenance burden.

                   2) Change the storage class of local DWORD_PTR variable
                      dwpVerItem from auto to static, to keep pointers away
                      from the stack.
    ============================================================================
*/

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API GetAllVerInfoA_P6C
(
    HINSTANCE phInstVersion ,
    LPINT     paintVerItems ,
    HINSTANCE phInstLabels
) ;

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API GetAllVerInfoW_P6C
(
    HINSTANCE phInstVersion ,
    LPINT     paintVerItems ,
    HINSTANCE phInstLabels
) ;

#ifdef UNICODE
    #define GetAllVerInfo_P6C       GetAllVerInfoW_P6C
#else
    #define GetAllVerInfo_P6C       GetAllVerInfoA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      AssembleAboutString_P6C

    Defining Source:    GetVersionInfoA_P6C.C   - ANSI implementation
                        GetVersionInfoW_P6C.C   - Unicode implementation

    Synopsis:           Given a list of version data values to retrieve and a
                        list of strings to put around them, call function
                        GetVersionInfo_P6C repeatedly for each, returning a list
                        of pointers to the requested items. Then, using the list
                        of strings, construct a string in a dynamic buffer and
                        return a pointer to the string.

    Arguments:          phInstVersion   = Instance handle, used to retrieve
                                          resources, such as version resources
                                          For console applications, pass NULL,
                                          as the instance handle that Windows
                                          provides to console applications is
                                          useless, and a NULL tells the resource
                                          functions to use the module that was
                                          loaded when the process was created.

                        paintVerItems   = Array of integers specifying version
                                          strings to retrieve.

                                          A value of -1 terminates the list.

                        paintVerLabels  = Array of resource IDs that correspond
                                          to labels for the returned version
                                          strings.

                                          The function requires one string per
                                          version item; there is no terminator.

                        phInstLabels    = Alternate instance handle from which
                                          to retrieve strings to use as labels.

                                          If phInstLabels is NULL, phInstVersion
                                          is substituted.

    Returns:            lpszVersionInfo = Array of long pointers to desired
                                          version string extracted from program
                                          file and held in module variable
                                          m_lpVersionData.

                                          A value of NULL terminates the list,
                                          which also has the same number of
                                          items as input list paenmVerItems.

    Remarks:            For console applications, pass a NULL for phInstVersion.
                        This signals the code that loads resource strings to use
                        a NULL instance handle, to signal the Windows kernel to
                        look for the resources in the program file that was used
                        to create the process. Quoting from the documentation of
                        function FindResource:

                            "A value of NULL specifies the module handle
                            associated with the image file that the operating
                            system used to create the current process."

                        Although the LoadString documentation omits this remark,
                        testing in console application WWLOGGER, which was used
                        to test the November 2005 version of this function,
                        confirms that this statement applies to it, too.

                        Further, these tests confirm that the instance handle
                        returned by GetWindowLongPtr is useless for this purpose
                        in console applications.

                        Call this function once with a list of items to extract
                        from the version resource table in a program.

                        Since the list of pointers returned by this function has
                        no terminator, the caller must remember how many items
                        it passed into this function, and stop walking the list
                        when the last item has been read.

                        You must process the entire list before calling function
                        GetVerInfoCleanup_P6C to free the memory occupied by the
                        version strings.

                        I chose the value of -1, symbolically represented by
                        VER_END_OF_ITEMS_P6C, to terminate the list to which
                        argument paintVerItems points because the list is
                        composed of resource string IDs, which must be positive
                        integers.

    References:         None

    Date Written:       Sunday, 10 July 2005.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2005/07/10 DAG First working version.

    2009/11/19 DAG Simplify formatting of internal documentation, to decrease
                   the maintenance burden.
    ============================================================================
*/

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API AssembleAboutStringA_P6C
(
    HINSTANCE phInstVersion ,
    LPINT     paintVerItems ,
    LPINT     paintVerLabels ,
    HINSTANCE phInstLabels
) ;

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API AssembleAboutStringW_P6C
(
    HINSTANCE phInstVersion ,
    LPINT     paintVerItems ,
    LPINT     paintVerLabels ,
    HINSTANCE phInstLabels
) ;

#ifdef UNICODE
    #define AssembleAboutString_P6C     AssembleAboutStringW_P6C
#else
    #define AssembleAboutString_P6C     AssembleAboutStringA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      P6VersionInfoErrorReported_P6C

    Defining Source:    P6VersionInfoErrorReported_P6C.C

    Synopsis:           Return TRUE if the last routine that caught an exception
                        reported it to the user via the console, a message box,
                        or the event log.

    Arguments:          None

    Returns:            The return value is TRUE (nonzero) if the last exception
                        caught a routine in this library has been reported. Once
                        called, the flag is also reset, saving another call.

    Dependencies:       Anther module in the same executable file, usually the
                        one that defines the entry point routine, must define
                        and initialize m_fErrorReported, an externally linked
                        Boolean, to FALSE.

    Remarks:            This routine is the second of a new class, which is
                        intended to prevent repetitively reporting the same
                        exception, usually with decreasing amounts of contextual
                        detail.

                        Though small, it gets a separate source file to simplify
                        incorporating similar routines into other libraries.

    References:         None

    Date Written:       Sunday, 13 May 2012
    ============================================================================
*/

BOOL LIBSPEC_VERSIONINFOLIB_P6C_API P6VersionInfoErrorReported_P6C ( void ) ;


/*
    ============================================================================

    Function Name:      GetVersionInfoErrorMsgHint_P6C

    Defining Source:    GetVersionInfoErrorMsgHintA_P6C.C  - ANSI
                        GetVersionInfoErrorMsgHintW_P6C.C  - Unicode

    Synopsis:           Return a pointer to a string that contains the error
                        message hint defined in string IDS_GETVERSION_ERRMSG.

    Arguments:          None

    Returns:            The return value is a pointer to a buffer, allocated
                        from the default process heap, that is exactly the right
                        size to hold the returned string.

    Dependencies:       The module that defines the DLL entry point routine must
                        expose the DLL instance handle and an initialized handle
                        to the default process heap as variables with a storage
                        class of extern.

    Remarks:            This routine provides external access to an otherwise
                        private resource string, without the caller needing to
                        know its ID or the instance handle of the DLL, which is
                        usually loaded at process startup.

                        Though small, it gets a separate source file to simplify
                        incorporating similar routines into other libraries.

    References:         None

    Date Written:       Sunday, 13 May 2012
    ============================================================================
*/

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API GetVersionInfoErrorMsgHintA_P6C ( void ) ;

LPTSTR LIBSPEC_VERSIONINFOLIB_P6C_API GetVersionInfoErrorMsgHintW_P6C ( void ) ;

#ifdef UNICODE
    #define GetVersionInfoErrorMsgHint_P6C      GetVersionInfoErrorMsgHintW_P6C
#else
    #define GetVersionInfoErrorMsgHint_P6C      GetVersionInfoErrorMsgHintA_P6C
#endif  /*  #ifdef UNICODE */

// Close the block of code that has "C" linkage.
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /* _GETVERSIONINFO_P6C_INCLUDED */