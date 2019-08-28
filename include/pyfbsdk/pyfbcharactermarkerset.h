#ifndef pyfbcharactermarkerset_h__
#define pyfbcharactermarkerset_h__
/**************************************************************************
 Copyright 2012 Autodesk, Inc.
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
#include "pyfbplotoptions.h"
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbpose.h"
#include "pyfbconstraint.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"

// =======================================================================================
// FBMarkerSet
// =======================================================================================
void FBCharacterMarkerSet_Init();

class PYSDK_DLL FBCharacterMarkerSet_Wrapper : public FBComponent_Wrapper {
public:
	FBCharacterMarkerSet* mFBCharacterMarkerSet;
public:
	FBCharacterMarkerSet_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBCharacterMarkerSet = (FBCharacterMarkerSet*)pFBComponent; }
	FBCharacterMarkerSet_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBCharacterMarkerSet( pName )) { mFBCharacterMarkerSet = (FBCharacterMarkerSet*)mFBComponent; }

	object GetMarkersProperty(FBBodyNodeId pBodyNodeId){ return FBProperty_Wrapper_Factory( mFBCharacterMarkerSet->GetMarkersProperty( pBodyNodeId )); }
	object GetExtractionProperty(FBBodyNodeId pBodyNodeId){ return FBProperty_Wrapper_Factory( mFBCharacterMarkerSet->GetExtractionProperty( pBodyNodeId )); }
	object GetSnapProperty(FBBodyNodeId pBodyNodeId, FBModelTransformationType pWhat){ return FBProperty_Wrapper_Factory( mFBCharacterMarkerSet->GetSnapProperty( pBodyNodeId, pWhat )); }
};
#endif // pyfbmarkerset_h__