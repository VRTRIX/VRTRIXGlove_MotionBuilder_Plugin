#ifndef pyfbplayercontrol_h__
#define pyfbplayercontrol_h__
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
// FBPlayerControl
// =======================================================================================
void FBPlayerControl_Init();

class PYSDK_DLL FBPlayerControl_Wrapper : public FBComponent_Wrapper {
public:
	FBPlayerControl* mFBPlayerControl;
public:
	FBPlayerControl_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBPlayerControl = (FBPlayerControl*)pFBComponent; }
	FBPlayerControl_Wrapper(  );
	virtual ~FBPlayerControl_Wrapper( );
	FBTimeMode GetTransportFps() { return mFBPlayerControl->GetTransportFps(  ); }
	double GetTransportFpsValue( FBTimeMode pTimeMode = kFBTimeModeDefault ) { return mFBPlayerControl->GetTransportFpsValue( pTimeMode ); }
	FBTransportMode GetTransportMode() { return mFBPlayerControl->GetTransportMode(  ); }
	bool Goto(FBTime_Wrapper& pTime, FBTimeReferential pTimeReferential = kFBTimeReferentialAction) { return mFBPlayerControl->Goto( *pTime.mFBTime, pTimeReferential ); }
	bool GotoEnd(FBTimeReferential pTimeReferential = kFBTimeReferentialAction) { return mFBPlayerControl->GotoEnd( pTimeReferential ); }
	void GotoNextKey() { mFBPlayerControl->GotoNextKey(  ); }
	void GotoPreviousKey() { mFBPlayerControl->GotoPreviousKey(  ); }
	bool GotoStart(FBTimeReferential pTimeReferential = kFBTimeReferentialAction) { return mFBPlayerControl->GotoStart( pTimeReferential ); }
	void Key() { mFBPlayerControl->Key(  ); }
	bool Play(bool pUseMarkers = false) { return mFBPlayerControl->Play( pUseMarkers ); }
	bool PlayReverse(bool pUseMarkers = false) { return mFBPlayerControl->PlayReverse( pUseMarkers ); }
	bool Record(bool pOverrideTake = false, bool pCopyData = true) { return mFBPlayerControl->Record( pOverrideTake, pCopyData ); }
	void LockTransport( bool pLock ) { mFBPlayerControl->LockTransport(pLock);}
	bool IsLocked() { return mFBPlayerControl->IsLocked(); }
	FBTransportPlaySpeed GetPlaySpeedMode() { return mFBPlayerControl->GetPlaySpeedMode(); }
	double GetPlaySpeed() { return mFBPlayerControl->GetPlaySpeed(); }
	void SetPlaySpeedMode(FBTransportPlaySpeed pPlaySpeedMode) { mFBPlayerControl->SetPlaySpeedMode( pPlaySpeedMode ); }
	void SetPlaySpeed(double pPlaySpeed) { mFBPlayerControl->SetPlaySpeed( pPlaySpeed ); }
	void SetTransportFps(FBTimeMode pTimeMode, double pCustom = 0.0) { mFBPlayerControl->SetTransportFps( pTimeMode, pCustom ); }
	bool StepBackward(FBTimeReferential pTimeReferential = kFBTimeReferentialAction) { return mFBPlayerControl->StepBackward( pTimeReferential ); }
	bool StepForward(FBTimeReferential pTimeReferential = kFBTimeReferentialAction) { return mFBPlayerControl->StepForward( pTimeReferential ); }
	bool Stop() { return mFBPlayerControl->Stop(  ); }
	bool GetIsPlaying(  ) { return mFBPlayerControl->IsPlaying; }
	bool GetIsRecording(  ) { return mFBPlayerControl->IsRecording; }
	bool GetIsPlotting(  ) { return mFBPlayerControl->IsPlotting; }
	void SetLoopActive( bool pLoopActive ) { mFBPlayerControl->LoopActive = pLoopActive; }
	bool GetLoopActive(  ) { return mFBPlayerControl->LoopActive; }
	void SetLoopStart( FBTime_Wrapper& pLoopStart ) { mFBPlayerControl->LoopStart = *pLoopStart.mFBTime; }
	FBTime_Wrapper* GetLoopStart(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->LoopStart ); }
	void SetLoopStop( FBTime_Wrapper& pLoopStop ) { mFBPlayerControl->LoopStop = *pLoopStop.mFBTime; }
	FBTime_Wrapper* GetLoopStop(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->LoopStop ); }
	FBTime_Wrapper* GetNextMarker(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->NextMarker ); }
	FBTime_Wrapper* GetPreviousMarker(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->PreviousMarker ); }
	void SetSnapMode( FBTransportSnapMode pSnapMode ) { mFBPlayerControl->SnapMode = pSnapMode; }
	FBTransportSnapMode GetSnapMode(  ) { return mFBPlayerControl->SnapMode; }
	void SetTransportTimeFormat( FBTransportTimeFormat pTransportTimeFormat ) { mFBPlayerControl->TransportTimeFormat = pTransportTimeFormat; }
	FBTransportTimeFormat GetTransportTimeFormat(  ) { return mFBPlayerControl->TransportTimeFormat; }
	void SetZoomWindowStart( FBTime_Wrapper& pZoomWindowStart ) { mFBPlayerControl->ZoomWindowStart = *pZoomWindowStart.mFBTime; }
	FBTime_Wrapper* GetZoomWindowStart(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->ZoomWindowStart ); }
	void SetZoomWindowStop( FBTime_Wrapper& pZoomWindowStop ) { mFBPlayerControl->ZoomWindowStop = *pZoomWindowStop.mFBTime; }
	FBTime_Wrapper* GetZoomWindowStop(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->ZoomWindowStop ); }
	FBTime_Wrapper* GetRecordingSamplingPeriod(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->RecordingSamplingPeriod ); }
	void SetRecordingSamplingPeriod( FBTime_Wrapper& pRecordingSamplingPeriod ) { mFBPlayerControl->RecordingSamplingPeriod = *pRecordingSamplingPeriod.mFBTime; }
	FBTime_Wrapper* GetPlotSamplingPeriod(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->PlotSamplingPeriod ); }
	void SetPlotSamplingPeriod( FBTime_Wrapper& pPlotSamplingPeriod ) { mFBPlayerControl->PlotSamplingPeriod = *pPlotSamplingPeriod.mFBTime; }
	FBTimeReferential GetTimeReferential(  ) { return mFBPlayerControl->GetTimeReferential(); }
	void SetTimeReferential( FBTimeReferential pTimeReferential ) { mFBPlayerControl->SetTimeReferential(pTimeReferential); }
	FBTime_Wrapper* GetEditCurrentTime(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->GetEditCurrentTime() ); }
	FBTime_Wrapper* GetEditStart(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->GetEditStart() ); }
	void SetEditStart( FBTime_Wrapper& pEditStart ) { mFBPlayerControl->SetEditStart(*pEditStart.mFBTime); }
	FBTime_Wrapper* GetEditStop(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->GetEditStop() ); }
	void SetEditStop( FBTime_Wrapper& pEditStop ) { mFBPlayerControl->SetEditStop(*pEditStop.mFBTime); }
	FBTime_Wrapper* GetEditZoomStart(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->GetEditZoomStart() ); }
	void SetEditZoomStart( FBTime_Wrapper& pEditZoomStart ) { mFBPlayerControl->SetEditZoomStart(*pEditZoomStart.mFBTime); }
	FBTime_Wrapper* GetEditZoomStop(  ) { return FBTime_Wrapper_Factory( mFBPlayerControl->GetEditZoomStop() ); }
	void SetEditZoomStop( FBTime_Wrapper& pEditZoomStop ) { mFBPlayerControl->SetEditZoomStop(*pEditZoomStop.mFBTime); }
	void EvaluationPause() { mFBPlayerControl->EvaluationPause(); }
	void EvaluationResume() { mFBPlayerControl->EvaluationResume(); }
	int AddGlobalTimeMark( FBTime_Wrapper& pTime ) { return mFBPlayerControl->AddGlobalTimeMark( *pTime.mFBTime ); }
	bool DeleteGlobalTimeMark( int pIndex ) { return mFBPlayerControl->DeleteGlobalTimeMark( pIndex ); }
	void DeleteAllGlobalTimeMarks() { mFBPlayerControl->DeleteAllGlobalTimeMarks(); }
	int GetGlobalTimeMarkCount() { return mFBPlayerControl->GetGlobalTimeMarkCount(); }
	FBTime_Wrapper* GetGlobalTimeMarkTime( int pIndex ) { return FBTime_Wrapper_Factory( mFBPlayerControl->GetGlobalTimeMarkTime( pIndex ) ); }
	int SetGlobalTimeMarkTime( int pIndex, FBTime_Wrapper& pTime ) { return  mFBPlayerControl->SetGlobalTimeMarkTime( pIndex, *pTime.mFBTime ); }
	const char* GetGlobalTimeMarkName( int pIndex ) { return mFBPlayerControl->GetGlobalTimeMarkName( pIndex ); }
	bool SetGlobalTimeMarkName( int pIndex, const char* pName ) { return mFBPlayerControl->SetGlobalTimeMarkName( pIndex, pName ); }
	FBTimeMarkAction GetGlobalTimeMarkAction( int pIndex ) { return mFBPlayerControl->GetGlobalTimeMarkAction( pIndex ); }
	bool SetGlobalTimeMarkAction( int pIndex, FBTimeMarkAction pAction ) { return mFBPlayerControl->SetGlobalTimeMarkAction( pIndex, pAction ); }
	FBColor_Wrapper* GetGlobalTimeMarkColor( int pIndex ) { return FBColor_Wrapper_Factory( mFBPlayerControl->GetGlobalTimeMarkColor( pIndex ) ); }
	bool SetGlobalTimeMarkColor( int pIndex, FBColor_Wrapper& pColor ) { return mFBPlayerControl->SetGlobalTimeMarkColor( pIndex, *pColor.mFBColor ); }
	int GetNextGlobalTimeMarkIndex() { return mFBPlayerControl->GetNextGlobalTimeMarkIndex(); }
	int GetPreviousGlobalTimeMarkIndex() { return mFBPlayerControl->GetPreviousGlobalTimeMarkIndex(); }
	
	object OnChange();

protected:
	FBPropertyEvent* GetPropertyEvent( FBEventName pEventName );
};
#endif // pyfbplayercontrol_h__
