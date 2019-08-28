#ifndef pyfbvideo_h__
#define pyfbvideo_h__
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

#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbimage.h"

// =======================================================================================
// FBVideo
// =======================================================================================
void FBVideo_Init();

class PYSDK_DLL FBVideo_Wrapper : public FBBox_Wrapper {
public:
	FBVideo* mFBVideo;
public:
	FBVideo_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBVideo = (FBVideo*)pFBComponent; }
	FBVideo_Wrapper( const char* pName ) : FBBox_Wrapper( new FBVideo( pName )) { mFBVideo = (FBVideo*)mFBComponent; SetAllocated(); }
	virtual ~FBVideo_Wrapper( ) {}
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(KeepOnGPU,bool);
};
#endif // pyfbvideo_h__
