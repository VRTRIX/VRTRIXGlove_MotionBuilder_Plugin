#ifndef pyfbmotionclip_h__
#define pyfbmotionclip_h__
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
// FBMotionClip
// =======================================================================================
void FBMotionClip_Init();

class PYSDK_DLL FBMotionClip_Wrapper : public FBComponent_Wrapper {
public:
	FBMotionClip* mFBMotionClip;
public:
	FBMotionClip_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBMotionClip = (FBMotionClip*)pFBComponent; }
	FBMotionClip_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBMotionClip( pName )) { mFBMotionClip = (FBMotionClip*)mFBComponent; }
	virtual ~FBMotionClip_Wrapper( ) { }
	void FBDelete() { mFBMotionClip->FBDelete(  ); }
	const char* GetFilename(  ) { return mFBMotionClip->Filename; }
	void SetFilename( const char* pFileName )	{ mFBMotionClip->Filename = pFileName; }
	const char* GetRelativePath(  ) { return mFBMotionClip->RelativePath; }
	void SetStart( FBTime_Wrapper& pTime ) { mFBMotionClip->Start = *(pTime.mFBTime); }
	FBTime_Wrapper* GetStart(  ) { return FBTime_Wrapper_Factory( mFBMotionClip->Start ); }
	void SetStop( FBTime_Wrapper& pTime ) { mFBMotionClip->Stop = *(pTime.mFBTime); }
	FBTime_Wrapper* GetStop(  ) { return FBTime_Wrapper_Factory( mFBMotionClip->Stop ); }
};
#endif // pyfbmotionclip_h__