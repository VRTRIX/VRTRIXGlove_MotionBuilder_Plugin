#ifndef pyfbaudioin_h__
#define pyfbaudioin_h__
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

// =======================================================================================
// FBAudioIn
// =======================================================================================
void FBAudioIn_Init();

class FBAudioIn_Wrapper : public FBComponent_Wrapper {
public:
	FBAudioIn* mFBAudioIn;
public:
	FBAudioIn_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAudioIn = (FBAudioIn*)pFBComponent; }
	FBAudioIn_Wrapper(  ) : FBComponent_Wrapper( new FBAudioIn(  )) { mFBAudioIn = (FBAudioIn*)mFBComponent; SetAllocated(); }
	virtual ~FBAudioIn_Wrapper( ) {}
};
#endif // pyfbaudioin_h__