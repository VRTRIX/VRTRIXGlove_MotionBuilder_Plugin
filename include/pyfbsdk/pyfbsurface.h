#ifndef pyfbsurface_h__
#define pyfbsurface_h__
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

// =======================================================================================
// FBSurface
// =======================================================================================
void FBSurface_Init();                              

class PYSDK_DLL FBSurface_Wrapper : public FBGeometry_Wrapper {
public:
	FBSurface* mFBSurface;
public:
	FBSurface_Wrapper( FBComponent* pFBComponent );
	virtual ~FBSurface_Wrapper();
	void ControlPointsBegin();
	void ControlPointsEnd();
	void GetControlPoint(int pIndex, double & pX, double & pY, double & pZ, double & pW);
	bool GetSurfaceCapped(int pUorV, int pDirection);
	int GetVertexCount(int pUorVorGlobal = -1);
	void SetControlPoint(int pIndex, double pX, double pY, double pZ, double pW);
	void SurfaceBegin();
	void SurfaceEditBegin();
	void SurfaceEditEnd();
	void SurfaceEnd();
	bool VertexGetSelected(int pU, int pV);
	bool VertexGetTransformable(int pU, int pV);
	bool VertexGetVisible(int pU, int pV);
	bool VertexSetSelected(int pU, int pV, bool pState);
	bool VertexSetVisible(int pU, int pV, bool pState);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(USize, int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(VSize, int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UStep, int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(VStep, int);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UClosed, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(VClosed, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SurfaceMode, FBSurfaceMode);
};
#endif // pyfbsurface_h__