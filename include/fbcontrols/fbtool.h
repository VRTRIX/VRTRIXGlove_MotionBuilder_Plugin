#ifndef __FBTOOL_H__
#define __FBTOOL_H__
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

/**	\file	fbtool.h
*	Declaration for the FBTool class.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbcontrols/fbcontrols.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {;
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBTool
////////////////////////////////////////////////////////////////////////////////////
/**	Register a tool
*	\param	ClassName		Name of tool class to register.
*	\param	Label			Short description of tool.
*	\param	Description		Long description of tool.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterTool( ClassName, Label, Description, IconFilename ) \
    static HIObject RegisterTool##ClassName( HIObject pOwner,const char* pName,void * pData) \
{\
    ClassName *Class = new ClassName( Label ); \
    Class->mAllocated = true; \
    if( Class->FBCreate() )	{\
    return Class->GetHIObject(); \
    } else { \
    delete Class; \
    return NULL; \
    } \
} \
    FBLibraryModule( ClassName )	\
{	\
    FBRegisterObject( ClassName,"UI/Tools",Label,Description,RegisterTool##ClassName, false, IconFilename );\
}

/**	Tool class declaration.
*	\param	ClassName	Name of tool class to declare.
*	\param	Parent		Name of tool class parent class.
*/
#define FBToolDeclare( ClassName,Parent ) \
    FBClassDeclare( ClassName,Parent ); \
public: \
    ClassName(const char *pName=NULL):Parent(pName) { FBClassInit; } \
private:

/**	Tool class implementation.
*	\param	ThisComponent	Tool class to implement.
*/
#define FBToolImplementation( ThisComponent ) \
    FBClassImplementation( ThisComponent )

FB_FORWARD( FBFbxObject );
__FB_FORWARD( FBTool );

enum FBToolPossibleDockPosition
{
    kFBToolPossibleDockPosNone = 0,	
    kFBToolPossibleDockPosTop = (1 << 0),	
    kFBToolPossibleDockPosLeft = (1 << 1),
    kFBToolPossibleDockPosRight = (1 << 2),
    kFBToolPossibleDockPosBottom = (1 << 3),
};

//! Tool class.
class  FBSDK_DLL FBTool :	public FBLayout {
    __FBClassDeclare( FBTool,FBLayout );
public:
    /** Constructor.
    *	\param	pName		Name of tool.
    */
    FBTool(const char* pName = NULL);

    /** Constructor used when creating tools not in the Tools menu of MotionBuilder.
    *	\param	pName		    Name of tool, must be an unique name.
    *	\param	pRegisterTool	Tells if we should register the tool on the toolmanager. You can later call Showtool to pop it.
    */    
    FBTool(const char* pName, bool pRegisterTool);

    /** Redefine Custom Destroy function. Internal use only
    *	\param	pIsLocal		Not Used
    */    
    virtual void Destroy(int pIsLocal) override;
    //@{
    /** Storage/Retrieval of information into the FBX file format.
    *	\param	pFbxObject	Object to interface with FBX file format.
    *	\param	pStoreWhat	Attributes to store in FBX file.
    */
    virtual bool	FbxStore	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
    virtual bool	FbxRetrieve	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
    //@}    

    /** Get the possible docking position for the tool (concatenated).
    *	\return	Get all the docking flags in one call. Flags can be concatenated.
    */
    FBToolPossibleDockPosition GetPossibleDockPosition();

    /** Set the possible docking position for the tool. Be sure to call this function once the tool is visible, a good place to call it is when the OnShow event of the layout is called.
    *	\param	pFlags	Set the docking position flag values. Note: this function overwrites all flags with those passed in parameter.
    */
    void SetPossibleDockPosition(FBToolPossibleDockPosition pFlags);

    IQuery_Declare(override);		// Interface to IObject.

    FBPropertyInt		StartSize	[2];	//!< <b>Read Write Property:</b> Starting Size. This is the initial size when the tool is opened. (0:Width, 1:Height. Default = 800x400)
    FBPropertyInt		MaxSize		[2];	//!< <b>Read Write Property:</b> Maximum Size (Disabled in this version). A value of -1 means no maximum size. (0:Width, 1:Height. Default = -1x-1)
    FBPropertyInt		MinSize		[2];	//!< <b>Read Write Property:</b> Minimum Size. A value of -1 means no minimum value. (0:Width, 1:Height. Default = 140x-1).
    FBPropertyInt		StartPos	[2];	//!< <b>Read Write Property:</b> Starting Position. This is the initial position when the tool is opened. (0:X, 1:Y. Default for first tool = 450x450)
    FBPropertyString    Name;               //!< <b>Read-Only Property:</b> Tool Name
    FBPropertyString    DisplayName;        //!< <b>Read Write Property:</b> Tool Display Name (Caption on the tool's title bar)
private:

    void InitTool();
};

/**	This function is used to bring up a specific tool in the GUI.
*   \param pToolName    The name of the tool as shown in the Open Reality menu.
*   \param pSetFocus    Indicate if the tool will have the focus.
*   \return             If the tool was brought up successfully.
*/
FBSDK_DLL bool FBPopNormalTool( const char* pToolName, bool pSetFocus = true );

/**	This function will show a specific tool in the GUI.
*   \param pToolName    The name of the tool as shown in the Open Reality menu.
*   \param pResizeWnd   Adjust the size of the tool window if needed (if started too close to the end of the screen for example).
*   \return             A pointer to the FBTool object, NULL otherwise.
*/
FBSDK_DLL FBTool* FBShowToolByName( const char* pToolName, bool pResizeWnd = true );

/**	This function will show a specific tool in the GUI.
*   \param pTool	    A pointer to the tool to show.
*   \param pResizeWnd   Adjust the size of the tool window if needed (if started too close to the end of the screen for example).
*   \return             A pointer to the FBTool object, NULL otherwise.
*/
FBSDK_DLL FBTool* FBShowTool( FBTool* pTool, bool pResizeWnd = true );

/**	This function will close a specific tool in the GUI.
*   \param pToolName    The name of the tool as shown in the Open Reality menu.
*   \return             True if the tool was closed successfully, false otherwise.
*/
FBSDK_DLL bool FBCloseToolByName( const char* pToolName );

/**	This function will close a specific tool in the GUI.
*   \param pTool	    A pointer to the tool to close.
*   \return             True if the tool was closed successfully, false otherwise.
*/
FBSDK_DLL bool FBCloseTool( FBTool* pTool );

/**	This function will destroy a specific tool in the GUI.
*   \param pToolName    The name of the tool as shown in the Open Reality menu.
*/
FBSDK_DLL void FBDestroyToolByName( const char* pToolName );

/**	This function will destroy a specific tool in the GUI.
*   \param pTool	    A pointer to the tool to destroy.
*/
FBSDK_DLL void FBDestroyTool( FBTool* pTool );

/**	This function will set the size of a specific tool in the GUI.
*   \param pToolName	The name of the tool as shown in the Open Reality menu.
*   \param pWidth       New width of the tool.
*   \param pHeight      New height of the tool.
*/
FBSDK_DLL void FBSetToolSizeByName( const char* pToolName, int pWidth, int pHeight );

/**	This function will set the size of a specific tool in the GUI.
*   \param pTool	    A pointer to the tool.
*   \param pWidth       New width of the tool.
*   \param pHeight      New height of the tool.
*/
FBSDK_DLL void FBSetToolSize( FBTool* pTool, int pWidth, int pHeight );

/**	This function will get the size of a specific tool in the GUI.
*   \param pToolName	The name of the tool as shown in the Open Reality menu.
*   \param pWidth       Current width of the tool.
*   \param pHeight      Current height of the tool.
*/
FBSDK_DLL void FBGetToolSizeByName( const char* pToolName, int &pWidth, int &pHeight );

/**	This function will get the size of a specific tool in the GUI.
*   \param pTool	    A pointer to the tool.
*   \param pWidth       Current width of the tool.
*   \param pHeight      Current height of the tool.
*/
FBSDK_DLL void FBGetToolSize( FBTool* pTool, int &pWidth, int &pHeight );

/**	This function will set the position of a specific tool.
*   \param pToolName	The name of the tool as shown in the Open Reality menu.
*   \param pPosX        New position in X for the tool.
*   \param pPosY        New position in Y for the tool.
*/
FBSDK_DLL void FBSetToolPositionByName( const char* pToolName, int pPosX, int pPosY );

/**	This function will set the position of a specific tool.
*   \param pTool	    A pointer to the tool.
*   \param pPosX        New position in X for the tool.
*   \param pPosY        New position in Y for the tool.
*/
FBSDK_DLL void FBSetToolPosition( FBTool* pTool, int pPosX, int pPosY );

/**	This function will get the position of a specific tool.
*   \param pToolName	The name of the tool as shown in the Open Reality menu.
*   \param pPosX        Current position in X of the tool.
*   \param pPosY        Current position in Y of the tool.
*/
FBSDK_DLL void FBGetToolPositionByName( const char* pToolName, int &pPosX, int &pPosY );

/**	This function will get the position of a specific tool.
*   \param pTool	    A pointer to the tool.
*   \param pPosX        Current position in X of the tool.
*   \param pPosY        Current position in Y of the tool.
*/
FBSDK_DLL void FBGetToolPosition( FBTool* pTool, int &pPosX, int &pPosY );

#ifdef FBSDKUseNamespace
}
#endif
#endif	/* __FBTOOL_H	*/
