#ifndef pyfbdevice_h__
#define pyfbdevice_h__
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

#include "pyfbmatrix.h"
#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbmodeltemplate.h"

// =======================================================================================
// FBDevice
// =======================================================================================
void FBDevice_Init();
class FBAnimationNode_Wrapper;
class PYSDK_DLL FBDevice_Wrapper : public FBBox_Wrapper {
public:
	FBDevice* mFBDevice;
public:
	FBDevice_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBDevice = (FBDevice*)pFBComponent; }
	virtual ~FBDevice_Wrapper( ) {}
	void AckOneBadSampleReceived() { mFBDevice->AckOneBadSampleReceived(  ); }
	void AckOneSampleReceived() { mFBDevice->AckOneSampleReceived(  ); }
	void AckOneSampleSent() { mFBDevice->AckOneSampleSent(  ); }
	//bool AnimationNodeNotify(FBAnimationNode_Wrapper& pAnimationNode, FBEvaluateInfo_Wrapper& pEvaluateInfo) { return mFBDevice->AnimationNodeNotify( pAnimationNode.mFBAnimationNode, pEvaluateInfo.mFBEvaluateInfo ); }
	bool FBCreate() { return mFBDevice->FBCreate(  ); }
	void FBDestroy() { mFBDevice->FBDestroy(  ); }
	void RecordingDoneAnimation(FBAnimationNode_Wrapper& pAnimationNode) { mFBDevice->RecordingDoneAnimation( pAnimationNode.mFBAnimationNode ); }
	void RecordingInitAnimation(FBAnimationNode_Wrapper& pAnimationNode) { mFBDevice->RecordingInitAnimation( pAnimationNode.mFBAnimationNode ); }
	object ModelBindingCreate() { return FBWrapperFactory::TheOne().WrapFBObject(mFBDevice->ModelBindingCreate()); }
	void SetCommType( int pCommType ) { mFBDevice->CommType = pCommType; }
	int GetCommType(  ) { return mFBDevice->CommType; }
	void SetHardwareVersionInfo( const char* pHardwareVersionInfo ) { mFBDevice->HardwareVersionInfo = pHardwareVersionInfo; }
	const char* GetHardwareVersionInfo(  ) { return mFBDevice->HardwareVersionInfo; }
	void SetInformation( const char* pInformation ) { mFBDevice->Information = pInformation; }
	const char* GetInformation(  ) { return mFBDevice->Information; }
	object GetInstruments(  ) { return FBPropertyListDeviceInstrument_Wrapper_Factory( mFBDevice->Instruments ); }
	void SetModelTemplate( FBModelTemplate_Wrapper& pModelTemplate ) { mFBDevice->ModelTemplate = *(pModelTemplate.mFBModelTemplate); }
	object GetModelTemplate(  ) { return FBWrapperFactory::TheOne().WrapFBObject( &(mFBDevice->ModelTemplate) ); }
	void SetModelBindingRoot( FBModel_Wrapper& pModel ) { mFBDevice->ModelBindingRoot = pModel.mFBModel; }
	object GetModelBindingRoot(  ) { return FBModel_Wrapper_Factory( mFBDevice->ModelBindingRoot ); }
	void ModelBindingRootsList( FBModelList_Wrapper& pList ) { mFBDevice->ModelBindingRootsList( *pList.mFBModelList ); }
	void SetOnline( bool pOnline ) { mFBDevice->Online = pOnline; }
	bool GetOnline(  ) { return mFBDevice->Online; }
	FBTime_Wrapper* GetRecordingStartTime(  ) { return FBTime_Wrapper_Factory( mFBDevice->RecordingStartTime ); }
	FBTime_Wrapper* GetRecordingStopTime(  ) { return FBTime_Wrapper_Factory( mFBDevice->RecordingStopTime ); }
	void SetSamplingMode( FBDeviceSamplingMode pSamplingMode ) { mFBDevice->SamplingMode = pSamplingMode; }
	FBDeviceSamplingMode GetSamplingMode(  ) { return mFBDevice->SamplingMode; }
	void SetSamplingPeriod( FBTime_Wrapper& pSamplingPeriod ) { mFBDevice->SamplingPeriod = *(pSamplingPeriod.mFBTime); }
	FBTime_Wrapper* GetSamplingPeriod(  ) { return FBTime_Wrapper_Factory( mFBDevice->SamplingPeriod ); }
	void SetStatus( const char* pStatus ) { mFBDevice->Status = pStatus; }
	const char* GetStatus(  ) { return mFBDevice->Status; }
};
#endif // pyfbdevice_h__

