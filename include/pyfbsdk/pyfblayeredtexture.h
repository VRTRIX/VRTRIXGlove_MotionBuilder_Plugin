#ifndef pyfblayeredtexture_h__
#define pyfblayeredtexture_h__
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
#include "pyfbtexture.h"

// =======================================================================================
// FBTexture
// =======================================================================================
void FBLayeredTexture_Init();

class PYSDK_DLL FBLayeredTexture_Wrapper : public FBTexture_Wrapper {
public:
	FBLayeredTexture* mFBLayeredTexture;
public:
	FBLayeredTexture_Wrapper( FBComponent* pFBComponent ) : FBTexture_Wrapper( pFBComponent ) { mFBLayeredTexture = (FBLayeredTexture*)pFBComponent; }
	FBLayeredTexture_Wrapper( const char* pName ) : FBTexture_Wrapper( new FBLayeredTexture( pName )) { mFBLayeredTexture = (FBLayeredTexture*)mFBComponent; }
	virtual ~FBLayeredTexture_Wrapper() {}
	void FBDelete()             { mFBLayeredTexture->FBDelete(  ); }
    void SetLayerConfigDirty()  { mFBLayeredTexture->SetLayerConfigDirty(); }
    object Clone()              { return FBWrapperFactory::TheOne().WrapFBObject( mFBLayeredTexture->Clone() ); }
	object GetLayers()          { return FBPropertyListTexture_Wrapper_Factory( mFBLayeredTexture->Layers ); }
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(FBLayeredTexture, BackgroundColor, FBColorAndAlpha);
};
#endif // pyfblayeredtexture_h__
