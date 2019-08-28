#ifndef pyfbassetfolder_h__
#define pyfbassetfolder_h__
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
// FBAssetFolder
// =======================================================================================
void FBAssetFolder_Init();

class FBAssetItem_Wrapper;
class PYSDK_DLL FBAssetFolder_Wrapper : public FBAssetItem_Wrapper {
public:
	FBAssetFolder* mFBAssetFolder;
public:
	FBAssetFolder_Wrapper( FBComponent* pFBComponent ) : FBAssetItem_Wrapper( pFBComponent ) { mFBAssetFolder = (FBAssetFolder*)pFBComponent; }
	virtual ~FBAssetFolder_Wrapper( ) {}
	object AddFile(const char* pLocalPath, const char* pComment = "", bool pCheckOut = false, bool pSilent = false) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetFolder->AddFile( FBString(pLocalPath), FBString(pComment), pCheckOut, pSilent )); }
	object AddFolder(const char* pName, const char* pComment = "", bool pSilent = false) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetFolder->AddFolder( FBString(pName), FBString(pComment), pSilent )); }
	bool FBCreate() { return mFBAssetFolder->FBCreate(  ); }
	void FBDestroy() { mFBAssetFolder->FBDestroy(  ); }
	object GetChild(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBAssetFolder_Wrapper::GetChildCount );
        return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetFolder->GetChild( pIndex )); 
    }
	int GetChildCount() { return mFBAssetFolder->GetChildCount(  ); }
	object GetFile(const char* pName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetFolder->GetFile( FBString(pName) )); }
	object GetFolder(const char* pName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetFolder->GetFolder( FBString(pName) )); }
};
#endif // pyfbassetfolder_h__
