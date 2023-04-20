/*!	\file hikutils.h
 *	\brief Header file containing HumanIK utilities.
 *
 *	This file contains utility functions for use with HumanIK.
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

#ifndef _HIK_UTILS_
#define _HIK_UTILS_

#include "humanik.h"
#include "hikproperty.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Set the translation (T), quaternion rotation (Q) and scaling (S) values in global space for Node \p pNodeId in HIKCharacterState \p pCharacterState,
 *	without applying any rotation and scale offsets contained in the character's characterization pose (its default T-stance).
 *
 *	You can use this function to set a Node's TQS values from FK animation in cases where the characterization pose of your character does not contain any rotation or scale offsets.
 *	This function is faster than HIKSetNodeStateTQSfv().
 *	\ingroup	CharacterStateSetupWrite
 *
 *	\param		pCharacter			HIKCharacter used to create the HIKCharacterState specified in the \p pCharacterState parameter.
 *	\param		pCharacterState		HIKCharacterState.
 *	\param		pNodeId				Index of the Node whose TQS values are to be set. See the ::HIKNodeId enumeration for possible values.
 *	\param		pT					Global translation values to set for the Node.
 *	\param		pQ					Global rotation values to set for the Node.
 *	\param		pS					Global scaling values to set for the Node.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeNormalizedStateTQSfv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float pT[4], const float pQ[4], const float pS[4]);
/**	\copydoc HIKSetNodeNormalizedStateTQSfv()
 *	\ingroup CharacterStateSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetNodeNormalizedStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeNormalizedStateTQSdv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const double pT[4], const double pQ[4], const double pS[4]);

/**	\brief Set the transform matrix for Node \p pNodeId in HIKCharacterState \p pCharacterState, without applying any rotation and scale offsets contained in the character's characterization pose (its default T-stance).
 *
 *	You can use this function to set a Node's TQS values from FK animation in cases where the characterization pose of your character does not contain any rotation or scale offsets.
 *	This function is faster than HIKSetNodeStatefv().
 *	\ingroup    CharacterStateSetupWrite
 *
 *	\param		pCharacter			HIKCharacter used to create the HIKCharacterState specified in the \p pCharacterState parameter.
 *	\param		pCharacterState		HIKCharacterState.
 *	\param		pNodeId				Index of the Node whose matrix is to be set. See the ::HIKNodeId enumeration for possible values.
 *	\param		pXForm				Transform matrix to set for the Node.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeNormalizedStatefv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float pXForm[16]);
/**	\copydoc HIKSetNodeNormalizedStatefv()
 *	\ingroup CharacterStateSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetNodeNormalizedStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetNodeNormalizedStatedv(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const double pXForm[16]);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) values in global space for Node \p pNodeId in HIKCharacterState \p pCharacterState, 
 *	without applying any rotation and scale offsets contained in the character's characterization pose (its default T-stance). 

 *	You can use this function to retrieve a Node's TQS values in cases where the characterization pose of your character does not contain any rotation or scale offsets.
 *	This function is faster than HIKGetNodeStateTQSfv().
 *	\ingroup CharacterStateSetupRead
 *
 *	\param		pCharacter			HIKCharacter used to create the HIKCharacterState specified in the \p pCharacterState parameter.
 *	\param		pCharacterState		HIKCharacterState.
 *	\param		pNodeId				Index of the Node whose TQS values are to be retrieved. See the ::HIKNodeId enumeration for possible values.
 *	\param[out]	pT					Global translation values of the Node.
 *	\param[out]	pQ					Global rotation values of the Node.
 *	\param[out]	pS					Global scaling values of the Node.
*/
HIK_EXPORT void	 HIK_API HIKGetNodeNormalizedStateTQSfv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, float pT[4], float pQ[4], float pS[4]);
/**	\copydoc HIKGetNodeNormalizedStateTQSfv()
 *	\ingroup CharacterStateSetupRead
 *	This function converts floating-point numbers internally to double-precision. For best performance, use the HIKGetNodeNormalizedStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeNormalizedStateTQSdv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, double pT[4], double pQ[4], double pS[4]);

/**	\brief Retrieve the transform matrix for Node \p pNodeId in HIKCharacterState \p pCharacterState, without applying any rotation and scale offsets contained in the
 *	character's characterization pose (its default T-stance). 
 *
 *	You can use this function to retrieve a Node's TQS values in cases where the characterization pose of your character does not contain any rotation or scale offsets.
 *	This function is faster than HIKGetNodeStatefv().
 *	\ingroup    CharacterStateSetupRead
 *
 *	\param		pCharacter			HIKCharacter used to create the HIKCharacterState specified in the \p pCharacterState parameter.
 *	\param		pCharacterState		HIKCharacterState.
 *	\param		pNodeId				Index of the Node whose matrix is to be retrieved. See the ::HIKNodeId enumeration for possible values.
 *	\param[out]	pXForm				Transform matrix of the Node.
 */
HIK_EXPORT void	 HIK_API HIKGetNodeNormalizedStatefv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, float  pXForm[16]);
/**	\copydoc HIKGetNodeNormalizedStatefv()
 *	\ingroup CharacterStateSetupRead
 *	This function converts floating-point numbers internally to double-precision. For best performance, use the HIKGetNodeNormalizedStatefv() function instead wherever possible.
*/
HIK_EXPORT void	 HIK_API HIKGetNodeNormalizedStatedv(const HIKCharacter *pCharacter, const HIKCharacterState *pCharacterState, int pNodeId, double pXForm[16]);

/**	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) values in global space for all Nodes listed in data description \p pDataDescription, without
 *	applying any rotation and scale offsets contained in the character's characterization pose (its default T-stance).
 *
 *	You can use this function to set a Node's TQS values from FK animation in cases where the characterization pose of your character does not contain any rotation or scale offsets.
 *	This function is faster than HIKSetCharacterStateTransformTQS(), and faster than setting the values for each Node individually through 
 *	iterative calls to HIKSetNodeNormalizedStateTQSfv().
 *	\ingroup CharacterStateSetupWrite
 *
 *	\param		pCharacter			HIKCharacter used to create the HIKCharacterState specified in the \p pCharacterState parameter.
 *	\param		pCharacterState		HIKCharacterState.
 *	\param		pDataDescription		Data description for your data set.
 *	\param		pDataSet				void pointer to the beginning of your first data block.
 */
HIK_EXPORT void	 HIK_API HIKSetNormalizedCharacterStateTransformTQS(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, const void* pDataSet);

/**	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) values in global space for all Nodes listed in data description \p pDataDescription, without
 *	applying any rotation and scale offsets contained in the character's characterization pose (its default T-stance).
 *
 *	You can use this function to retrieve a Node's TQS values in cases where the characterization pose of your character does not contain any rotation or scale offsets.
 *	This function is faster than HIKGetCharacterStateTransformTQS(), and faster than retrieving the values for each Node individually through 
 *	iterative calls to HIKGetNodeNormalizedStateTQSfv().
 *	\ingroup CharacterStateSetupRead
 *
 *	\param		pCharacter			HIKCharacter used to create the HIKCharacterState specified in the \p pCharacterState parameter.
 *	\param		pCharacterState		HIKCharacterState.
 *	\param		pDataDescription	Data description for your data set.
 *	\param[out]	pDataSet			void pointer to the beginning of your first data block.
 */
HIK_EXPORT void	 HIK_API HIKGetNormalizedCharacterStateTransformTQS(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKDataDescription* pDataDescription, void* pDataSet);

/**	\ingroup EffectorSetupWrite
 *	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) values in global space for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState, taking into account the IK pivot \p pIKPivot.
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pEffectorIndex		Index of the Effector whose TQS values are to be set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pT					Global translation values to set for the Effector.
 *	\param		pQ					Global rotation values to set for the Effector.
 *	\param		pS					Global scaling values to set for the Effector.
 *	\param		pIKPivot			Global position of the IK pivot.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorPivotStateTQSfv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const float pT[4], const float pQ[4], const float pS[4], const float pIKPivot[4]);
/**	@copydoc HIKSetEffectorPivotStateTQSfv()
 *	\ingroup EffectorSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorPivotStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorPivotStateTQSdv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const double pT[4], const double pQ[4], const double pS[4], const double pIKPivot[4]);

/**	\ingroup EffectorSetupWrite
 *	\brief Set the transform matrix for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState, taking into account the IK pivot \p pIKPivot.
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pEffectorIndex		Index of the Effector whose matrix is to be set. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pXForm				Transform matrix to set for the Effector.
 *	\param		pIKPivot			Global position of the IK pivot.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorPivotStatefv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const float pXForm[16], const float pIKPivot[4]);
/**	@copydoc HIKSetEffectorPivotStatefv()
 *	\ingroup EffectorSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorPivotStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetEffectorPivotStatedv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const double pXForm[16], const double pIKPivot[4]);

/**	\ingroup EffectorSetupRead
 *	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) values in global space for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState, taking into account the IK pivot \p pIKPivot.
 *
 *	The final position of the Effector is computed as follows:<br>
 *	<code>final_position = effector_position + effector_q * pivot</code>
 *
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pEffectorIndex		Index of the Effector whose TQS values are to be retrieved. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pT					Global translation values of the Effector.
 *	\param[out]	pQ					Global rotation values of the Effector.
 *	\param[out]	pS					Global scaling values of the Effector.
 *	\param		pIKPivot			Local position of the IK pivot.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorPivotStateTQSfv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pT[4], float pQ[4], float pS[4], const float pIKPivot[4]);
/**	@copydoc HIKGetEffectorPivotStateTQSfv()
 *	\ingroup EffectorSetupRead
 *	This function converts floating-point numbers internally to double-precision. For best performance, use the HIKGetEffectorPivotStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorPivotStateTQSdv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, double pT[4], double pQ[4], double pS[4], const double pIKPivot[4]);

/**	\ingroup EffectorSetupRead
 *	\brief Retrieve the transform matrix for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState, taking into account the IK pivot \p pIKPivot.
 *
 *	The final position of the Effector is computed as follows:<br>
 *	<code>final_position = effector_position + effector_q * pivot</code>
 *
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pEffectorIndex		Index of the Effector whose matrix is to be retrieved. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pXForm				Transform matrix of the Effector.
 *	\param		pIKPivot			Local position of the IK pivot.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorPivotStatefv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, float pXForm[16], const float pIKPivot[4]);
/**	@copydoc HIKGetEffectorPivotStatefv()
 *	\ingroup EffectorSetupRead
 *	This function converts floating-point numbers internally to double-precision. For best performance, use the HIKGetEffectorPivotStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKGetEffectorPivotStatedv(const HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, double pXForm[16], const double pIKPivot[4]);

/**	\ingroup EffectorSetupWrite
 *	\brief Set the translation (T), quaternion rotation (Q) and scaling (S) values in global space for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState, 
 *	removing any rotation and scale offsets contained in the character's characterization pose (its default T-stance) from the final rotation of the Effector.
 *
 *	You can use this function to set the rotation of a joint directly on its corresponding Effector.
 *
 *	\param		pCharacter			Set the Effector into this character's local space.
 *	\param		pEffectorIndex		Index of the Effector whose TQS values are to be set. See enum ::HIKEffectorId for possible values.
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pT					Global translation values to set for the Effector.
 *	\param		pQ					Global rotation values to set for the Effector.
 *	\param		pS					Global scaling values to set for the Effector.
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterSpaceEffectorStateTQSfv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, const float pT[4], const float pQ[4], const float pS[4]);
/**	\ingroup EffectorSetupWrite
 *	\brief Set the translation (T) and quaternion rotation (Q) values in global space for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState,
 *	removing any rotation and scale offsets contained in the character's characterization pose (its default T-stance) from the final rotation of the Effector. 
 *
 *	You can use this function to set the rotation of a joint directly on its corresponding Effector.
 *
 *	This function sets the scaling values for all axes to \p 1.0f.
 *	\param		pCharacter			Set the Effector into this character's local space.
 *	\param		pEffectorIndex		Index of the Effector whose TQ values are to be set. See enum ::HIKEffectorId for possible values.
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pT					Global translation values to set for the Effector.
 *	\param		pQ					Global rotation values to set for the Effector.
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterSpaceEffectorStateTQfv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, const float pT[4], const float pQ[4]);
/**	@copydoc HIKSetCharacterSpaceEffectorStateTQSfv()
 *	\ingroup EffectorSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetCharacterSpaceEffectorStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterSpaceEffectorStateTQSdv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, const double pT[4], const double pQ[4], const double pS[4]);

/**	\ingroup EffectorSetupWrite
 *	\brief Set the transform matrix in global space for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState, removing any 
 *	rotation and scale offsets contained in the character's characterization pose (its default T-stance) from the final rotation of the Effector. 
 *
 *	You can use this function to set the rotation of a joint directly on its corresponding Effector.
 *
 *	\param		pCharacter			Set the Effector into this character's local space.
 *	\param		pEffectorIndex		Index of the Effector whose matrix is to be set. See enum ::HIKEffectorId for possible values.
 *	\param		pEffectorSetState	Effectort set state.
 *	\param		pXForm				Global transform matrix to set for the Effector.
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterSpaceEffectorStatefv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, const float pXForm[16]);
/**	@copydoc HIKSetCharacterSpaceEffectorStatefv()
 *	\ingroup EffectorSetupWrite
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetCharacterSpaceEffectorStatefv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterSpaceEffectorStatedv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, const double pXForm[16]);

/**	\ingroup EffectorSetupRead
 *	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) values in global space for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState,
 *	and applies any rotation and scale offsets contained in the character's characterization pose (its default T-stance) to the final rotation of the Effector. 
 *
 *	You can use this function to retrieve the rotation of an Effector in character space.
 *
 *	\param		pCharacter			Retrieve the Effector from this character's local space.
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pEffectorIndex		Index of the Effector whose TQS values are to be retrieved. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pT					Stores the retrieved global translation value.
 *	\param[out]	pQ					Stores the retrieved global rotation value.
 *	\param[out]	pS					Stores the retrieved global scaling value.
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterSpaceEffectorStateTQSfv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, float pT[4], float pQ[4], float pS[4]);
/**	@copydoc HIKGetCharacterSpaceEffectorStateTQSfv()
 *	This function converts floating-point numbers internally to double-precision. For best performance, use the HIKGetCharacterSpaceEffectorStateTQSfv() function instead wherever possible.
 *	\ingroup EffectorSetupRead
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterSpaceEffectorStateTQSdv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, double pT[4], double pQ[4], double pS[4]);

/**	\ingroup EffectorSetupRead
 *	\brief Retrieve the transform matrix in global space for Effector \p pEffectorIndex in HIKEffectorSetState \p pEffectorSetState,
 *	and applies any rotation and scale offsets contained in the character's characterization pose (its default T-stance) to the final rotation of the Effector. 
 *
 *	You can use this function to retrieve the rotation of an Effector in character space.
 *
 *	\param		pCharacter			Retrieve the Effector from this character's local space.
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pEffectorIndex		Index of the effector whose TQS values are to be retrieved. See the ::HIKEffectorId enumeration for possible values.
 *	\param[out]	pXForm				Stores the retrieved global transform matrix.
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterSpaceEffectorStatefv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, float pXForm[16]);
/**	@copydoc HIKGetCharacterSpaceEffectorStatefv()
 *	This function converts floating-point numbers internally to double-precision. For best performance, use the HIKGetCharacterSpaceEffectorStatefv() function instead wherever possible.
 *	\ingroup EffectorSetupRead
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterSpaceEffectorStatedv(const HIKCharacter *pCharacter, int pEffectorIndex, HIKEffectorSetState *pEffectorSetState, double pXForm[16]);

/**	\ingroup EffectorSetupWrite
 *	\brief Set the translation (T), quaternion rotation (Q) and IK constraints for all Effectors specified in data description \p pDataDescription, 
 *	removing any rotation and scale offsets contained in the character's characterization pose (its default T-stance) from the final rotation of each Effector. 
 *
 *	You can use this function to set the rotation of your character's joints in local space directly on their corresponding Effectors.
 *	This function is faster than setting values for each Effector individually through iterative calls to HIKSetCharacterSpaceEffectorStateTQSfv().
 *
 *	This function sets the scaling values for all axes to \p 1.0f.
 *	\param		pCharacter			Set Effectors TQ in this character space.
 *	\param		pEffectorSetState	HIKEffectorSetState to set data in.
 *	\param		pDataDescription	Data description for your data set.
 *	\param		pDataSet			void pointer to the beginning of your first data block.
 */
HIK_EXPORT void	 HIK_API HIKSetCharacterSpaceEffectorStateDataTQ(const HIKCharacter *pCharacter, HIKEffectorSetState *pEffectorSetState, const HIKEffectorDataDescription* pDataDescription, const void* pDataSet);

/**	\ingroup EffectorSetupRead
 *	\brief Retrieve the translation (T), quaternion rotation (Q) and IK constraint values for all Effectors specified in data description \p pDataDescription, 
 *	applying any rotation and scale offsets contained in the character's characterization pose (its default T-stance) to the final rotation of each Effector. 
 *
 *	You can use this function to retrieve the rotation of multiple Effectors in local space.
 *	This function is faster than retrieving values for each Effector individually through iterative calls to HIKGetCharacterSpaceEffectorStateTQSfv().
 *
 *	\param		pCharacter			Retrieve the Effectors from this character space.
 *	\param		pEffectorSetState	HIKEffectorSetState to retrieve data from.
 *	\param		pDataDescription	Data description for your data set.
 *	\param		pDataSet			void pointer to the beginning of your first data block.
 */
HIK_EXPORT void	 HIK_API HIKGetCharacterSpaceEffectorStateDataTQ(const HIKCharacter *pCharacter, const HIKEffectorSetState *pEffectorSetState, const HIKEffectorDataDescription* pDataDescription, void* pDataSet);


/**	\ingroup FloorContact 
 *	\brief Retrieve the translation in global space for one of the markers used by the floor contact engine to define the feet or hands of 
 *	character \p pCharacter with HIKCharacterState \p pState.
 *
 *	For details on how these floor contact markers are calculated from character properties, see ~{ Foot and Hand Contact }~.
 *	\param		pCharacter			HIKCharacter.
 *	\param		pState				HIKCharacterState.
 *	\param		pPropertySetState	HIKPropertySetState defining the floor contact properties for the character. See the floor contact properties, such as HIKFootBottomToAnkleId, etc...
 *	\param		pMemberIndex		Defines which limb to retrieve the result from. 0 = left hand, 1 = right hand, 2 = left foot, 3 = right foot.
 *	\param		pContactIndex		Defines which floor contact marker to retrieve. Can be a value from 0 to 5 depending on floor contact type: normal, wrist, fingerbase or hoof.
 *	\param[out]	pT					Global translation of the floor contact marker. 
 *	\return							Returns 1 if pMemberIndex and pContactIndex are valid, otherwise 0.
 */
HIK_EXPORT int	     HIK_API HIKGetFloorContactPointPositionfv(const HIKCharacter *pCharacter, const HIKCharacterState *pState, const HIKPropertySetState *pPropertySetState, int pMemberIndex, int pContactIndex, float pT[4]);

/**	\ingroup FloorContact 
 *	\brief Retrieve the translation in global space for one of the markers used by the floor contact engine to define the feet or hands of 
 *	character \p pCharacter with HIKCharacterState \p pState.
 *
 *	For details on how these floor contact markers are calculated from character properties, see ~{ Foot and Hand Contact }~.
 *	\param		pCharacter			HIKCharacter.
 *	\param		pState				HIKCharacterState.
 *	\param		pPropertySetState	HIKPropertySetState defining the floor contact properties for the character. See the floor contact properties, such as HIKFootBottomToAnkleId, etc...
 *	\param		pMemberIndex		Defines which limb to retrieve the result from. 0 = left hand, 1 = right hand, 2 = left foot, 3 = right foot.
 *	\param		pContactIndex		Defines which floor contact marker to retrieve. Can be a value from 0 to 5 depending on floor contact type: normal, wrist, fingerbase or hoof.
 *	\param[out]	pXForm				Global transformation matrix of the floor contact marker. 
 *	\return							Returns 1 if pMemberIndex and pContactIndex are valid, otherwise 0.
 */
HIK_EXPORT int	     HIK_API HIKGetFloorContactPointPositiondv(const HIKCharacter *pCharacter, const HIKCharacterState *pState, const HIKPropertySetState *pPropertySetState, int pMemberIndex, int pContactIndex, double pXForm[16]);

/**	\ingroup Utility 
 *	\brief Transfer the Pull and Resist properties from the HIKPropertySetState \p pPropertySetState to the HIKEffectorSetState \p pEffectorSetState.
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pPropertySetState	HIKPropertySetState.
 */
HIK_EXPORT	void	 HIK_API HIKSetEffectorPullResistFromPropertyState(HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertySetState); 

/**	\ingroup Utility 
 *	\brief Retrieve the parent Node of the specified Node \p pChildNodeId.
 *	\param		pCharacter			HIKCharacter.
 *	\param		pChildNodeId		ID of the child node. See the ::HIKNodeId enumeration for possible values.
 *	\return							The HIKNodeId of the parent Node.
 */
HIK_EXPORT int		 HIK_API HIKGetParentNodeId(const HIKCharacter *pCharacter, int pChildNodeId);

/**	\ingroup Utility 
 *	\brief Retrieve the number of child Nodes associated with the parent Node \p pParentNodeId
 *	\param		pCharacter			HIKCharacter.
 *	\param		pParentNodeId		ID of the parent node. See the ::HIKNodeId enumeration for possible values.
 *	\return							The number of child Nodes possessed by the specified parent Node.
 */
HIK_EXPORT int		 HIK_API HIKGetChildNodeCount(const HIKCharacter *pCharacter, int pParentNodeId);

/**	\ingroup Utility 
 *	\brief Retrieve the child Node with index \p pChildIndex for the parent Node \p pParentNodeId.
 *	\param pCharacter				HIKCharacter.
 *	\param pParentNodeId			ID of the parent node. See the ::HIKNodeId enumeration for possible values.
 *	\param pChildIndex				Index of the child. Should be a value between 0 and the value returned by HIKGetChildNodeCount() for the parent Node.
 *	\return							The HIKNodeId of the child Node.
 */
HIK_EXPORT int		 HIK_API HIKGetChildNodeId(const HIKCharacter *pCharacter, int pParentNodeId, int pChildIndex);

/**	\ingroup Utility 
 *	\brief Copy HIKCharacterState from \p pStateIn to \p pStateOut.
 *	\param[out]	pStateOut			Output HIKCharacterState.
 *	\param		pStateIn			Input HIKCharacterState.
 */
HIK_EXPORT void      HIK_API HIKCharacterStateCopy(HIKCharacterState *pStateOut, const HIKCharacterState *pStateIn);

/**	\ingroup Utility 
 *	\brief Perform a linear blending between HIKCharacterState \p pStateIn1 and HIKCharacterState \p pStateIn2.
 *	\param		pCharacter			HIKCharacter for which the blend is performed.
 *	\param[out]	pStateOut			HIKCharacterState containing the blended pose.
 *	\param		pStateIn1			HIKCharacterState 1.
 *	\param		pStateIn2			HIKCharacterState 2.
 *	\param		blendFactor			Blend factor. The value of this parameter must be between 0 and 1, where lower values prioritize HIKCharacterState 1, higher values prioritize HIKCharacterState 2, and a value of 0.5 blends the two states equally.
 */
HIK_EXPORT void	     HIK_API HIKBlendState(const HIKCharacter* pCharacter, HIKCharacterState* pStateOut, HIKCharacterState const * pStateIn1, HIKCharacterState const * pStateIn2, float blendFactor);

/**	\brief Post multiply the current translation, rotation and scale of Effector \p pEffectorIndex with pT, pQ and pS.
 *	\ingroup Utility
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pEffectorIndex		Index of the Effector whose transform matrix will be post multiplied. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pT					Global translation to post multiply.
 *	\param		pQ					Global rotation to post multiply.
 *	\param		pS					Global scaling to post multiply.
 *	\param		pInverse			If set to 1, the inverse post multiplication is performed.
 */
HIK_EXPORT void	 HIK_API HIKEffectorStatePostMultTQSfv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const float pT[4], const float pQ[4], const float pS[4], int pInverse);
/**	@copydoc HIKEffectorStatePostMultTQSfv()
 *	\ingroup Utility
 */
HIK_EXPORT void	 HIK_API HIKEffectorStatePostMultTQSdv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const double pT[4], const double pQ[4], const double pS[4], int pInverse);

/**	\brief Post multiply the current translation, rotation and scale of Effector \p pEffectorIndex with pXForm.
 *	\ingroup Utility
 *	\param		pEffectorSetState	HIKEffectorSetState.
 *	\param		pEffectorIndex		Index of the Effector whose transform matrix will be post multiplied. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pXForm				Transform matrix to post multiply.
 *	\param		pInverse			If set to 1, the inverse post multiplication is performed.
 */
HIK_EXPORT void	 HIK_API HIKEffectorStatePostMultfv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const float pXForm[16], int pInverse);
/**	@copydoc HIKEffectorStatePostMultfv()
 *	\ingroup Utility
 */
HIK_EXPORT void	 HIK_API HIKEffectorStatePostMultdv(HIKEffectorSetState *pEffectorSetState, int pEffectorIndex, const double pXForm[16], int pInverse);

/**	\brief Applies the limits built in to the HumanIK bio-mechanical model to the pose contained in \p pState.
 *
 *	\ingroup Utility
 *	This function takes a pose that may not be tenable for a real biped, such as a pose generated by a ragdoll physics system, and constrains the translations and rotations of the Nodes to
 *	produce a valid position for a biped character that satisfies the requirements built in to the HumanIK bio-mechanical model.
 *	\param			pCharacter		The HIKCharacter corresponding to \p pState.
 *	\param[in, out]	pState			A HIKCharacterState containing the pose to be altered.
 */
HIK_EXPORT void		 HIK_API HIKApplyHumanLimits(const HIKCharacter* pCharacter, HIKCharacterState* pState);
/**	\brief Blends the pose contained in HIKCharacterState \p pState with a default "relaxed pose" generated internally for the character.
 *
 *	\ingroup Utility
 *	This function generates a "relaxed pose" for HIKCharacter \p pCharacter: a pose in which all limbs are rotated helf-way between their minimum and maximum extents.
 *	This relaxed pose is then blended with the pose provided in \p pState. 
 *
 *	The relative weight of the blending along each axis is controlled by \p pX, \p pY and \p pZ. A value of 0 for any of these parameters weights the blending entirely toward \p pState.
 *	A value of 1.0f weights the blending entirely toward the relaxed pose. Values in between interpolate the resulting position between \p pState and the relaxed pose.
 *	\param			pCharacter		The HIKCharacter corresponding to \p pState.
 *	\param[in, out]	pState			A HIKCharacterState containing the pose to be relaxed.
 *	\param			pX				The relative weight on the X axis when blending between \p pState and the relaxed pose. 
 *	\param			pY				The relative weight on the Y axis when blending between \p pState and the relaxed pose. 
 *	\param			pZ				The relative weight on the Z axis when blending between \p pState and the relaxed pose. 
 */
HIK_EXPORT void		 HIK_API HIKRelaxState(const HIKCharacter* pCharacter, HIKCharacterState* pState,float pX,float pY,float pZ);

/* *********************************************** */
/**	\defgroup Logging Logging 
 *	\brief This section describes the functions and enumerations provided for logging messages from HumanIK.
 *
 *	For an overview, see ~{ Logging Debug Messages }~
 */

/* *********************************************** */
/*!	\ingroup Logging
 *	\enum HIKLoggingLevel
 *	\brief Lists the possible logging levels that you can set for HumanIK. See HIKSetLoggingLevel().
 */
enum HIKLoggingLevel 
{
	/*! If specified on its own, this flag disables the generation of all log messages. If specified in conjunction
		with any other logging level listed below, this flag has no effect. */
	HIKNone = 0,
	/*! Configures HumanIK to log severe problems with your character setup. For example, if your HIKCharacter
		is missing one or more required Nodes. */
	HIKError = 1 << 0, 
	/*! Configures HumanIK to log informational messages that may indicate problems with your character setup.
		For example, if your character's arms do not appear to be aligned along the X axis.*/
	HIKMessage = 1 << 2,
	HIKCallstack = 1 << 3, //!< Configures HumanIK to log its call stack.
	HIKStacksize = 1 << 4, //!< Configures HumanIK to log the size of its call stack
	/*! Configures HumanIK to log the Degrees of Freedom set for each character when its geometry is finalized through
		a call to the HIKCharacterizeGeometry function.*/
	HIKLimits = 1 << 5
};

/**	\ingroup Logging
 *	\brief Set the logging level for HumanIK.
 *	\param		pLogging		Logging level, expressed as a bit mask built from the ::HIKLoggingLevel enumeration. To enable
								multiple types of log messages, concatenate them using the | operator (bitwise OR).
*/
HIK_EXPORT void  HIK_API HIKSetLoggingLevel(int pLogging);


/**	\brief Pre multiply the current translation, rotation and scale of Node \p pNodeId with pT, pQ and pS.
 *	\ingroup Utility
 *	\param		pCharacter			HIKCharacter to be modified.
 *	\param		pCharacterState		HIKCharacterState containing the pose to be modified by pre-rotation.
 *	\param		pNodeId				Index of the Node whose transform matrix will be pre multiplied. See the ::HIKNodeId enumeration for possible values.
 *	\param		pT					Global translation to pre multiply.
 *	\param		pQ					Global rotation to pre multiply.
 *	\param		pS					Global scaling to pre multiply.
 *	\param		pInverse			If set to 1, the inverse pre multiplication is performed.
 */
HIK_EXPORT void	 HIK_API HIKNodeStatePreMultTQSfv(const HIKCharacter* pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const float pT[4], const float pQ[4], const float pS[4], int pInverse);
/**	@copydoc HIKNodeStatePreMultTQSfv()
 *	\ingroup Utility
 */
HIK_EXPORT void	 HIK_API HIKNodeStatePreMultTQSdv(const HIKCharacter* pCharacter, HIKCharacterState *pCharacterState, int pNodeId, const double pT[4], const double pQ[4], const double pS[4], int pInverse);

/**	\brief Pre multiply the current translation, rotation and scale of all Nodes in the HIKCharacterState with pT, pQ and pS.
 *	\ingroup Utility
 *	\param		pCharacter			HIKCharacter to be modified.
 *	\param		pCharacterState		HIKCharacterState containing the pose to be modified by pre-rotation.
 *	\param		pT					Global translation to pre multiply.
 *	\param		pQ					Global rotation to pre multiply.
 *	\param		pS					Global scaling to pre multiply.
 *	\param		pInverse			If set to 1, the inverse pre multiplication is performed.
 */
HIK_EXPORT void	 HIK_API HIKNodeStatePreMultTQSUpfv(const HIKCharacter* pCharacter, HIKCharacterState *pCharacterState, const float pT[4], const float pQ[4], const float pS[4], int pInverse);
/**	@copydoc HIKNodeStatePreMultTQSUpfv()
 *	\ingroup Utility
 */
HIK_EXPORT void	 HIK_API HIKNodeStatePreMultTQSUpdv(const HIKCharacter* pCharacter, HIKCharacterState *pCharacterState, const double pT[4], const double pQ[4], const double pS[4], int pInverse);


/**	\ingroup EffectorSetupWrite
 *	\brief Retrieve the translation (T), quaternion rotation (Q) and scaling (S) of Effector \p pEffectorIndex for character \p pCharacter in HIKCharacterState \p pCharacterState, applying any rotation and scaling offsets contained in the character's characterization pose (its default T-stance) to the final rotation of the Effector.
 *	\param		pEffectorIndex		Unique ID of the Effector whose TQS values you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pCharacter			HIKCharacter to query.
 *	\param		pCharacterState		HIKCharacterState from which to retrieve the Effector placement.
 *	\param		pPropertyState		HIKPropertySetState containing all character properties for the character.
 *	\param[out]	pT					Stores the translation value.
 *	\param[out]	pQ					Stores the orientation value.
 *	\param[out]	pS					Stores the scaling value.
 */
HIK_EXPORT void  HIK_API HIKGetCharacterSpaceEffectorStateFromCharacterTQSfv(int pEffectorIndex,const HIKCharacter* pCharacter, const HIKCharacterState *pCharacterState, const HIKPropertySetState *pPropertyState, float pT[4], float pQ[4], float pS[4]);
/**	@copydoc HIKGetCharacterSpaceEffectorStateFromCharacterTQSfv()
 *	\ingroup Utility
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorPivotStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void  HIK_API HIKGetCharacterSpaceEffectorStateFromCharacterTQSdv(int pEffectorIndex,const HIKCharacter* pCharacter, const HIKCharacterState *pCharacterState, const HIKPropertySetState *pPropertyState, double pT[4], double pQ[4], double pS[4]);
/**	\ingroup EffectorSetupWrite
 *	\brief Retrieve the transform matrix of Effector \p pEffectorIndex for character \p pCharacter in HIKCharacterState \p pCharacterState, applying any rotation and scaling offsets contained in the character's characterization pose (its default T-stance) to the final rotation of the Effector.
 *	\param		pEffectorIndex		Unique ID of the Effector whose transform matrix you want to retrieve. See the ::HIKEffectorId enumeration for possible values.
 *	\param		pCharacter			HIKCharacter to query.
 *	\param		pCharacterState		HIKCharacterState from which to retrieve the Effector placement.
 *	\param		pPropertyState		HIKPropertySetState containing all character properties for the character.
 *	\param[out]	pXForm				Stores the transform matrix of the Effector in global space (4x4 column major matrix).
 */
HIK_EXPORT void  HIK_API HIKGetCharacterSpaceEffectorStateFromCharacterfv(int pEffectorIndex,const HIKCharacter* pCharacter, const HIKCharacterState *pCharacterState, const HIKPropertySetState *pPropertyState, float pXForm[16]);
/**	@copydoc HIKGetCharacterSpaceEffectorStateFromCharacterfv()
 *	\ingroup Utility
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorPivotStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void  HIK_API HIKGetCharacterSpaceEffectorStateFromCharacterdv(int pEffectorIndex,const HIKCharacter* pCharacter, const HIKCharacterState *pCharacterState, const HIKPropertySetState *pPropertyState, double pXForm[16]);

/**	\brief Blend the translation (T), quaternion rotation (Q), scaling (S) and IK constraints of Effector \p pEffectorId in HIKEffectorSetState \p pEffectorSetState between multiple values, each provided in a separate array.
 *
 *	\ingroup Utility1
 *	The blending between each set of values is controlled by the \p pReachTArray and \p pReachRArray parameters. The higher these values, the more the final solution will be weighted toward the corresponding set of TQS and IK constraint values.
 *	\param		pEffectorSetState	The HIKEffectorSetState containing \p pEffectorId.
 *	\param		pEffectorId			The unique ID of the Effector to be blended.
 *	\param		pT					An array that contains the different translation values to be blended for the Effector.
 *	\param		pQ					An array of quaternions that contains the different rotation values to be blended for the Effector.
 *	\param		pS					An array that contains the different scaling values to be blended for the Effector.
 *	\param		pIKPivotArray		An array of IK pivots to be blended for the Effector. You can blend TQS and IK constraint values for Effectors that do not have IK pivots by setting the values in this array to 0.0f.
 *	\param		pReachTArray		An array that controls the relative weight of the translation values provided for the Effector. 
 *	\param		pReachRArray		An array that controls the relative weight of the orientation values provided for the Effector. 
 *	\param		pPivotCount			The total number of sets of TQS and IK constraint values (i.e. the length of the \p pT, \p pQ, \p pT, \p pIKPivotArray, \p pReachTArray and \p pReachRArray parameters). 
 */
HIK_EXPORT void	 HIK_API HIKBlendEffectorPivotsTQSfv(HIKEffectorSetState *pEffectorSetState, int pEffectorId, float (*pT)[4], float (*pQ)[4], float (*pS)[4], float (*pIKPivotArray)[4], float *pReachTArray, float *pReachRArray, int pPivotCount);
/**	@copydoc HIKBlendEffectorPivotsTQSfv()
 *	\ingroup Utility
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorPivotStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKBlendEffectorPivotsTQSdv(HIKEffectorSetState *pEffectorSetState, int pEffectorId, double (*pT)[4], double (*pQ)[4], double (*pS)[4], double (*pIKPivotArray)[4], double *pReachTArray, double *pReachRArray, int pPivotCount);
/**	\brief Blend the transform matrix and IK constraints of Effector \p pEffectorId in HIKEffectorSetState \p pEffectorSetState between multiple values, each provided in a separate array.
 *
 *	\ingroup Utility1
 *	The blending between each set of values is controlled by the \p pReachTArray and \p pReachRArray parameters. The higher these values, the more the final solution will be weighted toward the corresponding transform matrix and IK constraint values.
 *	\param		pEffectorSetState	The HIKEffectorSetState containing \p pEffectorId.
 *	\param		pEffectorId			The unique ID of the Effector to be blended.
 *	\param		pXFormArray			An array that contains the different transform matrices to be blended for the Effector.
 *	\param		pIKPivotArray		An array of IK pivots to be blended for the Effector. You can blend the transform matrix and IK constraint values for Effectors that do not have IK pivots by setting the values in this array to 0.0f.
 *	\param		pReachTArray		An array that controls the relative weight of the translation values provided for the Effector. 
 *	\param		pReachRArray		An array that controls the relative weight of the orientation values provided for the Effector. 
 *	\param		pPivotCount			The total number of sets of transform matrices and IK constraint values (i.e. the length of the \p pXFormArray, \p pIKPivotArray, \p pReachTArray and \p pReachRArray parameters). 
 */
HIK_EXPORT void	 HIK_API HIKBlendEffectorPivotsfv(HIKEffectorSetState *pEffectorSetState, int pEffectorId, float (*pXFormArray)[16], float (*pIKPivotArray)[4], float *pReachTArray, float *pReachRArray, int pPivotCount);
/**	@copydoc HIKBlendEffectorPivotsfv()
 *	\ingroup Utility
 *	This function converts the double-precision numbers internally to floating-point numbers. It is intended for use only where floating-point values are unavailable. For best performance, use the HIKSetEffectorPivotStateTQSfv() function instead wherever possible.
 */
HIK_EXPORT void	 HIK_API HIKBlendEffectorPivotsdv(HIKEffectorSetState *pEffectorSetState, int pEffectorId, double (*pXFormArray)[16], double (*pIKPivotArray)[4], double *pReachTArray, double *pReachRArray, int pPivotCount);

/**	\brief Copies HIKCharacterState \p pFromState for HIKCharacter \p pFromCharacter, and pastes it into \p pOutputState for use with a different HIKCharacter.
 *
 *	\ingroup Utility
 *	\param		pCharacter		The HIKCharacter that will use the pasted HIKCharacterState.
 *	\param[out]	pOutputState	The HIKCharacterState containing the pose pasted from \p pFromState.
 *	\param		pCurrentState	The current pose of \p pCharacter.
 *	\param		pFromCharacter	The HIKCharacter corresponding to \p pFromState. 
 *	\param		pFromState		The HIKCharacterState to be pasted.
 *	\param		pFilterSet		The HIKPropertySetState corresponding to \p pCharacter.
 *	\param		pFromFilterSet	The HIKPropertySetState corresponding to \p pFromCharacter.
 *	\param		pHipsOffsetGX	The offset to apply to the hips, if any, expressed in global space.
 */
HIK_EXPORT void	 HIK_API HIKPasteState(HIKCharacter* pCharacter,	  HIKCharacterState* pOutputState, HIKCharacterState*	pCurrentState,
									  HIKCharacter* pFromCharacter, HIKCharacterState* pFromState,
									  HIKPropertySetState* pFilterSet, HIKPropertySetState* pFromFilterSet,
									  double pHipsOffsetGX[16] );

/**	\brief Reflects the pose contained in HIKCharacterState \p pFromState in a plane whose orientation is defined by \p pMirrorGQ.
 *
 *	\ingroup Utility
 *	\param		pCharacter		The HIKCharacter that will use the reflected HIKCharacterState.
 *	\param[out]	pMirrorState	The HIKCharacterState containing the pose reflected from \p pFromState.
 *	\param		pFromState		The HIKCharacterState to be reflected.
 *	\param		pFromCharacter	The HIKCharacter corresponding to \p pFromState. 
 *	\param		pMirrorGQ		The orientation of the plane of the mirror, expressed as a quaternion.
 */
HIK_EXPORT void	 HIK_API HIKMirrorState(	HIKCharacter* pCharacter, HIKCharacterState* pMirrorState, HIKCharacterState* pFromState, HIKCharacter* pFromCharacter, double pMirrorGQ[4]);


#ifdef __cplusplus
}
#endif

#endif
