#ifndef pyfbpointcachefile_h__
#define pyfbpointcachefile_h__
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

// =======================================================================================
// FBPopup
// =======================================================================================
void FBPointCacheFile_Init();

class PYSDK_DLL FBPointCacheFile_Wrapper : public FBComponent_Wrapper {
public:
	FBPointCacheFile* mFBPointCacheFile;
public:
	FBPointCacheFile_Wrapper( FBComponent* pFBComponent );
	FBPointCacheFile_Wrapper( const char* pName );
	virtual ~FBPointCacheFile_Wrapper( );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CacheFileName,	const char*);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ChannelCount,	int);
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(StartTime, FBTime);
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(StopTime,	FBTime);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PlaySpeed, double);
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(Offset, FBTime);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FreeRunning, bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(Loop, bool);
};
#endif // pyfbpointcachefile_h__