#ifndef pyfbshaderlighted_h__
#define pyfbshaderlighted_h__
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
// FBShaderLighted
// =======================================================================================
void FBShaderLighted_Init();

class PYSDK_DLL FBShaderLighted_Wrapper : public FBShader_Wrapper {
public:
	FBShaderLighted* mFBShaderLighted;
public:
	FBShaderLighted_Wrapper( FBComponent* pFBComponent ) : FBShader_Wrapper( pFBComponent ) { mFBShaderLighted = (FBShaderLighted*)pFBComponent; }
	FBShaderLighted_Wrapper( const char* pName = NULL ) : FBShader_Wrapper( new FBShaderLighted( pName )) { mFBShaderLighted = (FBShaderLighted*)mFBComponent; }
	virtual ~FBShaderLighted_Wrapper( ) {}
	void SetAlpha( double pAlpha ) { mFBShaderLighted->Alpha = pAlpha; }
	object GetAlpha(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBShaderLighted->Alpha ); }
	void SetContrast( double pContrast ) { mFBShaderLighted->Contrast = pContrast; }
	double GetContrast(  ) { return mFBShaderLighted->Contrast; }
	void SetLuminosity( double pLuminosity ) { mFBShaderLighted->Luminosity = pLuminosity; }
	double GetLuminosity(  ) { return mFBShaderLighted->Luminosity; }
	void SetSpecular( double pSpecular ) { mFBShaderLighted->Specular = pSpecular; }
	double GetSpecular(  ) { return mFBShaderLighted->Specular; }
	void SetTransparency( FBAlphaSource pTransparency ) { mFBShaderLighted->Transparency = pTransparency; }
	FBAlphaSource GetTransparency(  ) { return mFBShaderLighted->Transparency; }
	void SetUseContrast( bool pUseContrast ) { mFBShaderLighted->UseContrast = pUseContrast; }
	bool GetUseContrast(  ) { return mFBShaderLighted->UseContrast; }
	void SetUseLuminosity( bool pUseLuminosity ) { mFBShaderLighted->UseLuminosity = pUseLuminosity; }
	bool GetUseLuminosity(  ) { return mFBShaderLighted->UseLuminosity; }
	void SetUseSpecular( bool pUseSpecular ) { mFBShaderLighted->UseSpecular = pUseSpecular; }
	bool GetUseSpecular(  ) { return mFBShaderLighted->UseSpecular; }
};
#endif // pyfbshaderlighted_h__