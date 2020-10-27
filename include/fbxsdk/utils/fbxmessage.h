/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file fbxmessage.h
#ifndef _FBXSDK_UTILS_MESSAGE_H_
#define _FBXSDK_UTILS_MESSAGE_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxstring.h>
#include <fbxsdk/core/base/fbxarray.h>

#include <fbxsdk/core/base/fbxmap.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxLocalization;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class is a single typed log message. It can be formatted and localized.
  * \nosubgrouping
  */
class FBXSDK_DLL FbxMessage
{
public:
    FBXSDK_FRIEND_NEW();
    static const char* sClassName;

    static FbxMessage* Create(const char* pClassName = sClassName);
    virtual void Destroy();

    bool IsClass(const char* pClassName) const;

    /** \name Convenience functions to add a property. because they return the object, they can easily be chained.
      */
    //@{
    /** Add a text property.
      * \param pPropName the property name (without surrounding {}).
      * \param pText the text value of the property.
      * \return the FbxMessage.
    */
    FbxMessage* Add( const char* pPropName, const char* pText );
    /** Add a integer property.
      * \param pPropName the property name (without surrounding {}).
      * \param pValue the value of the property.
      * \return the FbxMessage.
    */
    FbxMessage* Add( const char* pPropName, int pValue );
    /** Add a double-precision number property.
      * \param pPropName the property name (without surrounding {}).
      * \param pValue the value of the property.
      * \return the FbxMessage.
    */
    FbxMessage* Add( const char* pPropName, double pValue );
    /** Add a boolean property.
      * \param pPropName the property name (without surrounding {}).
      * \param pValue the value of the property.
      * \return the FbxMessage.
    */
    FbxMessage* Add( const char* pPropName, bool pValue );
    /** Add a blob property.
      * \param pPropName the property name (without surrounding {}).
      * \param pData the blob data of the property.
      * \param pDataSize the blob size in bytes.
      * \return the FbxMessage.
    */
    FbxMessage* Add( const char* pPropName, const void* pData, int pDataSize );
    //@}

    bool Get(const char* pPropName, FbxString& pValue) const;
    bool Get(const char* pPropName, int& pValue) const;
    bool Get(const char* pPropName, double& pValue) const;
    bool Get(const char* pPropName, bool& pValue) const;
    bool Get(const char* pPropName, void*& pValue, int& pLen) const;

/*****************************************************************************************************************************
** WARNING! Anything beyond these lines is for internal use, may not be documented and is subject to change without notice! **
*****************************************************************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    friend class FbxMessageSerializer;

    FbxMessage();
    FbxMessage(const char* pClassName);
    virtual ~FbxMessage();

    virtual FbxString GetClassName() { return "FbxMessage"; }

    FbxString Serialize(const FbxString& pData) const;
    FbxString Serialize(const int pData) const;
    FbxString Serialize(const double pData) const;
    FbxString Serialize(const bool pData) const;
    FbxString Serialize(const void* pData, int pSize) const;

    void Unserialize(const char* pSerializedData, FbxString& pValue) const;
    void Unserialize(const char* pSerializedData, int& pValue) const;
    void Unserialize(const char* pSerializedData, double& pValue) const;
    void Unserialize(const char* pSerializedData, bool& pValue) const;
    void Unserialize(const char* pSerializedData, void*& pData, int& pDecodedBytes) const;

    typedef FbxMap<FbxString, FbxString> ValueMap;
    ValueMap mValues;
#endif /* !DOXYGEN_SHOULD_SKIP_THIS *****************************************************************************************/
};


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class can be registered with a message emitter to receive the messages.
  * \nosubgrouping
  */

class FBXSDK_DLL FbxMessageListener
{
public:
    virtual ~FbxMessageListener();

    /**
      * \name Message reception.
      */
    //@{
    /** Receive a message.
      * \param pMessage The message. Should not be modified nor deleted.
    */
    virtual void ReceiveLogMessage( FbxMessage* pMessage ) = 0;
    //@}

    /**
      * \name Helper function to format a time stamp.
      */
    //@{
    enum { TimeStampBufferCapacity = 20 };
    static const char* GetTimeStamp( char* pBuffer, int pCapacity /* >= TimeStampBufferCapacity */ );
    //@}

protected:

};


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/** This class receives log messages and dispatch them to listeners.
  * \nosubgrouping
  */

class FBXSDK_DLL FbxMessageEmitter
{
public:
    virtual ~FbxMessageEmitter();

    /**
      * \name Manage listeners.
      */
    //@{
    /** Adds a listener. Listener must exist until removed.
      * \param pListener The listener to add to this emitter.
    */
    virtual void AddListener( FbxMessageListener& pListener );
    /** Removes a listener.
      * \param pListener The listener to remove from this emitter.
    */
    virtual void RemoveListener( FbxMessageListener& pListener );
    /** Retrieves the number of registered listener.
      * \return the number of registered listeners
    */
    virtual int GetListenerCount() const;
    /** Retrieves a listener.
	  * \param pIndex The listener index.
      * \return the registered listener at the specified index (0-based).
    */
    virtual FbxMessageListener& GetListener(int pIndex );
    //@}

    /**
      * \name Message queuing.
      */
    //@{
    /** Queues the message to be sent to listeners. The timing of the send is unspecified.
      * \param pMessage the message to be sent. Ownership is transferred to this emitter.
    */
    virtual void LogMessage( FbxMessage* pMessage );
    //@}

protected:
    /**
      * \name Message dispatching to listeners.
      */
    //@{
    /** Sends the message to all listeners.
      * \param pMessage the message to be sent.
    */
    virtual void DispatchLogMessage( FbxMessage* pMessage );
    //@}

/*****************************************************************************************************************************
** WARNING! Anything beyond these lines is for internal use, may not be documented and is subject to change without notice! **
*****************************************************************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    typedef FbxArray<FbxMessageListener*> LogListeners;
    LogListeners mLogListeners;
#endif /* !DOXYGEN_SHOULD_SKIP_THIS *****************************************************************************************/
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_UTILS_MESSAGE_H_ */
