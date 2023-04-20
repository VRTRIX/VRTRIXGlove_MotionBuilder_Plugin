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

    int     GetSubRegionCount() { return mFBModelVertexData->GetSubRegionCount(); }
    object  GetSubRegionMaterial(int pSubRegionIndex) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModelVertexData->GetSubRegionMaterial(pSubRegionIndex)); }
    void    DrawSubRegion(int pSubRegionIndex, bool pWireFrame = false) { mFBModelVertexData->DrawSubRegion(pSubRegionIndex, pWireFrame); }
    void    EnableOGLVertexData(bool pAfterdeform = true) { mFBModelVertexData->EnableOGLVertexData(pAfterdeform); }
    void    DisableOGLVertexData() { mFBModelVertexData->DisableOGLVertexData(); }
    void    EnableOGLUVSet(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL) { mFBModelVertexData->EnableOGLUVSet(pTextureMapping, pUVSet); }
    void    DisableOGLUVSet() { mFBModelVertexData->DisableOGLUVSet(); }

    bool    IsDeformable()         { return mFBModelVertexData->IsDeformable(); }
    bool    IsDrawable()           { return mFBModelVertexData->IsDrawable(); }
    int     GetVertexCount()       { return mFBModelVertexData->GetVertexCount(); }
    int     GetSubPatchCount()     { return mFBModelVertexData->GetSubPatchCount(); }
    int     GetSubPatchMaterialId(int pSubPatchIndex)     { return mFBModelVertexData->GetSubPatchMaterialId(pSubPatchIndex); }
    object  GetSubPatchMaterial(int pSubPatchIndex)       { return FBWrapperFactory::TheOne().WrapFBObject( mFBModelVertexData->GetSubPatchMaterial(pSubPatchIndex)); }
    tuple   GetSubPatchPrimitiveType(int pSubPatchIndex);
    int     GetSubPatchIndexOffset(int pSubPatchIndex)    { return mFBModelVertexData->GetSubPatchIndexOffset(pSubPatchIndex); }
    int     GetSubPatchIndexSize(int pSubPatchIndex)      { return mFBModelVertexData->GetSubPatchIndexSize(pSubPatchIndex); }
    void    DrawSubPatch(int pSubPatchIndex, bool pWireFrame = false) { return mFBModelVertexData->DrawSubPatch(pSubPatchIndex, pWireFrame); }
    void    PushZDepthClipOverride()                      { mFBModelVertexData->PushZDepthClipOverride(); }
    void    PopZDepthClipOverride()                       { mFBModelVertexData->PopZDepthClipOverride(); }
    void    VertexArrayMappingRequest()                   { mFBModelVertexData->VertexArrayMappingRequest(); }
    void    VertexArrayMappingRelease()                   { mFBModelVertexData->VertexArrayMappingRelease(); }
    list    GetVertexArrayDuplicationMap();
    int     GetIndexArraySize()                           { return mFBModelVertexData->GetIndexArraySize(); }
    list    GetIndexArray();
    unsigned int GetIndexArrayVBOId()                     { return mFBModelVertexData->GetIndexArrayVBOId(); }
    FBGeometryArrayElementType GetVertexArrayType	(FBGeometryArrayID pArrayId, bool pAfterDeform = true)									{ return mFBModelVertexData->GetVertexArrayType(pArrayId, pAfterDeform); }
    list GetVertexArray								(FBGeometryArrayID pArrayId, bool pAfterDeform = true);
    unsigned int GetVertexArrayVBOId				(FBGeometryArrayID pArrayId, bool pAfterDeform = true)									{ return mFBModelVertexData->GetVertexArrayVBOId(pArrayId, pAfterDeform); }
    kReference GetVertexArrayVBOOffset				(FBGeometryArrayID pArrayId, bool pAfterDeform = true)									{ return (kReference)mFBModelVertexData->GetVertexArrayVBOOffset(pArrayId, pAfterDeform); }
    FBGeometryArrayElementType GetUVSetArrayFormat	(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = nullptr)	{ return mFBModelVertexData->GetUVSetArrayFormat(pTextureMapping, pUVSet); }
    int GetUVSetUVCount								(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = nullptr)	{ return mFBModelVertexData->GetUVSetUVCount(pTextureMapping, pUVSet); }
    list GetUVSetArray								(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = nullptr);
    unsigned int GetUVSetVBOId						(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = nullptr)	{ return mFBModelVertexData->GetUVSetVBOId(pTextureMapping, pUVSet); }
    kReference GetUVSetVBOOffset					(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = nullptr)	{ return (kReference)mFBModelVertexData->GetUVSetVBOOffset(pTextureMapping, pUVSet); }
};

#endif // pyfbmesh_h__
