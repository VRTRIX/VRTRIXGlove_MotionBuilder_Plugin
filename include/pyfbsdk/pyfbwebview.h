#ifndef pyfbwebview_h__
#define pyfbwebview_h__
/**************************************************************************
 Copyright 2012 Autodesk, Inc.
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
// FBWebView
// =======================================================================================
void FBWebView_Init();


class PYSDK_DLL FBWebView_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBWebView* mFBWebView;

public:
	FBWebView_Wrapper( FBComponent* pFBComponent );
	FBWebView_Wrapper();
	virtual ~FBWebView_Wrapper( );
	void Load(const char* pURL) { mFBWebView->Load(pURL); }
};
#endif // pyfbwebview_h__