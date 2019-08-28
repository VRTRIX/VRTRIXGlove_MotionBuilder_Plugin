#ifndef __FBCOMMAND_H__
#define __FBCOMMAND_H__
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

/**	\file	fbcommand.h
*	Declaration for the FBCommand class.
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

////////////////////////////////////////////////////////////////////////////////////
// FBCommand
////////////////////////////////////////////////////////////////////////////////////
/**	Command class registration.
*	\param	UniqueNameStr	Unique name.
*	\param	ClassName		Command class name.
*	\param	Label			Short description.
*	\param	Description		Long description.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterCommand( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
	HIObject RegisterCommand##ClassName( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
		ClassName *Class = new ClassName( Label ); \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName##R1,"Commands",Label,Description,RegisterCommand##ClassName, true, IconFilename );						\
		FBRegisterObject( ClassName##R2,"FbxStorable/Command",UniqueNameStr,Description,RegisterCommand##ClassName, true, IconFilename );	\
		FBRegisterObject( ClassName##R3,"Browsing/Templates/Commands",Label,Description,RegisterCommand##ClassName, true, "object_command.tif" );	\
	}	\

/**	Command class declaration.
*	\param	ClassName	Command class name.
*	\param	Parent		Parent class.
*/
#define FBCommandDeclare( ClassName, Parent  ) \
	FBClassDeclare( ClassName,Parent); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/**	Command class implementation.
*	\param	ThisComponent	Class to implement.
*/
#define FBCommandImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBCommand
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCommand );

/** FBCommandState */
enum FBCommandState		{	
	kFBCommandStateStandard,			//!< Standard.				
	kFBCommandStateMute,				//!< Mute.					
	kFBCommandStateSolo,				//!< Solo.					
	kFBCommandStateMuteBecauseSolo		//!< Mute because of solo.	
};

/** FBCommandState */
enum FBTimeReferential {
	kFBTimeReferentialAction, //!< Action
	kFBTimeReferentialShot,//!< Shot
	kFBTimeReferentialEdit,//!< Edit
};


FB_DEFINE_ENUM		( FBSDK_DLL, CommandState );
FB_DEFINE_ENUM		( FBSDK_DLL, TimeReferential );
FB_DEFINE_COMPONENT	( FBSDK_DLL, Command );

//! Command class.
class FBSDK_DLL FBCommand : public FBComponent {
	__FBClassDeclare( FBCommand, FBComponent );
public:
	/** Constructor.
	*	\param	pName		Name of Command (default is NULL).
	*	\param	pObject		Internal parent object to own FBComponent (default is NULL).
	*/
	FBCommand(const char* pName = NULL, HIObject pObject = NULL);

	IObject_Declare(K_IMPLEMENTATION);		// Interface to IObject.

	//@{
	/** Storage/Retrieval of information into the FBX file format.
	*	\param	pFbxObject	Object to interface with FBX file format.
	*	\param	pStoreWhat	Attributes to store in FBX file.
	*/
	virtual bool	FbxStore	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
	virtual bool	FbxRetrieve	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
	//@}

	//!	Execute the command.
	virtual	void	ExecuteNotify();

	//!	Clear the command from the dropped items.
	virtual void	DragAndDropClearNotify();

	/** Add an item with drag and drop.
	*	\param	pComponent	Item to add.
	*/
	virtual void	DragAndDropAddNotify( FBComponent* pComponent );

	/** Remove an item that was added with drag and drop.
	*	\param	pComponent	Item to Remove.
	*/
	virtual void RemoveNotify(HIObject pComponent);

	FBPropertyString		Description;		//!< <b>Property:</b> Command description.
	FBPropertyTime			StartTime;			//!< <b>Property:</b> Start time for the command.
	FBPropertyTime			StopTime;			//!< <b>Property:</b> Stop time for the command.
	FBPropertyCommandState	State;				//!< <b>Property:</b> Current state of the command.
	FBPropertyTimeReferential	TimeReferential;	//!< <b>Property:</b> What is the time referential of the command?
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif	/* __FBCOMMAND_H	*/
