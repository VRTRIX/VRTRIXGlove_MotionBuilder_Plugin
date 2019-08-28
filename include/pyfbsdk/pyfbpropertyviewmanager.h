#ifndef pyfbpropertyviewmanager_h__
#define pyfbpropertyviewmanager_h__
/**************************************************************************
 Copyright 2012 Autodesk, Inc.
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

#include "pyfbpropertyviewdefinition.h"
#include "pyfbpropertyviewlist.h"

// =======================================================================================
// FBPropertyViewManager
// =======================================================================================
void FBPropertyViewManager_Init();

class PYSDK_DLL FBPropertyViewManager_Wrapper : public FBComponent_Wrapper {
public:
	FBPropertyViewManager* mFBPropertyViewManager;
public:
	FBPropertyViewManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBPropertyViewManager = (FBPropertyViewManager*)pFBComponent; }
    FBPropertyViewManager_Wrapper() : FBComponent_Wrapper( &FBPropertyViewManager::TheOne()) { mFBPropertyViewManager = (FBPropertyViewManager*)mFBComponent; }
    virtual ~FBPropertyViewManager_Wrapper() {};

	FBPropertyViewList_Wrapper* CreatePropertyList(FBComponent_Wrapper* pObject, FBPropertyViewType pViewType, const char* pName)
	{
		return pObject ? FBPropertyViewList_Wrapper_Factory(mFBPropertyViewManager->CreatePropertyList(pObject->mFBComponent, pViewType, pName)) : NULL;
	}

	bool RemovePropertyList(FBComponent_Wrapper* pObject, FBPropertyViewType pViewType, const char* pName)
	{
		return pObject ? mFBPropertyViewManager->RemovePropertyList(pObject->mFBComponent, pViewType, pName) : false;
	}

	FBPropertyViewList_Wrapper* FindPropertyList(FBComponent_Wrapper* pObject, FBPropertyViewType pViewType, const char* pName)
	{
		return pObject ? FBPropertyViewList_Wrapper_Factory(mFBPropertyViewManager->FindPropertyList(pObject->mFBComponent, pViewType, pName)) : NULL;
	}

	FBPropertyViewDefinition_Wrapper* AddPropertyView(const char* pClassName, const char* pPropertyName, const char* pHierarchy)
	{
		return FBPropertyViewDefinition_Wrapper_Factory(mFBPropertyViewManager->AddPropertyView(pClassName,pPropertyName,pHierarchy));
	}

	bool RemovePropertyView(const char* pClassName, const char* pPropertyName)
	{
		return mFBPropertyViewManager->RemovePropertyView(pClassName,pPropertyName);
	}

	void HidePropertyView(const char* pClassName, const char* pPropertyName, bool pHide)
	{
		mFBPropertyViewManager->HidePropertyView(pClassName, pPropertyName, pHide);
	}

	void RefreshPropertyViews()
	{
		mFBPropertyViewManager->RefreshPropertyViews();
	}

};
#endif // pyfbpropertyviewmanager_h__

