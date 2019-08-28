#ifndef pyfbshadermodelinfo_h__
#define pyfbshadermodelinfo_h__
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
// FBShaderModelInfo
// =======================================================================================
void FBShaderModelInfo_Init();

class FBShaderModelInfo_Wrapper;
FBShaderModelInfo_Wrapper* FBShaderModelInfo_Wrapper_Factory( FBShaderModelInfo* pFBShaderModelInfo );
class PYSDK_DLL FBShaderModelInfo_Wrapper {
public:
	FBShaderModelInfo* mFBShaderModelInfo;
public:
	FBShaderModelInfo_Wrapper( const FBShaderModelInfo& pFBShaderModelInfo ) { mFBShaderModelInfo = new FBShaderModelInfo( pFBShaderModelInfo ); }
	virtual ~FBShaderModelInfo_Wrapper( ) { delete mFBShaderModelInfo; }
	object GetModel(  ) { return FBModel_Wrapper_Factory( mFBShaderModelInfo->GetFBModel() ); }
	int GetModel_Version(  ) { return mFBShaderModelInfo->GetModelVersion(); }
    int GetShader_Version( ) { return mFBShaderModelInfo->GetShaderVersion();}
};

PYSDK_DLL inline FBShaderModelInfo_Wrapper* FBShaderModelInfo_Wrapper_Factory( const FBShaderModelInfo& pFBShaderModelInfo )
{
	return new FBShaderModelInfo_Wrapper( pFBShaderModelInfo );
}
#endif // pyfbshadermodelinfo_h__