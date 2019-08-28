#ifndef pyfbundomanager_h__
#define pyfbundomanager_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

#include "pyfbmatrix.h"
#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"

// =======================================================================================
// FBUndoManager
// =======================================================================================
void FBUndoManager_Init();

class PYSDK_DLL FBUndoManager_Wrapper : public FBComponent_Wrapper {
public:
	FBUndoManager* mFBUndoManager;
public:
	FBUndoManager_Wrapper(FBComponent* pFBComponent) : FBComponent_Wrapper( pFBComponent ) { mFBUndoManager = (FBUndoManager*)pFBComponent; }
	FBUndoManager_Wrapper() : FBComponent_Wrapper( &FBUndoManager::TheOne() ) { mFBUndoManager = (FBUndoManager*)mFBComponent; }
	virtual ~FBUndoManager_Wrapper( ) { }
	bool Clear() { return mFBUndoManager->Clear(  ); }
	void Redo() { return mFBUndoManager->Redo(  ); }
	void Undo( bool pNoRedo = false ) { return mFBUndoManager->Undo( pNoRedo ); }

    bool TransactionBegin(const char *pTransactionName);
    bool TransactionIsOpen();
    bool TransactionAddModelTRS(FBModel_Wrapper& pModel);
    bool TransactionAddProperty(FBProperty_Wrapper& pProperty);
    bool TransactionAddObjectDestroy(FBComponent_Wrapper& pObject);
    bool TransactionEnd();
    bool ActiveOperation();
    object OnUndoCompleted();
    object OnUndo();
    object OnRedoCompleted();
    object OnRedo();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbundomanager_h__