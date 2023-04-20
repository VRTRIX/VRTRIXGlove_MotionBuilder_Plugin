#ifndef pyfbdeviceoptical_h__
#define pyfbdeviceoptical_h__
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
#include "pyfbdevicenotifyinfo.h"
#include "pyfbdevice.h"

// =======================================================================================
// FBDeviceOptical
// =======================================================================================
void FBDeviceOptical_Init();

class PYSDK_DLL FBDeviceOptical_Wrapper : public FBDevice_Wrapper {
public:
	FBDeviceOptical* mFBDeviceOptical;
public:
	FBDeviceOptical_Wrapper( FBComponent* pFBComponent ) : FBDevice_Wrapper( pFBComponent ) { mFBDeviceOptical = (FBDeviceOptical*)pFBComponent; }
	FBDeviceOptical_Wrapper( const char* pName ) : FBDevice_Wrapper( new FBDeviceOptical( pName )) { mFBDeviceOptical = (FBDeviceOptical*)mFBComponent; }
	virtual ~FBDeviceOptical_Wrapper( ) {}

	void FBDestroy() { mFBDeviceOptical->FBDestroy(); }
	bool FBCreate() { return mFBDeviceOptical->FBCreate(); }

	void DeviceOpticalBeginSetup() { mFBDeviceOptical->DeviceOpticalBeginSetup(); }
	void DeviceOpticalEndSetup() { mFBDeviceOptical->DeviceOpticalEndSetup(); }
	void DeviceOpticalRecordFrame(FBTime_Wrapper& pTime, FBDeviceNotifyInfo_Wrapper &pDeviceNotifyInfo) { mFBDeviceOptical->DeviceOpticalRecordFrame( *pTime.mFBTime, *pDeviceNotifyInfo.mFBDeviceNotifyInfo ); }
	
	//bool AnimationNodeNotify(FBAnimationNode_Wrapper& pAnimationNode, FBEvaluateInfo_Wrapper& pEvaluateInfo) { return mFBDeviceOptical->AnimationNodeNotify( pAnimationNode.mFBAnimationNode, pEvaluateInfo.mFBEvaluateInfo ); }
	//void DeviceIONotify(FBDevice::kDeviceIOs pAction, FBDeviceNotifyInfo_Wrapper& pDeviceNotifyInfo) { mFBDeviceOptical->DeviceIONotify( pAction, *pDeviceNotifyInfo.mFBDeviceNotifyInfo ); }

	void RecordingInitAnimation(FBAnimationNode_Wrapper& pAnimationNode ) { mFBDeviceOptical->RecordingInitAnimation( pAnimationNode.mFBAnimationNode ); }
	void RecordingDoneAnimation(FBAnimationNode_Wrapper& pAnimationNode ) { mFBDeviceOptical->RecordingDoneAnimation( pAnimationNode.mFBAnimationNode ); }

	object GetMarkers( ) { return FBPropertyListDeviceOpticalMarker_Wrapper_Factory( mFBDeviceOptical->Markers ); }
	void   SetModel( FBModel_Wrapper& pModel ) { mFBDeviceOptical->ModelOptical = pModel.mFBModel; }
	object GetModel( ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBDeviceOptical->ModelOptical ); }

	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SupportOcclusion,  bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(AutoAntialiasing,  bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(DampingTime, double)

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ForceOpticalSamplingRate, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(OpticalSamplingRate, double)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UseMarkerTimeStamp, bool)

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SkipFrame, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(MarkerTimeStamp, FBTime)
};
#endif // pyfbdeviceoptical_h__