#ifndef pyfbfcurve_h__
#define pyfbfcurve_h__
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

// =======================================================================================
// FBFCurve
// =======================================================================================
void FBFCurve_Init();

class PYSDK_DLL FBFCurve_Wrapper : public FBComponent_Wrapper {
public:
	FBFCurve* mFBFCurve;
public:
	FBFCurve_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBFCurve = (FBFCurve*)pFBComponent; }
	FBFCurve_Wrapper( ) : FBComponent_Wrapper( new FBFCurve( )) { mFBFCurve = (FBFCurve*)mFBComponent; }
	virtual ~FBFCurve_Wrapper( ) {}
	void EditBegin(int pKeyCount = -1) { mFBFCurve->EditBegin( pKeyCount ); }
	void EditClear() { mFBFCurve->EditClear(  ); }
	void EditEnd(int pKeyCount = -1) { mFBFCurve->EditEnd( pKeyCount ); }
	int	 KeyAdd(FBTime_Wrapper& pTime, double pValue) { return mFBFCurve->KeyAdd( *(pTime.mFBTime), pValue ); }
	void KeyInsert(FBTime_Wrapper& pTime, FBInterpolation pInterpolation = kFBInterpolationCubic, FBTangentMode pTangentMode = kFBTangentModeAuto) { mFBFCurve->KeyInsert( *pTime.mFBTime, pInterpolation, pTangentMode ); }
	bool KeyRemove(int pIndex) { return mFBFCurve->KeyRemove( pIndex ); }
	bool KeyDeleteByIndexRange(int pStartIndex, int pStopIndex) { return mFBFCurve->KeyDelete(pStartIndex, pStopIndex); }
	bool KeyDeleteByTimeRange(FBTime_Wrapper& pStartTime, FBTime_Wrapper& pStopTime, bool pInclusive = true){ return mFBFCurve->KeyDelete(*pStartTime.mFBTime, *pStopTime.mFBTime, pInclusive); }
	void KeyReplaceBy( FBFCurve_Wrapper& pSource, FBTime_Wrapper& pStart = FBTime_Wrapper::MinusInfinity, FBTime_Wrapper& pStop = FBTime_Wrapper::Infinity, bool pUseExactGivenSpan = false, bool pKeyStartEndOnNoKey = true ){ mFBFCurve->KeyReplaceBy(*pSource.mFBFCurve, *pStart.mFBTime, *pStop.mFBTime, pUseExactGivenSpan, pKeyStartEndOnNoKey); }
	
	bool KeyOffsetByIndexRange
	(
		FBTime_Wrapper& pOffsetTime,
		int				pStartIndex,
		int				pStopIndex
	)
	{
		return mFBFCurve->KeyOffset( *pOffsetTime.mFBTime, pStartIndex, pStopIndex );
	}

	bool KeyOffsetByTimeRange
	(
		FBTime_Wrapper& pOffsetTime,
		FBTime_Wrapper& pStartTime = FBTime_Wrapper::MinusInfinity,
		FBTime_Wrapper& pStopTime = FBTime_Wrapper::Infinity,
		bool			pInclusive = true
	)
	{
		return mFBFCurve->KeyOffset( *pOffsetTime.mFBTime, *pStartTime.mFBTime, *pStopTime.mFBTime, pInclusive );
	}

	float Evaluate(FBTime_Wrapper& pTime) { return mFBFCurve->Evaluate( *(pTime.mFBTime) ); }
    FBExtrapolationMode GetPostExtrapolationMode() {return mFBFCurve->GetPostExtrapolationMode(); }
    void SetPostExtrapolationMode(FBExtrapolationMode pExtrapolationMode) {return mFBFCurve->SetPostExtrapolationMode( pExtrapolationMode ); }
	int GetPostExtrapolationCount() {return mFBFCurve->GetPostExtrapolationCount();}
    void SetPostExtrapolationCount(int pCount) {return mFBFCurve->SetPostExtrapolationCount(pCount);}
    FBExtrapolationMode GetPreExtrapolationMode() {return mFBFCurve->GetPreExtrapolationMode(); }
    void SetPreExtrapolationMode(FBExtrapolationMode pExtrapolationMode) {return mFBFCurve->SetPreExtrapolationMode( pExtrapolationMode ); }
    int GetPreExtrapolationCount() {return mFBFCurve->GetPreExtrapolationCount();}
    void SetPreExtrapolationCount(int pCount) {return mFBFCurve->SetPreExtrapolationCount(pCount);}
	object CreateInterpolatorCurve(FBInterpolatorCurveType pCurveType) { return FBWrapperFactory::TheOne().WrapFBObject( mFBFCurve->CreateInterpolatorCurve( pCurveType )); }
	object GetKeys(  ) { return FBPropertyListFCurveKey_Wrapper_Factory( mFBFCurve->Keys ); }
	float KeyGetValue(int pIndex) { return mFBFCurve->KeyGetValue( pIndex ); }
	void KeySetValue(int pIndex, float pValue) { mFBFCurve->KeySetValue( pIndex, pValue ); }
	float KeyGetLeftDerivative(int pIndex) { return mFBFCurve->KeyGetLeftDerivative( pIndex ); }
	void KeySetLeftDerivative(int pIndex, float pValue) { mFBFCurve->KeySetLeftDerivative( pIndex, pValue ); }
	float KeyGetRightDerivative(int pIndex) { return mFBFCurve->KeyGetRightDerivative( pIndex ); }
	void KeySetRightDerivative(int pIndex, float pValue) { mFBFCurve->KeySetRightDerivative( pIndex, pValue ); }
	float KeyGetLeftTangentWeight(int pIndex) { return mFBFCurve->KeyGetLeftTangentWeight( pIndex ); }
	void KeySetLeftTangentWeight(int pIndex, float pValue) { mFBFCurve->KeySetLeftTangentWeight( pIndex, pValue ); }
	float KeyGetRightTangentWeight(int pIndex) { return mFBFCurve->KeyGetRightTangentWeight( pIndex ); }
	void KeySetRightTangentWeight(int pIndex, float pValue) { mFBFCurve->KeySetRightTangentWeight( pIndex, pValue ); }
	float KeyGetLeftBezierTangent(int pIndex) { return mFBFCurve->KeyGetLeftBezierTangent( pIndex ); }
	void KeySetLeftBezierTangent(int pIndex, float pValue) { mFBFCurve->KeySetLeftBezierTangent( pIndex, pValue ); }
	float KeyGetRightBezierTangent(int pIndex) { return mFBFCurve->KeyGetRightBezierTangent( pIndex ); }
	void KeySetRightBezierTangent(int pIndex, float pValue) { mFBFCurve->KeySetRightBezierTangent( pIndex, pValue ); }
	float KeyGetTCBTension(int pIndex) { return mFBFCurve->KeyGetTCBTension( pIndex ); }
	void KeySetTCBTension(int pIndex, float pValue) { mFBFCurve->KeySetTCBTension( pIndex, pValue ); }
	float KeyGetTCBContinuity(int pIndex) { return mFBFCurve->KeyGetTCBContinuity( pIndex ); }
	void KeySetTCBContinuity(int pIndex, float pValue) { mFBFCurve->KeySetTCBContinuity( pIndex, pValue ); }
	float KeyGetTCBBias(int pIndex) { return mFBFCurve->KeyGetTCBBias( pIndex ); }
	void KeySetTCBBias(int pIndex, float pValue) { mFBFCurve->KeySetTCBBias( pIndex, pValue ); }
	FBTime_Wrapper* KeyGetTime(int pIndex) { return FBTime_Wrapper_Factory( mFBFCurve->KeyGetTime( pIndex )); }
	void KeySetTime(int pIndex, FBTime_Wrapper& pTime) { mFBFCurve->KeySetTime( pIndex, *pTime.mFBTime ); }
	FBInterpolation KeyGetInterpolation(int pIndex) { return mFBFCurve->KeyGetInterpolation( pIndex ); }
	void KeySetInterpolation(int pIndex, FBInterpolation pValue) { mFBFCurve->KeySetInterpolation( pIndex, pValue ); }
	FBTangentMode KeyGetTangentMode(int pIndex) { return mFBFCurve->KeyGetTangentMode( pIndex ); }
	void KeySetTangentMode(int pIndex, FBTangentMode pValue) { mFBFCurve->KeySetTangentMode( pIndex, pValue ); }
	FBTangentClampMode KeyGetTangentClampMode(int pIndex) { return mFBFCurve->KeyGetTangentClampMode( pIndex ); }
	void KeySetTangentClampMode(int pIndex, FBTangentClampMode pValue) { mFBFCurve->KeySetTangentClampMode( pIndex, pValue ); }
	bool KeyGetTangentBreak(int pIndex) { return mFBFCurve->KeyGetTangentBreak( pIndex ); }
	void KeySetTangentBreak(int pIndex, bool pValue) { mFBFCurve->KeySetTangentBreak( pIndex, pValue ); }
	FBTangentConstantMode KeyGetTangentConstantMode(int pIndex) { return mFBFCurve->KeyGetTangentConstantMode( pIndex ); }
	void KeySetTangentConstantMode(int pIndex, FBTangentConstantMode pValue) { mFBFCurve->KeySetTangentConstantMode( pIndex, pValue ); }
	FBTangentCustomIndex KeyGetTangentCustomIndex(int pIndex) { return mFBFCurve->KeyGetTangentCustomIndex( pIndex ); }
	void KeySetTangentCustomIndex(int pIndex, FBTangentCustomIndex pValue) { mFBFCurve->KeySetTangentCustomIndex( pIndex, pValue ); }
	FBTangentWeightMode KeyGetTangentWeightMode(int pIndex) { return mFBFCurve->KeyGetTangentWeightMode( pIndex ); }
	void KeySetTangentWeightMode(int pIndex, FBTangentWeightMode pValue) { mFBFCurve->KeySetTangentWeightMode( pIndex, pValue ); }
	bool KeyGetSelected(int pIndex) { return mFBFCurve->KeyGetSelected( pIndex ); }
	bool KeySetSelected(int pIndex, bool pValue) { return mFBFCurve->KeySetSelected( pIndex, pValue ); }
	bool KeyGetMarkedForManipulation(int pIndex) { return mFBFCurve->KeyGetMarkedForManipulation( pIndex ); }
	bool KeySetMarkedForManipulation(int pIndex, bool pValue) { return mFBFCurve->KeySetMarkedForManipulation( pIndex, pValue ); }
};
#endif // pyfbfcurve_h__