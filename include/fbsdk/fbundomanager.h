#ifndef __FBUNDOMANAGER_H__
#define __FBUNDOMANAGER_H__
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

/** \file fbundomanager.h
*   Undo manager.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbarray.h>
#include <fbsdk/fbplug.h>
#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif



    ////////////////////////////////////////////////////////////////////////////////////
    // FBUndoManager
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBUndoManager );
    FB_FORWARD( FBUndo );

    FB_DEFINE_ARRAY(FBSDK_DLL, Plug);


    /** Access to global undo and redo functionality.
    *   Users have the possibility of undoing and redoing actions performed using
    *   the GUI, and interacting with the undo and redo stacks with custom actions.
    *   
    *   All undo/redo related functions should only be called inside UI event callback.
    *   Users should call TransactionBegin()/TransactionEnd() in pairs, Transaction stack 
    *   must be closed before UI event callback return.
    *
    *   This class cannot be used as a base class.
    */
    class FBSDK_DLL FBUndoManager : public FBComponent 
    {
        __FBClassDeclare( FBUndoManager,FBComponent );

        /** Disabled copy constructor.
        *   Voluntarily making the copy constructor unavailable.
        */
        FBUndoManager( const FBUndoManager& );

        /** Disabled assignment operator.
        *   Voluntarily making the assignment operator unavailable.
        */
        FBUndoManager& operator=( const FBUndoManager& );

    public:

        /** Constructor.
        */
        FBUndoManager(HIObject pObject=NULL);

        /** Clear the undo and redo stacks.
        *   \return A boolean value indicating success (true) or failure (false).
        */
        bool Clear();

        /** Redo last undone action.
        */
        void Redo();

        /** Undo last action.
        *   \param pNoRedo  If true, once the action is undone, it cannot be redone.
        */
        void Undo( bool pNoRedo = false );

        /** Open transaction stack for adding transactions.
        *   Users should call TransactionBegin()/TransactionEnd() in pairs, Transaction stack 
        *   must be closed before UI event callback return.    
        *   \param      pTransactionName     Name of Transaction.
        *   \return     true if open transaction stack successfully. 
        */
        bool	TransactionBegin(const char *pTransactionName);

        /** Query if transaction stack is already open.
        *   \return     true if transaction is already open.
        */
        bool	TransactionIsOpen();

        /** Add Transaction if transaction stack is open. 
        *   Multiple custom actions could be added into transaction stack by calling 
        *   this function multiple times. 
        *   \param      pUndo   Custom undoable action to be added, FBUndoManager takes ownership of pUndo.
        * 	\param      pDepdendPlugArray  Usually you shold use the default value (NULL).
        *   \return     true if add transaction successfully.
        */
        bool	TransactionAdd(FBUndo* pUndo, FBArrayPlug* pDepdendPlugArray = NULL);

        /** Add Transaction if transaction stack is open. 
        *   Quick Function to add Model TRS in Undo Stack 
        *   \param      pModel   Model to backup TRS
        *   \return     true if add transaction successfully.
        */
        bool	TransactionAddModelTRS(FBModel* pModel);

        /** Add Transaction if transaction stack is open. 
        *   Quick Function to add property value in Undo Stack
        *   \param      pProperty   Property to backup
        *   \return     true if add transaction successfully.
        */
        bool TransactionAddProperty(FBProperty* pProperty);

        /** Add Transaction if transaction stack is open. 
        *   Function to add object to destroy in Undo Stack.
        *   No need to call FBDelete() on the object after calling this function.
        *   \param      pObject   Object to backup
        *   \return     true if add transaction successfully.
        */
        bool	TransactionAddObjectDestroy(FBObject* pObject);

        /** Close transaction stack.
        *   Users should call TransactionBegin()/TransactionEnd() in pairs, Transaction stack 
        *   must be closed before UI event callback return.
        *   \return     true if transaction close successfully.
        */
        bool	TransactionEnd();

        /** Determine if an undo operation is in action
        *   \return     true the Undo Manager is performing an Undo or a Redo operation.
        */
        bool ActiveOperation();

        FBPropertyEvent			OnUndo;				//!< <b>Event:</b> An undo operation will be executed.
        FBPropertyEvent			OnUndoCompleted;	//!< <b>Event:</b> An undo operation has been executed.
        FBPropertyEvent			OnRedo;				//!< <b>Event:</b> A redo operation will be executed.
        FBPropertyEvent			OnRedoCompleted;	//!< <b>Event:</b> A redo operation has been executed.

        static FBUndoManager& TheOne();
    };

    /** Base Class for Custom Undoable Actions.
    */
    class FBSDK_DLL FBUndo {

    public:
        /** Destructor.
        */
        virtual ~FBUndo();

        /** Callback function for undo custom action.
        */
        virtual void	Undo();

        /** Callback function for redo custom action.
        */
        virtual void	Redo();

        /** Get Custom action name.
        */
        virtual const char*	GetName();
    };

#ifdef FBSDKUseNamespace
}
#endif
#endif

