#ifndef pyfbskeletonstate_h__
#define pyfbskeletonstate_h__
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

// =======================================================================================
// FBSkeletonState
// =======================================================================================
void FBSkeletonState_Init();

class PYSDK_DLL FBSkeletonState_Wrapper {
public:
	FBSkeletonState* mFBSkeletonState;
public:
    FBSkeletonState_Wrapper(FBSkeletonState* pFBSkeletonState) : mFBSkeletonState(pFBSkeletonState) {}
    virtual ~FBSkeletonState_Wrapper( ) {}
	void GetNodeMatrix(FBSkeletonNodeId pSkeletonId, FBMatrix_Wrapper &pSkeletonGlobalMatrix) { mFBSkeletonState->GetNodeMatrix(pSkeletonId, *pSkeletonGlobalMatrix.mFBMatrix); }
};

PYSDK_DLL inline FBSkeletonState_Wrapper* FBSkeletonState_Wrapper_Factory( FBSkeletonState* pFBSkeletonState )
{
	return new FBSkeletonState_Wrapper( pFBSkeletonState );
}

#endif // pyfbskeletonstate_h__