#if !defined ( _WWKERNELLIBWRAPPER_DEFINED )
#define _WWKERNELLIBWRAPPER_DEFINED

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /*  #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

/*
    ============================================================================

    Name:               WWKernelLibWrapper.H

	Library:            WWKernelLibWrapper32.dll (WWKernelLibWrapper32.lib)

    Synopsis:           Header file for a Windows Dynamic Link library,
                        WWKernelLibWrapper.DLL, which provides convenience
                        wrappers for a few frequently used functions exported by
                        Kernel32.dll.

    Remarks:            All functions that return long pointers to strings
                        (LPTSTR) allocate memory to hold the strings from the
                        process heap.

                        The memory can be subsequently freed in one of two ways.

                        1)  Call FreeDfltHeapBuf_P6C, which happens to be
                            exported by this library. C programmers may consult
                            CopyStringToNewBuf_P6C.H for its prototype, and
                            should include this header, as you include windows.h
                            to avail yourself of the functions in winbase.h.

                        2)  Call the Windows API HeapFree function directly,
                            passing the pointer, along with a handle to your
                            default process heap.

                        The first method incurs slightly more overhead, because
                        it adds another frame to the call stack, and consumes
                        another small chunk of your stack, but it permits any
                        program that can call this library to discard the memory
                        with just one call, rather than up to two calls to the
                        Windows API to use the second method.

                        If you keep a handle to the default process heap handy
                        at all times, as I usually do, either method requires
                        just one call, giving the second method an edge.

                        Though LIBSPEC_WWKERNELLIBWRAPPER_API is defined in
                        header SEHHeapAllocators.H, which appears early in this
                        header, well before the first reference to it, this
                        header must start from scratch.

    References:         "The Ultimate (DLL) Header File, Joseph M. Newcomer
                        http://www.flounder.com/ultimateheaderfile.htm

    Created:            Sunday, 05 June 2011

    License:            Copyright (C) 2009-2017, David A. Gray. All rights reserved.

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

    Date       Version    Author Synopsis
    ---------- ---------- ------ -----------------------------------------------
    2011/06/06 1, 0, 0, 0 DAG    First working version.

    2011/06/11 1, 1, 1, 0 DAG    Substitute a name, unique to this header, for
                                 LIBSPEC, to prevent symbolic name collisions.
                                 This is the approach implemented by the Visual
                                 C++ 6.0 AppWizard.

                                 The name used in this header is
                                 LIBSPEC_WWKERNELLIBWRAPPER_API.

    2011/08/29 1, 1, 2, 0 DAG    1) Fix an inverted logic error that prevented
                                    the function from ever returning a usable
                                    value, and move the function body into an
                                    inline #include file, GetCWD.INL.

                                 2) Move the definition of redefinition guard
                                    variable _WWKERNELLIBWRAPPER_DEFINED below
                                    the #pragma once directive, which performs
                                    the same service for programs compiled with
                                    Microsoft Visual C++.

    2011/09/02 1, 1, 3, 1 DAG    Correct the memory allocation routines in both
                                 implementations of GetCWD_P6C to release unused
                                 memory. As written, they return a buffer the
                                 size of MAX_PATH + 1 TCHARs, much of which is
                                 slack bytes, even with my long paths strings.

    2011/09/06 1, 2, 4, 0 DAG    Consolidate the wrappers around the heap memory
                                 allocation routines, such as FreeHeapMem_WW, in
                                 this header, and its associated dynamic link
                                 library. The consolidation includes mapping
                                 FreeHeapMem_WW to FreeDfltHeapBuf_P6C, which is
                                 newer and more robust, because it gracefully
                                 handles any pointer, regardless of whether it
                                 points to a block in the default process heap.
                                 The two functions have identical signatures.

                                 LIBSPEC_WWKERNELLIBWRAPPER_API is now used for
                                 every function declared in this header.

    2012/02/06 1, 3, 5, 0 DAG    Move function CopyStringToNewBuf_P6C from
                                 P6CStringLib1.dll to WWKernelLibWrapper.dll.

    2012/05/20 1, 4, 6, 0 DAG.WW 1) Streamline the flow of IsBufFromHeap_WW.

                                 2) Replace symbolic constant CUSTOMER_FLAG with
                                    APPLICATION_ERROR_MASK.

    2012/06/05 1, 5, 7, 0 DAG.WW Correct memory allocation errors in GetCWD.
                                 Both (ANSI and Unicode) implementations are
                                 affected.

    2012/06/08 1, 6, 8, 0 DAG.WW Add function DllLoadAsData_WW, with ANSI and
                                 Unicode flavors.

    2012/07/15 1, 7, 9, 0 DAG.WW 1) DllLoadAsData_WW: If _DLLLOADASDATA_MACRO_WW
                                    is defined, DllLoadAsData_WW is defined as a
                                    macro. Otherwise, the existing entry point
                                    for the current character encoding (ANSI or
                                    Unicode) is defined.

                                 2) FreeDfltHeapBuf_P6C: Return NULL when called
                                    with a NULL pointer. Previously, the return
                                    value was an invalid pointer (-1). Since it
                                    is conceivable for this routine to be called
                                    with a null pointer, rather than treat such
                                    a call as an outright error, I decided that
                                    it could be safely handled gracefully and
                                    silently.

                                 3) IsBufFromHeap_WW: Substitute my Unless macro
                                    for if (VarName == NULL), and add a note
                                    about the first-chance exception note left
                                    in the Debug output window when the catch
                                    block of the Structured Exception Handling
                                    code fires. Since if (VarName == NULL) and
                                    Unless ( VarName ) generate essentially the
                                    same code, and have the same outcome, this
                                    change is syntactic sugar.

                                 4) Move LeakTest_WW from P6CUtilLib1.

    2013/06/19 1, 7,10, 0 DAG    Eliminate CommonConstants_P6C.H in favor of the
                                 much more focused Const_Typedefs_WW.H.

    2015/02/01 1, 8, 0, 0 DAG    Define new functions AllocDfltHeapBufSEH_P6C
                                 and ReAllocDfltHeapBufSEH_P6C which wrap
                                 HeapAlloc and HeapReAlloc, respectively, in a
                                 Structured Exception Handling (SEH) block, and
                                 report the exception through SetLastError.

    2015/02/14 1, 8, 0, 3 DAG    When the return value of the last function call
                                 is the return value of the current function,
                                 make the last call the object of the Return
                                 statement.

                                 The following routines benefit from this tiny
                                 optimization.

                                    1) AllocDfltHeapBufSEH_P6C
                                    2) CopyStringToNewBuf_P6C
                                    3) GetCWD_P6C
                                    4) GetDLLModuleName_WW
                                    5) ReAllocDfltHeapBufSEH_P6C

                                 For a DEBUG build, this tiny optimization
                                 eliminates a store, followed by a redundant
                                 reloading of the EAX register with the value
                                 that is already in it. However, it does nothing
                                 for a retail build, because the compiler
                                 optimizes away the redundant store and load.

                                 Although it didn't gain from this optimization,
                                 FreeDfltHeapBuf_P6C got a small improvement of
                                 a different sort; I moved the DWORD allocated
                                 on entry to hold the status code reported in
                                 its catch block from module scope, which is not
                                 thread safe, to the stack frame, which is.

                                 Change the semantics of _DLLLOADASDATA_MACRO_WW
                                 to favor the macro over the function, which I
                                 am doing by replacing _DLLLOADASDATA_MACRO_WW,
                                 which has never been used outside this header,
                                 with a new symbol, _DLLLOADASDATA_FUNCTION_WW.

    2015/08/21 1, 9, 0, 4 DAG    1) Upgrade to Visual Studio 2013, and link
                                    against its CRT DLL. Other than eliminating
                                    the module definition file and correcting
                                    spelling errors identified by the spelling
                                    checker extension that I installed into
                                    the Visual Studio 2013 IDE, the code
                                    is unchanged, except as noted in the next
                                    item. However, changing the linkage
                                    editor settings to use default libraries got
                                    me a DLL whose Structured Exception Handlers
                                    are marked as safe.

                                 2) Eliminate the pointer validation from
                                    FreeDfltHeapBuf_P6C, and allow it to fail if
                                    the pointer is invalid. The structured
                                    exception handler will still catch the
                                    error and report it.

                                 3) Mark function IsBufFromHeap_WW as deprecated
                                    because of the way it behaves on Windows 7.
                                    Please see the Remarks section of its flower
                                    box for an explanation.

    2015/08/25 1, 9, 1, 5 DAG    Add the HEAP_GENERATE_EXCEPTIONS flag to the
                                 HeapFree function call in FreeDfltHeapBuf_P6C,
                                 and have it eat the ERROR_INVALID_PARAMETER
                                 exception returned when it receives an invalid
                                 heap pointer.

                                 In AllocDfltHeapBufSEH_P6C.C, correct errors
                                 flagged by the spelling checker add-in that I
                                 installed into my Visual Studio 2013 IDE.

    2015/10/06 1, 9, 2, 6 DAG    Move SHL_GetOsVersion, under a new name,
                                 GetOsVersionInfo.

    2015/10/07 1, 9, 2, 7 DAG    Rewrite the documentation of GetOsVersionInfo.
                                 Only the documentation embedded in this header
                                 is affected; the code remains unchanged. The
                                 version increment is strictly for change
                                 tracking.

    2015/10/12 1, 9, 2, 8 DAG    Define a version number constant, for use with
                                 GetOsVersionInfo, to designate Windows Vista or
                                 newer, and use the lessons learned today to
                                 make that routine follow the _stdcall calling
                                 conventions.

                                 Only the prototype of function GetOsVersionInfo
                                 is affected; the implementation is unchanged.

    2015/10/14 1, 9, 2, 8 DAG    Define major version number testing macros, for
                                 use with GetOsVersionInfo, to test for Windows
                                 Vista or newer, and to test for any major
                                 version or higher.

                                 Since this revision is confined to CPP macros,
                                 the library version is unchanged, and the
                                 library was not rebuilt.

    2015/10/18 1, 9, 2, 8 DAG    The name of the RTL_OSVERSIONINFOEXW structure
                                 must be a parameter of WWKW_OSIsVistaOrNewer
                                 and WWKW_OSIsMinimumVersion. Following reverse
                                 Polish notation, it becomes the second of the
                                 two arguments of the latter macro.

                                 Since this revision is confined to CPP macros,
                                 the library version is unchanged, and the
                                 library was not rebuilt.

    2017/01/16 2,0,0,1 DAG       Rename the library, from WWKernelLibWrapper to
                                 WWKernelLibWrapper32, and synchronize the name
                                 of its library header, so that I can make a
                                 wholesale calling convention change, from
                                 __cdecl, which I didn't fully understand in
                                 2005, to __stdcall, a slightly more efficient
                                 calling convention, including slightly less
                                 code bloat.

                                 Define three new routines that extend existing
                                 SEH protected heap allocators to support ANY
                                 heap.

                                 Use the following table as your map.

                                 ----------------------------------------------------
                                 Default Heap               Any Heap
                                 -------------------------  -------------------------
                                 AllocDfltHeapBufSEH_P6C    AllocAnyHeapBufSEH_P6C
                                 ReAllocDfltHeapBufSEH_P6C  ReAllocAnyHeapBufSEH_P6C
                                 FreeDfltHeapBuf_P6C        FreeAnyHeapBuf_P6C
                                 ----------------------------------------------------

                                 The new function prototypes are the same as are
                                 those of the original three functions, with the
                                 addition of a heap handle to the end of each
                                 argument list.

    2017/02/14 2, 0, 0, 2 DAG    Move GetProgramFQFN_P6C, GetProgramUQFNW_P6C,
                                 and GetProgramDir_P6C from P6VersionInfo.dll to
                                 this library. Since both are being deployed at
                                 the same time, this isn't a breaking change.

                                 Relocating some routines from P6VersionInfo.dll
                                 to this library, which requires them to import
                                 the memory allocators defined herein exposed an
                                 oversight that arose from duplicated definition
                                 of the original memory allocator wrappers. This
                                 is corrected, once and for all, by moving these
                                 declarations into SEHHeapAllocators.H, and
                                 removing them from WWKernelLibWrapper.H, which
                                 now includes SEHHeapAllocators.H.
    ============================================================================
*/

#include <windows.h>
#include <Const_Typedefs_WW.H>

//  ----------------------------------------------------------------------------
//  This copy book brings its own API macros and constants. It must be kept, for
//  the time being, because it isn't worth the effort to identify and remove the
//  references from existing code and rebuild all affected programs.
//  ----------------------------------------------------------------------------

#include <CopyStringToNewBuf_P6C.H>
#include <SEHHeapAllocators.H>

//  ----------------------------------------------------------------------------
//  Define our custom error codes.
//  ----------------------------------------------------------------------------

#define PATHSTRINGFIXUP_ERR_NO_ROOM         ( 0x00000021 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  Following a call to GetOsVersionInfo, use WWKW_GETOSVERSIONINFO_VISTA to
//  test the dwMajorVersion member of the RTL_OSVERSIONINFOEXW structure.
//  Test for greater than or equal to, so that the test is future proof. Better
//  still, just use the next macro, WWKW_OSIsVistaOrNewer, which evaluates to
//  Boolean TRUE if it is, otherwise, it evaluates to Boolean False.
//
//  Use WWKW_OSIsMinimumVersion for other major version tests. This macro also
//  expands into a Boolean expression, and argument pVerMajor is cast to DWORD,
//  to force a compiler diagnostic if it cannot be cast to that type. This also
//  ensures that your compiler won't complain about a signed/unsigned mismatch.
//
//  Constants WWKW_GETOSVERSIONINFO_WIN8 and WWKW_GETOSVERSIONINFO_WIN10 are for
//  using WWKW_OSIsMinimumVersion to verify minimum versions of 8 and 10,
//  respectively.
//
//  Microsoft wisely recommends the RtlVerifyVersionInfo routine for making more
//  complex decisions about the installed version of Windows and associated
//  components, such as Internet Explorer.
//  ----------------------------------------------------------------------------

#define WWKV_GETOSVERSIONINFO_WIN2K         0x00000005L
#define WWKW_GETOSVERSIONINFO_VISTA         0x00000006L
#define WWKW_GETOSVERSIONINFO_WIN8          0x00000008L
#define WWKW_GETOSVERSIONINFO_WIN10         0x0000000AL
#define WWKW_GETOSVERSIONINFO_BASE          0x00000000L     // Windows 2000, with WWKV_GETOSVERSIONINFO_WIN2K, or Windows Vista, with WWKW_GETOSVERSIONINFO_VISTA
#define WWKW_GETOSVERSIONINFO_PONT_1        0x00000001L     // Windows XP, with WWKV_GETOSVERSIONINFO_WIN2K, or Windows 7, with WWKW_GETOSVERSIONINFO_VISTA

//  ----------------------------------------------------------------------------
//  Allocate a RTL_OSVERSIONINFOEXW structure, call GetOsVersionInfo to fill it,
//  then use these macros to evaluate whether your code supports the version of
//  Microsoft Windows on which it is executing.
//
//  1)  WWKW_OSIsVistaOrNewer is a simplified macro that returns TRUE if the OS
//      is at least Windows Vista.
//
//  2)  WWKW_OSIsWindows7OrNewer is a simplified macro that returns TRUE if the OS
//      is at least Windows 7.
//
//  3)  WWKW_OSIsMinimumVersionMaj is a more advanced version that tests for any
//      major Windows version.
//
//  4)  WWKW_OSIsMinimumVersionMin extends WWKW_OSIsMinimumVersionMaj by adding
//      the minor version to its truth table. You need this version, with the
//      minor value set to 1, to differentiate Windows 7 from Windows Vista and
//      Windows XP from Windows 2000, in addition to its expected use to test
//      for Windows 8.1, a true minor upgrade.
//  ----------------------------------------------------------------------------

#define WWKW_OSIsVistaOrNewer(pk_OsVer)                              ( ( BOOL ) ( pk_OsVer.dwMajorVersion >= WWKW_GETOSVERSIONINFO_VISTA ) )
#define WWKW_OSIsWindows7OrNewer(pk_OsVer)                           ( ( BOOL ) ( pk_OsVer.dwMajorVersion >= WWKW_GETOSVERSIONINFO_VISTA && pk_OsVer.dwMinorVersion >= WWKW_GETOSVERSIONINFO_PONT_1 ) )
#define WWKW_OSIsMinimumVersionMaj(pVerMajor, pk_OsVer)              ( ( BOOL ) ( pk_OsVer.dwMajorVersion >= ( DWORD ) pVerMajor         ) )
#define WWKW_OSIsMinimumVersionMin(pVerMajor, pVerMinor, pk_OsVer)   ( ( BOOL ) ( pk_OsVer.dwMajorVersion >= ( DWORD ) pVerMajor         && pk_OsVer.dwMinorVersion >= ( DWORD ) pVerMinor ) )

//  ----------------------------------------------------------------------------
//  Define private custom symbolic constants used in building the code, and
//  others for use by callers.
//  ----------------------------------------------------------------------------

#if !defined ( PATHSTRINGFIXUP_EXTRA_ROOM )
    #define PATHSTRINGFIXUP_EXTRA_ROOM      PLUS_ONE_WW
#endif  /* #if !defined ( PATHSTRINGFIXUP_EXTRA_ROOM ) */

//  ----------------------------------------------------------------------------
//  Define enumerated constants used in arguments.
//  ----------------------------------------------------------------------------

#if ! defined ( __PATHSTRINGFIXUP_HOW_P6C_DEFINED )
    #define __PATHSTRINGFIXUP_HOW_P6C_DEFINED
typedef enum _tagPATHSTRINGFIXUP_HOW_P6C
{
    PATHSTRINGFIXUP_INVALID ,           // 0
    PATHSTRINGFIXUP_ADD_P6C ,           // 1
    PATHSTRINGFIXUP_REMOVE_P6C ,        // 2
}   PATHSTRINGFIXUP_HOW_P6C ;
#endif  /* #if ! defined ( __PATHSTRINGFIXUP_HOW_P6C_DEFINED ) */

//  ----------------------------------------------------------------------------
//  Define the decoration for the functions declared herein. These definitions
//  extend to WWKernelLibWrapper.H, which includes this header before it needs
//  LIBSPEC_WWKERNELLIBWRAPPER_API.
//  ----------------------------------------------------------------------------

#if defined ( LIBSPEC_WWKERNELLIBWRAPPER_API )
    #undef LIBSPEC_WWKERNELLIBWRAPPER_API
#endif  /* #if defined ( LIBSPEC_WWKERNELLIBWRAPPER_API ) */

#if defined ( _BUILDING_WWKERNELLIBWRAPPER )
    #if defined ( __WWKERNELLIBWRAPPER_LOCAL_CONSUMER__ )
        #define LIBSPEC_WWKERNELLIBWRAPPER_API  __declspec(dllimport) __stdcall
    #else
        #define LIBSPEC_WWKERNELLIBWRAPPER_API  __declspec(dllexport) __stdcall
    #endif  /* #if defined ( __WWKERNELLIBWRAPPER_LOCAL_CONSUMER__ ) */
#else
    #define LIBSPEC_WWKERNELLIBWRAPPER_API      __declspec(dllimport) __stdcall
#endif  /* #if defined ( _BUILDING_WWKERNELLIBWRAPPER ) */

//  ----------------------------------------------------------------------------
//  Declare functions exported by this library. All are declared with C linkage,
//  so that they work with callers written in C, C++, Visual Basic, or whatever.
//  If it can call the Windows API, it can call these, too.
//  ----------------------------------------------------------------------------

#if defined ( __cplusplus )
extern "C"
{
#endif  /* __cplusplus */


/*
    ----------------------------------------------------------------------------

    Name:               DllLoadAsData_WW

    Synopsis:           Load a DLL as data, e. g., to get resources from it.

    In:                 plpDllName      = Constant long pointer to a null
                                          terminated string that contains the
                                          name of the library to load.

    Out:                If the function succeeds, the return value is an
                        instance handle to use to read resources from it. If the
                        function fails, the return value is NULL. Call
                        GetLastError to get extended error information.

    Remarks:            1)  Since the input is a string, there are ANSI and
                            Unicode implementations.

                        2)  If the library path string is relative, it must be
                            accessible in the context of the current working
                            directory.

                        3)  To unload the library, call FreeLibrary, passing the
                            instance handle of the DLL to be discarded.

                        This function is deprecated in favor of the like named
                        preprocessor macro that emits the call to LoadLibraryEx
                        as inline code, saving a stack frame and a function call
                        and tear down. On 2015/02/14, I changed the preprocesor
                        macros so that the default is to use the macro code.

    Created:            Thursday, 07 June 2012 and Friday, 08 June 2012

    ----------------------------------------------------------------------------
*/

HINSTANCE LIBSPEC_WWKERNELLIBWRAPPER_API DllLoadAsDataA_WW
(
    LPCTSTR plpDllName
) ;

HINSTANCE LIBSPEC_WWKERNELLIBWRAPPER_API DllLoadAsDataW_WW
(
    LPCTSTR plpDllName
) ;

#if defined ( _DLLLOADASDATA_FUNCTION_WW )
    #if defined ( UNICODE )
        #define DllLoadAsData_WW  DllLoadAsDataW_WW
    #else
        #define DllLoadAsData_WW  DllLoadAsDataA_WW
    #endif  /* #if defined ( UNICODE ) */
#else
    #define DllLoadAsData_WW(plpDllName)  ( LoadLibraryEx ( plpDllName , DW_RESERVED , LOAD_LIBRARY_AS_DATAFILE ) )
#endif  /* #if defined ( _DLLLOADASDATA_FUNCTION_WW ) */



/*
    ----------------------------------------------------------------------------

    Name:               GetCWD_P6C

    Synopsis:           Get the current directory, returning a string that
                        conforms to the requirement represented by pAddOrRemove,
                        which determines whether or not the returned string is
                        terminated with a path delimiter.

    In:                 pAddOrRemove    = Member of the PATHSTRINGFIXUP_HOW_P6C
                                          enumeration, as follows.

                                          PATHSTRINGFIXUP_ADD_P6C    = 1
                                          PATHSTRINGFIXUP_REMOVE_P6C = 2

                                          Any other value is ignored, and the
                                          string is returned, unmodified, as it
                                          arrives from the underlying Windows
                                          API function.

                                          Unless it is already defined, this
                                          header defines PATHSTRINGFIXUP_HOW_P6C
                                          in exactly the same way as it is
                                          defined in P6CStringLib1.H.

    Out:                Long pointer to a string containing the fully qualified
                        name of the current working directory.

    Remarks:            1) The original version of this function, created for
                           use as part of the WWWILMuscle library, used a
                           companion function, PathStringFixup_P6C, to fix up
                           the path string as directed by the caller. To avoid
                           a circular linkage loop, and some extra overhead in
                           PathStringFixup_P6C, which also supports Unix path
                           strings, this function substitutes a call into the
                           Lightweight Shell API.

                        2) This function is implemented as both ANSI and Unicode
                           versions.

                        3) Variable m_hProcHeap is marked extern to instruct the
                           linkage editor to map its address to the real
                           m_hProcHeap in the same compilation unit as DllMain,
                           which is expected to initialize it when Windows calls
                           it with dwReason = DLL_PROCESS_ATTACH.

                        4) After a tad of consideration, I decided that a
                           preemptive call to SetLastError is unnecessary,
                           because the caller won't call GetLastError unless we
                           return an empty string, and we call SetLastError just
                           before we return the empty string.

                        5) The Windows API interface is exported, and this
                           function is used internally, but it is not exposed
                           through the WinBatch interface, because it adds no
                           value to WIL, which has a native function, DirGet(),
                           which does pretty much the same thing. To get exactly
                           the same result, pass the string returned by DirGet()
                           to PathStringFixupP6C.

    Created:    Sunday, 26 April 2009

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version     Author Synopsis
    ---------- ----------- ------ ----------------------------------------------
    2009/04/27 1, 0, 0, 15 DAG    First working version.
    2011/06/05 1, 1, 1, 16 DAG    Moved to its new home, outside WWWILMuscle.
    ----------------------------------------------------------------------------
*/

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetCWDA_P6C
(
    PATHSTRINGFIXUP_HOW_P6C pAddOrRemove
) ;

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetCWDW_P6C
(
    PATHSTRINGFIXUP_HOW_P6C pAddOrRemove
) ;

#ifdef UNICODE
    #define GetCWD_P6C  GetCWDW_P6C
#else
    #define GetCWD_P6C  GetCWDA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ----------------------------------------------------------------------------

    Function Name:      GetDLLModuleName_WW

    Function Synopsis:  Get the fully qualified name of a specified DLL.

    In:                 phInstThisDLL [in]  = Instance handle for the DLL for
                                              which to retrieve the fully
                                              qualified name of the file from
                                              which it was loaded. See Remarks.

    Out:                If the function succeeds, the return value is a pointer
                        to a null terminated string that contains the fully
                        qualified name of the file from which the DLL whose
                        instance handle was supplied was loaded. See Remarks.

    Remarks:            Argument phInstThisDLL is the HINSTANCE of the DLL or
                        EXE for which the name of the file from which it was
                        loaded is desired.

                        1)  In the case of a graphical Windows program, this is
                            one of the arguments passed to its WinMain routine.

                        2)  In the case of an executable dynamic-link library,
                            this is one of the arguments passed to its DllMain
                            routine.

                        3)  In the case of a DLL that is loaded via LoadLibrary,
                            the routine that loads it gets its instance handle
                            as the return value from LoadLibrary. This is true
                            even if the library is loaded in data mode.

                        4)  Finally, although a console mode program has no
                            instance handle, any function that takes one treats
                            a NULL as a reference to the first program file that
                            was loaded into the process (the program file that
                            exports the standard Main ( argc, argv[] ) routine.

                        The returned string is a long pointer to a precisely
                        sized buffer that contains a null terminated string. The
                        buffer is allocated from the main process heap, and can
                        be discarded by passing its address to HeapFree().

                        This function tightly wraps Windows API function
                        GetModuleFileName, providing it with a sufficiently big
                        buffer, which it shrinks to exactly fit the returned
                        string.

    Author:             David A. Gray

    Date Created:       Monday, 06 February 2012

    ----------------------------------------------------------------------------
*/

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetDLLModuleNameA_WW
(
    HINSTANCE phInstThisDLL
) ;

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetDLLModuleNameW_WW
(
    HINSTANCE phInstThisDLL
) ;

#ifdef UNICODE
    #define GetDLLModuleName_WW  GetDLLModuleNameW_WW
#else
    #define GetDLLModuleName_WW  GetDLLModuleNameA_WW
#endif  /*  #ifdef UNICODE */

/*
    ----------------------------------------------------------------------------

    Function Name:      GetProgramFQFN_P6C

    Defining Source:    GetProgramFQFNA_P6C.C   - ANSI implementation
                        GetProgramFQFNW_P6C.C   - Unicode implementation
                        GetProgramFQFN_P6C.INL  - Body of both of the above

    Synopsis:           Return the module name, returned by GetModuleFileName()
                        and stored in static module variable md_lpModulleFQFN,
                        by companion function, GetVersionInfo_P6C(), which uses
                        it to extract the version resources from the calling
                        program file.

    Arguments:          None

    Returns:            Address of md_lpModuleFQFN, which points to a block of
                        memory that contains the fully qualified name of the
                        module file.

    Remarks:            None

    References:         None

    Date Written:       Tuesday, 17 November 2009.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2009/11/19  DAG First working version.
    ----------------------------------------------------------------------------
*/

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetProgramFQFNA_P6C ( void ) ;

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetProgramFQFNW_P6C ( void ) ;

#ifdef UNICODE
    #define GetProgramFQFN_P6C      GetProgramFQFNW_P6C
#else
    #define GetProgramFQFN_P6C      GetProgramFQFNA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ----------------------------------------------------------------------------

    Function Name:      GetProgramUQFN_P6C

    Defining Source:    GetProgramUQFNA_P6C.C   - ANSI implementation
                        GetProgramUQFNW_P6C.C   - Unicode implementation

    Synopsis:           Return the unqualified file name from the module name
                        string returned by GetModuleFileName() and stored in
                        static module variable md_lpModulleFQFN by companion
                        function, GetVersionInfo_P6C(), which uses it to extract
                        the version resources from the calling program's file.

    Arguments:          None

    Returns:            Address of a precisely sized buffer that contains the
                        unqualified name of the program (module) file.

    Remarks:            None

    References:         None

    Date Written:       Tuesday, 17 November 2009.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2009/11/19 DAG First working version.
    ----------------------------------------------------------------------------
*/

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetProgramUQFNA_P6C ( void ) ;

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetProgramUQFNW_P6C ( void ) ;

#ifdef UNICODE
    #define GetProgramUQFN_P6C      GetProgramUQFNW_P6C
#else
    #define GetProgramUQFN_P6C      GetProgramUQFNA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ----------------------------------------------------------------------------

    Function Name:      GetProgramDir_P6C

    Defining Source:    GetProgramDirA_P6C.C    - ANSI implementation
                        GetProgramDirW_P6C.C    - Unicode implementation
                        GetProgramDir_P6C.INL   - Body of both of the above

    Synopsis:           Return the path (directory) from the module name string
                        returned by GetModuleFileName() and stored in static
                        module variable md_lpModulleFQFN by companion function,
                        GetVersionInfo_P6C(), which uses it to extract the
                        version resources from the calling program's file.

    Arguments:          PATHSTRINGFIXUP_HOW_P6C penmBackslashYorN - This member
                        of the  PATHSTRINGFIXUP_HOW_P6C enumeration determines
                        whether the returned string has a terminal backslash.

                            Name                        Value   Interpretation
                            --------------------------  -----   --------------
                            PATHSTRINGFIXUP_INVALID     0       Append a /
                            PATHSTRINGFIXUP_ADD_P6C     1       Append a /
                            PATHSTRINGFIXUP_REMOVE_P6C  2       Omit a /

                        If penmBackslashYorN has an invalid value, a backslash
                        is appended, because it is computationally cheaper to
                        trim an unwanted backslash than to append one.

    Returns:            Address of a precisely sized buffer that contains the
                        fully qualified name of the program (module) directory.

    Remarks:            None

    References:         None

    Date Written:       Tuesday, 17 November 2009.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       By  Synopsis
    ---------- --- -------------------------------------------------------------
    2009/11/19 DAG First working version.
    2012/05/27 DAG Correct coding errors that got missed in initial work.
    ----------------------------------------------------------------------------
*/

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetProgramDirA_P6C
(
    PATHSTRINGFIXUP_HOW_P6C penmBackslashYorN
) ;

LPTSTR LIBSPEC_WWKERNELLIBWRAPPER_API GetProgramDirW_P6C
(
    PATHSTRINGFIXUP_HOW_P6C penmBackslashYorN
) ;

#ifdef UNICODE
    #define GetProgramDir_P6C      GetProgramDirW_P6C
#else
    #define GetProgramDir_P6C      GetProgramDirA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ----------------------------------------------------------------------------

    Function Name:      GetOsVersionInfo

    Defined In File:    GetOsVersionInfo.CPP

    Synopsis:           Return the TRUE Windows version.

    Status:             This routine has been tested on Windows 7. Based on the
                        outcome of those tests, I anticipate that it will also
                        work correctly on all subsequent versions of Windows.

    In:                 pk_OsVer    = Pointer to a RTL_OSVERSIONINFOEXW data
                                      structure, which the caller is expected to
                                      allocate, though not fill, initialize.

    Out:                TRUE if the function succeeds in filling in the fields
                        of the RTL_OSVERSIONINFOEXW data structure.
                        FALSE if RTL_OSVERSIONINFOEXW cannot be filled, or is a
                        null reference.

    Remarks:            The szCSDVersion member of the RTL_OSVERSIONINFOW
                        structure is an array of 128 WCHARs. RtlGetVersion fills
                        it with a null terminated string of WIDE characters. If
                        you try to read it as a string of ANSI characters, you
                        will get only the first character on a Latin-1 system.

                        This routine makes no assumptions about the contents of
                        the RTL_OSVERSIONINFOW structure, and zero fills it
                        before using it.

                        This function uses a DDK function, RtlGetVersion,
                        exported from ntdll.dll, (documented as coming from
                        ntoskernel.dll, listed in import library ntoskernel.dll,
                        and declared in Ntddk.h, by ordinal only, to return the
                        true Windows version, even on Windows 10.

                        The MSDN document listed as the second reference says
                        the following about it.

                            RtlGetVersion is the kernel-mode equivalent of the
                            user-mode GetVersionEx function in the Windows SDK.
                            See the example in the Windows SDK that shows how to
                            get the system version.

                        The table of requirements in the same document states
                        that it has been available starting with Windows 2000.

                        While the RTL_OSVERSIONINFOEXW structure is defined in
                        winnt.h, RtlGetVersion is not defined in any public
                        header, apart from ntddk.h, which ships only as part of
                        the Windows Driver Development Kit.

    Reference:          1) "Part 1: Overcoming Windows 8.1's deprecation of GetVersionEx and GetVersion APIs"
                           Ehsan A Samani, 06 November 2013
                           http://www.codeproject.com/Articles/678606/Part-Overcoming-Windows-s-deprecation-of-GetVe

                        2) RtlGetVersion routine
                           https://msdn.microsoft.com/en-us/library/windows/hardware/ff561910(v=vs.85).aspx

                        3) RTL_OSVERSIONINFOW structure
                           https://msdn.microsoft.com/en-us/library/windows/hardware/ff563624(v=vs.85).aspx

                        4) RTL_OSVERSIONINFOEXW structure
                           https://msdn.microsoft.com/en-us/library/windows/hardware/ff563620(v=vs.85).aspx

                        5) RtlVerifyVersionInfo routine
                           https://msdn.microsoft.com/en-us/library/windows/hardware/ff563026(v=vs.85).aspx

    ----------------------------------------------------------------------------
*/

BOOL LIBSPEC_WWKERNELLIBWRAPPER_API     GetOsVersionInfo
(
    RTL_OSVERSIONINFOEXW* pk_OsVer
) ;


/*
    ----------------------------------------------------------------------------

    Function Name:      IsBufFromHeap_WW

    Defined In File:    IsBufFromHeap_WW.C

    Synopsis:           Determine whether a pointer belongs to a specified heap.

    Status:             Beginning with version 1, 9, 0, 4, this function is no
                        longer used internally, and external use is deprecated.
                        Please see the Remarks for an explanation of why this is
                        so.

    In:                 plpvBuf     = Pointer to buffer to test.

                        phHeap      = Handle to heap to be examined. If phHeap
                                      is NULL, get a handle to the process heap,
                                      and evaluate it.

    Out:                TRUE if buffer plpvBuf belongs to heap phHeap.
                        FALSE if buffer plpvBuf belongs to heap phHeap.

                        To be on the safe side, return FALSE if any exception
                        occurs. See Remarks.

    Remarks:            DEPRECATED: The original intent of this function was to
                        validate a heap pointer before treating it as such. The
                        behavior of the heap routines in Windows 7 makes this a
                        bad idea, because it runs the risk of raising avoidable
                        breakpoint exceptions, even in retail builds of the
                        calling code. Since HeapAlloc and HeapReAlloc fail with
                        a trappable exception, it seems more prudent to go ahead
                        and call them, and forgo the pointer sanity check.

                        Call this function before you attempt to treat any
                        pointer as a heap pointer (e. g., to free the associated
                        memory, or reallocate the associated buffer.

                        IMPORTANT:  Unless plpvBuf is the address of a memory
                                    block that was allocated from the default
                                    process heap, this routine generates the
                                    following message, when the routine runs in
                                    a debugger.

                                        User breakpoint called from code

                                    This message cannot be suppressed. However,
                                    when you acknowledge the message box, your
                                    code continues to execute normally.

                                    Prior to Windows Vista, outside a debugger,
                                    there was no outward sign of this exception,
                                    and the code behaves as expected.

                                    However, newer versions of Windows ALWAYS
                                    raise a first-chance exception, and invoke
                                    Watson, when this routine is called with an
                                    invalid address.

    ----------------------------------------------------------------------------
*/

BOOL LIBSPEC_WWKERNELLIBWRAPPER_API IsBufFromHeap_WW
(
    LPVOID plpvBuf ,
    HANDLE phHeap
) ;


/*
    ----------------------------------------------------------------------------

    Function Name:      LeakTest_WW

    Synopsis:           Compare two pointers, and discard the memory to which
                        the second points, if the two addresses differ.

    Out:                plpInput                = Void pointer to a location,
                                                  such as an input buffer passed
                                                  into a function for
                                                  transformation. See Remarks.

                        plpOutput               = Void pointer to a location,
                                                  such as the pointer returned
                                                  by a transformation function.
                                                  See Remarks.

    Out:                TRUE if memory was discarded, FALSE otherwise

    Remarks:            Suppose that a buffer, plpInput, is passed to a function
                        that is expected to either transform the contents of the
                        buffer at the location to which it points, and return a
                        pointer to the transformed copy, transform the data in
                        place, and return a pointer to the same location, or
                        simply return a copy of the input pointer, leaving the
                        data to which it points unchanged.

                        The algorithm which the function implements determines
                        which of the three courses of action takes place for any
                        given buffer, and the outcome is unknown, a priori, by
                        the caller.

                        To avoid leaking memory, when the caller is finished
                        with the returned data, if the transformation function
                        copied the data into a new buffer for transformation,
                        the caller must discard the buffer.

                        To transparently manage this, LeakTest_WW implements the
                        following algorithm.

                        1)  If the output pointer, plpOutput is NULL, return
                            without taking any action, since the transformation
                            function returned an invalid pointer.

                        2)  If pointers plpInput and plpOutput are equal, both
                            point to the same memory.

                            Unless plpInput points to memory allocated by the
                            calling routine, it cannot,and should not, discard
                            the memory to which IT points. That decision is the
                            caller's responsibility, and is out of scope.

                        3)  If pointers plpInput and plpOutput are unequal, then
                            plpOutput points to memory allocated by the trans-
                            formation routine, which must be discarded.

                        4)  As a final sanity check, call HeapSize on plpOutput.
                            Unless HeapSize returns -1, call HeapFree to discard
                            the memory to which plpOutput points.

                        5)  If HeapSize returns -1, return FALSE after passing
                            OUTPUT_PTR_IS_INVALID_WW to SetLastError.

    Assumptions:        1)  Pointer plpOutput, if its value differs from that of
                            plpInput, is assumed to point to memory allocated
                            from the default process heap.

                        2)  If the function returns FALSE, and GetLastError
                            returns OUTPUT_PTR_IS_INVALID_WW, the only safe
                            assumptions that can be made are as follows.

                            a)  Pointers plpOutput and plpInput refer to
                                different memory locations.

                            b)  The memory at location plpOutput wasn't
                                allocated from the default process heap.

                            There could still be a memory leak, if the transform
                            routine allocates its memory from a different pool,
                            such as a private heap or the global heap.

                        2)  Variable m_hDfltHeap is expected to contain a handle
                            to the default process heap. (Another routine that
                            can see m_hDfltHeap is expected to have initialized
                            it.)

                        3)  Since both pointers are cast as LPVOID, they may be
                            used to process pointers to anything, even Unicode
                            text.

    Date Written:       Friday, 05 November 2010

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Author Synopsis
    ---------- ------ ----------------------------------------------------------
    2010/11/05 DAG    First working version.
    2012/07/15 DAG    Move LeakTest_WW from P6CUtilLib1 to WWKernelLibWrapper.
    ----------------------------------------------------------------------------
*/

BOOL LIBSPEC_WWKERNELLIBWRAPPER_API LeakTest_WW
(
    LPVOID plpInput ,
    LPVOID plpOutput
) ;

#if defined ( __cplusplus )
}
#endif  /* __cplusplus */
#endif  /* #if! defined ( _WWKERNELLIBWRAPPER_DEFINED ) */