#ifndef pyfbhandle_h__
#define pyfbhandle_h__
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

#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"

// =======================================================================================
// FBHandle
// =======================================================================================
void FBHandle_Init();

class PYSDK_DLL FBHandle_Wrapper : public FBBox_Wrapper {
public:
	FBHandle* mFBHandle;
public:
	FBHandle_Wrapper( FBHandle* pFBHandle ) : FBBox_Wrapper( pFBHandle ) { mFBHandle = pFBHandle; }
	FBHandle_Wrapper( const char* pName ) : FBBox_Wrapper( new FBHandle( pName )) { mFBHandle = (FBHandle*)mFBComponent; }
	virtual ~FBHandle_Wrapper( ) {}
	void Select() { mFBHandle->Select(); }
	object GetFollow(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBHandle->Follow ); }
	object GetImage(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBHandle->Image ); }
	object GetManipulate(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBHandle->Manipulate ); }
	object GetManipulateRotation(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBHandle->ManipulateRotation ); }
	object GetManipulateScaling(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBHandle->ManipulateScaling ); }
	object GetManipulateTranslation(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBHandle->ManipulateTranslation ); }
};
#endif // pyfbhandle_h__

