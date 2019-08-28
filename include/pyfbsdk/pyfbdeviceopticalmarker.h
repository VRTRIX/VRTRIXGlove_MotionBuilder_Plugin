#ifndef pyfbdeviceopticalmarker_h__
#define pyfbdeviceopticalmarker_h__
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

// =======================================================================================
// FBDeviceOpticalMarker
// =======================================================================================
void FBDeviceOpticalMarker_Init();

class PYSDK_DLL FBDeviceOpticalMarker_Wrapper : public FBComponent_Wrapper {
public:
	FBDeviceOpticalMarker* mFBDeviceOpticalMarker;
public:
	FBDeviceOpticalMarker_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBDeviceOpticalMarker = (FBDeviceOpticalMarker*)pFBComponent; }
	FBDeviceOpticalMarker_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBDeviceOpticalMarker( pName )) { mFBDeviceOpticalMarker = (FBDeviceOpticalMarker*)mFBComponent; }
	virtual ~FBDeviceOpticalMarker_Wrapper( ) { }

	void SetData(double pX, double pY, double pZ=0.0, double pOcclusion=0.0 ) { return mFBDeviceOpticalMarker->SetData( pX, pY, pZ, pOcclusion ); }

	void   SetModel( FBModel_Wrapper& pModel ) { mFBDeviceOpticalMarker->Model = pModel.mFBModel; }
	object GetModel( ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBDeviceOpticalMarker->Model ); }
	void   SetPosition( FBVector3d_Wrapper& pPosition ) { mFBDeviceOpticalMarker->Position = *pPosition.mFBVector3d; }
	FBVector3d_Wrapper* GetPosition(  ) { return FBVector3d_Wrapper_Factory( mFBDeviceOpticalMarker->Position ); }
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(IsUsed,	bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Occlusion,	double);

};
#endif // pyfbdeviceopticalmarker_h__
