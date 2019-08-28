#ifndef pyfbhudmanager_h__
#define pyfbhudmanager_h__
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

#include "pyfbhud.h"

// =======================================================================================
// FBHUDManager
// =======================================================================================
void FBHUDManager_Init();

class PYSDK_DLL FBHUDManager_Wrapper : public FBComponent_Wrapper {
public:
	FBHUDManager* mFBHUDManager;
public:
	FBHUDManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBHUDManager = (FBHUDManager*)pFBComponent; }
	FBHUDManager_Wrapper(  ) : FBComponent_Wrapper( &FBHUDManager::TheOne() ) { mFBHUDManager = (FBHUDManager*)mFBComponent; }
	virtual ~FBHUDManager_Wrapper( ) { }

    object GetDefaultHUD() { return FBWrapperFactory::TheOne().WrapFBObject(mFBHUDManager->DefaultHUD); }
    void   SetDefaultHUD( FBHUD_Wrapper* pDefaultHUD ) { mFBHUDManager->DefaultHUD = pDefaultHUD ? pDefaultHUD->mFBHUD : NULL; }
};
#endif // pyfbhudmanager_h__