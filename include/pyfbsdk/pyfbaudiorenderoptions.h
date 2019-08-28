#ifndef pyfbaudiorenderoptions_h__
#define pyfbaudiorenderoptions_h__
/**************************************************************************
 Copyright 2011 Autodesk, Inc.
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
// FBVideoGrabOptions
// =======================================================================================
void FBAudioRenderOptions_Init();

class FBAudioRenderOptions_Wrapper;
PYSDK_DLL FBAudioRenderOptions_Wrapper* FBAudioRenderOptions_Wrapper_Factory( FBAudioRenderOptions* pFBAudioRenderOptions );
class PYSDK_DLL FBAudioRenderOptions_Wrapper {
public:
	FBAudioRenderOptions* mFBAudioRenderOptions;
public:
    FBAudioRenderOptions_Wrapper( const FBAudioRenderOptions& pFBAudioRenderOptions ) : mFBAudioRenderOptions( new FBAudioRenderOptions( pFBAudioRenderOptions ) ) {}
    FBAudioRenderOptions_Wrapper() : mFBAudioRenderOptions( new FBAudioRenderOptions ) {}
    virtual ~FBAudioRenderOptions_Wrapper( ) { delete mFBAudioRenderOptions; }

	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(TimeSpan,     FBTimeSpan);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ChannelMode,  FBAudioChannelMode);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(BitDepthMode, FBAudioBitDepthMode);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(RateMode,     FBAudioRateMode);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(OutputFileName, const char*);
};

PYSDK_DLL inline FBAudioRenderOptions_Wrapper* FBAudioRenderOptions_Wrapper_Factory( FBAudioRenderOptions* pFBAudioRenderOptions )
{
	FBAudioRenderOptions_Wrapper* lFBAudioRenderOptions = NULL;
	if( pFBAudioRenderOptions )
	{
		lFBAudioRenderOptions = new FBAudioRenderOptions_Wrapper( *pFBAudioRenderOptions );
	}
	return lFBAudioRenderOptions;
}
#endif // pyfbaudiorenderoptions_h__