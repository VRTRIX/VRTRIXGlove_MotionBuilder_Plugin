#ifndef pyfbmarkerset_h__
#define pyfbmarkerset_h__
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
#include "pyfbplotoptions.h"
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbpose.h"
#include "pyfbconstraint.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"

// =======================================================================================
// FBMarkerSet
// =======================================================================================
void FBMarkerSet_Init();

class PYSDK_DLL FBMarkerSet_Wrapper : public FBComponent_Wrapper {
public:
	FBMarkerSet* mFBMarkerSet;
public:
	FBMarkerSet_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBMarkerSet = (FBMarkerSet*)pFBComponent; }
	FBMarkerSet_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBMarkerSet( pName )) { mFBMarkerSet = (FBMarkerSet*)mFBComponent; }
	virtual ~FBMarkerSet_Wrapper( ) {}
    int AddMarker(FBSkeletonNodeId pNodeId, FBModel_Wrapper* pModel = NULL, bool pIsOriented = false) { return mFBMarkerSet->AddMarker( pNodeId, pModel ? pModel->mFBModel : NULL, pIsOriented ); }
	void BeginTransaction() { mFBMarkerSet->BeginTransaction(  ); }
	void EndTransaction() { mFBMarkerSet->EndTransaction(  ); }
	int GetMarkerCount(FBSkeletonNodeId pNodeId = kFBSkeletonInvalidIndex) { return mFBMarkerSet->GetMarkerCount( pNodeId ); }
	object GetMarkerModel(FBSkeletonNodeId pNodeId, int pMarkerIndex) { return FBModel_Wrapper_Factory( mFBMarkerSet->GetMarkerModel( pNodeId, pMarkerIndex )); }
	const char* GetMarkerName(FBSkeletonNodeId pNodeId, int pMarkerIndex) { return mFBMarkerSet->GetMarkerName( pNodeId, pMarkerIndex ); }
	bool GetMarkerOriented(FBSkeletonNodeId pNodeId, int pMarkerIndex) { return mFBMarkerSet->GetMarkerOriented( pNodeId, pMarkerIndex ); }
    void GetMarkerROffset(FBSkeletonNodeId pNodeId, int pMarkerIndex, FBVector3d_Wrapper& pROffset) { mFBMarkerSet->GetMarkerROffset( pNodeId, pMarkerIndex, (FBRVector*)pROffset.mFBVector3d ); }
    void GetMarkerTOffset(FBSkeletonNodeId pNodeId, int pMarkerIndex, FBVector3d_Wrapper& pTOffset) { mFBMarkerSet->GetMarkerTOffset( pNodeId, pMarkerIndex, (FBTVector*)pTOffset.mFBVector3d ); }
	bool GetMarkerUsed(FBSkeletonNodeId pNodeId, int pMarkerIndex) { return mFBMarkerSet->GetMarkerUsed( pNodeId, pMarkerIndex ); }
	object GetReferenceModel() { return FBModel_Wrapper_Factory( mFBMarkerSet->GetReferenceModel(  )); }
	int GetUsedMarkerCount(FBSkeletonNodeId pNodeId = kFBSkeletonInvalidIndex) { return mFBMarkerSet->GetUsedMarkerCount( pNodeId ); }
	void SetMarkerModel(FBSkeletonNodeId pNodeId, int pMarkerIndex, FBModel_Wrapper& pModel) { mFBMarkerSet->SetMarkerModel( pNodeId, pMarkerIndex, pModel.mFBModel ); }
	void SetMarkerName(FBSkeletonNodeId pNodeId, int pMarkerIndex, const char * pMarkerName) { mFBMarkerSet->SetMarkerName( pNodeId, pMarkerIndex, pMarkerName ); }
	void SetMarkerOriented(FBSkeletonNodeId pNodeId, int pMarkerIndex, bool pIsOriented) { mFBMarkerSet->SetMarkerOriented( pNodeId, pMarkerIndex, pIsOriented ); }
    void SetMarkerROffset(FBSkeletonNodeId pNodeId, int pMarkerIndex, FBVector3d_Wrapper& pROffset) { mFBMarkerSet->SetMarkerROffset( pNodeId, pMarkerIndex, (FBRVector*)pROffset.mFBVector3d ); }
    void SetMarkerTOffset(FBSkeletonNodeId pNodeId, int pMarkerIndex, FBVector3d_Wrapper& pTOffset) { mFBMarkerSet->SetMarkerTOffset( pNodeId, pMarkerIndex, (FBTVector*)pTOffset.mFBVector3d ); }
	void SetMarkerUsed(FBSkeletonNodeId pNodeId, int pMarkerIndex, bool pUsed) { mFBMarkerSet->SetMarkerUsed( pNodeId, pMarkerIndex, pUsed ); }
	bool SetMultipleMarkerModels(FBModelList_Wrapper& pModelList) { return mFBMarkerSet->SetMultipleMarkerModels( pModelList.mFBModelList ); }
	void SetReferenceModel(FBModel_Wrapper& pReferenceModel) { mFBMarkerSet->SetReferenceModel( pReferenceModel.mFBModel ); }
	void SetMarkerSetVisibility(bool pVisibility) { return mFBMarkerSet->SetMarkerSetVisibility( pVisibility ); }
	int GetMarkerSetVisibility() { return mFBMarkerSet->GetMarkerSetVisibility(); }
	bool GetLinkToModelOk() { return mFBMarkerSet->GetLinkToModelOk(); }
};
#endif // pyfbmarkerset_h__