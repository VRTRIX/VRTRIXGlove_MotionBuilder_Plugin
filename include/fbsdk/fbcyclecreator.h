#ifndef __FBCYCLECREATOR_H__
#define __FBCYCLECREATOR_H__
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

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

FB_DEFINE_COMPONENT( FBSDK_DLL, CycleCreator );



    ///////////////////////////////////////////////////////////////////////////////////
    // FBCycleCreator
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBCycleCreator );

    class FBSDK_DLL FBCycleCreator : public FBComponent
    {
        __FBClassDeclare( FBCycleCreator, FBComponent );

    public:
        /**	Constructor.
        *	\param	pObject		Internal parent object(default=NULL).
        */
        FBCycleCreator( HIObject pObject = NULL );

        /**	Get the global object for this class
        *	\return	the global object.
        */
        static FBCycleCreator& TheOne();

        /**	Create animation cycle for current character if pChar is
        *   NULL, else for the character assigned by pChar; during 
        *   the time scope between pStartTime and pEndTime.
        *   \param pStartTime Start time of the cycle
        *   \param pEndTime End time of the cycle
        *   \param pChar Target character, if it is NULL, try to use current character
        *   \param pMoveStartToZero Whether move start time to zero time
        *   \param pAddZeroKey Whether add zero key
        *   \param pNewTakeName The name used to create the new take.
        *   \param pReferencedIK The IK that used as referenced object in pose pasting.
        *   \param pPasteTx Whether consider Translation X on referenced IK when doing pose pasting
        *   \param pPasteTy Whether consider Translation Y on referenced IK when doing pose pasting
        *   \param pPasteTz Whether consider Translation Z on referenced IK when doing pose pasting
        *   \param pPasteR Whether consider Rotation on referenced IK when doing pose pasting
        *   \param pPasteG Whether respect Gravity when doing pose pasting (Translation = Global XZ / Rotation = Global Y).  Note: if G is true then Ty will be forced changed to false.
        *   \return true if successful.
        */
        bool CreateCycle(   FBTime pStartTime, 
                            FBTime pEndTime,
                            FBCharacter* pChar = NULL, 
                            bool pMoveStartToZero = false,
                            bool pAddZeroKey = true, 
                            const char* pNewTakeName = "", 
                            FBModel* pReferencedIK = NULL, 
                            bool pPasteTx = true, 
                            bool pPasteTy = false,
                            bool pPasteTz = true, 
                            bool pPasteR = true,
                            bool pPasteG = true );
    };




#ifdef FBSDKUseNamespace
};
#endif

#endif


