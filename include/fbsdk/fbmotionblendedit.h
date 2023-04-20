#ifndef __FBMOTIONBLENDEDIT_H__
#define __FBMOTIONBLENDEDIT_H__
// ===========================================================================
// Copyright 2018 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================

/** \file fbmotionblendedit.h
*    Base class for motion blend edits.
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
// FBMotionBlendEdit
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBMotionBlendEdit );

/** Motion Blend Edit class.
*	This class allows creating, deleting and interacting with Edits contained in the Motion Blend window.

\code
# This example shows how to create a new Edit, rename it and activate its 'Keep Active' option.
from pyfbsdk import *
myEdit = FBMotionBlendEdit( "myEdit" )
myEdit.SetName( "myRenamedEdit" )
myEdit.SetKeepActive( True )
\endcode
*/

//! Motion Blend Edit
class FBSDK_DLL FBMotionBlendEdit : public FBComponent 
{
	__FBClassDeclare( FBMotionBlendEdit, FBComponent );

public:
	/**	Constructor.
	*	\param	pName			The new Edit name. If unset, the name "Edit" will be set.
	*	\param	pSetAsCurrent	True (default) to set the new Edit as the current Edit to be used in the Motion Blend.
	*	\param	pObject			(C++ only) For internal use only (default = nullptr).
	*/
	FBMotionBlendEdit( const char* pName = nullptr, bool pSetAsCurrent = true, HIObject pObject = nullptr );

	/** Virtual FBDelete function. Remove the Edit from the Motion Blend.
	*/
	virtual void FBDelete() override;

public:
	/**	Get the Edit name.
	*	\return	The Edit name.
	*/
	const char* GetName();

	/**	Set the Edit name.
	*	\param	pName	The new name.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool SetName( const char* pName );

	/**	Clear the Edit.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool Clear();

	/**	Set the "Show All Ghosts" state.
	*	\param	pShow	True to display all of the Edit ghosts in the Viewer window, false to hide them all.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool SetShowAllGhosts( bool pShow );

	/**	Get the "Show All Ghosts" state.
	*	\return	True if all Edit ghosts are displayed in the Viewer window, false otherwise.
	*/
	bool GetShowAllGhosts();

	/**	Set the "Keep Edit Active" state.
	*	\param	pKeepActive	True to allow the result of the Edit to be shown while working on other Edits, false otherwise.
	*	\return	True if the operation is successful, false otherwise.
	*/
	bool SetKeepActive( bool pKeepActive );

	/**	Get the "Keep Edit Active" state.
	*	\return	True if the result of the Edit is shown while working on other Edits, false otherwise.
	*/
	bool GetKeepActive();
};

#ifdef FBSDKUseNamespace
}
#endif
#endif // __FBMOTIONBLENDEDIT_H__
