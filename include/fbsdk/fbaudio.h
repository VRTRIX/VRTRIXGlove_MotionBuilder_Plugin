#ifndef __FBAUDIO_H__
#define __FBAUDIO_H__
/**************************************************************************
 Copyright (c) 1994 - 2009 Autodesk, Inc. and/or its licensors.
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

/**	\file fbaudio.h
*	Audio interface for FBSDK
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbaudiofmt.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBAudioIn );
__FB_FORWARD( FBAudioOut );
__FB_FORWARD( FBAudioClip );
FB_DEFINE_COMPONENT( FBSDK_DLL, AudioIn );
FB_DEFINE_COMPONENT( FBSDK_DLL, AudioOut );
FB_DEFINE_COMPONENT( FBSDK_DLL, AudioClip );

//! Data access modes.
enum FBAccessMode {
	kFBAccessModeDisk,	//!< Access data directly to disk using a cache system.
	kFBAccessModeMemory	//!< Access data from memory, which means that it will copyed entirely into it.
};

//! Use Channel modes.
enum FBUseChnMode {
	kFBUseChannelLeftOnly,	//!< Left channel will be played in both speakers.
	kFBUseChannelRightOnly,	//!< Right channel will be played in both speakers.
	kFBUseChannelBoth		//!< Default mode, where each channel play in its respective speaker.
};

//! Audio clips' trigger styles.
enum FBTriggerStyle {
	kFBTriggerStyleContinue,	//!< Previously triggered clips that are still playing won't be stopped and mixing will occur.
	kFBTriggerStyleCut,			//!< Previously triggered clips that are still playing will be stopped.
	kFBTriggerStyleToggle		//!< If a previously triggered clip is playing, it will only be stopped, otherwise a new starts playing. No mixing and no loop.
};

FB_DEFINE_ENUM(FBSDK_DLL, AccessMode);
FB_DEFINE_ENUM(FBSDK_DLL, UseChnMode);
FB_DEFINE_ENUM(FBSDK_DLL, TriggerStyle);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBAudioIn
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Audio In class.
*	Properties of this class are work in progress, but you can still list them and get their names.
*/
class FBSDK_DLL FBAudioIn : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBAudioIn, FBComponent);
public:

	/**	Constructor.
	*	\param	pObject	For internal use only.
	*/
	FBAudioIn(HIObject pObject=NULL);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBAudioOut
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Audio Out class.
*	Properties of this class are work in progress, but you can still list them and get their names.
*/
class FBSDK_DLL FBAudioOut : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBAudioOut, FBComponent);
public:

	/**	Constructor.
	*	\param	pObject	For internal use only.
	*/
	FBAudioOut(HIObject pObject=NULL);
};

//! Get default audio output.
FBSDK_DLL FBAudioOut* FBAudioOutGetDefault();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBAudioClip
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Used to play audio clips and access their properties.
*	This class permits you to access audio clip's properties to read or change them.
*/
class FBSDK_DLL FBAudioClip : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBAudioClip, FBComponent);
public:

	/**	Constructor.
	*	\param	pFileName			The complete file path of the media file to access.
	*	\param	pSetToDefaultDest	If true and the media file open successfully, it will automatically be connected to an output device.
	*	\param	pObject				For internal use only.
	*/
	FBAudioClip(const char* pFileName, bool pSetToDefaultDest=true, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	/** Play audio clip now.
	*	\param	pStyle			How the audio clip should be triggered.
	*	\param	pDestination	Where the audio clip should be played. If NULL, it will play on the default destination.
	*	\return	Return true if the buffer for the audio clip was successfully allocated so that you can hear the sound.
	*/
	bool Play(FBTriggerStyle pStyle=kFBTriggerStyleContinue, FBAudioOut* pDestination=NULL);

	/** Stop any playing triggered audio clip on a specified destination.
	*	\param	pDestination	Where the audio clip is playing. If NULL, the default destination will be used.
	*/
	void Stop(FBAudioOut* pDestination=NULL);

	/**	Check if the audio clip constructed properly.
	*	\return	true if the audio clip was constructed properly.
	*/
	bool IsMediaReady();

	/**	Load an audio clip file.
	*	\param	pPath	The filesystem path of the audio clip file to load.
	*	\return	true if the audio clip loaded successfully.
	*/
	bool FileOpen(char const * pPath);


    FBPropertyString		Path;		    //!< <b>Read Only Property:</b> Full Path of the media.
    FBPropertyString		Filename;		//!< <b>[Deprecated]Read Only Property:</b> Refer to Path
    FBPropertyString		RelativePath;	//!< <b>Read Only Property:</b> Relative path of media.

    FBPropertyInt			Format;			//!< <b>Read Only Property:</b> Data format of media, including rate, bits and channels count. You can typecast it to a FBAudioFmt.
    FBPropertyInt			Channels;		//!< <b>Read Only Property:</b> the number of channels in use.
    FBPropertyInt			Rate;			//!< <b>Read Only Property:</b> the rate of media.
    FBPropertyInt			Bits;			//!< <b>Read Only Property:</b> the bits of media.
    FBPropertyAccessMode	AccessMode;		//!< <b>Read Write Property:</b> Specify the media data access mode between disk or memory.
    FBPropertyUseChnMode	UseChannel;		//!< <b>Read Write Property:</b> Enables you to control which track are used with stereo clips.
    FBPropertyUseChnMode	UseChannelMode;	//!< <b>[Deprecated]Read Write Property:</b> Enables you to control which track are used with stereo clips.
    FBPropertyDouble		ClipSpeed;		//!< <b>Read Write Property:</b> The speed of the media when being played.	

    FBPropertyTime          SrcIn;          //!< <b>Read Only Property:</b> The begin time of media.
    FBPropertyTime          SrcDuration;    //!< <b>Read Only Property:</b> The duration time of media.
    FBPropertyTime          SrcEnd;         //!< <b>Read Only Property:</b> The end time of media.
    
    FBPropertyTime          InPoint;        //!< <b>[Deprecated]Read Write Property:</b> Refer to DstIn.
    FBPropertyTime          DstIn;          //!< <b>Read Write Property:</b> When not used in the Story, this specify when the clips begin to play.
    FBPropertyTime          Duration;       //!< <b>[Deprecated]Read Write Property:</b> Refer to DstDuration.
    FBPropertyTime          DstDuration;    //!< <b>Read Write Property:</b> When not used in the Story, this specify when the clips stops playing.
    FBPropertyTime          EndPoint;       //!< <b>[Deprecated]Read Write Property:</b> Refer to DstEnd.
    FBPropertyTime          DstEnd;         //!< <b>Read Write Property:</b> Total duration of this audio clip.
    
	FBPropertyBool			TakeSetsInPoint;	//!< <b>[Deprecated]Read Write Property:</b> Indicates whether to lock the InPoint to the start of the take.
    FBPropertyBool			ConstrainDstToTake;	//!< <b>Read Write Property:</b> Indicates whether to constrain the EndPoint to the end of the take.
    FBPropertyBool			Scrubbing;			//!< <b>Read Write Property:</b> Control which clip (one at a time) can shuttle when playing a various speeds.
    FBPropertyBool			LockClipSpeed;		//!< <b>Read Write Property:</b> Indicates whether to lock the current playing speed.

    FBPropertyTake			CurrentTake;	//!< <b>Read Write Property:</b> The take this media belongs to.
    FBPropertyAudioOut		Destination;	//!< <b>Read Write Property:</b> The audio output destination where the clip will be played.

    FBPropertyDouble        Pitch;              //!< <b>Read Write Property:</b> The audio clip pitch value. To write to this property, you must first set LockPitchToSpeed property to false.
    FBPropertyBool          LockPitchToSpeed;   //!< <b>Read Write Property:</b> Time stretch enabled factor.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! <b>List:</b> AudioIn
class FBSDK_DLL FBPropertyListAudioIn : public FBPropertyListComponent
{
public:
	FBPropertyListAudioIn();
	/**	Get the audio input at \e pIndex.
	*	\param	pIndex	Index of audio input to get.
	*	\return Audio input at \e pIndex.
	*/
	FBAudioIn* operator[](int pIndex);
};

//! <b>List:</b> AudioOut
class FBSDK_DLL FBPropertyListAudioOut : public FBPropertyListComponent
{
public:
	FBPropertyListAudioOut();
	/**	Get the audio output at \e pIndex.
	*	\param	pIndex	Index of audio output to get.
	*	\return Audio output at \e pIndex.
	*/
	FBAudioOut* operator[](int pIndex);
};

//! <b>List:</b> AudioClip
class FBSDK_DLL FBPropertyListAudioClip : public FBPropertyListComponent
{
public:
	FBPropertyListAudioClip();
	/**	Get the audio clip at \e pIndex.
	*	\param	pIndex	Index of audio clip to get.
	*	\return Audio clip at \e pIndex.
	*/
	FBAudioClip* operator[](int pIndex);
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
