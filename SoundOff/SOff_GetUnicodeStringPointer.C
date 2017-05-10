//	============================================================================
//  SOff_GetUnicodeStringPointer.C: Get a pointer to a null terminated resource
//                                   string.
//	============================================================================

#include ".\SoundOff.H"

LPWSTR __stdcall SOff_GetUnicodeStringPointer
(
	CHMODULE                phSourceModule ,									// HINSTANCE of module containing the strings, per LoadLibraryEx or DLLMain
	FB_RES_STRING_ID		puintStringID ,										// Resource ID of string to load
	CLPUINT                 plpuintLength										// Pointer to a UINT (unsigned 32 bit integer) to receive the length, in TCHARs (characters) of the returned string, or FB_HIDE_LENGTH (NULL) if you don't want it
)
{
	LPTSTR lpTheString = NULL ;

	if ( plpuintLength )
	{	// The documented return value of LoadString excludes the trailing null. However, when nBufferMax = RCDATA_INPLACE_POINTER, it is included.
		if ( *plpuintLength = ( LoadString ( phSourceModule ,					// _in_     HMODULE   hModule
                                           puintStringID ,						// _In_     UINT      uID
									       ( LPTSTR ) &lpTheString ,			// _Out_    LPTSTR    lpBuffer
										   RCDATA_INPLACE_POINTER ) 			// _In_     int       nBufferMax
											- TRAILING_NULL_ALLOWANCE_P6C ) )
		{	// Have pointer, will return.
			return lpTheString ;
		}	// if ( ( *plpuintLength = LoadString ( phSourceModule , puintStringID , ( LPTSTR ) &lpTheString , RCDATA_INPLACE_POINTER ) ) )
	}	// TRUE (Return the string length through the supplied pointer) block, if ( plpuintLength )
	else
	{
		if ( LoadString ( phSourceModule ,										// _in_     HMODULE   hModule
			              puintStringID ,										// _In_     UINT      uID
			              ( LPTSTR ) &lpTheString ,								// _Out_    LPTSTR    lpBuffer
			              RCDATA_INPLACE_POINTER ) )							// _In_     int       nBufferMax
		{	// Have pointer, will return.
			return lpTheString ;
		}	// if ( LoadString ( phSourceModule , puintStringID , ( LPTSTR ) &lpTheString , RCDATA_INPLACE_POINTER ) )
	}	// FALSE (The caller said that it doesn't need to know how long the string is.) block, if ( plpuintLength )

	//	------------------------------------------------------------------------
	//	Make a report about the error retrievable through FB_GetlpErrMsgSprintf,
	//	then return NULL (always NULL) to signal the caller to fetch the message
	//	or do whatever else it wants about the load error. If the Structured
	//	Exception Handling flag is enabled, this call won't actually return,
	//	because raising the exception unwinds the stack.
	//	------------------------------------------------------------------------

	return ( LPTSTR ) SOff_ReportLoadStringError ( phSourceModule ,
		                                           puintStringID ,
		                                           RCDATA_INPLACE_POINTER ) ;
}	// SOff_GetUnicodeStringPointer