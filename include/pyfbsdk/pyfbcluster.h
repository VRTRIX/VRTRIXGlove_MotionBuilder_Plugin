#ifndef pyfbcluster_h__
#define pyfbcluster_h__
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

// =======================================================================================
// FBCluster
// =======================================================================================
void FBCluster_Init();

class PYSDK_DLL FBCluster_Wrapper : public FBComponent_Wrapper {
public:
	FBCluster* mFBCluster;
public:	
    FBCluster_Wrapper( FBModel_Wrapper* pModel ) : FBComponent_Wrapper( pModel->mFBModel->Cluster ) { mFBCluster = (FBCluster*)mFBComponent; }
	FBCluster_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBCluster = (FBCluster*)mFBComponent; }
	virtual ~FBCluster_Wrapper( ) {}
	int ClusterBegin(int pIndex = -1) { return mFBCluster->ClusterBegin( pIndex ); }
	int ClusterEnd() { return mFBCluster->ClusterEnd(); }
	void LinkClearUnused(double pThreshold = -1.0) { mFBCluster->LinkClearUnused( pThreshold ); }
	object LinkGetAssociateModel(int pLinkNumber) { return FBModel_Wrapper_Factory( mFBCluster->LinkGetAssociateModel( pLinkNumber )); }
	int LinkGetCount() { return mFBCluster->LinkGetCount(  ); }
	object LinkGetModel(int pLinkNumber) { return FBModel_Wrapper_Factory( mFBCluster->LinkGetModel( pLinkNumber )); }
	const char* LinkGetName(int pLinkNumber) { return mFBCluster->LinkGetName( pLinkNumber ); }
	int LinkGetVertexIndex(int pIndex) { return mFBCluster->LinkGetVertexIndex( pIndex ); }
	void LinkRemove(int pLinkNumber) { mFBCluster->LinkRemove( pLinkNumber ); }
	void LinkSetCurrentVertex(int pLinkIndex, int pPointIndex) { mFBCluster->LinkSetCurrentVertex( pLinkIndex, pPointIndex ); }
	void LinkSetModel(FBModel_Wrapper& pModel) { mFBCluster->LinkSetModel( pModel.mFBModel ); }
	void LinkSetName(const char * pName, int pLinkNumber) { mFBCluster->LinkSetName( pName, pLinkNumber ); }
	void VertexAdd(int pVertexIndex, double pWeight) { mFBCluster->VertexAdd( pVertexIndex, pWeight ); }
	void VertexClear() { mFBCluster->VertexClear(  ); }
	int VertexGetCount() { return mFBCluster->VertexGetCount(  ); }
	int VertexGetNumber(int pIndex) { return mFBCluster->VertexGetNumber( pIndex ); }
	void VertexGetTransform(FBVector3d_Wrapper& pPosition, FBVector3d_Wrapper& pRotation, FBVector3d_Wrapper& pScaling) { mFBCluster->VertexGetTransform( *(pPosition.mFBVector3d), *(pRotation.mFBVector3d), *(pScaling.mFBVector3d) ); }
	double VertexGetWeight(int pIndex) { return mFBCluster->VertexGetWeight( pIndex ); }
	void VertexRemove(int pVertexIndex) { mFBCluster->VertexRemove( pVertexIndex ); }
	void VertexSetTransform(FBVector3d_Wrapper& pPosition, FBVector3d_Wrapper& pRotation, FBVector3d_Wrapper& pScaling) { mFBCluster->VertexSetTransform( *(pPosition.mFBVector3d), *(pRotation.mFBVector3d), *(pScaling.mFBVector3d) ); }
	void VertexSetWeight(double pWeight, int pIndex) { mFBCluster->VertexSetWeight( pWeight, pIndex ); }
	void SetClusterAccuracy( double pClusterAccuracy ) { mFBCluster->ClusterAccuracy = pClusterAccuracy; }
	double GetClusterAccuracy(  ) { return mFBCluster->ClusterAccuracy; }
	void SetClusterMode( FBClusterMode pClusterMode ) { mFBCluster->ClusterMode = pClusterMode; }
	FBClusterMode GetClusterMode(  ) { return mFBCluster->ClusterMode; }
};
#endif // pyfbcluster_h__