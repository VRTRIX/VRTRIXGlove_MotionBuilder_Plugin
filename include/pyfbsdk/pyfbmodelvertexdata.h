#ifndef pyfbmodelvertexdata_h__
#define pyfbmodelvertexdata_h__
/**************************************************************************
 Copyright 2012 Autodesk, Inc.
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
// FBModelVertexData
// =======================================================================================
void FBModelVertexData_Init();

class PYSDK_DLL FBModelVertexData_Wrapper : public FBComponent_Wrapper 
{
public:
	FBModelVertexData* mFBModelVertexData;
public:
	FBModelVertexData_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBModelVertexData = (FBModelVertexData*)pFBComponent; }

    virtual ~FBModelVertexData_Wrapper( ) {}

    int     GetSubRegionCount() { return mFBModelVertexData->GetSubPatchCount(); }
    object  GetSubRegionMaterial(int pSubRegionIndex) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModelVertexData->GetSubRegionMaterial(pSubRegionIndex)); }
    void    DrawSubRegion(int pSubRegionIndex, bool pWireFrame = false) { mFBModelVertexData->DrawSubRegion(pSubRegionIndex, pWireFrame); }
    void    EnableOGLVertexData(bool pAfterdeform = true) { mFBModelVertexData->EnableOGLVertexData(pAfterdeform); }
    void    DisableOGLVertexData() { mFBModelVertexData->DisableOGLVertexData(); }
    void    EnableOGLUVSet(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL) { mFBModelVertexData->EnableOGLUVSet(pTextureMapping, pUVSet); }
    void    DisableOGLUVSet() { mFBModelVertexData->DisableOGLUVSet(); }

    //bool IsDeformable()         { return mFBModelVertexData->IsDeformable(); }        
    //bool IsDrawable()           { return mFBModelVertexData->IsDrawable();   }
    //int  GetVertexCount()       { return mFBModelVertexData->GetVertexCount();   }
    //int  GetSubPatchCount();    { return mFBModelVertexData->GetSubPatchCount(); }
    //int  GetSubPatchMaterialId(int pSubPatchIndex) { return mFBModelVertexData->GetSubPatchMaterialId(pSubPatchIndex); }
    //object GetSubPatchMaterial(int pSubPatchIndex) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModelVertexData->GetSubPatchMaterial(pSubPatchIndex)); }
    //FBGeometryPrimitiveType GetSubPatchPrimitiveType(int pSubPatchIndex, bool* pIsOptimized = NULL);
    //int GetSubPatchIndexOffset(int pSubPatchIndex)
    //int GetSubPatchIndexSize(int pSubPatchIndex);
    //void DrawSubPatch(int pSubPatchIndex, bool pWireFrame = false) { return mFBModelVertexData->DrawSubPatch(pSubPatchIndex, pWireFrame); }
    //void VertexArrayMappingRequest() { mFBModelVertexData->VertexArrayMappingRequest(); }
    //const int* GetVertexArrayDuplicationMap(unsigned int& pDuplicatedVertexCound)
    //void VertexArrayMappingRelease();
    //int* GetIndexArray();
    //unsigned int GetIndexArrayVBOId();
    //FBGeometryArrayElementType GetVertexArrayType(FBGeometryArrayID pArrayId, bool pAfterDeform = true);
    //void* GetVertexArray(FBGeometryArrayID pArrayId, bool pAfterDeform = true);
    //unsigned int GetVertexArrayVBOId(FBGeometryArrayID pArrayId, bool pAfterDeform = true);
    //void* GetVertexArrayVBOOffset(FBGeometryArrayID pArrayId, bool pAfterDeform = true);
    //FBGeometryArrayElementType GetUVSetArrayFormat(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);
    //void* GetUVSetArray(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);
    //unsigned int GetUVSetVBOId(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);
    //void* GetUVSetVBOOffset(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);
};

#endif // pyfbmesh_h__
