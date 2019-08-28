#ifndef pyfbfilepopup_h__
#define pyfbfilepopup_h__
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

#include "pyfbvisualcomponent.h"

// =======================================================================================
// FBFilePopup
// =======================================================================================
void FBFilePopup_Init();

class PYSDK_DLL FBFilePopup_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBFilePopup* mFBFilePopup;
public:
	FBFilePopup_Wrapper() : FBVisualComponent_Wrapper( new FBFilePopup()) 
	{
		mFBFilePopup = (FBFilePopup*)mFBComponent;
		SetAllocated();
	}
	virtual ~FBFilePopup_Wrapper( ) { }
	bool Execute() { return mFBFilePopup->Execute(  ); }
	void SetCaption( const char* pCaption ) { mFBFilePopup->Caption = pCaption; }
	const char* GetCaption(  ) { return mFBFilePopup->Caption; }
	void SetFileName( const char* pFileName ) { mFBFilePopup->FileName = pFileName; }
	const char* GetFileName(  ) { return mFBFilePopup->FileName; }
	void SetFilter( const char* pFilter ) { mFBFilePopup->Filter = pFilter; }
	const char* GetFilter(  ) { return mFBFilePopup->Filter; }
	const char* GetFullFilename(  ) { return mFBFilePopup->FullFilename; }
	void SetPath( const char* pPath ) { mFBFilePopup->Path = pPath; }
	const char* GetPath(  ) { return mFBFilePopup->Path; }
	void SetStyle( FBFilePopupStyle pStyle ) { mFBFilePopup->Style = pStyle; }
	FBFilePopupStyle GetStyle(  ) { return mFBFilePopup->Style; }
};
#endif // pyfbfilepopup_h__