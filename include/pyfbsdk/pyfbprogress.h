#ifndef pyfbprogress_h__
#define pyfbprogress_h__
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

// =======================================================================================
// FBProgress
// =======================================================================================
void FBProgress_Init();

class PYSDK_DLL FBProgress_Wrapper : public FBComponent_Wrapper {
public:
	FBProgress* mFBProgress;
public:
	FBProgress_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBProgress = (FBProgress*)pFBComponent; }
	FBProgress_Wrapper() : FBComponent_Wrapper( new FBProgress()) { mFBProgress = (FBProgress*)mFBComponent; }
	virtual ~FBProgress_Wrapper( ) {}
	void SetCaption( const char* pCaption ) { mFBProgress->Caption = pCaption; }
	const char* GetCaption(  ) { return mFBProgress->Caption; }
	void ProgressBegin() { mFBProgress->ProgressBegin(); }
	void ProgressDone() { mFBProgress->ProgressDone(); }
	bool UserRequestCancell() { return mFBProgress->UserRequestCancell(); }
	void SetPercent( int pPercent ) { mFBProgress->Percent = pPercent; }
	int GetPercent(  ) { return mFBProgress->Percent; }
	void SetText( const char* pText ) { mFBProgress->Text = pText; }
	const char* GetText(  ) { return mFBProgress->Text; }
};
#endif // pyfbprogress_h__