#ifndef pyfbrendererCallback_h__
#define pyfbrendererCallback_h__
/**************************************************************************
 Copyright 2011 Autodesk, Inc.
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

#include <kaydara.h>

#include "pyfbpropertylist.h"
DefinePropertyList ( RendererCallback );

// =======================================================================================
// FBRenderer
// =======================================================================================
void FBRendererCallback_Init();

class PYSDK_DLL FBRendererCallback_Wrapper : public FBComponent_Wrapper {
public:
	FBRendererCallback* mFBRendererCallback;
public:
	FBRendererCallback_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBRendererCallback = (FBRendererCallback*)pFBComponent; }
    FBRendererCallback_Wrapper( const char *pName );

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS (SupportIDBufferPicking,               bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS (DefaultCameraFrontPlateRendering,     bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS (DefaultCameraBackPlateRendering,      bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS (DefaultLightGroundProjectionRendering,   bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS (DefaultLightVolumeRendering,          bool);
};


#endif // pyfbrendererCallback_h__