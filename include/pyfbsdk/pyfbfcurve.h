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
	float Evaluate(FBTime_Wrapper& pTime) { return mFBFCurve->Evaluate( *(pTime.mFBTime) ); }
    FBExtrapolationMode GetPostExtrapolationMode() {return mFBFCurve->GetPostExtrapolationMode(); }
    void SetPostExtrapolationMode(FBExtrapolationMode pExtrapolationMode) {return mFBFCurve->SetPostExtrapolationMode( pExtrapolationMode ); }
    long GetPostExtrapolationCount() {return mFBFCurve->GetPostExtrapolationCount();}
    void SetPostExtrapolationCount(int pCount) {return mFBFCurve->SetPostExtrapolationCount(pCount);}
    FBExtrapolationMode GetPreExtrapolationMode() {return mFBFCurve->GetPreExtrapolationMode(); }
    void SetPreExtrapolationMode(FBExtrapolationMode pExtrapolationMode) {return mFBFCurve->SetPreExtrapolationMode( pExtrapolationMode ); }
    long GetPreExtrapolationCount() {return mFBFCurve->GetPreExtrapolationCount();}
    void SetPreExtrapolationCount(int pCount) {return mFBFCurve->SetPreExtrapolationCount(pCount);}
	object CreateInterpolatorCurve(FBInterpolatorCurveType pCurveType) { return FBWrapperFactory::TheOne().WrapFBObject( mFBFCurve->CreateInterpolatorCurve( pCurveType )); }
	object GetKeys(  ) { return FBPropertyListFCurveKey_Wrapper_Factory( mFBFCurve->Keys ); }
};
#endif // pyfbfcurve_h__