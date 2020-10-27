#ifndef pyfbvideoclip_h__
#define pyfbvideoclip_h__
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

#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbimage.h"
#include "pyfbvideo.h"

// =======================================================================================
// FBVideoClip
// =======================================================================================
void FBVideoClip_Init();

class PYSDK_DLL FBVideoClip_Wrapper : public FBVideo_Wrapper {
public:
	FBVideoClip* mFBVideoClip;
public:
	FBVideoClip_Wrapper( FBComponent* pFBComponent ) : FBVideo_Wrapper( pFBComponent ) { mFBVideoClip = (FBVideoClip*)pFBComponent; }
	FBVideoClip_Wrapper( const char* pName ) : FBVideo_Wrapper( new FBVideoClip( pName )) { mFBVideoClip = (FBVideoClip*)mFBComponent; }
	virtual ~FBVideoClip_Wrapper( ) {}
	void DrawImage(int pX = 0, int pY = 0, int pW = -1, int pH = -1, int pFrame = -1) { mFBVideoClip->DrawImage( pX, pY, pW, pH, pFrame ); }
	void FBDelete() { mFBVideoClip->FBDelete(  ); }
	bool IsValid() { return mFBVideoClip->IsValid(  ); }
	void SetCurrentFrame( int pCurrentFrame ) { mFBVideoClip->CurrentFrame = pCurrentFrame; }
	int GetCurrentFrame(  ) { return mFBVideoClip->CurrentFrame; }
	void SetCurrentFrameTime( FBTime_Wrapper& pCurrentFrameTime ) { mFBVideoClip->CurrentFrameTime = *pCurrentFrameTime.mFBTime; }
	FBTime_Wrapper* GetCurrentFrameTime(  ) { return FBTime_Wrapper_Factory( mFBVideoClip->CurrentFrameTime ); }
	void SetFilename( const char* pFilename ) { mFBVideoClip->Filename = pFilename; }
	const char* GetFilename(  ) { return mFBVideoClip->Filename; }
	const char* GetRelativePath(  ) { return mFBVideoClip->RelativePath; }
	FBVideoFormat GetFormat(  ) { return mFBVideoClip->Format; }
	FBTime_Wrapper* GetFrameTime(  ) { return FBTime_Wrapper_Factory( mFBVideoClip->FrameTime ); }
	void SetFreeRunning( bool pFreeRunning ) { mFBVideoClip->FreeRunning = pFreeRunning; }
	bool GetFreeRunning(  ) { return mFBVideoClip->FreeRunning; }
	int GetHeight(  ) { return mFBVideoClip->Height; }
	void SetInterlaceMode( FBVideoInterlaceMode pInterlaceMode ) { mFBVideoClip->InterlaceMode = pInterlaceMode; }
	FBVideoInterlaceMode GetInterlaceMode(  ) { return mFBVideoClip->InterlaceMode; }
	int GetLastFrame(  ) { return mFBVideoClip->LastFrame; }
	FBTime_Wrapper* GetLastFrameTime(  ) { return FBTime_Wrapper_Factory( mFBVideoClip->LastFrameTime ); }
	void SetLoop( bool pLoop ) { mFBVideoClip->Loop = pLoop; }
	bool GetLoop(  ) { return mFBVideoClip->Loop; }
	void SetPlaySpeed( double pPlaySpeed ) { mFBVideoClip->PlaySpeed = pPlaySpeed; }
	double GetPlaySpeed(  ) { return mFBVideoClip->PlaySpeed; }
	int GetPowerOfTwoHeight(  ) { return mFBVideoClip->PowerOfTwoHeight; }
	int GetPowerOfTwoWidth(  ) { return mFBVideoClip->PowerOfTwoWidth; }
	void SetProxyMode( FBVideoProxyMode pProxyMode ) { mFBVideoClip->ProxyMode = pProxyMode; }
	FBVideoProxyMode GetProxyMode(  ) { return mFBVideoClip->ProxyMode; }
	void SetStartFrame( int pStartFrame ) { mFBVideoClip->StartFrame = pStartFrame; }
	int GetStartFrame(  ) { return mFBVideoClip->StartFrame; }
	void SetStopFrame( int pStopFrame ) { mFBVideoClip->StopFrame = pStopFrame; }
	int GetStopFrame(  ) { return mFBVideoClip->StopFrame; }
	void SetStorageMode( FBVideoStorageMode pStorageMode ) { mFBVideoClip->StorageMode = pStorageMode; }
	FBVideoStorageMode GetStorageMode(  ) { return mFBVideoClip->StorageMode; }
	void SetTimeOffset( FBTime_Wrapper& pTimeOffset ) { mFBVideoClip->TimeOffset = *pTimeOffset.mFBTime; }
	FBTime_Wrapper* GetTimeOffset(  ) { return FBTime_Wrapper_Factory( mFBVideoClip->TimeOffset ); }
	int GetWidth(  ) { return mFBVideoClip->Width; }
    int GetTextureID( ) { return mFBVideoClip->GetTextureID(); }
	FBTime_Wrapper* GetCurrentFrameTimeCode(  ) { return FBTime_Wrapper_Factory( mFBVideoClip->CurrentFrameTimeCode ); }
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FrameRate,double);
};
#endif // pyfbvideoclip_h__