#ifndef pyfbmotionblendedit_h__
#define pyfbmotionblendedit_h__
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

// =======================================================================================
// FBMotionBlendEdit
// =======================================================================================
void FBMotionBlendEdit_Init();

class PYSDK_DLL FBMotionBlendEdit_Wrapper : public FBComponent_Wrapper {
public:
	FBMotionBlendEdit* mFBMotionBlendEdit;
public:
	FBMotionBlendEdit_Wrapper( FBMotionBlendEdit* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBMotionBlendEdit = (FBMotionBlendEdit*)pFBComponent; }
	FBMotionBlendEdit_Wrapper( const char* pName = nullptr, bool pSetAsCurrent = true ) : FBComponent_Wrapper( new FBMotionBlendEdit( pName, pSetAsCurrent ) ) { mFBMotionBlendEdit = (FBMotionBlendEdit*)mFBComponent; }
	virtual ~FBMotionBlendEdit_Wrapper() {}

	void FBDelete() { mFBMotionBlendEdit->FBDelete(); }

	const char* GetName() { return mFBMotionBlendEdit->GetName(); }
	bool SetName( const char* pName ) { return mFBMotionBlendEdit->SetName( pName ); }
	bool Clear() { return mFBMotionBlendEdit->Clear(); }
	bool SetShowAllGhosts( bool pShow ) { return mFBMotionBlendEdit->SetShowAllGhosts( pShow ); }
	bool GetShowAllGhosts() { return mFBMotionBlendEdit->GetShowAllGhosts(); }
	bool SetKeepActive( bool pKeepActive ) { return mFBMotionBlendEdit->SetKeepActive( pKeepActive ); }
	bool GetKeepActive() { return mFBMotionBlendEdit->GetKeepActive(); }
};

PYSDK_DLL inline object FBMotionBlendEdit_Wrapper_Factory( FBMotionBlendEdit* pFBMotionBlendEdit )
{
	return FBWrapperFactory::TheOne().WrapFBObject( pFBMotionBlendEdit );
}

#endif // pyfbmotionblendedit_h__