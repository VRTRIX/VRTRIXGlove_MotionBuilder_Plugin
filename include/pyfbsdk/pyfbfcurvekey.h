#ifndef pyfbfcurvekey_h__
#define pyfbfcurvekey_h__
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
// FBFCurveKey
// =======================================================================================
void FBFCurveKey_Init();

PYSDK_DLL FBFCurveKey_Wrapper* FBFCurveKey_Wrapper_Factory( const FBFCurveKey& pFBFCurveKey );
class PYSDK_DLL FBFCurveKey_Wrapper {
public:
    FBFCurveKey* mFBFCurveKey;
public:
    FBFCurveKey_Wrapper( const FBFCurveKey& pFBFCurveKey ) { mFBFCurveKey = new FBFCurveKey( pFBFCurveKey ); }
    FBFCurveKey_Wrapper() : mFBFCurveKey( new FBFCurveKey( NULL, 1 ) ) {}
    virtual ~FBFCurveKey_Wrapper( ) { delete mFBFCurveKey; }
    void SetBias( float pBias ) { mFBFCurveKey->Bias = pBias; }
    float GetBias(  ) { return mFBFCurveKey->Bias; }
    void SetContinuity( float pContinuity ) { mFBFCurveKey->Continuity = pContinuity; }
    float GetContinuity(  ) { return mFBFCurveKey->Continuity; }
    void SetInterpolation( FBInterpolation pInterpolation ) { mFBFCurveKey->Interpolation = pInterpolation; }
    FBInterpolation GetInterpolation(  ) { return mFBFCurveKey->Interpolation; }
    void SetLeftDerivative( float pLeftDerivative ) { mFBFCurveKey->LeftDerivative = pLeftDerivative; }
    float GetLeftDerivative(  ) { return mFBFCurveKey->LeftDerivative; }
    void SetRightDerivative( float pRightDerivative ) { mFBFCurveKey->RightDerivative = pRightDerivative; }
    float GetRightDerivative(  ) { return mFBFCurveKey->RightDerivative; }
    void SetLeftTangentWeight( float pLeftTangentWeight ) { mFBFCurveKey->LeftTangentWeight = pLeftTangentWeight; }
    float GetLeftTangentWeight(  ) { return mFBFCurveKey->LeftTangentWeight; }
    void SetRightTangentWeight( float pRightTangentWeight ) { mFBFCurveKey->RightTangentWeight = pRightTangentWeight; }
    float GetRightTangentWeight(  ) { return mFBFCurveKey->RightTangentWeight; }
    void SetLeftBezierTangent( float pLeftBezierTangent ) { mFBFCurveKey->LeftBezierTangent = pLeftBezierTangent; }
    float GetLeftBezierTangent(  ) { return mFBFCurveKey->LeftBezierTangent; }
    void SetRightBezierTangent( float pRightBezierTangent ) { mFBFCurveKey->RightBezierTangent = pRightBezierTangent; }
    float GetRightBezierTangent(  ) { return mFBFCurveKey->RightBezierTangent; }
    void SetTangentMode( FBTangentMode pTangentMode ) { mFBFCurveKey->TangentMode = pTangentMode; }
    FBTangentMode GetTangentMode(  ) { return mFBFCurveKey->TangentMode; }
    void SetTangentClampMode( FBTangentClampMode pTangentClampMode ) { mFBFCurveKey->TangentClampMode = pTangentClampMode; }
    FBTangentClampMode GetTangentClampMode(  ) { return mFBFCurveKey->TangentClampMode; }
    void SetTangentBreak( bool pTangentBreak) { mFBFCurveKey->TangentBreak = pTangentBreak; }
    bool GetTangentBreak( ) { return mFBFCurveKey->TangentBreak; }
    void SetTangentConstantMode( FBTangentConstantMode pTangentConstantMode ) { mFBFCurveKey->TangentConstantMode = pTangentConstantMode; }
    FBTangentConstantMode GetTangentConstantMode(  ) { return mFBFCurveKey->TangentConstantMode; }
    void SetSelected( bool pSelected) { mFBFCurveKey->Selected = pSelected; }
    bool GetSelected( ) { return mFBFCurveKey->Selected; }
    void SetMarkedForManipulation( bool pMarked) { mFBFCurveKey->MarkedForManipulation = pMarked; }
    bool GetMarkedForManipulation( ) { return mFBFCurveKey->MarkedForManipulation; }
    void SetTension( float pTension ) { mFBFCurveKey->Tension = pTension; }
    float GetTension(  ) { return mFBFCurveKey->Tension; }
    void SetTime( FBTime_Wrapper& pTime ) { mFBFCurveKey->Time = *pTime.mFBTime; }
    FBTime_Wrapper* GetTime(  ) { return FBTime_Wrapper_Factory( mFBFCurveKey->Time ); }
    void SetValue( float pValue ) { mFBFCurveKey->Value = pValue; }
    float GetValue(  ) { return mFBFCurveKey->Value; }
};

PYSDK_DLL inline FBFCurveKey_Wrapper* FBFCurveKey_Wrapper_Factory( const FBFCurveKey& pFBFCurveKey )
{
    return new FBFCurveKey_Wrapper( pFBFCurveKey );
}
#endif // pyfbfcurvekey_h__

