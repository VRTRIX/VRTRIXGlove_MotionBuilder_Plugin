/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file fbxnodefinder.h
#ifndef _FBXSDK_UTILS_NODE_FINDER_H_
#define _FBXSDK_UTILS_NODE_FINDER_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxarray.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxNode;

//! Class FbxNodeFinder
class FBXSDK_DLL FbxNodeFinder
{

public:
	//! Constructor.
	FbxNodeFinder();

	//! Destructor.
	virtual ~FbxNodeFinder();

	/** Find all the node corresponding to the search criterion.
	*	\param iSearchRoot
	*	\return
	*/
	FbxArray<FbxNode*>& Apply(FbxNode& iSearchRoot);

	//! Reset the finder object
	virtual void Reset() = 0;

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
	virtual bool CheckNode(FbxNode& iNode) = 0;

	//
	// data members
	//

	// Can be useful to some search algo...
	FbxNode* mSearchRoot;

	// Array holding found nodes.
	FbxArray<FbxNode*> mNodeArray;
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_UTILS_NODE_FINDER_H_ */
