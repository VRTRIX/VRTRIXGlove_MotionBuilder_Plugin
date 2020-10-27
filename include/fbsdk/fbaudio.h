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

//! Action to perform, when preparing an Audio In object to record, when the action clip associated to the recording path is already in the scene.
enum FBExistingClipAction {
	kFBExistingClipAskUser,			//!< Ask the user for desired operation via a dialog.
	kFBExistingClipRemove,			//!< Remove the action clip from the scene.
	kFBExistingClipAbortOperation	//!< Cancel preparing the audio in to record.
};

//! Action to perform, when preparing an Audio In object to record, when the action clip associated to the recording path already exists on disk and is not empty.
enum FBExistingFileAction {
	kFBExistingFileAskUser,			//!< Ask the user for desired operation via a dialog.
	kFBExistingFileOverwrite,		//!< Overwrite the existing file on disk.
	kFBExistingFileAppend,			//!< Append the new recording to existing recording. Warning: Be sure that the current file format match your recording option!
	kFBExistingFileAbortOperation,	//!< Cancel preparing the audio in to record.
};

FB_DEFINE_ENUM(FBSDK_DLL, AccessMode);
FB_DEFINE_ENUM(FBSDK_DLL, UseChnMode);
FB_DEFINE_ENUM(FBSDK_DLL, TriggerStyle);
FB_DEFINE_ENUM(FBSDK_DLL, ExistingClipAction);
FB_DEFINE_ENUM(FBSDK_DLL, ExistingFileAction);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBAudioIn
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Audio In class.
	Used to control Audio In objects (like a Microphone Audio Device).
    
    @code
    # This example shows how to prepare an FBAudioIn object for recording
    # by redirecting the audio to an FBAudioOut object and
    # by specifying a desired audio format and target audio file
    
    from pyfbsdk import *
    
    # Let's see how many FBAudioIn objects are available
    lAudioIns = FBSystem().AudioInputs
    print "The number of Audio Inputs:", len( lAudioIns )
    if len( lAudioIns ) > 0:
        # Work with the first Audio In object available
        lAudioIn = lAudioIns[0]
        print "Audio Input Name:", lAudioIn.Name
        
        # Let's turn it offline, if not already
        if lAudioIn.IsOnline():
            print "Turned offline successful?", lAudioIn.SetOnline( False )
        
        # Let's set the first AudioOut available as the Audio In destination
        # if any destination is set yet
        # (Windows Only)
        if lAudioIn.GetDestination() == None:
            lAudioOuts = FBSystem().AudioOutputs
            print "The number of Audio Outputs:", len( lAudioOuts )
            if len( lAudioOuts ) > 0:
                # Work with the first Audio Out object available
                lAudioOut = lAudioOuts[0]
                print "Audio Output Name:", lAudioOut.Name
                print "Setting destination successful?", lAudioIn.SetDestination( lAudioOut )
            else:
                print "No available Audio Out object available for destination"
        else:
            print "Audio Output <", lAudioIn.GetDestination().Name, "> already set for destination"
        
        # Let's try to record an audio file in 8-bit, 22060 hz and in stereo
        # Make sure this Audio In object supports this format
        lSupportedFormats = lAudioIn.GetSupportedFormats()
        if lSupportedFormats & FBAudioFmt_ConvertBitDepthMode( FBAudioBitDepthMode.kFBAudioBitDepthMode_8 ) != 0 and \
           lSupportedFormats & FBAudioFmt_ConvertRateMode( FBAudioRateMode.kFBAudioRateMode_22050 ) != 0 and \
           lSupportedFormats & FBAudioFmt_ConvertChannelMode( FBAudioChannelMode.kFBAudioChannelModeStereo ) != 0:
            
            # This format is supported, let's set it now
            lNewFormat  = FBAudioFmt_ConvertBitDepthMode( FBAudioBitDepthMode.kFBAudioBitDepthMode_8 )
            lNewFormat |= FBAudioFmt_ConvertRateMode( FBAudioRateMode.kFBAudioRateMode_22050 )
            lNewFormat |= FBAudioFmt_ConvertChannelMode( FBAudioChannelMode.kFBAudioChannelModeStereo )
            print "Setting recording format successful?", lAudioIn.SetRecordingFormat( lNewFormat )
            
            # Let's add a delay of 3 frames
            # (Windows only)
            print "Setting delay successful?", lAudioIn.SetDelay( FBTime( 0, 0, 0, 3 ) )
            
            # Let's turn it online now
            print "Turned online successful?", lAudioIn.SetOnline( True )
            
            # Now, prepare the Audio In object for recording
            # To turn it off first, if already in "Record" state
            if lAudioIn.IsReadyToRecord():
                print "Turned Off Recording?", lAudioIn.TurnOffRecording()
            
            lAudioFilePath = "C:\\temp\\myRecordedAudioFile.wav"
            
            # Note: To remove pop-ups that may occurs, if required, 
            # look at the optional parameters of the PrepareToRecord method
            print "Preparing to record successful?", lAudioIn.PrepareToRecord( lAudioFilePath )
            
            if lAudioIn.IsReadyToRecord():
                print "You are now ready to start recording and playback!"
            else:
                print "Something failed while preparing to record! Tip: Do you have a C:\temp folder?"
            
        else:
            print "This format (8-bit, 22060 hz, stereo) is not supported!"
    else:
        print "No available Audio In object available"
    @endcode
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


	/** Turns Audio In online or offline.
	*	\param	pOnline				True to turn the Audio In online, false to turn it offline.
	*	\return	True if operation is successful, false otherwise.
	*/
	bool SetOnline( bool pOnline );

	/** Is the Audio In online?
	*	\return	True if the Audio In is online, false if it is offline.
	*/
	bool IsOnline() const;


	/** Prepares the Audio In for recording (similar as checking the "Record" checkbox in the UI).
	*	If the Audio In is not already online, it will turn it online automatically.
	*	If the Audio In is already ready to record, it will turn it off first automatically.
	*	\param	pRecordingPath			The file path for the desired output wav file. The file must have the .wav extension.
	*	\param	pExistingClipAction		The action to perform when the action clip associated to the recording path is already in the scene.
	*	\param	pExistingFileAction		The action to perform when the file associated to the recording path already exists on disk and it not empty.
	*	\return	True if operation is successful, false otherwise. It could fail for different reasons (e.g. the specified file is not a WAV file or is invalid, the operation is abort by the user, etc.).
	*/
	bool PrepareToRecord(	const char*				pRecordingPath, 
							FBExistingClipAction	pExistingClipAction = kFBExistingClipAskUser,
							FBExistingFileAction	pExistingFileAction = kFBExistingFileAskUser );

	/** Turns off the Audio In recording (similar as un-checking the "Record" checkbox in the UI).
	*	\return	True if operation is successful, false otherwise.
	*/
	bool TurnOffRecording();

	/** Is the Audio In ready to record (has it been prepared properly)?
	*	\return	True if the audio is ready to record, false otherwise. 
	*/
	bool IsReadyToRecord() const;


	/** Returns all the Audio In supported formats (i.e. Bit Depths, Rates and Channels).
	*	\return	The Audio In supported formats.
	*/
	FBAudioFmt GetSupportedFormats() const;

	/** Sets the recording format (i.e. Bit Depth, Rate and Channel(s)) to use. The Audio In must be offline when this method is called.
	*	\param	pAudioFormat			The audio format to use for recording. It must specify a unique Bit Depth, Rate and Channels.
	*	\return	True if operation is successful, false otherwise. It could fail for different reasons (e.g. the specified audio format is not supported, more than one Bit Depth is specified, etc.).
	*/
	bool SetRecordingFormat( FBAudioFmt pAudioFormat );

	/** Returns the recording format (i.e. Bit Depth, Rate and Channel(s)) currently set.
	*	\return	The audio format currently set for recording.
	*/
	FBAudioFmt GetRecordingFormat() const;


	/** Sets the delay to use. The Audio In must be offline when this method is called. (Windows only).
	*	\param	pDelay				The delay to use. To mimic the UI, the FBTime should refer to a frame number.
	*	\return	True if operation is successful, false otherwise.
	*/
	bool SetDelay( FBTime& pDelay );

	/** Returns the delay currently set. (Windows only).
	*	\return	The delay currently set.
	*/
	FBTime GetDelay() const;


	/** Sets the Audio Out object to be used as the destination. The Audio In must be offline when this method is called. (Windows only).
	*	\param	pAudioOut				The Audio Out object to be used as the destination. Use a NULL pointer (None in Python) to unset the destination.
	*	\return	True if operation is successful, false otherwise.
	*/
	bool SetDestination( FBAudioOut* pAudioOut );

	/** Returns the Audio Out object currently used as the destination. (Windows only).
	*	\return	The Audio Out object currently used as the destination. Returns a NULL pointer (None in Python) if any Audio Out object is currently set.
	*/
	FBAudioOut* GetDestination() const;
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
