#ifndef pyfbcycleanalysis_h__
#define pyfbcycleanalysis_h__
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

//#include "fbsdk/fbcycleanalysisnode.h"
//class FBCycleAnalysisNode;

// =======================================================================================
// FBCycleAnalysisNode
// =======================================================================================
void FBCycleAnalysisNode_Init();

class PYSDK_DLL FBCycleAnalysisNode_Wrapper : public FBBox_Wrapper {
public:
    FBCycleAnalysisNode* mFBCycleAnalysisNode;
public:
    FBCycleAnalysisNode_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBCycleAnalysisNode = (FBCycleAnalysisNode*)pFBComponent; }
    FBCycleAnalysisNode_Wrapper( const char* pName ) : FBBox_Wrapper( new FBCycleAnalysisNode( pName )) { mFBCycleAnalysisNode = (FBCycleAnalysisNode*)mFBComponent; }
    virtual ~FBCycleAnalysisNode_Wrapper( ) { }
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBCycleAnalysisNode, RealTime, bool );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBCycleAnalysisNode, RootRMode, FBRootRMode );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBCycleAnalysisNode, RootHMode, FBRootHMode );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBCycleAnalysisNode, RootXZMode, FBRootXZMode );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBCycleAnalysisNode, RootSpeedMode, FBRootSpeedMode );
    object GetPoseFCurve() { return FBWrapperFactory::TheOne().WrapFBObject( mFBCycleAnalysisNode->GetPoseFCurve()); }
    object GetRootRFCurve() { return FBWrapperFactory::TheOne().WrapFBObject( mFBCycleAnalysisNode->GetRootRFCurve()); }
    object GetRootHFCurve() { return FBWrapperFactory::TheOne().WrapFBObject( mFBCycleAnalysisNode->GetRootHFCurve()); }
    object GetRootXZFCurve() { return FBWrapperFactory::TheOne().WrapFBObject( mFBCycleAnalysisNode->GetRootXZFCurve()); }
    object GetRootSpeedFCurve() { return FBWrapperFactory::TheOne().WrapFBObject( mFBCycleAnalysisNode->GetRootSpeedFCurve()); }

};
#endif // pyfbcycleanalysis_h__