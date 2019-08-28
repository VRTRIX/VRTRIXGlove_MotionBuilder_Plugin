#ifndef pyfbassetfile_h__
#define pyfbassetfile_h__
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

#include "pyfbassetitem.h"

// =======================================================================================
// FBAssetFile
// =======================================================================================
void FBAssetFile_Init();

class PYSDK_DLL FBAssetFile_Wrapper : public FBAssetItem_Wrapper {
public:
	FBAssetFile* mFBAssetFile;
public:
	FBAssetFile_Wrapper( FBComponent* pFBComponent ) : FBAssetItem_Wrapper( pFBComponent ) { mFBAssetFile = (FBAssetFile*)pFBComponent; }
	virtual ~FBAssetFile_Wrapper( ) {}
	bool FBCreate() { return mFBAssetFile->FBCreate(  ); }
	void FBDestroy() { mFBAssetFile->FBDestroy(  ); }
	const char* GetCheckedOutBy() { return mFBAssetFile->GetCheckedOutBy(  ); }
	bool IsCheckedOut() { return mFBAssetFile->IsCheckedOut(  ); }
	bool IsCheckedOutByMe() { return mFBAssetFile->IsCheckedOutByMe(  ); }
};
#endif // pyfbassetfile_h__
