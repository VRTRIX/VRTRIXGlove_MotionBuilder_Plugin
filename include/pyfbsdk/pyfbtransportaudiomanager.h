#ifndef pyfbtransportaudiomanager_h__
#define pyfbtransportaudiomanager_h__
/**************************************************************************
 Copyright 2018 Autodesk, Inc.
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
// FBTransportAudioManager
// =======================================================================================
void FBTransportAudioManager_Init();

class PYSDK_DLL FBTransportAudioManager_Wrapper
	: public FBComponent_Wrapper
{
public:
	FBTransportAudioManager* mFBTransportAudioManager;

public:
	FBTransportAudioManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBTransportAudioManager = (FBTransportAudioManager*)pFBComponent; }
	FBTransportAudioManager_Wrapper( ) : FBComponent_Wrapper( &FBTransportAudioManager::TheOne() ) { mFBTransportAudioManager = (FBTransportAudioManager*)mFBComponent; }
	virtual ~FBTransportAudioManager_Wrapper( ) { }

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


#endif //pyfbtransportaudiomanager_h__
