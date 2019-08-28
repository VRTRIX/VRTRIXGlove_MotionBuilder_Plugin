#ifndef pyfbplotoptions_h__
#define pyfbplotoptions_h__
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
// FBPlotOptions
// =======================================================================================
void FBPlotOptions_Init();

class FBPlotOptions_Wrapper;
FBPlotOptions_Wrapper* FBPlotOptions_Wrapper_Factory( FBPlotOptions* pFBPlotOptions );
class PYSDK_DLL FBPlotOptions_Wrapper {
public:
	FBPlotOptions* mFBPlotOptions;
public:
    FBPlotOptions_Wrapper( const FBPlotOptions& pFBPlotOptions ) : mFBPlotOptions( new FBPlotOptions( pFBPlotOptions ) ) {  }
    FBPlotOptions_Wrapper() : mFBPlotOptions( new FBPlotOptions ) {  }
    virtual ~FBPlotOptions_Wrapper( ) { delete mFBPlotOptions; }
	void SetConstantKeyReducerKeepOneKey( bool pConstantKeyReducerKeepOneKey ) { mFBPlotOptions->mConstantKeyReducerKeepOneKey = pConstantKeyReducerKeepOneKey; }
	bool GetConstantKeyReducerKeepOneKey(  ) { return mFBPlotOptions->mConstantKeyReducerKeepOneKey; }
	void SetPlotAllTakes( bool pPlotAllTakes ) { mFBPlotOptions->mPlotAllTakes = pPlotAllTakes; }
	bool GetPlotAllTakes(  ) { return mFBPlotOptions->mPlotAllTakes; }
	void SetPlotOnFrame( bool pPlotOnFrame ) { mFBPlotOptions->mPlotOnFrame = pPlotOnFrame; }
	bool GetPlotOnFrame(  ) { return mFBPlotOptions->mPlotOnFrame; }
	void SetPlotPeriod( FBTime_Wrapper& pPlotPeriod ) { mFBPlotOptions->mPlotPeriod = *pPlotPeriod.mFBTime; }
	FBTime_Wrapper* GetPlotPeriod(  ) { return FBTime_Wrapper_Factory( mFBPlotOptions->mPlotPeriod ); }
	void SetPlotTranslationOnRootOnly( bool pPlotTranslationOnRootOnly ) { mFBPlotOptions->mPlotTranslationOnRootOnly = pPlotTranslationOnRootOnly; }
	bool GetPlotTranslationOnRootOnly(  ) { return mFBPlotOptions->mPlotTranslationOnRootOnly; }
	void SetPreciseTimeDiscontinuities( bool pPreciseTimeDiscontinuities ) { mFBPlotOptions->mPreciseTimeDiscontinuities = pPreciseTimeDiscontinuities; }
	bool GetPreciseTimeDiscontinuities(  ) { return mFBPlotOptions->mPreciseTimeDiscontinuities; }
	void SetPlotLockedProperties( bool pPlotLockedProperties ) { mFBPlotOptions->mPlotLockedProperties = pPlotLockedProperties; }
	bool GetPlotLockedProperties(  ) { return mFBPlotOptions->mPlotLockedProperties; }
	void SetRotationFilterToApply( FBRotationFilter pRotationFilterToApply ) { mFBPlotOptions->mRotationFilterToApply = pRotationFilterToApply; }
	FBRotationFilter GetRotationFilterToApply(  ) { return mFBPlotOptions->mRotationFilterToApply; }
    void SetPlotTangentMode( FBPlotTangentMode pPlotTangentMode ) { mFBPlotOptions->mPlotTangentMode = pPlotTangentMode; }
    FBPlotTangentMode GetPlotTangentMode(  ) { return mFBPlotOptions->mPlotTangentMode; }
	void SetUseConstantKeyReducer( bool pUseConstantKeyReducer ) { mFBPlotOptions->mUseConstantKeyReducer = pUseConstantKeyReducer; }
	bool GetUseConstantKeyReducer(  ) { return mFBPlotOptions->mUseConstantKeyReducer; }
};

PYSDK_DLL inline FBPlotOptions_Wrapper* FBPlotOptions_Wrapper_Factory( const FBPlotOptions& pFBPlotOptions )
{
	return new FBPlotOptions_Wrapper( pFBPlotOptions );
}
#endif // pyfbplotoptions_h__