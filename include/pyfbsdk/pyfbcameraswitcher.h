#ifndef pyfbcameraswitcher_h__
#define pyfbcameraswitcher_h__
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
#include "pyfbvideo.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbcamera.h"

// =======================================================================================
// FBCameraSwitcher
// =======================================================================================
void FBCameraSwitcher_Init();

class PYSDK_DLL FBCameraSwitcher_Wrapper : public FBModel_Wrapper {
public:
	FBCameraSwitcher* mFBCameraSwitcher;
public:
	FBCameraSwitcher_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBCameraSwitcher = (FBCameraSwitcher*)pFBComponent; }
	FBCameraSwitcher_Wrapper(  ) : FBModel_Wrapper( new FBCameraSwitcher(  )) { mFBCameraSwitcher = (FBCameraSwitcher*)mFBComponent; }
	virtual ~FBCameraSwitcher_Wrapper( ) { }
	void SetCurrentCamera( FBCamera_Wrapper& pCurrentCamera ) { mFBCameraSwitcher->CurrentCamera = pCurrentCamera.mFBCamera; }
	object GetCurrentCamera(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCameraSwitcher->CurrentCamera ); }
	void SetCurrentCameraIndex( int pCameraIndex ) { mFBCameraSwitcher->CurrentCameraIndex = pCameraIndex; }
	int GetCurrentCameraIndex(  ) { return mFBCameraSwitcher->CurrentCameraIndex; }
	void UseEvaluateSwitch() { mFBCameraSwitcher->CurrentCamera = NULL; }
};
#endif // pyfbcameraswitcher_h__