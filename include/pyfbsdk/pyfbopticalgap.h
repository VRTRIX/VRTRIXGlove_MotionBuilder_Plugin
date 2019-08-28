#ifndef pyfbopticalgap_h__
#define pyfbopticalgap_h__
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
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbmodeloptical.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelmarkeroptical.h"

// =======================================================================================
// FBOpticalGap
// =======================================================================================
void FBOpticalGap_Init();
class FBModelMarkerOptical_Wrapper;
class PYSDK_DLL FBOpticalGap_Wrapper : public FBComponent_Wrapper {
public:
	FBOpticalGap* mFBOpticalGap;
public:
	FBOpticalGap_Wrapper( FBComponent* pFBComponent );
	FBOpticalGap_Wrapper( FBOpticalGap& pOpticalGap );
	FBOpticalGap_Wrapper( FBModelMarkerOptical_Wrapper& pModelMarkerOptical );
	virtual ~FBOpticalGap_Wrapper( );

	void InsertControlKey(FBTime_Wrapper& pTime) { mFBOpticalGap->InsertControlKey( *pTime.mFBTime ); }
	bool IsValid() { return mFBOpticalGap->IsValid(); }

	object GetData(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBOpticalGap->Data ); }
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(TimeSpan,	FBTimeSpan);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Interpolation,	FBGapMode);
};

PYSDK_DLL inline FBOpticalGap_Wrapper* FBOpticalGap_Wrapper_Factory( FBOpticalGap pFBOpticalGap )
{
	return new FBOpticalGap_Wrapper( pFBOpticalGap );
}
#endif // pyfbopticalgap_h__