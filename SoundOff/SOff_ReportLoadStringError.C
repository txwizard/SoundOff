#include ".\SoundOff.H"

DWORD __stdcall SOff_ReportLoadStringError
(
	CHMODULE			phSourceModule ,
	FB_RES_STRING_ID	puintStringID ,
	CUINT				puintBufferID
)
{
	DWORD dwStatus = GetLastError ( ) ;

	if ( dwStatus )
	{
		if ( FB_LoadFixedString_DfltBuf ( IDS_STRING_LOAD_ERROR_1 ) )
		{
			_stprintf ( FB_GetSprintFBuffer ( FB_FIRST_BUFFER_INDEX ) ,
				        FB_GetlpResourceBuffer ( FB_FIRST_BUFFER_INDEX ) ,
				        puintStringID ) ;
			_tprintf ( FB_FormatMessage ( FB_GetlpResourceBuffer ( FB_FIRST_BUFFER_INDEX ) ,
				                          dwStatus ,
				                          SCF2_HEXADECIMAL ) ) ;
		}   // if ( FB_LoadFixedString_DfltBuf ( IDS_STRING_LOAD_ERROR_1 ) )
	}   // TRUE block, if ( dwStatus )
	else
	{	// Since Windows provided no error, we supply our own.
		dwStatus = FB_ERR_STRNG_NOT_FOUND_FOR_ID ;
		SetLastError ( dwStatus );
		_tprintf ( FB_FormatMessage2 ( IDS_STRING_LOAD_ERROR_2 ,
  			                           dwStatus ,
				                       SCF2_HEXADECIMAL ) ) ;
	}   // FALSE block, if ( dwStatus )

	//	------------------------------------------------------------------------
	//	Raise a structured exception if the SEH flag is set. When this happens,
	//	there is no actual return, and the stack is unwound.
	//	------------------------------------------------------------------------

	return dwStatus ;	// Tell the calling routine to call GetLastError and/or FB_GetlpErrMsgSprintf (to get the message).
}	// SOff_ReportLoadStringError
