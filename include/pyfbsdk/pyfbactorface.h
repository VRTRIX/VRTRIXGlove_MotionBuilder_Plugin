#ifndef pyfbactorface_h__
#define pyfbactorface_h__
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

// =======================================================================================
// FBActorFace
// =======================================================================================
void FBActorFace_Init();

class PYSDK_DLL FBActorFace_Wrapper : public FBComponent_Wrapper {
public:
	FBActorFace* mFBActorFace;
public:
	FBActorFace_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBActorFace = (FBActorFace*)pFBComponent; }
	FBActorFace_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBActorFace( pName )) { mFBActorFace = (FBActorFace*)mFBComponent; }
	virtual ~FBActorFace_Wrapper( ) {}
	void FBDelete() { mFBActorFace->FBDelete(  ); }
	bool PlotAnimation() { return mFBActorFace->PlotAnimation(  ); }
};
#endif // pyfbactorface_h__
