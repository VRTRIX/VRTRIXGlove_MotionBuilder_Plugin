#ifndef pyfbnote_h__
#define pyfbnote_h__
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
// FBNote
// =======================================================================================
void FBNote_Init();

class PYSDK_DLL FBNote_Wrapper : public FBBox_Wrapper {
public:
	FBNote* mFBNote;
public:
	FBNote_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBNote = (FBNote*)pFBComponent; }
	FBNote_Wrapper( const char* pName ) : FBBox_Wrapper( new FBNote( pName )) { mFBNote = (FBNote*)mFBComponent; }
	virtual ~FBNote_Wrapper( ) {}
    bool Attach(FBComponent_Wrapper* pComp = NULL ) { return mFBNote->Attach( pComp ? pComp->mFBComponent : NULL ); }
    bool Detach(FBComponent_Wrapper* pComp = NULL ) { return mFBNote->Detach( pComp ? pComp->mFBComponent : NULL ); }
	void SetStaticComment( const char* pStaticComment ) { mFBNote->StaticComment = pStaticComment; }
	const char* GetStaticComment(  ) { return mFBNote->StaticComment; }
};
#endif // pyfbnote_h__