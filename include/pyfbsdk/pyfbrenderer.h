#ifndef pyfbrenderer_h__
#define pyfbrenderer_h__
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
#include "pyfbviewingoptions.h"
#include "pyfbrenderoptions.h"
#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbvideo.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbcamera.h"
#include "pyfbscene.h"
#include "pyfbrenderercallback.h"

// =======================================================================================
// FBRenderer
// =======================================================================================
void FBRenderer_Init();

class PYSDK_DLL FBRenderer_Wrapper : public FBComponent_Wrapper {
public:
    FBRenderer* mFBRenderer;
public:
    FBRenderer_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBRenderer = (FBRenderer*)pFBComponent; }
    virtual ~FBRenderer_Wrapper( ) {}
    bool FrameCurrentCameraWithModels(bool pAll) { return mFBRenderer->FrameCurrentCameraWithModels( pAll ); }
    FBViewingOptions_Wrapper* GetViewingOptions() { return FBViewingOptions_Wrapper_Factory( mFBRenderer->GetViewingOptions(  )); }
    void KeyboardInput(FBDeviceKeyboardKey pKeyIndex, bool pKeyState, bool pIsTrigger = false) { mFBRenderer->KeyboardInput( pKeyIndex, pKeyState, pIsTrigger ); }
    bool MouseInput(int pX, int pY, FBInputType pInputType, int pButtonKey, FBInputModifier pModifier, int pWheelDeltaValue = 0, int pLayer = -1) { return mFBRenderer->MouseInput( pX, pY, pInputType, pButtonKey, pModifier, pWheelDeltaValue, pLayer ); }
    bool MouseInputNormalized(float pX, float pY, FBInputType pInputType, int pButtonKey, FBInputModifier pModifier, int pWheelDeltaValue = 0, int pLayer = -1,  int pPaneId = -1) { return mFBRenderer->MouseInputNormalized( pX, pY, pInputType, pButtonKey, pModifier, pWheelDeltaValue, pLayer, pPaneId ); }
    bool Pick(int pX, int pY, FBPickInfosList_Wrapper& pPickInfosList) { return mFBRenderer->Pick( pX, pY, *pPickInfosList.mFBPickInfosList ); }
    bool PickNormalized(float pX, float pY, FBPickInfosList_Wrapper& pPickInfosList, int pPaneId = -1) { return mFBRenderer->PickNormalized( pX, pY, *pPickInfosList.mFBPickInfosList, false, pPaneId ); }
    bool RectPick(int pX1, int pY1, int pX2, int pY2, FBPickInfosList_Wrapper& pPickInfosList) { return mFBRenderer->RectPick( pX1, pY1, pX2, pY2, *pPickInfosList.mFBPickInfosList ); }
    bool RectPickNormalized(float pX1, float pY1, float pX2, float pY2, FBPickInfosList_Wrapper& pPickInfosList, int pPaneId = -1) { return mFBRenderer->RectPickNormalized(  pX1, pY1, pX2, pY2, *pPickInfosList.mFBPickInfosList, pPaneId ); }
    int  GetLastPickInfoList(FBPickInfosList_Wrapper& pPickInfosList) { return mFBRenderer->GetLastPickInfoList(*pPickInfosList.mFBPickInfosList); }
    bool PreRender(int pLayer = -1) { return mFBRenderer->PreRender( pLayer ); }
    bool Render(int pLayer = -1) { return mFBRenderer->Render( pLayer ); }
    bool RenderBegin(int pX, int pY, int pW, int pH) { return mFBRenderer->RenderBegin( pX, pY, pW, pH ); }
    bool RenderEnd() { return mFBRenderer->RenderEnd(); } // HACK: because FBView is not exposed to python yet.
    void OGLSetupSceneLights(FBRenderOptions_Wrapper& pRenderOptions) { return mFBRenderer->OGLSetupSceneLights(*pRenderOptions.mFBRenderOptions) ; }
    void OGLModelDisplay(FBRenderOptions_Wrapper& pRenderOptions, FBModel_Wrapper& pModel) { return mFBRenderer->OGLModelDisplay(*pRenderOptions.mFBRenderOptions, *pModel.mFBModel) ; }
    bool SetViewingOptions(FBViewingOptions_Wrapper& pOptions) { return mFBRenderer->SetViewingOptions( *pOptions.mFBViewingOptions ); }
    void SetViewport(int pX, int pY, int pW, int pH) { mFBRenderer->SetViewport( pX, pY, pW, pH ); }
    void SetCurrentCamera( FBCamera_Wrapper& pCurrentCamera ) { mFBRenderer->CurrentCamera = pCurrentCamera.mFBCamera; }
    object GetCurrentCamera(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBRenderer->CurrentCamera ); }
    object GetDisplayableGeometry(int pIndex) { return FBWrapperFactory::TheOne().WrapFBObject( mFBRenderer->GetDisplayableGeometry(pIndex)); }
    object GetDisplayableLight(int pIndex) { return FBWrapperFactory::TheOne().WrapFBObject( mFBRenderer->GetDisplayableLight(pIndex)); }
    void GetDisplayableGeometryInCameraFrustum(FBModelList_Wrapper& pFBModelList, FBCamera_Wrapper& pCamera);
    bool IsModelInsideCameraFrustum(FBModel_Wrapper& pGeometry, FBCamera_Wrapper& pCamera);
    void SetScene( FBScene_Wrapper& pScene ) { mFBRenderer->Scene = pScene.mFBScene; }
    object GetScene(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBRenderer->Scene ); }
    object GetRendererCallbacks(  ) { return FBPropertyListRendererCallback_Wrapper_Factory( mFBRenderer->RendererCallbacks ); }
	void SetCameraInPane(FBCamera_Wrapper& pCamera, unsigned int pPaneIndex = 0) { mFBRenderer->SetCameraInPane( pCamera.mFBCamera, pPaneIndex ); }
	object GetCameraInPane(unsigned int pPaneIndex = 0) { return FBWrapperFactory::TheOne().WrapFBObject( mFBRenderer->GetCameraInPane( pPaneIndex ) ); }
	void SetPaneCount(unsigned int pPaneCount) { mFBRenderer->SetPaneCount( pPaneCount ); }
	unsigned int GetPaneCount() { return mFBRenderer->GetPaneCount(); }
	void SetSchematicViewInPane(unsigned int pPaneIndex, bool pActive) { mFBRenderer->SetSchematicViewInPane( pPaneIndex, pActive ); }
	int GetSchematicViewPaneIndex() { return mFBRenderer->GetSchematicViewPaneIndex(); }
	void SetCameraSwitcherInPane( unsigned int pPaneIndex, bool pActive ) { mFBRenderer->SetCameraSwitcherInPane( pPaneIndex, pActive ); }
	bool IsCameraSwitcherInPane( unsigned int pPaneIndex ) { return mFBRenderer->IsCameraSwitcherInPane( pPaneIndex ); }
    
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UseCameraSwitcher, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(AutoEvaluate,      bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Background,        bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ShowStats,         bool);    
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FrustumCulling,    bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(DisplayNormals,    bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(IDBufferPicking,   bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(IDBufferPickingAlpha,   double);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(IDBufferDisplay,   bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SelectionOverride,   bool); 
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SelectionOverrideTransparency,   double);
    DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(SelectionOverrideColor, FBColor);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SelectionForceSnapPointsDisplay,   bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(DisplaySetUpdateId,       int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(RendererUpdateId,         int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(DisplayableGeometryCount,  int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(DisplayableLightCount,     int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(RegisteredCallbackCount,   int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CurrentPaneCallbackIndex,   int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CurrentPaneCallbackPrefIndex,   int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(AdvancedMaterialMode,   bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(AdvancedLightingMode,   bool);
};
#endif // pyfbrenderer_h__