#ifndef pyfbobjectposemirroroptions_h__
#define pyfbobjectposemirroroptions_h__
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
// FBObjectPoseMirrorOptions
// =======================================================================================
void FBObjectPoseMirrorOptions_Init();

class PYSDK_DLL FBObjectPoseMirrorOptions_Wrapper {
public:
	FBObjectPoseMirrorOptions* mFBObjectPoseMirrorOptions;
public:
	FBObjectPoseMirrorOptions_Wrapper( const FBObjectPoseMirrorOptions& pFBObjectPoseMirrorOptions ) { mFBObjectPoseMirrorOptions = new FBObjectPoseMirrorOptions( pFBObjectPoseMirrorOptions ); }	
    FBObjectPoseMirrorOptions_Wrapper() { mFBObjectPoseMirrorOptions = new FBObjectPoseMirrorOptions(); }
	virtual ~FBObjectPoseMirrorOptions_Wrapper( ) { delete mFBObjectPoseMirrorOptions; }
	void ClearFlag() { mFBObjectPoseMirrorOptions->ClearFlag(  ); }
	bool GetFlag(FBObjectPoseMirrorOptionsFlag pFlag) { return mFBObjectPoseMirrorOptions->GetFlag( pFlag ); }
	void SetFlag(FBObjectPoseMirrorOptionsFlag pFlag, bool pValue) { mFBObjectPoseMirrorOptions->SetFlag( pFlag, pValue ); }
	void SetMirrorPlaneEquation( FBVector4d_Wrapper& pMirrorPlaneEquation ) { mFBObjectPoseMirrorOptions->mMirrorPlaneEquation = *pMirrorPlaneEquation.mFBVector4d; }
	FBVector4d_Wrapper* GetMirrorPlaneEquation(  ) { return FBVector4d_Wrapper_Factory( mFBObjectPoseMirrorOptions->mMirrorPlaneEquation ); }
};
#endif // pyfbobjectposemirroroptions_h__