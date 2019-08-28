#ifndef __FBSCENE_H__
#define __FBSCENE_H__
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

/**	\file fbscene.h
*	Contains information pertaining to the FBScene class, a representation
*	of a scene in the 3D world.
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
#include <fbsdk/fbdata.h>
#include <fbsdk/fbfolder.h>
#include <fbsdk/fbrenderer.h>
#include <fbsdk/fbshader.h>
#include <fbsdk/fbmodel.h>
#include <fbsdk/fbhud.h>
#include <fbsdk/fbcamera.h>
#include <fbsdk/fblight.h>
#include <fbsdk/fbvideo.h>
#include <fbsdk/fbmotion.h>
#include <fbsdk/fbgroup.h>
#include <fbsdk/fbfilereference.h>
#include <fbsdk/fbnamespace.h>
#include <fbsdk/fbobjectpose.h>

#if !defined(K_NO_CHARACTER)
#include <fbsdk/fbcharacter.h>
#include <fbsdk/fbcharacterface.h>
#include <fbsdk/fbcharacterpose.h>
#include <fbsdk/fbcharacterextension.h>
#endif

#if !defined(K_NO_DECK)
#include <fbsdk/fbdeck.h>
#endif

#if !defined(K_NO_AUDIO)
#include <fbsdk/fbaudio.h>
#endif

#if !defined(K_NO_MANIPULATOR)
#include <fbsdk/fbmanipulator.h>
#endif

#if !defined(K_NO_NOTE)
#include <fbsdk/fbnote.h>
#endif

#if !defined(K_NO_POSE)
#include <fbsdk/fbpose.h>
#endif

#if !defined(K_NO_STORY)
#include <fbsdk/fbcommand.h>
#endif

#if !defined(K_NO_PROJECTSETTINGS)
#include <fbsdk/fbprojectsettings.h>
#endif

#ifndef FBSDK_LEAN_AND_MEAN
#include <fbsdk/fbuserobject.h>
#endif

#include <fbsdk/fbconstraint.h>
#if !defined(K_NO_OPTICAL)
	#include <fbsdk/fboptical.h>
#endif


#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {;
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBSceneEvent
////////////////////////////////////////////////////////////////////////////////////
//! Types of model selection events.
enum FBSceneChangeType
{
    kFBSceneChangeNone,					//!< Unknown event
    kFBSceneChangeDestroy,				//!< Object destroyed
    kFBSceneChangeAttach,				//!< Object attached
    kFBSceneChangeDetach,				//!< Object detached
    kFBSceneChangeAddChild,				//!< Child added
    kFBSceneChangeRemoveChild,			//!< Child removed
    kFBSceneChangeSelect,				//!< Object selection
    kFBSceneChangeUnselect,				//!< Object deselection
    kFBSceneChangeRename,				//!< Before object rename
    kFBSceneChangeRenamePrefix,			//!< Before object rename prefix
    kFBSceneChangeRenameUnique,			//!< Before object rename unique
    kFBSceneChangeRenameUniquePrefix,	//!< Before object rename unique prefix
    kFBSceneChangeRenamed,				//!< After object rename
    kFBSceneChangeRenamedPrefix,		//!< After object rename prefix
    kFBSceneChangeRenamedUnique,		//!< After object rename unique
    kFBSceneChangeRenamedUniquePrefix,	//!< After object rename unique prefix
    kFBSceneChangeSoftSelect,			//!< Soft selection
    kFBSceneChangeSoftUnselect,			//!< Soft deselection
    kFBSceneChangeHardSelect,			//!< Hard selection
    kFBSceneChangeActivate,				//!< Activate
    kFBSceneChangeDeactivate,			//!< Deactivate
    kFBSceneChangeLoadBegin,			//!< Begin loading file
    kFBSceneChangeLoadEnd,				//!< End loading file
    kFBSceneChangeClearBegin,			//!< Begin clearing file (file new)
    kFBSceneChangeClearEnd,				//!< End clearing file (file new)
    kFBSceneChangeTransactionBegin,		//!< Begin transaction
    kFBSceneChangeTransactionEnd,		//!< End transaction
    kFBSceneChangeMergeTransactionBegin,//!< Begin merge transaction
    kFBSceneChangeMergeTransactionEnd,	//!< End merge transaction
    kFBSceneChangeReSelect,				//!< Re-selection
    kFBSceneChangeChangeName,			//!< Object change name
    kFBSceneChangeChangedName,			//!< Object changed name
    kFBSceneChangePreParent,			//!< Before object parenting
    kFBSceneChangePreUnparent,			//!< Before object unparenting
    kFBSceneChangeFocus,				//!< Object have focus
    kFBSceneChangeChangedParent,		//!< Object changed parent
    kFBSceneChangeReorder,				//!< Object reorder
    kFBSceneChangeReordered,			//!< Object reordered
};

FB_DEFINE_ENUM( FBSDK_DLL, SceneChangeType );

__FB_FORWARD( FBEventSceneChange );

/** Select model event class.
*	This event occurs every time a model is:
*	- (un)selected
*	- added
*	- destroyed
*	- renamed, etc..
*/
class FBSDK_DLL FBEventSceneChange: public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventSceneChange( HKEventBase pEvent );		

    FBPropertySceneChangeType	Type;			 //!< <b>Read Only Property:</b> Type of selection event.
    FBPropertyComponent			Component;		 //!< <b>Read Only Property:</b> Modified component
    FBPropertyComponent			ChildComponent;  //!< <b>Read Only Property:</b> Child component of the event.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventTakeChange
////////////////////////////////////////////////////////////////////////////////////
//! Types of take change events.
enum FBTakeChangeType	
{
    kFBTakeChangeAdded,			
    kFBTakeChangeRemoved,		
    kFBTakeChangeOpened,		
    kFBTakeChangeClosed,		
    kFBTakeChangeRenamed,		
    kFBTakeChangeUpdated,		
    kFBTakeChangeMoved,			
    kFBTakeChangeNone			
};

FB_DEFINE_ENUM( FBSDK_DLL, TakeChangeType );

__FB_FORWARD( FBEventTakeChange );

/** Take change event class.
*	This event occurs every time a take is:
*	- added
*	- destroyed
*	- renamed
*	- selected, etc.
*/
class FBSDK_DLL FBEventTakeChange: public FBEvent 
{
public:

    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventTakeChange( HKEventBase pEvent );		

    FBPropertyTakeChangeType	Type;		 //!< <b>Read Only Property:</b> Type of take change event.
    FBPropertyTake				Take;		 //!< <b>Read Only Property:</b> The take modified.
};

////////////////////////////////////////////////////////////////////////////////////
// FBSceneList
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD		( FBPropertyListScene );
__FB_FORWARD( FBScene );
FB_DEFINE_LIST	( FBSDK_DLL, Scene );

/** \b PropertyList: Scene.
*/
class FBSDK_DLL FBPropertyListScene : public FBPropertyBaseList< FBScene* >
{
private:
public:
    /**	Add a scene to the list.
    *	\param	pItem	Scene to add to list.
    *	\return Number of scenes in list after operation.
    */
    virtual int Add( FBScene* pItem );
    /**	Remove the scene at \p pIndex from list.
    *	\param	pIndex	Index of Scene to remove.
    */
    virtual void RemoveAt( int pIndex );
    /**	Get the Scene at \p pIndex.
    *	\param	pIndex	Index of Scene to get a handle on.
    *	\return Scene at \p pIndex.
    */
    virtual FBScene* operator[](int pIndex);
    /**	Get the Scene count.
    *	\return Number of Scenes.
    */
    virtual int GetCount();
};

////////////////////////////////////////////////////////////////////////////////////
// FBScene
////////////////////////////////////////////////////////////////////////////////////

/**	Access to the MotionBuilder scene.
*	In MotionBuilder, the scene is the environment where your models exist. The scene contains models 
which you can import, select, transform, copy, tweak, and animate.

The FBScene object is obtained from the scene attribute of FBSystem.

The FBScene class contains many attributes that you can use to access objects, e.g cameras, characters, 
lights, and takes, essentially everything you see in the Navigator in the UI. A project can only contain 
one scene, and if you try to create an instance of a scene you will get an error, so you must access the 
scene by getting a handle through FBSystem.
\code
myScene = FBSystem().Scene
\endcode

See also the C++ code sample in toolscene.
*/
class FBSDK_DLL FBScene : public FBComponent {
    __FBClassDeclare( FBScene,FBComponent );

    // We want to disallow the use of the copy constructor and operator for FBScene.
    FBScene( const FBScene* );
    FBScene( const FBScene& );
    FBScene& operator=( const FBScene& );

public:

    /**	Constructor.
    * Client code cannot instantiate objects of this class. The FBSystem class
    * provides access to the current scene object.
    *	\param	pObject	Internal parent object.
    */
    FBScene(HIObject pObject);

    /** Virtual FBDelete function.
    */
    virtual void FBDelete();

    /**	Clears the elements part of the scene. Not those that belong to all the scenes.   	
    */
    void Clear();

    /** Evaluate the scene.
    *   \note MoBu's is highly optimized for real-time performance, due to its multi-thread, double buffer 
    *           and lazy-evaluation architecture, complex scripts are often required to call FBScene::Evaluate() 
    *           to commit previous scene change commands before execute following operations. Also, certain operations 
    *           in SDK may require cached data to be reevaluated. In typical large scenes this call may be consider 
    *           as very costly. That's why user is responsible to design code in the way that requires as little as 
    *           possible calls to FBScene::Evaluate. We should consider use FBScene::Evaluate() between scene change 
    *           commands as "common scripting practice
    *
    *	\return true if successful.
    */
    bool Evaluate();

    /** Resolving the Candidate.
    *   \return true if successful.
    */
    bool CandidateEvaluationAndResolve();

    /** Evaluate the deformations of the scene
    *	\return true if successful.
    */
    bool EvaluateDeformations();

    /** Get paths of all the python scripts object in the scene.
    *	\param pPathList Out parameter, to collect the path of python scripts. 
    */
    void GetScriptsPaths( FBStringList& pPathList );

    /**
    * \name Namespace Management.
    */
    //@{

    /** Get list of children namespaces in the given namespace. 
    *	\param  pNamespaceList	the list of namespace to return.
    *	\param	pNamespace      specify the parent namespace, NULL for the whole scene.
    *	\param	pRecursive	    \b True only work on the direct children level namespace, otherwise will work on the whole children namespace hierarchy recursively.
    *	\return the list of children namespaces.
    */	
    int NamespaceGetChildrenList(FBStringList& pNamespaceList, const char* pNamespace = NULL, bool pRecursive = true );

    /** Get Owner FileReference object if the namespace is originated from File Reference.
    *	\param	pNamespace		the namespace to work on, could be nested namespace inside the FileReference's namespace.
    *	\return the FileReference object is the namespace is originated from. NULL otherwise.
    */	
    FBFileReference* NamespaceGetOwnerFileReference(const char* pNamespace);

    /** Get Namespace object.
    *   \param  pNamespace      the namespace to query
    *   \return Namespace with exact name matching
    */
    FBNamespace* NamespaceGet(const char* pNamespace);

    /** Query if namespace exists
    *   \param  pNamespace      the namespace to query
    *   \return \b True if the namespace exist, otherwise return \b False.
    */
    bool NamespaceExist(const char* pNamespace);

    /** Query if namespace is empty
    *   \param  pNamespace      the namespace to query, NULL for whole scene.
    *   \return \b True if the namespace (don't include nested children namespace) is empty
    */
    bool NamespaceEmpty(const char* pNamespace);

    /** Get List of the namespace content.
    *	\param	pContentList	the list of content to return.
    *	\param	pNamespace		the namespace to work on, NULL for whole scene.
    *	\param	pModificationFlags	bitwise combination of kFBConnectionSrcObjectModified,  kFBConnectionDstObjectModified, kFBConnectionSrcPropertyModified, kFBConnectionDstPropertyModified flags. kFBPlugAllContent means all the content.
    *                              Modification flags beside kFBPlugAllContent will only work on FileReference Namespace. 
    *	\param	pRecursive	    \b True only work on the direct children level namespace, otherwise will work on the whole children namespace hierarchy recursively.
    *	\param  pTypeInfo		the typeInfo of the type of interested object, 0 for all the objects. 
    *   \param  pExactTypeMatch if \b True, the derived typeInfo won't be considered (For example, FBCamera won't be considered when passing FBModel::TypeInfo).
    */
    void NamespaceGetContentList(FBComponentList& pContentList, const char* pNamespace, FBPlugModificationFlag pModificationFlags = kFBPlugAllContent, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false);

    /** Select (or de-select) the namespace content.
    *	\param	pNamespace		the namespace to work on, NULL for whole scene.
    *	\param	pSelect			\b True (or \b False) indicate to select (or de-select)
    *	\param	pModificationFlags	bitwise combination of kFBConnectionSrcObjectModified,  kFBConnectionDstObjectModified, kFBConnectionSrcPropertyModified, kFBConnectionDstPropertyModified flags. kFBPlugAllContent means all the content.
    *                              Modification flags beside kFBPlugAllContent will only work on FileReference Namespace. 
    *	\param	pRecursive	    \b True only work on the direct children level namespace, otherwise will work on the children namespace hierarchy recursively.
    *	\param  pTypeInfo		the typeInfo of the type of interested object, default for all the objects. 
    *   \param  pExactTypeMatch if \b True, the derived typeInfo won't be considered (For example, FBCamera won't be considered when passing FBModel::TypeInfo).
    */
    void NamespaceSelectContent(const char* pNamespace, bool pSelect, FBPlugModificationFlag pModificationFlags = kFBPlugAllContent, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false);

    /** Rename the namespace.
    *	\param	pNameSpace		the namespace to work on, NULL for whole scene.
    *	\param  pNewNamespace	the new namespace
    *	\param	pRecursive	    \b True only work on the direct children level namespace, otherwise will work on the children namespace hierarchy recursively.
    *	\param  pTypeInfo		the typeInfo of the type of interested object, default for all the objects. 
    *   \param  pExactTypeMatch if \b True, the derived typeInfo won't be considered (For example, FBCamera won't be considered when passing FBModel::TypeInfo).
    *	\return \b True if operation successfully, \b False is this namespace (or pTypeInfo type of objects) doesn't exist, or locked (by FileReferencing or etc.,)
    *   \note call with default parameters is considered as renaming of the whole namespace structure, otherwise will be considered as partially renaming individual
    *           objects. Renaming permission will be validated accordingly. 
    */
    bool NamespaceRename(const char* pNameSpace, const char* pNewNamespace, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false);

    /** Delete the namespace & all its content.
    *	\param	pNamespace		the namespace to work on
    *	\return \b True if operation successfully, \b False is this namespace doesn't exist, or is locked (by FileReferencing or etc.,)
    */
    bool NamespaceDelete(const char* pNamespace);

    /** Remove all empty namespaces.
    *   During some namespace operations, empty namespace may left over, while this is not harmful but could be annoying.
    *   Save the scene and load it back those empty namespaces will disappear. And this function also allow user to remove all empty 
    *   namespaces from the scene easily via SDK.
    *	\return \b True if operation successfully.
    */
    bool NamespaceCleanup();

    /** Delete the namespace content.
    *	\param	pNamespace		the namespace to work on
    *	\param	pModificationFlags	bitwise combination of kFBConnectionSrcObjectModified,  kFBConnectionDstObjectModified, kFBConnectionSrcPropertyModified, kFBConnectionDstPropertyModified flags. kFBPlugAllContent means all the content.
    *                              Modification flags beside kFBPlugAllContent will only work on FileReference Namespace. 
    *	\param	pRecursive	    \b True only work on the direct children level namespace, otherwise will work on the children namespace hierarchy recursively.
    *	\param  pTypeInfo		the typeInfo of the type of interested object, default for all the objects. 
    *   \param  pExactTypeMatch if \b True, the derived typeInfo won't be considered (For example, FBCamera won't be considered when passing FBModel::TypeInfo).
    *	\return \b False is the given namespace doesn't exist, or is locked (by FileRef or etc.,), \b True otherwise.
    *   \note   Not all the objects will be deletable (system objects and etc.,). Deletion of partial FileRef content isn't prevented, however the behavior is undefined. 
    */
    bool NamespaceDeleteContent(const char* pNamespace, FBPlugModificationFlag pModificationFlags = kFBPlugAllContent, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false);

    /** Import file into Namespace (or as file reference)
    *	\param	pNamespace		the namespace to import to, must be in editable scope.
    *   \param  pFilePath       the referenced file path to import.
    *   \param  pAsFileReference import the file as file reference. The default value is false.
    *   \return \b True if successfully.
    */
    bool NamespaceImport(const char* pNamespace, const char* pFilePath, bool pAsFileReference = false );

    /** Import file into multiple Namespaces (or as file references)
    *	\param	pDstNamespaceList	the Dst namespaces list to import, must not exist or be self contained.
    *   \param  pFilePath           the referenced file path to import.
    *   \param  pAsFileReference import the file as file reference. The default value is false.
    *   \return \b True if successfully.
	*   \note   Nested destination namespaces are not allowed (e.g. a DstNamespaceList contains "NS1" and "NS1:NS2" will return False).
    */
    bool NamespaceImportToMultiple(const FBStringList& pDstNamespaceList, const char* pFilePath, bool pAsFileReference = false );

    /** Export scene content within namespace to file
    *	\param	pNamespace		the namespace to use, must exist
    *   \param  pFilePath       the referenced file path to export.
    *   \param  pASCIIFormat    save the file in ASCII format.
    *   \return \b True if successfully.
    */
    bool NamespaceExport(const char* pNamespace, const char* pFilePath, bool pASCIIFormat = false);

    //@}

    FBPropertyListTake				Takes;			//!< <b>List:</b> Takes for scene.
    FBPropertyModel					RootModel;		//!< <b>Read Only Property:</b> Scene Root model for that scene
    FBPropertyListCamera			Cameras;		//!< <b>List:</b> Cameras in scene.
    FBPropertyListMaterial			Materials;		//!< <b>List:</b> Materials for scene.
    FBPropertyListTexture			Textures;		//!< <b>List:</b> Textures for scene.
    FBPropertyListShader			Shaders;		//!< <b>List:</b> Shaders for scene.
    FBPropertyListDeformer			Deformers;		//!< <b>List:</b> Deformers for scene.
    FBPropertyListDevice			Devices;		//!< <b>List:</b> Devices for scene.
    FBPropertyListConstraint		Constraints;	//!< <b>List:</b> Constraints in scene.

    FBPropertyListLight				Lights;			//!< <b>List:</b> Lights in scene.
#if !defined(K_NO_AUDIO)
    FBPropertyListAudioClip			AudioClips;		//!< <b>List:</b> Audio clips in scene.
#endif
#if !defined(K_NO_VIDEO)
    FBPropertyListVideoClip			VideoClips;		//!< <b>List:</b> Video clips in scene.
#endif

    FBPropertyListMotionClip		MotionClips;	//!< <b>List:</b> Motion clips in scene.

#if !defined(K_NO_FOLDER)
    FBPropertyListFolder			Folders;		//!< <b>List:</b> Folders in scene.
#endif

#if !defined(K_NO_NOTE)
    FBPropertyListNote              Notes;          //!< <b>List:</b> Notes in scene.
#endif

#if !defined(K_NO_POSE)
    FBPropertyListPose              Poses;          //!< <b>List:</b> Poses in scene.
    FBPropertyListObjectPose		ObjectPoses;	//!< <b>List:</b> ObjectPoses in scene.
#endif

#if !defined(K_NO_ACTOR)
    FBPropertyListActor				Actors;			//!< <b>List:</b> Actors in scene.
    FBPropertyListActorFace			ActorFaces;		//!< <b>List:</b> ActorFaces in scene.
#endif

#if !defined(K_NO_CHARACTER)
    FBPropertyListMarkerSet			MarkerSets;		//!< <b>List:</b> Marker sets in scene.
    FBPropertyListCharacterMarkerSet CharacterMarkerSets;		//!< <b>List:</b> Character marker sets in scene.
    FBPropertyListControlSet		ControlSets;	//!< <b>List:</b> Control set rigs in scene.
    FBPropertyListCharacter			Characters;		//!< <b>List:</b> Characters in scene.
    FBPropertyListCharacterFace		CharacterFaces;	//!< <b>List:</b> Character faces in scene.
    FBPropertyListCharacterPose		CharacterPoses;	//!< <b>List:</b> Character poses in scene.
    FBPropertyListCharacterExtension CharacterExtensions;	//!< <b>List:</b> Character extensions available in the scene.
#endif

#ifndef FB_KERNEL 
    FBPropertyListUserObject		UserObjects;	//!< <b>List:</b> User objects
#endif

#if !defined(K_NO_PROJECTSETTINGS)
    FBPropertyProjectSettings		ProjectSettings;//!< <b>Read Only Property:</b> Local project settings
#endif

    FBPropertyRenderer				Renderer;		//!< <b>Read Only Property:</b> Local renderer.
    FBPropertyListComponent			Components;		//!< <b>List:</b> Generic List of components.
    FBPropertyListGroup				Groups;			//!< <b>List:</b> Groups available in the scene.
    FBPropertyListSet				Sets;			//!< <b>List:</b> Sets available in the scene.
    FBPropertyListNamespace         Namespaces;     //!< <b>List:</b> Namespace (include FileReference) available in the scene 
    FBPropertyListFileReference		FileReferences;	//!< <b>List:</b> FileReference available in the scene.

#ifndef K_NO_UI
    FBPropertyListHandle			Handles;		//!< <b>List:</b> Handles present in the scene.
#endif
#ifndef K_NO_HUD 
    FBPropertyListHUD				HUDs;           //!< <b>Read Only Property:</b> Heads Up Displays in the scene.
#endif

    FBPropertyListConstraintSolver		ConstraintSolvers;		//!< <b>List:</b> Constraint Solvers present in the scene.
    FBPropertyListPhysicalProperties	PhysicalProperties;		//!< <b>List:</b> PhysicalProperties present in the scene.

    FBPropertyString				FilePath;		//!< <b>Read Write Property:</b> File path of the scene.

    FBPropertyListKeyingGroup       KeyingGroups;	//!< <b>Read Write Property:</b> Keying Groups in the scene.
    FBPropertyListModelSkeleton     ModelSkeletons; //!< <b>Read Write Property:</b> Bones (Skeletons) in the scene.
#ifndef K_NO_OPTICAL
    FBPropertyListModelOptical      ModelOpticals;  //!< <b>Read Write Property:</b> Optical Data in the scene.
#endif
    FBPropertyEvent					OnChange;		//!< <b>Event:</b> Something in the scene has happened.(FBEventSceneChange)
    FBPropertyEvent					OnTakeChange;	//!< <b>Event:</b> Something related to a take has happened.(FBEventTakeChange)
};

#ifndef __FB_COMPONENT_SCENE
#define __FB_COMPONENT_SCENE
FB_DEFINE_COMPONENT( FBSDK_DLL, Scene );
#endif


#ifdef FBSDKUseNamespace
}
#endif
#endif

