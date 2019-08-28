#ifndef pyfblayoutregion_h__
#define pyfblayoutregion_h__
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

#include "pyfbvisualcomponent.h"

// =======================================================================================
// FBLayoutRegion
// =======================================================================================
void FBLayoutRegion_Init();

class PYSDK_DLL FBLayoutRegion_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBLayoutRegion* mFBLayoutRegion;
public:
	FBLayoutRegion_Wrapper( FBComponent* pFBComponent );
	FBLayoutRegion_Wrapper();
	virtual ~FBLayoutRegion_Wrapper( ) {  }
};
#endif // pyfblayoutregion_h__