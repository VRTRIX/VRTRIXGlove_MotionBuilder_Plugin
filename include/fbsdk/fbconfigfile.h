#ifndef __FBCONFIGFILE_H__
#define __FBCONFIGFILE_H__
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

/** @file   fbconfigfile.h
*   Declaration for the FBConfigFile class.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
    #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbversion.h>

#ifdef FBSDKUseNamespace
    namespace FBSDKNamespace {
#endif

/**  Interface to the application config files.
*    This class allows client code to generate, modify and query configuration files.
*    Config files will be automatically created when needed. They will be located in the
*    $(INSTALLDIR)/bin/config folder or an explicitly specified folder depending on
*    the constructor used.
*/
class FBSDK_DLL FBConfigFile
{
    ///\name Restricted methods. 
    //@{
    /** Voluntarily making the copy constructor and assignment
    *   operator unavailable.
    */
    FBConfigFile( const FBConfigFile& );
    FBConfigFile& operator=( const FBConfigFile& );
    //@}

    //! Internal implementation.
    void* mImplementation;

public:
    /** Constructor.
    *   This will open the desired config file from the [APPLICATION]/bin/config folder.
    *   The file will be created if it does not exists.
    *   By prefixing the character '@' to the file name, this will automatically prepend
    *   the current machine name to the config file, the way it is done for the other config
    *   files of the application.
    *   \param  pConfigFileName     Name the config file to use.
    *   \param  pVirtualMode        Enable this to limit disk access, file will only be read at construction and written at destruction.
    *   \param  pClearFile          Remove all existing content from the config file.
    */
    FBConfigFile( const char* pConfigFileName, bool pVirtualMode = false, bool pClearFile = false);

    /** Constructor.
    *   This will open the desired config file in the designed folder.
    *   The file will be created if it does not exists.
    *   By prefixing the character '@' to the file name, this will automatically prepend
    *   the current machine name to the config file, the way it is done for the other config
    *   files of the application.
    *   \param  pConfigFileName     Name the config file to use.
    *   \param  pConfigFilePath     Location where the file should reside. Missing directories will not be created.
    *   \param  pVirtualMode        Enable this to limit disk access, file will only be read at construction and written at destruction.
    *   \param  pClearFile          Remove all existing content from the config file.
    */
    FBConfigFile( const char* pConfigFileName, const char* pConfigFilePath, bool pVirtualMode = false, bool pClearFile = false );

    //! Destructor
    ~FBConfigFile();
    
    /** Set an item's value.
    *   Assign a value to an item in the config file.
    *   If the item does not exist, it will be created.
    *   \param  pSectionName    Name of the section.
    *   \param  pItemName       Name of the item.
    *   \param  pValue          Value assigned to the item.
    *   \param  pComment        Optional parameter that can be used to add a comment.
    *   \return \b true if the item was written to the config file, \b false otherwise.
    */
    bool Set( const char* pSectionName, const char* pItemName, const char* pValue, const char* pComment = 0 );

    /** Get an item's value.
    *   Get an item's value by looking inside a specific section of the config file.
    *   \param  pSectionName    Name of the section.
    *   \param  pItemName       Name of the item.
    *   \param  pDefaultValue   Default value that will be returned if the item is not found.
    *   \return The value assigned to the item in the specified section of the config file, or the default value if not found.
    */
    const char* Get( const char* pSectionName, const char* pItemName, const char* pDefaultValue = 0 ); 

    /** Get a value from the config file and set it if it was not found.
    *   \param  pSectionName    Name of the section.
    *   \param  pItemName       Name of the item.
    *   \param  pValue          Reference the the string that will contain the value of the item. If the item is not found in the file, it will be added with the initial value in this string.
    *   \param  pComment        Optional parameter that can be used to add a comment.
    *   \return \b true if the value was found or added, or false if the item was not found and could not be added to the file.
    */
    bool GetOrSet( const char* pSectionName, const char* pItemName, const char*& pValue, const char* pComment = 0 );

    /** Remove all content from the config file.
    */
    void ClearFile();
};


#ifdef FBSDKUseNamespace
    }
#endif
#endif /* __FBCONFIGFILE_H__ */
