#ifndef __FBCONSTRUCTIONHISTORY_H__
#define __FBCONSTRUCTIONHISTORY_H__
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

/** \file fbconstructionhistory.h
*   Construction History.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
    #define FBSDK_DLL K_DLLIMPORT
#endif
#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbarray.h>
#include <fbsdk/fbplug.h>
#include <fbsdk/fbstring.h>

class KConstructionOperation;

#ifdef FBSDKUseNamespace
    namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBConstructionHistory
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBConstructionHistory );
__FB_FORWARD( FBConstructionOperation );
FB_DEFINE_COMPONENT( FBSDK_DLL, ConstructionHistory );

FB_DEFINE_ARRAY(FBSDK_DLL, Plug);

/** FBConstructionOperation is used to represent an operation in the construction history. The operation can be any valid script.
*   Currently, only python scripts are supported. 
*
*   An instance of this class defaults to the correct value in order to add a new construction history. If the workgroup plugin is loaded, the operation
*   will be replicated on all machine within a session.
*/
class FBSDK_DLL FBConstructionOperation
{
	friend class FBConstructionHistory;
public:

    /** Constructor.
    */
    FBConstructionOperation();
	FBConstructionOperation(const FBConstructionOperation* pOperation);

	const char*	GetLanguage();
	int			GetLanguageVersion();
	const char*	GetScript();
    const char*	GetOrigin();
	int			GetCommandId();
    bool        GetExecuteAsLocalOperation();

	/**	SetLanguage
	*	Set the script language for this operation. Currently only "python" is supported.
	*
	*	\param	language Langugage string. Default to construction history's code generator's language (Currently "python").
	*/
	void		SetLanguage( const char* language );

	/**	SetLanguageVersion
	*	Set the script language interpreter's version that this operation should be interpreted with.
	*
	*	\param	version Version number. Defaults to construction history's code generator's version (Currently 1).
	*/
	void		SetLanguageVersion( int version );

	/**	SetScript
	*	Set the script content for this operation.
	*
	*	\param	script Script content as a string. Defaults to empty.
	*/
	void		SetScript( const char* script );

	/**	SetCommandId
	*	Set the operation's Id so that operation transactions can be resolved properly (eg: command 1 should go before command 2). Set this to -1 for new operations.
	*
	*	\param	commandId Command Id. Defaults to -1.
	*/
	void		SetCommandId( int commandId );

	/**	SetOrigin
	*	Set operation's original creator. For instance "localhost" or http://192.0.0.1:9000. Should mostly be "localhost" for new operations.
	*
	*	\param	origin Operation's Origin. Defaults to "localhost".
	*/
	void        SetOrigin( const char* origin );

	/**	SetExecuteAsLocalOperation
	*	Whether to execute this operation as local or remote. If this is set to false (remote) and an operation is sent to the construction history, it will 
	*   also execute locally on this motionbuilder.
	*
	*	\param	bIsLocal Defaults to true (local).
	*/
	void        SetExecuteAsLocalOperation( bool bIsLocal );

private:
	KConstructionOperation*	mOperation;
	bool					mExecuteAsLocal;
};

/** Simple wrapper for construction operation arrays
*
*/
class FBSDK_DLL	FBConstructionOperationArray : public FBArrayTemplate<FBConstructionOperation*>
{
	/** Disabled copy constructor.
    *   Voluntarily making the copy constructor unavailable.
    */
    FBConstructionOperationArray( const FBConstructionHistory& );

    /** Disabled assignment operator.
    *   Voluntarily making the assignment operator unavailable.
    */
    FBConstructionOperationArray& operator=( const FBConstructionHistory& );

public:

	 /** Constructor.
    */
    FBConstructionOperationArray();

	/** Destructor.
    */
	~FBConstructionOperationArray();
};

//! Construction history manager state
enum FBConstructionHistoryState {
	kFBConstructionHistory_Listening,	        //!< Construction history is currently listening and recording operations
	kFBConstructionHistory_Replaying	        //!< Construction history is currently replaying an operation
};

/** Event to retrieve the command id of a construction history change.
*
*/
class FBSDK_DLL FBEventConstructionHistoryChange : public FBEvent 
{
public:

    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventConstructionHistoryChange( HKEventBase pEvent );		

    /**	GetCommandId
	*	Returns the index of the command that was executed in the construction history
	*
	*	\return	the index of the command
	*/
    int GetCommandId();
};

/** Access to global construction history functionality.
*
*/
class FBSDK_DLL FBConstructionHistory : public FBComponent 
{
    __FBClassDeclare( FBConstructionHistory, FBComponent );

    /** Disabled copy constructor.
    *   Voluntarily making the copy constructor unavailable.
    */
    FBConstructionHistory( const FBConstructionHistory& );

    /** Disabled assignment operator.
    *   Voluntarily making the assignment operator unavailable.
    */
    FBConstructionHistory& operator=( const FBConstructionHistory& );

public:

    /** Constructor.
    */
    FBConstructionHistory();

	/**	GetDeltaOperations
	*	Get the list of delta operations in the construction history
	*   \param sinceCommandId
	*	\param	pOperations	Array of operations, will be filled by the function.
	*/

	void GetDeltaOperations( FBConstructionOperationArray* pOperations, int sinceCommandId = -1);

	/**	RunOperation
	*	Runs an operation
	*
	*	\param	operation	The operation to run
    *	\param	out_errors  A string containing the text of errors generated by running the operations (if any)
	*/

	int RunOperation ( FBConstructionOperation& operation, FBString& out_errors );

    /**	GetState
	*	returns the current state of the construction history manager
	*
	*	\return	returns a FBConstructionHistoryState indicating the state
	*/
    FBConstructionHistoryState  GetState();

    /**	 <b>Event:</b> History changed.
	*	triggered when construction history changes
	*/
    FBPropertyEvent			OnChange;

    /**	NetDelete
	*	Network delete with support for Network Undo
	*   \param component
	*	\param	key	A key that uniquely identifies the operation
	*/

	void NetDelete ( FBComponent* component, kInt64 key );

    /**	NetUndo
	*	Perform network undo operation
	*	\param	key	        The operation to undo
	*/

	void NetUndo ( kInt64 key );

    /**	GetScriptOutput
	*	Returns the output from the scripting engine
	*
	*	\param	script  the script text
    *	\param	errors  the error outputted from the scripting engine
	*/

	void    GetScriptOutput ( FBString& script, FBString& errors );


    /**	Get the global construction history
    *	\return	the global object.
    */
    static FBConstructionHistory& TheOne();

};

#ifdef FBSDKUseNamespace
    }
#endif
#endif

