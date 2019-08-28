#ifndef __FBACTIONMANAGER_H__
#define __FBACTIONMANAGER_H__
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

/**	\file fbActionmanager.h
*	
*	The FBActionManager file contains the necessary declarations to 
*	interface with the underlying actions regarding input devices.
*/

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
#endif //FBSDKUseNamespace

FB_FORWARD( FBActionManager );
FB_DEFINE_COMPONENT( FBSDK_DLL, FBActionManager );

/** Action Manager class.
*   <b>This class is introduced to enable users to access to the actions related functions. 
*   between versions.</b>
*/
class FBSDK_DLL FBActionManager: public FBComponent
{
    FBClassDeclare( FBActionManager, FBComponent );

public:
    /** Constructor.
    */
    FBActionManager();

public:
    /** Returns the current selected interaction mode.
    * \return the current selected interaction mode in string
    */
    const char* GetCurrentInteractionMode();

    /** Set the the current selected interaction mode.
    * \param pMode the interaction mode to be selected. If pMode is not in the list of interaction modes, this function will choose "MotionBuilder" as default.
    */
    void SetCurrentInteractionMode( const char *pMode );

    /** Returns the only instance of FBActionManager.
    * \return the only instance of FBActionManager
    */
    static FBActionManager& TheOne();
};

#ifdef FBSDKUseNamespace
}
#endif //FBSDKUseNamespace

#endif //__FBACTIONMANAGER_H__