#ifndef pyfbimage_h__
#define pyfbimage_h__
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
// FBImage
// =======================================================================================
void FBImage_Init();

class PYSDK_DLL FBImage_Wrapper : public FBComponent_Wrapper {
public:
	FBImage* mFBImage;
public:
	FBImage_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBImage = (FBImage*)pFBComponent; }
	FBImage_Wrapper( const char* pFileName ) : FBComponent_Wrapper( new FBImage( pFileName )) { mFBImage = (FBImage*)mFBComponent; SetAllocated(); }

	virtual ~FBImage_Wrapper( ) { }
	void Cleanup() { mFBImage->Cleanup(  ); }
	bool ConvertFormat(FBImageFormat pNewFormat) { return mFBImage->ConvertFormat( pNewFormat ); }
	bool ConvertSize(int pWidth, int pHeight) { return mFBImage->ConvertSize( pWidth, pHeight ); }
	void FBDelete() { mFBImage->FBDelete(  ); }
	kReference GetBufferAddress() { return (kReference)mFBImage->GetBufferAddress(); }
	bool Init(FBImageFormat pFormat, int pWidth, int pHeight) { return mFBImage->Init( pFormat, pWidth, pHeight ); }
	bool IsCompressedTif(const char * pFileName) { return mFBImage->IsCompressedTif( pFileName ); }
	void VerticalFlip() { mFBImage->VerticalFlip(  ); }
	bool WriteToTif(const char * pFileName, const char * pComments, bool pCompressed) { return mFBImage->WriteToTif( pFileName, pComments, pCompressed ); }
	void SetDepth( int pDepth ) { mFBImage->Depth = pDepth; }
	int GetDepth(  ) { return mFBImage->Depth; }
	void SetFormat( FBImageFormat pFormat ) { mFBImage->Format = pFormat; }
	FBImageFormat GetFormat(  ) { return mFBImage->Format; }
	void SetHeight( int pHeight ) { mFBImage->Height = pHeight; }
	int GetHeight(  ) { return mFBImage->Height; }
	FBImageInterleaveType GetInterleaveType(  ) { return mFBImage->InterleaveType; }
	FBImageInterpolationType GetInterpolationType(  ) { return mFBImage->InterpolationType; }
	FBImageType GetType(  ) { return mFBImage->Type; }
	void SetWidth( int pWidth ) { mFBImage->Width = pWidth; }
	int GetWidth(  ) { return mFBImage->Width; }
};
#endif // pyfbimage_h__