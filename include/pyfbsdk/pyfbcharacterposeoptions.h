#ifndef pyfbcharacterposeoptions_h__
#define pyfbcharacterposeoptions_h__
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
#include "pyfbplotoptions.h"
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbpose.h"
#include "pyfbconstraint.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"
#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbactorface.h"
#include "pyfbkeyinggroup.h"
#include "pyfbobjectposeoptions.h"
#include "pyfbobjectposemirroroptions.h"
#include "pyfbobjectpose.h"
#include "pyfbcharacterextension.h"
#include "pyfbcharactersolver.h"
#include "pyfbcharacter.h"
#include "pyfbcharacterface.h"			// Requires FBModelList_Wrapper from pyfbarraytemplate.h

// =======================================================================================
// FBCharacterPoseOptions
// =======================================================================================
void FBCharacterPoseOptions_Init();

class PYSDK_DLL FBCharacterPoseOptions_Wrapper {
public:
	FBCharacterPoseOptions* mFBCharacterPoseOptions;
public:	
	FBCharacterPoseOptions_Wrapper(  ) { mFBCharacterPoseOptions = new FBCharacterPoseOptions; }
	virtual ~FBCharacterPoseOptions_Wrapper( ) { delete mFBCharacterPoseOptions; }
	void ClearFlag() { mFBCharacterPoseOptions->ClearFlag(  ); }
	bool GetFlag(FBCharacterPoseFlag pFlag) { return mFBCharacterPoseOptions->GetFlag( pFlag ); }
	void SetFlag(FBCharacterPoseFlag pFlag, bool pValue) { mFBCharacterPoseOptions->SetFlag( pFlag, pValue ); }
	void SetCharacterPoseKeyingMode( FBCharacterPoseKeyingMode pmCharacterPoseKeyingMode ) { mFBCharacterPoseOptions->mCharacterPoseKeyingMode = pmCharacterPoseKeyingMode; }
	FBCharacterPoseKeyingMode GetCharacterPoseKeyingMode(  ) { return mFBCharacterPoseOptions->mCharacterPoseKeyingMode; }
	void SetMirrorPlaneEquation( FBVector4d_Wrapper& pMirrorPlaneEquation ) { mFBCharacterPoseOptions->mMirrorPlaneEquation = *pMirrorPlaneEquation.mFBVector4d; }
	FBVector4d_Wrapper* GetMirrorPlaneEquation(  ) { return FBVector4d_Wrapper_Factory( mFBCharacterPoseOptions->mMirrorPlaneEquation ); }
	void SetMirrorPlanePanAngle( double pmMirrorPlanePanAngle ) { mFBCharacterPoseOptions->mMirrorPlanePanAngle = pmMirrorPlanePanAngle; }
	double GetMirrorPlanePanAngle(  ) { return mFBCharacterPoseOptions->mMirrorPlanePanAngle; }
	void SetMirrorPlaneTiltAngle( double pmMirrorPlaneTiltAngle ) { mFBCharacterPoseOptions->mMirrorPlaneTiltAngle = pmMirrorPlaneTiltAngle; }
	double GetMirrorPlaneTiltAngle(  ) { return mFBCharacterPoseOptions->mMirrorPlaneTiltAngle; }
	void SetMirrorPlaneType( FBMirrorPlaneType pmMirrorPlaneType ) { mFBCharacterPoseOptions->mMirrorPlaneType = pmMirrorPlaneType; }
	FBMirrorPlaneType GetMirrorPlaneType(  ) { return mFBCharacterPoseOptions->mMirrorPlaneType; }
	void SetModelToMatch( FBModel_Wrapper& pmModelToMatch ) { mFBCharacterPoseOptions->mModelToMatch = pmModelToMatch.mFBModel; }
	object GetModelToMatch(  ) { return FBModel_Wrapper_Factory( mFBCharacterPoseOptions->mModelToMatch ); }
};
#endif // pyfbcharacterposeoptions_h__