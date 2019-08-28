#ifndef pyfbtexture_h__
#define pyfbtexture_h__
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
#include "pyfbimage.h"
#include "pyfbvideo.h"
#include "pyfbvideoclip.h"
#include "pyfbvideoin.h"
#include "pyfbvideoout.h"

// =======================================================================================
// FBTexture
// =======================================================================================
void FBTexture_Init();

class PYSDK_DLL FBTexture_Wrapper : public FBBox_Wrapper {
public:
	FBTexture* mFBTexture;
public:
	FBTexture_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBTexture = (FBTexture*)pFBComponent; }
	FBTexture_Wrapper( const char* pName ) : FBBox_Wrapper( new FBTexture( pName )) { mFBTexture = (FBTexture*)mFBComponent; }
	virtual ~FBTexture_Wrapper( ) {}
	void FBDelete() { mFBTexture->FBDelete(  ); }
    object Clone() { return FBWrapperFactory::TheOne().WrapFBObject( mFBTexture->Clone() ); }
	void OGLInit() { mFBTexture->OGLInit(  ); }
	void SetAlpha( double pAlpha ) { mFBTexture->Alpha = pAlpha; }
	object GetAlpha(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBTexture->Alpha ); }
	void SetBlendMode( FBTextureBlendMode pBlendMode ) { mFBTexture->BlendMode = pBlendMode; }
	FBTextureBlendMode GetBlendMode(  ) { return mFBTexture->BlendMode; }
	int GetHeight(  ) { return mFBTexture->Height; }
	void SetUseType( FBTextureUseType pUseType ) { mFBTexture->UseType = pUseType; }
	FBTextureUseType GetUseType ( ) { return mFBTexture->UseType; }
	void SetMapping( FBTextureMapping pMapping ) { mFBTexture->Mapping = pMapping; }
	FBTextureMapping GetMapping(  ) { return mFBTexture->Mapping; }
	void SetRotation( FBVector3d_Wrapper& pRotation ) { mFBTexture->Rotation = *pRotation.mFBVector3d; }
	object GetRotation(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBTexture->Rotation ); }
	void SetScaling( FBVector3d_Wrapper& pScaling ) { mFBTexture->Scaling = *pScaling.mFBVector3d; }
	object GetScaling(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBTexture->Scaling ); }
	void SetSwapUV( bool pSwapUV ) { mFBTexture->SwapUV = pSwapUV; }
	bool GetSwapUV(  ) { return mFBTexture->SwapUV; }
	void SetTranslation( FBVector3d_Wrapper& pTranslation ) { mFBTexture->Translation = *pTranslation.mFBVector3d; }
	object GetTranslation(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBTexture->Translation ); }
	void SetVideo( FBVideo_Wrapper* pVideo ) { pVideo != NULL ? mFBTexture->Video = pVideo->mFBVideo : mFBTexture->Video = NULL; }
	object GetVideo(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBTexture->Video ); }
	int GetWidth(  ) { return mFBTexture->Width; }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(TextureOGLId, unsigned int);
};
#endif // pyfbtexture_h__