#ifndef pyfbmesh_h__
#define pyfbmesh_h__
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

#include "pyfbgeometry.h"

// =======================================================================================
// FBMesh
// =======================================================================================
void FBMesh_Init();

class PYSDK_DLL FBMesh_Wrapper : public FBGeometry_Wrapper {
public:
	FBMesh* mFBMesh;
public:
	FBMesh_Wrapper( FBComponent* pFBComponent ) : FBGeometry_Wrapper( pFBComponent ) { mFBMesh = (FBMesh*)pFBComponent; }
	FBMesh_Wrapper( const char* pName ) : FBGeometry_Wrapper( new FBMesh( pName )) { mFBMesh = (FBMesh*)mFBComponent; }
	virtual ~FBMesh_Wrapper( ) {}

    int PolygonBegin(int pMaterialId=0);
	bool PolygonVertexAdd(int pVertex);
    int PolygonEnd();
	int PolygonCount() const { return mFBMesh->PolygonCount(  ); }
    int PolygonMaterialIdGet(int pIndex = -1) const { return mFBMesh->PolygonMaterialIdGet( pIndex ); }
	int PolygonVertexCount(int pPolygonIndex) const { return mFBMesh->PolygonVertexCount( pPolygonIndex ); }
	int PolygonVertexIndex(int pPolygonIndex, int pVertexPolygonIndex) const { return mFBMesh->PolygonVertexIndex( pPolygonIndex, pVertexPolygonIndex ); }
	void ComputeVertexNormals(bool pCW = false) { mFBMesh->ComputeVertexNormals(pCW); }
	void InverseNormal() { mFBMesh->InverseNormal(); }
    list PolygonVertexArrayGet() const;
    bool IsTriangleMesh() const;
    bool TriangleListAdd(int pIndexArraySize, list pIndexArray, int pMaterialId=0);
    bool TriangleStripAdd(int pIndexArraySize, list pIndexArray, int pMaterialId=0);
    bool PolygonListAdd(int pPolygonSize, int pIndexArraySize, list pIndexArray, int pMaterialId=0);
};
#endif // pyfbmesh_h__
