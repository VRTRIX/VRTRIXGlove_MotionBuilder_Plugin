#ifndef pyfbmodelroot_h__
#define pyfbmodelroot_h__
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
#include "pyfbmodelplane.h"

// =======================================================================================
// FBModelRoot
// =======================================================================================
void FBModelRoot_Init();

class PYSDK_DLL FBModelRoot_Wrapper : public FBModel_Wrapper {
public:
	FBModelRoot* mFBModelRoot;
public:
	FBModelRoot_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBModelRoot = (FBModelRoot*)pFBComponent; }
	FBModelRoot_Wrapper( const char* pName ) : FBModel_Wrapper( new FBModelRoot( pName )) { mFBModelRoot = (FBModelRoot*)mFBComponent; }
	virtual ~FBModelRoot_Wrapper( ) {}
	void SetSize( double pSize ) { mFBModelRoot->Size = pSize; }
	double GetSize(  ) { return mFBModelRoot->Size; }
};
#endif // pyfbmodelroot_h__
