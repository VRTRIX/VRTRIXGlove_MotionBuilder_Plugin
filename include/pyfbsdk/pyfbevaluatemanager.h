#ifndef pyfbevaluatemanager_h__
#define pyfbevaluatemanager_h__
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
// FBEvaluateManager
// =======================================================================================
void FBEvaluateManager_Init();

class PYSDK_DLL FBEvaluateManager_Wrapper : public FBComponent_Wrapper {
public:
	FBEvaluateManager* mFBEvaluateManager;
public:
	FBEvaluateManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBEvaluateManager = (FBEvaluateManager*)pFBComponent; }
    FBEvaluateManager_Wrapper() : FBComponent_Wrapper ( &FBEvaluateManager::TheOne()) { mFBEvaluateManager = (FBEvaluateManager*)mFBComponent; }
    virtual ~FBEvaluateManager_Wrapper() {};

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ParallelPipeline, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ParallelDeformation, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UseGPUDeformation, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FrameSkipOptimization, bool);    
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_DEPRECATED(ParallelScheduleType, FBParallelScheduleType);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ParallelEvaluation, bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(DualQuaternionSkinning, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(NodeCount,   int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(DeviceCount, int);

    //object OnEvaluationPipelineEvent();
    object OnRenderingPipelineEvent();
    object OnSynchronizationEvent();

    bool IsInteractiveMode() const { return mFBEvaluateManager->IsInteractiveMode(); }
    void InvalidateDAG() { mFBEvaluateManager->InvalidateDAG(); }

protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName) override;
};
#endif // pyfbevaluatemanager_h__

