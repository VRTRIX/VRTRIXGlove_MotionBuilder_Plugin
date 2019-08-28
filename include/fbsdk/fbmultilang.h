#ifndef __FBMULTILANG_H__
#define __FBMULTILANG_H__
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

/** \file fbmultilang.h
*	Contains language and localization related functionalities.
*/

#include <kaydaradef.h>

#include <fbsdk/fbtypes.h>

#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

FB_FORWARD( FBPlug );

/** Name lookup in the context of an object.
*   Most application objects have an internal name which differs from the name shown
*   by the GUI. This will often be the case for the names of an object's properties.
*
*   The way that support for multiple languages has been implemented is using conversion
*   tables that will map the internal name to a localized name. Since the same internal
*   name might mean different things for different objects, we can provide a context
*   to help the lookup process.
*
*   In this case, the context is a class object instance. When the lookup fails within
*   a context, we sucessively try a lookup using the parent classes in the object
*   hierarchy.
*
*   It is important to note that for given property, it only knows about its internal
*   name. The localized name is not attached to the property object itself as it resides
*   elsewhere, in a lookup table. This is also the case for any other application object.
*
*   The lookup table used to find the localized, or GUI name, of an object is dependent
*   on the current language used. This information is available via the class
*   FBMultiLangManager, which can indicate which language are availables and provides
*   methode to query and change the current language.
*
*   @param pContext         Object which dictates the context of the lookup.
*   @param pKey             String to look up.
*   @param pFlagReturnKey   Should the lookup fail, will return the key instead of an empty string.
*   @return                 The corresponding string if the lookup was succesfull. If not will
*                           return an empty string if pFlagReturnKey was false. Otherwise will
*                           return the key string.
*
*   Python sample code:
*   @code
    from pyfbsdk import *

    # Let's pick the first camera present in the system.
    lCamera = FBSystem().Cameras[0]

    # We know that cameras have a property named 'LockMode'.
    lPropInternalName = lCamera.PropertyList.Find( 'LockMode' )
    if lPropInternalName:
        print 'Actual property name, as defined internally: "%s"' % lPropInternalName.GetName()
        print 'Property name as shown by the GUI: "%s"' % FBGetMultiLangText( lCamera, lPropInternalName.GetName())
    
        lPropLocalizedName = lCamera.PropertyList.Find( FBGetMultiLangText( lCamera, lPropInternalName.GetName()))
        if lPropLocalizedName and lPropInternalName.GetName() == lPropLocalizedName.GetName():
            print 'Found the same property using both the internal (%s) and localized name (%s).' % (
                lPropLocalizedName.GetName(),
                FBGetMultiLangText( lCamera, lPropInternalName.GetName()))
*   @endcode
*
*   C++ sample code:
*   @code
    // Let's pick the first camera present in the system.
    FBCamera* lCamera = FBSystem().Cameras[0];

    // We know that cameras have a property named 'LockMode'.
    FBProperty* lPropInternalName = lCamera->PropertyList.Find( "LockMode" );
    if( lPropInternalName )
    {
        FBTrace( "Actual property name, as defined internally: '%s'\n", lPropInternalName->GetName());
        FBTrace( "Property name as shown by the GUI: '%s'\n", FBGetMultiLangText( lCamera, lPropInternalName->GetName()));
    
        FBProperty* lPropLocalizedName = lCamera->PropertyList.Find( FBGetMultiLangText( lCamera, lPropInternalName->GetName()));
        if( lPropLocalizedName && stricmp( lPropInternalName->GetName(), lPropLocalizedName->GetName()) == 0 )
        {
            FBTrace( "Found the same property using both the internal (%s) and localized name (%s).\n",
                lPropLocalizedName->GetName(),
                FBGetMultiLangText( lCamera, lPropInternalName->GetName()));
        }
    }
*   @endcode
*/
FBSDK_DLL const char* FBGetMultiLangText( FBPlug* pContext, const char* pKey, bool pFlagReturnKey = false );

/** Name lookup in a user defined context context.
*   This version of the function is a little less useful as the context string, if not
*   empty, will usually refer to internal class names of objects which is not easily 
*   available to the outside world.
*
*   As a general rule, an SDK object whose class is 'FBObject' will be wrapping an
*   internal object of class 'KObject'. For example an 'FBCamera' is a wrapper around
*   a 'KCamera' object. Similarily an 'FBConstraint' wll wrap a 'KConstraint'. This
*   pattern is not universal and may differ at times, so it will not always be
*   applicable. There are also cases where an 'FB' objects has no corresponding
*   'K' object, such as in the case of an 'FBSystem' object.
*
*   On lookup there are potentially two searches made: a first one, using the context
*   if one was provided. Should the first search fail, a second search will be done
*   without using the context.
*
*   Again the lookup result is dependant on the current language selected, as
*   indicated by the class FBMultiLangManager.
*
*   @param pContext         String which dictates the context of the lookup.
*   @param pKey             String to look up.
*   @param pFlagReturnKey   Should the lookup fail, will return the key instead of an empty string.
*   @return                 The corresponding string if the lookup was succesfull. If not will
*                           return an empty string if pFlagReturnKey was false. Otherwise will
*                           return the key string.
*
*   The following sample code shows 2 cases that do not use context, and 2 cases
*   that are using a context which are internal class names.
*
*   Python sample code:
*   @code
    from pyfbsdk import *

    print FBGetMultiLangText( '', 'CharacterExtension' )            # Will return 'Character Extension'.
    print FBGetMultiLangText( '', 'TranslationMax' )                # Will return 'Max Freedom'.
    print FBGetMultiLangText( 'KConstraintUIName', 'Parent-Child' ) # Will return 'Parent/Child'.
    print FBGetMultiLangText( 'KCamera', 'FieldOfView' )            # Will return 'Field Of View'.
*   @endcode
*
*   C++ sample code:
*   @code
    // Will return 'Character Extension'.
    FBTrace( "%s\n", FBGetMultiLangText( "", "CharacterExtension" ));

    // Will return 'Max Freedom'.
    FBTrace( "%s\n", FBGetMultiLangText( "", "TranslationMax" ));

    // Will return 'Parent/Child'.
    FBTrace( "%s\n", FBGetMultiLangText( "KConstraintUIName", "Parent-Child" ));

    // Will return 'Field Of View'.
    FBTrace( "%s\n", FBGetMultiLangText( "KCamera", "FieldOfView" ));
*   @endcode
*/
FBSDK_DLL const char* FBGetMultiLangText( const char* pContext, const char* pKey, bool pFlagReturnKey = false );


////////////////////////////////////////////////////////////////////////////////////
// FBMultiLangManager
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBMultiLangManager );

/** Language manager.
*   The class FBMultiLangManager indicates the supported languages and allows to query
*   and change the current language.
*
*   The support for localization is done using conversion tables from internal names
*   to language specific names, so that they can be used in the GUI and other human
*   readable contexts.
*
*   @warning    At this time, changing the current language will not affect the
*               GUI. Only calls to functions 'FBGetMultiLangText()' will be affected.
*
*   The following sample code lists the names of the supported languages:
*
*   Python sample code:
*   @code
    from pyfbsdk import *

    lManager = FBMultiLangManager()
    print 'Current localization language: ', lManager.GetCurrentLanguage()
    print 'Supported languages:'
    for lLanguage in lManager.Languages:
        print '  ', lLanguage
*   @endcode
*
*   C++ sample code:
*   @code
    FBMultiLangManager lManager;
    FBTrace( "Current localization language: %s\n", lManager.GetCurrentLanguage());
    FBTrace( "Supported languages:\n" );

    int lIdx = 0;
    while( lIdx < lManager.Languages.GetCount())
    {
        FBTrace( "  %s\n", lManager.Languages[lIdx++] );
    }
*   @endcode
*/
class FBSDK_DLL FBMultiLangManager
{
    /** Disabled copy constructor.
    *   Voluntarily making the copy constructor unavailable.
    */
    FBMultiLangManager( const FBMultiLangManager& );

    /** Disabled assignment operator.
    *   Voluntarily making the assignment operator unavailable.
    */
    FBMultiLangManager& operator=( const FBMultiLangManager& );

public:

    //! Constructor.
    FBMultiLangManager();

    //! Destructor.
    ~FBMultiLangManager();

    /** Obtain the current language.
    *   Query the current language used for the GUI.
    *
    *   @return Will return the string associated with the current language used.
    */
    const char* GetCurrentLanguage() const;

    /** Set the current language.
    *   Change the current language to another available language.
    *
    *   @param pLanguage    The string corresponding to the desired language, as defined in property Languages.
    *   @return             Indicate if the change of language was successful.
    *
    *   @warning Setting the current language will affect the lookup done
    *   with the functions FBGetMultiLangText, but will not have any effect
    *   on the GUI.
    */
    bool SetCurrentLanguage( const char* pLanguage );

    /** List of available languages.
    *   @warning    This list should not be modified. Changes to its value will not affect the languages supported.
    */
    FBStringList Languages;
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif
