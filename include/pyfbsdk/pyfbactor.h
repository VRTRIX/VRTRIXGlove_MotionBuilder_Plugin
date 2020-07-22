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
	bool GetSkeletonVisibility() { return mFBActor->SkeletonVisibility; }
	void SetSkeletonVisibility( bool pState ) { mFBActor->SkeletonVisibility = pState; }
	bool GetPivotPointsVisibility() { return mFBActor->PivotPointsVisibility; }
	void SetPivotPointsVisibility( bool pState ) { mFBActor->PivotPointsVisibility = pState; }
	void SetHeadOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->HeadOffsetT = *pOffset.mFBVector3d; }
	object GetHeadOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->HeadOffsetT ); }
	void SetHeadOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->HeadOffsetR = *pOffset.mFBVector3d; }
	object GetHeadOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->HeadOffsetR ); }
	void SetNeckOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->NeckOffsetT = *pOffset.mFBVector3d; }
	object GetNeckOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->NeckOffsetT ); }
	void SetNeckOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->NeckOffsetR = *pOffset.mFBVector3d; }
	object GetNeckOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->NeckOffsetR ); }
	void SetChestOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->ChestOffsetT = *pOffset.mFBVector3d; }
	object GetChestOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->ChestOffsetT ); }
	void SetChestOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->ChestOffsetR = *pOffset.mFBVector3d; }
	object GetChestOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->ChestOffsetR ); }
	void SetLeftCollarOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftCollarOffsetT = *pOffset.mFBVector3d; }
	object GetLeftCollarOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftCollarOffsetT ); }
	void SetLeftCollarOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftCollarOffsetR = *pOffset.mFBVector3d; }
	object GetLeftCollarOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftCollarOffsetR ); }
	void SetRightCollarOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightCollarOffsetT = *pOffset.mFBVector3d; }
	object GetRightCollarOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightCollarOffsetT ); }
	void SetRightCollarOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightCollarOffsetR = *pOffset.mFBVector3d; }
	object GetRightCollarOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightCollarOffsetR ); }
	void SetLeftShoulderOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftShoulderOffsetT = *pOffset.mFBVector3d; }
	object GetLeftShoulderOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftShoulderOffsetT ); }
	void SetLeftShoulderOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftShoulderOffsetR = *pOffset.mFBVector3d; }
	object GetLeftShoulderOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftShoulderOffsetR ); }
	void SetRightShoulderOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightShoulderOffsetT = *pOffset.mFBVector3d; }
	object GetRightShoulderOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightShoulderOffsetT ); }
	void SetRightShoulderOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightShoulderOffsetR = *pOffset.mFBVector3d; }
	object GetRightShoulderOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightShoulderOffsetR ); }
	void SetLeftElbowOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftElbowOffsetT = *pOffset.mFBVector3d; }
	object GetLeftElbowOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftElbowOffsetT ); }
	void SetLeftElbowOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftElbowOffsetR = *pOffset.mFBVector3d; }
	object GetLeftElbowOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftElbowOffsetR ); }
	void SetRightElbowOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightElbowOffsetT = *pOffset.mFBVector3d; }
	object GetRightElbowOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightElbowOffsetT ); }
	void SetRightElbowOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightElbowOffsetR = *pOffset.mFBVector3d; }
	object GetRightElbowOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightElbowOffsetR ); }
	void SetLeftWristOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftWristOffsetT = *pOffset.mFBVector3d; }
	object GetLeftWristOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftWristOffsetT ); }
	void SetLeftWristOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftWristOffsetR = *pOffset.mFBVector3d; }
	object GetLeftWristOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftWristOffsetR ); }
	void SetRightWristOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightWristOffsetT = *pOffset.mFBVector3d; }
	object GetRightWristOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightWristOffsetT ); }
	void SetRightWristOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightWristOffsetR = *pOffset.mFBVector3d; }
	object GetRightWristOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightWristOffsetR ); }
	void SetWaistOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->WaistOffsetT = *pOffset.mFBVector3d; }
	object GetWaistOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->WaistOffsetT ); }
	void SetWaistOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->WaistOffsetR = *pOffset.mFBVector3d; }
	object GetWaistOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->WaistOffsetR ); }
	void SetHipsOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->HipsOffsetT = *pOffset.mFBVector3d; }
	object GetHipsOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->HipsOffsetT ); }
	void SetHipsOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->HipsOffsetR = *pOffset.mFBVector3d; }
	object GetHipsOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->HipsOffsetR ); }
	void SetLeftHipOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftHipOffsetT = *pOffset.mFBVector3d; }
	object GetLeftHipOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftHipOffsetT ); }
	void SetLeftHipOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftHipOffsetR = *pOffset.mFBVector3d; }
	object GetLeftHipOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftHipOffsetR ); }
	void SetRightHipOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightHipOffsetT = *pOffset.mFBVector3d; }
	object GetRightHipOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightHipOffsetT ); }
	void SetRightHipOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightHipOffsetR = *pOffset.mFBVector3d; }
	object GetRightHipOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightHipOffsetR ); }
	void SetLeftKneeOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftKneeOffsetT = *pOffset.mFBVector3d; }
	object GetLeftKneeOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftKneeOffsetT ); }
	void SetLeftKneeOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftKneeOffsetR = *pOffset.mFBVector3d; }
	object GetLeftKneeOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftKneeOffsetR ); }
	void SetRightKneeOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightKneeOffsetT = *pOffset.mFBVector3d; }
	object GetRightKneeOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightKneeOffsetT ); }
	void SetRightKneeOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightKneeOffsetR = *pOffset.mFBVector3d; }
	object GetRightKneeOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightKneeOffsetR ); }
	void SetLeftAnkleOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftAnkleOffsetT = *pOffset.mFBVector3d; }
	object GetLeftAnkleOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftAnkleOffsetT ); }
	void SetLeftAnkleOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftAnkleOffsetR = *pOffset.mFBVector3d; }
	object GetLeftAnkleOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftAnkleOffsetR ); }
	void SetRightAnkleOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightAnkleOffsetT = *pOffset.mFBVector3d; }
	object GetRightAnkleOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightAnkleOffsetT ); }
	void SetRightAnkleOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightAnkleOffsetR = *pOffset.mFBVector3d; }
	object GetRightAnkleOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightAnkleOffsetR ); }
	void SetLeftFootOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftFootOffsetT = *pOffset.mFBVector3d; }
	object GetLeftFootOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftFootOffsetT ); }
	void SetLeftFootOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftFootOffsetR = *pOffset.mFBVector3d; }
	object GetLeftFootOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftFootOffsetR ); }
	void SetRightFootOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightFootOffsetT = *pOffset.mFBVector3d; }
	object GetRightFootOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightFootOffsetT ); }
	void SetRightFootOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightFootOffsetR = *pOffset.mFBVector3d; }
	object GetRightFootOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightFootOffsetR ); }
	void SetLeftThumbAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftThumbAOffsetT = *pOffset.mFBVector3d; }
	object GetLeftThumbAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftThumbAOffsetT ); }
	void SetLeftThumbAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftThumbAOffsetR = *pOffset.mFBVector3d; }
	object GetLeftThumbAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftThumbAOffsetR ); }
	void SetLeftThumbBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftThumbBOffsetT = *pOffset.mFBVector3d; }
	object GetLeftThumbBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftThumbBOffsetT ); }
	void SetLeftThumbBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftThumbBOffsetR = *pOffset.mFBVector3d; }
	object GetLeftThumbBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftThumbBOffsetR ); }
	void SetLeftThumbCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftThumbCOffsetT = *pOffset.mFBVector3d; }
	object GetLeftThumbCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftThumbCOffsetT ); }
	void SetLeftThumbCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftThumbCOffsetR = *pOffset.mFBVector3d; }
	object GetLeftThumbCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftThumbCOffsetR ); }
	void SetLeftIndexAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftIndexAOffsetT = *pOffset.mFBVector3d; }
	object GetLeftIndexAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftIndexAOffsetT ); }
	void SetLeftIndexAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftIndexAOffsetR = *pOffset.mFBVector3d; }
	object GetLeftIndexAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftIndexAOffsetR ); }
	void SetLeftIndexBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftIndexBOffsetT = *pOffset.mFBVector3d; }
	object GetLeftIndexBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftIndexBOffsetT ); }
	void SetLeftIndexBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftIndexBOffsetR = *pOffset.mFBVector3d; }
	object GetLeftIndexBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftIndexBOffsetR ); }
	void SetLeftIndexCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftIndexCOffsetT = *pOffset.mFBVector3d; }
	object GetLeftIndexCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftIndexCOffsetT ); }
	void SetLeftIndexCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftIndexCOffsetR = *pOffset.mFBVector3d; }
	object GetLeftIndexCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftIndexCOffsetR ); }
	void SetLeftMiddleAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftMiddleAOffsetT = *pOffset.mFBVector3d; }
	object GetLeftMiddleAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftMiddleAOffsetT ); }
	void SetLeftMiddleAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftMiddleAOffsetR = *pOffset.mFBVector3d; }
	object GetLeftMiddleAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftMiddleAOffsetR ); }
	void SetLeftMiddleBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftMiddleBOffsetT = *pOffset.mFBVector3d; }
	object GetLeftMiddleBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftMiddleBOffsetT ); }
	void SetLeftMiddleBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftMiddleBOffsetR = *pOffset.mFBVector3d; }
	object GetLeftMiddleBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftMiddleBOffsetR ); }
	void SetLeftMiddleCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftMiddleCOffsetT = *pOffset.mFBVector3d; }
	object GetLeftMiddleCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftMiddleCOffsetT ); }
	void SetLeftMiddleCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftMiddleCOffsetR = *pOffset.mFBVector3d; }
	object GetLeftMiddleCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftMiddleCOffsetR ); }
	void SetLeftRingAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftRingAOffsetT = *pOffset.mFBVector3d; }
	object GetLeftRingAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftRingAOffsetT ); }
	void SetLeftRingAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftRingAOffsetR = *pOffset.mFBVector3d; }
	object GetLeftRingAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftRingAOffsetR ); }
	void SetLeftRingBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftRingBOffsetT = *pOffset.mFBVector3d; }
	object GetLeftRingBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftRingBOffsetT ); }
	void SetLeftRingBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftRingBOffsetR = *pOffset.mFBVector3d; }
	object GetLeftRingBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftRingBOffsetR ); }
	void SetLeftRingCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftRingCOffsetT = *pOffset.mFBVector3d; }
	object GetLeftRingCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftRingCOffsetT ); }
	void SetLeftRingCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftRingCOffsetR = *pOffset.mFBVector3d; }
	object GetLeftRingCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftRingCOffsetR ); }
	void SetLeftPinkyAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftPinkyAOffsetT = *pOffset.mFBVector3d; }
	object GetLeftPinkyAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftPinkyAOffsetT ); }
	void SetLeftPinkyAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftPinkyAOffsetR = *pOffset.mFBVector3d; }
	object GetLeftPinkyAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftPinkyAOffsetR ); }
	void SetLeftPinkyBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftPinkyBOffsetT = *pOffset.mFBVector3d; }
	object GetLeftPinkyBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftPinkyBOffsetT ); }
	void SetLeftPinkyBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftPinkyBOffsetR = *pOffset.mFBVector3d; }
	object GetLeftPinkyBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftPinkyBOffsetR ); }
	void SetLeftPinkyCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftPinkyCOffsetT = *pOffset.mFBVector3d; }
	object GetLeftPinkyCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftPinkyCOffsetT ); }
	void SetLeftPinkyCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->LeftPinkyCOffsetR = *pOffset.mFBVector3d; }
	object GetLeftPinkyCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->LeftPinkyCOffsetR ); }
	void SetRightThumbAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightThumbAOffsetT = *pOffset.mFBVector3d; }
	object GetRightThumbAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightThumbAOffsetT ); }
	void SetRightThumbAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightThumbAOffsetR = *pOffset.mFBVector3d; }
	object GetRightThumbAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightThumbAOffsetR ); }
	void SetRightThumbBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightThumbBOffsetT = *pOffset.mFBVector3d; }
	object GetRightThumbBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightThumbBOffsetT ); }
	void SetRightThumbBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightThumbBOffsetR = *pOffset.mFBVector3d; }
	object GetRightThumbBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightThumbBOffsetR ); }
	void SetRightThumbCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightThumbCOffsetT = *pOffset.mFBVector3d; }
	object GetRightThumbCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightThumbCOffsetT ); }
	void SetRightThumbCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightThumbCOffsetR = *pOffset.mFBVector3d; }
	object GetRightThumbCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightThumbCOffsetR ); }
	void SetRightIndexAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightIndexAOffsetT = *pOffset.mFBVector3d; }
	object GetRightIndexAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightIndexAOffsetT ); }
	void SetRightIndexAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightIndexAOffsetR = *pOffset.mFBVector3d; }
	object GetRightIndexAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightIndexAOffsetR ); }
	void SetRightIndexBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightIndexBOffsetT = *pOffset.mFBVector3d; }
	object GetRightIndexBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightIndexBOffsetT ); }
	void SetRightIndexBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightIndexBOffsetR = *pOffset.mFBVector3d; }
	object GetRightIndexBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightIndexBOffsetR ); }
	void SetRightIndexCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightIndexCOffsetT = *pOffset.mFBVector3d; }
	object GetRightIndexCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightIndexCOffsetT ); }
	void SetRightIndexCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightIndexCOffsetR = *pOffset.mFBVector3d; }
	object GetRightIndexCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightIndexCOffsetR ); }
	void SetRightMiddleAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightMiddleAOffsetT = *pOffset.mFBVector3d; }
	object GetRightMiddleAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightMiddleAOffsetT ); }
	void SetRightMiddleAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightMiddleAOffsetR = *pOffset.mFBVector3d; }
	object GetRightMiddleAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightMiddleAOffsetR ); }
	void SetRightMiddleBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightMiddleBOffsetT = *pOffset.mFBVector3d; }
	object GetRightMiddleBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightMiddleBOffsetT ); }
	void SetRightMiddleBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightMiddleBOffsetR = *pOffset.mFBVector3d; }
	object GetRightMiddleBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightMiddleBOffsetR ); }
	void SetRightMiddleCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightMiddleCOffsetT = *pOffset.mFBVector3d; }
	object GetRightMiddleCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightMiddleCOffsetT ); }
	void SetRightMiddleCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightMiddleCOffsetR = *pOffset.mFBVector3d; }
	object GetRightMiddleCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightMiddleCOffsetR ); }
	void SetRightRingAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightRingAOffsetT = *pOffset.mFBVector3d; }
	object GetRightRingAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightRingAOffsetT ); }
	void SetRightRingAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightRingAOffsetR = *pOffset.mFBVector3d; }
	object GetRightRingAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightRingAOffsetR ); }
	void SetRightRingBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightRingBOffsetT = *pOffset.mFBVector3d; }
	object GetRightRingBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightRingBOffsetT ); }
	void SetRightRingBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightRingBOffsetR = *pOffset.mFBVector3d; }
	object GetRightRingBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightRingBOffsetR ); }
	void SetRightRingCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightRingCOffsetT = *pOffset.mFBVector3d; }
	object GetRightRingCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightRingCOffsetT ); }
	void SetRightRingCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightRingCOffsetR = *pOffset.mFBVector3d; }
	object GetRightRingCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightRingCOffsetR ); }
	void SetRightPinkyAOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightPinkyAOffsetT = *pOffset.mFBVector3d; }
	object GetRightPinkyAOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightPinkyAOffsetT ); }
	void SetRightPinkyAOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightPinkyAOffsetR = *pOffset.mFBVector3d; }
	object GetRightPinkyAOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightPinkyAOffsetR ); }
	void SetRightPinkyBOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightPinkyBOffsetT = *pOffset.mFBVector3d; }
	object GetRightPinkyBOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightPinkyBOffsetT ); }
	void SetRightPinkyBOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightPinkyBOffsetR = *pOffset.mFBVector3d; }
	object GetRightPinkyBOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightPinkyBOffsetR ); }
	void SetRightPinkyCOffsetT( FBVector3d_Wrapper& pOffset ) { mFBActor->RightPinkyCOffsetT = *pOffset.mFBVector3d; }
	object GetRightPinkyCOffsetT(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightPinkyCOffsetT ); }
	void SetRightPinkyCOffsetR( FBVector3d_Wrapper& pOffset ) { mFBActor->RightPinkyCOffsetR = *pOffset.mFBVector3d; }
	object GetRightPinkyCOffsetR(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBActor->RightPinkyCOffsetR ); }
	void SetManipulateOffsets( bool pManipulateOffsets ) { mFBActor->ManipulateOffsets = pManipulateOffsets; }
	bool GetManipulateOffsets(  ) { return mFBActor->ManipulateOffsets; }
	void SetIKManip( bool pIKManip ) { mFBActor->IKManip = pIKManip; }
	bool GetIKManip(  ) { return mFBActor->IKManip; }

};
#endif // pyfbactor_h__