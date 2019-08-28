#ifndef pyfbmodelplaceholder_h__
#define pyfbmodelplaceholder_h__
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

// =======================================================================================
// FBModelPlaceHolder
// =======================================================================================
void FBModelPlaceHolder_Init();

class PYSDK_DLL FBModelPlaceHolder_Wrapper : public FBBoxPlaceHolder_Wrapper {
public:
	FBModelPlaceHolder* mFBModelPlaceHolder;
public:
	FBModelPlaceHolder_Wrapper( FBComponent* pFBComponent ) : FBBoxPlaceHolder_Wrapper( pFBComponent ) { mFBModelPlaceHolder = (FBModelPlaceHolder*)pFBComponent; }
	virtual ~FBModelPlaceHolder_Wrapper( ) {}
	object GetModel(  ) { return FBModel_Wrapper_Factory( mFBModelPlaceHolder->Model ); }
	void SetUseGlobalTransforms( bool pUseGlobalTransforms ) { mFBModelPlaceHolder->UseGlobalTransforms = pUseGlobalTransforms; }
	bool GetUseGlobalTransforms(  ) { return mFBModelPlaceHolder->UseGlobalTransforms; }
};
#endif // pyfbmodelplaceholder_h__