#ifndef pyfbboxplaceholder_h__
#define pyfbboxplaceholder_h__
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

#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"

// =======================================================================================
// FBBoxPlaceHolder
// =======================================================================================
void FBBoxPlaceHolder_Init();

class PYSDK_DLL FBBoxPlaceHolder_Wrapper : public FBBox_Wrapper {
public:
	FBBoxPlaceHolder* mFBBoxPlaceHolder;
public:
	FBBoxPlaceHolder_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBBoxPlaceHolder = (FBBoxPlaceHolder*)pFBComponent; }
	virtual ~FBBoxPlaceHolder_Wrapper( ) {}
    object GetBox(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBBoxPlaceHolder->Box ); }
};
#endif // pyfbboxplaceholder_h__