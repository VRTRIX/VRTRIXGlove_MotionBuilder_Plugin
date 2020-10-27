#ifndef __FBMATH_H__
#define __FBMATH_H__
/**************************************************************************
 Copyright (c) 1994 - 2009 Autodesk, Inc. and/or its licensors.
 All Rights Reserved.
 
 The coded instructions, statements, computer programs, and/or related 
 material (collectively the "Data") in these files contain unpublished 
 information proprietary to Autodesk, Inc. and/or its licensors, which is 
 protected by Canada and United States of America federal copyright law 
 and by international treaties.
 
 The Data may not be disclosed or distributed to third parties, in whole 
 or in part, without the prior written consent of Autodesk, Inc. 
 ("Autodesk").
 
 THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
 ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO 
 WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR 
 ARISING BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES 
 OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 PURPOSE OR USE. WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT 
 WARRANT THAT THE OPERATION OF THE DATA WILL BE UNINTERRUPTED OR ERROR 
 FREE.
 
 IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS 
 OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR 
 EXPENSES OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE 
 DAMAGES OR OTHER SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS 
 OF PROFITS, REVENUE OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR 
 DAMAGES OF ANY KIND), HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF 
 LIABILITY, WHETHER DERIVED FROM CONTRACT, TORT (INCLUDING, BUT NOT 
 LIMITED TO, NEGLIGENCE), OR OTHERWISE, ARISING OUT OF OR RELATING TO THE 
 DATA OR ITS USE OR ANY OTHER PERFORMANCE, WHETHER OR NOT AUTODESK HAS 
 BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS OR DAMAGE.
 
**************************************************************************/

/**	\file fbmath.h
*	Contains routines for vector and matrix manipulation.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbtypes.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

const double FBMat2EulerDegenerateForPrecision10 = 16.0e-10;     //Default precision since Mobu 2016 for converting rotation matrix to Euler vector

//! Specify the Euler rotation order.
enum FBRotationOrder { 
	kFBXYZ,		//!< XYZ  
    kFBXZY,     //!< XZY 
    kFBYXZ,     //!< YXZ 
	kFBYZX,		//!< YZX 	
	kFBZXY,		//!< ZXY 	
    kFBZYX,     //!< ZYX
};

FB_DEFINE_ENUM( FBSDK_DLL, RotationOrder ); 

////////////////////////////////////////////////////////////////////////////////////
// Matrix
////////////////////////////////////////////////////////////////////////////////////
/**	Invert a matrix.
*	\retval	pMatrix	Calculated inverse matrix.
*	\param	pSrc	Source matrix to invert.
*/
FBSDK_DLL void FBMatrixInverse (FBMatrix  &pMatrix, const FBMatrix  &pSrc);

/**	Transpose a matrix.
*	\retval	pMatrix	Calculated transpose matrix.
*	\param	pSrc	Source matrix to transpose.
*/
FBSDK_DLL void FBMatrixTranspose (FBMatrix  &pMatrix, const FBMatrix  &pSrc);

/**	Multiply two matrices.
*	\retval	pMatrix	Calculated resulting matrix.
*	\param	pA		1st matrix.
*	\param	pB		2nd matrix.
*/
FBSDK_DLL void FBMatrixMult	(FBMatrix  &pMatrix, const FBMatrix  &pA, const FBMatrix  &pB);

/** Multiply a vertex by a matrix.
*	\retval	pOutVertex	Resulting vertex.
*	\param	pMatrix		Matrix to affect the vertex with.
*	\param	pVertex		Source vertex.
*/
FBSDK_DLL void FBVertexMatrixMult( FBVertex &pOutVertex, const FBMatrix &pMatrix,	const FBVertex &pVertex );

/** Multiply a vector by a matrix.
*	\retval	pOutVector	Resulting vector.
*	\param	pMatrix		Matrix to affect the vector with.
*	\param	pVector		Source vector.
*/
FBSDK_DLL void FBVectorMatrixMult( FBVector4d &pOutVector, const FBMatrix &pMatrix, const FBVector4d &pVector );

////////////////////////////////////////////////////////////////////////////////////
// T,R/Q,S to Matrix
////////////////////////////////////////////////////////////////////////////////////
// N.B. Rotation is in EulerXYZ
/**	Convert a translation vector to a matrix.
*	\retval	pMatrix	Calculated resulting matrix.
*	\param	pVector	Translation vector.
*/
FBSDK_DLL void FBTranslationToMatrix	(FBMatrix  &pMatrix,		const FBTVector& pVector);

/**	Convert a rotation vector to a matrix.
*	\retval	pMatrix	Calculated resulting matrix.
*	\param	pVector	Rotation vector, ordered the same way as the rotation order specified by pRotationOrder.
*	\param	pRotationOrder Rotation order.
*/
FBSDK_DLL void FBRotationToMatrix		(FBMatrix  &pMatrix,		const FBRVector& pVector, FBRotationOrder pRotationOrder = kFBXYZ);

/**	Convert a scaling vector to a matrix.
*	\retval	pMatrix	Calculated resulting matrix.
*	\param	pVector	Scaling vector.
*/
FBSDK_DLL void FBScalingToMatrix		(FBMatrix  &pMatrix,		const FBSVector& pVector);

/**	Convert translation, rotation, and scaling vectors to a matrix.
*	\retval	pMatrix	Calculated resulting matrix.
*	\param	pTVector	Translation vector.
*	\param	pRVector	Rotation vector.
*	\param	pSVector	Scaling vector.
*	\warning Rotation is in EulerXYZ
*/
FBSDK_DLL void FBTRSToMatrix			(FBMatrix  &pMatrix,		const FBTVector& pTVector, const FBRVector& pRVector, const FBSVector& pSVector);

/**	Convert translation vector, rotation quaternion, and scaling vector to a matrix.
*	\retval	pMatrix	Calculated resulting matrix.
*	\param	pTVector	Translation vector.
*	\param	pQuaternion	Rotation quaternion.
*	\param	pSVector	Scaling vector.
*/
FBSDK_DLL void FBTQSToMatrix			(FBMatrix  &pMatrix, const FBTVector& pTVector, const FBQuaternion& pQuaternion, const FBSVector& pSVector);

////////////////////////////////////////////////////////////////////////////////////
// Matrix to T,R/Q,S
////////////////////////////////////////////////////////////////////////////////////
// Rotation is in EulerXYZ
/**	Obtain translation vector from a matrix.
*	\retval	pVector	Extracted translation vector.
*	\param	pMatrix	Input matrix.
*/
FBSDK_DLL void FBMatrixToTranslation	(FBTVector &pVector,		const FBMatrix& pMatrix);

/**	Obtain rotation vector from a matrix.
*	\retval	pVector	Extracted rotation vector, ordered the same way as the rotation order specified by pRotationOrder.
*	\param	pMatrix	Input matrix.
*	\param	pRotationOrder	Rotation order.
*/
FBSDK_DLL void FBMatrixToRotation		(FBRVector &pVector,		const FBMatrix& pMatrix, FBRotationOrder pRotationOrder = kFBXYZ);

/**	Obtain scaling vector from a matrix.
*	\retval	pVector	Extracted scaling vector.
*	\param	pMatrix	Input matrix.
*/
FBSDK_DLL void FBMatrixToScaling		(FBSVector &pVector,		const FBMatrix& pMatrix);

/**	Obtain translation, rotation, and scaling vectors from a matrix.
*	\retval	pTVector	Extracted translation vector.
*	\retval	pRVector	Extracted rotation vector.
*	\retval	pSVector	Extracted scaling vector.
*	\param	pMatrix		Input matrix.
*	\warning Rotation is in EulerXYZ
*/
FBSDK_DLL void FBMatrixToTRS			(FBTVector &pTVector, FBRVector &pRVector, FBSVector &pSVector, const FBMatrix& pMatrix);

/**	Obtain translation vector, rotation quaternion, and scaling vector from a matrix.
*	\retval	pTVector	Extracted translation vector.
*	\retval	pQuaternion	Extracted rotation quaternion.
*	\retval	pSVector	Extracted scaling vector.
*	\param	pMatrix		Input matrix.
*/
FBSDK_DLL void FBMatrixToTQS			(FBTVector &pTVector, FBQuaternion &pQuaternion, FBSVector &pSVector, const FBMatrix& pMatrix);

////////////////////////////////////////////////////////////////////////////////////
// Quaternion
////////////////////////////////////////////////////////////////////////////////////
/**	Get a quaternion from a rotation vector.
*	\retval	pQuaternion	    Calculated quaternion.
*	\param	pVector		    Input rotation vector, ordered the same way as the rotation order specified by pRotationOrder.
*	\param	pRotationOrder	Rotation order.
*/
FBSDK_DLL void FBRotationToQuaternion	(FBQuaternion &pQuaternion,	const FBRVector& pVector, FBRotationOrder pRotationOrder = kFBXYZ);

/**	Get a rotation vector from a quaternion vector.
*	\retval pVector		    Calculated rotation vector, ordered the same way as the rotation order specified by pRotationOrder.
*	\param	pQuaternion	    Input quaternion.
*	\param	pRotationOrder	Rotation order.
*	\warning Rotation is in EulerXYZ or kFBZYX only
*/
FBSDK_DLL void FBQuaternionToRotation	(FBRVector &pVector,		const FBQuaternion& pQuaternion, FBRotationOrder pRotationOrder = kFBXYZ);

/**	Get a quaternion from a matrix (potential ).
*	\retval	pQuaternion	    Calculated quaternion.
*	\param	pMatrix		    Input matrix.
*	\warning Matrix can contain scaling and/or translation, we orthogonalize matrix before.
*/
FBSDK_DLL void FBMatrixToQuaternion(FBQuaternion &pQuaternion,	const FBMatrix& pMatrix);

/**	Get a rotation matrix from a quaternion vector.
*	\retval pMatrix		    Calculated rotation matrix.
*	\param	pQuaternion	    Input quaternion.
*/
FBSDK_DLL void FBQuaternionToMatrix(FBMatrix &pMatrix,		const FBQuaternion& pQuaternion);


////////////////////////////////////////////////////////////////////////////////////
// Local/Global conversions
////////////////////////////////////////////////////////////////////////////////////
/**	Get local matrix from parent and child matrices.
*	Will calculate the local matrix from two global matrices. The resulting matrix will be a local matrix
*	containing the local transformations to go from the parent referentialto the child referential.
*	\retval	pMatrix			Calculated local matrix.
*	\param	pMatrixParent	Parent matrix (new base referential).
*	\param	pMatrixChild	Child matrix.
*/
FBSDK_DLL void FBGetLocalMatrix			(FBMatrix &pMatrix, const FBMatrix& pMatrixParent, const FBMatrix& pMatrixChild);

/**	Get global matrix from parent and child matrices.
*	From an input referential, this function will calculate the global matrix corresponding to 
*	the input local matrix (which is with respect to the parent matrix).
*	\retval	pMatrix			Calculated local matrix.
*	\param	pMatrixParent	Parent matrix.
*	\param	pLocalMatrix	Local matrix.
*/
FBSDK_DLL void FBGetGlobalMatrix		(FBMatrix &pMatrix, const FBMatrix& pMatrixParent, const FBMatrix& pLocalMatrix);


/**	Make sure that rotation vectors are orthogonal and normalized (fast way for removing scaling from matrix)
*	\retval	pMatrix		Orthogonalized matrix.
*	\param	pMatrix	    Rotation Matrix to Orthogonalize.
*/
FBSDK_DLL void FBMatrixOrthogonalize	(FBMatrix &pMatrix);

////////////////////////////////////////////////////////////////////////////////////
// Vector operations
////////////////////////////////////////////////////////////////////////////////////
/**	Add two vectors together (\e pResult = \e pV1 \b + \e pV2)
*	\retval	pResult	Resulting vector.
*	\param	pV1		1st vector.
*	\param	pV2		2nd vector.
*/
FBSDK_DLL void		FBAdd				(FBTVector &pResult, const FBTVector &pV1, const FBTVector &pV2);

/**	Subtract \e pV2 from \e pV1 (\e pResult = \e pV1 \b - \e pV2)
*	\retval	pResult	Resulting vector.
*	\param	pV1		1st vector.
*	\param	pV2		2nd vector.
*/
FBSDK_DLL void		FBSub				(FBTVector &pResult, const FBTVector &pV1, const FBTVector &pV2);

/**	Multiply \e pV2 from \e pV1 (\e pResult = \e pV1 \b * \e pV2)
*	\retval	pResult	Resulting vector.
*	\param	pV1		1st vector.
*	\param	pV2		2nd vector.
*/
FBSDK_DLL void		FBMult				(FBTVector &pResult, const FBTVector &pV1, double pV2);

/** Calculate the cross product of two vectors.
*	\retval	pResult	Resulting vector.
*	\param	pV1		1st vector.
*	\param	pV2		2nd vector.
*/
FBSDK_DLL void		FBMult				(FBTVector &pResult, const FBTVector &pV1, const FBTVector &pV2);

/** Calculate the cross product of a Matrix and Scale Vector.
*	\retval	pResult	Resulting Matrix.
*	\param	pM		Matrix.
*	\param	pV		vector.
*/
FBSDK_DLL void		FBMult				(FBMatrix &pResult, const FBMatrix &pM, const FBSVector &pV);

/**	Calculate the dot product of two vectors.
*	\param	pV1		1st vector.
*	\param	pV2		2nd vector.
*	\return	Dot product.
*/
FBSDK_DLL double	FBDot				(const FBTVector &pV1, const FBTVector &pV2);

/**	Get the length of a vector.
*	\param	pV			Vector to calculate length for.
*	\return	Length of vector \e pV.
*/
FBSDK_DLL double	FBLength			(const FBTVector &pV);

////////////////////////////////////////////////////////////////////////////////////
// Quaternion operations
////////////////////////////////////////////////////////////////////////////////////
/**	Add two quaternions together (\e pResult = \e pQ1 \b + \e pQ2)
*	\retval	pResult	Resulting quaternion.
*	\param	pQ1		1st quaternion.
*	\param	pQ2		2nd quaternion.
*/
FBSDK_DLL void		FBQAdd				(FBQuaternion &pResult, const FBQuaternion &pQ1, const FBQuaternion &pQ2);

/**	Subtract \e pQ2 from \e pQ1 (\e pResult = \e pQ1 \b - \e pQ2)
*	\retval	pResult	Resulting quaternion.
*	\param	pQ1		1st quaternion.
*	\param	pQ2		2nd quaternion.
*/
FBSDK_DLL void		FBQSub				(FBQuaternion &pResult, const FBQuaternion &pQ1, const FBQuaternion &pQ2);

/**	Multiply \e pQ2 from \e pQ1 (\e pResult = \e pQ1 \b * \e pQ2)
*	\retval	pResult	Resulting quaternion.
*	\param	pQ1		1st quaternion.
*	\param	pQ2		2nd quaternion.
*/
FBSDK_DLL void		FBQMult				(FBQuaternion &pResult, const FBQuaternion &pQ1, double pQ2);

/** Calculate the cross product of two quaternions.
*	\retval	pResult	Resulting quaternion.
*	\param	pQ1		1st quaternion.
*	\param	pQ2		2nd quaternion.
*/
FBSDK_DLL void		FBQMult				(FBQuaternion &pResult, const FBQuaternion &pQ1, const FBQuaternion &pQ2);

/**	Calculate the dot product of two quaternions.
*	\param	pQ1		1st quaternion.
*	\param	pQ2		2nd quaternion.
*	\return	Dot product.
*/
FBSDK_DLL double	FBQDot				(const FBQuaternion &pQ1, const FBQuaternion &pQ2);

/**	Get the length of a quaternion.
*	\param	pQ	Quaternion to calculate length for.
*	\return	Length of quaternion \e pQ.
*/
FBSDK_DLL double	FBQLength			(const FBQuaternion &pQ);

////////////////////////////////////////////////////////////////////////////////////
// Vertex operations
////////////////////////////////////////////////////////////////////////////////////
/**	Get the length of a vertex (from origin)
*	\param	pV	Vertex for which length is to be measured.
*	\return	Length of vertex (from origin).
*/
FBSDK_DLL double	FBLength			(const FBVertex &pV);

////////////////////////////////////////////////////////////////////////////////////
// Rotation utilities
////////////////////////////////////////////////////////////////////////////////////
/**	Interpolate a rotation in Euler space.
*	\retval	pROut	Resulting, interpolated rotation.
*	\param	pR0	1st rotation.
*	\param	pR1	2nd rotation.
*	\param	pU	Interpolation ratio.
*/
FBSDK_DLL void	FBInterpolateRotation( FBRVector &pROut, const FBRVector &pR0, const FBRVector &pR1, double pU );

/**	Interpolate a rotation in Quaternion.
*	\retval	pQOut	Resulting, interpolated rotation.
*	\param	pQ0	1st rotation.
*	\param	pQ1	2nd rotation.
*	\param	pU	Interpolation ratio.
*/
FBSDK_DLL void	FBInterpolateRotation( FBQuaternion &pQOut, const FBQuaternion &pQ0, const FBQuaternion &pQ1, double pU );

/**	Get a continuous rotation in Euler space.
*	This routine will help to avoid gimble locks due to interpolation.
*	\retval	pROut	Successful continuous rotation (gimble-lock free).
*	\param	pR0	Suggested next rotation.
*	\param	pR1	Previous rotation.
*/
FBSDK_DLL void		FBGetContinuousRotation	( FBRVector &pROut, const FBRVector &pR0, const FBRVector &pR1 );

////////////////////////////////////////////////////////////////////////////////////
// Miscellaneous utilities 
////////////////////////////////////////////////////////////////////////////////////
/**	Clamp value.
*	\param	pV			Value to clamp.
*	\param	pL			Low limit.
*	\param	pH			High limit.
*	\return	Clamped value.
*/
FBSDK_DLL double	FBClamp		(double pV, double pL, double pH);

/**	Change from big endian to native format.
*	\param	pV			Value to modify.
*/
FBSDK_DLL void	FBBigEndianToNative		(unsigned short &pV);

/**	Change from little endian to native format.
*	\param	pV			Value to modify.
*/
FBSDK_DLL void	FBLittleEndianToNative	(unsigned short &pV);

/**	Obtain rotation vector from a matrix.
*	\retval	pVector	Extracted rotation vector.
*	\param	pMatrix	Input matrix.
*	\param	pRotationOrder	Rotation Order.
*	\param	pPrecision	Indicate the precision level (pow(10.0, -pPrecision)) used when calculating the threshold value for gimble lock.
*	\warning Rotation is in EulerXYZ or EulerZYX only
*/
FBSDK_DLL void FBMatrixToRotationWithPrecision		(FBRVector &pVector, const FBMatrix& pMatrix, FBRotationOrder pRotationOrder, double pPrecision = FBMat2EulerDegenerateForPrecision10);

/**	Get a rotation vector from a quaternion vector.
*	\retval pVector		    Calculated rotation vector.
*	\param	pQuaternion	    Input quaternion.
*	\param	pRotationOrder	Rotation order of the rotation vector.
*	\param	pPrecision		Indicate the precision level (pow(10.0, -pPrecision)) used when calculating the threshold value for gimble lock.
*	\warning Rotation is in EulerXYZ or kFBZYX only
*/
FBSDK_DLL void FBQuaternionToRotationWithPrecision	(FBRVector &pVector, const FBQuaternion& pQuaternion, FBRotationOrder pRotationOrder, double pPrecision = FBMat2EulerDegenerateForPrecision10);

#ifdef FBSDKUseNamespace
	}
#endif
#endif
