#ifndef pyfbvideograbber_h__
#define pyfbvideograbber_h__
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

#include "pyfbvideograboptions.h"

// =======================================================================================
// FBVideoGrabber
// =======================================================================================
void FBVideoGrabber_Init();

class PYSDK_DLL FBVideoGrabber_Wrapper : public FBComponent_Wrapper {
public:
	FBVideoGrabber* mFBVideoGrabber;
public:
	FBVideoGrabber_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBVideoGrabber = (FBVideoGrabber*)pFBComponent; }
	FBVideoGrabber_Wrapper(  ) : FBComponent_Wrapper( new FBVideoGrabber(  )) { mFBVideoGrabber = (FBVideoGrabber*)mFBComponent; SetAllocated(); }
	virtual ~FBVideoGrabber_Wrapper( ) { }
	bool BeginGrab() { return mFBVideoGrabber->BeginGrab(  ); }
	void EndGrab() { mFBVideoGrabber->EndGrab(  ); }
	const char* GetLastErrorMsg() { return mFBVideoGrabber->GetLastErrorMsg(  ); }
	FBVideoGrabOptions_Wrapper* GetOptions() { FBVideoGrabOptions lOptions = mFBVideoGrabber->GetOptions(  ); return FBVideoGrabOptions_Wrapper_Factory( &lOptions ); }
	FBVideoGrabStats GetStatistics() { return mFBVideoGrabber->GetStatistics(  ); }
	void Grab() { mFBVideoGrabber->Grab(  ); }
	object RenderSnapshot(int pWidth = -1, int pHeight = -1, bool pCameraLabel = false, bool pTimeCode = false, bool pSafeArea = false, bool pAxis = false, bool pGrid = false, bool pFrontPlate = false, bool pBackPlate = false) { return FBWrapperFactory::TheOne().WrapFBObject( mFBVideoGrabber->RenderSnapshot( pWidth, pHeight, pCameraLabel, pTimeCode, pSafeArea, pAxis, pGrid, pFrontPlate, pBackPlate )); }	
    void ResetOptions() { mFBVideoGrabber->ResetOptions(  ); }
	void SetOptions(FBVideoGrabOptions_Wrapper& pOptions) { mFBVideoGrabber->SetOptions( pOptions.mFBVideoGrabOptions ); }
};
#endif // pyfbvideograbber_h__