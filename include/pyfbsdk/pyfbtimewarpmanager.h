#ifndef pyfbtimewarpmanager_h__
#define pyfbtimewarpmanager_h__
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
#include "pyfbtake.h"

// =======================================================================================
// FBTimeWarpManager
// =======================================================================================
void FBTimeWarpManager_Init();

class PYSDK_DLL FBTimeWarpManager_Wrapper : public FBComponent_Wrapper {
public:
    typedef void (*TimeWarpChangeCallback)(void* pObject);
public:
    FBTimeWarpManager* mFBTimeWarpManager;
public:
    FBTimeWarpManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBTimeWarpManager = (FBTimeWarpManager*)pFBComponent; }
    FBTimeWarpManager_Wrapper(  ) : FBComponent_Wrapper( &FBTimeWarpManager::TheOne() ) { mFBTimeWarpManager = (FBTimeWarpManager*)mFBComponent; }
    virtual ~FBTimeWarpManager_Wrapper( ) { }

    void TimeWarpTakeChange() { mFBTimeWarpManager->TimeWarpTakeChange(); }
    void TimeWarpClearTake(FBTake_Wrapper& pTake) { mFBTimeWarpManager->TimeWarpClearTake( pTake.mFBTake ); }
    void TimeWarpInitTake(FBTake_Wrapper& pTake) { mFBTimeWarpManager->TimeWarpInitTake( pTake.mFBTake ); }
    void TimeWarpCopyTake(FBTake_Wrapper& pDstTake, FBTake_Wrapper& pSrcTake) { mFBTimeWarpManager->TimeWarpCopyTake( pDstTake.mFBTake, pSrcTake.mFBTake ); }
	
    void TimeWarpAddToTake(FBTake_Wrapper& pTake, FBAnimationNode_Wrapper& pTimeWarp, int pNickNumber = 0) { mFBTimeWarpManager->TimeWarpAddToTake( pTake.mFBTake, pTimeWarp.mFBAnimationNode, pNickNumber ); }
    void DestroyTimeWarpFromTake(FBTake_Wrapper& pTake, FBAnimationNode_Wrapper& pTimeWarp ) { mFBTimeWarpManager->DestroyTimeWarpFromTake( pTake.mFBTake, pTimeWarp.mFBAnimationNode ); }
    void RemoveTimeWarpFromScene(FBAnimationNode_Wrapper& pTimeWarp) { mFBTimeWarpManager->RemoveTimeWarpFromScene( pTimeWarp.mFBAnimationNode ); }
	
    kLong GetTimeWarpCount(FBTake_Wrapper& pTake) { return mFBTimeWarpManager->GetTimeWarpCount( pTake.mFBTake ); }
    object GetTimeWarpAtIndex(FBTake_Wrapper& pTake, kLong pIndex) { return FBWrapperFactory::TheOne().WrapFBObject(mFBTimeWarpManager->GetTimeWarpAtIndex( pTake.mFBTake, pIndex )); }
	
    int GetTimeWarpNickNumber(FBTake_Wrapper& pTake, FBAnimationNode_Wrapper& pTimeWarp) { return mFBTimeWarpManager->GetTimeWarpNickNumber( pTake.mFBTake, pTimeWarp.mFBAnimationNode ); }
    bool SetTimeWarpNickNumber(FBTake_Wrapper& pTake, FBAnimationNode_Wrapper& pTimeWarp, int pNumber) { return mFBTimeWarpManager->SetTimeWarpNickNumber( pTake.mFBTake, pTimeWarp.mFBAnimationNode, pNumber ); }
    int GetTimeWarpNickNumberAtIndex(FBTake_Wrapper& pTake, kLong pIndex) { return mFBTimeWarpManager->GetTimeWarpNickNumberAtIndex( pTake.mFBTake, pIndex ); }
    object GetTimeWarpFromNickNumber(FBTake_Wrapper& pTake, int pNumber) { return FBWrapperFactory::TheOne().WrapFBObject(mFBTimeWarpManager->GetTimeWarpFromNickNumber( pTake.mFBTake, pNumber )); }
    int FindTimeWarpNickNumberGlobal(FBAnimationNode_Wrapper& pTimeWarp) { return mFBTimeWarpManager->FindTimeWarpNickNumberGlobal( pTimeWarp.mFBAnimationNode ); }
	
    bool ApplyTimeWarp(FBTake_Wrapper& pTake, FBProperty_Wrapper* pProperty, FBAnimationNode_Wrapper& pTimeWarp) { return mFBTimeWarpManager->ApplyTimeWarp( pTake.mFBTake, pProperty->mFBProperty, pTimeWarp.mFBAnimationNode ); }
    void RemoveTimeWarp(FBTake_Wrapper& pTake, FBProperty_Wrapper* pProperty) { mFBTimeWarpManager->RemoveTimeWarp( pTake.mFBTake, pProperty->mFBProperty ); }
	
    void TimeWarpRegisterChangeEvent(TimeWarpChangeCallback pCallback, void* pObject) { mFBTimeWarpManager->TimeWarpRegisterChangeEvent( pCallback, pObject ); }
    void TimeWarpUnregisterChangeEvent(TimeWarpChangeCallback pCallback, void* pObject) { mFBTimeWarpManager->TimeWarpUnregisterChangeEvent( pCallback, pObject ); }
	
    object TimeWarpCreateNew(const char* pName) { return FBWrapperFactory::TheOne().WrapFBObject(mFBTimeWarpManager->TimeWarpCreateNew( pName )); }
    void TimeWarpRename(FBTake_Wrapper& pTake, FBAnimationNode_Wrapper& pTimeWarp, const char* pNewName) { mFBTimeWarpManager->TimeWarpRename( pTake.mFBTake, pTimeWarp.mFBAnimationNode, pNewName ); }
    void TimeWarpMergeCurveNode(FBTake_Wrapper& pTake, FBProperty_Wrapper* pProperty, FBAnimationNode_Wrapper& pNode, FBAnimationNode_Wrapper& pTimeWarpNode) { mFBTimeWarpManager->TimeWarpMergeCurveNode( pTake.mFBTake, pProperty->mFBProperty, pNode.mFBAnimationNode, pTimeWarpNode.mFBAnimationNode); }
};
#endif // pyfbtimewarpmanager_h__