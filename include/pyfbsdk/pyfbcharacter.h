#ifndef pyfbcharacter_h__
#define pyfbcharacter_h__
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
#include "pyfbplotoptions.h"
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbpose.h"
#include "pyfbconstraint.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"
#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbactorface.h"
#include "pyfbkeyinggroup.h"
#include "pyfbobjectposeoptions.h"
#include "pyfbobjectposemirroroptions.h"
#include "pyfbobjectpose.h"
#include "pyfbcharacterextension.h"
#include "pyfbcharactersolver.h"
#include "pyfbcontrolset.h"

// =======================================================================================
// FBCharacter
// =======================================================================================
void FBCharacter_Init();

class PYSDK_DLL FBCharacter_Wrapper : public FBConstraint_Wrapper {
public:
	FBCharacter* mFBCharacter;
public:
	FBCharacter_Wrapper( FBComponent* pFBComponent ) : FBConstraint_Wrapper( pFBComponent ) { mFBCharacter = (FBCharacter*)pFBComponent; }
	FBCharacter_Wrapper( const char* pName ) : FBConstraint_Wrapper( new FBCharacter( pName )) { mFBCharacter = (FBCharacter*)mFBComponent; }
	virtual ~FBCharacter_Wrapper( ) { }
	void AddCharacterExtension(FBCharacterExtension_Wrapper& pExt) { mFBCharacter->AddCharacterExtension( pExt.mFBCharacterExtension ); }
	void CopyAnimation() { mFBCharacter->CopyAnimation(  ); }
	void FBDelete() { mFBCharacter->FBDelete(  ); }
    virtual object Clone() { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacter->Clone( ) ); }
	object GetCtrlRigModel(FBBodyNodeId pBodyNodeId) { return FBModel_Wrapper_Factory( mFBCharacter->GetCtrlRigModel( pBodyNodeId )); }
	object GetEffectorModel(FBEffectorId pEffectorId, FBEffectorSetID pSetId=FBEffectorSetDefault) { return FBModel_Wrapper_Factory( mFBCharacter->GetEffectorModel( pEffectorId, pSetId )); }
    FBBodyNodeId GetIndexByModel( FBModelSkeleton_Wrapper& pModel ) { return mFBCharacter->GetIndexByModel(pModel.mFBModel); }
	object GetModel(FBBodyNodeId pBodyNodeId) { return FBModel_Wrapper_Factory( mFBCharacter->GetModel( pBodyNodeId )); }
	object GetGoalModel(FBBodyNodeId pBodyNodeId) { return FBModel_Wrapper_Factory( mFBCharacter->GetGoalModel( pBodyNodeId )); }
    void GetSkinModelList(FBModelList_Wrapper& pFBSkinModelList) { mFBCharacter->GetSkinModelList( *(pFBSkinModelList.mFBModelList) ); }
    void GoToStancePose(bool pPushUndo = false, bool pIncludeCharacterExtensions = true) { mFBCharacter->GoToStancePose( pPushUndo, pIncludeCharacterExtensions ); }
	bool PlotAnimation(FBCharacterPlotWhere pPlotWhere, FBPlotOptions_Wrapper& pPlotOptions) { return mFBCharacter->PlotAnimation( pPlotWhere, pPlotOptions.mFBPlotOptions ); }
	bool ReadyForRetarget() { return mFBCharacter->ReadyForRetarget(  ); }
	void RemoveCharacterExtension(FBCharacterExtension_Wrapper& pExt) { mFBCharacter->RemoveCharacterExtension( pExt.mFBCharacterExtension ); }
	void ResetProperties( FBCharacterResetProperties pType ) { mFBCharacter->ResetProperties( pType ); }
	void Retarget(bool pOnBaseLayer) { mFBCharacter->Retarget( pOnBaseLayer ); }
	void SelectModels(bool pSelect, bool pApplyToCharacter, bool pApplyToRig, bool pApplyToExtensions) { mFBCharacter->SelectModels( pSelect, pApplyToCharacter, pApplyToRig, pApplyToExtensions ); }
    object GetCharacterExtensions(  ) { return FBPropertyListCharacterExtension_Wrapper_Factory( mFBCharacter->CharacterExtensions ); }
    void SetInputActor( FBActor_Wrapper& pInputActor ) { mFBCharacter->InputActor = pInputActor.mFBActor; }
    object GetInputActor(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacter->InputActor ); }
    void SetInputCharacter( FBCharacter_Wrapper& pInputCharacter ) { mFBCharacter->InputCharacter = pInputCharacter.mFBCharacter; }
    object GetInputCharacter(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacter->InputCharacter ); }
    bool SetCharacterizeOn(  bool pSetAsBiped ) { return mFBCharacter->SetCharacterizeOn(pSetAsBiped); }
	void SetCharacterizeOff() { mFBCharacter->SetCharacterizeOff(); }
	bool GetCharacterize( ) { return mFBCharacter->GetCharacterize(); }
	bool CreateControlRig( bool pSetFK){ return mFBCharacter->CreateControlRig(pSetFK);}
	void ConnectControlRig( FBControlSet_Wrapper& pControlSet, bool pUpdateLimit, bool pResetHierarchy){ mFBCharacter->ConnectControlRig(pControlSet.mFBControlSet,pUpdateLimit,pResetHierarchy);}
	void DisconnectControlRig( ){ mFBCharacter->DisconnectControlRig(); }
	bool CreateAuxiliary( FBEffectorId pEffectorId, bool pPivot, double pAuxReachT=100, double pAuxReachR=100){ return mFBCharacter->CreateAuxiliary(pEffectorId,pPivot,pAuxReachT,pAuxReachR);}
	bool CreateCharacterMarkerSet(bool pSetActive){ return mFBCharacter->CreateCharacterMarkerSet(pSetActive);}
	const char * GetCharacterizeError() { return mFBCharacter->GetCharacterizeError(); }
    void GetParentROffset(FBBodyNodeId pBodyNodeId, FBVector3d_Wrapper& pVector) { return mFBCharacter->GetParentROffset( pBodyNodeId, pVector.mFBVector3d ); }
    object GetExternalSolver( ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacter->GetExternalSolver( ) ); }
    void SetExternalSolverWithIndex( int pIndex ) { mFBCharacter->SetExternalSolver( pIndex ); }
    void SetExternalSolver(FBCharacterSolver_Wrapper& pSolver){mFBCharacter->SetExternalSolver(pSolver.mFBCharacterSolver);}
	object GetCurrentControlSet( ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacter->GetCurrentControlSet( ) ); }
    object GetCharacterMarkerSet( bool pForce ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacter->GetCharacterMarkerSet( pForce ) ); }
    bool IsRotationPin(FBEffectorId pEffectorIndex) { return mFBCharacter->IsRotationPin( pEffectorIndex ); }
    bool IsTranslationPin(FBEffectorId pEffectorIndex) { return mFBCharacter->IsTranslationPin( pEffectorIndex ); }
    object GetFloorContactModel( FBFloorContactID pMemberIndex ) { return FBModel_Wrapper_Factory(mFBCharacter->GetFloorContactModel( pMemberIndex )); }
    void GetTOffset( FBBodyNodeId pBodyNodeId, FBVector4d_Wrapper& pTVector ) { mFBCharacter->GetTOffset( pBodyNodeId, pTVector.mFBVector4d ); }
    void GetROffset( FBBodyNodeId pBodyNodeId, FBVector3d_Wrapper& pRVector ) { mFBCharacter->GetROffset( pBodyNodeId, pRVector.mFBVector3d ); }
    void GetSOffset( FBBodyNodeId pBodyNodeId, FBVector3d_Wrapper& pSVector ) { mFBCharacter->GetSOffset( pBodyNodeId, (FBSVector*)pSVector.mFBVector3d ); }
    void GetTransformOffset( FBBodyNodeId pBodyNodeId, FBMatrix_Wrapper&  pOffsetMatrix ) { return mFBCharacter->GetTransformOffset(pBodyNodeId, pOffsetMatrix.mFBMatrix); }
    bool IsParentNodeOffset( FBBodyNodeId pNodeId ) { return mFBCharacter->IsParentNodeOffset(pNodeId); }

    list GetActiveBodyPart()
    {
        bool lActiveBodyPart[12];
        mFBCharacter->GetActiveBodyPart( lActiveBodyPart ); 
        
        list lReturnList;
        for(int i = 0; i < 12; i++)
        {
            lReturnList.append(lActiveBodyPart[i]);
        }
        return lReturnList;
    }

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ActiveInput, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( InputType, FBCharacterInputType );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( KeyingMode, FBCharacterKeyingMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( RollSolver, FBCharacterRollSolver );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ContactBehaviour, FBCharacterContactBehaviour );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( MirrorMode, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ShoulderCorrection, double );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( LeftKneeKillPitch, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( RightKneeKillPitch, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( LeftElbowKillPitch, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( RightElbowKillPitch, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( HipsTranslationMode, FBCharacterHipsTranslationMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( WriteReference, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( SyncMode, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( InverseLeftKnee, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( InverseRightKnee, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( InverseLeftElbow, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( InverseRightElbow, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( LockX, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( LockY, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( LockZ, bool );
};
#endif // pyfbcharacter_h__