#ifndef pyfbfcurveeventmanager_h__
#define pyfbfcurveeventmanager_h__
// ===========================================================================
// Copyright 2018 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================

#include <kaydaradef.h>
#ifndef PYSDK_DLL
/** \def PYSDK_DLL
*    Be sure that PYSDK_DLL is defined only once...
*/
#define PYSDK_DLL K_DLLIMPORT
#endif

#include "pyfbcomponent.h"

// =======================================================================================
// FBFCurveEventManager
// =======================================================================================
void FBFCurveEventManager_Init();

class PYSDK_DLL FBFCurveEventManager_Wrapper : public FBComponent_Wrapper {
public:
	FBFCurveEventManager* mFBFCurveEventManager;
public:
	FBFCurveEventManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBFCurveEventManager = (FBFCurveEventManager*)pFBComponent; }
	FBFCurveEventManager_Wrapper() : FBComponent_Wrapper( &FBFCurveEventManager::TheOne() ) { mFBFCurveEventManager = (FBFCurveEventManager*)mFBComponent; }
	virtual ~FBFCurveEventManager_Wrapper() {}

	bool RegisterProperty( FBPropertyAnimatable_Wrapper& pProperty ) { return mFBFCurveEventManager->RegisterProperty( (FBPropertyAnimatable*)pProperty.mFBProperty ); }
	bool UnregisterProperty( FBPropertyAnimatable_Wrapper& pProperty ) { return mFBFCurveEventManager->UnregisterProperty( (FBPropertyAnimatable*)pProperty.mFBProperty ); }

	object OnPropertyEvent();
	object OnFCurveEvent();

protected:
	FBPropertyEvent* GetPropertyEvent( FBEventName pEventName );
}; 
#endif // pyfbfcurveeventmanager_h__