#ifndef pyfbreferencetime_h__
#define pyfbreferencetime_h__
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
// FBReferenceTime
// =======================================================================================
void FBReferenceTime_Init();

class PYSDK_DLL FBReferenceTime_Wrapper : public FBComponent_Wrapper {
public:
	FBReferenceTime* mFBReferenceTime;
public:
	FBReferenceTime_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBReferenceTime = (FBReferenceTime*)pFBComponent; }	    
    FBReferenceTime_Wrapper() : FBComponent_Wrapper( new FBReferenceTime()) { mFBReferenceTime = (FBReferenceTime*)mFBComponent; SetAllocated(); }
	virtual ~FBReferenceTime_Wrapper( ) {}
	int Add(const char* pName) { return mFBReferenceTime->Add( pName ); }
	FBTime_Wrapper* GetTime(int pIndex, FBTime_Wrapper& pSystem) { return FBTime_Wrapper_Factory( mFBReferenceTime->GetTime( pIndex, *pSystem.mFBTime )); }
	void Remove(int pIndex) { mFBReferenceTime->Remove( pIndex ); }
	void SetTime(int pIndex, FBTime_Wrapper& pReferenceTime, FBTime_Wrapper& pSystem) { mFBReferenceTime->SetTime( pIndex, *pReferenceTime.mFBTime, *pSystem.mFBTime ); }
	int GetCount(  ) { return mFBReferenceTime->Count; }
	void SetItemIndex( int pItemIndex ) { mFBReferenceTime->ItemIndex = pItemIndex; }
	int GetItemIndex(  ) { return mFBReferenceTime->ItemIndex; }
	void SetCurrentTimeReferenceID( int pCurrentTimeReferenceID ) { mFBReferenceTime->CurrentTimeReferenceID = pCurrentTimeReferenceID; }
	int GetCurrentTimeReferenceID(  ) { return mFBReferenceTime->CurrentTimeReferenceID; }
    const char* GetReferenceTimeName( int pID ) { return mFBReferenceTime->GetReferenceTimeName(pID); }
	list GetUniqueIDList()
	{
		list lUniqueID;
		
		FBArrayTemplate<int> lIDArray;
		mFBReferenceTime->GetUniqueIDList(&lIDArray);

		for( int i = 0; i < lIDArray.GetCount(); i++ )
			lUniqueID.append( lIDArray[ i ] );

		return lUniqueID;
	}
};
#endif // pyfbreferencetime_h__