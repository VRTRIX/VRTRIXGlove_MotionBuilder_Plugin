#ifndef pyfbmotionblend_h__
#define pyfbmotionblend_h__
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
#include "pyfbmotionblendedit.h"

// =======================================================================================
// FBMotionBlend
// =======================================================================================
void FBMotionBlend_Init();

class PYSDK_DLL FBMotionBlend_Wrapper : public FBComponent_Wrapper {
public:
	FBMotionBlend* mFBMotionBlend;
public:
	FBMotionBlend_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBMotionBlend = (FBMotionBlend*)pFBComponent; }
	FBMotionBlend_Wrapper() : FBComponent_Wrapper( &FBMotionBlend::TheOne() ) { mFBMotionBlend = (FBMotionBlend*)mFBComponent; }
	virtual ~FBMotionBlend_Wrapper() {}

	int GetEditCount() { return mFBMotionBlend->GetEditCount(); }
	object GetEdit( int pIndex ) { return FBMotionBlendEdit_Wrapper_Factory( mFBMotionBlend->GetEdit( pIndex ) ); }
	object GetCurrentEdit() { return FBMotionBlendEdit_Wrapper_Factory( mFBMotionBlend->GetCurrentEdit() ); }
	bool SetCurrentEdit( FBMotionBlendEdit_Wrapper& pEdit ) { return mFBMotionBlend->SetCurrentEdit( pEdit.mFBMotionBlendEdit ); }
	object AddEdit( const char* pName = nullptr, bool pSetAsCurrent = true ) { return FBMotionBlendEdit_Wrapper_Factory( mFBMotionBlend->AddEdit( pName, pSetAsCurrent ) ); }
	bool RemoveEdit( FBMotionBlendEdit_Wrapper& pEdit ) { return mFBMotionBlend->RemoveEdit( pEdit.mFBMotionBlendEdit ); };
	bool RemoveAllEdits() { return mFBMotionBlend->RemoveAllEdits(); }
	bool SetSnapOnFrame( bool pSnap ) { return mFBMotionBlend->SetSnapOnFrame( pSnap ); }
	bool GetSnapOnFrame() { return mFBMotionBlend->GetSnapOnFrame(); }
	bool SetForceTime( bool pForceTime ) { return mFBMotionBlend->SetForceTime( pForceTime ); }
	bool GetForceTime() { return mFBMotionBlend->GetForceTime(); }
	bool SetSyncTakeEditStartEnd( bool pSync ) { return mFBMotionBlend->SetSyncTakeEditStartEnd( pSync ); }
	bool GetSyncTakeEditStartEnd() { return mFBMotionBlend->GetSyncTakeEditStartEnd(); }
}; 
#endif // pyfbmotionblend_h__