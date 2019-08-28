#ifndef pyfbvideoin_h__
#define pyfbvideoin_h__
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
#include "pyfbimage.h"
#include "pyfbvideo.h"
#include "pyfbvideoclip.h"

// =======================================================================================
// FBVideoIn
// =======================================================================================
void FBVideoIn_Init();

class PYSDK_DLL FBVideoIn_Wrapper : public FBVideo_Wrapper {
public:
	FBVideoIn* mFBVideoIn;
public:
	FBVideoIn_Wrapper( FBComponent* pFBComponent ) : FBVideo_Wrapper( pFBComponent ) { mFBVideoIn = (FBVideoIn*)pFBComponent; }
	FBVideoIn_Wrapper(  ) : FBVideo_Wrapper( new FBVideoIn(  )) { mFBVideoIn = (FBVideoIn*)mFBComponent; }
	virtual ~FBVideoIn_Wrapper( ) { }
	void LiveSetCompressor( int pCompressorIndex ) { mFBVideoIn->LiveSetCompressor(pCompressorIndex); }
	int LiveGetCompressor(  ) { return mFBVideoIn->LiveGetCompressor(); }
	int LiveGetCompressorCount(  ) { return mFBVideoIn->LiveGetCompressorCount(); }
	const char* LiveGetCompressorName( int pCompressorIndex ) { return mFBVideoIn->LiveGetCompressorName(pCompressorIndex); }
	void LiveSetResolutionFR( int pIndex ) { mFBVideoIn->LiveSetResolutionFR(pIndex); }
	int LiveGetResolutionFR( ) { return mFBVideoIn->LiveGetResolutionFR(); }
	int LiveGetResolutionFRCount( ) { return mFBVideoIn->LiveGetResolutionFRCount(); }
	const char* LiveGetResolutionFRName( int pIndex ) { return mFBVideoIn->LiveGetResolutionFRName(pIndex); }
	FBVideoLiveType LiveGetType( ) { return mFBVideoIn->LiveGetType(); }
	bool GetOnline() { return mFBVideoIn->Online; }
	void SetOnline(bool pValue) { mFBVideoIn->Online = pValue; }
	bool GetRecord() { return mFBVideoIn->Recording; }
	void SetRecord(bool pValue) { mFBVideoIn->Recording = pValue; }
	bool GetRecordAudio() { return mFBVideoIn->RecordAudio; }
	void SetRecordAudio(bool pValue) { mFBVideoIn->RecordAudio = pValue; }
	const char* GetFilePath() { return mFBVideoIn->FilePath; }
	void SetFilePath(const char* pValue) { mFBVideoIn->FilePath = pValue; }
};
#endif // pyfbvideoin_h__