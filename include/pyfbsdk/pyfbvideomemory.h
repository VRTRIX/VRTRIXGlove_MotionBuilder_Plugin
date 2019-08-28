#ifndef pyfbvideomemory_h__
#define pyfbvideomemory_h__
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

#include "pyfbvideo.h"

// =======================================================================================
// FBVideo
// =======================================================================================
void FBVideoMemory_Init();

class PYSDK_DLL FBVideoMemory_Wrapper : public FBVideo_Wrapper {
protected:
	FBVideoMemory* mFBVideoMemory;

public:
	FBVideoMemory_Wrapper( FBComponent* pFBComponent ) : FBVideo_Wrapper( pFBComponent ) { mFBVideoMemory = (FBVideoMemory*)pFBComponent; }
	FBVideoMemory_Wrapper( const char* pName );
	virtual ~FBVideoMemory_Wrapper( ) {}

    void SetObjectImageSize(int pW,int pH) { mFBVideoMemory->SetObjectImageSize(pW, pH);}
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(TextureOGLId, unsigned int);
};
#endif // pyfbvideo_h__
