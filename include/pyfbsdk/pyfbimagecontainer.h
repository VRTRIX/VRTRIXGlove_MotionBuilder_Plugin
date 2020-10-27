#ifndef pyfbimagecontainer_h__
#define pyfbimagecontainer_h__
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
// FBImageContainer
// =======================================================================================
void FBImageContainer_Init();

class PYSDK_DLL FBImageContainer_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBImageContainer* mFBImageContainer;
public:
	FBImageContainer_Wrapper( FBComponent* pFBComponent );
	FBImageContainer_Wrapper();
	virtual ~FBImageContainer_Wrapper( ) {  }

	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBImageContainer, Filename, const char* );

    object OnDragAndDrop();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbimagecontainer_h__