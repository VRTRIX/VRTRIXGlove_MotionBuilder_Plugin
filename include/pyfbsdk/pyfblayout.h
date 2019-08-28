#ifndef pyfblayout_h__
#define pyfblayout_h__
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
// FBLayout
// =======================================================================================
void FBLayout_Init();

class PYSDK_DLL FBLayout_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBLayout* mFBLayout;
public:

    struct AddRegionParam;

	FBLayout_Wrapper( FBComponent* pFBComponent );
	FBLayout_Wrapper();
	virtual ~FBLayout_Wrapper( ) {  }
    
    bool AddRegion(const char* pName, const char* pTitle, AddRegionParam* pX, AddRegionParam* pY, AddRegionParam* pW, AddRegionParam* pH);
	bool GetRegion(const char* pName) { return mFBLayout->GetRegion( pName ); }
	bool GetRegionPositions(const char * pName, bool pComputed, int * pX, int * pY, int * pW = NULL, int * pH = NULL) { return mFBLayout->GetRegionPositions( pName, pComputed, pX, pY, pW, pH ); }
    FBLayout::FBSplitStyle GetSplitStyle(const char* pName) { return mFBLayout->GetSplitStyle( pName ); }
	bool MoveRegion(const char * pName, int pX, int pY) { return mFBLayout->MoveRegion( pName, pX, pY ); }
	bool RemoveRegion(const char* pName) { return mFBLayout->RemoveRegion( pName ); }
	bool RenameRegion(const char * pOldName, const char * pNewName) { return mFBLayout->RenameRegion( pOldName, pNewName ); }
	bool SetBorder(const char * pName, FBBorderStyle pType, bool pShowTitle, bool pInSet, int pWidth, int pSpacing, float pMaxAngle, int pCornerRadius) { return mFBLayout->SetBorder( pName, pType, pShowTitle, pInSet, pWidth, pSpacing, pMaxAngle, pCornerRadius ); }
	bool SetControl(const char * pName, FBVisualComponent_Wrapper& pComponent) { return mFBLayout->SetControl( pName, pComponent.mFBVisualComponent ); }
	bool SetRegionTitle(const char * pName, const char * pTitle) { return mFBLayout->SetRegionTitle( pName, pTitle ); }
	bool SetSplitStyle(const char * pName, FBLayout::FBSplitStyle pRegionType) { return mFBLayout->SetSplitStyle( pName, pRegionType ); }
	bool SetView(const char * pName, FBVisualComponent_Wrapper& pComponent) { return mFBLayout->SetView( pName, pComponent.mFBVisualComponent ); }
	bool SizeRegion(const char * pName, int pW, int pH) { return mFBLayout->SizeRegion( pName, pW, pH ); }
	void ClearControl(const char* pName) { mFBLayout->ClearControl( pName ); }
    object GetControl(const char* pName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBLayout->GetControl( pName ) ); }	

    void SetAutoRestructure( bool );
    void Restructure( bool pNoMove );

    object OnIdle();
    object OnPaint();
    object OnResize();
    object OnInput();
    object OnShow();
protected:

    FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfblayout_h__