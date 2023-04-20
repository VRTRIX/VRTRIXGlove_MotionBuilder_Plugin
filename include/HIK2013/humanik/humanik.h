/*!	\file humanik.h
 *	\brief Main header file for HumanIK.
 *
 *	This file contains the HumanIK retargeting and full-body IK solvers.
 */

/**************************************************************************************

Copyright © 2009 Autodesk, Inc.
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

#ifndef _HUMAN_IK_
#define _HUMAN_IK_

#define HUMANIK_VERSION_MAJOR  2013
#define HUMANIK_VERSION_MINOR  0
#define HUMANIK_VERSION_THIRD  2

#ifndef HIK_EXPORT     
    #define HIK_EXPORT extern    
#endif

#if ( !defined(_MSC_VER) && !defined(HIK_API) )
	#define HIK_API
#else 
	#define HIK_API  __cdecl
#endif

#include <stddef.h> // for size_t

#ifdef __cplusplus
extern "C" {
#endif

/* *********************************************** */
/*!	\enum HIKNodeId
 *	\brief Lists all Nodes known to HumanIK, used to set up and access data for \HIKCharacters.
 *	\sa ~{ Mapping Joints to HumanIK Nodes and Effectors }~.
 *	\remarks Some Nodes are required for all characters. Others are optional. 
 */
enum HIKNodeId 
{
    ReferenceNodeId = 0,			//!< An optional repository for the overall translation, rotation and scale of your character.
	/*! @{ */
	/*! Required. */
	HipsNodeId,
    LeftHipNodeId,
    LeftKneeNodeId,
    LeftAnkleNodeId,
    RightHipNodeId,
    RightKneeNodeId,
    RightAnkleNodeId,
    WaistNodeId,
    LeftShoulderNodeId,
    LeftElbowNodeId,
    LeftWristNodeId,
    RightShoulderNodeId,
    RightElbowNodeId,
    RightWristNodeId,
    HeadNodeId,
	/*! @} */
	/*! @{ */
	/*! Optional. */
    LeftFootNodeId,
    RightFootNodeId,
    LeftCollarNodeId,
    RightCollarNodeId,
    NeckNodeId,
    LeftHandNodeId,
    RightHandNodeId,
    Spine1NodeId,
    Spine2NodeId,
    Spine3NodeId,
    Spine4NodeId,
    Spine5NodeId,
    Spine6NodeId,
    Spine7NodeId,
    Spine8NodeId,
    Spine9NodeId,
    Neck1NodeId,
    Neck2NodeId,
    Neck3NodeId,
    Neck4NodeId,
    Neck5NodeId,
    Neck6NodeId,
    Neck7NodeId,
    Neck8NodeId,
    Neck9NodeId,
    LeftHipRollNodeId,
    LeftKneeRollNodeId,
    RightHipRollNodeId,
    RightKneeRollNodeId,
    LeftShoulderRollNodeId,
    LeftElbowRollNodeId,
    RightShoulderRollNodeId,
    RightElbowRollNodeId,
    HipsTranslationId,
    LeftThumbANodeId,
    LeftThumbBNodeId,
    LeftThumbCNodeId,
    LeftThumbDNodeId,
    LeftIndexANodeId,
    LeftIndexBNodeId,
    LeftIndexCNodeId,
    LeftIndexDNodeId,
    LeftMiddleANodeId,
    LeftMiddleBNodeId,
    LeftMiddleCNodeId,
    LeftMiddleDNodeId,
    LeftRingANodeId,
    LeftRingBNodeId,
    LeftRingCNodeId,
    LeftRingDNodeId,
    LeftPinkyANodeId,
    LeftPinkyBNodeId,
    LeftPinkyCNodeId,
    LeftPinkyDNodeId,
    LeftExtraFingerANodeId,
    LeftExtraFingerBNodeId,
    LeftExtraFingerCNodeId,
    LeftExtraFingerDNodeId,
    RightThumbANodeId,
    RightThumbBNodeId,
    RightThumbCNodeId,
    RightThumbDNodeId,
    RightIndexANodeId,
    RightIndexBNodeId,
    RightIndexCNodeId,
    RightIndexDNodeId,
    RightMiddleANodeId,
    RightMiddleBNodeId,
    RightMiddleCNodeId,
    RightMiddleDNodeId,
    RightRingANodeId,
    RightRingBNodeId,
    RightRingCNodeId,
    RightRingDNodeId,
    RightPinkyANodeId,
    RightPinkyBNodeId,
    RightPinkyCNodeId,
    RightPinkyDNodeId,
    RightExtraFingerANodeId,
    RightExtraFingerBNodeId,
    RightExtraFingerCNodeId,
    RightExtraFingerDNodeId,
    LeftFootThumbANodeId,
    LeftFootThumbBNodeId,
    LeftFootThumbCNodeId,
    LeftFootThumbDNodeId,
    LeftFootIndexANodeId,
    LeftFootIndexBNodeId,
    LeftFootIndexCNodeId,
    LeftFootIndexDNodeId,
    LeftFootMiddleANodeId,
    LeftFootMiddleBNodeId,
    LeftFootMiddleCNodeId,
    LeftFootMiddleDNodeId,
    LeftFootRingANodeId,
    LeftFootRingBNodeId,
    LeftFootRingCNodeId,
    LeftFootRingDNodeId,
    LeftFootPinkyANodeId,
    LeftFootPinkyBNodeId,
    LeftFootPinkyCNodeId,
    LeftFootPinkyDNodeId,
    LeftExtraFootFingerANodeId,
    LeftExtraFootFingerBNodeId,
    LeftExtraFootFingerCNodeId,
    LeftExtraFootFingerDNodeId,
    RightFootThumbANodeId,
    RightFootThumbBNodeId,
    RightFootThumbCNodeId,
    RightFootThumbDNodeId,
    RightFootIndexANodeId,
    RightFootIndexBNodeId,
    RightFootIndexCNodeId,
    RightFootIndexDNodeId,
    RightFootMiddleANodeId,
    RightFootMiddleBNodeId,
    RightFootMiddleCNodeId,
    RightFootMiddleDNodeId,
    RightFootRingANodeId,
    RightFootRingBNodeId,
    RightFootRingCNodeId,
    RightFootRingDNodeId,
    RightFootPinkyANodeId,
    RightFootPinkyBNodeId,
    RightFootPinkyCNodeId,
    RightFootPinkyDNodeId,
    RightExtraFootFingerANodeId,
    RightExtraFootFingerBNodeId,
    RightExtraFootFingerCNodeId,
    RightExtraFootFingerDNodeId,
    LeftThumbInNodeId,
    LeftIndexInNodeId,
    LeftMiddleInNodeId,
    LeftRingInNodeId,
    LeftPinkyInNodeId,
    LeftExtraFingerInNodeId,
    RightThumbInNodeId,
    RightIndexInNodeId,
    RightMiddleInNodeId,
    RightRingInNodeId,
    RightPinkyInNodeId,
    RightExtraFingerInNodeId,
    LeftFootThumbInNodeId,
    LeftFootIndexInNodeId,
    LeftFootMiddleInNodeId,
    LeftFootRingInNodeId,
    LeftFootPinkyInNodeId,
    LeftExtraFootFingerInNodeId,
    RightFootThumbInNodeId,
    RightFootIndexInNodeId,
    RightFootMiddleInNodeId,
    RightFootRingInNodeId,
    RightFootPinkyInNodeId,
    RightExtraFootFingerInNodeId,
    LeftCollarExtraNodeId,
    RightCollarExtraNodeId,
	/*! @} */
	LastNodeId						//!< Marks the end of the enumeration.
};

/* *********************************************** */
/*!	\enum HIKEffectorId
 *	\brief Lists all Effectors used by HumanIK as goal points for IK solving.
 *	\sa ~{ Mapping Joints to HumanIK Nodes and Effectors }~.
 */
enum HIKEffectorId
{
	/*!	Provides an IK goal point for an imaginary point on the character's skeleton that lies exactly half-way between
		the placement of LeftHipNodeId and RightHipNodeId when the character is in its default T-stance. */
	HipsEffectorId = 0,				// 0 
	LeftAnkleEffectorId,			/*!< Provides an IK goal point for the LeftAnkleNodeId. */ // 1 
	RightAnkleEffectorId,			/*!< Provides an IK goal point for the RightAnkleNodeId. */ // 2 
	LeftWristEffectorId,			/*!< Provides an IK goal point for the LeftWristNodeId. */ // 3 
	RightWristEffectorId,			/*!< Provides an IK goal point for the RightWristNodeId. */ // 4 
	LeftKneeEffectorId,				/*!< Provides an IK goal point for the LeftKneeNodeId. */ // 5 
	RightKneeEffectorId,			/*!< Provides an IK goal point for the RightKneeNodeId. */ // 6 
	LeftElbowEffectorId,			/*!< Provides an IK goal point for the LeftElbowNodeId. */ // 7 
	RightElbowEffectorId,			/*!< Provides an IK goal point for the RightElbowNodeId. */ // 8 
	ChestOriginEffectorId,			/*!< Provides an IK goal point for the WaistNodeId. */ // 9 
	/*!	Provides an IK goal point for an imaginary point on the character's skeleton that lies exactly half-way between
		the placement of LeftShoulderNodeId and RightShoulderNodeId when the character is in its default T-stance. */
	ChestEndEffectorId,				// 10 
	LeftFootEffectorId,				/*!< Provides an IK goal point for the LeftFootNodeId. */ // 11 
	RightFootEffectorId,			/*!< Provides an IK goal point for the RightFootNodeId. */ // 12 
	LeftShoulderEffectorId,			/*!< Provides an IK goal point for the LeftShoulderNodeId. */ // 13 
	RightShoulderEffectorId,		/*!< Provides an IK goal point for the RightShoulderNodeId. */ // 14 
	HeadEffectorId,					/*!< Provides an IK goal point for the HeadNodeId. */ // 15 
	LeftHipEffectorId,				/*!< Provides an IK goal point for the LeftHipNodeId. */ // 16 
	RightHipEffectorId,				/*!< Provides an IK goal point for the RightHipNodeId. */ // 17 
    LeftHandEffectorId,				/*!< Provides an IK goal point for the LeftHandNodeId. */ // 18 
	RightHandEffectorId,			/*!< Provides an IK goal point for the RightHandNodeId. */ // 19 
	LeftHandThumbEffectorId,		/*!< Provides an IK goal point for the last Node in the thumb of the left hand. */ // 20 
	LeftHandIndexEffectorId,		/*!< Provides an IK goal point for the last Node in the index finger of the left hand. */ // 21 
	LeftHandMiddleEffectorId,		/*!< Provides an IK goal point for the last Node in the middle finger of the left hand. */ // 22 
	LeftHandRingEffectorId,			/*!< Provides an IK goal point for the last Node in the ring finger of the left hand. */ // 23 
	LeftHandPinkyEffectorId,		/*!< Provides an IK goal point for the last Node in the pinky finger of the left hand. */ // 24 
	LeftHandExtraFingerEffectorId,	/*!< Provides an IK goal point for the last Node in the extra finger of the left hand. */ // 25 
	RightHandThumbEffectorId,		/*!< Provides an IK goal point for the last Node in the thumb of the right hand. */ // 26 
	RightHandIndexEffectorId,		/*!< Provides an IK goal point for the last Node in the index finger of the right hand. */ // 27 
	RightHandMiddleEffectorId,		/*!< Provides an IK goal point for the last Node in the middle finger of the right hand. */ // 28 
	RightHandRingEffectorId,		/*!< Provides an IK goal point for the last Node in the ring finger of the right hand. */ // 29 
	RightHandPinkyEffectorId,		/*!< Provides an IK goal point for the last Node in the pinky finger of the right hand. */ // 30 
	RightHandExtraFingerEffectorId,	/*!< Provides an IK goal point for the last Node in the extra finger of the right hand. */ // 31 
	LeftFootThumbEffectorId,		/*!< Provides an IK goal point for the last Node in the thumb of the left foot. */ // 32 
	LeftFootIndexEffectorId,		/*!< Provides an IK goal point for the last Node in the index toe of the left foot. */ // 33 
	LeftFootMiddleEffectorId,		/*!< Provides an IK goal point for the last Node in the middle toe of the left foot. */ // 34 
	LeftFootRingEffectorId,			/*!< Provides an IK goal point for the last Node in the ring toe of the left foot. */ // 35 
	LeftFootPinkyEffectorId,		/*!< Provides an IK goal point for the last Node in the pinky toe of the left foot. */ // 36 
	LeftFootExtraFingerEffectorId,	/*!< Provides an IK goal point for the last Node in the extra toe of the left foot. */ // 37 
	RightFootThumbEffectorId,		/*!< Provides an IK goal point for the last Node in the thumb of the right foot. */ // 38 
	RightFootIndexEffectorId,		/*!< Provides an IK goal point for the last Node in the index toe of the right foot. */ // 39 
	RightFootMiddleEffectorId,		/*!< Provides an IK goal point for the last Node in the middle toe of the right foot. */ // 40 
	RightFootRingEffectorId,		/*!< Provides an IK goal point for the last Node in the ring toe of the right foot. */ // 41 
	RightFootPinkyEffectorId,		/*!< Provides an IK goal point for the last Node in the pinky toe of the right foot. */ // 42 
	RightFootExtraFingerEffectorId,	/*!< Provides an IK goal point for the last Node in the extra toe of the right foot. */ // 43 
	LastEffectorId					/*!< Marks the end of the enumeration. */ // 44 
};

/* *********************************************** */
/*!	\enum HIKFloorContact
 *	\ingroup FloorContact
 *	\brief Lists the surfaces that can be controlled by the floor contact engine. 
 *
 *	Used when setting the transform matrix that defines the position of the floor for a limb. See HIKSetEffectorFloorStatefv() and HIKGetEffectorFloorStatefv().
 *	\sa ~{ Setting up Foot and Hand Contact }~.
 */
enum HIKFloorContact
{
    HIKLeftHandFloor=0,				//!< Left hand floor contact
    HIKRightHandFloor,				//!< Right hand floor contact
	HIKLeftFootFloor,				//!< Left foot floor contact
    HIKRightFootFloor,				//!< Right foot floor contact
	HIKLastFloorId					//!< Marks the end of the enumeration.
};

/* *********************************************** */
/*!	\enum HIKSolvingStep
 *	\brief Lists the solving steps supported by the IK solver. Used when setting the solving steps
 *	that the solver should perform. See HIKSetIKSolvingStep() and HIKGetIKSolvingStep().
 */
enum HIKSolvingStep
{ 
	/*!	Activates the full-body Pull engine for the inverse kinematics solver. You must specify this solving step in 
		order for the solver to take the Pull and Resist settings of your Effectors into account.*/
	HIKSolvingStepBodyPull			= 1 << 0,
	/*!	Activates the Foot and Hand Contact engine for the inverse kinematics solver. You must specify this solving step 
		in order for the solver to prevent your character's feet and hands from passing through oriented planes such as floors 
		and walls. See ~{ Foot and Hand Contact }~. */
	HIKSolvingStepContact			= 1 << 1,
	/*!	Configures the inverse kinematics solver to perform an initial approximate solving with the floor contact engine before
		invoking the full-body Pull engine. This first pass helps ensure that the Pull engine does not accidentally pull any other 
		body parts through the oriented planes specified for your character's hands and feet. You should use this solving step if you 
		use both the ::HIKSolvingStepBodyPull and ::HIKSolvingStepContact solving steps. */
	HIKSolvingStepContactApprox		= 1 << 2,
    HIKSolvingStepLeftShoulder		= 1 << 3,	//!< Solves the character's left collar bones: ::LeftCollarNodeId and ::LeftCollarExtraNodeId.
    HIKSolvingStepRightShoulder		= 1 << 4,	//!< Solves the character's right collar bones: ::RightCollarNodeId and ::RightCollarExtraNodeId.
    HIKSolvingStepLeftArm			= 1 << 5,	//!< Solves the character's left arm, from ::LeftShoulderNodeId to ::LeftHandNodeId inclusive.
    HIKSolvingStepRightArm			= 1 << 6,	//!< Solves the character's right arm, from ::RightShoulderNodeId to ::RightHandNodeId inclusive.
    HIKSolvingStepLeftLeg			= 1 << 7,	//!< Solves the character's left leg, from ::LeftHipNodeId to ::LeftFootNodeId inclusive.
    HIKSolvingStepRightLeg			= 1 << 8,	//!< Solves the character's right leg, from ::RightHipNodeId to ::RightFootNodeId inclusive.
    HIKSolvingStepLeftHand			= 1 << 9,	//!< Solves the fingers of the left hand. Note that ::LeftHandNodeId itself is included in ::HIKSolvingStepLeftArm.
    HIKSolvingStepRightHand			= 1 << 10,	//!< Solves the fingers of the right hand. Note that ::RightHandNodeId itself is included in ::HIKSolvingStepRightArm.
    HIKSolvingStepLeftFoot			= 1 << 11,	//!< Solves the toes of the left foot. Note that ::LeftFootNodeId itself is included in ::HIKSolvingStepLeftLeg.
    HIKSolvingStepRightFoot			= 1 << 12,	//!< Solves the toes of the right foot. Note that ::RightFootNodeId itself is included in ::HIKSolvingStepRightLeg. 
    HIKSolvingStepHead			    = 1 << 13,	//!< Solves the character's neck and head, including ::NeckNodeId, ::Neck1NodeId to ::Neck9NodeId, and ::HeadNodeId.
    HIKSolvingStepSpine				= 1 << 14,	//!< Solves the character's spine, including ::WaistNodeId, and ::Spine1NodeId to ::Spine9NodeId.
	HIKSolvingStepHipsTranslation	= 1 << 15,	//!< Adjusts the translation of the character's hips, if necessary.
	/*!	Shifts a percentage of the roll rotation from the character's shoulders, elbows, hips and knees to their respective roll bones. 
		The percentage of the roll rotation that is extracted from the Nodes and applied to the roll Nodes is specified by a set of character 
		properties. See ~{ General Properties }~. */
    HIKSolvingStepRollExtraction    = 1 << 16,
    HIKSolvingStepLeftArmSnS		= 1 << 17,	//!< Activates Squash & Strech for the left arm, from ::LeftShoulderNodeId to ::LeftHandNodeId inclusive.
    HIKSolvingStepRightArmSnS		= 1 << 18,	//!< Activates Squash & Strech for the right arm, from ::RightShoulderNodeId to ::RightHandNodeId inclusive.
    HIKSolvingStepLeftLegSnS		= 1 << 19,	//!< Activates Squash & Strech for the left arm, from ::LeftHipNodeId to ::LeftFootNodeId inclusive.
    HIKSolvingStepRightLegSnS		= 1 << 20,	//!< Activates Squash & Strech for the right arm, from ::RightHipNodeId to ::RightFootNodeId inclusive.
	/*!	Enables the solving steps for all body parts, from ::HIKSolvingStepLeftShoulder to ::HIKSolvingStepSpine. 
		Excludes pull, contact, hips translation, roll extraction and Squash 'n' Stretch. */
    HIKSolvingStepAllParts      = HIKSolvingStepLeftShoulder | HIKSolvingStepRightShoulder | HIKSolvingStepLeftArm  | HIKSolvingStepRightArm  |
                                  HIKSolvingStepLeftLeg      | HIKSolvingStepRightLeg      | HIKSolvingStepLeftHand | HIKSolvingStepRightHand |
                                  HIKSolvingStepLeftFoot     | HIKSolvingStepRightFoot     | HIKSolvingStepHead     | HIKSolvingStepSpine,
	/*!	Enables all solving steps listed above. */
	HIKSolvingStepAll = HIKSolvingStepBodyPull | HIKSolvingStepContact | HIKSolvingStepContactApprox | HIKSolvingStepAllParts | HIKSolvingStepHipsTranslation | HIKSolvingStepRollExtraction
};

/**	\typedef HIKMalloc
 *	Memory allocator function. This is exactly the same signature as \p malloc.
 */
typedef void* (HIK_API * HIKMalloc)(size_t);

/**	\typedef HIKFree
 *	Memory de-allocator function. This is exactly the same signature as \p free.
 */
typedef void  (HIK_API * HIKFree)(void *);


/* *********************************************** */
/**	\defgroup Object HumanIK Objects 
 *	\brief This section describes the principal objects used by HumanIK.
 */

/**	\struct HIKCharacter
 *	\ingroup Object
 *	\brief Defines a character to be used with HumanIK.
 *
 *	An HIKCharacter contains all the information required by HumanIK to define a character:
 *		- the Nodes used in the character's skeletal hierarchy.
 *		- the default characterization pose that defines the character's geometry.
 *		- degrees of freedom assigned to each Node, if any.
 *		- a parent offset assigned to each Node, if any.
 *
 *	The exact byte size of an HIKCharacter object depends on which joints the character uses, and whether it has allocated memory for parent offsets and DoF are allocated.
 *	See ~{ HumanIK Objects and Memory Management }~.
 *
 *	You can move HIKCharacter objects freely between memory locations, or send them to another processing unit through DMA. 
 *
 *	\remarks HIKCharacter objects should be used as pointers only. To create and destroy an HIKCharacter, see HIKCharacterCreate() and HIKCharacterDestroy().
 */
struct HIKCharacter;


/**	\struct HIKEffectorSetState
 *	\ingroup Object
 *	\brief Defines an HIKEffectorSetState.
 *
 *	Represents a set of IK goal points at a given moment in time. 
 *	It contains:
 *		- The global space transformation matrix for each Effector. See HIKSetEffectorStatefv() and HIKGetEffectorStatefv().
 *		- The IK solving steps to be performed by the solver. See HIKSetIKSolvingStep() and HIKGetIKSolvingStep().
 *		- The Reach Translation value for each Effector. See HIKSetTranslationActive() and HIKGetTranslationActive().
 *		- The Reach Rotation value for each Effector. See HIKSetRotationActive() and HIKGetRotationActive().
 *		- The Pull value for each Effector. See HIKSetPull() and HIKGetPull().
 *		- The Resist value for each Effector. See HIKSetResist(), HIKGetResist().
 *		- The floor contact position for each foot and hand. See HIKSetEffectorFloorStatefv() and HIKGetEffectorFloorStatefv().
 *
 *	For the size in memory of an HIKEffectorSetState, see ~{ HumanIK Objects and Memory Management }~.
 *
 *	You can move HIKEffectorSetState objects freely between memory locations, or send them to another processing unit through DMA. 
 *
 *	\remarks HIKEffectorSetState objects should be used as pointers only. To create and destroy an HIKEffectorSetState, see HIKEffectorSetStateCreate() and HIKEffectorSetStateDestroy().
 */
struct HIKEffectorSetState;


/**	\struct HIKCharacterState
 *	\ingroup Object
 *	\brief Defines a pose for a character.
 *
 *	This structure represents the pose of a specific character at a given moment in time. 
 *	It contains the global space transformation matrix for each Node. See HIKSetNodeStatefv() and HIKGetNodeStatefv().
 *
 *	The size of a HIKCharacterState depends on how many Nodes the character uses. See ~{ HumanIK Objects and Memory Management }~.
 *
 *	You can move HIKCharacterState objects freely between memory locations, or send them to another processing unit through DMA. 
 *
 *	\remarks HIKCharacterState objects should be used as pointers only. To create and destroy an HIKCharacterState, see HIKCharacterStateCreate() and HIKCharacterStateDestroy().
 */
struct HIKCharacterState;


/**	\struct HIKPropertySetState
 *	\ingroup Object
 *	\brief Defines a character's properties.
 *
 *	This structure contains the modes and values of all of a character's properties at a given moment in time. 
 *	These properties set detailed information about the character, and control the way the IK and retargeting solvers
 *	handle the character.
 *
 *	For the size in memory of an HIKPropertySetState, see ~{ HumanIK Objects and Memory Management }~.
 *
 *	You can move HIKPropertySetState objects freely between memory locations, or send them to another processing unit through DMA. 
 *
 *	\remarks HIKPropertySetState objects should be used as pointers only. To create and destroy an HIKPropertySetState, see HIKPropertySetStateCreate() and HIKPropertySetStateDestroy().
 */
struct HIKPropertySetState;

/**	\ingroup Object
 *	\brief Flags used in the characterization process, in conjunction with HIKCharacterDefinition.
 */
enum HIKNodeFlags
{
	HIKNodeNotUsed      = 0,                            /*!< Node is not characterized.                                                     */
	HIKNodeUsed         = 1 << 0,                       /*!< Node is characterized.                                                         */
    HIKNodeParentOffset = 1 << 1 | HIKNodeUsed,         /*!< Node has a parent unknown to HumanIK, used for local space transform and DoF. Transparently assigns ::HIKNodeUsed. */
	HIKNodeLimits       = 1 << 2 | HIKNodeParentOffset  /*!< Node has limits (DoF). Transparently assigns ::HIKNodeParentOffset, which in turn assigns ::HIKNodeUsed.           */
};

/**	\struct HIKCharacterDefinition
 *	\ingroup Object
 *	\brief Defines which Nodes are to be used by an HIKCharacter.
 *
 *	This structure is used when creating \HIKCharacters, to specify which Nodes that character will use. You must always initialize this 
 *	structure to 0 using a function like memcpy().
 *
 *	For details on using this structure, see also ~{ Initialization }~. 
 */
typedef struct sHIKCharacterDefinition
{
	/**	An array of integers that contains an element for each Node known to HumanIK, listed in the ::HIKNodeId enumeration. You must set each element
	*	in this array to a value in the ::HIKNodeFlags array, to indicate whether an HIKCharacter created from this definition should allocate 
	*	memory for that Node, and how much memory needs to be allocated. 
	*/
    int mUsedNodes[LastNodeId];
} HIKCharacterDefinition;


/* *********************************************** */
/**	@defgroup Constructor Constructors
 *	\ingroup Object
 *	\brief This section describes the functions used to create HIK objects.
 *
 *	For details on memory management when creating these objects, see ~{ HumanIK Objects and Memory Management }~.
 *
 *	For details on using these functions in the context of initializing HumanIK, see ~{ Initialization }~.
 */

	#if defined(HIK_VERBOSE)
	/*! Determines whether or not the specified HIKCharacterDefinition is valid: i.e. not missing any required Nodes. 
	 *	\pp If this method returns \c true, you should be able to create a valid HIKCharacter from the definition.
	 *	\pp If this method returns \c false, check the log for errors detected in the validation.
	 *	\pp Available only in verbose builds.
	 *	\param pCharacterDefinition			The HIKCharacterDefinition to validate.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateHierarchy(const HIKCharacterDefinition *pCharacterDefinition);

	/*! Determines whether or not the T-stance of the specified HIKCharacter is valid. This function validates:
	 *	-	That the hips and arms are aligned along the X axis.
	 *	-	That the spine is aligned along the Y axis.
	 *	-	That no two Nodes are at the same coordinates in 3D space.
	 *	\pp If this method returns \c true, you should be able to finalize the character geometry by calling HIKCharacterizeGeometry().
	 *	\pp If this method returns \c false, check the log for errors detected in the validation. 
	 *	\pp Available only in verbose builds. 
	 *	\param pCharacter					The HIKCharacter to validate.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateGeometry(const HIKCharacter *pCharacter);
#endif
/**	\ingroup Constructor 
 *	\brief Create a new HIKCharacter.
 *	\param		pCharacterDefinition	The HIKCharacterDefinition that specifies which Nodes your character will be using, and which Nodes have DoF and parent offsets.
 *	\param		pMalloc					Pointer to a memory allocation function. If you do not have a custom memory allocation function, use &malloc.
 *	\param		pValidationString		The customer identification string given to you by Autodesk to license the use of HumanIK in your project.
 *	\param		pValidationKey			The license key given to you by Autodesk to license the use of HumanIK in your project.
 *  \return		NULL if an error occurs during the creation. This may indicate an invalid license, or that required Nodes are missing in the character definition. 
 *				You can determine which Nodes are missing by calling HIKValidateRequiredBone() on your HIKCharacterDefinition.
 */
   HIK_EXPORT HIKCharacter	    * HIK_API HIKCharacterCreate( const HIKCharacterDefinition *pCharacterDefinition, HIKMalloc pMalloc, char *pValidationString, unsigned int pValidationKey);

/**	\ingroup Constructor 
 *	\brief Create a new HIKCharacter in the buffer \p pBuffer.
 *
 *	Characters created using this function do not need to be destroyed with HIKCharacterDestroy(), as the memory allocation is typically managed outside HumanIK.
 *	\param		pCharacterDefinition	The HIKCharacterDefinition that specifies which Nodes your character will be using, and which Nodes have DoF and parent offsets.
 *	\param		pBuffer					Pre-allocated memory buffer of the appropriate size, aligned on 16 bytes.
 *	\param		pValidationString		The customer identification string ("Customer String") given to you by Autodesk to license the use of HumanIK in your project.
 *	\param		pValidationKey			The license key ("Customer Key") given to you by Autodesk to license the use of HumanIK in your project.
 *  \return		NULL if an error occurs during the creation. This may indicate an invalid license, or that required Nodes are missing in the character definition. 
 *				You can determine which Nodes are missing by calling HIKValidateRequiredBone() on your HIKCharacterDefinition.
 */
   HIK_EXPORT HIKCharacter	    * HIK_API HIKCharacterCreateInPlace( const HIKCharacterDefinition *pCharacterDefinition, void* pBuffer, char *pValidationString, unsigned int pValidationKey);
   

/**	\ingroup Constructor 
 *	\brief Create a new HIKEffectorSetState. 
 *
 *	This HIKEffectorSetState will be used by the full-body IK solver.
 *	\param		pMalloc				Pointer to a memory allocation function. If you do not have a custom memory allocation function, use &malloc.
 */
HIK_EXPORT HIKEffectorSetState * HIK_API HIKEffectorSetStateCreate( HIKMalloc pMalloc);

/**	\ingroup Constructor 
 *	\brief Create a new HIKEffectorSetState in the buffer \p pBuffer.
 *
 *	This HIKEffectorSetState will be used by the full-body IK solver. \HIKEffectorSetStates created using this function do not need to be destroyed
 *	with HIKEffectorSetStateDestroy(), as the memory allocation is typically managed outside HumanIK. 
 *	\param		pBuffer				Pre-allocated memory buffer of the appropriate size, aligned on 16 bytes.
 */
HIK_EXPORT HIKEffectorSetState * HIK_API HIKEffectorSetStateCreateInPlace(void* pBuffer);

/**	\ingroup Constructor 
 *	\brief Create a new HIKCharacterState.
 *
 *	Each characterized joint requires 128 bytes of memory.
 *	\param		pCharacter			HIKCharacter associated with this HIKCharacterState.
 *	\param		pMalloc				Pointer to a memory allocation function. If you do not have a custom memory allocation function, use &malloc.
 *	\remarks						This HIKCharacterState cannot be shared between different \HIKCharacters.
 */
HIK_EXPORT HIKCharacterState   * HIK_API HIKCharacterStateCreate(const HIKCharacter *pCharacter, HIKMalloc pMalloc);

/**	\ingroup Constructor 
 *	\brief Create a new HIKCharacterState in the buffer \p pBuffer.
 *
 *	\HIKCharacterStates created using this function do not need to be destroyed with HIKCharacterStateDestroy(), as the memory allocation is 
 *	typically managed outside HumanIK. 
 *	\param pCharacter				HIKCharacter associated with this HIKCharacterState.
 *	\param pBuffer					Pre-allocated memory buffer of the appropriate size, aligned on 16 bytes.
 */
HIK_EXPORT HIKCharacterState * HIK_API HIKCharacterStateCreateInPlace(const HIKCharacter *pCharacter, void* pBuffer);

/* *********************************************** */
/**	\defgroup Destructor Destructors
 *	\ingroup Object
 *	\brief This section describes the functions used to destroy HIK objects.
 *
 *	For details on memory management when destroying these objects, see ~{ HumanIK Objects and Memory Management }~.
 *
 *	For details on using these functions in the context of closing HumanIK, see ~{ Cleanup }~.
 */

/**	\ingroup Destructor
 *	\brief Destroy HIKCharacter \p pCharacter.
 *	\param		pCharacter			Character to destroy.
 *	\param		pFree				Pointer to a memory de-allocation function. If you do not have a custom memory de-allocation function, use &free.
 */
HIK_EXPORT void  HIK_API HIKCharacterDestroy         (HIKCharacter        *pCharacter,      HIKFree pFree);

/**	\ingroup Destructor
 *	\brief Destroy HIKEffectorSetState \p pESetState.
 *	\param		pESetState			HIKEffectorSetState to destroy.
 *	\param		pFree				Pointer to a memory de-allocation function. If you do not have a custom memory de-allocation function, use &free.
 */
HIK_EXPORT void  HIK_API HIKEffectorSetStateDestroy  (HIKEffectorSetState *pESetState,      HIKFree pFree);

/**	\ingroup Destructor
 *	\brief Destroy HIKCharacterState \p pCharacterState.
 *	\param		pCharacterState		HIKCharacterState to destroy.
 *	\param		pFree				Pointer to a memory de-allocation function. If you do not have a custom memory de-allocation function, use &free.
 */
HIK_EXPORT void  HIK_API HIKCharacterStateDestroy    (HIKCharacterState   *pCharacterState, HIKFree pFree);

/* *********************************************** */
/**	\defgroup CharacterSetup Character Setup
 *	\brief This section describes the functions used to set up an HIKCharacter.
 */

/**	\defgroup CharacterLimits Limits (Degrees of Freedom)
 *	\ingroup CharacterSetup
 *	\brief This section describes the functions used to set up limits (Degrees of Freedom) for a character.
 *	\sa ~{ Degrees of Freedom }~.
 */

/**	\defgroup CharacterQuadruped Quadrupeds
 *	\ingroup CharacterSetup
 *	\sa ~{ Using HumanIK for Quadrupeds }~.
 *	\brief This section describes utility functions for use with quadruped characters.
 */

/*!	\enum HIKLimitActiveMask
 *	\ingroup CharacterLimits
 *	\brief Lists the possible types of limits that can be activated for a Node. See HIKSetMinXYZRotationfv(), HIKSetMaxXYZRotationfv(), and HIKSetLimitsfv().
 */
enum HIKLimitActiveMask
{ 
	HIKActiveMinX = 1 << 0,	//!< Activate minimum limit on X axis.
	HIKActiveMinY = 1 << 1,	//!< Activate minimum limit on Y axis.
	HIKActiveMinZ = 1 << 2,	//!< Activate minimum limit on Z axis.
	HIKActiveMaxX = 1 << 3,	//!< Activate maximum limit on X axis.
	HIKActiveMaxY = 1 << 4,	//!< Activate maximum limit on Y axis.
	HIKActiveMaxZ = 1 << 5 	//!< Activate maximum limit on Z axis.	
};

/*!	\enum HIKRotationOrder
 *	\ingroup CharacterLimits
 *	\brief Lists the possible rotation orders for the values set in the HIKSetRotationOrder() function.
 */
enum HIKRotationOrder
{ 
	HIKOrderEulerXYZ = 0,	//!< Euler x, y, z.
	HIKOrderEulerXYX,		//!< Euler x, y, x.
	HIKOrderEulerXZY,		//!< Euler x, z, y.
	HIKOrderEulerXZX,		//!< Euler x, z, x.
	HIKOrderEulerYZX,		//!< Euler y, z, x.
	HIKOrderEulerYZY,		//!< Euler y, z, y.
	HIKOrderEulerYXZ,		//!< Euler y, x, z.
	HIKOrderEulerYXY,		//!< Euler y, x, y.
	HIKOrderEulerZXY,		//!< Euler z, x, y.
	HIKOrderEulerZXZ,		//!< Euler z, x, z.
	HIKOrderEulerZYX,		//!< Euler z, y, x.
	HIKOrderEulerZYZ,		//!< Euler z, y, z.
	HIKOrderSphericXYZ		//!< Spheric x, y, z.
};

/*!	see enum ::HIKRotationOrder */
typedef enum HIKRotationOrder    eHIKRotationOrder;


/**	\brief Set the transform matrix for the Node \p pNodeId when the character is standing in the default T-stance.
 *	\ingroup CharacterSetup
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The unique ID of the Node that you want to set up. See the ::HIKNodeId enumeration for possible values.
 *	\param		pXForm				Default stance matrix for this Node in global space (4x4 column major matrix).
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterizeNodeStatefv(HIKCharacter *pCharacter, int pNodeId, const float  pXForm[16]);
/**	@copydoc HIKSetCharacterizeNodeStatefv()
 *	\ingroup CharacterSetup
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterizeNodeStatedv(HIKCharacter *pCharacter, int pNodeId, const double pXForm[16]);

/**	\brief Set the translation, orientation and scaling for the Node \p pNodeId when the character is standing in the default T-stance.
 *	\ingroup CharacterSetup
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The unique ID of the Node that you want to set up. See the ::HIKNodeId enumeration for possible values.
 *	\param		pT					Default stance translation for this joint in global space.
 *	\param		pQ					Default stance orientation for this joint in global space, expressed as a quaternion.
 *	\param		pS					Default stance scale for this joint in global space.
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterizeNodeStateTQSfv(HIKCharacter *pCharacter, int pNodeId, const float  pT[4], const float  pQ[4], const float  pS[4]);
/**	@copydoc HIKSetCharacterizeNodeStateTQSfv()
 *	\ingroup CharacterSetup
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterizeNodeStateTQSdv(HIKCharacter *pCharacter, int pNodeId, const double pT[4], const double pQ[4], const double pS[4]);

/**	\brief Retrieve the translation, orientation and scaling for the Node \p pNodeId when the character is standing in the default T-stance.
 *	\ingroup CharacterSetup
 *	\param		pCharacter			The character you want to query.
 *	\param		pNodeId				The Node that you want to query. See the ::HIKNodeId enumeration for possible values.
 *	\param		pT					Default stance translation for this joint in global space.
 *	\param		pQ					Default stance orientation for this joint in global space, expressed as a quaternion.
 *	\param		pS					Default stance scale for this joint in global space.
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterizeNodeStateTQSfv(const HIKCharacter *pCharacter, int pNodeId, float  pT[4], float  pQ[4], float  pS[4]);
/**	@copydoc HIKGetCharacterizeNodeStateTQSfv()
 *	\ingroup CharacterSetup
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterizeNodeStateTQSdv(const HIKCharacter *pCharacter, int pNodeId, double pT[4], double pQ[4], double pS[4]);

/**	\brief Retrieve the transform matrix for the Node \p pNodeId when the character is standing in the default T-stance.
 *	\ingroup CharacterSetup
 *	\param		pCharacter			The character you want to query.
 *	\param		pNodeId				The Node that you want to query. See the ::HIKNodeId enumeration for possible values.
 *	\param		pXForm				The transform matrix of this joint in the default T-stance, in global space.
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterizeNodeStatefv(const HIKCharacter *pCharacter, int pNodeId, float  pXForm[16]);

/**	\brief Set up and initialize character \p pCharacter for solving. 
 *
 *	Call this function after you have called HIKSetCharacterizeNodeStatefv() for all your character's Nodes. This function
 *	finalizes the default stance and calibrates the engine.
 *	\ingroup CharacterSetup
 *	\param		pCharacter			Character to set up and initialize.
 *	\remarks	The character must be standing in a T-stance, facing the positive direction of the Z axis, with the left hand pointing along the positive
 *				direction of the X axis and the right hand pointing along the negative direction of the X axis. See ~{ Overview }~ for an image.
 *				Your character MUST be characterized in this pose in order for the HumanIK solvers to be able to control your character.
 *	\return		\c false if there is an error in the provided T-stance.
*/
HIK_EXPORT bool	 HIK_API HIKCharacterizeGeometry(HIKCharacter *pCharacter);

/**	\brief Retrieve the default T-stance for character \p pCharacter, storing it in HIKCharacterState \p pCharacterState.
 *	This function always returns the same stance for the given character. The default stance does not differ before and after you perform a solve.
 *	\ingroup CharacterSetup
 *	\param		pCharacter			Character whose default stance is to be retrieved.
 *	\param[out]	pCharacterState		HIKCharacterState to contain the default stance.
 */
HIK_EXPORT void	 HIK_API HIKGetDefaultState(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState);


/**	\brief Calculate a basic seated pose for character \p pCharacter, storing it in HIKCharacterState \p pCharacterState.
 *	\ingroup CharacterSetup
 *	\param		pCharacter			Character whose seated pose is to be retrieved.
 *	\param[out]	pCharacterState		HIKCharacterState to contain the default stance.
 */
HIK_EXPORT void	 HIK_API HIKGetRelaxPose(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState);

/**	\brief Retrieve the characterization flag set for Node \p pNodeId in HIKCharacter \p pCharacter.
 *	\ingroup CharacterSetup
 *	\param		pCharacter			Character.
 *	\param		pNodeId				Node ID whose flag is to be retrieved. See the ::HIKNodeId enumeration for possible values.
 *	\return		A bit mask that indicates the status of Node \p pNodeId within HIKCharacter \p pCharacter. This bit mask is composed of the flags in the ::HIKNodeFlags enumeration.
 *				- If the Node is used by the character, the ::HIKNodeUsed flag will be \p true.
 *				- If the Node supports the use of a parent offset, the ::HIKNodeParentOffset flag will also be \p true 
 *				- If the Node supports the use of limits (Degrees of Freedom), the ::HIKNodeLimits flag will also be \p true 
 *				- If the Node is not used, all flags will be \p false. 
 */
HIK_EXPORT int    	 HIK_API HIKGetNodeUse(const HIKCharacter *pCharacter, int pNodeId);

/**	\brief Set the parent offset for Node \p pNodeId. 
 *
 *	This function is needed only if the parent joint is unknown to HumanIK, and if you are using either local space transforms or limits (DoF).
 *	\ingroup CharacterSetup
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The Node whose parent offset you want to set up. See the ::HIKNodeId enumeration for possible values.
 *	\param		pParentTOffset		The parent node translation offset, relative to the next HumanIK Node above the parent in the joint chain.
 *	\param		pParentQOffset		The parent node rotation offset, expressed as a quaternion., relative to the next HumanIK Node above the parent in the joint chain. This value must be normalized.
 *									You can calculate this offset as follows: <pre>pParentQOffset = inverse(HIKParentGQ) * RealParentGQ</pre>
 *									where:
 *									- \p HIKParentGQ is a quaternion containing the rotation of the next HumanIK joint above the unknown parent joint in the skeletal hierarchy, expressed in global space
 *									- \p RealParentGQ is a quaternion containing the rotation of the unknown parent joint, expressed in global space.
 *	\param		pParentSOffset		The parent node scaling offset, relative to the next HumanIK Node above the parent in the joint chain.
 */
HIK_EXPORT void	 HIK_API HIKSetParentOffsetfv(HIKCharacter *pCharacter, int pNodeId, const float pParentTOffset[4], const float pParentQOffset[4], const float pParentSOffset[4]);
/**	@copydoc HIKSetParentOffsetfv()
 *	\ingroup CharacterSetup
 */
HIK_EXPORT void	 HIK_API HIKSetParentOffsetdv(HIKCharacter *pCharacter, int pNodeId, const double pParentTOffset[4], const double pParentQOffset[4], const double pParentSOffset[4]);

/**	\brief Retrieve the parent offset set for Node \p pNodeId. 
 *
 *	This function is needed only if the parent joint is unknown to HumanIK, and if you are using either local space transforms or limits (DoF).
 *	\ingroup CharacterSetup
 *	\param		pCharacter			The character you want to get.
 *	\param		pNodeId				The Node whose parent offset you want to retrieve. See the ::HIKNodeId enumeration for possible values.
 *	\param		pParentTOffset		The parent node translation offset.
 *	\param		pParentQOffset		The parent node rotation offset, expressed as a quaternion.
 *	\param		pParentSOffset		The parent node scaling offset.
 */
HIK_EXPORT void	 HIK_API HIKGetParentOffsetfv(const HIKCharacter *pCharacter, int pNodeId, float pParentTOffset[4], float pParentQOffset[4], float pParentSOffset[4]);
/**	@copydoc HIKGetParentOffsetfv()
 *	\ingroup CharacterSetup
 */
HIK_EXPORT void	 HIK_API HIKGetParentOffsetdv(const HIKCharacter *pCharacter, int pNodeId, double pParentTOffset[4], double pParentQOffset[4], double pParentSOffset[4]);

/*!	\ingroup CharacterSetup
 *	\brief Lists the joints that can be inverted using the HIKInverseJoint() function.
 */
enum HIKMiddleJoint
{
    HIKLeftKnee = 0,	//!< Represents the left knee (HIKNodeId::LeftKneeNodeId).
    HIKRightKnee,		//!< Represents the right knee (HIKNodeId::RightKneeNodeId).
    HIKLeftElbow,		//!< Represents the left elbow (HIKNodeId::LeftElbowNodeId).
    HIKRightElbow		//!< Represents the right elbow (HIKNodeId::RightElbowNodeId).
};

/*!	see enum ::HIKMiddleJoint */
typedef enum HIKMiddleJoint eHIKMiddleJoint;

/**	\brief Reverses the direction in which a middle joint bends, such as a knee or elbow. 
 *
 *	If you characterize your character programmatically, this function can only be called after the character's geometry has been finalized 
 *	by the call to HIKCharacterizeGeometry().
 *	\ingroup CharacterSetup
 *	\param		pCharacter			The character you want to set up.
 *	\param		pJoint				The joint to be inverted. See the ::HIKMiddleJoint enumeration for possible values.
 *	\param		pInverse			Specifies the direction of rotation for the joint. 0 = normal rotation, any other value = inverse rotation.
 */
HIK_EXPORT void	 HIK_API HIKInverseJoint(HIKCharacter *pCharacter, eHIKMiddleJoint pJoint, int pInverse);

/**	\brief Indicates whether or not a middle joint is inverted.
 *
 *	If you characterize your character programmatically, this function can only be called after the character's geometry has been finalized 
 *	by the call to HIKCharacterizeGeometry().
 *	\ingroup CharacterSetup
 *	\param		pCharacter			The character whose joint inversion you want to query.
 *	\param		pJoint				The joint to be queried for its inversion state. See the ::HIKMiddleJoint enumeration for possible values.
 *	\return							0 = normal rotation, any other value = inverse rotation.
 */
HIK_EXPORT int	HIK_API HIKIsJointInverted(const HIKCharacter *pCharacter, eHIKMiddleJoint pJoint);

/**	\brief Set the minimum rotation for the Node \p pNodeId.
 *	\ingroup CharacterLimits
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The unique ID of the Node for which you want to set a minimum rotation. See the ::HIKNodeId enumeration for possible values.
 *	\param		pMin				The minimum rotation to allow for this Node. This is a vector in radians.
 *	\param		pMinActiveMask		Bit mask that determines which axes are activated. See the ::HIKLimitActiveMask enumeration for possible values. You can combine multiple values using the bitwise "OR" operator.
 */
HIK_EXPORT void	 HIK_API HIKSetMinXYZRotationfv(HIKCharacter *pCharacter, int pNodeId, const float pMin[3], int pMinActiveMask);
/**	@copydoc HIKSetMinXYZRotationfv()
 *	\ingroup CharacterLimits
 */
HIK_EXPORT void	 HIK_API HIKSetMinXYZRotationdv(HIKCharacter *pCharacter, int pNodeId, const double pMin[3], int pMinActiveMask);

/**	\brief Set the maximum rotation for the Node \p pNodeId.
 *	\ingroup CharacterLimits
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The unique ID of the Node for which you want to set a maximum rotation. See the ::HIKNodeId enumeration for possible values.
 *	\param		pMax				The maximum rotation to allow for this Node. This is a vector in radians.
 *	\param		pMaxActiveMask		Bit mask that determines which axes are activated. See the ::HIKLimitActiveMask enumeration for possible values. You can combine multiple values using the bitwise "OR" operator.
 */
HIK_EXPORT void	 HIK_API HIKSetMaxXYZRotationfv(HIKCharacter *pCharacter, int pNodeId, const float pMax[3], int pMaxActiveMask);
/**	@copydoc HIKSetMaxXYZRotationfv()
 *	\ingroup CharacterLimits
 */
HIK_EXPORT void	 HIK_API HIKSetMaxXYZRotationdv(HIKCharacter *pCharacter, int pNodeId, const double pMax[3], int pMaxActiveMask);

/**	\brief Sets the order in which the axes are specified in the limits set for Node \p pNodeId.
 *	\ingroup CharacterLimits   
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The unique ID of the Node for which you want to set the rotation order. See the ::HIKNodeId enumeration for possible values.
 *	\param		pRotationOrder		The rotation order to set. See the ::HIKRotationOrder enumeration for possible values.
 */
HIK_EXPORT void	 HIK_API HIKSetRotationOrder(HIKCharacter *pCharacter, int pNodeId, eHIKRotationOrder pRotationOrder);

/**	\brief Apply the pre rotation \p pPreQ to Node \p pNodeId.
 *	\ingroup CharacterLimits
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The unique ID of the Node for which you want to set the pre rotation. See the ::HIKNodeId enumeration for possible values.
 *	\param		pPreQ				The pre rotation to apply. This is a quaternion that must be normalized.
 */
HIK_EXPORT void	 HIK_API HIKSetPreQfv(HIKCharacter *pCharacter, int pNodeId, const float pPreQ[4]);
/**	@copydoc HIKSetPreQfv()
 *	\ingroup CharacterLimits
 */
HIK_EXPORT void	 HIK_API HIKSetPreQdv(HIKCharacter *pCharacter, int pNodeId, const double pPreQ[4]);

/**	\brief Apply the post rotation \p pPostQ to the Node \p pNodeId.
 *	\ingroup CharacterLimits
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The unique ID of the Node for which you want to set the post rotation. See the ::HIKNodeId enumeration for possible values.
 *	\param		pPostQ				The post rotation to apply. This is a quaternion that must be normalized.
 */
HIK_EXPORT void	 HIK_API HIKSetPostQfv(HIKCharacter *pCharacter, int pNodeId, const float pPostQ[4]);
/**	@copydoc HIKSetPostQfv()
 *	\ingroup CharacterLimits
 */
HIK_EXPORT void	 HIK_API HIKSetPostQdv(HIKCharacter *pCharacter, int pNodeId, const double pPostQ[4]);

/**	\brief Set up limits for Node \p pNodeId.
 *	\ingroup CharacterLimits
 *	\param		pCharacter			The character you want to set up.
 *	\param		pNodeId				The unique ID of the Node you want to set up. See the ::HIKNodeId enumeration for possible values.
 *	\param		pMin				Determines the minimum rotation, in radians, that the joint can achieve around each axis. The order in which the 
 *									X, Y and Z axes should be represented in this array depends on the value set for the \p pRotationOrder parameter.
 *	\param		pMax				Determines the maximum rotation, in radians, that the joint can achieve around each axis. The order in which the 
 *									X, Y and Z axes should be represented in this array depends on the value set for the \p pRotationOrder parameter.
 *	\param		pPreQ				A quaternion that defines the pre-rotation offset, which HumanIK will apply to the rotation of this Node before 
 *									testing whether the orientation of the Node lies within the minimum and maximum limits.
 *	\param		pPostQ				A quaternion that defines the post-rotation offset, which HumanIK will apply to the rotation of this Node after 
 *									testing whether the orientation of the Node lies within the minimum and maximum limits.
 *	\param		pActiveMask			Bit mask that determines which axes are activated. This mask may include any one or more of the elements in the 
 *									::HIKLimitActiveMask enumeration. You can combine multiple values using the | operator (bitwise OR).
 *	\param		pRotationOrder		An element from the ::HIKRotationOrder enumeration that indicates the order in which the X, Y and Z axes are listed in the 
 *									\p pMin and \p pMax parameters. This rotation order also determines the order in which HumanIK calculates Euler rotations. 
 *									Changing this order can help to avoid or alleviate issues with gimbal locking. \n\n 
 *									HumanIK always interprets the first axis in this rotation order as the roll axis for the Node. This axis should align 
 *									with the bone attached to the joint, controlling the way that bone rolls or twists around its center. 
 */
HIK_EXPORT void	 HIK_API HIKSetLimitsfv(HIKCharacter *pCharacter, int pNodeId, 
										   const float pMin[3], const float pMax[3], 
										   const float pPreQ[4], const float pPostQ[4],
										   int pActiveMask,
										   eHIKRotationOrder pRotationOrder);
/**	@copydoc HIKSetLimitsfv()
 *	\ingroup CharacterLimits
 */
HIK_EXPORT void	 HIK_API HIKSetLimitsdv(HIKCharacter *pCharacter, int pNodeId, 
										   const double pMin[3], const double pMax[3], 
										   const double pPreQ[4], const double pPostQ[4],
										   int pActiveMask,
										   eHIKRotationOrder pRotationOrder);


/**	\brief Retrieve the limits set for Node \p pNodeId.
 *	\ingroup CharacterLimits
 *	\param		pCharacter			The character you want to query.
 *	\param		pNodeId				The unique ID of the Node you want to query. See the ::HIKNodeId enumeration for possible values.
 *	\param		pMin				The minimum rotation, in radians, that the joint can achieve around each axis. The order in which the 
 *									X, Y and Z axes are stored in this array depends on the value set for the \p pRotationOrder parameter.
 *	\param		pMax				The maximum rotation, in radians, that the joint can achieve around each axis. The order in which the 
 *									X, Y and Z axes are stored in this array depends on the value set for the \p pRotationOrder parameter.
 *	\param		pPreQ				A quaternion that defines the pre-rotation offset, which HumanIK will apply to the rotation of this Node before 
 *									testing whether the orientation of the Node lies within the minimum and maximum limits.
 *	\param		pPostQ				A quaternion that defines the post-rotation offset, which HumanIK will apply to the rotation of this Node after 
 *									testing whether the orientation of the Node lies within the minimum and maximum limits.
 *	\param		pActiveMask			Bit mask that determines which axes are activated. See the ::HIKLimitActiveMask enumeration for possible values. 
 *	\param		pRotationOrder		An element from the ::HIKRotationOrder enumeration that indicates the order in which the X, Y and Z axes are listed in the 
 *	 								\p pMin and \p pMax parameters.
*/
HIK_EXPORT void	 HIK_API HIKGetLimitsfv(const HIKCharacter *pCharacter, int pNodeId, 
										   float pMin[3], float pMax[3], 
										   float pPreQ[4], float pPostQ[4],
										   int &pActiveMask,
										   eHIKRotationOrder &pRotationOrder);
/**	@copydoc HIKGetLimitsfv()
 *	\ingroup CharacterLimits
 */
HIK_EXPORT void	 HIK_API HIKGetLimitsdv(const HIKCharacter *pCharacter, int pNodeId, 
										   double pMin[3], double pMax[3], 
										   double pPreQ[4],double pPostQ[4],
										   int &pActiveMask,
										   eHIKRotationOrder &pRotationOrder);

/**	\brief Add quadruped offsets to HIKCharacterState \p pCharacterState.
 *	\ingroup CharacterQuadruped
 *	\param		pCharacter			The HIKCharacter to which the offsets will be added.
 *	\param		pCharacterState		The HIKCharacterState to which the offsets will be added.
 *	\remarks	All characters, both biped and quadruped, must be characterized in a T-stance. This default T-stance, returned by the
 *				HIKGetDefaultState() function, can provide a good neutral starting point for animating bipeds. However, it is not a
 *				natural position for quadrupeds. The HIKAddQuadripedOffset() function adds a set of offsets to the T-stance that produce
 *				a similar basic starting position for a quadruped. The following Nodes are offset to the following rotations:
 *				- ::HipsNodeId: 90.0,0.0,0.0.
 *				- ::LeftAnkleNodeId: 90.0,0.0,0.0.
 *				- ::RightAnkleNodeId: 90.0,0.0,0.0.
 *				- ::LeftCollarNodeId: 90.0,0.0,-90.0.
 *				- ::LeftShoulderNodeId: 0.0,0.0,-90.0.
 *				- ::RightCollarNodeId: 90.0,0.0,90.0.
 *				- ::RightShoulderNodeId: 0.0,0.0,90.0.
 *				- ::LeftElbowNodeId: 90.0,0.0,-90.0.
 *				- ::RightElbowNodeId: 90.0,0.0,90.0.
 */
HIK_EXPORT void	 HIK_API HIKAddQuadripedOffset(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState);

/**	\brief Subtract quadruped offsets from HIKCharacterState \p pCharacterState.
 *	\ingroup CharacterQuadruped
 *	\param		pCharacter			The HIKCharacter from which the offsets will be subtracted.
 *	\param		pCharacterState		The HIKCharacterState from which the offsets will be subtracted.
 *	\remarks	Reverses all offsets added by the HIKAddQuadripedOffset() function.
 */
HIK_EXPORT void	 HIK_API HIKSubQuadripedOffset(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState);

/* *********************************************** */
/**	\defgroup Retargeter Retargeting
 *	\brief This section describes the functions used to retarget animations.
 * 
 *	Retargeting takes an animation pre-recorded for a character, and uses that same animation to drive the movements
 *	of a different target character that may have a very different skeleton, dimensions or characteristics. 
 *	For retargeting, you need to have a source character, an HIKCharacterState that contains its current position
 *	(typically drawn from a pre-recorded animation) and a destination character. The retargeting solver creates a
 *	new pose for the destination character that mimics the source character's pose, and stores this pose in an
 *	HIKCharacterState that you provide. You retrieve this pose and apply it back to the destination character in your game.
 *
 *	You can also specify a variety of character properties for your destination character that control the operation of the
 *	retargeting solver. For example, you can provide Reach values that influence how closely the different parts of the
 *	destination character's body should match the positions of the source character's body.
 *	This step is done through a call to the IK solver after the retargeting process.  
 */

/**	\brief Given source character \p pSrcCharacter with HIKCharacterState \p pSrcCharacterState, calculate HIKCharacterState \p pCharacterState for destination character \p pDstCharacter.
 *
 *	\ingroup Retargeter
 *	This function calls the following functions in order.
 *		- HIKSolveForCharacterRetarget()
 *		- HIKSolveForCharacterPrepareEffectorSet()
 *		- HIKSolveForEffectorSetFloorContactApprox()
 * 		- HIKSolveForEffectorSetBodyPull()
 * 		- HIKSolveForEffectorSetArmsAndLegs()
 * 		- HIKSolveForEffectorSetFingersAndToes()
 * 		- HIKSolveForEffectorSetHeadAndNeck()
 * 		- HIKSolveForEffectorSetFloorContact()
 * 		- HIKSolveForEffectorSetHipsTranslation()
 * 		- HIKSolveForEffectorSetRollExtraction()
 *
 *	\param		pDstCharacter			Destination character.
 *	\param[out]	pCharacterState			HIKCharacterState for the destination character. This HIKCharacterState is used to store the final solution.
 *	\param		pSrcCharacter			Source character.
 *	\param		pSrcCharacterState		HIKCharacterState containing the current pose of the source character, which is to be adapted to the destination character.
 *	\param		pEffectorSetState		HIKEffectorSetState used for a full-body IK pass after the retargeting. Remember to set appropriate solving steps for this state. See HIKSetIKSolvingStep().
 *	\param		pDstPropertyState		HIKPropertySetState containing all character properties to be used by the solver for the destination character.
 *	\param		pSrcPropertyState		HIKPropertySetState for the source character. This state is only used if you have enabled the ::HIKSolvingStepContact solving step in your HIKEffectorSetState. If so, the property ::HIKFootBottomToAnkleId
 *										will be read from this HIKPropertySetState to define the height of the source character's ankles. This value is used to adapt the height of the poses generated for the destination character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForCharacter(const HIKCharacter *pDstCharacter, HIKCharacterState *pCharacterState, const HIKCharacter *pSrcCharacter, const HIKCharacterState *pSrcCharacterState, HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pDstPropertyState, const HIKPropertySetState *pSrcPropertyState);

/**	\brief Simple rotation mapper between \p pSrcCharacter and \p pDstCharacter.
 *	\ingroup Retargeter
 *
 *	\param		pDstCharacter			Destination character.
 *	\param[out]	pDstCharacterState		HIKCharacterState for the destination character. This HIKCharacterState is used to store the final solution.
 *	\param		pSrcCharacter			Source character.
 *	\param		pSrcCharacterState		HIKCharacterState containing the current pose of the source character, which is to be adapted to the destination character.
 *	\param		pDstPropertyState		HIKPropertySetState containing all character properties to be used by the solver for the destination character.
 *
*/
HIK_EXPORT void  HIK_API HIKSolveForCharacterRetarget(const HIKCharacter *pDstCharacter, HIKCharacterState *pDstCharacterState, const HIKCharacter *pSrcCharacter, const HIKCharacterState *pSrcCharacterState, const HIKPropertySetState *pDstPropertyState);

/**	\brief Sync IK \e pEffectorSetState on source FK \e pSrcCharacterState and adjust IK relative to destination character \e pDstCharacter.
 *	\ingroup Retargeter
 *
 *	\param		pDstCharacter			Destination character.
 *	\param[out]	pDstCharacterState		HIKCharacterState for the destination character. This HIKCharacterState is used to store the final solution.
 *	\param		pSrcCharacter			Source character.
 *	\param		pSrcCharacterState		HIKCharacterState containing the current pose of the source character, which is to be adapted to the destination character.
 *	\param[out]	pEffectorSetState		HIKEffectorSetState set up by this function to control a pass through the IK solver to finalize the retargeting. 
 *	\param		pDstPropertyState		HIKPropertySetState containing all character properties to be used by the solver for the destination character.
 *	\param		pSrcPropertyState		HIKPropertySetState for the source character. This state is only used if you have enabled the HIKSolvingStepContact solving step in your HIKEffectorSetState. If so, the property HIKFootBottomToAnkleId
 *										will be read from this HIKPropertySetState to define the height of the source character's ankles. This value is used to adapt the height of the poses generated for the destination character.
*/
HIK_EXPORT void  HIK_API HIKSolveForCharacterPrepareEffectorSet(const HIKCharacter *pDstCharacter, HIKCharacterState *pDstCharacterState, const HIKCharacter *pSrcCharacter, const HIKCharacterState *pSrcCharacterState, HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pDstPropertyState, const HIKPropertySetState *pSrcPropertyState);

// ***********************************************
/**	\defgroup IK Full-body IK
 *	\brief This section describes the functions used to perform a full-body IK solving.
 *
 *	To use full-body IK for a character, you must have already created an HIKCharacter object that defines your character.
 *	You need to create an HIKCharacterState for your character, and set the transform matrix of each Node in the HIKCharacterState to
 *	match the current pose of the character in your game. You must create an HIKEffectorSetState that defines the IK goal points for
 *	the character's body, values for the constraints (Reach Translation, Reach Rotation, Pull and Resist) that control how the
 *	IK solver balances the IK goal points, and the solving steps that the IK solver is to perform. Finally, you must create a Property
 *	Set State that defines a set of optional configuration parameters for the solver. You must then pass all of these objects to the 
 *	HIKSolveForEffectorSet() function to perform the solve. The solver stores its results in the same HIKCharacterState you pass in.
 */

/**	\ingroup EffectorSetupWrite
 *	\brief Retrieve the transform matrix of Effector \p pEffectorIndex for character \p pCharacter in HIKCharacterState \p pCharacterState.
 *	\param		pCharacter			Character to query.
 *	\param		pEffectorIndex		Unique ID of the Effector whose transform matrix you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pCharacterState		HIKCharacterState from which to retrieve the Effector placement.
 *	\param[out]	pXForm				Stores the transform matrix of the Effector in global space (4x4 column major matrix).
 *	\param		pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void     HIK_API HIKGetEffectorStateFromCharacterfv(const HIKCharacter *pCharacter, int pEffectorIndex, const HIKCharacterState *pCharacterState, const HIKPropertySetState *pPropertyState, float pXForm[16]);
/**	@copydoc HIKGetEffectorStateFromCharacterfv()
 *	This function converts floating-point numbers internally to double-precision. For best performance, use the HIKGetEffectorStateFromCharacterfv() function instead wherever possible. 
 *	\ingroup EffectorSetupWrite
 */
HIK_EXPORT void     HIK_API HIKGetEffectorStateFromCharacterdv(const HIKCharacter *pCharacter, int pEffectorIndex, const HIKCharacterState *pCharacterState, const HIKPropertySetState *pPropertyState, double pXForm[16]);

/**	\ingroup EffectorSetupWrite
 *	\brief Set up HIKEffectorSetState \p pEffectorSetState to match character \p pCharacter in HIKCharacterState \p pCharacterState.
 *	\param		pCharacter			Character to query.
 *	\param[out]	pEffectorSetState	HIKEffectorSetState to be set up. 
 *	\param		pCharacterState		HIKCharacterState from which to set up the HIKEffectorSetState.
 *	\param		pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void     HIK_API HIKEffectorSetFromCharacter(const HIKCharacter *pCharacter, HIKEffectorSetState *pEffectorSetState, const HIKCharacterState *pCharacterState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Solve character \p pCharacter with HIKEffectorSetState \p pEffectorSetState and initial HIKCharacterState \p pCharacterState, storing results in \p pCharacterState.
 *
 *	The HIKSolveForEffectorSet() function calls the following functions in order:
 *		- HIKSolveForEffectorSetBegin()
 *		- HIKSolveForEffectorSetFloorContactApprox()
 *		- HIKSolveForEffectorSetBodyPull()
 *		- HIKSolveForEffectorSetArmsAndLegs()
 *		- HIKSolveForEffectorSetFingersAndToes()
 *		- HIKSolveForEffectorSetHeadAndNeck()
 *		- HIKSolveForEffectorSetFloorContact()
 *		- HIKSolveForEffectorSetHipsTranslation()
 *		- HIKSolveForEffectorSetRollExtraction()
 *
 *	You can enable or disable different parts of the solver by calling the HIKSetIKSolvingStep() function
 *	to set the solving step in HIKEffectorSetState \p pEffectorSetState.
 *
 *	You can re-use the same HIKEffectorSetState over multiple calls to this function, changing the position, rotation and IK constraints of only the Effectors you need to modify.
 *
 *	Only Effectors with a Reach Translation or Reach Rotation value greater than 0 are taken into account.
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSet(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Initializes an IK solve for character \p pCharacter.
 *
 *	When not using the global HIKSolveForEffectorSet() function, you must start each IK solve with a call to HIKSolveForEffectorSetBegin().
 *	After this you can call one or more functions from the following list: 
 *		- HIKSolveForEffectorSetFloorContactApprox(), HIKSolveForEffectorSetBodyPull(), 
 *		- HIKSolveForEffectorSetArmsAndLegs(), HIKSolveForEffectorSetFingersAndToes(), 
 *		- HIKSolveForEffectorSetFingersAndToes(), HIKSolveForEffectorSetHeadAndNeck(), 
 *		- HIKSolveForEffectorSetFloorContact().
 *
 *	\param			pCharacter			Character to prepare.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetBegin(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Call the floor contact approximation solver for character \p pCharacter.
 *
 *	This solver moves the wrists and ankles to approximate locations above the floor position, if floor contact is enabled in the HIKPropertySetState \p pPropertyState.
 *
 *	This function should be called before the pull solver, to avoid having the feet and hands pulled below the floor. 
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetFloorContactApprox(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState,HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Call the pull solver for character \p pCharacter.
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetBodyPull(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState,HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Call the arms, legs and shoulders IK solver for character \p pCharacter.
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetArmsAndLegs(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState,HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Call the fingers and toes IK solver for character \p pCharacter.
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetFingersAndToes(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState,HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Call the head and neck IK solver for character \p pCharacter.
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetHeadAndNeck(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState,HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Call the floor solver for character \p pCharacter.
 *
 *	This solver move the wrist, ankle, fingers and toes above the floor position.
 *	Floor contact must be enabled into the Properties State \p pPropertyState.
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetFloorContact(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState,HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Call the special hips translation solver for character \p pCharacter.
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetHipsTranslation(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState,HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IK
 *	\brief Call the roll extraction solver for character \p pCharacter.
 *
 *	\param			pCharacter			Character to solve.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose for your character, which may influence the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties for the character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetRollExtraction(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState,HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

// ***********************************************
/**	\defgroup EffectorSetup Read/Write HIKEffectorSetState Data
 *	\brief This section describes the functions used to read and write data in \HIKEffectorSetStates.
 *
 *	For an overview, see ~{ Setting and Retrieving Data in HIKEffectorSetStates }~
 */

/**	\defgroup EffectorSetupRead Read HIKEffectorSetState Data
 *	\ingroup EffectorSetup
 *	\brief This section describes the functions used to read data from an HIKEffectorSetState.
 *
 *	All of these functions return translation.w = 0.f and scale.w = 1.f.
 */

/**	\defgroup EffectorSetupWrite Write HIKEffectorSetState Data
 *	\ingroup EffectorSetup
 *	\brief This section describes the functions used to write data to an HIKEffectorSetState.
 *
 *	All of these functions mask translation.w to 0.f and scale.w to 1.f.
 */

/** \brief Set the transform matrix of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose matrix you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose matrix you want to set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pXForm				Transform matrix to set for the Effector in global space (4x4 column major matrix).
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorStatefv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const float pXForm[16]);
/**	\copydoc HIKSetEffectorStatefv()
 *	\ingroup EffectorSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorStatedv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const double pXForm[16]);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) in global space of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState. Values are provided in separate arrays.
 *
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose translation, rotation and scaling values you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation, rotation and scaling values you want to set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pT					Translation value to set in global space.
 *	\param		pQ					Rotation value to set in global space.
 *	\param		pS					Scaling value to set in global space.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorStateTQSfv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const float pT[4], const float pQ[4], const float pS[4]);
/**	\copydoc HIKSetEffectorStateTQSfv()
 *	\ingroup EffectorSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorStateTQSdv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const double pT[4], const double pQ[4], const double pS[4]);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) in global space of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState. Values are read from specified offsets within a single array.
 *
 *	\ingroup EffectorSetupWrite
 *	The T, Q and S values are each expected to be expressed as an array of four floating-point numbers within the \p pTQS array, and the offset of each of these arrays must be aligned on 16 bytes. 
 *	The arrays containing the T, Q and S values may be in any order within the larger array. For example, the offset of the scaling data may be less than the offset of the translation data. 
 *	The \p pTQS array may also contain other arbitrary data values interspersed between the arrays containing the T, Q and S values, if that is convenient.
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose translation, rotation and scaling values you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation, rotation and scaling values you want to set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pTQS				Pointer to an array of floating-point numbers containing the data for the Effector in global space. This array must be aligned on 16 bytes.
 *	\param		pTOffset			Offset of the translation values within \p pTQS. This offset must be aligned on 16 bytes.
 *	\param		pQOffset			Offset of the rotation values within \p pTQS. This offset must be aligned on 16 bytes.
 *	\param		pSOffset			Offset of the scaling values within \p pTQS. This offset must be aligned on 16 bytes.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorStateTQSAlignfv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const float* pTQS, size_t pTOffset, size_t pQOffset, size_t pSOffset);

/**	\brief Set the translation (T) and quaternion rotation (Q) in global space of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState. Values are read from specified offsets within a single array.
 *
 *	\ingroup EffectorSetupWrite
 *	This function sets the scaling values for all axes to \p 1.0f.
 *
 *	The T and Q values are each expected to be expressed as an array of four floating-point numbers within the \p pTQ array, and the offset of each of these arrays must be aligned on 16 bytes. 
 *	The arrays containing the T and Q values may be in any order within the larger array. For example, the offset of the quaternion rotation data may be less than the offset of the translation data. 
 *	The \p pTQ array may also contain other arbitrary data values interspersed between the arrays containing the T and Q values, if that is convenient.
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose translation and rotation values you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation and rotation values you want to set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pTQ					Pointer to an array of floating-point numbers containing the data for the Effector in global space. This array must be aligned on 16 bytes.
 *	\param		pTOffset			Offset of the translation values within \p pTQ. This offset must be aligned on 16 bytes.
 *	\param		pQOffset			Offset of the rotation values within \p pTQ. This offset must be aligned on 16 bytes.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorStateTQAlignfv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const float* pTQ, size_t pTOffset, size_t pQOffset);

/**	\brief Retrieve the transform matrix of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState. 
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose matrix you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose matrix you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pXForm				Stores the transform matrix of the Effector in global space (4x4 column major matrix).
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStatefv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pXForm[16]);
/**	\copydoc HIKGetEffectorStatefv() 
 *	\ingroup EffectorSetupRead
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStatedv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, double pXForm[16]);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) in global space of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState. Values are expressed using separate arrays.
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose translation, rotation and scaling you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation, rotation and scaling you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pT					Stores the translation value, in global space.
 *	\param[out]	pQ					Stores the rotation value, in global space.
 *	\param[out]	pS					Stores the scaling value, in global space.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStateTQSfv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pT[4], float pQ[4], float pS[4]);
/**	\brief Retrieve the translation (T) and quaternion rotation (Q) in global space of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState. Values are expressed using separate arrays.
 *	
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose translation and rotation values you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation and rotation values you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pT					Stores the translation value, in global space.
 *	\param[out]	pQ					Stores the rotation value, in global space.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStateTQfv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pT[4], float pQ[4]);
/**	\copydoc HIKGetEffectorStateTQSfv()
 *	\ingroup EffectorSetupRead
 *	This function converts the double-precision numbers internally to floating-point numbers. For best performance, use the HIKGetEffectorStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStateTQSdv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, double pT[4], double pQ[4], double pS[4]);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) in global space of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState. Values are stored at specified offsets within a single array.
 *
 *	\ingroup EffectorSetupRead
 *	The T, Q and S values are each stored as an array of four floating-point numbers within the \p pTQS array, and the offset of each of these arrays must be aligned on 16 bytes. 
 *	The arrays containing the T, Q and S values may be stored in any order within the larger array. For example, the offset of the scaling data may be less than the offset of the translation data. 
 *	The \p pTQS array may also contain other arbitrary data values interspersed between the arrays containing the T, Q and S values, if that is convenient.
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose translation, rotation and scaling you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation, rotation and scaling you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pTQS				Stores the translation, rotation and scaling values of the Effector, in global space.
 *	\param		pTOffset			Offset for the translation values within \p pTQS. This offset must be aligned on 16 bytes.
 *	\param		pQOffset			Offset for the rotation values within \p pTQS. This offset must be aligned on 16 bytes.
 *	\param		pSOffset			Offset for the scaling values within \p pTQS. This offset must be aligned on 16 bytes.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStateTQSAlignfv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float* pTQS, size_t pTOffset, size_t pQOffset, size_t pSOffset);

/**	\brief Retrieve the translation (T) and quaternion rotation (Q) in global space of Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState. Values are stored at specified offsets within a single array.
 *
 *	\ingroup EffectorSetupRead
 *	The T and Q values are each stored as an array of four floating-point numbers within the \p pTQ array, and the offset of each of these arrays must be aligned on 16 bytes. 
 *	The arrays containing the T and Q values may be in any order within the larger array. For example, the offset of the quaternion rotation data may be less than the offset of the translation data. 
 *	The \p pTQ array may also contain other arbitrary data values interspersed between the arrays containing the T and Q values, if that is convenient.
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose translation and rotation you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation and rotation you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pTQ					Stores the translation, rotation and scaling values of the Effector, in global space.
 *	\param		pTOffset			Offset for the translation values within \p pTQ. This offset must be aligned on 16 bytes.
 *	\param		pQOffset			Offset for the rotation values within \p pTQ. This offset must be aligned on 16 bytes.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStateTQAlignfv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float* pTQ, size_t pTOffset, size_t pQOffset);

/**	\brief Set the Reach Translation constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose value you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Reach Translation you want to set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pValue				Value must be between 0.0 (pin the joint to the translation of the FK pose) and 1.0 (pin the joint to the translation of the Effector).
 */
HIK_EXPORT void	 HIK_API HIKSetTranslationActive(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pValue);

/**	\brief Retrieve the Reach Translation constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose value you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Reach Translation you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\return		Value is between 0.0 (the joint is pinned to the translation of the FK pose) and 1.0 (the joint is pinned to the translation of the Effector)
 */
HIK_EXPORT float	 HIK_API HIKGetTranslationActive(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex);

/**	\brief Set the Reach Rotation constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose value you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Reach Rotation you want to set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pValue				Value must be between 0.0 (pin the joint to the rotation of the FK pose) and 1.0 (pin the joint to the rotation of the Effector).
 */
HIK_EXPORT void	 HIK_API HIKSetRotationActive(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pValue);

/**	\brief Retrieve the Reach Rotation constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose value you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Reach Rotation you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\return		Value is between 0.0 (the joint is pinned to the rotation of the FK pose) and 1.0 (the joint is pinned to the rotation of the Effector)
 */
HIK_EXPORT float	 HIK_API HIKGetRotationActive(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex);

/**	\brief Set the Pull constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose value you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Pull you want to set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pValue				Value must be between 0.0 (the joint will not pull other joints in order to reach its target) and 1.0 (the joint will have maximum priority for reaching its target).
 */
HIK_EXPORT void	 HIK_API HIKSetPull(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pValue);

/**	\brief Retrieve the Pull constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose value you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Pull you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\return		alue is between 0.0 (the joint does not pull other joints in order to reach its target) and 1.0 (the joint has maximum priority for reaching its target).
 */
HIK_EXPORT float	 HIK_API HIKGetPull(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex);

/**	\brief Set the Resist constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose value you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Resist you want to set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pValue				Value must be between 0.0 (the joint moves freely) and 1.0 (the joint is constrained to its original rotation).
 */
HIK_EXPORT void	 HIK_API HIKSetResist(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pValue);

/**	\brief Retrieve the Resist constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState containing the Effector whose value you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Resist you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\return		Value is between 0.0 (the joint moves freely) and 1.0 (the joint is constrained to its original rotation).
 */
HIK_EXPORT float	 HIK_API HIKGetResist(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex);


/**	\brief Set the amount of pull the left or right hand can exert on the hips.
*
*	By default, both hands can pull the hips (unless the hips have Pull and Reach Translation values assigned to them). You can use this function to change this default priority, 
*	and make the hands unable to pull the hips under any circumstances.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKEffectorSetState containing the left or right hand Effector whose Pull you want to set.
 *	\param		pLeft				Indicates whether to set the pull for the left hand or right hand. 0 = right, 1 = left.
 *	\param		pValue				Value must be between 0.0 (the hand cannot pull the hips) and 1.0 (the hand has full priority over the hips).
 */
HIK_EXPORT void	 HIK_API HIKSetHandPullHips(HIKEffectorSetState *pEffectorSetState, int pLeft, float pValue);

/**	\brief Retrieve the amount of pull the left or right hand can exert on the hips.
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState containing the left or right hand Effector whose Pull you want to retrieve.
 *	\param		pLeft				Indicates whether to retrieve the pull for the left hand or right hand. 0 = right, 1 = left.
 *	\return		Value is between 0.0 (the hand cannot pull the hips) and 1.0 (the hand has full priority over the hips).
 */
HIK_EXPORT float	 HIK_API HIKGetHandPullHips(const HIKEffectorSetState *pEffectorSetState, int pLeft);

/**	\defgroup FloorContact Floor Contact
 *	\ingroup CharacterSetup
 *	\brief This section describes the functions used to set up floor contact for your characters. 
 *
 *	Note that setting up floor contact also requires you to set up appropriate character properties in your HIKPropertySetState.
 *	For an overview of the HumanIK floor contact engine, and for complete instructions on the process of setting up floor contact, see ~{ Foot and Hand Contact }~.
 */

/**	\brief Set the transform matrix of the oriented plane that the floor contact engine applies to one of your character's feet or hands.
 *	\ingroup FloorContact
 *	\param		pEffectorSetState	HIKEffectorSetState that will hold the floor orientation.
 *	\param		pFloor				Determines the joint to which the floor orientation will apply. See the ::HIKFloorContact enumeration for possible values.
 *	\param		pXForm				Transform matrix of the floor or oriented plane, in global space (4x4 column major matrix).
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorFloorStatefv(HIKEffectorSetState *pEffectorSetState, int pFloor, const float pXForm[16]);
/**	@copydoc HIKSetEffectorFloorStatefv()
 *	\ingroup FloorContact
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorFloorStatedv(HIKEffectorSetState *pEffectorSetState, int pFloor, const double pXForm[16]);

/**	\brief Set the translation and rotation in global space of the oriented plane that the floor contact engine applies to one of your character's feet or hands.
 *	\ingroup FloorContact
 *	\param		pEffectorSetState	HIKEffectorSetState that will hold the floor orientation.
 *	\param		pFloor				Determines the joint to which the floor orientation will apply. See the ::HIKFloorContact enumeration for possible values.
 *	\param		pT					Translation value to set, in global space.
 *	\param		pQ					Rotation value to set, in global space.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorFloorStateTQfv(HIKEffectorSetState *pEffectorSetState, int pFloor, const float pT[4], const float pQ[4]);
/**	@copydoc HIKSetEffectorFloorStateTQfv()
 *	\ingroup FloorContact
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorFloorStateTQdv(HIKEffectorSetState *pEffectorSetState, int pFloor, const double pT[4], const double pQ[4]);

/**	\brief Retrieve the transform matrix of the oriented plane that the floor contact engine applies to one of your character's feet or hands.
 *	\ingroup FloorContact
 *	\param		pEffectorSetState	HIKEffectorSetState that holds the floor orientation.
 *	\param		pFloor				Specifies the joint for which the floor orientation will be retrieved. See the ::HIKFloorContact enumeration for possible values.
 *	\param[out]	pXForm				Stores the transform matrix of the floor or oriented plane, in global space (4x4 column major matrix).
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorFloorStatefv(const HIKEffectorSetState *pEffectorSetState, int pFloor, float pXForm[16]);
/**	@copydoc HIKGetEffectorFloorStatefv()
 *	\ingroup FloorContact
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorFloorStatedv(const HIKEffectorSetState *pEffectorSetState, int pFloor, double pXForm[16]);

/**	\brief Retrieve the translation and rotation in global space of the oriented plane that the floor contact engine applies to one of your character's feet or hands.
 *	\ingroup FloorContact
 *	\param		pEffectorSetState	HIKEffectorSetState that holds the floor orientation.
 *	\param		pFloor				Specifies the joint for which the floor orientation will be retrieved. See the ::HIKFloorContact enumeration for possible values.
 *	\param		pT					Translation value to retrieve, in global space.
 *	\param		pQ					Rotation value to retrieve, in global space.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorFloorStateTQfv(const HIKEffectorSetState *pEffectorSetState, int pFloor, float pT[4], float pQ[4]);
/**	@copydoc HIKGetEffectorFloorStateTQfv()
 *	\ingroup FloorContact
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorFloorStateTQdv(const HIKEffectorSetState *pEffectorSetState, int pFloor, double pT[4],double pQ[4]);

/**	\brief Retrieve the IK solving steps currently set for HIKEffectorSetState \p pEffectorSetState.
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKEffectorSetState that you want to query.
 *	\return		Bit mask indicating the active steps. See the ::HIKSolvingStep enumeration for descriptions of the bit values.
 */
HIK_EXPORT int	     HIK_API HIKGetIKSolvingStep(const HIKEffectorSetState *pEffectorSetState);

/**	\brief Set the IK solving steps for HIKEffectorSetState \p pEffectorSetState.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKEffectorSetState that you want to query.
 *	\param		pSolvingStep		Bit mask indicating the active steps. See the ::HIKSolvingStep enumeration for descriptions of the bit values.
 */
HIK_EXPORT void     HIK_API HIKSetIKSolvingStep(HIKEffectorSetState *pEffectorSetState,int pSolvingStep);

// ***********************************************
/**	\defgroup CharacterStateSetup Read/Write HIKCharacterState Data
 *	\brief This section describes the functions used to read and write data in \HIKCharacterStates.
 *
 *	For an overview, see ~{ Setting and Retrieving Data in HIKCharacterStates }~
 */

/**	\defgroup CharacterStateSetupRead Read HIKCharacterState Data
 *	\ingroup CharacterStateSetup
 *	\brief This section describes the functions used to read data from an HIKCharacterState.
 *
 *	All of these functions return translation.w = 0.f and scale.w = 1.f.
 */

/**	\defgroup CharacterStateSetupWrite Write HIKCharacterState Data
 *	\ingroup CharacterStateSetup
 *	\brief This section describes the functions used to write data to an HIKCharacterState.
 *
 *	All of these functions mask translation.w to 0.f and scale.w to 1.f.
 */

/*!	\ingroup CharacterStateSetup
 *	\brief Lists special values that you can use within the list of Node IDs in a data description. See HIKDataDescription.
 */
enum HIKToken
{
    HIKNotUsed =  -1,	/*!<  Indicates that the data block represented by this index should not be read by HumanIK. The engine will ignore it.  */
    HIKLastNode = -2	/*!<  Indicates the end of the list of Nodes. Always finish your list with this token.                                   */
};

/*!	see enum ::HIKToken */
typedef enum HIKToken eHIKToken;


/**\struct HIKDataDescription
 *		\brief A description of a data set that contains separate translation, quaternion rotation, and scaling values for multiple different Nodes in an HIKCharacterState. 
 *
 *	A data set is a memory buffer containing many data blocks, where each block contains the animation data for one of your character's Nodes.
 *	This structure contains metadata about the data set, indicating its transform space, its stride (the total size of each data block),
 *	a set of HumanIK NodeIDs that indicates how your data blocks map onto HumanIK Nodes, and the offset of the translation, rotation and scaling
 *	data within each data block. 
 *	\remarks Because HumanIK uses SIMD instructions to load data, your translation, quaternion and scaling values must be aligned on 16 bytes.
 *	\ingroup CharacterStateSetup
*/
typedef struct sHIKDataDescription
{  
	/*!	Indicates whether your Node data is expressed in local or global space.  */
    enum
    { 
        HIKGlobalSpace = 0,		/*!<	Data is expressed in global space.	*/
        HIKLocalSpace  = 1		/*!<	Data is expressed in local space.	*/
    }mTransformSpace;

	size_t mTOffset;			/*!<	Specifies the offset of the translation data within each data block. Must be a 4x1 vector, aligned on 16 bytes.			*/
	size_t mQOffset;			/*!<	Specifies the offset of the quaternion rotation data within each data block. Must be a 4x1 vector, aligned on 16 bytes.	*/
	size_t mSOffset;			/*!<	Specifies the offset of the scaling data within each data block. Must be a 4x1 vector, aligned on 16 bytes.				*/
	
	size_t mStride;				/*!<	Specifies the total size of each data block.																			*/
    int *mHIKNodeId;			/*!<	A list of HumanIK Node IDs indicating which Node each of your data blocks applies to.
										The last value in this list must be the special token ::HIKLastNode. See the ::HIKToken enumeration.					*/
} HIKDataDescription;

/**	\example datadescriptiontqs.h
 *	This code example shows how to set and retrieve character animations using a data set that follows the HIKDataDescription structure, in conjunction with the HIKSetCharacterStateTransformTQS() / HIKGetCharacterStateTransformTQS() functions.
 */

/**	\example datadescriptionscattersqt.h
 *	This code example shows how to set and retrieve character animations using a data set that follows the HIKDataDescription structure, in conjunction with the HIKSetCharacterStateTransformTQS() / HIKGetCharacterStateTransformTQS() functions.
 *	In this example, the TQS values are ordered differently within the data block (S first at offset 0, Q at offset 32, and T at offset 80). In addition, these values
 *	are interleaved with arbitrary data not used by HumanIK.
 */
 
/**	\struct HIKDataDescriptionMatrix
 *	\brief A description of a data set that contains transform matrices for multiple different Nodes in an HIKCharacterState. 
 *
 *	A data set is a memory buffer containing many data blocks, where each block contains the animation data for one of your character's Nodes.
 *	This structure contains metadata about the data set, indicating its transform space, its stride (the total size of each data block),
 *	a set of HumanIK NodeIDs that indicates how your data blocks map onto HumanIK Nodes, and the offset of the transform matrix
 *	data within each data block.
 *	\remarks Because HumanIK uses SIMD instructions to load data, your translation, quaternion and scaling values must be aligned on 16 bytes.
 *	\ingroup CharacterStateSetup
 */
typedef struct sHIKDataDescriptionMatrix
{  
	/*!	Indicates whether your Node data is expressed in local or global space.  */
    enum
    { 
        HIKGlobalSpace = 0,		/*!<	Data is expressed in global space.	*/
        HIKLocalSpace  = 1		/*!<	Data is expressed in local space.	*/
    }mTransformSpace;           

	size_t mMatrixOffset;       /*!<	Specifies the offset of the transform matrix within each data block. Must be a 4x4 column major matrix, aligned on 16 bytes.	*/
		
    size_t mStride;             /*!<	Specifies the total size of each data block.																					*/
    int *mHIKNodeId;            /*!<	A list of HumanIK Node IDs indicating which Node each of your data blocks applies to.
										The last value in this list must be the special token ::HIKLastNode. See the ::HIKToken enumeration.							*/
} HIKDataDescriptionMatrix;

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) of multiple Nodes from data set \p pDataSet, interpreted according to data description \p pDataDescription. 
 *
 *	\ingroup CharacterStateSetupWrite  
 *	This function is faster than setting the data for each Node individually using functions such as HIKSetNodeStateTQS().
 *	\param		pCharacter			HIKCharacter for which you want to set the data values.
 *	\param		pCharacterState		HIKCharacterState in which you want to set the data values.
 *	\param		pDataDescription	Data description defining the memory layout of your data set.
 *	\param		pDataSet			Void pointer to the beginning of your first data block.
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterStateTransformTQS(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, const void* pDataSet);
/**	\brief Set the translation (T) and quaternion rotation (Q) of multiple Nodes from data set \p pDataSet, interpreted according to data description \p pDataDescription. 
 *
 *	\ingroup CharacterStateSetupWrite  
 *	This function sets the scaling values for all axes to \p 1.0f.
 *
 *	\copydetails HIKSetCharacterStateTransformTQS()
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterStateTransformTQ(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, const void* pDataSet);

/**	\brief Set the transform matrix of multiple Nodes from data set \p pDataSet, interpreted according to data description \p pDataDescription. 
 *	\ingroup CharacterStateSetupWrite  
 *	\copydetails HIKSetCharacterStateTransformTQS()
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterStateTransform(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescriptionMatrix* pDataDescription, const void* pDataSet);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) of multiple Nodes from data set \p pDataSet, interpreted according to data description \p pDataDescription. 
 *
 *	\ingroup CharacterStateSetupWrite  
 *	When using this SoA function, each data block is expected to interleave the data for four Nodes instead of containing data for only one Node.
 *	If you choose to use this format, the offsets in your data description must give the location of the first translation, orientation and scaling vectors within each data block. 
 *	HumanIK reads the values for all four Nodes in order starting from those offsets.
 *
 *	\copydetails HIKSetCharacterStateTransformTQS() 
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterStateTransformTQS_SoA(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, const void* pDataSet);

/**	\brief Set the transform matrix of Node \p pNodeId in HIKCharacterState \p pCharacterState.
 *	\ingroup CharacterStateSetupWrite
 *	\param		pCharacter			HIKCharacter for which you want to set the matrix.
 *	\param		pCharacterState		HIKCharacterState in which you want to set the matrix.
 *	\param		pNodeId				Unique ID of the Node whose matrix you want to set. See the ::HIKNodeId enumeration for possible values.
 *	\param		pXForm				Transform matrix to set, in global space (4x4 column major matrix).
 */
HIK_EXPORT void	 HIK_API HIKSetNodeStatefv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float pXForm[16]);
/**	\copydoc HIKSetNodeStatefv()
 *	\ingroup CharacterStateSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are
 *	unavailable. For best performance, use the HIKSetNodeStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeStatedv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const double pXForm[16]);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are expressed using separate arrays.
 *	\ingroup CharacterStateSetupWrite
 *	\param		pCharacter			HIKCharacter for which you want to set the translation, rotation and scaling values.
 *	\param		pCharacterState		HIKCharacterState in which you want to set the translation, rotation and scaling values.
 *	\param		pNodeId				Unique ID of the Node whose data you want to set. See the ::HIKNodeId enumeration for possible values.
 *	\param		pT					Translation value to set, in global space.
 *	\param		pQ					Rotation value to set, in global space.
 *	\param		pS					Scaling value to set, in global space.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeStateTQSfv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float pT[4], const float pQ[4], const float pS[4]);
/**	\brief Set the translation (T), quaternion rotation (Q) and non-uniform scaling (S) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are expressed using separate arrays.
 *
 *	\ingroup CharacterStateSetupWrite
 *	This function allows you to specify different scaling values for the X, Y and Z axes. 
 *	\copydetails HIKSetNodeStateTQSfv()
 */
HIK_EXPORT void	 HIK_API HIKSetNodeStateTQNonUniformSfv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float pT[4], const float pQ[4], const float pS[4]);
/**	\copydoc HIKSetNodeStateTQSfv()
 *
 *	\ingroup CharacterStateSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are
 *	unavailable. For best performance, use the HIKSetNodeStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeStateTQSdv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const double pT[4], const double pQ[4], const double pS[4]);

/**	\brief Set the translation (T) and quaternion rotation (Q) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are expressed using separate arrays.
 *
 *	\ingroup CharacterStateSetupWrite
 *	This function sets the scaling values for all axes to \p 1.0f.
 *	\param		pCharacter			HIKCharacter for which you want to set the data values.
 *	\param		pCharacterState		HIKCharacterState in which you want to set the data values.
 *	\param		pNodeId				Unique ID of the Node whose data you want to set. See the ::HIKNodeId enumeration for possible values.
 *	\param		pT					Translation value to set, in global space.
 *	\param		pQ					Rotation value to set, in global space.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeStateTQfv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float pT[4], const float pQ[4]);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are read from specified offsets within a single array.
 *
 *	\ingroup CharacterStateSetupWrite
 *	The T, Q and S values are each expected to be expressed as an array of four floating-point numbers within the \p pTQS array, and the offset of each of these arrays must be aligned on 16 bytes. 
 *	The arrays containing the T, Q and S values may be in any order within the larger array. For example, the offset of the scaling data may be less than the offset of the translation data. 
 *	The \p pTQS array may also contain other arbitrary data values interspersed between the arrays containing the T, Q and S values, if that is convenient.
 *	\param		pCharacter			HIKCharacter for which you want to set the translation, rotation, and scaling values.
 *	\param		pCharacterState		HIKCharacterState in which you want to set the translation, rotation, and scaling values.
 *	\param		pNodeId				Unique ID of the Node whose TQS values you want to set. See the ::HIKNodeId enumeration for possible values.
 *	\param		pTQS				Pointer to an array of floating-point numbers containing the desired translation, rotation and scaling values for the Node. This array must be aligned on 16 bytes.
 *	\param		pTOffset			Offset of the translation values within the \p pTQS array. This offset must be aligned on 16 bytes.
 *	\param		pQOffset			Offset of the rotation values within the \p pTQS array. This offset must be aligned on 16 bytes.
 *	\param		pSOffset			Offset of the scaling values within the \p pTQS array. This offset must be aligned on 16 bytes.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeStateTQSAlignfv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float* pTQS, size_t pTOffset, size_t pQOffset, size_t pSOffset);

/**	\brief Set the translation (T) and quaternion rotation (Q) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are read from specified offsets within a single array.
 *
 *	\ingroup CharacterStateSetupWrite
 *	This function sets the scaling values for all axes to \p 1.0f.
 *
 *	The T and Q values are each expected to be expressed as an array of four floating-point numbers within the \p pTQ array, and the offset of each of these arrays must be aligned on 16 bytes. 
 *	The arrays containing the T and Q values may be in any order within the larger array. For example, the offset of the quaternion rotation data may be less than the offset of the translation data. 
 *	The \p pTQ array may also contain other arbitrary data values interspersed between the arrays containing the T and Q values, if that is convenient.
 *	\param		pCharacter			HIKCharacter for which you want to set the translation and rotation values.
 *	\param		pCharacterState		HIKCharacterState in which you want to set the translation and rotation values.
 *	\param		pNodeId				Unique ID of the Node whose TQ values you want to set. See the ::HIKNodeId enumeration for possible values.
 *	\param		pTQ					Pointer to an array of floating-point numbers containing the desired translation and rotation values for the Node. This array must be aligned on 16 bytes.
 *	\param		pTOffset			Offset of the translation values within the \p pTQ array. This offset must be aligned on 16 bytes.
 *	\param		pQOffset			Offset of the rotation values within the \p pTQ array. This offset must be aligned on 16 bytes.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeStateTQAlignfv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float* pTQ, size_t pTOffset, size_t pQOffset);


/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) of multiple Nodes from HIKCharacterState \p pCharacterState, writing them to memory in data set \p pDataSet according to data description \p pDataDescription. 
 *
 *	\ingroup CharacterStateSetupRead
 *	This function is faster than retrieving the data for each Node individually using functions such as HIKGetNodeStateTQS().
 *	\param		pCharacter			HIKCharacter from which you want to retrieve the data values.
 *	\param		pCharacterState		HIKCharacterState from which you want to retrieve the data values.
 *	\param		pDataDescription	Data description defining the memory layout of your data set.
 *	\param[out]	pDataSet			Void pointer to the beginning of your first data block.
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterStateTransformTQS(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, void* pDataSet);
/**	\brief Retrieve the translation (T) and quaternion rotation (Q) of multiple Nodes from HIKCharacterState \p pCharacterState, writing them to memory in data set \p pDataSet according to data description \p pDataDescription. 
 *	\ingroup CharacterStateSetupRead
 *	\copydetails HIKGetCharacterStateTransformTQS()
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterStateTransformTQ(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, void* pDataSet);
/**	\brief Retrieve the quaternion rotation (Q) of multiple Nodes from HIKCharacterState \p pCharacterState, writing them to memory in data set \p pDataSet according to data description \p pDataDescription. 
 *	\ingroup CharacterStateSetupRead
 *	\copydetails HIKGetCharacterStateTransformTQS()
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterStateTransformQ(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, void* pDataSet);

/**	\brief Retrieve the transform matrices of multiple Nodes from HIKCharacterState \p pCharacterState, writing them to memory in data set \p pDataSet according to data description \p pDataDescription. 
 *	\ingroup CharacterStateSetupRead
 *	\copydetails HIKGetCharacterStateTransformTQS()
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterStateTransform(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescriptionMatrix* pDataDescription, void* pDataSet);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) of multiple Nodes from HIKCharacterState \p pCharacterState, writing them to memory in data set \p pDataSet according to data description \p pDataDescription. 
 *
 *	\ingroup CharacterStateSetupRead
 *	When using this SoA function, each data block will interleave the data for four Nodes instead of containing data for only one Node.
 *	If you choose to use this format, the offsets in your data description must give the location of the first translation, orientation and scaling vectors within each data block. 
 *	HumanIK will store the values for all four Nodes in order starting from those offsets.
 *
 *	\copydetails HIKGetCharacterStateTransformTQS()
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterStateTransformTQS_SoA(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, void* pDataSet);

/**	\brief Retrieve the transform matrix of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are expressed using separate arrays.
 *	\ingroup CharacterStateSetupRead
 *	\param		pCharacter			HIKCharacter from which you want to retrieve the matrix.
 *	\param		pCharacterState		HIKCharacterState from which you want to retrieve the matrix.
 *	\param		pNodeId				Unique ID of the Node whose TQS values you want to set. See the ::HIKNodeId enumeration for possible values.
 *	\param[out]	pXForm				Stores the retrieved transform matrix, in global space.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeStatefv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, float pXForm[16]);
/**	\copydoc HIKGetNodeStatefv()
 *	\ingroup CharacterStateSetupRead
 *	This function converts floating-point numbers internally to double-precision. It is intended for use only where floating-point values are
 *	unavailable. For best performance, use the HIKGetNodeStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeStatedv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, double pXForm[16]);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are expressed using separate arrays.
 *	\ingroup CharacterStateSetupRead
 *	\param		pCharacter			HIKCharacter from which you want to retrieve the translation, rotation, and scaling values.
 *	\param		pCharacterState		HIKCharacterState from which you want to retrieve the translation, rotation, and scaling values.
 *	\param		pNodeId				Unique ID of the Node whose data you want to retrieve. See the ::HIKNodeId enumeration for possible values.
 *	\param[out]	pT					Translation value retrieved, in global space.
 *	\param[out]	pQ					Rotation value retrieved, in global space.
 *	\param[out]	pS					Scaling value retrieved, in global space.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeStateTQSfv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, float pT[4], float pQ[4], float pS[4]);
/**	\brief Retrieve the translation (T), quaternion rotation (Q) and non-uniform scaling (S) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are expressed using separate arrays.
 *
 *	\ingroup CharacterStateSetupRead
 *	This function allows you to specify different scaling values for the X, Y and Z axes. 
 *	\copydetails HIKGetNodeStateTQSfv()
 */
HIK_EXPORT void	 HIK_API HIKGetNodeStateTQNonUniformSfv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, float pT[4], float pQ[4], float pS[4]);
/**	\copydoc HIKGetNodeStateTQSfv()
 *	\ingroup CharacterStateSetupRead
 *	This function converts floating-point numbers internally to double-precision. It is intended for use only where floating-point values are
 *	unavailable. For best performance, use the HIKGetNodeStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeStateTQSdv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, double pT[4], double pQ[4], double pS[4]);

/**	\brief Retrieve the translation (T) and quaternion rotation (Q) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are expressed using separate arrays.
 *	\ingroup CharacterStateSetupRead
 *	\param		pCharacter			HIKCharacter from which you want to retrieve the translation and rotation values.
 *	\param		pCharacterState		HIKCharacterState from which you want to retrieve the translation and rotation values.
 *	\param		pNodeId				Unique ID of the Node whose TQS values you want to retrieve. See the ::HIKNodeId enumeration for possible values.
 *	\param		pT					Translation value retrieved, in global space.
 *	\param		pQ					Rotation value retrieved, in global space.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeStateTQfv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, float pT[4], float pQ[4]);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are stored at specified offsets within a single array.
 *
 *	\ingroup CharacterStateSetupRead
 *	The T, Q and S values are each stored as an array of four floating-point numbers within the \p pTQS array, and the offset of each of these arrays must be aligned on 16 bytes. 
 *	The arrays containing the T, Q and S values may be in any order within the larger array. For example, the offset of the scaling data may be less than the offset of the translation data. 
 *	The \p pTQS array may also contain other arbitrary data values interspersed between the arrays containing the T, Q and S values, if that is convenient.
 *	\param		pCharacter			HIKCharacter from which you want to retrieve the translation, rotation, and scaling values.
 *	\param		pCharacterState		HIKCharacterState from which you want to retrieve the translation, rotation, and scaling values.
 *	\param		pNodeId				Unique ID of the Node whose data you want to retrieve. See the ::HIKNodeId enumeration for possible values.
 *	\param		pTQS				Pointer to an array of floating-point numbers that will be used to store the translation, rotation and scaling values of the Node. This array must be aligned on 16 bytes.
 *	\param		pTOffset			Offset of the translation values within the \p pTQS array. This offset must be aligned on 16 bytes.
 *	\param		pQOffset			Offset of the rotation values within the \p pTQS array. This offset must be aligned on 16 bytes.
 *	\param		pSOffset			Offset of the scaling values within the \p pTQS array. This offset must be aligned on 16 bytes.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeStateTQSAlignfv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, float* pTQS, size_t pTOffset, size_t pQOffset, size_t pSOffset);

/**	\brief Retrieve the translation (T) and quaternion rotation (Q) in global space of Node \p pNodeId in HIKCharacterState \p pCharacterState. Values are stored at specified offsets within a single array.
 *
 *	\ingroup CharacterStateSetupRead
 *	The T and Q values are each expected to be expressed as an array of four floating-point numbers within the \p pTQ array, and the offset of each of these arrays must be aligned on 16 bytes. 
 *	The arrays containing the T and Q values may be in any order within the larger array. For example, the offset of the scaling data may be less than the offset of the translation data. 
 *	The \p pTQ array may also contain other arbitrary data values interspersed between the arrays containing the T and Q , if that is convenient.
 *	\param		pCharacter			HIKCharacter from which you want to retrieve the translation and rotation values.
 *	\param		pCharacterState		HIKCharacterState from which you want to retrieve the translation and rotation values.
 *	\param		pNodeId				Unique ID of the Node whose data you want to retrieve. See the ::HIKNodeId enumeration for possible values.
 *	\param		pTQ					Pointer to an array of floating-point numbers that will be used to store the translation and rotation values of the Node. This array must be aligned on 16 bytes.
 *	\param		pTOffset			Offset of the translation values within the \p pTQ array. This offset must be aligned on 16 bytes.
 *	\param		pQOffset			Offset of the rotation values within the \p pTQ array. This offset must be aligned on 16 bytes.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeStateTQAlignfv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, float* pTQ, size_t pTOffset, size_t pQOffset);


/**	\struct HIKEffectorDataDescription
 *	\brief A description of a data set that contains separate translation, quaternion rotation, and scaling values for multiple Effectors in an HIKEffectorSetState. 
 *
 *	A data set is a memory buffer containing many data blocks, where each block contains the animation data for one of your character's Effectors.
 *	This structure contains metadata about the data set, its stride (the total size of each data block),
 *	a set of HumanIK Effector IDs that indicates how your data blocks map onto HumanIK Effectors, the offsets of the translation, rotation and scaling
 *	data within each data block, and the offset of the IK constraint data within each data block. 

 *	\remarks Because HumanIK uses SIMD instructions to load data, your translation, quaternion, scaling and IK constraint values must be aligned on 16 bytes.
 *	\ingroup EffectorSetup
 */
typedef struct sHIKEffectorDataDescription
{  
    size_t mTOffset;			/*!<	Specifies the offset of the translation data within each data block. Must be a 4x1 vector, aligned on 16 bytes.			*/
    size_t mQOffset;			/*!<	Specifies the offset of the quaternion rotation data within each data block. Must be a 4x1 vector, aligned on 16 bytes.	*/
    size_t mSOffset;			/*!<	Specifies the offset of the scaling data within each data block. Must be a 4x1 vector, aligned on 16 bytes.				*/
	size_t mParameterOffset;    /*!<	Specifies the offset of the IK constraint data within each data block. Must be a 4x1 vector, aligned on 16 bytes. 
										The format of this data must be {ReachT, ReachR, Pull, Resist}, and each value must be between 0.0 and 1.0.				*/
    size_t mStride;				/*!<	Specifies the total size of each data block.																			*/
    int *mHIKEffectorId;		/*!<	A list of HumanIK Effector IDs indicating which Effector each of your data blocks applies to.
										The last value in this list must be the special token ::HIKLastNode. See the ::HIKToken enumeration.					*/
} HIKEffectorDataDescription;

/**	\struct HIKEffectorDataDescriptionMatrix
 *	\brief A description of a data set that contains transform matrices for multiple different Effectors in an HIKEffectorSetState. 
 *
 *	A data set is a memory buffer containing many data blocks, where each block contains the animation data for one of your character's Effectors.
 *	This structure contains metadata about the data set, its stride (the total size of each data block),
 *	a set of HumanIK Effector IDs that indicates how your data blocks map onto HumanIK Effectors, the offsets of the transform matrix
 *	data within each data block, and the offset of the IK constraint data within each data block. 

 *	\remarks    Because HumanIK uses SIMD instructions to load data, your transform matrix and IK constraint values must be aligned on 16 bytes.
 *	\ingroup EffectorSetup
*/
typedef struct sHIKEffectorDataDescriptionMatrix
{  
    size_t mMatrixOffset;		/*!<	Specifies the offset of the transform matrix within each data block. Must be a 4x4 column major matrix, aligned on 16 bytes.	*/
	size_t mParameterOffset;	/*!<	pecifies the offset of the IK constraint data within each data block. Must be a 4x1 vector, aligned on 16 bytes. 
										The format of this data must be {ReachT, ReachR, Pull, Resist}, and each value must be between 0.0 and 1.0.						*/
    size_t mStride;				/*!<	Specifies the total size of each data block.																					*/
    int *mHIKEffectorId;		/*!<	A list of HumanIK Effector IDs indicating which Effector each of your data blocks applies to.
										The last value in this list must be the special token ::HIKLastNode. See the ::HIKToken enumeration.							*/
} HIKEffectorDataDescriptionMatrix;

/**	\brief Set the translation (T), quaternion rotation (Q), scaling (S), and IK constraints of multiple Effectors from data set \p pDataSet, interpreted according to data description \p pDataDescription. 
 *
 *	\ingroup EffectorSetupWrite  
 *	This function is faster than setting the matrix of each Effector individually using functions such as HIKSetEffectorState().
 *	\param		pEffectorSetState	HIKEffectorSetState in which to set the data.
 *	\param		pDataDescription	Data description defining the memory layout of your data set.
 *	\param		pDataSet			Void pointer to the beginning of your first data block.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorStateDataTQS(HIKEffectorSetState *pEffectorSetState, const HIKEffectorDataDescription* pDataDescription, const void* pDataSet);

/**	\brief Set the transform matrix and IK constraints of multiple Effectors from data set \p pDataSet, interpreted according to data description \p pDataDescription. 
 *	\ingroup EffectorSetupWrite  
 *	\copydetails HIKSetEffectorStateDataTQS()
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorStateData(HIKEffectorSetState *pEffectorSetState, const HIKEffectorDataDescriptionMatrix* pDataDescription, const void* pDataSet);

/**	\brief Retrieve the translation (T), quaternion rotation (Q), scaling (S), and IK constraints of multiple Effectors from HIKEffectorSetState \p pEffectorSetState, writing them to memory in data set \p pDataSet according to data description \p pDataDescription. 
 *
 *	\ingroup EffectorSetupRead  
 *	This function is faster than retrieving the matrix of each Effector individually using functions such as HIKGetEffectorState().
 *	\param		pEffectorSetState	HIKEffectorSetState from which to retrieve the data.
 *	\param		pDataDescription	Data description defining the memory layout of your data set.
 *	\param		pDataSet			Void pointer to the beginning of your first data block.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStateDataTQS(const HIKEffectorSetState *pEffectorSetState, const HIKEffectorDataDescription* pDataDescription, void* pDataSet);

/**	\brief Retrieve the transform matrix and IK constraints of multiple Effectors from HIKEffectorSetState \p pEffectorSetState, writing them to memory in data set \p pDataSet according to data description \p pDataDescription. 
 *	\ingroup EffectorSetupRead  
 *	\copydetails HIKGetEffectorStateDataTQS()
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorStateData(const HIKEffectorSetState *pEffectorSetState, const HIKEffectorDataDescriptionMatrix* pDataDescription, void* pDataSet);

// ***********************************************
/**	\defgroup Utility Utilities
 *	\brief Utility functions for use with HumanIK. 
 */

/**	\brief Retrieve the Node ID from a descriptive name. This is a utility function that maps between FBX and HIK.
 *	\ingroup Utility
 *	\param		pName				Descriptive name for a Node. Must match a value returned by HIKNodeNameFromNodeId().
 *	\return		The Node ID associated with the specified name. See the ::HIKNodeId enumeration for possible values.
 */
HIK_EXPORT int          HIK_API HIKNodeIdFromNodeName(const char* pName);

/**	\brief Retrieve a descriptive name for Node \p pNodeId. This is a utility function that maps between FBX and HIK.
 *	\ingroup Utility
 *	\param		pNodeId				Unique ID of the Node. See the ::HIKNodeId enumeration for possible values.
 *	\return		The name associated with the specified Node ID.
 */
HIK_EXPORT const char*  HIK_API HIKNodeNameFromNodeId(int pNodeId);

/**	\brief Retrieve the Effector ID from a descriptive name. This is a utility function that maps between FBX and HIK.
 *	\ingroup Utility
 *	\param		pName				Descriptive name for an Effector. Must match a value returned by HIKEffectorNameFromEffectorId().
 *	\return		The Effector ID associated with the specified name. See the ::HIKEffectorId enumeration for possible values.
 */
HIK_EXPORT int          HIK_API HIKEffectorIdFromEffectorName(const char* pName);

/**	\brief Retrieve a descriptive name for Effector \p pEffectorId. This is a utility function that maps between FBX and HIK.
 *	\ingroup Utility
 *	\param		pEffectorId			Unique ID of the Effector. See the ::HIKEffectorId enumeration for possible values.
 *	\return		The name associated with the specified Effector ID.
 */
HIK_EXPORT const char*  HIK_API HIKEffectorNameFromEffectorId(int pEffectorId);


// ***********************************************
/**	\defgroup Stream Determining Object Size in Memory
 *	\ingroup Object
 *	\brief This page describes the functions provided for determining the size in memory of the different HumanIK objects. 
 *
 *	These functions can be useful when streaming objects and copying objects between memory locations.
 */

/**	\brief Returns the size in bytes required by an HIKCharacter based on HIKCharacterDefinition \p pCharacterDefinition.
 *	\ingroup Stream
 *	\param		pCharacterDefinition	HIKCharacterDefinition.
 */
HIK_EXPORT size_t  HIK_API HIKCharacterDefinitionSize(const HIKCharacterDefinition *pCharacterDefinition);

/**	\brief Returns the size in bytes required by any HIKCharacterState that defines a pose for an HIKCharacter based on HIKCharacterDefinition \p pCharacterDefinition.
 *	\ingroup Stream
 *	\param		pCharacterDefinition 	HIKCharacterDefinition.
 */
HIK_EXPORT size_t  HIK_API HIKCharacterStateSizeFromDefinition(const HIKCharacterDefinition *pCharacterDefinition);



/**	\brief Returns the size of HIKCharacter \p pCharacter in bytes.
 *	\ingroup Stream
 *	\param		pCharacter			Character.
 */
HIK_EXPORT size_t  HIK_API HIKCharacterSize(const HIKCharacter* pCharacter);

/**	\brief Returns the size in bytes required by any HIKCharacterState that defines a pose for HIKCharacter \p pCharacter.
 *	All \HIKCharacterStates for a given character are always the same size.
 *	\ingroup Stream
 *	\param		pCharacter			Character.
 */
HIK_EXPORT size_t  HIK_API HIKCharacterStateSize(const HIKCharacter* pCharacter);


/**	\brief Returns the size of HIKCharacterState \p pCharacterState in bytes.
 *	All \HIKCharacterStates for a given character are always the same size.
 *	\ingroup Stream
 *	\param		pCharacterState		HIKCharacterState.
 */
HIK_EXPORT size_t  HIK_API HIKCharacterStateSizeFromState(const HIKCharacterState* pCharacterState);

/**	\brief Return the size of an HIKEffectorSetState object in bytes.
 *	\ingroup Stream
 */
HIK_EXPORT size_t  HIK_API HIKEffectorSetStateSize();

#ifdef __cplusplus
}
#endif

#endif
