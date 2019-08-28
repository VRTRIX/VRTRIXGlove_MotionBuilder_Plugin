#ifndef pyfbmodelmarkeroptical_h__
#define pyfbmodelmarkeroptical_h__
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
#include "pyfbrigidbody.h"

// =======================================================================================
// FBModelMarkerOptical
// =======================================================================================
void FBModelMarkerOptical_Init();
class FBRigidBody_Wrapper;
class PYSDK_DLL FBModelMarkerOptical_Wrapper : public FBModelMarker_Wrapper {
public:
	FBModelMarkerOptical* mFBModelMarkerOptical;
public:
	FBModelMarkerOptical_Wrapper( FBComponent* pFBComponent ) : FBModelMarker_Wrapper( pFBComponent ) { mFBModelMarkerOptical = (FBModelMarkerOptical*)pFBComponent; }
	FBModelMarkerOptical_Wrapper( const char* pName, FBModelOptical_Wrapper& pModelOptical ) : FBModelMarker_Wrapper( new FBModelMarkerOptical( pName, pModelOptical.mFBModelOptical )) { mFBModelMarkerOptical = (FBModelMarkerOptical*)mFBComponent; }
	virtual ~FBModelMarkerOptical_Wrapper( ) { }


	int  ImportBegin() { return mFBModelMarkerOptical->ImportBegin(); }
	int  ExportBegin() { return mFBModelMarkerOptical->ExportBegin(); }

	bool ImportKey( double pX, double pY, double pZ=0.0, double pOcclusion=0.0 ) { return mFBModelMarkerOptical->ImportKey( pX, pY, pZ, pOcclusion ); }
	bool ExportKey( double *pX, double *pY, double *pZ=NULL, double *pOcclusion=NULL ) { return mFBModelMarkerOptical->ExportKey( pX, pY, pZ ? pZ:NULL, pOcclusion ? pOcclusion:NULL); }

	bool ImportEnd() { return mFBModelMarkerOptical->ImportEnd(); }
	bool ExportEnd() { return mFBModelMarkerOptical->ExportEnd(); }
	
	FBRigidBody_Wrapper* GetRigidBody() { return FBRigidBody_Wrapper_Factory( mFBModelMarkerOptical->GetRigidBody() ); }

	void SetModelOptical( FBModelOptical_Wrapper& pOptical ) { mFBModelMarkerOptical->SetModelOptical( pOptical.mFBModelOptical ); }
	void InsertSegmentedData(FBAnimationNode_Wrapper& pTData, FBAnimationNode_Wrapper& pOData) { mFBModelMarkerOptical->InsertSegmentedData( pTData.mFBAnimationNode, pOData.mFBAnimationNode ); }

	object GetData(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModelMarkerOptical->Data ); }
	object GetOptical(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBModelMarkerOptical->Optical ); }
	object GetGaps(  ) { return FBPropertyListOpticalGap_Wrapper_Factory( mFBModelMarkerOptical->Gaps ); }
	object GetSegments(  ) { return FBPropertyListMarkerSegment_Wrapper_Factory( mFBModelMarkerOptical->Segments ); }

	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(Color,	FBColor);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Done,	bool);
};
#endif // pyfbmodelmarkeroptical_h__