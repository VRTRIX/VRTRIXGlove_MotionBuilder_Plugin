#ifndef pyfbdeformerpointcache_h__
#define pyfbdeformerpointcache_h__
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

#include "pyfbdeformer.h"
#include "pyfbpointcachefile.h"

// =======================================================================================
// FBPopup
// =======================================================================================
void FBDeformerPointCache_Init();
class FBPointCacheFile_Wrapper;
class PYSDK_DLL FBDeformerPointCache_Wrapper : public FBDeformer_Wrapper {
public:
	FBDeformerPointCache* mFBDeformerPointCache;
public:
	FBDeformerPointCache_Wrapper( FBComponent* pFBComponent );
	FBDeformerPointCache_Wrapper( const char* pName );
	virtual ~FBDeformerPointCache_Wrapper( );
	object GetPointCacheFile(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBDeformerPointCache->PointCacheFile ); }
	void SetPointCacheFile(FBPointCacheFile_Wrapper& pPointCacheFile  ) { mFBDeformerPointCache->PointCacheFile = pPointCacheFile.mFBPointCacheFile; }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Active, bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ChannelIndex,	int);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ChannelName,	const char*);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ChannelCount,	int);
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(ChannelStart,	FBTime);
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(ChannelEnd,	FBTime);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ChannelSampleRegular, bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ChannelFrameRate, double);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ChannelPointCount, int);
};
#endif // pyfbdeformerpointcache_h__
