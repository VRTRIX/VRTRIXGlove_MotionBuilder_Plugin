#ifndef pyfbmaterial_h__
#define pyfbmaterial_h__
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

#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbvideo.h"
#include "pyfbtexture.h"

// =======================================================================================
// FBMaterial
// ======================================================================================
void FBMaterial_Init();

class PYSDK_DLL FBMaterial_Wrapper : public FBBox_Wrapper {
public:
	FBMaterial* mFBMaterial;
public:
	FBMaterial_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBMaterial = (FBMaterial*)pFBComponent; }
	FBMaterial_Wrapper( const char* pName ) : FBBox_Wrapper( new FBMaterial( pName )) { mFBMaterial = (FBMaterial*)mFBComponent; }
	virtual ~FBMaterial_Wrapper( ) {}
    object Clone() { return FBWrapperFactory::TheOne().WrapFBObject( mFBMaterial->Clone() ); }
	void OGLInit() {  mFBMaterial->OGLInit(  ); }
	object GetTexture(FBMaterialTextureType pType= kFBMaterialTextureDiffuse) { return FBWrapperFactory::TheOne().WrapFBObject(mFBMaterial->GetTexture(pType)); }
	void SetTexture(FBTexture_Wrapper& pTexture, FBMaterialTextureType pType = kFBMaterialTextureDiffuse) { return mFBMaterial->SetTexture(pTexture.mFBTexture, pType);}
    void SetAmbient( FBColor_Wrapper& pAmbient ) { mFBMaterial->Ambient = *pAmbient.mFBColor; }
	FBColor_Wrapper* GetAmbient(  ) { return FBColor_Wrapper_Factory( mFBMaterial->Ambient ); }    
	void SetAmbientFactor( double pAmbientFactor ) { mFBMaterial->AmbientFactor = pAmbientFactor; }
    double GetAmbientFactor(  ) { return mFBMaterial->AmbientFactor; }

    void SetDiffuse( FBColor_Wrapper& pDiffuse ) { mFBMaterial->Diffuse = *pDiffuse.mFBColor; }
	object GetDiffuse(  ) { return WrapFBObject<FBPropertyAnimatableColor_Wrapper,FBPropertyAnimatableColor>( &mFBMaterial->Diffuse ); }
	void SetDiffuseFactor( double pDiffuseFactor ) { mFBMaterial->DiffuseFactor = pDiffuseFactor; }
    double GetDiffuseFactor(  ) { return mFBMaterial->DiffuseFactor; }

    void SetEmissive( FBColor_Wrapper& pEmissive ) { mFBMaterial->Emissive = *pEmissive.mFBColor; }
	FBColor_Wrapper* GetEmissive(  ) { return FBColor_Wrapper_Factory( mFBMaterial->Emissive ); }
    void SetEmissiveFactor( double pEmissiveFactor ) { mFBMaterial->EmissiveFactor = pEmissiveFactor; }
    double GetEmissiveFactor(  ) { return mFBMaterial->EmissiveFactor; }

    void SetTransparentColor( FBColor_Wrapper& pTransparentColor ) { mFBMaterial->TransparentColor = *pTransparentColor.mFBColor; }
    FBColor_Wrapper* GetTransparentColor(  ) { return FBColor_Wrapper_Factory( mFBMaterial->TransparentColor );}
    void SetTransparencyFactor( double pTransparencyFactor ) { mFBMaterial->TransparencyFactor = pTransparencyFactor; }
	double GetTransparencyFactor(  ) { return mFBMaterial->TransparencyFactor; }

    void SetBump( FBColor_Wrapper& pBump ) { mFBMaterial->Bump = *pBump.mFBColor; }
    FBColor_Wrapper* GetBump(  ) { return FBColor_Wrapper_Factory( mFBMaterial->Bump );}

    void SetNormalMap( FBColor_Wrapper& pNormalMap ) { mFBMaterial->NormalMap = *pNormalMap.mFBColor; }
    FBColor_Wrapper* GetNormalMap(  ) { return FBColor_Wrapper_Factory( mFBMaterial->NormalMap );}

	void SetBumpFactor( double pBumpFactor ) { mFBMaterial->BumpFactor = pBumpFactor; }
    double GetBumpFactor() { return mFBMaterial->BumpFactor; }

    void SetReflection( FBColor_Wrapper& pReflection ) { mFBMaterial->Reflection = *pReflection.mFBColor; }
    FBColor_Wrapper* GetReflection(  ) { return FBColor_Wrapper_Factory( mFBMaterial->Reflection );}
    void SetReflectionFactor( double pReflectionFactor ) { mFBMaterial->ReflectionFactor = pReflectionFactor; }
	double GetReflectionFactor(  ) { return mFBMaterial->ReflectionFactor; }

    void SetShininess( double pShininess ) { mFBMaterial->Shininess = pShininess; }
	double GetShininess(  ) { return mFBMaterial->Shininess; }

    void SetSpecular( FBColor_Wrapper& pSpecular ) { mFBMaterial->Specular = *pSpecular.mFBColor; }
	FBColor_Wrapper* GetSpecular(  ) { return FBColor_Wrapper_Factory( mFBMaterial->Specular ); }
    void SetSpecularFactor( double pSpecularFactor ) { mFBMaterial->SpecularFactor = pSpecularFactor; }
    double GetSpecularFactor(  ) { return mFBMaterial->SpecularFactor; }

	void SetDisplacementColor( FBColor_Wrapper& pDisplacementColor ) { mFBMaterial->DisplacementColor = *pDisplacementColor.mFBColor; }
	FBColor_Wrapper* GetDisplacementColor(  ) { return FBColor_Wrapper_Factory( mFBMaterial->DisplacementColor ); }
	void SetDisplacementFactor( double pDisplacementFactor ) { mFBMaterial->DisplacementFactor = pDisplacementFactor; }
	double GetDisplacementFactor(  ) { return mFBMaterial->DisplacementFactor; }
};
#endif // pyfbmaterial_h__
