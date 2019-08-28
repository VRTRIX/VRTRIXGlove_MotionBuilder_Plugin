#ifndef __FBMOTIONCLIP_H__
#define __FBMOTIONCLIP_H__
/**************************************************************************
 Copyright (c) 2009 - 2010 Autodesk, Inc. and/or its licensors.
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

/**	\file fbmotion.h
*	Motion interface for FBSDK
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
#endif

__FB_FORWARD( FBMotionClip );

FB_DEFINE_COMPONENT( FBSDK_DLL, MotionClip );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBMotionClip
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Motion class.
*	Properties of this class are work in progress, but you can still list them and get their names.
*/
class FBSDK_DLL FBMotionClip : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBMotionClip, FBComponent);
public:

	/**	Constructor.
	*	\param	pFileName			The complete file path of the media file to access.
	*	\param	pObject				For internal use only.
	*/
	FBMotionClip(const char* pFileName, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	FBPropertyString		Filename;		//!< <b>Read Write Property:</b> Filename and path of motion file.
	FBPropertyString		RelativePath;	//!< <b>Read Only Property:</b> Relative path to the motion file.
	FBPropertyTime			Start;			//!< <b>Read Only Property:</b> Start time of clip.
	FBPropertyTime			Stop;			//!< <b>Read Only Property:</b> Stop time of clip.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! <b>List:</b> MotionClip
class FBSDK_DLL FBPropertyListMotionClip : public FBPropertyListComponent
{
public:
	FBPropertyListMotionClip();
	/**	Get the motion at \e pIndex.
	*	\param	pIndex	Index of motion to get.
	*	\return Motion at \e pIndex.
	*/
	FBMotionClip* operator[](int pIndex);
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
