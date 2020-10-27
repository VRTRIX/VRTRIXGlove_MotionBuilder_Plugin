/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file fbxlocale.h
#ifndef _FBXSDK_UTILS_LOCALE_H_
#define _FBXSDK_UTILS_LOCALE_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxstring.h>
#include <fbxsdk/core/base/fbxarray.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxLocalization_internal;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class holds localized messages.
  * \nosubgrouping
  */
class FBXSDK_DLL FbxLocalization
{
public:
    FBXSDK_FRIEND_NEW();
    /** 
	  * \name Localization object creation functions.
	  */
	//@{
	/** Create an empty localization object with the given locale name.
      * \param pLocaleName the locale name (ex: "en" or "en-US").
	*/
    static FbxLocalization* Create( const char* pLocaleName );
	//@}

    ~FbxLocalization();

    /** 
	  * \name Localization.
	  */
	//@{
	/** Retrieve the localized message.
      * \param pID the identifier for the localized message.
      * \param pDefault the default message to return if not found. Pass NULL to have the pID returned.
      * \return the localized message, or the ID passed in parameter if not found.
	*/
    const char* GetLocalizedMessage( const char* pID, const char* pDefault = NULL ) const;
	/** Verify if a message is localized.
      * \param pID the identifier for the message to verify.
      * \return true if the message has a localization.
      *
      * Note: this function is mainly provided for callers who want to fill localization objects
      *       and want to avoid overwriting existing data.
	*/
    bool HasLocalizedMessage( const char* pID ) const;
	/** Retrieve the locale name.
      * \return the locale name (ex: "en" or "en-US").
	*/
    const FbxString& GetLocaleName() const;
	//@}
    
    /** 
	  * \name Localization addition.
	  */
	//@{
	/** Add a new text-to-text and ID-to-text message.
      * \param pID the identifier for the localized message.
      * \param pSource the source text for the localized message.
      * \param pTarget the localized message.
	*/
    void AddLocalizedMessage( const char* pID, const char* pSource, const char* pTarget );
	//@}

    /** 
	  * \name Localization listing.
	  */
	//@{
	/** Retrieve the number of existing localizations.
      * \return the number of localizations, both by-text and by-ID.
	*/
    int GetLocalizedCount() const;
	/** Retrieve information about a localization by index.
      * \param pIndex the index of the localization to retrieve.
      * \param pID buffer to be filled with the ID of the localization.
      *            If the message has no ID, the buffer will be emptied.
      * \param pSource buffer to be filled with the source text of the localization.
      *                If the message has no source, the buffer will be emptied.
      * \param pTo     buffer to be filled with the target text of the localization.
      * \return true if the index was valid.
	*/
    bool GetLocalizedMessageByIndex( int pIndex, FbxString* pID, FbxString* pSource, FbxString* pTo ) const;
	//@}


/*****************************************************************************************************************************
** WARNING! Anything beyond these lines is for internal use, may not be documented and is subject to change without notice! **
*****************************************************************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    FbxLocalization( const char* pName );

private:
    // Unimplemented, prevent copies.
    FbxLocalization( const FbxLocalization& );
    void operator=( const FbxLocalization& );

    FbxLocalization_internal* mData;
#endif /* !DOXYGEN_SHOULD_SKIP_THIS *****************************************************************************************/
};


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** 
  * \name XLIFF I/O function.
  */
//@{
/** Load a localization definition from a file in XLIFF (XML) in a new object.
  * \param pLocaleName the target locale name (ex: "en" or "en-US").
  * \param pFileName the XLIFF filename.
  * \return the localization object or null on failure.
*/
FBXSDK_DLL FbxLocalization* LoadXLIFF( const char* pLocaleName, const char* pFileName );
/** Load a localization definition from a file in XLIFF (XML) in an existing object.
  * \param pLocalization the localization object to be filled. Its locale name is used as the target locale.
  * \param pFileName the XLIFF filename.
  * \return true on success.
*/
bool FBXSDK_DLL LoadXLIFF( FbxLocalization* pLocalization, const char* pFileName );
/** Save a localization definition to a file in XLIFF (XML).
  * \param pLocalization the localization object to be saved. Its locale name is used as the target locale.
  * \param pFileName the XLIFF filename.
  * \return true on success.
*/
bool FBXSDK_DLL SaveXLIFF( const FbxLocalization* pLocalization, const char* pFileName );
//@}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class FbxLocalizationManager_internal;

/** This class manages multiple localization files for a given module.
  * Use one instance in your module if it need to have its own set of
  * localization files.
  * \nosubgrouping
  */
class FBXSDK_DLL FbxLocalizationManager
{
public:

    //! Locale name for the English locale.
    static const char* sEnglishLocale;

    /** 
	  * \name Constructor and destructor. Nothing to see...
	  */
	//@{
    FbxLocalizationManager();
    ~FbxLocalizationManager();
	//@}

    /** 
	  * \name Localization file repository management.
      * Localization files have the "xlf" extension and are expected to have
      * the format "<basename>-<locale>.xlf", for example "FBXLOG-fr.xlf".
	  */
	//@{
	/** Retrieves the localization file repository folder.
	*/
    const char* GetLocalizationRepositoryFolder() const;
	/** Sets the localization file repository folder.
	* \param pFolder The localization file repository folder to be set.
	*/
    void SetLocalizationRepositoryFolder(const char* pFolder);
	/** Retrieves the localization file base-name prefix.
      * \return the prefix of the localization file names.
	*/
    const char* GetLocalizationBaseNamePrefix() const;
	/** Sets the localization file repository folder.
      * \param pPrefix the new prefix for localization file names.
	*/
    void SetLocalizationBaseNamePrefix(const char* pPrefix);
	/** Build a log localization file name from a locale.
      * \param pLocale the locale name (ex: "en", "fr", etc).
      * \return the full file name of the log localization file,
      *         using the localization repository folder and the
      *         localization base-name prefix.
	*/
    FbxString GetLocalizationFileName(const char* pLocale) const;
	//@}

    /** 
	  * \name Known localization initialization.
	  */
	//@{
	/** Initializes the list of known locales. Uses the the repository folder
      * and the base-name prefix to scan for valid files.
	*/
    void InitializeKnownLocales() const;
	/** Resets the known locales. Provided for optional cleanup on exit.
      * Note: to avoid multi-threading issue with other threads doing
      *       localization while the object is being reset, do *not* call
      *       this function for no reason.
	*/
    void ResetKnownLocales();
	//@}

    /** 
	  * \name Localization object access.
	  */
	//@{
	/** Retrieves the number of known locale.
	*/
    int GetKnownLocaleCount() const;
	/** Retrieve a locale name by index. Names are like "en", "fr", etc.
      * \param pIndex the locale index, zero-based.
	  * \return The indexed locale name or null.
	*/
    FbxString GetKnownLocale( int pIndex ) const;
	/** Retrieve a localization by locale name.
      * \param pLocale the locale name, ex: "en" or "en-US".
	  * \return The named localization or null.
	*/
    FbxLocalization* GetLocalization( const char* pLocale ) const;
	//@}

    /** 
      * \name Current locale access for logging.
      */
    //@{
    /** Retrieve the current localization in use for this particular manager.
      * \return The current localization.
    */
    FbxLocalization* GetCurrentLocalization() const;
    /** Set the current localization used for this particular manager.
      * \param  pLocale the name of the localization locale.
      * \return true if the locale was valid and could be loaded.
    */
    bool SetCurrentLocalization(const char* pLocale);

/*****************************************************************************************************************************
** WARNING! Anything beyond these lines is for internal use, may not be documented and is subject to change without notice! **
*****************************************************************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:
    FbxLocalizationManager_internal* mData;

    // Unimplemented, avoid copies.
    FbxLocalizationManager( const FbxLocalizationManager& );
    void operator=(const FbxLocalizationManager&);
#endif /* !DOXYGEN_SHOULD_SKIP_THIS *****************************************************************************************/
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_UTILS_LOCALE_H_ */

