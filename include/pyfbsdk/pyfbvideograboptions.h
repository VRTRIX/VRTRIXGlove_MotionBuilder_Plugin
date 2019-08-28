#ifndef pyfbvideograboptions_h__
#define pyfbvideograboptions_h__
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
// FBVideoGrabOptions
// =======================================================================================
void FBVideoGrabOptions_Init();

class FBVideoGrabOptions_Wrapper;
PYSDK_DLL FBVideoGrabOptions_Wrapper* FBVideoGrabOptions_Wrapper_Factory( FBVideoGrabOptions* pFBVideoGrabOptions );
class PYSDK_DLL FBVideoGrabOptions_Wrapper {
public:
	FBVideoGrabOptions* mFBVideoGrabOptions;
public:
    FBVideoGrabOptions_Wrapper( const FBVideoGrabOptions& pFBVideoGrabOptions ) : mFBVideoGrabOptions( new FBVideoGrabOptions( pFBVideoGrabOptions ) ) {}
    FBVideoGrabOptions_Wrapper() : mFBVideoGrabOptions( new FBVideoGrabOptions ) {}
    virtual ~FBVideoGrabOptions_Wrapper( ) { delete mFBVideoGrabOptions; }
	void SetTimeSpan( FBTimeSpan_Wrapper& pValue ) { mFBVideoGrabOptions->mTimeSpan = *pValue.mFBTimeSpan; }
	FBTimeSpan_Wrapper* GetTimeSpan() { return FBTimeSpan_Wrapper_Factory( mFBVideoGrabOptions->mTimeSpan ); }
	void SetTimeSteps( FBTime_Wrapper& pValue ) { mFBVideoGrabOptions->mTimeSteps = *pValue.mFBTime; }
	FBTime_Wrapper* GetTimeSteps() { return FBTime_Wrapper_Factory( mFBVideoGrabOptions->mTimeSteps ); }
	void SetCameraResolution( FBCameraResolutionMode pValue ) { mFBVideoGrabOptions->mCameraResolution = pValue; }
	FBCameraResolutionMode GetCameraResolution() { return mFBVideoGrabOptions->mCameraResolution; }
	void SetBitsPerPixel( FBVideoRenderDepth pValue ) { mFBVideoGrabOptions->mBitsPerPixel = pValue; }
	FBVideoRenderDepth GetBitsPerPixel() { return mFBVideoGrabOptions->mBitsPerPixel; }
	void SetFieldMode( FBVideoRenderFieldMode pValue ) { mFBVideoGrabOptions->mFieldMode = pValue; }
	FBVideoRenderFieldMode GetFieldMode() { return mFBVideoGrabOptions->mFieldMode; }
	void SetViewingMode( FBVideoRenderViewingMode pValue ) { mFBVideoGrabOptions->mViewingMode = pValue; }
	FBVideoRenderViewingMode GetViewingMode() { return mFBVideoGrabOptions->mViewingMode; }
	void SetStereoDisplayMode( FBStereoDisplayMode pValue ) { mFBVideoGrabOptions->mStereoDisplayMode = pValue; }
	FBStereoDisplayMode GetStereoDisplayMode() { return mFBVideoGrabOptions->mStereoDisplayMode; }
    void SetOutputFileName( const char* pValue ) { mFBVideoGrabOptions->mOutputFileName = pValue; }
    void SetRendererCallbackIndex(int pIndex) { mFBVideoGrabOptions->mRendererCallbackIndex = pIndex; }
    int  GetRendererCallbackIndex() { return mFBVideoGrabOptions->mRendererCallbackIndex; }
    void SetRendererCallbackPrefIndex(int pIndex) { mFBVideoGrabOptions->mRendererCallbackPrefIndex = pIndex; }
    int  GetRendererCallbackPrefIndex() { return mFBVideoGrabOptions->mRendererCallbackPrefIndex; }
	const char* GetOutputFileName() { return mFBVideoGrabOptions->mOutputFileName; }
    void SetShowSafeArea( bool pValue ) { mFBVideoGrabOptions->mShowSafeArea = pValue; }
    bool GetShowSafeArea() { return mFBVideoGrabOptions->mShowSafeArea; }
    void SetShowTimeCode( bool pValue ) { mFBVideoGrabOptions->mShowTimeCode = pValue; }
    bool GetShowTimeCode() { return mFBVideoGrabOptions->mShowTimeCode; }
    void SetShowCameraLabel( bool pValue ) { mFBVideoGrabOptions->mShowCameraLabel = pValue; }
    bool GetShowCameraLabel() { return mFBVideoGrabOptions->mShowCameraLabel; }
	void SetAntiAliasing( bool pValue ) { mFBVideoGrabOptions->mAntiAliasing = pValue; }
	bool GetAntiAliasing() { return mFBVideoGrabOptions->mAntiAliasing; }
	void SetRenderAudio( bool pValue ) { mFBVideoGrabOptions->mRenderAudio = pValue; }
	bool GetRenderAudio() { return mFBVideoGrabOptions->mRenderAudio; }
	void SetAudioRenderFormat( FBAudioFmt pValue ) { mFBVideoGrabOptions->mAudioRenderFormat = pValue; }
	FBAudioFmt GetAudioRenderFormat() { return mFBVideoGrabOptions->mAudioRenderFormat; }
    void SetStillImageCompression ( int pValue ) { mFBVideoGrabOptions->mStillImageCompression = pValue; }
    int  GetStillImageCompression ( ) { return mFBVideoGrabOptions->mStillImageCompression; }
};

PYSDK_DLL inline FBVideoGrabOptions_Wrapper* FBVideoGrabOptions_Wrapper_Factory( FBVideoGrabOptions* pFBVideoGrabOptions )
{
	FBVideoGrabOptions_Wrapper* lFBVideoGrabOptions = 0;
	if( pFBVideoGrabOptions )
	{
		lFBVideoGrabOptions = new FBVideoGrabOptions_Wrapper( *pFBVideoGrabOptions );
	}
	return lFBVideoGrabOptions;
}
#endif // pyfbvideograboptions_h__