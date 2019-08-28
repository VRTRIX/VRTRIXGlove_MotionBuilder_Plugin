#ifndef pyfbvideoclipimage_h__
#define pyfbvideoclipimage_h__

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

#include "pyfbvideoclip.h"

// =======================================================================================
// FBVideoClipImage
// =======================================================================================
void FBVideoClipImage_Init();

class PYSDK_DLL FBVideoClipImage_Wrapper : public FBVideoClip_Wrapper {
public:
	FBVideoClipImage* mFBVideoClipImage;
public:
	FBVideoClipImage_Wrapper( FBComponent* pFBComponent ) : FBVideoClip_Wrapper( pFBComponent ) { mFBVideoClipImage = (FBVideoClipImage*)pFBComponent; }
	FBVideoClipImage_Wrapper( const char* pName ) : FBVideoClip_Wrapper( new FBVideoClipImage( pName )) { mFBVideoClipImage = (FBVideoClipImage*)mFBComponent; }
	virtual ~FBVideoClipImage_Wrapper( ) { }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ImageSequence,bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UseSystemFrameRate,bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(MaxMipMapResolution, FBVideoResolution);
};
#endif // pyfbvideoclipimage_h__