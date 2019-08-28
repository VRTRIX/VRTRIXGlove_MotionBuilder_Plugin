#ifndef pyfbfilter_h__
#define pyfbfilter_h__
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

#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"

// =======================================================================================
// FBFilter
// =======================================================================================
void FBFilter_Init();
class FBAnimationNode_Wrapper;
class PYSDK_DLL FBFilter_Wrapper : public FBComponent_Wrapper {
public:
	FBFilter* mFBFilter;
public:
	FBFilter_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBFilter = (FBFilter*)pFBComponent; }
	virtual ~FBFilter_Wrapper( ) {}
	bool Apply(FBAnimationNode_Wrapper& pNode, bool pRecursive) { return mFBFilter->Apply( pNode.mFBAnimationNode, pRecursive ); }
	bool Apply(FBFCurve_Wrapper& pCurve) { return mFBFilter->Apply( pCurve.mFBFCurve ); }
	void FBDelete() { mFBFilter->FBDelete(  ); }
	void Reset() { mFBFilter->Reset(  ); }
	void SetStart( FBTime_Wrapper& pStart ) { mFBFilter->Start = *pStart.mFBTime; }
	FBTime_Wrapper* GetStart(  ) { return FBTime_Wrapper_Factory( mFBFilter->Start ); }
	void SetStop( FBTime_Wrapper& pStop ) { mFBFilter->Stop = *pStop.mFBTime; }
	FBTime_Wrapper* GetStop(  ) { return FBTime_Wrapper_Factory( mFBFilter->Stop ); }
};
#endif // pyfbfilter_h__