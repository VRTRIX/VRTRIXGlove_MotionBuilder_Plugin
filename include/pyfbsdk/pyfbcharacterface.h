#ifndef pyfbcharacterface_h__
#define pyfbcharacterface_h__
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
#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbactorface.h"
#include "pyfbkeyinggroup.h"
#include "pyfbobjectposeoptions.h"
#include "pyfbobjectposemirroroptions.h"
#include "pyfbobjectpose.h"
#include "pyfbcharacterextension.h"
#include "pyfbcharactersolver.h"
#include "pyfbcharacter.h"

// =======================================================================================
// FBCharacterFace
// =======================================================================================
void FBCharacterFace_Init();

class PYSDK_DLL FBCharacterFace_Wrapper : public FBConstraint_Wrapper {
public:
	FBCharacterFace* mFBCharacterFace;
public:
	FBCharacterFace_Wrapper( FBComponent* pFBComponent ) : FBConstraint_Wrapper( pFBComponent ) { mFBCharacterFace = (FBCharacterFace*)pFBComponent; }
	FBCharacterFace_Wrapper( const char* pName ) : FBConstraint_Wrapper( new FBCharacterFace( pName )) { mFBCharacterFace = (FBCharacterFace*)mFBComponent; }
	virtual ~FBCharacterFace_Wrapper( ) {}
	void FBDelete() { mFBCharacterFace->FBDelete(  ); }
	bool PlotAnimation() { return mFBCharacterFace->PlotAnimation(  ); }

	void GotoRest() { mFBCharacterFace->GotoRest(); }

	bool ShapeGroupAdd( FBModelList_Wrapper* pList, const char* pName = NULL ) { return mFBCharacterFace->ShapeGroupAdd( pList->mFBModelList, pName ); }
	bool ShapeGroupRemove( int pShapeGrpId ) { return mFBCharacterFace->ShapeGroupRemove( pShapeGrpId ); }
	int ShapeGroupFindByName( const char* pName ) { return mFBCharacterFace->ShapeGroupFindByName( pName ); }
	int ShapeGroupGetCount() { return mFBCharacterFace->ShapeGroupGetCount(); }
	const char* ShapeGroupGetName( int pShapeGrpId ) { return mFBCharacterFace->ShapeGroupGetName( pShapeGrpId ); }
	bool ShapeGroupSetName( int pShapeGrpId, const char* pName ) { return mFBCharacterFace->ShapeGroupSetName( pShapeGrpId, pName ); }

	int ShapeFindByName( int pShapeGrpId, const char* pName ) { return mFBCharacterFace->ShapeFindByName( pShapeGrpId, pName ); }
	int ShapeGetCount( int pShapeGrpId ) { return mFBCharacterFace->ShapeGetCount( pShapeGrpId ); }
	const char* ShapeGetName( int pShapeGrpId, int pShapeId ) { return mFBCharacterFace->ShapeGetName( pShapeGrpId, pShapeId ); }
	bool ShapeSetName( int pShapeGrpId, int pShapeId, const char* pName ) { return mFBCharacterFace->ShapeSetName( pShapeGrpId, pShapeId, pName ); }

	int ClusterGroupAdd( FBModelList_Wrapper* pList, const char* pName = NULL ) { return mFBCharacterFace->ClusterGroupAdd( pList->mFBModelList, pName ); }
	bool ClusterGroupRemove( int pClusterGrpId ) { return mFBCharacterFace->ClusterGroupRemove( pClusterGrpId ); }
	int ClusterGroupFindByName( const char* pName ) { return mFBCharacterFace->ClusterGroupFindByName( pName ); }
	int ClusterGroupGetCount() { return mFBCharacterFace->ClusterGroupGetCount(); }
	const char* ClusterGroupGetName( int pClusterGrpId ) { return mFBCharacterFace->ClusterGroupGetName( pClusterGrpId ); }
	bool ClusterGroupSetName( int pClusterGrpId, const char* pName ) { return mFBCharacterFace->ClusterGroupSetName( pClusterGrpId, pName ); }
	bool ClusterGroupSnapRest( int pClusterGrpId ) { return mFBCharacterFace->ClusterGroupSnapRest( pClusterGrpId ); }

	int ClusterShapeAdd( int pClusterGrpId, const char* pName = NULL ) { return mFBCharacterFace->ClusterShapeAdd( pClusterGrpId, pName ); }
	bool ClusterShapeRemove( int pClusterGrpId, int pClusterShapeId ) { return mFBCharacterFace->ClusterShapeRemove( pClusterGrpId, pClusterShapeId ); }
	int ClusterShapeFindByName( int pClusterGrpId, const char* pName ) { return mFBCharacterFace->ClusterShapeFindByName( pClusterGrpId, pName ); }
	int ClusterShapeGetCount( int pClusterGrpId ) { return mFBCharacterFace->ClusterShapeGetCount( pClusterGrpId ); }
	const char* ClusterShapeGetName( int pClusterGrpId, int pClusterShapeId ) { return mFBCharacterFace->ClusterShapeGetName( pClusterGrpId, pClusterShapeId ); }
	bool ClusterShapeSetName( int pClusterGrpId, int pClusterShapeId, const char* pName ) { return mFBCharacterFace->ClusterShapeSetName( pClusterGrpId, pClusterShapeId, pName ); }
	bool ClusterShapeSnap( int pClusterGrpId, int pClusterShapeId ) { return mFBCharacterFace->ClusterShapeSnap( pClusterGrpId, pClusterShapeId ); }

	int ExpressionAdd( const char* pName ) { return mFBCharacterFace->ExpressionAdd( pName ); }
	bool ExpressionRemove( int pExpressionId ) { return mFBCharacterFace->ExpressionRemove( pExpressionId ); }
	int ExpressionFindByName( const char* pName ) { return mFBCharacterFace->ExpressionFindByName( pName ); }
	int ExpressionGetCount() { return mFBCharacterFace->ExpressionGetCount(); }
	const char* ExpressionGetName( int pExpressionId ) { return mFBCharacterFace->ExpressionGetName( pExpressionId ); }
	bool ExpressionSetName( int pExpressionId, const char* pName ) { return mFBCharacterFace->ExpressionSetName( pExpressionId, pName ); }
	bool ExpressionSetShapeWeight( int pExpressionId, int pGrpId, int pShapeId, float pValue = 0.0f ) { return mFBCharacterFace->ExpressionSetShapeWeight( pExpressionId, pGrpId, pShapeId, pValue ); }

	void SetActiveInput( bool pActiveInput ) { mFBCharacterFace->ActiveInput = pActiveInput; }
	bool GetActiveInput(  ) { return mFBCharacterFace->ActiveInput; }
	void SetInputActorFace( FBActorFace_Wrapper& pInputActorFace ) { mFBCharacterFace->InputActorFace = pInputActorFace.mFBActorFace; }
	object GetInputActorFace(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacterFace->InputActorFace ); }
};
#endif // pyfbcharacterface_h__