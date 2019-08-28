#ifndef pyfbevent_h__
#define pyfbevent_h__
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
// FBEvent
// =======================================================================================

#error ???

class PYSDK_DLL FBEvent_Wrapper : public FBComponent_Wrapper {
public:
	FBEvent* mFBEvent;
public:
	FBEvent_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBEvent = (FBEvent*)pFBComponent; }
	FBEvent_Wrapper( HKEvent pEvent ) : FBComponent_Wrapper( new FBEvent( pEvent )) { mFBEvent = (FBEvent*)mFBComponent; }
	virtual ~FBEvent_Wrapper( ) { }
	const char* ClassName() { return mFBEvent->ClassName(  ); }
	bool Is(int pTypeId) { return mFBEvent->Is( pTypeId ); }
	void SetmLocalPtr( DataFBEvent * pmLocalPtr ) { mFBEvent->mLocalPtr = pmLocalPtr; }
	DataFBEvent * GetmLocalPtr(  ) { return mFBEvent->mLocalPtr; }
	int GetType(  ) { return mFBEvent->Type; }
};
#endif // pyfbevent_h__
