#ifndef pyfbbox_h__
#define pyfbbox_h__
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

#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"

// =======================================================================================
// FBBox
// =======================================================================================
void FBBox_Init();

class PYSDK_DLL FBBox_Wrapper : public FBComponent_Wrapper {
public:
	FBBox* mFBBox;
public:
	FBBox_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBBox = (FBBox*)pFBComponent; }
	FBBox_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBBox( pName )) { mFBBox = (FBBox*)mFBComponent; }
	virtual ~FBBox_Wrapper( ) {}
	bool AnimationNodeDestroy(FBAnimationNode_Wrapper& pAnimationNode) { return mFBBox->AnimationNodeDestroy( pAnimationNode.mFBAnimationNode ); }
	object AnimationNodeInGet() { return FBWrapperFactory::TheOne().WrapFBObject( mFBBox->AnimationNodeInGet(  )); }
	bool AnimationNodeIsUserData(FBAnimationNode_Wrapper* pAnimationNode) { return mFBBox->AnimationNodeIsUserData( pAnimationNode->mFBAnimationNode ); }
	object AnimationNodeOutGet() { return FBWrapperFactory::TheOne().WrapFBObject( mFBBox->AnimationNodeOutGet(  )); }
	void SetAnimatable( bool pAnimatable ) { mFBBox->Animatable = pAnimatable; }
	bool GetAnimatable(  ) { return mFBBox->Animatable; }
	void SetLive( bool pLive ) { mFBBox->Live = pLive; }
	bool GetLive(  ) { return mFBBox->Live; }
	void SetRecordMode( bool pRecordMode ) { mFBBox->RecordMode = pRecordMode; }
	bool GetRecordMode(  ) { return mFBBox->RecordMode; }
	void SetUniqueName( const char* pUniqueName ) { mFBBox->UniqueName = pUniqueName; }
	const char* GetUniqueName(  ) { return mFBBox->UniqueName; }
};
#endif // pyfbbox_h__
