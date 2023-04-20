#ifndef pyfbtoollayoutmanager_h__
#define pyfbtoollayoutmanager_h__
/**************************************************************************
 Copyright 2019 Autodesk, Inc.
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
// FBToolLayoutManager
// =======================================================================================
void FBToolLayoutManager_Init();

class PYSDK_DLL FBToolLayoutManager_Wrapper
	: public FBComponent_Wrapper
{
public:
	FBToolLayoutManager* mFBToolLayoutManager;

public:
	FBToolLayoutManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBToolLayoutManager = (FBToolLayoutManager*)pFBComponent; }
	FBToolLayoutManager_Wrapper( ) : FBComponent_Wrapper( &FBToolLayoutManager::TheOne() ) { mFBToolLayoutManager = (FBToolLayoutManager*)mFBComponent; }
	virtual ~FBToolLayoutManager_Wrapper( ) { }

	int GetFactoryLayoutCount();
	int GetCustomLayoutCount();
	const char* GetLayoutName( int pLayoutIdx );
	int GetCurrentLayoutIdx();
	const char* GetCurrentLayoutName();
	bool SetCurrentLayoutFromIdx( int pLayoutIdx );
	bool SetCurrentLayoutFromName( const char* pLayoutName );
	const char* CreateLayout( const char* pLayoutName );
	bool DeleteLayoutFromIdx( int pLayoutIdx );
	bool DeleteLayoutFromName( const char* pLayoutName );
	bool UpdateCurrentLayout();
	const char* RenameLayout( const char* pOldLayoutName, const char* pNewLayoutName );
	bool GetAutoUpdateLayout();
	bool SetAutoUpdateLayout( bool pAutoUpdate );
	bool GetPreventDocking();
	bool SetPreventDocking( bool pPreventDocking );
};


#endif //pyfbtoollayoutmanager_h__
