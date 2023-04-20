#ifndef __FBCHARACTERMANIPULATOR_H__
#define __FBCHARACTERMANIPULATOR_H__
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

/**	\file fbcharactermanipulator.h
*	This class allows customization of the character manipulator behavior.
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
#include <fbsdk/fbcharacter.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// Return value for manipulation functions
////////////////////////////////////////////////////////////////////////////////////
//! Manipulation Start Result.
enum FBManipulationStartResult 
{ 
	kFBManipulationOK,				//!< This is the default value to return, means that you will handle the manipulation.
	kFBManipulationOKNoUndo,		//!< This value means that the manipulation will be done, but the manipulation will not be undoable.
	kFBManipulationRefuse			//!< Manipulation will be skipped.
};

//! Manipulation Get Result.
enum FBManipulationGetResult
{ 
	kFBManipulationGetDone,         //!< Return this value when you can provided the requested value.
	kFBManipulationGetContinue,     //!< Return this value when you cannot provided the requested value, another manipulator will try to provided the value.
	kFBManipulationGetFail          //!< Return this value to prevent other manipulator to handle the request.
};

//! Manipulation Set Result.
enum FBManipulationSetResult
{ 
	kFBManipulationSetContinue,     //!< Return this value when you don't want handle the request, another manipulator will try to handle it.
	kFBManipulationSetFail          //!< Return this value when you have set the value.
};

//! Specify the referential when a manipulation function is called
enum FBReferencialType
{
	FBRefTypeNone,                  //!< No type specified.
	FBRefTypeGlobal,                //!< Referential is in global coordinate.
	FBRefTypeLocal,                 //!< Referential is in local coordinate.
	FBRefTypeLayer,                 //!< Local additive rotation.
	FBRefTypeSumLayers,             //!< Global additive rotation.
	FBRefTypeParent,                //!< Parenting mode.
};

//! Specify what to do with the provided value
enum FBSetType
{
	FBSetTypeNone,                  //!< Do nothing with the value.
	FBSetTypeExact,                 //!< Set the value directly.
	FBSetTypeCumulative,		    //!< Add the provided value to the original value.
};

//! Specify what part of the provided value should be used
enum FBSetWhat
{
	FBSetWhatNone,                  //!< Do nothing with the value.
	FBSetWhatX,                     //!< Set only the X component of the value
	FBSetWhatY,                     //!< Set only the Y component of the value
	FBSetWhatZ,                     //!< Set only the Z component of the value
	FBSetWhatXYZ,                   //!< Set the XYZ components of the value
	FBSetWhatAll,                   //!< Set all components of the value
};                                  
                                    
//! Specify how the pivot should be interpreted
enum FBManipPivot
{
	FBManipPivotObjectTranslation,  //!< Consider the translation of the pivot.
	FBManipPivotObjectRotation,     //!< Consider the rotation of the pivot.
	FBManipPivotObjectScaling,      //!< Consider the scaling of the pivot.
	FBManipPivotObjectUnknown       //!< Don't consider the pivot.
};

//! Manipulator Mode
enum FBManipMode
{
	FBManip_EditorOther,        //!< Unknown Manipulation Mode.
	FBManip_EditorTranslation,  //!< Translation Manipulation Mode.
	FBManip_EditorRotation,     //!< Rotation Manipulation Mode.
	FBManip_EditorScaling       //!< Scaling Manipulation Mode.
};

FB_DEFINE_COMPONENT( FBSDK_DLL, CharacterManipulator );
FB_DEFINE_COMPONENT( FBSDK_DLL, CharacterManipulatorCtrlSet );

////////////////////////////////////////////////////////////////////////////////////
// FBCharacterManipulator
////////////////////////////////////////////////////////////////////////////////////
/** Used to translate, rotate or scale a character.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*   This class exposes part of the functionality associated with Character manipulation.
*   This class is a pure virtual class, it defined the basic functions that a manipulator
*   must implement to be useful.
*   Here is an example of how a manipulator works (translation manipulator in this case):
*   1-  After a model has been selected in the viewer, the manipulator is displayed. 
*       The function TranslationGet() is called to determnine the location of the manipulator.
*   2-  The user select the manipualtor and start a manipulation.
*       The function TranslationIsEditable() is called. Based on the returned value, the 
*       manipulation will continue or will be stopped (the manipulator will not moved).
*   3-  If the manipulation continues, the function TranslationStartManipulation() will be called.
*       This function is useful to setup internal state before the actual manipulation starts.
*       Based on the returned value of TranslationStartManipulation(), the manipulation will continue
*       or will be stopped.
*   4-  If the manipulation continue, a TranslationSet() will be called. This function will contains
*       a new value and information about the manipulation. Use this information to set the new TRS
*       values of the manipulated model.
*   5-  TranslationGet() and TranslationSet() will be called one after the other until the
*       manipulation is done, to reposition the manipulator and to update the model location.
*   6-  When the manipulation is finished, TranslationStopManipulation() is called. 
*/
__FB_FORWARD( FBCharacterManipulator);

//! Character Manipulator class.
class FBSDK_DLL FBCharacterManipulator : public FBComponent 
{
	__FBClassDeclare( FBCharacterManipulator,FBComponent );
public:
	/** Constructor.
	*	\param	pName		Name of manipulator.
	*	\param	pObject		For internal use only (default is NULL).
	*/
	FBCharacterManipulator(const char* pName, HIObject pObject=NULL);

    /** Returned value will indicate if a translation manipulation can be done.
	*	\param	pEditable	Value to modify to indicate if a manipulation can be done.
    *   \param  pRefType    Referential of the manipulation.
    *   \return Manipulation can be done
    */
    virtual FBManipulationGetResult	    TranslationIsEditable( bool &pEditable, FBReferencialType pRefType ) = 0;

    // Manipulation Get/Set
    /** Set the value of the translation to the manipulated model.
	*	\param	pT      	New value based on manipulation done by the user.
    *   \param  pRefType    Referential of the manipulation.
    *   \param  pSetType    How to apply the provided value.
    *   \param  pSetWhat    Which component of the provided value to use.
    *   \return Indicate if we have handle the call or if we want other manipulators to handle it. 
    */
    virtual FBManipulationSetResult	    TranslationSet( FBTVector &pT, FBReferencialType pRefType, FBSetType pSetType, FBSetWhat pSetWhat ) = 0;
    /** Get the translation manipulator position.
	*	\param	pT      	FBTVector value to fill with the translation value.
    *   \param  pRefType    Referential of the manipulation.
    *   \param  pPivot      How to consider the pivot if there is one.
    *   \return Indicate if we have handle the call or if we want other manipulators to handle it. 
    */
    virtual FBManipulationGetResult	    TranslationGet( FBTVector &pT, FBReferencialType pRefType, FBManipPivot pPivot = FBManipPivotObjectTranslation ) = 0;
	
    // Manipulation
    /** Called to determine if the manipulation can be done.
    *   \param  pRefType    Referential of the manipulation.
    *   \return Indicate if we can handle the manipualtion. 
    */
	virtual FBManipulationStartResult	TranslationStartManipulation( FBReferencialType pRefType, const FBTime* pTime = NULL ) = 0;
    /** Called when the manipulation is finished.
    */
    virtual void					    TranslationStopManipulation () = 0;


    //Rotation
    /** Returned value will indicate if a rotation manipulation can be done.
	*	\param	pEditable	Value to modify to indicate if a manipulation can be done.
    *   \param  pRefType    Referential of the manipulation.
    *   \return Manipulation can be done
    */
    virtual FBManipulationGetResult		RotationIsEditable( bool &pEditable, FBReferencialType pRefType ) = 0;
	
    /* Matrix Get/Set */
    /** Set the value of the translation to the manipulated model.
	*	\param	pRM      	New value based on manipulation done by the user.
    *   \param  pRefType    Referential of the manipulation.
    *   \param  pSetType    How to apply the provided value.
    *   \param  pOnlyRoot   Manipulate only root node.
    *   \return Indicate if we have handle the call or if we want other manipulators to handle it. 
    */
    virtual FBManipulationSetResult		RotationSet( FBMatrix &pRM, FBReferencialType pRefType, FBSetType pSetType, bool pOnlyRoot = false ) = 0;
    /** Get the rotation manipulator position.
	*	\param	pRM      	FBMatrix value to fill with the rotation value.
    *   \param  pRefType    Referential of the manipulation.
    *   \return Indicate if we have handle the call or if we want other manipulators to handle it. 
    */
	virtual FBManipulationGetResult		RotationGet( FBMatrix &pRM, FBReferencialType pRefType ) = 0;

	/* Manipulation */
    /** Called to determine if the manipulation can be done.
    *   \param  pRefType    Referential of the manipulation.
    *   \return Indicate if we can handle the manipualtion. 
    */
    virtual FBManipulationStartResult	RotationStartManipulation( FBReferencialType pRefType ) = 0;
    /** Called when the manipulation is finished.
    */
    virtual void						RotationStopManipulation () = 0;

    //Scaling
    /** Returned value will indicate if a scaling manipulation can be done.
	*	\retval	pEditable	Value to modify to indicate if a manipulation can be done.
    *   \return Manipulation can be done
    */
    virtual FBManipulationGetResult	    ScalingIsEditable( bool &pEditable ) = 0;
	
    /* Manipulation Get/Set*/
    /** Set the value of the scale to the manipulated model.
	*	\param	pS      	New value based on manipulation done by the user.
    *   \param  pRefType    Referential of the manipulation.
    *   \param  pSetType    How to apply the provided value.
    *   \param  pSetWhat    Which component of the provided value to use.
    *   \return Indicate if we have handle the call or if we want other manipulators to handle it. 
    */
    virtual FBManipulationSetResult	    ScalingSet( FBSVector &pS, FBReferencialType pRefType, FBSetType pSetType, FBSetWhat pSetWhat ) = 0;
    /** Get the scale manipulator position.
	*	\param	pS      	FBSVector value to fill with the scale value.
    *   \param  pRefType    Referential of the manipulation.
    *   \return Indicate if we have handle the call or if we want other manipulators to handle it. 
    */
    virtual FBManipulationGetResult	    ScalingGet( FBSVector &pS, FBReferencialType pRefType ) = 0;

    /* Manipulation */
    /** Called to determine if the manipulation can be done.
    *   \param  pRefType    Referential of the manipulation.
    *   \return Indicate if we can handle the manipualtion. 
    */
    virtual FBManipulationStartResult   ScalingStartManipulation( FBReferencialType pRefType ) = 0;
    /** Called when the manipulation is finished.
    */
    virtual void					    ScalingStopManipulation () = 0;

   /** Call this to know if the Button Release is on when manipulating
    *   \return true if Release Pin is pressed in Character Tool. 
    */
    bool    IsReleasePinPressed();

   /** return the manipulated Model
    *   \return Model being manipulated
    */
    FBModel *GetManipulatedNode();

   /** return the manipulator Mode
    *   \return Manipulation Mode
    */
    FBManipMode GetManipulatorMode();
};

/** Manipulator class declaration.
*	\param	ClassName	Manipulator class name.
*	\param	Parent		Parent class name.
*	\warning The class must inherit directly from FBCharacterManipulatorContact.
*/
#define FBCharacterManipulatorCtrlSetDeclare( ClassName, Parent ) \
	FBClassDeclare( ClassName, Parent ); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/** Manipulator class implementation.
*	\param	ThisComponent The name of the class to implement.
*/
#define FBCharacterManipulatorCtrlSetImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBCharacterManipulatorCtrlSet
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCharacterManipulatorCtrlSet);

//! Constraint class.
class FBSDK_DLL FBCharacterManipulatorCtrlSet : public FBCharacterManipulator 
{
	__FBClassDeclare( FBCharacterManipulatorCtrlSet,FBCharacterManipulator );
public:
	/** Constructor.
	*	\param	pName		Name of manipulator.
	*	\param	pObject		For internal use only (default is NULL).
	*/
	FBCharacterManipulatorCtrlSet(const char* pName, HIObject pObject=NULL);

    /** Returns the character being manipulated.
    *   \return The character being manipulated.
    */
    FBCharacter *                       GetCharacter();

    /** Override this method to allocate the necessary state requires when manipulating a character.  
    *   This method is called once when the character is connected to the solver
	*	\param	pCharacter		Character that will be manipulated by the manipulator.
    */
    virtual void                        AllocateState(FBCharacter* pCharacter);

    /** Override this method to deallocate the state allocate in the AllocateState() function.  
    *   This method is called once when the character is disconnected from the solver
    */
    virtual void                        DeallocateState();

    /** Determine if the character is in Full Body keying mode.
    *   \return Returns true if the character is in Full Body keying mode.
    */
    bool                                IsFullBody(); 

    /** Determine if the character is in Full Body - No Pull keying mode.
    *   \return Returns true if the character is in Full Body - No Pull keying mode.
    */
    bool                                IsFullBodyNoPull(); 

    /** Determine if the character is in Body Part keying mode.
    *   \return Returns true if the character is in Body Part keying mode.
    */
    bool                                IsBodyPart(); 

    /** Determine if the reach override option is enable for the manipulated character.
    *   \return Returns true if the reach override option is enable. 
    */
    bool                                IsReachOverride();

    /** Determine if the stiffness override option is enable for the manipulated character.
    *   \return Returns true if the stiffness override option is enable.
    */
    bool                                IsStiffnessOverride();

    /** Determine if IK pivot are used when manipualting a character.
    *   \return Returns true if the IK pivot are used. 
    */
    bool                                IsIKPivotUse();

    /** Synchronize the character after doing a manipulation using this function.
    */
    virtual void                        SyncCharacter(FBEvaluateInfo *pEvalInfo);
   
    /** Find the index of the currently manipulated effector for Translation or Rotation depending of Mode.
    *   \return Returns the index of the effector or kFBInvalidEffectorId if no effector is manipulated or if the reference is manipulated. 
    */
    FBEffectorId                        GetManipulatedEffectorId();

    /** Find the index of the currently manipulated effector for Rotation Only.
    *   \return Returns the index of the effector or kFBInvalidEffectorId if no effector is manipulated or if the reference is manipulated. 
    */
    FBEffectorId                        GetManipulatedEffectorIdForRotation();

    /** Find the index of the currently manipulated effector For Translation.
    *   \return Returns the index of the effector or kFBInvalidEffectorId if no effector is manipulated or if the reference is manipulated. 
    */
    FBEffectorId                        GetManipulatedEffectorIdForTranslation();

    /** Find the index of the currently manipulated effector set.
    *   \return Returns the index of the manipulated effector set. 
    */
    FBEffectorSetID                     GetEffectorSet();

    /** Find the index of the currently manipulated effector set.
    *   \return Returns the index of the manipulated effector set. 
    */
    FBBodyNodeId                        GetManipulatedBodyNode();

    /** Determine if one of the effector's child has a IK Pull value bigger than 0.5 on the current manipulated character.
	*	\param	pEffectorId		Effector to verify if his child effectors are pulling.
    *   \return Returns true is one of the effector's child has an IK Pull value > 0.5. 
    */
    bool                                IsDescendantPulling(FBEffectorId pEffectorId);

    /** Return the child effector count of the provided effector based on the skeleton hierarchy.
	*	\param	pEffectorId		Effector to get to number of child effector of.
    *   \return Returns the number of child for the effector index provided. 
    */
    int                                 GetDescendantEffectorCount(FBEffectorId pEffectorId);

    /** Return the child effector for the provided effector.
	*	\param	pEffectorId		Effector to get the child effector of.
	*	\param	pIndex  		Index of the child effector.
    *   \return Returns the child effector of the provided effector index. 
    */
    FBEffectorId                        GetDescendantEffector(FBEffectorId pEffectorId, int pIndex);

    /** Get the reach T (IK Blend T since MotionBuilder 2013) value for a specified effector on the current manipulated character.
	*	\param	pEffectorId		Effector to get the reach value.
    *   \return Returns the value of the translation reach. 
    */
    float                               GetEffectorReachTValue(int pEffectorId);              
    /** Set the reach T (IK Blend T since MotionBuilder 2013) value for a specified effector on the current manipulated character.
	*	\param	pEffectorId		Effector to set the reach value.
	*	\param	pValue		    New translation reach for the effector.
    */
    void                                SetEffectorReachTValue(int pEffectorId, float pValue);              

    /** Get the pull (IK Pull since MotionBuilder 2013) value for a specified effector on the current manipulated character.
	*	\param	pEffectorId		Effector to get the IK Pull value.
    *   \return Returns the pull value. 
    */
    float                               GetEffectorPullValue(int pEffectorId);              
    /** Set the pull (IK Pull since MotionBuilder 2013) value for a specified effector on the current manipulated character.
	*	\param	pEffectorId		Effector to set the IK Pull value.
	*	\param	pValue		    New IK Pull value for the effector.
    */
    void                                SetEffectorPullValue(int pEffectorId, float pValue);              

    /** Set the translation for the specified effector on the current manipulated character in global coordinate.
	*	\param	pVector		    New translation value.
	*	\param	pEffectorId		Effector to set the IK Pull value.
    */
    void                                TranslationSetGlobal(FBTVector pVector, int pEffectorId);
    /** Set the translation for the specified effector on the current manipulated character in local coordinate.
	*	\param	pVector		    New translation value.
	*	\param	pEffectorId		Effector to set the IK Pull value.
    */
    void                                TranslationSetLocal(FBTVector pVector, int pEffectorId);

    //For the following function, please see the description in the parent class.
    //Translation
    virtual FBManipulationGetResult	    TranslationIsEditable( bool &pEditable, FBReferencialType pRefType ) override;
	// Manipulation Get/Set
    virtual FBManipulationSetResult	    TranslationSet( FBTVector &pT, FBReferencialType pRefType, FBSetType pSetType, FBSetWhat pSetWhat ) override;
	virtual FBManipulationGetResult	    TranslationGet( FBTVector &pT, FBReferencialType pRefType, FBManipPivot pPivot = FBManipPivotObjectTranslation ) override;
	// Manipulation
	virtual FBManipulationStartResult	TranslationStartManipulation( FBReferencialType pRefType, const FBTime* pTime = NULL ) override;
	void					            TranslationStopManipulation () override;

    //Rotation
    virtual FBManipulationGetResult		RotationIsEditable( bool &pEditable, FBReferencialType pRefType ) override;
	/* Matrix Get/Set */
    virtual FBManipulationSetResult		RotationSet( FBMatrix &pRM, FBReferencialType pRefType, FBSetType pSetType, bool pOnlyRoot = false ) override;
	virtual FBManipulationGetResult		RotationGet( FBMatrix &pRM, FBReferencialType pRefType ) override;
	/* Manipulation */
	virtual FBManipulationStartResult	RotationStartManipulation( FBReferencialType pRefType ) override;
	virtual void						RotationStopManipulation () override;

    //Scaling
    virtual FBManipulationGetResult	    ScalingIsEditable( bool &pEditable ) override;
	/* Manipulation Get/Set*/
	virtual FBManipulationGetResult	    ScalingGet( FBSVector &pS, FBReferencialType pRefType ) override;
    virtual FBManipulationSetResult	    ScalingSet( FBSVector &pS, FBReferencialType pRefType, FBSetType pSetType, FBSetWhat pSetWhat ) override;
	/* Manipulation */
	virtual FBManipulationStartResult   ScalingStartManipulation( FBReferencialType pRefType ) override;
	virtual void					    ScalingStopManipulation () override;
};

#ifdef FBSDKUseNamespace
    }
#endif
#endif
