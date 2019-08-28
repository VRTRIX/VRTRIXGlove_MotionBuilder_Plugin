#ifndef pyfbmodel_h__
#define pyfbmodel_h__
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
#include "pyfbboxplaceholder.h"
#include "pyfbgeometry.h"
#include "pyfbmath.h"

// =======================================================================================
// FBModel
// =======================================================================================
void FBModel_Init();

class FBCamera_Wrapper;

class PYSDK_DLL FBModel_Wrapper : public FBBox_Wrapper 
{
public:
    FBModel* mFBModel;

public:
    FBModel_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBModel = (FBModel*)pFBComponent; }
    FBModel_Wrapper( const char* pName ) : FBBox_Wrapper( new FBModel( pName )) { mFBModel = (FBModel*)mFBComponent; }
    virtual ~FBModel_Wrapper( ) {}
    void FBDelete() { mFBModel->FBDelete(  ); }
    object Clone() { return FBModel_Wrapper_Factory( mFBModel->Clone(  )); }	
    const char* FbxGetObjectSubType() { return mFBModel->FbxGetObjectSubType(  ); }
    const char* FbxGetObjectType() { return mFBModel->FbxGetObjectType(  ); }
    void GetBoundingBox(FBVector3d_Wrapper& pMin, FBVector3d_Wrapper& pMax) { mFBModel->GetBoundingBox( *pMin.mFBVector3d, *pMax.mFBVector3d ); }
    void GetMatrix(FBMatrix_Wrapper& pMatrix, FBModelTransformationType pWhat = kModelTransformation, bool pGlobalInfo = true, FBEvaluateInfo_Wrapper *pEvalInfo = NULL) 
    { mFBModel->GetMatrix( *pMatrix.mFBMatrix, pWhat, pGlobalInfo, (pEvalInfo) ? pEvalInfo->mFBEvaluateInfo : NULL ); }
    list GetHierarchyWorldMatrices(unsigned int pMatricesCountMax, FBModelHiercharyTraverserType pHiercharyTraverserType, FBEvaluateInfo_Wrapper *pEvalInfo = NULL);
    int GetSelectedPointsCount() { return mFBModel->GetSelectedPointsCount(  ); }
    void GetVector(FBVector3d_Wrapper& pVector, FBModelTransformationType pWhat = kModelTranslation, bool pGlobalInfo = true, FBEvaluateInfo_Wrapper *pEvalInfo = NULL) 
    { mFBModel->GetVector( *pVector.mFBVector3d, pWhat, pGlobalInfo, (pEvalInfo) ? pEvalInfo->mFBEvaluateInfo : NULL ); }
    void SetMatrix(FBMatrix_Wrapper& pMatrix, FBModelTransformationType pWhat = kModelTransformation, bool pGlobalInfo = true, FBEvaluateInfo_Wrapper *pEvalInfo = NULL) 
    { mFBModel->SetMatrix( *pMatrix.mFBMatrix, pWhat, pGlobalInfo, false, (pEvalInfo) ? pEvalInfo->mFBEvaluateInfo : NULL ); }
    void SetMatrixWithPrecision(FBMatrix_Wrapper& pMatrix, FBModelTransformationType pWhat = kModelTransformation, bool pGlobalInfo = true, FBEvaluateInfo_Wrapper *pEvalInfo = NULL, double pPrecision = FBMat2EulerDegenerateForPrecision10) 
    { mFBModel->SetMatrixWithPrecision( *pMatrix.mFBMatrix, pWhat, pGlobalInfo, false, (pEvalInfo) ? pEvalInfo->mFBEvaluateInfo : NULL, pPrecision ); }
    void SetVector(FBVector3d_Wrapper& pVector, FBModelTransformationType pWhat = kModelTranslation, bool pGlobalInfo = true, FBEvaluateInfo_Wrapper *pEvalInfo = NULL) 
    { mFBModel->SetVector( *pVector.mFBVector3d, pWhat, pGlobalInfo, (pEvalInfo) ? pEvalInfo->mFBEvaluateInfo : NULL ); }
    void MatrixToRotation(FBVector3d_Wrapper& pVector, FBMatrix_Wrapper& pMatrix) {  mFBModel->MatrixToRotation(*pVector.mFBVector3d, *pMatrix.mFBMatrix); }
    void RotationToMatrix(FBMatrix_Wrapper& pMatrix, FBVector3d_Wrapper& pVector) { mFBModel->RotationToMatrix(*pMatrix.mFBMatrix, *pVector.mFBVector3d); }
    void LRMToDof(FBVector3d_Wrapper& pDof, FBMatrix_Wrapper& pLRM) { mFBModel->LRMToDof(*pDof.mFBVector3d, *pLRM.mFBMatrix);}
    void DofToLRM(FBMatrix_Wrapper& pLRM, FBVector3d_Wrapper& pDof) { mFBModel->DofToLRM(*pLRM.mFBMatrix, *pDof.mFBVector3d); }
    void SetSchematicPosition(int pX,int pY){ mFBModel->SetSchematicPosition(pX,pY); }
    void SetSchematicPosition(FBVector2d_Wrapper &pVector2d){ mFBModel->SetSchematicPosition(*(pVector2d.mFBVector2d)); }
    FBVector2d_Wrapper* GetSchematicPosition(){ return FBVector2d_Wrapper_Factory( mFBModel->GetSchematicPosition() );}
    object GetAnimationNode(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModel->AnimationNode ); }
    object GetChildren(  ) { return FBPropertyListModel_Wrapper_Factory( mFBModel->Children ); }
    void SetGeometricRotation( FBVector3d_Wrapper& pGeometricRotation ) { mFBModel->GeometricRotation = *pGeometricRotation.mFBVector3d; }
    FBVector3d_Wrapper* GetGeometricRotation(  ) { return FBVector3d_Wrapper_Factory( mFBModel->GeometricRotation ); }
    void SetGeometricScaling( FBVector3d_Wrapper& pGeometricScaling ) { mFBModel->GeometricScaling = *pGeometricScaling.mFBVector3d; }
    FBVector3d_Wrapper* GetGeometricScaling(  ) { return FBVector3d_Wrapper_Factory( mFBModel->GeometricScaling ); }
    void SetGeometricTranslation( FBVector3d_Wrapper& pGeometricTranslation ) { mFBModel->GeometricTranslation = *pGeometricTranslation.mFBVector3d; }
    FBVector3d_Wrapper* GetGeometricTranslation(  ) { return FBVector3d_Wrapper_Factory( mFBModel->GeometricTranslation ); }
    object GetGeometry(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModel->Geometry ); }
    void SetGeometry(FBGeometry_Wrapper& pGeometry  ) { mFBModel->Geometry = pGeometry.mFBGeometry; }
    object GetModelVertexData(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModel->ModelVertexData ); }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Icon3D,  bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(IsDeformable,  bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(IsConstrained, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(GeometryUpdateId, int)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SkeletonDeformable, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(BlendShapeDeformable, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ConstrainDeformable, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PointCacheDeformable, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PointCacheRecord, bool)
    FBColor_Wrapper* GetUniqueColorId() { return FBColor_Wrapper_Factory( mFBModel->UniqueColorId ); }
    bool SetAdditionalUniqueColorIDCount(unsigned int pCount) { return mFBModel->SetAdditionalUniqueColorIDCount(pCount); }
    unsigned int GetAdditionalUniqueColorIDCount() const { return mFBModel->GetAdditionalUniqueColorIDCount(); }
    FBColor_Wrapper* GetAdditionalUniqueColorID(unsigned int pIndex) { return FBColor_Wrapper_Factory(mFBModel->GetAdditionalUniqueColorID(pIndex)); }
    void SetLookAt( FBModel_Wrapper& pLookAt ) { mFBModel->LookAt = pLookAt.mFBModel; }
    object GetLookAt(  ) { return FBModel_Wrapper_Factory( mFBModel->LookAt ); }
    void SetParent( FBModel_Wrapper* pParent ) { mFBModel->Parent = pParent ? pParent->mFBModel : NULL; }
    object GetParent(  ) { return FBModel_Wrapper_Factory( mFBModel->Parent ); }
    void SetPostRotation( FBVector3d_Wrapper& pPostRotation ) { mFBModel->PostRotation = *pPostRotation.mFBVector3d; }
    FBVector3d_Wrapper* GetPostRotation(  ) { return FBVector3d_Wrapper_Factory( mFBModel->PostRotation ); }
    void SetPreRotation( FBVector3d_Wrapper& pPreRotation ) { mFBModel->PreRotation = *pPreRotation.mFBVector3d; }
    FBVector3d_Wrapper* GetPreRotation(  ) { return FBVector3d_Wrapper_Factory( mFBModel->PreRotation ); }
    void SetQuaternionInterpolate( bool pQuaternionInterpolate ) { mFBModel->QuaternionInterpolate = pQuaternionInterpolate; }
    bool GetQuaternionInterpolate(  ) { return mFBModel->QuaternionInterpolate; }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PrimaryVisibility, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CastsShadows, bool)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ReceiveShadows, bool)
    void SetRotation( FBVector3d_Wrapper& pRotation ) { mFBModel->Rotation = *pRotation.mFBVector3d; }
    object GetRotation(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBModel->Rotation ); }
    void SetRotationActive( bool pRotationActive ) { mFBModel->RotationActive = pRotationActive; }
    bool GetRotationActive(  ) { return mFBModel->RotationActive; }
    void SetRotationMax( FBVector3d_Wrapper& pRotationMax ) { mFBModel->RotationMax = *pRotationMax.mFBVector3d; }
    FBVector3d_Wrapper* GetRotationMax(  ) { return FBVector3d_Wrapper_Factory( mFBModel->RotationMax ); }
    void SetRotationMaxX( bool pRotationMaxX ) { mFBModel->RotationMaxX = pRotationMaxX; }
    bool GetRotationMaxX(  ) { return mFBModel->RotationMaxX; }
    void SetRotationMaxY( bool pRotationMaxY ) { mFBModel->RotationMaxY = pRotationMaxY; }
    bool GetRotationMaxY(  ) { return mFBModel->RotationMaxY; }
    void SetRotationMaxZ( bool pRotationMaxZ ) { mFBModel->RotationMaxZ = pRotationMaxZ; }
    bool GetRotationMaxZ(  ) { return mFBModel->RotationMaxZ; }
    void SetRotationMin( FBVector3d_Wrapper& pRotationMin ) { mFBModel->RotationMin = *pRotationMin.mFBVector3d; }
    FBVector3d_Wrapper* GetRotationMin(  ) { return FBVector3d_Wrapper_Factory( mFBModel->RotationMin ); }
    void SetRotationMinX( bool pRotationMinX ) { mFBModel->RotationMinX = pRotationMinX; }
    bool GetRotationMinX(  ) { return mFBModel->RotationMinX; }
    void SetRotationMinY( bool pRotationMinY ) { mFBModel->RotationMinY = pRotationMinY; }
    bool GetRotationMinY(  ) { return mFBModel->RotationMinY; }
    void SetRotationMinZ( bool pRotationMinZ ) { mFBModel->RotationMinZ = pRotationMinZ; }
    bool GetRotationMinZ(  ) { return mFBModel->RotationMinZ; }
    void SetRotationOrder( FBModelRotationOrder pRotationOrder ) { mFBModel->RotationOrder = pRotationOrder; }
    FBModelRotationOrder GetRotationOrder(  ) { return mFBModel->RotationOrder; }
    void SetRotationSpaceForLimitOnly( bool pRotationSpaceForLimitOnly ) { mFBModel->RotationSpaceForLimitOnly = pRotationSpaceForLimitOnly; }
    bool GetRotationSpaceForLimitOnly(  ) { return mFBModel->RotationSpaceForLimitOnly; }
    void SetScaling( FBVector3d_Wrapper& pScaling ) { mFBModel->Scaling = *pScaling.mFBVector3d; }
    object GetScaling(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBModel->Scaling ); }
    object GetScene(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModel->Scene ); }
    void SetSelected( bool pSelected ) { mFBModel->Selected = pSelected; }
    bool GetSelected(  ) { return mFBModel->Selected; }
    object GetShaders(  ) { return FBPropertyListShader_Wrapper_Factory( mFBModel->Shaders ); }
    object GetMaterials(  ) { return FBPropertyListMaterial_Wrapper_Factory( mFBModel->Materials ); }
    object GetTextures(  ) { return FBPropertyListTexture_Wrapper_Factory( mFBModel->Textures ); }
    object GetDeformers(  ) { return FBPropertyListDeformer_Wrapper_Factory( mFBModel->Deformers ); }
    void SetShadingMode( FBModelShadingMode pShadingMode ) { mFBModel->ShadingMode = pShadingMode; }
    FBModelShadingMode GetShadingMode(  ) { return mFBModel->ShadingMode; }	
    FBModelCullingMode GetCullingMode() const { return mFBModel->GetCullingMode(); }
    void SetCullingMode(FBModelCullingMode pCullingMode ) { mFBModel->SetCullingMode( pCullingMode ); }   
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBModel, Pickable, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBModel, Show, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBModel, Transformable, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBModel, SoftSelected, bool);
    void SetTranslation( FBVector3d_Wrapper& pTranslation ) { mFBModel->Translation = *pTranslation.mFBVector3d; }
    object GetTranslation(  ) { return WrapFBObject<FBPropertyAnimatableVector3d_Wrapper,FBPropertyAnimatableVector3d>( &mFBModel->Translation ); }
    void SetUpVector( FBModel_Wrapper& pUpVector ) { mFBModel->UpVector = pUpVector.mFBModel; }
    object GetUpVector(  ) { return FBModel_Wrapper_Factory( mFBModel->UpVector ); }
    void SetVisibility( bool pVisibility ) { mFBModel->Visibility = pVisibility; }
    object GetVisibility(  ) { return WrapFBObject<FBPropertyAnimatableBool_Wrapper,FBPropertyAnimatableBool>( &mFBModel->Visibility ); }
    bool IsVisible() { return mFBModel->IsVisible(); }
    bool IsEvaluationReady(FBModelEvaluationTaskType pWhat, FBEvaluateInfo_Wrapper* pEvalInfo=NULL) const { return mFBModel->IsEvaluationReady( pWhat, (pEvalInfo) ? pEvalInfo->mFBEvaluateInfo : NULL ); }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(VisibilityInheritance, bool)
    void ForceAlwaysEvaluate()      { mFBModel->ForceAlwaysEvaluate(); }
    bool IsForceAlwaysEvaluate()    { return mFBModel->IsForceAlwaysEvaluate(); }
    int  NoFrustumCullingRequire()  { return mFBModel->NoFrustumCullingRequire() ;}
    int  NoFrustumCullingRelease()  { return mFBModel->NoFrustumCullingRelease() ;}
    bool UseFrustumCulling()        { return mFBModel->UseFrustumCulling() ;}
    void SetupPropertiesForShapes() { mFBModel->SetupPropertiesForShapes(); }
    bool RayCast(FBCamera_Wrapper* pCamera, int pMouseX, int pMouseY, FBVector3d_Wrapper& pHitPosition,  FBVector3d_Wrapper& pHitNormal);
};

#endif // pyfbmodel_h__
