#ifndef pyfbnurbs_h__
#define pyfbnurbs_h__
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
// FBNurbs
// =======================================================================================
void FBNurbs_Init();

class PYSDK_DLL FBNurbs_Wrapper : public FBSurface_Wrapper {
public:
	FBNurbs* mFBNurbs;
public:
	FBNurbs_Wrapper( FBComponent* pFBComponent );
	FBNurbs_Wrapper( const char* pName );
	virtual ~FBNurbs_Wrapper();
	void ControlPointsBegin();
	void ControlPointsEnd();
	double GetControlKnotValue(int pUorV, int pIndex);
	int GetControlMultiplicity(int pUorV, int pIndex);
	double GetControlWeight(int pIndex);
	int GetKnotCount(int pUorV);
	void SetControlKnotValue(int pUorV, int pIndex, double pKnotValue);
	void SetControlMultiplicity(int pUorV, int pIndex, int pMultiplicity);
	void SetControlWeight(int pIndex, double pWeight);
	void SurfaceBegin();
	void SurfaceEditBegin();
	void SurfaceEditEnd();
	void SurfaceEnd();
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UOrder, int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(VOrder, int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UNurbType, FBNurbType);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(VNurbType, FBNurbType);
};
#endif // pyfbnurbs_h__