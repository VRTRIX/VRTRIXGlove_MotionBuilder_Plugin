#ifndef pyfbmodelmarker_h__
#define pyfbmodelmarker_h__
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

// =======================================================================================
// FBModelMarker
// =======================================================================================
void FBModelMarker_Init();

class PYSDK_DLL FBModelMarker_Wrapper : public FBModel_Wrapper {
public:
	FBModelMarker* mFBModelMarker;
public:
	FBModelMarker_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBModelMarker = (FBModelMarker*)pFBComponent; }
	FBModelMarker_Wrapper( const char* pName ) : FBModel_Wrapper( new FBModelMarker( pName )) { mFBModelMarker = (FBModelMarker*)mFBComponent; }
	virtual ~FBModelMarker_Wrapper( ) {}
	void SetColor( FBColor_Wrapper& pColor ) { mFBModelMarker->Color = *pColor.mFBColor; }
	FBColor_Wrapper* GetColor(  ) { return FBColor_Wrapper_Factory( mFBModelMarker->Color ); }
	void SetIKPivot( FBVector3d_Wrapper& pIKPivot ) { mFBModelMarker->IKPivot = *pIKPivot.mFBVector3d; }
	FBVector3d_Wrapper* GetIKPivot(  ) { return FBVector3d_Wrapper_Factory( mFBModelMarker->IKPivot ); }
	void SetLength( double pLength ) { mFBModelMarker->Length = pLength; }
	double GetLength(  ) { return mFBModelMarker->Length; }
	void SetLook( FBMarkerLook pLook ) { mFBModelMarker->Look = pLook; }
	FBMarkerLook GetLook(  ) { return mFBModelMarker->Look; }
	void SetType( FBMarkerType pType ) { mFBModelMarker->Type = pType; }
	FBMarkerType GetType(  ) { return mFBModelMarker->Type; }
	void SetResLevel( FBMarkerResolutionLevel pResLevel ) { mFBModelMarker->ResLevel = pResLevel; }
	FBMarkerResolutionLevel GetResLevel(  ) { return mFBModelMarker->ResLevel; }
	void SetSize( double pSize ) { mFBModelMarker->Size = pSize; }
	double GetSize(  ) { return mFBModelMarker->Size; }
};
#endif // pyfbmodelmarker_h__