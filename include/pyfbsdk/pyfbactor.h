#ifndef pyfbactor_h__
#define pyfbactor_h__
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

// =======================================================================================
// FBActor
// =======================================================================================
void FBActor_Init();
    
class FBActor_Wrapper;
class PYSDK_DLL FBActor_Wrapper : public FBConstraint_Wrapper {
public:
	FBActor* mFBActor;
public:
	FBActor_Wrapper( FBComponent* pFBComponent ) : FBConstraint_Wrapper( pFBComponent ) { mFBActor = (FBActor*)pFBComponent; }
	explicit FBActor_Wrapper( const char* pName ) : FBConstraint_Wrapper( new FBActor( pName )) { mFBActor = (FBActor*)mFBComponent; }
	virtual ~FBActor_Wrapper( ) {}
	void FBDelete() { mFBActor->FBDelete(  ); }
	bool Snap(FBRecalcMarkerSetOffset pRecalcOffset) { return mFBActor->Snap( pRecalcOffset ); }
    void UpdateValues( FBEvaluateInfo* pEvalInfo ) { mFBActor->UpdateValues( pEvalInfo ); }
    void GetDefinitionScaleVector(	FBSkeletonNodeId pSkeletonId, FBVector3d_Wrapper &pScaleVector ) { mFBActor->GetDefinitionScaleVector( pSkeletonId, *(pScaleVector.mFBVector3d) ); }
    void SetDefinitionScaleVector(	FBSkeletonNodeId pSkeletonId, FBVector3d_Wrapper& pScaleVector, bool pSymmetricUpdate = true ) { mFBActor->SetDefinitionScaleVector( pSkeletonId, *pScaleVector.mFBVector3d,pSymmetricUpdate ); }
    void SetDefinitionRotationVector(	FBSkeletonNodeId pSkeletonId, FBVector3d_Wrapper& pRotationVector, bool pSymmetricUpdate = true ) { mFBActor->SetDefinitionRotationVector( pSkeletonId, *pRotationVector.mFBVector3d,pSymmetricUpdate ); }
    FBSkeletonState_Wrapper* GetDefaultSkeletonState( ) { return FBSkeletonState_Wrapper_Factory(mFBActor->GetDefaultSkeletonState()); }
	FBSkeletonState_Wrapper* GetCurrentSkeletonState( ) { return FBSkeletonState_Wrapper_Factory(mFBActor->GetCurrentSkeletonState()); }
    FBSkeletonState_Wrapper* GetCurrentSkeletonState1( bool pResetOrientation ) { return FBSkeletonState_Wrapper_Factory(mFBActor->GetCurrentSkeletonState(pResetOrientation)); }
	void SetBodyColor( FBColor_Wrapper& pBodyColor ) { mFBActor->BodyColor = *pBodyColor.mFBColor; }
	FBColor_Wrapper* GetBodyColor(  ) { return FBColor_Wrapper_Factory( mFBActor->BodyColor ); }
	void SetChestPosition( FBVector3d_Wrapper& pChestPosition ) { mFBActor->ChestPosition = *pChestPosition.mFBVector3d; }
	FBVector3d_Wrapper* GetChestPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->ChestPosition ); }
	void SetHeadPosition( FBVector3d_Wrapper& pHeadPosition ) { mFBActor->HeadPosition = *pHeadPosition.mFBVector3d; }
	FBVector3d_Wrapper* GetHeadPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->HeadPosition ); }
	void SetHipsPosition( FBVector3d_Wrapper& pHipsPosition ) { mFBActor->HipsPosition = *pHipsPosition.mFBVector3d; }
	FBVector3d_Wrapper* GetHipsPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->HipsPosition ); }
	void SetLeftAnklePosition( FBVector3d_Wrapper& pLeftAnklePosition ) { mFBActor->LeftAnklePosition = *(pLeftAnklePosition.mFBVector3d); }
	FBVector3d_Wrapper* GetLeftAnklePosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->LeftAnklePosition ); }
	void SetLeftCollarPosition( FBVector3d_Wrapper& pLeftCollarPosition ) { mFBActor->LeftCollarPosition = *(pLeftCollarPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetLeftCollarPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->LeftCollarPosition ); }
	void SetLeftElbowPosition( FBVector3d_Wrapper& pLeftElbowPosition ) { mFBActor->LeftElbowPosition = *(pLeftElbowPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetLeftElbowPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->LeftElbowPosition ); }
	void SetLeftFootPosition( FBVector3d_Wrapper& pLeftFootPosition ) { mFBActor->LeftFootPosition = *(pLeftFootPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetLeftFootPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->LeftFootPosition ); }
	void SetLeftHipPosition( FBVector3d_Wrapper& pLeftHipPosition ) { mFBActor->LeftHipPosition = *(pLeftHipPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetLeftHipPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->LeftHipPosition ); }
	void SetLeftKneePosition( FBVector3d_Wrapper& pLeftKneePosition ) { mFBActor->LeftKneePosition = *(pLeftKneePosition.mFBVector3d); }
	FBVector3d_Wrapper* GetLeftKneePosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->LeftKneePosition ); }
	void SetLeftShoulderPosition( FBVector3d_Wrapper& pLeftShoulderPosition ) { mFBActor->LeftShoulderPosition = *(pLeftShoulderPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetLeftShoulderPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->LeftShoulderPosition ); }
	void SetLeftWristPosition( FBVector3d_Wrapper& pLeftWristPosition ) { mFBActor->LeftWristPosition = *(pLeftWristPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetLeftWristPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->LeftWristPosition ); }
	void SetMarkerSet( FBMarkerSet_Wrapper& pMarkerSet ) { mFBActor->MarkerSet = pMarkerSet.mFBMarkerSet; }
	object GetMarkerSet(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBActor->MarkerSet ); }
	void SetMarkerSetSize( double pMarkerSetSize ) { mFBActor->MarkerSetSize = pMarkerSetSize; }
	double GetMarkerSetSize(  ) { return mFBActor->MarkerSetSize; }
	void SetNeckPosition( FBVector3d_Wrapper& pNeckPosition ) { mFBActor->NeckPosition = *(pNeckPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetNeckPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->NeckPosition ); }
	void SetOutputMarkerSet( FBMarkerSet_Wrapper& pOutputMarkerSet ) { mFBActor->OutputMarkerSet = pOutputMarkerSet.mFBMarkerSet; }
	object GetOutputMarkerSet(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBActor->OutputMarkerSet ); }
	void SetPivotColor( FBColor_Wrapper& pPivotColor ) { mFBActor->PivotColor = *(pPivotColor.mFBColor); }
	FBColor_Wrapper* GetPivotColor(  ) { return FBColor_Wrapper_Factory( mFBActor->PivotColor ); }
	void SetPivotSize( double pPivotSize ) { mFBActor->PivotSize = pPivotSize; }
	double GetPivotSize(  ) { return mFBActor->PivotSize; }
	void SetRightAnklePosition( FBVector3d_Wrapper& pRightAnklePosition ) { mFBActor->RightAnklePosition = *(pRightAnklePosition.mFBVector3d); }
	FBVector3d_Wrapper* GetRightAnklePosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->RightAnklePosition ); }
	void SetRightCollarPosition( FBVector3d_Wrapper& pRightCollarPosition ) { mFBActor->RightCollarPosition = *(pRightCollarPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetRightCollarPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->RightCollarPosition ); }
	void SetRightElbowPosition( FBVector3d_Wrapper& pRightElbowPosition ) { mFBActor->RightElbowPosition = *(pRightElbowPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetRightElbowPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->RightElbowPosition ); }
	void SetRightFootPosition( FBVector3d_Wrapper& pRightFootPosition ) { mFBActor->RightFootPosition = *(pRightFootPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetRightFootPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->RightFootPosition ); }
	void SetRightHipPosition( FBVector3d_Wrapper& pRightHipPosition ) { mFBActor->RightHipPosition = *(pRightHipPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetRightHipPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->RightHipPosition ); }
	void SetRightKneePosition( FBVector3d_Wrapper& pRightKneePosition ) { mFBActor->RightKneePosition = *(pRightKneePosition.mFBVector3d); }
	FBVector3d_Wrapper* GetRightKneePosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->RightKneePosition ); }
	void SetRightShoulderPosition( FBVector3d_Wrapper& pRightShoulderPosition ) { mFBActor->RightShoulderPosition = *(pRightShoulderPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetRightShoulderPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->RightShoulderPosition ); }
	void SetRightWristPosition( FBVector3d_Wrapper& pRightWristPosition ) { mFBActor->RightWristPosition = *(pRightWristPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetRightWristPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->RightWristPosition ); }
	void SetSkeletonColor( FBColor_Wrapper& pSkeletonColor ) { mFBActor->SkeletonColor = *(pSkeletonColor.mFBColor); }
	FBColor_Wrapper* GetSkeletonColor(  ) { return FBColor_Wrapper_Factory( mFBActor->SkeletonColor ); }
	void SetWaistPosition( FBVector3d_Wrapper& pWaistPosition ) { mFBActor->WaistPosition = *(pWaistPosition.mFBVector3d); }
	FBVector3d_Wrapper* GetWaistPosition(  ) { return FBVector3d_Wrapper_Factory( mFBActor->WaistPosition ); }
	void    SetLeftHandIndexIndex( double pValue )  { mFBActor->LeftHandIndexIndex = pValue; }
	double  GetLeftHandIndexIndex(  )        { return mFBActor->LeftHandIndexIndex; }
	void    SetLeftHandIndexMiddle( double pValue ) { mFBActor->LeftHandIndexMiddle = pValue; }
	double  GetLeftHandIndexMiddle(  )       { return mFBActor->LeftHandIndexMiddle; }
	void    SetLeftHandIndexRing( double pValue )   { mFBActor->LeftHandIndexRing = pValue; }
	double  GetLeftHandIndexRing(  )         { return mFBActor->LeftHandIndexRing; }
	void    SetLeftHandIndexPinky( double pValue )  { mFBActor->LeftHandIndexPinky = pValue; }
	double  GetLeftHandIndexPinky(  )        { return mFBActor->LeftHandIndexPinky; }
	void    SetLeftHandMiddleIndex( double pValue ) { mFBActor->LeftHandMiddleIndex = pValue; }
	double  GetLeftHandMiddleIndex(  )       { return mFBActor->LeftHandMiddleIndex; }
	void    SetLeftHandMiddleMiddle( double pValue ){ mFBActor->LeftHandMiddleMiddle = pValue; }
	double  GetLeftHandMiddleMiddle(  )      { return mFBActor->LeftHandMiddleMiddle; }
	void    SetLeftHandMiddleRing( double pValue )  { mFBActor->LeftHandMiddleRing = pValue; }
	double  GetLeftHandMiddleRing(  )        { return mFBActor->LeftHandMiddleRing; }
	void    SetLeftHandMiddlePinky( double pValue ) { mFBActor->LeftHandMiddlePinky = pValue; }
	double  GetLeftHandMiddlePinky(  )       { return mFBActor->LeftHandMiddlePinky; }
	void    SetLeftHandRingIndex( double pValue )   { mFBActor->LeftHandRingIndex = pValue; }
	double  GetLeftHandRingIndex(  )         { return mFBActor->LeftHandRingIndex; }
	void    SetLeftHandRingMiddle( double pValue )  { mFBActor->LeftHandRingMiddle = pValue; }
	double  GetLeftHandRingMiddle(  )        { return mFBActor->LeftHandRingMiddle; }
	void    SetLeftHandRingRing( double pValue )    { mFBActor->LeftHandRingRing = pValue; }
	double  GetLeftHandRingRing(  )          { return mFBActor->LeftHandRingRing; }
	void    SetLeftHandRingPinky( double pValue )   { mFBActor->LeftHandRingPinky = pValue; }
	double  GetLeftHandRingPinky(  )         { return mFBActor->LeftHandRingPinky; }
	void    SetLeftHandPinkyIndex( double pValue )  { mFBActor->LeftHandPinkyIndex = pValue; }
	double  GetLeftHandPinkyIndex(  )        { return mFBActor->LeftHandPinkyIndex; }
	void    SetLeftHandPinkyMiddle( double pValue ) { mFBActor->LeftHandPinkyMiddle = pValue; }
	double  GetLeftHandPinkyMiddle(  )       { return mFBActor->LeftHandPinkyMiddle; }
	void    SetLeftHandPinkyRing( double pValue )   { mFBActor->LeftHandPinkyRing = pValue; }
	double  GetLeftHandPinkyRing(  )         { return mFBActor->LeftHandPinkyRing; }
	void    SetLeftHandPinkyPinky( double pValue )  { mFBActor->LeftHandPinkyPinky = pValue; }
	double  GetLeftHandPinkyPinky(  )        { return mFBActor->LeftHandPinkyPinky; }
	void    SetRightHandIndexIndex( double pValue )  { mFBActor->RightHandIndexIndex = pValue; }
	double  GetRightHandIndexIndex(  )        { return mFBActor->RightHandIndexIndex; }
	void    SetRightHandIndexMiddle( double pValue ) { mFBActor->RightHandIndexMiddle = pValue; }
	double  GetRightHandIndexMiddle(  )       { return mFBActor->RightHandIndexMiddle; }
	void    SetRightHandIndexRing( double pValue )   { mFBActor->RightHandIndexRing = pValue; }
	double  GetRightHandIndexRing(  )         { return mFBActor->RightHandIndexRing; }
	void    SetRightHandIndexPinky( double pValue )  { mFBActor->RightHandIndexPinky = pValue; }
	double  GetRightHandIndexPinky(  )        { return mFBActor->RightHandIndexPinky; }
	void    SetRightHandMiddleIndex( double pValue ) { mFBActor->RightHandMiddleIndex = pValue; }
	double  GetRightHandMiddleIndex(  )       { return mFBActor->RightHandMiddleIndex; }
	void    SetRightHandMiddleMiddle( double pValue ){ mFBActor->RightHandMiddleMiddle = pValue; }
	double  GetRightHandMiddleMiddle(  )      { return mFBActor->RightHandMiddleMiddle; }
	void    SetRightHandMiddleRing( double pValue )  { mFBActor->RightHandMiddleRing = pValue; }
	double  GetRightHandMiddleRing(  )        { return mFBActor->RightHandMiddleRing; }
	void    SetRightHandMiddlePinky( double pValue ) { mFBActor->RightHandMiddlePinky = pValue; }
	double  GetRightHandMiddlePinky(  )       { return mFBActor->RightHandMiddlePinky; }
	void    SetRightHandRingIndex( double pValue )   { mFBActor->RightHandRingIndex = pValue; }
	double  GetRightHandRingIndex(  )         { return mFBActor->RightHandRingIndex; }
	void    SetRightHandRingMiddle( double pValue )  { mFBActor->RightHandRingMiddle = pValue; }
	double  GetRightHandRingMiddle(  )        { return mFBActor->RightHandRingMiddle; }
	void    SetRightHandRingRing( double pValue )    { mFBActor->RightHandRingRing = pValue; }
	double  GetRightHandRingRing(  )          { return mFBActor->RightHandRingRing; }
	void    SetRightHandRingPinky( double pValue )   { mFBActor->RightHandRingPinky = pValue; }
	double  GetRightHandRingPinky(  )         { return mFBActor->RightHandRingPinky; }
	void    SetRightHandPinkyIndex( double pValue )  { mFBActor->RightHandPinkyIndex = pValue; }
	double  GetRightHandPinkyIndex(  )        { return mFBActor->RightHandPinkyIndex; }
	void    SetRightHandPinkyMiddle( double pValue ) { mFBActor->RightHandPinkyMiddle = pValue; }
	double  GetRightHandPinkyMiddle(  )       { return mFBActor->RightHandPinkyMiddle; }
	void    SetRightHandPinkyRing( double pValue )   { mFBActor->RightHandPinkyRing = pValue; }
	double  GetRightHandPinkyRing(  )         { return mFBActor->RightHandPinkyRing; }
	void    SetRightHandPinkyPinky( double pValue )  { mFBActor->RightHandPinkyPinky = pValue; }
	double  GetRightHandPinkyPinky(  )        { return mFBActor->RightHandPinkyPinky; }
	void	SetFKFingerMultiplier( double pValue )	{ mFBActor->FKFingerMultiplier = pValue; }
	double	GetFKFingerMultiplier(  )				{ return mFBActor->FKFingerMultiplier; }
	void	SetFKFingerTipMultiplier( double pValue )	{ mFBActor->FKFingerTipMultiplier = pValue; }
	double	GetFKFingerTipMultiplier(  )				{ return mFBActor->FKFingerTipMultiplier; }
	void	SetFKThumbTipMultiplier( double pValue )	{ mFBActor->FKThumbTipMultiplier = pValue; }
	double	GetFKThumbTipMultiplier(  )					{ return mFBActor->FKThumbTipMultiplier; }
	void	SetHumanFingerLimits( bool pValue )			{ mFBActor->HumanFingerLimits = pValue; }
	bool	GetHumanFingerLimits(  )					{ return mFBActor->HumanFingerLimits; }
    void SetActorTranslation( FBVector3d_Wrapper& pTranslationVector ) { mFBActor->SetActorTranslation( *(pTranslationVector.mFBVector3d) ); }
	void SetVisibility( bool pState ) { mFBActor->Visibility = pState; }
	bool GetVisibility( ) { return mFBActor->Visibility; }

};
#endif // pyfbactor_h__