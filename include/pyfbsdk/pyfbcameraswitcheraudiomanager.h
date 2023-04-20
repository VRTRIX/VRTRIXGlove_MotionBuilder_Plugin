#ifndef pyfbcameraswitcheraudiomanager_h__
#define pyfbcameraswitcheraudiomanager_h__
/**************************************************************************
 Copyright 2019 Autodesk, Inc.
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

#include "pyfbaudioclip.h"
#include "pyfbstorytrack.h"

// =======================================================================================
// FBCameraSwitcherAudioManager
// =======================================================================================
void FBCameraSwitcherAudioManager_Init();

class PYSDK_DLL FBCameraSwitcherAudioManager_Wrapper
	: public FBComponent_Wrapper
{
public:
	FBCameraSwitcherAudioManager* mFBCameraSwitcherAudioManager;

public:
	FBCameraSwitcherAudioManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBCameraSwitcherAudioManager = (FBCameraSwitcherAudioManager*)pFBComponent; }
	FBCameraSwitcherAudioManager_Wrapper( ) : FBComponent_Wrapper( &FBCameraSwitcherAudioManager::TheOne() ) { mFBCameraSwitcherAudioManager = (FBCameraSwitcherAudioManager*)mFBComponent; }
	virtual ~FBCameraSwitcherAudioManager_Wrapper( ) { }

	bool SetShowAudio( bool pShow );
	bool GetShowAudio();
	bool SetAudioClip( FBAudioClip_Wrapper& pAudioClip );
	object GetAudioClip();
	bool SetAudioTrack( FBStoryTrack_Wrapper& pAudioTrack );
	object GetAudioTrack();
	bool RemoveAudio();
	bool SetShowLeftChannel( bool pShow );
	bool GetShowLeftChannel();
	bool SetShowRightChannel( bool pShow );
	bool GetShowRightChannel();
	bool SetLockPitchToSpeed( bool pLock );
	bool GetLockPitchToSpeed();
};


#endif //pyfbcameraswitcheraudiomanager_h__
