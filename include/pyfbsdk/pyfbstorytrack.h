#ifndef pyfbstorytrack_h__
#define pyfbstorytrack_h__
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
#include "pyfbcharacter.h"
#include "pyfbcharacterface.h"			// Requires FBModelList_Wrapper from pyfbarraytemplate.h
#include "pyfbcharacterposeoptions.h"
#include "pyfbcharacterpose.h"
#include "pyfbcontrolset.h"
#include "pyfbstoryfolder.h"

// =======================================================================================
// FBStoryTrack
// =======================================================================================
void FBStoryTrack_Init();

class PYSDK_DLL FBStoryTrack_Wrapper : public FBConstraint_Wrapper {
public:
	FBStoryTrack* mFBStoryTrack;
public:
	FBStoryTrack_Wrapper( FBComponent* pFBComponent ) : FBConstraint_Wrapper( pFBComponent ) { mFBStoryTrack = (FBStoryTrack*)pFBComponent; }
    FBStoryTrack_Wrapper( FBStoryTrackType pTrackType, FBStoryFolder_Wrapper* pFolder=NULL ) : FBConstraint_Wrapper( new FBStoryTrack( pTrackType, pFolder ? pFolder->mFBStoryFolder : 0 )) { mFBStoryTrack = (FBStoryTrack*)mFBComponent; }
    FBStoryTrack_Wrapper( FBComponent_Wrapper& pTrackType, FBStoryFolder_Wrapper* pFolder=NULL ) : FBConstraint_Wrapper( new FBStoryTrack( pTrackType.mFBComponent, pFolder ? pFolder->mFBStoryFolder : 0 )) { mFBStoryTrack = (FBStoryTrack*)mFBComponent; }
	virtual ~FBStoryTrack_Wrapper( ) {}
	void ChangeDetailsBegin() { mFBStoryTrack->ChangeDetailsBegin(  ); }
	void ChangeDetailsEnd() { mFBStoryTrack->ChangeDetailsEnd(  ); }
	void EnableBodyPart(FBStoryTrackBodyPart pPart, bool pEnable) { mFBStoryTrack->EnableBodyPart( pPart, pEnable ); }
	void AddClip(FBComponent_Wrapper& pClip, FBTime_Wrapper& pTime) {mFBStoryTrack->AddClip(pClip.mFBComponent, *(pTime.mFBTime));}
    object CopyTakeIntoTrack_1(FBTimeSpan_Wrapper& pTimeSpan, FBTake_Wrapper& pTake, FBTime_Wrapper* pOutputOffset = nullptr, bool pMakeUndoable = true);
	object CopyTakeIntoTrack_2(FBTimeSpan_Wrapper& pTimeSpan, FBTake_Wrapper& pTake, bool pConnectToCurrentTake, FBTime_Wrapper* pOutputOffset = nullptr, bool pMakeUndoable = true);
	void FBDelete() { mFBStoryTrack->FBDelete(  ); }
	void Load(bool pLoad) { mFBStoryTrack->Load( pLoad ); }
	bool IsBodyPartEnabled(FBStoryTrackBodyPart pPart) { return mFBStoryTrack->IsBodyPartEnabled( pPart ); }
	void SetAcceptKey( bool pAcceptKey ) { mFBStoryTrack->AcceptKey = pAcceptKey; }
	bool GetAcceptKey(  ) { return mFBStoryTrack->AcceptKey; }
	void SetAudioOutIndex( int pAudioOutIndex ) { mFBStoryTrack->AudioOutIndex = pAudioOutIndex; }
	int GetAudioOutIndex(  ) { return mFBStoryTrack->AudioOutIndex; }
	void SetWeight( double pWeight ) { mFBStoryTrack->Weight = pWeight; }
	double GetWeight(  ) { return mFBStoryTrack->Weight; }
	void SetCharacterIndex( int pCharacterIndex ) { mFBStoryTrack->CharacterIndex = pCharacterIndex; }
	int GetCharacterIndex(  ) { return mFBStoryTrack->CharacterIndex; }
	void SetCharacter( FBCharacter_Wrapper& pCharacter ) { mFBStoryTrack->Character = pCharacter.mFBCharacter; }
	object GetCharacter(  ) { return FBWrapperFactory::TheOne().WrapFBObject(mFBStoryTrack->Character); }
	object GetClips(  ) { return FBPropertyListStoryClip_Wrapper_Factory( mFBStoryTrack->Clips ); }
	object GetDetails(  ) { return FBPropertyListStoryDetails_Wrapper_Factory( mFBStoryTrack->Details ); }
	void SetGhost( bool pGhost ) { mFBStoryTrack->Ghost = pGhost; }
	bool GetGhost(  ) { return mFBStoryTrack->Ghost; }
	void SetGhostModel( bool pGhostModel ) { mFBStoryTrack->GhostModel = pGhostModel; }
	bool GetGhostModel(  ) { return mFBStoryTrack->GhostModel; }
	void SetGhostPivot( bool pGhostPivot ) { mFBStoryTrack->GhostPivot = pGhostPivot; }
	bool GetGhostPivot(  ) { return mFBStoryTrack->GhostPivot; }
	void SetGhostTravelling( bool pGhostTravelling ) { mFBStoryTrack->GhostTravelling = pGhostTravelling; }
	bool GetGhostTravelling(  ) { return mFBStoryTrack->GhostTravelling; }
    void SetGhostShowTrackMode( FBStoryTrackGhostShowMode pGhostShowTrackMode ) { mFBStoryTrack->GhostShowTrackMode = pGhostShowTrackMode; }
    FBStoryTrackGhostShowMode GetGhostShowTrackMode(  ) { return mFBStoryTrack->GhostShowTrackMode; }
	void SetLabel( const char* pLabel ) { mFBStoryTrack->Label = pLabel; }
	const char* GetLabel(  ) { return mFBStoryTrack->Label; }
	void SetMute( bool pMute ) { mFBStoryTrack->Mute = pMute; }
	bool GetMute(  ) { return mFBStoryTrack->Mute; }
	void SetOffsetEnable( bool pOffsetEnable ) { mFBStoryTrack->OffsetEnable = pOffsetEnable; }
	bool GetOffsetEnable(  ) { return mFBStoryTrack->OffsetEnable; }
	object GetParentFolder(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryTrack->ParentFolder ); }
	object GetParentTrack(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryTrack->ParentTrack ); }
	void SetPassThrough( bool pPassThrough ) { mFBStoryTrack->PassThrough = pPassThrough; }
	bool GetPassThrough(  ) { return mFBStoryTrack->PassThrough; }
	void SetReferenceMode( FBStoryTrackRefMode pReferenceMode ) { mFBStoryTrack->ReferenceMode = pReferenceMode; }
	FBStoryTrackRefMode GetReferenceMode(  ) { return mFBStoryTrack->ReferenceMode; }
	void SetShowBackplate( bool pShowBackplate ) { mFBStoryTrack->ShowBackplate = pShowBackplate; }
	bool GetShowBackplate(  ) { return mFBStoryTrack->ShowBackplate; }
	void SetShowFrontplate( bool pShowFrontplate ) { mFBStoryTrack->ShowFrontplate = pShowFrontplate; }
	bool GetShowFrontplate(  ) { return mFBStoryTrack->ShowFrontplate; }
	void SetSolo( bool pSolo ) { mFBStoryTrack->Solo = pSolo; }
	bool GetSolo(  ) { return mFBStoryTrack->Solo; }
	void SetRecordClipPath( const char* pRecordClipPath ) { mFBStoryTrack->RecordClipPath = pRecordClipPath; }
	const char* GetRecordClipPath(  ) { return mFBStoryTrack->RecordClipPath; }
	void SetClipNameConvention( const char* pClipNameConvention ) { mFBStoryTrack->ClipNameConvention = pClipNameConvention; }
	const char* GetClipNameConvention(  ) { return mFBStoryTrack->ClipNameConvention; }
	void SetRecordTrack( bool pRecordTrack ) { mFBStoryTrack->RecordTrack = pRecordTrack; }
	bool GetRecordTrack(  ) { return mFBStoryTrack->RecordTrack; }
	object GetSubTracks(  ) { return FBPropertyListStorySubTrack_Wrapper_Factory( mFBStoryTrack->SubTracks ); }
    object CreateSubTrack(FBStoryTrackType pTrackType, FBStoryTrackRefMode pRefMode){ return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryTrack->CreateSubTrack(pTrackType,pRefMode)) ; }
	object GetTrackVideo(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryTrack->TrackVideo ); }
	FBStoryTrackType GetType(  ) { return mFBStoryTrack->Type; }
};
#endif // pyfbstorytrack_h__