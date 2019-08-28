#ifndef class_f_b_physicalproperties_gen_h__
#define class_f_b_physicalproperties_gen_h__
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
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbconstraint.h"
#include "pyfbconstraintsolver.h"

// =======================================================================================
// FBPhysicalProperties
// =======================================================================================
void FBPhysicalProperties_Init();

class PYSDK_DLL FBPhysicalProperties_Wrapper : public FBBox_Wrapper {
public:
	FBPhysicalProperties* mFBPhysicalProperties;
public:
	FBPhysicalProperties_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBPhysicalProperties = (FBPhysicalProperties*)pFBComponent; }
	FBPhysicalProperties_Wrapper( const char* pName = NULL ) : FBBox_Wrapper( new FBPhysicalProperties( pName )) { mFBPhysicalProperties = (FBPhysicalProperties*)mFBComponent; }
	virtual ~FBPhysicalProperties_Wrapper( ) {}
};
#endif // class_f_b_physicalproperties_gen_h__