; Listing generated by Microsoft (R) Optimizing Compiler Version 18.00.31101.0 

	TITLE	C:\Users\DAVE\Documents\Programming\Visual_Studio_6\EXE\Console\SoundOff\SoundOff\SoundOff.C
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

EXTRN	__imp__PlaySoundW@12:PROC
EXTRN	__imp__AnnounceMeToCRTPNW_WW@12:PROC
PUBLIC	_wmain
; Function compile flags: /Ogtp
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soundoff.c
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soff_getunicodestringpointer.c
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soundoff.c
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soff_getunicodestringpointer.c
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soundoff.c
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soff_getunicodestringpointer.c
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soundoff.c
;	COMDAT _wmain
_TEXT	SEGMENT
_lpTheString$1 = -4					; size = 4
_lpTheString$2 = -4					; size = 4
_argc$ = 8						; size = 4
_argv$ = 12						; size = 4
_wmain	PROC						; COMDAT

; 4    : {

	push	ebp
	mov	ebp, esp
	push	ecx
	push	ebx
	push	edi

; 5    : 	DWORD	rdwStatus = ERROR_SUCCESS;

	xor	edi, edi

; 6    : 
; 7    : 	LPTSTR	lpPgmName = AnnounceMeToCRTPN_WW ( VER_USING_LABELS_IN_DLL_P6C ,
; 8    : 		                                       VER_LABELS_FROM_DLL_P6C ,
; 9    : 		                                       VER_BRIEF_BANNER ) ;

	push	edi
	push	1
	push	edi
	call	DWORD PTR __imp__AnnounceMeToCRTPNW_WW@12
	mov	ebx, eax

; 10   : 
; 11   : 	if ( lpPgmName )

	test	ebx, ebx
	je	$LN6@wmain

; 12   : 	{
; 13   : 		if ( argc > ARGV_FIRST_CMDLINE_ARG_P6C )

	cmp	DWORD PTR _argc$[ebp], 1
	jle	$LN5@wmain
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soff_getunicodestringpointer.c

; 33   : 			              RCDATA_INPLACE_POINTER ) )							// _In_     int       nBufferMax

	push	edi
	lea	eax, DWORD PTR _lpTheString$2[ebp]
	mov	DWORD PTR _lpTheString$2[ebp], edi
	push	eax
	push	104					; 00000068H
	push	edi
	call	DWORD PTR __imp__LoadStringW@16
	test	eax, eax
	je	SHORT $LN9@wmain

; 34   : 		{	// Have pointer, will return.
; 35   : 			return lpTheString ;

	mov	eax, DWORD PTR _lpTheString$2[ebp]
	jmp	SHORT $LN13@wmain
$LN9@wmain:

; 49   : 		                                           RCDATA_INPLACE_POINTER ) ;

	push	ecx
	mov	edx, 104				; 00000068H
	call	_SOff_ReportLoadStringError@12
$LN13@wmain:
	push	esi
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soundoff.c

; 18   : 					   argv [ ARGV_FIRST_CMDLINE_ARG_P6C ] );

	mov	esi, DWORD PTR _argv$[ebp]
	push	DWORD PTR [esi+4]
	push	eax
	call	DWORD PTR __imp__wprintf
	add	esp, 8

; 19   : 
; 20   : 			if ( PlaySound ( argv [ ARGV_FIRST_CMDLINE_ARG_P6C ] ,				// LPCTSTR pszSound = A string that specifies the sound to play. The maximum length, including the null terminator, is 256 characters.
; 21   : 				             LP_UNUSED ,										// HMODULE hMod		= Handle to the executable file that contains the resource to be loaded. This parameter must be NULL unless SND_RESOURCE is specified in fdwSound.
; 22   : 							 SND_FILENAME | SND_NODEFAULT | SND_SYNC ) )		// DWORD   fdwSound	= Flags for playing the sound.

	push	131074					; 00020002H
	push	0
	push	DWORD PTR [esi+4]
	call	DWORD PTR __imp__PlaySoundW@12
	pop	esi
	test	eax, eax
	je	SHORT $LN4@wmain
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soff_getunicodestringpointer.c

; 33   : 			              RCDATA_INPLACE_POINTER ) )							// _In_     int       nBufferMax

	push	0
	lea	eax, DWORD PTR _lpTheString$1[ebp]
	mov	DWORD PTR _lpTheString$1[ebp], edi
	push	eax
	push	105					; 00000069H
	push	0
	call	DWORD PTR __imp__LoadStringW@16
	test	eax, eax
	je	SHORT $LN15@wmain

; 34   : 		{	// Have pointer, will return.
; 35   : 			return lpTheString ;

	mov	eax, DWORD PTR _lpTheString$1[ebp]
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soundoff.c

; 27   : 					       lpPgmName );

	push	ebx
	push	eax
	mov	eax, DWORD PTR __imp__wprintf
	call	eax
	add	esp, 8

; 48   : 	}	// FALSE (unanticipated outcome) block, if ( lpPgmName )
; 49   : 
; 50   : 	return rdwStatus;

	mov	eax, edi
	pop	edi
	pop	ebx

; 51   : }	// main

	mov	esp, ebp
	pop	ebp
	ret	0
$LN15@wmain:
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soff_getunicodestringpointer.c

; 49   : 		                                           RCDATA_INPLACE_POINTER ) ;

	push	ecx
	mov	edx, 105				; 00000069H
	call	_SOff_ReportLoadStringError@12
; File c:\users\dave\documents\programming\visual_studio_6\exe\console\soundoff\soundoff\soundoff.c

; 27   : 					       lpPgmName );

	push	ebx
	push	eax
	mov	eax, DWORD PTR __imp__wprintf
	call	eax
	add	esp, 8

; 48   : 	}	// FALSE (unanticipated outcome) block, if ( lpPgmName )
; 49   : 
; 50   : 	return rdwStatus;

	mov	eax, edi
	pop	edi
	pop	ebx

; 51   : }	// main

	mov	esp, ebp
	pop	ebp
	ret	0
$LN4@wmain:

; 28   : 			}	// TRUE (anticipated outcome) block, if ( PlaySound ( argv [ 1 ] , NULL , SND_FILENAME | SND_NODEFAULT | SND_SYNC ) )
; 29   : 			else
; 30   : 			{	// PlaySound failed, leaving a status code in LastError.
; 31   : 				rdwStatus = GetLastError ( );

	call	DWORD PTR __imp__GetLastError@0
	mov	edi, eax

; 32   : 				_tprintf ( FB_FormatMessage2 ( IDS_STRING102 ,
; 33   : 					                           rdwStatus ,
; 34   : 											   SCF2_HEXADECIMAL ) );

	push	0
	push	edi
	push	102					; 00000066H
	call	DWORD PTR __imp__FB_FormatMessage2W
	push	eax
	mov	eax, DWORD PTR __imp__wprintf
	call	eax

; 45   : 		_tprintf ( FB_FormatMessage2 ( IDS_STRING103 ,
; 46   : 			                           rdwStatus ,
; 47   : 			                           SCF2_HEXADECIMAL ) );

	add	esp, 16					; 00000010H

; 48   : 	}	// FALSE (unanticipated outcome) block, if ( lpPgmName )
; 49   : 
; 50   : 	return rdwStatus;

	mov	eax, edi
	pop	edi
	pop	ebx

; 51   : }	// main

	mov	esp, ebp
	pop	ebp
	ret	0
$LN5@wmain:
	pop	edi

; 35   : 			}	// FALSE (unanticipated outcome) block, if ( PlaySound ( argv [ 1 ] , NULL , SND_FILENAME | SND_NODEFAULT | SND_SYNC ) )
; 36   : 		}	// TRUE (anticipated outcome) block, if ( argc >= 2 )
; 37   : 		else
; 38   : 		{
; 39   : 			return 1;

	mov	eax, 1
	pop	ebx

; 51   : }	// main

	mov	esp, ebp
	pop	ebp
	ret	0
$LN6@wmain:

; 40   : 		}	// FALSE (unanticipated outcome) block, if ( argc >= 2 )
; 41   : 	}	// TRUE (anticipated outcome) block, if ( lpPgmName )
; 42   : 	else
; 43   : 	{	// AnnounceMeToCRTPN_WW failed, leaving a status code in LastError.
; 44   : 		rdwStatus = GetLastError ( );

	call	DWORD PTR __imp__GetLastError@0
	mov	edi, eax

; 45   : 		_tprintf ( FB_FormatMessage2 ( IDS_STRING103 ,
; 46   : 			                           rdwStatus ,
; 47   : 			                           SCF2_HEXADECIMAL ) );

	push	0
	push	edi
	push	103					; 00000067H
	call	DWORD PTR __imp__FB_FormatMessage2W
	push	eax
	call	DWORD PTR __imp__wprintf
	add	esp, 16					; 00000010H

; 48   : 	}	// FALSE (unanticipated outcome) block, if ( lpPgmName )
; 49   : 
; 50   : 	return rdwStatus;

	mov	eax, edi
	pop	edi
	pop	ebx

; 51   : }	// main

	mov	esp, ebp
	pop	ebp
	ret	0
_wmain	ENDP
_TEXT	ENDS
END