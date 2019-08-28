#ifndef pyfbvideocodecmanager_h__
#define pyfbvideocodecmanager_h__
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
// FBVideoGrabber
// =======================================================================================

void FBVideoCodecManager_Init();

class PYSDK_DLL FBVideoCodecManager_Wrapper 
{
public:
    FBVideoCodecMode GetVideoCodecMode();
    void SetVideoCodecMode( FBVideoCodecMode pVideoCodecMode );

    list GetCodecIdList( const char* pFileFormatInfo );    
    
    void SetDefaultCodec( const char* pFileFormatInfo, const char* pCodecId );
    const char* GetDefaultCodec( const char* pFileFormatInfo );

	bool RegisterExternalVideoFormat( const char* pFormatSuffix );
};

#endif // pyfbvideocodecmanager_h__
