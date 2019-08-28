#ifndef pyfbpointcachemanager_h__
#define pyfbpointcachemanager_h__
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

#include "pyfbmatrix.h"
#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"

// =======================================================================================
// FBPointCacheManager
// =======================================================================================
void FBPointCacheManager_Init();

class PYSDK_DLL FBPointCacheManager_Wrapper : public FBComponent_Wrapper {
public:
	FBPointCacheManager* mFBPointCacheManager;
public:
	FBPointCacheManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBPointCacheManager = (FBPointCacheManager*)pFBComponent; }
	FBPointCacheManager_Wrapper(  ) : FBComponent_Wrapper( &FBPointCacheManager::TheOne() ) { mFBPointCacheManager = (FBPointCacheManager*)mFBComponent; }
	virtual ~FBPointCacheManager_Wrapper( ) { }

    object GetModels()      { return FBWrapperFactory::TheOne().WrapFBObject( &mFBPointCacheManager->Models ); }

    void   SetNewModelRoot( FBModel_Wrapper& pNewModelRoot ) { mFBPointCacheManager->NewModelRoot = pNewModelRoot.mFBModel; }
	object GetNewModelRoot() { return FBWrapperFactory::TheOne().WrapFBObject( mFBPointCacheManager->NewModelRoot ); }

    void  SetTransformReference() { mFBPointCacheManager->SetTransformReference(); }

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ApplyGlobalTransform, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ApplyCacheOnNewModel, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(AllowCacheResampling, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(AlwaysAskForPath, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(DefaultPath, const char*);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CacheNormal, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CacheAABBox, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CreateMultiChannelCache, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CreateFilePerFrameCache, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SaveEveryFrame, int);
};
#endif // pyfbpointcachemanager_h__