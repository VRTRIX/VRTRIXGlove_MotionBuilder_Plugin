#ifndef pyfbstoryclip_h__
#define pyfbstoryclip_h__
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
#include "pyfbtake.h"
#include "pyfbgeometry.h"
#include "pyfbvideo.h"
#include "pyfbaudioclip.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbpose.h"
#include "pyfbconstraint.h"
#include "pyfbcamera.h"
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
#include "pyfbcharacter.h"
#include "pyfbcharacterface.h"			// Requires FBModelList_Wrapper from pyfbarraytemplate.h
#include "pyfbcharacterposeoptions.h"
#include "pyfbcharacterpose.h"
#include "pyfbcontrolset.h"
#include "pyfbstoryfolder.h"
#include "pyfbstorytrack.h"

// =======================================================================================
// FBStoryClip
// =======================================================================================
void FBStoryClip_Init();

class PYSDK_DLL FBStoryClip_Wrapper : public FBComponent_Wrapper {
public:
	FBStoryClip* mFBStoryClip;
public:
	FBStoryClip_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBStoryClip = (FBStoryClip*)pFBComponent; }
	FBStoryClip_Wrapper( FBComponent_Wrapper& pClipObject, FBStoryTrack_Wrapper& pTrack, FBTime_Wrapper& pTime ) : FBComponent_Wrapper( new FBStoryClip( pClipObject.mFBComponent, pTrack.mFBStoryTrack, *(pTime.mFBTime))) { mFBStoryClip = (FBStoryClip*)mFBComponent; }
	FBStoryClip_Wrapper( const char* pFilePath, FBStoryTrack_Wrapper& pTrack, FBTime_Wrapper& pTime ) : FBComponent_Wrapper( new FBStoryClip( pFilePath, pTrack.mFBStoryTrack, *(pTime.mFBTime))) { mFBStoryClip = (FBStoryClip*)mFBComponent; }
    FBStoryClip_Wrapper( const char* pFilePath, FBStoryTrack_Wrapper& pTrack, FBTime_Wrapper& pTime, FBTime_Wrapper& pTimeOffset ) : FBComponent_Wrapper( new FBStoryClip( pFilePath, pTrack.mFBStoryTrack, *(pTime.mFBTime), *(pTimeOffset.mFBTime))) { mFBStoryClip = (FBStoryClip*)mFBComponent; }
    virtual ~FBStoryClip_Wrapper( ) {}
	bool ExportToFile(const char* pOutputFile) { return mFBStoryClip->ExportToFile( pOutputFile ); }
	void FBDelete() { mFBStoryClip->FBDelete(  ); }
	object Clone() { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryClip->Clone() ); }

	list GetAffectedAnimationNodes(FBComponent_Wrapper& pClipObject)
    {
        list lResult;
        FBArrayTemplate<FBAnimationNode*> pAffectedAnimationNodes;
        mFBStoryClip->GetAffectedAnimationNodes( &pAffectedAnimationNodes, pClipObject.mFBComponent );
        for( int lIdx = 0; lIdx < pAffectedAnimationNodes.GetCount(); ++lIdx )
        {            
            lResult.append( FBWrapperFactory::TheOne().WrapFBObject( pAffectedAnimationNodes[lIdx] ) );
        }

        return lResult;
    }
    
	list GetAffectedObjects()
    {        
        list lResult;
        FBArrayTemplate<FBComponent*> pAffectedObjects;
        mFBStoryClip->GetAffectedObjects( &pAffectedObjects );
        for( int lIdx = 0; lIdx < pAffectedObjects.GetCount(); ++lIdx )
        {
            lResult.append( FBWrapperFactory::TheOne().WrapFBObject( pAffectedObjects[lIdx] ) );
        }

        return lResult;
    }

    bool DestinationSetObject( const char* pSrcName, FBComponent_Wrapper& pObjet)
    {
        return mFBStoryClip->DestinationSetObject ( pSrcName, pObjet.mFBComponent );
    }


	bool CanAssignSourcesToDestinations(  ) { return mFBStoryClip->CanAssignSourcesToDestinations(); }

	tuple GetAssignSourcesToDestinationsInfo()
	{
		list lSrcList;
		list lAvailableDstList;
		list lDefaultDstList;
		list lEffectiveDstList;

		FBStringList lSrcStringList, lAvailableDstStringList, lDefaultDstStringList, lEffectiveDstStringList;
		mFBStoryClip->GetAssignSourcesToDestinationsInfo( lSrcStringList, lAvailableDstStringList, lDefaultDstStringList, lEffectiveDstStringList );

		for( int i = 0; i < lSrcStringList.GetCount(); i++ )
			lSrcList.append( lSrcStringList[ i ] );

		for( int i = 0; i < lAvailableDstStringList.GetCount(); i++ )
			lAvailableDstList.append( lAvailableDstStringList[ i ] );

		for( int i = 0; i < lDefaultDstStringList.GetCount(); i++ )
			lDefaultDstList.append( lDefaultDstStringList[ i ] );

		for( int i = 0; i < lEffectiveDstStringList.GetCount(); i++ )
			lEffectiveDstList.append( lEffectiveDstStringList[ i ] );

		return make_tuple( lSrcList, lAvailableDstList, lDefaultDstList, lEffectiveDstList );
	}

	bool SetAssignSourcesToDestinationsInfo( list& pEffectiveDstList )
	{
		FBStringList lEffectiveDstStringList;

		for( long i = 0; i < len( pEffectiveDstList ); i++ )
			lEffectiveDstStringList.Add( boost::python::extract<const char*>( pEffectiveDstList[ i ] ) );

		return mFBStoryClip->SetAssignSourcesToDestinationsInfo( lEffectiveDstStringList );
	}

    bool UpdateFromCurrentTake()
    {
        return mFBStoryClip->UpdateFromCurrentTake();
    }    

	void Match() { mFBStoryClip->Match(  ); }
	void Match2(const char* pObjectName, FBStoryClipMatchingTimeType pTimeType, FBStoryClipMatchingTranslationType pTranslationType, FBStoryClipMatchingRotationType pRotationType)
	{
		mFBStoryClip->Match( FBString( pObjectName ), pTimeType, pTranslationType, pRotationType );
	}

	bool MakeWritable() { return mFBStoryClip->MakeWritable( ); }
	FBTime_Wrapper* Move(FBTime_Wrapper& pDelta, bool pForce = true) { return FBTime_Wrapper_Factory( mFBStoryClip->Move( *pDelta.mFBTime, pForce )); }
	FBTime_Wrapper* MoveTo(FBTime_Wrapper& pTime, bool pForce = true) { return FBTime_Wrapper_Factory( mFBStoryClip->MoveTo( *pTime.mFBTime, pForce )); }
	object Razor(FBTime_Wrapper& pTime) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryClip->Razor( *pTime.mFBTime )); }
	void SetAutoLoop( bool pAutoLoop ) { mFBStoryClip->AutoLoop = pAutoLoop; }
	bool GetAutoLoop(  ) { return mFBStoryClip->AutoLoop; }
	void SetColor( FBColor_Wrapper& pColor ) { mFBStoryClip->Color = *pColor.mFBColor; }
	FBColor_Wrapper* GetColor(  ) { return FBColor_Wrapper_Factory( mFBStoryClip->Color ); }
	void SetLoaded( bool pLoad ) { mFBStoryClip->Loaded = pLoad; }
	bool GetLoaded(  ) { return mFBStoryClip->Loaded; }
	void SetGhost( bool pGhost ) { mFBStoryClip->Ghost = pGhost; }
	bool GetGhost(  ) { return mFBStoryClip->Ghost; }
	void SetGhostModel( bool pGhostModel ) { mFBStoryClip->GhostModel = pGhostModel; }
	bool GetGhostModel(  ) { return mFBStoryClip->GhostModel; }
	void SetGhostPivot( bool pGhostPivot ) { mFBStoryClip->GhostPivot = pGhostPivot; }
	bool GetGhostPivot(  ) { return mFBStoryClip->GhostPivot; }
	void SetGhostTravelling( bool pGhostTravelling ) { mFBStoryClip->GhostTravelling = pGhostTravelling; }
	bool GetGhostTravelling(  ) { return mFBStoryClip->GhostTravelling; }
	void SetLoop( bool pLoop ) { mFBStoryClip->Loop = pLoop; }
	bool GetLoop(  ) { return mFBStoryClip->Loop; }
	void SetLoopTranslation( FBVector3d_Wrapper& pLoopTranslation ) { mFBStoryClip->LoopTranslation = *pLoopTranslation.mFBVector3d; }
	FBVector3d_Wrapper* GetLoopTranslation(  ) { return FBVector3d_Wrapper_Factory( mFBStoryClip->LoopTranslation ); }
	void SetGhostManipulatorOffset( FBVector3d_Wrapper& pGhostManipulatorOffset ) { mFBStoryClip->GhostManipulatorOffset = *pGhostManipulatorOffset.mFBVector3d; }
	FBVector3d_Wrapper* GetGhostManipulatorOffset(  ) { return FBVector3d_Wrapper_Factory( mFBStoryClip->GhostManipulatorOffset ); }
	object GetTravellingNode(  ) { return FBWrapperFactory::TheOne().WrapFBObject( &mFBStoryClip->TravellingNode ); }
	void SetTravellingNodeFunction( FBStoryClipNodeFunction pTravellingNodeFunction ) { mFBStoryClip->TravellingNodeFunction = pTravellingNodeFunction; }
	FBStoryClipNodeFunction GetTravellingNodeFunction(  ) { return mFBStoryClip->TravellingNodeFunction; }
	void SetGhostManipulatorMode( FBStoryClipGhostTimeMode pGhostManipulatorMode ) { mFBStoryClip->GhostManipulatorMode = pGhostManipulatorMode; }
	FBStoryClipGhostTimeMode GetGhostManipulatorMode(  ) { return mFBStoryClip->GhostManipulatorMode; }
	void SetGhostManipulatorCustomTime( FBTime_Wrapper& pGhostManipulatorCustomTime ) { mFBStoryClip->GhostManipulatorCustomTime = *pGhostManipulatorCustomTime.mFBTime; }
	FBTime_Wrapper* GetGhostManipulatorCustomTime(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->GhostManipulatorCustomTime ); }
	void SetMarkIn( FBTime_Wrapper& pMarkIn ) { mFBStoryClip->MarkIn = *pMarkIn.mFBTime; }
	FBTime_Wrapper* GetMarkIn(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->MarkIn ); }
	void SetMarkOut( FBTime_Wrapper& pMarkOut ) { mFBStoryClip->MarkOut = *pMarkOut.mFBTime; }
	FBTime_Wrapper* GetMarkOut(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->MarkOut ); }
	void SetOffset( FBTime_Wrapper& pOffset ) { mFBStoryClip->Offset = *pOffset.mFBTime; }
	FBTime_Wrapper* GetOffset(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->Offset ); }
	object GetPivots(  ) { return FBPropertyListPivot_Wrapper_Factory( mFBStoryClip->Pivots ); }
	void SetPostBlend( FBTimeSpan_Wrapper& pPostBlend ) { mFBStoryClip->PostBlend = *pPostBlend.mFBTimeSpan; }
	FBTimeSpan_Wrapper* GetPostBlend(  ) { return FBTimeSpan_Wrapper_Factory( mFBStoryClip->PostBlend ); }
	void SetPreBlend( FBTimeSpan_Wrapper& pPreBlend ) { mFBStoryClip->PreBlend = *pPreBlend.mFBTimeSpan; }
	FBTimeSpan_Wrapper* GetPreBlend(  ) { return FBTimeSpan_Wrapper_Factory( mFBStoryClip->PreBlend ); }
	void SetRotation( FBVector3d_Wrapper& pRotation ) { mFBStoryClip->Rotation = *pRotation.mFBVector3d; }
	FBVector3d_Wrapper* GetRotation(  ) { return FBVector3d_Wrapper_Factory( mFBStoryClip->Rotation ); }
	void SetScale( double pScale ) { mFBStoryClip->Scale = pScale; }
	double GetScale(  ) { return mFBStoryClip->Scale; }
	void SetShotActionStart( FBTime_Wrapper& pShotActionStart ) { mFBStoryClip->ShotActionStart = *pShotActionStart.mFBTime; }
	FBTime_Wrapper* GetShotActionStart(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->ShotActionStart ); }
	void SetShotActionStop( FBTime_Wrapper& pShotActionStop ) { mFBStoryClip->ShotActionStop = *pShotActionStop.mFBTime; }
	FBTime_Wrapper* GetShotActionStop(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->ShotActionStop ); }
	void SetShotStartStopLocked(bool pStartStopLocked) { mFBStoryClip->ShotStartStopLocked = pStartStopLocked; }
	bool GetShotStartStopLocked() { return mFBStoryClip->ShotStartStopLocked; }
	void SetShotBackplate( FBVideo_Wrapper& pShotBackplate ) { mFBStoryClip->ShotBackplate = pShotBackplate.mFBVideo; }
	object GetShotBackplate(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryClip->ShotBackplate ); }
	void SetShotFrontplate( FBVideo_Wrapper& pShotFrontplate ) { mFBStoryClip->ShotFrontplate = pShotFrontplate.mFBVideo; }
    object GetShotFrontplate(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryClip->ShotFrontplate ); }
	void SetShotCamera( FBCamera_Wrapper& pShotCamera ) { mFBStoryClip->ShotCamera = pShotCamera.mFBCamera; }
	object GetShotCamera(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryClip->ShotCamera ); }
	void SetShowBackplate( bool pShowBackplate ) { mFBStoryClip->ShowBackplate = pShowBackplate; }
	bool GetShowBackplate(  ) { return mFBStoryClip->ShowBackplate; }
	void SetShowFrontplate( bool pShowFrontplate ) { mFBStoryClip->ShowFrontplate = pShowFrontplate; }
	bool GetShowFrontplate(  ) { return mFBStoryClip->ShowFrontplate; }
	void SetShowGhostClipMode( FBStoryClipShowGhostMode pShowGhostClipMode ) { mFBStoryClip->ShowGhostClipMode = pShowGhostClipMode; }
	FBStoryClipShowGhostMode GetShowGhostClipMode(  ) { return mFBStoryClip->ShowGhostClipMode; }
    void SetGhostCustomTime( FBTime_Wrapper& pGhostCustomTime ) { mFBStoryClip->GhostCustomTime = *pGhostCustomTime.mFBTime; }
    FBTime_Wrapper* GetGhostCustomTime(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->GhostCustomTime ); }
    void SetSolvingMode( FBStoryClipSolveMode pSolvingMode ) { mFBStoryClip->SolvingMode = pSolvingMode; }
    FBStoryClipSolveMode GetSolvingMode(  ) { return mFBStoryClip->SolvingMode; }
	void SetSpeed( double pSpeed ) { mFBStoryClip->Speed = pSpeed; }
	double GetSpeed(  ) { return mFBStoryClip->Speed; }
	void SetStart( FBTime_Wrapper& pStart ) { mFBStoryClip->Start = *pStart.mFBTime; }
	FBTime_Wrapper* GetStart(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->Start ); }
	void SetStop( FBTime_Wrapper& pStop ) { mFBStoryClip->Stop = *pStop.mFBTime; }
	FBTime_Wrapper* GetStop(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->Stop ); }
	bool GetStartStopLocked() { return mFBStoryClip->StartStopLocked; }
	void SetStartStopLocked(bool pStartStopLocked) { return mFBStoryClip->StartStopLocked = pStartStopLocked; }
	void SetTranslation( FBVector3d_Wrapper& pTranslation ) { mFBStoryClip->Translation = *pTranslation.mFBVector3d; }
	FBVector3d_Wrapper* GetTranslation(  ) { return FBVector3d_Wrapper_Factory( mFBStoryClip->Translation ); }
    bool GetReadOnly() { return mFBStoryClip->GetReadOnly( ); }
    bool SetReadOnly(bool pMakeClipReadOnly, const char* pOutputFile = NULL) { return mFBStoryClip->SetReadOnly( pMakeClipReadOnly, pOutputFile ); }
    object GetAudioClip(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryClip->AudioClip ); }
    void SetAudioClip( FBAudioClip_Wrapper& pAudioClip ) { mFBStoryClip->AudioClip = pAudioClip.mFBAudioClip; }
	bool GetTimeWarpEnabled(  ) { return mFBStoryClip->TimeWarpEnabled; }
	void SetTimeWarpEnabled( bool pTimeWrapEnabled ) { mFBStoryClip->TimeWarpEnabled = pTimeWrapEnabled; }
	FBStoryClipTimeWarpInterpolatorType GetTimeWarpInterpolatorType(  ) { return mFBStoryClip->TimeWarpInterpolatorType; }
	void SetTimeWarpInterpolatorType( FBStoryClipTimeWarpInterpolatorType pTimeWarpInterpolatorType ) { mFBStoryClip->TimeWarpInterpolatorType = pTimeWarpInterpolatorType; }
	bool GetTimeWarpReverse(  ) { return mFBStoryClip->TimeWarpReverse; }
	void SetTimeWarpReverse( bool pTimeWrapReverse ) { mFBStoryClip->TimeWarpReverse = pTimeWrapReverse; }
	object GetCustomTimeWarp(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryClip->CustomTimeWarp ); }
	void SetTime(FBTime_Wrapper* pSrcIn, FBTime_Wrapper* pSrcOut, FBTime_Wrapper* pDstIn, FBTime_Wrapper* pDstOut, bool pUseAlternateSrcInProp = false) { mFBStoryClip->SetTime( pSrcIn ? pSrcIn->mFBTime : NULL, pSrcOut ? pSrcOut->mFBTime : NULL, pDstIn ? pDstIn->mFBTime : NULL, pDstOut ? pDstOut->mFBTime : NULL, pUseAlternateSrcInProp ); }

	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ClipPitch,            double );
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( LockPitchToSpeed,     bool ); 
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ImageSequence,                 bool );
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( UseSystemFrameRate,            bool );
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( FrameRate,                     double );
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ShowEmbeddedTimecode,          bool );

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ClipAnimationPath,             const char* );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ClipAudioPath,                 const char* );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ClipVideoPath,                 const char* );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ConnectedToTake,               bool );

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( MirrorAnimation,      bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( MirrorPlane,          FBStoryClipMirrorPlane );

	object OnChange();
protected:
	FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbstoryclip_h__