#ifndef pyfbconstructionhistory_h__
#define pyfbconstructionhistory_h__
/**************************************************************************
 Copyright 2012 Autodesk, Inc.
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

#include "pyfbcomponent.h"

#if !defined(K_NO_CONSTRUCTION_HISTORY)

// =======================================================================================
// FBConstructionOperation
// =======================================================================================
void FBConstructionOperation_Init();

class PYSDK_DLL FBConstructionOperation_Wrapper
{
	friend class FBConstructionHistory_Wrapper;

	FBConstructionOperation mOperation;
public:

    /** Constructor.
    */
	FBConstructionOperation_Wrapper(const char* pScript = "");
    FBConstructionOperation_Wrapper(const FBConstructionOperation* pFBComponent) : mOperation(pFBComponent) {}

	const char*	GetLanguage() {return mOperation.GetLanguage();}
	int			GetLanguageVersion() {return mOperation.GetLanguageVersion();}
	const char*	GetScript() {return mOperation.GetScript();}
	const char*	GetOrigin() {return mOperation.GetOrigin();}
	int			GetCommandId() {return mOperation.GetCommandId();}
    bool        GetExecuteAsLocalOperation() {return mOperation.GetExecuteAsLocalOperation();}

	void		SetLanguage( const char* language ) {mOperation.SetLanguage(language);}
	void		SetLanguageVersion( int version ) {mOperation.SetLanguageVersion(version);}
	void		SetScript( const char* script ) {mOperation.SetScript(script);}
	void		SetCommandId( int commandId ) {mOperation.SetCommandId(commandId);}
    void        SetOrigin( const char* origin ) {mOperation.SetOrigin(origin);}
    void        SetExecuteAsLocalOperation( bool bIsLocal ) {mOperation.SetExecuteAsLocalOperation(bIsLocal);}
};

PYSDK_DLL inline FBConstructionOperation_Wrapper* FBConstructionOperation_Wrapper_Factory( const FBConstructionOperation* pFBComponent)
{
	return new FBConstructionOperation_Wrapper(pFBComponent);
}

// =======================================================================================
// FBConstructionHistory
// =======================================================================================
void FBConstructionHistory_Init();

class PYSDK_DLL FBConstructionHistory_Wrapper : public FBComponent_Wrapper {
public:
	FBConstructionHistory_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { }
	virtual ~FBConstructionHistory_Wrapper( ) {}

	void NetDelete(FBComponent_Wrapper* pComponent, unsigned long long key );
	void NetUndo(unsigned long long key);

	object OnChange();

	int RunOperation ( FBConstructionOperation_Wrapper& operation, list out_errors );
	FBConstructionHistoryState  GetState();
	void GetDeltaOperations( list pOperations, int sinceCommandId = -1);	
	void GetScriptOutput ( list script, list errors );

protected:

	FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif

#endif // pyfbconstructionhistory_h__