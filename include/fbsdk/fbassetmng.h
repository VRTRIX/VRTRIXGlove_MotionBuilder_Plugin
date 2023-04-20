#ifndef __FBASSETMNG_H__
#define __FBASSETMNG_H__
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

/**	\file	fbassetmng.h
*	Declaration for the FBAssetMng class.
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


__FB_FORWARD( FBAssetItem );
__FB_FORWARD( FBAssetFile );
__FB_FORWARD( FBAssetFolder );
__FB_FORWARD( FBAssetMng );


////////////////////////////////////////////////////////////////////////////////////
// FBAssetItem
////////////////////////////////////////////////////////////////////////////////////

//! Base class for all managed assets.
class FBSDK_DLL FBAssetItem : public FBComponent
{
	__FBClassDeclare( FBAssetItem, FBComponent );
public:

	/** Constructor.
	*	\param	pName		Name of Command.
	*	\param	pObject		Internal parent object to own FBComponent (default is NULL).
	*/
	FBAssetItem( const char* pName, HIObject pObject=NULL );

	/** Get the name of this item (file name or folder name).
	*	\return The name of the item, as an FBString.
	*/
	virtual FBString GetName() const = 0;

	/** Get the path to this item on the local hard disk.
	*	\return The path as an \b FBString.
	*/
	virtual FBString GetLocalPath() const = 0;

	/** Get the path to this item on the database.
	*	\return The server path as an \b FBString.
	*/
	virtual FBString GetServerPath() const = 0;

	/**	Get the parent folder of this item.
	*	\return An \b FBAssetFolder* if the parent was found, or NULL if this is the root item.
	*/
	virtual FBAssetFolder* GetParent() const = 0;

	/** Obtain the latest version of the item from the server.
	*	\param	pReplaceCheckedOut	Whether to replace the checked out file or not.
	*	\param	pSilent				If pSilent is set to true, no dialog will be displayed by this method.
	*	\return A boolean indicating if the operation was successful.
	*/
	virtual bool GetLatest( bool pReplaceCheckedOut = false, bool pSilent = false ) = 0;

	/** Checks in this item and all its children (if this is a folder item).
	*	\param	pComment			Comment to be applied for the check in.
	*	\param	pKeepCheckedOut		Flag that indicates whether the item will be kept checked out.
	*	\param	pSilent				If pSilent is set to true, no dialog will be displayed by this method.
	*	\return A boolean indicating if the operation was successful.
	*/
	virtual bool CheckIn( const FBString& pComment = "", bool pKeepCheckedOut = false, bool pSilent = false ) = 0;

	/** Checks out this item and it's childs (if this is a folder item) and makes them
	*	writeable on the local disk. 
	*	\param	pComment			Comment to be applied for the check out.
	*	\param	pDontGetLocal		Indicate if local copy should retrieved or not. 
	*	\param	pSilent				If pSilent is set to true, no dialog will be displayed by this method.
	*	\return A boolean indicating if the operation was successful.
	*/
	virtual bool CheckOut( const FBString& pComment = "", bool pDontGetLocal = false, bool pSilent = false ) = 0;

	/**	Cancel the last check out operation.
	*	\param	pReplaceLocalFile	Flag indicating if the local item(s) should be replaced by the server version.
	*	\param	pSilent				If pSilent is set to true, no dialog will be displayed by this method.
	*	\return A boolean indicating if the operation was successful.
	*/
	virtual bool UndoCheckOut( bool pReplaceLocalFile = true, bool pSilent = false ) = 0;

	/** Display a dialog with this item history.
	*/
	virtual void ShowHistory() const = 0;

	/** Display a dialog showing the properties of this item.
	*/
	virtual void ShowProperties() const = 0;

	FBString					LastError;		//!<	Last error string.
};


////////////////////////////////////////////////////////////////////////////////////
// FBAssetFile
////////////////////////////////////////////////////////////////////////////////////
/**	AssetFile class registration.
*	\param	UniqueNameStr	Unique name.
*	\param	ClassName		AssetFile class name.
*	\param	Label			Short description.
*	\param	Desc			Long description.
*   \param  IconFilename    Name of the icon file to use.
*/
#define FBRegisterAssetFile( UniqueNameStr, ClassName, Label, Desc, IconFilename ) \
	HIObject RegisterAssetFile##ClassName( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName( Label ); \
	    Class->mAllocated = true; \
		Class->Name = UniqueNameStr; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName,"Asset/AssetItem/AssetFile",Label,Desc,RegisterAssetFile##ClassName, true, IconFilename );	\
	}

/**	AssetFile class declaration.
*	\param	ClassName	AssetFile class name.
*	\param	Parent		Class parent.
*/
#define FBAssetFileDeclare( ClassName, Parent  ) \
	FBClassDeclare( ClassName,Parent); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/**	AssetFile class implementation.
*	\param	ThisComponent	Class to implement.
*/
#define FBAssetFileImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBAssetFile
////////////////////////////////////////////////////////////////////////////////////

//! Class representing a file stored in a version control database.
class FBSDK_DLL FBAssetFile : public FBAssetItem
{
	__FBClassDeclare( FBAssetFile, FBAssetItem );
public:
	/** Constructor.
	*	\param	pName		Name of Command.
	*	\param	pObject		Internal parent object to own FBComponent (default is NULL).
	*/
	FBAssetFile( const char* pName, HIObject pObject=NULL );

	IObject_Declare(override);		// Interface to IObject.

	/** Open Reality Creation function.
	*	\return Outcome of creation (true/false).
	*/
	virtual bool FBCreate() override;

	/** Returns a boolean value indicating if this file is checked out by any user.
	*	\return A boolean value indicating if this node is checked out.
	*/
	virtual bool IsCheckedOut() const = 0;

	/** Returns a boolean value indicating if this file is checked out by the current user.
	*	\return A boolean value indicating if this node is checked out by the current user.
	*/
	virtual bool IsCheckedOutByMe() const = 0;

	/** Returns the name of the user who currently has this file checked out.
	*	\return The user name if the file is checked out, or an empty string if it is not.
	*/
	virtual FBString GetCheckedOutBy() const = 0;
};


////////////////////////////////////////////////////////////////////////////////////
// FBAssetFolder
////////////////////////////////////////////////////////////////////////////////////
/**	AssetFolder class registration.
*	\param	UniqueNameStr	Unique name.
*	\param	ClassName		AssetFolder class name.
*	\param	Label			Short description.
*	\param	Desc			Long description.
*   \param  IconFilename    Name of the icon file to use.
*/
#define FBRegisterAssetFolder( UniqueNameStr, ClassName, Label, Desc, IconFilename ) \
	HIObject RegisterAssetFolder##ClassName( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName( Label ); \
	    Class->mAllocated = true; \
		Class->Name = UniqueNameStr; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName,"Asset/AssetItem/AssetFolder",Label,Desc,RegisterAssetFolder##ClassName, true, IconFilename );	\
	}

/**	AssetFolder class declaration.
*	\param	ClassName	AssetFolder class name.
*	\param	Parent		Class parent.
*/
#define FBAssetFolderDeclare( ClassName, Parent  ) \
	FBClassDeclare( ClassName,Parent); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/**	AssetFolder class implementation.
*	\param	ThisComponent	Class to implement.
*/
#define FBAssetFolderImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBAssetFolder
////////////////////////////////////////////////////////////////////////////////////

//! Class representing a folder stored in a version control database.
class FBSDK_DLL FBAssetFolder : public FBAssetItem
{
	__FBClassDeclare( FBAssetFolder, FBAssetItem );
public:
	/** Constructor.
	*	\param	pName		Name of Command.
	*	\param	pObject		Internal parent object to own FBComponent (default is NULL).
	*/
	FBAssetFolder( const char* pName, HIObject pObject=NULL );

	IObject_Declare(override);		// Interface to IObject.

	/** Open Reality Creation function.
	*	\return Outcome of creation (true/false).
	*/
	virtual bool FBCreate() override;

	/** Get the number of items in this folder.
	*	\return The number of items in this folder.
	*/
	virtual int	GetChildCount() const = 0;

	/**	Get the child at index \b pIndex.
	*	\return The child at \b pIndex, or NULL if the index was out of range.
	*/
	virtual FBAssetItem* GetChild( int pIndex ) = 0;

	/** Get a file present in this folder by using it's name.
	*	\return The file with the given name, or NULL if it was not found.
	*/
	virtual FBAssetFile* GetFile( const FBString& pName ) = 0;

	/** Get a folder present in this folder by using it's name.
	*	\return The folder with the given name, or NULL if it was not found.
	*/
	virtual FBAssetFolder* GetFolder( const FBString& pName ) = 0;

	/** Add a specified file into the database. It will be added in this folder.
	*	\param pLocalPath	The full path to the file on the local disk.
	*	\param pComment		Comment to be applied for the operation.
	*	\param pCheckOut	Whether the file should be checked out or not.
	*	\param pSilent		If pSilent is set to true, no dialog will be displayed by this method.
	*	\return	An FBAssetfile* object representing the newly added file.
	*/
	virtual FBAssetFile* AddFile( const FBString& pLocalPath, const FBString& pComment = "", bool pCheckOut = false, bool pSilent = false ) = 0;

	/** Add a folder in the database. It will be added in this folder.
	*	\param pName		Name of the folder to be created.
	*	\param pComment		Comment to be applied for the operation.
	*	\param pSilent		If pSilent is set to true, no dialog will be displayed by this method.
	*	\return	An FBAssetFolder* object representing the newly added folder.
	*/
	virtual FBAssetFolder* AddFolder( const FBString& pName, const FBString& pComment = "", bool pSilent = false ) = 0;
};


////////////////////////////////////////////////////////////////////////////////////
// FBAssetMng
////////////////////////////////////////////////////////////////////////////////////
/**	Asset manager class registration.
*	\param	UniqueNameStr	Unique name.
*	\param	ClassName		Asset manager class name.
*	\param	Label			Short description.
*	\param	Desc    		Long description.
*   \param  IconFilename    Name of the icon file to use.
*/
#define FBRegisterAssetMng( UniqueNameStr, ClassName, Label, Desc, IconFilename ) \
	HIObject RegisterAssetMng##ClassName( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName( Label ); \
	    Class->mAllocated = true; \
		Class->Name = UniqueNameStr; \
		Class->Description = Desc; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName,"Asset/AssetMng",Label,Desc,RegisterAssetMng##ClassName, false, IconFilename );	\
	}

/**	Asset manager class declaration.
*	\param	ClassName	Asset manager class name.
*	\param	Parent		Class parent.
*/
#define FBAssetMngDeclare( ClassName, Parent  ) \
	FBClassDeclare( ClassName,Parent); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/**	Asset manager class implementation.
*	\param	ThisComponent	Class to implement.
*/
#define FBAssetMngImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBAssetMng
////////////////////////////////////////////////////////////////////////////////////

/** Show or hide version control menu items.
*	Let you specify which functionalities will be available from the menus.
*/
enum FBAssetMngMenuOptions		{	
	kMenuOpenFromDatabase	= 1<<0,		//!< File -> Open from database.
	kMenuAddToDatabase		= 1<<1,		//!< File -> Add to database.
	kMenuUploadToDatabase	= 1<<2,		//!< File -> Upload to database.
	kMenuGetLatest			= 1<<3,		//!< Version Control -> Get Latest.
	kMenuCheckIn			= 1<<4,		//!< Version Control -> Check In.
	kMenuCheckOut			= 1<<5,		//!< Version Control ->	Check Out.
	kMenuUndoCheckOut		= 1<<6,		//!< Version Control ->	Undo Check Out.
	kMenuShowHistory		= 1<<7,		//!< Version Control -> Show History.
	kMenuShowProperties		= 1<<8,		//!< Version Control ->	Show Properties.
	kMenuShowExplorer		= 1<<9,		//!< Version Control -> Show Explorer.
	kMenuShowReferenceMng	= 1<<10,	//!< Version Control -> Show Reference Manager.
	kMenuShowSettings		= 1<<11,	//!< Version Control ->	Show Settings.
	kMenuEnable				= 1<<12,	//!< Version Control -> Disable Version Control Integration.

	//! Support all elements from the File menu.
	kMenuFileAll			= kMenuOpenFromDatabase | kMenuAddToDatabase | kMenuUploadToDatabase,

	//! Support all elements from the Version Control menu.
	kMenuSourceControlAll	= kMenuGetLatest | kMenuCheckIn | kMenuCheckOut | kMenuUndoCheckOut |
							  kMenuShowHistory | kMenuShowProperties | kMenuShowExplorer |
							  kMenuShowReferenceMng | kMenuShowSettings | kMenuEnable,

	//! Support only the basics functionalities.
	kMenuSourceControlMin	=  kMenuGetLatest | kMenuCheckIn | kMenuCheckOut | kMenuUndoCheckOut |
							   kMenuShowSettings | kMenuEnable,

	//! Support everything.
	kMenuAll				= 0xFFFFFFFF
};


/** Behavior of the application when working with managed files.
*/
enum FBAssetMngFileOptions	{
	kFileCheckOutOnLoad		= 1<<0,		//!< Check out file automatically on load.
	kFileCheckOutOnLoad_Ask	= 1<<1,		//!< Ask for checkout on load.
	kFileUploadOnSave		= 1<<2,		//!< Upload file automatically on save.
	kFileUploadOnSave_Ask	= 1<<3,		//!< Ask for upload on save.
	kFileAddOnNewSave		= 1<<4,		//!< Add new file automatically on save.
	kFileAddOnNewSave_Ask	= 1<<5,		//!< Ask for adding new file on save.
	kFileCheckInOnClose		= 1<<6,		//!< Check in file automatically when closing it.
	kFileCheckInOnClose_Ask	= 1<<7,		//!< Ask for check in file when closing it.
	kFileOptionsAll			= 0xFFFFFFFF
};


FB_DEFINE_COMPONENT( FBSDK_DLL, AssetMng );

/** Used to access asset manager functionity to get files locally or from a server.
*/
class FBSDK_DLL FBAssetMng : public FBComponent {
	__FBClassDeclare( FBAssetMng, FBComponent );
public:
	/** Constructor.
	*	\param	pName		Name of Command.
	*	\param	pObject		Internal parent object to own FBComponent (default is NULL).
	*/
	FBAssetMng( const char* pName, HIObject pObject=NULL );

	IObject_Declare(override);		// Interface to IObject.

	/** Initialize the connection to the server.
	*	\return \b True if the connection was established, \b false otherwise.
	*/
	virtual bool Initialize() = 0;

	/** Let the user browse the asset database to select a file.
	*	\return A file object representing the file that was selected, or NULL if none.
	*/
	virtual FBAssetFile* BrowseForFile() = 0;

	/** Let the user browse the asset database to select a folder.
	*	\return A FBAssetFolder* object representing the folder that was selected, or NULL if none.
	*/
	virtual FBAssetFolder* BrowseForFolder() = 0;

	/** Create a folder path on the server side by adding each missing folders.
	*	\param pServerPath	The path to create on the server side.
	*	\return A FBAssetFolder* object representing the deepest folder of the path.
	*/
	virtual FBAssetFolder* CreateServerPath( const FBString& pServerPath ) = 0;
	
	/** Is the specified local file managed (ie. also present in the database).
	*	\param pFilename	Path to the file on the local disk.
	*	\return A boolean indicating if the file is managed or not.
	*/
	virtual bool FileIsManaged( const FBString& pFilename ) = 0;
	
	/** Is the specified local path below a managed path.
	*	\param pLocalPath	Local path to be checked.
	*	\return A boolean indicating if the path is within a managed path or not.
	*/
	virtual bool WithinManagedPath( const FBString& pLocalPath ) = 0;
	
	/** Convert the local path to a server path by using managed paths mapping.
	*	\param pLocalPath	Local path to be mapped.
	*	\return A string with the resulting server path, will be empty if the mapping fail.
	*/
	virtual FBString MapLocalPathToServerPath( const FBString& pLocalPath ) = 0;

	/** Get a file object using it's server path.
	*	\param pServerFilename	Path to the file on the server.
	*	\return An FBAssetFile* object, or NULL if the file was not found.
	*/
	virtual FBAssetFile* GetAssetFile( const FBString& pServerFilename ) = 0;
	
	/** Get a file object using it's local path.
	*	\param pLocalFilename	Path to the file on the local disk.
	*	\return An FBAssetFile* object, or NULL if the file was not found or no mapping could be done.
	*/
	virtual FBAssetFile* GetAssetFileFromLocalPath( const FBString& pLocalFilename ) = 0;

	/** Get a folder object using it's server path.
	*	\param pServerPath		Path the the folder on the server.
	*	\return An FBAssetFolder* object, or NULL if the folder was not found.
	*/
	virtual FBAssetFolder* GetAssetFolder( const FBString& pServerPath ) = 0;
	
	/** Get a folder object using it's local path.
	*	\param pLocalPath		Path to the folder on the local disk.
	*	\return An FBAssetFolder* object, or NULL if the folder was not found or no mapping could be done.
	*/
	virtual FBAssetFolder* GetAssetFolderFromLocalPath( const FBString& pLocalPath ) = 0;

	/** Display a dialog that let the user changes settings.
	*/
	virtual void ShowSettings() = 0;

	/** Get the file options (i.e. what to do when loading, saving or closing managed files).
	*	\return The options.
	*/
	virtual int GetFileOptions() = 0;

	/** Check if this manager can be used on the computer.
	*/
	virtual bool CheckAvailability() const = 0;
	
	FBPropertyString			Name;			//!< <b>Read Write Property:</b> Unique Name.
	FBPropertyString			Description;	//!< <b>Read Write Property:</b> Description of the manager.
	FBPropertyInt				MenuFlags;		//!< <b>Read Write Property:</b> Flags specifing which menu items are added by the manager.
	FBString					LastError;		//!< Last error string.
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif	/* __FBASSETMNG_H__	*/
