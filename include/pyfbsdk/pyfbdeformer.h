#ifndef pyfbdeformer_h__
#define pyfbdeformer_h__
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
// FBPopup
// =======================================================================================
void FBDeformer_Init();

class PYSDK_DLL FBDeformer_Wrapper : public FBComponent_Wrapper {
public:
	FBDeformer* mFBDeformer;
public:
	FBDeformer_Wrapper( FBComponent* pFBComponent );
	FBDeformer_Wrapper( const char* pName );
	virtual ~FBDeformer_Wrapper( );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(DeformerType, FBDeformerType);
};
#endif // pyfbdeformer_h__