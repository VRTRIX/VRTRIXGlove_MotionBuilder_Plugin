#ifndef pyfbmodelopticaladvanced_h__
#define pyfbmodelopticaladvanced_h__
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
#include "pyfbtake.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbmodeloptical.h"

// =======================================================================================
// FBModelOpticalAdvanced
// =======================================================================================
void FBModelOpticalAdvanced_Init();

class PYSDK_DLL FBModelOpticalAdvanced_Wrapper : public FBComponent_Wrapper {
public:
	FBModelOpticalAdvanced* mFBModelOpticalAdvanced;
public:
	FBModelOpticalAdvanced_Wrapper( FBComponent* pFBComponent );
	FBModelOpticalAdvanced_Wrapper( FBModelOptical_Wrapper& pModelOptical );
	virtual ~FBModelOpticalAdvanced_Wrapper( );

	void AcceptAllSegments() { mFBModelOpticalAdvanced->AcceptAllSegments(); }
	void AcceptSegment() { mFBModelOpticalAdvanced->AcceptSegment(); }
	void SkipSegment() { mFBModelOpticalAdvanced->SkipSegment(); }
	void AutomaticBuild() { mFBModelOpticalAdvanced->AutomaticBuild(); }
	void CropSegmentsAnimation() { mFBModelOpticalAdvanced->CropSegmentsAnimation(); }

	object GetQuality() { return	FBWrapperFactory::TheOne().WrapFBObject( mFBModelOpticalAdvanced->Quality ); }

	void SetUsedTake( FBTake_Wrapper& pCurrentTake ) { mFBModelOpticalAdvanced->UsedTake = pCurrentTake.mFBTake; }
	object GetUsedTake(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModelOpticalAdvanced->UsedTake ); }
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ShowRigidQuality,	bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(GenerationMode,	FBGenerationMode);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ControllerMode, FBControllerMode);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SegmentMode,	FBSegmentMode);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(InsertSegmentMode,	FBInsertSegmentMode);

	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PlayToNextSegment,	bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(AutoPlayToNextSegment,	bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(MaxMatchDistance, double);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Active,	bool);
};
#endif // pyfbmodelopticaladvanced_h__