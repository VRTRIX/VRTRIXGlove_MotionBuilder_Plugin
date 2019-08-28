#ifndef pyfbtimespan_h__
#define pyfbtimespan_h__
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
// FBTimeSpan
// =======================================================================================
void FBTimeSpan_Init();

class FBTimeSpan_Wrapper;
FBTimeSpan_Wrapper* FBTimeSpan_Wrapper_Factory( const FBTimeSpan& pFBTimeSpan );
class FBTimeSpan_Wrapper {
public:
	FBTimeSpan* mFBTimeSpan;
public:
	FBTimeSpan_Wrapper( const FBTimeSpan& pFBTimeSpan ) { mFBTimeSpan = new FBTimeSpan( pFBTimeSpan ); }
    FBTimeSpan_Wrapper( FBTime_Wrapper* pStart = 0, FBTime_Wrapper* pStop = 0 ) { mFBTimeSpan = new FBTimeSpan( pStart ? *(pStart->mFBTime) : 0, pStop ? *(pStop->mFBTime) : 0 ); }
	virtual ~FBTimeSpan_Wrapper( ) { delete mFBTimeSpan; }
	int GetDirection() { return mFBTimeSpan->GetDirection(  ); }
	FBTime_Wrapper* GetDuration() { return FBTime_Wrapper_Factory( mFBTimeSpan->GetDuration(  )); }
	FBTime_Wrapper* GetSignedDuration() { return FBTime_Wrapper_Factory( mFBTimeSpan->GetSignedDuration(  )); }
	FBTime_Wrapper* GetStart() { return FBTime_Wrapper_Factory( mFBTimeSpan->GetStart(  )); }
	FBTime_Wrapper* GetStop() { return FBTime_Wrapper_Factory( mFBTimeSpan->GetStop(  )); }
	void Set(FBTime_Wrapper& pStart, FBTime_Wrapper& pStop) { mFBTimeSpan->Set( *pStart.mFBTime, *pStop.mFBTime ); }
};

inline FBTimeSpan_Wrapper* FBTimeSpan_Wrapper_Factory( const FBTimeSpan& pFBTimeSpan )
{
	return new FBTimeSpan_Wrapper( pFBTimeSpan );
}
#endif // pyfbtimespan_h__