#ifndef pyfbrenderoptions_h__
#define pyfbrenderoptions_h__
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

#include "pyfbviewingoptions.h"

// =======================================================================================
// FBRenderOptions
// =======================================================================================
void FBRenderOptions_Init();

class PYSDK_DLL FBRenderOptions_Wrapper {
public:
	FBRenderOptions* mFBRenderOptions;
public:
	FBRenderOptions_Wrapper( const FBRenderOptions& pRenderOptions ) { mFBRenderOptions = new FBRenderOptions( pRenderOptions ); }    
	virtual ~FBRenderOptions_Wrapper( ) { delete mFBRenderOptions; }
    object GetRenderingCamera() { return FBWrapperFactory::TheOne().WrapFBObject( mFBRenderOptions->GetRenderingCamera()); }
    int GetRenderFrameId() { return mFBRenderOptions->GetRenderFrameId(  ); }
    bool IsIDBufferPicking() const { return mFBRenderOptions->IsIDBufferRendering(); }
    bool IsIDBufferRendering() const { return mFBRenderOptions->IsIDBufferRendering(); }
    float GetIDBufferPickingAlphaThreshold() const { return mFBRenderOptions->GetIDBufferPickingAlphaThreshold(); } 
    bool IsOfflineRendering() const { return mFBRenderOptions->IsOfflineRendering(); }
    FBViewingOptions_Wrapper* GetViewerOptions() const { return FBViewingOptions_Wrapper_Factory( mFBRenderOptions->GetViewerOptions() ); }

};
#endif // pyfbrenderoptions_h__