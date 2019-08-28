#ifndef __FBKEYINGGROUP_H__
#define __FBKEYINGGROUP_H__
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

/**	\file fbkeyinggroup.h
*	KeyingGroups interface for FBSDK
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
#endif

    __FB_FORWARD( FBKeyingGroup );
    FB_DEFINE_COMPONENT( FBSDK_DLL, KeyingGroup );
    FB_DEFINE_LIST( FBSDK_DLL, KeyingGroup );

    //! Keying group types
    enum FBKeyingGroupType {	
        kFBKeyingGroupGlobal,		//!< All selected objects with the same properties as those defined in the keying group will be keyed.
        kFBKeyingGroupObjectType,	//!< All selected objects of the specified type in the keying group with the same properties as those defined in the keying group will be keyed.
        kFBKeyingGroupLocal 	    //!< Only properties of objects specified in the keying group will be keyed
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // FBKeyingGroup
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** KeyingGroup class.
    *	This class is an interface to manipulate which properties will be keyed when active. 
    *   A derived class could control when the keying group should activate and what content it should have.
    *   For example, a derived class could activate based one that is selected in the scene.
    *
    *	To create a custom keying group, use the appropriate FBKeyingGroupType flag. Then, if it is
    *	a local keying group, call AddObjectDependency() to add an object to the keying group. You can then add
    *	properties belonging to the new object with AddProperty(). 
    *
    *	If you are creating an object type keying group, call SetObjectType() to specify what kind of object will be keyed
    *	by this keying group. Then, add a property from an object, the name of the property will be used
    *	by the keying group the find corresponding properties in selected object.
    *
    *	If you create a global keying group, simply properties from an object with AddProperty(). The name of
    *	the property will be used by the keying group to find corresponding properties in the selected object.
    */
    class FBSDK_DLL FBKeyingGroup : public FBComponent
    {
        //--- Open Reality declaration.
        __FBClassDeclare(FBKeyingGroup, FBComponent);
    public:

        /**	Constructor.
        *	\param	pName	Group name.
        *	\param	pType	Keying group type.
        *	\param	pObject	For internal use only.
        */
        FBKeyingGroup(const char* pName, FBKeyingGroupType pType, HIObject pObject=NULL);

        /** Virtual FBDelete function.
        */
        virtual void FBDelete();

        /**	Set the object type filter for and object type keying group.
        *	\param	pObject	Object that will be used to set the keying group object type. Use NULL to remove the filter.
        */
        void SetObjectType(FBComponent* pObject);

        /**	Add property to be keyed when current keying group is active.
        *	\param	pProp	Property to be added.
        */
        void AddProperty(FBProperty* pProp);
        /**	RemoveProperty from the keyinggroup list.
        *	\param	pProp	Property to be removed.
        */
        void RemoveProperty(FBProperty* pProp); 

        /**	GetProperty from the keyinggroup list.
        *	\param	pIndex index of the desired property.
        *   \return property coresponding to pIndex.
        */
        FBProperty* GetProperty(int pIndex); 

        /**	GetPropertyCount.
        *   \return the number of properties in  the keying group.
        */
        int GetPropertyCount();

        /**	FindPropertyIndex.
        *   \param pProp must be in the list (return -1 if not).
        *   \return the index of pProp in the keyinggroup property list.
        */
        int FindPropertyIndex( FBProperty* pProp ); 

        /**	AddObjectDependency An object dependency is the content of a keying group and will activate keying group when selected (activation only works if the keying group is a character extension).
        *   \param pObj a Dependency of the keying group.
        */
        void    AddObjectDependency(FBComponent* pObj);

        /**	RemoveObjectDependency An object dependency is the content of a keying group and will activate keying group when selected (activation only works if the keying group is a character extension).
        *   \param pObj a Dependency of the keying group.
        */
        void    RemoveObjectDependency(FBComponent* pObj); 

        /**	IsObjectDependency determine if the \p pObj is a dependency.
        *   \param pObj an object to test the Dependency.
        *   \return true if it depend.
        */
        bool    IsObjectDependency(FBComponent* pObj);

        /**	IsObjectDependencySelected.
        *   \return return true as soon as a Property Owner or another Object Dependency is selected.
        */
        bool    IsObjectDependencySelected();

        /**	IsObjectDependencySelected empty the property list.
        */
        void    RemoveAllProperties();
        /**	IsObjectDependencySelected empty the content list.
        */
        void    RemoveAllObjectDependency();

        /**	RemoveAllSubKeyingGroup empty the child keying group.
        */
        void    RemoveAllSubKeyingGroup();

        /**	GetParentKeyingGroupCount 
        *   \return the number of parent.
        */
        int                 GetParentKeyingGroupCount();
        /**	GetParentKeyingGroup.
        *   \param pIndex is the index of the parent list of the current keying group.
        *   \return the parent keying group.
        */
        FBKeyingGroup*      GetParentKeyingGroup(int pIndex);
        /**	GetSubKeyingGroupCount.
        *   \return the number of child keying group.
        */
        int                 GetSubKeyingGroupCount();
        /**	GetSubKeyingGroup.
        *   \param pIndex index of the desired keying group child.
        *   \return the the child at the index.
        */
        FBKeyingGroup*      GetSubKeyingGroup(int pIndex);
        /**	GetSubObjectCount.
        *   \return the number of ObjectDependency of the keying group.
        */
        int                 GetSubObjectCount();
        /**	GetSubObject.
        *   \param pIndex index in the content Object Dependency list
        *   \return the desired object at \p pIndex.
        */
        FBComponent*        GetSubObject(int pIndex);

        /**	GetCumulativePropertyCount Same as GetSubKeyingGroupCount but recursive in child keying group.
        *   \param pStopAtVisible consider all keying group and stop to the first visible keying group.
        *   \return he number of ObjectDependency of the keying group.
        */
        int                 GetCumulativePropertyCount( bool pStopAtVisible = false );
        /**	GetCumulativeProperty Same as GetSubKeyingGroup but recursive in child keying group.
        *   \param pIndex index in the content Object Dependency list
        *   \param pStopAtVisible consider all keying group and stop to the first visible keying group.
        *   \return he number of ObjectDependency of the keying group.
        */
        FBProperty*			GetCumulativeProperty( int pIndex, bool pStopAtVisible = false );

        /**	ClearAllItems clear object dependency, properties and child keying group.
        */
        void ClearAllItems();


        /**	SetEnabled, makes the keying group available in keying group list of the key control UI.
        */
        void SetEnabled(bool pEnable);

        /**	SetActive, activate the keying group, replacing the other keying group
        */
        void SetActive(bool pActive);

        /**	SetActiveAppend, activate and append the keying group to the other keying groups
        */
        void SetActiveAppend(bool pActive);

        /**	FBDeselectAllAnimatableProperties, deselect all animatable properties in the scene
        */
        static void DeselectAllAnimatableProperties();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListKeyingGroup
    ////////////////////////////////////////////////////////////////////////////////////
    FB_DEFINE_LIST( FBSDK_DLL, KeyingGroup );
    FB_FORWARD( FBPropertyListKeyingGroup );

    //! \b PropertyList: KeyingGroup.
    class FBSDK_DLL FBPropertyListKeyingGroup : public FBPropertyListComponent
    {
    public:
        FBPropertyListKeyingGroup();
        /**	Get the KeyingGroup at \e pIndex.
        *	\param	pIndex	Index of KeyingGroup to get.
        *	\return KeyingGroup at \e pIndex.
        */
        FBKeyingGroup* operator[](int pIndex);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FBSDKUseNamespace
}
#endif
#endif /* this must be the last line of this file */
