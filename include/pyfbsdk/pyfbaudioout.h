#ifndef pyfbaudioout_h__
#define pyfbaudioout_h__
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
// FBAudioOut
// =======================================================================================
void FBAudioOut_Init();

class PYSDK_DLL FBAudioOut_Wrapper : public FBComponent_Wrapper {
public:
	FBAudioOut* mFBAudioOut;
public:
	FBAudioOut_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAudioOut = (FBAudioOut*)pFBComponent; }
	FBAudioOut_Wrapper(  ) : FBComponent_Wrapper( new FBAudioOut(  )) { mFBAudioOut = (FBAudioOut*)mFBComponent; SetAllocated(); }
	virtual ~FBAudioOut_Wrapper( ) {}
};
#endif // pyfbaudioout_h__
