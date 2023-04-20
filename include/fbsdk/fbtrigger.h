#ifndef __FBTRIGGER_H__
#define __FBTRIGGER_H__
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

/**	\file fbtrigger.h
*	Basic classes for trigger tree manipulation.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBTriggerGroup				);
__FB_FORWARD( FBTrigger						);
__FB_FORWARD( FBMotionClip					);
__FB_FORWARD( FBTriggerBranch				);

__FB_FORWARD( FBPropertyListTriggerGroup	);
__FB_FORWARD( FBPropertyListTrigger			);
__FB_FORWARD( FBPropertyListMotionClip		);
__FB_FORWARD( FBPropertyListTriggerBranch	);

FB_DEFINE_COMPONENT( FBSDK_DLL, TriggerGroup	);
FB_DEFINE_COMPONENT( FBSDK_DLL, Trigger		);
FB_DEFINE_COMPONENT( FBSDK_DLL, MotionClip		);
FB_DEFINE_COMPONENT( FBSDK_DLL, TriggerBranch	);

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListTriggerGroup
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: TriggerGroup
class FBSDK_DLL FBPropertyListTriggerGroup : public FBPropertyBaseList< FBTriggerGroup* >
{
public:
	/**	Add a TriggerGroup to the property list.
	*	\param	pItem	TriggerGroup to add to list.
	*	\return	Number of items in list.
	*/
	virtual int	 Add	( FBTriggerGroup* pItem );
    virtual void RemoveAt( int pIndex );
	virtual FBTriggerGroup* operator[](int pIndex);
	virtual int  GetCount();
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListTrigger
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: Trigger
class FBSDK_DLL FBPropertyListTrigger : public FBPropertyBaseList< FBTrigger* >
{
public:
	/**	Add a trigger to the property list.
	*	\param	pItem	Trigger to add to list.
	*	\return	Number of items in list.
	*/
	virtual int	 Add	( FBTrigger* pItem );
    virtual void RemoveAt( int pIndex );
	virtual FBTrigger* operator[](int pIndex);
	virtual int  GetCount();
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListMotionClip
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: MotionClip
class FBSDK_DLL FBPropertyListMotionClip : public FBPropertyBaseList< FBMotionClip* >
{
public:
	/**	Add an MotionClip to the property list.
	*	\param	pItem	MotionClip to add to list.
	*	\return	Number of items in list.
	*/
	virtual int	 Add	( FBMotionClip* pItem );
    virtual void RemoveAt( int pIndex );
	virtual FBMotionClip* operator[](int pIndex);
	virtual int  GetCount();
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListTriggerBranch
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: TriggerBranch
class FBSDK_DLL FBPropertyListTriggerBranch : public FBPropertyBaseList< FBTriggerBranch* >
{
public:
	/**	Add an TriggerBranch to the property list.
	*	\param	pItem	TriggerBranch to add to list.
	*	\return	Number of items in list.
	*/
	virtual int	 Add	( FBTriggerBranch* pItem );
    virtual void RemoveAt( int pIndex );
	virtual FBTriggerBranch* operator[](int pIndex);
	virtual int  GetCount();
};


////////////////////////////////////////////////////////////////////////////////////
// FBTrigger
////////////////////////////////////////////////////////////////////////////////////
//! \enum FBTriggerSource
/**Trigger Sources*/
enum FBTriggerSource	
{ 
	kFBTriggerSourceDefault,	//!< Default. 
	kFBTriggerSourceKeyboard,	//!< Keyboard.
	kFBTriggerSourceJoystick1,	//!< Joystick1.
	kFBTriggerSourceJoystick2	//!< Joystick2.
};
//! \enum FBTriggerMode
/**Trigger Mode*/
enum FBTriggerMode
{
	kFBTriggerModeLocal,				//!< Local.
	kFBTriggerModeGlobal,				//!< Global.
	kFBTriggerModeGlobalMatch,			//!< Global Match.
	kFBTriggerModeGlobalGravityMatch	//!< Global Gravity Match.
};

FB_DEFINE_ENUM( FBSDK_DLL, TriggerSource	);
FB_DEFINE_ENUM( FBSDK_DLL, TriggerMode		);

class FBSDK_DLL FBTriggerGroup : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBTriggerGroup, FBComponent );

public:
	/** Constructor.
	*	\param	pName   Name of the new group.
	*	\param	pObject Internal parent object to own trigger.
	*/
	FBTriggerGroup(char* pName = NULL, HIObject pObject = NULL);

	IObject_Declare(override);		// Interface to IObject.

	void Synchronize();

	FBPropertyString		Name;			//!< <b>Property:</b> Name of trigger group.
	FBPropertyBool			Active;			//!< <b>Property:</b> Is trigger group active?
	FBPropertyTriggerSource	Source;			//!< <b>Property:</b> Source of triggering information.
	FBPropertyTriggerMode	Mode;			//!< <b>Property:</b> Motion clip play mode.
	FBPropertyDouble		Speed;			//!< <b>Property:</b> Motion clip speed.

	FBPropertyListModel			Nodes;			//!< <b>List:</b> Nodes to be animated (note must be in a hierarchy).
	FBPropertyListTrigger		Triggers;		//!< <b>List:</b> Triggers for the group.
	FBPropertyListMotionClip	MotionClips;	//!< <b>List:</b> Motion clips for the group.
};

////////////////////////////////////////////////////////////////////////////////////
// FBTrigger
////////////////////////////////////////////////////////////////////////////////////
//! \enum FBTriggerType
/**Trigger Types*/
enum FBTriggerType
{
	kFBTriggerTypeOff,				//!< Off.
	kFBTriggerTypeActivate,			//!< Activate.
	kFBTriggerTypeDeactivate,		//!< Deactivate.
	kFBTriggerTypeActivateRepeat,	//!< Activate Repeat.
	kFBTriggerTypeDeactivateRepeat	//!< Deacticate Repeat.
};

FB_DEFINE_ENUM( FBSDK_DLL, TriggerType );

class FBSDK_DLL FBTrigger	: public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBTrigger, FBComponent );

public:
	/** Constructor.
	*	\param	pName   Name of the trigger.
	*	\param	pObject Internal parent object to own trigger.
	*/
	FBTrigger(char* pName = NULL, HIObject pObject = NULL);

	IObject_Declare(override);	// Interface to IObject.

	FBPropertyString		Name;		//!< Name of trigger.
	FBPropertyTriggerType	Type;		//!< Trigger type.
};

////////////////////////////////////////////////////////////////////////////////////
// FBMotionClip
////////////////////////////////////////////////////////////////////////////////////
class FBSDK_DLL FBMotionClip	: public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBMotionClip, FBComponent );

public:
	/** Constructor.
	*	\param	pName       Name of the new MotionClip.
	*	\param	pFilename   Name of the file containing the associated motion.
	*	\param	pObject     Internal parent object to own MotionClip.
	*/
	FBMotionClip(char* pName, char* pFilename, HIObject pObject = NULL);

	IObject_Declare(override);		// Interface to IObject.

	FBPropertyString		Name;		//!< Name of motion clip.
	FBPropertyString		Filename;	//!< Filename to load clip from.
};

////////////////////////////////////////////////////////////////////////////////////
// FBTriggerBranch
////////////////////////////////////////////////////////////////////////////////////
class FBSDK_DLL FBTriggerBranch	: public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBTriggerBranch, FBComponent );

public:
	/** Constructor.
	*	\param	pName   Name of the TriggerBranch.
	*	\param	pObject Internal parent object to own TriggerBranch.
	*/
	FBTriggerBranch(char* pName, HIObject pObject = NULL);

	IObject_Declare(override);		// Interface to IObject.

	FBPropertyMotionClip	MotionClip;		//!< Motion clip to branch into.
	FBPropertyTrigger		Trigger;		//!< Trigger to control branching.
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* _FB_TRIGGER_H_ */
