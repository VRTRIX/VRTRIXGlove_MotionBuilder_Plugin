/*!	\file hikcreature.h
 *	\brief Header file for Creature solver.
 *
 *	This file contains solver primitives for running IK on creatures (non human and non quadrued)
 */

/**************************************************************************************

Copyright (C) 2014 Autodesk, Inc.
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

#ifndef _HIKCREATURE_
#define _HIKCREATURE_

#include "humanik.h"
#include "hikproperty.h"

#ifdef __cplusplus
extern "C" {
#endif

/**	\struct HIKCreature
 *	\ingroup Object
 *	\brief Defines a Creature to be used with HumanIK.
 *
 *	An HIKCreature contains all the information required by HumanIK to define a Creature:
 *		- the Nodes used in the Creature's skeletal hierarchy.
 *		- the default characterization pose that defines the Creature's geometry.
 *		- degrees of freedom assigned to each Node, if any.
 *		- a parent offset assigned to each Node, if any.
 *
 *	The exact byte size of an HIKCreature object depends on which joints the Creature uses, and whether it has allocated memory for parent offsets and DoF are allocated.
 *	See ~{ HumanIK Objects and Memory Management }~.
 *
 *	You can move HIKCreature objects freely between memory locations, or send them to another processing unit through DMA. 
 *
 *	\remarks HIKCreature objects should be used as pointers only. To create and destroy an HIKCreature, see HIKCreatureCreate() and HIKCreatureDestroy().
 */
struct HIKCreature;

/**	\struct HIKCreatureState
 *	\ingroup Object
 *	\brief Defines a pose for a creature.
 *
 *	This structure represents the pose of a specific creature at a given moment in time. 
 *	It contains the global space transformation matrix for each Node. See HIKSetNodeStatefv() and HIKGetNodeStatefv().
 *
 *	The size of a HIKCreatureState depends on how many Nodes the creature uses. See ~{ HumanIK Objects and Memory Management }~.
 *
 *	You can move HIKCreatureState objects freely between memory locations, or send them to another processing unit through DMA. 
 *
 *	\remarks HIKCreatureState objects should be used as pointers only. To create and destroy an HIKCreatureState, see HIKCreatureStateCreate() and HIKCreatureStateDestroy().
 */
struct HIKCreatureState;

/**	\struct HIKCreatureEffectorSetState
*	\ingroup Object
 *	\brief Defines an HIKCreatureEffectorSetState.
 *
 *	Represents a set of IK goal points at a given moment in time. 
 *	It contains:
 *		- The global space transformation matrix for each Effector. See HIKCreatureSetEffectorStatefv() and HIKCreatureGetEffectorStatefv().
 *		- The Reach Translation value for each Effector. See HIKCreatureSetTranslationActive() and HIKCreatureGetTranslationActive().
 *
 *	The size of a HIKCreatureState depends on how many Chains and Segment the creature uses.
 *
 *	You can move HIKCreatureEffectorSetState objects freely between memory locations, or send them to another processing unit through DMA. 
 *
 *	\remarks HIKCreatureEffectorSetState objects should be used as pointers only. To create and destroy an HIKCreatureEffectorSetState, see HIKCreatureEffectorSetStateCreate() and HIKCreatureEffectorSetStateDestroy().
 */
struct HIKCreatureEffectorSetState;

// ***********************************************
/**	\defgroup IKCreature Full-Body IK solver
 *	\ingroup IK
 *	\brief This page details the functions used to perform full-body IK solving for Creatures. 
 *
 */

typedef struct sHIKCreatureChainDefinition
{
	int mNbNodes;
	int mSection;				// Owner of the chain (-1 if free chain)
	int mNbParentOffsets;		// Can only be non-zero when working in local coordinates
	int mNbLimits;				// Number of nodes using limits
} HIKCreatureChainDefinition;

typedef struct sHIKCreatureSectionDefinition
{
	int mParentChain;			// -1 if not relevant (root section)
	int mHasParentOffset;		// Can only be non-zero when working in local coordinates
	int mHasLimits;				// Does the root node implement limits?
} HIKCreatureSectionDefinition;

typedef struct sHIKCreatureDefinition
{
	/**	The number of IK chains for this creature
	*/
	int mNbChains;
	int mNbSections;
    HIKCreatureChainDefinition * mChains;
	HIKCreatureSectionDefinition * mSections;
} HIKCreatureDefinition;

enum HIKChainSolvingType
{
	/*!	Fastest solving mode. The solving only involves the chain root. */
	HIKChainSolvingTypeOneBoneIK=0,
	/*!	Fastest solving mode. The solving only involves the chain root + an intermediary node. */
	HIKChainSolvingTypeTwoBonesIK,
	/*!	The solving only involves the chain root + all intermediary nodes, all folding on the same plane. */
	HIKChainSolvingTypeCoplanar,
	/*!	The solving involves all nodes in the chain, freely rotating - approximation only. */
	HIKChainSolvingTypeTentacleApprox,
	/*!	The solving involves all nodes in the chain, freely rotating, constrained with orienation reach. */
	HIKChainSolvingTypeTentacleCCD,
	/*!	The solving involves all nodes in the chain, potentially DOF constrained, re-ordered, all folding on the same plane. */
	HIKChainSolvingTypeQuadrupedLeg,
};

enum HIKParamTwoBonesIK
{
	/*! Index of the joint to fold in the chain (top = 0); default is 1. */
	HIKParamTwoBonesIK_FoldingJointIndex,
};

enum HIKParamTentacleCCD
{
	/*! Number of iterations for the CCD algorithm; default is 32. */
	HIKParamTentacleCCD_IterationCount,
	/*! Maximal joint rotation in radians; default is 0.157f. */
	HIKParamTentacleCCD_DOFAngle,
	/*! Defines how DOFs are applied along the chain.
	    0.0f : DOFFunction_Const : DOF is applied uniformy
		1.0f : DOFFunction_Linear : DOF is 0.0f for end node and linearly grows to HIKDOFAngle
		2.0f : DOFFunction_Square : DOF is 0.0f for end node and quadratically grows to HIKDOFAngle
	*/
	HIKParamTentacleCCD_DOFMode,
	/*! Defines how many joints in chain (from the end) should contribute to end orientation reach; default is 0.5f !*/
	HIKParamTentacleCCD_EndOrientationInfluence
};

/**	\ingroup IKCreature 
 *	\brief Create a new HIKCreature.
 *	\param		pCreatureDefinition		The HIKCreatureDefinition that specifies which Nodes your creature will be using, and which Nodes have DoF and parent offsets.
 *	\param		pMalloc					Pointer to a memory allocation function. If you do not have a custom memory allocation function, use &malloc.
 *	\param		pValidationString		The customer identification string given to you by Autodesk to license the use of HumanIK in your project.
 *  \return		NULL if an error occurs during the creation. This may indicate an invalid license, or that required Nodes are missing in the creature definition. 
 */

HIK_EXPORT HIKCreature * HIK_API HIKCreatureCreate( const HIKCreatureDefinition *pCreatureDefinition, HIKMalloc pMalloc, const char *pValidationString);

/**	\brief Set up and initialize creature \p pCreature for solving. 
 *
 *	Call this function after you have called HIKCreatureSetCharacterizeNodeStatefv() for all your creature's Nodes. This function
 *	finalizes the default stance and calibrates the engine.
 *	\ingroup CreatureSetup
 *	\param		pCcreature			Creature to set up and initialize.
 *	\remarks	The character must be standing in a stance where folding angles for chains are explicit (not 180 or 0 degrees)
*/

HIK_EXPORT bool	HIKCreatureCharacterizeGeometry(HIKCreature *pCreature);

/**	\brief Set the translation, orientation and scaling for the Node \p pNodeId when the character is standing in the default stance.
 *	\ingroup CreatureSetup
 *	\param		pCreature			The creature you want to set up.
 *	\param		pElementId			The unique ID of the Element that you want to set up (ChainId or -SectionId-1).
 *	\param		pNodeId				The unique ID of the Node that you want to set up.
 *	\param		pT					Default stance translation for this joint in global space.
 *	\param		pQ					Default stance orientation for this joint in global space, expressed as a quaternion.
 *	\param		pS					Default stance scale for this joint in global space.
 *  \return		FALSE if an error occured. This usually comes from wrong index (check 'pElementId' and 'pNodeId'). 
 */

HIK_EXPORT bool HIK_API HIKCreatureSetCharacterizeNodeStateTQSfv(HIKCreature * pCreature, int pElementId, int pNodeId, const float pT[4], const float pQ[4], const float pS[4]);

/** \brief Only relevant when working in local coordinates. Declares a parent offset for a chain node.
	       Has to be called before HIKCreatureCharacterizeGeometry(...)
		   Number of parent offsets for a Chain should be declared in the HIKCreatureChainDefinition structure first.
 *	\ingroup CreatureSetup
 *	\param		pCreature			The creature you want to set up.
 *	\param		pChainId			The unique ID of the Chain that you want to set up.
 *	\param		pNodeId				The unique ID of the Node that you want to set up.
*/

HIK_EXPORT bool HIK_API HIKCreatureSetHasParentOffset(HIKCreature *pCreature, int pChainId, int pNodeId);

/** \brief Declares a chain node implements limits.
	       Has to be called before HIKCreatureCharacterizeGeometry(...)
		   Number of limits for a Chain should be declared in the HIKCreatureChainDefinition structure first.
 *	\ingroup CreatureSetup
 *	\param		pCreature			The creature you want to set up.
 *	\param		pChainId			The unique ID of the Chain that you want to set up.
 *	\param		pNodeId				The unique ID of the Node that you want to set up.
*/

HIK_EXPORT bool HIK_API HIKCreatureSetHasLimits(HIKCreature *pCreature, int pChainId, int pNodeId);

/**	\brief Only relevant when working in local coordinates. Set the parent offset for Node \p pNodeId. 
 *
 *	This function is needed only if the parent joint is unknown to HumanIK
 *	\ingroup CreatureSetup
 *	\param		pCreature			The creature you want to set up.
 *	\param		pElementId			The unique ID of the Element that you want to set up (ChainId or -SectionId-1).
 *	\param		pNodeId				The unique ID of the Node that you want to set up.
 *	\param		pT					The parent node translation offset, relative to the next HumanIK Node above the parent in the joint chain.
 *	\param		pQ					The parent node rotation offset, expressed as a quaternion., relative to the next HumanIK Node above the parent in the joint chain. This value must be normalized.
 *									You can calculate this offset as follows: <pre>pParentQOffset = inverse(HIKParentGQ) * RealParentGQ</pre>
 *									where:
 *									- \p HIKParentGQ is a quaternion containing the rotation of the next HumanIK joint above the unknown parent joint in the skeletal hierarchy, expressed in global space
 *									- \p RealParentGQ is a quaternion containing the rotation of the unknown parent joint, expressed in global space.
 *	\param		pS					The parent node scaling offset, relative to the next HumanIK Node above the parent in the joint chain.
 */
HIK_EXPORT bool HIK_API HIKCreatureSetParentOffsetfv(HIKCreature *pCreature, int pElementId, int pNodeId, const float pT[4], const float pQ[4], const float pS[4]);

/**	\brief Retrieve the parent offset set for Node \p pNodeId. 
 *
 *	This function is needed only if the parent joint is unknown to HumanIK, and if you are using either local space transforms or limits (DoF).
 *	\ingroup CreatureSetup
 *	\param		pCreature			The character you want to get.
 *	\param		pElementId			The unique ID of the Element that you want to set up (ChainId or -SectionId-1).
 *	\param		pNodeId				The unique ID of the Node that you want to set up.
 *	\param		pT					The parent node translation offset.
 *	\param		pQ					The parent node rotation offset, expressed as a quaternion.
 *	\param		pS					The parent node scaling offset.
 */
HIK_EXPORT bool HIK_API HIKCreatureGetParentOffsetfv(const HIKCreature *pCreature, int pElementId, int pNodeId, float pT[4], float pQ[4], float pS[4]);

/**	\brief Set up limits for Node \p pNodeId.
 *	\ingroup CreatureLimits
 *	\param		pCreature			The creature you want to set up.
 *	\param		pElementId			The unique ID of the Element that you want to set up (ChainId or -SectionId-1).
 *	\param		pNodeId				The unique ID of the Node that you want to set up.
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
HIK_EXPORT bool HIK_API HIKCreatureSetLimitsfv(HIKCreature *pCreature, int pElementId, int pNodeId, 
										   const float pMin[3], const float pMax[3], 
										   const float pPreQ[4], const float pPostQ[4],
										   int pActiveMask,
										   eHIKRotationOrder pRotationOrder);

/**	\ingroup Constructor 
 *	\brief Create a new HIKCreatureState.
 *
 *	Each characterized joint requires 128 bytes of memory.
 *	\param		pCreature			HIKCreature associated with this HIKCreatureState.
 *	\param		pMalloc				Pointer to a memory allocation function. If you do not have a custom memory allocation function, use &malloc.
 *	\remarks						This HIKCreatureState cannot be shared between different \HIKCreatures.
 */

HIK_EXPORT HIKCreatureState * HIK_API HIKCreatureStateCreate(const HIKCreature *pCreature, HIKMalloc pMalloc);

/**	\ingroup Constructor 
 *	\brief Create a new HIKCreatureEffectorSetState. 
 *
 *	Each characterized chain requires XXX bytes of memory.
 *	Each characterized segment requires XXX bytes of memory.
 *	This HIKCreatureEffectorSetState will be used by the full-body IK solver.
  *	\param		pCreature			HIKCreature associated with this HIKCreatureState.
 *	\param		pMalloc				Pointer to a memory allocation function. If you do not have a custom memory allocation function, use &malloc.
 */

HIK_EXPORT HIKCreatureEffectorSetState * HIK_API HIKCreatureEffectorSetStateCreate(const HIKCreature *pCreature, HIKMalloc pMalloc);

/**	\brief Retrieve the default natural stance for creature \p pCreature, storing it in HIKCreatureState \p pCreatureState.
 *	This function always returns the same stance for the given creature. The default stance does not differ before and after you perform a solve.
 *	\ingroup CreatureSetup
 *	\param		pCreature			Creature whose default stance is to be retrieved.
 *	\param[out]	pCreatureState		HIKCreatureState to contain the default stance.
 */

HIK_EXPORT void	 HIK_API HIKCreatureGetDefaultState(const HIKCreature *pCreature, HIKCreatureState *pCreatureState);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) in global space of Node \p pNodeId from Chain \p pChainId in HIKCreatureState \p pCreatureState. Values are expressed using separate arrays.
 *	\ingroup CreatureStateSetupWrite
 *	\param		pCreature			HIKCreature for which you want to set the translation, rotation and scaling values.
 *	\param		pCreatureState		HIKCreatureState in which you want to set the translation, rotation and scaling values.
 *	\param		pElementId			Unique ID of the Element whose data you want to set (chainId or -sectionId-1)
 *	\param		pNodeId				Unique ID of the Node whose data you want to set.
 *	\param		pT					Translation value to set, in global space.
 *	\param		pQ					Rotation value to set, in global space.
 *	\param		pS					Scaling value to set, in global space.
 */

HIK_EXPORT void HIK_API HIKCreatureSetNodeStateTQSfv(const HIKCreature *pCreature, HIKCreatureState *pCreatureState, int pElementId, int pNodeId, const float pT[4], const float pQ[4], const float pS[4]);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) in global space of Node \p pNodeId from Chain \p pChainId in HIKCreatureState \p pCreatureState. Values are expressed using separate arrays.
 *	\ingroup CreatureStateSetupRead
 *	\param		pCreature			HIKCharacter from which you want to retrieve the translation, rotation, and scaling values.
 *	\param		pCreatureState		HIKCharacterState from which you want to retrieve the translation, rotation, and scaling values.
*	\param		pElementId			Unique ID of the Element whose data you want to set (chainId or -sectionId-1)
 *	\param		pNodeId				Unique ID of the Node whose data you want to retrieve.
 *	\param[out]	pT					Translation value retrieved, in global space.
 *	\param[out]	pQ					Rotation value retrieved, in global space.
 *	\param[out]	pS					Scaling value retrieved, in global space.
 */

HIK_EXPORT void HIK_API HIKCreatureGetNodeStateTQSfv(const HIKCreature *pCreature, const HIKCreatureState *pCreatureState, int pElementId, int pNodeId, float pT[4], float pQ[4], float pS[4]);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) of multiple Nodes from data set \p pDataSet, interpreted according to data description \p pDataDescription. 
 *
 *	\ingroup CreatureStateSetupWrite  
 *	This function is faster than setting the data for each Node individually using functions such as HIKCreatureSetNodeStateTQS().
 *	\param		pCreature			HIKCreature for which you want to set the data values.
 *	\param		pCreatureState		HIKCreatureState in which you want to set the data values.
 *	\param		pDataDescription	Data description defining the memory layout of your data set.
 *	\param		pDataSet			Void pointer to the beginning of your first data block.
 */

HIK_EXPORT bool HIK_API HIKCreatureSetStateTransformTQS(const HIKCreature *pCreature, HIKCreatureState *pCreatureState, const HIKDataDescription* pDataDescription, const void* pDataSet);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) of multiple Nodes from HIKCreatureState \p pCreatureState, writing them to memory in data set \p pDataSet according to data description \p pDataDescription. 
 *
 *	\ingroup CreatureStateSetupRead
 *	This function is faster than retrieving the data for each Node individually using functions such as HIKCreatureGetNodeStateTQS().
 *	\param		pCreature			HIKCreature from which you want to retrieve the data values.
 *	\param		pCreatureState		HIKCreatureState from which you want to retrieve the data values.
 *	\param		pDataDescription	Data description defining the memory layout of your data set.
 *	\param[out]	pDataSet			Void pointer to the beginning of your first data block.
 */

HIK_EXPORT bool HIK_API HIKCreatureGetStateTransformTQS(const HIKCreature *pCreature, HIKCreatureState *pCreatureState, const HIKDataDescription* pDataDescription, void* pDataSet);

/**	\ingroup EffectorSetupWrite
 *	\brief Set up HIKCreatureEffectorSetState \p pEffectorSetState to match creature \p pCreature in HIKCreatureState \p pCreatureState.
 *	\param		pCreature			Creature to query.
 *	\param[out]	pEffectorSetState	HIKEffectorSetState to be set up. 
 *	\param		pCreatureState		HIKCreatureState from which to set up the HIKCreatureEffectorSetState.
 */
HIK_EXPORT void HIK_API HIKEffectorSetFromCreature(const HIKCreature *pCreature, HIKCreatureEffectorSetState *pEffectorSetState, const HIKCreatureState *pCreatureState);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) in global space of Effector \p pEffectorIndex in HIKCreatureEffectorSetState \p pEffectorSetState. Values are expressed using separate arrays.
 *	\ingroup EffectorSetupRead
 *	\param		pEffectorSetState	HIKCreatureEffectorSetState containing the Effector whose translation, rotation and scaling you want to retrieve.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation, rotation and scaling you want to retrieve.
 *	\param[out]	pT					Stores the translation value, in global space.
 *	\param[out]	pQ					Stores the rotation value, in global space.
 *	\param[out]	pS					Stores the scaling value, in global space.
 */
HIK_EXPORT void HIK_API HIKCreatureGetEffectorStateTQSfv(const HIKCreatureEffectorSetState *pEffectorSetState, int pEffectorIndex, float pT[4], float pQ[4], float pS[4]);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) in global space of Effector \p pEffectorIndex in HIKCreatureEffectorSetState \p pEffectorSetState. Values are provided in separate arrays.
 *
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKCreatureEffectorSetState containing the Effector whose translation, rotation and scaling values you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose translation, rotation and scaling values you want to set.
 *	\param		pT					Translation value to set in global space.
 *	\param		pQ					Rotation value to set in global space.
 *	\param		pS					Scaling value to set in global space.
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetEffectorStateTQSfv(HIKCreatureEffectorSetState *pEffectorSetState, int pEffectorIndex, const float pT[4], const float pQ[4], const float pS[4]);

/**	\brief Set the Reach Translation constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKCreatureEffectorSetState containing the Effector whose value you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Reach Translation you want to set.
 *	\param		pValue				Value must be between 0.0 (pin the joint to the translation of the FK pose) and 1.0 (pin the joint to the translation of the Effector).
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetTranslationActive(HIKCreatureEffectorSetState *pEffectorSetState, int pEffectorIndex, float pValue);

/**	\brief Set the Reach Rotation constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKCreatureEffectorSetState containing the Effector whose value you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Reach Rotation you want to set.
 *	\param		pValue				Value must be between 0.0 (pin the joint to the rotation of the FK pose) and 1.0 (pin the joint to the rotation of the Effector).
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetRotationActive(HIKCreatureEffectorSetState *pEffectorSetState, int pEffectorIndex, float pValue);

/**	\brief Set the Pull constraint for Effector \p pEffectorIndex.
 *	\ingroup EffectorSetupWrite
 *	\param		pEffectorSetState	HIKCreatureEffectorSetState containing the Effector whose value you want to set.
 *	\param		pEffectorIndex		Unique ID of the Effector whose Pull you want to set.
 *	\param		pValue				Value must be between 0.0 (the joint will not pull other joints in order to reach its target) and 1.0 (the joint will have maximum priority for reaching its target).
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetPull(HIKCreatureEffectorSetState *pEffectorSetState, int pEffectorIndex, float pValue);

/**	\ingroup IK
 *	\brief Solve creature \p pCreature with HIKCreatureEffectorSetState \p pEffectorSetState and initial HIKCreatureState \p pCreatureState, storing results in \p pCreatureState.
 *
 *	You can enable or disable different parts of the solver by calling the HIKSetIKSolvingStep() function
 *	to set the solving step in HIKCreatureEffectorSetState \p pEffectorSetState.
 *
 *	You can re-use the same HIKCreatureEffectorSetState over multiple calls to this function, changing the position, rotation and IK constraints of only the Effectors you need to modify.
 *
 *	Only Effectors with a Reach Translation or Reach Rotation value greater than 0 are taken into account.
 *
 *	\param			pCreature			Creature to solve.
 *	\param			pEffectorSetState	HIKCreatureEffectorSetState containing the IK goal points and IK constraint values.
 *	\param[in,out]	pCreatureState		HIKCreatureState containing the initial FK pose for your creature, which may influence the IK solution.
 */
HIK_EXPORT void HIK_API HIKCreatureSolveForEffectorSet(HIKCreature *pCreature, HIKCreatureState *pCreatureState, HIKCreatureEffectorSetState *pEffectorSetState);

/**	\brief Sets how stiff a chain should behave (* Only relevant when doing FBIK)
 *	\ingroup CreatureTunings
 *	\param		pCreature			The creature you want to set up.
 *	\param		pChainId			The unique ID of the Chain to set up.
 *	\param		pValue				The stiffness (0.0 means no stiffnes, 1.0 means maximal stiffness)
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetChainStiffness(HIKCreature *pCreature, int pChainId, float pValue);

/**	\brief Sets how resistant a chain should behave when being compressed (* Only relevant when doing FBIK)
 *	\ingroup CreatureTuning
 *	\param		pCreature			The creature you want to set up.
 *	\param		pChainId			The unique ID of the Chain to set up.
 *	\param		pValue				The resistance to compression (0.0 means no resistance, 1.0 means maximal resistance)
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetChainCompressionResistance(HIKCreature *pCreature, int pChainId, float pValue);

/**	\brief Sets how a section should emphasizes its pull (* Only relevant when doing FBIK)
 *	\ingroup CreatureTuning
 *	\param		pCreature			The creature you want to set up.
 *	\param		pSectionId			The unique ID of the Section to set up.
 *	\param		pValue				The extra pull factor (0.0 means no extra pull (default))
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetSectionExtraPull(HIKCreature *pCreature, int pSectionId, float pValue);

/**	\brief Enable or disable FullBodyIK solving on the creature
 *	\ingroup CreatureTuning
 *	\param		pEffectorSetState	The EffectorSetState you want to set up.
 *	\param		pValue				Set to TRUE to enable FBIK solving; Set to FALSE to disable FBIK solving
 */
HIK_EXPORT void	 HIK_API HIKCreatureEnableFBIK(HIKCreatureEffectorSetState *pEffectorSetState, bool pValue);

/**	\brief Enable or disable torque solving on the creature (* Only relevant when doing FBIK)
 *	\ingroup CreatureTuning
 *	\param		pEffectorSetState	The EffectorSetState you want to set up.
 *	\param		pValue				Set to TRUE to enable torque solving; Set to FALSE to disable torque solving
 */
HIK_EXPORT void	 HIK_API HIKCreatureEnableTorque(HIKCreatureEffectorSetState *pEffectorSetState, bool pValue);

/**	\brief Set solving type for a specific chain in the creature
 *	\ingroup CreatureTuning
 *	\param		pCreature			The creature you want to set up.
 *	\param		pChainId			The unique ID of the Chain to set up.
 *	\param		pValue				Chain solving type (see enum above)
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetChainSolvingType(HIKCreature *pCreature, int pChainId, HIKChainSolvingType pValue);

/**	\brief Set property for a specific chain in the creature
 *	\ingroup CreatureTuning
 *	\param		pCreature			The creature you want to set up.
 *	\param		pChainId			The unique ID of the Chain to set up.
 *  \param		pPropertyIndex		Property index
 *	\param		pValue				Chain solving type (see enum above)
 */
HIK_EXPORT void	 HIK_API HIKCreatureSetChainProperty(HIKCreature *pCreature, int pChainId, int pPropertyIndex, float pValue);

/**	\brief Get parent section index for a chain
 *	\ingroup CreatureTuning
 *	\param		pCreature			The creature you want to set up.
 *	\param		pChainId			The unique ID of the Chain to set up.
 */
HIK_EXPORT int	 HIK_API HIKCreatureGetChainParentSectionIndex(HIKCreature *pCreature, int pChainId);

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
 *	\brief Destroy HIKCreature \p pCreature.
 *	\param		pCreature			Character to destroy.
 *	\param		pFree				Pointer to a memory de-allocation function. If you do not have a custom memory de-allocation function, use &free.
 */
HIK_EXPORT void  HIK_API HIKCreatureDestroy(HIKCreature *pCreature, HIKFree pFree);

/**	\ingroup Destructor
 *	\brief Destroy HIKCreatureEffectorSetState \p pEffectorSetState.
 *	\param		pEffectorSetState	HIKCreatureEffectorSetState to destroy.
 *	\param		pFree				Pointer to a memory de-allocation function. If you do not have a custom memory de-allocation function, use &free.
 */
HIK_EXPORT void  HIK_API HIKCreatureEffectorSetStateDestroy(HIKCreatureEffectorSetState *pEffectorSetState, HIKFree pFree);

/**	\ingroup Destructor
 *	\brief Destroy HIKCreatureState \p pCreatureState.
 *	\param		pCreatureState		HIKCreatureState to destroy.
 *	\param		pFree				Pointer to a memory de-allocation function. If you do not have a custom memory de-allocation function, use &free.
 */
HIK_EXPORT void  HIK_API HIKCreatureStateDestroy(HIKCreatureState *pCreatureState, HIKFree pFree);

// Stats (please do not rely on these functions)

HIK_EXPORT float HIK_API HIKCreatureGetChainLastPull(HIKCreature *pCreature, int pChainId);
HIK_EXPORT float HIK_API HIKCreatureGetChainLastPullLength(HIKCreature *pCreature, int pChainId);
HIK_EXPORT float HIK_API HIKCreatureGetChainLastChainWeightsT(HIKCreature *pCreature, int pChainId);
HIK_EXPORT void  HIK_API HIKCreatureGetChainLastChainPullDir(HIKCreature *pCreature, int pChainId, int pIter, float pT[4]);
HIK_EXPORT float HIK_API HIKCreatureGetChainLastChainErrT(HIKCreature *pCreature, int pChainId, int pIter);
HIK_EXPORT void  HIK_API HIKCreatureGetChainLastChainErrQ(HIKCreature *pCreature, int pChainId, int pIter, float pQ[4]);
HIK_EXPORT void  HIK_API HIKCreatureGetSectionLastSumErr(HIKCreature *pCreature, int pSectionId, int pIter, float pT[4]);
HIK_EXPORT float HIK_API HIKCreatureGetSectionLastSectionErrWeightT(HIKCreature *pCreature, int pSectionId, int pIter);
HIK_EXPORT float HIK_API HIKCreatureGetSectionLastSectionWeights(HIKCreature *pCreature, int pSectionId, int pIter);
HIK_EXPORT void  HIK_API HIKCreatureGetSectionLastSectionErrQPull(HIKCreature *pCreature, int pSectionId, int pIter, float pQ[4]);
HIK_EXPORT void  HIK_API HIKCreatureGetSectionLastSectionErrQReach(HIKCreature *pCreature, int pSectionId, int pIter, float pQ[4]);

#ifdef __cplusplus
}
#endif

#endif
