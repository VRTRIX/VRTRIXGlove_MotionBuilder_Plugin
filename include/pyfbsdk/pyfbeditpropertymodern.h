#ifndef pyfbeditpropertymodern_h__
#define pyfbeditpropertymodern_h__
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
// FBEditPropertyModern
// =======================================================================================
void FBEditPropertyModern_Init();

class PYSDK_DLL FBEditPropertyModern_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBEditPropertyModern* mFBEditPropertyModern;
public:
	FBEditPropertyModern_Wrapper( FBComponent* pFBComponent );
	FBEditPropertyModern_Wrapper();
	virtual ~FBEditPropertyModern_Wrapper( ) {  }
	void SetBackgroundColorIndex(FBColorIndex pIndex) { mFBEditPropertyModern->SetBackgroundColorIndex( pIndex ); }
	void SetLargeInc( double pLargeInc ) { mFBEditPropertyModern->LargeInc = pLargeInc; }
	double GetLargeInc(  ) { return mFBEditPropertyModern->LargeInc; }
	void SetPrecision( double pPrecision ) { mFBEditPropertyModern->Precision = pPrecision; }
	double GetPrecision(  ) { return mFBEditPropertyModern->Precision; }
	void SetProperty( FBProperty_Wrapper* pProperty );
	object GetProperty(  ) { return FBProperty_Wrapper_Factory( static_cast<FBProperty*>(mFBEditPropertyModern->Property) ); }
	void SetSliderMax( double pSliderMax ) { mFBEditPropertyModern->SliderMax = pSliderMax; }
	double GetSliderMax(  ) { return mFBEditPropertyModern->SliderMax; }
	void SetSliderMin( double pSliderMin ) { mFBEditPropertyModern->SliderMin = pSliderMin; }
	double GetSliderMin(  ) { return mFBEditPropertyModern->SliderMin; }
	void SetSmallInc( double pSmallInc ) { mFBEditPropertyModern->SmallInc = pSmallInc; }
	double GetSmallInc(  ) { return mFBEditPropertyModern->SmallInc; }
};
#endif // pyfbeditpropertymodern_h__