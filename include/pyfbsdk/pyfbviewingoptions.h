#ifndef pyfbviewingoptions_h__
#define pyfbviewingoptions_h__
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
// FBViewingOptions
// =======================================================================================
void FBViewingOptions_Init();

class FBViewingOptions_Wrapper;
PYSDK_DLL FBViewingOptions_Wrapper* FBViewingOptions_Wrapper_Factory( FBViewingOptions* pFBViewingOptions );
class PYSDK_DLL FBViewingOptions_Wrapper {
public:
	FBViewingOptions* mFBViewingOptions;
public:
    FBViewingOptions_Wrapper( FBViewingOptions* pFBViewingOptions ) : mFBViewingOptions( pFBViewingOptions ) {}
	virtual ~FBViewingOptions_Wrapper( ) {}
	void SetDisplayMode( FBModelShadingMode pValue ) { mFBViewingOptions->ShadingMode(  ) = pValue; }
	FBModelShadingMode GetDisplayMode() { return mFBViewingOptions->ShadingMode(  ); }
    void SetStereoDisplayMode( FBStereoDisplayMode pValue ) { mFBViewingOptions->StereoDisplayMode() = pValue; }
    FBStereoDisplayMode GetStereoDisplayMode() { return mFBViewingOptions->StereoDisplayMode(); }
	void SetDisplayWhat( int pValue ) { mFBViewingOptions->DisplayWhat(  ) = pValue; }
	int GetDisplayWhat() { return mFBViewingOptions->DisplayWhat(  ); }
	void SetPickingMode( FBPickingMode pValue ) { mFBViewingOptions->PickingMode(  ) = pValue; }
	FBPickingMode GetPickingMode() { return mFBViewingOptions->PickingMode(  ); }
	void SetShowCameraLabel( bool pValue ) { mFBViewingOptions->ShowCameraLabel(  ) = pValue; }
	bool GetShowCameraLabel() { return mFBViewingOptions->ShowCameraLabel(  ); }
	void SetShowSafeArea( bool pValue ) { mFBViewingOptions->ShowSafeArea(  ) = pValue; }
	bool GetShowSafeArea() { return mFBViewingOptions->ShowSafeArea(  ); }
	void SetShowTimeCode( bool pValue ) { mFBViewingOptions->ShowTimeCode(  ) = pValue; }
	bool GetShowTimeCode() { return mFBViewingOptions->ShowTimeCode(  ); }
    bool InPicking() const;
    bool IsInSelectionBufferPicking() const { return mFBViewingOptions->IsInSelectionBufferPicking(); }
    bool IsInColorBufferPicking() const { return mFBViewingOptions->IsInColorBufferPicking(); }
    unsigned int RenderCallbackPrefIndex() const { return mFBViewingOptions->RenderCallbackPrefIndex(); }
    int GetPaneIndex() const { return mFBViewingOptions->PaneIndex(); }
};

PYSDK_DLL inline FBViewingOptions_Wrapper* FBViewingOptions_Wrapper_Factory( FBViewingOptions* pFBViewingOptions )
{
	FBViewingOptions_Wrapper* lFBViewingOptions = 0;
	if( pFBViewingOptions )
	{
		lFBViewingOptions = new FBViewingOptions_Wrapper( pFBViewingOptions );
	}
	return lFBViewingOptions;
}
#endif // pyfbviewingoptions_h__