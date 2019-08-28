#ifndef pyfbconstraintsolver_h__
#define pyfbconstraintsolver_h__
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
// FBConstraintSolver
// =======================================================================================
void FBConstraintSolver_Init();

class PYSDK_DLL FBConstraintSolver_Wrapper : public FBConstraint_Wrapper {
public:
	FBConstraintSolver* mFBConstraintSolver;
public:
	FBConstraintSolver_Wrapper( FBComponent* pFBComponent ) : FBConstraint_Wrapper( pFBComponent ) { mFBConstraintSolver = (FBConstraintSolver*)pFBComponent; }
	FBConstraintSolver_Wrapper( const char* pName = NULL ) : FBConstraint_Wrapper( new FBConstraintSolver( pName )) { mFBConstraintSolver = (FBConstraintSolver*)mFBComponent; }
	virtual ~FBConstraintSolver_Wrapper( ) {}
};
#endif // pyfbconstraintsolver_h__