#ifndef pyfbpose_h__
#define pyfbpose_h__
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
// FBPose
// =======================================================================================
void FBPose_Init();

class PYSDK_DLL FBPose_Wrapper : public FBComponent_Wrapper {
public:
	FBPose* mFBPose;
public:
	FBPose_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBPose = (FBPose*)pFBComponent; }
	FBPose_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBPose( pName )) { mFBPose = (FBPose*)mFBComponent; }
	virtual ~FBPose_Wrapper( ) {}
    int AddNode(FBModel_Wrapper& pObject, FBMatrix_Wrapper* pMatrix = NULL, bool pIsLocalMatrix = false) { return mFBPose->AddNode( pObject.mFBModel, pMatrix ? pMatrix->mFBMatrix : NULL , pIsLocalMatrix ); }
	int Find(const char* pNodeName) { return mFBPose->Find( pNodeName ); }
	int GetNodeCount() { return mFBPose->GetNodeCount(  ); }
	FBMatrix_Wrapper* GetNodeMatrix(int pIndex) 
    {         
        return FBMatrix_Wrapper_Factory( mFBPose->GetNodeMatrix( pIndex )); 
    }
	const char* GetNodeName(int pIndex) { return mFBPose->GetNodeName( pIndex ); }
	object GetNodeObject(int pIndex) { return FBModel_Wrapper_Factory( mFBPose->GetNodeObject( pIndex )); }
	bool IsNodeLocalMatrix(int pIndex) { return mFBPose->IsNodeLocalMatrix( pIndex ); }
	void RemoveNode(int pIndex) { mFBPose->RemoveNode( pIndex ); }
	void SetIsNodeLocalMatrix(int pIndex, bool pIsNodeLocalMatrix) { mFBPose->SetIsNodeLocalMatrix( pIndex, pIsNodeLocalMatrix ); }
	void SetNodeMatrix(int pIndex, FBMatrix_Wrapper& pMatrix) { mFBPose->SetNodeMatrix( pIndex, pMatrix.mFBMatrix ); }
	void SetNodeObject(int pIndex, FBModel_Wrapper& pObject) { mFBPose->SetNodeObject( pIndex, pObject.mFBModel ); }
	FBPoseType GetType(  ) { return mFBPose->Type; }
	void CreatePoseThumbnail() { mFBPose->CreatePoseThumbnail(); }
};
#endif // pyfbpose_h__