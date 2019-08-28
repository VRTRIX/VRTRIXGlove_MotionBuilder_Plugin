#ifndef pyfbvisualcontainer_h__
#define pyfbvisualcontainer_h__
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
#include "pyfbimage.h"
#include "pyfbimagecontainer.h"	// to remove K_DEPRECATED_2014

// =======================================================================================
// FBVisualContainer
// =======================================================================================
void FBVisualContainer_Init();
class FBImage_Wrapper;
class FBImageContainer_Wrapper;	// to remove K_DEPRECATED_2014
class PYSDK_DLL FBVisualContainer_Wrapper : public FBVisualComponent_Wrapper  {
public:
	FBVisualContainer* mFBVisualContainer;
public:
	FBVisualContainer_Wrapper( FBComponent* pFBComponent );
	FBVisualContainer_Wrapper(  );
	virtual ~FBVisualContainer_Wrapper( ) {  }
	int GetSelection() { return mFBVisualContainer->GetSelection(  ); }
	bool ItemIconSet(kReference pRef, FBImage_Wrapper* pImage, bool pUseACopyOfTheImage = true) { return mFBVisualContainer->ItemIconSet( pRef, pImage->mFBImage, pUseACopyOfTheImage ); }
	bool ItemIconSet(kReference pRef, FBImageContainer_Wrapper* pImage, bool pUseACopyOfTheImage = true);
	bool ItemIconSet(kReference pRef, const char * pFilename) { return mFBVisualContainer->ItemIconSet( pRef, pFilename ); }
	bool ItemNameEdit(kReference pRef) { return mFBVisualContainer->ItemNameEdit( pRef ); }
	void SetIconPosition( FBIconPosition pIconPosition ) { mFBVisualContainer->IconPosition = pIconPosition; }
	FBIconPosition GetIconPosition(  ) { return mFBVisualContainer->IconPosition; }
	void SetItemHeight( int pItemHeight ) { mFBVisualContainer->ItemHeight = pItemHeight; }
	int GetItemHeight(  ) { return mFBVisualContainer->ItemHeight; }
	void SetItemIndex( int pItemIndex ) { mFBVisualContainer->ItemIndex = pItemIndex; }
	int GetItemIndex(  ) { return mFBVisualContainer->ItemIndex; }
	void SetItems( FBPropertyStringList_Wrapper& pItems ) { mFBVisualContainer->Items = *pItems.mFBPropertyString; }
	object GetItems(  ) { return FBPropertyStringList_Wrapper_Factory( mFBVisualContainer->Items ); }
	void SetItemWidth( int pItemWidth ) { mFBVisualContainer->ItemWidth = pItemWidth; }
	int GetItemWidth(  ) { return mFBVisualContainer->ItemWidth; }
	void SetItemWrap( bool pItemWrap ) { mFBVisualContainer->ItemWrap = pItemWrap; }
	bool GetItemWrap(  ) { return mFBVisualContainer->ItemWrap; }
	void SetOrientation( FBOrientation pOrientation ) { mFBVisualContainer->Orientation = pOrientation; }
	FBOrientation GetOrientation(  ) { return mFBVisualContainer->Orientation; }
    object OnChange();
    object OnDblClick();
    object OnDragAndDrop();

protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbvisualcontainer_h__