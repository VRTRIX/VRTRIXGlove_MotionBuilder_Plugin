#ifndef pyfbconfigfile_h__
#define pyfbconfigfile_h__
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
// FBConfigFile
// =======================================================================================
void FBConfigFile_Init();

class PYSDK_DLL FBConfigFile_Wrapper {
public:
	FBConfigFile* mFBConfigFile;
public:
	FBConfigFile_Wrapper( const char* pConfigFileName, bool pVirtualMode = false, bool pClearFile = false ) { mFBConfigFile = new FBConfigFile( pConfigFileName, pVirtualMode, pClearFile ); }
	FBConfigFile_Wrapper( const char* pConfigFileName, const char* pConfigFilePath, bool pVirtualMode = false, bool pClearFile = false ) { mFBConfigFile = new FBConfigFile( pConfigFileName, pConfigFilePath, pVirtualMode, pClearFile ); }
	virtual ~FBConfigFile_Wrapper( ) { delete mFBConfigFile; }
	void ClearFile() { mFBConfigFile->ClearFile(  ); }
	const char* Get(const char* pSectionName, const char* pItemName, const char* pDefaultValue = NULL) { return mFBConfigFile->Get( pSectionName, pItemName, pDefaultValue ); }
	tuple GetOrSet(const char* pSectionName, const char* pItemName, const char* pValue, const char* pComment = NULL)
    {
        const char* lValue = pValue;
        bool lResult = mFBConfigFile->GetOrSet( pSectionName, pItemName, lValue, pComment );
        return make_tuple( lResult, lValue );
    }
	bool Set(const char* pSectionName, const char* pItemName, const char* pValue, const char* pComment = NULL) { return mFBConfigFile->Set( pSectionName, pItemName, pValue, pComment ); }
};
#endif // pyfbconfigfile_h__