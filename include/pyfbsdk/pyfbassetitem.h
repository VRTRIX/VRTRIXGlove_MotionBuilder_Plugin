#ifndef pyfbassetitem_h__
#define pyfbassetitem_h__
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

// =======================================================================================
// FBAssetItem
// =======================================================================================
void FBAssetItem_Init();

class FBAssetFolder_Wrapper;
class PYSDK_DLL FBAssetItem_Wrapper : public FBComponent_Wrapper {
public:
	FBAssetItem* mFBAssetItem;
public:
	FBAssetItem_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAssetItem = (FBAssetItem*)pFBComponent; }
	virtual ~FBAssetItem_Wrapper( ) {}
	bool CheckIn(const char* pComment = "", bool pKeepCheckedOut = false, bool pSilent = false) { return mFBAssetItem->CheckIn( FBString(pComment), pKeepCheckedOut, pSilent ); }
	bool CheckOut(const char* pComment = "", bool pDontGetLocal = false, bool pSilent = false) { return mFBAssetItem->CheckOut( FBString(pComment), pDontGetLocal, pSilent ); }
	bool GetLatest(bool pReplaceCheckedOut = false, bool pSilent = false) { return mFBAssetItem->GetLatest( pReplaceCheckedOut, pSilent ); }
	const char* GetLocalPath() { return mFBAssetItem->GetLocalPath(  ); }
	const char* GetName() { return mFBAssetItem->GetName(  ); }
	object GetParent() { return FBWrapperFactory::TheOne().WrapFBObject( mFBAssetItem->GetParent(  )); }
	const char* GetServerPath() { return mFBAssetItem->GetServerPath(  ); }
	void ShowHistory() { mFBAssetItem->ShowHistory(  ); }
	void ShowProperties() { mFBAssetItem->ShowProperties(  ); }
	bool UndoCheckOut(bool pReplaceLocalFile = true, bool pSilent = false) { return mFBAssetItem->UndoCheckOut( pReplaceLocalFile, pSilent ); }
	void SetLastError( const char* pLastError ) { mFBAssetItem->LastError = pLastError; }
	const char* GetLastError(  ) { return mFBAssetItem->LastError; }
};
#endif // pyfbassetitem_h__