#ifndef pyfbeditproperty_h__
#define pyfbeditproperty_h__
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
// FBEditProperty
// =======================================================================================
void FBEditProperty_Init();

class PYSDK_DLL FBEditProperty_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBEditProperty* mFBEditProperty;
public:
	FBEditProperty_Wrapper( FBComponent* pFBComponent );
	FBEditProperty_Wrapper();
	virtual ~FBEditProperty_Wrapper( ) {  }
	void SetLargeInc( double pLargeInc ) { mFBEditProperty->LargeInc = pLargeInc; }
	double GetLargeInc(  ) { return mFBEditProperty->LargeInc; }
	void SetPrecision( double pPrecision ) { mFBEditProperty->Precision = pPrecision; }
	double GetPrecision(  ) { return mFBEditProperty->Precision; }
	void SetProperty( FBProperty_Wrapper* pProperty );
	object GetProperty(  ) { return FBProperty_Wrapper_Factory( static_cast<FBProperty*>(mFBEditProperty->Property) ); }
	void SetSliderMax( double pSliderMax ) { mFBEditProperty->SliderMax = pSliderMax; }
	double GetSliderMax(  ) { return mFBEditProperty->SliderMax; }
	void SetSliderMin( double pSliderMin ) { mFBEditProperty->SliderMin = pSliderMin; }
	double GetSliderMin(  ) { return mFBEditProperty->SliderMin; }
	void SetSmallInc( double pSmallInc ) { mFBEditProperty->SmallInc = pSmallInc; }
	double GetSmallInc(  ) { return mFBEditProperty->SmallInc; }
};
#endif // pyfbeditproperty_h__