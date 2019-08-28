#ifndef pyfbmath_h__
#define pyfbmath_h__
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

const double PYFBMat2EulerDegenerateForPrecision10 = 16.0e-10;     //Default precision since Mobu 2016 for converting rotation matrix to Euler vector

// =======================================================================================
// Math routines for vector and matrix manipulation
// =======================================================================================

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTIONS: 
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Globals Initializer
void FBMath_Init();

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Matrix
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBMatrixInverse FBMatrixTranspose FBMatrixMult FBVertexMatrixMult FBVectorMatrixMult
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBMatrixInverse_Wrapper( FBMatrix_Wrapper& pMatrix, FBMatrix_Wrapper& pSrc )
{
    FBMatrixInverse( *pMatrix.mFBMatrix, *pSrc.mFBMatrix ); 
}


PYSDK_DLL inline void FBMatrixTranspose_Wrapper( FBMatrix_Wrapper& pMatrix, FBMatrix_Wrapper& pSrc )
{
    FBMatrixTranspose( *pMatrix.mFBMatrix, *pSrc.mFBMatrix ); 
}

PYSDK_DLL inline void FBMatrixMult_Wrapper( FBMatrix_Wrapper& pMatrix, FBMatrix_Wrapper& pA, FBMatrix_Wrapper& pB )
{
    FBMatrixMult( *pMatrix.mFBMatrix, *pA.mFBMatrix, *pB.mFBMatrix ); 
}

PYSDK_DLL inline void FBVertexMatrixMult_Wrapper( FBVertex_Wrapper& pOutVertex, FBMatrix_Wrapper& pMatrix, FBVertex_Wrapper& pVertex )
{
    FBVertexMatrixMult( *pOutVertex.mFBVertex, *pMatrix.mFBMatrix, *pVertex.mFBVertex ); 
}

PYSDK_DLL inline void FBVectorMatrixMult_Wrapper( FBVector4d_Wrapper& pOutVector, FBMatrix_Wrapper& pMatrix, FBVector4d_Wrapper& pVector )
{
    FBVectorMatrixMult( *pOutVector.mFBVector4d, *pMatrix.mFBMatrix, *pVector.mFBVector4d ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// T,R,S to Matrix
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBTranslationToMatrix FBRotationToMatrix FBScalingToMatrix FBTRSToMatrix
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBTranslationToMatrix_Wrapper( FBMatrix_Wrapper& pMatrix, FBVector4d_Wrapper& pVector )
{
    FBTranslationToMatrix( *pMatrix.mFBMatrix, *pVector.mFBVector4d ); 
}

PYSDK_DLL inline void FBRotationToMatrix_Wrapper( FBMatrix_Wrapper& pMatrix, FBVector3d_Wrapper& pVector, FBRotationOrder pRotationOrder = kFBXYZ )
{
    FBRotationToMatrix( *pMatrix.mFBMatrix, *pVector.mFBVector3d, pRotationOrder ); 
}

PYSDK_DLL inline void FBScalingToMatrix_Wrapper( FBMatrix_Wrapper& pMatrix, FBSVector_Wrapper& pVector )
{
    FBScalingToMatrix( *pMatrix.mFBMatrix, *pVector.mFBSVector ); 
}

PYSDK_DLL inline void FBTRSToMatrix_Wrapper( FBMatrix_Wrapper& pMatrix, FBVector4d_Wrapper& pTVector, FBVector3d_Wrapper& pRVector, FBSVector_Wrapper& pSVector )
{
    FBTRSToMatrix( *pMatrix.mFBMatrix, *pTVector.mFBVector4d, *pRVector.mFBVector3d, *pSVector.mFBSVector ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Matrix to T,R,S
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBMatrixToTranslation FBMatrixToRotation FBMatrixToScaling FBMatrixToTRS
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBMatrixToTranslation_Wrapper( FBVector4d_Wrapper& pVector, FBMatrix_Wrapper& pMatrix )
{
	FBMatrixToTranslation( *pVector.mFBVector4d, *pMatrix.mFBMatrix ); 
}

PYSDK_DLL inline void FBMatrixToRotation_Wrapper( FBVector3d_Wrapper& pVector, FBMatrix_Wrapper& pMatrix, FBRotationOrder pRotationOrder = kFBXYZ )
{
	FBMatrixToRotation( *pVector.mFBVector3d, *pMatrix.mFBMatrix, pRotationOrder ); 
}

PYSDK_DLL inline void FBMatrixToRotationWithPrecision_Wrapper( FBVector3d_Wrapper& pVector, FBMatrix_Wrapper& pMatrix, FBRotationOrder pRotationOrder, double pPrecision = PYFBMat2EulerDegenerateForPrecision10 )
{
	FBMatrixToRotationWithPrecision( *pVector.mFBVector3d, *pMatrix.mFBMatrix, pRotationOrder, pPrecision ); 
}

PYSDK_DLL inline void FBMatrixToScaling_Wrapper( FBSVector_Wrapper& pVector, FBMatrix_Wrapper& pMatrix )
{
    FBMatrixToScaling( *pVector.mFBSVector, *pMatrix.mFBMatrix ); 
}

PYSDK_DLL inline void FBMatrixToTRS_Wrapper( FBVector4d_Wrapper& pTVector, FBVector3d_Wrapper& pRVector, FBSVector_Wrapper& pSVector, FBMatrix_Wrapper& pMatrix )
{
    FBMatrixToTRS( *pTVector.mFBVector4d, *pRVector.mFBVector3d, *pSVector.mFBSVector, *pMatrix.mFBMatrix ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Quaternion
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBRotationToQuaternion FBQuaternionToRotation
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBRotationToQuaternion_Wrapper( FBVector4d_Wrapper& pQuaternion, FBVector3d_Wrapper& pVector, FBRotationOrder pRotationOrder = kFBXYZ )
{
    FBRotationToQuaternion( *pQuaternion.mFBVector4d, *pVector.mFBVector3d, pRotationOrder ); 
}

PYSDK_DLL inline void FBQuaternionToRotation_Wrapper( FBVector3d_Wrapper& pVector, FBVector4d_Wrapper& pQuaternion, FBRotationOrder pRotationOrder = kFBXYZ )
{
    FBQuaternionToRotation( *pVector.mFBVector3d, *pQuaternion.mFBVector4d, pRotationOrder ); 
}

PYSDK_DLL inline void FBQuaternionToRotationWithPrecision_Wrapper( FBVector3d_Wrapper& pVector, FBVector4d_Wrapper& pQuaternion, FBRotationOrder pRotationOrder, int pPrecision)
{
    FBQuaternionToRotationWithPrecision( *pVector.mFBVector3d, *pQuaternion.mFBVector4d, pRotationOrder, pPrecision ); 
}

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBMatrixToQuaternion FBQuaternionToMatrix
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBMatrixToQuaternion_Wrapper( FBVector4d_Wrapper& pQuaternion, FBMatrix_Wrapper& pMatrix )
{
	FBMatrixToQuaternion( *pQuaternion.mFBVector4d, *pMatrix.mFBMatrix ); 
}

PYSDK_DLL inline void FBQuaternionToMatrix_Wrapper( FBMatrix_Wrapper& pMatrix, FBVector4d_Wrapper& pQuaternion )
{
	FBQuaternionToMatrix( *pMatrix.mFBMatrix, *pQuaternion.mFBVector4d ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Local/Global conversions
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetLocalMatrix FBGetGlobalMatrix FBMatrixOrthogonalize
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBGetLocalMatrix_Wrapper( FBMatrix_Wrapper& pMatrix, FBMatrix_Wrapper& pMatrixParent, FBMatrix_Wrapper& pMatrixChild )
{
    FBGetLocalMatrix( *pMatrix.mFBMatrix, *pMatrixParent.mFBMatrix, *pMatrixChild.mFBMatrix ); 
}

PYSDK_DLL inline void FBGetGlobalMatrix_Wrapper( FBMatrix_Wrapper& pMatrix, FBMatrix_Wrapper& pMatrixParent, FBMatrix_Wrapper& pLocalMatrix )
{
    FBGetGlobalMatrix( *pMatrix.mFBMatrix, *pMatrixParent.mFBMatrix, *pLocalMatrix.mFBMatrix ); 
}

PYSDK_DLL inline void FBMatrixOrthogonalize_Wrapper( FBMatrix_Wrapper& pMatrix )
{
    FBMatrixOrthogonalize( *pMatrix.mFBMatrix ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Vector operations
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAdd FBSub FBMult FBMult FBMult FBDot FBLength
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBAdd_Wrapper( FBVector4d_Wrapper& pResult, FBVector4d_Wrapper& pV1, FBVector4d_Wrapper& pV2 )
{
    FBAdd( *pResult.mFBVector4d, *pV1.mFBVector4d, *pV2.mFBVector4d ); 
}

PYSDK_DLL inline void FBSub_Wrapper( FBVector4d_Wrapper& pResult, FBVector4d_Wrapper& pV1, FBVector4d_Wrapper& pV2 )
{
    FBSub( *pResult.mFBVector4d, *pV1.mFBVector4d, *pV2.mFBVector4d ); 
}

PYSDK_DLL inline void FBMult_Wrapper( FBVector4d_Wrapper& pResult, FBVector4d_Wrapper& pV1, double pV2 )
{
    FBMult( *pResult.mFBVector4d, *pV1.mFBVector4d, pV2 ); 
}

PYSDK_DLL inline void FBMult_Wrapper( FBVector4d_Wrapper& pResult, FBVector4d_Wrapper& pV1, FBVector4d_Wrapper& pV2 )
{
    FBMult( *pResult.mFBVector4d, *pV1.mFBVector4d, *pV2.mFBVector4d ); 
}

PYSDK_DLL inline void FBMult_Wrapper( FBMatrix_Wrapper& pResult, FBMatrix_Wrapper& pM, FBSVector_Wrapper& pV )
{
    FBMult( *pResult.mFBMatrix, *pM.mFBMatrix, *pV.mFBSVector ); 
}

PYSDK_DLL inline double FBDot_Wrapper( FBVector4d_Wrapper& pV1, FBVector4d_Wrapper& pV2 )
{
    return FBDot( *pV1.mFBVector4d, *pV2.mFBVector4d ); 
}

PYSDK_DLL inline double FBLength_Wrapper( FBVector4d_Wrapper& pV )
{
    return FBLength( *pV.mFBVector4d ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Quaternion operations
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBQAdd FBQSub FBQMult FBQMult FBQDot FBQLength
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBQAdd_Wrapper( FBVector4d_Wrapper& pResult, const FBVector4d_Wrapper& pQ1, const FBVector4d_Wrapper& pQ2 )
{
    FBQAdd( *pResult.mFBVector4d, *pQ1.mFBVector4d, *pQ2.mFBVector4d ); 
}

PYSDK_DLL inline void FBQSub_Wrapper( FBVector4d_Wrapper& pResult, const FBVector4d_Wrapper& pQ1, const FBVector4d_Wrapper& pQ2 )
{
    FBQSub( *pResult.mFBVector4d, *pQ1.mFBVector4d, *pQ2.mFBVector4d ); 
}

PYSDK_DLL inline void FBQMult_Wrapper( FBVector4d_Wrapper& pResult, const FBVector4d_Wrapper& pQ1, double pQ2 )
{
    FBQMult( *pResult.mFBVector4d, *pQ1.mFBVector4d, pQ2 ); 
}

PYSDK_DLL inline void FBQMult_Wrapper( FBVector4d_Wrapper& pResult, const FBVector4d_Wrapper& pQ1, const FBVector4d_Wrapper& pQ2 )
{
    FBQMult( *pResult.mFBVector4d, *pQ1.mFBVector4d, *pQ2.mFBVector4d ); 
}

PYSDK_DLL inline double FBQDot_Wrapper( const FBVector4d_Wrapper& pQ1, const FBVector4d_Wrapper& pQ2 )
{
    return FBQDot( *pQ1.mFBVector4d, *pQ2.mFBVector4d ); 
}

PYSDK_DLL inline double FBQLength_Wrapper( const FBVector4d_Wrapper& pQ )
{
    return FBQLength( *pQ.mFBVector4d ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Vertex operations
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBLength
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline double FBLength_Wrapper( FBVertex_Wrapper& pQ )
{
    return FBLength( *pQ.mFBVertex ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Rotation utilities
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBInterpolateRotation FBInterpolateRotation FBGetContinuousRotation
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBInterpolateRotation_Wrapper( FBVector3d_Wrapper& pROut, const FBVector3d_Wrapper& pR0, const FBVector3d_Wrapper& pR1, double pU )
{
    FBInterpolateRotation( *pROut.mFBVector3d, *pR0.mFBVector3d, *pR1.mFBVector3d, pU ); 
}

PYSDK_DLL inline void FBInterpolateRotation_Wrapper( FBVector4d_Wrapper& pQOut, const FBVector4d_Wrapper& pQ0, const FBVector4d_Wrapper& pQ1, double pU )
{
    FBInterpolateRotation( *pQOut.mFBVector4d, *pQ0.mFBVector4d, *pQ1.mFBVector4d, pU ); 
}

PYSDK_DLL inline void FBGetContinuousRotation_Wrapper( FBVector3d_Wrapper& pROut, FBVector3d_Wrapper& pR0, FBVector3d_Wrapper& pR1 )
{
    FBGetContinuousRotation( *pROut.mFBVector3d, *pR0.mFBVector3d, *pR1.mFBVector3d ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Miscellaneous utilities
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBClamp FBBigEndianToNative FBLittleEndianToNative
//
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline double FBClamp_Wrapper( double pV, double pL, double pH )
{
    return FBClamp( pV, pL, pH ); 
}
#endif // pyfbmath_h__