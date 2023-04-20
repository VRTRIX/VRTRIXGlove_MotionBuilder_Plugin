/*!	\file hiklod.h
 *	\brief Header file for low-LoD solvers.
 *
 *	This file contains versions of the HumanIK inverse kinematics and retargeting solvers that function
 *	at a lower level of detail for increased performance. See also ~{ Solving at a Lower Level of Detail }~.
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

#ifndef _HIKLOD_
#define _HIKLOD_

#include "humanik.h"
#include "hikproperty.h"

#ifdef __cplusplus
extern "C" {
#endif

// ***********************************************
/**	\defgroup IKLOD Low-LoD Full-Body IK
 *	\ingroup IK
 *	\brief This page details the functions used to perform full-body IK solving for a character with a low level of detail. 
 *
 *	See also ~{ Solving at a Lower Level of Detail }~.
 */

/**	\ingroup IKLOD
 *	\brief Prepare the solving for character \p pCharacter.
 *
 *	\param			pCharacter			HIKCharacter to solve.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose of the character, which will influence the IK solution.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the target positions, orientations, and constraints for the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties to be used by the solver.
 */
HIK_EXPORT void  HIK_API HIKSolveForEffectorSetBeginLowLOD(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IKLOD
 *	\brief Call only the pull engine for character \p pCharacter.
 *
 *	\param			pCharacter			HIKCharacter to solve.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose of the character, which will influence the IK solution.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the target positions, orientations, and constraints for the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties to be used by the solver.
 */
HIK_EXPORT void  HIK_API HIKSolveForEffectorSetBodyPullLowLOD(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IKLOD
 *	\brief Call the IK solver for the arms, legs and shoulders of character \p pCharacter.
 *
 *	\param			pCharacter			HIKCharacter to solve.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose of the character, which will influence the IK solution.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the target positions, orientations, and constraints for the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties to be used by the solver.
 */
HIK_EXPORT void	 HIK_API HIKSolveForEffectorSetArmsAndLegsLowLOD(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, const HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/**	\ingroup IKLOD
 *	\brief Solve character \p pCharacter with HIKEffectorSetState \p pEffectorSetState and HIKCharacterState \p pCharacterState, result will be in \p pCharacterState.
 *
 *	You can enable/disable solvers by setting solving step in the HIKEffectorSetState \p pEffectorSetState with a function call to HIKSetIKSolvingStep().
 *
 *	\param			pCharacter			HIKCharacter to solve.
 *	\param[in,out]	pCharacterState		HIKCharacterState containing the initial FK pose of the character, which will influence the IK solution.
 *	\param			pEffectorSetState	HIKEffectorSetState containing the target positions, orientations, and constraints for the IK solution.
 *	\param			pPropertyState		HIKPropertySetState containing all character properties to be used by the solver.
 */
HIK_EXPORT void  HIK_API HIKSolveForEffectorSetLowLOD(const HIKCharacter *pCharacter, HIKCharacterState *pCharacterState, HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pPropertyState);

/* *********************************************** */
/**	\defgroup RetargeterLOD Low-LoD Retargeting
 *	\ingroup Retargeter
 *	\brief This page details the functions used to perform a retargeting for a character with a low level of detail.
 *
 *	See also ~{ Solving at a Lower Level of Detail }~.
 */

/**	\ingroup RetargeterLOD
 *	\brief Retarget the pose defined by HIKCharacterState \p pSrcCharacterState from character \p pSrcCharacter to character \p pDstCharacter, saving the result in HIKCharacterState \p pCharacterState.
 *
 *	After retargeting the source character to the destination character, this function calls HIKSolveForEffectorSetLowLOD() to perform an IK pass. 
 *
 *	\param		pDstCharacter			Destination character.
 *	\param[out]	pCharacterState			HIKCharacterState for the destination character. This HIKCharacterState holds the final solution generated by the retargeting solver.
 *	\param		pSrcCharacter			Source character.
 *	\param		pSrcCharacterState		HIKCharacterState the solver retargets from the source character to the destination character.
 *	\param		pEffectorSetState		HIKEffectorSetState used for the full-body IK pass, if at least one solving step is set in this HIKEffectorSetState. See HIKSetIKSolvingStep().
 *	\param		pDstPropertyState		HIKPropertySetState containing all character properties to be used by the solver for the destination character.
 *	\param		pSrcPropertyState		HIKPropertySetState for the source character. This state is only used if you have enabled the ::HIKSolvingStepContact solving step in your HIKEffectorSetState. If so, the property ::HIKFootBottomToAnkleId
 *										is read from this HIKPropertySetState to define the height of the source character's ankles. This value is used to adapt the height of the poses generated for the destination character.
 */
HIK_EXPORT void	 HIK_API HIKSolveForCharacterLowLOD(const HIKCharacter *pDstCharacter, HIKCharacterState *pCharacterState, const HIKCharacter *pSrcCharacter, const HIKCharacterState *pSrcCharacterState, HIKEffectorSetState *pEffectorSetState, const HIKPropertySetState *pDstPropertyState, const HIKPropertySetState *pSrcPropertyState);


#ifdef __cplusplus
}
#endif

#endif
