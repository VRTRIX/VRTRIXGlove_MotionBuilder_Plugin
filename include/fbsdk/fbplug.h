#ifndef __FBPLUG_H__
#define __FBPLUG_H__
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

/** \file fbplug.h
*   Definition of the class FBPlug and related enums and utility functions.
*   All the Open Reality objects that expose application objects will inherit
*   from FBPlug.
*/

#include <kaydaradef.h>

#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

// Global includes
#include <object/i/icallback.h>
#include <fbsdk/fbdefines.h>
#include <fbsdk/fbscriptwrapper.h>
#include <fbsdk/fbarray.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {;
#endif

/** \def __FBClassImplementation 
*	For internal use only
*/
#define __FBClassImplementation( ThisComponent,pInternalClassId )	\
    int ThisComponent::TypeInfo=__FBRegisterTypeInfo(pInternalClassId);\
    int ThisComponent::GetInternalClassId() { return pInternalClassId; }

#define __FBClassImplementationGroup( ThisComponent, pInternalClass )	\
    __FBClassImplementation( ThisComponent,pInternalClass::ClassId )\
    const char* ThisComponent::ClassGroupName = pInternalClass::ClassGroupName;

FB_FORWARD( FBPlug );

//! Possible actions when a notify plug event occurs
enum FBConnectionAction
{
    // Connection notify actions
    kFBRequestConnectSrc = 0,//!< Request connection of source to destination.
    kFBRequestConnectDst,	//!< Request connection of destination to source.
    kFBConnectSrc,			//!< Connect source to destination.
    kFBConnectDst,			//!< Connect destination to source.
    kFBConnectedSrc,		//!< Connected source to destination.
    kFBConnectedDst,		//!< Connected destination to source.

    kFBRequestDisconnectSrc,//!< Request disconnection of source to destination.
    kFBRequestDisconnectDst,//!< Request disconnection of destination to source.
    kFBDisconnectSrc,		//!< Disconnect source from destination.
    kFBDisconnectDst,		//!< Disconnect destination from source.
    kFBDisconnectedSrc,		//!< Disconnected source from destination.
    kFBDisconnectedDst,		//!< Disconnected destination from source.

    kFBBeginReplaceSrc,		//!< Begin replace source during merge
    kFBEndReplaceSrc,		//!< End replace source during merge
    kFBBeginReplaceDst,		//!< Begin replace destination during merge
    kFBEndReplaceDst,		//!< End replace destination during merge
    kFBReorderSrc,			//!< Reorder of source
    kFBReorderedSrc,		//!< Source has been reordered

    kFBBeginChange,			//!< Begin change on destination.
    kFBEndChange,			//!< End change on destination.
    kFBConnectedOwner,		//!< Connected owner to destination.
    kFBDisconnectOwner,		//!< Disconnect owner from destination.

    // Data notify actions
    kFBCandidate,			//!< Data candidate event, before the data is set.
    kFBCandidated,			//!< Data candidate event, after the data is set.
    kFBCandidateGlobal,		//!< Data candidate event, global candidate.

    // State notify actions
    kFBDetached,			//!< Component detached from scene.
    kFBDestroy,				//!< Component destroy.

    kFBSelect,				//!< Component selection.
    kFBUnselect,			//!< Component de-selection.
    kFBReselect,			//!< Component re-selection.

    kFBRequestRename,       //!< Component request rename.
    kFBRename,				//!< Component is going to be renamed.
    kFBRenamed,				//!< Component has been renamed.

    kFBRequestPrefixRename, //!< Compoent request Prefix Rename.
    kFBPrefixRename,		//!< Component prefix is going to be renamed.
    kFBPrefixRenamed,		//!< Component prefix has been renamed.

    kFBDescription,			//!< Component description event.

    // Keying Notify actions
    kFBKeyingKey,			//!< Component keying add event.
    kFBKeyingDeleteKey,		//!< Component keying delete event.
    kFBKeyingCandidate,		//!< Component keying candidate event.
    kFBKeyingCurveChange,	//!< Component curve has changed.

    // for backward compatibility
    kFBConnect = kFBConnectSrc,
    kFBConnected = kFBConnectedSrc,
    kFBDisconnect = kFBDisconnectSrc,
    kFBDisconnected = kFBDisconnectedSrc
};

FBSDK_DLL const char* FBGetConnectionActionString( FBConnectionAction pAction );

//! Connection types available between plugs.
enum FBConnectionType
{
    kFBConnectionTypeNone,          //!< Default connection type.
    kFBConnectionTypeSystem         //!< System connection type.
};

enum FBPlugModificationFlag 
{
    kFBPlugAllContent						= 0,		//!< None Modified.
    kFBSelfDataModified						= 1 << 8,   //!< Object/Property itself has been dirty, in case of property get dirty, its owner object will be set dirty as well. 
    kFBContentDataModified					= 1 << 9,   //!< Owner object/Namespace has data dirty property/objects.  
    kFBAllDataModified                      = kFBSelfDataModified | kFBContentDataModified,

    kFBSelfKeyingModified					= 1 << 10,  //!< Object/Property itself has been dirty, in case of property get dirty, its owner object will be set dirty as well. 
    kFBContentKeyingModified				= 1 << 11,  //!< Owner object/Namespace has data dirty property/objects.  
    kFBAllKeyingModified                    = kFBSelfKeyingModified | kFBContentKeyingModified,

    kFBSelfStateModified					= 1 << 12,	//!< Object/Property naming change. 
    kFBContentStateModified					= 1 << 13,	//!< Owner object/Namespace has state dirty property/objects.
    kFBAllStateModified                     = kFBSelfStateModified | kFBContentStateModified,

    kFBSelfConnectionSrcObjectModified		= 1 << 14,	//!< The src object of this plug has been modified.
    kFBSelfConnectionSrcPropertyModified	= 1 << 15,	//!< The src property of this plug has been modified.
    kFBSelfConnectionDstObjectModified		= 1 << 16,	//!< The dst object of this plug has been modified.
    kFBSelfConnectionDstPropertyModified	= 1 << 17,	//!< The dst property of this plug has been modified.
    kFBSelfConnectionModifiedMask			= kFBSelfConnectionSrcObjectModified | kFBSelfConnectionSrcPropertyModified | kFBSelfConnectionDstObjectModified | kFBSelfConnectionDstPropertyModified,
    kFBContentConnectionModified			= 1 << 18,	//!< Owner object/namespace	has connection modified property/objects.
    kFBAllConnectionModified                = kFBSelfConnectionModifiedMask | kFBContentConnectionModified,

    kFBSelfCustomPropertyModified           = 1 << 19,  //!< Object custom property change.
    kFBContentCustomPropertyModified        = 1 << 20,  //!< Owner object/Namespace has dirty property/objects. 
    kFBAllCustomPropertyModified            = kFBSelfCustomPropertyModified | kFBContentCustomPropertyModified,

    kFBSelfAllModifiedMask					= kFBSelfDataModified    | kFBSelfKeyingModified    | kFBSelfStateModified    | kFBSelfCustomPropertyModified | kFBSelfConnectionModifiedMask,
    kFBContentAllModifiedMask				= kFBContentDataModified | kFBContentKeyingModified | kFBContentStateModified | kFBContentCustomPropertyModified | kFBContentConnectionModified,
    kFBAllModifiedMask						= kFBSelfAllModifiedMask | kFBContentAllModifiedMask
};

enum FBPlugStatusFlag
{
    kFBPlugStatusFlagNone                 = 0,		//!< Plug has no status set.
    kFBOwnedByUndo                        = 1<<21,	//!< Plug is owned by undo framework.
    kFBPlugStatusFlagMask                 = kFBOwnedByUndo
};

//! typedef FBArrayTemplate<FBPlug*> FBPlugList;
typedef FBArrayTemplate<FBPlug*> FBPlugList;

/**	Create a FBPlugList object.
*	This is to get around memory management issues when mixing debug and release runtime
*   libraries on Windows. By using the FBCreateObjectList/FBDestroyObjectList
*   duo of functions, you ensure that the memory used in the array is allocated,
*   reallocated and freed in the same memory pool.
*/
FBSDK_DLL FBPlugList* FBCreatePlugList();

/** Delete a FBPlugList object.
*   \param  pPlugList  pointer to the object created with a call to FBCreatePlugList().
*/
FBSDK_DLL void FBDestroyPlugList( FBPlugList* pPlugList );

FBSDK_DLL const char* FBGetConnectionTypeString( FBConnectionType pType );

/** Connections Basic Open Reality SDK Element.
*   Most elements that are available in the SDK inherit from this base class since
*   FBComponent and FBProperty inherit from FBPlug. Basically, all objects can be
*	connected together because they are all "plugs". To simplify the graph, you
*	can think of a "source" connection as a child, and a "destination" connection
*	as a parent. Also, it is correct to assume that a source affect/work on its
*	destination. For example, a shader applied on an object would be seen as the
*	source while the object is the destination. So FBPlug is a set of functions
*	that enables you to control those connections with flexibility and ease.
*/
class FBSDK_DLL FBPlug : public ICallback
    , public FBWrapperHolder
{
protected:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    /**! Constructor
    *   Internal use only. 
    *   User code shouldn't instantiate FBPlug directly. 
    */
    FBPlug( HIObject pObject );
public:
    //! Destructor
    virtual ~FBPlug();

    //! Return an internal pointer.
    virtual HIObject GetHIObject() const;

    //! Assign component to an internal pointer.
    virtual bool SetHIObject( HIObject pObject, bool pSDKComponent );
#endif

    //! Return whether or not item is an SDK component.
    bool IsSDKComponent();

    /** Add a source connection.
    *   \param pSrc				Source plug.
    *   \param pConnectionType  Type of connection, taken from FBConnectionType. Default value should work in all cases.
    *   \return                 A boolean indicating success (True) or failure (False).
    */
    bool                ConnectSrc( FBPlug* pSrc, FBConnectionType pConnectionType=kFBConnectionTypeNone );

    /** Add a destination connection.
    *   \param pDst				Destination plug.
    *   \param pConnectionType  Type of connection, taken from FBConnectionType. Default value should work in all cases.
    *   \return                 A boolean indicating success (True) or failure (False)
    */
    bool                ConnectDst( FBPlug* pDst, FBConnectionType pConnectionType=kFBConnectionTypeNone );

    /** Add a source connection.
    *	\param pDst_SrcIndex	Index that tells where to add this source connection in the destination's connection list.
    *                           if index is out of bound, and this source connection will be appended at the end.
    *   \param pSrc				Source plug.
    *   \param pConnectionType  Type of connection, taken from FBConnectionType. Default value should work in all cases.
    *   \return                 A boolean indicating success (True) or failure (False).
    */
    bool                ConnectSrcAt( int pDst_SrcIndex, FBPlug* pSrc, FBConnectionType pConnectionType=kFBConnectionTypeNone );

    /** Add a destination connection.
    *	\param pSrc_DstIndex	Index that tells where to add this destination connection in the source's connection list.
    *                           if index is out of bound, and this destination connection will be appended at the end.
    *   \param pDst				Destination plug.
    *   \param pConnectionType  Type of connection, taken from FBConnectionType. Default value should work in all cases.
    *   \return                 A boolean indicating success (True) or failure (False).
    */
    bool                ConnectDstAt( int pSrc_DstIndex, FBPlug* pDst, FBConnectionType pConnectionType=kFBConnectionTypeNone );

    /** Remove a destination connection.
    *   \param pDst	Destination plug.
    *   \return		A boolean indicating success (True) or failure (False).
    */
    bool                DisconnectDst( FBPlug* pDst );

    /** Remove a source connection.
    *   \param pSrc	Source plug.
    *   \return		A boolean indicating success (True) or failure (False).
    */
    bool                DisconnectSrc( FBPlug* pSrc );

    /** Remove all source connections. */
    void                DisconnectAllSrc();

    /** Remove all destination connections. */
    void                DisconnectAllDst();

    /** Remove a destination connection at a specified index.
    *   \param pIndex	Destination plug index.
    *   \return			A boolean indicating success (True) or failure (False).
    */
    bool                DisconnectDstAt( int pIndex );

    /** Remove a source connection at a specified index.
    *   \param pIndex	Source plug index.
    *   \return			A boolean indicating success (True) or failure (False).
    */
    bool                DisconnectSrcAt( int pIndex );

    /** Replace a destination connection at a specified index.
    *   \param pIndex	Destination plug index.
    *   \param pDst		Plug that will replace the other at index.
    *   \return			A boolean indicating success (True) or failure (False).
    */
    bool                ReplaceDstAt( int pIndex, FBPlug* pDst );

    /** Replace a source connection at a specified index.
    *   \param pIndex	Source plug index.
    *   \param pSrc		Plug that will replace the other at index.
    *   \return			A boolean indicating success (True) or failure (False).
    */
    bool                ReplaceSrcAt( int pIndex, FBPlug* pSrc );

    /** Swap source connection at index A with source connection at index B.
    *   \param pIndexA	Plug index.
    *   \param pIndexB	Other plug index.
    *   \return			A boolean indicating success (True) or failure (False).
    */
    bool                SwapSrc( int pIndexA, int pIndexB );

    /** Move source connection at pIndex to pAtIndex.
    *   \param pIndex	Plug current index.
    *   \param pAtIndex	Plug new index.
    *   \return			A boolean indicating success (True) or failure (False).
    *	\remarks		This is not like the swap function since the connection at pAtIndex is untouched.
    */
    bool                MoveSrcAt( int pIndex, int pAtIndex );

    /** Move source connection pSrc to the position of pAtSrc.
    *   \param pSrc		Plug.
    *   \param pAtSrc	Plug that mark where we want to insert (will insert before this one).
    *   \return			A boolean indicating success (True) or failure (False).
    *	\remarks			This is not like the swap function since the connection at pAtSrc is untouched.
    */
    bool                MoveSrcAt( FBPlug* pSrc, FBPlug* pAtSrc );

    /** Get source connection count.
    *   \return	Total sources connections count.
    */
    int                 GetSrcCount();

    /** Get a source connection's plug at specified index.
    *	\param	pIndex	Index of the source connection's plug.
    *   \return			Source plug at specified index.
    */
    FBPlug*             GetSrc( int pIndex );

    /** Get a source connection's type at specified index.
    *	\param	pIndex	Index of the source connection's type.
    *   \return			Source connection's type at specified index.
    */
    FBConnectionType    GetSrcType( int pIndex );

    /** Get destination connection count.
    *   \return	Total destinations connections count.
    */
    int                 GetDstCount();

    /** Get a destination connection's plug at specified index.
    *	\param	pIndex	Index of the destination connection's plug.
    *   \return			Destination plug at specified index.
    */
    FBPlug*             GetDst( int pIndex );

    /** Get a destination connection's type at specified index.
    *	\param	pIndex	Index of the destination connection's type.
    *   \return			Destination connection's type at specified index.
    */
    FBConnectionType    GetDstType( int pIndex );

    /** Begins a change on multiple plugs.
    *   \return	A boolean indicating success (True) or failure (False).
    */
    bool                BeginChange();

    /** Ends a change on multiple plugs. */
    void                EndChange();

    /** Set the plug's self modification flag.
    *	\param pFlag	bitwise AND of self modification flags. 
    *	\param pBool	true if self changed.
    */
    void				SetSelfModified(FBPlugModificationFlag pFlag, bool pBool);

    /** Tell if the plug's self has changed.
    *	\param pFlag	bitwise AND of self modification flags. 
    *	\return			true if self changed
    */
    bool				GetSelfModified(FBPlugModificationFlag pFlag);	

    /** Set the plug's owned property/object's modification flag.
    *	\param  pFlag	bitwise AND of content modification flags. 
    *	\param	pBool	true if content has modification.
    */
    void                SetContentModified(FBPlugModificationFlag pFlag, bool pBool);

    /** Tell if the plug's content has changed.
    *	\param pFlag	bitwise AND of content modification flags. 
    *	\return			true if content connection changed.
    */
    bool                GetContentModified(FBPlugModificationFlag pFlag);

    /** Get plug's modified src/dst property/object connection added/removed List.
    *	\param  pPlugList					plug list to fill up.
    *	\param  pConnectionModificatonFlag	Src/Dst Property/Object connection modification flag.
    *	\param  pAddRemove					Ask for the added list if true, removed list if false.
    *	\return						        count of list;
    */
    int					GetPlugConnectionModifiedList(FBPlugList& pPlugList, FBPlugModificationFlag pConnectionModificatonFlag, bool pAddRemove);

    /** Revert the plug's modification to original status. 
    *   \param pFlag    the type of modification to be reverted.
    *   \return         true if revert successfully.
    */
    bool                RevertModification(FBPlugModificationFlag pFlag = kFBAllModifiedMask);

    /** Set the plug's status flag.
    *	\param  pStatus	bitwise AND of status flags. 
    *	\param	pValue	true if status has modification.
    */
    void                SetStatusFlag(FBPlugStatusFlag pStatus, bool pValue);

    /** Tell if the plug's status has changed.
    *	\param pStatus	bitwise AND of self modification flags. 
    *	\return			true if self changed
    */
    bool                GetStatusFlag(FBPlugStatusFlag pStatus) const;

    /** Get the owner of this plug. Very useful for properties since they are plugs too.
    *   \return	The owner of this plug.
    */
    FBPlug*             GetOwner();

    /** Get the owned plug at specified index.
    *	\param	pIndex	Index of the owned plug to get.
    *   \return			The owned plug at specified index.
    */
    FBPlug*             GetOwned( int pIndex );

    /** Get the owned plug count.
    *   \return	The owned plug count.
    */
    int                 GetOwnedCount();

    //! internal System vars.
    virtual const char* ClassName();
    //!Is( int pTypeId )
    /**	\param pTypeId Type Identification.
    *	\return True if Plug is a Instance of pTypeId.
    */
    virtual bool        Is( int pTypeId );

    //!GetTypeId( int pTypeId )
    /**	
    *	\return The TypeInfo of the object
    */
    virtual int        GetTypeId();

    //! ClassGroupName of the object.
    static const char* ClassGroupName;

    //! TypeInfo
    static int TypeInfo;

    //! Contain the Allocation State of the Component
    bool			mAllocated;

    /** PlugDataNotify when overloaded is equivalent of FBSystem.OnConnectionDataNotify but in the context of the derived object only
    * \param pAction Plug action, the event type.
    * \param pThis Plug concerned.
    * \param pData Current data, meaning depends of plug action.
    * \param pDataOld Previous data, meaning depends of plug action.
    * \param pDataSize Size of data.
    * \return unused should return true
    */
    virtual	bool PlugDataNotify(FBConnectionAction pAction,FBPlug* pThis,void* pData=NULL,void* pDataOld=NULL,int pDataSize=0);

    /** PlugStateNotify when overloaded is equivalent of FBSystem.OnConnectionStateNotify but in the context of the derived object only
    * \param pAction Plug action, the event type.
    * \param pThis Plug concerned.
    * \param pData Current data, meaning depends of plug action.
    * \param pDataOld Previous data, meaning depends of plug action.
    * \param pDataSize Size of data.
    * \return unused should return true except in the case of property rename kFBRename
    */
    virtual	bool PlugStateNotify(FBConnectionAction pAction,FBPlug* pThis,void* pData=NULL,void* pDataOld=NULL,int pDataSize=0);

    /** PlugNotify when overloaded is equivalent of FBSystem.OnConnectionNotify but in the context of the derived object only
    * \param pAction Plug action, the event type.
    * \param pThis Plug concerned.
    * \param pIndex Index of the plug.
    * \param pPlug Other plug concerned.
    * \param pConnectionType Connection type between the plugs.
    * \param pNewPlug New plug (for the replace event).
    * \return should by default return true except in the case of connection requests (kFBRequestConnectSrc or kFBRequestConnectDst)
    */
    virtual	bool PlugNotify(FBConnectionAction pAction,FBPlug* pThis,int pIndex,FBPlug* pPlug = NULL,FBConnectionType pConnectionType=kFBConnectionTypeNone,FBPlug* pNewPlug=NULL );

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    IObject_Declare(K_IMPLEMENTATION);
    ICallback_Declare(K_IMPLEMENTATION);

    /** Print out internal Class (ID) Definition table.
    *   For internal debug purpose only. 
    */
    static void   PrintClassDefinitions();

#endif

protected:
    /** Actual destructor for a FBPlug.
    *   It should never be called from client code. This is meant for internal use only!
    */
    virtual void        FBDelete();

    static int          mGlobalTypeInfo; 		//!< Represente the Type Index.
    static int			GetInternalClassId();	//!< Internal class Id
    HIObject            mObject;		 		//!< Handle on the Plug.
    bool                mSDKComponent;	 		//!< bool Plug is an SDK component.    
    FBSDK_DLL friend int __FBRegisterTypeInfo(int pInternalClassId);
};


////////////////////////////////////////////////////////////////////////////////////
// Connection related utility functions.
////////////////////////////////////////////////////////////////////////////////////
/** Request the connection two FBPlug objects.
*   \param pSrc             Source plug.
*   \param pDst             Destination plug.
*   \param pConnectionType  Type of connection, taken from FBConnectionType.
*   \return                 A boolean indicating success (True) or failure (False).
*   \remark                 This global function is used primarily to connect connectors in a FBConstraintRelation.
*/
FBSDK_DLL bool FBConnect( FBPlug* pSrc, FBPlug* pDst, FBConnectionType pConnectionType=kFBConnectionTypeNone );

/** Connect two FBPlug objects.
*   \param pSrc             Source plug.
*   \param pDst             Destination plug.
*   \return                 A boolean indicating success (True) or failure (False).
*   \remark                 This global function is used primarily to disconnect connectors in a FBConstraintRelation.
*/
FBSDK_DLL bool FBDisconnect( FBPlug* pSrc, FBPlug* pDst );

/**	Get the FBPlug from an Internal Object.
*	\param	pObject		Object to get SDK object for.
*	\param	pAutoCreate	Create object if it doesn't exist? (default is \b true)
*	\return	FBComponent for \e pObject.
*/
FBSDK_DLL FBPlug*       FBGetFBPlug( HIObject pObject, bool pAutoCreate=true );

/**	Get the SDK object from an Internal Object.
*	\param	pObject			Object to get SDK object for.
*	\param	pAutoCreate		Create object if it doesn't exist? (default = false)
*	\return	SDK object for \p pObject.
*/
FBSDK_DLL HIObject		FBGetFBObject( HIObject pObject, bool pAutoCreate=false );

/**	Cast the SDK object using it's IObject interface into the proper class.
*	\param	pObject			Object to get SDK object for.
*	\param	pAutoCreate		Create object if it doesn't exist? (default = false)
*	\return	SDK object for \p pObject.
*/
template<class T> inline T* FBCast(HIObject pObject, bool pAutoCreate = false)
{
    HIObject lObject = FBGetFBObject(pObject, pAutoCreate);
    // Should also validate type but not available for now
    return (T*)lObject;
}

/** Handler of FBPlug object
*   Use this handler object to gracefully take care of dangling pointer problem.
*   For example, you created FBCamera object and hold it's pointer address to further usage,
*   However, this FBCamera object could be destroyed by the application internally at any 
*   moment and its pointer you currently hold is invalid. But you don't easy way to tell so. 
*   This HdlFBPlug class provide means to handle this case gracefully. 
*/
class FBSDK_DLL HdlFBPlug 
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    HdlFBPlug();			  
    HdlFBPlug(const FBPlug * pFBPlug); 
    HdlFBPlug(HdlFBPlug const &pFBPlug); 
    ~HdlFBPlug();			  

    // VALIDATION
    bool Ok() const;

    //!Is( int pTypeId )
    /**	\param pTypeId Type Identification.
    *	\return True if Plug is a Instance of pTypeId.
    */
    bool Is( int pTypeId );

    //bool WasOk() const;
    //int	RefCount() const;

    // CASTING & ASSIGNATION
    HdlFBPlug&      operator= (const FBPlug*    pFBPlug); 
    HdlFBPlug&      operator= (const HdlFBPlug& pFBPlug); 

    // Comparison 
    bool			operator==(const HdlFBPlug& pFBPlug) const; 
    bool			operator!=(const HdlFBPlug& pFBPlug) const; 

    FBPlug*	        GetPlug() const;
    inline  FBPlug*	operator()() const { return GetPlug(); }
    inline  FBPlug*	operator->() const { return GetPlug(); }

    inline operator FBPlug* () const 
    { 
        return (FBPlug *)GetPlug(); 
    }


protected:
    void SetPlug(const FBPlug*    pFBPlug); 

private:
    void * mData;
};

template <class T> class HdlFBPlugTemplate : public HdlFBPlug
{
public:
    HdlFBPlugTemplate()
    {
    }

    HdlFBPlugTemplate(HdlFBPlug const &pPlug)	
        : HdlFBPlug(pPlug) 
    {
    }

    HdlFBPlugTemplate(const FBPlug *pPlug)	
        : HdlFBPlug((FBPlug *)pPlug) 
    {
    }

    HdlFBPlugTemplate<T>& operator=(const HdlFBPlugTemplate<T>& pPlug)
    { 
        SetPlug(pPlug.GetPlug());
        return *this;
    }

    bool operator==(const HdlFBPlugTemplate<T>& pFBPlug) const
    {
        return GetPlug() == pFBPlug.GetPlug();
    }

    bool operator!=(const HdlFBPlugTemplate<T>& pFBPlug) const
    {
        return GetPlug() != pFBPlug.GetPlug();
    }

    T* operator()() const			
    { 
        return (T *)GetPlug(); 
    }

    T* operator->() const			
    { 
        return (T *)GetPlug(); 
    }

    operator T*() const 
    { 
        return (T *)GetPlug(); 
    }
};

#ifdef FBSDKUseNamespace
}
#endif

#endif
