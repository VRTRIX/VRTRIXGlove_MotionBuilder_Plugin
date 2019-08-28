#ifndef pyfbactionmanager_h__
#define pyfbactionmanager_h__
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

void FBActionManager_Init();

class PYSDK_DLL FBActionManager_Wrapper
    : public FBComponent_Wrapper
{
public:
    FBActionManager *mFBActionManager;

public:
    FBActionManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBActionManager = (FBActionManager*)pFBComponent; }
    FBActionManager_Wrapper( ) : FBComponent_Wrapper( &FBActionManager::TheOne() ) { mFBActionManager = (FBActionManager*)mFBComponent; }
    virtual ~FBActionManager_Wrapper( ) { }

    const char* GetCurrentInteractionMode();

    void SetCurrentInteractionMode( const char *pMode );
};


#endif //pyfbactionmanager_h__