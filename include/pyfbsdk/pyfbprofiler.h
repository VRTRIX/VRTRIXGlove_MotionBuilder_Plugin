#ifndef pyfbprofiler_h__
#define pyfbprofiler_h__
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
// FBProfiler
// =======================================================================================
void FBProfiler_Init();

class FBProfileTimeEvent_Wrapper;

class PYSDK_DLL FBProfiler_Wrapper : public FBComponent_Wrapper {
public:
	FBProfiler* mFBProfiler;
public:
	FBProfiler_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBProfiler = (FBProfiler*)pFBComponent; }
	FBProfiler_Wrapper(  );
	virtual ~FBProfiler_Wrapper( );

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ProfilingMode,		FBProfilingMode);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(EvaluationDepth,	int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(BufferSize,		int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FrameReference,	bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ActiveSampling,	bool);

	int GetEventSampleCount(){ return mFBProfiler->GetEventSampleCount(); }
	FBProfileTimeEvent_Wrapper* GetEventSample( int pIndex );
	FBProfileTimeEvent_Wrapper* GetEndEventSample( int pIndex );

	int	GetStatCount() { return mFBProfiler->GetStatCount(); }
	int	GetStatIndex(const char* pName) { return mFBProfiler->GetStatIndex(pName); }
	const char*	GetStatName(int pIndex) { return mFBProfiler->GetStatName(pIndex); }
	const char*	GetStatComment(int pIndex) { return mFBProfiler->GetStatComment(pIndex); }
	double GetStatStart(int pIndex) { return mFBProfiler->GetStatStart(pIndex); }
	double GetStatStop(int pIndex) { return mFBProfiler->GetStatStop(pIndex); }
	double GetStatDuration(int pIndex) { return mFBProfiler->GetStatDuration(pIndex); }
	double GetProfilingCost() { return mFBProfiler->GetProfilingCost(); }
};
#endif // pyfbprofiler_h__