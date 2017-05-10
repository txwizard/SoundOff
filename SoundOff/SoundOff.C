#include ".\SoundOff.H"

int _tmain ( int argc , TCHAR **argv )
{
	DWORD	rdwStatus = ERROR_SUCCESS;

	LPTSTR	lpPgmName = AnnounceMeToCRTPN_WW ( VER_USING_LABELS_IN_DLL_P6C ,
		                                       VER_LABELS_FROM_DLL_P6C ,
		                                       VER_BRIEF_BANNER ) ;

	if ( lpPgmName )
	{
		if ( argc > ARGV_FIRST_CMDLINE_ARG_P6C )
		{
			_tprintf ( SOff_GetUnicodeStringPointer ( FB_LOOK_IN_THIS_EXE , 
				                                      IDS_STRING104 ,
													  FB_HIDE_LENGTH ) ,
					   argv [ ARGV_FIRST_CMDLINE_ARG_P6C ] );

			if ( PlaySound ( argv [ ARGV_FIRST_CMDLINE_ARG_P6C ] ,				// LPCTSTR pszSound = A string that specifies the sound to play. The maximum length, including the null terminator, is 256 characters.
				             LP_UNUSED ,										// HMODULE hMod		= Handle to the executable file that contains the resource to be loaded. This parameter must be NULL unless SND_RESOURCE is specified in fdwSound.
							 SND_FILENAME | SND_NODEFAULT | SND_SYNC ) )		// DWORD   fdwSound	= Flags for playing the sound.
			{	// Sound is playing in a thread that presumably belongs to the system.
				_tprintf ( SOff_GetUnicodeStringPointer ( FB_LOOK_IN_THIS_EXE ,
					                                      IDS_STRING105 ,
					                                      FB_HIDE_LENGTH ) ,
					       lpPgmName );
			}	// TRUE (anticipated outcome) block, if ( PlaySound ( argv [ 1 ] , NULL , SND_FILENAME | SND_NODEFAULT | SND_SYNC ) )
			else
			{	// PlaySound failed, leaving a status code in LastError.
				rdwStatus = GetLastError ( );
				_tprintf ( FB_FormatMessage2 ( IDS_STRING102 ,
					                           rdwStatus ,
											   SCF2_HEXADECIMAL ) );
			}	// FALSE (unanticipated outcome) block, if ( PlaySound ( argv [ 1 ] , NULL , SND_FILENAME | SND_NODEFAULT | SND_SYNC ) )
		}	// TRUE (anticipated outcome) block, if ( argc >= 2 )
		else
		{
			return 1;
		}	// FALSE (unanticipated outcome) block, if ( argc >= 2 )
	}	// TRUE (anticipated outcome) block, if ( lpPgmName )
	else
	{	// AnnounceMeToCRTPN_WW failed, leaving a status code in LastError.
		rdwStatus = GetLastError ( );
		_tprintf ( FB_FormatMessage2 ( IDS_STRING103 ,
			                           rdwStatus ,
			                           SCF2_HEXADECIMAL ) );
	}	// FALSE (unanticipated outcome) block, if ( lpPgmName )

	return rdwStatus;
}	// main