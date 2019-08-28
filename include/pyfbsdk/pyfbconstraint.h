#ifndef pyfbconstraint_h__
#define pyfbconstraint_h__
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

#include "pyfbmatrix.h"
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"

// =======================================================================================
// FBConstraint
// =======================================================================================
void FBConstraint_Init();

class PYSDK_DLL FBConstraint_Wrapper : public FBBox_Wrapper {
public:
	FBConstraint* mFBConstraint;
public:
	FBConstraint_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBConstraint = (FBConstraint*)pFBComponent; }
	FBConstraint_Wrapper( const char* pName ) : FBBox_Wrapper( new FBConstraint( pName )) { mFBConstraint = (FBConstraint*)mFBComponent; }
	virtual ~FBConstraint_Wrapper( ) { }
	object AnimationNodeInCreate(kReference pUserId, FBModel_Wrapper& pModel, const char * pAttribute) { return FBWrapperFactory::TheOne().WrapFBObject( mFBConstraint->AnimationNodeInCreate( pUserId, pModel.mFBModel, pAttribute )); }
	object AnimationNodeOutCreate(kReference pUserId, FBModel_Wrapper& pModel, const char * pAttribute) { return FBWrapperFactory::TheOne().WrapFBObject( mFBConstraint->AnimationNodeOutCreate( pUserId, pModel.mFBModel, pAttribute )); }
	virtual object Clone() { return FBConstraint_Wrapper_Factory( mFBConstraint->Clone(  )); }
	bool DeformerBind(FBModel_Wrapper& pModel) { return mFBConstraint->DeformerBind( pModel.mFBModel ); }
    bool DeformerUnBind(FBModel_Wrapper& pModel) { return mFBConstraint->DeformerUnBind( pModel.mFBModel ); }
	bool Disable(FBModel_Wrapper& pModel) { return mFBConstraint->Disable( pModel.mFBModel ); }
	void FreezeSRT(FBModel_Wrapper& pModel, bool pS, bool pR, bool pT) { mFBConstraint->FreezeSRT( pModel.mFBModel, pS, pR, pT ); }
	void FreezeSuggested() { mFBConstraint->FreezeSuggested(  ); }
	bool ReferenceAdd(int pGroupIndex, FBModel_Wrapper& pModel) { return mFBConstraint->ReferenceAdd( pGroupIndex, pModel.mFBModel ); }
	object ReferenceGet(int pGroupIndex, int pItemIndex = 0) { return FBModel_Wrapper_Factory( mFBConstraint->ReferenceGet( pGroupIndex, pItemIndex )); }
	int ReferenceGetCount(int pGroupIndex) { return mFBConstraint->ReferenceGetCount( pGroupIndex ); }
	int ReferenceGroupAdd(const char * pGroupName, int pMaxItemCount) { return mFBConstraint->ReferenceGroupAdd( pGroupName, pMaxItemCount ); }
	int ReferenceGroupGetCount() { return mFBConstraint->ReferenceGroupGetCount(  ); }
	int ReferenceGroupGetMaxCount(int pGroupIndex) { return mFBConstraint->ReferenceGroupGetMaxCount( pGroupIndex ); }
	const char* ReferenceGroupGetName(int pGroupIndex) { return mFBConstraint->ReferenceGroupGetName( pGroupIndex ); }
	bool ReferenceRemove(int pGroupIndex, FBModel_Wrapper& pModel) { return mFBConstraint->ReferenceRemove( pGroupIndex, pModel.mFBModel ); }
	void RemoveAllAnimationNodes() { mFBConstraint->RemoveAllAnimationNodes(  ); }
	void RestoreModelState(FBModel_Wrapper& pModel) { mFBConstraint->RestoreModelState( pModel.mFBModel ); }
	void SaveModelState(FBModel_Wrapper& pModel, bool pS, bool pR, bool pT) { mFBConstraint->SaveModelState( pModel.mFBModel, pS, pR, pT ); }
	void SetupAllAnimationNodes() { mFBConstraint->SetupAllAnimationNodes(  ); }
	void Snap() { mFBConstraint->Snap(); }
	void SnapSuggested() { mFBConstraint->SnapSuggested(  ); }
	void SetActive( bool pActive ) { mFBConstraint->Active = pActive; }
	bool GetActive(  ) { return mFBConstraint->Active; }
	void SetDeformer( bool pDeformer ) { mFBConstraint->Deformer = pDeformer; }
	bool GetDeformer(  ) { return mFBConstraint->Deformer; }
	void SetDescription( const char* pDescription ) { mFBConstraint->Description = pDescription; }
	const char* GetDescription(  ) { return mFBConstraint->Description; }
	void SetHasLayout( bool pHasLayout ) { mFBConstraint->HasLayout = pHasLayout; }
	bool GetHasLayout(  ) { return mFBConstraint->HasLayout; }
	void SetLock( bool pLock ) { mFBConstraint->Lock = pLock; }
	bool GetLock(  ) { return mFBConstraint->Lock; }
	void SetWeight( double pWeight ) { mFBConstraint->Weight = pWeight; }
	object GetWeight(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBConstraint->Weight ); }
};
#endif // pyfbconstraint_h__