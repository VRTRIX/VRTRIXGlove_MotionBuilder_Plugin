#ifndef pyfbdeck_h__
#define pyfbdeck_h__
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

// =======================================================================================
// FBDeck
// =======================================================================================
void FBDeck_Init();

class PYSDK_DLL FBDeck_Wrapper : public FBComponent_Wrapper {
public:
	FBDeck* mFBDeck;
public:
	FBDeck_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBDeck = (FBDeck*)pFBComponent; }	
	virtual ~FBDeck_Wrapper( ) {}
	void CueAt(FBTime_Wrapper* pTime) { mFBDeck->CueAt( *(pTime->mFBTime) ); }
	void DeckAutoCommandsNotify() { mFBDeck->DeckAutoCommandsNotify(  ); }
	void DeckStatusUpdateNotify() { mFBDeck->DeckStatusUpdateNotify(  ); }
	void Eject() { mFBDeck->Eject(  ); }
	void Forward() { mFBDeck->Forward(  ); }
	FBTime_Wrapper* GetTime() { return FBTime_Wrapper_Factory( mFBDeck->GetTime(  )); }
	void Play(double pSpeed = 1.0) { mFBDeck->Play( pSpeed ); }
	void ReversePlay(double pSpeed = 1.0) { mFBDeck->ReversePlay( pSpeed ); }
	void Rewind() { mFBDeck->Rewind(  ); }
	void StepBack() { mFBDeck->StepBack(  ); }
	void StepForward() { mFBDeck->StepForward(  ); }
	void Stop() { mFBDeck->Stop(  ); }
	void ThreadSync() { mFBDeck->ThreadSync(  ); }
	bool GetCassetteInside(  ) { return mFBDeck->CassetteInside; }
	void SetEE( bool pEE ) { mFBDeck->EE = pEE; }
	bool GetEE(  ) { return mFBDeck->EE; }
	void SetIconFilename( const char* pIconFilename ) { mFBDeck->IconFilename = pIconFilename; }
	const char* GetIconFilename(  ) { return mFBDeck->IconFilename; }
	void SetLatency( FBTime_Wrapper& pLatency ) { mFBDeck->Latency = *(pLatency.mFBTime); }
	FBTime_Wrapper* GetLatency(  ) { return FBTime_Wrapper_Factory( mFBDeck->Latency ); }
	void SetOffset( FBTime_Wrapper& pOffset ) { mFBDeck->Offset = *(pOffset.mFBTime); }
	FBTime_Wrapper* GetOffset(  ) { return FBTime_Wrapper_Factory( mFBDeck->Offset ); }
	void SetOnline( bool pOnline ) { mFBDeck->Online = pOnline; }
	bool GetOnline(  ) { return mFBDeck->Online; }
	bool GetPlayingBackward(  ) { return mFBDeck->PlayingBackward; }
	bool GetPlayingForward(  ) { return mFBDeck->PlayingForward; }
	void SetPostRoll( FBTime_Wrapper& pPostRoll ) { mFBDeck->PostRoll = *(pPostRoll.mFBTime); }
	FBTime_Wrapper* GetPostRoll(  ) { return FBTime_Wrapper_Factory( mFBDeck->PostRoll ); }
	void SetPreRoll( FBTime_Wrapper& pPreRoll ) { mFBDeck->PreRoll = *(pPreRoll.mFBTime); }
	FBTime_Wrapper* GetPreRoll(  ) { return FBTime_Wrapper_Factory( mFBDeck->PreRoll ); }
	void SetStandBy( bool pStandBy ) { mFBDeck->StandBy = pStandBy; }
	bool GetStandBy(  ) { return mFBDeck->StandBy; }
	void SetTransportControl( FBDeckTransportMode pTransportControl ) { mFBDeck->TransportControl = pTransportControl; }
	FBDeckTransportMode GetTransportControl(  ) { return mFBDeck->TransportControl; }
	void SetUniqueName( const char* pUniqueName ) { mFBDeck->UniqueName = pUniqueName; }
	const char* GetUniqueName(  ) { return mFBDeck->UniqueName; }
};
#endif // pyfbdeck_h__