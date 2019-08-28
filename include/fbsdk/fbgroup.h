#ifndef __FBGROUP_H__
#define __FBGROUP_H__
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

/**	\file fbgroup.h
*	Groups interface for FBSDK
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcore.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBGroup );
__FB_FORWARD( FBSet );
FB_DEFINE_COMPONENT( FBSDK_DLL, Group );
FB_DEFINE_COMPONENT( FBSDK_DLL, Set );

FB_FORWARD( FBPropertyListGroup );
FB_FORWARD( FBPropertyListSet );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! <b>List:</b> Group
class FBSDK_DLL FBPropertyListGroup : public FBPropertyListComponent
{
public:
	FBPropertyListGroup();
	/**	Get the group at \e pIndex.
	*	\param	pIndex	Index of group to get.
	*	\return Group at \e pIndex.
	*/
	FBGroup* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! <b>List:</b> Set
class FBSDK_DLL FBPropertyListSet : public FBPropertyListComponent
{
public:
	FBPropertyListSet();
	/**	Get the set at \e pIndex.
	*	\param	pIndex	Index of set to get.
	*	\return Set at \e pIndex.
	*/
	FBSet* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBGroup
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Objects Grouping class.
*	This class is an interface to manipulate object's grouping in the scene.
*/
class FBSDK_DLL FBGroup : public FBBox
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBGroup, FBBox);
public:

	/**	Constructor.
	*	\param	pName	Group name.
	*	\param	pObject	For internal use only.
	*/
	FBGroup(const char* pName, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

    /** Clone the group.
    *    This will duplicated the current group. 
    *    \return Newly created group.
    */
    FBGroup* Clone();

	/** Select
	*	\param	pSelect	If <b>true</b>, group contents will be selected.
	*/
	void Select(bool pSelect);

	/** Contains
	*	\param	pComponent	Component to verify if it is in the Group
    *   \return True if the object is in the Group
	*/
	bool Contains(FBComponent* pComponent);

	FBPropertyBool			Show;			//!< <b>Read Write Property:</b> Controls if objects in the group are displayed.
	FBPropertyBool			Pickable;		//!< <b>Read Write Property:</b> Controls if objects in the group are pickable.
	FBPropertyBool			Transformable;	//!< <b>Read Write Property:</b> Controls if objects in the group are transformable.
	FBPropertyListComponent	Items;			//!< <b>List:</b> Items in the group.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBSet
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Objects Set class.
*	This class is an interface to manipulate object sets in the scene.
*	Note: an item cannot be in two FBSet objects at once. Also, an FBGroup cannot
*	contain FBSet objects, although an FBSet object can contain an FBGRoup.
*/
class FBSDK_DLL FBSet : public FBBox
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBSet, FBBox);
public:

	/**	Constructor.
	*	\param	pName	Set name.
	*	\param	pObject	For internal use only.
	*/
	FBSet(const char* pName, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	/** Select
	*	\param	pSelect	If <b>true</b>, set contents will be selected.
	*/
	void Select(bool pSelect);

	/** Contains
	*	\param	pComponent	Component to verify if it is in the Group
    *   \return 0 if the component is not in the FBSet, 1 if it is in this FBSet, 2 if it is in another FBSet
	*/
	int Contains(FBComponent* pComponent);

	FBPropertyAnimatableBool	Visibility;		//!< <b>Read Write Property:</b> Visibility of set (animatable).
	FBPropertyBool				Pickable;		//!< <b>Read Write Property:</b> Controls if objects in the set are pickable.
	FBPropertyBool				Transformable;	//!< <b>Read Write Property:</b> Controls if objects in the set are transformable.
	FBPropertyListComponent		Items;			//!< <b>List:</b> Items in the set.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
