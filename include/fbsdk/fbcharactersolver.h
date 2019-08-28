#ifndef __FBCHARACTERSOLVER_H__
#define __FBCHARACTERSOLVER_H__
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

/**	\file fbconstraint.h
*	Contraint classes.
*	Classes from this file permit the user to derive, create and control
*	constraints via the software development kit.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbcore.h>
#if !defined(K_NO_MANIPULATOR)
	#include <fbsdk/fbcharactermanipulator.h>
#endif
#include <fbsdk/fbcharacter.h>
#include <fbsdk/fbcharacterpose.h>
#include <fbsdk/fbobjectpose.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

FB_DEFINE_COMPONENT( FBSDK_DLL, CharacterSolver );

/**	Register the constraint.
*	\param	UniqueNameStr	Unique name.
*	\param	ClassName		Name of the constraint class.
*	\param	Label			Short description of constraint.
*	\param	Description		Long description of constraint.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterCharacterSolver( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
	HIObject RegisterCharacterSolver##ClassName##Create( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName(pName); \
		Class->UniqueName = UniqueNameStr; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
\
	FBLibraryModule( ClassName ) \
	{	\
		FBRegisterObject( ClassName##R1,"FbxStorable/CharacterSolver",UniqueNameStr,Description,RegisterCharacterSolver##ClassName##Create, true, IconFilename ); \
		FBRegisterObject( ClassName##R2,"Character/Solvers",UniqueNameStr,Description,RegisterCharacterSolver##ClassName##Create,true, IconFilename ); \
	}

/** Constraint class declaration.
*	\param	ClassName	Constraint class name.
*	\param	Parent		Parent class name.
*	\warning The class must inherit directly from FBCharacterSolver.
*/
#define FBCharacterSolverDeclare( ClassName, Parent ) \
	FBClassDeclare( ClassName, Parent ); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/** Constraint class implementation.
*	\param	ThisComponent The name of the class to implement.
*/
#define FBCharacterSolverImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBConstraint
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCharacterSolver );
__FB_FORWARD( FBCharacterManipulatorCtrlSet );

//! Constraint class.
class FBSDK_DLL FBCharacterSolver : public FBConstraint 
{
	__FBClassDeclare( FBCharacterSolver,FBConstraint );
public:
	/** Constructor.
	*	\param	pName		Name of constraint.
	*	\param	pObject		For internal use only (default is NULL).
	*/
	FBCharacterSolver(const char* pName, HIObject pObject=NULL);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    IObject_Declare(K_IMPLEMENTATION);
#endif

	int mEvaluationId;						//!< Last Evaluation Id
	FBPropertyCharacter	TargetCharacter;	//!< <b>Read Write Property:</b> The character being constrained.
	FBPropertyComponent	Source;				//!< <b>Read Write Property:</b> Source character when doing a character retarget.

	/**	Start background evaluation. Needs to be released as soon as possible. 
	*	\param	pSourceEvaluateInfo	Source evaluation. Needs to be valid one.
	*	\param	pEvaluateCandidates	Notify that we want to be able to resolve candidates - this can be called only from main thread (on other threads won't work)
	*	\return Background evaluation info that will work with new ID and in secured buffers.
	*	\note	Example of usage can be found in /OpenRealitySDK/Samples/constraints/CharacterSolver/HIK2014Solver
	*/
    FBEvaluateInfo* BackgroundEvaluateInfoBegin(FBEvaluateInfo* pSourceEvaluateInfo, bool pEvaluateCandidates=false);

	/**	Start recursive background evaluation. Needs to be released as soon as possible. 
	*	\param	pSourceEvaluateInfo	Source evaluation. Needs to be valid one.
	*	\param	pForceUpdateLocals	Evaluate local transformation, even if only global was requested
	*	\return Background evaluation info that will work with new ID and in secured buffers.
	*	\note	Example of usage can be found in /OpenRealitySDK/Samples/constraints/CharacterSolver/HIK2014Solver
	*/
    FBEvaluateInfo* BackgroundEvaluateInfoRecursiveBegin(FBEvaluateInfo* pSourceEvaluateInfo, bool pForceUpdateLocals=false);

	//! Release background evaluation info - very important.
	void			BackgroundEvaluateInfoEnd(FBEvaluateInfo* pBackgroundEvaluateInfo);

	/**	Enable evaluation notification
	*	\param	pBackgroundEvaluateInfo	Background evaluation that was started for this object and for which we want to change enable/disable notification callback
	*	\param	pFunction				Callback function, will be called when FBAnimationNode of this constraint is being evaluated. Passing NULL disable notification.
	*	\param	pCustomData				Customer can pass custom data to callback.
	*	\return Confirms that change was made to pBackgroundEvaluateInfo
	*	\note	Example of usage can be found in /OpenRealitySDK/Samples/constraints/CharacterSolver/IK2014Solver
	*/
	bool			BackgroundEvaluateInfoNotify(FBEvaluateInfo* pBackgroundEvaluateInfo, kBackgroundEvaluationCallback pFunction, void* pCustomData=NULL);

	void			ResetConnectorSetup();
	
	virtual FBCharacterManipulatorCtrlSet* CreateCharacterManipulatorCtrlSet(const char* pName);

	//! Version of the solver. Needs to be overloaded in derived class.
	virtual double	GetCharacterSolverVersion() { return 1.0; };
	
	/**	Return number of extra FK model (ex. extra shoulder)
	*	\return	number of extra FK.
	*/
    virtual int         GetExtraFKCount() { return 0; }
	/**	Return the specified extra FK Name (ex. extra shoulder)
	*	\param	pIndex	Index of extra FK to get.
	*	\return	Name corresponding to FK index.
	*/
    virtual const char* GetExtraFKNameAt(int pIndex) { return NULL; }
	/**	Return The specified extra FK BodyPart (ex. Left Arm )
	*	\param	pIndex	Index of extra Bone to get.
	*	\return	BodyPart associated with this model.
	*/
    virtual FBBodyPartId GetExtraFKBodyPartAt(int pIndex) { return kFBCtrlSetPartNone; }
    /**	Return number of extra Bone model (ex. extra shoulder)
	*	\return	number of extra Bone.
	*/
    virtual int         GetExtraBoneCount() { return 0; }
	/**	Return The specified extra Bone name (ex. extra shoulder)
	*	\param	pIndex	Index of extra Bone to get.
	*	\return	Name corresponding to Bone index.
	*/
    virtual const char* GetExtraBoneNameAt(int pIndex) { return NULL; }
	/**	Return The specified extra Bone BodyPart (ex. Left Arm )
	*	\param	pIndex	Index of extra Bone to get.
	*	\return	BodyPart associated with this model.
	*/
    virtual FBBodyPartId GetExtraBoneBodyPartAt(int pIndex) { return kFBCtrlSetPartNone; }

	/**	Return The specified extra Bone model (ex. extra shoulder)
	*	\param	pIndex	Index of extra Bone to get.
	*	\return	FBModel corresponding to Bone index.
	*/
    FBModel*    GetExtraBoneModelAt(int pIndex);
	/**	Return the specified extra FK model (ex. extra shoulder)
	*	\param	pIndex	Index of extra FK to get.
	*	\return	FBModel corresponding to FK index.
	*/
    FBModelMarker*    GetExtraFKModelAt(int pIndex);



	/**	Set the specified extra Bone model for a specified Extra Bone Index. (ex. extra shoulder)
	*	\param	pModel	Extra Bone Model used for characterization.
	*	\param	pIndex	Index of extra Bone to set.
	*/
    void    SetExtraBoneModelAt(FBModel* pModel, int pIndex);
	/**	Set the specified extra FK model for a specified Extra FK Index (ex. extra shoulder)
	*	\param	pModel	Extra FK Model used for character Rig
	*	\param	pIndex	Index of extra FK to set.
	*/
    void    SetExtraFKModelAt(FBModelMarker* pModel, int pIndex);

	/**	Extract Transforms Of Extra Bones for character stance pose information
    */
    void ExtractOffsets();
	/**	Get the transform of the Given Extra Bone Index.  The transorm is the Global Transform
    *    extracted at Characterisation (in Stance Pose)
	*	\param	pT	return Global Translation in Stance Pose.
	*	\param	pR	return Global Rotation in Stance Pose.
	*	\param	pS	return Global Scaling in Stance Pose.
	*	\param	pIndex	Index of extra Bone to get.
	*/
    void GetTransformOffset( FBVector3d &pT, FBRVector &pR, FBSVector &pS, int pIndex );
	/**	Set the transform of the Given Extra Bone Index.  The transorm is the Global Transform
    *    extracted at Characterisation (in Stance Pose)
	*	\param	pT	Global Translation to set for the Stance Pose.
	*	\param	pR	Global Rotation to set for the Stance Pose.
	*	\param	pS	Global Scaling to set for the Stance Pose.
	*	\param	pIndex	Index of extra Bone to set.
	*/
    void SetTransformOffset( FBVector3d &pT, FBRVector &pR, FBSVector &pS, int pIndex );
	/**	Get the Parent Rotation Offset of the Given Extra Bone Index.  The rotation Offset if
    *    extracted at Characterisation (in Stance Pose).  You don't need this value if the parent of the bone 
    *    is characterized too.
	*	\param	pR	Offset Rotation between the Bone and is parent at Stance Pose.
	*	\param	pIndex	Index of extra Bone to get.
	*/
    void GetParentRotationOffset( FBRVector &pR, int pIndex );
	/**	Set the Parent Rotation Offset of the Given Extra Bone Index.  The rotation Offset if
    *    extracted at Characterisation (in Stance Pose).  You don't need this value if the parent of the bone 
    *    is characterized too.
	*	\param	pR	Offset Rotation between the Bone and is parent at Stance Pose.
	*	\param	pIndex	Index of extra Bone to get.
	*/
    void SetParentRotationOffset( FBRVector &pR, int pIndex );

	/**	Paste the state of a character on another one
	*	\param	pFromCharacter	Character with the state that we want to paste.
	*	\param	pPose	Pose object containing the pose.
	*	\param	pCharacterPoseOptions	Pose options to use with this paste.
	*/    
    virtual void CharacterPasteState( FBCharacter* pFromCharacter, FBCharacterPose* pPose, FBCharacterPoseOptions& pCharacterPoseOptions) {}

    /**	Support for resetting properties that are defined and specific to custom solver
    *   Override this function in derived class so that these 'extra' properties can be reset (e.g., to default values) when
	*	"Reset All Properties" button in "Character Settings" tab in Navigator is clicked, or when FBCharacter::ResetProperties() is called. 
	*/  
    virtual void ResetExtraProperties() {};
	
	/**	Returns true when control rig has Rig Align property on.
	*/
	bool GetRigAlign();

	/**	Returns true when control rig has Double Solve property on.
	*/
	bool GetDoubleSolve();
};


// Registered Character Solver and Instanciation

/** Get character external solver count.
*   \return          Number of external character solver available.
*/
FBSDK_DLL int FBGetCharacterExternalSolverCount();

/** Get character external solver name.
*   \param pIndex    Index of external solver.
*   \return          Name of the external solver specified at the provided index.
*/
FBSDK_DLL const char* FBGetCharacterExternalSolverName(int pIndex);

/** Get character external solver index.
*   \param pName    Name of external solver.
*   \return         Index of external solver specified at the provided name.
*/
FBSDK_DLL int FBGetCharacterExternalSolverIndex(const char* pName);

/** Instanciate the given external character solver.
*   \param pIndex	Index of the registered external character solver.
*   \param pSolverName	Name of external solver.
*   \return	Instance of the external character solver specified by the Index.
*/
FBSDK_DLL FBCharacterSolver* FBInstanciateCharacterExternalSolver(int pIndex, const char *pSolverName = NULL);



#ifdef FBSDKUseNamespace
    }
#endif
#endif
