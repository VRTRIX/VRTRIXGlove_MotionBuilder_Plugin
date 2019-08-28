#ifndef pyfbcomponent_h__
#define pyfbcomponent_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

// =======================================================================================
// FBComponent
// =======================================================================================
void FBComponent_Init();

class PYSDK_DLL FBComponent_Wrapper : public FBPlug_Wrapper {
public:
	FBComponent* mFBComponent;
public:
	FBComponent_Wrapper( FBComponent* pFBComponent );
	virtual ~FBComponent_Wrapper( ) { }
	const char* ClassName() { return mFBComponent->ClassName(  ); }
	void DisableObjectFlags(FBObjectFlag pFlags) { mFBComponent->DisableObjectFlags( pFlags ); }
	void EnableObjectFlags(FBObjectFlag pFlags) { mFBComponent->EnableObjectFlags( pFlags ); }
	bool FBCreate() { return mFBComponent->FBCreate(  ); }
	void FBDelete() { mFBComponent->FBDelete(  ); }
	void FBDestroy() { mFBComponent->FBDestroy(  ); }
	FBObjectFlag GetObjectFlags() { return mFBComponent->GetObjectFlags(  ); }
	bool GetObjectStatus(FBObjectStatus pStatus) { return mFBComponent->GetObjectStatus( pStatus ); }
	bool HasObjectFlags(FBObjectFlag pFlags) { return mFBComponent->HasObjectFlags( pFlags ); }
	bool Is(int pTypeId) { return mFBComponent->Is( pTypeId ); }
	bool ProcessNamespaceHierarchy(FBNamespaceAction pNamespaceAction, const char * pNamespaceName, const char * pReplaceTo = NULL, bool pAddRight = true) { return mFBComponent->ProcessNamespaceHierarchy( pNamespaceAction, pNamespaceName, pReplaceTo, pAddRight ); }
	bool ProcessObjectNamespace(FBNamespaceAction pNamespaceAction, const char * pNamespaceName, const char * pReplaceTo = NULL, bool pAddRight = true) { return mFBComponent->ProcessObjectNamespace( pNamespaceAction, pNamespaceName, pReplaceTo, pAddRight ); }
	int PropertyAdd(FBProperty_Wrapper& pProperty) { return mFBComponent->PropertyAdd( pProperty.mFBProperty ); }
	bool PropertyAddReferenceProperty(FBProperty_Wrapper* pReferenceProperty) { return pReferenceProperty ? mFBComponent->PropertyAddReferenceProperty( pReferenceProperty->mFBProperty ) : false; }
	object PropertyCreate(const char* pName, FBPropertyType pType, const char * pDataType, bool pAnimatable, bool pIsUser = false, FBProperty_Wrapper* pReferenceSource = NULL) { return FBProperty_Wrapper_Factory( mFBComponent->PropertyCreate( pName, pType, pDataType, pAnimatable, pIsUser, pReferenceSource ? pReferenceSource->mFBProperty:NULL )); }
	void PropertyRemove(FBProperty_Wrapper& Property) { mFBComponent->PropertyRemove( Property.mFBProperty ); }
	void SetObjectFlags(FBObjectFlag pFlags) { mFBComponent->SetObjectFlags( pFlags ); }
	void SetObjectStatus(FBObjectStatus pStatus, bool pValue) { mFBComponent->SetObjectStatus( pStatus,pValue ); }
	object GetComponents(  ) { return WrapFBObject<FBPropertyListComponent_Wrapper,FBPropertyListComponent>( &mFBComponent->Components ); }
	void SetName( const char* pName ) { mFBComponent->Name = pName; }
	const char* GetName(  ) { return mFBComponent->Name; }
    void SetLongName( const char* pName ) { mFBComponent->LongName = pName; }
    const char* GetLongName(  ) { return mFBComponent->LongName; }
    const char* GetFullName( void ) { return mFBComponent->GetFullName(); }
	object GetParents(  ) { return WrapFBObject<FBPropertyListComponent_Wrapper,FBPropertyListComponent>( &mFBComponent->Parents ); }
	FBPropertyManager_Wrapper* GetPropertyList(  ) { return FBPropertyManager_Wrapper_Factory( &mFBComponent->PropertyList ); }
	void SetSelected( bool pSelected ) { mFBComponent->Selected = pSelected; }
	bool GetSelected(  ) { return mFBComponent->Selected; }
	void HardSelect( ) { mFBComponent->HardSelect(); }
    void SetOwnerNamespace( FBNamespace_Wrapper& pOwnerNamespace );
    object GetOwnerNamespace( void );
    object GetOwnerFileReference( void );

    FBPropertyList_Wrapper* PropertyGetModifiedList(FBPlugModificationFlag pModificationFlags);

};
#endif // pyfbcomponent_h__