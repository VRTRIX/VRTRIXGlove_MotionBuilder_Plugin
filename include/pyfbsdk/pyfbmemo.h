#ifndef pyfbmemo_h__
#define pyfbmemo_h__
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

#include "pyfbstringlist.h"
#include "pyfbvisualcomponent.h"
#include "pyfbedit.h"

// =======================================================================================
// FBMemo
// =======================================================================================
void FBMemo_Init();
class FBEdit_Wrapper;
class PYSDK_DLL FBMemo_Wrapper : public FBEdit_Wrapper {
public:
	FBMemo* mFBMemo;
public:
	FBMemo_Wrapper( FBComponent* pFBComponent );
	FBMemo_Wrapper();
	virtual ~FBMemo_Wrapper( ) {  }
	void GetStrings(FBStringList_Wrapper& pLines) { mFBMemo->GetStrings( pLines.mFBStringList ); }
	void SetStrings(FBStringList_Wrapper& pLines) { mFBMemo->SetStrings( pLines.mFBStringList ); }    
};
#endif // pyfbmemo_h__