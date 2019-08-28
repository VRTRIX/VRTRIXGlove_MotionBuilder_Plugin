#ifndef pyfbeditvector_h__
#define pyfbeditvector_h__
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
// FBEditVector
// =======================================================================================
void FBEditVector_Init();

class PYSDK_DLL FBEditVector_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBEditVector* mFBEditVector;
public:
	FBEditVector_Wrapper( FBComponent* pFBComponent );
	FBEditVector_Wrapper();
	virtual ~FBEditVector_Wrapper( ) {  }
	void SetValue( FBVector3d_Wrapper& pValue ) { mFBEditVector->Value = *pValue.mFBVector3d; }
	FBVector3d_Wrapper* GetValue(  ) { return FBVector3d_Wrapper_Factory( mFBEditVector->Value ); }
    object OnChange();

protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbeditvector_h__