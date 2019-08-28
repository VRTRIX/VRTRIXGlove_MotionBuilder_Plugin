#ifndef pyfbview_h__
#define pyfbview_h__
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
// FBView
// =======================================================================================
void FBView_Init();

class PYSDK_DLL FBView_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBView* mFBView;
public:
	FBView_Wrapper( FBComponent* pFBComponent );
	FBView_Wrapper();
	virtual ~FBView_Wrapper( ) {  }
	void DrawString(const char * pText, float pX, float pY, int pEnable = -1) { mFBView->DrawString( pText, pX, pY, pEnable ); }
	bool IsView() { return mFBView->IsView(  ); }
	void Refresh(bool pNow = false) { mFBView->Refresh( pNow ); }
	bool SetViewport(int pX, int pY, int pW, int pH) { return mFBView->SetViewport( pX, pY, pW, pH ); }
	bool GetDoubleBuffer(  ) { return mFBView->DoubleBuffer; }
	bool GetGraphicOGL(  ) { return mFBView->GraphicOGL; }
};
#endif // class_f_b_view_gen_h__