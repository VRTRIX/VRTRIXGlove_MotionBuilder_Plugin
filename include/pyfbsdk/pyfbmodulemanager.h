#ifndef pyfbmodulemanager_h__
#define pyfbmodulemanager_h__
// =======================================================================
// Copyright 2020 Autodesk, Inc. All rights reserved.
//
// This computer source code and related instructions and comments are the
// unpublished confidential  and proprietary information of Autodesk, Inc.
// and are protected under applicable copyright and trade secret law. They 
// may not be disclosed to, copied  or used by any third party without the 
// prior written consent of Autodesk, Inc.
// =======================================================================

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

void FBModuleManager_Init();

class PYSDK_DLL FBModuleManager_Wrapper
    : public FBComponent_Wrapper
{
public:
    FBModuleManager *mFBModuleManager;

public:
	FBModuleManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBModuleManager = (FBModuleManager*)pFBComponent; }
	FBModuleManager_Wrapper( ) : FBComponent_Wrapper( &FBModuleManager::TheOne() ) { mFBModuleManager = (FBModuleManager*)mFBComponent; }
    virtual ~FBModuleManager_Wrapper( ) { }

	FBStringList_Wrapper* GetModuleSearchPaths() const { return FBStringList_Wrapper_Factory( mFBModuleManager->GetModuleSearchPaths() ); };
	FBStringList_Wrapper* GetLoadedModuleNames() const { return FBStringList_Wrapper_Factory( mFBModuleManager->GetLoadedModuleNames() ); };
	const char* GetModulePath( const char* pModuleName ) const { return mFBModuleManager->GetModulePath( pModuleName ); };
	const char* GetModuleVersion( const char* pModuleName ) const { return mFBModuleManager->GetModuleVersion( pModuleName ); };
	const char* GetModuleModFilePath( const char* pModuleName ) const { return mFBModuleManager->GetModuleModFilePath( pModuleName ); };
};


#endif //pyFBModuleManager_h__