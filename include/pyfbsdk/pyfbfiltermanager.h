#ifndef pyfbfiltermanager_h__
#define pyfbfiltermanager_h__
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

#include "pyfbstringlist.h"

// =======================================================================================
// FBFilterManager
// =======================================================================================
void FBFilterManager_Init();

class PYSDK_DLL FBFilterManager_Wrapper {
public:
	FBFilterManager* mFBFilterManager;
public:
    FBFilterManager_Wrapper(  ) : mFBFilterManager( new FBFilterManager ) {}
	virtual ~FBFilterManager_Wrapper( ) { delete mFBFilterManager; }
	object CreateFilter(const char * pFilterTypeName) {
        return FBWrapperFactory::TheOne().WrapFBObject( mFBFilterManager->CreateFilter( pFilterTypeName ));
    }
	FBStringList_Wrapper* GetFilterTypeNames(  ) { return FBStringList_Wrapper_Factory( &( mFBFilterManager->FilterTypeNames )); }
};
#endif // pyfbfiltermanager_h__
