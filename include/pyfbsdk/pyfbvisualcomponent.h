#ifndef pyfbvisualcomponent_h__
#define pyfbvisualcomponent_h__
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
// FBVisualComponent
// =======================================================================================
void FBVisualComponent_Init();

class PYSDK_DLL FBVisualComponent_Wrapper : public FBComponent_Wrapper {
public:
	FBVisualComponent* mFBVisualComponent;
public:
	FBVisualComponent_Wrapper( FBComponent* pFBComponent );	
	virtual ~FBVisualComponent_Wrapper( );
	bool AddChild(FBVisualComponent_Wrapper& pChild, int pId = 0) { return mFBVisualComponent->AddChild( pChild.mFBVisualComponent, pId ); }
	object GetChild(int pId = 0) { return FBWrapperFactory::TheOne().WrapFBObject( mFBVisualComponent->GetChild( pId )); }
	bool IsView() { return mFBVisualComponent->IsView(  ); }
	void Refresh(bool pNow = false) { mFBVisualComponent->Refresh( pNow ); }
	void ViewExpose() { mFBVisualComponent->ViewExpose(  ); }
	void ViewInput(int pMouseX, int pMouseY, FBInputType pAction, int pButtonKey, int pModifier) { mFBVisualComponent->ViewInput( pMouseX, pMouseY, pAction, pButtonKey, pModifier ); }	
	void SetCaption( const char* pCaption ) { mFBVisualComponent->Caption = pCaption; }
	const char* GetCaption(  ) { return mFBVisualComponent->Caption; }
    kReference  GetQWidgetAddress() { return (kReference)mFBVisualComponent->GetQWidgetAddress(); }
    // Region stuff exposition:
    const char* GetRegionName();

    void SetRegionOffsetX( int pX );
    int GetRegionOffsetX(  );
    void SetRegionOffsetY( int pY );
    int GetRegionOffsetY(  );
    void SetRegionOffsetWidth( int pWidth );
    int GetRegionOffsetWidth(  );
    void SetRegionOffsetHeight( int pHeight );
    int GetRegionOffsetHeight(  );

    void SetRegionRatioX( float pRatioX );
    float GetRegionRatioX(  );
    void SetRegionRatioY( float pRatioY );
    float GetRegionRatioY(  );
    void SetRegionRatioWidth( float pRatioWidth );
    float GetRegionRatioWidth(  );
    void SetRegionRatioHeight( float pRatioHeight );
    float GetRegionRatioHeight(  );

    void SetRegionAttachTypeX( FBAttachType pX );
    FBAttachType GetRegionAttachTypeX(  );
    void SetRegionAttachTypeY( FBAttachType pY );
    FBAttachType GetRegionAttachTypeY(  );
    void SetRegionAttachTypeWidth( FBAttachType pWidth );
    FBAttachType GetRegionAttachTypeWidth(  );
    void SetRegionAttachTypeHeight( FBAttachType pHeight );
    FBAttachType GetRegionAttachTypeHeight(  );

    void SetRegionAttachToX( object pAttachToX );
    object GetRegionAttachToX(  );
    void SetRegionAttachToY( object pAttachToY );
    object GetRegionAttachToY(  );
    void SetRegionAttachToWidth( object pAttachToWidth );
    object GetRegionAttachToWidth(  );
    void SetRegionAttachToHeight( object pAttachToHeight );
    object GetRegionAttachToHeight(  );

    void SetRegionPosMinX( int pX );
    int GetRegionPosMinX(  );
    void SetRegionPosMaxX( int pX );
    int GetRegionPosMaxX(  );
    void SetRegionPosMinY( int pY );
    int GetRegionPosMinY(  );
    void SetRegionPosMaxY( int pY );
    int GetRegionPosMaxY(  );
    

    // Border stuff exposition:   
    void SetBorderCaption( const char* pCaption );
    const char* GetBorderCaption(  );

    void SetBorderShowCaption( bool pShowCaption );
    bool GetBorderShowCaption(  );

    void SetBorderStyle( FBBorderStyle pBorderStyle );
    FBBorderStyle GetBorderStyle(  );

    void SetBorderInSet( bool pInSet );
    bool GetBorderInSet(  );

    void SetBorderWidth( int pWidth );
    int GetBorderWidth(  );

    void SetBorderSpacing( int pSpacing );
    int GetBorderSpacing(  );

    void SetBorderMaxAngle( float pMaxAngle );
    float GetBorderMaxAngle(  );

    void SetBorderCornerRadius( int pCornerRadius );
    int GetBorderCornerRadius(  );    

	void SetEnabled( bool pEnabled ) { mFBVisualComponent->Enabled = pEnabled; }
	bool GetEnabled(  ) { return mFBVisualComponent->Enabled; }

	void SetHint( const char* pHint ) { mFBVisualComponent->Hint = pHint; }
	const char* GetHint(  ) { return mFBVisualComponent->Hint; }

	void SetReadOnly( bool pReadOnly ) { mFBVisualComponent->ReadOnly = pReadOnly; }
	bool GetReadOnly(  ) { return mFBVisualComponent->ReadOnly; }	

	void SetVisible( bool pVisible ) { mFBVisualComponent->Visible = pVisible; }
	bool GetVisible(  ) { return mFBVisualComponent->Visible; }

	virtual void SetLeft( int pLeft );
	virtual int  GetLeft(  );

	virtual void SetTop( int pTop );
	virtual int  GetTop(  );

	virtual void SetWidth( int pWidth );
	virtual int  GetWidth(  );

	virtual void SetHeight( int pHeight );
	virtual int  GetHeight(  );    
    
};
#endif // pyfbvisualcomponent_h__
