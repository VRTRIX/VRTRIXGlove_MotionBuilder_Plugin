#ifndef pyfbscrollbox_h__
#define pyfbscrollbox_h__
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
// FBScrollBox
// =======================================================================================
void FBScrollBox_Init();

class PYSDK_DLL FBScrollBox_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBScrollBox* mFBScrollBox;
public:
	FBScrollBox_Wrapper( FBComponent* pFBComponent );
	FBScrollBox_Wrapper();
	virtual ~FBScrollBox_Wrapper( );
	void SetContentSize( int pContentWidth, int pContentHeight );
	object GetContent();
};
#endif // pyfbscrollbox_h__