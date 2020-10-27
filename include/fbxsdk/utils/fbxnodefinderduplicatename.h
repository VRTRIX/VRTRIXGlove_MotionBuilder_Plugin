/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file fbxnodefinderduplicatename.h
#ifndef _FBXSDK_UTILS_NODE_FINDER_DUPLICATE_NAME_H_
#define _FBXSDK_UTILS_NODE_FINDER_DUPLICATE_NAME_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/utils/fbxnodefinder.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxScene;
class FbxGeometry;
class FbxSurfaceMaterial;
class FbxTexture;
class FbxVideo;
class FbxGenericNode;
class FbxLayerElementTexture;

//
//	CLASS FbxNodeFinderDuplicateName
//

//! FbxNodeFinderDuplicateName 
class FBXSDK_DLL FbxNodeFinderDuplicateName : public FbxNodeFinder
{
public:

	/** \enum EState
	  * - \e eCHECK_NODE_NAME
	  * - \e eCHECK_MATERIAL_NAME
	  * - \e eCHECK_TEXTURE_NAME
	  * - \e eCHECK_VIDEO_NAME
	  * - \e eCHECK_GENERIC_NODE_NAME
	  * - \e eSTATE_COUNT
	  */
	typedef enum 
	{
		eCHECK_NODE_NAME,
		eCHECK_MATERIAL_NAME,
		eCHECK_TEXTURE_NAME,
		eCHECK_VIDEO_NAME,
		eCHECK_GENERIC_NODE_NAME,
		eSTATE_COUNT
	} EState;

	/** Constructor. 
	 *  When the destination scene is specified, duplicates are searched in both the destination scene and in the processed node tree.
	 *  \param pDestinationScene     Destination scene to search. \c NULL by default.
	 */
	FbxNodeFinderDuplicateName(FbxScene* pDestinationScene = NULL);

	//! Destructor.
	virtual ~FbxNodeFinderDuplicateName();

	//! Reset the finder object
	virtual void Reset();

	/** GetState.
	*	\param pStateIndex     State index.
	*	\return                State of pStateIndex.
	*/
	bool GetState(int pStateIndex) const;

	/** SetState.
	*	\param pStateIndex     State index.
	*	\param pValue          
	*/
	void SetState(int pStateIndex, bool pValue);

	/** GetNodeArray.
	*	\return
	*/
	FbxArray<FbxNode*>& GetNodeArray();

	/** GetNodeArray.
	*	\return
	*/
	FbxArray<FbxNode*>& GetDuplicateNodeArray();

	/** GetMaterialArray.
	*	\return
	*/
	FbxArray<FbxSurfaceMaterial*>& GetMaterialArray();

	/** GetMaterialArray.
	*	\return
	*/
	FbxArray<FbxSurfaceMaterial*>& GetDuplicateMaterialArray();

	/** GetTextureArray.
	*	\return
	*/
	FbxArray<FbxTexture*>& GetTextureArray();

	/** GetTextureArray.
	*	\return
	*/
	FbxArray<FbxTexture*>& GetDuplicateTextureArray();

	/** GetVideoArray.
	*	\return
	*/
	FbxArray<FbxVideo*>& GetVideoArray();

	/** GetVideoArray.
	*	\return
	*/
	FbxArray<FbxVideo*>& GetDuplicateVideoArray();


	FbxArray<FbxGenericNode*>& GetGenericNodeArray();

	FbxArray<FbxGenericNode*>& GetDuplicateGenericNodeArray();


protected:

	/** Find all the node corresponding to the search criterion.
	*	\param iNode
	*/
	virtual void ApplyRecursive(FbxNode& iNode);
	
	/** Check if a node answers to search criterion.
	*	Criteria must be defined by child class.
	*	\param iNode
	*	\return
	*/
	virtual bool CheckNode(FbxNode& iNode);

	/** Check for duplicate node name.
	*	\param pNode
	*	\return True if there is a duplicate node name, false otherwise.
	*/
	bool CheckNodeName(FbxNode& pNode);

	/** Check for duplicate material name.
	*	\param pGeometry
	*   \param pNode
	*	\return True if there is a duplicate material name, false otherwise.
	*/
	bool CheckMaterialName(FbxGeometry* pGeometry, FbxNode* pNode);

	/** Check for duplicate texture name.
	*	\param pGeometry
	*	\return True if there is a duplicate texture name, false otherwise.
	*/
	bool CheckTextureName(FbxGeometry* pGeometry);
	bool CheckLayerElementTextureName(FbxLayerElementTexture* pLayerElementTexture);

	/** Check for duplicate video name.
	*	\param pGeometry
	*	\return True if there is a duplicate video name, false otherwise.
	*/
	bool CheckVideoName(FbxGeometry* pGeometry);
	bool CheckLayerElementVideoName(FbxLayerElementTexture* pLayerElementTexture);

	bool CheckGenericNodeName(char* pNodeName);

	bool mStates [eSTATE_COUNT];

	FbxArray <FbxNode*> mENodeArray;
	FbxArray <FbxNode*> mDuplicateNodeArray;
	FbxArray <FbxSurfaceMaterial*> mMaterialArray;
	FbxArray <FbxSurfaceMaterial*> mDuplicateMaterialArray;
    FbxArray <FbxTexture*> mTextureArray;
	FbxArray <FbxTexture*> mDuplicateTextureArray;
    FbxArray <FbxVideo*> mVideoArray;
	FbxArray <FbxVideo*> mDuplicateVideoArray;
	FbxArray <FbxGenericNode*> mGenericNodeArray;
	FbxArray <FbxGenericNode*> mDuplicateGenericNodeArray;

	#ifdef _MULTIENTITY
		FbxScene* mSourceScene;
	#endif // #ifdef _MULTIENTITY
	FbxScene* mDestinationScene;
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_UTILS_NODE_FINDER_DUPLICATE_NAME_H_ */
