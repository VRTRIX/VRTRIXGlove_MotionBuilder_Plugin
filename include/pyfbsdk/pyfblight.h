#ifndef pyfblight_h__
#define pyfblight_h__
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
#include "pyfbvideo.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"

// =======================================================================================
// FBLight
// =======================================================================================
void FBLight_Init();

class PYSDK_DLL FBLight_Wrapper : public FBModel_Wrapper {
public:
	FBLight* mFBLight;
public:
	FBLight_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBLight = (FBLight*)pFBComponent; }
	FBLight_Wrapper( const char* pName ) : FBModel_Wrapper( new FBLight( pName )) { mFBLight = (FBLight*)mFBComponent; }
	virtual ~FBLight_Wrapper( ) {}
	void SetCastLightOnObject( bool pCastLightOnObject ) { mFBLight->CastLightOnObject = pCastLightOnObject; }
	bool GetCastLightOnObject(  ) { return mFBLight->CastLightOnObject; }	
	void SetConeAngle( double pConeAngle ) { mFBLight->OuterAngle = pConeAngle; }
	object GetConeAngle(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBLight->OuterAngle ); }
	void SetInnerAngle( double pConeAngle ) { mFBLight->InnerAngle = pConeAngle; }
    object GetInnerAngle(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBLight->InnerAngle ); }
    void SetOuterAngle( double pConeAngle ) { mFBLight->OuterAngle = pConeAngle; }
    object GetOuterAngle(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBLight->OuterAngle ); }
	void SetDiffuseColor( FBColor_Wrapper& pDiffuseColor ) { mFBLight->DiffuseColor = *pDiffuseColor.mFBColor; }
	object GetDiffuseColor(  ) { return WrapFBObject<FBPropertyAnimatableColor_Wrapper,FBPropertyAnimatableColor>( &mFBLight->DiffuseColor ); }
	void SetDrawFrontFacingVolumetric( bool pDrawFrontFacingVolumetric ) { mFBLight->DrawFrontFacingVolumetric = pDrawFrontFacingVolumetric; }
	bool GetDrawFrontFacingVolumetric(  ) { return mFBLight->DrawFrontFacingVolumetric; }
	void SetDrawGroundProjection( bool pDrawGroundProjection ) { mFBLight->DrawGroundProjection = pDrawGroundProjection; }
	bool GetDrawGroundProjection(  ) { return mFBLight->DrawGroundProjection; }
	void SetDrawVolumetricLight( bool pDrawVolumetricLight ) { mFBLight->DrawVolumetricLight = pDrawVolumetricLight; }
	bool GetDrawVolumetricLight(  ) { return mFBLight->DrawVolumetricLight; }
	void SetFogIntensity( double pFogIntensity ) { mFBLight->FogIntensity = pFogIntensity; }
	object GetFogIntensity(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBLight->FogIntensity ); }
    void SetGoboMedia( FBVideo_Wrapper* pGoboMedia ) { mFBLight->GoboMedia = pGoboMedia ? pGoboMedia->mFBVideo : NULL ; }
	object GetGoboMedia(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBLight->GoboMedia ); }
	void SetIntensity( double pIntensity ) { mFBLight->Intensity = pIntensity; }
	object GetIntensity(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBLight->Intensity ); }
    void SetLightType( FBLightType pLightType ) { mFBLight->LightType = pLightType; }
    FBLightType GetLightType(  ) { return mFBLight->LightType; }
    void SetAttenuationType( FBAttenuationType pAttenuationType ) { mFBLight->AttenuationType = pAttenuationType; }
    FBAttenuationType GetAttenuationType(  ) { return mFBLight->AttenuationType; }
	void SetAreaLightShape( FBLight::EAreaLightShapes pValue ) { mFBLight->AreaLightShape = pValue; }
	FBLight::EAreaLightShapes GetAreaLightShape(  ) { return mFBLight->AreaLightShape; }
	template< FBLight::EAreaLightShapes pValue > static FBLight::EAreaLightShapes EAreaLightShapes() { return pValue; }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( CastShadows,    bool   )
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( EnableBarnDoor, bool   )
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( LeftBarnDoor  , double )
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( RightBarnDoor , double )
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( TopBarnDoor   , double )
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( BottomBarnDoor, double )
};
#endif // pyfblight_h__