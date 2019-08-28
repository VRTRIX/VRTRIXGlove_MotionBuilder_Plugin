#ifndef pyfbshader_h__
#define pyfbshader_h__
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

// =======================================================================================
// FBShader
// =======================================================================================
void FBShader_Init();


class PYSDK_DLL FBShader_Wrapper : public FBBox_Wrapper {
public:
	FBShader* mFBShader;
public:
	FBShader_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBShader = (FBShader*)pFBComponent; }
	virtual ~FBShader_Wrapper( ) {}
	void Append(FBModel_Wrapper* pModel) { mFBShader->Append( pModel->mFBModel ); }
	void CloneShaderParameter(FBShader_Wrapper& pNewShader) { mFBShader->CloneShaderParameter( pNewShader.mFBShader ); }
	void ReplaceAll(FBModel_Wrapper& pModel) { mFBShader->ReplaceAll( pModel.mFBModel ); }
	bool ShaderNeedBeginRender() { return mFBShader->ShaderNeedBeginRender(  ); }
	void SetRenderingPass( FBRenderingPass pRenderingPass ) { mFBShader->RenderingPass = pRenderingPass; }
	FBRenderingPass GetRenderingPass(  ) { return mFBShader->RenderingPass; }
	void SetShaderDescription( const char* pShaderDescription ) { mFBShader->ShaderDescription = pShaderDescription; } // BIZARRE!!!! pas de copie de la chaine...
	const char* GetShaderDescription(  ) { return mFBShader->ShaderDescription; }
};
#endif // pyfbshader_h__
