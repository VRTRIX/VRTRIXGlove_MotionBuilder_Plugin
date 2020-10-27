#ifndef __FBSTORY_H__
#define __FBSTORY_H__
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

/**	\file fbstory.h
*	Story interface for FBSDK
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbcore.h>
#include <fbsdk/fbvideo.h>
#include <fbsdk/fbmodel.h>
#include <fbsdk/fbcamera.h>

#ifndef FBXSDK_NAMESPACE
	#define FBXSDK_NAMESPACE fbxsdk
#endif

namespace FBXSDK_NAMESPACE {
	class FbxScene;
}

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBStory );
__FB_FORWARD( FBStoryFolder );
__FB_FORWARD( FBStoryTrack );
__FB_FORWARD( FBStoryClip );
__FB_FORWARD( FBStoryGroupClip );
FB_DEFINE_COMPONENT( FBSDK_DLL, Story );
FB_DEFINE_COMPONENT( FBSDK_DLL, StoryFolder );
FB_DEFINE_COMPONENT( FBSDK_DLL, StoryTrack );
FB_DEFINE_COMPONENT( FBSDK_DLL, StoryClip );
FB_DEFINE_COMPONENT( FBSDK_DLL, StoryGroupClip );
FB_DEFINE_COMPONENT( FBSDK_DLL, AnimationNode );
FB_DEFINE_COMPONENT( FBSDK_DLL, Video );
FB_DEFINE_COMPONENT( FBSDK_DLL, AudioClip );

//! Types for new story tracks.
enum FBStoryTrackType {
	kFBStoryTrackAnimation,		//!< Animation track.
	kFBStoryTrackCamera,		//!< Camera animation track.
	kFBStoryTrackCharacter,		//!< Character animation track.
	kFBStoryTrackConstraint,	//!< Constraint track.
	kFBStoryTrackCommand,		//!< Command track.
	kFBStoryTrackShot,			//!< Shot track.
	kFBStoryTrackAudio,			//!< Audio track.
	kFBStoryTrackVideo			//!< Video track.
};

//! References Modes for story animation tracks.
enum FBStoryTrackRefMode {
	kFBStoryTrackOverride,	//!< Override track.
	kFBStoryTrackAdditive	//!< Additive track.
};

//! Body Parts for story track character.
enum FBStoryTrackBodyPart {
	kFBStoryTrackBodyPartNone = 0,

	kFBStoryTrackBodyPartHead			= 1 << 0,

	kFBStoryTrackBodyPartLeftShoulder	= 1 << 1,
	kFBStoryTrackBodyPartLeftHand		= 1 << 2,
	kFBStoryTrackBodyPartLeftArm		= 1 << 3 | kFBStoryTrackBodyPartLeftShoulder | kFBStoryTrackBodyPartLeftHand,
	kFBStoryTrackBodyPartRightShoulder	= 1 << 4,
	kFBStoryTrackBodyPartRightHand		= 1 << 5,
	kFBStoryTrackBodyPartRightArm		= 1 << 6 | kFBStoryTrackBodyPartRightShoulder | kFBStoryTrackBodyPartRightHand,

	kFBStoryTrackBodyPartLeftFoot		= 1 << 7,
	kFBStoryTrackBodyPartLeftLeg		= 1 << 8 | kFBStoryTrackBodyPartLeftFoot,
	kFBStoryTrackBodyPartRightFoot		= 1 << 9,
	kFBStoryTrackBodyPartRightLeg		= 1 << 10| kFBStoryTrackBodyPartRightFoot,

	kFBStoryTrackBodyPartProps			= 1 << 11,
    kFBStoryTrackBodyPartExtensions		= 1 << 12,

	kFBStoryTrackBodyPartSpine			= 1 << 13,

	kFBStoryTrackBodyPartUpperBody		= kFBStoryTrackBodyPartHead | kFBStoryTrackBodyPartSpine |
										  kFBStoryTrackBodyPartLeftArm | kFBStoryTrackBodyPartLeftShoulder | kFBStoryTrackBodyPartLeftHand |
										  kFBStoryTrackBodyPartRightArm | kFBStoryTrackBodyPartRightShoulder | kFBStoryTrackBodyPartRightHand,

	kFBStoryTrackBodyPartLowerBody		= kFBStoryTrackBodyPartLeftLeg | kFBStoryTrackBodyPartLeftFoot | kFBStoryTrackBodyPartRightLeg | kFBStoryTrackBodyPartRightFoot,

	kFBStoryTrackBodyPartAll			= kFBStoryTrackBodyPartUpperBody | kFBStoryTrackBodyPartLowerBody,
};

//! Ghost Show Modes for story animation tracks.
enum FBStoryTrackGhostShowMode {
    kFBStoryTrackShowAllClips,                  //!< Show the ghosts for all the clips on the track.
    kFBStoryTrackShowCurrentTimeAdjacentClips	//!< Show the ghosts only for the previous clip, current clip, and next clip relative to current time.
};

//! Show Ghost Modes for story animation clips.
enum FBStoryClipShowGhostMode {
	kFBStoryClipAlways,		//!< Always show the ghost.
	kFBStoryClipTimeCursor,	//!< Show the ghost only on time cursor.
    kFBStoryClipTimeCustom	//!< Show the ghost for custom time frame.
};

//! Time mode to display ghost.
enum FBStoryClipGhostTimeMode {
	kFBStoryClipGhostCurrent,	//!< Show the ghost at current time of the clip.
	kFBStoryClipGhostStart,		//!< Show the ghost at start time of the clip.
	kFBStoryClipGhostStop,		//!< Show the ghost at stop time of the clip.
	kFBStoryClipGhostCustom		//!< Show the ghost at custom time of the clip. See GhostManipulatorCustomTime property.
};

//! Node function. 
enum FBStoryClipNodeFunction {
	kFBStoryClipNodeAverage,				//!< Average.
	kFBStoryClipNodeFloorProjection,		//!< Project on XZ plane.
	kFBStoryClipNodeNone					//!< None.
};

//! Solve Modes for story character clips.
enum FBStoryClipSolveMode {
	kFBStoryClipRetargetSkeleton,	//!< Solve retarget skeleton.
	kFBStoryClipAnimSkeleton,		//!< Solve skeleton animation.
	kFBStoryClipAnimFkIk,			//!< Solve forward and inverse kinematic animation.
	kFBStoryClipAnimSkeletonIk		//!< Solve skeleton inverse kinematic animation.
};

//! Several mirror planes to mirror animation.
enum FBStoryClipMirrorPlane {
    kFBStoryClipMirrorPlaneXY,	//!< X-Y plane.
    kFBStoryClipMirrorPlaneZY,	//!< Z-Y plane.
    kFBStoryClipMirrorPlaneXZ   //!< X-Z plane.
};

//! Compensation Modes for story character clips.
enum FBStoryClipCompMode {
	kFBStoryClipOff,	//!< No compensation.
	kFBStoryClipAuto,	//!< Automatic compensation.
	kFBStoryClipUser	//!< User defined compensation.
};

//! Matching Time Types, when matching clips to each other.
enum FBStoryClipMatchingTimeType
{
	kFBStoryClipMatchingTimeCurrentTime,						//!< Matches the start of the selected clip to the previous/next clip at the current time.
	kFBStoryClipMatchingTimeStartOfSelectedClip,				//!< Matches the start of the selected clip to the start of the blend with the previous clip.
	kFBStoryClipMatchingTimeBetweenPreviousAndSelectedClip,		//!< Matches the selected clip and the previous clip at the middle of the blend.
	kFBStoryClipMatchingTimeEndOfPreviousClip,					//!< Matches the end of the blend with the selected clip to the end of the previous clip.
	kFBStoryClipMatchingTimeStartOfNextClip,					//!< Matches the start of the blend with the selected clip to the start of the next clip.
	kFBStoryClipMatchingTimeBetweenSelectedAndNextClip,			//!< Matches the selected clip and the next clip at the middle of the blend.
	kFBStoryClipMatchingTimeEndOfSelectedClip,					//!< Matches the end of the selected clip to the end of the blend with the previous clip. 
	kFBStoryClipMatchingTimeDefault,							//!< Uses the matching time type stored in the Application configuration file: [Story] > MatchWhen. This value, in the configuration file, is update each time a matching is done, with the selected value.
};

//! Matching Translation, Types when matching clips to each other.
enum FBStoryClipMatchingTranslationType
{
	kFBStoryClipMatchingTranslationNone,			//!< The clip's match object is not translated to match another clip's animation.
	kFBStoryClipMatchingTranslationXYZ,				//!< Translates a selected clip's match object to the same location as the previous clip's match object.
	kFBStoryClipMatchingTranslationGravityXZ,		//!< Translates a selected clip's match object along the global X and Z axes.
	kFBStoryClipMatchingTranslationDefault,			//!< Uses the matching translation type stored in the Application configuration file: [Story] > MatchTranslation. This value, in the configuration file, is update each time a matching is done, with the selected value.
};

//! Matching Rotation Types, when matching clips to each other.
enum FBStoryClipMatchingRotationType
{
	kFBStoryClipMatchingRotationNone,				//!< The clip's match object is not rotated to match another clip's animation.
	kFBStoryClipMatchingRotationXYZ,				//!< Rotates a selected clip's match object to the same orientation as the previous clip's match object.
	kFBStoryClipMatchingRotationGravityXZ,			//!< Rotates a selected clip's match object around the global Y axis.
	kFBStoryClipMatchingRotationDefault,			//!< Uses the matching translation type stored in the Application configuration file: [Story] > MatchRotation. This value, in the configuration file, is update each time a matching is done, with the selected value.
};


//! Alignment Types when aligning clips.
enum FBStoryClipAlignmentType {
	kFBStoryClipAlignmentCurrentTimeline,			//!< Align all selected clips with the current time.
	kFBStoryClipAlignmentEndPrevious,				//!< Align selected clips to the end of the previous clip.
	kFBStoryClipAlignmentEndPreviousAllAligned,		//!< Align selected clips to the end of the previous clip, all clips will be align to the selected clip position.
	kFBStoryClipAlignmentBeginningNext,				//!< Align selected clips to the beginning of the next clip.
	kFBStoryClipAlignmentBeginningNextAllAligned,	//!< Align selected clips to the beginning of the next clip, all clips will be align to the selected clip position.
	kFBStoryClipAlignmentCurrentTimelineWithOffset,	//!< Align all selected clips with the current time, while keeping the relative offset.
	kFBStoryClipAlignmentEndPreviousWithOffset,		//!< Align selected clips to the end of the previous clip, while keeping the relative offset.
	kFBStoryClipAlignmentBeginningNextWithOffset	//!< Align selected clips to the beginning of the next clip, while keeping the relative offset.
};

//! Alignment Types when aligning groups.
enum FBStoryGroupClipAlignmentType {
	kFBStoryGroupClipAlignmentCurrentTimeline,			//!< Align the clips contained in the group clip with the current time.
	kFBStoryGroupClipAlignmentEndPreviousWithOffset,		//!< Align the clips contained in the group clip to the end of the previous clip, while keeping the relative offset.
	kFBStoryGroupClipAlignmentBeginningNextWithOffset,	//!< Align the clips contained in the group clip to the beginning of the next clip, while keeping the relative offset.
};

//! Types of clip change events, matching KEventClip.eType
//! Expose only kFBStoryClipMoveClip and kFBStoryClipRemoved for now
enum FBStoryClipChangeType {
	kFBStoryClipNotSet,     //!< Clip none
	kFBStoryClipMoveClip,   //!< Clip moved
	kFBStoryClipMoveData,   //!< Clip data moved
	kFBStoryClipMoveBlend,  //!< Clip move blend
	kFBStoryClipUpdateUI,   //!< Clip UI update
	kFBStoryClipRemoved     //!< Clip removed
};

//! Types of TimeWrap Interpolator for Story Clips.
enum FBStoryClipTimeWarpInterpolatorType {
	kFBStoryClipTimeWarpInterpolatorCustom,					//!< 'Custom' TimeWarp Interpolation
	kFBStoryClipTimeWarpInterpolatorLinear,					//!< 'Normal' TimeWarp Interpolation
	kFBStoryClipTimeWarpInterpolatorSmoothedEnds,			//!< 'Smoothed Ends' TimeWarp Interpolation
	kFBStoryClipTimeWarpInterpolatorGoingFaster,			//!< 'Going Faster' TimeWarp Interpolation
	kFBStoryClipTimeWarpInterpolatorSlowingDown,			//!< 'Slowing Down' TimeWarp Interpolation
	kFBStoryClipTimeWarpInterpolatorLinearReversed,			//!< 'Reversed' TimeWarp Interpolation
	kFBStoryClipTimeWarpInterpolatorSmoothedEndsReversed,	//!< 'Reversed, Smoothed Ends' TimeWarp Interpolation
	kFBStoryClipTimeWarpInterpolatorGoingFasterReversed,	//!< 'Reversed, Going Faster' TimeWarp Interpolation
	kFBStoryClipTimeWarpInterpolatorSlowingDownReversed		//!< 'Reversed, Slowing Down' TimeWarp Interpolation
};

FB_DEFINE_ENUM(FBSDK_DLL, StoryClipChangeType );
FB_DEFINE_ENUM(FBSDK_DLL, StoryTrackType);
FB_DEFINE_ENUM(FBSDK_DLL, StoryTrackRefMode);
FB_DEFINE_ENUM(FBSDK_DLL, StoryTrackGhostShowMode);
FB_DEFINE_ENUM(FBSDK_DLL, StoryClipShowGhostMode);
FB_DEFINE_ENUM(FBSDK_DLL, StoryClipGhostTimeMode);
FB_DEFINE_ENUM(FBSDK_DLL, StoryClipNodeFunction);
FB_DEFINE_ENUM(FBSDK_DLL, StoryClipSolveMode);
FB_DEFINE_ENUM(FBSDK_DLL, StoryClipMirrorPlane);
FB_DEFINE_ENUM(FBSDK_DLL, StoryClipCompMode);
FB_DEFINE_ENUM(FBSDK_DLL, StoryClipAlignmentType);
FB_DEFINE_ENUM(FBSDK_DLL, StoryClipTimeWarpInterpolatorType);


////////////////////////////////////////////////////////////////////////////////////
// FBClipEvent
////////////////////////////////////////////////////////////////////////////////////

__FB_FORWARD( FBEventClipChange );

class FBSDK_DLL FBEventClipChange: public FBEvent 
{
    public:
        /**	Constructor.
        *	\param pEvent Base event (internal) to obtain information from.
        */
        FBEventClipChange( HKEventBase pEvent );		

        FBPropertyStoryClipChangeType	Type;			 //!< <b>Read Only Property:</b> Type of event.
};

FB_FORWARD( FBPropertyListStoryFolder );
//! <b>List:</b> StoryFolder
class FBSDK_DLL FBPropertyListStoryFolder : public FBPropertyListComponentBase
{
public:
	/**	Add a folder to the property list.
	*	\param	pItem	Folder to add to list.
	*	\return	Number of items in list after operation.
	*	\remark	A folder can't be in two or more separate folders at once nor multiple times in the same one.
	*/
	virtual int Add(FBStoryFolder* pItem);

	/**	Remove folder \e pItem from property list.
	*	\param	pItem	Folder to remove from list.
	*	\return Number of items in list after operation.
	*	\remark	A folder can't be in two or more separate folders at once nor multiple times in the same one.
	*/
    virtual int Remove(FBStoryFolder* pItem);

	/** Remove the folder at \e pIndex.
	*	\param pIndex	Index of folder to remove.
	*/
    virtual void RemoveAt(int pIndex);

	/**	Get the folder at \e pIndex.
	*	\param	pIndex	Index of folder to get.
	*	\return Folder at \e pIndex.
	*/
	virtual FBStoryFolder* operator[](int pIndex);

	/** Get the number of folder.
	*	\return Number of folders.
	*/
	virtual int GetCount();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
	inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
private:
	inline virtual int Add	( FBComponent* pItem ) { return Add((FBStoryFolder*)pItem); }
#endif
};

FB_FORWARD( FBPropertyListStoryTrack );
//! <b>List:</b> StoryTrack
class FBSDK_DLL FBPropertyListStoryTrack : public FBPropertyListComponentBase
{
public:
	/**	Add a track to the property list.
	*	\param	pItem	Track to add to list.
	*	\return	Number of items in list after operation.
	*	\remark	A track can't be in two or more separate folders at once nor multiple times in the same one.
	*/
	virtual int Add(FBStoryTrack* pItem);

	/**	Remove track \e pItem from property list.
	*	\param	pItem	Track to remove from list.
	*	\return Number of items in list after operation.
	*	\remark	A track can't be in two or more separate folders at once nor multiple times in the same one.
	*/
    virtual int Remove(FBStoryTrack* pItem);

	/** Remove the track at \e pIndex.
	*	\param pIndex	Index of track to remove.
	*/
    virtual void RemoveAt(int pIndex);

	/**	Get the track at \e pIndex.
	*	\param	pIndex	Index of track to get.
	*	\return Track at \e pIndex.
	*/
	virtual FBStoryTrack* operator[](int pIndex);

	/** Get the number of track.
	*	\return Number of tracks.
	*/
	virtual int GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
private:
	inline virtual int Add	( FBComponent* pItem ) { return Add((FBStoryTrack*)pItem); }
#endif
};

FB_FORWARD( FBPropertyListStorySubTrack );
//! <b>List:</b> StorySubTrack
class FBSDK_DLL FBPropertyListStorySubTrack : public FBPropertyListComponentBase
{
public:
	/**	Add a sub-track to the property list.
	*	\param	pItem	Sub-Track to add to list.
	*	\return	Number of items in list after operation.
	*	\remark	A sub-track can't be in two or more separate track at once nor multiple times in the same one.
	*/
	virtual int Add(FBStoryTrack* pItem);

	/**	Remove sub-track \e pItem from property list.
	*	\param	pItem	Sub-Track to remove from list.
	*	\return Number of items in list after operation.
	*	\remark	A sub-track can't be in two or more separate track at once nor multiple times in the same one.
	*/
    virtual int Remove(FBStoryTrack* pItem);

	/** Remove the sub-track at \e pIndex.
	*	\param pIndex	Index of sub-track to remove.
	*/
    virtual void RemoveAt(int pIndex);

	/**	Get the sub-track at \e pIndex.
	*	\param	pIndex	Index of sub-track to get.
	*	\return Sub-Track at \e pIndex.
	*/
	virtual FBStoryTrack* operator[](int pIndex);

	/** Get the number of sub-track.
	*	\return Number of sub-tracks.
	*/
	virtual int GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
private:
	inline virtual int Add	( FBComponent* pItem ) { return Add((FBStoryTrack*)pItem); }
#endif
};

FB_FORWARD( FBPropertyListStoryClip );
//! <b>List:</b> StoryClip
class FBSDK_DLL FBPropertyListStoryClip : public FBPropertyListComponentBase
{
public:
	/**	Add a clip to the property list.
	*	\param	pItem	Clip to add to list.
	*	\return	Number of items in list after operation.
	*/
	virtual int Add(FBStoryClip* pItem);

	/**	Remove clip \e pItem from property list.
	*	\param	pItem	Clip to remove from list.
	*	\return Number of items in list after operation.
	*/
    virtual int Remove(FBStoryClip* pItem);

	/** Remove the clip at \e pIndex.
	*	\param pIndex	Index of clip to remove.
	*/
    virtual void RemoveAt(int pIndex);

	/**	Get the clip at \e pIndex.
	*	\param	pIndex	Index of clip to get.
	*	\return Clip at \e pIndex.
	*/
	virtual FBStoryClip* operator[](int pIndex);

	/** Get the number of clip.
	*	\return Number of clips.
	*/
	virtual int GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
private:
	inline virtual int Add	( FBComponent* pItem ) { return Add((FBStoryClip*)pItem); }
#endif
};

FB_FORWARD( FBPropertyListStoryDetails );
//! <b>List:</b> Story track Details
class FBSDK_DLL FBPropertyListStoryDetails : public FBPropertyListComponentBase
{
public:
	/**	Add a object to the property list.
	*	\param	pItem	Object to add to list.
	*	\return	Number of items in list after operation.
	*/
	virtual int Add(FBComponent* pItem);

	/**	Remove object \e pItem from property list.
	*	\param	pItem	Object to remove from list.
	*	\return Number of items in list after operation.
	*/
    virtual int Remove(FBComponent* pItem);

	/** Remove the object at \e pIndex.
	*	\param pIndex	Index of object to remove.
	*/
    virtual void RemoveAt(int pIndex);

	/**	Get the object at \e pIndex.
	*	\param	pIndex	Index of object to get.
	*	\return Object at \e pIndex.
	*/
	virtual FBComponent* operator[](int pIndex);

	/** Get the number of object.
	*	\return Number of objects.
	*/
	virtual int GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
#endif
};

FB_FORWARD( FBPropertyListPivot );
//! <b>List:</b> Story Clip pivot models
class FBSDK_DLL FBPropertyListPivot : public FBPropertyListComponentBase
{
public:
	/**	Add a object to the property list.
	*	\param	pItem	Object to add to list.
	*	\return	Number of items in list after operation.
	*/
	virtual int Add(FBModel* pItem);

	/**	Remove object \e pItem from property list.
	*	\param	pItem	Object to remove from list.
	*	\return Number of items in list after operation.
	*/
    virtual int Remove(FBModel* pItem);

	/** Remove the object at \e pIndex.
	*	\param pIndex	Index of object to remove.
	*/
    virtual void RemoveAt(int pIndex);

	/**	Get the object at \e pIndex.
	*	\param	pIndex	Index of object to get.
	*	\return Object at \e pIndex.
	*/
	virtual FBModel* operator[](int pIndex);

	/** Get the number of object.
	*	\return Number of objects.
	*/
	virtual int GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
private:
	inline virtual int Add	( FBComponent* pItem ) { return Add((FBModel*)pItem); }
#endif
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBStory
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Story Management class.
*	This class serve as a management control for the Story global settings and members.
*/
class FBSDK_DLL FBStory : public FBComponent 
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBStory, FBComponent);

public:
    /**	Constructor.
	*/
	FBStory();
	FBPropertyBool			Mute;						//!< <b>Read Write Property:</b> If true, the Story mode will be globally disabled.
	FBPropertyBool			LockedShot;					//!< <b>Read Write Property:</b> If true, shots will be locked (no time discontinuity).
	FBPropertyBool			MaintainShotAndClipShotLengthsSynced; //!< <b>Read Write Property:</b> When working in time discontinuity, if true, shots and their corresponding shot clips will be kept in sync in regards of their lengths.
	FBPropertyBool			SummaryClip;				//!< <b>Read Write Property:</b> If true, summary clips for story folders will be created to help manipulating folder content.
	FBPropertyBool			RecordToDisk;				//!< <b>Read Write Property:</b> If true, record to story will record directly to disk.
	FBPropertyBool			NoneBlockingPostprocess;	//!< <b>Read Write Property:</b> If true, record to disk will post process recorded data in low priority thread without affecting application performance. Clip in story will remain unloaded.
	FBPropertyBool			ClipsTextsVisible;			//!< <b>Read Write Property:</b> If true, clips' texts are visible.
	FBPropertyStoryFolder	RootFolder;					//!< <b>Read Only Property:</b> Story's root folder
	FBPropertyStoryFolder	RootEditFolder;				//!< <b>Read Only Property:</b> Story's root edit folder

    /** Remove all empty tracks and folders present in the Story Tool.
    *	\return The number of empty story tracks and/or folders removed.
    */
	int CleanEmptyTracksAndFolders();

    /**	Get the global story object
    *	\return	the global object.
    */
    static FBStory& TheOne();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBStoryFolder
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Story Folder class.
*	With folders, you can group tracks together and create different timelines.
*/
class FBSDK_DLL FBStoryFolder : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBStoryFolder, FBComponent);
public:

	/**	Constructor.
	*	\param	pParentFolder	If NULL, parent will be the global root folder, according to its type.
	*	\param	pObject			For internal use only.
	*	\remark	You can't create a folder with the RootEditFolder as parent.
	*/
	FBStoryFolder(FBStoryFolder* pParentFolder=NULL, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	/** Allow to load/unload all story clips under this folder.
	*	\remark	Currently only animation clips are supported.
	*/
	void Load(bool pLoad);

	FBPropertyString			Label;				//!< <b>Read Write Property:</b> Label to display for this story folder.
    FBPropertyBool				Collapsed;			//!< <b>Read Write Property:</b> Toggle to collapse or expand the story folder.
	FBPropertyBool				Solo;				//!< <b>Read Write Property:</b> If true, this story folder will be the only one to play. 
	FBPropertyBool				Mute;				//!< <b>Read Write Property:</b> If true, this story folder will be muted.
	FBPropertyString			RecordClipPath;		//!< <b>Read Write Property:</b> Path for story recording. Can be relative or full path.
	FBPropertyStoryFolder		Parent;		//!< <b>Read Only Property:</b> Object pointing to the folder's parent.
	FBPropertyListStoryFolder	Childs;		//!< <b>List:</b> Children folders of this folder.
	FBPropertyListStoryTrack	Tracks;		//!< <b>List:</b> Tracks of this folder.

	/** Used to align selected clips .
	*	\param	pType				Type of alignment that will be done.
	*	\param	pReferenceClip		Needed when kFBStoryClipAlignmentEndPreviousAllAligned, kFBStoryClipAlignmentBeginningNextAllAligned or kFBStoryClipAlignmentCurrentTimelineWithOffset are used.
	*/
	void AlignSelectedClips(FBStoryClipAlignmentType pType, FBComponent* pReferenceClip);

	/** Used to align clips inside a group.
	*	\param	pType				Type of alignment that will be done.
	*/
	void AlignSelectedClipsGroup(FBStoryGroupClipAlignmentType pType);

	/** Used to expand selected clips .
	*	\param	pPreserveOverlap	If true, portion of clips that overlap other clips won't be modified.
	*/
	void ExpandSelectedClips(bool pPreserveOverlap);

	/** Convert all clips to read-only clips. Identical clips are replaced by the same read-only clip.
	*	\param	pSelected			Only selected clip will be converted.
	*	\param	pFilePath			Folder path where the read-only clips will be saved.
	*	\remark	Currently only animation clips are supported in the Root Folder
	*/
	void ConvertClipsToReadOnly(bool pSelected, char* pFilePath);

	/** ExpandSelectedClipsGroup
	*	Used to expand group clip dependent clips.
	*	\param	pPreserveOverlap	If true, portion of clips that overlap other clips won't be modified.
	*/
	void ExpandSelectedClipsGroup(bool pPreserveOverlap);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBStoryTrack
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Story Track class.
*	Tracks are containers for clips (medias), have a specific type which offer different functions.
*	Note: To change the travelling node of a track, search for the "TravellingNode" property on the track and then connect/disconnect the appropriate object.
*	Python example:
*	lPropTravellingNode = lAnimTrack.PropertyList.Find("TravellingNode")
*	lCube.ConnectDst(lPropTravellingNode)
*/
class FBSDK_DLL FBStoryTrack : public FBConstraint
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBStoryTrack, FBConstraint);
public:

	/**	Constructor.
	*	\param	pTrackType	Type of the track to be created.
	*	\param	pFolder		If NULL, parent will be the global root folder.
	*	\param	pObject		For internal use only.
	*/
	FBStoryTrack(FBStoryTrackType pTrackType, FBStoryFolder* pFolder=NULL, HIObject pObject=NULL);

	/**	Constructor.
	*	\param	pSource		Source of the track to be created based on media component type.
	*	\param	pFolder		If NULL, parent will be the global root folder.
	*	\param	pObject		For internal use only.
	*/
	FBStoryTrack(FBComponent* pSource, FBStoryFolder* pFolder=NULL, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	/**	ChangeDetailsBegin.
	*	You must call this function before adding/removing any object to the Details list or it won't work.
	*/
	void ChangeDetailsBegin();

	/**	ChangeDetailsEnd.
	*	You must call this function after adding/removing any object to the Details list or it won't work.
	*/
	void ChangeDetailsEnd();

	//--- Animation track functions -----------------------------------------------------------------------------------------------------
	/**	CopyTakeIntoTrack
	*	Copy animation from the specified take for affected objects of the track.
	*	\param	pTimeSpan 		Time span for the clip to create.
	*	\param	pTake	  		Take to get the animation from.
	*	\param	pOutputOffset  	Time offset for the clip if necessary.
	*	\param	pMakeUndoable  	If the operation should be undoable.
	*	\return Created story clip if the operation succeeded otherwize NULL.
	*/
	FBStoryClip* CopyTakeIntoTrack(FBTimeSpan& pTimeSpan, FBTake* pTake, FBTime pOutputOffset = 0, bool pMakeUndoable = false);

	//--- Character track functions -----------------------------------------------------------------------------------------------------
	/**	EnableBodyPart.
	*	\param	pPart	Which part to enable/disable.
	*	\param	pEnable	If True, this will enable the body part solving while false will disable it.
	*	Enable a specific body part for character solving.
	*/
	void EnableBodyPart(FBStoryTrackBodyPart pPart, bool pEnable);

	/**	IsBodyPartEnabled.
	*	Is a specific body part is enabled.
	*/
	bool IsBodyPartEnabled(FBStoryTrackBodyPart pPart);

	/** AddClip
	*	Add the clip to the track.
	*/
	void AddClip(FBComponent* pClip, FBTime pTime);

    /** Create a sub track, Only Character and Animation tracks can have sub-tracks.
    *	\param	pTrackType	Type of the sub track to be created.
    *	\param	pRefMode	Composition mode of the sub track, kFBStoryTrackOverride or kFBStoryTrackAdditive.
	*	\return Created sub story track if the operation succeeded otherwise NULL.
	*/
	FBStoryTrack* CreateSubTrack(FBStoryTrackType pTrackType, FBStoryTrackRefMode pRefMode);

	/** Allow to load/unload all story clips under this track.
	*	\remark	Currently only animation clips are supported.
	*/
	void Load(bool pLoad);

	//--- All track properties ----------------------------------------------------------------------------------------------------------
	FBPropertyStoryTrackType	Type;			//!< <b>Read Only Property:</b> Type of the track
	FBPropertyString			Label;			//!< <b>Read Write Property:</b> Label to display for this story track.
	FBPropertyBool				Mute;			//!< <b>Read Write Property:</b> If true, this track wont' play.
	FBPropertyBool				Solo;			//!< <b>Read Write Property:</b> If true, this track will be the only one to play.
	FBPropertyString			RecordClipPath;	//!< <b>Read Write Property:</b> Path for story recording. Can be relative or full path.
	FBPropertyString			ClipNameConvention;//!< <b>Read Write Property:</b> Naming convention for each new recording clip that is created. Can use special tags: &lt;Name&gt; &lt;StartTCValue&gt; &lt;StartFrameValue&gt; &lt;StartDate&gt; &lt;StartTime&gt; &lt;TakeName&gt;
	FBPropertyBool				RecordTrack;	//!< <b>Read Write Property:</b> Path for story recording. Can be relative or full path.
	FBPropertyStoryFolder		ParentFolder;	//!< <b>Read Only Property:</b> Parent folder.
	FBPropertyStoryTrack		ParentTrack;	//!< <b>Read Only Property:</b> Parent track, if the track is of Character or Animation type.
	FBPropertyListStorySubTrack	SubTracks;		//!< <b>List:</b> Only Character and Animation tracks can have sub-tracks.
	FBPropertyListStoryClip		Clips;			//!< <b>List:</b> Clips contained in this track.
	FBPropertyListStoryDetails	Details;		//!< <b>List:</b> All objects associated to this track for processing.

	//--- Animation and Constraint track properties -------------------------------------------------------------------------------------
	FBPropertyAnimatableDouble	Weight;			//!< <b>Read Write Property:</b> Control the blend amount.

	//--- Animation track properties ----------------------------------------------------------------------------------------------------
	FBPropertyBool				Ghost;			//!< <b>Read Write Property:</b> Show ghosts
	FBPropertyBool				GhostModel;		//!< <b>Read Write Property:</b> Show ghost of models
	FBPropertyBool				GhostTravelling;//!< <b>Read Write Property:</b> Show ghost of clip vector or traveling node
	FBPropertyBool				GhostPivot;		//!< <b>Read Write Property:</b> Show ghost of match object
    FBPropertyStoryTrackGhostShowMode	GhostShowTrackMode;	//!< <b>Read Write Property:</b> Show the ghosts for all the clips or only the adjacent clips. See FBStoryTrackGhostShowMode
	FBPropertyBool				AcceptKey;		//!< <b>Read Write Property:</b> Allow track to accept keys
	FBPropertyStoryTrackRefMode	ReferenceMode;	//!< <b>Read Write Property:</b> Track composition mode, kFBStoryTrackOverride or kFBStoryTrackAdditive
	FBPropertyBool				OffsetEnable;	//!< <b>Read Write Property:</b> When enabled, allow clip to be offset
	FBPropertyBool				PassThrough;	//!< <b>Read Write Property:</b> Enable passthrough of animation if there is no clip on track animation is taken from other tracks of take

	//--- Character track properties ----------------------------------------------------------------------------------------------------
    FBPropertyCharacter			Character;	    //!< <b>Read Write Property:</b> Character to use.
    FBPropertyInt				CharacterIndex;	//!< <b>Read Write Property:</b> Character's index to use.

	//--- Shot track properties ---------------------------------------------------------------------------------------------------------
	FBPropertyBool				ShowBackplate;	//!< <b>Read Write Property:</b> If true, the backplate will be shown.
	FBPropertyBool				ShowFrontplate;	//!< <b>Read Write Property:</b> If true, the frontplate will be shown.

	//--- Audio track properties --------------------------------------------------------------------------------------------------------
	FBPropertyInt				AudioOutIndex;	//!< <b>Read Write Property:</b> Audio Output's index to use.

	//--- Video track properties --------------------------------------------------------------------------------------------------------
	FBPropertyVideo				TrackVideo;		//!< <b>Read Only Property:</b> This FBVideo can be used as a texture.
private:
	void FBStoryTrackInitProperties();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBStoryClip
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Story Clip class.
*	Clips represents media, at a specific time, for a specific duration, in a track.
*
*	Clip offset is depending on Traveling node and Traveling node function. 
*	First we compute clip transformation matrix, where scaling is always 1, 1, 1. 
*	Translation is in position of Traveling node at clip first frame. 
*	Rotation is based on vector from first to last frame position of Traveling node. 
*	On top of that we apply offset and expose that as Clip Offset T & R.
*	When you change clip offset T or R we extract clip offset based on current clip transformation matrix. 
*	Clip transformation matrix can change when Traveling node change or Traveling node function change.
*
*/
class FBSDK_DLL FBStoryClip : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBStoryClip, FBComponent);
public:

	/**	Constructor.
	*	\param	pClipObject	Object (media data) for the clip.
	*	\param	pTrack		The track in which we create the clip.
	*	\param	pTime		Time where the clip should begin.
	*	\param	pObject		For internal use only.
	*/
	FBStoryClip(FBComponent* pClipObject, FBStoryTrack* pTrack, FBTime pTime, HIObject pObject=NULL);

	/**	Constructor.
	*	\param	pFilePath	Media file path to create clip with.
	*	\param	pTrack		The track in which we create the clip.
	*	\param	pTime		Time where the clip should begin.
	*	\param	pObject		For internal use only.
	*/
	FBStoryClip(const char* pFilePath, FBStoryTrack* pTrack, FBTime pTime, HIObject pObject=NULL);

	/**	Constructor.
	*	\param	pFilePath	Media file path to create clip with.
	*	\param	pTrack		The track in which we create the clip.
	*	\param	pTime		Time where the clip should begin.
	*	\param	pTimeOffset	Time offset where the clip should begin.
	*	\param	pObject		For internal use only.
	*/
	FBStoryClip(const char* pFilePath, FBStoryTrack* pTrack, FBTime pTime, FBTime pTimeOffset, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	/** Clone the clip.
	*/
	FBStoryClip* Clone();

	/**	Move.
	*	Move the clip of a delta offset.
	*	\param	pDelta	Delta time to apply to the clip.
	*	\param	pForce	Force clip to find the nearest position if the move fail.
	*	\return Return the delta between the new and previous clip's position.
	*/
	FBTime Move(FBTime pDelta, bool pForce=true);

	/**	MoveTo.
	*	Move the clip to the specified time.
	*	\param	pTime	Time where to put the clip.
	*	\param	pForce	Force clip to find the nearest position if the move fail.
	*	\return Returns the new clip's time position.
	*/
	FBTime MoveTo(FBTime pTime, bool pForce=true);

	/**	Razor.
	*	Cut (razor) the clip at the specified time.
	*	\param	pTime	Time where to cut. This time is local to the track, not to the clip.
	*	\return Returns the new clip generated by the razor action (right part).
	*/
	FBStoryClip* Razor(FBTime pTime);

	//--- Animation clip functions ------------------------------------------------------------------------------------------------------
	/**	Match.
	*	Match the animation clip with the specified pivot property.
	*/
	void Match();

	/**	Match.
	*	Match the animation clip to its previous/next animation clip, one to each other.
	*	\param	pObjectName			The object name that specifies which part of the track content to use to match clips. If the object name is not valid, or empty, the match object will be disabled so that the blend does not take it into account when matching clips.
	*	\param	pTimeType			The time type specifying which point of a cross-blend the selected clip is matched.
	*	\param	pTranslationType	The translation type specifying if/how a clip's match object is translated to match another clip's animation.
	*	\param	pRotationType		The rotation type specifying if/how a clip's match object is rotated to match another clip's animation.
	*/
	void Match
	(
		FBString							pObjectName,
		FBStoryClipMatchingTimeType			pTimeType,
		FBStoryClipMatchingTranslationType	pTranslationType,
		FBStoryClipMatchingRotationType		pRotationType
	);

	/**	ExportToFile.
	*	Export animation clip to disk file.
	*	\param	pOutputFile	Output file path name.
	*	\return	Returns true if successful.
	*/
	bool ExportToFile(FBString pOutputFile);
	
	/**	GetReadOnly
	*	Retrieves the clip read-only status.
	*	\return	Returns the clip read-only status.
	*/
    bool GetReadOnly();

    /**	SetReadOnly
	*	Assigns the clip read-only status.
    *	\param	pMakeClipReadOnly New read-only status
    *	\param	pOutputFile	Output file path name, when setting the clip's read-only status to true.
	*	\return	Returns true if successful.
	*/
    bool SetReadOnly(bool pMakeClipReadOnly, FBString pOutputFile = FBString());

	/**	MakeWritable.
	*	Imports FCurves from story clip scene making them accessible for the user.
	*	\return	Returns true if successful.
	*/
	bool MakeWritable();

	/**	GetAffectedObjects.
	*	Get the list of objects affected by this story clip.
	*	\par Python
	*	The function takes no parameter and returns a Python list. ex : lArray = lClip.GetAffectedObjects()  
	*
	*	\param	pAffectedObjects	Array of affected objects, will be filled by the function.
	*/
	void GetAffectedObjects( FBArrayTemplate<FBComponent*>* pAffectedObjects );

	/**	GetAffectedAnimationNodes.
	*	Get the list of animation nodes affected by this story clip, for a specific object.
	*	\par Python
	*	The function takes only one parameter (pClipObject) and returns a Python list. ex : lArray = lClip.GetAffectedAnimationNodes(lObject)
	*
	*	\param	pAffectedAnimationNodes	Array of affected animation nodes, will be filled by the function.
	*	\param	pClipObject				The object for which we search for affected animation nodes.
	*/
	void GetAffectedAnimationNodes( FBArrayTemplate<FBAnimationNode*>* pAffectedAnimationNodes, FBComponent* pClipObject );

    /**	Assign source to destination if the pSrcName is found in source list and pObject is in the Details list.
	*	\param	pSrcName	The name of the source.
	*	\param	pObject	    The destination object.
	*	\return	Returns true if assignment has been executed when the pSrcName is found in source list and pObject is in the Details list.
    *   \remarks Assignment success depends on if they have the same name property and with animation on the source property.
	*/
	bool DestinationSetObject( const char* pSrcName, FBComponent* pObject );

    /**	SetTime
    *   Sets any in/out values for the source/destination times.
    *   In and out values are optional and the current values for the story 
    *   clip will be used if not supplied.
    *   The story "Speed" property will be adjusted in order for the supplied
    *   values to be respected by the story clip.
    *
    *	\param	pSourceIn       New value for the source IN time. Passing a value 
    *                           will modify the "MarkIn" and/or the "Speed" 
    *                           properties.
    *	\param	pSourceOut      New value for the source OUT time. Passing a value 
    *                           will modify the "MarkOut" and/or the "Speed" 
    *                           properties.
    *	\param	pDestinationIn  New value for the destination IN time. Passing a value 
    *                           will modify the "Stop" and/or the "Speed" 
    *                           properties.
    *	\param	pDestinationOut New value for the destination OUT time. Passing a value 
    *                           will modify the "Start" and/or the "Speed" 
    *                           properties.
    *	\param	pUseAlternateSrcInProp  Will work on the "ExtractStart" property instead of the "MarkIn" property when passing pSourceIn. 
	*/
    void SetTime( FBTime *pSourceIn = NULL, FBTime *pSourceOut = NULL, FBTime *pDestinationIn = NULL, FBTime *pDestinationOut = NULL, bool pUseAlternateSrcInProp = false );

	/**	CanAssignSourcesToDestinations.
	*	Determines if the animation clip can assign its sources to some destinations or not.
	*	\return	Returns true if the animation clip can assign its sources to some destinations, false otherwise.
	*/
	bool CanAssignSourcesToDestinations();

	/**	GetAssignSourcesToDestinationsInfo.
	*	Returns the information about the current state of Sources to Destinations assignment.
	*	The pSrcList, pDefaultDstList & pEffectiveDstList parameters will all be of same size, each index being related to the same index in the other lists.
	*	The pAvailableDstList parameter can contains more item than the other lists.
	*	\param	pSrcList	String list containing all the sources, will be filled by the method.
	*	\param	pAvailableDstList	String list containing all the available destinations, will be filled by the method.
	*	\param	pDefaultDstList	String list containing the default destinations (contains each string item that will be put back when pressing the 'Reset' button in the UI), will be filled by the method.
	*	\param	pEffectiveDstList	String list containing the effective destination (destinations currently active), will be filled by the method.
	*/
	void GetAssignSourcesToDestinationsInfo( FBStringList& pSrcList, FBStringList& pAvailableDstList, FBStringList& pDefaultDstList, FBStringList& pEffectiveDstList );

	/**	SetAssignSourcesToDestinationsInfo.
	*	Sets the new effective destinations information for the Sources to Destinations assignment.
	*	The input string list size must contain the same number of items than the effective destination list returned by the GetAssignSourcesToDestinationsInfo method.
	*	Each item in the input string list must match an item in the available destination list returned by the GetAssignSourcesToDestinationsInfo method.
	*	The item at a given index of the input string list will be related to the same index of the sources list returned by the GetAssignSourcesToDestinationsInfo method.
	*	\param	pEffectiveDstList	String list containing the new effective destination.
	*	\return	Returns true if the assign succeeded, false otherwise.
	*/
	bool SetAssignSourcesToDestinationsInfo( FBStringList& pEffectiveDstList );

	/** Get KFbxScene.
	*	Will only return valid pointer to KFbxScene for readonly animation clip.
	*/
	FBXSDK_NAMESPACE::FbxScene* GetFbxScene();

    /** Update clip animation from current take animation for clip track's scope, works only for clip created by Insert Current Take and connected to current take.
    *   \return	Returns true if succeed.
	*/
	bool UpdateFromCurrentTake();

	//--- All clip properties -----------------------------------------------------------------------------------------------------------
	FBPropertyColor		Color;			//!< <b>Read Write Property:</b> Color of the clip.
	FBPropertyTime		Start;			//!< <b>Read Write Property:</b> Start time of the clip local to its track.
	FBPropertyTime		Stop;			//!< <b>Read Write Property:</b> Stop time of the clip local to its track.
	FBPropertyTime		MarkIn;			//!< <b>Read Write Property:</b> Start time inside the clip.
	FBPropertyTime		MarkOut;		//!< <b>Read Write Property:</b> Stop time inside the clip.
	FBPropertyTimeSpan	PreBlend;		//!< <b>Read Write Property:</b> Start/Stop time of the pre-blend phase.
	FBPropertyTimeSpan	PostBlend;		//!< <b>Read Write Property:</b> Start/Stop time of the post-blend phase.
	FBPropertyTime		Offset;			//!< <b>Read Write Property:</b> First loop time offset.
	FBPropertyDouble	Speed;			//!< <b>Read Write Property:</b> Speed of the clip.
	FBPropertyBool		StartStopLocked;//!< <b>Read Write Property:</b> Clip's 'In/Out Locked' property value. True if the clip's In/Out properties (start/stop times of the clip local to its track) are locked, false otherwise.

	//--- Shot clip properties ----------------------------------------------------------------------------------------------------------
	FBPropertyCamera	ShotCamera;			//!< <b>Read Write Property:</b> The camera used for that specific shot.
	FBPropertyVideo		ShotBackplate;		//!< <b>Read Write Property:</b> The backplate used for that specific shot.
	FBPropertyVideo		ShotFrontplate;		//!< <b>Read Write Property:</b> The frontplate used for that specific shot.
	FBPropertyBool		ShowBackplate;		//!< <b>Read Write Property:</b> Enable/Disable the shot backplate.
	FBPropertyBool		ShowFrontplate;		//!< <b>Read Write Property:</b> Enable/Disable the shot frontplate.
	FBPropertyTime		ShotActionStart;	//!< <b>Read Write Property:</b> If not in locked shot mode (time discontinuity enabled), this time can be different from the Clip->Start property.
	FBPropertyTime		ShotActionStop;		//!< <b>Read Write Property:</b> If not in locked shot mode (time discontinuity enabled), this time can be different from the Clip->Start property.
	FBPropertyBool		ShotStartStopLocked;//!< <b>Read Write Property:</b> Shot clip's 'In/Out Locked' property value. True if the shot clip's In/Out properties (start/stop times of the clip local to its track) are locked, false otherwise.

	//--- Audio clip properties ---------------------------------------------------------------------------------------------------------
	FBPropertyAudioClip	AudioClip;		//!< <b>Read Only Property:</b> The audio clip used by this StoryClip.
    FBPropertyString    ClipAudioPath;  //!< <b>Read Write Property:</b> Audio clip's file path
	FBPropertyDouble    ClipPitch;      //!< <b>Read Write Property:</b> The clip pitch value.
	FBPropertyBool      LockPitchToSpeed;   //!< <b>Read Write Property:</b> Time-stretching enabled or not. 

	//--- Video clip properties ---------------------------------------------------------------------------------------------------------
    FBPropertyString        ClipVideoPath;        //!< <b>Read Write Property:</b> Video clip's file path
    FBPropertyBool          ImageSequence;        //!< <b>Read Write Property:</b> Whether is a image sequence. 
	FBPropertyBool          UseSystemFrameRate;   //!< <b>Read Write Property:</b> Whether always use system frame rate. 
	FBPropertyDouble        FrameRate;            //!< <b>Read Write Property:</b> Frame rate value. Only effective when UseSystemFrameRate is false.
	FBPropertyBool          ShowEmbeddedTimecode; //!< <b>Read Write Property:</b> Whether to show embedded timecode of the clip, if available.

	//--- Animation clip properties -----------------------------------------------------------------------------------------------------
    FBPropertyString                    ClipAnimationPath;  //!< <b>Read Write Property:</b> Animation clip's file path
	FBPropertyDouble					Scale;				//!< <b>Read Write Property:</b> Animation clip's scaling (some don't support this property)
	FBPropertyVector3d					Translation;		//!< <b>Read Write Property:</b> Animation clip's translation offset. Refer to class notes to learn more about how this is applied.
	FBPropertyVector3d					Rotation;			//!< <b>Read Write Property:</b> Animation clip's rotation offset. Refer to class notes to learn more about how this is applied.
	FBPropertyVector3d					LoopTranslation;	//!< <b>Read Write Property:</b> Animation clip's loop translation.
	FBPropertyBool						AutoLoop;			//!< <b>Read Write Property:</b> If true, clip will automatically loop
	FBPropertyBool						Loop;				//!< <b>Read Write Property:</b> If true, loop clip's animation
	FBPropertyBool						Ghost;				//!< <b>Read Write Property:</b> Show ghosts
	FBPropertyBool						GhostModel;			//!< <b>Read Write Property:</b> Show ghost of models
	FBPropertyBool						GhostTravelling;	//!< <b>Read Write Property:</b> Show ghost of clip vector or traveling node
	FBPropertyBool						GhostPivot;			//!< <b>Read Write Property:</b> Show ghost of match object
	FBPropertyStoryClipShowGhostMode	ShowGhostClipMode;	//!< <b>Read Write Property:</b> Show the ghost depending on the time. See FBStoryClipShowGhostMode
    FBPropertyTime						GhostCustomTime;	//!< <b>Read Write Property:</b> Custom time to display ghost, only applicable if ShowGhostClipMode is kFBStoryClipTimeCustom.
	FBPropertyAnimationNode				PreBlendData;		//!< <b>Read Only Property:</b>	To get the animation of the Pre blend curve
	FBPropertyAnimationNode				PostBlendData;		//!< <b>Read Only Property:</b> To get the animation of the Post blend curve
	FBPropertyListPivot					Pivots;				//!< <b>List:</b> Pivots models (Generally, only one model is necessary)
	FBPropertyBool						Loaded;				//!< <b>Read Write Property:</b> If true, clip file is loaded into memory and can be evaluated (will affect track content).
	FBPropertyVector3d					GhostManipulatorOffset;	//!< <b>Read Write Property:</b> Animation clip's ghost manipulator offset.
    FBPropertyListObject				TravellingNode;		//!< <b>List:</b> Travelling node(s). If set, this property will overwrite the Track's Travelling node(s).
	FBPropertyStoryClipNodeFunction		TravellingNodeFunction;	//!< <b>Read Write Property:</b> Travelling node function. If set, this property will overwrite the Track's Travelling node function. See FBStoryClipNodeFunction.
	FBPropertyStoryClipGhostTimeMode	GhostManipulatorMode;	//!< <b>Read Write Property:</b> Time mode to display ghost manipulator. See FBStoryClipGhostTimeMode.
	FBPropertyTime						GhostManipulatorCustomTime;	//!< <b>Read Write Property:</b> Custom time to display ghost manipulator, only applicable if GhostManipulatorMode is kFBStoryClipGhostCustom.
    FBPropertyBool						ConnectedToTake;	//!< <b>Read Write Property:</b> When connected to current take, user can do updating from current take, but user can't edit clip animation by adding keys, only works for clips created by Insert Current Take.

	//--- Character clip properties -----------------------------------------------------------------------------------------------------
	FBPropertyStoryClipSolveMode		SolvingMode;		//!< <b>Read Write Property:</b> Solve Modes for story character clips. See FBStoryClipSolveMode
    FBPropertyBool						MirrorAnimation;    //!< <b>Read Write Property:</b> If true, clip animation will be mirrored
    FBPropertyStoryClipMirrorPlane      MirrorPlane;    	//!< <b>Read Write Property:</b> Several mirror planes to mirror animation. See FBStoryClipMirrorPlane

	FBPropertyEvent						OnChange;			//!< <b>Event:</b> Something in the clip has changed. (FBEventClip)

	//--- Character and shot clip properties -----------------------------------------------------------------------------------------------------
	FBPropertyBool								TimeWarpEnabled;			//!< <b>Read Write Property:</b> Animation and Shot clip's TimeWarp activeness.
	FBPropertyStoryClipTimeWarpInterpolatorType	TimeWarpInterpolatorType;	//!< <b>Read Write Property:</b> Animation and Shot clip's TimeWarp interpolation type. See FBStoryClipTimeWarpInterpolatorType.
	FBPropertyBool								TimeWarpReverse;			//!< <b>Read Write Property:</b> If true, reverse the Animation or Shot clip's TimeWarp FCurve.
	FBPropertyAnimationNode						CustomTimeWarp;				//!< <b>Read Only Property:</b> Animation and Shot clip's custom TimeWarp FCurve.

private:
	void FBStoryClipInitProperties();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBStoryGroupClip
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Story Group Clip class.
*	Group Clip represents a group of clips that can be manipulated together.
*/
class FBSDK_DLL FBStoryGroupClip : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBStoryGroupClip, FBComponent);
public:

	/**	Constructor.
	*	\param	pAffectedClipObject	Clips that will be controlled by the group clip.
	*	\param	pObject				For internal use only.
	*/
	FBStoryGroupClip(FBArrayTemplate<FBStoryClip*>* pAffectedClipObject, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	/**	Move.
	*	Move the clip of a delta offset.
	*	\param	pDelta	Delta time to apply to the clip.
	*	\param	pForce	Force clip to find the nearest position if the move fail.
	*	\return Return the delta between the new and previous clip's position.
	*/
	FBTime Move(FBTime pDelta, bool pForce=true);

	/**	MoveTo.
	*	Move the clip to the specified time.
	*	\param	pTime	Time where to put the clip.
	*	\param	pForce	Force clip to find the nearest position if the move fail.
	*	\return Returns the new clip's time position.
	*/
	FBTime MoveTo(FBTime pTime, bool pForce=true);

	/**	Razor.
	*	Cut (razor) the clip at the specified time.
	*	\param	pTime	Time where to cut. This time is local to the track, not to the clip.
	*/
	void Razor(FBTime pTime);

	FBPropertyTime		Start;			//!< <b>Read Write Property:</b> Start time of the clip.
	FBPropertyTime		Stop;			//!< <b>Read Write Property:</b> Stop time of the clip.
	FBPropertyBool		StartStopLocked;//!< <b>Read Write Property:</b> Clip's 'In/Out Locked' property value. True if the clip's In/Out properties (start/end times of the clip local to its track) are locked, false otherwise.
	FBPropertyListObject DependentClips;//!< <b>Read Write Property:</b> Clips that are included in the group clip.

private:
	void FBStoryClipInitProperties();
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
