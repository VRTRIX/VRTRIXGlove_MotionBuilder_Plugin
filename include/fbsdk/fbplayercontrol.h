#ifndef __FBPLAYERCONTROL_H__
#define __FBPLAYERCONTROL_H__
/**************************************************************************
Copyright (c) 1994 - 2013 Autodesk, Inc. and/or its licensors.
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

/**	\file fbplayercontrol.h
*	Transport control and timing management interface
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

// Essential includes
#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbcommand.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {;
#endif

//! Transport modes.
enum FBTransportMode {	
    kFBTransportPlay,			/**!< Play mode		*/	kFBTransportPlayPrepare,		kFBTransportPlayReady,
    kFBTransportStop,			/**!< Stop mode		*/	kFBTransportStopPost,			kFBTransportStopReady,
    kFBTransportShuttle,		/**!< Shuttle mode	*/	kFBTransportShuttlePrepare,		kFBTransportShuttleReady,
    kFBTransportPlayReverse,	/**!< Play reverse.	*/	kFBTransportPlayReversePrepare,	kFBTransportPlayReverseReady,
    kFBTransportJog,			/**!< Jog.			*/	kFBTransportJogPrepare,			kFBTransportJogReady,
    kFBTransportGoto,			/**!< Goto.			*/	kFBTransportGotoPrepare,		kFBTransportGotoReady,
    kFBTransportStepForward,	/**!< Step forward	*/	kFBTransportStepForwardPrepare,	kFBTransportStepForwardReady,
    kFBTransportStepBackward,	/**!< Step backward.*/	kFBTransportStepBackwardPrepare,kFBTransportStepBackwardReady
};
FB_DEFINE_ENUM( FBSDK_DLL, TransportMode );

//! Available transport control time display.
enum FBTransportTimeFormat
{
    kFBTimeFormatTimecode, //!< Timecode time display mode.
    kFBTimeFormatFrame, //!< Frame time display mode.
};

FB_DEFINE_ENUM(FBSDK_DLL, TransportTimeFormat);


//! Available transport control play speed.
enum FBTransportPlaySpeed
{
    kFBSpeed_1_10x, //!< 0.10x
    kFBSpeed_1_5x,  //!< 0.20x
    kFBSpeed_1_4x,  //!< 0.25x
    kFBSpeed_1_3x,  //!< 0.33x
    kFBSpeed_1_2x,  //!< 0.50x
    kFBSpeed_1x,    //!< 1x
    kFBSpeed_ALL_FR, //!< All frames
    kFBSpeed_2x,    //!< 2x
    kFBSpeed_3x,    //!< 3x
    kFBSpeed_4x,    //!< 4x
    kFBSpeed_5x,    //!< 5x
    kFBSpeed_10x,    //!< 10x
    kFBSpeed_Custom //!< Custom speed
};
FB_DEFINE_ENUM( FBSDK_DLL, TransportPlaySpeed);

//! Available snap methods for the transport control.
enum FBTransportSnapMode
{
    kFBTransportSnapModeNoSnap,              //!< No snapping is applied.
    kFBTransportSnapModeSnapOnFrames,        //!< Snaps to an exact frame when modifying the current time.
    kFBTransportSnapModePlayOnFrames,        //!< When playing, plays to exact frames.
    kFBTransportSnapModeSnapAndPlayOnFrames, //!< Combines both Snap and Play on frames modes.
};
FB_DEFINE_ENUM( FBSDK_DLL, TransportSnapMode );

//! Available loop modes for the transport control.
enum FBTransportLoopMode {
	kFBTransportNoLoop,					//!< Playback not looping.
	kFBTransportLoopCurrentTake,		//!< Playback looping the current take.
	kFBTransportLoopThroughAllTakes,	//!< Playback from the current take through all takes in order then stops.
};
FB_DEFINE_ENUM( FBSDK_DLL, TransportLoopMode );

//! Types of player control change events.
enum FBPlayerControlChangeType {
	kFBPlayerControlNone,			//!< None
	kFBPlayerControlPlay,			//!< Play
	kFBPlayerControlPlayReverse,	//!< Play reverse
	kFBPlayerControlStop,			//!< Stop
	kFBPlayerControlStepForward,	//!< Step forward
	kFBPlayerControlStepBackward,	//!< Step backward
	kFBPlayerControlGoto,			//!< Goto
	kFBPlayerControlRecordModeOn,	//!< Record mode on
	kFBPlayerControlRecordModeOff,	//!< Record mode off
};
FB_DEFINE_ENUM( FBSDK_DLL, PlayerControlChangeType );

////////////////////////////////////////////////////////////////////////////////////
// FBEventPlayerControlChange
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventPlayerControlChange );

class FBSDK_DLL FBEventPlayerControlChange: public FBEvent 
{
	public:
		/**	Constructor.
		*	\param pEvent Base event (internal) to obtain information from.
		*/
		FBEventPlayerControlChange( HKEventBase pEvent );		

		FBPropertyPlayerControlChangeType	Type;			 //!< <b>Read Only Property:</b> Type of event.
};


////////////////////////////////////////////////////////////////////////////////////
// FBPlayerControl
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBPlayerControl );

/**	Player control.
*	Interface to use the transport controls (play, stop, etc.)
The following Python snippet shows its basic playback operation
\code
lPlayer = FBPlayerControl()
lPlayer.GotoStart()
lPlayer.Play()
\endcode
Keys can also be set and used with Key(), GotoNextKey(), and GotoPreviousKey().
\n
All actions are performed by default on the current take. The is the MotionBuilder
default take, unless you have multiple takes in your scene. To switch between takes,
use FBTake.
*/
class FBSDK_DLL FBPlayerControl : public FBComponent {
    __FBClassDeclare( FBPlayerControl,FBComponent );
public:

    /**	Constructor.
    *	\param	pObject		Internal parent object(default=NULL).
    */
    FBPlayerControl(HIObject pObject=NULL);

    /**	Play button.
    *	\param	pUseMarkers	Play until next marker if true, ignore markers otherwise.
    *	\return	true if successful.
    */
    bool Play(bool pUseMarkers = false);

    /**	Play Reverse button.
    *	\param	pUseMarkers	Play until next marker if true, ignore markers otherwise.
    *	\return	true if successful.
    */
    bool PlayReverse(bool pUseMarkers = false);

    /**	Set Play Speed Mode. 
    *	\param	pPlaySpeedMode	a pre-defined play speed mode.  Don't make sense to input kFBSpeed_Custom. To set the custom speed, use SetPlaySpeed() function directly.
    */
    void SetPlaySpeedMode (FBTransportPlaySpeed pPlaySpeedMode);

    /**	Set Play Speed.
    *	\param	pPlaySpeed	set customized speed. It will automatically convert to one of pre-defined play speed mode if it is equal to the pre-defined speed.
    */
    void SetPlaySpeed(double pSpeed);

    /**	Get Play Speed Mode.
    *	\return	transport current playback speed mode, including kFBSpeed_Custom mode.
    */
    FBTransportPlaySpeed GetPlaySpeedMode();

    /**	Get Play Speed .
    *	\return	transport current playback speed.
    */
    double GetPlaySpeed();

    /**	Stop button.
    *	\return	true if successful.
    */
    bool Stop();

    /**	GotoStart button (Rewind).
    *	\return	true if successful.
    */
    bool GotoStart();

    /**	GotoEnd button (FastForward).
    *	\return	true if successful.
    */
    bool GotoEnd();

    /**	Goto a time specified by \p pTime.
    *	\param	pTime	Time to jump to.
    *	\return	true if successful.
    */
    bool Goto( FBTime pTime );

    /**	Step one frame ahead.
    *	\return	true if successful.
    */
    bool StepForward();

    /**	Step one frame backward.
    *	\return	true if successful.
    */
    bool StepBackward();

    /**	Begin recording.
    *	\param	pOverrideTake	Write over current take?(default=false)
    *	\param	pCopyData		Unused. Necessary for compatibility(default=true).
    *	\return	true if successful.
    */
    bool Record( bool pOverrideTake=false,bool pCopyData=true );

    /** Lock the transport control 
    * \param pLock		boolean value that indicates the new locked state of the transport. 
    *
    */
    void LockTransport( bool pLock );

    /** Return the current locking state of the transport 
    *
    */
    bool IsLocked(); 

    /** Get Transport Mode.
    *	\return Current mode of the transport controls.
    */
    FBTransportMode	GetTransportMode();

    /**	Set the system frame rate use for display.
    *	\param	pTimeMode	Indicate the frame rate value to use base on the FBTimeMode values enum.(kFBTimeModeDefault will be stored in fps)
    *   \param  pCustom     Should the time mode be kFBTimeModeCustom, this is used to specify the custom framerate.
    */
    void       SetTransportFps ( FBTimeMode pTimeMode, double pCustom=0.0);

    /**	Get the UI frame rate use for display configure in the system
    *	\return current FrameRate selected for the system. 
    */
    FBTimeMode GetTransportFps ();

    /**	Get the UI frame rate value
    *   \param pTimeMode the time mode whose frame rate will be returned
    *	\return Frame rate of the input time mode or system time mode when pTimeMode is not provided.
    */
    double     GetTransportFpsValue ( FBTimeMode pTimeMode = kFBTimeModeDefault );

    /** Key default data.
    *	Key all selected data.
    */
    void Key();

    /** Go to the next key.
    */
    void GotoNextKey();

    /** Go to the previous key.
    */
    void GotoPreviousKey();

    /** Pause device evaluation thread.
    */
    void EvaluationPause();

    /** Resume device evaluation thread.
    */
    void EvaluationResume();

    /* K_DEPRECATED_2019 */ FBPropertyBool	LoopActive;		//!< <b>Read Write Property:</b> Is looping active? Deprecated, use the LoopMode property instead.
	FBPropertyTransportLoopMode LoopMode;	//!< <b>Read Write Property:</b> Loop mode.
    FBPropertyTime	LoopStart;		//!< <b>Read Write Property:</b> Loop begin time.
    FBPropertyTime	LoopStop;		//!< <b>Read Write Property:</b> Loop end time.

    FBPropertyTime	ZoomWindowStart;	//!< <b>Read Write Property:</b> Starting time of the transport control zoom window.
    FBPropertyTime	ZoomWindowStop;		//!< <b>Read Write Property:</b> Stopping time of the transport control zoom window.

    FBPropertyTime	NextMarker;		//!< <b>Read Only Property:</b> Next marked time.
    FBPropertyTime	PreviousMarker;	//!< <b>Read Only Property:</b> Previous marked time.

    FBPropertyBool	IsRecording;	//!< <b>Read Only Property:</b> Is there a recording in progress?
    FBPropertyBool	IsPlaying;		//!< <b>Read Only Property:</b> Is the transport control playing?
    FBPropertyBool	IsPlotting;		//!< <b>Read Only Property:</b> Is there a plotting in progress?

    FBPropertyTransportSnapMode SnapMode;   //!< <b>Read Write Property:</b> Set the transport control snap mode.

    FBPropertyTransportTimeFormat TransportTimeFormat; //!< <b>Read Write Property:</b> Current Time Mode of the transport controls.

    FBPropertyTime	RecordingSamplingPeriod;	//!< <b>Read Write Property:</b> Sampling period for the model recording.
    FBPropertyTime	PlotSamplingPeriod;			//!< <b>Read Write Property:</b> Sampling period for the model plotting.

    FBPropertyEvent	OnChange;					//!< <b>Event Property:</b> Fired when something in the player control has changed. (see FBEventPlayerControlChange)

    /**	Get the global object for this class
    *	\return	the global object.
    */
    static FBPlayerControl& TheOne();

	/**	Goto a time specified by \e pTime. 
	*	\param	pTime				Time to jump to.
	*	\param	pTimeReferential	Time referential to use. kFBTimeReferentialAction or kFBTimeReferentialEdit
	*	\return	\b true if successful.
	*/
	bool Goto( FBTime, FBTimeReferential );

	/**	GotoStart button (Rewind).
	*	\param	pTimeReferential	Time referential to use. kFBTimeReferentialAction or kFBTimeReferentialEdit
	*	\return	\b true if successful.
	*/
	bool GotoStart( FBTimeReferential );

	/**	GotoEnd button (FastForward).
	*	\param	pTimeReferential	Time referential to use. kFBTimeReferentialAction or kFBTimeReferentialEdit
	*	\return	\b true if successful.
	*/
	bool GotoEnd( FBTimeReferential );

	/**	Step one frame ahead.
	*	\param	pTimeReferential	Time referential to use. kFBTimeReferentialAction or kFBTimeReferentialEdit
	*	\return	\b true if successful.
	*/
	bool StepForward( FBTimeReferential );

	/**	Step one frame backward.
	*	\param	pTimeReferential	Time referential to use. kFBTimeReferentialAction or kFBTimeReferentialEdit
	*	\return	\b true if successful.
	*/
	bool StepBackward( FBTimeReferential );

	/** Get Time Referential.
	*	\return Current time referential.
	*/
	FBTimeReferential GetTimeReferential();

	/** Set Time Referential.
	*   \param  pTimeReferential The new time referential. Only kFBTimeReferentialAction and kFBTimeReferentialEdit are supported
	*/
	void SetTimeReferential(FBTimeReferential pTimeReferential);

	/** Get Edit Current Time.
	*	\return The current time, in the edit time referential.
	*/
	FBTime GetEditCurrentTime();

	/** Get Edit Start.
	*	\return Start value for the edit time range.
	*/
	FBTime GetEditStart();

	/** Set Edit Start.
	*   \param  pTime The new start value for the edit time range.
	*/
	void SetEditStart(FBTime pTime);

	/** Get Edit Stop.
	*	\return Stop value for the edit time range.
	*/
	FBTime GetEditStop();

	/** Set Edit Stop.
	*   \param  pTime The new stop value for the edit time range.
	*/
	void SetEditStop(FBTime pTime);

	/** Get Edit Zoom Start.
	*	\return Start value for the edit zoom window.
	*/
	FBTime GetEditZoomStart();

	/** Set Edit Zoom Start.
	*   \param  pTime The new start value for the edit zoom window.
	*/
	void SetEditZoomStart(FBTime pTime);

	/** Get Edit Zoom Stop.
	*	\return Stop value for the edit zoom window.
	*/
	FBTime GetEditZoomStop();

	/** Set Edit Zoom Stop.
	*   \param  pTime The new stop value for the edit zoom window.
	*/
	void SetEditZoomStop(FBTime pTime);

	/** Add a global time mark. It doesn't allow creating a time mark at the same time of another time mark.
	*   Note: Internally, the global time marks are stored in time order. Adding a time mark before other existing time marks will modify the index of these other time marks.
	*   \param pTime Time where to add the time mark.
	*   \param pName Name of the time mark to add.
	*   \return The index of the time mark added if the operation is successful, -1 otherwise.
	*/
	int AddGlobalTimeMark( FBTime pTime, const char* pName = NULL );

	/** Delete a global time mark.
	*   Note: Internally, the global time marks are stored in time order. Deleting a time mark will modify the index of time marks laying after the deleted time mark.
	*   \param pIndex Index of the time mark to delete.
	*   \return True if the operation is successful, false otherwise.
	*/
	bool DeleteGlobalTimeMark( int pIndex );

	/** Delete all global time marks.
	*/
	void DeleteAllGlobalTimeMarks();

	/** Returns the number of global time marks.
	*   \return The number of global time marks.
	*/
	int GetGlobalTimeMarkCount();

	/** Returns the time associated with a global time mark.
	*   \param pIndex Index of the time mark.
	*   \return The time associated with the time mark.
	*/
	FBTime GetGlobalTimeMarkTime( int pIndex );

	/** Sets a new time for an existing global time mark.
	*   Note: Internally, the global time marks are stored in time order. Modifying the time of a time mark may modify the index of all time marks.
	*   \param pIndex Index of the time mark.
	*   \param pTime The new time for the time mark.
	*   \return The new index of the modified time mark.
	*/
	int SetGlobalTimeMarkTime( int pIndex, FBTime pTime );

	/** Returns the name associated with a global time mark.
	*   \param pIndex Index of the time mark.
	*   \return The name associated with the time mark.
	*/
	const char* GetGlobalTimeMarkName( int pIndex );

	/** Sets a new name for an existing global time mark.
	*   \param pIndex Index of the time mark.
	*   \param pName The new name for the time mark.
	*   \return True if the operation is successful, false otherwise.
	*/
	bool SetGlobalTimeMarkName( int pIndex, const char* pName );

	/** Returns the action associated with a global time mark.
	*   \param pIndex Index of the time mark.
	*   \return The action associated with the time mark.
	*/
	FBTimeMarkAction GetGlobalTimeMarkAction( int pIndex );

	/** Sets a new action for an existing global time mark.
	*   \param pIndex Index of the time mark.
	*   \param pAction The new action for the time mark.
	*   \return True if the operation is successful, false otherwise.
	*/
	bool SetGlobalTimeMarkAction( int pIndex, FBTimeMarkAction pAction );

	/** Returns the color associated with a global time mark.
	*   \param pIndex Index of the time mark.
	*   \return The color associated with the time mark.
	*/
	FBColor GetGlobalTimeMarkColor( int pIndex );

	/** Sets a new color for an existing global time mark.
	*   \param pIndex Index of the time mark.
	*   \param pColor The new color for the time mark.
	*   \return True if the operation is successful, false otherwise.
	*/
	bool SetGlobalTimeMarkColor( int pIndex, FBColor pColor );

	/** Returns the next global time mark index, based on the current local time.
	*   \return The next global time mark index, -1 if any next time mark is available.
	*/
	int GetNextGlobalTimeMarkIndex();

	/** Returns the previous global time mark index, based on the current local time.
	*   \return The previous global time mark index, -1 if any previous time mark is available.
	*/
	int GetPreviousGlobalTimeMarkIndex();
};

////////////////////////////////////////////////////////////////////////////////////
// FBReferenceTime
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBReferenceTime );

/**	Reference time class.
*	Interface for the reference time used by MotionBuilder
The reference time are identified using unique ID. A unique ID is given when a reference time is added to the system with Add().
Instead of using a linear array to store the reference time, a map is used to link an ID to a reference time.
The available IDs can be queried using GetUniqueIDList().
*/
class FBSDK_DLL FBReferenceTime : public FBComponent {
    __FBClassDeclare( FBReferenceTime,FBComponent );
public:
    /**	Constructor.
    *	\param	pObject	For internal use only(default=NULL).
    */
    FBReferenceTime(HIObject pObject=NULL);

    /**	Add a reference time to list.
    *	\param	pName	Name of time to add the list.
    *	\return Unique ID of the reference time, use this ID to access the reference time in the future.
    */
    int    Add( const char *pName );

    /**	Remove a reference time from the list.
    *	\param	pID	ID of reference time to remove.
    */
    void   Remove( int pID );

    /**	Set a reference time.
    *	\param	pID				ID of reference time set.
    *	\param	pReferenceTime	Time to use as reference time.
    *	\param	pSystem			System time.
    */
    void   SetTime( int pID, FBTime pReferenceTime, FBTime pSystem );
    /**	Get a reference time.
    *	\param	pID			ID of reference to get.
    *	\param	pSystem		System time.
    *	\return	Reference time at \p pIndex.
    */
    FBTime GetTime( int pID, FBTime pSystem );

    /**	Overloaded [] operator
    *	\param	pID
    *	\return	Name of reference time with the \p pID.
    */
    const char *operator[](int pID);

    /**	Get list of currently available IDs.
    *	\param	pIDArray	Array that will be filled with the requested IDs.
    */
    void GetUniqueIDList( FBArrayTemplate<int>* pIDArray );

    /**	Get the name of a time reference.
    *	\param	pID	ID of the time reference whose name will be returned.
    *	\return	Name of reference time with the \p pID.
    */
    const char * GetReferenceTimeName( int pID );

    /*K_DEPRECATED_2019*/ FBPropertyInt				Count;			//!< <b>Read Only Property:</b> Number of reference times. Deprecated, use GetUniqueIDList() instead.
    /*K_DEPRECATED_2019*/ FBPropertyInt				ItemIndex;		//!< <b>Read Write Property:</b> Current reference time index. Deprecated, use CurrentTimeReferenceID instead.

	FBPropertyInt				CurrentTimeReferenceID;		//!< <b>Read Write Property:</b> Current reference time ID
	FBPropertyBool				UseRelativeLocalTime;		//!< <b>Read Write Property:</b> True to show the relative local time, false otherwise. This will only be effective when displaying the Local Time, but the state can be changed even if not currently displaying the Local Time.
};

#ifdef FBSDKUseNamespace
} // namespace FBSDKNamespace
#endif

#endif