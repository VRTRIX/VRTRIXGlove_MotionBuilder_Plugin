#ifndef __FBNOTE_H__
#define __FBNOTE_H__
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

/** \file fbnote.h
*	Access to notes.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcore.h>
#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif


__FB_FORWARD( FBNote );

////////////////////////////////////////////////////////////////////////////////////
// FBNote
////////////////////////////////////////////////////////////////////////////////////

//! Note class.
class FBSDK_DLL FBNote : public FBBox 
{
	__FBClassDeclare( FBNote, FBBox );

public:
	/**	Constructor.
	*	\param	pName		Name of note.
	*	\param	pObject 	For internal use only(default=NULL).
	*/
	FBNote( const char *pName, HIObject pObject = NULL );

    IQuery_Declare(override);

    /** Attach the note to a component.
    *   Will attach the note to the component.  If \b pComp is NULL, 
    *   the note will only be added to the scene.
    *   \param  pComp   Component on which to attach note.
    *   \return A boolean indicating if the operation was successful or not.
    */
	virtual bool Attach( FBComponent* pComp = NULL );

    /** Detach the note from a component.
    *   Will detach the note from the component.  If \b pComp is NULL, 
    *   the note will be removed from the scene and detached from all
    *   components.
    *   \param  pComp   Component from which to detach note.
    *   \return A boolean indicating if the operation was successful or not.
    */
    virtual bool Detach( FBComponent* pComp = NULL );

public:
    FBPropertyString            StaticComment;      //!< <b>Read Write Property:</b> Comment associated to this note.
};

FB_DEFINE_COMPONENT( FBSDK_DLL, Note );


////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListNote
////////////////////////////////////////////////////////////////////////////////////
//! <b>List:</b> Note
class FBSDK_DLL FBPropertyListNote : public FBPropertyListComponent
{
public:
	FBPropertyListNote();
	/**	Get the note at \e pIndex.
	*	\param	pIndex	Index of note to get.
	*	\return Note at \e pIndex.
	*/
	FBNote* operator[](int pIndex);
};

FB_DEFINE_LIST( FBSDK_DLL, Note );

#ifdef FBSDKUseNamespace
	}
#endif
#endif
