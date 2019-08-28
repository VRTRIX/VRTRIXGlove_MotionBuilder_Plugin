#ifndef pyfbtabpanel_h__
#define pyfbtabpanel_h__
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
#include "pyfblayout.h"

// =======================================================================================
// FBTabPanel
// =======================================================================================
void FBTabPanel_Init();

class PYSDK_DLL FBTabPanel_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBTabPanel* mFBTabPanel;
public:
	FBTabPanel_Wrapper( FBComponent* pFBComponent );
	FBTabPanel_Wrapper();
	virtual ~FBTabPanel_Wrapper( ) {  }
	void SetItemIndex( int pItemIndex ) { mFBTabPanel->ItemIndex = pItemIndex; }
	int GetItemIndex(  ) { return mFBTabPanel->ItemIndex; }
	void SetItems( FBPropertyStringList_Wrapper& pItems ) { mFBTabPanel->Items = *pItems.mFBPropertyString; }
	object GetItems(  ) { return FBPropertyStringList_Wrapper_Factory( mFBTabPanel->Items ); }
	void SetLayout( FBLayout_Wrapper& pLayout ) { mFBTabPanel->Layout = pLayout.mFBLayout; }
	object GetLayout(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBTabPanel->Layout ); }
	void SetTabStyle( int pTabStyle );
	int GetTabStyle(  ) { return mFBTabPanel->TabStyle; }
    object OnChange();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbtabpanel_h__

