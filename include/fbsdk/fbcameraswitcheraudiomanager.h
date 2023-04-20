#ifndef __FBCAMERASWITCHERAUDIOMANAGER_H__
#define __FBCAMERASWITCHERAUDIOMANAGER_H__
/**************************************************************************
Copyright (c) 1994 - 2019 Autodesk, Inc. and/or its licensors.
All Rights Reserved.

The coded instructions, statements, computer programs, and/or related 
material (collectively the "Data") in these files contain unpublished 
information proprietary to Autodesk, Inc. and/or its licensors, which is 
protected by Canada and United States of America federal copyright law 
and by international treaties.

The Data may not be disclosed or distributed to third parties, in whole 
or in part, without the prior written consent of Autodesk, Inc. 
("Autodesk").

THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO 
WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR 
ARISING BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES 
OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
PURPOSE OR USE. WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT 
WARRANT THAT THE OPERATION OF THE DATA WILL BE UNINTERRUPTED OR ERROR 
FREE.

IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS 
OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR 
EXPENSES OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE 
DAMAGES OR OTHER SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS 
OF PROFITS, REVENUE OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR 
DAMAGES OF ANY KIND), HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF 
LIABILITY, WHETHER DERIVED FROM CONTRACT, TORT (INCLUDING, BUT NOT 
LIMITED TO, NEGLIGENCE), OR OTHERWISE, ARISING OUT OF OR RELATING TO THE 
DATA OR ITS USE OR ANY OTHER PERFORMANCE, WHETHER OR NOT AUTODESK HAS 
BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS OR DAMAGE.

**************************************************************************/

/**	\file fbcameraswitcheraudiomanager.h
*	
*	The FBCameraSwitcherAudioManager file contains the necessary declarations to 
*	interact with the Audio Manager of the Camera Switcher.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif //FBSDKUseNamespace

FB_FORWARD( FBStoryTrack );

FB_FORWARD( FBCameraSwitcherAudioManager );
FB_DEFINE_COMPONENT( FBSDK_DLL, FBCameraSwitcherAudioManager );

/** Camera Switcher Audio Manager class.
*   <b>This class allows users to interact with the Audio Manager of the Camera Switcher.</b>
*/
class FBSDK_DLL FBCameraSwitcherAudioManager: public FBComponent
{
	FBClassDeclare( FBCameraSwitcherAudioManager, FBComponent );

protected:
	/** Constructor.
		Protected constructor, use TheOne() access instead.
	*/
	FBCameraSwitcherAudioManager();

public:
	/** Set the 'Show Audio' state.
	*	\param pShow True to show the Audio waveform, false otherwise.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetShowAudio( bool pShow );

	/** Get the 'Show Audio' state.
	*	\return True if the 'Show Audio' state is set, false otherwise.
	*/
	bool GetShowAudio();
	
	/** Set the Audio Clip to display on the Camera Switcher.
	*	\param pAudioClip The Audio Clip to display.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetAudioClip( FBAudioClip* pAudioClip );

	/** Get the Audio Clip displayed on the Camera Switcher.
	*	\return The Audio Clip displayed, nullptr (C++) / None (Python) if any.
	*/
	FBAudioClip* GetAudioClip();

	/** Set the Audio Track to display on the Camera Switcher.
	*	\param pAudioTrack The Audio Track to display.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetAudioTrack( FBStoryTrack* pAudioTrack );

	/** Get the Audio Track displayed on the Camera Switcher.
	*	\return The Audio Track displayed, nullptr (C++) / None (Python) if any.
	*/
	FBStoryTrack* GetAudioTrack();

	/** Remove the audio clip or audio track currently displayed on the Camera Switcher.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool RemoveAudio();

	/** Set the 'Show Left Channel' state.
	*	\param pShow True to show the left channel, false otherwise.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetShowLeftChannel( bool pShow );

	/** Get the 'Show Left Channel' state.
	*	\return True if the 'Show Left Channel' state is set, false otherwise.
	*/
	bool GetShowLeftChannel();

	/** Set the 'Show Right Channel' state.
	*	\param pShow True to show the right channel, false otherwise.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetShowRightChannel( bool pShow );

	/** Get the 'Show Right Channel' state.
	*	\return True if the 'Show Right Channel' state is set, false otherwise.
	*/
	bool GetShowRightChannel();

	/** Set the 'Lock Pitch to Speed' state.
	*	\param pLock True to lock pitch to speed, false otherwise.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetLockPitchToSpeed( bool pLock );

	/** Get the 'Lock Pitch to Speed' state.
	*	\return True if the 'Lock Pitch to Speed' state is set, false otherwise.
	*/
	bool GetLockPitchToSpeed();

	/** Returns the only instance of FBCameraSwitcherAudioManager.
	* \return The only instance of FBCameraSwitcherAudioManager.
	*/
	static FBCameraSwitcherAudioManager& TheOne();
};

#ifdef FBSDKUseNamespace
}
#endif //FBSDKUseNamespace

#endif //__FBCAMERASWITCHERAUDIOMANAGER_H__
