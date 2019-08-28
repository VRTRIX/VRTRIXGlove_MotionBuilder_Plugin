#ifndef __GENERIC_MENU_H__
#define __GENERIC_MENU_H__
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

/**	\file fbcontrols.h
*	Contains the user interface components for the SDK.
*	All of the user interface elements available for use with the SDK are 
*	defined in this file. These elements (for the most part) derive from 
*	the FBVisualComponent base class and provide the functionality 
*	required to develop an interface for a plugin.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	//! FBSDKDLL_ K_DLLEXPORT
	#define FBSDK_DLL K_DLLEXPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbcontrols/fbcontrols.h>

K_FORWARD( IKtObject );


#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBGenericMenuItem );
__FB_FORWARD( FBGenericMenu );
__FB_FORWARD( FBMenuManager );
FB_DEFINE_COMPONENT( FBSDK_DLL, GenericMenuItem );
FB_DEFINE_COMPONENT( FBSDK_DLL, GenericMenu );
FB_DEFINE_COMPONENT( FBSDK_DLL, MenuManager );

/**	FBGenericMenuItem
    This class stores data for a single menu item. A single menu item can contains another menu
    (embedded menu) or not. A GenericMenuItem has an Id and a Name.

    You can use a GenericMenuItem to modify the attributes of a menu (it is the only way to change
    its name).

    You cannot create a FBGenericMenuItem directly. You must use the insertion method in FBMenu of FBMenuManager
    to obtain a handle on a FBGenericMenuItem.
*/
class  FBSDK_DLL FBGenericMenuItem : public FBComponent {
    __FBClassDeclare( FBGenericMenuItem, FBComponent );
public:      
    FBGenericMenuItem(HIObject pObject);  

	FBPropertyString Caption; //!< <b>Read/Write Property:</b> Caption of the menu item.
    FBPropertyInt Id; //!< <b>Read/Write Property:</b> Id of the menu item. 
    FBPropertyBool Enable; //!< <b>Read/Write Property:</b> Enable or Disable (grey out) a menu Item.
    FBPropertyGenericMenu Menu; //!< <b>Read/Write Property:</b> If the menu item leads to another menu.
};

/**
    A GenericMenu class. You can use this class either to create a new menu in the menu bar 
    (or in a menuitem in the menu bar) or you can use this class to create a pop-up menu.

    @code
    #to start a pop up menu use the Execute method
    def mouseClick(x, y):
        item = menu.Execute(x, y)
        if item.Id == 10:
           [do this]
        else if item.Id == 100:
            [do that...]
    @endcode

    There are 4 ways to insert new item in a menu. Each method needs the name of the menuitem as well
    as it's unique id. You can also optionnally sets a new menu for a specific item.    

    @code
    embeededMenu = FBGenericMenu()
    menu.InsertLast("new new item", 67, embeddedMenu)

    #A genericMenu contains a GenericMenuItem for each entry. You can iterate on the different menuitem
    #using GetFirstITem/GetNextItem or if you already know the id of the item you can get it with GetItem.
    
    item = menu.GetFirstItem()
    while item:
        print item.Name
        item = menu.GetNextItem(item)
    @endcode

    You can also delete a Menu item: this will remove the item from the menu as well as freeing its memory.

    To be notified when a menuitem is clicked, you can register using OnMenuActivate. This will send a FBEventMenu
    containing the name and the Id of the menu item that was clicked.
*/
class  FBSDK_DLL FBGenericMenu : public FBComponent {
    __FBClassDeclare( FBGenericMenu, FBComponent );
public:
    /** Default constructor. Used to create embedded menu (inside aniother menu item) or pop-up menu.
    */
    FBGenericMenu(HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete() override;
	
	/** Returns the first menu item (if existing) in this menu. You can then use GetNextItem
        to iterate on other menu items.
    \return The first menu item in this Menu.
    */
    FBGenericMenuItem* GetFirstItem();

    /** Returns the last menu item (if existing) in this menu. You can then use GetPrevItem
    to reverse iterate on other menu items.
    \return The last menu item in this Menu.
    */
    FBGenericMenuItem* GetLastItem();

    /** Returns the menu item following an other item. Returns null if this is the last item in menu.    
    \param pItem Will return the item after pItem
    \return Will return the item after pItem. Null if pItem is the last item.
    */
    FBGenericMenuItem* GetNextItem(FBGenericMenuItem* pItem);

    /** Returns the menu item preceding an other item. Returns null if this is the first item in menu.    
    \param pItem Will return the item BEFORE pItem
    \return Will return the item BEFORE pItem. Null if pItem is the first item.
    */
    FBGenericMenuItem* GetPrevItem(FBGenericMenuItem* pItem);

    /** Returns the menu item corresponding to an id. 
    \param pItemId Id of the item we are looking for.
    \return Will return the Item corresponding to an id (null if not found).
    */
    FBGenericMenuItem* GetItem( int pItemId );

    /** Inserts a new menu Item at the first position in the menu list. 
    \param pItemName Caption of the newly added item.
    \param pItemId Unique id of this menu item.
    \param pMenu Optionnal. If this Item leads to another menu (embddedd) it can be specified here.
    \return Will return the menu item created from this insertion.
    */
    FBGenericMenuItem* InsertFirst(const char*  pItemName, int pItemId, FBGenericMenu* pMenu = NULL);

    /** Inserts a new menu Item at the last position in the menu list. 
    \param pItemName Caption of the newly added item.
    \param pItemId Unique id of this menu item.
    \param pMenu Optionnal. If this Item leads to another menu (embddedd) it can be specified here.
    \return Will return the menu item created from this insertion.
    */
    FBGenericMenuItem* InsertLast(const char*  pItemName, int pItemId, FBGenericMenu* pMenu = NULL);

    /** Inserts a new menu Item AFTER another item.
    \param pBeforeItem The reference item. We will create a new item AFTER this one.
    \param pItemName Caption of the newly added item.
    \param pItemId Unique id of this menu item.
    \param pMenu Optionnal. If this Item leads to another menu (embddedd) it can be specified here.
    \return Will return the menu item created from this insertion.
    */
    FBGenericMenuItem* InsertAfter(FBGenericMenuItem* pBeforeItem, const char*  pItemName, int pItemId, FBGenericMenu* pMenu = NULL);

    /** Inserts a new menu Item BEFORE another item.
    \param pAfterItem The reference item. We will create a new item BEFORE this one.
    \param pItemName Caption of the newly added item.
    \param pItemId Unique id of this menu item.
    \param pMenu Optionnal. If this Item leads to another menu (embddedd) it can be specified here.
    \return Will return the menu item created from this insertion.
    */
    FBGenericMenuItem* InsertBefore(FBGenericMenuItem* pAfterItem, const char*  pItemName, int pItemId, FBGenericMenu* pMenu = NULL);
    
    /** Remove a menu item from the menu and delete it.
    \param pToDelete The item to remove.    
    */
    void DeleteItem(FBGenericMenuItem* pToDelete);

    /** Starts the menu as a pop-up menu at a specific location on screen. It returns the item that was clicked
    by the user.
    \param pX X location in pixel on screen where the menu is to be popped.
    \param pY Y location in pixel on screen where the menu is to be poppded.
    \param pRightAlign All menu item will be align to the right justified (if true) or left justifed (if false)    
    \return The selected item by the user. Null if the user clicks outside the menu.
    */
    FBGenericMenuItem* Execute(int pX, int pY, bool pRightAlign = true);


    FBPropertyEvent OnMenuActivate; //!< <b>Event Property:</b> Register on this property to be notified when a menu item is clicked by the user.
private:
    friend class FBMenuManager;
    friend class DataFBMenuManager;
    friend class DataFBGenericMenu;
};

/**
    The menu manager allows access to MotionBuilder menu bar. 

    It can be used to retrieve the item corresponding to a menu path in the menu bar. A menu path
    is similar to a file path but it specifies the location of menu item in a hierarchy of menu.
    ex: to retrieve the item corresponding to MoBu Save item:
    item = menuMgr.GetMenu("File/Save")

    Other menu items in MoBu menu bar include the following:
    "File", "Edit","Animation","Window","Settings", "Layout","Help"

    The menu manager can be used to insert new menu item in the menubar. You have to specify the menu path
    at which to insert the menu (to insert a new root menu, use NULL or None as the menu path)
    @code
    #Insert a new Root Menu before the Help menu
    menuMgr.InsertBefore(None, "Help", "before menu")

    #Insert a new Root Menu after the Help menu
    menuMgr.InsertAfter(None, "Help", "After menu")
    @endcode

    As a convenience operation, you can from the menu manager enable and disable menu item (instead of retrieving their
    corresponding item).
    
*/
class  FBSDK_DLL FBMenuManager : public FBComponent {
    __FBClassDeclare( FBMenuManager, FBComponent );
public:
    /** Constructor. There is only one MenuManager in MotionBuilder, creating multiple FBMenuManager always return
    the same handle to the same global menu manager.
    */
    FBMenuManager();
    
    /** Get the Menu (NOT menu item) corresponding to a menu path. Don't forget that most menu path already in MotionBuilder
    have a "&"as the first letter of their name. You have to use / as a separator in the specified
    menu path (ex: "Settings/&Preferences...").
    \param pPath Path of the menu to retrieve
    \return the FBGenericMenu at this path./
    */
    FBGenericMenu* GetMenu(const char*  pPath);

    /** Insert a new menu at the first position of a specific path.
    \param pMenuPath Path where to insert the menu. If this is NULL (None) it will insert a new root menu.
    \param pMenuName Name (Caption) of the newly inserted menu.
    \return Returns the menu item corresponding to the newly inserted menu.
    */
    FBGenericMenuItem* InsertFirst(const char*  pMenuPath, const char*  pMenuName);

    /** Insert a new menu at the last position of a specific path.
    \param pMenuPath Path where to insert the menu. If this is NULL (None) it will insert a new root menu.
    \param pMenuName Name (Caption) of the newly inserted menu.
    \return Returns the menu item corresponding to the newly inserted menu.
    */
    FBGenericMenuItem* InsertLast(const char*  pMenuPath, const char*  pMenuName);

    /** Insert a new menu at a specific path BEFORE another item.
    \param pMenuPath Path where to insert the menu. If this is NULL (None) it will insert a new root menu.
    \param pAfterMenuName Name of the menu item BEFORE which we will insert the new item.
    \return Returns the menu item corresponding to the newly inserted menu.
    */
    FBGenericMenuItem* InsertBefore(const char*  pMenuPath, const char*  pAfterMenuName, const char*  pMenuName);    

    /** Insert a new menu at a specific path AFTER another item.
    \param pMenuPath Path where to insert the menu. If this is NULL (None) it will insert a new root menu.
    \param pBeforeMenuName Name of the menu item AFTER which we will insert the new item.
    \return Returns the menu item corresponding to the newly inserted menu.
    */
    FBGenericMenuItem* InsertAfter(const char*  pMenuPath, const char*  pBeforeMenuName, const char*  pMenuName);    

    /** Enable or disable a specific menu item. The menu path specifies the menu where we find 
        the item to be enabled/disabled. The Id specifies which item in the menu.
    \param pMenuPath Path where to find the menu to enable/disable
    \param pItemId Id of the item in the menu to disable.  
    \param pEnable Enable (true) or disable  (false) a menu item.
    */
    void SetItemEnable(const char*  pMenuPath, int pItemId, bool pEnable );

    /** Check if a particular item is enabled or disabled. The menu path specifies the menu where we find 
    the item to be enabled/disabled. The Id specifies which item in the menu.
    \param pMenuPath Path where to find the menu to check
    \param pItemId Id of the item to check.  
    \return Is the item enable or not.
    */
    bool IsItemEnable(const char*  pMenuPath, int pItemId);
private:
    FBGenericMenuItem* GetMenuItem(const char*  pMenuPath, const char*  pMenuName, int pId );
};



#ifdef FBSDKUseNamespace
	}
#endif

#endif
