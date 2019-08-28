#ifndef pyfbplug_h__
#define pyfbplug_h__
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

void FBPlug_Init();

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBObjectList (FBArrayTemplate<FBComponent*>)
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class PYSDK_DLL FBPlugList_Wrapper {

public:
	// FBArrayTemplate<FBComponent*>* mFBObjectList;
	FBPlugList* mFBPlugList;

	FBPlugList_Wrapper() : mFBPlugList( FBCreatePlugList() )
	{
	};
	// DTOR
	~FBPlugList_Wrapper()
	{
		FBDestroyPlugList( mFBPlugList );
	};

	int GetCount()
	{
		return mFBPlugList->GetCount();
	};

	object GetObject( int lIdx )
	{
		if( lIdx < 0 ) {
			lIdx += GetCount();
		}
		if( lIdx < 0 || lIdx >= GetCount()) {
			PyErr_SetString(PyExc_IndexError,"list index out of range");
			throw_error_already_set();
			return object();
		}
		return FBWrapperFactory::TheOne().WrapFBObject( mFBPlugList->operator[]( lIdx ) );
	};
};

// =======================================================================================
// FBPlug
// =======================================================================================

class FBPlug_Wrapper;

class PYSDK_DLL FBPlug_Wrapper : public FBPythonWrapper {
public:
	FBPlug* mFBPlug;    
public:
	FBPlug_Wrapper( FBPlug* pFBPlug );
	virtual ~FBPlug_Wrapper( );

	bool BeginChange() { return mFBPlug->BeginChange(  ); }
	const char* ClassName() {  return mFBPlug->ClassName(  ); }
	bool ConnectDst(FBPlug_Wrapper& pDst, FBConnectionType pConnectionType = kFBConnectionTypeNone) { return mFBPlug->ConnectDst( pDst.mFBPlug, pConnectionType ); }
	bool ConnectDstAt(int pSrc_DstIndex, FBPlug_Wrapper& pDst, FBConnectionType pConnectionType = kFBConnectionTypeNone) { return mFBPlug->ConnectDstAt( pSrc_DstIndex, pDst.mFBPlug, pConnectionType ); }
	bool ConnectSrc(FBPlug_Wrapper& pSrc, FBConnectionType pConnectionType = kFBConnectionTypeNone) { return mFBPlug->ConnectSrc( pSrc.mFBPlug, pConnectionType ); }
	bool ConnectSrcAt(int pDst_SrcIndex, FBPlug_Wrapper& pSrc, FBConnectionType pConnectionType = kFBConnectionTypeNone) { return mFBPlug->ConnectSrcAt( pDst_SrcIndex, pSrc.mFBPlug, pConnectionType ); }
	void DisconnectAllDst() { mFBPlug->DisconnectAllDst(  ); }
	void DisconnectAllSrc() { mFBPlug->DisconnectAllSrc(  ); }
	bool DisconnectDst(FBPlug_Wrapper& pDst) { return mFBPlug->DisconnectDst( pDst.mFBPlug ); }
	bool DisconnectDstAt(int pIndex) { return mFBPlug->DisconnectDstAt( pIndex ); }
	bool DisconnectSrc(FBPlug_Wrapper& pSrc) { return mFBPlug->DisconnectSrc( pSrc.mFBPlug ); }
	bool DisconnectSrcAt(int pIndex) { return mFBPlug->DisconnectSrcAt( pIndex ); }
	void EndChange() { mFBPlug->EndChange(  ); }

	void SetSelfModified(FBPlugModificationFlag pFlag, bool pBool){ mFBPlug->SetSelfModified(pFlag, pBool); }
	bool GetSelfModified(FBPlugModificationFlag pFlag) { return mFBPlug->GetSelfModified(pFlag); }	
	void SetContentModified(FBPlugModificationFlag pFlag, bool pBool) { mFBPlug->SetContentModified(pFlag, pBool); }
	bool GetContentModified(FBPlugModificationFlag pFlag) { return mFBPlug->GetContentModified(pFlag); }
	int  GetPlugConnectionModifiedList(FBPlugList_Wrapper& pPlugList, FBPlugModificationFlag pConnectionModificatonFlag, bool pAddRemove) { return mFBPlug->GetPlugConnectionModifiedList(*(pPlugList.mFBPlugList), pConnectionModificatonFlag, pAddRemove); }
    bool RevertModification(FBPlugModificationFlag pFlag = kFBAllModifiedMask) { return mFBPlug->RevertModification(pFlag); }

	object GetDst(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBPlug_Wrapper::GetDstCount );
        return FBWrapperFactory::TheOne().WrapFBObject( mFBPlug->GetDst( pIndex ));
    }

	int GetDstCount() { return mFBPlug->GetDstCount(  ); }
	FBConnectionType GetDstType(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBPlug_Wrapper::GetDstCount );        
        return mFBPlug->GetDstType( pIndex );
    }

	object GetOwned(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBPlug_Wrapper::GetOwnedCount );
        return FBWrapperFactory::TheOne().WrapFBObject( mFBPlug->GetOwned( pIndex ));
    }
	int GetOwnedCount() { return mFBPlug->GetOwnedCount(  ); }
	object GetOwner() { return FBWrapperFactory::TheOne().WrapFBObject( mFBPlug->GetOwner(  )); }
	object GetSrc(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBPlug_Wrapper::GetSrcCount );
        return FBWrapperFactory::TheOne().WrapFBObject( mFBPlug->GetSrc( pIndex ));
    }

	int GetSrcCount() { return mFBPlug->GetSrcCount(  ); }
	FBConnectionType GetSrcType(int pIndex) 
    {         
        ValidateIndexAccess( pIndex, this, &FBPlug_Wrapper::GetSrcCount );
        return mFBPlug->GetSrcType( pIndex );
    }
	bool Is(int pTypeId) { return mFBPlug->Is( pTypeId ); }
	bool IsSDKComponent() { return mFBPlug->IsSDKComponent(  ); }
	bool MoveSrcAt(int pIndex, int pAtIndex) { return mFBPlug->MoveSrcAt( pIndex, pAtIndex ); }
	bool MoveSrcAt(FBPlug_Wrapper& pSrc, FBPlug_Wrapper& pAtSrc) { return mFBPlug->MoveSrcAt( pSrc.mFBPlug, pAtSrc.mFBPlug ); }
	bool ReplaceDstAt(int pIndex, FBPlug_Wrapper& pDst) { return mFBPlug->ReplaceDstAt( pIndex, pDst.mFBPlug ); }
	bool ReplaceSrcAt(int pIndex, FBPlug_Wrapper& pSrc) { return mFBPlug->ReplaceSrcAt( pIndex, pSrc.mFBPlug ); }
	bool SwapSrc(int pIndexA, int pIndexB) { return mFBPlug->SwapSrc( pIndexA, pIndexB ); }
    static void PrintClassDefinitions() { return FBPlug::PrintClassDefinitions(); }
};
#endif // pyfbplug_h__
