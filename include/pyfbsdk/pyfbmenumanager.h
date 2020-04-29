#ifndef pyfbmenumanager_h__
#define pyfbmenumanager_h__
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
// FBMenuManager
// =======================================================================================
void FBMenuManager_Init();

class PYSDK_DLL FBMenuManager_Wrapper : public FBComponent_Wrapper {
public:
	FBMenuManager* mFBMenuManager;
public:
	FBMenuManager_Wrapper( FBComponent* pFBComponent ) 
        : FBComponent_Wrapper( pFBComponent ) 
    { 
        mFBMenuManager = (FBMenuManager*)pFBComponent; 
    }
    FBMenuManager_Wrapper() : FBComponent_Wrapper( new FBMenuManager() ) 
    { 
        mFBMenuManager = (FBMenuManager*)mFBComponent; 
		SetAllocated();
    }

	virtual ~FBMenuManager_Wrapper( ) 
    {

    }

    object GetMenu(const char* pPath)
    {
        return FBWrapperFactory::TheOne().WrapFBObject( mFBMenuManager->GetMenu(pPath) );
    }

    object InsertFirst(const char* pMenuPath, const char* pMenuName)
    {
        return FBWrapperFactory::TheOne().WrapFBObject( mFBMenuManager->InsertFirst(pMenuPath, pMenuName) );
    }

    object InsertLast(const char* pMenuPath, const char* pMenuName)
    {
        return FBWrapperFactory::TheOne().WrapFBObject( mFBMenuManager->InsertLast(pMenuPath, pMenuName) );
    }

    object InsertAfter(const char* pMenuPath, const char* pAfterMenuName, const char* pMenuName)
    {
        return FBWrapperFactory::TheOne().WrapFBObject( mFBMenuManager->InsertAfter(pMenuPath, pAfterMenuName, pMenuName) );
    }

    object InsertBefore(const char* pMenuPath, const char* pBeforeMenuName, const char* pMenuName)
    {
        return FBWrapperFactory::TheOne().WrapFBObject( mFBMenuManager->InsertBefore(pMenuPath, pBeforeMenuName, pMenuName) );
    }

    void SetItemEnable(const char* pMenuPath, int pItemId, bool pEnable )
    {
        mFBMenuManager->SetItemEnable(pMenuPath, pItemId, pEnable);
    }

    bool IsItemEnable(const char* pMenuPath, int pItemId)
    {
        return mFBMenuManager->IsItemEnable(pMenuPath, pItemId);
    }

    bool ExecuteMenuItem( const char* pMenuPath, int pMenuItemId )
    {
        return mFBMenuManager->ExecuteMenuItem( pMenuPath, pMenuItemId );
    }

    bool ExecuteMenuItemFromFullPath( const char* pMenuItemFullPath )
    {
        return mFBMenuManager->ExecuteMenuItemFromFullPath( pMenuItemFullPath );
    }
};

#endif // pyfbmenumanager_h__
