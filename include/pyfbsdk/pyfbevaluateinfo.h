#ifndef pyfbevaluateinfo_h__
#define pyfbevaluateinfo_h__
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
// FBEvaluateInfo
// =======================================================================================
void FBEvaluateInfo_Init();

class FBEvaluateInfo_Wrapper;
PYSDK_DLL FBEvaluateInfo_Wrapper* FBEvaluateInfo_Wrapper_Factory( FBEvaluateInfo* pEvaluateInfo );

class PYSDK_DLL FBEvaluateInfo_Wrapper {
public:
	FBEvaluateInfo* mFBEvaluateInfo;
public:
    FBEvaluateInfo_Wrapper(FBEvaluateInfo* pEvaluateInfo) : mFBEvaluateInfo( pEvaluateInfo ) {}
	virtual ~FBEvaluateInfo_Wrapper() { }
	FBTime_Wrapper* GetLocalTime() { return FBTime_Wrapper_Factory( mFBEvaluateInfo->GetLocalTime(  )); }
	int GetSyncCount() { return mFBEvaluateInfo->GetSyncCount(  ); }
	FBTime_Wrapper* GetSystemTime() { return FBTime_Wrapper_Factory( mFBEvaluateInfo->GetSystemTime(  )); }
	bool IsStop() { return mFBEvaluateInfo->IsStop(  ); }
    int GetEvaluationID() { return mFBEvaluateInfo->GetEvaluationID(); }
};

PYSDK_DLL inline FBEvaluateInfo_Wrapper* FBEvaluateInfo_Wrapper_Factory( FBEvaluateInfo* pEvaluateInfo )
{
	FBEvaluateInfo_Wrapper* lEvaluateInfo = 0;
	if( pEvaluateInfo )
	{
		lEvaluateInfo = new FBEvaluateInfo_Wrapper( pEvaluateInfo );
	}

	return lEvaluateInfo;
}

#endif // pyfbevaluateinfo_h__