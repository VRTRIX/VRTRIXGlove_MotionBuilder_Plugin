#ifndef pyfbeditnumber_h__
#define pyfbeditnumber_h__
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
// FBEditNumber
// =======================================================================================
void FBEditNumber_Init();

class PYSDK_DLL FBEditNumber_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBEditNumber* mFBEditNumber;
public:
	FBEditNumber_Wrapper( FBComponent* pFBComponent );
	FBEditNumber_Wrapper();
	virtual ~FBEditNumber_Wrapper( ) {  }
	void SetLargeStep( double pLargeStep ) { mFBEditNumber->LargeStep = pLargeStep; }
	double GetLargeStep(  ) { return mFBEditNumber->LargeStep; }
	void SetMax( double pMax ) { mFBEditNumber->Max = pMax; }
	double GetMax(  ) { return mFBEditNumber->Max; }
	void SetMin( double pMin ) { mFBEditNumber->Min = pMin; }
	double GetMin(  ) { return mFBEditNumber->Min; }
	void SetPrecision( double pPrecision ) { mFBEditNumber->Precision = pPrecision; }
	double GetPrecision(  ) { return mFBEditNumber->Precision; }
	void SetSmallStep( double pSmallStep ) { mFBEditNumber->SmallStep = pSmallStep; }
	double GetSmallStep(  ) { return mFBEditNumber->SmallStep; }
	void SetValue( double pValue ) { mFBEditNumber->Value = pValue; }
	double GetValue(  ) { return mFBEditNumber->Value; }
    object OnChange();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbeditnumber_h__