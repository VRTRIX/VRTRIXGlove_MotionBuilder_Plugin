#ifndef __FBCHARACTER_H__
#define __FBCHARACTER_H__
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

/** \file fbcharacter.h
*	Contains definitions for actors, characters, and marker sets <b>In Development</b>.
*	\warning
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbconstraint.h>
#include <fbsdk/fbcycleanalysisnode.h>
#include <fbsdk/fbcharacterextension.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

class FBCharacterSolver;

//! All Skeleton nodes   
enum FBSkeletonNodeId
{	
	kFBSkeletonInvalidIndex = -1, 
	kFBSkeletonHipsIndex = 0, 
	kFBSkeletonLeftHipIndex,
	kFBSkeletonLeftKneeIndex,
	kFBSkeletonLeftAnkleIndex,
	kFBSkeletonLeftFootIndex,
	kFBSkeletonRightHipIndex,
	kFBSkeletonRightKneeIndex,
	kFBSkeletonRightAnkleIndex,
	kFBSkeletonRightFootIndex,
	kFBSkeletonWaistIndex,
	kFBSkeletonChestIndex,
	kFBSkeletonLeftCollarIndex,
	kFBSkeletonLeftShoulderIndex,
	kFBSkeletonLeftElbowIndex,
	kFBSkeletonLeftWristIndex,
	kFBSkeletonRightCollarIndex,
	kFBSkeletonRightShoulderIndex,
	kFBSkeletonRightElbowIndex,
	kFBSkeletonRightWristIndex,
	kFBSkeletonNeckIndex,
	kFBSkeletonHeadIndex,
	kFBSkeletonLeftThumbAIndex,
	kFBSkeletonLeftThumbBIndex,
	kFBSkeletonLeftThumbCIndex,
	kFBSkeletonLeftIndexAIndex,
	kFBSkeletonLeftIndexBIndex,
	kFBSkeletonLeftIndexCIndex,
	kFBSkeletonLeftMiddleAIndex,
	kFBSkeletonLeftMiddleBIndex,
	kFBSkeletonLeftMiddleCIndex,
	kFBSkeletonLeftRingAIndex,
	kFBSkeletonLeftRingBIndex,
	kFBSkeletonLeftRingCIndex,
	kFBSkeletonLeftPinkyAIndex,
	kFBSkeletonLeftPinkyBIndex,
	kFBSkeletonLeftPinkyCIndex,
	kFBSkeletonRightThumbAIndex,
	kFBSkeletonRightThumbBIndex,
	kFBSkeletonRightThumbCIndex,
	kFBSkeletonRightIndexAIndex,
	kFBSkeletonRightIndexBIndex,
	kFBSkeletonRightIndexCIndex,
	kFBSkeletonRightMiddleAIndex,
	kFBSkeletonRightMiddleBIndex,
	kFBSkeletonRightMiddleCIndex,
	kFBSkeletonRightRingAIndex,
	kFBSkeletonRightRingBIndex,
	kFBSkeletonRightRingCIndex,
	kFBSkeletonRightPinkyAIndex,
	kFBSkeletonRightPinkyBIndex,
	kFBSkeletonRightPinkyCIndex,
	kFBSkeletonReferenceIndex,
	kFBSkeletonLastIndex
};

//! All body nodes
enum FBBodyNodeId 
{
	kFBInvalidNodeId = -1,
	kFBHipsNodeId = 0,             //!< Required.
	kFBLeftHipNodeId,              //!< Required.
	kFBLeftKneeNodeId,             //!< Required.
	kFBLeftAnkleNodeId,            //!< Required.
	kFBLeftFootNodeId,             //!<
	kFBRightHipNodeId,             //!< Required.
	kFBRightKneeNodeId,            //!< Required.
	kFBRightAnkleNodeId,           //!< Required.
	kFBRightFootNodeId,            //!<
	kFBWaistNodeId,		        //!< Required, Spine 0.
	kFBChestNodeId,		        //!< Spine 1.
	kFBLeftCollarNodeId,           //!<
	kFBLeftShoulderNodeId,         //!< Required.
	kFBLeftElbowNodeId,            //!< Required.
	kFBLeftWristNodeId,            //!< Required.
	kFBRightCollarNodeId,          //!<
	kFBRightShoulderNodeId,        //!< Required.
	kFBRightElbowNodeId,           //!< Required.
	kFBRightWristNodeId,           //!< Required.
	kFBNeckNodeId,                 //!<
	kFBHeadNodeId,                 //!< Required.
	kFBLeftHipRollNodeId,          //!<
	kFBLeftKneeRollNodeId,         //!<
	kFBRightHipRollNodeId,         //!<
	kFBRightKneeRollNodeId,        //!<
    kFBLeftShoulderRollNodeId,     //!<
    kFBLeftElbowRollNodeId,        //!<
    kFBRightShoulderRollNodeId,    //!<
    kFBRightElbowRollNodeId,       //!<
	kFBSpine2NodeId,               //!<
	kFBSpine3NodeId,               //!<
	kFBSpine4NodeId,               //!<
	kFBSpine5NodeId,               //!<
	kFBSpine6NodeId,               //!<
	kFBSpine7NodeId,               //!<
	kFBSpine8NodeId,               //!<
	kFBSpine9NodeId,               //!<
	kFBLeftThumbANodeId,           //!<
	kFBLeftThumbBNodeId,           //!<
	kFBLeftThumbCNodeId,           //!<
	kFBLeftIndexANodeId,           //!<
	kFBLeftIndexBNodeId,           //!<
	kFBLeftIndexCNodeId,           //!<
	kFBLeftMiddleANodeId,          //!<
	kFBLeftMiddleBNodeId,          //!<
	kFBLeftMiddleCNodeId,          //!<
	kFBLeftRingANodeId,            //!<
	kFBLeftRingBNodeId,            //!<
	kFBLeftRingCNodeId,            //!<
	kFBLeftPinkyANodeId,           //!<
	kFBLeftPinkyBNodeId,           //!<
	kFBLeftPinkyCNodeId,           //!<
    kFBRightThumbANodeId,          //!<
    kFBRightThumbBNodeId,          //!<
    kFBRightThumbCNodeId,          //!<
    kFBRightIndexANodeId,          //!<
    kFBRightIndexBNodeId,          //!<
    kFBRightIndexCNodeId,          //!<
    kFBRightMiddleANodeId,         //!<
    kFBRightMiddleBNodeId,         //!<
    kFBRightMiddleCNodeId,         //!<
    kFBRightRingANodeId,           //!<
    kFBRightRingBNodeId,           //!<
    kFBRightRingCNodeId,           //!<
    kFBRightPinkyANodeId,          //!<
    kFBRightPinkyBNodeId,          //!<
    kFBRightPinkyCNodeId,          //!<
	kFBReferenceNodeId,            //!<
    // -- New bones for 2.0 --
    kFBLeftThumbInNodeId,          //!<
    kFBLeftThumbDNodeId,           //!<
    kFBLeftIndexInNodeId,          //!<
    kFBLeftIndexDNodeId,           //!<
    kFBLeftMiddleInNodeId,         //!<
    kFBLeftMiddleDNodeId,          //!<
    kFBLeftRingInNodeId,           //!<
    kFBLeftRingDNodeId,            //!<
    kFBLeftPinkyInNodeId,          //!<
    kFBLeftPinkyDNodeId,           //!<
    kFBRightThumbInNodeId,         //!<
    kFBRightThumbDNodeId,          //!<
    kFBRightIndexInNodeId,         //!<
    kFBRightIndexDNodeId,          //!<
    kFBRightMiddleInNodeId,        //!<
    kFBRightMiddleDNodeId,         //!<
    kFBRightRingInNodeId,          //!<
    kFBRightRingDNodeId,           //!<
    kFBRightPinkyInNodeId,         //!<
    kFBRightPinkyDNodeId,          //!<

    kFBLeftExtraFingerInNodeId,    //!< New extra finger bone
    kFBLeftExtraFingerANodeId,     //!< New extra finger bone
    kFBLeftExtraFingerBNodeId,     //!< New extra finger bone
    kFBLeftExtraFingerCNodeId,     //!< New extra finger bone
    kFBLeftExtraFingerDNodeId,     //!< New extra finger bone
    kFBRightExtraFingerInNodeId,   //!< New extra finger bone
    kFBRightExtraFingerANodeId,    //!< New extra finger bone
    kFBRightExtraFingerBNodeId,    //!< New extra finger bone
    kFBRightExtraFingerCNodeId,    //!< New extra finger bone
    kFBRightExtraFingerDNodeId,    //!< New extra finger bone

    kFBLeftFootThumbInNodeId,      //!<
    kFBLeftFootThumbANodeId,       //!<
	kFBLeftFootThumbBNodeId,       //!<
	kFBLeftFootThumbCNodeId,       //!<
    kFBLeftFootThumbDNodeId,       //!<
	kFBLeftFootIndexInNodeId,      //!<
    kFBLeftFootIndexANodeId,       //!<
	kFBLeftFootIndexBNodeId,       //!<
	kFBLeftFootIndexCNodeId,       //!<
    kFBLeftFootIndexDNodeId,       //!<
	kFBLeftFootMiddleInNodeId,     //!<
    kFBLeftFootMiddleANodeId,      //!<
	kFBLeftFootMiddleBNodeId,      //!<
	kFBLeftFootMiddleCNodeId,      //!<
    kFBLeftFootMiddleDNodeId,      //!<
	kFBLeftFootRingInNodeId,       //!<
    kFBLeftFootRingANodeId,        //!<
	kFBLeftFootRingBNodeId,        //!<
	kFBLeftFootRingCNodeId,        //!<
    kFBLeftFootRingDNodeId,        //!<
	kFBLeftFootPinkyInNodeId,      //!<
    kFBLeftFootPinkyANodeId,       //!<
	kFBLeftFootPinkyBNodeId,       //!<
	kFBLeftFootPinkyCNodeId,       //!<
    kFBLeftFootPinkyDNodeId,       //!<
    kFBRightFootThumbInNodeId,     //!<
    kFBRightFootThumbANodeId,      //!<
    kFBRightFootThumbBNodeId,      //!<
    kFBRightFootThumbCNodeId,      //!<
    kFBRightFootThumbDNodeId,      //!<
    kFBRightFootIndexInNodeId,     //!<
    kFBRightFootIndexANodeId,      //!<
    kFBRightFootIndexBNodeId,      //!<
    kFBRightFootIndexCNodeId,      //!<
    kFBRightFootIndexDNodeId,      //!<
    kFBRightFootMiddleInNodeId,    //!<
    kFBRightFootMiddleANodeId,     //!<
    kFBRightFootMiddleBNodeId,     //!<
    kFBRightFootMiddleCNodeId,     //!<
    kFBRightFootMiddleDNodeId,     //!<
    kFBRightFootRingInNodeId,      //!<
    kFBRightFootRingANodeId,       //!<
    kFBRightFootRingBNodeId,       //!<
    kFBRightFootRingCNodeId,       //!<
    kFBRightFootRingDNodeId,       //!<
    kFBRightFootPinkyInNodeId,     //!<
    kFBRightFootPinkyANodeId,      //!<
    kFBRightFootPinkyBNodeId,      //!<
    kFBRightFootPinkyCNodeId,      //!<
    kFBRightFootPinkyDNodeId,      //!<

    kFBLeftExtraFootFingerInNodeId,        //!< New extra finger bone
    kFBLeftExtraFootFingerANodeId,         //!< New extra finger bone
    kFBLeftExtraFootFingerBNodeId,         //!< New extra finger bone
    kFBLeftExtraFootFingerCNodeId,         //!< New extra finger bone
    kFBLeftExtraFootFingerDNodeId,         //!< New extra finger bone
    kFBRightExtraFootFingerInNodeId,       //!< New extra finger bone
    kFBRightExtraFootFingerANodeId,        //!< New extra finger bone
    kFBRightExtraFootFingerBNodeId,        //!< New extra finger bone
    kFBRightExtraFootFingerCNodeId,        //!< New extra finger bone
    kFBRightExtraFootFingerDNodeId,        //!< New extra finger bone

	kFBLeftHandNodeId,             //!<
	kFBRightHandNodeId,            //!<
    kFBNeck1NodeId,                //!<
	kFBNeck2NodeId,                //!<
	kFBNeck3NodeId,                //!<
	kFBNeck4NodeId,                //!<
	kFBNeck5NodeId,                //!<
	kFBNeck6NodeId,                //!<
	kFBNeck7NodeId,                //!<
	kFBNeck8NodeId,                //!<
	kFBNeck9NodeId,                //!<

    kFBHipsTranslationNodeId,       //!<
    
    // -- HIK 2016.5 new leaf roll nodes --
    // this should be consistent with HipsNodeId defined in kernel\humanik.h
    // so HIKNodeTypeFromNodeId & HIKNodeIndexFromNodeId could map to correct
    // data.
    // kFBLastNodeId_Old represent last id before introduction of new roll bone for
    // previous solvers. First new roll bone id equals to ensure continuity
    kFBLastNodeId_Old, 
    kFBLeftHipRollNode1Id = kFBLastNodeId_Old,              //!< New leaf roll bone
    kFBLeftKneeRollNode1Id,                                 //!< New leaf roll bone
    kFBRightHipRollNode1Id,                                 //!< New leaf roll bone
    kFBRightKneeRollNode1Id,                                //!< New leaf roll bone
    kFBLeftShoulderRollNode1Id,                             //!< New leaf roll bone
    kFBLeftElbowRollNode1Id,                                //!< New leaf roll bone
    kFBRightShoulderRollNode1Id,                            //!< New leaf roll bone
    kFBRightElbowRollNode1Id,                               //!< New leaf roll bone

    kFBLeftHipRollNode2Id,                                  //!< New leaf roll bone
    kFBLeftKneeRollNode2Id,                                 //!< New leaf roll bone
    kFBRightHipRollNode2Id,                                 //!< New leaf roll bone
    kFBRightKneeRollNode2Id,                                //!< New leaf roll bone
    kFBLeftShoulderRollNode2Id,                             //!< New leaf roll bone
    kFBLeftElbowRollNode2Id,                                //!< New leaf roll bone
    kFBRightShoulderRollNode2Id,                            //!< New leaf roll bone
    kFBRightElbowRollNode2Id,                               //!< New leaf roll bone

    kFBLeftHipRollNode3Id,                                  //!< New leaf roll bone
    kFBLeftKneeRollNode3Id,                                 //!< New leaf roll bone
    kFBRightHipRollNode3Id,                                 //!< New leaf roll bone
    kFBRightKneeRollNode3Id,                                //!< New leaf roll bone
    kFBLeftShoulderRollNode3Id,                             //!< New leaf roll bone
    kFBLeftElbowRollNode3Id,                                //!< New leaf roll bone
    kFBRightShoulderRollNode3Id,                            //!< New leaf roll bone
    kFBRightElbowRollNode3Id,                               //!< New leaf roll bone

    kFBLeftHipRollNode4Id,                                  //!< New leaf roll bone
    kFBLeftKneeRollNode4Id,                                 //!< New leaf roll bone
    kFBRightHipRollNode4Id,                                 //!< New leaf roll bone
    kFBRightKneeRollNode4Id,                                //!< New leaf roll bone
    kFBLeftShoulderRollNode4Id,                             //!< New leaf roll bone
    kFBLeftElbowRollNode4Id,                                //!< New leaf roll bone
    kFBRightShoulderRollNode4Id,                            //!< New leaf roll bone
    kFBRightElbowRollNode4Id,                               //!< New leaf roll bone

    kFBLeftHipRollNode5Id,                                  //!< New leaf roll bone
    kFBLeftKneeRollNode5Id,                                 //!< New leaf roll bone
    kFBRightHipRollNode5Id,                                 //!< New leaf roll bone
    kFBRightKneeRollNode5Id,                                //!< New leaf roll bone
    kFBLeftShoulderRollNode5Id,                             //!< New leaf roll bone
    kFBLeftElbowRollNode5Id,                                //!< New leaf roll bone
    kFBRightShoulderRollNode5Id,                            //!< New leaf roll bone
    kFBRightElbowRollNode5Id,                               //!< New leaf roll bone

    kFBLastNodeId				    //!<
};

//! Last Actor NodeId
const int kFBLastActorNodeId = ( kFBHeadNodeId + 1 );

//! All effector nodes
enum FBEffectorId
{
	kFBInvalidEffectorId = -1,         //!<
	kFBHipsEffectorId = 0,             //!<
	kFBLeftAnkleEffectorId,            //!<
	kFBRightAnkleEffectorId,           //!<
	kFBLeftWristEffectorId,            //!<
	kFBRightWristEffectorId,           //!<
	kFBLeftKneeEffectorId,             //!<
	kFBRightKneeEffectorId,            //!<
	kFBLeftElbowEffectorId,            //!<
	kFBRightElbowEffectorId,           //!<
	kFBChestOriginEffectorId,          //!<
	kFBChestEndEffectorId,             //!<
	kFBLeftFootEffectorId,             //!<
	kFBRightFootEffectorId,            //!<
	kFBLeftShoulderEffectorId,         //!<
	kFBRightShoulderEffectorId,        //!<
	kFBHeadEffectorId,                 //!<
	kFBLeftHipEffectorId,              //!<
	kFBRightHipEffectorId,             //!<
    // -- New effector for 2.0 --
    kFBLeftHandEffectorId,             //!<
	kFBRightHandEffectorId,            //!<
	kFBLeftHandThumbEffectorId,        //!<
	kFBLeftHandIndexEffectorId,        //!<
	kFBLeftHandMiddleEffectorId,       //!<
	kFBLeftHandRingEffectorId,         //!<
	kFBLeftHandPinkyEffectorId,        //!<
	kFBLeftHandExtraFingerEffectorId,  //!<
	kFBRightHandThumbEffectorId,       //!<
	kFBRightHandIndexEffectorId,       //!<
	kFBRightHandMiddleEffectorId,      //!<
	kFBRightHandRingEffectorId,        //!<
	kFBRightHandPinkyEffectorId,       //!<
	kFBRightHandExtraFingerEffectorId, //!<
	kFBLeftFootThumbEffectorId,        //!<
	kFBLeftFootIndexEffectorId,        //!<
	kFBLeftFootMiddleEffectorId,       //!<
	kFBLeftFootRingEffectorId,         //!<
	kFBLeftFootPinkyEffectorId,        //!<
	kFBLeftFootExtraFingerEffectorId,  //!<
	kFBRightFootThumbEffectorId,       //!<
	kFBRightFootIndexEffectorId,       //!<
	kFBRightFootMiddleEffectorId,      //!<
	kFBRightFootRingEffectorId,        //!<
	kFBRightFootPinkyEffectorId,       //!<
	kFBRightFootExtraFingerEffectorId, //!<
	kFBLastEffectorId				   //!<
};

//! Effector ID identifier
enum FBEffectorSetID
{	
	FBEffectorSetDefault = 0, 
	FBEffectorSetAux1, 
	FBEffectorSetAux2, 
	FBEffectorSetAux3, 
	FBEffectorSetAux4, 
	FBEffectorSetAux5, 
	FBEffectorSetAux6, 
	EFBffectorSetAux7, 
	FBEffectorSetAux8, 
	FBEffectorSetAux9, 
	FBEffectorSetAux10, 
	FBEffectorSetAux11, 
	FBEffectorSetAux12, 
	FBEffectorSetAux13, 
	FBEffectorSetAux14, 
	FBLastEffectorSetIndex 
};

//! Floor contact for the given index.
enum FBFloorContactID
{
	FBLeftHandMemberIndex,
	FBRightHandMemberIndex,
	FBLeftFootMemberIndex,
	FBRightFootMemberIndex,	
	FBLastCharacterMember
};

//! Body part for character 
enum FBBodyPartId
{ 
	kFBCtrlSetPartNone = 0,     //!< No part selected.
	kFBCtrlSetPartHips,         //!< Hips Body Part.
	kFBCtrlSetPartChest,        //!< Chest Body Part.
	kFBCtrlSetPartLeftArm,      //!< Left Arm Body Part.
	kFBCtrlSetPartRightArm,     //!< Right Arm Body Part.
	kFBCtrlSetPartLeftLeg,      //!< Left Leg Body Part.
	kFBCtrlSetPartRightLeg,     //!< Right Leg Body Part.
	kFBCtrlSetPartHead,         //!< Head Body Part.
	kFBCtrlSetPartLeftHand,     //!< Left Hand Body Part.
	kFBCtrlSetPartRightHand,    //!< Right Hand Body Part.
	kFBCtrlSetPartLeftFoot,     //!< Left Foot Body Part.
	kFBCtrlSetPartRightFoot,    //!< Right Foot Body Part.
	kFBLastCtrlSetPartIndex     //!< Part count.
};



//! Character Input/Output types.
enum FBCharacterInputType
{ 
	kFBCharacterInputActor, 
	kFBCharacterInputCharacter,
	kFBCharacterInputMarkerSet, 
	kFBCharacterOutputMarkerSet, 
	kFBCharacterInputStance,
	kFBCharacterInputMoCap
};
FB_DEFINE_ENUM( FBSDK_DLL, CharacterInputType );

//! Character keying modes.
enum FBCharacterKeyingMode
{ 
	kFBCharacterKeyingFullBody, 
	kFBCharacterKeyingBodyPart,
	kFBCharacterKeyingSelection, 
	kFBCharacterKeyingFullBodyNoPull, 
};
FB_DEFINE_ENUM( FBSDK_DLL, CharacterKeyingMode );

//! Character Reset Properties Type.
enum FBCharacterResetProperties
{
	kFBCharacterResetPropertiesAll,
	kFBCharacterResetPropertiesSolving,
	kFBCharacterResetPropertiesDefinition
};

//! Where to plot a character.
enum FBCharacterPlotWhere
{
	kFBCharacterPlotOnControlRig,
	kFBCharacterPlotOnSkeleton
};
FB_DEFINE_ENUM( FBSDK_DLL, CharacterPlotWhere );

//! Character Hips Translation modes.
enum FBCharacterHipsTranslationMode 
{ 
	kFBParamHipsTranslationWorldRigid = 0, 
	kFBParamHipsTranslationBodyRigid, 
	kFBLastHipsTranslationMode 
};
FB_DEFINE_ENUM( FBSDK_DLL, CharacterHipsTranslationMode );

//! Character Roll Solver version.
enum FBCharacterRollSolver 
{ 
	kFBParamRollSolver70 = 0, 
	kFBParamRollSolver75, 
	kFBLastRollSolver
};
FB_DEFINE_ENUM( FBSDK_DLL, CharacterRollSolver );

//! Character Contact Behaviour.
enum FBCharacterContactBehaviour
{
    kFBParamContactNeverSync = 0, 
    kFBParamContactSyncOnKey, 
    kFBParamContactAlwaysSync, 
    kFBLastContactBehaviour
};
FB_DEFINE_ENUM( FBSDK_DLL, CharacterContactBehaviour );

//! Character ControlSet type.
enum FBControlSetType
{
    kFBControlSetTypeNone = 0, 
    kFBControlSetTypeFKIK, 
    kFBControlSetTypeIKOnly
};
FB_DEFINE_ENUM( FBSDK_DLL, ControlSetType );

//! Device Mocap skeleton tracking state.
enum FBSkeletonTrackingState
{
    kFBSkeletonNotTracked = 0,
    kFBSkeletonPositionOnly,
    kFBSkeletonTracked
};
FB_DEFINE_ENUM( FBSDK_DLL, SkeletonTrackingState );

//! Device Mocap skeleton joint tracking state.
enum FBSkeletonJointTrackingState
{
    kFBSkeletonJointNotTracked = 0,
    kFBSkeletonJointInferred,
    kFBSkeletonJointTracked
};
FB_DEFINE_ENUM( FBSDK_DLL, SkeletonJointTrackingState );

//! Device Mocap character calibration state.
enum FBCalibrationState
{
    FBCalibrationNoRequest = 0,
    FBCalibrationInProcessing,
    FBCalibrationSuccessfully
};
FB_DEFINE_ENUM( FBSDK_DLL, CalibrationState );

/** Get the UI name associated with a body node.
	*	\param	pBodyNodeId The body node ID.
	*	\return				The UI name for this body node.
	*/
FBSDK_DLL const char* FBCharacterBodyNodeNameFromId( FBBodyNodeId pBodyNodeId );

/** Get the UI name associated with an effector.
	*	\param	pEffectorId		The effector ID.
	*	\return					The UI name for this effector.
	*/
FBSDK_DLL const char* FBCharacterEffectorNameFromId( FBEffectorId pEffectorId );

////////////////////////////////////////////////////////////////////////////////////
// FBMarkerSet - Marker set for an actor
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBMarkerSet );
FB_DEFINE_COMPONENT( FBSDK_DLL, MarkerSet );
FB_FORWARD( FBModel );

//! typedef class FBSDK_DLL FBArrayTemplate<FBModel*> FBModelList;
typedef class FBSDK_DLL FBArrayTemplate<FBModel*> FBModelList;

/** Marker set class.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBMarkerSet : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBMarkerSet, FBComponent );
public:
	/** Constructor.
	*	\param	pName		Name of new marker set.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBMarkerSet(const char* pName, HIObject pObject=NULL);

	/** Get the reference model associated with this marker set.
	*	\return					The reference model associated with the marker set.
    */
	FBModel* GetReferenceModel( );

    /** Associate a model to a marker.
    *   \param  pReferenceModel Model to be associated to the marker.
    */
	void SetReferenceModel( FBModel* pReferenceModel );

	/** Get the model associated with a marker.
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker.
	*	\return					The model associated with the marker.
    */
	FBModel* GetMarkerModel( FBSkeletonNodeId pNodeId, int pMarkerIndex );

    /** Associate a model to a marker.
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker.
    *   \param  pModel          Model to be associated to the marker.
    */
	void SetMarkerModel( FBSkeletonNodeId pNodeId, int pMarkerIndex, FBModel* pModel );

	/** Associate multiple models to markers, matching them by name.
    *   \param  pModelList		A list of models to be matched with marker names.
    *   \return					True if at least one marker was matched.
    */
	bool SetMultipleMarkerModels( FBModelList* pModelList );

    /** Get the name of marker at index \b pMarkerIndex.
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker to access.
    *   \return Name of marker at index \b pMarkerIndex.
    */
	const char* GetMarkerName( FBSkeletonNodeId pNodeId, int pMarkerIndex );

    /** Set the name of marker at index \b pMarkerIndex.
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker to access.
    *   \param  pMarkerName     New name to give to the marker.
    */
	void SetMarkerName( FBSkeletonNodeId pNodeId, int pMarkerIndex, const char* pMarkerName );

    //@{
    /** Get/Set a marker translation.
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker to access.
    *   \retval pTOffset        Current or new value of the marker translation.
    */
	void GetMarkerTOffset( FBSkeletonNodeId pNodeId, int pMarkerIndex, FBTVector* pTOffset );
	void SetMarkerTOffset( FBSkeletonNodeId pNodeId, int pMarkerIndex, FBTVector* pTOffset );
    //@}

    //@{
    /** Get/Set a marker rotation.
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker to access.
    *   \retval pROffset        Current or new value of the marker rotation.
    */
	void GetMarkerROffset( FBSkeletonNodeId pNodeId, int pMarkerIndex, FBRVector* pROffset );
	void SetMarkerROffset( FBSkeletonNodeId pNodeId, int pMarkerIndex, FBRVector* pROffset );
    //@}

	/** Is marker orientated ?
	*	\param	pNodeId			Id of Actor body node.
    *   \param  pMarkerIndex    Index of marker to access.
    *   \return					\b True if marker is oriented, \b false otherwise.
    */
    bool GetMarkerOriented( FBSkeletonNodeId pNodeId, int pMarkerIndex );

    /** Set marker to be oriented or not.
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker to access.
    *   \param  pIsOriented     Oriented or not.
    */
	void SetMarkerOriented( FBSkeletonNodeId pNodeId, int pMarkerIndex, bool pIsOriented );

	/** Is marker used ?
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker to access.
    *   \return					\b True if marker is used, \b false otherwise.
    */
    bool GetMarkerUsed( FBSkeletonNodeId pNodeId, int pMarkerIndex );

    /** Set marker to be used or not.
	*	\param	pNodeId			Id of Actor skeleton node.
    *   \param  pMarkerIndex    Index of marker to access.
    *   \param  pUsed			Used or not.
    */
	void SetMarkerUsed( FBSkeletonNodeId pNodeId, int pMarkerIndex, bool pUsed );
	
    /** Get the number of marker in the set.
    *   \param  pNodeId			If specified, obtain the number of marker for the specific node.
    *   \return					Total number of marker.
    */
	int GetMarkerCount( FBSkeletonNodeId pNodeId = kFBSkeletonInvalidIndex );

	/** Get the number of used marker in the set.
    *   \param  pNodeId			If specified, obtain the number of used marker for the specific node.
    *   \return					Total number of used marker.
    */
	int GetUsedMarkerCount( FBSkeletonNodeId pNodeId = kFBSkeletonInvalidIndex );

    /** Add a marker to the marker set.
    *   \param	pNodeId			Id of Actor skeleton node. For hand, use the "C" index (ex:kFBSkeletonLeftThumbCIndex, kFBSkeletonLeftMiddleCIndex...)
	*	\param	pModel			The model to be associated with the marker (Optional).
	*	\param	pIsOriented		Set marker to be oriented or not (Optional).
    *   \return					Index of the new marker.
    */
	int AddMarker( FBSkeletonNodeId pNodeId, FBModel* pModel = NULL, bool pIsOriented = false );

    /** Set the marker set visibility.
    *   \param	pVisibility			True will make to markers visible, false will hide them.   
    */
    void SetMarkerSetVisibility(bool pVisibility);

    /** Get the marker set visibility.
    *   \return 1 if all markers are visible, 2 if some are visible, 0 if none are visible.   
    */
    int GetMarkerSetVisibility();

	/** Get the marker set association correctness.
    *   \return True if all used markers are link with models.
    */
	bool GetLinkToModelOk();

	/** Specify that you are about to call a group of functions.
    *   \remark This is used to speed up operations, the UI won't be refreshed until EndTransaction() is called.
    */
	void BeginTransaction( );

	/** Specify that you are  done calling a group of functions.
    *   \remark This is used to speed up operations, the UI won't be refreshed until EndTransaction() is called.
    */
	void EndTransaction( );

};

////////////////////////////////////////////////////////////////////////////////////
// FBControlSet - Control set for an actor
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBControlSet );
FB_DEFINE_COMPONENT( FBSDK_DLL, ControlSet );

/** Control set class.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBControlSet : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBControlSet, FBComponent );
public:
	/** Constructor.
	*	\param	pName		Name of new control set.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBControlSet(const char* pName, HIObject pObject=NULL);

	/** Get the reference model associated with this Control Set.
	*	\return					The reference model associated with the Control Set.
    */
	FBModel* GetReferenceModel( );

	/** Get the reference name associated with this Control Set.
	*	\return		The reference name associated with the Control Set.
    */
	const char* GetReferenceName( );

	/** Return the Index of the Given Model.
	*   \param		pModel	Given Model to Obtain Index
    *   \return		The Index of the Given Model.
    */
	int			GetIKEffectorIndex(FBModel* pModel);
	/** Return the object associated to the given Index.
	*   \param		pEffectorIndex	Given Index to obtain Model
	*   \param		pPivotIndex		Index of effector pivot
    *   \return		return the model at the specified Index.
    */
	FBModel*	GetIKEffectorModel(FBEffectorId pEffectorIndex, int pPivotIndex = 0);
	/** return the number of IK Effector Slot
    *   \return		return the number of IK Effector Slot
    */
	int			GetIKEffectorPivotCount(FBEffectorId pEffectorIndex);
	/** return the name of IK Effector 
	*   \param		pEffectorIndex	Given Index to obtain Name
    *   \return		the name of IK Effector
    */
	const char*	GetIKEffectorName(FBEffectorId pEffectorIndex);



	/** Return The Index of the Given Model.
	*   \param		pModel Given Model to obtain Index
    *   \return		The Index of the Given Model.
    */
	int			GetFKIndex(FBModel* pModel);
	/** Return the object associated to the given Index.
	*   \param		pIndex	Given Index to obtain Model
    *   \return		return the model at the specified Index.
    */
	FBModel*	GetFKModel(int pIndex);
	/** return the name of FK Effector at the given index
	*   \param		pIndex	Given Index
    *   \return		return the name of IK Effector Slot
    */
	const char*	GetFKName(int pIndex);

	/** return the number of FK Effector Slot
    *   \return		return the number of IK Effector Slot
    */
	int			GetFKCount();



    FBPropertyControlSetType ControlSetType; //!< <b>Read Property:</b> the control Set Type (FKIK or IK).
	FBPropertyBool	UseAxis; //!< <b>Read Write Property:</b> is using axis.
    FBPropertyDouble  FKOpacity; //!< <b>Read Write Property:</b> Opacity value used on FK (between 0 and 100).
};

/** Control Set State class.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
__FB_FORWARD( FBControlSetState );
class FBSDK_DLL FBControlSetState
{
public:
	/** Returned global matrix associated to the given Index.
	*   \param		pNodeId				Index of the character Node
	*   \param		pNodeGlobalMatrix	returned global matrix of the index Given
    */
	void GetNodeMatrix(FBBodyNodeId pNodeId, FBMatrix &pNodeGlobalMatrix);
};

/** Effector Set State class.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
__FB_FORWARD( FBEffectorSetState );
class FBSDK_DLL FBEffectorSetState
{
public:
	/** Returned global matrix associated to the given Index.
	*   \param		pEffectorId			Index of the effector Node
	*   \param		pEffectorGlobalMatrix	returned global matrix of the index Given
    */
	void GetEffectorMatrix(FBEffectorId pEffectorId, FBMatrix &pEffectorGlobalMatrix);

	/** Returned translation and rotation reach associated to the given Index.
	*   \param		pEffectorId		Index of the effector Node
	*   \param		pReachT			returned reach translation of the index Given
	*   \param		pReachR		returned reach rotation of the index Given
    */
	void GetReach(FBEffectorId pEffectorId, double &pReachT, double &pReachR);
};

////////////////////////////////////////////////////////////////////////////////////
// FBCharacterMarkerSet - Marker set for an character
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCharacterMarkerSet );
FB_DEFINE_COMPONENT( FBSDK_DLL, CharacterMarkerSet );

/** Character marker set class.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBCharacterMarkerSet : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBCharacterMarkerSet, FBComponent );
public:
	/** Constructor.
	*	\param	pName		Name of new character marker set.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBCharacterMarkerSet(const char* pName, HIObject pObject=NULL);

	/** Read FK and IK state from goals.
	*	\param	pFKState		Extracted FK state from goals.
	*	\param	pIKState		Extracted IK state from goals.
	*	\param	pEvaluateInfo	Evaluation info to use for this read.
	*/
	void		ReadCtrlSetAndEffectorState(FBControlSetState* pFKState, FBEffectorSetState* pIKState, FBEvaluateInfo* pEvaluateInfo);

	/** Get the marker property associated with each body part of the character.
	*	\return	The property associated with given pNodeId.
	*/
	FBProperty*	GetMarkersProperty(FBBodyNodeId pNodeId);

	/** Get the extraction property associated with each body part of the character.
	*	\return	The property associated with given pNodeId.
	*/
	FBProperty*	GetExtractionProperty(FBBodyNodeId pNodeId);

	/** Get the snap property associated with each body part of the character for given transformation.
	*	Current version snap only translation and rotation.
	*	\return	The property associated with given pNodeId and pWhat.
	*/
	FBProperty*	GetSnapProperty(FBBodyNodeId pNodeId, FBModelTransformationType pWhat);
};

/** Skeleton State class.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
__FB_FORWARD( FBSkeletonState );
class FBSDK_DLL FBSkeletonState
{
public:
	/** Returned global matrix associated to the given Index.
	*   \param		pSkeletonId				Index of the skeleton Node
	*   \param		pSkeletonGlobalMatrix	returned global matrix of the index Given
    */
	void GetNodeMatrix(FBSkeletonNodeId pSkeletonId, FBMatrix &pSkeletonGlobalMatrix);
};

////////////////////////////////////////////////////////////////////////////////
// FBActor - Representation of an actor
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBActor );
FB_DEFINE_COMPONENT( FBSDK_DLL, Actor );

//! Recalculate MarkerSet offset for?
enum FBRecalcMarkerSetOffset
{
	kFBRecalcMarkerSetOffsetTR,			//!< Recalculate MarkerSet offset for TR
	kFBRecalcMarkerSetOffsetROnly		//!< Recalculate MarkerSet offset for R Only
};

/**	FBActor is used to link motion data to a character.
* In MotionBuilder, an actor is a model used to link captured 
* motion data to a character.  Use functions in FBActor to set the body
* color, skeleton color, pivot color, marker size, pivot size, pivot
* information, etc. on an actor.
* 
*
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*
*   To obtain the list of actors present in a scene, you need to create an
*   instance of class FBSystem, to obtain the current scene. The FBScene
*   object holds the list of actors in the property Actors.
*
*   @code
*       FBSystem lSystem;
*       FBScene* lScene = lSystem.Scene;
*       for( int lIdx = 0; lIdx < lScene->Actors.GetCount(); ++lIdx )
*       {
*           FBTrace( "Actor[%d]: '%s'\n", lIdx, (char*)lScene->Actors[lIdx] );
*       }
*   @endcode
*
*   The current actor selected in the Character tool can be obtained via
*   the FBApplication object.
*
*   @code
*       FBApplication lApplication;
*       FBActor* lActor = lApplication.CurrentActor;
*       if( lActor )
*       {
*           FBTrace( "Current actor is: '%s'\n", (char*)lActor->Name );
*       }
*       else
*       {
*           FBTrace( "No actor currently selected\n" );
*       }
*   @endcode
*
*/
class FBSDK_DLL FBActor : public FBConstraint
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBActor, FBConstraint );
public:
	/** Constructor.
	*	\param	pName		Name of new actor.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBActor(const char* pName, HIObject pObject=NULL);

    /** Actual Actor destructor.
    *   This method is used to delete the actual actor object represented by an instance of FBActor.
    */
    virtual void FBDelete();

	FBPropertyMarkerSet		MarkerSet;		//!< <b>Read Write Property:</b> Associated marker set.
	FBPropertyMarkerSet		OutputMarkerSet;//!< <b>Read Write Property:</b> Associated output marker set.

	FBPropertyColor			BodyColor;		//!< <b>Read Write Property:</b> The color of the body of the actor.
	FBPropertyColor			SkeletonColor;	//!< <b>Read Write Property:</b> The color of the skeleton of the actor.
	FBPropertyColor			PivotColor;		//!< <b>Read Write Property:</b> The color of the pivot points of the actor.
	FBPropertyDouble		MarkerSetSize;	//!< <b>Read Write Property:</b> The size of the markers of the actor.
	FBPropertyDouble		PivotSize;		//!< <b>Read Write Property:</b> The size of the pivot points of the actor.

	FBPropertyVector3d		HipsPosition;			//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		LeftHipPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		LeftKneePosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		LeftAnklePosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		LeftFootPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		RightHipPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		RightKneePosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		RightAnklePosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		RightFootPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		WaistPosition;			//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		ChestPosition;			//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		LeftCollarPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		LeftShoulderPosition;	//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		LeftElbowPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		LeftWristPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		RightCollarPosition;	//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		RightShoulderPosition;	//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		RightElbowPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		RightWristPosition;		//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		NeckPosition;			//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyVector3d		HeadPosition;			//!< <b>Read Write Property:</b> Body part pivot of the actor.
	FBPropertyBool			Visibility;				//!< <b>Read Write Property:</b> Show or Hide the Actor Body.

    FBPropertyAnimatableDouble  LeftHandIndexIndex;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandIndexMiddle;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandIndexRing;      //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandIndexPinky;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.

	FBPropertyAnimatableDouble  LeftHandMiddleIndex;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandMiddleMiddle;   //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandMiddleRing;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandMiddlePinky;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.

	FBPropertyAnimatableDouble  LeftHandRingIndex;      //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandRingMiddle;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandRingRing;       //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandRingPinky;      //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.

	FBPropertyAnimatableDouble  LeftHandPinkyIndex;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandPinkyMiddle;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandPinkyRing;      //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  LeftHandPinkyPinky;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.

	FBPropertyAnimatableDouble  RightHandIndexIndex;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandIndexMiddle;   //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandIndexRing;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandIndexPinky;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.

	FBPropertyAnimatableDouble  RightHandMiddleIndex;   //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandMiddleMiddle;  //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandMiddleRing;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandMiddlePinky;   //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.

	FBPropertyAnimatableDouble  RightHandRingIndex;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandRingMiddle;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandRingRing;      //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandRingPinky;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.

	FBPropertyAnimatableDouble  RightHandPinkyIndex;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandPinkyMiddle;   //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandPinkyRing;     //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.
	FBPropertyAnimatableDouble  RightHandPinkyPinky;    //!< <b>Read Write Property:</b> Used to set blending coefficients. Each of the 4 fingers can be a blend of the 4 finger. This is not available for thumbs.

	FBPropertyAnimatableDouble  FKFingerMultiplier;    //!< <b>Read Write Property:</b> Used to augment the amount of FK propagation for unmarkered intermediate finger phalanges.
	FBPropertyAnimatableDouble  FKFingerTipMultiplier;    //!< <b>Read Write Property:</b> Used to augment the amount of FK propagation for unmarkered finger tip phalanges.
	FBPropertyAnimatableDouble  FKThumbTipMultiplier;    //!< <b>Read Write Property:</b> Used to augment the amount of FK propagation for unmarkered thumb tip phalanges.
	FBPropertyAnimatableBool  HumanFingerLimits;    //!< <b>Read Write Property:</b> Enables/Disables human finger limits during actor solve.
    

	/** Snap the marker set of the actor.
	*	\return	True if the operation completed successfully.
	*/
	virtual bool Snap( FBRecalcMarkerSetOffset pRecalcOffset );


	/** Update Internal Values to be corresponding to the Given Evaluate Information
	*   \param		pEvalInfo				Evaluate Info of the Values
    */
	void	UpdateValues( FBEvaluateInfo* pEvalInfo );

	/** Set Actor Scaling Definition
	*   \param		pSkeletonId		Skeleton Node Id
	*	\param		pScaleVector	Actor Scaling value for the given ID
	*	\param		pSymmetricUpdate	Update right and left part at the same time
    */
	void	SetDefinitionScaleVector(	FBSkeletonNodeId pSkeletonId, FBVector3d pScaleVector, bool pSymmetricUpdate = true );

	/** Get Actor Scaling Definition
	*   \param		pSkeletonId		Skeleton Node Id
	*	\retval		pScaleVector	Actor Scaling Definition for the given ID
    */
	void	GetDefinitionScaleVector(	FBSkeletonNodeId pSkeletonId, FBVector3d &pScaleVector );

	/** Set Actor Rotation Definition
	*   \param		pSkeletonId		Skeleton Node Id
	*	\param		pRotationVector	Actor Rotation value for the given ID
	*	\param		pSymmetricUpdate	Update right and left part at the same time
    */
	void	SetDefinitionRotationVector(	FBSkeletonNodeId pSkeletonId, FBVector3d pRotationVector, bool pSymmetricUpdate = true );
    
    /** Translate Actor, similar to moving the hips of the Actor in the UI
	*   \param		pTranslationVector      Will move the entire Actor to pTranslationVector coordinate
    */
	void	SetActorTranslation( FBVector3d pTranslationVector );    

	/** Return the Default Skeleton State
	*   \return		Default Skeleton State
    */
	FBSkeletonState*	GetDefaultSkeletonState	();

	/** Return the Current Skeleton State
	*   \param		pResetOrientation      When set to true, all rotations in the state will be reset to characterization values.
	*   \return		Current Skeleton State
	*	\note	Usage of this function can be found in script sample /bin/config/Scripts/Samples/Character/CharacterMarkerSetFromActor.py
    */
	FBSkeletonState*	GetCurrentSkeletonState	(bool pResetOrientation=false);

	/** Get the reference model associated with left hand.
	*	\return The reference model associated with the left hand.
    */
	FBModel* GetLeftGloveReferenceModel( );

    /** Set a model to be the left glove reference.
    *   \param  pReferenceModel Model to be the left glove reference.
    */
	void SetLeftGloveReferenceModel( FBModel* pReferenceModel );

	/** Get the reference model associated with right hand.
	*	\return The reference model associated with the right hand.
    */
	FBModel* GetRightGloveReferenceModel( );

    /** Set a model to be the right glove reference.
    *   \param  pReferenceModel Model to be the right glove reference.
    */
	void SetRightGloveReferenceModel( FBModel* pReferenceModel );

private:
	FBSkeletonState*		mDefaultSkeletonState;
	FBSkeletonState*		mCurrentSkeletonState;
};

/** Device motion capture skeleton joints state class.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
__FB_FORWARD( FBMocapJointsState );
class FBSDK_DLL FBMocapJointsState
{
public:
    
	/** Constructor.
	*	\param	pSkeletonJointsCount		Number of joints set by specific motion capture device.
	*/
	FBMocapJointsState(int pSkeletonJointsCount);
    ~FBMocapJointsState();

    int                             mSkeletonJointsCount;                   //!< Number of joints according to specific motion capture device.
    double                          mFloorClipPlaneW;                       //!< Floor Clip Plane W value for camera reposition.
    FBSkeletonTrackingState         mSkeletonTrackingState;                 //!< State of the skeleton tracking.
    FBTVector                       mSkeletonPosition;                      //!< Position of the skeleton.
    FBTVector*                      mSkeletonJointsPositions;               //!< Positions of each joint.
    FBMatrix*                       mSkeletonJointsGlobalOrientations;       //!< Global orientations of each bone.
    FBSkeletonJointTrackingState*   mSkeletonJointTrackingState;            //!< State of the skeleton joint tracking.
};

////////////////////////////////////////////////////////////////////////////////////
// FBCharacter - Representation of a character
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBPlotOptions );
__FB_FORWARD( FBCharacter );
FB_DEFINE_COMPONENT( FBSDK_DLL, Character );

/**	A character is the link between a motion source and a character model.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*   This class exposes part of the functionality associated with a Character.
*   A character can possess a number of potential sources at the same time, such as
*   an actor and another character, but with only one active at any given time.
*   Before setting the InputType to the desired value, one must make sure to have
*   previously set either the InputCharacter or the InputActor.
*
*   To obtain the list of characters present in a scene, you need to create an
*   instance of class FBSystem, to obtain the current scene. The FBScene
*   object holds the list of characters in the property Characters.
*
*   @code
*       FBSystem lSystem;
*       FBScene* lScene = lSystem.Scene;
*       for( int lIdx = 0; lIdx < lScene->Characters.GetCount(); ++lIdx )
*       {
*           FBTrace( "Character[%d]: '%s'\n", lIdx, (char*)lScene->Characters[lIdx] );
*       }
*   @endcode
*
*   The current character selected in the Character tool can be obtained via
*   the FBApplication object.
*
*   @code
*       FBApplication lApplication;
*       FBCharacter* lCharacter = lApplication.CurrentCharacter;
*       if( lCharacter )
*       {
*           FBTrace( "Current character is: '%s'\n", (char*)lCharacter->Name );
*       }
*       else
*       {
*           FBTrace( "No character currently selected\n" );
*       }
*   @endcode
*
*/
class FBSDK_DLL FBCharacter : public FBConstraint
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBCharacter, FBConstraint );
public:
	/** Constructor.
	*	\param	pName		Name of new character.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBCharacter(const char* pName, HIObject pObject=NULL);

	IObject_Declare(K_IMPLEMENTATION);				// Interface to IObject.

    /** Actual Character destructor.
    *   This method is used to delete the actual character object represented by an instance of FBCharacter.
    */
    virtual void FBDelete();

	//! Clone the character.
    FBCharacter* Clone();

	FBPropertyCharacterInputType	InputType;		//!< <b>Read Write Property:</b> The input type for the character (ex: Actor).
	FBPropertyCharacterKeyingMode	KeyingMode;		//!< <b>Read Write Property:</b> The current keying mode.
	FBPropertyActor					InputActor;		//!< <b>Read Write Property:</b> The index of the actor used for the input.
	FBPropertyCharacter				InputCharacter;	//!< <b>Read Write Property:</b> The index of the character used for the input.
	FBPropertyBool				    ActiveInput;	//!< <b>Read Write Property:</b> Is the character input active?

    FBPropertyListCharacterExtension CharacterExtensions;	//!< <b>List:</b> Character Extensions in the character.

    /** Run Cycle Analysis on current character.
	*	\param HICharacter current character.
	*/
    void CycleAnalysisCurrentCharacter();

    /** Get the Cycle Analysis Node from the current character
	*	\return	Cycle Analysis Node linked to the current character, or create a new node
	*/
    FBCycleAnalysisNode* GetCycleAnalysisNode();

    /** AddCharacterExtension.
	*	\param pExt extension to be added to the character.
	*/
    void AddCharacterExtension(FBCharacterExtension* pExt);  

    /** Get the model associated with each body part of the character.
	*	\param pExt extension to be removed to the character.
	*/
    void RemoveCharacterExtension(FBCharacterExtension* pExt);

	/** Get the model associated with each body part of the character.
	*	\return	The model linked to the specified body part.
	*/
	FBModel* GetModel( FBBodyNodeId pBodyNodeId );

	/** Get the skin model associated with character bones. Could be deformable model connected 
    *   to bone via cluster, or non deformable model parented directly under the bones. 
	*	\param pSkinModelList   List to be filled up. (will not be cleared)
	*/
	void GetSkinModelList( FBModelList& pSkinModelList );

	/** Get the index associated with Given Model.
	*	\return	The model linked to the specified body part.
	*/
	FBBodyNodeId GetIndexByModel( FBModel* pModel );

	/** Get the model associated with each body part in the Control Rig of the character.
	*	\return	The model in the Control Rig corresponding to the specified body part.
	*/
	FBModel* GetCtrlRigModel( FBBodyNodeId pBodyNodeId );

	/** Get the index of the model associated with each body part in the Control Rig of the character.
	*	\return	The Index if the model in the Control Rig corresponding to the specified body part.
	*/
    FBBodyNodeId GetCtrlRigIndexByModel( FBModel* pModel );

	/** Get the model associated with each effector in the Control Rig of the character.
	*	\param pEffectorId	The effector ID.
	*	\param pEffectorSetID  Id of the ControlSet to obtain, if not specified the current one is taken.
	*	\return	The model in the Control Rig corresponding to the specified Effector.
	*/
	FBModel* GetEffectorModel( FBEffectorId pEffectorId, FBEffectorSetID  pEffectorSetID = FBEffectorSetDefault );

	/** Get the model associated with the floor contact ID
	*	\param pMemberIndex  Id of the floor contact
	*	\return	The model associated with the floor contact ID
	*/
	FBModel* GetFloorContactModel( FBFloorContactID pMemberIndex );

	/** Get the goal model associated with each body part in the Character Marker Set of the character.
	*	\return	The model in the Character Marker Set corresponding to the specified body part.
	*/
	FBModel* GetGoalModel( FBBodyNodeId pBodyNodeId );

	/* Get The Translation Offset associated to the given BodyPart
	*	\param pTVector  The Translation Offset
	*/
	void GetTOffset( FBBodyNodeId pBodyNodeId, FBTVector* pTVector );

	/* Get The Rotation Offset associated to the given BodyPart
	*	\param pRVector  The Rotation Offset
	*/
	void GetROffset( FBBodyNodeId pBodyNodeId, FBRVector* pRVector );

	/* Get The Scaling Offset associated to the given BodyPart
	*	\param pTVector  The Scaling Offset
	*/
	void GetSOffset( FBBodyNodeId pBodyNodeId, FBSVector* pSVector );

	/* Get The Transform Offset associated to the given BodyPart
	*	\param pOffsetMatrix  The Translation, Rotation and Scaling Offset
	*/
	void GetTransformOffset( FBBodyNodeId pBodyNodeId, FBMatrix *pOffsetMatrix );

	/* Get The Parent Rotation Offset associated to the given BodyPart
	*	\param pRVector  The Rotation Offset
	*/
	void GetParentROffset( FBBodyNodeId pBodyNodeId, FBRVector* pRVector );

	/** Plot the animation of the character.
	*	\param pPlotWhere  Where to plot a character, control rig or Skeleton
	*   \param pPlotOptions Option parameters for plotting
	*	\return	True if the operation completed successfully.
	*/
	virtual bool PlotAnimation( FBCharacterPlotWhere pPlotWhere, FBPlotOptions* pPlotOptions );

	/** Test if character is ready for the Retarget operation (basically, is it in character input ?).
	*	\return	True if the character is ready.
	*/
	bool ReadyForRetarget();

	/** Retarget the animation from the input character to us.
    *   \param  pOnBaseLayer  if true, keys corrections will be made on base layer; else they will be made on another layer. 
	*/
	void Retarget( bool pOnBaseLayer );

	/** Copy the animation from the input character to us.
	*/
	void CopyAnimation();

	/** Reset the properties of the character.
    *   \param  pType  Speficy which properties will be reset.
	*/
	virtual void ResetProperties( FBCharacterResetProperties pType );

	/** Select the objects that make a character.
    *   \param  pSelect  True to select, false to deselect.
    *   \param  pApplyToCharacter  TSould the character contraint be selected ?
    *   \param  pApplyToRig  should The rig (and its children) be selected ?
    *   \param  pApplyToExtensions  Should the character extensions (and their children) be selected ?
	*/
    void SelectModels( bool pSelect, bool pApplyToCharacter, bool pApplyToRig, bool pApplyToExtensions );

	/** Set the character in stance pose.
	*	\param pPushUndo					Should we push an undo transaction on the undo stack? Don't push undo in non UI thread.
	*	\param pIncludeCharacterExtensions	Should the character extensions go to stance pose too?
	*/
	void GoToStancePose( bool pPushUndo = false, bool pIncludeCharacterExtensions = true );
    
    /** Set the Mocap calibration state. If the value is FBCalibrationInProcessing, the processing work is done inside Mobu. 
    *   \param pState The state of calibration, including FBCalibrationNoRequest, FBCalibrationInProcessing and FBCalibrationSuccessfully
	*/
    void SetMocapCalibrationState(FBCalibrationState pState);

    /** Get Mocap calibration state.
    *	\return	Current Mocap calibration state.
	*/
    FBCalibrationState GetMocapCalibrationState();

    /** SetupDeviceMocap.
    *   \remark This method is to initialize this device character that the motion capture device will be its animation source. 
    *   \remark And to set the skeleton hierarchy that this motion capture device is using.
	*	\param pDevice The motion capture device that will be the animation source of the character.
	*	\param pSkeletonJointsCount Number of joints according to specific motion capture device.
	*	\param pSkeletonJointsOrder The order of joints in which the motion capture joints state data will be provided by the motion capture device.
	*/
    void SetupDeviceMocap(FBDevice* pDevice, int pSkeletonJointsCount, FBBodyNodeId* pSkeletonJointsOrder );

    /** SetSensorFloorOffset.
    *   \remark This method is to set the height of sensor above the floor, so MotionBuilder cam move the device skeleton to roughly on the ground.
	*	\param pFloorOffset The sensor to floor offset.
	*/
    void SetSensorFloorOffset(double pSensorFloorOffset);

    /** PassDeviceMocapData.
    *   \remark This method is called by motion capture device to pass the motion capture skeleton joints state data got from hardware to internal character skeleton.
	*	\param pDeviceMocapData The motion capture skeleton joints state data provided by the motion capture device.
	*/
    void PassDeviceMocapData(FBMocapJointsState* pDeviceMocapData);

    /** Set the Characterize flag on.
	*   \param pSetAsBiped  true to use biped characterization or false to use quadruped.
	*   \return             current state of the flag after the operation (true if it did succeed).
	*/
	bool SetCharacterizeOn( bool pSetAsBiped );
	
	/** Get error message for the previous SetCharacterizeOn operation.
	*   \return  The string containing all errors and warnings.
	*/
	const char * GetCharacterizeError();

	/** Set Characterize flag off.
	*/
	void SetCharacterizeOff();
	
	/** Get Characterize flag.
	*   \return Current state of the Characterize flag.
	*/
	bool GetCharacterize();
	
	/** Create the Control-Rig.
	*   \param pSetFKIK  true to use FK/IK or false to use IK only.
	*   \return          current state of the flag after the operation (true if it did succeed).
	*/
	bool CreateControlRig(bool pSetFKIK);

	/** Connect a Control-Rig to the character.
	*   \param pControlSet  The control set to connect. NULL will disconnect the Control-Rig from the character.
	*   \param pUpdateLimit Whether to update the models' limit for a character. E.g. the Pre rotation and post rotation.
    *   \param pResetHierarchy Whether to reset hierarchy for a character.
    */
	void ConnectControlRig(FBControlSet* pControlSet, bool pUpdateLimit, bool pResetHierarchy);

	/** Disconnect the Control-Rig from the character.
	*/
	void DisconnectControlRig();

	/** Create auxiliary on effector.
	*   \param pEffectorId	The effector ID.
	*   \param pPivot		Create effector or pivot (pivot offset should be set on IKPivot property, at creation default values are set).
	*   \param pAuxReachT	Default auxiliary effector reach for translation (IK Blend T since MotionBuilder 2013).
	*   \param pAuxReachR	Default auxiliary effector reach for rotation (IK Blend R since MotionBuilder 2013).
	*   \return				True if auxiliary was created (can fail if FBLastEffectorSetIndex limit reached).
	*/
	bool CreateAuxiliary(FBEffectorId pEffectorId, bool pPivot, double pAuxReachT=100, double pAuxReachR=100);

	/** Obtain Input ControlSet.
	*   \param pForce    If True, will return the current ControlSet even if the character is not in ControlSet Input.
	*   \return          Return current Active ControlSet, NULL if none.
	*/
    FBControlSet * GetCurrentControlSet(bool pForce = false);

	/** Create the Character Marker Set.
	*   \param pSetActive	True when new input should be set and active.
	*   \return				True when marker got created and connected to character.
	*/
	bool CreateCharacterMarkerSet(bool pSetActive);

	/** Obtain Input CharacterMarkerSet.
	*   \param pForce    If True, will return the current CharacterMarkerSet even if the character is not in CharacterMarkerSet Input.
	*   \return          Return current Active CharacterMarkerSet, NULL if none.
	*/
    FBCharacterMarkerSet * GetCharacterMarkerSet(bool pForce = false);

	/** Check if there is an offset on Parent.
	*   \param pNodeId   Node Id to Check.
	*   \return          True if there is an offset on Parent.
	*/
	bool IsParentNodeOffset( FBBodyNodeId pNodeId );

	/** Get a pointer to the external solver of a character, or NULL is no external solver is used on the character.
	*   \return          The pointer of the current External Solver, NULL if it's the internal solver.
	*/
    FBCharacterSolver *GetExternalSolver();

	/** Set character external solver.
	*   \param pIndex    Index of external solver.
	*/
    void SetExternalSolver(int pIndex);

    /** Set character solver.
    *   \param pSolver    Character solver that will be used by the character.
    */
    void SetExternalSolver(FBCharacterSolver* pSolver);

	/** Get the active body part array.
	*   \param pActivePart   A pointer to an array of bool. On return, the index with a "true" value are active part.
	*/
    void GetActiveBodyPart(bool* pActivePart);

	/** Return true if the object is Pinned in Rotation (Manipulation).
	*   \param		pEffectorIndex	Given Index to obtain Model
    *   \return		True if the effector is pinned in Rotation
    */
    bool        IsRotationPin(FBEffectorId pEffectorIndex);
	/** Return true if the object is Pinned in Translation (Manipulation).
	*   \param		pEffectorIndex	Given Index to obtain Model
    *   \return		True if the effector is pinned in Translation
    */
    bool        IsTranslationPin(FBEffectorId pEffectorIndex);

    /** Return true Ctrl Set is Ready to be used.
    *	\return return true if character is active, characterized and is in input control rig
    */
    bool        IsCtrlSetReady();

    /** Return true if the Actor is currently being plot to the Control Rig.
    *	\return return true if the Actor is currently being plot to the Control Rig.
    */
    bool        IsPlottingActorToCtrlRig();

	/** Return pointer to evaluation cache that is dedicated for control set and given pEvaluateInfo.
    *	\return valid pointer to evaluation cache.
    */
	FBControlSetState*	GetControlSetEvaluationCache(FBEvaluateInfo* pEvaluateInfo);
	
	/** Return pointer to evaluation cache that is dedicated for effector set and given pEvaluateInfo.
    *	\return valid pointer to evaluation cache.
    */
	FBEffectorSetState*	GetEffectorEvaluationCache(FBEvaluateInfo* pEvaluateInfo);

    /** Mirror character extensions.
	*	\param pEvaluateInfo the evaluation info
	*/
    void MirrorCharacterExtensions(FBEvaluateInfo* pEvaluateInfo);

	/** Used to store SetCharacterizeOn errors and warnings */
	FBString mCharacterizeError;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ParamModifier
	FBPropertyBool					        MirrorMode;					//!< <b>Read Write Property:</b> is in mirror mode.
	FBPropertyAnimatableDouble		        ShoulderCorrection;			//!< <b>Read Write Property:</b> shoulder correction values.
	FBPropertyBool					        LeftKneeKillPitch;			//!< <b>Read Write Property:</b> is Pitch used for Left knee.
	FBPropertyBool					        RightKneeKillPitch;			//!< <b>Read Write Property:</b> is Pitch used for Right knee.
	FBPropertyBool					        LeftElbowKillPitch;			//!< <b>Read Write Property:</b> is Pitch used for Left elbow.
	FBPropertyBool					        RightElbowKillPitch;		//!< <b>Read Write Property:</b> is Pitch used for Right elbow.
	FBPropertyCharacterHipsTranslationMode  HipsTranslationMode;        //!< <b>Read Write Property:</b> Hips Translation Mode.
	FBPropertyBool					        WriteReference;				//!< <b>Read Write Property:</b> are we writing back on reference.
	FBPropertyBool					        SyncMode;					//!< <b>Read Write Property:</b> is character in sync mode.
	FBPropertyBool					        InverseLeftKnee;			//!< <b>Read Write Property:</b> Is left knee inverted.
	FBPropertyBool					        InverseRightKnee;			//!< <b>Read Write Property:</b> Is right knee inverted.
	FBPropertyBool					        InverseLeftElbow;			//!< <b>Read Write Property:</b> Is left elbow inverted.
	FBPropertyBool					        InverseRightElbow;			//!< <b>Read Write Property:</b> Is right elbow inverted.
	FBPropertyCharacterRollSolver	        RollSolver;					//!< <b>Read Write Property:</b> Roll Solver selection.
    FBPropertyCharacterContactBehaviour	    ContactBehaviour;			//!< <b>Read Write Property:</b> Contact Behavior selection.

    FBPropertyAnimatableDouble              ScaleCompensation;
    FBPropertyAnimatableDouble              HipsHeightCompensation;
    FBPropertyAnimatableDouble              AnkleHeightCompensation;
    FBPropertyAnimatableDouble              AnkleProximityCompensation;

	FBPropertyBool					        LockX;			//!< <b>Read Write Property:</b> Lock character skeleton in place on X axis.
	FBPropertyBool					        LockY;			//!< <b>Read Write Property:</b> Lock character skeleton in place on Y axis.
	FBPropertyBool					        LockZ;			//!< <b>Read Write Property:</b> Lock character skeleton in place on Z axis.
};


////////////////////////////////////////////////////////////////////////////////////
// Property List: MarkerSet
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: MarkerSet.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBPropertyListMarkerSet : public FBPropertyListComponent
{
public:
	FBPropertyListMarkerSet();
	/**	Get the marker set at \e pIndex.
	*	\param	pIndex	Index of marker set to get a handle on.
	*	\return Marker set at \e pIndex.
	*/
	FBMarkerSet* operator[](int pIndex);
	/** Duplicate a marker set.
	*	\param	pIndex	Index of Market set to duplicate.
	*	\return Total number of marker sets after operation.
	*/
	virtual int Duplicate(int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// Property List: CharacterMarkerSet
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: CharacterMarkerSet.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBPropertyListCharacterMarkerSet : public FBPropertyListComponent
{
public:
	FBPropertyListCharacterMarkerSet();
	/**	Get the character marker set at \e pIndex.
	*	\param	pIndex	Index of marker set to get a handle on.
	*	\return Character marker set at \e pIndex.
	*/
	FBCharacterMarkerSet* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// Property List: ControlSet
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: MarkerSet.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
	*/
class FBSDK_DLL FBPropertyListControlSet : public FBPropertyListComponent
{
public:
	FBPropertyListControlSet();
	/**	Get the marker set at \e pIndex.
	*	\param	pIndex	Index of marker set to get a handle on.
	*	\return Marker set at \e pIndex.
	*/
	FBControlSet* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// Property List: Actor
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: Actor.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBPropertyListActor : public FBPropertyListComponent
{
  public:
	FBPropertyListActor();
	/**	Get the actor at \e pIndex.
	*	\param	pIndex	Index of actor to get a handle on.
	*	\return Actor at \e pIndex.
	*/
	FBActor* operator[]( int pIndex );
	/** Duplicate an actor.
	*	\param	pIndex	Index of actor to duplicate.
	*	\return	Total number of actors after operation.
	*/
	virtual int Duplicate( int pIndex );
};


////////////////////////////////////////////////////////////////////////////////////
// Property List: Character
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD		( FBPropertyListCharacter );

/** \b PropertyList: Character.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBPropertyListCharacter : public FBPropertyListComponent
{
  public:
	FBPropertyListCharacter();
	/**	Get the Character at \e pIndex.
	*	\param	pIndex	Index of Character to get a handle on.
	*	\return Character at \e pIndex.
	*/
	FBCharacter* operator[]( int pIndex );
	/** Duplicate a Character.
	*	\param	pIndex	Index of character to duplicate.
	*	\return	Total number of Characters after operation.
	*/
	virtual int Duplicate( int pIndex );
};

//Helpers

/** return Character Manipulation/Keying Mode
*	\return Keying Mode
*/
FBSDK_DLL FBCharacterKeyingMode FBGetCharactersKeyingMode();

/** return BodyPart ID from Effector.
*	\param	pEffectorId	Effector ID.
*	\return ID of the BodyPart the effector is in.
*/
FBSDK_DLL FBBodyPartId FBGetEffectorBodyPart( FBEffectorId pEffectorId );

/** return BodyPart ID from Bones.
*	\param	pBodyNodeId	Body Node ID.
*	\return ID of the BodyPart the effector is in.
*/
FBSDK_DLL FBBodyPartId FBGetBodyNodeBodyPart( FBBodyNodeId pBodyNodeId );

/** Get character by its associated IK/FK Marker or Bone 
*	\param pPart	associated IK/FK Marker or Bone
*	\return			character.
*/
FBSDK_DLL FBCharacter* FBGetCharacterByAssociatedPart(FBComponent* pPart);

/** Queries visibility of the floor contacts of the current character.
*	\return	True if floor contacts of the current character are visible, or false if they are hidden.
*/
FBSDK_DLL bool FBGetCharacterFloorContactsVisibility();

/** Sets visibility of the floor contacts of the current character.
*	\param  pShow   Specifies if floor contacts of the current character should be visible.
*/
FBSDK_DLL void FBSetCharacterFloorContactsVisibility(bool pShow);

/** Queries visibility of the finger-tips of the current character.
*	\return	True if finger-tips of the current character are visible, or false if they are hidden.
*/
FBSDK_DLL bool FBGetCharacterFingerTipsVisibility();

/** Sets visibility of the finger-tips of the current character.
*	\param  pShow   Specifies if finger-tips of the current character should be visible.
*/
FBSDK_DLL void FBSetCharacterFingerTipsVisibility(bool pShow);

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* _FB_CHARACTER_H_ */
