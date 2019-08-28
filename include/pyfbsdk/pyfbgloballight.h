#ifndef pyfbgloballight_h__
#define pyfbgloballight_h__
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

// =======================================================================================
// FBGlobalLight
// =======================================================================================
void FBGlobalLight_Init();

class PYSDK_DLL FBGlobalLight_Wrapper : public FBBox_Wrapper {
public:
	FBGlobalLight* mFBGlobalLight;
public:
	FBGlobalLight_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBGlobalLight = (FBGlobalLight*)pFBComponent; }
	FBGlobalLight_Wrapper(  ) : FBBox_Wrapper( &(FBGlobalLight::TheOne()) ) { mFBGlobalLight = (FBGlobalLight*)mFBComponent; }
	virtual ~FBGlobalLight_Wrapper( ) { }
	void SetAmbientColor( FBColor_Wrapper& pAmbientColor ) { mFBGlobalLight->AmbientColor = *pAmbientColor.mFBColor; }
	object GetAmbientColor(  ) { return WrapFBObject<FBPropertyAnimatableColor_Wrapper,FBPropertyAnimatableColor>( &mFBGlobalLight->AmbientColor ); }
	void SetFogBegin( double pFogBegin ) { mFBGlobalLight->FogBegin = pFogBegin; }
	object GetFogBegin(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBGlobalLight->FogBegin ); }
	void SetFogColor( FBColor_Wrapper& pFogColor ) { mFBGlobalLight->FogColor = *pFogColor.mFBColor; }
	object GetFogColor(  ) { return WrapFBObject<FBPropertyAnimatableColor_Wrapper,FBPropertyAnimatableColor>( &mFBGlobalLight->FogColor ); }
	void SetFogDensity( double pFogDensity ) { mFBGlobalLight->FogDensity = pFogDensity; }
	object GetFogDensity(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBGlobalLight->FogDensity ); }
	void SetFogEnable( bool pFogEnable ) { mFBGlobalLight->FogEnable = pFogEnable; }
	bool GetFogEnable(  ) { return mFBGlobalLight->FogEnable; }
	void SetFogEnd( double pFogEnd ) { mFBGlobalLight->FogEnd = pFogEnd; }
	object GetFogEnd(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBGlobalLight->FogEnd ); }
	void SetFogMode( FBFogMode pFogMode ) { mFBGlobalLight->FogMode = pFogMode; }
	FBFogMode GetFogMode(  ) { return mFBGlobalLight->FogMode; }
};
#endif // pyfbgloballight_h__
