#ifndef pyfbmodelpath3d_h__
#define pyfbmodelpath3d_h__
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
#include "pyfbgeometry.h"
#include "pyfbmodel.h"

// =======================================================================================
// FBModelPath3D
// =======================================================================================
void FBModelPath3D_Init();

class PYSDK_DLL FBModelPath3D_Wrapper : public FBModel_Wrapper 
{
public:
	FBModelPath3D* mFBModelPath3D;

public:
	FBModelPath3D_Wrapper( FBComponent* pFBComponent ) : FBModel_Wrapper( pFBComponent ) { mFBModelPath3D = (FBModelPath3D*)pFBComponent; }
	FBModelPath3D_Wrapper( const char* pName ) : FBModel_Wrapper( new FBModelPath3D( pName )) { mFBModelPath3D = (FBModelPath3D*)mFBComponent; }
	virtual ~FBModelPath3D_Wrapper( ) { }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(PathLength,   double);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(PathLengthInString,   const char*);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PathLengthUnit,    FBModelPath3D::ELengthUnitType);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PathEndCapStyle,   FBModelPath3D::EPathEndCapStyle);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PathLengthShow,    bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PathEndCapScale,   double);    
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(TextScale,         double);
    DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(TextBackground, FBColorAndAlpha);
    void SetColor( FBColor_Wrapper& pColor ) { mFBModelPath3D->Color = *(pColor.mFBColor); }
    object GetColor(  ) { return WrapFBObject<FBPropertyAnimatableColor_Wrapper,FBPropertyAnimatableColor>( &mFBModelPath3D->Color ); }
	double ConvertSegmentPercentToTotalPercent(double pPercent) { return mFBModelPath3D->ConvertSegmentPercentToTotalPercent( pPercent ); }
	double ConvertToSegmentPercentFactor() { return mFBModelPath3D->ConvertToSegmentPercentFactor(  ); }
	double ConvertTotalPercentToSegmentPercent(double pPercent) { return mFBModelPath3D->ConvertTotalPercentToSegmentPercent( pPercent ); }
	double ConvertToTotalPercentFactor() { return mFBModelPath3D->ConvertToTotalPercentFactor(  ); }
	int GetSelectedPathKeyCount() { return mFBModelPath3D->GetSelectedPathKeyCount(  ); }
	int InsertNewEndKey() { return mFBModelPath3D->InsertNewEndKey(  ); }
	int InsertNewStartKey() { return mFBModelPath3D->InsertNewStartKey(  ); }
	void PathKeyClear() { mFBModelPath3D->PathKeyClear(  ); }
	int PathKeyEndAdd(FBVector4d_Wrapper& pTLocal) { return mFBModelPath3D->PathKeyEndAdd( *pTLocal.mFBVector4d ); }
	FBVector4d_Wrapper* PathKeyGet(int pKeyIndex) 
    { 
        ValidateIndexAccess( pKeyIndex, this, &FBModelPath3D_Wrapper::PathKeyGetCount );
        return FBVector4d_Wrapper_Factory( mFBModelPath3D->PathKeyGet( pKeyIndex )); 
    }
	int PathKeyGetCount() { return mFBModelPath3D->PathKeyGetCount(  ); }
    FBVector4d_Wrapper* PathKeyGetLeftTangent(int pKeyIndex) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->PathKeyGetLeftTangent( pKeyIndex )); }
    FBVector4d_Wrapper* PathKeyGetRightTangent(int pKeyIndex) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->PathKeyGetRightTangent( pKeyIndex )); }
	FBVector4d_Wrapper* PathKeyGetXYZDerivative(int pKeyIndex) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->PathKeyGetXYZDerivative( pKeyIndex )); }
	void PathKeyRemove(int pKeyIndex) { mFBModelPath3D->PathKeyRemove( pKeyIndex ); }
	void PathKeyRemoveSelected() { mFBModelPath3D->PathKeyRemoveSelected(); }
	void PathKeySet(int pKeyIndex, FBVector4d_Wrapper& pTLocal, bool pUpdate = true) { mFBModelPath3D->PathKeySet( pKeyIndex, *pTLocal.mFBVector4d, pUpdate ); }
    void PathKeySetLeftTangent(int pKeyIndex, FBVector4d_Wrapper& pTLocal, bool pUpdate = true) { mFBModelPath3D->PathKeySetLeftTangent( pKeyIndex, *pTLocal.mFBVector4d, pUpdate ); }
    void PathKeySetRightTangent(int pKeyIndex, FBVector4d_Wrapper& pTLocal, bool pUpdate = true) { mFBModelPath3D->PathKeySetRightTangent( pKeyIndex, *pTLocal.mFBVector4d, pUpdate ); }
    void PathKeySetLeftRightTangent(int pKeyIndex, FBVector4d_Wrapper& pTLocalKey, FBVector4d_Wrapper& pTLocalLeftKey, FBVector4d_Wrapper& pTLocalRightKey, bool pUpdate=true) {  mFBModelPath3D->PathKeySetLeftRightTangent(pKeyIndex,*pTLocalKey.mFBVector4d, *pTLocalLeftKey.mFBVector4d, *pTLocalRightKey.mFBVector4d, pUpdate); }
	void PathKeySetXDerivative(int pKeyIndex, double pDerivative, bool pUpdate) { mFBModelPath3D->PathKeySetXDerivative( pKeyIndex, pDerivative, pUpdate ); }
	void PathKeySetXYZDerivative(int pKeyIndex, FBVector4d_Wrapper& pDerivative, bool pUpdate) { mFBModelPath3D->PathKeySetXYZDerivative( pKeyIndex, *pDerivative.mFBVector4d, pUpdate ); }
	void PathKeySetYDerivative(int pKeyIndex, double pDerivative, bool pUpdate) { mFBModelPath3D->PathKeySetYDerivative( pKeyIndex, pDerivative, pUpdate ); }
	void PathKeySetZDerivative(int pKeyIndex, double pDerivative, bool pUpdate) { mFBModelPath3D->PathKeySetZDerivative( pKeyIndex, pDerivative, pUpdate ); }
	int PathKeyStartAdd(FBVector4d_Wrapper& pTLocal) { return mFBModelPath3D->PathKeyStartAdd( *pTLocal.mFBVector4d ); }
    double PathKeyGetLeftTangentLength(int pKeyIndex) { return mFBModelPath3D->PathKeyGetLeftTangentLength( pKeyIndex ); }
    double PathKeyGetRightTangentLength(int pKeyIndex) { return mFBModelPath3D->PathKeyGetRightTangentLength( pKeyIndex ); }
	FBVector4d_Wrapper* Segment_GlobalPathEvaluate(double pSegmentPercent) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->Segment_GlobalPathEvaluate( pSegmentPercent )); }
	FBVector4d_Wrapper* Segment_GlobalPathEvaluateDerivative(double pSegmentPercent) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->Segment_GlobalPathEvaluateDerivative( pSegmentPercent )); }
	int Segment_IsPathKey(double pSegmentPercent) { return mFBModelPath3D->Segment_IsPathKey( pSegmentPercent ); }
	FBVector4d_Wrapper* Segment_LocalPathEvaluate(double pSegmentPercent) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->Segment_LocalPathEvaluate( pSegmentPercent )); }
	FBVector4d_Wrapper* Segment_LocalPathEvaluateDerivative(double pSegmentPercent) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->Segment_LocalPathEvaluateDerivative( pSegmentPercent )); }
	int Segment_PathKeyAdd(double pSegmentPercent, FBVector4d_Wrapper& pTLocal) { return mFBModelPath3D->Segment_PathKeyAdd( pSegmentPercent, *pTLocal.mFBVector4d ); }
	void ShowCurveControls(bool pShow) { mFBModelPath3D->ShowCurveControls( pShow ); }
	void ShowCurvePoints(bool pShow) { mFBModelPath3D->ShowCurvePoints( pShow ); }
	FBVector4d_Wrapper* Total_GlobalPathEvaluate(double pTotalPercent) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->Total_GlobalPathEvaluate( pTotalPercent )); }
	FBVector4d_Wrapper* Total_GlobalPathEvaluateDerivative(double pTotalPercent) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->Total_GlobalPathEvaluateDerivative( pTotalPercent )); }
	int Total_IsPathKey(double pTotalPercent) { return mFBModelPath3D->Total_IsPathKey( pTotalPercent ); }
	FBVector4d_Wrapper* Total_LocalPathEvaluate(double pTotalPercent) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->Total_LocalPathEvaluate( pTotalPercent )); }
	FBVector4d_Wrapper* Total_LocalPathEvaluateDerivative(double pTotalPercent) { return FBVector4d_Wrapper_Factory( mFBModelPath3D->Total_LocalPathEvaluateDerivative( pTotalPercent )); }
	int Total_PathKeyAdd(double pTotalPercent, FBVector4d_Wrapper& pTLocal) { return mFBModelPath3D->Total_PathKeyAdd( pTotalPercent, *pTLocal.mFBVector4d ); }
};
#endif // pyfbmodelpath3d_h__