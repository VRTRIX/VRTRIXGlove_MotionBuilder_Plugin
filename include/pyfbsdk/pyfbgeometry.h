#ifndef pyfbgeometry_h__
#define pyfbgeometry_h__
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

// =======================================================================================
// FBGeometry
// =======================================================================================
void FBGeometry_Init();

class FBGeometry_Wrapper;
class FBFastTessellator_Wrapper;
class FBStringList_Wrapper;

class PYSDK_DLL FBGeometry_Wrapper : public FBComponent_Wrapper {
public:
	FBGeometry* mFBGeometry;
public:
	FBGeometry_Wrapper( FBComponent* pFBComponent );
	virtual ~FBGeometry_Wrapper( );
	bool GeometryBegin();
	bool GeometryEnd();
	int  VertexAdd(FBVertex_Wrapper& pVertex);
	int  VertexAdd(double px, double py, double pz);
	bool VertexArrayClear();
    bool VertexClear();
	int  VertexCount();
	FBVertex_Wrapper* VertexGet(int pIndex);
	bool VertexGetSelected(int pIndex);
	bool VertexGetTransformable(int pIndex);
	bool VertexGetVisible(int pIndex);
    bool VertexArrayInit(int pVertexcount, bool pUniqueMaterial, unsigned int pFBGeometryArrayIDs = 0);
    void VertexInit(int pSize, bool pResize, bool pInitUV = true, bool pInitVertexColor = false);
	FBNormal_Wrapper* VertexNormalGet(int pIndex = -1);
	bool VertexNormalSet_1(FBNormal_Wrapper& pNormal, int pIndex = -1);
	bool VertexNormalSet_2(double px, double py, double pz, int pIndex = -1);
	FBColorAndAlpha_Wrapper* VertexColorGet(int pIndex = -1);
	bool VertexColorSet_1(FBColorAndAlpha_Wrapper& pColorAndAlpha, int pIndex = -1);
	bool VertexColorSet_2(double pRed, double pGreen, double pBlue, double pAlpha, int pIndex = -1);
	bool VertexSet_1(FBVertex_Wrapper& pVertex, int pIndex = -1);
	bool VertexSet_2(double px, double py, double pz, int pIndex = -1);
	bool VertexSetSelected(int pIndex, bool pState);
	bool VertexSetVisible(int pIndex, bool pState);
	FBUV_Wrapper* VertexUVGet(int pIndex = -1);
    bool VertexUVSet_1(FBUV_Wrapper& pFBUV, int pIndex = -1);
	bool VertexUVSet_2(float pU, float pV, int pIndex = -1);

    list GetPositionsArray() const;
    bool SetPositionsArray(list pList);

    list GetNormalsDirectArray() const;
    bool SetNormalsDirectArray(list pList);   
    list GetNormalsIndexArray() const;
    bool SetNormalsIndexArray(list pList);
    
    list GetTangentsDirectArray() const;
    bool SetTangentsDirectArray(list pList);
    list GetTangentsIndexArray() const;
    bool SetTangentsIndexArray(list pList);
    
    list GetBinormalsDirectArray() const;
    bool SetBinormalsDirectArray(list pList);
    list GetBinormalsIndexArray() const;
    bool SetBinormalsIndexArray(list pList);
    
    list GetVertexColorsDirectArray() const;
    bool SetVertexColorsDirectArray(list pList);
    list GetVertexColorsIndexArray() const;
    bool SetVertexColorsIndexArray(list pList);
    
    list GetUVSetIndexArray(const char* pUVSetName = NULL) const;
    bool SetUVSetIndexArray(list pList, const char* pUVSetName = NULL);
    list GetUVSetDirectArray(const char* pUVsetName = NULL) const;
    bool SetUVSetDirectArray(list pList, const char* pUVsetName = NULL);
    
    list GetMaterialIndexArray() const;
    bool SetMaterialIndexArray(list pList);

    int  ShapeGetCount() const;
	const char* ShapeGetName(int pShapeIdx) const;
	int  ShapeAdd(const char* pName);
	void ShapeClearAll();
	void ShapeInit(int pShapeIdx, int pDiffSize, bool pWithNormal = false );
	bool ShapeSetDiffPoint(int pShapeIdx, int pDiffIndex, int pOriIndex, const FBVertex_Wrapper& pPosDiff, const FBNormal_Wrapper& pNormalDiff = FBNormal_Wrapper());
	bool ShapeGetDiffPoint(int pShapeIdx, int pDiffIndex, int& pOriIndex, FBVertex_Wrapper& pPosDiff, FBNormal_Wrapper& pNormalDiff);

    FBStringList_Wrapper*    GetUVSets();
    FBGeometryMappingMode    GetUVSetMappingMode  (const char* pUVSetName = NULL) const;
    FBGeometryReferenceMode  GetUVSetReferenceMode(const char* pUVSetName = NULL) const;

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( MaterialMappingMode,		FBGeometryMappingMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( NormalMappingMode,		FBGeometryMappingMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( NormalReferenceMode,		FBGeometryReferenceMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( TangentMappingMode,		FBGeometryMappingMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( TangentReferenceMode,	FBGeometryReferenceMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( BinormalMappingMode,		FBGeometryMappingMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( BinormalReferenceMode,	FBGeometryReferenceMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( VertexColorMappingMode,	FBGeometryMappingMode );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( VertexColorReferenceMode,FBGeometryReferenceMode );
};
#endif // pyfbgeometry_h__