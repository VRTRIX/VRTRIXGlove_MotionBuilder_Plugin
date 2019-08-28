// ordevicevrtrixglove.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


//--- SDK include
#include <fbsdk/fbsdk.h>

//--- Library declaration
FBLibraryDeclare( ordevicevrtrixglove )
{
	FBLibraryRegister( ORDeviceVRTRIXGlove	);
	FBLibraryRegister( ORDeviceVRTRIXLayout	);
}
FBLibraryDeclareEnd;

/************************************************
 *	Library functions.
 ************************************************/
bool FBLibrary::LibInit()	{ return true; }
bool FBLibrary::LibOpen()	{ return true; }
bool FBLibrary::LibReady()	{ return true; }
bool FBLibrary::LibClose()	{ return true; }
bool FBLibrary::LibRelease(){ return true; }
