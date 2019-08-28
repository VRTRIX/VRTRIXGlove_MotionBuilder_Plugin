#ifndef pyfbdeviceinstrument_h__
#define pyfbdeviceinstrument_h__
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
// FBDeviceInstrument
// =======================================================================================
void FBDeviceInstrument_Init();

class PYSDK_DLL FBDeviceInstrument_Wrapper : public FBComponent_Wrapper {
public:
	FBDeviceInstrument* mFBDeviceInstrument;
public:
	FBDeviceInstrument_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBDeviceInstrument = (FBDeviceInstrument*)pFBComponent; }
	FBDeviceInstrument_Wrapper( FBDevice_Wrapper& pDevice ) : FBComponent_Wrapper( new FBDeviceInstrument( pDevice.mFBDevice )) { mFBDeviceInstrument = (FBDeviceInstrument*)mFBComponent; SetAllocated(); }
	virtual ~FBDeviceInstrument_Wrapper( ) {}

	void InstrumentRecordFrame(FBTime_Wrapper& pRecordTime, FBDeviceNotifyInfo_Wrapper& pNotifyInfo) { mFBDeviceInstrument->InstrumentRecordFrame( *(pRecordTime.mFBTime), *(pNotifyInfo.mFBDeviceNotifyInfo) ); }
	bool InstrumentWriteData(FBEvaluateInfo_Wrapper& pEvaluateInfo) { return mFBDeviceInstrument->InstrumentWriteData( pEvaluateInfo.mFBEvaluateInfo ); }
	void SetActive( bool pActive ) { mFBDeviceInstrument->Active = pActive; }
	bool GetActive(  ) { return mFBDeviceInstrument->Active; }
	void SetDevice( FBDevice_Wrapper& pDevice ) { mFBDeviceInstrument->Device = pDevice.mFBDevice; }
	object GetDevice(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBDeviceInstrument->Device ); }
	void SetModelTemplate( FBModelTemplate_Wrapper& pModelTemplate ) { mFBDeviceInstrument->ModelTemplate = pModelTemplate.mFBModelTemplate; }
	object GetModelTemplate(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBDeviceInstrument->ModelTemplate ); }
};
#endif // pyfbdeviceinstrument_h__