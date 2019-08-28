#ifndef pyfbfcurveeditor_h__
#define pyfbfcurveeditor_h__
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
#include "pyfbvisualcomponent.h"

// =======================================================================================
// FBFCurveEditor
// =======================================================================================
void FBFCurveEditor_Init();
class FBAnimationNode_Wrapper;
class PYSDK_DLL FBFCurveEditor_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBFCurveEditor* mFBFCurveEditor;
public:
	FBFCurveEditor_Wrapper( FBComponent* pFBComponent );
	FBFCurveEditor_Wrapper();
	virtual ~FBFCurveEditor_Wrapper( ) {  }
	void AddAnimationNode(FBAnimationNode_Wrapper& pAnimationNode) { mFBFCurveEditor->AddAnimationNode( pAnimationNode.mFBAnimationNode ); }
	void RemoveAnimationNode(FBAnimationNode_Wrapper& pAnimationNode) { mFBFCurveEditor->RemoveAnimationNode( pAnimationNode.mFBAnimationNode ); }    
	void AddProperty(FBPropertyAnimatable_Wrapper& pProperty) { mFBFCurveEditor->AddProperty((FBPropertyAnimatable*)pProperty.mFBProperty); }
	void Clear() { mFBFCurveEditor->Clear(); }    
}; 
#endif // pyfbfcurveeditor_h__