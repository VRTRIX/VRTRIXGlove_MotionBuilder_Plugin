#ifndef pyfbcamerastereo_h__
#define pyfbcamerastereo_h__
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
// FBCameraStereo
// =======================================================================================
void FBCameraStereo_Init();

class PYSDK_DLL FBCameraStereo_Wrapper : public FBCamera_Wrapper {
public:
	FBCameraStereo* mFBCameraStereo;
public:
	FBCameraStereo_Wrapper( FBComponent* pFBComponent ) : FBCamera_Wrapper( pFBComponent ) { mFBCameraStereo = (FBCameraStereo*)pFBComponent; }
	FBCameraStereo_Wrapper( const char* pName ) : FBCamera_Wrapper( new FBCameraStereo( pName )) { mFBCameraStereo = (FBCameraStereo*)mFBComponent; }
	virtual ~FBCameraStereo_Wrapper( ) {}
	object GetRightCamera (){ return FBWrapperFactory::TheOne().WrapFBObject((FBCamera*)mFBCameraStereo->RightCamera ); }
 	object GetLeftCamera  (){ return FBWrapperFactory::TheOne().WrapFBObject((FBCamera*)mFBCameraStereo->LeftCamera ); }
    object GetCenterCamera(){ return FBWrapperFactory::TheOne().WrapFBObject((FBCamera*)mFBCameraStereo->CenterCamera ); }
    void   SetRightCamera ( FBCamera_Wrapper& pCamera ) { mFBCameraStereo->RightCamera  = pCamera.mFBCamera; }
    void   SetLeftCamera  ( FBCamera_Wrapper& pCamera ) { mFBCameraStereo->LeftCamera   = pCamera.mFBCamera; }
    void   SetCenterCamera( FBCamera_Wrapper& pCamera ) { mFBCameraStereo->CenterCamera = pCamera.mFBCamera; }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Stereo,                    FBCameraStereoType);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(InteraxialSeparation,      double);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ZeroParallax,              double);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ToeInAdjust,               double);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FilmOffsetRightCam,        double);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FilmOffsetLeftCam,         double);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PrecompFileName,           const char*);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(RelativePrecompFileName,   const char*);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(DisplayZeroParallaxPlane,  bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ZeroParallaxPlaneTransparency, double);
    DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(ZeroParallaxPlaneColor,    FBColor);
};
#endif // pyfbcamerastereo_h__