#ifndef __FBMOTIONBLEND_H__
#define __FBMOTIONBLEND_H__
// ===========================================================================
// Copyright 2018 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================

/** \file fbmotionblend.h
*    Base class for the motion blend window.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*    Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBMotionBlend
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBMotionBlend );
__FB_FORWARD( FBMotionBlendEdit );

/** Motion Blend class.
*	This class allows interacting with the Edits and options of the Motion Blend window.

\code
# This example shows how to clear all the Edits, create a new Edit and activate the 'Snap On Frame' option.
from pyfbsdk import *
motionBlend = FBMotionBlend()
motionBlend.RemoveAllEdits()
myEdit = motionBlend.AddEdit( "myEdit" )
motionBlend.SetSnapOnFrame( True )
\endcode
*/

class FBSDK_DLL FBMotionBlend : public FBComponent
{
	__FBClassDeclare( FBMotionBlend, FBComponent );

public:
	/**	Get the global FBMotionBlend object.
	*	\return	The global FBMotionBlend object.
	*/
	static FBMotionBlend& TheOne();

	/**	Get the number of Edits in the Motion Blend.
	*	\return	The number of Edits in the Motion Blend, or -1 in case of an error.
	*/
	int GetEditCount();

	/**	Get the Edit associated to the input index.
	*	\param	pIndex	The index of the Edit to get.
	*	\return	The FBMotionBlendEdit object if successful, nullptr (C++) or None (Python) otherwise.
	*/
	FBMotionBlendEdit* GetEdit( int pIndex );

	/**	Get the current Edit used in the Motion Blend.
	*	\return	The current FBMotionBlendEdit object if successful, nullptr (C++) or None (Python) otherwise.
	*/
	FBMotionBlendEdit* GetCurrentEdit();

	/**	Set the current Edit to be used in the Motion Blend.
	*	\param	pEdit	The FBMotionBlendEdit object to set as the current Edit.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool SetCurrentEdit( FBMotionBlendEdit* pEdit );

	/**	Add a new Edit in the Motion Blend.
	*	\param	pName			The new Edit name. If unset, the name "Edit" will be set.
	*	\param	pSetAsCurrent	True (default) to set the new Edit as the current Edit to be used in the Motion Blend.
	*	\return	The new FBMotionBlendEdit object if successful, nullptr (C++) or None (Python) otherwise.
	*/
	FBMotionBlendEdit* AddEdit( const char* pName = nullptr, bool pSetAsCurrent = true );

	/**	Remove an Edit from the Motion Blend.
	*	\param	pEdit	The FBMotionBlendEdit object to remove.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool RemoveEdit( FBMotionBlendEdit* pEdit );

	/**	Remove all Edits from the Motion Blend. A default empty Edit is then created.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool RemoveAllEdits();

	/**	Set the "Snap On Frame" state.
	*	\param	pSnap	True to force the start and end times of all cuts and poses to snap to the nearest frame, false otherwise.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool SetSnapOnFrame( bool pSnap );

	/**	Get the "Snap On Frame" state.
	*	\return	True if the Motion Blend forces the start and end times of all cuts and poses to snap to the nearest frame, false otherwise.
	*/
	bool GetSnapOnFrame();

	/**	Set the "Force Time" state.
	*	\param	pForceTime	True to snap the Timeline indicator in place so that it cannot be moved by dragging, false otherwise.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool SetForceTime( bool pForceTime );

	/**	Get the "Force Time" state.
	*	\return	True if the Motion Blend snaps the Timeline indicator in place so that it cannot be moved by dragging, false otherwise.
	*/
	bool GetForceTime();

	/**	Set the "Sync Take/Edit Start & End" state.
	*	\param	pSync	True to sync the Take start/end times with the Take start/end times stored in the Motion Blend Edit selected, false otherwise.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool SetSyncTakeEditStartEnd( bool pSync );

	/**	Get the "Sync Take/Edit Start & End" state.
	*	\return	True if the Take start/end times sync with the Take start/end times stored in the Motion Blend Edit selected, false otherwise.
	*/
	bool GetSyncTakeEditStartEnd();

private:
	/**	Constructor.
	*	Protected constructor, use TheOne() access instead. 
	*/
	FBMotionBlend();
};

#ifdef FBSDKUseNamespace
}
#endif
#endif // __FBMOTIONBLEND_H__
