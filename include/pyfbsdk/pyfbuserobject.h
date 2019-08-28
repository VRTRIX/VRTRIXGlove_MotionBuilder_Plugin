#ifndef pyfbuserobject_h__
#define pyfbuserobject_h__
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
// FBUserObject
// =======================================================================================
void FBUserObject_Init();

class PYSDK_DLL FBUserObject_Wrapper : public FBBox_Wrapper {
public:
	FBUserObject* mFBUserObject;
public:
	FBUserObject_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBUserObject = (FBUserObject*)pFBComponent; }
	FBUserObject_Wrapper( const char* pName ) : FBBox_Wrapper( new FBUserObject( pName )) { mFBUserObject = (FBUserObject*)mFBComponent; }
	virtual ~FBUserObject_Wrapper( ) {}
};
#endif // pyfbuserobject_h__