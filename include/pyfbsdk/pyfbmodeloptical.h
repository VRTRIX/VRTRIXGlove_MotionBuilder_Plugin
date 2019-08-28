#ifndef pyfbmodeloptical_h__
#define pyfbmodeloptical_h__
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

// =======================================================================================
// FBModelOptical
// =======================================================================================
void FBModelOptical_Init();

class PYSDK_DLL FBModelOptical_Wrapper : public FBModel_Wrapper {
public:
	FBModelOptical* mFBModelOptical;
public:
	FBModelOptical_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBModelOptical = (FBModelOptical*)pFBComponent; }
	FBModelOptical_Wrapper( const char* pName ) : FBModel_Wrapper( new FBModelOptical( pName )) { mFBModelOptical = (FBModelOptical*)mFBComponent; }
	virtual ~FBModelOptical_Wrapper( ) { }
	void ClearSegments(bool pUnUsedOnly = true) { mFBModelOptical->ClearSegments( pUnUsedOnly ); }
	bool ExportSetup() { return mFBModelOptical->ExportSetup(  ); }
	bool ImportSetup() { return mFBModelOptical->ImportSetup(  ); }	
	void SetMarkerSize( double pMarkerSize ) { mFBModelOptical->MarkerSize = pMarkerSize; }
	double GetMarkerSize(  ) { return mFBModelOptical->MarkerSize; }	
	void SetSamplingPeriod( FBTime_Wrapper& pSamplingPeriod ) { mFBModelOptical->SamplingPeriod = *pSamplingPeriod.mFBTime; }
	FBTime_Wrapper* GetSamplingPeriod(  ) { return FBTime_Wrapper_Factory( mFBModelOptical->SamplingPeriod ); }
	void SetSamplingStart( FBTime_Wrapper& pSamplingStart ) { mFBModelOptical->SamplingStart = *pSamplingStart.mFBTime; }
	FBTime_Wrapper* GetSamplingStart(  ) { return FBTime_Wrapper_Factory( mFBModelOptical->SamplingStart ); }
	void SetSamplingStop( FBTime_Wrapper& pSamplingStop ) { mFBModelOptical->SamplingStop = *pSamplingStop.mFBTime; }
	FBTime_Wrapper* GetSamplingStop(  ) { return FBTime_Wrapper_Factory( mFBModelOptical->SamplingStop ); }
	object GetMarkers()      { return FBPropertyListModelMarkerOptical_Wrapper_Factory( mFBModelOptical->Markers ); }
	object GetSegments()     { return FBPropertyListOpticalSegment_Wrapper_Factory( mFBModelOptical->Segments ); }
	object GetRigidBodies()  { return FBPropertyListRigidBody_Wrapper_Factory( mFBModelOptical->RigidBodies ); }
};
#endif // pyfbmodeloptical_h__