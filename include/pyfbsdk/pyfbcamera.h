#ifndef pyfbcamera_h__
#define pyfbcamera_h__
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
#include "pyfbtexture.h"

// =======================================================================================
// FBCamera
// =======================================================================================
void FBCamera_Init();

class PYSDK_DLL FBCamera_Wrapper : public FBModel_Wrapper {
public:
	FBCamera* mFBCamera;
    
/*
////////////////WARNING////////////////////////////////////
BACK-COMP implementation: 
The proper implementation is to change UseDepthOfField, FocusDistance and FocusAngle from 
FBProperty* to FBPropertyAnimatable*. This breaks 
backward compatibility and should only be done for major releases
////////////////WARNING////////////////////////////////////
*/
    FBPropertyAnimatableDouble mAnimatableFarPlane;
    FBPropertyAnimatableDouble mAnimatableNearPlane;
public:
    FBCamera_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBCamera = (FBCamera*)pFBComponent; }
    FBCamera_Wrapper( const char* pName ) : FBModel_Wrapper( new FBCamera( pName )) { mFBCamera = (FBCamera*)mFBComponent; }
    virtual ~FBCamera_Wrapper( ) {}
    void SetAntiAliasingIntensity( double pAntiAliasingIntensity ) { mFBCamera->AntiAliasingIntensity = pAntiAliasingIntensity; }
    double GetAntiAliasingIntensity(  ) { return mFBCamera->AntiAliasingIntensity; }
    void SetAntiAliasingMethod( FBCameraAntiAliasingMethod pAntiAliasingMethod ) { mFBCamera->AntiAliasingMethod = pAntiAliasingMethod; }
    FBCameraAntiAliasingMethod GetAntiAliasingMethod(  ) { return mFBCamera->AntiAliasingMethod; }
    void SetApertureMode( FBCameraApertureMode pApertureMode ) { mFBCamera->ApertureMode = pApertureMode; }
    FBCameraApertureMode GetApertureMode(  ) { return mFBCamera->ApertureMode; }
    void SetBackGroundColor( FBColor_Wrapper& pBackGroundColor ) { mFBCamera->BackGroundColor = *(pBackGroundColor.mFBColor); }
    object GetBackGroundColor(  ) { return WrapFBObject<FBPropertyAnimatableColor_Wrapper,FBPropertyAnimatableColor>( &mFBCamera->BackGroundColor ); }
    void SetForeGroundAlpha( double pForeGroundAlpha ) { mFBCamera->ForeGroundAlpha = pForeGroundAlpha; }
    object GetForeGroundAlpha(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->ForeGroundAlpha ); }
    void SetForeGroundImageCenter( bool pForeGroundImageCenter ) { mFBCamera->ForeGroundImageCenter = pForeGroundImageCenter; }
    bool GetForeGroundImageCenter(  ) { return mFBCamera->ForeGroundImageCenter; }
    void SetForeGroundImageCrop( bool pForeGroundImageCrop ) { mFBCamera->ForeGroundImageCrop = pForeGroundImageCrop; }
    bool GetForeGroundImageCrop(  ) { return mFBCamera->ForeGroundImageCrop; }
    void SetForeGroundImageFit( bool pForeGroundImageFit ) { mFBCamera->ForeGroundImageFit = pForeGroundImageFit; }
    bool GetForeGroundImageFit(  ) { return mFBCamera->ForeGroundImageFit; }
    void SetForeGroundImageKeepRatio( bool pForeGroundImageKeepRatio ) { mFBCamera->ForeGroundImageKeepRatio = pForeGroundImageKeepRatio; }
    bool GetForeGroundImageKeepRatio(  ) { return mFBCamera->ForeGroundImageKeepRatio; }
    void SetForeGroundImageOffsetX( double pOffsetX ) { mFBCamera->ForeGroundImageOffsetX = pOffsetX; }
    object GetForeGroundImageOffsetX(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->ForeGroundImageOffsetX ); }
    void SetForeGroundImageOffsetY( double pOffsetY ) { mFBCamera->ForeGroundImageOffsetY = pOffsetY; }
    object GetForeGroundImageOffsetY(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->ForeGroundImageOffsetY ); }
    void SetForeGroundImageScaleX( double pScaleX ) { mFBCamera->ForeGroundImageScaleX = pScaleX; }
    object GetForeGroundImageScaleX(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->ForeGroundImageScaleX ); }
    void SetForeGroundImageScaleY( double pScaleY ) { mFBCamera->ForeGroundImageScaleY = pScaleY; }
    object GetForeGroundImageScaleY(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->ForeGroundImageScaleY ); }
    void SetForeGroundMaterialThreshold( double pForeGroundMaterialThreshold ) { mFBCamera->ForeGroundMaterialThreshold = pForeGroundMaterialThreshold; }
    double GetForeGroundMaterialThreshold(  ) { return mFBCamera->ForeGroundMaterialThreshold; }
    void SetForeGroundTexture( FBTexture_Wrapper* pForeGroundTexture ) { mFBCamera->ForeGroundTexture = pForeGroundTexture->mFBTexture; }
    object GetForeGroundTexture(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCamera->ForeGroundTexture ); }
    void SetForeGroundMedia( FBVideo_Wrapper* pForeGroundMedia );
    object GetForeGroundMedia();
    void SetForeGroundPlaneDistance( double pForeGroundPlaneDistance ) { mFBCamera->ForeGroundPlaneDistance = pForeGroundPlaneDistance; }
    double GetForeGroundPlaneDistance(  ) { return mFBCamera->ForeGroundPlaneDistance; }
    void SetForeGroundPlaneDistanceMode( FBCameraDistanceMode pForeGroundPlaneDistanceMode ) { mFBCamera->ForeGroundPlaneDistanceMode = pForeGroundPlaneDistanceMode; }
    FBCameraDistanceMode GetForeGroundPlaneDistanceMode(  ) { return mFBCamera->ForeGroundPlaneDistanceMode; }
    void SetBackGroundImageCenter( bool pBackGroundImageCenter ) { mFBCamera->BackGroundImageCenter = pBackGroundImageCenter; }
    bool GetBackGroundImageCenter(  ) { return mFBCamera->BackGroundImageCenter; }
    void SetBackGroundImageCrop( bool pBackGroundImageCrop ) { mFBCamera->BackGroundImageCrop = pBackGroundImageCrop; }
    bool GetBackGroundImageCrop(  ) { return mFBCamera->BackGroundImageCrop; }
    void SetBackGroundImageFit( bool pBackGroundImageFit ) { mFBCamera->BackGroundImageFit = pBackGroundImageFit; }
    bool GetBackGroundImageFit(  ) { return mFBCamera->BackGroundImageFit; }
    void SetBackGroundImageKeepRatio( bool pBackGroundImageKeepRatio ) { mFBCamera->BackGroundImageKeepRatio = pBackGroundImageKeepRatio; }
    bool GetBackGroundImageKeepRatio(  ) { return mFBCamera->BackGroundImageKeepRatio; }
    void SetBackGroundImageOffsetX( double pOffsetX ) { mFBCamera->BackGroundImageOffsetX = pOffsetX; }
    object GetBackGroundImageOffsetX(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->BackGroundImageOffsetX ); }
    void SetBackGroundImageOffsetY( double pOffsetY ) { mFBCamera->BackGroundImageOffsetY = pOffsetY; }
    object GetBackGroundImageOffsetY(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->BackGroundImageOffsetY ); }
    void SetBackGroundImageScaleX( double pScaleX ) { mFBCamera->BackGroundImageScaleX = pScaleX; }
    object GetBackGroundImageScaleX(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->BackGroundImageScaleX ); }
    void SetBackGroundImageScaleY( double pScaleY ) { mFBCamera->BackGroundImageScaleY = pScaleY; }
    object GetBackGroundImageScaleY(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->BackGroundImageScaleY ); }
    void SetBackGroundTexture( FBTexture_Wrapper* pBackGroundTexture ) { mFBCamera->BackGroundTexture = pBackGroundTexture->mFBTexture; }
    object GetBackGroundTexture(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCamera->BackGroundTexture ); }
    void SetBackGroundMedia( FBVideo_Wrapper* pBackGroundMedia );
    object GetBackGroundMedia(  );
    void SetBackGroundPlaneDistance( double pBackGroundPlaneDistance ) { mFBCamera->BackGroundPlaneDistance = pBackGroundPlaneDistance; }
    double GetBackGroundPlaneDistance(  ) { return mFBCamera->BackGroundPlaneDistance; }
    void SetBackGroundPlaneDistanceMode( FBCameraDistanceMode pBackGroundPlaneDistanceMode ) { mFBCamera->BackGroundPlaneDistanceMode = pBackGroundPlaneDistanceMode; }
    FBCameraDistanceMode GetBackGroundPlaneDistanceMode(  ) { return mFBCamera->BackGroundPlaneDistanceMode; }
    void SetDisplay2DMagnifierFrame( bool pDisplay2DMagnifierFrame ) { mFBCamera->Display2DMagnifierFrame = pDisplay2DMagnifierFrame; }
    bool GetDisplay2DMagnifierFrame(  ) { return mFBCamera->Display2DMagnifierFrame; }
    void SetDisplayTurnTableIcon( bool pDisplayTurnTableIcon ) { mFBCamera->DisplayTurnTableIcon = pDisplayTurnTableIcon; }
    bool GetDisplayTurnTableIcon(  ) { return mFBCamera->DisplayTurnTableIcon; }
    void SetFarPlaneDistance( double pFarPlaneDistance ) { mFBCamera->FarPlaneDistance = pFarPlaneDistance; }
    double GetFarPlaneDistance(  ) { return mFBCamera->FarPlaneDistance; }
    void SetFieldOfView( double pFieldOfView ) { mFBCamera->FieldOfView = pFieldOfView; }
    object GetFieldOfView(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->FieldOfView ); }
    void SetFieldOfViewX( double pFieldOfViewX ) { mFBCamera->FieldOfViewX = pFieldOfViewX; }
    object GetFieldOfViewX(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->FieldOfViewX ); }
    void SetFieldOfViewY( double pFieldOfViewY ) { mFBCamera->FieldOfViewY = pFieldOfViewY; }
    object GetFieldOfViewY(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->FieldOfViewY ); }
    void SetFilmAspectRatio( double pFilmAspectRatio ) { mFBCamera->FilmAspectRatio = pFilmAspectRatio; }
    double GetFilmAspectRatio(  ) { return mFBCamera->FilmAspectRatio; }
    void SetFilmBackType( FBCameraFilmBackType pFilmBackType ) { mFBCamera->FilmBackType = pFilmBackType; }
    FBCameraFilmBackType GetFilmBackType(  ) { return mFBCamera->FilmBackType; }
    void SetFilmSizeHeight( double pFilmSizeHeight ) { mFBCamera->FilmSizeHeight = pFilmSizeHeight; }
    double GetFilmSizeHeight(  ) { return mFBCamera->FilmSizeHeight; }
    void SetFilmSizeWidth( double pFilmSizeWidth ) { mFBCamera->FilmSizeWidth = pFilmSizeWidth; }
    double GetFilmSizeWidth(  ) { return mFBCamera->FilmSizeWidth; }
    void SetFocalLength( double pFocalLength ) { mFBCamera->FocalLength = pFocalLength; }
    object GetFocalLength(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->FocalLength ); }
    void SetFocusAngle( double pFocusAngle ) { mFBCamera->FocusAngle = pFocusAngle; }
    object GetFocusAngle(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->FocusAngle ); }
    void SetFocusDistanceSource( FBCameraFocusDistanceSource pFocusDistanceSource ) { mFBCamera->FocusDistanceSource = pFocusDistanceSource; }
    FBCameraFocusDistanceSource GetFocusDistanceSource(  ) { return mFBCamera->FocusDistanceSource; }
    void SetFocusSpecificDistance( double pFocusSpecificDistance ) { mFBCamera->FocusSpecificDistance = pFocusSpecificDistance; }
    object GetFocusSpecificDistance(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->FocusSpecificDistance ); }
    void SetFocusModel( FBModel_Wrapper &pFocusModel) { mFBCamera->FocusModel= pFocusModel.mFBModel; }
    object GetFocusModel(  ) { return FBModel_Wrapper_Factory( mFBCamera->FocusModel ); }
    void SetForeGroundTransparent( bool pForeGroundTransparent ) { mFBCamera->ForeGroundTransparent = pForeGroundTransparent; }
    bool GetForeGroundTransparent(  ) { return mFBCamera->ForeGroundTransparent; }
    void SetFrameColor( FBColor_Wrapper& pFrameColor ) { mFBCamera->FrameColor = *(pFrameColor.mFBColor); }
    FBColor_Wrapper* GetFrameColor(  ) { return FBColor_Wrapper_Factory( mFBCamera->FrameColor ); }
    void SetFrameSizeMode( FBCameraFrameSizeMode pFrameSizeMode ) { mFBCamera->FrameSizeMode = pFrameSizeMode; }
    FBCameraFrameSizeMode GetFrameSizeMode(  ) { return mFBCamera->FrameSizeMode; }
    void SetInteractiveMode( bool pInteractiveMode ) { mFBCamera->InteractiveMode = pInteractiveMode; }
    bool GetInteractiveMode(  ) { return mFBCamera->InteractiveMode; }
    void SetInterest( FBModel_Wrapper& pInterest ) { mFBCamera->Interest = pInterest.mFBModel; }
    object GetInterest(  ) { return FBModel_Wrapper_Factory( mFBCamera->Interest ); }
    void SetMagnifierPosX( double pMagnifierPosX ) { mFBCamera->MagnifierPosX = pMagnifierPosX; }
    object GetMagnifierPosX(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->MagnifierPosX ); }
    void SetMagnifierPosY( double pMagnifierPosY ) { mFBCamera->MagnifierPosY = pMagnifierPosY; }
    object GetMagnifierPosY(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->MagnifierPosY ); }
    void SetMagnifierZoom( double pMagnifierZoom ) { mFBCamera->MagnifierZoom = pMagnifierZoom; }
    object GetMagnifierZoom(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->MagnifierZoom ); }
    void SetMotionBlurIntensity( double pValue ) { mFBCamera->MotionBlurIntensity = pValue; }
    object GetMotionBlurIntensity(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->MotionBlurIntensity ); }
    void SetUseMotionBlur( bool pValue ) { mFBCamera->UseMotionBlur = pValue; }
    bool GetUseMotionBlur(  ) { return mFBCamera->UseMotionBlur; }
    void SetUseRealTimeMotionBlur( bool pValue ) { mFBCamera->UseRealTimeMotionBlur = pValue; }
    bool GetUseRealTimeMotionBlur(  ) { return mFBCamera->UseRealTimeMotionBlur; }
    void SetMouseLockCamera( bool pMouseLockCamera ) { mFBCamera->MouseLockCamera = pMouseLockCamera; }
    bool GetMouseLockCamera(  ) { return mFBCamera->MouseLockCamera; }
    void SetNearPlaneDistance( double pNearPlaneDistance ) { mFBCamera->NearPlaneDistance = pNearPlaneDistance; }
    double GetNearPlaneDistance(  ) { return mFBCamera->NearPlaneDistance; }
    void SetNumberOfSamples( int pNumberOfSamples ) { mFBCamera->NumberOfSamples = pNumberOfSamples; }
    int GetNumberOfSamples(  ) { return mFBCamera->NumberOfSamples; }
    void SetOpticalCenterX( double pOpticalCenterX ) { mFBCamera->OpticalCenterX = pOpticalCenterX; }
    object GetOpticalCenterX(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->OpticalCenterX ); }
    void SetOpticalCenterY( double pOpticalCenterY ) { mFBCamera->OpticalCenterY = pOpticalCenterY; }
    object GetOpticalCenterY(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->OpticalCenterY ); }
    void SetPixelAspectRatio( double pPixelAspectRatio ) { mFBCamera->PixelAspectRatio = pPixelAspectRatio; }
    double GetPixelAspectRatio(  ) { return mFBCamera->PixelAspectRatio; }
    void SetResolutionHeight( double pResolutionHeight ) { mFBCamera->ResolutionHeight = pResolutionHeight; }
    double GetResolutionHeight(  ) { return mFBCamera->ResolutionHeight; }
    void SetResolutionMode( FBCameraResolutionMode pResolutionMode ) { mFBCamera->ResolutionMode = pResolutionMode; }
    FBCameraResolutionMode GetResolutionMode(  ) { return mFBCamera->ResolutionMode; }
    void SetResolutionWidth( double pResolutionWidth ) { mFBCamera->ResolutionWidth = pResolutionWidth; }
    double GetResolutionWidth(  ) { return mFBCamera->ResolutionWidth; }
    void SetRoll( double pRoll ) { mFBCamera->Roll = pRoll; }
    object GetRoll(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->Roll ); }
    void SetSafeAreaMode( FBCameraSafeAreaMode pSafeAreaMode ) { mFBCamera->SafeAreaMode = pSafeAreaMode; }
    FBCameraSafeAreaMode GetSafeAreaMode(  ) { return mFBCamera->SafeAreaMode; }
    void SetSamplingType( FBCameraSamplingType pSamplingType ) { mFBCamera->SamplingType = pSamplingType; }
    FBCameraSamplingType GetSamplingType(  ) { return mFBCamera->SamplingType; }
    void SetSqueezeRatio( double pSqueezeRatio ) { mFBCamera->SqueezeRatio = pSqueezeRatio; }
    double GetSqueezeRatio(  ) { return mFBCamera->SqueezeRatio; }
    bool GetSystemCamera(  ) { return mFBCamera->SystemCamera; }
    void SetTurnTable( double pTurnTable ) { mFBCamera->TurnTable = pTurnTable; }
    object GetTurnTable(  ) { return WrapFBObject<FBPropertyAnimatableDouble_Wrapper,FBPropertyAnimatableDouble>( &mFBCamera->TurnTable ); }
    void SetType( FBCameraType pType ) { mFBCamera->Type = pType; }
    FBCameraType GetType(  ) { return mFBCamera->Type; }
    void SetUse2DMagnifier( bool pUse2DMagnifier ) { mFBCamera->Use2DMagnifier = pUse2DMagnifier; }
    bool GetUse2DMagnifier(  ) { return mFBCamera->Use2DMagnifier; }
    void SetUseAccumulationBuffer( bool pUseAccumulationBuffer ) { mFBCamera->UseAccumulationBuffer = pUseAccumulationBuffer; }
    bool GetUseAccumulationBuffer(  ) { return mFBCamera->UseAccumulationBuffer; }
    void SetUseAntiAliasing( bool pUseAntiAliasing ) { mFBCamera->UseAntiAliasing = pUseAntiAliasing; }
    bool GetUseAntiAliasing(  ) { return mFBCamera->UseAntiAliasing; }
    void SetUseDepthOfField( bool pUseDepthOfField ) { mFBCamera->UseDepthOfField = pUseDepthOfField; }
    object GetUseDepthOfField(  ) { return WrapFBObject<FBPropertyAnimatableBool_Wrapper,FBPropertyAnimatableBool>( &mFBCamera->UseDepthOfField ); }
    void SetUseFrameColor( bool pUseFrameColor ) { mFBCamera->UseFrameColor = pUseFrameColor; }
    bool GetUseFrameColor(  ) { return mFBCamera->UseFrameColor; }
    void SetViewBackGroundPlaneMode( FBCameraViewPlaneMode pViewBackGroundPlaneMode ) { mFBCamera->ViewBackGroundPlaneMode = pViewBackGroundPlaneMode; }
    FBCameraViewPlaneMode GetViewBackGroundPlaneMode(  ) { return mFBCamera->ViewBackGroundPlaneMode; }
    void SetViewForeGroundPlaneMode( FBCameraViewPlaneMode pViewForeGroundPlaneMode ) { mFBCamera->ViewForeGroundPlaneMode = pViewForeGroundPlaneMode; }
    FBCameraViewPlaneMode GetViewForeGroundPlaneMode(  ) { return mFBCamera->ViewForeGroundPlaneMode; }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewCameraInterest, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewDisplaySafeArea, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewNearFarPlane, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewOpticalCenter, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewShowAxis, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewShowName, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewShowManipulators, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewShowGrid, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ViewShowTimeCode, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(WindowHeight, double);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(WindowWidth, double);
    void GetCameraMatrix( FBMatrix_Wrapper& pMatrix, FBCameraMatrixType pType, FBEvaluateInfo_Wrapper* pEvalInfo = NULL ) { mFBCamera->GetCameraMatrix( *pMatrix.mFBMatrix, pType, (pEvalInfo) ? pEvalInfo->mFBEvaluateInfo : NULL ); }
    FBVector4d_Wrapper* InverseProjection( int pX, int pY, double pDistanceFromCamera );
    FBVector4d_Wrapper* InverseProjection( int pX, int pY, double pDistanceFromCamera, bool pRelativeToViewport );
#if !defined(K_NO_HUD)
    object GetHUDs(  )      { return FBPropertyListHUD_Wrapper_Factory( mFBCamera->HUDs ); }
#endif

/*
////////////////WARNING////////////////////////////////////
BACK-COMP implementation: 
The proper implementation is to change UseDepthOfField, FocusDistance and FocusAngle from 
FBProperty* to FBPropertyAnimatable*. This breaks 
backward compatibility and should only be done for major releases
////////////////WARNING////////////////////////////////////
*/
    object GetAnimatableFarPlane();
    object GetAnimatableNearPlane();
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(CameraViewportX,     int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(CameraViewportY,     int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(CameraViewportWidth, int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(CameraViewportHeight,int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(OrthoZoom, double);

};
#endif // pyfbcamera_h__
