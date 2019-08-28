#ifndef pyfbedit_h__
#define pyfbedit_h__
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
// FBEdit
// =======================================================================================
void FBEdit_Init();

class PYSDK_DLL FBEdit_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBEdit* mFBEdit;
public:
	FBEdit_Wrapper( FBComponent* pFBComponent );
	FBEdit_Wrapper();
	virtual ~FBEdit_Wrapper( ) {  }
	void SetPasswordMode( bool pPasswordMode ) { mFBEdit->PasswordMode = pPasswordMode; }
	bool GetPasswordMode(  ) { return mFBEdit->PasswordMode; }
	void SetText( const char* pText ) { mFBEdit->Text = pText; }
	const char* GetText(  ) { return mFBEdit->Text; }
    object OnChange();

protected:
	FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbedit_h__