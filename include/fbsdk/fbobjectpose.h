#ifndef __FBOBJECTPOSE_H__
#define __FBOBJECTPOSE_H__
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

/** \file fbobjectpose.h
*	Contains definitions for object poses.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbpose.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif


//! Transform mode of pose.
enum FBPoseTransformType
{ 
	kFBPoseTransformInvalid = -1, 
	kFBPoseTransformLocal   =  0,
	kFBPoseTransformGlobal, 
	kFBPoseTransformLocalRef, 
	kFBPoseTransformTypeCount
};

//! ObjectPoseOptions flags.
enum FBObjectPoseOptionsFlag
{
	kFBObjectPoseOptionsNoFlag		= 0,
	kFBObjectPoseOptionsTranslationX= 1,
	kFBObjectPoseOptionsTranslationY= 1<<1,
	kFBObjectPoseOptionsTranslationZ= 1<<2,
	kFBObjectPoseOptionsRotation	= 1<<3,
	kFBObjectPoseOptionsScaling		= 1<<4,
};

//! ObjectPoseMirrorOptions flags.
enum FBObjectPoseMirrorOptionsFlag
{
	kFBObjectPoseMirrorOptionsNoFlag					= 0,
	kFBObjectPoseMirrorOptionsUpdateLocal				= 1,
	kFBObjectPoseMirrorOptionsUpdateLocalMirrorParent	= 1<<1,
	kFBObjectPoseMirrorOptionsUpdateLocalRef			= 1<<2,
	kFBObjectPoseMirrorOptionsUpdateLocalRefMirrorRef	= 1<<3,
};

////////////////////////////////////////////////////////////////////////////////////
// FBObjectPoseOptions
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBObjectPoseOptions );

/** FBObjectPoseOptions class.
*	This class exposes the object used to store the options for operations on object poses.
*/
class FBSDK_DLL FBObjectPoseOptions
{
  public:

	//! Transform type (Local, Global or LocalRef).
	FBPoseTransformType mPoseTransformType;

	//! Global translation vector of reference object.
	FBTVector mReferenceGT;

	//! Global rotation matrix of reference object.
	FBMatrix mReferenceGRM;

	//! Global scaling matrix of reference object.
	FBMatrix mReferenceGSM;

	/** Constructor.
	*/
	FBObjectPoseOptions();

	/** Set a flag value.
	*	\param pFlag	Flag to set.
	*	\param pValue	Value to set.
	*/
	void SetFlag( FBObjectPoseOptionsFlag pFlag, bool pValue );

	/** Get a flag value.
	*	\param pFlag	Flag to get.
	*	\return			Value of the flag.
	*/
	bool GetFlag( FBObjectPoseOptionsFlag pFlag );

	/** Clear all flags.
	*/
	void ClearFlag();

  private:

	FBObjectPoseOptionsFlag mFlags;
};

////////////////////////////////////////////////////////////////////////////////////
// FBObjectPoseMirrorOptions
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBObjectPoseMirrorOptions );

/** FBObjectPoseMirrorOptions class.
*	This class exposes the object used to store the options for the mirror of an object pose.
*/
class FBSDK_DLL FBObjectPoseMirrorOptions
{
  public:

	/** Equation of the mirror plane.
	*	It is a vector defining four scalars (a,b,c,d) for the equation of a plane (ax + by + cz + d = 0).
	*	(a,b,c) represents the normal of the plane.
	*	(d) represents the offset from the origin in the direction of the normal.
	*	Example: (1,0,0,0) defines the plane YZ intersecting with the origin.
	*/
	FBVector4<double> mMirrorPlaneEquation;

	/** Constructor.
	*/
	FBObjectPoseMirrorOptions();

	/** Set a flag value.
	*	\param pFlag	Flag to set.
	*	\param pValue	Value to set.
	*/
	void SetFlag( FBObjectPoseMirrorOptionsFlag pFlag, bool pValue );

	/** Get a flag value.
	*	\param pFlag	Flag to get.
	*	\return			Value of the flag.
	*/
	bool GetFlag( FBObjectPoseMirrorOptionsFlag pFlag );

	/** Clear all flags.
	*/
	void ClearFlag();

  private:

	FBObjectPoseMirrorOptionsFlag mFlags;
};

////////////////////////////////////////////////////////////////////////////////////
// FBObjectPose
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBObjectPose );

/** FBObjectPose class.
*	This class exposes the object used to store the pose of objects.
*/
class FBSDK_DLL FBObjectPose : public FBPose
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBObjectPose, FBPose );

  public:
	/** Public constructor.
	*   This constructor is used to create a new object.
	*   \param pName Object name. If pObject is not NULL, pName will be ignored.
	*   \param pObject For internal use only.
	*/
	FBObjectPose( const char* pName, HIObject pObject=NULL );

	/** Clear all the data of the pose.
	*/
	void ClearPose();

	/** Is the property poseable?
	*	\return \c True if the value of this property can be stored in the pose.
	*/
	bool IsPropertyPoseable( FBProperty &pProperty );

	/** Get all the object names currently stored in this pose.
	*	\return All the object names currently stored in this pose.
	*/
	FBStringList GetStoredObjectNames();

	/** Copy the pose of all the properties of an object.
	*	\remarks You can specify a pObjectName different from the name of pObject.
	*	\param pObjectName	Name of the object to store in the pose.
	*	\param pObject		Object from which we'll read all the property values to store in the pose.
	*/
	void CopyObjectPose( const char* pObjectName, FBComponent& pObject );

	/** Copy the pose of a property of an object.
	*	\remarks You can specify a pObjectName different from the name of pObject.
	*	\param pObjectName		Name of the object to store in the pose.
	*	\param pProperty		Property from which we'll read the value to store in the pose.
	*/
	void CopyPropertyPose( const char* pObjectName, FBProperty& pProperty );

	/** Paste the pose of all the properties of an object.
	*	\remarks You can specify a pObjectName different from the name of pObject.
	*	\remarks Properties that were not stored in the pose will not be affected.
	*	\param pObjectName	Name of the object stored in the pose.
	*	\param pObject		Object which will receive the values stored in the pose.
	*/
	void PasteObjectPose( const char* pObjectName, FBComponent& pObject );

	/** Paste the pose of a property of an object.
	*	\remarks You can specify a pObjectName different from the name of pObject.
	*	\remarks The property will not be affected if it was not stored in the pose.
	*	\param pObjectName		Name of the object stored in the pose.
	*	\param pProperty		Property which will receive the value stored in the pose.
	*/
	void PastePropertyPose( const char* pObjectName, FBProperty& pProperty );

	/** Set the value of a property in the pose.
	*	\param pValue			Value to set.
	*	\param pSize			Number of elements in pValue.
	*	\param pObjectName		Name of the object to set the value.
	*	\param pPropertyName	Name of the property to set the value.
	*/
	void SetPropertyValue( const char* pObjectName, const char* pPropertyName, double* pValue, int pSize );

	/** Get the value of a property stored in the pose.
	*	\param pValue			Value to get.
	*	\param pSize			Number of elements in pValue.
	*	\param pObjectName		Name of the object to get the value.
	*	\param pPropertyName	Name of the property to get the value.
	*/
	void GetPropertyValue( double* pValue, int pSize, const char* pObjectName, const char* pPropertyName );

	/** Is the property stored in the pose?
	*	\param pObjectName		Name of the object.
	*	\param pPropertyName	Name of the property.
	*	\return					\c True if the property is stored in the pose.
	*/
	bool IsPropertyStored( const char* pObjectName, const char* pPropertyName );

	/** Copy the transform of an object.
	*	\remarks This function will always copy all the TransformAttributes (T,R,S) in all TransformType (Local, Global, LocalRef).
	*	\param pObjectName			Name of the object to store in the pose.
	*	\param pObject				Object from which we'll evaluate the transform values to store in the pose.
	*	\param pObjectPoseOptions	PoseOptions used to specify the transform of the reference object (Default: Identity).
	*/
	void CopyTransform( const char* pObjectName, FBComponent& pObject, FBObjectPoseOptions& pObjectPoseOptions );

	/** Paste the transform of an object.
	*	\remarks Use the pObjectPoseOptions to specify which TransformType to use when pasting.
	*	\param pObjectName			Name of the object stored in the pose.
	*	\param pObject				Object which will receive the transform values stored in the pose.
	*	\param pObjectPoseOptions	PoseOptions used to specify the transform of the reference object, the TransformType and TransformAttributes to paste.
	*   \param pEvaluateInfo		Information concerning the evaluation of the animation (time, etc.)
	*/
	void PasteTransform( const char* pObjectName, FBComponent& pObject, FBObjectPoseOptions& pObjectPoseOptions, FBEvaluateInfo* pEvaluateInfo = NULL  );

	/** Set the transform of an object in the pose.
	*	\param pT					Translation to set.
	*	\param pRM					Rotation to set.
	*	\param pSM					Scaling to set.
	*	\param pObjectName			Name of the object to set the transform.
	*	\param pPoseTransformType	Transform type in which to set the transform (Local, Global or LocalRef).
	**/
	void SetTransform( FBTVector& pT, FBMatrix& pRM, FBMatrix& pSM, const char* pObjectName, FBPoseTransformType pPoseTransformType );

	/** Get the transform of an object in the pose.
	*	\param pT					Translation to get.
	*	\param pRM					Rotation to get.
	*	\param pSM					Scaling to get.
	*	\param pObjectName			Name of the object to get the transform.
	*	\param pPoseTransformType	Transform type in which to set the transform (Local, Global or LocalRef).
	*	\return						\c True if the transform was found in the pose.
	**/
	bool GetTransform( FBTVector& pT, FBMatrix& pRM, FBMatrix& pSM, const char* pObjectName, FBPoseTransformType pPoseTransformType );

	/** Is the transform of this object stored in the specified TransformType?
	*	\remarks If pPoseTransformType is set to kFBPoseTransformInvalid, will check in all TransformTypes.
	*	\param pObjectName			Name of the object.
	*	\param pPoseTransformType	Transform type in which to check.
	*	\return						\c True if the transform of this object is stored in the specified TransformType (Local, Global and LocalRef).
	*/
	bool IsTransformStored( const char* pObjectName, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid );

	/** Multiply the transform of all objects in the pose.
	*	\param pGX					Transformation matrix to apply.
	*	\param pTransformAttribute	Transform attribute to affect. Supported: T,R,S and Transformation.
	*	\param pPoseTransformType	Transform type in which to mult the transform (Local, Global or LocalRef).
	*/
	void MultTransformAllObjects( FBMatrix& pGX, FBModelTransformationType pTransformAttribute, FBPoseTransformType pPoseTransformType );

	/** Multiply the transform of an objects in the pose.
	*	\param pObjectName			Name of the object.
	*	\param pGX					Transformation matrix to apply.
	*	\param pTransformAttribute	Transform attribute to affect. Supported: T,R,S and Transformation.
	*	\param pPoseTransformType	Transform type in which to mult the transform (Local, Global or LocalRef).
	*/
	void MultTransform( const char* pObjectName, FBMatrix& pGX, FBModelTransformationType pTransformAttribute, FBPoseTransformType pPoseTransformType );

	/** Mirror the transform of all objects in the pose.
	*	\param pObjectPoseMirrorOptions MirrorOptions used to specify the mirror plane.
	*/
	void MirrorPoseAllObjects( FBObjectPoseMirrorOptions& pObjectPoseMirrorOptions );

	/** Mirror the transform of an object in the pose.
	*	\param pObjectName				Name of the object to mirror.
	*	\param pObjectPoseMirrorOptions MirrorOptions used to specify the mirror plane.
	*/
	void MirrorPose( const char* pObjectName, FBObjectPoseMirrorOptions& pObjectPoseMirrorOptions );

	/** Remove the StanceOffset from all the objects in the pose.
	*	\remarks Working with poses with their StanceOffset removed is usefull for retargetting.
	*	\remarks If pPoseTransformType is set to kFBPoseTransformInvalid, offsets will be removed in all TransformTypes.
	*	\param pStancePose			Pose representing the stance of all objects.
	*	\param pPoseTransformType	Transform type in which to remove the offset (Local, Global or LocalRef).
	*/
	void RemoveStanceOffsetAllObjects( FBObjectPose& pStancePose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid );
	
	/** Remove the StanceOffset from an object in the pose.
	*	\remarks Working with poses with their StanceOffset removed is usefull for retargetting.
	*	\remarks If pPoseTransformType is set to kFBPoseTransformInvalid, offsets will be removed in all TransformTypes.
	*	\param pObjectName			Name of the object.
	*	\param pStancePose			Pose representing the stance of all objects.
	*	\param pPoseTransformType	Transform type in which to remove the offset (Local, Global or LocalRef).
	*/
	void RemoveStanceOffset( const char* pObjectName, FBObjectPose& pStancePose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid );
	
	/** Add the StanceOffset to all the objects in the pose.
	*	\remarks Working with poses with their StanceOffset removed is usefull for retargetting.
	*	\remarks If pPoseTransformType is set to kFBPoseTransformInvalid, offsets will be added in all TransformTypes.
	*	\param pStancePose			Pose representing the stance of all objects.
	*	\param pPoseTransformType	Transform type in which to add the offset (Local, Global or LocalRef).
	*/
	void AddStanceOffsetAllObjects( FBObjectPose& pStancePose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid );
	
	/** Add the StanceOffset to an object in the pose.
	*	\remarks Working with poses with their StanceOffset removed is usefull for retargetting.
	*	\remarks If pPoseTransformType is set to kFBPoseTransformInvalid, offsets will be added in all TransformTypes.
	*	\param pObjectName			Name of the object.
	*	\param pStancePose			Pose representing the stance of all objects.
	*	\param pPoseTransformType	Transform type in which to add the offset (Local, Global or LocalRef).
	*/
	void AddStanceOffset( const char* pObjectName, FBObjectPose& pStancePose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid );

	/** Mirror the transform of all objects in the SrcPose and retarget the result on the DstPose.
	*	\remarks This function can be used to mirror the pose of a right-arm on a left-arm, or a tail on itself.
	*	\remarks The mirror plane should intersect with the origin because we mirror the pose with stance offsets removed.
	*	\param pDstPose				Destination pose to receive the result.
	*	\param pSrcPose				Source pose to mirror.
	*	\param pDstStancePose		Stance pose for the DstPose.
	*	\param pSrcStancePose		Stance pose for the SrcPose.
	*	\param pMirrorPlaneEquation Mirror plane used to mirror the SrcPose once the stance offsets are removed.
	*/
	static void MirrorRetargetPoseAllObjects
	(
		FBObjectPose& pDstPose,
		FBObjectPose& pSrcPose,
		FBObjectPose& pDstStancePose,
		FBObjectPose& pSrcStancePose,
		FBVector4<double>& pMirrorPlaneEquation
	);

	/** Mirror the transform of an object in the SrcPose and retarget the result on the DstPose.
	*	\remarks This function can be used to mirror the pose of a right-arm on a left-arm, or a tail on itself.
	*	\remarks The mirror plane should intersect with the origin because we mirror the pose with stance offsets removed.
	*	\param pDstPose				Destination pose to receive the result.
	*	\param pSrcPose				Source pose to mirror.
	*	\param pDstStancePose		Stance pose for the DstPose.
	*	\param pSrcStancePose		Stance pose for the SrcPose.
	*	\param pMirrorPlaneEquation Mirror plane used to mirror the SrcPose once the stance offsets are removed.
	*	\param pDstObjectName		Name of the object in the DstPose to receive the mirror of the SrcPose.
	*	\param pSrcObjectName		Name of the object to mirror from the SrcPose.
	*/
	static void MirrorRetargetPose
	(
		FBObjectPose& pDstPose,
		FBObjectPose& pSrcPose,
		FBObjectPose& pDstStancePose,
		FBObjectPose& pSrcStancePose,
		FBVector4<double>& pMirrorPlaneEquation,
		const char* pDstObjectName,
		const char* pSrcObjectName
	);

	/** Retarget the non-transform properties from the SrcPose to the DstPose.
	*	\remarks This will copy all stored properties from the specified object in SrcPose to the specified object in DstPose.
	*	\param pDstPose				Destination pose.
	*	\param pSrcPose				Source pose.
	*	\param pDstObjectName		Name of the object in the DstPose to receive the copy.
	*	\param pSrcObjectName		Name of the object to copy from the SrcPose.
	*/
    static void RetargetPose
    (
        FBObjectPose& pDstPose,
        FBObjectPose& pSrcPose,
        const char* pDstObjectName,
        const char* pSrcObjectName
    );

	/** Copy everything from a given object.
	*	\remarks Will copy everything, including the object name, properties, data etc. Objects will be identical.
	*	\param pFromPose Pose from which to copy.
	*/
	void CopyFrom( FBObjectPose& pFromPose );

    /** Copy all the pose data from a given pose.
	*	\remarks Will copy all the data of the pose including the transforms.
	*	\param pFromPose Pose from which to copy the data.
	*/
	void CopyPoseDataFrom( FBObjectPose& pFromPose );

	/** Copy all the transforms from a given pose.
	*	\remarks If pPoseTransformType is set to kFBPoseTransformInvalid, copy all TransformTypes.
	*	\param pFromPose			Pose from which to copy the data.
	*	\param pPoseTransformType	Transform type from which to copy the transform (Local, Global or LocalRef).
	*/
	void CopyPoseAllObjectsTransformFrom( FBObjectPose& pFromPose, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid );

	/** Copy the transforms of an object from a given pose.
	*	\remarks If pPoseTransformType is set to kFBPoseTransformInvalid, copy all TransformTypes.
	*	\param pFromPose			Pose from which to copy the data.
	*	\param pObjectName			Name of object to copy the transform from.
	*	\param pPoseTransformType	Transform type from which to copy the transform (Local, Global or LocalRef).
	*/
	void CopyPoseTransformFrom( FBObjectPose& pFromPose, const char* pObjectName, FBPoseTransformType pPoseTransformType = kFBPoseTransformInvalid );

  private:

	//@{
	/** Restricted methods.
	*   Voluntarily making the copy constructor and assignment
	*   operator unavailable.
	*/
	FBObjectPose( const FBObjectPose& );
	FBObjectPose& operator=( const FBObjectPose& );
	//@}
};

////////////////////////////////////////////////////////////////////////////////////
// Property List: ObjectPose
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: ObjectPose.
*/
class FBSDK_DLL FBPropertyListObjectPose : public FBPropertyListComponent
{
  public:
	FBPropertyListObjectPose();
	/**	Get the object pose at \e pIndex.
	*	\param	pIndex	Index of object pose to get a handle on.
	*	\return			Object pose at \e pIndex.
	*/
	FBObjectPose* operator[]( int pIndex );
};

////////////////////////////////////////////////////////////////////////////////////
// Useful functions
////////////////////////////////////////////////////////////////////////////////////

/** Get a plane equation from a normal vector and a point on the plane.
*	\param pPlaneEquation		Out: The plane equation computed.
*	\param pPlaneNormalVector	Normal vector to the plane.
*	\param pPointOnPlane		A point on the plane.
*/
FBSDK_DLL void GetPlaneEquation( FBVector4<double>& pPlaneEquation, const FBTVector& pPlaneNormalVector, const FBTVector& pPointOnPlane );

/** Get a plane equation from a point on the plane and a rotation matrix relative to the plane XZ.
*	\param pPlaneEquation		Out: The plane equation computed.
*	\param pPointOnPlane		A point on the plane.
*	\param pPlaneRM				Rotation matrix of the plane, identity being the plane XZ.
*/
FBSDK_DLL void GetPlaneEquation( FBVector4<double>& pPlaneEquation, const FBTVector& pPointOnPlane, const FBMatrix& pPlaneRM );

/** Get the plane rotation matrix from a plane equation.
*	\param pPlaneRM				Out: Rotation matrix of the plane, identity being the plane XZ.
*	\param pPlaneEquation		The equation of the plane.
*/
FBSDK_DLL void GetPlaneRotation( FBMatrix& pPlaneRM, const FBVector4<double>& pPlaneEquation );

/** Normalize a plane equation.
*	\param pNormalizedPlaneEquation	Out: Plane equation normalized.
*	\param pPlaneEquation			Plane equation to normalized.
*/
FBSDK_DLL void NormalizePlaneEquation( FBVector4<double>& pNormalizedPlaneEquation, FBVector4<double>& pPlaneEquation );

/** Mirror a transformation using the specified mirror plane.
*	\param pMirrorT			Out: Mirrored translation.
*	\param pMirrorRM		Out: Mirrored rotation.
*	\param pMirrorSM		Out: Mirrored scaling.
*	\param pT				Translation to mirror.
*	\param pRM				Rotation to mirror.
*	\param pSM				Scaling to mirror.
*	\param pPlaneEquation	The equation of the mirror plane.
*/
FBSDK_DLL void MirrorTransform( FBTVector& pMirrorT, FBMatrix& pMirrorRM, FBMatrix& pMirrorSM, const FBTVector& pT, const FBMatrix& pRM, const FBMatrix& pSM, const FBVector4<double>& pPlaneEquation );

/** Mirror a translation using the specified mirror plane.
*	\param pMirrorT			Out: Mirrored translation.
*	\param pT				Translation to mirror.
*	\param pPlaneEquation	The equation of the mirror plane.
*/
FBSDK_DLL void MirrorTransformT( FBTVector& pMirrorT, const FBTVector& pT, const FBVector4<double>& pPlaneEquation );

/** Mirror a rotation using the specified mirror plane.
*	\param pMirrorRM		Out: Mirrored rotation.
*	\param pRM				Rotation to mirror.
*	\param pPlaneEquation	The equation of the mirror plane.
*/
FBSDK_DLL void MirrorTransformR( FBMatrix& pMirrorRM, const FBMatrix& pRM, const FBVector4<double>& pPlaneEquation );


#ifdef FBSDKUseNamespace
	}
#endif

#endif /* __FBOBJECTPOSE_H__ */
