/*!	\file hikvalidation.h
*	\brief Header file for validating character definitions and geometry.
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

#ifndef HIKVALIDATION_H
#define HIKVALIDATION_H

#include "humanik.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! @defgroup CharacterValidation Character Validation
	\brief Contains functions that validate character definitions and character geometry. */

/*! The number of required Nodes for an HIKCharacter.
		\ingroup CharacterValidation */
#define HIKRequiredBoneCount 15
/*! The maximum number of possible Nodes in a character's spine.
		\ingroup CharacterValidation */
#define HIKSpineBoneCount 9
/*! The maximum number of possible Nodes in a character's neck.
		\ingroup CharacterValidation */
#define HIKNeckBoneCount 9
/*! The maximum number of possible roll Nodes in a character's arms and legs.
		\ingroup CharacterValidation */
#define HIKRollBoneCount 8
	/*! Returns a list of integers that identify which Nodes in the #HIKNodeId enumeration are required.
		The length of the array should always be equal to #HIKRequiredBoneCount.
		\ingroup CharacterValidation */
	const int* HIKGetRequiredBoneList();

	/*! Returns a list of integers that identify which Nodes in the #HIKNodeId enumeration are part of the spine.
		The length of the array should always be equal to #HIKSpineBoneCount.
		\ingroup CharacterValidation */
	const int* HIKGetSpineBoneList();

	/*! Returns a list of integers that identify which Nodes in the #HIKNodeId enumeration are part of the neck.
		The length of the array should always be equal to #HIKNeckBoneCount.
		\ingroup CharacterValidation */
	const int* HIKGetNeckBoneList();

	/*! Returns a list of integers that identify which Nodes in the #HIKNodeId enumeration are roll Nodes.
		The length of the array should always be equal to #HIKNeckBoneCount.
		\ingroup CharacterValidation */
	const int* HIKGetRollBoneList();
	
	/*! Validates that the specified HIKCharacterDefinition contains all required Nodes.
	 *	If one or more Nodes are missing, the function returns \c false and updates the \c pErrorMsg
	 *	to list the missing Nodes.
	 *	\param pCharacterDefinition		The HIKCharacterDefinition to test.
	 *	\param[out] pErrorMsg			Updated to list all missing Nodes not found in the definition.
	 *	\param[out] pErrorMsgSize		Updated to indicate the number of characters in the \c pErrorMsg string.
	 *	\return \c false if at least one required Node is missing in the character definition, or \c true otherwise.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateRequiredBone(const HIKCharacterDefinition *pCharacterDefinition, char* pErrorMsg = 0, unsigned int pErrorMsgSize = 0);

	/*! Validates that the spine of the specified HIKCharacterDefinition does not have any missing Nodes. For example,
	 *	a character can not be created with #Spine3NodeId unless it also has #Spine2NodeId and #Spine1NodeId.
	 *	If one or more Nodes in the spine are missing, the function returns \c false and updates the \c pErrorMsg
	 *	to list the missing Nodes.
	 *	\param pCharacterDefinition		The HIKCharacterDefinition to test.
	 *	\param[out] pErrorMsg			Updated to list all missing spine Nodes not found in the definition.
	 *	\param[out] pErrorMsgSize		Updated to indicate the number of characters in the \c pErrorMsg string.
	 *	\return \c false if at least one spine Node is missing in the character definition, or \c true otherwise.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateSpine(const HIKCharacterDefinition *pCharacterDefinition, char* pErrorMsg = 0, unsigned int pErrorMsgSize = 0);

	/*! Validates that the neck of the specified HIKCharacterDefinition does not have any missing Nodes. For example,
	 *	a character can not be created with #Neck3NodeId unless it also has #Neck2NodeId and #Neck1NodeId.
	 *	If one or more Nodes in the nech are missing, the function returns \c false and updates the \c pErrorMsg
	 *	to list the missing Nodes.
	 *	\param pCharacterDefinition		The HIKCharacterDefinition to test.
	 *	\param[out] pErrorMsg			Updated to list all missing neck Nodes not found in the definition.
	 *	\param[out] pErrorMsgSize		Updated to indicate the number of characters in the \c pErrorMsg string.
	 *	\return \c false if at least one neck Node is missing in the character definition, or \c true otherwise.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateNeck(const HIKCharacterDefinition *pCharacterDefinition, char* pErrorMsg = 0, unsigned int pErrorMsgSize = 0);

	/*! Validates that the hips of the specified HIKCharacter are aligned along the X axis. If the alignment of the
	 *	hips is too far off, the function returns \c false and updates the \c pErrorMsg to indicate the problem.
	 *	\param pCharacter				The HIKCharacter to test.
	 *	\param[out] pErrorMsg			Updated to indicate any errors detected with the character geometry.
	 *	\param[out] pErrorMsgSize		Updated to indicate the number of characters in the \c pErrorMsg string.
	 *	\return \c false if the alignment of the hips is too far off the X axis, or \c true otherwise.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateHipsXAxis(const HIKCharacter *pCharacter, char* pErrorMsg = 0, unsigned int pErrorMsgSize = 0);

	/*! Validates that the arms of the specified HIKCharacter are aligned along the X axis. If the alignment of the
	 *	arms is too far off, the function returns \c false and updates the \c pErrorMsg to indicate the problem.
	 *	\param pCharacter				The HIKCharacter to test.
	 *	\param[out] pErrorMsg			Updated to indicate any errors detected with the character geometry.
	 *	\param[out] pErrorMsgSize		Updated to indicate the number of characters in the \c pErrorMsg string.
	 *	\return \c false if the alignment of the arms is too far off the X axis, or \c true otherwise.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateArmsXAxis(const HIKCharacter *pCharacter, char* pErrorMsg = 0, unsigned int pErrorMsgSize = 0);

	/*! Validates that the spine of the specified HIKCharacter is aligned along the Y axis. If the alignment of the
	 *	spine is too far off, the function returns \c false and updates the \c pErrorMsg to indicate the problem.
	 *	\param pCharacter				The HIKCharacter to test.
	 *	\param[out] pErrorMsg			Updated to indicate any errors detected with the character geometry.
	 *	\param[out] pErrorMsgSize		Updated to indicate the number of characters in the \c pErrorMsg string.
	 *	\return \c false if the alignment of the spine is too far off the Y axis, or \c true otherwise.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateSpineYAxis(const HIKCharacter *pCharacter, char* pErrorMsg = 0, unsigned int pErrorMsgSize = 0);

	/*! Validates that no two Nodes are set at the same position in 3D space. If two Nodes are found at the same
	 *	position, the function returns \c false and updates the \c pErrorMsg to indicate the problem.
	 *	\param pCharacter				The HIKCharacter to test.
	 *	\param[out] pErrorMsg			Updated to indicate any errors detected with the character geometry.
	 *	\param[out] pErrorMsgSize		Updated to indicate the number of characters in the \c pErrorMsg string.
	 *	\return \c false if two or more Nodes are at the same position, or \c true otherwise.
	 *	\ingroup CharacterValidation
	 */
	bool HIKValidateBonePosition(const HIKCharacter *pCharacter, char* pErrorMsg = 0, unsigned int pErrorMsgSize = 0);

	/*! Returns \c true if the specified Node index corresponds to a roll bone in an arm or leg. */
	bool HIKIsRollBone(int id);

#ifdef __cplusplus
}
#endif

#endif