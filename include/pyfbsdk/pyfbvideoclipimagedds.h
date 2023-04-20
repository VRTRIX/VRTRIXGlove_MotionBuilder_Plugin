#ifndef pyfbvideoclipimagedds_h__
#define pyfbvideoclipimagedds_h__

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

#include "pyfbvideoclipimage.h"

// =======================================================================================
// FBVideoClipImageDDS
// =======================================================================================
void FBVideoClipImageDDS_Init();

class PYSDK_DLL FBVideoClipImageDDS_Wrapper : public FBVideoClipImage_Wrapper {
public:
	FBVideoClipImageDDS* mFBVideoClipImageDDS;
public:
	FBVideoClipImageDDS_Wrapper( FBComponent* pFBComponent ) : FBVideoClipImage_Wrapper( pFBComponent ) { mFBVideoClipImageDDS = (FBVideoClipImageDDS*)pFBComponent; }
	FBVideoClipImageDDS_Wrapper( const char* pName ) : FBVideoClipImage_Wrapper( new FBVideoClipImageDDS( pName ) ) { mFBVideoClipImageDDS = (FBVideoClipImageDDS*)mFBComponent; }
	virtual ~FBVideoClipImageDDS_Wrapper() { }
};
#endif // pyfbvideoclipimagedds_h__