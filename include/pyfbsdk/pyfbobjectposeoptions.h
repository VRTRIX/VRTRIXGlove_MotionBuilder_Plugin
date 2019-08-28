#ifndef pyfbobjectposeoptions_h__
#define pyfbobjectposeoptions_h__
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

// =======================================================================================
// FBObjectPoseOptions
// =======================================================================================
void FBObjectPoseOptions_Init();

class PYSDK_DLL FBObjectPoseOptions_Wrapper {
public:
	FBObjectPoseOptions* mFBObjectPoseOptions;
public:
	FBObjectPoseOptions_Wrapper( const FBObjectPoseOptions& pFBObjectPoseOptions ) { mFBObjectPoseOptions = new FBObjectPoseOptions( pFBObjectPoseOptions ); }	
    FBObjectPoseOptions_Wrapper() { mFBObjectPoseOptions = new FBObjectPoseOptions(); }	
	virtual ~FBObjectPoseOptions_Wrapper( ) { delete mFBObjectPoseOptions; }
	void ClearFlag() { mFBObjectPoseOptions->ClearFlag(  ); }
	bool GetFlag(FBObjectPoseOptionsFlag pFlag) { return mFBObjectPoseOptions->GetFlag( pFlag ); }
	void SetFlag(FBObjectPoseOptionsFlag pFlag, bool pValue) { mFBObjectPoseOptions->SetFlag( pFlag, pValue ); }
	void SetmPoseTransformType( FBPoseTransformType pmPoseTransformType ) { mFBObjectPoseOptions->mPoseTransformType = pmPoseTransformType; }
	FBPoseTransformType GetmPoseTransformType(  ) { return mFBObjectPoseOptions->mPoseTransformType; }
	void SetmReferenceGRM( FBMatrix_Wrapper& pmReferenceGRM ) { mFBObjectPoseOptions->mReferenceGRM = *pmReferenceGRM.mFBMatrix; }
	FBMatrix_Wrapper* GetmReferenceGRM(  ) { return FBMatrix_Wrapper_Factory( mFBObjectPoseOptions->mReferenceGRM ); }
	void SetmReferenceGSM( FBMatrix_Wrapper& pmReferenceGSM ) { mFBObjectPoseOptions->mReferenceGSM = *pmReferenceGSM.mFBMatrix; }
	FBMatrix_Wrapper* GetmReferenceGSM(  ) { return FBMatrix_Wrapper_Factory( mFBObjectPoseOptions->mReferenceGSM ); }
	void SetmReferenceGT( FBVector4d_Wrapper& pmReferenceGT ) { mFBObjectPoseOptions->mReferenceGT = *pmReferenceGT.mFBVector4d; }
	FBVector4d_Wrapper* GetmReferenceGT(  ) { return FBVector4d_Wrapper_Factory( mFBObjectPoseOptions->mReferenceGT ); }
};
#endif // pyfbobjectposeoptions_h__