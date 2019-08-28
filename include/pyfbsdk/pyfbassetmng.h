#ifndef pyfbassetmng_h__
#define pyfbassetmng_h__
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
// FBAssetMng
// =======================================================================================
void FBAssetMng_Init();

class FBAssetMng_Wrapper;
PYSDK_DLL FBAssetMng_Wrapper* FBAssetMng_Wrapper_Factory( FBAssetMng* pFBAssetMng );
class PYSDK_DLL FBAssetMng_Wrapper : public FBComponent_Wrapper {
public:
	FBAssetMng* mFBAssetMng;
public:
	FBAssetMng_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAssetMng = (FBAssetMng*)pFBComponent; }
	virtual ~FBAssetMng_Wrapper( ) {}
	object BrowseForFile() { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetMng->BrowseForFile(  )); }
	object BrowseForFolder() { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetMng->BrowseForFolder(  )); }
	bool CheckAvailability() { return mFBAssetMng->CheckAvailability(  ); }
	object CreateServerPath(const char* pServerPath) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetMng->CreateServerPath( FBString(pServerPath) )); }
	bool FileIsManaged(const char* pFilename) { return mFBAssetMng->FileIsManaged( FBString(pFilename) ); }
	object GetAssetFile(const char* pServerFilename) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetMng->GetAssetFile( FBString(pServerFilename) )); }
	object GetAssetFileFromLocalPath(const char* pLocalFilename) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetMng->GetAssetFileFromLocalPath( FBString(pLocalFilename) )); }
	object GetAssetFolder(const char* pServerPath) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetMng->GetAssetFolder( FBString(pServerPath) )); }
	object GetAssetFolderFromLocalPath(const char* pLocalPath) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetMng->GetAssetFolderFromLocalPath( FBString(pLocalPath) )); }
	int GetFileOptions() { return mFBAssetMng->GetFileOptions(  ); }
	bool Initialize() { return mFBAssetMng->Initialize(  ); }
	const char* MapLocalPathToServerPath(const char* pLocalPath) { return mFBAssetMng->MapLocalPathToServerPath( FBString(pLocalPath) ); }
	void ShowSettings() { mFBAssetMng->ShowSettings(  ); }
	bool WithinManagedPath(const char* pLocalPath) { return mFBAssetMng->WithinManagedPath( FBString(pLocalPath) ); }
	void SetDescription( const char* pDescription ) { mFBAssetMng->Description = pDescription; }
	const char* GetDescription(  ) { return mFBAssetMng->Description; }
	void SetLastError( const char* pLastError ) { mFBAssetMng->LastError = pLastError; }
	const char* GetLastError(  ) { return mFBAssetMng->LastError; }
	void SetMenuFlags( int pMenuFlags ) { mFBAssetMng->MenuFlags = pMenuFlags; }
	int GetMenuFlags(  ) { return mFBAssetMng->MenuFlags; }
	void SetName( const char* pName ) { mFBAssetMng->Name = pName; }
	const char* GetName(  ) { return mFBAssetMng->Name; }
};
#endif // pyfbassetmng_h__