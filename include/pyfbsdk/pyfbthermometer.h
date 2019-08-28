#ifndef pyfbthermometer_h__
#define pyfbthermometer_h__
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
// FBThermometer
// =======================================================================================
void FBThermometer_Init();

class PYSDK_DLL FBThermometer_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBThermometer* mFBThermometer;
public:
	FBThermometer_Wrapper( FBComponent* pFBComponent );
	FBThermometer_Wrapper();
	virtual ~FBThermometer_Wrapper( ) {  }
	void Clear() { mFBThermometer->Clear(  ); }
	void SetMax( float pMax ) { mFBThermometer->Max = pMax; }
	float GetMax(  ) { return mFBThermometer->Max; }
	void SetMin( float pMin ) { mFBThermometer->Min = pMin; }
	float GetMin(  ) { return mFBThermometer->Min; }
	void SetValue( float pValue ) { mFBThermometer->Value = pValue; }
	float GetValue(  ) { return mFBThermometer->Value; }
};
#endif // pyfbthermometer_h__