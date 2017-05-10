#ifndef _GETBOM_P6C_DEFINED
#define _GETBOM_P6C_DEFINED

/*
    ============================================================================

    Name:               GetBom_P6C.H

    Synopsis:           Declare Byte Order Mark detection function GetBom_P6C,
                        and the data structure through which it communicates, in
                        both directions, with its caller.

    Remarks:            These changes, made for version 1, 0, 0, 3, accompany
                        removal of function GetBOM_P6C from dynamic link library
                        WWTrimLog.dll to static link library P6CLIB1.

                        Dynamic link library WWTrimLog.dll is, of course, being
                        compiled and linked to pull the code into is from the
                        static library. These changes allow me to incorporate
                        GetBom_P6C into stand alone programs, such as
                        WWCountLines, that need its capabilities.

    Created:            Saturday, 15 April 2006

    License:            Copyright (C) 2006-2016, David A. Gray. All rights reserved.

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
    2006/04/15 DAG First working version.

    2007/11/08 DAG Move to its own header, and into static link library P6CLIB1.
                   The only code changes were the removal of the contents of
                   this header from WWTrimLog.H. Please see the Remarke section
                   for details.

    2010/03/08 DAG Add #pragma once, and move extern "C" just above the function
                   prototypes.

    2010/04/25 DAG Reinstate direct inclusion of windows.h, since, as of this
                   date, CommonConstants_P6C.H works just fine without it.

    2010/06/04 DAG Move the #pragma once preprocessor directive outside the
                   scope of the preprocessor variable which performs the same
                   function for other C compilers.

    2012/06/30 DAG Based on recently gained knowledge of how various guard code
                   schemes work, move the #pragma once block inside the block
                   protected by the preprocessor guard variable.

    2013/06/18 DAG Eliminate an overlooked reference to CommonConstants_P6C.H
                   and substitute Const_Typedefs_WW.H, which is plenty for a
                   public interface. This update is built into P6CStringLib1,
                   version 2,8,1,0.

                   While I'm at it, implement LIBSPEC_P6CSTRINGLIB1_API.

    2015/10/05 DAG Replace BOMINFOP6C member dwBOMType with an enumerated type,
                   GETBOM_RESULT_P6C, renamed enmBOMType.

    2016/01/10 DAG Wrap the code that defines LIBSPEC_P6CSTRINGLIB1_API in guard
                   code, and insert my three-clause BSD license.

    2016/01/22 DAG Add the inverse function, SetBOM, to append a Byte Order Mark
                   to a string.
    ============================================================================
*/

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /* #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

#include <windows.h>

#include <Const_Typedefs_WW.H>

#if defined ( _P6CSTRINGLIB1_DEFINED )
    #pragma message ( "GetBom_P6C.H: Calling convention in this translation unit was established by P6CStringLib1.H." )
#else
    #if defined ( _BUILDING_P6CSTRINGLIB1 )
        #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllexport)
    #else
        #if defined (  _P6CSTRINGLIB1 )
            #define LIBSPEC_P6CSTRINGLIB1_API extern
        #else   /*  #ifdef _P6CSTRINGLIB1 */
            #define LIBSPEC_P6CSTRINGLIB1_API __declspec(dllimport)
        #endif  /*  #if defined (  _P6CSTRINGLIB1 ) */
    #endif  /* #if defined ( _BUILDING_P6CSTRINGLIB1 ) */
#endif	/* #if defined ( _P6CSTRINGLIB1_DEFINED ) */

//  ----------------------------------------------------------------------------
//  Define public constants, primarily error and status codes.
//  ----------------------------------------------------------------------------

//  ----------------------------------------------------------------------------
//  Define the maximum size, in BYTES, of a Byte Order Mark.
//  ----------------------------------------------------------------------------

#define UNICODE_BOM_SIZE_P6C            2
#define UNICODE_REV_BOM_SIZE_P6C        2
#define UTF8_BOM_SIZE_P6C               3
#define BOM_SIZE_MAX_P6C                4

#define SETBOM_NULL_POINTER				( 0x00000001 | APPLICATION_ERROR_MASK )

//  ----------------------------------------------------------------------------
//  The following enumeration replaces symbolic constant macros previously used
//	with the dwBOMType member that it replaces. Notwithstanding that the number
//	of calls into this function are so few, I am changing both the type and name
//	of the DWORD dwBOMType that it replaces, to GETBOM_RESULT_P6C enmBOMType.
//  ----------------------------------------------------------------------------

typedef enum _GETBOM_RESULT_P6C
{
    GETBOM_UNINITIALIZED_RESULT_P6C		= 0 ,
    TEXT_HAS_INSUFF_DATA_P6C			= 1 ,
    TEXT_HAS_NO_SIG_P6C					= 2 ,
    TEXT_HAS_UNICODE_SIG_P6C			= 3 ,
    TEXT_HAS_UNICODE_REV_SIG_P6C		= 4 ,
    TEXT_HAS_UTF8_SIG_P6C				= 5 ,
    TEXT_RESULT_OUT_OF_BOUNDS			= 6
} GETBOM_RESULT_P6C ;

//	-----------------------------------------------------------------------------
//	Use this type to set the penmType argument of SetBOM.
//	-----------------------------------------------------------------------------

typedef enum _BOM_TYPE_P6C
{
    BOM_TYPE_UNICODE_LE_WINDOWS_INTEL	= 0 ,
    BOM_TYPE_UNICODE_BE_ALPHA_MAINFRAME	= 1 ,
    BOM_TYPE_UTF8						= 2
} BOM_TYPE_P6C ;

typedef const BOM_TYPE_P6C				CBOM_TYPE_P6C ;

//	-----------------------------------------------------------------------------
//	Use this type to set the penmOrigDisposition argument of SetBOM.
//	-----------------------------------------------------------------------------

typedef enum _ORIGINAL_DISPOSITION {
    ORIGINAL_DISP_KEEP					= 0 ,
    ORIGINAL_DISP_DISCARD				= 1 ,
    ORIGINAL_DISP_SECURE				= 2
} ORIGINAL_DISPOSITION ;

typedef const ORIGINAL_DISPOSITION		CORIGINAL_DISPOSITION ;

//  ----------------------------------------------------------------------------
//  Data structure used by function GetBOM_P6C, kept in caller's address space
//  and passed by reference.
//  ----------------------------------------------------------------------------

typedef struct BOM_INFO_P6C {
    LPVOID            lpCharBuff ;                      // [in] Pointer to buffer to be evaluated.
    DWORD             dwNBytes ;                        // [in] Size, in BYTES, of buffer to be evaluated.
    char              szBOM [ BOM_SIZE_MAX_P6C ] ;      // [out] Buffer to hold Byte Order Mark, if one is present.
    int               intBOMSize ;                      // [out] Size, in BYTES, of Byte Order Mark, if one is present.
    GETBOM_RESULT_P6C enmBOMType ;                      // [out] Type code identifying type of Byte Order Mark found, if any.
} BOMINFOP6C, FAR *LPBOMINFOP6C ;


//  ----------------------------------------------------------------------------
//	Define functions , all having "C" linkage , so that they work with both C
//  and C++ code.
//  ----------------------------------------------------------------------------

#if defined ( __cplusplus )
extern "C"
{
#endif	/* __cplusplus */

/*
    ============================================================================

    Name:               GetBOM_P6C

    Synopsis:           Given a buffer of at least 3 bytes that contains some
                        text of indeterminate type, which may be either Unicode,
                        Unicode Big Endian, or UTF-8, with or without a Byte
                        Order Marker (BOM), find and extract the BOM, if present.

    Arguments:          BOMINFOP6C           = Data structure composed of the
                                               following members.

                                  lpCharBuff = [in] Pointer to the buffer that
                                               contains the text from which the
                                               Byte Order Mark, if present, is
                                               to be extracted.

                                  dwNBytes   = [in] Unsigned integer containing
                                               size, in bytes, of the buffer to
                                               which lpCharBuff points.

                                  szBOM      = [out] Buffer to hold Byte Order
                                               Mark, if one exists, organized as
                                               an array of char types.

                                  intBOMSize = [out] Size, in BYTES, of Byte Order
                                               Mark, if one is present.

                                  enmBOMType = [out] Code identifying type of
                                               Byte Order Mark found, if any,
                                               expressed as a member of the
                                               GETBOM_RESULT_P6C enumeration.

    Returns:            If the function succeeds, BOMINFOP6C member enmBOMType 
                        is set to a member of the GETBOM_RESULT_P6C enumeration.
                        GETBOM_UNINITIALIZED_RESULT_P6C indicates an enmBOMType
                        that is uninitialized, while TEXT_RESULT_OUT_OF_BOUNDS,
                        should it ever appear, indicates a corrupted structure.

    Remarks:            1)  The BOMINFOP6C structure is passed by reference, and
                            its three output members need not be initialized
                            before the function is called.

                        2)  This function uses a variety of methods to ensure
                            that it always returns a valid Byte Order Mark, or
                            leaves the members of the szBOM array set to NULL if
                            no marker is present.

                        3)  Check the value of enmBOMType for status information.
                            A value of TEXT_HAS_INSUFF_DATA_P6C indicates a
                            buffer size too short to contain a Byte Order Mark.

    Created:            Friday, 14 April 2006 through Saturday, 15 April 2006.

    ----------------------------------------------------------------------------
    Revision History
    ----------------------------------------------------------------------------

    Date       Version    By  Synopsis
    ---------- ---------- --- --------------------------------------------------
    04/15/2006 1, 0, 0, 1 DAG First working version.

    2007/11/08 1, 0, 0, 3 DAG Move to its own header, and into static link
                              library P6CLIB1. The only code changes were the
                              removal of the contents of this header from
                              WWTrimLog.H. Please see Notes for details.

    2015/10/05 3, 3, 0, 5 DAG Replace BOMINFOP6C member dwBOMType with an
                              enumerated type, GETBOM_RESULT_P6C, renamed
                              enmBOMType.
    ============================================================================
*/

void LIBSPEC_P6CSTRINGLIB1_API GetBOM_P6C ( BOMINFOP6C * ) ;


/*
    ============================================================================

    Name:               SetBOM

    Synopsis:           Append a encoding agnostic block of bytes to a specified
                        type of Byte Order Marks.

    Arguments:          plpBytes             = Void pointer to block of bytes

                        puintCBytes			 = Size of block to which plpBytes
                                               points, in bytes

                        penmType             = The BOM_TYPE_P6C enumeration
                                               member that specifies which type
                                               of Byte Order Mark is desired

                        penmOrigDisposition	= The ORIGINAL_DISPOSITION member
                                              that specifies disposition of the
                                              buffer to which plpBytes points

    Returns:			If the function succeeds, the return value is a new
                        block of bytes that begins with the specified Byte Order
                        Mark, followed immediately by the block of bytes to
                        which plpBytes points.
                        
                        If plpBytes is NULL, the function returns NULL, and sets
                        LastError to SETBOM_NULL_POINTER.

                        iF puintCBytes is zero, the function calls HeapSize with
                        plpBytes, and uses its return value as its size.

                        If the function cannot allocate enough memory to hold a
                        BOM followed by the input block, it returns NULL, and
                        LastError returns a system status code. Allocation is
                        handled by a routine that employs Structured Exception
                        Handling, which has the potential to yield better clues.
    ============================================================================
*/

LIBSPEC_P6CSTRINGLIB1_API LPBYTE __stdcall SetBOM
(
    CLPBYTE					plpBytes ,
    CUINT					puintCBytes ,
    CBOM_TYPE_P6C			penmType ,
    CORIGINAL_DISPOSITION	penmOrigDisposition
) ;

// Close the block of code that has "C" linkage.
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif  /*  _GETBOM_P6C_DEFINED */