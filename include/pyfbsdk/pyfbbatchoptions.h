#ifndef pyfbbatchoptions_h__
#define pyfbbatchoptions_h__
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
#include "pyfbconstraint.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"
#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbkeyinggroup.h"
#include "pyfbcharacterextension.h"
#include "pyfbcharactersolver.h"
#include "pyfbcharacter.h"

// =======================================================================================
// FBBatchOptions
// =======================================================================================
void FBBatchOptions_Init();

class PYSDK_DLL FBBatchOptions_Wrapper {
public:
	FBBatchOptions* mFBBatchOptions;
public:
    FBBatchOptions_Wrapper(  ) : mFBBatchOptions( new FBBatchOptions ) {}
    virtual ~FBBatchOptions_Wrapper( ) { delete mFBBatchOptions; }
	void SetCharacter( FBCharacter_Wrapper& pCharacter ) { mFBBatchOptions->mCharacter = pCharacter.mFBCharacter; }
	object GetCharacter(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBBatchOptions->mCharacter ); }
	void SetFrameAnimation( bool pFrameAnimation ) { mFBBatchOptions->mFrameAnimation = pFrameAnimation; }
	bool GetFrameAnimation(  ) { return mFBBatchOptions->mFrameAnimation; }
	void SetInputDirectory( const char* pInputDirectory ) { mFBBatchOptions->mInputDirectory = pInputDirectory; }
	const char* GetInputDirectory(  ) { return mFBBatchOptions->mInputDirectory; }
	void SetInputFileFormat( FBBatchFileFormat pInputFileFormat ) { mFBBatchOptions->mInputFileFormat = pInputFileFormat; }
	FBBatchFileFormat GetInputFileFormat(  ) { return mFBBatchOptions->mInputFileFormat; }
	void SetKeepCharacterConstraint( bool pKeepCharacterConstraint ) { mFBBatchOptions->mKeepCharacterConstraint = pKeepCharacterConstraint; }
	bool GetKeepCharacterConstraint(  ) { return mFBBatchOptions->mKeepCharacterConstraint; }
	void SetKeepDummyBones( bool pKeepDummyBones ) { mFBBatchOptions->mKeepDummyBones = pKeepDummyBones; }
	bool GetKeepDummyBones(  ) { return mFBBatchOptions->mKeepDummyBones; }
	void SetOnContainsBatchTakesAction( FBBatchOnContainsBatchTakes pOnContainsBatchTakesAction ) { mFBBatchOptions->mOnContainsBatchTakesAction = pOnContainsBatchTakesAction; }
	FBBatchOnContainsBatchTakes GetOnContainsBatchTakesAction(  ) { return mFBBatchOptions->mOnContainsBatchTakesAction; }
	void SetOnTakeExistAction( FBBatchOnTakeExist pOnTakeExistAction ) { mFBBatchOptions->mOnTakeExistAction = pOnTakeExistAction; }
	FBBatchOnTakeExist GetOnTakeExistAction(  ) { return mFBBatchOptions->mOnTakeExistAction; }
	void SetOutputDirectory( const char* pOutputDirectory ) { mFBBatchOptions->mOutputDirectory = pOutputDirectory; }
	const char* GetOutputDirectory(  ) { return mFBBatchOptions->mOutputDirectory; }
	void SetOutputFileFormat( FBBatchFileFormat pOutputFileFormat ) { mFBBatchOptions->mOutputFileFormat = pOutputFileFormat; }
	FBBatchFileFormat GetOutputFileFormat(  ) { return mFBBatchOptions->mOutputFileFormat; }
	void SetOverwriteScaling( bool pOverwriteScaling ) { mFBBatchOptions->mOverwriteScaling = pOverwriteScaling; }
	bool GetOverwriteScaling(  ) { return mFBBatchOptions->mOverwriteScaling; }
	void SetPlotToCharacter( bool pPlotToCharacter ) { mFBBatchOptions->mPlotToCharacter = pPlotToCharacter; }
	bool GetPlotToCharacter(  ) { return mFBBatchOptions->mPlotToCharacter; }
	void SetPlotToControlSet( bool pPlotToControlSet ) { mFBBatchOptions->mPlotToControlSet = pPlotToControlSet; }
	bool GetPlotToControlSet(  ) { return mFBBatchOptions->mPlotToControlSet; }
	void SetProcessType( FBBatchProcessType pProcessType ) { mFBBatchOptions->mProcessType = pProcessType; }
	FBBatchProcessType GetProcessType(  ) { return mFBBatchOptions->mProcessType; }
	void SetSkeletonFile( const char* pSkeletonFile ) { mFBBatchOptions->mSkeletonFile = pSkeletonFile; }
	const char* GetSkeletonFile(  ) { return mFBBatchOptions->mSkeletonFile; }
	void SetStartAnimationAtZero( bool pStartAnimationAtZero ) { mFBBatchOptions->mStartAnimationAtZero = pStartAnimationAtZero; }
	bool GetStartAnimationAtZero(  ) { return mFBBatchOptions->mStartAnimationAtZero; }
	void SetUseBatchSuffix( bool pUseBatchSuffix ) { mFBBatchOptions->mUseBatchSuffix = pUseBatchSuffix; }
	bool GetUseBatchSuffix(  ) { return mFBBatchOptions->mUseBatchSuffix; }
	void SetUseSingleTake( bool pUseSingleTake ) { mFBBatchOptions->mUseSingleTake = pUseSingleTake; }
	bool GetUseSingleTake(  ) { return mFBBatchOptions->mUseSingleTake; }
	void SetWriteRate( bool pWriteRate ) { mFBBatchOptions->mWriteRate = pWriteRate; }
	bool GetWriteRate(  ) { return mFBBatchOptions->mWriteRate; }
	void SetWriteTranslation( bool pWriteTranslation ) { mFBBatchOptions->mWriteTranslation = pWriteTranslation; }
	bool GetWriteTranslation(  ) { return mFBBatchOptions->mWriteTranslation; }
};
#endif // pyfbbatchoptions_h__

