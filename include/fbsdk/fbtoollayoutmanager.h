#ifndef __FBTOOLLAYOUTMANAGER_H__
#define __FBTOOLLAYOUTMANAGER_H__
/**************************************************************************
Copyright (c) 1994 - 2019 Autodesk, Inc. and/or its licensors.
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

/**	\file fbtoollayoutmanager.h
*	
*	The FBToolLayoutManager file contains the necessary declarations to 
*	interact with Layouts.
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

FB_FORWARD( FBStoryTrack );

FB_FORWARD( FBToolLayoutManager );
FB_DEFINE_COMPONENT( FBSDK_DLL, FBToolLayoutManager );

/** Tool Layout Manager class.
*   <b>This class allows users to interact with Layouts.</b>
*
*   Sample Python code:
*
*   @code

    from pyfbsdk import *

    lToolLayoutMan = FBToolLayoutManager()

    # Delete all existing custom layout
    for i in range( lToolLayoutMan.GetCustomLayoutCount() ):
        lToolLayoutMan.DeleteLayout( lToolLayoutMan.GetCustomLayoutCount() - 1 )
    
    # Create a new layout
    lToolLayoutMan.CreateLayout( "MyLayout" )
    
    # Print the names of all the factory layouts
    print "Factory layouts:"
    print "----------------"
    for aLayoutIdx in range(lToolLayoutMan.GetFactoryLayoutCount()):
        print lToolLayoutMan.GetLayoutName(-aLayoutIdx-1)
    
    # Print the names of all the custom layouts
    print ""
    print "Custom layouts:"
    print "----------------"
    for aLayoutIdx in range(lToolLayoutMan.GetCustomLayoutCount()):
        print lToolLayoutMan.GetLayoutName(aLayoutIdx)
    
    # Set the Scripting Layout
    lToolLayoutMan.SetCurrentLayout( -2 )
    
    # Delete the custom layout
    lToolLayoutMan.DeleteLayout( "MyLayout" )

*   @endcode
*/
class FBSDK_DLL FBToolLayoutManager: public FBComponent
{
	FBClassDeclare( FBToolLayoutManager, FBComponent );

protected:
	/** Constructor.
		Protected constructor, use TheOne() access instead.
	*/
	FBToolLayoutManager();

public:

	/** Get the number of factory layouts.
	*	\return The number of factory layouts.
	*/
	int GetFactoryLayoutCount();

	/** Get the number of custom layouts.
	*	\return The number of custom layouts.
	*/
	int GetCustomLayoutCount();

	/** Get the layout name associated with the given layout index.
	*	\param pLayoutIdx The layout index to query. The factory layouts are using negative indices.
	*	\return The layout name if the operation is successful, nullptr (C++) or None (Python) otherwise.
	*/
	const char* GetLayoutName( int pLayoutIdx );

	/** Get the layout index of the current layout.
	*	\return The layout index of the current layout.
	*/
	int GetCurrentLayoutIdx();

	/** Get the name of the current layout.
	*	\return The name of the current layout.
	*/
	const char* GetCurrentLayoutName();

	/** Set the current layout from the given layout index.
	*	\param pLayoutIdx The layout index to set as the current layout. The factory layouts are using negative indices.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetCurrentLayout( int pLayoutIdx );

	/** Set the current layout from the given layout name.
	*	\param pLayoutName The layout's name to set as the current layout.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetCurrentLayout( const char* pLayoutName );

	/** Create a new layout from the current layout state.
	*	\param pLayoutName The new layout name to create.
	*	\return The new layout's name (could be different that the one supplied) if the operation is successful, nullptr (C++) or None (Python) otherwise.
	*/
	const char* CreateLayout( const char* pLayoutName );

	/** Delete the layout associated with the given layout index. Deleting a factory layout is not permitted.
	*	\param pLayoutIdx The layout index to delete.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool DeleteLayout( int pLayoutIdx );

	/** Delete the layout with the given layout name. Deleting a factory layout is not permitted.
	*	\param pLayoutName The layout name to delete.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool DeleteLayout( const char* pLayoutName );

	/** Update the current layout from the current layout state. Updating a factory layout is not permitted.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool UpdateCurrentLayout();

	/** Rename a layout. Renaming a factory layout is not permitted.
	*	\param pOldLayoutName The layout's name to rename.
	*	\param pNewLayoutName The new layout name.
	*	\return The new layout's name (could be different that the one supplied) if the operation is successful, nullptr (C++) or None (Python) otherwise.
	*/
	const char* RenameLayout( const char* pOldLayoutName, const char* pNewLayoutName );

	/** Get the 'Auto-update Layout' state value.
	*	\return The 'Auto-update Layout' state value.
	*/
	bool GetAutoUpdateLayout();

	/** Set the 'Auto-update Layout' state value.
	*	\param pAutoUpdate The 'Auto-update Layout' state value.
	*	\return True if the operation is successful, false otherwise.
	*/
	bool SetAutoUpdateLayout( bool pAutoUpdate );


	/** Returns the only instance of FBToolLayoutManager.
	* \return The only instance of FBToolLayoutManager.
	*/
	static FBToolLayoutManager& TheOne();
};

#ifdef FBSDKUseNamespace
}
#endif //FBSDKUseNamespace

#endif //__FBTOOLLAYOUTMANAGER_H__
