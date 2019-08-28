#ifndef pyfbconstraintrelation_h__
#define pyfbconstraintrelation_h__
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
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbconstraint.h"

// =======================================================================================
// FBConstraintRelation
// =======================================================================================
void FBConstraintRelation_Init();

class PYSDK_DLL FBConstraintRelation_Wrapper : public FBConstraint_Wrapper {
public:
	FBConstraintRelation* mFBConstraintRelation;
public:
	FBConstraintRelation_Wrapper( FBComponent* pFBComponent ) : FBConstraint_Wrapper( pFBComponent ) { mFBConstraintRelation = (FBConstraintRelation*)pFBComponent; }
	FBConstraintRelation_Wrapper( const char* pName = NULL ) : FBConstraint_Wrapper( new FBConstraintRelation( pName )) { mFBConstraintRelation = (FBConstraintRelation*)mFBComponent; }
	virtual ~FBConstraintRelation_Wrapper( ) {}
	object ConstrainObject(FBBox_Wrapper& pConstrainedObject) { return FBWrapperFactory::TheOne().WrapFBObject( mFBConstraintRelation->ConstrainObject( pConstrainedObject.mFBBox )); }
	object CreateFunctionBox(const char * pGroup, const char * pName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBConstraintRelation->CreateFunctionBox( pGroup, pName )); }
	tuple GetBoxPosition(FBBox_Wrapper& pBox)
    {
        int lX = 0;
        int lY = 0;
        bool lResult = mFBConstraintRelation->GetBoxPosition( pBox.mFBBox, lX, lY );
        return make_tuple( lResult, lX, lY );
    }
	object SetAsSource(FBBox_Wrapper& pSource) { return FBWrapperFactory::TheOne().WrapFBObject( mFBConstraintRelation->SetAsSource( pSource.mFBBox )); }
	bool SetBoxPosition(FBBox_Wrapper& pBox, int pX, int pY) { return mFBConstraintRelation->SetBoxPosition( pBox.mFBBox, pX, pY ); }
	object GetBoxes(  ) { return FBPropertyListBox_Wrapper_Factory( mFBConstraintRelation->Boxes ); }
};
#endif // pyfbconstraintrelation_h__
