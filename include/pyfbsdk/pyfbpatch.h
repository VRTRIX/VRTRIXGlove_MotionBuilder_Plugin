#ifndef pyfbpatch_h__
#define pyfbpatch_h__
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

#include "pyfbgeometry.h"
#include "pyfbsurface.h"

// =======================================================================================
// FBPatch
// =======================================================================================
void FBPatch_Init();

class PYSDK_DLL FBPatch_Wrapper : public FBSurface_Wrapper {
public:
	FBPatch* mFBPatch;
public:
	FBPatch_Wrapper( FBComponent* pFBComponent );
	FBPatch_Wrapper( const char* pName );
	virtual ~FBPatch_Wrapper();
	void ControlPointsBegin();
	void ControlPointsEnd();
	void SurfaceBegin();
	void SurfaceEditBegin();
	void SurfaceEditEnd();
	void SurfaceEnd();
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(USurfaceType, FBSurfaceType)
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(VSurfaceType, FBSurfaceType)
};
#endif // pyfbpatch_h__
