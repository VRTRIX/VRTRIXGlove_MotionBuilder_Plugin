#ifndef __FBCONSTRAINTLAYOUT_H__
#define __FBCONSTRAINTLAYOUT_H__
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

/**	\file fbconstraintlayout.h
*	FBConstraint layout file.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

// Core includes
#include <fbsdk/fbconstraint.h>	// FBPropertyConstraint

// UI includes
#include <fbcontrols/fbcontrols.h>

// Namespace declaration
#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

/** Register a Constraint layout class
*	\param	ClassName		Name of Constraint layout class.
*	\param	UniqueNameStr	Unique name of class.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterConstraintLayout( ClassName,UniqueNameStr, IconFilename ) \
	HIObject RegisterConstraintLayout##ClassName( HIObject /*pOwner*/,const char * /*pName*/,void *pData) \
	{\
		ClassName *Class = new ClassName( (FBConstraint*)FBGetFBObject((HIObject)pData) ); \
		Class->mAllocated = true; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	\
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName,"UI_Associated_ClassName",UniqueNameStr,UniqueNameStr" Constraint Layout",RegisterConstraintLayout##ClassName, true, IconFilename );	\
	}

/**	Constraint layout declaration.
*	\param	ClassName	Name of Constraint layout class.
*	\param	Parent		Parent of Constraint layout class. 
*/
#define FBConstraintLayoutDeclare( ClassName,Parent ) \
	FBClassDeclare( ClassName,Parent ); \
  public: \
    ClassName(FBConstraint* pConstraint):Parent(pConstraint) { FBClassInit; } \
  private:

/** Constraint layout implementation.
*	\param	ThisComponent	Name of Constraint layout class to implement.
*/
#define FBConstraintLayoutImplementation( ThisComponent ) \
	FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBConstraint
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBConstraintLayout );

//! Constraint layout class.
class FBSDK_DLL FBConstraintLayout : public FBLayout 
{
	__FBClassDeclare( FBConstraintLayout,FBLayout );

public:
	/**	Constructor.
	*	\param pConstraint Constraint to association with Constraint layout.
	*/
	FBConstraintLayout( FBConstraint* pConstraint = NULL );

	FBPropertyConstraint	Constraint;		//!< <b>Property:</b> Constraint.
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif
