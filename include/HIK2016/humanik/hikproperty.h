/*!	\file hikproperty.h
 *	\brief Header file for character properties.
 *
 *	This file contains functions for managing character properties.
 */

/**************************************************************************************

Copyright (C) 2015 Autodesk, Inc.
All Rights Reserved.

The coded instructions, statements, computer programs, and/or related material (collectively "Data")
in these files contain unpublished information proprietary to Autodesk, Inc., ("Autodesk") which is
protected by Canada and United States of America federal copyright law and by international treaties.

The Data may not be disclosed or distributed to third parties, in whole or in part, without the prior
written consent of Autodesk.

THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED.
AUTODESK MAKES NO WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR ARISING BY CUSTOM
OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
FITNESS FOR A PARTICULAR PURPOSE OR USE. WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT WARRANT THAT
THE OPERATION OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE.

IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS OR SUPPLIERS ("AUTODESK GROUP")
BE LIABLE FOR ANY LOSSES, DAMAGES OR EXPENSES OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR
MULTIPLE DAMAGES OR OTHER SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS OF PROFITS, REVENUE
OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR DAMAGES OF ANY KIND), HOWEVER CAUSED, AND REGARDLESS
OF THE THEORY OF LIABILITY, WHETHER DERIVED FROM CONTRACT, TORT (INCLUDING, BUT NOT LIMITED TO,
NEGLIGENCE), OR OTHERWISE, ARISING OUT OF OR RELATING TO THE DATA OR ITS USE OR ANY OTHER PERFORMANCE,
WHETHER OR NOT AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS OR DAMAGE.

**************************************************************************************/

#ifndef HIKPROPERTY_H
#define HIKPROPERTY_H

#include "humanik.h"

#ifdef __cplusplus
extern "C" {
#endif

// ***********************************************
/**	\defgroup CharacterProperties Property Descriptions
 *	\ingroup PropertyState
 *	\brief This section offers brief descriptions of all character properties contained in each HIKPropertySetState. 
 *
 *	For detailed information, including default and accepted values, see ~{ Character Properties }~.
 */

//! \enum HIKProperty
//! \brief Lists all character properties contained in the HIKPropertySetState.
//! \ingroup CharacterProperties
enum HIKProperty
{
	/*! This property constrains the positions in space of the target character's limbs to those of the selected source, even when the source and target have different dimensions. 
	*	For example, when retargeting a walking animation from a smaller character to a larger character, the larger character will take steps the same size as the smaller character, without adjusting those steps to its own larger size.
	*	\remarks Used by HIKSolveForCharacter only
	*/
    HIKForceActorSpaceId,
    
    
	/*!	Compensates for the difference in action space between source and target characters. It moves the target character's feet and legs with the movement of the source's feet, but makes adjustments to the feet and leg movements based on differences in scale. When the HIKForceActorSpaceId property is active, Scale Compensation is constrained to 100%. 
	*	\remarks Used by HIKSolveForCharacter only
	*/
    HIKScaleCompensationId,

	/*!	Smooths leg movements by preventing a Character's hips from pulling down too quickly when the legs are moving. This also prevents heavy footfalls. 	
	*	\remarks Used by HIKSolveForCharacter only
	*/
    HIKMassCenterCompensationId,

	/*!	If your source and target character have their ankles at different heights above the floor, use this property to specify the difference between their ankle heights.
	*	\remarks Used by HIKSolveForCharacter only
	*/
    HIKAnkleHeightCompensationId,

	/*!	Adjusts the spacing between the left and right ankles of the target character relative to the source character.
	*	\remarks Used by HIKSolveForCharacter only
	*/
    HIKAnkleProximityCompensationId,

	/*!	Adjusts the height of the target character's hips.
	*	\remarks Used by HIKSolveForCharacter only
	*/
	HIKHipsHeightCompensationId,

	//@{
	/**	The Reach properties control how closely the target character's Nodes are in the final solution to the corresponding Nodes of the source character. 
	*	\remarks Used by HIKSolveForCharacter only
	*/
    HIKReachActorLeftAnkleId,
    HIKReachActorRightAnkleId,
    HIKReachActorChestId,
    HIKReachActorLeftWristId,
    HIKReachActorRightWristId,
	HIKReachActorLeftKneeId,
	HIKReachActorRightKneeId,
	HIKReachActorHeadId,
	HIKReachActorLeftElbowId,
	HIKReachActorRightElbowId,
    HIKReachActorLeftAnkleRotationId,
    HIKReachActorRightAnkleRotationId,
    HIKReachActorHeadRotationId,
    HIKReachActorLeftWristRotationId,
    HIKReachActorRightWristRotationId,
    HIKReachActorLeftFingerBaseId,
	HIKReachActorRightFingerBaseId,
    HIKReachActorLeftToesBaseId,
	HIKReachActorRightToesBaseId,
    HIKReachActorLeftFingerBaseRotationId,
	HIKReachActorRightFingerBaseRotationId,
    HIKReachActorLeftToesBaseRotationId,
	HIKReachActorRightToesBaseRotationId,
    HIKReachActorChestRotationId,
	HIKReachActorLowerChestRotationId,
    HIKReachActorLeftHandThumbId,
	HIKReachActorLeftHandIndexId,
	HIKReachActorLeftHandMiddleId,
	HIKReachActorLeftHandRingId,
	HIKReachActorLeftHandPinkyId,
	HIKReachActorLeftHandExtraFingerId,
    HIKReachActorRightHandThumbId,
	HIKReachActorRightHandIndexId,
	HIKReachActorRightHandMiddleId,
	HIKReachActorRightHandRingId,
	HIKReachActorRightHandPinkyId,
	HIKReachActorRightHandExtraFingerId,
    HIKReachActorLeftFootThumbId,
	HIKReachActorLeftFootIndexId,
	HIKReachActorLeftFootMiddleId,
	HIKReachActorLeftFootRingId,
	HIKReachActorLeftFootPinkyId,
	HIKReachActorLeftFootExtraFingerId,
    HIKReachActorRightFootThumbId,
	HIKReachActorRightFootIndexId,
	HIKReachActorRightFootMiddleId,
	HIKReachActorRightFootRingId,
	HIKReachActorRightFootPinkyId,
	HIKReachActorRightFootExtraFingerId,

	//@}
    
	//	Each floor contact position setting defines a different aspect of the floor contact area.
	HIKFootFloorContactId,                      //!< Activates the floor contact engine for the character's feet.
	HIKFootBottomToAnkleId,                     //!< Defines the distance from the ankle to the bottom of the model's foot.
    HIKFootBackToAnkleId,                       //!< Defines the distance from the ankle to the back of the model's foot.
    HIKFootMiddleToAnkleId,                     //!< Defines the distance from the ankle to the middle of the model's foot (its ball, or toe base). 
    HIKFootFrontToMiddleId,                     //!< Defines the distance from the ankle to the front end of the model's toes.
    HIKFootInToAnkleId,                         //!< Defines the distance from the ankle to the inside edge of the model's foot (the instep).
    HIKFootOutToAnkleId,                        //!< Defines the distance from the ankle to the outside edge of the model's foot.
    HIKHandFloorContactId,                      //!< Activates the floor contact engine for the character's hands.
    HIKHandBottomToWristId,	                    //!< Defines the distance from the wrist to the bottom of the model's hand.
    HIKHandBackToWristId,	                    //!< Defines the distance from the wrist to the back of the model's hand.
    HIKHandMiddleToWristId,	                    //!< Defines the distance from the wrist to the middle of the model's hand (its knuckles, or finger base). 
    HIKHandFrontToMiddleId,	                    //!< Defines the distance from the wrist to the front end of the model's fingers.
    HIKHandInToWristId,	                        //!< Defines the distance from the wrist to the inside edge of the model's hand (the side of the thumb).
    HIKHandOutToWristId,	                    //!< Defines the distance from the wrist to the outside edge of the model's hand (the side with the pinky).

	//!	Sets the contact type for the character's hands, which defines the number and orientation of the markers used to define the outline of the character's hands. The value may be any of the following: 
	//!		- 0 (Normal): Six markers define each hand's floor contact. The middle markers should define where the fingers begin. 
	//!		- 1 (Wrist): Four markers define each hand's floor contact. 
	//!		- 2 (FingerBase): Four markers define each hand's floor contact. 
	//!		- 3 (Hoof): Four markers define each hand's floor contact, but the points are oriented at a 90 degree angle, letting you define the floor contact for animal types with hooves, such as horses. These contact markers allow for 180 degrees of movement.
    HIKHandContactTypeId,

	//!	Activates the floor contact engine for your character's fingers.
	HIKHandFingerContactId,                     

	//!	Determines the behavior of the fingers when they make contact with the floor. The value may be any of the following: 
	//!		- 0 (Sticky): Each finger sticks to the floor exactly where contact is made. 
	//!		- 1 (Spread): Spreads the fingers as they make contact with the floor, attempting to keep the position of the fingers intact. Rotation is applied to the root of each finger. 
	//!		- 2 (Sticky and Spread): Averages the finger behaviour between both Sticky and Spread. 
	HIKHandFingerContactModeId,

	//!	Sets the contact type for the character's feet, which defines the number and orientation of the markers used to define the outline of the character's feet. The value may be any of the following: 
	//!		- 0 (Normal): Six markers define each foot's floor contact. The middle markers should define where the toes begin. 
	//!		- 1 (Ankle):  Four points define each foot's floor contact. 
	//!		- 2 (ToeBase): Four points define each foot's floor contact. 
	//!		- 3 (Hoof): Four points define each foot's floor contact, but the points are oriented at a 90 degree angle, letting you define the floor contact for animal types with hooves, such as horses. These contact markers allow for 180 degrees of movement.    
    HIKFootContactTypeId,

	//!	Activates the floor contact engine for your character's toes.
	HIKFootFingerContactId,            
    
	//!	Lets you choose the behavior of the toes when they make contact with the floor. The value may be any of the following: 
	//!		- 0 (Sticky): Each toe sticks to the floor exactly where contact is made. 
	//!		- 1 (Spread): Spreads the toes as they make contact with the floor, attempting to keep the position of the toes intact. Rotation is applied to the root of each toe. 
	//!		- 2 (Sticky and Spread): Averages the toe behaviour between both Sticky and Spread. 	
	HIKFootFingerContactModeId,

	//@{
	/**	The Roll properties adjust the way roll rotations on the shoulders, elbows, hips and knees are shifted to their child Nodes in the skeletal hierarchy. For example, if
		a roll rotation is applied to the LeftShoulderNodeId, the HIKLeftArmRollId property determines how much of that rotation is extracted and applied to the next Node in 
		the hierarchy: i.e. the optional LeftShoulderRollNodeId if characterized, or to the LeftElbowNodeId otherwise. For more information, see ~{ Using Roll Extraction }~.
			- At 100%, all of the roll transfers from the original Node to its child.       
			- At 50%, the roll is equally distributed between the original Node and its child. 
			- At 0%, none of the roll is transferred to the child, moving only the original Node.
	*/
    HIKLeftUpLegRollId,
    HIKLeftLegRollId,
    HIKRightUpLegRollId,
    HIKRightLegRollId,
    HIKLeftArmRollId,
    HIKLeftForeArmRollId,
    HIKRightArmRollId,
    HIKRightForeArmRollId,
    //@}

   /*!	Mirrors a Character's pose along the X-axis.
	*	\remarks Used by HIKSolveForCharacter only
	*/
    HIKMirrorId,

   //@{
    //!	The Kill Pitch properties remove the pitch axis on the left and right knees and elbows.
    HIKLeftKneeKillPitchId,
	HIKRightKneeKillPitchId,
	HIKLeftElbowKillPitchId,
	HIKRightElbowKillPitchId,
    //@}

    //@{
	/**	The Pull properties determine the extent to which parts of the body can pull other parts of the body during a retargeting.
	 *	The effect of each Node's pull value is contingent on its Reach value. For example, if Pull is set to 100%, but Reach is set to 0%, the Pull value has no effect.
	 *		- At 100%, the Node has full pull. It will be placed at the target point determined for it by the solver, even if the solver has to move other body parts.
	 *		- At 50%, the Node has half pull. This means that moving other body parts that normally transform the Node will have a damping effect.
	 *		- At 0%, the Node has no pull. This means that moving other body parts transforms the Node identically.
	 *	\remarks Used by HIKSolveForCharacter only
	 */
    HIKCtrlPullLeftFootId,
	HIKCtrlPullRightFootId,
	HIKCtrlPullLeftHandId,
	HIKCtrlPullRightHandId,
	HIKCtrlPullHeadId,
    HIKCtrlPullLeftToeBaseId,
    HIKCtrlPullLeftKneeId,
	HIKCtrlPullRightToeBaseId,
    HIKCtrlPullRightKneeId,
	HIKCtrlPullLeftFingerBaseId,
	HIKCtrlPullLeftElbowId,
	HIKCtrlPullRightFingerBaseId,
	HIKCtrlPullRightElbowId,
    HIKCtrlChestPullLeftHandId,
    HIKCtrlChestPullRightHandId,
	HIKCtrlResistHipsPositionId,			// bob: This is Hips Pull
	HIKCtrlEnforceGravityId,				// bob: Hips Pull sub-param
	//@}

	//@{
	/**	Resist is the rotation equivalent of Pull. Perhaps a more accurate way to describe "resist" is the degree to which the solver 
	 *	tries to preserve the initial, FK angle of a joint during a retargeting. For example, if the initial pose of a character has a bent elbow, 
	 *	a resist value of 0 will allow the arm to stretch during the retargeting, while a resist value of 1 will make the elbow remain bent.
	 *	\remarks Used by HIKSolveForCharacter only
	 */
	HIKCtrlResistHipsOrientationId,   
	HIKCtrlResistChestPositionId,     
	HIKCtrlResistChestOrientationId,  
	HIKCtrlResistLeftCollarId,        
	HIKCtrlResistRightCollarId,       
	HIKCtrlResistLeftKneeId,          
	HIKCtrlResistRightKneeId,         
	HIKCtrlResistLeftElbowId,         
	HIKCtrlResistRightElbowId, 
	//@}

	/**	Defines how motion is distributed over the character's spine bones. This value must be between 0.0 and 1.0, where: 
	 *		- a value of 0.0 causes motion to be equally distributed over all spine bones.
	 *		- a value of 1.0 causes only the base spine bone to move.
	 */
	HIKCtrlSpineStiffnessId,          
       
	//@{
	//!	The Hips and Chest Offset properties offset the translation of the character's hips and chest along each axis by the specified value.
    HIKHipsTOffsetXId,                
    HIKHipsTOffsetYId,                
    HIKHipsTOffsetZId,                
    HIKChestTOffsetXId,               
    HIKChestTOffsetYId,               
    HIKChestTOffsetZId,               
	//@}
    
	//!	Specific to MotionBuilder.
    HIKFootAutomaticToesId,           

	/*!	Defines a stable point when applying floor contact. May be any of the following values:
	 *		- 0 (Auto): Averages the Ankle and Toes modes described below.
	 *		- 1 (Ankle): When the toes make contact with the floor, they are translated forward to keep the ankle's trajectory towards the floor constant.
	 *		- 2 (Toes): When the toes make contact with the floor, the ankle is translated backwards to keep the toes firmly planted on the floor.
	 */
    HIKFootFloorPivotId,              

	//!	Specific to MotionBuilder.
    HIKPostureId,

	//!	Specific to MotionBuilder.
    HIKHandAutomaticFingersId,	         

	//!	Defines a stable point when applying floor contact. Auto, Ankle or Toes.
    HIKHandFloorPivotId,	             

	/**	Defines how motion is distributed over the character's neck bones. This value must be between 0.0 and 1.0, where: 
	 *		- a value of 0.0 causes motion to be equally distributed over all neck bones.
	 *		- a value of 1.0 causes only the base neck bone to move.
	 */
	HIKCtrlNeckStiffnessId,              

	/*!	Specifies the behavior of the ::HipsTranslationId Node. May be any of the following values:
	 *		- 0 (WorldRigid): Causes hip rotations to be applied only to the character's hip Nodes, and not to the ::HipsTranslationId Node.
	 *		- 1 (BodyRigid): Causes sip rotations to be applied both to the character's hip Nodes and to its ::HipsTranslationId Node, if any.
	 *		- 2 (Trajectory): Causes any data stored in the ::HipsTranslationId Node of a source character to be retargeted to the ::HipsTranslationId Node of a target character. See ~{ Retargeting Animation Trajectories }~.
	 */
	HIKHipsTranslationModeId,            

	//!	Specific to MotionBuilder.
	HIKFingerSolvingId,                  

	/**	Defines how the angle of the ankle joint reacts to a floor contact.
	 *		- At 100%, the floor contact engine cannot change the ankle rotation. This maintains the foot configuration.
	 *		- At 0%, the ankle may be rotated freely in order to minimize floor penetration.
	 *	In both cases, final corrections will be performed by translating the ankle.
	 */
    HIKFootContactStiffnessId,           

	//@{
	//!	The Resist Maximum Extension properties dampen the extension of the legs and arms as they reach their maximum extensions, to prevent limb snapping. 
	//!	The higher the value, the more gradually the limb extends. The default value of 0.5 corrects most limb snapping.
	HIKCtrlResistMaximumExtensionLeftKnee,
    HIKCtrlResistMaximumExtensionRightKnee,
    HIKCtrlResistMaximumExtensionLeftElbow,
    HIKCtrlResistMaximumExtensionRightElbow,
	//@}

	//@{
	//!	The Resist Compression Factor properties dampen the compression of extended legs and arms as they contract or close.
	//!	At 1.0 (full effect), the extended leg or arm doesn't bend inward. Instead, it pushes the character's chest, moving the character. 
	HIKCtrlResistCompressionFactorLeftKnee,
	HIKCtrlResistCompressionFactorRightKnee,
	HIKCtrlResistCompressionFactorLeftElbow,
	HIKCtrlResistCompressionFactorRightElbow,
	//@}

    
    HIKHandFingerContactRollStiffness,          //!< Sets the roll stiffness of the fingers. The higher the value of this property, the less likely the character's fingers are to roll when they hit the floor, preserving the configuration of the fingers relative to each other.
    HIKFootFingerContactRollStiffness,          //!< Sets the roll stiffness of the fingers. The higher the value of this property, the less likely the character's fingers are to roll when they hit the floor, preserving the configuration of the fingers relative to each other.

	/**	Defines how the angle of the wrist joint reacts to a floor contact.
	 *		- At 100%, the floor contact engine cannot change the wrist rotation. This maintains the wrist configuration.
	 *		- At 0%, the wrist may be rotated freely in order to minimize floor penetration.
	 *	In both cases, final corrections will be performed by translating the wrist.
	 */
    HIKHandContactStiffness,                    //< See HIKFootContactStiffnessId
        
	/*!	Defines how roll extraction is performed:
	 *		- 0 (Relative)
	 *		- 1 (Absolute)
	 */
    HIKRollExtractionMode,

	//!	Sets the number of times pull is calculated.
	//!	The greater the number of iterations, the more accurate the results of the pull engine.
	//!	However, a higher number of iterations may decrease system performance.
	//!	By default, the value of this property is set to 10.
    HIKPullIterationCount,
	
	//@{
	//!	The Tip Sizes properties adjust the size of the floor markers used to outline the character's fingertips and toe tips for the floor contact engine.     
	HIKLeftHandThumbTip,
	HIKLeftHandIndexTip,
	HIKLeftHandMiddleTip,
	HIKLeftHandRingTip,
	HIKLeftHandPinkyTip,
	HIKLeftHandExtraFingerTip,	
	HIKRightHandThumbTip,
	HIKRightHandIndexTip,
	HIKRightHandMiddleTip,
	HIKRightHandRingTip,
	HIKRightHandPinkyTip,	
	HIKRightHandExtraFingerTip,	
	HIKLeftFootThumbTip,
	HIKLeftFootIndexTip,
	HIKLeftFootMiddleTip,
	HIKLeftFootRingTip,
	HIKLeftFootPinkyTip,
	HIKLeftFootExtraFingerTip,	
	HIKRightFootThumbTip,
	HIKRightFootIndexTip,
	HIKRightFootMiddleTip,
	HIKRightFootRingTip,
	HIKRightFootPinkyTip,	
	HIKRightFootExtraFingerTip,
	//@}

	//!	When human shoulders rotate, they move upwards. This property emulates this behaviour by shifting
	//!	rotation from the shoulder Node to the collar Node when the arms are raised. 
	HIKRealisticShoulder,

	//@{
	//!	Sets the maximum angle of extension for the Node.     
	HIKLeftLegMaxExtensionAngle,
	HIKRightLegMaxExtensionAngle,
	HIKLeftArmMaxExtensionAngle,
	HIKRightArmMaxExtensionAngle,
	//@}

	//!	Defines how shoulder rotation is distributed over the collar Nodes. This value must be between 0.0 and 1.0, where: 
	//!		- 0.0: Rotation is applied totally to the base collar bone.
	//!		- 1.0: Rotation is applied totally to the extra collar bone.
	HIKExtraCollarRatioId,

	//@{
	//!	Sets the flexibility of the collar bones when rotating around the X, Y and Z axes. Higher values cause the collar to be stiffer and less likely to rotate around the axis; lower values cause the collar to be more flexible and more likely to rotate around the axis
	HIKCollarStiffnessX,
	HIKCollarStiffnessY,
	HIKCollarStiffnessZ,
	//@}

	//@{
	/**	The Reach properties control how closely the target character's Nodes are in the final solution to the corresponding Nodes of the source character. 
	 * \remarks Used by HIKSolveForCharacter only
	 */
	HIKReachActorLeftShoulderId,
	HIKReachActorRightShoulderId,
	//@}

	/**	When retargeting an animation to a target character that has more fingers or finger joints than the source character, this property causes the source character's finger movements to be applied to the target character's extra fingers and finger joints. 
	 *	\remarks Used by HIKSolveForCharacter only
	 */
	HIKFingerPropagationId,

	//@{
	/**	When a roll rotation is applied to the character's ankle, this parameter determines the percentage of that rotation that will be extracted from the ankle
		and applied instead to the character's hips. This allows you to keep the character's knee and upper leg more in line with the orientation of its foot, which
		produces a more realistic effect in most cases.
			- At 0%, the hips are not rotated at all. All rotation is applied to the ankle.
			- At 100%, all rotation is applied to the hips instead of the ankle.
	 */
	HIKRealisticLeftKneeSolvingId,
	HIKRealisticRightKneeSolvingId,
	//@}

	/**	Sets the percentage of the arm or leg length at which those limbs can begin to stretch. For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKStretchStartArmsAndLegs,
	/**	Sets the percentage of the arm or leg length at which those limbs stop stretching freely. To avoid popping, this parameter is a soft limit: above this
		percentage, the limb continues to stretch at a rate that decreases exponentially. For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKStretchStopArmsAndLegs,
	/**	Determines the amount of scaling to apply to the Nodes in the arms and legs when those limbs are squashed or stretched.
		For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKSnSScaleArmsAndLegs,
	// @{
	/**	Sets the stretch reach for this Node, which determines how freely the limb may stretch to reach a distant goal. In order for Squash 'n' Stretch to
		affect a character's arm or leg, this parameter must be greater than 0, and the Reach Translation of the wrist or hand (or ankle or foot) must also be greater than 0.
		For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKSnSReachLeftWrist,
	HIKSnSReachRightWrist,
	HIKSnSReachLeftAnkle,
	HIKSnSReachRightAnkle,
	// @}

	/**	Determines the amount of scaling to apply to the Nodes in the spine when the spine is squashed or stretched.
		For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKSnSScaleSpine,
	/**	Determines whether or not the neck and collar Nodes (or shoulder Nodes if no collar Nodes are characterized) are squashed or stretched in proportion
		to the compression and expansion of the spine. For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKSnSScaleSpineChildren,
	/**	Sets the stretch reach for this Node, which determines how freely the spine may stretch to reach a distant goal. In order for Squash 'n' Stretch to
		affect a character's spine, the Reach Translation of the ChestEndEffectorId must be greater than 0. For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKSnSReachChestEnd,
	/**	Determines the amount of scaling to apply to the Nodes in the neck when the neck is squashed or stretched.
		For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKSnSScaleNeck,
	/**	Sets the stretch reach for this Node, which determines how freely the neck may stretch to reach a distant goal. In order for Squash 'n' Stretch to
		affect a character's neck, the Reach Translation of the HeadEffectorId must be greater than 0. For more information, see ~{ Using Squash 'n' Stretch }~. */
	HIKSnSReachHead,

	//@{
	/**	The RollEx properties adjust the way roll rotations on the optional roll Nodes are shifted to their child Nodes in the skeletal hierarchy. For example, if a
		roll rotation is applied to the LeftShoulderRollNodeId, the ::HIKLeftArmRollExId property determines how much of that roll is extracted and applied instead
		to the LeftElbowNodeId. For more information, see ~{ Using Roll Extraction }~.
		- At 100%, all of the roll transfers from the roll Node to the next Node in the hierarchy. The roll Node will therefore
			remain at the same rotation as its parent.
		- At 50%, the roll is equally distributed between the roll Node and the next Node in the hierarchy. 
		- At 0%, none of the roll is transferred to the next Node in the hierarchy. The roll Node will therefore
			be at the same rotation as its child.
	*/
    HIKLeftUpLegRollExId,
    HIKLeftLegRollExId,
    HIKRightUpLegRollExId,
    HIKRightLegRollExId,
    HIKLeftArmRollExId,
    HIKLeftForeArmRollExId,
    HIKRightArmRollExId,
    HIKRightForeArmRollExId,
	//@}

    /**	This property is used only when a source animation used for a retargeting bends forward at the waist while
		tilting its head back. Tuning this property can help to prevent the retargeted character from displaying a
		sharp bend in its neck, or a straight neck-to-chin curve.
		- At 100%, a maximum of the neck rotation is spread back to the spine, creating a smoother bend in the neck. 
		- At 50% (the default value), this property has no effect.
		- At 0%, the neck is bent even more sharply than the default. */
    HIKTopSpineCorrectionId,
    HIKLowerSpineCorrectionId,
	/**	This property is used in cunjunction of SnS Neck & Spine Reach value. It indicate whether to smooth the reach or not */
	HIKSnSSmoothReach,
    /** This property allows to lock the character's hips on it's TStance default position */
    HIKLockXId,
    HIKLockYId,
    HIKLockZId,
    /** This property allows to switch on/off realistic arm solving */
    HIKRealisticArmSolvingId,
	/** Extra roll bones tuning (up to 5 leaf roll bones per half limb) */
	HIKLeafLeftUpLegRoll1Id,
    HIKLeafLeftLegRoll1Id,
    HIKLeafRightUpLegRoll1Id,
    HIKLeafRightLegRoll1Id,
    HIKLeafLeftArmRoll1Id,
    HIKLeafLeftForeArmRoll1Id,
    HIKLeafRightArmRoll1Id,
    HIKLeafRightForeArmRoll1Id,
	HIKLeafLeftUpLegRoll2Id,
    HIKLeafLeftLegRoll2Id,
    HIKLeafRightUpLegRoll2Id,
    HIKLeafRightLegRoll2Id,
    HIKLeafLeftArmRoll2Id,
    HIKLeafLeftForeArmRoll2Id,
    HIKLeafRightArmRoll2Id,
    HIKLeafRightForeArmRoll2Id,
	HIKLeafLeftUpLegRoll3Id,
    HIKLeafLeftLegRoll3Id,
    HIKLeafRightUpLegRoll3Id,
    HIKLeafRightLegRoll3Id,
    HIKLeafLeftArmRoll3Id,
    HIKLeafLeftForeArmRoll3Id,
    HIKLeafRightArmRoll3Id,
    HIKLeafRightForeArmRoll3Id,
	HIKLeafLeftUpLegRoll4Id,
    HIKLeafLeftLegRoll4Id,
    HIKLeafRightUpLegRoll4Id,
    HIKLeafRightLegRoll4Id,
    HIKLeafLeftArmRoll4Id,
    HIKLeafLeftForeArmRoll4Id,
    HIKLeafRightArmRoll4Id,
    HIKLeafRightForeArmRoll4Id,
	HIKLeafLeftUpLegRoll5Id,
    HIKLeafLeftLegRoll5Id,
    HIKLeafRightUpLegRoll5Id,
    HIKLeafRightLegRoll5Id,
    HIKLeafLeftArmRoll5Id,
    HIKLeafLeftForeArmRoll5Id,
    HIKLeafRightArmRoll5Id,
    HIKLeafRightForeArmRoll5Id,
	HIKLeftLegFullRollExtractionId,
	HIKRightLegFullRollExtractionId,
	HIKLeftArmFullRollExtractionId,
	HIKRightArmFullRollExtractionId,

    HIKLastPropertyId	//!< Marks the end of the enumeration.
};

/*!	\enum HIKPropertyModeType
 *	@ingroup PropertyInfo
 *	\brief Lists the possible mode types for character properties. See HIKGetPropertyInfoModeType().
 * 
 *	Possible modes are:
 *		- Off:  Property is off.
 *		- On,   Property is on.
 *		- Auto, Property value is controlled by HumanIK.
 *		- User, Property value is controlled by the user.
 *
 *	\remarks The values listed for each mode in the enumeration descriptions, such as "Off (0), On (1)", are the values that must be passed to the \p pMode parameter of the HIKSetPropertyMode() function when the mode is set. See HIKSetPropertyMode() and HIKGetPropertyMode().
 */
enum HIKPropertyModeType
{
    HIKPropertyNoMode = 0,		//!< Properties with this mode type are always On, and their current values are always taken into account by the HumanIK solvers.
    HIKPropertyOffOn,			//!< Properties with this mode type can be set to either the Off (0) or On (1) mode.
    HIKPropertyOffAutoUser,		//!< Properties with this mode type can be set to any of the Off (0), Auto (1), or User (2) modes.
    HIKPropertyAutoUser			//!< Properties with this mode type can be set to either the Auto (0) or User (1) mode, but cannot be disabled. 
};

/*!	\enum HIKPropertyValueType
 *	@ingroup PropertyInfo
 *	\brief Lists the possible value types for character properties. See HIKGetPropertyInfoValueType().
 */
enum HIKPropertyValueType
{ 
    HIKPropertyScalar = 0                      //!< Property is a scalar.    
};

/*!	\enum HIKPropertyUnit
 *	@ingroup PropertyInfo
 *	\brief Lists the possible unit types for character properties. See HIKGetPropertyInfoUnit().
 */
enum HIKPropertyUnit
{ 
    HIKPropertyNoUnit = 0,                      //!< Indicates that the value of this property should never be used. Typically used only for properties with mode type ::HIKPropertyOffOn, to indicate that the property is a simple on/off toggle.
    HIKPropertyPercent,                         //!< The value of the property is expressed in the range between 0.0 and 1.0.
    HIKPropertySecond,                          //!< The value of the property is stored in seconds.
    HIKPropertyCentimeter,                      //!< The value of the property is a scalar distance. The unit of measure should be the same as the unit used when characterizing the geometry of your HIKCharacter. This unit is referred to as a "centimeter" only because the default values of all properties with this value type are sized for characters approximately 180 units tall.
    HIKPropertyDegree,                          //!< The value of the property is stored in degrees.
    HIKPropertyEnum,						    //!< The value of the property is an integer, whose interpretation is defined by an enumeration specific to that property. See each property description for details. Use the HIKSetPropertyMode() and HIKGetPropertyMode() functions to set and get the enumeration values for these properties.
    HIKPropertyReal                             //!< The value of the property is an arbitrary floating-point number.
};

/*!	see enum ::HIKPropertyModeType */
typedef enum HIKPropertyModeType    eHIKPropertyModeType;
/*!	see enum ::HIKPropertyValueType */
typedef enum HIKPropertyValueType   eHIKPropertyValueType;
/*!	see enum ::HIKPropertyUnit */
typedef enum HIKPropertyUnit        eHIKPropertyUnit;

// ***********************************************
/**	\defgroup PropertyInfo Retrieving Property Information
 *	\ingroup PropertyState
 *	\brief This section describes functions for retrieving information about character properties, such as their minimum and maximum values, mode types, current mode, name, etc.
 *
 *	These functions are typically of use when building a graphical user interface for controlling character properties.
 *
 *	For more information on property modes, mode types, and values, see ~{ Character Properties }~.
 */

/**	@ingroup PropertyInfo
 *	\brief Retrieves a human-readable, English-language string that identifies property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						Property name.
 */
HIK_EXPORT const char*            HIK_API HIKGetPropertyName(int pPropertyId);

/**	@ingroup PropertyInfo
 *	\brief Retrieves the unique ID of property \p pName from its descriptive name.
 *	\param pName				Unique name of the property. Must match the string returned by HIKGetPropertyName() for the property.
 *	\return						Property ID. See the ::HIKProperty enumeration for possible values. -1 indicates that no matching property could be found.
 */
HIK_EXPORT int                    HIK_API HIKGetPropertyId(const char* pName);

/**	@ingroup PropertyInfo
 *	\brief Retrieves the mode type for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						An enumeration value indicating the possible mode types for the property. See the ::HIKPropertyModeType enumeration for possible values.
 */
HIK_EXPORT eHIKPropertyModeType   HIK_API HIKGetPropertyInfoModeType(int pPropertyId);

/**	@ingroup PropertyInfo
 *	\brief Retrieves the value type for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						An enumeration value indicating the value type for the property. See the ::HIKPropertyValueType enumeration for possible values.
 */
HIK_EXPORT eHIKPropertyValueType  HIK_API HIKGetPropertyInfoValueType(int pPropertyId);

/**	@ingroup PropertyInfo
 *	\brief Retrieves the unit type for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						An enumeration value indicating the unit type for the property. See the ::HIKPropertyUnit enumeration for possible values.
 */
HIK_EXPORT eHIKPropertyUnit       HIK_API HIKGetPropertyInfoUnit(int pPropertyId);

/**	@ingroup PropertyInfo
 *	\brief Retrieves the default mode for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						An integer that indicates the default mode for the property. The interpretation of this integer depends on the mode type of the property. See the ::HIKPropertyModeType enumeration.
 */
HIK_EXPORT int                   HIK_API HIKGetPropertyInfoDefaultMode(int pPropertyId);

/**	@ingroup PropertyInfo
 *	\brief Retrieves the default value for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						The default value of the property.
 */
HIK_EXPORT float                HIK_API HIKGetPropertyInfoDefaultValue(int pPropertyId);

/**	@ingroup PropertyInfo
 *	\brief Retrieves the minimum accepted value for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						The minimum value of the property.
 */
HIK_EXPORT float                HIK_API HIKGetPropertyInfoDefaultMin(int pPropertyId);

/**	@ingroup PropertyInfo
 *	\brief Retrieves the maximum accepted value for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						The maximum value of the property.
 */
HIK_EXPORT float                HIK_API HIKGetPropertyInfoDefaultMax(int pPropertyId);

/**	@ingroup PropertyInfo
 *	\brief Retrieves a human-readable, English-language string that identifies mode \p pMode for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\param pMode				An integer that indicates the mode whose name you want to retrieve. The interpretation of this integer depends on the mode type of the property. See the ::HIKPropertyModeType enumeration.
 *	\return						A string identifying the current mode of the property.
 */
HIK_EXPORT const  char*         HIK_API HIKGetPropertyModeName(int pPropertyId, int pMode);

/**	@ingroup PropertyInfo
 *	\brief Retrieves a human-readable, English-language string that identifies the enumeration value \p pValue for property \p pPropertyId.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values. This property must have the unit type ::HIKPropertyEnum.
 *	\param pValue				An integer that indicates the enumeration value whose name you want to retrieve. 
 *	\return						A string identifying the enumeration value.
 */
HIK_EXPORT const char*          HIK_API HIKGetPropertyEnumName(int pPropertyId, int pValue);

/**	@ingroup PropertyInfo
 *	\brief Indicates whether or not the property is a description. 
 *
 *	A property is typically considered to be a "description" if it defines the character's stance or dimensions 
 *	(such as the properties used to define the outline of the character's feet and hands for the floor contact engine). 
 *	Non-descriptive properties, by contrast, typically control or constrain the HumanIK solvers in specific ways, as is
 *	the case for most other properties.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						1 if the property is a description, 0 otherwise. 
 */
HIK_EXPORT int					 HIK_API HIKIsPropertyDescription(int pPropertyId);




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

/**	@ingroup Constructor 
 *	\brief Create a new HIKPropertySetState.
 *	\param pMalloc				Pointer to a memory allocation function. If you do not have a custom memory allocation function, use &malloc.
 */
HIK_EXPORT HIKPropertySetState * HIK_API HIKPropertySetStateCreate(HIKMalloc pMalloc);

/**	\ingroup Constructor 
 *	\brief Create a new HIKPropertySetState in the buffer \p pBuffer.
 *
 *	\HIKPropertySetStates created using this function do not need to be destroyed with HIKPropertySetStateDestroy(), 
 *	as the memory allocation is typically managed outside HumanIK.
 *	\param pBuffer				Pre-allocated memory buffer of the appropriate size, aligned on 16 bytes.
 */
HIK_EXPORT HIKPropertySetState * HIK_API HIKPropertySetStateCreateInPlace(void* pBuffer);

/**	@ingroup Destructor
 *	\brief Destroy HIKPropertySetState \p pPropertySetState.
 *	\param pPropertySetState	HIKPropertySetState to destroy.
 *	\param pFree				Pointer to a memory de-allocation function. If you do not have a custom memory de-allocation function, use &free.
 */
HIK_EXPORT void                 HIK_API HIKPropertySetStateDestroy(HIKPropertySetState *pPropertySetState, HIKFree pFree);

/**	\brief Retrieves the size of an HIKPropertySetState object in bytes.
 *	\ingroup Stream
 */
HIK_EXPORT size_t               HIK_API HIKPropertySetStateSize();



// ***********************************************
/**	\defgroup PropertyState Character Properties
 *	\ingroup CharacterSetup
 *	\brief This section describes the functions provided for setting and retrieving the modes and values of character properties within \HIKPropertySetStates. 
 *
 *	For more information on property modes, mode types, and values, see ~{ Character Properties }~.
 */

/**	@ingroup PropertyState
 *	\brief Retrieves the current mode set for property \p pPropertyId in HIKPropertySetState \p pState.
 *
 *	See the description of each property for details on interpreting the enumeration values that can be returned by each property.
 *	\param pState				HIKPropertySetState containing the property.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						An integer that indicates the current mode of the property. The interpretation of this integer depends on the mode type of the property. See the ::HIKPropertyModeType enumeration.
 */
HIK_EXPORT int                   HIK_API HIKGetPropertyMode (HIKPropertySetState *pState, int pPropertyId);

/**	@ingroup PropertyState
 *	\brief Retrieves the current value set for property \p pPropertyId in HIKPropertySetState \p pState.
 *	\param pState				HIKPropertySetState containing the property.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						The current value of the property.
 */
HIK_EXPORT float                 HIK_API HIKGetPropertyValue(HIKPropertySetState *pState, int pPropertyId);

/**	@ingroup PropertyState
 *	\brief Sets the current mode for property \p pPropertyId in HIKPropertySetState \p pState.
 *
 *	See the description of each property for details on the enumeration values that can be set for that property.
 *	\param pState				HIKPropertySetState containing the property.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\param pMode				An integer that indicates the mode to set for the property. The interpretation of this integer depends on the mode type of the property. See the ::HIKPropertyModeType enumeration.
 */
HIK_EXPORT void                  HIK_API HIKSetPropertyMode (HIKPropertySetState *pState, int pPropertyId, int pMode);

/**	@ingroup PropertyState
 *	\brief Sets the current value for property \p pPropertyId in HIKPropertySetState \p pState.
 *	\param pState				HIKPropertySetState containing the property.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\param pValue				The current value of the property.
 */
HIK_EXPORT void                  HIK_API HIKSetPropertyValue(HIKPropertySetState *pState, int pPropertyId, float pValue);

/**	@ingroup PropertyState
 *	\brief Copies all values and mode settings from HIKPropertySetState \p pStateIn to HIKPropertySetState \p pStateOut.
 *	\param pStateIn				Input HIKPropertySetState.
 *	\param pStateOut			Output HIKPropertySetState.
 */
HIK_EXPORT void                  HIK_API HIKPropertySetStateCopy(HIKPropertySetState *pStateOut,HIKPropertySetState *pStateIn);

/**	@ingroup PropertyState
 *	\brief Indicates whether or not property \p pPropertyId in HIKPropertySetState \p pState is active--i.e. whether its value is currently taken into account by the HumanIK solvers.
 *	\param pState				HIKPropertySetState containing the property.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						True if the property is active, false otherwise.
 */
HIK_EXPORT int                  HIK_API HIKIsPropertyActive(HIKPropertySetState *pState, int pPropertyId);

/**	@ingroup PropertyState
 *	\brief Indicates whether or not the current mode of property \p pPropertyId in HIKPropertySetState \p pState is "auto".
 *	\param pState				HIKPropertySetState containing the property.
 *	\param pPropertyId			Unique ID of the property. See the ::HIKProperty enumeration for possible values.
 *	\return						True if the property is auto, false otherwise.
 */
HIK_EXPORT int					 HIK_API HIKIsPropertyAuto(HIKPropertySetState *pState, int pPropertyId);



#ifdef __cplusplus
}
#endif

#endif
