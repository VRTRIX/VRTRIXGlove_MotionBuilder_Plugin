#ifndef pyfbopticalsegment_h__
#define pyfbopticalsegment_h__
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
#include "pyfbmodelmarker.h"
#include "pyfbmodeloptical.h"
#include "pyfbmodelmarkeroptical.h"

// =======================================================================================
// FBOpticalSegment
// =======================================================================================
void FBOpticalSegment_Init();
class FBModelMarkerOptical_Wrapper;
class PYSDK_DLL FBOpticalSegment_Wrapper : public FBComponent_Wrapper {
public:
	FBOpticalSegment* mFBOpticalSegment;
public:
	FBOpticalSegment_Wrapper( FBComponent* pFBComponent );
	FBOpticalSegment_Wrapper( FBOpticalSegment& pFBOpticalSegment ) ;
	FBOpticalSegment_Wrapper( FBModelOptical_Wrapper& pModelOptical );
	virtual ~FBOpticalSegment_Wrapper( );

	void Cut(FBTime_Wrapper& pTime) { mFBOpticalSegment->Cut( *pTime.mFBTime ); }
	bool IsValid() { return mFBOpticalSegment->IsValid(); }
	void Reset() { mFBOpticalSegment->Reset(); }

	object GetData(  ) { return	FBWrapperFactory::TheOne().WrapFBObject( mFBOpticalSegment->Data ); }
	object GetMarker(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBOpticalSegment->Marker ); }
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(OriginalTimeSpan,	FBTimeSpan);
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(TimeSpan,	FBTimeSpan);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Used, bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(MarkerTimeSpan,	FBTimeSpan);
};

PYSDK_DLL inline FBOpticalSegment_Wrapper* FBOpticalSegment_Wrapper_Factory( FBOpticalSegment pFBOpticalSegment )
{
	return new FBOpticalSegment_Wrapper( pFBOpticalSegment );
}
#endif // pyfbopticalsegment_h__