#ifndef pyfbshadershadowlive_h__
#define pyfbshadershadowlive_h__
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

#include "pyfbmatrix.h"
#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbshader.h"

// =======================================================================================
// FBShaderShadowLive
// =======================================================================================
void FBShaderShadowLive_Init();

class PYSDK_DLL FBShaderShadowLive_Wrapper : public FBShader_Wrapper {
public:
	FBShaderShadowLive* mFBShaderShadowLive;
public:
	FBShaderShadowLive_Wrapper( FBComponent* pFBComponent ) : FBShader_Wrapper( pFBComponent ) { mFBShaderShadowLive = (FBShaderShadowLive*)pFBComponent; }
	FBShaderShadowLive_Wrapper( const char* pName = NULL ) : FBShader_Wrapper( new FBShaderShadowLive( pName )) { mFBShaderShadowLive = (FBShaderShadowLive*)mFBComponent; }
	virtual ~FBShaderShadowLive_Wrapper( ) {}
	void SetLocalShadow( bool pLocalShadow ) { mFBShaderShadowLive->LocalShadow = pLocalShadow; }
	bool GetLocalShadow(  ) { return mFBShaderShadowLive->LocalShadow; }
	object GetModels(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBShaderShadowLive->Models ); }
	void SetShadowFrameType( FBShadowFrameType pShadowFrameType ) { mFBShaderShadowLive->ShadowFrameType = pShadowFrameType; }
	FBShadowFrameType GetShadowFrameType(  ) { return mFBShaderShadowLive->ShadowFrameType; }
	void SetShadowIntensity( double pShadowIntensity ) { mFBShaderShadowLive->ShadowIntensity = pShadowIntensity; }
	object GetShadowIntensity(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBShaderShadowLive->ShadowIntensity ); }
	object GetLights(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBShaderShadowLive->Lights ); }
	void SetShadowType( FBShadowType pShadowType ) { mFBShaderShadowLive->ShadowType = pShadowType; }
	FBShadowType GetShadowType(  ) { return mFBShaderShadowLive->ShadowType; }
	void SetShadowZOffset( double pShadowZOffset ) { mFBShaderShadowLive->ShadowZOffset = pShadowZOffset; }
	double GetShadowZOffset(  ) { return mFBShaderShadowLive->ShadowZOffset; }
	void SetUseGobo( bool pUseGobo ) { mFBShaderShadowLive->UseGobo = pUseGobo; }
	bool GetUseGobo(  ) { return mFBShaderShadowLive->UseGobo; }
};
#endif // pyfbshadershadowlive_h__