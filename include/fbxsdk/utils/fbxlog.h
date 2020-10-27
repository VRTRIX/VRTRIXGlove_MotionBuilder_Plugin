/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file fbxlog.h
#ifndef _FBXSDK_UTILS_MSG_LOG_H_
#define _FBXSDK_UTILS_MSG_LOG_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxstatus.h>
#include <fbxsdk/core/base/fbxstring.h>
#include <fbxsdk/core/base/fbxarray.h>
#include <fbxsdk/core/base/fbxmap.h>
#include <fbxsdk/utils/fbxmessage.h>
#include <fbxsdk/utils/fbxlocale.h>

#include <fbxsdk/fbxsdk_nsbegin.h>


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class is for log messages.
  * \nosubgrouping
  */

class FBXSDK_DLL FbxLogMsg : public FbxMessage
{
public:
    /**
      * \name Some pre-defined message types for the different types
      *       of log messages.
      */
    //@{
    static const char sClassName[];
    static const char sDebugClassName[];
    static const char sInfoClassName[];
    static const char sWarningClassName[];
    static const char sFatalClassName[];
    static const char sErrorClassName[];
    static const char sProgressClassName[];
    static const char sBeginOperationClassName[];
    static const char sEndOperationClassName[];
    static const char sJournalInformationClassName[];
    static const char sInvalidImageFilesClassName[];
    static const char sFbxOOPCrashErrorClassName[];
    static const char sInsufficientDiskErrorClassName[];
    static const char sInsufficientMemoryErrorClassName[];
    static const char sPluginErrorClassName[];
    //@}

    /**
      * \name Helper functions to create pre-defined message types.
      *       Consciously made non-member so that new version will
      *       be on "equal footing".
      */
    //@{
	static FbxLogMsg* Create(const char* pClassName = sClassName);

	static FbxLogMsg* CreateDebugLogMsg(const char * pMessage, const char * pID = NULL);
	static FbxLogMsg* CreateInfoLogMsg(const char * pMessage, const char * pID = NULL);
	static FbxLogMsg* CreateWarningLogMsg(const char * pMessage, const char * pID = NULL);
	static FbxLogMsg* CreateFatalLogMsg(const char * pMessage, const char * pID = NULL);
	static FbxLogMsg* CreateErrorLogMsg(const char * pMessage, const char * pID = NULL);
	static FbxLogMsg* CreateErrorLogMsg(const FbxStatus & pError, const char * pID = NULL);

	static FbxLogMsg* CreateProgressLogMsg(const char * pOperation, double pProgress, const char * pID = NULL);
	static FbxLogMsg* CreateBeginOperationLogMsg(const char * pOperation, const char * pID = NULL,
									double pGranularity = 10., double pInitialCompleteness = 0.);
	static FbxLogMsg* CreateEndOperationLogMsg(const char * pOperation, const char * pID = NULL);

	static FbxLogMsg* CreateJournalLogMsg(    const char * pMessage, const char * pID = NULL);

	static FbxLogMsg* CreateInvalidImageFilesLogMsg(const char * pMessage, const char * pID = NULL);

	static FbxLogMsg* CreateFbxOOPCrashErrorLogMsg(const char * pMessage, const char * pID = NULL);
	static FbxLogMsg* CreateInsufficientDiskErrorLogMsg(const char * pMessage, const char * pID = NULL);
	static FbxLogMsg* CreateInsufficientMemoryErrorLogMsg(const char * pMessage, const char * pID = NULL);
	static FbxLogMsg* CreatePluginErrorLogMsg(const char * pMessage, int pMessageCode = -1, const char * pID = NULL);
    //@}

    virtual void Destroy();

    // Property names
    static const char* sRawMessageName;     // the content of the message
    static const char* sIDName;             // the pId of the message used for localization
    static const char* sMessageCode;        // message code for the message  

    /** \name Message formatting into a text buffer.
      */
    //@{
    /** Format a message with an optional localization. Localization uses either the message ID or the message itself for lookup.
      * The message supports property substitutions using the following format:  
      * "This is a string {prop1} with a parameter"
      * 
      * "{" can be escaped in two ways: \{ or {{, the latter to be compatible with Mental Ray escaping rules.
      * \param pBuffer the buffer to received the formatted message.
      * \param pCapacity the capacity of the buffer, in characters.
      * \param pLoc the optional localization. If null, no translation will be done.
      * \return true if successful.
    */
    virtual bool Format( char * pBuffer, int pCapacity, FbxLocalization * pLoc = NULL );
    //@}

    /** \name Log message prefix based on run-time class ID.
      */
    //@{
    /** Map from a run-time class ID to a string for log message types.
      * For example: FbxErrorMsg -> ERROR, FbxWarningMsg -> WARNING, etc.
      * \return the prefix or "LOG" if not found.
      */
    virtual const char * GetMessagePrefix() const;
    /** Register a class ID to string mapping.
      * \param pID the class ID to map.
      * \param pPrefix the corresponding prefix to be used in logs.
      */
    static void RegisterMessagePrefix( const char* pID, const char * pPrefix );

	/** Unregister a class ID
	* \param pID the class ID to map.
	*/
	static void UnregisterMessagePrefix( const char* pID);
    //@}

protected:
    FbxLogMsg();
    FbxLogMsg(const char* pClassName);
    ~FbxLogMsg();
    virtual FbxString GetClassName() { return "FbxLogMsg"; }

private:
	typedef FbxMap<FbxString, FbxString> LogPrefixMap;
	static LogPrefixMap sLogPrefixes;

    FBXSDK_FRIEND_NEW();
};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class contains the localization settings for logging sub-classes that needs it.
  * \nosubgrouping
  */

class FBXSDK_DLL FbxLogBase : public FbxMessageListener
{
public:
    FbxLogBase();
    ~FbxLogBase();
    /** Retrieves the localizations manager for the loggers.
	 */
    FbxLocalizationManager& GetLocalizationManager();

protected:
    FbxLocalizationManager mLogLocalizationManager;
};


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class contains the console log consumer.
  * \nosubgrouping
  */

class FBXSDK_DLL FbxLogConsole : public FbxLogBase
{
public:
    FbxLogConsole( const char * pUnused = NULL );
    virtual ~FbxLogConsole();

/*****************************************************************************************************************************
** WARNING! Anything beyond these lines is for internal use, may not be documented and is subject to change without notice! **
*****************************************************************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    virtual void ReceiveLogMessage(FbxMessage *);
#endif /* !DOXYGEN_SHOULD_SKIP_THIS *****************************************************************************************/
};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class contains the callback log consumer.
  * \nosubgrouping
  */

class FBXSDK_DLL FbxLogCallback : public FbxLogBase
{
public:
    FbxLogCallback(const char * pUnused = NULL);
    virtual ~FbxLogCallback();

    typedef void (*CallbackFunction)(FbxMessage *,
                                     void* pUserData);

    void SetCallback(CallbackFunction pFunction, void* pUserData = NULL);

/*****************************************************************************************************************************
** WARNING! Anything beyond these lines is for internal use, may not be documented and is subject to change without notice! **
*****************************************************************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    virtual void ReceiveLogMessage(FbxMessage *);

protected:
    CallbackFunction mCallbackFunction;
    void* mUserData;
#endif /* !DOXYGEN_SHOULD_SKIP_THIS *****************************************************************************************/
};


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class contains the log file consumer.
  * \nosubgrouping
  */

class FBXSDK_DLL FbxLogFile : public FbxLogBase
{
public:
    FbxLogFile( const char * pUnused = NULL );
    virtual ~FbxLogFile();

    void SetFile(const char* pFileName, bool pTruncate);
    void CloseFile();

/*****************************************************************************************************************************
** WARNING! Anything beyond these lines is for internal use, may not be documented and is subject to change without notice! **
*****************************************************************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    virtual void ReceiveLogMessage(FbxMessage *);

protected:
    FbxString mFileName;
    FILE* mFile;
#endif /* !DOXYGEN_SHOULD_SKIP_THIS *****************************************************************************************/
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_UTILS_MSG_LOG_H_ */
