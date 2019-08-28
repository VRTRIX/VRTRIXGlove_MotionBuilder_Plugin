#ifndef __FBCHARACTERPOSE_H__
#define __FBCHARACTERPOSE_H__
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

/** \file FBCharacterPose.h
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

FB_FORWARD( FBCharacter );
FB_FORWARD( FBCharacterExtension );
FB_FORWARD( FBObjectPose );
FB_FORWARD( FBModel );

//! Character Pose Options flags.
enum FBCharacterPoseFlag
{
	kFBCharacterPoseNoFlag				= 0,
	kFBCharacterPoseMirror				= 1,
	kFBCharacterPoseGravity				= 1<<1,
	kFBCharacterPoseMatchTX				= 1<<2,
	kFBCharacterPoseMatchTY				= 1<<3,
	kFBCharacterPoseMatchTZ				= 1<<4,
	kFBCharacterPoseMatchR				= 1<<5,
	kFBCharacterPoseMatchPivot			= 1<<6,
    kFBCharacterPoseUseKeyingGroup		= 1<<7
};

//! Mirror Plane Type.
enum FBMirrorPlaneType
{
	kFBMirrorPlaneTypeInvalid = -1,
	kFBMirrorPlaneTypeAuto    =  0,
	kFBMirrorPlaneTypeZY,
	kFBMirrorPlaneTypeXY,
	kFBMirrorPlaneTypeXZ,
	kFBMirrorPlaneTypeUser,
	kFBMirrorPlaneTypeEquation,
	kFBMirrorPlaneTypeCount
};

//! Character Pose Keying Mode.
enum FBCharacterPoseKeyingMode
{
	kFBCharacterPoseKeyingModeInvalid   = -1,
	kFBCharacterPoseKeyingModeFullBody  =  0,
	kFBCharacterPoseKeyingModeBodyPart,
	kFBCharacterPoseKeyingModeCount
};

////////////////////////////////////////////////////////////////////////////////////
// FBCharacterPoseOptions
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBCharacterPoseOptions );

/** Stores options for operations on poses.
*	This class exposes the object used to store the options for operations on object poses. Before using a FBCharacterPoseOptions,
*	you need to specify the various members of the object. Here are the default values of a FBCharacterPoseOptions object:
*	mCharacterPoseKeyingMode = kFBCharacterPoseKeyingModeFullBody
*	mModelToMatch = NULL
*	mMirrorPlaneType = kFBMirrorPlaneTypeAuto
*	mMirrorPlaneEquation = 1.0, 0.0, 0.0, 0.0
*	mMirrorPlaneTiltAngle = 90.0
*	mMirrorPlanePanAngle = 0.0
*	Flag = kFBCharacterPoseNoFlag
*	You need to change at least the Flag value by using SetFlag() to set how the pose will be pasted; see the FBCharacterPoseFlag enum
*	for the various options.
*/
class FBSDK_DLL FBCharacterPoseOptions
{
  public:

	/** Model to match.
	*	When pasting a pose and matching T/R, the pose is pasted so that the T/R of this model does not change.
	*/
	FBModel* mModelToMatch;

	//! CharacterPoseKeyingMode (FullBody or BodyPart).
	FBCharacterPoseKeyingMode mCharacterPoseKeyingMode;

	//! Mirror plane type.
	FBMirrorPlaneType mMirrorPlaneType;

	/** Mirror plane equation (used when mMirrorPlaneType = kFBMirrorPlaneTypeEquation).
	*	It is a vector defining four scalars (a,b,c,d) for the equation of a plane (ax + by + cz + d = 0).
	*	(a,b,c) represents the normal of the plane.
	*	(d) represents the offset from the origin in the direction of the normal.
	*	Example: (1,0,0,0) defines the plane YZ intersecting with the origin.
	*/
	FBVector4<double> mMirrorPlaneEquation;

	//! Mirror plane tilt angle in degrees (used when mMirrorPlaneType = kFBMirrorPlaneTypeUser).
	double mMirrorPlaneTiltAngle;

	//! Mirror plane pan angle in degrees (used when mMirrorPlaneType = kFBMirrorPlaneTypeUser).
	double mMirrorPlanePanAngle;
	
	/** Constructor.
	*/
	FBCharacterPoseOptions();

	/** Set a flag value.
	*	\param pFlag	Flag to set.
	*	\param pValue	Value to set.
	*/
	void SetFlag( FBCharacterPoseFlag pFlag, bool pValue );

	/** Get a flag value.
	*	\param pFlag	Flag to get.
	*	\return			Value of the flag.
	*/
	bool GetFlag( FBCharacterPoseFlag pFlag ) const;

	/** Clear all flags.
	*/
	void ClearFlag();

  private:

	FBCharacterPoseFlag mFlags;
};

////////////////////////////////////////////////////////////////////////////////////
// FBCharacterPose
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCharacterPose );

/** Used to work with character poses.
*	This class exposes the object used to store the pose of objects.
*/
class FBSDK_DLL FBCharacterPose : public FBPose
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBCharacterPose, FBPose );

  public:
	/** Public constructor.
	*   This constructor is used to create a new object.
	*   \param pName Object name.
	*   \param pObject For internal use only.
	*/
	FBCharacterPose( const char* pName, HIObject pObject=NULL );

	/** Clear all the data of the pose.
	*/
	void ClearPose();

	/** Clear only the pose of the character (omit the extensions).
	*/
	void ClearCharacterPose();

	/** Clear only the pose of the character extensions (omit the character).
	*/
	void ClearCharacterExtensionsPose();

    /** Copy the pose of a character and its extensions.
	*	\param pCharacter Character to copy the pose from.
	*/
	void CopyPose( FBCharacter& pCharacter );

	/** Copy the pose of only the character (omit the extensions).
	*	\param pCharacter Character to copy the pose from.
	*/
	void CopyPoseCharacter( FBCharacter& pCharacter );

	/** Copy the pose of only the character extensions (omit the character).
	*	\param pCharacter Character to copy the pose of the extensions from.
	*/
	void CopyPoseCharacterExtensions( FBCharacter& pCharacter );

	/** Copy the pose of a single character extension.
	*	\param pCharacterExtension Character extension to copy the pose from.
	*/
	void CopyPoseCharacterExtension( FBCharacterExtension& pCharacterExtension );

	/** Paste the pose of a character and its extensions.
	*	\remarks Supports the match and mirror options.
	*	\remarks When pasting in body part, the selected parts and extensions of the character will be pasted.
	*	\param pCharacter				Character to paste the pose to.
	*	\param pCharacterPoseOptions	Options used to specify how to paste.
	*/
	void PastePose( FBCharacter& pCharacter, FBCharacterPoseOptions& pCharacterPoseOptions );

	/** Paste the pose of only the character (omit the extensions).
	*	\remarks Does not support the match and mirror options.
	*	\param pCharacter				Character to paste the pose to.
	*	\param pCharacterPoseOptions	Options used to specify how to paste.
	*/
	void PastePoseCharacter( FBCharacter& pCharacter, FBCharacterPoseOptions& pCharacterPoseOptions );

	/** Paste the pose of only the character extensions (omit the character).
	*	\remarks Does not support the match and mirror options.
	*	\param pCharacter				Character to paste the pose of the extensions to.
	*	\param pCharacterPoseOptions	Options used to specify how to paste.
	*/
	void PastePoseCharacterExtensions( FBCharacter& pCharacter, FBCharacterPoseOptions& pCharacterPoseOptions );

	/** Paste the pose of a single character extension.
	*	\remarks Does not support the match and mirror options.
	*	\param pCharacterExtension		Character extension to paste the pose to.
	*	\param pCharacterPoseOptions	Options used to specify how to paste.
	*/
	void PastePoseCharacterExtension( FBCharacterExtension& pCharacterExtension, FBCharacterPoseOptions& pCharacterPoseOptions );

	/** Is the pose of the character stored in the pose?
	*	\return \b true if the pose of the character stored in the pose.
	*/
	bool IsCharacterPoseStored();

	/** Is the pose of the character extension stored in the pose?
	*	\param pCharacterExtensionName	Name of the character extension.
	*	\return							\b true if the pose of the character extension stored in the pose.
	*/
	bool IsCharacterExtensionPoseStored( const char* pCharacterExtensionName );

	/** Copy everything from a given object.
	*	\remarks Will copy everything, including the object name, properties, data etc. Objects will be identical.
	*	\param pFromPose Pose from which to copy.
	*/
	void CopyFrom( FBCharacterPose& pFromPose );

    /** Copy all the pose data from a given pose.
	*	\remarks Will copy all the data of the pose.
	*	\param pFromPose Pose from which to copy the data.
	*/
	void CopyPoseDataFrom( FBCharacterPose& pFromPose );

	/** Copy the pose data of only the character from a given pose.
	*	\param pFromPose Pose from which to copy the data.
	*/
	void CopyPoseCharacterFrom( FBCharacterPose& pFromPose );

	/** Copy the pose data of only the character extensions from a given pose.
	*	\param pFromPose Pose from which to copy the data.
	*/
	void CopyPoseCharacterExtensionsFrom( FBCharacterPose& pFromPose );

	/** Get the number of character extension stored in the pose.
	*	\return Number of character extension stored in the pose.
	*/
	int GetCharacterExtensionPoseCount();

	/** Get the pose of a character extension.
	*	\param pIndex	Index of the character extension pose to get.
	*	\return			The pose of the character extension.
	*/
	FBObjectPose* GetCharacterExtensionPoseAt( int pIndex );
	
	/** Get the pose of a character extension.
	*	\param pCharacterExtensionName	Name of the character extension pose to get (It is the label name of the character extension).
	*	\return							The pose of the character extension, NULL if not found.
	*/
	FBObjectPose* GetCharacterExtensionPose( const char* pCharacterExtensionName );

	/** Get the pose of a character extension and create it if necessary.
	*	\remarks Use this function to manually add a pose of a character extension.
	*	\param pCharacterExtensionName	Name of the character extension pose to get (It is the label name of the character extension).
	*	\return							The pose of the character extension.
	*/
	FBObjectPose* GetOrCreateCharacterExtensionPose( const char* pCharacterExtensionName );

	/** Remove the pose of a character extension.
	*	\param pIndex	Index of the character extension pose to remove.
	*/
	void RemoveCharacterExtensionPoseAt( int pIndex );
	
	/** Remove the pose of a character extension.
	*	\param pCharacterExtensionName	Name of the character extension pose to remove (It is the label name of the character extension).
	*/
	void RemoveCharacterExtensionPose( const char* pCharacterExtensionName );

	/** Get the name of the character extension for the specified pose.
	*	\param pCharacterExtensionPose Pose of a character extension to check its name.
	*	\return The name of the character extension (It is the label name of the character extension).
	*/
	FBString GetCharacterExtensionNameFromPose( FBObjectPose& pCharacterExtensionPose );

	/** Get the mirror plane equation that would be used to mirror according to the CharacterPoseOptions.
	*	\param pMirrorPlaneEquation		Out: Mirror plane equation.
	*	\param pCharacter				Character to receive the pose.
	*	\param pCharacterPoseOptions	Options used to paste the pose.
	*/
	void GetMirrorPlaneEquation( FBVector4<double>& pMirrorPlaneEquation, FBCharacter& pCharacter, FBCharacterPoseOptions& pCharacterPoseOptions );

	/** Get the mirror plane equation that would be used to mirror according to the CharacterPoseOptions.
	*	\param pMirrorPlaneEquation		Out: Mirror plane equation.
	*	\param pCharacter				Character to receive the pose.
	*	\param pCharacterPoseOptions	Options used to paste the pose.
	*/
	void GetMirrorPlaneEquation( FBMatrix& pMirrorPlaneEquation, FBCharacter& pCharacter, FBCharacterPoseOptions& pCharacterPoseOptions );

    
    /** Get the number of extra bones contained in the character pose.
	*	\return The number of extra bones contained in the character pose.
	*/
    int GetExtraBoneCount();

	/** Get the extra bone model at the specified index.
	*	\param pIndex Index of the extra bone to get.
	*	\return The extra bone model if the index was valid, otherwise, null is returned.
	*/
    FBModel* GetExtraBoneModelAt(int pIndex);

	/** Get the extra bone transformation offset.
	*	\param pT A vector that will contains the translation offset value on return.
	*	\param pR A vector that will contains the rotation offset value on return.
	*	\param pS A vector that will contains the scale offset value on return.
	*	\param pIndex Index of the extra bone to get.
	*/
    void GetExtraBoneTransformOffset(FBVector3d &pT, FBVector3d &pR, FBVector3d &pS, int pIndex );

	/** Get the extra bone transformation.
	*	\param pT A vector that will contains the translation value on return.
	*	\param pR A vector that will contains the rotation value on return.
	*	\param pS A vector that will contains the scale value on return.
	*	\param pIndex Index of the extra bone to get.
	*/
    void GetExtraBoneTransform(FBVector3d &pT, FBVector3d &pR, FBVector3d &pS, int pIndex );

	/** Get the extra bone transformation offset.
	*	\param pR A vector that will contains the parent rotation offset value on return.
	*	\param pIndex Index of the extra bone to get.
	*/
    void GetExtraBoneParentRotationOffset( FBRVector &pR, int pIndex );

	/** After setting the candidate on the skeleton node, calling this function will allow 
    *   subsequent call to get the TRS value of a skeleton node to return the candidate value.
    */
    void ApplyPoseCandidate();

  private:

	//@{
	/** Restricted methods.
	*   Voluntarily making the copy constructor and assignment
	*   operator unavailable.
	*/
	FBCharacterPose( const FBCharacterPose& );
	FBCharacterPose& operator=( const FBCharacterPose& );
	//@}
};

////////////////////////////////////////////////////////////////////////////////////
// Property List: CharacterPose
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: CharacterPose.
*/
class FBSDK_DLL FBPropertyListCharacterPose : public FBPropertyListComponent
{
  public:
	FBPropertyListCharacterPose();
	/**	Get the character pose at \e pIndex.
	*	\param	pIndex	Index of character pose to get a handle on.
	*	\return			Character pose at \e pIndex.
	*/
	FBCharacterPose* operator[]( int pIndex );
};

#ifdef FBSDKUseNamespace
	}
#endif

#endif /* __FBCHARACTERPOSE_H__ */
