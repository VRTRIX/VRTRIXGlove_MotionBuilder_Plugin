#ifndef pyfbstory_h__
#define pyfbstory_h__
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
// FBStory
// =======================================================================================
void FBStory_Init();

class FBStory_Wrapper;
FBStory_Wrapper* FBStory_Wrapper_Factory( FBStory* pFBStory );
class PYSDK_DLL FBStory_Wrapper : public FBComponent_Wrapper {
public:
	FBStory* mFBStory;
public:
	FBStory_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBStory = (FBStory*)pFBComponent; }
	FBStory_Wrapper(  ) : FBComponent_Wrapper( &FBStory::TheOne()) { mFBStory = (FBStory*)mFBComponent; }
	virtual ~FBStory_Wrapper( ) {}
	void SetLockedShot( bool pLockedShot ) { mFBStory->LockedShot = pLockedShot; }
	bool GetLockedShot(  ) { return mFBStory->LockedShot; }
	void SetMute( bool pMute ) { mFBStory->Mute = pMute; }
	bool GetMute(  ) { return mFBStory->Mute; }
	void SetSummaryClip( bool pSummaryClipOn ) { mFBStory->SummaryClip = pSummaryClipOn; }
	bool GetSummaryClip(  ) { return mFBStory->SummaryClip; }
	void SetRecordToDisk( bool pRecordToDisk ) { mFBStory->RecordToDisk = pRecordToDisk; }
	bool GetRecordToDisk(  ) { return mFBStory->RecordToDisk; }
	void SetNoneBlockingPostprocess( bool pNoneBlockingPostprocess ) { mFBStory->NoneBlockingPostprocess = pNoneBlockingPostprocess; }
	bool GetNoneBlockingPostprocess(  ) { return mFBStory->NoneBlockingPostprocess; }
	object GetRootEditFolder(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStory->RootEditFolder ); }
	object GetRootFolder(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStory->RootFolder ); }
};
#endif // pyfbstory_h__