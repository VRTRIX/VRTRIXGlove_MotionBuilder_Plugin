#ifndef pyfbtreenode_h__
#define pyfbtreenode_h__
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
// FBTreeNode
// =======================================================================================
void FBTreeNode_Init();

class PYSDK_DLL FBTreeNode_Wrapper : public FBComponent_Wrapper {
public:
	FBTreeNode* mFBTreeNode;
public:
	FBTreeNode_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBTreeNode = (FBTreeNode*)pFBComponent; }
	virtual ~FBTreeNode_Wrapper( ) { }
    void SetReference( kReference pReference ) { mFBTreeNode->Reference = pReference; }
	kReference GetReference(  ) { return mFBTreeNode->Reference; }
	void SetChecked( bool pChecked ) { mFBTreeNode->Checked = pChecked; }
	bool GetChecked(  ) { return mFBTreeNode->Checked; }
};
#endif // pyfbtreenode_h__