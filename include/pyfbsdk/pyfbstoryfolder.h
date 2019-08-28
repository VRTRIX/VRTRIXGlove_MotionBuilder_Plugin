#ifndef pyfbstoryfolder_h__
#define pyfbstoryfolder_h__
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
// FBStoryFolder
// =======================================================================================
void FBStoryFolder_Init();

class PYSDK_DLL FBStoryFolder_Wrapper : public FBComponent_Wrapper {
public:
	FBStoryFolder* mFBStoryFolder;
public:
	FBStoryFolder_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBStoryFolder = (FBStoryFolder*)pFBComponent; }
    FBStoryFolder_Wrapper( FBStoryFolder_Wrapper* pParentFolder=NULL ) : FBComponent_Wrapper( new FBStoryFolder( pParentFolder ? pParentFolder->mFBStoryFolder : 0 )) { mFBStoryFolder = (FBStoryFolder*)mFBComponent; }
	virtual ~FBStoryFolder_Wrapper( ) {}
	void FBDelete() { mFBStoryFolder->FBDelete(  ); }
	void Load(bool pLoad) { mFBStoryFolder->Load( pLoad ); }
	object GetChilds(  ) { return FBPropertyListStoryFolder_Wrapper_Factory( mFBStoryFolder->Childs ); }
	void SetLabel( const char* pLabel ) { mFBStoryFolder->Label = pLabel; }
	const char* GetLabel(  ) { return mFBStoryFolder->Label; }
	void SetMute( bool pMute ) { mFBStoryFolder->Mute = pMute; }
	bool GetMute(  ) { return mFBStoryFolder->Mute; }
	object GetParent(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBStoryFolder->Parent ); }
	void SetSolo( bool pSolo ) { mFBStoryFolder->Solo = pSolo; }
	bool GetSolo(  ) { return mFBStoryFolder->Solo; }
	void SetRecordClipPath( const char* pRecordClipPath ) { mFBStoryFolder->RecordClipPath = pRecordClipPath; }
	const char* GetRecordClipPath(  ) { return mFBStoryFolder->RecordClipPath; }
	object GetTracks(  ) { return FBPropertyListStoryTrack_Wrapper_Factory( mFBStoryFolder->Tracks ); }
	void AlignSelectedClips(FBStoryClipAlignmentType pType, FBComponent_Wrapper* pClip) { mFBStoryFolder->AlignSelectedClips( pType, pClip ? pClip->mFBComponent : NULL ); }
	void ExpandSelectedClips(bool pPerserveOverlap) { mFBStoryFolder->ExpandSelectedClips( pPerserveOverlap ); }
	void ConvertClipsToReadOnly( bool pSelected, char* pPath ) { mFBStoryFolder->ConvertClipsToReadOnly(pSelected,pPath); }

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Collapsed,bool);
};
#endif // pyfbstoryfolder_h__
