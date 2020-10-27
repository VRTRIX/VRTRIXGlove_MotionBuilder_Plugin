#ifndef pyfbmotionfileoptions_h__
#define pyfbmotionfileoptions_h__
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
// FBFbxManager
// =======================================================================================
void FBMotionFileOptions_Init();

class FBMotionFileOptions_Wrapper : public FBComponent_Wrapper {
public:
	FBMotionFileOptions* mFBMotionFileOptions;
public:
	FBMotionFileOptions_Wrapper( FBStringList_Wrapper& pFileList ) : FBComponent_Wrapper( new FBMotionFileOptions(pFileList.mFBStringList)) { mFBMotionFileOptions = (FBMotionFileOptions*)mFBComponent; SetAllocated(); }
	FBMotionFileOptions_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBMotionFileOptions = (FBMotionFileOptions*)pFBComponent; }
	virtual ~FBMotionFileOptions_Wrapper( ) { }

	int GetTakeCount() const { return mFBMotionFileOptions->GetTakeCount(); }           

    bool GetTakeSelect(int pTakeIndex) const { return mFBMotionFileOptions->GetTakeSelect(pTakeIndex); }
    void SetTakeSelect(int pTakeIndex, bool pSelect) { mFBMotionFileOptions->SetTakeSelect(pTakeIndex, pSelect); }
   
    const char* GetTakeName(int pTakeIndex) const {return mFBMotionFileOptions->GetTakeName(pTakeIndex); }
    void SetTakeName(int pTakeIndex,  const char* pName) { mFBMotionFileOptions->SetTakeName(pTakeIndex, pName); }

	void SetTakeStart(int pTakeIndex, FBTime_Wrapper& pStart) { mFBMotionFileOptions->SetTakeStart(pTakeIndex, *pStart.mFBTime); }
	FBTime_Wrapper* GetTakeStart(int pTakeIndex) { return FBTime_Wrapper_Factory(mFBMotionFileOptions->GetTakeStart(pTakeIndex)); }    

	void SetTakeStop(int pTakeIndex, FBTime_Wrapper& pStop) { mFBMotionFileOptions->SetTakeStop(pTakeIndex, *pStop.mFBTime); }
	FBTime_Wrapper* GetTakeStop(int pTakeIndex) { return FBTime_Wrapper_Factory(mFBMotionFileOptions->GetTakeStop(pTakeIndex)); }    

	void SetTakeSamples(int pTakeIndex, int pSamplesCount) { mFBMotionFileOptions->SetTakeSamples(pTakeIndex, pSamplesCount); }
	int GetTakeSamples(int pTakeIndex) { return mFBMotionFileOptions->GetTakeSamples(pTakeIndex); }    

	void SetTakeSamplingRate(int pTakeIndex, FBTimeMode pTimeMode, double pCustomSamplingRate=30.0) { mFBMotionFileOptions->SetTakeSamplingRate(pTakeIndex, pTimeMode, pCustomSamplingRate); }
	FBTimeMode GetTakeSamplingRateMode(int pTakeIndex) { return mFBMotionFileOptions->GetTakeSamplingRateMode(pTakeIndex); }    
	double GetTakeSamplingRate(int pTakeIndex) { return mFBMotionFileOptions->GetTakeSamplingRate(pTakeIndex); }    

    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, CreateInsteadOfMerge, bool);

    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, ModelSelection, FBModelSelection);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, TakeStartEnd, FBTakeSpanOnLoad);

	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, IgnoreModelType, bool);
	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, CreateUnmatchedModels, bool);
	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, ImportScaling, int);
	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, ImportDOF, bool);
	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, CreateReferenceNode, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, KeepDummyNode, bool );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, SetLimits, bool );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, BaseTranslationOnRotationOffset, bool );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, BaseRotationOnPreRotation, bool );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, CreateOpticalSegments, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, CreateUnusedOpticalSegments, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, SetOccludedToLastValidPosition, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBMotionFileOptions, KeepActorPrefix, bool);

};
#endif // pyfbmotionfileoptions_h__