#ifndef pyfblabel_h__
#define pyfblabel_h__
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
// FBLabel
// =======================================================================================
void FBLabel_Init();


class PYSDK_DLL FBLabel_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBLabel* mFBLabel;

public:
	FBLabel_Wrapper( FBComponent* pFBComponent );
	FBLabel_Wrapper();
	virtual ~FBLabel_Wrapper( );
	void SetJustify( FBTextJustify pJustify ) { mFBLabel->Justify = pJustify; }
	FBTextJustify GetJustify(  ) { return mFBLabel->Justify; }
	void SetStyle( FBTextStyle pStyle ) { mFBLabel->Style = pStyle; }
	FBTextStyle GetStyle(  ) { return mFBLabel->Style; }
	void SetWordWrap( bool pWordWrap ) { mFBLabel->WordWrap = pWordWrap; }
	bool GetWordWrap(  ) { return mFBLabel->WordWrap; }    
};
#endif // pyfblabel_h__