//  ============================================================================
//
//  File Name:          ReformatSysDate_P6C_FormatStrings.H
//
//  Synopsis:           The symbolic constants defined in this C header file
//                      correspond to the resource strings defined in Windows
//                      resource script ReformatSysDate_P6C_FormatStrings.RC,
//                      which are intended for use with ReformatSysDate_P6C(),
//                      which is exported by WWDateLib.dll.
//
//  Remarks:            Although intended for use with WWDateLib.dll, this
//                      satellite DLL is NOT auto-loaded by it, because there
//                      are many legacy programs that have embedded format
//                      strings.
//
//                      Any project that includes the resource strings defined
//                      in ReformatSysDate_P6C_FormatStrings.RC and exported by
//                      resource only DLL ReformatSysDate_P6C_FormatStrings.DLL
//                      must include this header, and LoadLibraryEx to load
//                      it.
//
//						NOTE:	If ReformatSysDate_P6C_FormatStrings.dll and
//                      		WWDateLib.dll are installed into the same
//                      		directory, as I intended, you can call
//                      		LoadFormatStringLibrary_P6C (in WWDateLib.dll)
//                      		to load the the satellite DLL, because it knows
//                      		how to find it in a side by side installation.
//
//                      Please see ReformatSysDate_P6C_FormatStrings.RC to learn
//                      about the format strings.
//
//  Author:             David A. Gray
//
//  Copyright:          Copyright 2011-2012, David A. Gray, Irving, Texas, USA.
//                      All rights reserved world wide.
//
//                      This code may be freely reproduced, so long as it
//                      remains intact, including this copyright notice and
//                      license.
//
//                      However, since it is in the public domain, it is
//                      unsupported in any way and carries no warranty. Use it
//                      at your own risk.
//
//  Date Written:       Tuesday, 23 August 2011
//
//  ----------------------------------------------------------------------------
//  Revision History
//  ----------------------------------------------------------------------------
//
//  Date       Version   Author Synsopsis
//  ---------- --------- ------ ------------------------------------------------
//  2011/08/23 1,3,127,1 DAG/WW Initial implementation.
//  2012/01/31 2,0,128,1 DAG/WW Add millisecond formats and clean up everything.
//  2012/02/05 2,0,128,1 DAG/WW Add standard preprocessor macros to prevent
//                              redefinition. Since the DLL is unaffected, the
//                              version number is unchanged.
//  2012/06/02 2,1,129,1 DAG/WW Add /OPT:NOWIN98 to the linkage editor options.
//  ============================================================================


#if defined (_MSC_VER) && (_MSC_VER >= 1020)
    #pragma once
#endif  /*  #if defined (_MSC_VER) && (_MSC_VER >= 1020) */

#ifndef __REFORMATSYSDATE_P6C_INCLUDED__
#define __REFORMATSYSDATE_P6C_INCLUDED__

#define IDS_FORMAT_WYMDHMS_UTC                  1
#define IDS_FORMAT_WYMDHMS_LOCAL                2
#define IDS_FORMAT_WYMDHMS_EITHER               3

#define IDS_FORMAT_YMDHMS_UTC                   4
#define IDS_FORMAT_YMDHMS_LOCAL                 5
#define IDS_FORMAT_YMDHMS_EITHER                6

#define IDS_FORMAT_WDDMMMYYYYHHMMSS_UTC         7
#define IDS_FORMAT_WDDMMMYYYYHHMMSS_LOCAL       8
#define IDS_FORMAT_WDDMMMYYYYHHMMSS_EITHER      9

#define IDS_FORMAT_HHMMSS_UTC                  10
#define IDS_FORMAT_HHMMSS_LOCAL                11
#define IDS_FORMAT_HHMMSS_EITHER               12

#define IDS_FORMAT_WDDMMYYYY_UTC               13
#define IDS_FORMAT_WDDMMYYYY_LOCAL             14
#define IDS_FORMAT_WDDMMYYYY_EITHER            15

#define IDS_FORMAT_DDMMYYYY_UTC                16
#define IDS_FORMAT_DDMMYYYY_LOCAL              17
#define IDS_FORMAT_DDMMYYYY_EITHER             18

#define IDS_FORMAT_MMDDYYYY_UTC                19
#define IDS_FORMAT_MMDDYYYY_LOCAL              20
#define IDS_FORMAT_MMDDYYYY_EITHER             21

#define IDS_FORMAT_YYYYMMDD_UTC                22
#define IDS_FORMAT_YYYYMMDD_LOCAL              23
#define IDS_FORMAT_YYYYMMDD_EITHER             24

#define IDS_FORMAT_MMDDYYYYHHMMSS_UTC          25
#define IDS_FORMAT_MMDDYYYYHHMMSS_LOCAL        26
#define IDS_FORMAT_MMDDYYYYHHMMSS_EITHER       27

#define IDS_FORMAT_YYYYMMDDHHMMSS_UTC          28
#define IDS_FORMAT_YYYYMMDDHHMMSS_LOCAL        29
#define IDS_FORMAT_YYYYMMDDHHMMSS_EITHER       30

#define IDS_FORMAT_SORTABLEYMDHMS_UTC          31
#define IDS_FORMAT_SORTABLEYMDHMS_LOCAL        32
#define IDS_FORMAT_SORTABLEYMDHMS_EITHER       33

#define IDS_FORMAT_SORTABLEYMD_UTC             34
#define IDS_FORMAT_SORTABLEYMD_LOCAL           35
#define IDS_FORMAT_SORTABLEYMD_EITHER          36

#define IDS_FORMAT_SORTABLEHMS_UTC             37
#define IDS_FORMAT_SORTABLEHMS_LOCAL           38
#define IDS_FORMAT_SORTABLEHMS_EITHER          39

#define IDS_FORMAT_WWDDMMMYYYYHHMMSS_UTC       40
#define IDS_FORMAT_WWDDMMMYYYYHHMMSS_LOCAL     41
#define IDS_FORMAT_WWDDMMMYYYYHHMMSS_EITHER    42

#define IDS_FORMAT_YYYYMMDMHMS_MILLISECONDS    43
#define IDS_FORMAT_SORTABLEHHMMSS_MILLISECONDS 44

//  ----------------------------------------------------------------------------
//  Next default values for new objects.
//  ----------------------------------------------------------------------------

#ifdef APSTUDIO_INVOKED
    #ifndef APSTUDIO_READONLY_SYMBOLS
        #define _APS_NEXT_RESOURCE_VALUE           102
        #define _APS_NEXT_COMMAND_VALUE            40001
        #define _APS_NEXT_CONTROL_VALUE            1000
        #define _APS_NEXT_SYMED_VALUE              101
    #endif  /*  #ifndef APSTUDIO_READONLY_SYMBOLS */
#endif  /*  #ifdef APSTUDIO_INVOKED */
#endif  /*  __REFORMATSYSDATE_P6C_INCLUDED__ */
