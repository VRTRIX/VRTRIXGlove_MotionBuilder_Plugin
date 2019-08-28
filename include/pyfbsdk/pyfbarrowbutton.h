#ifndef pyfbarrowbutton_h__
#define pyfbarrowbutton_h__
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
// FBButton
// =======================================================================================
void FBArrowButton_Init();

class PYSDK_DLL FBArrowButton_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBArrowButton* mFBButton;
public:	
    FBArrowButton_Wrapper();
    FBArrowButton_Wrapper( FBComponent* pFBComponent );
	virtual ~FBArrowButton_Wrapper( );
    void SetContent( const char* pTitle, FBVisualComponent_Wrapper& pContent, int pContentWidth, int pContentHeight );
	
};
#endif // pyfbarrowbutton_h__