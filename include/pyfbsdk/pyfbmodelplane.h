#ifndef pyfbmodelplane_h__
#define pyfbmodelplane_h__
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
#include "pyfbboxplaceholder.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbmodelplaceholder.h"
#include "pyfbmodeltemplate.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelnull.h"

// =======================================================================================
// FBModelPlane
// =======================================================================================
void FBModelPlane_Init();

class PYSDK_DLL FBModelPlane_Wrapper : public FBModel_Wrapper {
public:
	FBModelPlane* mFBModelPlane;
public:
	FBModelPlane_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBModelPlane = (FBModelPlane*)pFBComponent; }
	FBModelPlane_Wrapper( const char* pName ) : FBModel_Wrapper( new FBModelPlane( pName )) { mFBModelPlane = (FBModelPlane*)mFBComponent; }
	virtual ~FBModelPlane_Wrapper( ) {}
};
#endif // pyfbmodelplane_h__