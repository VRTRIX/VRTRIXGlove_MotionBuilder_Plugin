#ifndef pyfbbutton_h__
#define pyfbbutton_h__
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
// FBButton
// =======================================================================================
void FBButton_Init();

class PYSDK_DLL FBButton_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBButton* mFBButton;
public:
	FBButton_Wrapper( FBComponent* pFBComponent );
    FBButton_Wrapper();
	virtual ~FBButton_Wrapper( );
	FBColor_Wrapper* GetStateColor(FBButtonState pState) { return FBColor_Wrapper_Factory( mFBButton->GetStateColor( pState )); }
	void SetStateColor(FBButtonState pState, FBColor_Wrapper* pColor) { mFBButton->SetStateColor( pState, *(pColor->mFBColor) ); }
	void SetState( int pState ) { mFBButton->State = pState; }
	int GetState(  ) { return mFBButton->State; }
	void SetStyle( FBButtonStyle pStyle ) { mFBButton->Style = pStyle; }
	FBButtonStyle GetStyle(  ) { return mFBButton->Style; }
	void SetLook( FBButtonLook pLook ) { mFBButton->Look = pLook; }
	FBButtonLook GetLook(  ) { return mFBButton->Look; }
	void SetJustify( FBTextJustify pJustify ) { mFBButton->Justify = pJustify; }
	FBTextJustify GetJustify(  ) { return mFBButton->Justify; }
	void HookToButton( FBButton_Wrapper& pHook ) { mFBButton->HookToButton(pHook.mFBButton); }
    void SetImageFileNames( const char* pDown, const char* pUp = 0, const char* pImage3 = 0, bool pFromResources = false );
    object OnClick();
protected:
	FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbbutton_h__