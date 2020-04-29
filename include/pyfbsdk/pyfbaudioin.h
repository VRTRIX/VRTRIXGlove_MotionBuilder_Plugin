#ifndef pyfbaudioin_h__
#define pyfbaudioin_h__
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

#include "pyfbaudioout.h"

// =======================================================================================
// FBAudioIn
// =======================================================================================
void FBAudioIn_Init();

class FBAudioIn_Wrapper : public FBComponent_Wrapper {
public:
	FBAudioIn* mFBAudioIn;
public:
	FBAudioIn_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAudioIn = (FBAudioIn*)pFBComponent; }
	FBAudioIn_Wrapper(  ) : FBComponent_Wrapper( new FBAudioIn(  )) { mFBAudioIn = (FBAudioIn*)mFBComponent; SetAllocated(); }
	virtual ~FBAudioIn_Wrapper( ) {}
	bool SetOnline( bool pOnline ) { return mFBAudioIn->SetOnline( pOnline ); }
	bool IsOnline() const { return mFBAudioIn->IsOnline(); }
	bool PrepareToRecord( const char* pRecordingPath, FBExistingClipAction pExistingClipAction = kFBExistingClipAskUser, FBExistingFileAction pExistingFileAction = kFBExistingFileAskUser ) { return mFBAudioIn->PrepareToRecord( pRecordingPath, pExistingClipAction, pExistingFileAction ); }
	bool TurnOffRecording() { return mFBAudioIn->TurnOffRecording(); }
	bool IsReadyToRecord() const { return mFBAudioIn->IsReadyToRecord(); }
	FBAudioFmt GetSupportedFormats() const { return mFBAudioIn->GetSupportedFormats(); }
	bool SetRecordingFormat( FBAudioFmt pAudioFormat ) { return mFBAudioIn->SetRecordingFormat( pAudioFormat ); }
	FBAudioFmt GetRecordingFormat() const { return mFBAudioIn->GetRecordingFormat(); }
	bool SetDelay( const FBTime_Wrapper& pDelay ) { return mFBAudioIn->SetDelay( *pDelay.mFBTime ); }
	FBTime_Wrapper* GetDelay() const { return FBTime_Wrapper_Factory( mFBAudioIn->GetDelay() ); }
	bool SetDestination( object pDestination )
	{
		FBAudioOut_Wrapper* lAudioOutWrapper = extract<FBAudioOut_Wrapper*>( pDestination );
		return mFBAudioIn->SetDestination( lAudioOutWrapper ? lAudioOutWrapper->mFBAudioOut : NULL );
	}
	object GetDestination() const { return FBWrapperFactory::TheOne().WrapFBObject( mFBAudioIn->GetDestination() );  }

};
#endif // pyfbaudioin_h__