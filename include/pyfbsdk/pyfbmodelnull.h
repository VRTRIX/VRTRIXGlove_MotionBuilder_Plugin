#ifndef pyfbmodelnull_h__
#define pyfbmodelnull_h__
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

// =======================================================================================
// FBModelNull
// =======================================================================================
void FBModelNull_Init();

class PYSDK_DLL FBModelNull_Wrapper : public FBModel_Wrapper {
public:
	FBModelNull* mFBModelNull;
public:
	FBModelNull_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBModelNull = (FBModelNull*)pFBComponent; }
	FBModelNull_Wrapper( const char* pName ) : FBModel_Wrapper( new FBModelNull( pName )) { mFBModelNull = (FBModelNull*)mFBComponent; }
	virtual ~FBModelNull_Wrapper( ) {}
	void SetSize( double pSize ) { mFBModelNull->Size = pSize; }
	double GetSize(  ) { return mFBModelNull->Size; }
};
#endif // pyfbmodelnull_h__