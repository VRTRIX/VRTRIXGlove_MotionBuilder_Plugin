#ifndef pyfbrigidbody_h__
#define pyfbrigidbody_h__
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

// =======================================================================================
// FBRigidBody
// =======================================================================================
//#pragma once

void FBRigidBody_Init();

class PYSDK_DLL FBRigidBody_Wrapper : public FBComponent_Wrapper {
public:
	FBRigidBody* mFBRigidBody;
public:
	FBRigidBody_Wrapper( FBComponent* pFBComponent );
	FBRigidBody_Wrapper( FBRigidBody& pFBRigidBody );
	FBRigidBody_Wrapper( FBModelOptical_Wrapper& pModelOptical );
	virtual ~FBRigidBody_Wrapper( );

	void Snap() { mFBRigidBody->Snap(); }
	bool IsValid() { return mFBRigidBody->IsValid(); }
	void ComputeAnimation() { mFBRigidBody->ComputeAnimation(); }

	object GetQualityData( ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBRigidBody->QualityData ); }
	void   SetModel( FBModel_Wrapper& pModel ) { mFBRigidBody->Model = pModel.mFBModel; }
	object GetModel( ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBRigidBody->Model ); }
	object GetMarkers( ) { return FBPropertyListRigidBodyMarkers_Wrapper_Factory( mFBRigidBody->Markers ); }
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Done,	bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SmoothWidth,	int);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Mode,	FBRigidBodyMode	);
};

PYSDK_DLL inline FBRigidBody_Wrapper* FBRigidBody_Wrapper_Factory( FBRigidBody pFBRigidBody )
{
	return new FBRigidBody_Wrapper( pFBRigidBody );
}
#endif // pyfbrigidbody_h__