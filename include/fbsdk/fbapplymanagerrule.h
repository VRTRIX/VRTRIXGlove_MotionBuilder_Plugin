#ifndef __FBAPPLYMANAGERRULE_H__
#define __FBAPPLYMANAGERRULE_H__
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

/**    \file fbapplymanagerrule.h
*    Derive new Apply Manager Rules using the FBApplyManagerRule class.
*   Define the custom rule to manipulate objects for varous operations.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*    Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

    __FB_FORWARD( FBApplyManagerRule );
    __FB_FORWARD( FBAMMenu );

    FB_DEFINE_COMPONENT( FBSDK_DLL, ApplyManagerRule);

    /**    Filter class registration.
    *    \param    ClassName            Filter class name.
    *    \param    Label                Short description.
    *    \param    Description            Long description.
    */
#define FBRegisterApplyManagerRule( ClassName, Label, Description ) \
    HIObject RegisterApplyManagerRule##ClassName( HIObject pOwner,const char * /*pName*/,void * /*pData*/) \
    { \
    ClassName *Class = new ClassName( ); \
    if (Class->FBCreate()) { \
    return Class->GetHIObject(); \
    } else { \
    delete Class; \
    return NULL; \
    } \
    } \
    FBLibraryModule( ClassName )    \
    {    \
    FBRegisterObject( ClassName,"Browsing/Apply",Label,Description,RegisterApplyManagerRule##ClassName,false, NULL );    \
    }

    /**    Apply Manager Rule class declaration.
    *    \param    ClassName    ApplyManagerRule class name.
    *    \param    Parent        Parent class name.
    */
#define FBApplyManagerRuleDeclare( ClassName, Parent  ) \
    FBClassDeclare( ClassName,Parent); \
public: \
    ClassName( HIObject pO = NULL ):Parent(pO) { FBClassInit; } \
private:

    /**    ApplyManagerRule class implementation.
    *    \param    ThisComponent    Class to implement.
    */
#define FBApplyManagerRuleImplementation( ThisComponent ) \
    FBClassImplementation( ThisComponent )


    ////////////////////////////////////////////////////////////////////////////////////
    // FBApplyManagerRule - ApplyManagerRule layer on top of internals.
    ////////////////////////////////////////////////////////////////////////////////////
    /** ApplyManagerRules are used to define custom rules for manipulating custom objects. 
    *   It controls the relationship between the
    *   custom type objects and MB Core objects. For example, you can use it to 
    *   allow the connection between your custom ragdoll physical property and 
    *   the MB core character type object. And thus you can drag the ragdoll property
    *   from the asset browser or from scene navigator and attach it to a character. 
    *   
    *   @warning    You shouldn't override the system default rule. All the function
    *               should return false if won't handle the call back.
    */
    class FBSDK_DLL FBApplyManagerRule : public FBComponent
    {
        //--- Open Reality declaration.
        __FBClassDeclare( FBApplyManagerRule, FBComponent );

    public:
        /** Constructor.
        *    \param    pObject                For internal use only (default is NULL).
        */
        FBApplyManagerRule( HIObject pObject = NULL );

        /** Return true if pSrc is the type of custom object which this rule to be defined for. 
        *
        *    @warning you should only return true if pSrc is the type of custom object you defined.
        */
        virtual bool IsValidSrc( FBComponent* /*pSrc*/) { return false; }

        /** Return true if pDst is the type of custom or MB object which your custom object 
        *    pSrc will be applied on. it's possible to return proper destination and return it by pDst. 
        *    For example, pSrc is RagDoll Property, pDst is a one of IK/FK bone, then you can find
        *    associated Character and replace.
        *
        *    \param    pSrc    the custom type of object you drag it to attach another object.
        *    \retval    pDst    one of the selected destinations, it could be modified and return proper destination.
        *    \retval    pAllowMultiple    return true if allow multiple objects of same type as pSrc to be connected
        *                   to pDst.
        *    \return            return true if connection between pSrc and pDst is allowed.
        */
        virtual bool IsValidConnection( FBComponent* pSrc, FBComponent*& pDst, bool& pAllowMultiple) { return false; }

        /** Build context menu for the type of custom object.
        *
        *    \param    pAMMenu    the menu to add menu option on.
        *    \param    pFocusedObject    the custom type of object you right-click on.
        *    \return    return true if menu item has been added.
        */
        virtual bool MenuBuild( FBAMMenu* pAMMenu, FBComponent* pFocusedObject) { return false; }

        /** Perform action if the added menu item is clicked.
        *
        *    \param    pMenuId    the menu ID right-click on.
        *    \param    pFocusedObject    the custom type of object right-click on.
        *    \return    return true if action has been performed.
        */
        virtual bool MenuAction( int pMenuId, FBComponent* pFocusedObject) { return false; }
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // FBAMMenu
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** Context menu.
    *    Expose KAMMenu to dd menu item on context menu in ORSDK.
    */
    class FBSDK_DLL FBAMMenu : public FBComponent
    {
        //--- Open Reality declaration.
        __FBClassDeclare(FBAMMenu, FBComponent);
    public:

        /**    Constructor.
        *    \param    pName    AMMenu name.
        *    \param    pObject    For internal use only.
        */
        FBAMMenu(const char* pName, HIObject pObject=NULL);

        /** Add menu option item on this menu.
        *
        *    \param    pMenuOptions    the menu option to add.
        *    \param    pId             the menu ID for this menu option.
        *    \param    pEnable         enable the menu option or not.
        *    \return    return         The menu ID for the added menu option.
        */
        int AddOption( const char* pMenuOptions, int pId = -1, bool pEnable = false );
    };

#ifdef FBSDKUseNamespace
}
#endif
#endif /* _FB_FILTER_H_ */
