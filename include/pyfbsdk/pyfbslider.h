#ifndef pyfbslider_h__
#define pyfbslider_h__
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
// FBSlider
// =======================================================================================
void FBSlider_Init();

class PYSDK_DLL FBSlider_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBSlider* mFBSlider;
public:
	FBSlider_Wrapper( FBComponent* pFBComponent );
	FBSlider_Wrapper();
    virtual ~FBSlider_Wrapper( ) {  }	
	void SetMax( double pMax ) { mFBSlider->Max = pMax; }
	double GetMax(  ) { return mFBSlider->Max; }
	void SetMin( double pMin ) { mFBSlider->Min = pMin; }
	double GetMin(  ) { return mFBSlider->Min; }
	void SetOrientation( FBOrientation pOrientation ) { mFBSlider->Orientation = pOrientation; }
	FBOrientation GetOrientation(  ) { return mFBSlider->Orientation; }	
	void SetValue( double pValue ) { mFBSlider->Value = pValue; }
	double GetValue(  ) { return mFBSlider->Value; }
    object OnChange();
    object OnTransaction();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbslider_h__