#ifndef pyfbkeyinggroup_h__
#define pyfbkeyinggroup_h__
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
// FBKeyingGroup
// =======================================================================================
void FBKeyingGroup_Init();

class PYSDK_DLL FBKeyingGroup_Wrapper : public FBComponent_Wrapper {
public:
	FBKeyingGroup* mFBKeyingGroup;
public:
	FBKeyingGroup_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBKeyingGroup = (FBKeyingGroup*)pFBComponent; }
	FBKeyingGroup_Wrapper( const char* pName, FBKeyingGroupType pType ) : FBComponent_Wrapper( new FBKeyingGroup( pName, pType )) { mFBKeyingGroup = (FBKeyingGroup*)mFBComponent; }
	virtual ~FBKeyingGroup_Wrapper( ) {}
	void AddObjectDependency(FBComponent_Wrapper& pObj) { mFBKeyingGroup->AddObjectDependency( pObj.mFBComponent ); }
	void AddProperty(FBProperty_Wrapper& pProp) { mFBKeyingGroup->AddProperty( pProp.mFBProperty ); }
	void ClearAllItems() { mFBKeyingGroup->ClearAllItems(  ); }
	void FBDelete() { mFBKeyingGroup->FBDelete(  ); }
	int FindPropertyIndex(FBProperty_Wrapper& pProp) { return mFBKeyingGroup->FindPropertyIndex( pProp.mFBProperty ); }
	object GetCumulativeProperty(int pIndex, bool pStopAtVisible = false) { return FBProperty_Wrapper_Factory( mFBKeyingGroup->GetCumulativeProperty( pIndex, pStopAtVisible )); }
	int GetCumulativePropertyCount(bool pStopAtVisible = false) { return mFBKeyingGroup->GetCumulativePropertyCount( pStopAtVisible ); }
	object GetParentKeyingGroup(int pIndex) { return FBWrapperFactory::TheOne().WrapFBObject( mFBKeyingGroup->GetParentKeyingGroup( pIndex )); }
	int GetParentKeyingGroupCount() { return mFBKeyingGroup->GetParentKeyingGroupCount(  ); }
	object GetProperty(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBKeyingGroup_Wrapper::GetPropertyCount );
        return FBProperty_Wrapper_Factory( mFBKeyingGroup->GetProperty( pIndex )); 
    }
	int GetPropertyCount() { return mFBKeyingGroup->GetPropertyCount(  ); }
	object GetSubKeyingGroup(int pIndex)
    { 
        ValidateIndexAccess( pIndex, this, &FBKeyingGroup_Wrapper::GetSubKeyingGroupCount );
        return FBWrapperFactory::TheOne().WrapFBObject( mFBKeyingGroup->GetSubKeyingGroup( pIndex )); 
    }
	int GetSubKeyingGroupCount() { return mFBKeyingGroup->GetSubKeyingGroupCount(  ); }

    object GetSubObject(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBKeyingGroup_Wrapper::GetSubObjectCount );
        return FBWrapperFactory::TheOne().WrapFBObject( mFBKeyingGroup->GetSubObject( pIndex )); 
    }
	int GetSubObjectCount() { return mFBKeyingGroup->GetSubObjectCount(  ); }
	bool IsObjectDependency(FBComponent_Wrapper& pObj) { return mFBKeyingGroup->IsObjectDependency( pObj.mFBComponent ); }
	bool IsObjectDependencySelected() { return mFBKeyingGroup->IsObjectDependencySelected(  ); }
	void RemoveAllObjectDependency() { mFBKeyingGroup->RemoveAllObjectDependency(  ); }
	void RemoveAllProperties() { mFBKeyingGroup->RemoveAllProperties(  ); }
	void RemoveAllSubKeyingGroup() { mFBKeyingGroup->RemoveAllSubKeyingGroup(  ); }
	void RemoveObjectDependency(FBComponent_Wrapper& pObj) { mFBKeyingGroup->RemoveObjectDependency( pObj.mFBComponent ); }
	void RemoveProperty(FBProperty_Wrapper& pProp) { mFBKeyingGroup->RemoveProperty( pProp.mFBProperty ); }
	void SetActive(bool pActive) { mFBKeyingGroup->SetActive( pActive ); }
	void SetActiveAppend(bool pActive) { mFBKeyingGroup->SetActiveAppend( pActive ); }
	void SetEnabled(bool pEnable) { mFBKeyingGroup->SetEnabled( pEnable ); }
	void SetObjectType(FBComponent_Wrapper& pObj) { mFBKeyingGroup->SetObjectType( pObj.mFBComponent ); }
    static void DeselectAllAnimatableProperties() { FBKeyingGroup::DeselectAllAnimatableProperties(); }
};
#endif // pyfbkeyinggroup_h__