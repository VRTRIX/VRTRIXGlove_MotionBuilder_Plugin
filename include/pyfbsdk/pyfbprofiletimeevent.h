#ifndef pyfbprofiletimeevent_h__
#define pyfbprofiletimeevent_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

// =======================================================================================
// FBProfileTimeEvent
// =======================================================================================
void FBProfileTimeEvent_Init();

class FBProfileTimeEvent_Wrapper;
PYSDK_DLL FBProfileTimeEvent_Wrapper* FBProfileTimeEvent_Wrapper_Factory( FBProfileTimeEvent* pFBProfileTimeEvent );

class PYSDK_DLL FBProfileTimeEvent_Wrapper {
public:
	FBProfileTimeEvent* mFBProfileTimeEvent;
public:
    FBProfileTimeEvent_Wrapper( FBProfileTimeEvent* pTE ) : mFBProfileTimeEvent( pTE ) {}
	virtual ~FBProfileTimeEvent_Wrapper( ) { }

	FBTime_Wrapper* GetTime(){ return FBTime_Wrapper_Factory(mFBProfileTimeEvent->GetTime()); }
	FBColor_Wrapper* GetColor();
	const char* GetTypeName(){ return mFBProfileTimeEvent->GetTypeName(); }
	const char* GetComment(){ return mFBProfileTimeEvent->GetComment(); }
	int GetThreadID(){ return mFBProfileTimeEvent->GetThreadID(); }
	bool IsSingleEvent(){ return mFBProfileTimeEvent->IsSingleEvent(); }
};

PYSDK_DLL inline FBProfileTimeEvent_Wrapper* FBProfileTimeEvent_Wrapper_Factory( FBProfileTimeEvent* pFBProfileTimeEvent )
{
	FBProfileTimeEvent_Wrapper* lFBProfileTimeEvent = 0;
	if( pFBProfileTimeEvent )
	{
		lFBProfileTimeEvent = new FBProfileTimeEvent_Wrapper( pFBProfileTimeEvent );
	}

	return lFBProfileTimeEvent;
}

#endif // pyfbprofiletimeevent_h__