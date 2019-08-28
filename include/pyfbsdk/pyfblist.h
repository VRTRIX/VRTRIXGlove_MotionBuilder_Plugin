#ifndef pyfblist_h__
#define pyfblist_h__
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

#include "pyfbvisualcomponent.h"

// =======================================================================================
// FBList
// =======================================================================================
void FBList_Init();

class PYSDK_DLL FBList_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBList* mFBList;
public:
	FBList_Wrapper( FBComponent* pFBComponent );
	FBList_Wrapper();
	virtual ~FBList_Wrapper( ) {  }
	bool IsSelected(int pIndex) 
    {         
        return mFBList->IsSelected( pIndex ); 
    }
	void Selected(int pIndex, bool pSelected)
    {         
        mFBList->Selected( pIndex, pSelected ); 
    }
	void SetExtendedSelect( bool pExtendedSelect ) { mFBList->ExtendedSelect = pExtendedSelect; }
	bool GetExtendedSelect(  ) { return mFBList->ExtendedSelect; }
	void SetItemIndex( int pItemIndex ) { mFBList->ItemIndex = pItemIndex; }
	int GetItemIndex(  ) { return mFBList->ItemIndex; }
	void SetItems( FBPropertyStringList_Wrapper& pItems ) { mFBList->Items = *pItems.mFBPropertyString; }
	object GetItems(  ) { return FBPropertyStringList_Wrapper_Factory( mFBList->Items ); }
	void SetMultiSelect( bool pMultiSelect ) { mFBList->MultiSelect = pMultiSelect; }
	bool GetMultiSelect(  ) { return mFBList->MultiSelect; }
	FBListStyle GetStyle(  ) { return mFBList->Style; }
    void SetStyle( FBListStyle pStyle ) { mFBList->Style = pStyle; }
    object OnChange();
    object OnDragAndDrop();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfblist_h__