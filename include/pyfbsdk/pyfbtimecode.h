#ifndef pyfbtimecode_h__
#define pyfbtimecode_h__
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
// FBEditTimeCode
// =======================================================================================
void FBEditTimeCode_Init();

class PYSDK_DLL FBEditTimeCode_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBEditTimeCode* mFBEditTimeCode;
public:
	FBEditTimeCode_Wrapper( FBEditTimeCode* pFBTimeCode );
	FBEditTimeCode_Wrapper();
	virtual ~FBEditTimeCode_Wrapper( ) {  }
	void SetValue( FBTime_Wrapper& pValue ) { mFBEditTimeCode->Value = *pValue.mFBTime; }
	FBTime_Wrapper* GetValue(  ) { return FBTime_Wrapper_Factory( mFBEditTimeCode->Value ); }
    object OnChange();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbtimecode_h__
