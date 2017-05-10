// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
//  ============================================================================
//  SoundOff.H was initially generated as stdafx.h by the New Project wizard, 
//	but I transformed it into the main application header (include) file, since
//	this project doesn't use compiled headers.
//
//  Copyright:          2017, David A.Gray. All rights reserved world wide.
//
//  ----------------------------------------------------------------------------
//  Revision History
//  ----------------------------------------------------------------------------
//
//  Date       By  Synopsis
//  ---------- --- -------------------------------------------------------------
//  2017/05/09 DAG The program for which this is the header was completed.
//  ============================================================================

#pragma once

#include ".\targetver.h"

#include <StandardMacros_DAG.H>

#include <AnnounceMeToCRT_WW.H>
#include <FixedStringBuffers.H>

#include "resource.h"

#if defined ( __cplusplus )
extern "C"
{
#endif  /* #if defined ( __cplusplus ) */
    //  ------------------------------------------------------------------------
    //  Function Name:      SOff_GetUnicodeStringPointer
    //
    //  Abstract:           Get a pinter to a null terminated string resource
    //                      for use, in situ, by any routine that deals in such
    //                      strings.
    //
    //  In:                 1)  phSourceModule is either the instance handle of
    //                          the module from which the string was expected to
    //                          be read, or NULL, indicating that the source is
    //                          the first PE file that was loaded into the
    //                          current process.
    //
    //                      2)  puintStringID is the unsigned integer resource
    //                          (string) ID that was sought.
    //
    //                      1)  plpuintLength is the location where the length
    //                          of the returned string should be written, if the
    //                          calling routine needs it. Otherwise, the pointer
    //                          may be NULL.
    //
    //  Out:                If it succeeds, the return value is a pointer to the
    //                      desired null terminated Unicode string resource. If
    //                      the desired string cannot be found in the specified
    //                      module, the return value is NULL, and a call to
    //                      GetLastError should give some hint about why the
    //                      call failed.
    //
    //  Remarks:            Since this routine supports only Unicode strings, it
    //                      has a return type of LPWSTR.
    //
    //                      The documented return value of LoadString excludes
    //                      the trailing null from the reported string length.
    //                      However, when nBufferMax = RCDATA_INPLACE_POINTER,
    //                      it is included. Hence, for consistency, this routine
    //                      deducts one from the return value when reporting the
    //                      length of the string.
    //  ------------------------------------------------------------------------

    LPWSTR __stdcall SOff_GetUnicodeStringPointer
    (
        CHMODULE                phSourceModule ,            // HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
		FB_RES_STRING_ID        puintStringID ,             // Resource ID of string to load
        CLPUINT                 plpuintLength               // Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
    ) ;

    //  ------------------------------------------------------------------------
    //  Function Name:      SOff_GetUnicodeStringPointer
    //
    //  Abstract:           Get a pinter to a null terminated string resource
    //                      for use, in situ, by any routine that deals in such
    //                      strings.
    //
    //  In:                 1)  phSourceModule is either the instance handle of
    //                          the module from which the string was expected to
    //                          be read, or NULL, indicating that the source is
    //                          the first PE file that was loaded into the
    //                          current process.
    //
    //                      2)  puintStringID is the unsigned integer resource
    //                          (string) ID that was sought.
    //
    //                      1)  plpuintLength is the location where the length
    //                          of the returned string should be written, if the
    //                          calling routine needs it. Otherwise, the pointer
    //                          may be NULL.
    //
    //  Out:                If it succeeds, the return value is a pointer to the
    //                      desired null terminated Unicode string resource. If
    //                      the desired string cannot be found in the specified
    //                      module, the return value is NULL, and a call to
    //                      GetLastError should give some hint about why the
    //                      call failed.
    //
    //  Remarks:            Since this routine supports only Unicode strings, it
    //                      has a return type of LPWSTR.
    //
    //                      The documented return value of LoadString excludes
    //                      the trailing null from the reported string length.
    //                      However, when nBufferMax = RCDATA_INPLACE_POINTER,
    //                      it is included. Hence, for consistency, this routine
    //                      deducts one from the return value when reporting the
    //                      length of the string.
    //  ------------------------------------------------------------------------

    LPWSTR __stdcall SOff_GetUnicodeStringPointer
    (
        CHMODULE                phSourceModule ,            // HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
		FB_RES_STRING_ID        puintStringID ,             // Resource ID of string to load
        CLPUINT                 plpuintLength               // Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
    ) ;

    //  ------------------------------------------------------------------------
    //  Function Name:      SOff_ReportLoadStringError
    //
    //  Abstract:           If the specified status code is nonzero, set it into
    //                      the system status code location, where GetLastError
    //                      can find it, then return it. Otherwise, return the
    //                      result from a call to GetLastError.
    //
    //  In:                 1)  phSourceModule is either the instance handle of
    //                          the module from which the string was expected to
    //                          be read, or NULL, indicating that the source is
    //                          the first PE file that was loaded into the
    //                          current process.
    //
    //                      2)  puintStringID is the unsigned integer resource
    //                          (string) ID that was sought.
    //
    //                      3)  puintBufferID is the buffer index, the array
    //                          subscript of the destination buffer. This value
    //                          is also zero for a Unicode string that is being
    //                          used in situ.
    //
    //  Out:                Since this function always returns through a
    //                      LoadString routine, which called it to handle an
    //                      error, it always returns NULL, signaling the
    //                      routine that requested the string that an error
    //                      prevented it being loaded. Please see the Remarks
    //                      section for additional information.
    //
    //  Remarks:            Since it must return NULL to signal an error, and it has
    //                      no decent way of knowing whether or how to display a
    //                      message about the error, the message is constructed in
    //                      the buffer to which externally linked pointer
    //                      m_lpErrMsgSprintf points, from which it can be retrieved
    //                      by calling FB_GetlpErrMsgSprintf.
    //  ----------------------------------------------------------------------------

    DWORD __stdcall SOff_ReportLoadStringError
    (
        CHMODULE            phSourceModule ,                // HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
		FB_RES_STRING_ID    puintStringID ,                 // Resource ID of string to load
        CUINT               puintBufferID                   // Index of that was designated in the original call.
    );
#if defined ( __cplusplus )
}
#endif  /* #if defined ( __cplusplus ) */