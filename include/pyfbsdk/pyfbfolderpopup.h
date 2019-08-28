#ifndef pyfbfolderpopup_h__
#define pyfbfolderpopup_h__
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
// FBFolderPopup
// =======================================================================================
void FBFolderPopup_Init();

class PYSDK_DLL FBFolderPopup_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBFolderPopup* mFBFolderPopup;
public:	
	FBFolderPopup_Wrapper():FBVisualComponent_Wrapper( new FBFolderPopup()) 
	{
		mFBFolderPopup = (FBFolderPopup*)mFBComponent;
		SetAllocated();
	}
    virtual ~FBFolderPopup_Wrapper( ) {}
	bool Execute() { return mFBFolderPopup->Execute(  ); }
	void SetCaption( const char* pCaption ) { mFBFolderPopup->Caption = pCaption; }
	const char* GetCaption(  ) { return mFBFolderPopup->Caption; }
	void SetPath( const char* pPath ) { mFBFolderPopup->Path = pPath; }
	const char* GetPath(  ) { return mFBFolderPopup->Path; }
};
#endif // pyfbfolderpopup_h__