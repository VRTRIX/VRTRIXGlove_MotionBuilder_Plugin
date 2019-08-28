#ifndef pyfbbrowsingproperty_h__
#define pyfbbrowsingproperty_h__
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
// FBBrowsingProperty
// =======================================================================================
void FBBrowsingProperty_Init();

class PYSDK_DLL FBBrowsingProperty_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBBrowsingProperty* mFBBrowsingProperty;
public:
	FBBrowsingProperty_Wrapper( FBVisualComponent* pFBComponent ) : FBVisualComponent_Wrapper( pFBComponent ) { mFBBrowsingProperty = (FBBrowsingProperty*)pFBComponent; }
	FBBrowsingProperty_Wrapper() : FBVisualComponent_Wrapper( new FBBrowsingProperty()) { mFBBrowsingProperty = (FBBrowsingProperty*)mFBVisualComponent; }
	virtual ~FBBrowsingProperty_Wrapper( ) {}	

    void AddObject(FBPlug_Wrapper& pObject); 
    void RemoveObject(FBPlug_Wrapper& pObject);
    int ObjectGetCount();
    object ObjectGet(int pIndex);
    
    // int AddButtonInToolbar(const char* pCaption, HICallback pOwner, kICallbackHandler pHandler);
};
#endif // pyfbbrowsingproperty_h__