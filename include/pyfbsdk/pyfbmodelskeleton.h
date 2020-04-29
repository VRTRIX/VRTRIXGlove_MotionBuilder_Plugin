#ifndef pyfbmodelskeleton_h__
#define pyfbmodelskeleton_h__
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
#include "pyfbboxplaceholder.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbmodelplaceholder.h"
#include "pyfbmodeltemplate.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelnull.h"
#include "pyfbmodelplane.h"
#include "pyfbmodelroot.h"
#include "pyfbarraytemplate.h"

// =======================================================================================
// FBModelSkeleton
// =======================================================================================
void FBModelSkeleton_Init();

class PYSDK_DLL FBModelSkeleton_Wrapper : public FBModel_Wrapper {
public:
	FBModelSkeleton* mFBModelSkeleton;
public:
	FBModelSkeleton_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBModelSkeleton = (FBModelSkeleton*)pFBComponent; }
	FBModelSkeleton_Wrapper( const char* pName ) : FBModel_Wrapper( new FBModelSkeleton( pName )) { mFBModelSkeleton = (FBModelSkeleton*)mFBComponent; }
	virtual ~FBModelSkeleton_Wrapper( ) {}
	void SetColor( FBColor_Wrapper& pColor ) { mFBModelSkeleton->Color = *pColor.mFBColor; }
	FBColor_Wrapper* GetColor(  ) { return FBColor_Wrapper_Factory( mFBModelSkeleton->Color ); }
	void SetSize( double pSize ) { mFBModelSkeleton->Size = pSize; }
	double GetSize(  ) { return mFBModelSkeleton->Size; }
    void GetSkinModelList(FBModelList_Wrapper& pFBSkinModelList) { mFBModelSkeleton->GetSkinModelList( *(pFBSkinModelList.mFBModelList) ); }
	FBSkeletonLook GetLook( ) { return mFBModelSkeleton->Look; }
	void SetLook( FBSkeletonLook pLook ) { mFBModelSkeleton->Look = pLook; }
	FBSkeletonResolutionLevel GetResolution( ) { return mFBModelSkeleton->Resolution; }
	void SetResolution( FBSkeletonResolutionLevel pResolution ) { mFBModelSkeleton->Resolution = pResolution; }
	double GetLength( ) { return mFBModelSkeleton->Length; }
	void SetLength( double pLength ) { mFBModelSkeleton->Length = pLength; }
	bool GetLinkFollowGeometryOffset( ) { return mFBModelSkeleton->LinkFollowGeometryOffset; }
	void SetLinkFollowGeometryOffset( bool pFollow ) { mFBModelSkeleton->LinkFollowGeometryOffset = pFollow; }
	bool GetPreserveLinkEndPosition( ) { return mFBModelSkeleton->PreserveLinkEndPosition; }
	void SetPreserveLinkEndPosition( bool pPreserve ) { mFBModelSkeleton->PreserveLinkEndPosition = pPreserve; }
};
#endif // pyfbmodelskeleton_h__