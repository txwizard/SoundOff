#if !defined ( _P6CSTRINGLIB1_DEFINED )
#define _P6CSTRINGLIB1_DEFINED

/*
    ============================================================================

    Name:               P6CStringLib1.H

    Library:            P6CStringLib1.dll (P6CStringLib1.lib)

    Synopsis:           This is the header file for a standard string library,
                        P6CStringLib1.DLL, in which all external functions are
                        declared directly or in included headers.

    Configuration:      Pending application of special flags to the assorted
                        assembler modules, the structured exception handlers in
                        it cannot be marked as safe.

    Dependencies:       Projects that include this header and its library depend
                        on following additional private libraries.

                        Link Library            Dynamic Link Library    Header
                        ----------------------  ----------------------  --------------------
                        WWKernelLibWrapper.lib  WWKernelLibWrapper.dll  WWKernelLibWrapper.H
                        --------------------------------------------------------------------

                        Calling programs need not include the library header
                        listed above.  It is listed for two reasons.

                        1)  It declares Function FreeDfltHeapBuf_P6C, which you
                            should use to release the string buffers returned by
                            all of these functions.

                        2)  It declares other useful utility functions.

                        Since this library is linked against MSVCRT.lib, it is
                        also dependent upon it. By linking against and using
                        MSVCRT.dll, any security issues found and fixed in it
                        will be incorporated into any project that links to this
                        library.

    Remarks:            Since the local storage used by these functions is
                        allocated on the stack, and the functions that use the
                        PrintF family of functions use the multi-threaded version
                        of the CRT library, I believe they are thread-safe.
                        However, since I have not tested them in a multi-threaded
                        application, I cannot guarantee them to be so.

                        Functions Returning LPTSTRs
                        ---------------------------

                        All functions that return long pointers to strings
                        (LPTSTR) allocate memory to hold the strings from the
                        process heap.  The memory can be subsequently freed in
                        one of four ways.

                        1)  Call FreeDfltHeapBuf_P6C, which happens to be one of
                            the functions exported by WWKernelLibWrapper.dll.
                            C programmers may consult CopyStringToNewBuf_P6C.H
                            for its prototype, and should include this header,
                            as you include windows.h to avail yourself of the
                            functions in winbase.h.

                        2)  Call the Windows API HeapFree function directly,
                            passing the pointer, along with a handle to your
                            default process heap.

                        3)  Call macro FreeProcHeapMem_WW, which is defined in header
                            TcharMacros_WW.H, and expects an externally linked
                            variable named m_hProcHeap, which is of type HANDLE.

                        4)  Call macro FreeBuffer_WW, which is defined in header
                            TcharMacros_WW.H, and expects an externally linked
                            variable named m_hProcHeap, which is of type HANDLE.

                            However, if preprocessor symbol _HMAC_SHAX_MALLOC or
                            _MALLOC_AS_MEMORY_ALLOCATOR is defined, it calls
                            routine free, in the Standard C Runtime Library, and
                            expects a pointer to memory that was allocated by
                            malloc, realloc, or calloc, all of which also belong
                            to the Standard C Runtime Library.

                        The first method incurs slightly more overhead, because
                        it adds another frame to the call stack, and consumes
                        another small chunk of your stack, but it permits any
                        program that can call this library to discard the memory
                        with just one more call, rather than up to two calls to
                        the Windows API to use the second method.

                        Except as noted above, the third and fourth methods
                        generate code that expands into calls that implement the
                        second method.

                        Combined with symbol _MALLOC_AS_MEMORY_ALLOCATOR and the
                        companion macros listed in the table below cover many
                        use cases, using CRT functions from the malloc family.

                        --------------------------------------------------------
                        Name of Macro   Action Performed by Macro Code
                        --------------- ----------------------------------------
                        AllocBytes_WW   Allocate pCount bytes of memory.

                        AllocCString_WW Allocate enough memory to hold a
                                        null terminated string (a. k. a., a
                                        C string) of pCount characters, null
                                        character and all.

                        AllocTchars_WW  Allocate enough memory to hold pCount
                                        characters.
                        --------------------------------------------------------

                        If you keep a handle to the default process heap handy
                        at all times, as I usually do, any of these methods
                        requires just one call, giving the second, third, and
                        fourth methods a slight performance edge.

                        Efficient Dynamic Linking
                        -------------------------

                        This library selectively applies the following scheme,
                        which is intended to enable the compiler to substitute a
                        call to the address in the Import Address Table for a
                        call to that address, followed by a jump instruction.

                          #ifdef _BUILDING_uniqueheadername   //------4------+    |
                            #define LIBSPEC __declspec(dllexport)         // |    |
                          #else                                           // |    |
                            #define LIBSPEC __declspec(dllimport)         // |    |
                          #endif // _BUILDING_uniqueheadername   //---4------+    |

                        Note: The symbolic names have been changed from those
                              shown in the article from which the above example is
                              taken.

                        A few routines are intentionally excluded from the above
                        scenario.

                        1)  All of the Visual Basic wrapper routines, which have
                            names that end in "_VB," use __stdcall, because the
                            VBA runtime library chokes on __declspec(dllimport).

                        2)  The handful of routines that are written entirely in
                            assembly language use __stdcall, matching the
                            calling convention specified in the prologue
                            generated by the Microsoft Macro Assembler, version
                            6.11.

                        CreateGUIDString, added Sunday, 10 January 2016, takes
                        advantage of a recent discovery to implement __stdcall
                        for stack frame management. I refrained from a wholesale
                        update, because doing so would require virtually every
                        program in my library to be compiled and linked.

                        See reference 1.

    References:         1)  "The Ultimate (DLL) Header File, Joseph M. Newcomer
                            http://www.flounder.com/ultimateheaderfile.htm

    Author:             David A. Gray

    Created:            Wednesday, 07 September 2005

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

    Date       Version  Author Synopsis
    ---------- -------- ------ ----------------------------------------------
    2005/09/08 1,0,0,0  DAG    First working version.

    2005/12/11 1,0,1,1  DAG    Add a bunch of new functions and reorganize this
                               header along the lines of the Windows SDK header
                               files, based on lessons learned since I created
                               my first library prototype headers.

    2005/12/23 Private  DAG    Rename AdvanceToNextToken_P6C to
                               GetTokeyByIndex_P6C, to more accurately
                               reflect its algorithm and application, in the
                               course of making the Unicode version work
                               correctly.

    2007/11/08 Private  DAG    Incorporate GetBom_P6C and its like named
                               header, GetBom_P6C.H, so that we can pull it
                               into a DLL, in addition to keeping the
                               original in a static link library.

    2009/12/07 Private  DAG    1) Incorporate CopyStringToNewBuf_P6C and its
                                  like named header CopyStringToNewBuf_P6C.H,
                                  so that we can pull it into a DLL,

                               2) Move the symbolic constants and includes
                                  outside the scope of the extern "C" block.
                                  Now that I understand what extern "C" does,
                                  I know that they belong outside it.

                               3) Modernize and simplify the documentation.

                               4) Change all functions that use the process
                                  heap to share a single handle, through an
                                  externally linked symbol.

                               5) Change StrReplace_P6C so that it calls
                                  SetLastError for all exceptions not already
                                  reported by the Windows API.

                               6) Change the StrIndex* functions to return
                                  their results directly, rather than through
                                  a variable whose sole purpose is to hold
                                  them until the next instruction returns
                                  them, by placing them in the standard
                                  return register, EAX. This should ensure
                                  that the compiler optimizes away the
                                  scratch variable, and uses a bare minimum of
                                  space on the stack frame.

                                7) Change the StrIndexI* functions to copy
                                   their arguments into local storage, since
                                   the CharLower function converts in place,
                                   and corrupting the caller's memory is bad
                                   practice, not to mention unsafe.

                                8) Fix memory leaks caused by neglecting to
                                   to free local buffers used by all three VB
                                   wrapper functions.

    2010/02/27 1,0,2,1  DAG    Add functions declared in GetMyResource_WW.H,
                               as follows.

                                      GetAnyResource_WW     = Get the resource
                                                              from any PE file,
                                                              given its instance
                                                              handle.

                                      GetConsoleResource_WW = Get the resource
                                                              from a PE that
                                                              runs in console,
                                                              or character,
                                                              mode. Console
                                                              programs possess
                                                              no instance
                                                              handle.

                                      GetDLLResource_WW     = Get the resource
                                                              from PE that was
                                                              loaded as a
                                                              dynamic link
                                                              library. This
                                                              entry point is
                                                              useful only when
                                                              the module in
                                                              which it is
                                                              defined is
                                                              statically
                                                              linked into the
                                                              DLL from which
                                                              it is called.

                                  Object code of the above functions is stored
                                  in static link library P6CLIB1, where they
                                  shall remain, so that they can also be pulled
                                  into programs that I want to make self
                                  contained.

    2010/03/08 Private  DAG    1) Replace ShrinkBufToFitASCIIZAnyHeapP6C
                                  with ShrinkBufToFitASCIIZString, a much
                                  more straightforward macro.

                               2) Prefix the second and third arguments to
                                  StrReplace_P6C with a lower case "p" so
                                  that their names follow the Reddick-Gray
                                  Naming Convention for function parameters.

                               3) Follow calls to ShrinkBufToFitASCIIZString
                                  with calls to SetLastError, setting a
                                  status code of P6STRINGLIB_MALLOC_ERR_P6C,
                                  if ShrinkBufToFitASCIIZString returns NULL,
                                  because two of its three embedded functions,
                                  HeapReAlloc and _tcslen, don't call
                                  SetLastError.

                               4) Replace hard coded constants with symbolics
                                  defined in CommonConstants_P6C.H.

                               5) Add #pragma once above CommonConstants_P6C.H
                                  and below #define _P6CSTRINGLIB1_DEFINED.

    2010/03/11 2,1,4,0  DAG    1) Incorporate ANSIStrToBSTR_P6C.H by #include.

                                  With the addition of ANSIStrToBSTR_P6C.H,
                                  this header covers, directly or indirectly,
                                  every entry point in P6CStringLib1.DEF.

                               2) Change name of function GetTokeyByIndex, a
                                  typographical error, to GetTokenByIndex.

                                  Although this is a breaking change, I have
                                  identified only a handful of affected
                                  programs, one of which, 2007TXFIX.C, was
                                  retired in 2008. The rest are functions
                                  exported by two other libraries, both
                                  scheduled for updates in the next few
                                  weeks, and internal test programs.

                                  Since P6CStringLib1, which is unpublished,
                                  is the only library that exports them, that
                                  should be the end of it.

                               3) Find and fix the I18N error, which affected
                                  the ANSI version of GetTokenByIndex_P6C,
                                  GetTokenByIndexA_P6C, which, incorrectly,
                                  defined the UNICODE preprocessor variable,
                                  causing calls to string functions to
                                  resolve to their Unicode entry points. This
                                  ran the risk of scanning past the end of
                                  the list in search of a terminal NULL.

                                  In extreme cases, this error could have led
                                  to a memory read access violation, if the
                                  scan reached the highest address in the
                                  process address space.

                                  The security ramifications depend on what
                                  is done with the returned pointer. If a
                                  caller uses it to modify data, the
                                  potential exists for a classic RCE (Remote
                                  Code Execution) vulnerability.

                                  Fortunately, this function has never been
                                  published, and the only applications that I
                                  have made of it involved reading data from
                                  a list.

                               4) In testing the correction of the previous
                                  item, I discovered a related bug that could
                                  have precisely the same effect, if a caller
                                  requests an index beyond the upper bound of
                                  the token array.

    2010/04/26 2,2,5,0  DAG    Reinstate direct inclusion of windows.h, since
                               CommonConstants_P6C.H finally works just fine
                               without it.

    2010/06/04 2,2,6,0  DAG    Move the #pragma once preprocessor directive
                               outside the scope of the preprocessor variable
                               which performs the same function for other C
                               compilers.

    2010/09/27 2,2,7,0  DAG    1) Synchronize version numbers with the values
                                  stored in the version resource file.

                               2) Add the following existing routines, all of
                                  which were, heretofore, statically linked into
                                  every program that needed one or more of them.

                                      EM_ShowMsgOnConsoleA_WW
                                      EM_ShowMsgOnConsoleW_WW
                                      EM_FormatMsgForMsgboxW_WW
                                      EM_FormatMsgForMsgboxA_WW

                               2) Incorporate header FormatMsgs_WW.H by include.

    2011/06/07 2,3,8,0  DAG    1) Increment version to 2,3,8,0, to cover the
                                  following additions to the list of exported
                                  functions, all of which were moved here from
                                  WWWILMuscle, to resolve an external symbol
                                  reference without creating a linkage loop.

                                      ----------------------------------------
                                      Name                            Ordinal
                                      ---------------------           --------
                                      MakeFQFNWP6C                    Auto
                                      PathStringFixup_P6C             Auto
                                      QuoteStringP6C                  Auto
                                      ----------------------------------------

                               2) Move #pragma once above inside the #ifndef
                                  _P6CSTRINGLIB1_DEFINED block, and move this
                                  comment block inside it.

    2011/09/05 2,3,9,0  DAG    1) Substitute a name, unique to this header, for
                                  LIBSPEC, to prevent symbolic name collisions.
                                  This is the approach implemented by the Visual
                                  C++ 6.0 AppWizard.

                                  The name used in this header is
                                  LIBSPEC_P6CSTRINGLIB1_API.

                               2) Correct a copy truncation error in the Unicode
                                  implementation of PathStringFixup_P6C, and
                                  move the code of both implementations into an
                                  inline #include file, PathStringFixupP6C.INL.

    2011/09/23 2,3,10,0 DAG    1) On error, set the variable that holds the
                                  return value, rlpMyString, to NULL. As it was,
                                  rlpMyString held the pointer returned by
                                  HeapAlloc, which is invalidated when the
                                  function fails. This change affects all six
                                  functions declared in GetMyResource_WW.H.

                               2) The six functions are three variations on the
                                  same theme, differing only with respect to two
                                  properties.

                                  A) The character set of the returned string is
                                     either ANSI or Unicode.

                                  B) The instance handle used to retrieve the
                                     resource strings.

                                  This leads to two simplifications of the code
                                  base.

                                  A) Two of the three cases can be implemented
                                     as wrappers around the third, which takes a
                                     HINSTANCE, which may have one of three
                                     things.

                                     a) The general case is that its value comes
                                        from the caller, which may obtain it by
                                        any number of methods.

                                     b) One of two special cases is that the
                                        wrapper function supplies the HINSTANCE
                                        of the containing Windows program or DLL
                                        by passing its own instance handle. This
                                        assumes that the entry point routine
                                        (DLLMain for a DLL, or WinMain for a
                                        standard graphical Windows program)
                                        saves its instance handle at an address
                                        that is marked with the extern storage
                                        class.

                                     c) The other special case is that of a
                                        console mode (character mode) program,
                                        which has no instance handle, and is
                                        expected to pass NULL for its instance
                                        handle.

                                  B) Since the code for the two character sets
                                     is identical, except for the character set
                                     mappings, all of which are eliminated at
                                     the source code level by means of TCHAR.H
                                     and preprocessor mappings, the ANSI and
                                     Unicode implementations of the most generic
                                     version of the routines can be collapsed to
                                     a single inline header (.INL) file.

                                  The impact of these changes is that all six of
                                  the routines are condensed into a single block
                                  of source code.

                               3) To maintain consistency with the underlying
                                  LoadString API call, the resource IDs are now
                                  unsigned integers.\

                                  This change will prompt a signed/unsigned
                                  mismatch WARNING the next time any code that
                                  imports these functions is compiled. However,
                                  fixing this mismatch is not strictly necessary
                                  because the code will work regardless, because
                                  a negative number will be seen as a huge
                                  string ID, which will be caught and reported.

                               4) Substitute APPLICATION_ERROR_MASK, which is
                                  defined in WinNT.H, for CUSTOMER_FLAG.

    2011/09/28 2,3,10,1 DAG    This revision is confined to the header, since
                               the revision is confined entirely to defining
                               four new macros.

                               Define macros to return the first or last
                               character of a string, or the position (array
                               subscript) of its last character.

                                      PosLastCharOfString
                                      FirstCharOfString
                                      LastCharOfStringKnownLen    Known length
                                      LastCharOfStringUnKnownLen  Unknown length

    2011/10/02 2,4,0,0  DAG    1) Incorporate header BinToHex_WW.H, to include
                                  both (ANSI and Unicode) implementations of
                                  function BinToHex_WW, which is defined in
                                  static library P6CLib1.

                               2) Make error messages unique throughout the
                                  routines exported by this library, with the
                                  exception of P6STRINGLIB_MALLOC_ERR_P6C, which
                                  is used throughout.

                                  So that I wouldn't need to visit each routine,
                                  the existing symbolic error codes were mapped
                                  to P6STRINGLIB_MALLOC_ERR_P6C in the header in
                                  which each routine is declared.

                                  In the course of completing this task, the old
                                  CUSTOMER_FLAG symbol has been completely
                                  replaced by APPLICATION_ERROR_MASK, the symbol
                                  defined in WinNT.h that I felt certain had to
                                  exist.

    2011/10/11 2,4,1,0  DAG    Swap the last two arguments of BinToHex_WW, so
                               that they occur in their order of importance and
                               probable use. Strictly speaking, only 3 source
                               files are affected:

                                    1) BinToHex_WW.H
                                    2) BinToHexA_WW.C
                                    3) BinToHexW_WW.C

    2011/10/27 2,4,2,0  DAG    Add CmdArgs_P6C.H, and add the functions declared
                               in it to the list of functions exported by
                               P6CStringLib1.dll, and linked through its link
                               library, P6CStringLib1.lib.

    2012/05/17 2,5,3,0  DAG    Add new functions and hearers.

                               A) New Functions:

                                  1) CmdArgSwitches (ANSI and Unicode) (P6CLib1)
                                  2) LoadStringErrNoSuchString_P6C (P6CLib1)
                                  3) SafeAppendStrToBuff_WW (ANSI and Unicode)
                                  4) ShowAddress_WW (ANSI and Unicode)
                                  5) strEscape_P6C (ANSI and Unicode)

                               B) New Headers:

                                  1) CmdArgs_P6C.H
                                  2) LoadStringErrNoSuchString_P6C.H
                                  3) ShowAddress_WW.H.
                                  4) strEscape_P6C.H

                               C) All function prototypes are now complete. Each
                                  argument name is listed along with its type,
                                  and the arguments are visually arranged as
                                  lists.

                               D) Move CopyStringToNewBuf_P6C and its like named
                                  header, CopyStringToNewBuf_P6C.H, to utility
                                  library WWKernelLibWrapper.dll. Since this
                                  library links to WWKernelLibWrapper.dll for
                                  other routines, it adds no overhead, makes
                                  CopyStringToNewBuf_P6C available separately,
                                  and puts a pair of related primitive memory
                                  management routines in the same DLL.

                               E) Fix I18N off-by-one errors in StrIndex_P6C and
                                  StrIndexIW_P6C, and more serious I18N errors
                                  in StrReplaceW_P6C.

                               F) Move strEscape_VB_P6C from P6CUtilLib1.

                                  The ANSI and Unicode functions that return C
                                  strings are already in this library, and they
                                  have been removed from P6CUtilLib1.

                               G) Move strCopyCStrToBstr_P6C from P6CUtilLib1.

    2012/06/30 2,6,4,0  DAG    Applying a lesson learned while developing
                               version 1,7,0,0 of P6VersionInfo.dll, change the
                               calling convention of the VB/VBA wrapper routines
                               from LIBSPEC_P6CSTRINGLIB1_API,
                               __declspec(dllimport) to the outside world, to
                               __stdcall. Apparently, there is a subtle
                               difference between the two that causes problems
                               with returning results to a calling VBA routine.

                               In ANSIStrToBSTR_P6C and ANSIStrToWCSTR_P6C,
                               preserve LastError set by caller, to cover cases
                               in which an empty string is being returned to a
                               caller through COM or the external DLL interface
                               of a Visual Basic Runtime to signal an error.
                               This change resolves a potential issue in which a
                               routine in the runtime library resets it before a
                               calling VBA routine gets a chance to check it.

    2012/07/02 2,7,5,0  DAG    1) Export function GetItemFromArray_WW, declared
                                  in GetItemFromArray_WW.H, which is already
                                  used internally.

                               2) Apply an optimization discovered in the course
                                  of a debug session, to SaveCmdArgPvtA_P6C and
                                  SaveCmdArgPvtW_P6C, defined in CmdArgsA_P6C.C
                                  and CmdArgsW_P6C.C, respectively. For complete
                                  details, please see inline include file
                                  SaveCmdArgPvt_P6C.INL, where the optimized
                                  code and an accompanying note.

    2012/07/02 2,7,6,0  DAG    Export function StoreAddressInArray_WW, declared
                               in StoreAddressInArray_WW.H.

    2012/07/12 2,7,7,0  DAG    Fix an off-by-one memory allocation error that
                               caused PathStringFixup_P6C to leave its returned
                               string unterminated (without its terminal NULL)
                               when it was called with plpPathString pointing to
                               a string that needs a terminal path delimiter, and
                               pAddOrRemove set to PATHSTRINGFIXUP_ADD_P6C. Both
                               implementations (ANSI and Unicode) are affected.

    2013/05/15 2,7,7,2  DAG    1) This build adds SafeStringCopy_WW, a new,
                                  safer replacement for memcpy, intended
                                  primarily for copying strings into the middle
                                  of a buffer. It is safer than raw memcpy,
                                  because it verifies that the buffer can
                                  accommodate the anticipated copy operation. If
                                  not, it attempts to enlarge the buffer,
                                  failing unless it succeeds.

                               2) This build links a new version of a private
                                  function, ParseCmdArgs_P6C, from P6CLib1. The
                                  new version addresses an issue that affects
                                  register usage by inline assembly. (You cannot
                                  assume that the EAX register still contains
                                  the value returned by the immediately
                                  preceding function, even when the next
                                  statement is the beginning of the inline
                                  assembly block.

                                  None of the routines defined in this library
                                  is directly affected. The affected routine is
                                  declared in CmdArgs_P6C.H and defined in
                                  CmdArgsA_P6C.C and CmdArgsW_P6C.C, both of
                                  which live in static library P6CLib1.lib, and
                                  are linked into the main DLL.

                               3) The ANSI and Unicode versions of StrLeft_P6C
                                  suffer from an off-by-one memory allocation
                                  error, which can lead to a corrupted heap,
                                  and, in lesser circumstances, throws an
                                  untrappable exception that attempts to force
                                  the process into a debugger.

                               4) The following functions erroneously tested the
                                  value returned by CRT routine memcpy,
                                  returning NULL, after calling SetLastError
                                  with a status of P6STRINGLIB_LSTRCPYN_ERR_P6C.
                                  Since memcpy always returns its first
                                  argument, this test would always return TRUE.

                                      StrLeft_P6C
                                      StrReplace_P6C
                                      StrRight_P6C

                                  Eliminating this test is a small optimization.

    2013/05/29 2,8,0,0  DAG    1) Declare a new function, IsSameExtension_WW.

                               2) Eliminate CommonConstants_P6C.H in favor of
                                  the much more focused Const_Typedefs_WW.H.

                               3) Replace macro ShrinkBufToFitASCIIZString with
                                  ShrinkBufToFitASCIIZAnyHeapP6C in function
                                  StrReplace_P6C, to gain a slight performance
                                  improvement, by using the process heap handle
                                  that the DLL maintains for use by all of its
                                  routines.

    2013/06/18 2,8,1,0  DAG    Eliminate an overlooked inclusion of header
                               CommonConstants_P6C.H in ANSIStrToBSTR_P6C.H, and
                               substitute Const_Typedefs_WW.H, which is plenty
                               for its public interface.

    2013/07/05 2,8,2,0  DAG    In function strCopyCStrToBstr_P6C, correct an
                               error that cased an access denied error when it
                               attempted to free a static block, as it is
                               designed to do when a block was allocated from
                               the default process heap. The original test
                               didn't work correctly with the DWORD returned by
                               the HeapSize function.

                               Since I had the routine open, I replaced memset
                               with RtlZeroMemory, to prevent the compiler from
                               optimizing away this security measure.

    2013/07/18 2,8,3,0  DAG    1) Declare a new function, IsSameBaseName_WW.

                               2) Define two new macros, StringIsNullOrEmptyWW
                                  and StringIsEmptyWW. IsSameBaseName_WW uses
                                  StringIsEmptyWW. At the expense of collapsing
                                  a distinction between a null pointer and a
                                  pointer to the empty string, it could have
                                  used StringIsNullOrEmptyWW, although doing so
                                  would save only the handful of machine
                                  instructions required to call SetLastError 4
                                  times instead of 2.

    2013/07/21 2,8,4,0  DAG    Declare a new function, PathReplaceExtension_WW,
                               which exposes a Lightweight Shell API function,
                               PathRenameExtension.

    2013/09/03 2,8,5,0  DAG    Correct internal errors in QuoteStringP6C.

    2013/09/09 2,8,5,1  DAG    1) Make QUOTESTRING_ACTION_P6C argument pAction a
                                  constant value, extending const protection to
                                  the only QuoteStringP6C argument not already
                                  so marked.

                                  Since the effect of this change is internal,
                                  the signature remains unchanged, and the
                                  change is transparent to callers.

                               2) QuoteStringP6C is fully implemented and
                                  tested, including the
                                  QUOTESTRING_ACTION_QUOTE_STRIP action, which
                                  had been a stub.

    2014/08/02 2,8,5,2  DAG    StrSub_P6C: Correct a math error that caused it
                               to crash with a memory access exception when two
                               of a substring were too close to each other.

    2014/08/02 2,8,5,2  DAG    P6CStringLib1.H ONLY: Include MathMacros_WW.H, so
                               that symbolic constants used in several macros
                               are defined even in the unlikely event that this
                               file is included in a unit that hasn't already
                               included MathMacros_WW.H, either directly or
                               indirectly.

                               MathMacros_WW.H arrives indirectly, through header
                               CharPosMacros_WW.H, which I created by moving the
                               macros that needed MathMacros_WW.H and adding the
                               SecondCharOfString macro. It was in the course of
                               relocating it from UniqueDENameGen\StdAfx.h that
                               I discovered that several of the relocated macros
                               depend upon constants defined in MathMacros_WW.H,
                               which is included via CommonConstants_P6C.H.

                               This change makes P6CStringLib1.H self
                               sufficient.

    2014/08/27 2,9,0,1  DAG    BinToHex_WW: Add a flag to specify which of two
                               tables to use, so that the library can generate
                               FIPS 180-2 compliant hexadecimal strings. Header
                               BinToHex_WW.H also got a good cosmetic cleaning
                               that corrects several typographical errors and
                               one argument that was named out of order in the
                               flower box.

                               I decided to incorporate TcharMacros_WW.H, so
                               that everything needed for string processing is
                               made visible through this header.

    2014/12/11 2,9,0,2  DAG    Incorporate FNReplacReservedChars.H into this
                               header, and the ANSI and Unicode implementations
                               of FNReplacReservedChars to the library.
                               Although Visual Studio builds a new library,
                               since it marks any source file that includes this
                               header as outdated, for all practical purposes a
                               link.

    2015/01/03 2,9,0,3  DAG    BinToHex_WW: Extend B2H_XLATE_TABLE with another
                               value that can be combined with the existing
                               value to allocate memory for the output buffer
                               via malloc, rather than HeapAlloc, so that my
                               Secure Hash Algorithm library can break free of a
                               direct dependency on the Windows Platform SDK.

    2015/01/15 2,9,0,4  DAG    StoreAddressInArray_WW Replace calling convention
                                                      APIENTRY with __stdcall.

                               GetItemFromArray_WW    Replace calling convention
                                                      APIENTRY with __stdcall.

                               FNReplacReservedChar   Replace calling convention
                                                      APIENTRY with __stdcall.

                               The foregoing changes are confined to headers and
                               the library .DEF and .RC files.

    2015/01/24 2,9,0,5  DAG    Since it is now formally dependent upon stdio.h,
                               TcharMacros_WW.H must go.

    2015/02/03 3,0,0,1  DAG    Add SplitStringSimple_WW, implemented as ANSI and
                               Unicode.

    2015/02/09 3,0,0,2  DAG    1) Decrease the buffer allocation for the general
                                  case of StrLeft_P6C to the length of the
                                  requested substring, rather than that of the
                                  input string. A request for a short substring
                                  from a long string requested a lot of memory
                                  that would probably never be used, since
                                  strings are usually treated as immutable
                                  objects.

                               2) Use macro StringIsNullOrEmptyWW to avoid an
                                  expensive call to _tcslen, which expends a log
                                  more effort to discover that its input string
                                  is empty.

                                  Apply this change to the following routines.

                                  - strEscape_P6C
                                  - StrLeft_P6C (This routine started it all.)
                                  - StrIndex_P6C
                                  - StrIndexI_P6C
                                  - StrRight_P6C
                                  - StrSub_P6C

                               3) Implement the more C-ish form of the tests for
                                  defined macros.

    2015/02/14 3,1,0,3  DAG    Add function StringCompareRobust.H, which wraps a
                               null reference guard around the CRT string
                               compare routines.

                               Declarations are in StringCompareRobust.H, which
                               is included below.

    2015/03/13 3.1.0.4  DAG    Segregate the substring functions into a new self
                               contained header, SubsStrings_WW.H.

                               Although nothing substantial changed, I built and
                               tested a new version of the library, to verify
                               that I didn't break anything.

    2015/08/19 3,2,0,4  DAG    Do the bare minimum to upgrade to Visual Studio
                               2013.

                               NOTE: I am deferring the issue of marking the DLL
                                     as comprised entirely of safe Structured
                                     Exception Handlers, because I need to find
                                     that note that I saw earlier today about
                                     marking assembler modules as safe for SEH.

    2015/10/06 3,2,0,5  DAG    Adapt GetBOM_P6C to use an enumeration in place
                               of the present dwBOMType member in the BOMINFOP6C
                               structure. Make the changes in such a way that
                               they are transparent to the outside world.

    2016/01/23 3,4,0,6  DAG    Add functions CreateGUIDString, defined in newish
                               header CreateGUIDString.H, so described because
                               it is an update of a very old header that was
                               never put into production.

                               Declare FormatIntAsHex, a small family of
                               functions that format integers of all sizes as
                               hexadecimal strings.

                               Define a new MoveBytes macro, which I needed for
                               CreateGUIDString, but decided to define here, for
                               use elsewhere.

                               Define SetBOM, a new function that appends blocks
                               of arbitrary bytes to a specified type of Byte
                               Order Mark (BOM).

                               This update also incorporates correction of many
                               long standing typographical errors, made much
                               more apparent by the spelling checker add-in that
                               I wish had existed long ago.

    2016/01/25 3,4,0,6  DAG    Define a new macro, HeapSizeInTCHARs, for use as
                               the buffer size argument with _stprintf_s and
                               LoadString, among others, that require a buffer
                               size, expressed in TCHARs, including room for the
                               terminal null character, when the buffer size is
                               unknown or may vary.

    2016/07/18 3,5,0,7 DAG     Integrate function FormatLongInt_P6C under a new,
                               shortened name. This is a function about which I
                               had all but forgotten, which was left in my old
                               WWWILMuscle44i library, which is effectively
                               deprecated, since I am no longer actively working
                               with WinBatch, and haven't done anything new in
                               that language for the last two years or so.

                               This routines incorporates GetLocaleInfoEx and is
                               compatible with all supported versions of Windows
                               as of its development date. That is to say, this
                               version is incompatible with Windows XP, but is
                               forward looking.
    ============================================================================
*/

#if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 )
    #pragma once
#endif  /* #if defined ( _MSC_VER ) && ( _MSC_VER >= 1020 ) */

#include <windows.h>

//  ----------------------------------------------------------------------------
//  Define custom typedefs used in function prototypes.
//  ----------------------------------------------------------------------------

#include <Const_Typedefs_WW.H>

//  ----------------------------------------------------------------------------
//  Define macros used in selected function declarations.
//
//  Note:   For this to work correctly, the module that defines a function must
//          define preprocessor constant _BUILDING_P6CSTRINGLIB1. Otherwise, the
//          wrong calling scheme, __declspec(dllimport), is generated.
//
//          There are no such special considerations for calling routines.
//  ----------------------------------------------------------------------------

#if defined ( _BUILDING_P6CSTRINGLIB1 )
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
#else   /* #if defined ( _BUILDING_P6CSTRINGLIB1 ) */
    #if defined ( _P6CSTRINGLIB1 )
        #define LIBSPEC_P6CSTRINGLIB1_API extern
    #else
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
    #endif  /* #if defined ( _P6CSTRINGLIB1 ) */

    //  ------------------------------------------------------------------------
    //  Omit StringCompareRobust.H if building the library.
    //  ------------------------------------------------------------------------

    #include <StringCompareRobust.H>
#endif  /* #if defined ( _BUILDING_P6CSTRINGLIB1 ) */

//  ----------------------------------------------------------------------------
//  Pull additional headers into the compilation to incorporate other functions.
//  ----------------------------------------------------------------------------

#include <ANSIStrToBSTR_P6C.H>

//  ----------------------------------------------------------------------------
//  Anticipating such a need, Microsoft provided a proprietary stack onto which
//  macro definitions can be pushed, so that they can be temporarily redefined.
//  Of necessity, this header must do exactly so, to coerce the linker into
//  importing the BinToHex_WW functions declared in BinToHex_WW.H.
//
//  An alternative, which I have applied in numerous other cases, is to list the
//  exported functions in a module definition file. Having discovered certain
//  shortcomings of module definition files, this is my attempt to avoid using
//  one.
//  ----------------------------------------------------------------------------

#if defined ( _BUILDING_CREATEGUIDSTRING_ )
    #pragma push_macro ( "LIBSPEC_P6CSTRINGLIB1_API" )
    #undef LIBSPEC_P6CSTRINGLIB1_API
    #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
#endif  /* #if defined ( _BUILDING_CREATEGUIDSTRING_ ) */

#include <BinToHex_WW.H>

//  ----------------------------------------------------------------------------
//  Once BinToHex_WW.H gets into the compilation stream, revert to the original
//  definition of LIBSPEC_P6CSTRINGLIB1_API, by popping it off the stack.
//  ----------------------------------------------------------------------------

#if defined ( _BUILDING_CREATEGUIDSTRING_ )
    #pragma pop_macro ( "LIBSPEC_P6CSTRINGLIB1_API" )
#endif /* #if defined ( _BUILDING_CREATEGUIDSTRING_ ) */

#include <CmdArgs_P6C.H>
#include <CreateGUIDString.H>
#include <FNReplacReservedChars.H>
#include <FormatMsgs_WW.H>
#include <GetBom_P6C.H>
#include <GetItemFromArray_WW.H>
#include <GetMyResource_WW.H>
#include <LoadStringErrNoSuchString_P6C.H>
#include <ShowAddress_WW.H>
#include <StoreAddressInArray_WW.H>
#include <strCopyCStrToBstr_P6C.H>
#include <strEscape_P6C.H>
#include <SubsStrings_WW.H>

//  ----------------------------------------------------------------------------
//  Define macros for evaluating strings and removing selected characters from
//  them, such as the first, second, and last character.
//  ----------------------------------------------------------------------------

#include <CharPosMacros_WW.H>

//  ----------------------------------------------------------------------------
//  Error codes are defined in groups by function.
//  ----------------------------------------------------------------------------

//  ----------------------------------------------------------------------------
//  Codes shared by many functions, for such things as memory management errors:
//	Unless routines remain that haven't been upgraded to the SEH wrappers, code
//	P6STRINGLIB_MALLOC_ERR_P6C is unused. Regardless, it is deprecated.
//  ----------------------------------------------------------------------------

#define P6STRINGLIB_MALLOC_ERR_P6C          ( 0x00000001 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  Error codes shared by functions in this library:
//  ----------------------------------------------------------------------------

#define P6STRINGLIB_INPUT_TOO_BIG_P6C       ( 0x00000002 | APPLICATION_ERROR_MASK )
#define P6STRINGLIB_LSTRCPYN_ERR_P6C        ( 0x00000003 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  Errors returned by PathStringFixup:
//  ----------------------------------------------------------------------------

#define PATHSTRINGFIXUP_PATH_NULL           ( 0x0000000B | APPLICATION_ERROR_MASK )
#define PATHSTRINGFIXUP_PATH_EMPTY          ( 0x0000000C | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  Errors returned by MakeFQFNP6C:
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_MAKEFQFN_NFN          ( 0x0000000D | APPLICATION_ERROR_MASK )
#define P6CSTRINGLIB1_MAKEFQFN_EFN          ( 0x0000000E | APPLICATION_ERROR_MASK )
#define P6CSTRINGLIB1_MAKEFQFN_NPN          ( 0x0000000F | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  Errors returned by QuoteString functions:
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_QS_NULL_STR           ( 0x00000011 | APPLICATION_ERROR_MASK )
#define P6CSTRINGLIB1_QS_EMPTY_STR          ( 0x00000012 | APPLICATION_ERROR_MASK )
#define P6CSTRINGLIB1_QS_INV_ACTION         ( 0x00000013 | APPLICATION_ERROR_MASK )
#define P6CSTRINGLIB1_QS_EMBEDDED_QUOTE     ( 0x00000014 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  Errors returned by SafeAppendStrToBuff_WW functions:
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_SA_ERROR_WW           ( 0x00000400 | APPLICATION_ERROR_MASK )

#define P6CSTRINGLIB1_SA_NEWSTR_NULL_WW     ( 0x00000001 | P6CSTRINGLIB1_SA_ERROR_WW )
#define P6CSTRINGLIB1_SA_NEWSTR_TOO_LONG_WW ( 0x00000002 | P6CSTRINGLIB1_SA_ERROR_WW )
#define P6CSTRINGLIB1_SA_NEWSTR_WONT_FIT_WW ( 0x00000004 | P6CSTRINGLIB1_SA_ERROR_WW )
#define P6CSTRINGLIB1_SA_NEWSTR_NO_MEM_WW   ( 0x00000008 | P6CSTRINGLIB1_SA_ERROR_WW )
#define P6CSTRINGLIB1_SA_NEWSTR_INV_LEN_WW  ( 0x00000010 | P6CSTRINGLIB1_SA_ERROR_WW )
#define P6CSTRINGLIB1_SA_NEWSTR_INV_BUFF_WW ( 0x00000011 | P6CSTRINGLIB1_SA_ERROR_WW )

//  ----------------------------------------------------------------------------
//  Errors returned by IsSameBaseName_WW functions:
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_TB_ERROR_WW           ( 0x00000600 | APPLICATION_ERROR_MASK )

#define P6CSTRINGLIB1_TB_FILENAME1_NULL_WW  ( 0x00000011 | P6CSTRINGLIB1_TB_ERROR_WW )
#define P6CSTRINGLIB1_TB_FILENAME1_BLANK_WW ( 0x00000012 | P6CSTRINGLIB1_TB_ERROR_WW )

#define P6CSTRINGLIB1_TB_FILENAME2_NULL_WW  ( 0x00000021 | P6CSTRINGLIB1_TB_ERROR_WW )
#define P6CSTRINGLIB1_TB_FILENAME2_BLANK_WW ( 0x00000022 | P6CSTRINGLIB1_TB_ERROR_WW )

//  ----------------------------------------------------------------------------
//  Errors returned by IsSameExtension_WW functions:
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_TE_ERROR_WW           ( 0x00000500 | APPLICATION_ERROR_MASK )

#define P6CSTRINGLIB1_TE_FILENAME_NULL_WW   ( 0x00000011 | P6CSTRINGLIB1_TE_ERROR_WW )
#define P6CSTRINGLIB1_TE_FILENAME_BLANK_WW  ( 0x00000012 | P6CSTRINGLIB1_TE_ERROR_WW )
#define P6CSTRINGLIB1_TE_FILENAME_NO_EXT_WW ( 0x00000013 | P6CSTRINGLIB1_TE_ERROR_WW )

#define P6CSTRINGLIB1_TE_EXTENSION_NULL_WW  ( 0x00000021 | P6CSTRINGLIB1_TE_ERROR_WW )
#define P6CSTRINGLIB1_TE_EXTENSION_BLANK_WW ( 0x00000022 | P6CSTRINGLIB1_TE_ERROR_WW )

//  ----------------------------------------------------------------------------
//  Errors returned by PathReplaceExtension_WW functions:
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_RE_ERROR_WW           ( 0x00000700 | APPLICATION_ERROR_MASK )

#define P6CSTRINGLIB1_RE_FILENAME_NULL_WW   ( 0x00000011 | P6CSTRINGLIB1_RE_ERROR_WW )
#define P6CSTRINGLIB1_RE_FILENAME_BLANK_WW  ( 0x00000012 | P6CSTRINGLIB1_RE_ERROR_WW )
#define P6CSTRINGLIB1_RE_FILENAME_NO_EXT_WW ( 0x00000013 | P6CSTRINGLIB1_RE_ERROR_WW )

#define P6CSTRINGLIB1_RE_EXTENSION_NULL_WW  ( 0x00000021 | P6CSTRINGLIB1_RE_ERROR_WW )
#define P6CSTRINGLIB1_RE_EXTENSION_BLANK_WW ( 0x00000022 | P6CSTRINGLIB1_RE_ERROR_WW )

#define P6CSTRINGLIB1_RE_PATH_TOO_LONG_WW   ( 0x00000031 | P6CSTRINGLIB1_RE_ERROR_WW )

//  ----------------------------------------------------------------------------
//  Errors returned by SplitStringSimple_WW functions:
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_SSS_ERROR_WW          ( 0x00000800 | APPLICATION_ERROR_MASK )

#define P6CSTRINGLIB1_SSS_NULL_STRING_WW    ( 0x00000001 | P6CSTRINGLIB1_SSS_ERROR_WW )
#define P6CSTRINGLIB1_SSS_DELIMITER_NULL_WW ( 0x00000002 | P6CSTRINGLIB1_SSS_ERROR_WW )

#if !defined ( P6CSTRINGLIB1_RSC_ERROR_WW )
    #define P6CSTRINGLIB1_RSC_ERROR_WW      ( 0x00000900 | APPLICATION_ERROR_MASK )

    #define P6CSTRINGLIB1_RSC_NULL_STRING1  ( 0x00000001 | P6CSTRINGLIB1_RSC_ERROR_WW )
    #define P6CSTRINGLIB1_RSC_NULL_STRING2  ( 0x00000002 | P6CSTRINGLIB1_RSC_ERROR_WW )

    #define P6CSTRINGLIB1_RSC_NULL_STRINGS  ( P6CSTRINGLIB1_RSC_NULL_STRING1 | P6CSTRINGLIB1_RSC_NULL_STRING2 )
#endif  /* #if !defined ( P6CSTRINGLIB1_RSC_ERROR_WW ) */

#define P6CSTRINGLIB1_SSS_INVALID_ARGS_WW   0xffffffff

//  ----------------------------------------------------------------------------
//  Errors returned by the FormatIntAsHex functions.
//  ----------------------------------------------------------------------------

#define INT_AS_HEX_ERROR_WW                 ( 0x00000900 | APPLICATION_ERROR_MASK )
#define INT_AS_HEX_UNKNOWN_RES_STR_LOAD_ERR ( 0x00000001 | INT_AS_HEX_ERROR_WW )

//  ----------------------------------------------------------------------------
//  Use these symbolic constants with the Flags argument to the FormatIntAsHex
//  family of functions.
//  ----------------------------------------------------------------------------

#define INT_AS_HEX_DEFAULT              0x00000000                              // All flags OFF yields fixed width upper case, sans 0x prefix.

#define INT_AS_HEX_0X_PREFIX            0x00000001                              // Bit 0 is ON (decimal value = 1)
#define INT_AS_HEX_MIN                  0x00000002                              // Bit 1 is ON (decimal value = 2)
#define INT_AS_HEX_UCASE                0x00000004                              // Bit 2 is ON (decimal value = 4)

#define INT_AS_HEX_BARE                 ( ! INT_AS_HEX_0X_PREFIX )              // Bit 0 is OFF.
#define INT_AS_HEX_FIXED                ( ! INT_AS_HEX_MIN )                    // Bit 1 is OFF.
#define INT_AS_HEX_LCASE                ( ! INT_AS_HEX_UCASE )                  // Bit 2 is OFF.

//  ----------------------------------------------------------------------------
//  Enumeration used by MakeFQFNP6C and others;
//  ----------------------------------------------------------------------------

#if !defined ( __PATHSTRINGSEMANTICS_P6C_DEFINED__ )
    #define __PATHSTRINGSEMANTICS_P6C_DEFINED__

    typedef enum _tagPATHSTRINGSEMANTICS_P6C
    {
        PATHSTRINGSEMANTICS_UNDEFINED_P6C ,                 // 0
        PATHSTRINGSEMANTICS_WINDOWS_P6C ,                   // 1
        PATHSTRINGSEMANTICS_UNIX_P6C ,                      // 2
    }   PATHSTRINGSEMANTICS_P6C ;
#endif  /* #if !defined ( __PATHSTRINGSEMANTICS_P6C_DEFINED__ ) */

#if !defined ( __PATHSTRINGFIXUP_HOW_P6C_DEFINED )
    #define __PATHSTRINGFIXUP_HOW_P6C_DEFINED

    typedef enum _tagPATHSTRINGFIXUP_HOW_P6C
    {
        PATHSTRINGFIXUP_INVALID ,                           // 0
        PATHSTRINGFIXUP_ADD_P6C ,                           // 1
        PATHSTRINGFIXUP_REMOVE_P6C ,                        // 2
    }   PATHSTRINGFIXUP_HOW_P6C ;
#endif  /* #if !defined ( __PATHSTRINGFIXUP_HOW_P6C_DEFINED ) */

#if !defined ( __QUOTESTRING_ACTION_P6C_DEFINED__ )
    #define __QUOTESTRING_ACTION_P6C_DEFINED__
    typedef enum _tagQUOTESTRING_ACTION_P6C
    {
        QUOTESTRING_INVALID ,                               // 0
        QUOTESTRING_ACTION_QUOTE_SPACES ,                   // 1
        QUOTESTRING_ACTION_QUOTE_ALWAYS ,                   // 2
        QUOTESTRING_ACTION_QUOTE_STRIP  ,                   // 3
    }   QUOTESTRING_ACTION_P6C ;
#endif  /* #if !defined ( __QUOTESTRING_ACTION_P6C_DEFINED__ ) */

typedef const QUOTESTRING_ACTION_P6C    CQUOTESTRING_ACTION_P6C ;

//  ----------------------------------------------------------------------------
//  Use these constants to set IsSameExtension_WW and IsSameBaseName_WW argument
//  pfUnixSemantics.
//  ----------------------------------------------------------------------------

#define P6CSTRINGLIB1_TB_UNIX_WW        TRUE
#define P6CSTRINGLIB1_TB_WINDOWS_WW     FALSE

#define P6CSTRINGLIB1_TE_UNIX_WW        TRUE
#define P6CSTRINGLIB1_TE_WINDOWS_WW     FALSE

//  ----------------------------------------------------------------------------
//  Macro Name:         HeapSizeInTCHARs
//
//  Macro Synopsis:     Copy source bytes, such as a string, from one location
//                      into another, discard the memory from which the bytes
//                      were copied, and advance the pointer that points to the
//                      copy destination past the bytes that were just appended.
//
//  In:                 plpBuffFromHeap = Pointer to destination of copy task
//  Out:                The return value is the capacity of the buffer expressed
//                      in TCHARs, including the terminal NULL character, which
//                      is required by both _stprintf_s and LoadString.
//
//  Remarks:            This macro is intended to be employed as an expression,
//                      within an argument list.
//
//                      Use this macro to derive the correct value of the size_t
//                      sizeOfBuffer argument for _stprintf_s or LoadString when
//                      the size of the buffer is unknown at run time.
//  ----------------------------------------------------------------------------

#define HeapSizeInTCHARs(plpBuffFromHeap) \
                                        ( BytesToTCHARsP6C ( HeapSize ( m_hProcHeap ,        \
                                                                        HEAP_ALL_FLAGS_OFF , \
                                                                        plpBuffFromHeap ) ) )


//  ----------------------------------------------------------------------------
//  Macro Name:         MoveString
//
//  Macro Synopsis:     Copy source bytes, such as a string, from one location
//                      into another, discard the memory from which the bytes
//                      were copied, and advance the pointer that points to the
//                      copy destination past the bytes that were just appended.
//
//  In:                 pDestination    = Pointer to destination of copy task
//                      pSource         = Pointer to source of bytes to copy
//                      pNUnits         = Number of units to copy (See Remarks).
//                      pUnitSize       = Size of units  to copy (See Remarks).
//
//  Remarks:            This macro is intended to be the entire contents of a C
//                      or C++ program statement.
//
//                      ANY mishap in this macro causes the calling routine to
//                      execute a return instruction, setting its return value to
//                      NULL. Assuming that the calling routine returns a string
//                      pointer, this should be OK.
//
//                      Arguments pNUnits and pUnitSize allow this macro to copy
//                      an arbitrary number of like sized objects, such as bytes
//                      that contain characters, composed of a fixed number of
//                      bytes for each unit copied. The pNUnits value is a name
//                      or type name, which is fed to the sizeof pseudo function
//                      and the result multiplied by pNUnits to determine the
//                      number of bytes to move, and the amount by which to
//                      advance the pointer.
//  ----------------------------------------------------------------------------

#define MoveBytes(pDestination,pSource,pNUnits,pUnitSize ) \
    if ( pDestination )                                                                                                 \
    {                                                                                                                   \
        memcpy ( pDestination ,                                                                                         \
                 pSource ,                                                                                              \
                 sizeof ( pNUnits ) * pUnitSize );                                                                      \
                                                                                                                        \
        if ( pSource = ( LPTSTR ) FreeDfltHeapBuf_P6C ( pSource ) )                                                     \
        {                                                                                                               \
            return NULL ;                                                                                               \
        }   /* TRUE (UNanticipated outcome) block, if ( pSource = ( LPTSTR ) FreeDfltHeapBuf_P6C ( pSource ) )  */      \
        else                                                                                                            \
        {   /* The following computation must compensate for the compiler doubling the value for wide characters .*/    \
            pDestination += ( ( sizeof ( pNUnits ) * pUnitSize ) / sizeof ( TCHAR ) ) ;                                 \
        }   /* FALSE (anticipated outcome) block, if ( pSource = ( LPTSTR ) FreeDfltHeapBuf_P6C ( pSource ) )  */       \
    }   /* TRUE (anticipated outcome) block, if ( pDestination ) */                                                     \
    else                                                                                                                \
    {                                                                                                                   \
        return NULL ;                                                                                                   \
    }   /* FALSE (UNanticipated outcome) block, if ( pDestination ) */


//  ----------------------------------------------------------------------------
//  Define standard C interfaces for the functions that do useful work.
//  Using "C" linkage permits these routines to be used with virtually any
//  programming language that has a Windows compiler; if it supports STDCALL, it
//  can use them.
//
//  The routines that return pointers to strings have custom wrappers that
//  return a BSTR, for use with Visual Basic 6,  Visual Basic for Applications,
//  and COM modules, all of which expect returned strings to be BSTRs. These are
//  proven with the versions of VBA that come with Microsoft Office; they have
//  been tested with the following versions: 2000, 2002 (XP), and 2010.
//
//  I think it is safe to say that they work with their immediate predecessor,
//  Office 97, the skipped versions (2003 and 2007), and their immediate
//  successor, Office 2013.
//  ----------------------------------------------------------------------------

#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */

/*
    ----------------------------------------------------------------------------
    Function Names:     FormatIntAsHex_uchr     Unsigned Character (BYTE)
                        FormatIntAsHex_swrd     Signed WORD (16 bit integer)
                        FormatIntAsHex_uwrd     Unsigned WORD (16 bit integer)
                        FormatIntAsHex_sLng     Signed DWORD (32 bit integer)
                        FormatIntAsHex_uLng     Unsigned DWORD (32 bit integer)
                        FormatIntAsHex_sulng    Signed QWORD (64 bit integer)
                        FormatIntAsHex_uulng    Unsigned QWORD (64 bit integer)

    Synopsis:           Format an integer as a hexadecimal string.

    Arguments:          ToFormat    = Integer to format (See table in Remarks.)

                        Flags       = Bit mask that governs formatting, as
                                      follows:

                                        INT_AS_HEX_FIXED    Fixed width
                                        INT_AS_HEX_MIN      Minimum width
                                        INT_AS_HEX_UCASE    A-F in upper case
                                        INT_AS_HEX_LCASE    A-F in lower case

                                       See table in Remarks.

    Returns:            If it succeeds, the function returns the input integer,
                        formatted as hexadecimal digits. The returned pointer
                        refers to a small memory block that was allocated from
                        the default process heap. Call FreeDfltHeapBuf_P6C,
                        declared in WWKernelLibWrapper.H, or HeapFree, declared
                        in Windows.h, to prevent a memory leak by discarding it.

                        Please see the tables in the next section for
                        additional details.

    Remarks:            The first of the two arguments to these functionally
                        identical routines uses a prefix to differentiate the
                        integer size that it implements, as shown in the
                        following table.

                        --------------------------------------------------------
                        Function Name        Input Type   Typedef  Argument Name
                        -------------------- ------------- ------- -------------
                        FormatIntAsHex_uchr  unsigned char CUCHAR  uchrToFormat
                        FormatIntAsHex_swrd  SHORT         CSHORT  swrdToFormat
                        FormatIntAsHex_uwrd  USHORT        CUSHORT uwrdToFormat
                        FormatIntAsHex_sLng  LONG          CLONG   sLngToFormat
                        FormatIntAsHex_uLng  ULONG         CULONG  uLngToFormat
                        FormatIntAsHex_sulng __int64       CINT64  sulngToFormat
                        FormatIntAsHex_uulng __int64       CUINT64 uulngToFormat
                        --------------------------------------------------------

                        The second of the two arguments, pFlags, is a CDWORD, a
                        constant DWORD (unsigned 32 bit integer) bit mask that
                        governs the formatting of the integer, as follows.

                        1)  By default, a fixed length string of upper case hex
                            characters is returned.

                        2)  If the INT_AS_HEX_MIN flag is specified, a variable
                            length string containing the minimum number of hex
                            digits needed to represent the integer is returned.

                        3)  If the INT_AS_HEX_UCASE flag is specified, a string
                            of UPPER case hexadecimal digits is returned. The
                            initial implementation defaulted to upper case, but
                            I realized that upper case creates the possibility
                            of an ambiguity between the '8' and 'b' digits.

                        4)  Both defaults are documented as symbolic constants.
                            However, since their values are zero (all bits OFF),
                            there is little practical use for them, apart from
                            explicitly setting all formatting options.

                        5)  Extra bits not identified above are ignored.

                        The following table lists and describes constants for
                        setting the bits in the second argument, called pFlags
                        in all seven cases. The last three offer explicit values
                        for the default (OFF) values of the three defined bits.

                        ----------------------------------------------------------------------------------
                        Name                  Definition                  Comment
                        --------------------  --------------------------  --------------------------------
                        INT_AS_HEX_DEFAULT    0x00000000                  All flags OFF yields fixed width
                                                                          lower case, sans 0x prefix.

                        INT_AS_HEX_0X_PREFIX  0x00000001                  Bit 0 is ON (decimal value = 1)
                        INT_AS_HEX_MIN        0x00000002                  Bit 1 is ON (decimal value = 2)
                        INT_AS_HEX_UCASE      0x00000004                  Bit 2 is ON (decimal value = 4)

                        INT_AS_HEX_BARE       ( ! INT_AS_HEX_0X_PREFIX )  Bit 0 is OFF.
                        INT_AS_HEX_FIXED      ( ! INT_AS_HEX_MIN )        Bit 1 is OFF.
                        INT_AS_HEX_LCASE      ( ! INT_AS_HEX_UCASE )      Bit 2 is OFF.
                        ----------------------------------------------------------------------------------

                        The following table lists the pertinent properties of
                        the seven functions. The last column, labeled "Hex," is
                        the length of the default fixed length string, and the
                        maximum length of the variable length string returned by
                        the function.

                        -------------------------------------------------------------
                        Function Name        Typedef  Input Type    Signed   Bits Hex
                        -------------------- -------- ------------- -------- ---- ---
                        FormatIntAsHex_uchr  CUCHAR   unsigned char Unsigned    8   2
                        FormatIntAsHex_swrd  CSHORT   SHORT         Signed     16   4
                        FormatIntAsHex_uwrd  CUSHORT  USHORT        Unsigned   16   4
                        FormatIntAsHex_sLng  CLONG    LONG          Signed     32   8
                        FormatIntAsHex_uLng  CULONG   ULONG         Unsigned   32   8
                        FormatIntAsHex_sulng CINT64   __int64       Signed     64  16
                        FormatIntAsHex_uulng CUINT64  __int64       Unsigned   64  16
                        -------------------------------------------------------------

                        Since these functions return pointers to strings, there
                        are ANSI (legacy narrow character) and Unicode (wide
                        character) implementations, along with standard TCHAR
                        mapping macros.

                        Internally, all fourteen functions are implemented as a
                        C++ template function, which depends on four format
                        control strings, stored as Win32 string resources, and
                        is defined privately.
    ----------------------------------------------------------------------------
*/
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_uchrA  ( CUCHAR  uchrToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_swrdA  ( CSHORT  swrdToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_uwrdA  ( CUSHORT uwrdToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_sLngA  ( CLONG   sLngToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_uLngA  ( CULONG  uLngToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_sulngA ( CINT64  sulngToFormat , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_uulngA ( CUINT64 uulngToFormat , CDWORD pFlags ) ;

    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_uchrW  ( CUCHAR  uchrToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_swrdW  ( CSHORT  swrdToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_uwrdW  ( CUSHORT uwrdToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_sLngW  ( CLONG   sLngToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_uLngW  ( CULONG  uLngToFormat  , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_sulngW ( CINT64  sulngToFormat , CDWORD pFlags ) ;
    LIBSPEC_P6CSTRINGLIB1_API LPTSTR __stdcall FormatIntAsHex_uulngW ( CUINT64 uulngToFormat , CDWORD pFlags ) ;

#if defined ( UNICODE )
    #define FormatIntAsHex_uchr  FormatIntAsHex_uchrW
    #define FormatIntAsHex_swrd  FormatIntAsHex_swrdW
    #define FormatIntAsHex_uwrd  FormatIntAsHex_uwrdW
    #define FormatIntAsHex_sLng  FormatIntAsHex_sLngW
    #define FormatIntAsHex_uLng  FormatIntAsHex_uLngW
    #define FormatIntAsHex_sulng FormatIntAsHex_sulngW
    #define FormatIntAsHex_uulng FormatIntAsHex_uulngW
#else
    #define FormatIntAsHex_uchr  FormatIntAsHex_uchrA
    #define FormatIntAsHex_swrd  FormatIntAsHex_swrdA
    #define FormatIntAsHex_uwrd  FormatIntAsHex_uwrdA
    #define FormatIntAsHex_sLng  FormatIntAsHex_sLngA
    #define FormatIntAsHex_uLng  FormatIntAsHex_uLngA
    #define FormatIntAsHex_sulng FormatIntAsHex_sulngA
    #define FormatIntAsHex_uulng FormatIntAsHex_uulngA
#endif /* #if defined ( UNICODE ) */

    /*
    ============================================================================

    Name:               FormatLongInt_P6C

    Synopsis:           Use the locale settings to format a long integer. This
                        is the ANSI (ASCII, or legacy) implementation.

    Arguments:          plngNumber  = Long integer to be formatted, using the
                                      current user's language settings.

    Returns:			if the function succeeds, its return value is a pointer
                        to a string that contains the formatted integer.

                        If an error occurs, the return value is NULL.

    Remarks:            The function handles any valid long integer, which can
                        have a value from -2,147,483,648 to +2,147,483,648,
                        which can use up to 14 characters (15 counting the
                        trailing null).

    Reference:          "Generating and Parsing Localized Numbers In Windows,"
                        by Steven Engelhardt,
                        http://www.deez.info/sengelha/2007/07/11/generating-and-parsing-localized-numbers-in-windows/

    Created:            Tuesday, 25 April 2006 through Sunday, 30 April 2006.

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API _stdcall FormatLongIntA
(
    long plngNumber
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API _stdcall FormatLongIntW
(
    long plngNumber
) ;

#ifdef UNICODE
    #define FormatLongInt  FormatLongIntW
#else
    #define FormatLongInt  FormatLongIntA
#endif  /* #ifdef UNICODE */


//  ----------------------------------------------------------------------------
//  Many of the following functions are inspired by similar functions defined in
//  the Windows Interface Language (WIL), more commonly called WinBatch. For the
//  most part, these are native code replacements, although their intended use
//  is outside the context of a WIL interpreter, where they have uses in native
//  code implemented in C, C++, and other programming languages. Since Visual
//  Basic remains very much alive, as Visual Basic for Applications, functions
//  that return strings have wrappers that return Basic Strings (BSTRs), and are
//  called via __stdcall. By meeting both requirements, any application that
//  hosts a VBA runtime library can use them.
//  ----------------------------------------------------------------------------

/*
    ============================================================================

    Name:               GetTokenByIndex_P6C

    Synopsis:           Given a character array of null delimited tokens, the 1
                        based index of the desired token, and the size, in bytes,
                        of the array, return a pointer to the desired token.

    Arguments:          plpTokenArray   = Array of characters containing tokens,
                                          delimited by ASCII NULL characters,
                                          such that each token behaves like a C
                                          string when made the object of a string
                                          pointer.

                        plngTokenIndex  = Index (1 based) of desired token.

                        pintTokenStrSz  = Size, in BYTES, of token string,
                                          derived by taking sizeof
                                          ( plpTokenArray ) in the caller.

    Returns:            rlpNextToken    = Pointer to next token in array.

    Remarks:            1)  This function is implemented for ANSI and Unicode
                            strings, which are symbolically mapped to the single
                            name, GetTokenByIndex_P6C.

                        2)  This function assumes two things about plpTokenArray.

                            a)  Although cast to LPCTSTR, the array itself is of
                                type char , wchar_t, or TCHAR.

                            b)  When the C compiler lays out the array in
                                memory, it appends a NULL character, so that the
                                array behaves like a normal C string. Although
                                the compiler ignores the embedded nulls in the
                                Unicode mappings of ANSI strings, the terminal
                                null suits us quite nicely.

                        3)  This function returns a pointer to a valid C string,
                            unless the list has been exhausted. In that case,
                            it returns a NULL.

                        4)  Following a hunch, I did a bit of research, and
                            concluded that lstrlen should be replaced by _tcslen.
                            Although the first two references are essentially
                            identical, and a tad vague, the third, in a forum
                            devoted to game developers, cites benchmark results
                            that suggest that my hunch that _tcslen is
                            measurably faster than lstrlen has legs.

                        5)  The source code revisions are entirely cosmetic, and
                            include long overdue corrections to their internal
                            documentation.

    Calls:              The following Windows API functions are called in the
                        order named.

                            Function            Library         Header
                            ------------------  --------------  ----------------
                            _tcslen             CRT             stdlib.h
                            ----------------------------------------------------

    Created:            Saturday, 10 December 2005 - Sunday, 11 December 2005

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API GetTokenByIndexA_P6C
(
    LPCTSTR plpTokenArray ,
    long    plngTokenIndex ,
    int     pintTokenStrSz
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API GetTokenByIndexW_P6C
(
    LPCTSTR plpTokenArray ,
    long    plngTokenIndex ,
    int     pintTokenStrSz
) ;

#ifdef UNICODE
    #define GetTokenByIndex_P6C GetTokenByIndexW_P6C
#else
    #define GetTokenByIndex_P6C GetTokenByIndexA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Name:               IsSameBaseName_WW

    Synopsis:           Given two file names, compare their base names (the file
                        name, without its extension, and return TRUE if they
                        match.

    Arguments:          pstrFileName1   = String containing a file name to be
                                          evaluated, where pstrFileName1 may be
                                          fully qualified or relative.

                        pstrFileName2   = String containing a file name to be
                                          evaluated, where pstrFileName2 may be
                                          fully qualified or relative.

                        pfUnixSemantics = Set this Boolean value to TRUE to use
                                          Unix (case sensitive) semantics. The
                                          default is FALSE, for Windows (case
                                          insensitive) semantics.

    Returns:            If the base names of pstrFileName1 and pstrFileName2 are
                        the same, the return value is TRUE, else it is FALSE.

    Remarks:            1)  Lightweight Shell API routines are used to find the
                            base name in a path string, and to remove the file
                            extension, because these routines handle Unix
                            path strings gracefully, and have ANSI and Unicode
                            implementations that map to the same symbolic name.

                        2)  On the other hand, CRT library routines are used to
                            compare the strings, since I am unconvinced that the
                            native Windows routines are any better for this kind
                            of work.

                        3)  Since these routines use thread-safe system routines
                            to allocate storage for copies of strings from the
                            process heap, which is thread-safe, and addresses go
                            into automatic variables (which are allocated on the
                            stack), they should be thread-safe.

    See Also:           IsSameExtension_WW

    Created:            Tuesday, 16 July 2013

    ============================================================================
*/

BOOL LIBSPEC_P6CSTRINGLIB1_API IsSameBaseNameA_WW
(
    LPCTSTR pstrFileName1 ,
    LPCTSTR pstrFileName2 ,
    BOOL    pfUnixSemantics
) ;

BOOL LIBSPEC_P6CSTRINGLIB1_API IsSameBaseNameW_WW
(
    LPCTSTR pstrFileName1 ,
    LPCTSTR pstrFileName2 ,
    BOOL    pfUnixSemantics
) ;

#ifdef UNICODE
    #define IsSameBaseName_WW    IsSameBaseNameW_WW
#else
    #define IsSameBaseName_WW    IsSameBaseNameA_WW
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Name:               IsSameExtension_WW

    Synopsis:           Given the name of a file and an extension, with or
                        without its delimiter, compare the extension of the file
                        and return TRUE if it matches the specified extension.

    Arguments:          pstrFileName    = String containing the file name to be
                                          evaluated, where pstrFileName may be
                                          fully qualified or relative.

                        pstrExtension   = String containing the extension to be
                                          evaluated, with or without its leading
                                          delimiter.

                        pfUnixSemantics = Set this Boolean value to TRUE to use
                                          Unix (case sensitive) semantics. The
                                          default is FALSE, for Windows (case
                                          insensitive) semantics.

    Returns:            If the extension of the file name in pstrFileName is the
                        same as pstrExtension, the return value is TRUE, else it
                        is FALSE.

    Remarks:            1)  Lightweight Shell API routines are used to extract a
                            file extension, because these routines handle Unix
                            path strings gracefully, and have ANSI and Unicode
                            implementations that map to the same symbolic name.

                        2)  On the other hand, CRT library routines are used to
                            compare the strings, since I am unconvinced that the
                            native Windows routines are any better for this kind
                            of work.

                        3)  Since these routines use thread-safe system routines
                            to allocate storage for copies of strings from the
                            process heap, which is thread-safe, and addresses go
                            into automatic variables (which are allocated on the
                            stack), they should be thread-safe.

    See Also:           IsSameBaseName_WW

    Created:            Friday, 24 May 2013 through Sunday, 26 May 2013

    ============================================================================
*/

BOOL LIBSPEC_P6CSTRINGLIB1_API IsSameExtensionA_WW
(
    LPCTSTR pstrFileName ,
    LPCTSTR pstrExtension ,
    BOOL    pfUnixSemantics
) ;

BOOL LIBSPEC_P6CSTRINGLIB1_API IsSameExtensionW_WW
(
    LPCTSTR pstrFileName ,
    LPCTSTR pstrExtension ,
    BOOL    pfUnixSemantics
) ;

#ifdef UNICODE
    #define IsSameExtension_WW    IsSameExtensionW_WW
#else
    #define IsSameExtension_WW    IsSameExtensionA_WW
#endif  /* #ifdef UNICODE */


/*
    ============================================================================

    Function:           MakeFQFNP6C

    Module:             MakeFQFNAP6C.C and MakeFQFNWP6C.C

    Synopsis:           Given two strings, the first containing a file name and
                        the second a path, return a fully qualified file name.

    Arguments:          pFileName   = File name to test and fix up if it is
                                      unqualified.

                        pDirName    = Name of directory to prefix to pFileName,
                                      if it is found to be unqualified.

                                      If pDirName is an empty string, substitute
                                      the current working directory (CWD).

                        pchrPathDlm = Pointer to a TCHAR to treat as a path
                                      delimiter.

                                      If pchrPathDlm is NULL, a DOS/Windows path
                                      delimiter (the backslash character) is the
                                      path delimiter.

    Returns:            rFQFN       = Fully qualified file name.

    Remarks             1)  This function copies the string into a buffer
                            allocated from the local (default) heap, and always
                            returns a pointer to the copy.

                        2)  If argument pFileName is null or an empty string, an
                            empty string is returned, and SetLastError is called
                            to set a custom error code.

    Created:            Monday, 08 May 2006

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Author Synopsis
    ---------- ------ ----------------------------------------------------------
    2006/05/10 DAG    First working version.

    2010/02/16 DAG    Relocate from the WWWILMuscle source code tree to the
                      P6CLIB1 source code tree.

    2010/03/08 DAG    Remove version numbers, which have no practical meaning
                      when applied to functions that are part of a static
                      library.

    2010/06/04 DAG    Move the #pragma once preprocessor directive INSIDE the
                      scope of the preprocessor variable which performs the same
                      function for other C compilers.

    2011/06/05 DAG    1) Move these functions to P6CUtilLib1, from WWWILMuscle,
                         to resolve an unresolved external symbol reference
                         without creating a linkage loop.

                      2) Change the calling sequence from WINAPI to LIBSPEC
                         actually __declspec(dllexport), to cause the compiler
                         to emit code that puts the function into the Export
                         Address Table, without the need for an entry in the
                         Module Definition (.DEF) File.

                      3) Ensure that ALL errors related to memory allocation and
                         deallocation are trapped and reported.

    2011/08/28 DAG    Document the third ( TCHAR * ) argument, and verify that
                      the function works as intended.

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API MakeFQFNAP6C
(
    LPCTSTR       pFileName ,
    LPCTSTR       pDirName ,
    const TCHAR * pchrPathDlm
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API MakeFQFNWP6C
(
    LPCTSTR       pFileName ,
    LPCTSTR       pDirName ,
    const TCHAR * pchrPathDlm
) ;

#ifdef UNICODE
    #define MakeFQFNP6C MakeFQFNWP6C
#else
    #define MakeFQFNP6C MakeFQFNAP6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Function Name:      QuoteStringP6C

    File Name:          QuoteStringAP6C.C and QuoteStringWP6C.C

    Synopsis:           Enclose a string in quotation marks if it contains
                        embedded spaces, or always, or strip enclosing quotes, as
                        specified by argument pAction.

    Arguments:          pString         = String to process.

                        pAction         = A nonzero member of the
                                          QUOTESTRING_ACTION_P6C enumeration,
                                          which is interpreted as follows.

                                          QUOTESTRING_INVALID = Illegal value.

                                          QUOTESTRING_ACTION_QUOTE_SPACES = Quote
                                          if string contains spaces.

                                          QUOTESTRING_ACTION_QUOTE_ALWAYS = Always quote .

                                          QUOTESTRING_ACTION_QUOTE_STRIP = Strip quotes,
                                          if present.

                                          Any other value is ignored, an empty
                                          string is returned, and SetLastError
                                          is called.

                        pQuoteChar      = The desired quote character. If this
                                          argument is null or is an empty string,
                                          use a double quote.

    Returns:            rNewString      = One of the following:

                                            - Modified string per above, if
                                              pAction is valid

                                            - If pAction is invalid (non-numeric
                                               or out of range), an empty string

                                            - For a run-time error, an empty
                                              string (Call GetLastError)

    Remarks:            1)  This function copies the string into a buffer
                            allocated from the local (default) heap, and always
                            returns a pointer to the copy, or a pointer to an
                            empty string.

                        2)  This source module is the ANSI implementation.

    Created:            Thursday, 11 May 2006

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Author Synopsis
    ---------- ------ ----------------------------------------------------------
    2006/05/11 DAG    First working version.

    2009/02/19 DAG    Replace hard coded chrDoubleQu0oteA with a string resource.

    2009/04/26 DAG    1) Remove call to SetLastError, which sets our own code,
                         overwriting the code left by the memory allocation
                         function.

                      2) Add a reference to m_hProcHeap, which has library
                         scope, and is initialized by DllMain.

                      3) Replace most hard coded constants with symbolics.

    2010/05/24 DAG    Substitute _tcslen for lstrlen, to improve performance.

    2011/06/05 DAG    1) Move from WWWilMuscle to P6CStringLib1. where it
                         belongs.

                      2) Add a reference to m_hProcHeap, which has library
                         scope, and is initialized by DllMain.

                      3) Ensure that ALL errors related to memory allocation and
                         deallocation are trapped and reported.

                      4) Substitute the TcharsMinBufSizeP6C macro for hand coded
                         buffer size calculations, and move the calculations
                         inside the HeapAlloc function calls, which are their
                         sole use. This relocation eliminates a DWORD variable
                         from the stack frame used by the function, and pushes
                         the compiler to generate code that performs the
                         calculations entirely in CPU registers.

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API QuoteStringAP6C
(
    LPCTSTR                 pString ,
    CQUOTESTRING_ACTION_P6C pAction ,
    LPCTSTR                 pQuoteChar
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API QuoteStringWP6C
(
    LPCTSTR                 pString ,
    CQUOTESTRING_ACTION_P6C pAction ,
    LPCTSTR                 pQuoteChar
) ;

#ifdef UNICODE
    #define QuoteStringP6C  QuoteStringWP6C
#else
    #define QuoteStringP6C  QuoteStringAP6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Name:               PathReplaceExtension_WW

    Synopsis:           Given the name of a file and an extension, with or
                        without its delimiter, replace the existing extension
                        with the new one.

    Arguments:          pstrFileName    = String containing the file name to be
                                          changed, where pstrFileName may be
                                          fully qualified or relative, and need
                                          not exist.

                        pstrNewExt      = String containing the extension to be
                                          substituted, with or without its
                                          leading delimiter.

    Returns:            If the function succeeds, the return value is a new
                        string, contained in a buffer allocated from the process
                        heap, with the extension replaced. Otherwise, it returns
                        NULL. Call GetLastError to get extended error
                        information.

    Remarks:            1)  Lightweight Shell API routines are used to swap the
                            file extension, because these routines handle Unix
                            path strings gracefully, and have ANSI and Unicode
                            implementations that map to the same symbolic name.

                        2)  On the other hand, CRT library routines are used to
                            test for the leading dot in the extension string,
                            since I am unconvinced that the native Windows
                            routines are any better for this kind of work.

                        3)  Since these routines use thread-safe system routines
                            to allocate storage for copies of strings from the
                            process heap, which is thread-safe, and addresses go
                            into automatic variables (which are allocated on the
                            stack), they should be thread-safe.

    See Also:           IsSameBaseName_WW

    Created:            Saturday, 20 July 2013 and Sunday, 21 July 2013

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API PathReplaceExtensionA_WW
(
    LPCTSTR pstrFileName ,
    LPCTSTR pstrNewExte
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API PathReplaceExtensionW_WW
(
    LPCTSTR pstrFileName ,
    LPCTSTR pstrNewExt
) ;

#ifdef UNICODE
    #define PathReplaceExtension_WW    PathReplaceExtensionW_WW
#else
    #define PathReplaceExtension_WW    PathReplaceExtensionA_WW
#endif  /* #ifdef UNICODE */


/*
    ============================================================================

    Name:               PathStringFixup_P6C

    Module:             PathStringFixupAP6C.C and PathStringFixupWP6C.C

    Synopsis:           Given a string containing a path string, which may or
                        may not have a trailing backslash, and a flag that
                        specifies whether a trailing backslash is wanted, return
                        an appropriately formatted path string.

    Arguments:          plpPathString   = Long pointer to string containing a
                                          path string, which may or may not end
                                          with a backslash.

                        pAddOrRemove    = Member of the PATHSTRINGFIXUP_HOW_P6C
                                          enumeration, as follows.

                                            PATHSTRINGFIXUP_ADD_P6C    = 1
                                            PATHSTRINGFIXUP_REMOVE_P6C = 2

                                          Any other value is ignored, and the
                                          string is returned, unmodified.

                        pchrPathDlm     = Character to substitute for the
                                          default path delimiter, which is a
                                          backslash.

    Returns:            rPathFixed      = Path string, edited, as needed, to
                                          conform to the pAddOrRemove
                                          instruction.

                                          An unmodified copy of the string is
                                          returned if the pAddOrRemove argument
                                          is invalid.

    Remarks:            1)  This function copies the string into a buffer,
                            allocated from the local (default) heap, and always
                            returns a pointer to the copy.

                        2)  If argument pPathString is null or an empty string,
                            an empty string is returned, and SetLastError is
                            called, to set a custom error code.

                        3)  This function implements the LIBSPEC calling
                            convention, and is, therefore, omitted from the .DEF
                            file, yet it has an entry in the Export Address
                            Table.

    Created:    Monday, 08 May 2006

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Author Synopsis
    ---------- ------ ----------------------------------------------------------
    2006/05/08 DAG    First working version.

    2006/05/11 DAG    Remove unnecessary #include file (DateLib.H).

    2009/04/27 DAG    1) Add pchrPathDlm as an optional argument, and substitute
                         symbolic constants for most hard coded constants,
                         including the sizeof (TCHAR) pseudo-function, which
                         behaves more like a constant or a preprocessor macro.

                      2) Replace calls to GetProcessHeap ( ) with references to
                         library variable, m_hProcHeap, which always has a
                         working handle.

    2009/12/16 DAG    Fix, by way or a cast, compiler warnings about differing
                      levels of indirection.

    2010/05/24 DAG    Substitute _tcslen for lstrlen, to improve performance.

    2011/06/05 DAG    1) Move these functions to P6CUtilLib1, from WWWILMuscle,
                         to resolve an unresolved external symbol reference
                         without creating a linkage loop.

                      2) Change the calling sequence from WINAPI to LIBSPEC
                         actually __declspec(dllexport), to cause the compiler
                         to emit code that puts the function into the Export
                         Address Table, without the need for an entry in the
                         Module Definition (.DEF) File.

                      3) Ensure that ALL errors related to memory allocation and
                         deallocation are trapped and reported.

                      4) Substitute the TcharsMinBufSizeP6C macro for hand coded
                         buffer size calculations, and move the calculations
                         inside the HeapAlloc function calls, which are their
                         sole use. This relocation eliminates a DWORD variable
                         from the stack frame used by the function, and pushes
                         the compiler to generate code that performs the
                         calculations entirely in CPU registers.

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API PathStringFixupA_P6C
(
    LPCTSTR                 plpPathString ,
    PATHSTRINGFIXUP_HOW_P6C pAddOrRemove ,
    TCHAR *                 pchrPathDlm
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API PathStringFixupW_P6C
(
    LPCTSTR                 plpPathString ,
    PATHSTRINGFIXUP_HOW_P6C pAddOrRemove ,
    TCHAR *                 pchrPathDlm
) ;

#ifdef UNICODE
    #define PathStringFixup_P6C PathStringFixupW_P6C
#else
    #define PathStringFixup_P6C PathStringFixupA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Name:               SafeAppendStrToBuff_WW

    Synopsis:           Append a string to the end of the string in an existing
                        buffer, enlarging the buffer as needed to accommodate the
                        new string.

    Arguments:          plpNewString    = Pointer to the new string. See item 1
                                          in Remarks.

                        plpInBuffer     = Pointer to the input buffer. See item 2
                                          in Remarks.

                        pdwMaxNewTchars = Maximum length of new string, in
                                          TCHARS. See item 3 in Remarks.

                        pdwMaxBuffBytes = Maximum size, in bytes, to which the
                                          buffer may grow. See item 4 in
                                          Remarks.

    Returns:            If it succeeds, the function returns a pointer to the
                        updated buffer. See item 5 in Remarks.

    Remarks:            1)  Input string plpNewString must be null terminated,
                            and must be free of embedded null characters that
                            would prevent function _tcslen from computing its
                            length.

                        2)  Buffer plpInBuffer must be the pointer returned by a
                            call to HeapAlloc (or malloc, which is implemented
                            by HeapAlloc), because this function uses a Windows
                            intrinsic to determine its size.

                            Pass NULL if you want SafeAppendStrToBuff_WW to
                            allocate the initial buffer.

                        3)  DWORD input pdwMaxNewTchars establishes an upper
                            limit on the length of the string to which
                            plpNewString points.

                        4)  DWORD input pdwMaxBuffBytes establishes an upper
                            limit on the final size of the buffer.

                        5)  If input buffer plpInBuffer is too small and cannot
                            be enlarged without moving it, rlpNewString may
                            differ from plpInBuffer. If this is so:

                            a)  You must substitute rlpNewString for
                                plpInBuffer, since plpInBuffer is now an invalid
                                pointer.

                            b)  Since the memory has been moved, substitution is
                                a safe operation that doesn't leak memory.

                        This function provides a secure method of concatenating
                        one or more strings. Its security comes from its third
                        and fourth arguments, pdwMaxNewTchars and
                        pdwMaxBuffBytes. Since both are declared as DWORDs
                        (unsigned long), if a negative number gets into either,
                        the function fails and reports an error.

    Created:            Sunday, 15 January 2012 - Saturday, 21 January 2012

    ============================================================================
*/

LPTSTR LIBSPEC_P6CSTRINGLIB1_API SafeAppendStrToBuffA_WW
(
    LPCTSTR plpNewString,       // New string to append
    LPTSTR  plpInBuffer,        // Buffer to which to append string
    CDWORD  pdwMaxNewTchars,    // Maximum length of plpNewString (TCHARS)
    CDWORD  pdwMaxBuffBytes     // Maximum size of plpInBuffer (bytes)
) ;

LPTSTR LIBSPEC_P6CSTRINGLIB1_API SafeAppendStrToBuffW_WW
(
    LPCTSTR plpNewString,       // New string to append
    LPTSTR  plpInBuffer,        // Buffer to which to append string
    CDWORD  pdwMaxNewTchars,    // Maximum length of plpNewString (TCHARS)
    CDWORD  pdwMaxBuffBytes     // Maximum size of plpInBuffer (bytes)
) ;

#ifdef UNICODE
    #define SafeAppendStrToBuff_WW  SafeAppendStrToBuffW_WW
#else
    #define SafeAppendStrToBuff_WW  SafeAppendStrToBuffA_WW
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Name:               StrIndex_P6C

    Synopsis:           Return the index (position) of a subsstring, rather than
                        a pointer, as does the wcsstr function included in the
                        ANSI c libraries, including LIBC and Microsoft's
                        MSVCRT.DLL.

    Arguments:          plpStrToSearch  = Pointer to string to be searched.

                        plpStrToFind    = Pointer to string to find in
                                          plpStrToSearch.

    Returns:            if it succeeds, the function returns the index where the
                        first character in plpStrToFind is found, where the first
                        character of the string is considered to be in position 1.
                        Otherwise, the return value is zero.

    Remarks:            There are both Unicode (wide character) and ANSI (narrow
                        character) versions of this function.

    Created:            Wednesday, 07 September 2005

    ============================================================================
*/

long LIBSPEC_P6CSTRINGLIB1_API StrIndexA_P6C
(
    LPCTSTR plpStrToSearch ,
    LPCTSTR plpStrToFind
) ;

long LIBSPEC_P6CSTRINGLIB1_API StrIndexW_P6C
(
    LPCTSTR plpStrToSearch ,
    LPCTSTR plpStrToFind
) ;

#ifdef UNICODE
    #define StrIndex_P6C    StrIndexW_P6C
#else
    #define StrIndex_P6C    StrIndexA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Name:       StrIndexI_P6C

    Synopsis:           Return the index (position) of a subsstring, rather than
                        a pointer, as does the wcsstr function included in the
                        ANSI c libraries, including LIBC and Microsoft's
                        MSVCRT.DLL.

    Arguments:          plpStrToSearch  = Pointer to string to be searched.

                        plpStrToFind    = Pointer to string to find in
                                          plpStrToSearch.

    Returns:            if it succeeds, the function returns the index where the
                        first character in plpStrToFind is found, where the first
                        character of the string is considered to be in position 1.
                        Otherwise, the return value is zero.

    Remarks:            There are both Unicode (wide character) and ANSI (narrow
                        character) versions of this function.

                        Unlike companion function StrIndex_P6C, this function
                        performs a case insensitive search.

                        This function uses CharLower to convert the match string
                        to lower case. Unlike CRT library function tolower,
                        CharLower converts whole strings in place in one go.

    Calls:              The following Windows API functions are called in the
                        order listed.

                        Function            Library         Header
                        ------------------  --------------  ----------------
                        _tcslen             CRT             stdlib.h
                        CharLower           User32.lib      Winuser.h
                        ----------------------------------------------------

    Created:    Saturday, 10 September 2005

    ============================================================================
*/

long LIBSPEC_P6CSTRINGLIB1_API StrIndexIA_P6C
(
    LPCTSTR plpStrToSearch ,
    LPCTSTR plpStrToFind
) ;

long LIBSPEC_P6CSTRINGLIB1_API StrIndexIW_P6C
(
    LPCTSTR plpStrToSearch ,
    LPCTSTR plpStrToFind
) ;

#ifdef UNICODE
    #define StrIndexI_P6C   StrIndexIW_P6C
#else
    #define StrIndexI_P6C   StrIndexIA_P6C
#endif  /*  #ifdef UNICODE */


/*
    ============================================================================

    Name:               SplitStringSimple_WW

    Synopsis:           Split a simple string at each occurrence of a delimiter
                        character, returning the number of substrings, which is
                        the number of pointers that were inserted into the array
                        of pointers to which plpSubstrings points.

    Arguments:          plpInput        = Const pointer to string to split

                        pchr            = Const delimiter character

                        plpSubstrings   = Location for pointer to the array of
                                          substring pointers

    Returns:            If the function succeeds, the return value is the
                        substring count, and plpSubstrings points to the array
                        of pointers to them. If the function fails, the return
                        value is P6CSTRINGLIB1_SSS_INVALID_ARGS_WW ( -1 ), and
                        GetLastError returns one of the status codes listed
                        in the next section, or a system error code.

    Errors:             P6CSTRINGLIB1_SSS_NULL_STRING_WW    plpInput is a null
                                                            reference or points
                                                            to the empty string.

                        P6CSTRINGLIB1_SSS_DELIMITER_NULL_WW pchr is ASCII NUL.

    Remarks:    There are Unicode (wide character) and ANSI (narrow character)
                versions of this function.

    Created:    Thursday, 15 January 2015

    ============================================================================
*/

int LIBSPEC_P6CSTRINGLIB1_API SplitStringSimpleA_WW
(
    LPCTSTR     plpInput ,      // _In_     String to split
    CTCHAR      pchr ,          // _In_     Delimiter character
    LPTSTR *    plpSubstrings   // _Out_    Pointer to array of substrings
) ;

int LIBSPEC_P6CSTRINGLIB1_API SplitStringSimpleW_WW
(
    LPCTSTR     plpInput ,      // _In_     String to split
    CTCHAR      pchr ,          // _In_     Delimiter character
    LPTSTR *    plpSubstrings   // _Out_    Pointer to array of substrings
) ;

#ifdef UNICODE
    #define SplitStringSimple_WW    SplitStringSimpleW_WW
#else
    #define SplitStringSimple_WW    SplitStringSimpleA_WW
#endif  /*  #ifdef UNICODE */


//  ****************************************************************************
//  ****************************************************************************
//  **********                                                        **********
//  **********   V i s u a l   B a s i c   E n t r y   P o i n t s    **********
//  **********                                                        **********
//  ****************************************************************************
//  ****************************************************************************

//  ----------------------------------------------------------------------------
//
//  Define Visual Basic interfaces for functions that return strings.
//
//  Remarks:            1)  These are included only in DLL versions of this
//                          library, though it might be possible to statically
//                          link code into Visual Basic 6 code.
//
//                      2)  These entry points work equally well with Visual
//                          Basic for Applications (VBA) modules, which use the
//                          same method of linking to functions that follow the
//                          __stdcall calling convention.
//
//  ----------------------------------------------------------------------------

/*
    ============================================================================

    Function Name:      strEscape_VB_P6C

    Synopsis:           Given a pointer to a character string containing a match
                        string that is intended to become the match string for a
                        regular expression, escape all the metacharacters.

    Arguments:          pstrStringIn        = Long pointer to input string to be
                                              escaped.

                        pstrMetaChars       = Long pointer to optional string of
                                              metacharacters, which may be NULL
                                              or an empty string, in which case
                                              a default list of metacharacters
                                              is used.

    Returns:            rstrEscaped         = Long pointer to string of escaped
                                              characters.

    Remarks:            This is a VB/VBA wrapper for the strEscape_P6C function,
                        which is used to "escape" metacharacters in data that is
                        intended to become part of a regular expression.

    References:         None.

    Calls:              None. This function uses only native C functions and
                        operators.

    Date Completed:     Tuesday, 24 October 2006

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version    Author Synopsis
    ---------- ---------- ------ -----------------------------------------------
    2006/10/26 1, 0, 0, 9 DAG    Initial release.
    2012/05/20 2, 5, 3, 0 DAG    Move from P6CUtilLib1 to P6CStringLib1, beside
                                 the C string function that it wraps.
    ============================================================================
*/

BSTR __stdcall strEscape_VB_P6C
(
    LPCTSTR pstrStringIn ,
    LPCTSTR pstrMetaChars
) ;


/*
    ============================================================================

    Name:               StrLeft_VB_P6C

    Synopsis:           Return a new string containing the left-most (first N)
                        characters of the input string.

    Arguments:          plpStrinput     = Pointer to string to be searched.

                        plngNChars      = Number of characters to copy from
                                          plpStrinput.

    Returns:            bsBasicString   = Pointer to new string containing the
                                          first plngNChars characters of input
                                          string plpStrinput.

    Remarks:            This function accepts the ANSI string supplied by the
                        VB/VBA interface, calls the ANSI (OEM/DBCS) version of
                        function. StrLeft_P6C, and transforms the output into
                        the BSTR that VB requires.

                        Since this function duplicates code that is provided by
                        the native VB function Left(), there is probably no real
                        need for it, at least for use with VB. However, if this
                        library acquires a COM interface, or is called by a COM
                        library, it must be able to return BSTRs. In the latter
                        case, we need a version that takes a BSTR as input.

    Created:            Thursday, 08 September 2005

    ============================================================================
*/

BSTR __stdcall StrLeft_VB_P6C
(
    LPCTSTR    plpStrinput ,
    const long plngNChars
) ;


/*
    ============================================================================

    Name:               StrRight_VB_P6C

    Synopsis:           Return a new string containing the Right-most (last N)
                        characters of the input string.

    Arguments:          plpStrinput     = Pointer to string to be searched.

                        plngNChars      = Number of characters to copy from
                                          plpStrinput.

    Returns:            bsBasicString   = Pointer to new string containing the
                                          last plngNChars characters of input
                                          string plpStrinput.

    Remarks:            This function accepts the ANSI string supplied by the
                        VB/VBA interface, calls the ANSI (OEM/DBCS) version of
                        function. StrLeft_P6C, and transforms the output into
                        the BSTR that VB requires.

                        Since this function duplicates code that is provided by
                        the native VB function Left(), there is probably no real
                        need for it, at least for use with VB. However, if this
                        library acquires a COM interface, or is called by a COM
                        library, it will need to be able to return BSTRs. In the
                        latter case, we need a version that takes a BSTR as
                        input.

    Calls:              The following Windows API functions are called in the
                        order named.

                        Function            Library         Header
                        ------------------  --------------  --------------------
                        SysAllocString      oleaut32.lib    oleauto.h
                        --------------------------------------------------------

    Created:            Saturday, 10 September 2005

    ============================================================================
*/

BSTR __stdcall StrRight_VB_P6C
(
    LPCTSTR    plpStrinput ,
    const long plngNChars
) ;


/*
    ============================================================================

    Name:               StrSub_VB_P6C

    Synopsis:           Return a new string containing the specified number of
                        characters, starting at a specified position in the
                        input string.

    Arguments:          plpStrinput     = Pointer to string to be extracted.

                        plngStartPos    = Position (1 based) of first character.

                        plngNChars      = Number of characters to copy from
                                          plpStrinput.

    Returns:            rlpNewString    = Pointer to new string containing the
                                          last plngNChars characters of input
                                          string plpStrinput.

    Remarks:            This function accepts the ANSI string supplied by the
                        VB/VBA interface, calls the ANSI (OEM/DBCS) version of
                        function. StrLeft_P6C, and transforms the output into
                        the BSTR that VB requires.

                        Since this function duplicates code that is provided by
                        the native VB function Left(), there is probably no real
                        need for it, at least for use with VB. However, if this
                        library acquires a COM interface, or is called by a COM
                        library, it will need to be able to return BSTRs. In the
                        latter case, we need a version that takes a BSTR as
                        input.

    Calls:              The following Windows API functions are called in the
                        order named.

                        Function            Library         Header
                        ------------------  --------------  --------------------
                        SysAllocString      oleaut32.lib    oleauto.h
                        --------------------------------------------------------

    Created:            Saturday, 10 September 2005

    ============================================================================
*/

BSTR __stdcall StrSub_VB_P6C
(
    LPCTSTR    plpStrinput ,
    const long plngStartPos ,
    const long plngNChars
) ;

//  ----------------------------------------------------------------------------
//  Close the block of code that has "C" linkage, and the outermost #ifdef.
//  ----------------------------------------------------------------------------

#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */
#endif  /* #if !defined ( _P6CSTRINGLIB1_DEFINED ) */