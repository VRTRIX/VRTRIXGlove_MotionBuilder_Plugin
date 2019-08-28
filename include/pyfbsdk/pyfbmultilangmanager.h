#ifndef pyfbmultilangmanager_h__
#define pyfbmultilangmanager_h__
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

#include "pyfbstringlist.h"

// =======================================================================================
// FBMultiLangManager
// =======================================================================================
void FBMultiLangManager_Init();

class PYSDK_DLL FBMultiLangManager_Wrapper {
public:
	FBMultiLangManager* mFBMultiLangManager;
public:
	FBMultiLangManager_Wrapper() : mFBMultiLangManager( new FBMultiLangManager ) {} // Memory leak!
	virtual ~FBMultiLangManager_Wrapper( ) { delete mFBMultiLangManager; }
	const char * GetCurrentLanguage() { return mFBMultiLangManager->GetCurrentLanguage(  ); }
	bool SetCurrentLanguage(const char * pLanguage) { return mFBMultiLangManager->SetCurrentLanguage( pLanguage ); }
	FBStringList_Wrapper* GetLanguages(  ) { return FBStringList_Wrapper_Factory( &( mFBMultiLangManager->Languages )); }
};
#endif // pyfbmultilangmanager_h__