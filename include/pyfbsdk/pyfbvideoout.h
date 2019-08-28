#ifndef pyfbvideoout_h__
#define pyfbvideoout_h__
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
#include "pyfbvideo.h"
#include "pyfbvideoclip.h"
#include "pyfbvideoin.h"

// =======================================================================================
// FBVideoOut
// =======================================================================================
void FBVideoOut_Init();

class PYSDK_DLL FBVideoOut_Wrapper : public FBVideo_Wrapper {
public:
	FBVideoOut* mFBVideoOut;
public:
	FBVideoOut_Wrapper( FBComponent* pFBComponent ) : FBVideo_Wrapper( pFBComponent ) { mFBVideoOut = (FBVideoOut*)pFBComponent; }
	FBVideoOut_Wrapper(  ) : FBVideo_Wrapper( new FBVideoOut(  )) { mFBVideoOut = (FBVideoOut*)mFBComponent; }
	virtual ~FBVideoOut_Wrapper( ) { }
	bool GetOnline() { return mFBVideoOut->Online; }
	void SetOnline(bool pValue) { mFBVideoOut->Online = pValue; }
};
#endif // pyfbvideoout_h__