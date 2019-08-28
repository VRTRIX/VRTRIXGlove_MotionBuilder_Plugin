#ifndef __FBMANIPULATORLAYOUT_H__
#define __FBMANIPULATORLAYOUT_H__
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

/**	\file fbmanipulatorlayout.h
*	FBManipulator layout file.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

// Core includes
#include <fbsdk/fbmanipulator.h>

// UI includes
#include <fbcontrols/fbcontrols.h>

// Namespace declaration
#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

/** Register a Manipulator layout class
*	\param	ClassName		Name of Manipulator layout class.
*	\param	UniqueNameStr	Unique name of class.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterManipulatorLayout( ClassName,UniqueNameStr, IconFilename ) \
	HIObject RegisterManipulatorLayout##ClassName( HIObject /*pOwner*/,const char * /*pName*/,void *pData) \
	{\
		ClassName *Class = new ClassName( (FBManipulator*)FBGetFBObject((HIObject)pData) ); \
		Class->mAllocated = true; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName,"UI_Associated_ClassName",UniqueNameStr,UniqueNameStr" Manipulator Layout",RegisterManipulatorLayout##ClassName, true, IconFilename );	\
	}

/**	Manipulator layout declaration.
*	\param	ClassName	Name of Manipulator layout class.
*	\param	Parent		Parent of Manipulator layout class. 
*/
#define FBManipulatorLayoutDeclare( ClassName,Parent ) \
	FBClassDeclare( ClassName,Parent ); \
  public: \
    ClassName(FBManipulator* pManipulator):Parent(pManipulator) { FBClassInit; } \
  private:

/** Manipulator layout implementation.
*	\param	ThisComponent	Name of Manipulator layout class to implement.
*/
#define FBManipulatorLayoutImplementation( ThisComponent ) \
	FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// Manipulator layout.
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBManipulatorLayout );

//! Manipulator layout class.
class FBSDK_DLL FBManipulatorLayout : public FBLayout 
{
	__FBClassDeclare( FBManipulatorLayout, FBLayout );

public:
	/**	Constructor.
	*	\param pManipulator Manipulator to association with Manipulator layout.
	*/
	FBManipulatorLayout( FBManipulator* pManipulator = NULL );

	FBPropertyInt		StartSize	[2];	//!< Starting Size. This is the initial size when the manipulator is opened. (0:Width, 1:Height. Default = 800x400)
	FBPropertyInt		MaxSize		[2];	//!< Maximum Size (Disabled in this version). A value of -1 means no maximum size. (0:Width, 1:Height. Default = -1x-1)
	FBPropertyInt		MinSize		[2];	//!< Minimum Size. A value of -1 means no minimum value. (0:Width, 1:Height. Default = 140x-1).

	FBPropertyManipulator	Manipulator;	//!< \b Property: Manipulator.
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif
