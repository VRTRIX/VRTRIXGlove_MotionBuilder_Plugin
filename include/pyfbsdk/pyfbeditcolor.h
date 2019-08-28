#ifndef pyfbeditcolor_h__
#define pyfbeditcolor_h__
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

void FBEditColor_Init();

// =======================================================================================
// FBEditColor
// =======================================================================================
class PYSDK_DLL FBEditColor_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBEditColor* mFBEditColor;
public:
	FBEditColor_Wrapper( FBComponent* pFBComponent );
	FBEditColor_Wrapper();
	virtual ~FBEditColor_Wrapper( ) {  }
	void SetColorMode( int pColorMode ) { mFBEditColor->ColorMode = pColorMode; }
	int GetColorMode(  ) { return mFBEditColor->ColorMode; }
	void SetValue( FBColor_Wrapper& pValue ) { mFBEditColor->Value = *pValue.mFBColor; }
	FBColor_Wrapper* GetValue(  ) { return FBColor_Wrapper_Factory( mFBEditColor->Value ); }
    object OnChange();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbeditcolor_h__