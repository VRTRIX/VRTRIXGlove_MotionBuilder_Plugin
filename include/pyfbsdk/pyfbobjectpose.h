#ifndef pyfbobjectpose_h__
#define pyfbobjectpose_h__
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
#include "pyfbpose.h"
#include "pyfbobjectposeoptions.h"
#include "pyfbobjectposemirroroptions.h"

// =======================================================================================
// FBObjectPose
// =======================================================================================
void FBObjectPose_Init();

class PYSDK_DLL FBObjectPose_Wrapper : public FBPose_Wrapper {
public:
	FBObjectPose* mFBObjectPose;
public:
	FBObjectPose_Wrapper( FBComponent* pFBComponent ) : FBPose_Wrapper( pFBComponent ) { mFBObjectPose = (FBObjectPose*)pFBComponent; }
	FBObjectPose_Wrapper( const char* pName ) : FBPose_Wrapper( new FBObjectPose( pName )) { mFBObjectPose = (FBObjectPose*)mFBComponent; }
	virtual ~FBObjectPose_Wrapper( ) { }
	void AddStanceOffsetAllObjects(FBObjectPose_Wrapper& pStancePose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid) { mFBObjectPose->AddStanceOffsetAllObjects( *pStancePose.mFBObjectPose, pPoseTransformType ); }
	void AddStanceOffset(const char * pObjectName, FBObjectPose_Wrapper& pStancePose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid) { mFBObjectPose->AddStanceOffset( pObjectName, *pStancePose.mFBObjectPose, pPoseTransformType ); }
	void ClearPose() { mFBObjectPose->ClearPose(  ); }
	void CopyFrom(FBObjectPose_Wrapper& pFromPose) { mFBObjectPose->CopyFrom( *pFromPose.mFBObjectPose ); }
	void CopyObjectPose(const char * pObjectName, FBComponent_Wrapper& pObject) { mFBObjectPose->CopyObjectPose( pObjectName, *pObject.mFBComponent ); }
	void CopyPropertyPose(const char * pObjectName, FBProperty_Wrapper& pProperty) { mFBObjectPose->CopyPropertyPose( pObjectName, *pProperty.mFBProperty ); }
	void CopyPoseDataFrom(FBObjectPose_Wrapper& pFromPose) { mFBObjectPose->CopyPoseDataFrom( *pFromPose.mFBObjectPose ); }
	void CopyPoseAllObjectsTransformFrom(FBObjectPose_Wrapper& pFromPose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid) { mFBObjectPose->CopyPoseAllObjectsTransformFrom( *pFromPose.mFBObjectPose, pPoseTransformType ); }
	void CopyPoseTransformFrom(FBObjectPose_Wrapper& pFromPose, const char * pObjectName, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid) { mFBObjectPose->CopyPoseTransformFrom( *pFromPose.mFBObjectPose, pObjectName, pPoseTransformType ); }
	void CopyTransform(const char * pObjectName, FBComponent_Wrapper& pObject, FBObjectPoseOptions_Wrapper& pObjectPoseOptions) { mFBObjectPose->CopyTransform( pObjectName, *pObject.mFBComponent, *pObjectPoseOptions.mFBObjectPoseOptions ); }
	void GetPropertyValue(list &pValue, int pSize, const char * pObjectName, const char * pPropertyName);
	bool GetTransform(FBTVector & pT, FBMatrix_Wrapper& pRM, FBMatrix_Wrapper& pSM, const char * pObjectName, FBPoseTransformType pPoseTransformType) { return mFBObjectPose->GetTransform( pT, *pRM.mFBMatrix, *pSM.mFBMatrix, pObjectName, pPoseTransformType ); }
	bool IsPropertyPoseable(FBProperty_Wrapper& pProperty) { return mFBObjectPose->IsPropertyPoseable( *pProperty.mFBProperty ); }
	bool IsPropertyStored(const char * pObjectName, const char * pPropertyName) { return mFBObjectPose->IsPropertyStored( pObjectName, pPropertyName ); }
	bool IsTransformStored(const char * pObjectName, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid) { return mFBObjectPose->IsTransformStored( pObjectName, pPoseTransformType ); }
	void MirrorPoseAllObjects(FBObjectPoseMirrorOptions_Wrapper& pObjectPoseMirrorOptions) { mFBObjectPose->MirrorPoseAllObjects( *pObjectPoseMirrorOptions.mFBObjectPoseMirrorOptions ); }
	void MirrorPose(const char * pObjectName, FBObjectPoseMirrorOptions_Wrapper& pObjectPoseMirrorOptions) { mFBObjectPose->MirrorPose( pObjectName, *pObjectPoseMirrorOptions.mFBObjectPoseMirrorOptions ); }
	void MultTransformAllObjects(FBMatrix_Wrapper& pGX, FBModelTransformationType pTransformAttribute, FBPoseTransformType pPoseTransformType) { mFBObjectPose->MultTransformAllObjects( *pGX.mFBMatrix, pTransformAttribute, pPoseTransformType ); }
	void MultTransform(const char * pObjectName, FBMatrix_Wrapper& pGX, FBModelTransformationType pTransformAttribute, FBPoseTransformType pPoseTransformType) { mFBObjectPose->MultTransform( pObjectName, *pGX.mFBMatrix, pTransformAttribute, pPoseTransformType ); }
	void PasteObjectPose(const char * pObjectName, FBComponent_Wrapper& pObject) { mFBObjectPose->PasteObjectPose( pObjectName, *pObject.mFBComponent ); }
	void PastePropertyPose(const char * pObjectName, FBProperty_Wrapper& pProperty) { mFBObjectPose->PastePropertyPose( pObjectName, *pProperty.mFBProperty ); }
	void PasteTransform(const char * pObjectName, FBComponent_Wrapper& pObject, FBObjectPoseOptions_Wrapper& pObjectPoseOptions) { mFBObjectPose->PasteTransform( pObjectName, *pObject.mFBComponent, *pObjectPoseOptions.mFBObjectPoseOptions ); }
	void RemoveStanceOffsetAllObjects(FBObjectPose_Wrapper& pStancePose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid) { mFBObjectPose->RemoveStanceOffsetAllObjects( *pStancePose.mFBObjectPose, pPoseTransformType ); }
	void RemoveStanceOffset(const char * pObjectName, FBObjectPose_Wrapper& pStancePose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid) { mFBObjectPose->RemoveStanceOffset( pObjectName, *pStancePose.mFBObjectPose, pPoseTransformType ); }
	void SetPropertyValue(const char * pObjectName, const char * pPropertyName, double * pValue, int pSize) { mFBObjectPose->SetPropertyValue( pObjectName, pPropertyName, pValue, pSize ); }
	void SetTransform(FBTVector & pT, FBMatrix_Wrapper& pRM, FBMatrix_Wrapper& pSM, const char * pObjectName, FBPoseTransformType pPoseTransformType) { mFBObjectPose->SetTransform( pT, *pRM.mFBMatrix, *pSM.mFBMatrix, pObjectName, pPoseTransformType ); }
};
#endif // pyfbobjectpose_h__