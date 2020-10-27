#ifndef __FBBASE_H__
#define __FBBASE_H__
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

/**	\file fbcomponent.h
*	Basic class definitions.
*	Contains the basic classes that most SDK objects will derive from. 
*	These classes form the base of many functionalities of the SDK. The file
*	also contains the base macros used in the definition/registration 
*	of the SDK classes.
*/

#include <kaydaradef.h>

// This include directive is necessary because of the definition of the
// FBLibrary class.
#include <fbsdk/fblibrary.h>

#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

// Global includes
#include <fbsdk/fbplug.h>
#include <fbsdk/fbarray.h>
#include <fbsdk/fbstring.h>
#include <fbsdk/fbproperties.h>

#ifdef _MSC_VER
	#pragma warning (disable: 4275)	// 'int' : forcing value to bool 'true' or 'false' (performance warning) 
	#pragma warning (disable: 4661)	// no suitable definition provided for explicit template instantiation request
#endif

K_FORWARD( IRegister );
K_FORWARD( IError );
K_FORWARD( IStore );
K_FORWARD( IKtView );
K_FORWARD( KEventBase );
K_FORWARD( KGlobalNamedEvent );

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

#ifndef FBINCLUDE
// Section that must be exported
#else
#endif
/** \def FB_DEFAULT_SDK_ICON
*	Define SDK icon filename
*/
#define FB_DEFAULT_SDK_ICON	"openreality_noicon.png"

// For internal use only.
/** \def __FBClassInit
*	For internal use only
*/
#define __FBClassInit mLocalPtr = NULL;        

// For internal use only.
/** \def __FBClassDeInit
*	For internal use only
*/
#define __FBClassDeInit if (mLocalPtr) {delete mLocalPtr; mLocalPtr = NULL;}

// For internal use only.
/** \def __FBClassInitSDKComponent
*	For internal use onlyL  decide if we need to delete the corresponding KObject
*/
#define __FBClassInitSDKComponent( pObjectToWrappedIsAllocated ) \
    __FBClassInit; \
    mSDKComponent = pObjectToWrappedIsAllocated;

/** __FBRegisterTypeInfo
* For internal use only, 
* Register the TypeInfo mapped to internal class id.
*/
FBSDK_DLL int  __FBRegisterTypeInfo(int pInternalClassId);

/** __FBGetInternalClassId
* For internal use only, 
* Get the internal class Id from the ORSDK FBCompoent's TypeInfo.
*/
FBSDK_DLL int  __FBGetInternalClassId(int pTypeInfo);

/** __FBObjectCreatorSub
* For internal use only, 
* Create the FBPlug object from internal object.
*/
FBSDK_DLL FBPlug* __FBObjectCreatorSub(HIObject pObject);

/** \def __FBClassDeclare
*	For internal use only
*/
#define __FBClassDeclare( Name,Parent ) \
    friend FBSDK_DLL FBPlug* __FBObjectCreatorSub(HIObject pObject);\
  public: \
	/*! \fn typedef Parent __FBParentClass
	 *  Type definition. 
	*/\
	typedef Parent	__FBParentClass;\
	/*! \fn typedef Name __FBClassType
	 *  Type definition. 
	*/\
	typedef Name	__FBClassType;\
	/** \fn ClassName
	*	\return Name
	*/\
	virtual const char* ClassName() override { return #Name; } \
	/** \fn Is( int pTypeId )
	*	\param pTypeId Represent the id of the type asked.
	*	\return true if the object id correspond
	*/\
	virtual bool Is( int pTypeId ) override { return (pTypeId==TypeInfo) ? true : Parent::Is( pTypeId ); } \
    virtual int GetTypeId() override { return TypeInfo; } \
	/** \fn GetInternalClassId()
	*	\return Internal class Id
	*/\
	static  int GetInternalClassId(); \
	/** \var mLocalPtr 
	    \brief Internal pointer.
	*/\
	Data##Name* mLocalPtr; \
	virtual ~Name(); \
	static int TypeInfo; \
    /** return to the default scope (private) */\
  private:

/** \def __FBClassDeclareGroup
*	For internal use only
*/
#define __FBClassDeclareGroup( Name,Parent ) \
    __FBClassDeclare( Name,Parent )\
  public:\
    static  const char*	ClassGroupName; \
    /** return to the default scope (private) */\
  private: 

FBSDK_DLL void __FBAddModelToScene( HIObject pObject );         //!< For internal usage only
FBSDK_DLL void __FBRemoveModelFromScene( HIObject pObject );    //!< For internal usage only

/** Storable Class implementation.
*	This should be placed in the source code file for a class.
*/
#define FBStorableClassImplementation(ClassName, Type)\
	const char* ClassName::FbxGetObjectSubType(){ return #ClassName; }\
	HIObject RegisterStorable##ClassName##Create(HIObject /*pOwner*/, const char* pName, void* /*pData*/){\
		ClassName* Class = new ClassName(pName);\
		Class->mAllocated = true;\
		if( Class->FBCreate() ){\
            __FBRemoveModelFromScene( Class->GetHIObject() ); /* Hack in MoBu2013, we shouldn't add object to the scene/entity automatically*/\
            return Class->GetHIObject();\
		} else {\
			delete Class;\
			return NULL;}}\
	FBLibraryModule(ClassName##Storable){\
		FBString lGroup = "FbxStorable/";\
		lGroup += #Type;\
		FBRegisterObject(ClassName##R2, lGroup, #ClassName, "", RegisterStorable##ClassName##Create, true, NULL);}

/** Element Class implementation. (Asset system)
*	This should be placed in the source code file for a class.
*/
#define FBElementClassImplementation(ClassName,IconFileName)\
	HIObject RegisterElement##ClassName##Create(HIObject /*pOwner*/, const char* pName, void* /*pData*/){\
		ClassName* Class = new ClassName(pName);\
		Class->mAllocated = true;\
		if( Class->FBCreate() ){\
            __FBRemoveModelFromScene( Class->GetHIObject() ); /* Hack in MoBu2013, we shouldn't add object to the scene/entity automatically*/\
			return Class->GetHIObject();\
		} else {\
			delete Class;\
			return NULL;}}\
	FBLibraryModule(ClassName##Element){\
		FBRegisterObject(ClassName##R2, "Browsing/Templates/Elements", #ClassName, "", RegisterElement##ClassName##Create, true, IconFileName);}

/** Shading Element Class implementation.
*	This should be placed in the source code file for a class.
*/
#define FBShadingElementClassImplementation(ClassName,IconFileName)\
	HIObject RegisterShadingElement##ClassName##Create(HIObject /*pOwner*/, const char* pName, void* /*pData*/){\
		ClassName* Class = new ClassName(pName);\
		Class->mAllocated = true;\
		if( Class->FBCreate() ){\
			return Class->GetHIObject();\
		} else {\
			delete Class;\
			return NULL;}}\
	FBLibraryModule(ClassName##ShadingElement){\
		FBRegisterObject(ClassName##R2, "Browsing/Templates/Shading Elements", #ClassName, "", RegisterShadingElement##ClassName##Create, true, IconFileName);}

/**	Storable Class declaration.
*	Overloads the necessary functions when a class inherits from
*	FBComponent (or its derivatives) and that you want it to be persistent.
*	\param Name		Name of class to declare.
*	\param Parent	Parent class to associate with \e Name.
*/
#define FBStorableClassDeclare(Name, Parent)\
	FBClassDeclare(Name, Parent);\
public:\
	virtual const char* FbxGetObjectSubType() override; \
    /** Return to default scope (private)*/\
private: \


/**	Initialize a property: component.
*	\param	Param		Owner name.
*	\param	Type		Type of variable.
*	\param	PropName	Component name.
*	\param	Get			Get function pointer.
*	\param	Set			Set function pointer.
*/
#define FBPropertyInitComponent( Param,Type,PropName,Get,Set ) \
	{ \
		PropertyAdd(PropName.Init( (void *)Param,#PropName,(Type* (*)(void *))Get,(void (*)(void *,Type*))Set )); \
		PropName.TypeInfo = &Type::TypeInfo; \
	}

/** Macro to verify the type of a component.
*	Used to compare a component to another, by verifying their
*	Class::TypeInfo values.
*	\param Component		Component to verify.
*	\param ComponentType	Type to verify \e Component with.
*	\return \b true if object is of type \e ComponentType.
*/
#define FBIS( Component,ComponentType ) \
	((Component) && (Component)->Is( ComponentType::TypeInfo ))

////////////////////////////////////////////////////////////////////////////////////
// Utility function
////////////////////////////////////////////////////////////////////////////////////
// For internal use only.
__FB_FORWARD( FBComponent );
__FB_FORWARD( FBVisualComponent );

/** Get a handle to the FBComponent belonging to an HIObject.
*	This will not create the internal SDK object, and will return NULL if
*	the SDK object has not been initialized.
*	\param Object	Internal object for which the FBComponent is required.
*	\return Handle to FBComponent belonging to \e Object.
*/
FBSDK_DLL FBComponent* GetFBComponent( const HIObject Object );

#if !defined(K_NO_UI)
/**	Get the FBComponent from an Internal Object.
*	\param	pObject		Object to get SDK object for.
*	\param	pAutoCreate	Create object if it doesn't exist? (default is \b true)
*	\return	FBComponent for \e pObject.
*/
FBSDK_DLL FBVisualComponent*  FBGetFBVisualComponent( HIKtView pObject,bool pAutoCreate=true );
#endif

/**	Get the FBComponent from an Internal Object.
*	\param	pObject		Object to get SDK object for.
*	\param	pAutoCreate	Create object if it doesn't exist? (default is \b true)
*	\return	FBComponent for \e pObject.
*/
FBSDK_DLL FBComponent*  FBGetFBComponent( HIObject pObject, bool pAutoCreate=true );

//! typedef FBArrayTemplate<FBComponent*> FBComponentList;
typedef FBArrayTemplate<FBComponent*> FBComponentList;

/**	Create a FBObjectList object.
*	This is to get around memory management issues when mixing debug and release runtime
*   libraries on Windows. By using the FBCreateObjectList/FBDestroyObjectList
*   duo of functions, you ensure that the memory used in the array is allocated,
*   reallocated and freed in the same memory pool.
*/
FBSDK_DLL FBComponentList* FBCreateComponentList();

/** Delete a FBObjectList object.
*   \param  pObjectList  pointer to the object created with a call to FBCreateObjectList().
*/
FBSDK_DLL void FBDestroyComponentList( FBComponentList* pObjectList );

/** Get the Root FBComponent
*/
FBSDK_DLL FBArrayTemplate<FBComponent*>& FBGetComponentArray();

////////////////////////////////////////////////////////////////////////////////////
// Registration macros
////////////////////////////////////////////////////////////////////////////////////

/** \def FBRegisterEvent
*	Event registration/un-registration.
*	For internal use only.
*/
#define FBRegisterEvent		( Object, EventId, EventProc )	IQ(	Object,IRegister)->Register		( EventId,(HICallback)this,(kICallbackHandler)EventProc );
/** \def FBUnregisterEvent
*	Event registration/un-registration.
*	For internal use only.
*/
#define FBUnregisterEvent	( Object, EventId, EventProc )	IQ(	Object,IRegister)->Unregister	( EventId,(HICallback)this,(kICallbackHandler)EventProc );

/** \def FBSetStoreableCustomModelRegistered
*	Set custom models have been defined.
*	For internal use only.
*/
FBSDK_DLL void FBSetStoreableCustomModelRegistered();
FBSDK_DLL bool FBGetStoreableCustomModelRegistered();

/** \def FBSetStoreableCustomMaterialRegistered
*	Set custom materials have been defined.
*	For internal use only.
*/
FBSDK_DLL void FBSetStoreableCustomMaterialRegistered();
FBSDK_DLL bool FBGetStoreableCustomMaterialRegistered();

/** \def FBSetStoreableCustomTextureRegistered
*	Set custom texture have been defined.
*	For internal use only.
*/
FBSDK_DLL void FBSetStoreableCustomTextureRegistered();
FBSDK_DLL bool FBGetStoreableCustomTextureRegistered();

FBSDK_DLL bool FBObject_Register  ( const char * pGroupName,const char * pEntryName,const char * pDescription, kObjectCreatorFnc pCreatorFnc, bool pIsMultipleAllowed,const char * pIconFilename);
FBSDK_DLL bool FBObject_Unregister( const char * pGroupName,const char * pEntryName, int nth=0 );

/** A set of functions to query the registration table.
*/
FBSDK_DLL int			FBObject_GetGroupCount          ();
FBSDK_DLL const char*	FBObject_GetGroupName           ( int pGroupIndex );
FBSDK_DLL int			FBObject_GetEntryCount          ( int pGroupIndex );
FBSDK_DLL const char*	FBObject_GetEntryName           ( int pGroupIndex, int pIndex );
FBSDK_DLL const char*	FBObject_GetEntryDescription    ( int pGroupIndex, int pIndex, int nth = 0 );
FBSDK_DLL const char*	FBObject_GetEntryDLLName        ( int pGroupIndex, int pIndex, int nth = 0 );
FBSDK_DLL const char*	FBObject_GetIconName            ( int pGroupIndex, int pIndex, int nth = 0 );
FBSDK_DLL bool			FBObject_GetMultiplicity        ( int pGroupIndex, int pIndex, int nth = 0 );

/** FBCreateObject
*	\param pGroupName	Set the name of the Group.
*	\param pEntryName	Set the name of the Entry.
*	\param pName		Set the name of the Object to create.
*	\param pData		Data to pass to object creator function.
*	\param nth			Set the occurrence of the object to remove.
*/
FBSDK_DLL FBComponent* FBCreateObject( const char* pGroupName, const char* pEntryName, const char* pName, void* pData = NULL, int nth = 0 );

/** FBUnregisterObject
*	\param pGroupName	Set the Name of the Group from which unregister an object.
*	\param pEntryName	Set the name of the Object to unregister.
*	\param nth			Set the occurrence of the object to remove.
*/
inline  bool FBUnregisterObject( const char * pGroupName, const char * pEntryName, int nth=0 ) { return FBObject_Unregister( pGroupName,pEntryName,nth ); }

/** \def FBRegisterObject
*	Event registration/un-registration.
*	For internal use only.
*/
#define FBRegisterObject( LocalId,Path,Name,Description,Constructor,IsMultipleAllowed,IconFilename ) \
	static int __R##LocalId = FBObject_Register( Path,Name,Description,Constructor,IsMultipleAllowed,IconFilename )

/** HISender*/
typedef HIRegister	HISender;

/** HKEvent*/
typedef HKEventBase HKEvent;

/** FBCallback 
*	\param	pSender	Set the sender
*	\param	pEvent	Set the event
*/
typedef void (ICallback::*FBCallback)(HISender pSender,HKEvent pEvent);

FBSDK_DLL int FBRegister_ClassId(const char* pClassName);

/** \def FBDeclareUserObject
*	Event registration/un-registration.
*	For internal use only.
*/
#define FBDeclareUserObject(ClassName)\
public:\
	static int		ClassId;\
	virtual int		GetUserClassId();\
	virtual const char*	FbxGetObjectSubType() override;\
    /** Return to default scope (private)*/\
private:

////////////////////////////////////////////////////////////////////////////////////
// FBComponent
////////////////////////////////////////////////////////////////////////////////////
#ifdef new
	/** \def RENEW
	*	For internal use only.
	*/
	#define RENEW new
	#undef new
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBSceneList
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBPropertyListComponent );
__FB_FORWARD( FBComponent );
FB_DEFINE_LIST( FBSDK_DLL, Component );

FB_FORWARD( FBFolder );
FB_DEFINE_COMPONENT( FBSDK_DLL, Folder );

//! Available flags for any component
enum FBObjectFlag
{
	kFBFlagSelectable           = (1 << 0),		//!< Can be selected. If disabled, representation of the object, like in the navigator, can still be selected and can still affect the original object.
	kFBFlagDeletable            = (1 << 1),		//!< Can be deleted
	kFBFlagSavable              = (1 << 2),		//!< Can be saved
	kFBFlagVisible              = (1 << 3),		//!< Can be visible. If disabled, the object will still be available in the navigator, it is only hidden in the viewer.
	kFBFlagClonable             = (1 << 4),		//!< Can be cloned. If disabled, the "Duplicate" option will be removed in the contextual menu.
	kFBFlagSystem               = (1 << 5),		//!< Created from System (not from user)
	kFBFlagNewable              = (1 << 6),		//!< Deleted on File->New
	kFBFlagRenamable            = (1 << 7),		//!< Can be renamed
	kFBFlagMergeable            = (1 << 8),		//!< Can be merged
	kFBFlagBrowsable            = (1 << 9),		//!< Visible in the Scene Navigator/Schematic View/Property View/Model View. If disabled, the object representation in the navigator will not be visible. In the Schematic View, system object are not shown and other objects will still be visible, but a red X will be drawn on them. It is not possible to select the object in the Schematic View. After disabling that flag of a selected object, it will still be selected to allow a script based on selection to work. It will then be possible for a user to deselect the object, but it will not be possible to select it.
	kFBFlagParentable           = (1 << 10),    //!< Object (model) can be "parented". Used by the apply manager contextual menu.
    kFBFlagDetachable           = (1 << 11),	//!< Object can be "detached". Used by the apply manager contextual menu.
	kFBFlagUndoable             = (1 << 12),	//!< Object can undo its actions and states, in a global Undo Stack.
	kFBFlagUndoableSeparately   = (1 << 13),	//!< Object which has kFlagUndoableSeparately flag turned on will have a separate Undo Stack.
    kFBFlagKeyable              = (1 << 14),	//!< Object can Key his property. (System Camera can't) 
	kFBFlagAllocated            = (1 << 15),	//!< Object is allocated, so it must call 'delete this' on destroy.
	kFBFlagStory                = (1 << 16),	//!< Object created/used by the Story tool. Useful flag for filtering Story objects.
	kFBFlagStorable6            = (1 << 17),	//!< System/Obsolete.
    kFBFlagStorableData6        = (1 << 18),	//!< System/Obsolete.
    kFBFlagStorableBlindData    = (1 << 19),    //!< Used in FBX SDK native IO
    kFBFlagStorableBlindDataForceBinary = (1 << 20), //! < Used in FBX SDK native IO, force bindary format for the bindary data. 
    kFBFlagUniqueName           = (1 << 21),	//!< Object unique name can be added to the unique name list (at first, only RootNode have this flag)
    kFBFlagNotSelectableNameSpace = (1 << 22),	//!< The entity will not add the namespace of the object to his list of all the namespaces of the scene.   
    kFBFlagNamespaceEditable      = (1 << 23),  //!< Allow editing on the namespace objects. If disabled, the "Add/Remove Namespace..." option is removed from the contextual menu.
};

//! Available lifetime status for any component
enum FBObjectStatus {
	kFBStatusCreating	= (1 << 0),	//!< Object is in creation operations.
	kFBStatusStoring	= (1 << 1),	//!< Object is in storing operations.
	kFBStatusRetrieving	= (1 << 2),	//!< Object is in retrieving operations.
	kFBStatusMerging	= (1 << 3),	//!< Object is in Merging operations.
	kFBStatusDestroying	= (1 << 4),	//!< Object is in destruction operations.
	kFBStatusClearing	= (1 << 5), //!< Object is in clearing operations (File new).
};

//! Namespace flags 
enum FBNamespaceAction
{
    kFBConcatNamespace,                     //!< Use to add a namespace name to object.
    kFBReplaceNamespace,                    //!< Use to replace a define namespace
    kFBRemoveAllNamespace                   //!< Remove all the namespace name
};

FB_DEFINE_ENUM(FBSDK_DLL, ConnectionType);
FB_DEFINE_ENUM(FBSDK_DLL, ConnectionAction);
FB_DEFINE_ENUM(FBSDK_DLL, ObjectFlag);

/** \b PropertyList: Component.
*/
class FBSDK_DLL FBPropertyListComponentBase : public FBPropertyBasicList
{
  protected:
	//! Class Id.
	int		mClassId;
	//! mParent.
	bool mParents;
  public:
	//! Constructor.
	FBPropertyListComponentBase();
	/**	Add a component to the list.
	*	\param	pItem	Component to add to list.
	*	\return Number of components in list after operation.
	*/
	virtual int Add( FBComponent* pItem );
	/**	Remove the component at \e pIndex from list.
	*	\param	pIndex	Index of Component to remove.
	*/
    virtual void RemoveAt( int pIndex );
	/**	Get the Component at \e pIndex.
	*	\param	pIndex	Index of Component to get a handle on.
	*	\return Component at \e pIndex.
	*/
	virtual FBComponent* GetAt(int pIndex)=0;
	/**	Get the Component at \e pIndex.
	*	\param	pIndex	Index of Component to get a handle on.
	*	\return Component at \e pIndex.
	*/
	FBComponent* operator[](int pIndex);
	/**	Get the Component count.
	*	\return Number of Components.
	*/
	virtual int GetCount();

	/**	Locate a property in the list.
	*	\param pItem Property to find in the list.
	*	\return Index where \e pItem can be found.
	*/
	virtual int Find( FBComponent* pItem );

	/**	Remove \e pItem from the list.
	*	\param pItem Property to remove from the list.
	*	\return Index where property was removed.
	*/
	virtual int Remove( FBComponent* pItem );

	// Internal functions
	void SetClassId( int pClassId );
	int  GetClassId( );
	void SetListOfParents( bool pListOfParents );
	bool GetIsListOfParents();

	/**	Get the property's type.
	*	\return	The property's type.
	*/
	virtual FBPropertyType GetPropertyType( ) override { return kFBPT_object; }
};
/** \b PropertyList: Concrete class for PropertyList of component
*/
class FBSDK_DLL FBPropertyListComponent : public FBPropertyListComponentBase
{
  public:
	/**	Get the Component at \e pIndex.
	*	\param	pIndex	Index of Component to get a handle on.
	*	\return Component at \e pIndex.
	*/
	virtual FBComponent* GetAt(int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListObject
////////////////////////////////////////////////////////////////////////////////////

FB_FORWARD( FBPropertyListObject );

/** \b List of scene objects.
*   This list is a more generic container often used as object properties.
*   The types of actual object that it can contain can be specialized.
*/
class FBSDK_DLL FBPropertyListObject : public FBPropertyListComponent
{
  public:
    //! Constructor.
    FBPropertyListObject();

    /** Get the object count.
    *   \return Number of Objects.
    */
    virtual int GetCount();

    //@{
    /** Get the object at \e pIndex.
    *   \param  pIndex  Index of the object to query.
    *   \return The object at \e pIndex.
    */
    virtual FBComponent* operator[]( int pIndex );
    virtual FBComponent* GetAt( int pIndex );
    //@}

    /** Add an object at the end of the list.
    *   \param  pObject Object to add to list.
    *   \return Index of the newly added object. A return value of '-1' indicated the the object has not been added.
    */
    virtual int Add( FBComponent* pObject );

    /** Replace an existing entry at a specific index.
    *   \param  pIndex    Index of the object that should be replaced.
    *   \param  pObject   Object to insert in the list.
    *   \return Index of the replaced object. A return value of '-1' indicated the the object has not been replaced.
    */
    virtual int SetAt(int pIndex, FBComponent* pObject);

    /** Remove an object at a specific index.
    *   \param  pIndex    Index of the object that should be removed.
    */
    virtual void RemoveAt( int pIndex );

    /** Insert an object at a specific index.
    *   \param  pIndex    Index where the object should be inserted.
    *   \param  pObject   Object to insert in the list.
    *   \return Index of the inserted object. A return value of '-1' indicated the the object has not been inserted.
    */
    virtual int InsertAt(int pIndex, FBComponent* pObject);

    /** Clears the content of the list.
    */
    virtual void Clear();

	/**	Set if the connection is single or multiple.
	*	\param pSingleConnect set to true for only one connection allowed.
	*/
	virtual void SetSingleConnect(bool pSingleConnect);

	/**	Get if the connection support only one connection.
	*	\return true is the connection support only one connection.
	*/
	virtual int GetSingleConnect();

	/**	Set the filter connections to the property list (UI only).
	*	\param pInternalClassId used for filtering connections; should be taken from object::GetInternalClassId() (-1 equal no filter).
	*/
	void SetFilter(int pInternalClassId);

	/**	Get the filter class Id for the property list (UI only).
	*	\return MBClassId used for filtering connections (-1 equal no filter).
	*/
	int GetFilter();

private:
    //@{
    /** Restricted methods.
    *   Voluntarily making the copy constructor and assignment
    *   operator unavailable.
    */
    FBPropertyListObject( const FBPropertyListObject& );
    const FBPropertyListObject& operator =( const FBPropertyListObject& );
    //@}
};

__FB_FORWARD( FBNamespace );
__FB_FORWARD( FBFileReference );

/**	MotionBuilder SDK base class.
*   FBComponent defines common object characteristics, including creation and destruction methods.
*   It is used to encapsulate internal application objects so they can be exposed to the SDK.
*   It is also used as the base class to encapsulate objects with FBProperty data members and provides a scheme for property management. 
    You cannot instantiate FBProperty objects. To reference a property, use an instance of an FBComponent object. The methods FBComponent::PropertyCreate
	and FBComponent::PropertyRemove can be used to modify an object's properties. 
*   Basic operators are overloaded in FBComponent. The constructor and destructor are created and defined with macros in the header files.
*   Objects inheriting from FBComponent must define FBComponent::FBCreate(), and FBComponent::FBDestroy().
    All memory management issues for the component should also be addressed here.
    Destroy an object with FBDelete().
*   The code sample FBComponent.py shows how to get a handle on a scene object via its name. 
*/
class FBSDK_DLL FBComponent : public FBPlug
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	//! Handle on DataFBComponent.
	DataFBComponent* mLocalPtr;					
protected:
	//! Name of the component.
	FBString		mName;
#endif
    
public:
	//! Contains the Type information of the object.
	static int		TypeInfo;

	/** \fn GetInternalClassId()
	*	\return Internal class Id
	*/
	static int GetInternalClassId();

	/** Constructor
	*	\param pObject  Object to copy component from (default is NULL).
	*/
	FBComponent( HIObject pObject );		

	//! Destructor.
	virtual ~FBComponent();								

	/** Open Reality Creation function.
	*	\return Outcome of creation (true/false).
	*/
	virtual bool FBCreate();

	//! Open Reality destruction function.
	virtual void FBDestroy();

	//! Open Reality deletion function.
	virtual void FBDelete() override;

  	//! Assign component to an internal pointer.
	virtual bool SetHIObject(HIObject pObject, bool pSDKComponent) override;

	/** Add a property to the component's property manager.
	*	\param pProperty The property to add to the property manager.
	*	\return Index in the property array where property was inserted.
	*/
	virtual int	PropertyAdd( FBProperty* pProperty );

	/** Add a reference property to the component's property manager.
	*	\param pReferenceProperty The property to from an other object to add a reference to (property cannot be a custom ORSDK property).
	*	\return True if the reference property could be added.
	*/
	bool PropertyAddReferenceProperty( FBProperty* pReferenceProperty );

	/** Remove a Property from the component's Property manager.
	*	If the property was dynamically allocated, it is deleted.
	*	\param pProperty The property to remove from the property manager.
	*/
	void PropertyRemove( FBProperty* pProperty );

    /** Get list of properties which have been modified since last loading. 
	*	\param pPropList property list to hold the modified properties. 
	*	\param	pModificationFlags	type of modification to query.
    */
    void PropertyGetModifiedList(FBArrayTemplate<FBProperty*>& pPropList, FBPlugModificationFlag pModificationFlags);

	/** Create user or dynamic property.
	*	\param pName The name of the property.
	*	\param pType Type of the property. See enum FBPropertyType.
	*	\param pDataType DataType of the property.
	*	\param pAnimatable To specify if the property can be animated.
	*	\param pIsUser To specify if the property is available as a custom property or dynamic and attached to the object.
	*	\param pReferenceSource Specifies the property that a reference refers to.
	*/
	FBProperty* PropertyCreate( const char* pName, FBPropertyType pType, const char * pDataType, bool pAnimatable, bool pIsUser = false, FBProperty* pReferenceSource = NULL  );

	/** Get all Object Flags (concatenated).
	*	\return	Get all object flags in one call. Flags can be concatenated.
	*/
	FBObjectFlag GetObjectFlags();

	/** SetObjectFlags
	*	\param	pFlags	Set flag values. Note: this function overwrites all flags with those passed in parameter.
	*/
	void SetObjectFlags(FBObjectFlag pFlags);

	/** Check whether a specific object flag is enabled.
	*	\param	pFlags	Flags to check if they are present.
	*	\return			True if all flags in pFlags are enabled.
	*/
	bool HasObjectFlags(FBObjectFlag pFlags);

	/** Enable a specific Object Flags
	*	\param	pFlags	Flags to enable.
	*/
	void EnableObjectFlags(FBObjectFlag pFlags);

	/** Disable a specific Object Flags
	*	\param	pFlags	Flags to disable.
	*/
	void DisableObjectFlags(FBObjectFlag pFlags);

	/** Enable/Disable a specific Object Status.
	*	\param	pStatus	Status to change.
	*	\param	pValue	Value to change the status to.
	*/
	void SetObjectStatus(FBObjectStatus pStatus, bool pValue);

	/** Check to see if an object status is enabled.
	*	\param	pStatus	Status to query.
	*/
	bool GetObjectStatus(FBObjectStatus pStatus);

    /** ProcessNamespaceHierarchy.
    *   New Namespace name should only contains alphabet, digit and '_', Can't start with digit.
    *   This recursive function goes through the whole hierarchy (children) to add/replace the prefix.
    *   If you need to work on a single object, use the ProcessObjectPrefix function.
    *   \param  pNamespaceAction        Which operation to do on the hierarchy (children).
    *   \param  pNamespaceName          The Namespace name on Add/Delete or the prefix to replace in case of replace.
    *   \param  pReplaceTo              The new Namespace Name or NULL in case of add or delete.
    *   \param  pAddRight               Whether to add the namespace on right-most or left-most side or other namespace.
    *   \return                         return true if process successful.
    */
    bool ProcessNamespaceHierarchy( FBNamespaceAction pNamespaceAction, const char* pNamespaceName, const char* pReplaceTo=NULL, bool pAddRight=true );

    /** ProcessObjectNamespace.
    *   New Namespace name should only contains alphabet, digit and '_', Can't start with digit.
    *   This function is the same as ProcessNamespaceHierarchy except that it applies only on the current object and not
    *   to the object's children.
    *   \param  pNamespaceAction        Which operation to do on the hierarchy (children).
    *   \param  pNamespaceName          The Namespace name on Add/Delete or the prefix to replace in case of replace.
    *   \param  pReplaceTo              The new Namespace Name or NULL in case of add or delete.
    *   \param  pAddRight               Whether to add the namespace on right-most or left-most side or other namespace.
    *   \return                         return true if process successful.
    */
    bool ProcessObjectNamespace ( FBNamespaceAction pNamespaceAction, const char* pNamespaceName, const char* pReplaceTo=NULL, bool pAddRight=true );

	/** Get the class name.
	*	\return The class name (i.e. "FBComponent").
	*/
	virtual const char* ClassName() override;

    /** Use the custom property viewSet or not. 
    *    To have custom property view for custom subclass, modification bin/config/propertyview.fbx is required. 
    *   \return False if to use internal corresponding object's viewSet of the parent class. 
    */
    virtual bool UseCustomPropertyViewSet() const { return true; }

    /** Get the full name.
     *  \return the full name of the component.
     */
    const char* GetFullName( void );

    /** Set the owner Namespace object.
    */
    void SetOwnerNamespace(FBNamespace* pOwnerNSObj);

    /** Get the owner Namespace object.
     *  \return the owner Namespace object
     */
    FBNamespace* GetOwnerNamespace( void );
    

    /** Get the owner FileReference object
     *  \return the owner FileReference object
     */
    FBFileReference* GetOwnerFileReference( void );

	/** HardSelect.
	*	Selects the object, and emits a hard select event for UI update notification.
	*/
	void HardSelect();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
	//@{
	// Overloaded allocation/destruction operator.
	void *operator new( size_t stAllocateBlock );
	void operator delete( void *pvMem );

	void *operator new( size_t stAllocateBlock,	int blockType, const char *filename, int linenumber  );
#if	_MSC_VER >= 1200
	void operator delete( void *pvMem, int blockType, const char *filename, int linenumber  );
#endif
	//@}

	//@{
	// Used to manage sub property events.
    void RegisterPropertyEvent(FBPropertyEvent* pPropertyEvent);
    void UnregisterPropertyEvent(FBPropertyEvent* pPropertyEvent);
    void InvalidatePropertyEventsParents();
	//@}
#endif

    FBPropertyManager		PropertyList;	//!< <b>Read Only Property:</b> Manages all of the properties for the component.
	FBPropertyListComponent	Components;		//!< <b>List:</b> List of components.
	FBPropertyListComponent	Parents;		//!< <b>List:</b> Parents.
	FBPropertyBool			Selected;		//!< <b>Read Write Property:</b> Selected property.
	FBPropertyString		Name;			//!< <b>Read Write Property:</b> Unique name of object.
    FBPropertyString		LongName;		//!< <b>Read Write Property:</b> Name and namespace for object.    

#if !defined(K_NO_FOLDER)
	FBPropertyFolder		Folder;			//!< <b>Read Write Property:</b> The folder that contain this component.
#endif

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    IObject_Declare(K_IMPLEMENTATION);
    ICallback_Declare(K_IMPLEMENTATION);
#endif

	/** Returns true if object is of type TypeId.
	*	\param pTypeId TypeId to compare object to.
	*	\return Result of the comparison.
	*/
	virtual bool Is( int pTypeId );
    virtual int GetTypeId();

	static void FBComponentSetName( FBComponent* pObject, const char *pName );
	static const char* FBComponentGetName( FBComponent* pObject );

    static void FBComponentSetLongName( FBComponent* pObject, const char *pName );
    static const char* FBComponentGetLongName( FBComponent* pObject );

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	/** Internal Dummy Object for non KObject Components.*/
	KObject*	mDummyObject;
    void KObjectEvent(HIRegister pView, HKEventBase pEvent);
#endif
};

//! Equivalent to FBComponent for gradual transition
typedef FBComponent FBObject;

/**	Cast the SDK object using it's IObject interface into the proper class.
*	\param	pObject			Object to get SDK object for.
*	\param	pAutoCreate		Create object if it doesn't exist? (default = false)
*	\return	SDK object for \p pObject.
*/
template<class T> inline T* FBCast(FBObject* pObject, bool pAutoCreate = false)
{
    HIObject lObject = pObject ? FBGetFBObject(pObject->GetHIObject(), pAutoCreate) : NULL;
    // Should also validate type but not available for now
    return (T*)lObject;
}

/**	FBFindObjectsByName.
*   This function will query the system for objects fulfilling a particular name pattern
*	\param	pNamePattern	        Indicate the name pattern to search. This pattern can contain any amount of *. (ex: *tr*mod*scene )
*	\param	pList                 List that contains the objects
*	\param	pIncludeNamespace     Does the search use the complete name (with namespace)
*   \param  pModelsOnly           Is the search on models or all types of objects
*/
FBSDK_DLL void FBFindObjectsByName( const char* pNamePattern, FBComponentList& pList, bool pIncludeNamespace = true, bool pModelsOnly = false );

/**  FBFindObjectByFullName.
*    This function will query the system for an object with its FullName matching.
*    Full name is "GroupName::NameSpaceName:ObjectName".
*    Label name is "NameSpaceName:ObjectName". also known as "PrefixName::ObjectName"
*    \param	pObjectFullName	Full Name of object to search for. Specify it with schema like "GroupName::NameSpaceName:ObjectName",or "GroupName::ObjectName" if no NameSpaceName.
*    \return	A handle onto the object with Full name matching pObjectFullName, returns 
*               NULL if no object was found by the search.
*/
FBSDK_DLL FBComponent* FBFindObjectByFullName( const char* pObjectFullName );

/** FBDeleteObjectsByName.
*   This function will query the system for objects fulfilling a particular name pattern and delete them. specify 
*   a namespace preferred, delete all objects with the group name without specified a namespace specified may 
*   lead to inconsistent in scene.
*   Wrap multiple calls to FBDeleteObjectsByName() inside pair of FBPreventUIUpdateBegin() / FBPreventUIUpdateEnd() 
*   could improve application's performance.
*   
*   \param pNamePattern          if not NULL, indicate the name pattern to search. This pattern can contain any amount of *. (ex: *tr*mod*scene ). 
*                                if is NULL or Empty string, * will be used for match all.
*   \param pNameSpace            if not NULL, the objects must be inside the given namespace. 
*   \param pGroupName            if not NULL, indicate the object group name (type).
*   \return                      the count of objects found and deleted. 
*/
FBSDK_DLL int FBDeleteObjectsByName( const char* pNamePattern, const char* pNameSpace = NULL, const char* pGroupName = NULL);

#ifdef RENEW
	#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
	#undef RENEW
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBEvent
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEvent );

//! Base Event class.
class FBSDK_DLL FBEvent
{
public:
	/** Constructor.
	*	Receives an object of type HKEvent that the 
	*	corresponding callback will receive as a parameter. 
	*	\param pEvent  Internal event to obtain information from.
	*/
	FBEvent( HKEvent pEvent );

	FBPropertyInt	Type;				//!< <b>Read Only Property:</b> Type of event.
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
	/** Internal Event pointer.*/
	HKEventBase mEvent;
public:
	/** Empty function to avoid creating property container object.*/
	void PropertyAdd( FBProperty* ) {};
#endif
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventConnectionNotify
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventConnectionNotify );

//! Connection notify event class.
class FBSDK_DLL FBEventConnectionNotify : public FBEvent
{
public:
	/**	Constructor.
	*	\param pEvent	 Base event (internal) to obtain information from.
	*/
	FBEventConnectionNotify(HKEventBase pEvent);

	FBPropertyConnectionAction	Action;			//!< <b>Read Only Property:</b> Connection's action performed.
	FBPropertyInt				SrcIndex;		//!< <b>Read Only Property:</b> Index of the source in the destination component.
	FBPropertyConnectionType	ConnectionType;	//!< <b>Read Only Property:</b> Connection's type.
	FBPropertyPlug				SrcPlug;		//!< <b>Read Only Property:</b> The source plug involved in the action.
	FBPropertyPlug				DstPlug;		//!< <b>Read Only Property:</b> The destination plug involved in the action.
	FBPropertyPlug				NewPlug;		//!< <b>Read Only Property:</b> New plug created by the action. (Mostly used by merge/replace)
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventConnectionDataNotify
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventConnectionDataNotify );

//! Connection notify event class.
class FBSDK_DLL FBEventConnectionDataNotify : public FBEvent
{
public:
	/**	Constructor.
	*	\param pEvent	 Base event (internal) to obtain information from.
	*/
	FBEventConnectionDataNotify(HKEventBase pEvent);

	FBPropertyConnectionAction	Action;			//!< <b>Read Only Property:</b> Connection's action performed.
	FBPropertyPlug				Plug;			//!< <b>Read Only Property:</b> The plug involved in the action.
	void*						GetData();		//!< Available data pointer
	void*						GetOldData();	//!< Last available data pointer
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventConnectionStateNotify
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventConnectionStateNotify );

//! Connection notify event class.
class FBSDK_DLL FBEventConnectionStateNotify : public FBEvent
{
public:
	/**	Constructor.
	*	\param pEvent	 Base event (internal) to obtain information from.
	*/
	FBEventConnectionStateNotify(HKEventBase pEvent);

	FBPropertyConnectionAction	Action;			//!< <b>Read Only Property:</b> Connection's action performed.
	FBPropertyPlug				Plug;			//!< <b>Read Only Property:</b> The plug involved in the action.
	void*						GetData();		//!< Available data pointer
	void*						GetOldData();	//!< Last available data pointer
};

////////////////////////////////////////////////////////////////////////////////////
// __FB_FORWARD( FBEventConnectionKeyingNotify );								  //
////////////////////////////////////////////////////////////////////////////////////
 __FB_FORWARD( FBEventConnectionKeyingNotify );
 
class FBSDK_DLL FBEventConnectionKeyingNotify : public FBEvent
{
public:
	/**	Constructor.
	*	\param pEvent	 Base event (internal) to obtain information from.
	*/
	FBEventConnectionKeyingNotify(HKEventBase pEvent);

	/**	returns keying action
	*	
	*	
	*	\return keying action
	*/
	FBConnectionAction  GetAction( void );

	/**	returns FBPlug that the keying action takes effect upon.
	*	
	*	
	*	\return FBPlug that the keying action takes effect upon.
	*/
	FBPlug*				GetPlug( void );
	/**	returns FBProperty that the keying action takes effect upon.
	*	
	*	
	*	\return FBProperty that the keying action takes effect upon.
	*/
	FBPlug*				GetProperty( void );
	/**	returns data which is related to the keying action.
	*	
	*	
	*	\return data which is related to the keying action.
	*/
	void*				GetData( void );
};


////////////////////////////////////////////////////////////////////////////////////
// FBLibrary
////////////////////////////////////////////////////////////////////////////////////
/** Library class for DLL registration.
*	Manages the DLL control via a global FBLibrary object. For each DLL to be created, an implementation
*	of the FBLibrary functions will be necessary, see the sample code to see an example implementation.
*/
class FBSDK_DLL FBLibraryBase : public ICallback
{
public:
	FBLibraryBase();
	virtual ~FBLibraryBase();
    IObject_Declare(K_IMPLEMENTATION);
    ICallback_Declare(K_IMPLEMENTATION);

	/** Initialize library.
	*	Initial load of DLL into memory.
	*	\return \b true if successful.
	*/
	virtual bool LibInit();

	/**	Open library.
	*	Library is opened to peruse the exported symbols.
	*	\return \b true if successful.
	*/
	virtual bool LibOpen();

	/**	Is library ready?
	*	Ready the library to begin accessing the functions. Any on library
	*	activation code should be placed in this function.
	*	\return \b true if successful.
	*/
	virtual bool LibReady();

	/**	Close library.
	*	\return \b true if successful.
	*/
	virtual bool LibClose();

	/**	Release library.
	*	\return \b true if successful.
	*/
	virtual bool LibRelease();
						//!Library Open.
	KGlobalNamedEvent  *mLibrary_Open,		//!Library Ready. 
					   *mLibrary_Ready,	//!Library Close. 
					   *mLibrary_Close,	//!Library Release. 
					   *mLibrary_Release;	

	void Library_OpenHandler(HIRegister pCaller,HKEventBase pEvent);
	void Library_ReadyHandler(HIRegister pCaller,HKEventBase pEvent);
	void Library_CloseHandler(HIRegister pCaller,HKEventBase pEvent);
	void Library_ReleaseHandler(HIRegister pCaller,HKEventBase pEvent);
};

////////////////////////////////////////////////////////////////////////////////////
// FBLibrary
////////////////////////////////////////////////////////////////////////////////////
/** Library class for DLL registration.
*	Manages the DLL control via a global FBLibrary object. For each DLL to be created, an implementation
*	of the FBLibrary functions will be necessary, see the sample code to see an example implementation.
*/
class FBLibrary : public FBLibraryBase
{
public:
	/** Initialize library.
	*	Initial load of DLL into memory.
	*	\return \b true if successful.
	*/
	virtual bool LibInit();

	/**	Open library.
	*	Library is opened to peruse the exported symbols.
	*	\return \b true if successful.
	*/
	virtual bool LibOpen();

	/**	Is library ready?
	*	Ready the library to begin accessing the functions. Any on library
	*	activation code should be placed in this function.
	*	\return \b true if successful.
	*/
	virtual bool LibReady();

	/**	Close library.
	*	\return \b true if successful.
	*/
	virtual bool LibClose();

	/**	Release library.
	*	\return \b true if successful.
	*/
	virtual bool LibRelease();
};

/** Declare the library for the application.
*	Creates the FBLibrary object and generic interface functions for DLL access.
*/
#if defined(K_NODLL)
	#define FBLibraryDeclare( LibName ) \
	FB_DLL_INIT( LibName, Operation )				\
	{												\
		switch( Operation )							\
		{											\
			case kFBDllLoad:						\
			{										\

#else
	#define FBLibraryDeclare( LibName ) \
	static FBLibrary LibName##GlobalFBLibrary; \
	extern "C" {	\
		K_DLLEXPORT bool LIBRARY_INIT(HIError /*Error*/) \
		{ \
			FB_EXT_INIT( LibName ); if (LibName##GlobalFBLibrary.LibInit()) return true; return false; \
		} \
	} \
	FB_DLL_INIT( LibName, Operation )				\
	{												\
		switch( Operation )							\
		{											\
			case kFBDllLoad:						\
			{				
#endif

/**	FBLibraryModule 
*	Define a module registration call.
*	\param Name		Module to register.
*/
#define FBLibraryModule(Name)					\
	void FBModule##Name()

/**	FBLibraryRegister 
*	Declare the module's registration functions.
*	\param ClassName	Class to declare registration functions for.
*/
#define FBLibraryRegister( ClassName )			\
	extern void FBModule##ClassName( );			\
	FBModule##ClassName( );

/** FBLibraryRegisterStorable 
*	Declare the module's registration functions for storable classes.
*	\param ClassName	Class to declare registration functions for.
*/
#define FBLibraryRegisterStorable( ClassName )			\
	extern void FBModule##ClassName##Storable( );			\
	FBModule##ClassName##Storable( );

/** FBLibraryRegisterElement 
*	Declare the module's registration functions for element classes.
*	\param ClassName	Class to declare registration functions for.
*/
#define FBLibraryRegisterElement( ClassName )			\
	extern void FBModule##ClassName##Element( );			\
	FBModule##ClassName##Element( );

/** FBLibraryRegisterShadingElement 
*	Declare the module's registration functions for shading element classes.
*	\param ClassName	Class to declare registration functions for.
*/
#define FBLibraryRegisterShadingElement( ClassName )			\
	extern void FBModule##ClassName##ShadingElement( );			\
	FBModule##ClassName##ShadingElement( );

//! Finish library declaration.
#define FBLibraryDeclareEnd						\
		}										\
		break;									\
        default:                                \
        break;                                  \
	}											\
}

// **********************************************************************************

/** FBCustomManagerImplementation
*	\param ThisComponent	Component to customize
*/
#define FBCustomManagerImplementation( ThisComponent )  \
    FBClassImplementation( ThisComponent )              \

/** FBRegisterCustomManager
*	\param ClassName	Class to declare registration functions for.
*/
#define FBRegisterCustomManager( ClassName )            \
    FBLibraryModule( ClassName )                        \
    {                                                   \
        static ClassName g##ClassName;                  \
        g##ClassName.FBCreate();                        \
        g##ClassName.RegisterManager();                 \
    }                                                   \

/** FBRegisterCustomDeclare
*	\param ClassName	Class to declare registration functions for.
*/
#define FBCustomManagerDeclare( ClassName )             \
FBClassDeclare( ClassName, FBCustomManager );           \
    public:                                             \
    ClassName() : FBCustomManager() { FBClassInit; }    \
    /** Return to default scope (private)*/             \
    private:                                            


////////////////////////////////////////////////////////////////////////////////////
// FBCustomManager
////////////////////////////////////////////////////////////////////////////////////

__FB_FORWARD( FBCustomManager );

/** Custom manager class for user controlled observer objects.
*	This class is used to create a singleton object that has a lifetime similar to
*   the one of the application. Meaning that it is created early in the
*   initialization of the application and survives across File->Open and File->New,
*   being destroyed upon shutdown of the application.
*
*   The manager object is notified by the application at certain points in time,
*   such as when the scene is cleared or the application is shutting down.
*
*   Manager objects are not saved or mentioned in the FBX files created. Its
*   behavior can be controlled via custom configuration files.
*/
class FBSDK_DLL FBCustomManager : public FBComponent {
    __FBClassDeclare( FBCustomManager, FBComponent );
public:
    /** Constructor.
    */
    FBCustomManager();

    /** Instantiating the manager is not enough. It also need to be registered in
    *   the list of all managers. This call is done automatically via the use
    *   of the macro 'FBRegisterCustomManager'.
    */
    void RegisterManager();

    /** Open Reality Creation function.
    *   \return Outcome of creation (true/false).
    */
    virtual bool FBCreate();

    /** This method is called upon the loading of the plugin, right after
    *   FBCreate is called. Since it happens very early in the lifespan of
    *   the application, not all the initialization is done. So access to
    *   system objects is very limited.
    *
    */
    virtual bool     Init()   ;

    /** Now all the basic initialization is done, but we have yet to load any
    *   FBX files or even create the GUI.
    *   /warning if Init does not return true, the 'Close()' method will
    *   not be called.
    */
    virtual bool     Open()   ;

    /** This callback is used when the scene is cleared. This may be from a new
    *   file being loaded (not appended to the current one), a File->New or the
    *   application being shutdown.
    */
    virtual bool     Clear()  ;

    /** The application is shutting down. Time to cleanup anything that references
    *   system resources.
    */
    virtual bool     Close()  ;

};


#ifdef FBSDKUseNamespace
	}
#endif

#endif
