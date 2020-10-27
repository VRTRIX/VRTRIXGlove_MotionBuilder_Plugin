#ifndef pyfbviewerinfos_h__
#define pyfbviewerinfos_h__
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
// FBHUD
// =======================================================================================
void FBHUD_Init();


class PYSDK_DLL FBHUD_Wrapper : public FBBox_Wrapper {
public:
	FBHUD* mFBHUD;
public:
	FBHUD_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBHUD = (FBHUD*)pFBComponent; }
	explicit FBHUD_Wrapper( const char* pName ) : FBBox_Wrapper( new FBHUD( pName )) { mFBHUD = (FBHUD*)mFBComponent; }
	virtual ~FBHUD_Wrapper( );
	void SetVisibility( bool pVisibility ) { mFBHUD->Visibility = pVisibility; }
	bool GetVisibility(  ) { return mFBHUD->Visibility; }
	object OnDisplay();
    object GetElements() { return FBPropertyListHUDElement_Wrapper_Factory( mFBHUD->Elements ); }

    object CreateElement( FBHUD::EStockElement pType, const char *pName );
    object CreateCustomElement( const char* pHUDElementClassName, const char* pName );

    template< FBHUD::EStockElement pValue > static FBHUD::EStockElement EStockElement() { return pValue; }

protected:
    FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};

class PYSDK_DLL FBHUDElement_Wrapper : public FBBox_Wrapper {
public:
	FBHUDElement* mFBHUDElement;
public:
	FBHUDElement_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBHUDElement = (FBHUDElement*)pFBComponent; }

	virtual ~FBHUDElement_Wrapper( );

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_DEPRECATED( Visibility, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Show, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Justification, FBHUDElementHAlignment );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( HorizontalDock, FBHUDElementHAlignment );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( VerticalDock, FBHUDElementVAlignment );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( X, double );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Y, double );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( PositionByPercent, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ScaleByPercent, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Width,  double );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Height, double );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ScaleUniformly, bool );
};

class PYSDK_DLL FBHUDTextElement_Wrapper : public FBHUDElement_Wrapper {
public:
	FBHUDTextElement* mFBHUDTextElement;
public:
	FBHUDTextElement_Wrapper( FBComponent* pFBComponent ) : FBHUDElement_Wrapper( pFBComponent ) { mFBHUDTextElement = (FBHUDTextElement*)pFBComponent; }
	explicit FBHUDTextElement_Wrapper( const char* pName ) : FBHUDElement_Wrapper( new FBHUDTextElement( pName )) { mFBHUDTextElement = (FBHUDTextElement*)mFBComponent; }
	virtual ~FBHUDTextElement_Wrapper( );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Content, const char* );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Font, const char* );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( ForceTimeCodeDisplay, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( AdjustWidthToFitText, bool );    
	void SetColor( FBColorAndAlpha_Wrapper&  pValue ) { mFBHUDTextElement->Color = *pValue.mFBColorAndAlpha; }
	FBColorAndAlpha_Wrapper* GetColor(  ) { return FBColorAndAlpha_Wrapper_Factory( mFBHUDTextElement->Color ); }
	void SetBackgroundColor( FBColorAndAlpha_Wrapper&  pValue ) { mFBHUDTextElement->BackgroundColor = *pValue.mFBColorAndAlpha; }
	FBColorAndAlpha_Wrapper* GetBackgroundColor(  ) { return FBColorAndAlpha_Wrapper_Factory( mFBHUDTextElement->BackgroundColor ); }


    FBStringList_Wrapper* GetFontList() { return FBStringList_Wrapper_Factory( mFBHUDTextElement->GetFontList() ); }
};

class PYSDK_DLL FBHUDRectElement_Wrapper : public FBHUDElement_Wrapper
{
public:
    FBHUDRectElement* mFBHUDRectElement;

public:
    FBHUDRectElement_Wrapper( FBComponent* pFBComponent ) : FBHUDElement_Wrapper( pFBComponent ) { mFBHUDRectElement = (FBHUDRectElement*)pFBComponent; }
    explicit FBHUDRectElement_Wrapper( const char* pName ) : FBHUDElement_Wrapper( new FBHUDRectElement( pName )) { mFBHUDRectElement = (FBHUDRectElement*)mFBComponent; }
    virtual ~FBHUDRectElement_Wrapper( ){}

    void                        SetColor( FBColorAndAlpha_Wrapper&  pValue )    { mFBHUDRectElement->Color = *pValue.mFBColorAndAlpha; }
    FBColorAndAlpha_Wrapper*    GetColor()                                      { return FBColorAndAlpha_Wrapper_Factory( mFBHUDRectElement->Color ); }

};


class PYSDK_DLL FBHUDTextureElement_Wrapper : public FBHUDElement_Wrapper {
public:
	FBHUDTextureElement* mFBHUDTextureElement;
public:
	FBHUDTextureElement_Wrapper( FBComponent* pFBComponent ) : FBHUDElement_Wrapper( pFBComponent ) { mFBHUDTextureElement = (FBHUDTextureElement*)pFBComponent; }
	explicit FBHUDTextureElement_Wrapper( const char* pName ) : FBHUDElement_Wrapper( new FBHUDTextureElement( pName )) { mFBHUDTextureElement = (FBHUDTextureElement*)mFBComponent; }
	virtual ~FBHUDTextureElement_Wrapper( );
	object GetTexture(  ) { return FBPropertyListTexture_Wrapper_Factory( mFBHUDTextureElement->Texture ); }

};


class PYSDK_DLL FBHUDFlashElement_Wrapper : public FBHUDElement_Wrapper {
public:
    FBHUDFlashElement* mFBHUDFlashElement;
public:
    FBHUDFlashElement_Wrapper( FBComponent* pFBComponent ) : FBHUDElement_Wrapper( pFBComponent ) { mFBHUDFlashElement = (FBHUDFlashElement*)pFBComponent; }
    explicit FBHUDFlashElement_Wrapper( const char* pName ) : FBHUDElement_Wrapper( new FBHUDFlashElement( pName )) { mFBHUDFlashElement = (FBHUDFlashElement*)mFBComponent; }
    virtual ~FBHUDFlashElement_Wrapper( );

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( FilePath, const char* );

};

class PYSDK_DLL FBHUDBloopSlateElement_Wrapper : public FBHUDFlashElement_Wrapper {
public:
    FBHUDBloopSlateElement* mFBHUDBloopSlateElement;
public:
    FBHUDBloopSlateElement_Wrapper( FBComponent* pFBComponent ) : FBHUDFlashElement_Wrapper( pFBComponent ) { mFBHUDBloopSlateElement = (FBHUDBloopSlateElement*)pFBComponent; }
    explicit FBHUDBloopSlateElement_Wrapper( const char* pName ) : FBHUDFlashElement_Wrapper( new FBHUDBloopSlateElement( pName )) { mFBHUDBloopSlateElement = (FBHUDBloopSlateElement*)mFBComponent; }
    virtual ~FBHUDBloopSlateElement_Wrapper( );
    FBColorAndAlpha_Wrapper* GetBackgroundColor(  ) { return FBColorAndAlpha_Wrapper_Factory( (FBColorAndAlpha)mFBHUDBloopSlateElement->BackgroundColor ); }
    void SetBackgroundColor( FBColorAndAlpha_Wrapper&  pValue ) { mFBHUDBloopSlateElement->BackgroundColor = *pValue.mFBColorAndAlpha; }
    FBColorAndAlpha_Wrapper* GetForegroundColor(  ) { return FBColorAndAlpha_Wrapper_Factory( (FBColorAndAlpha)mFBHUDBloopSlateElement->ForegroundColor ); }
    void SetForegroundColor( FBColorAndAlpha_Wrapper&  pValue ) { mFBHUDBloopSlateElement->ForegroundColor = *pValue.mFBColorAndAlpha; }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS( Enable, bool );
    FBTime_Wrapper* GetShowAfterDelayOnRecordPlay(  ) { return FBTime_Wrapper_Factory( mFBHUDBloopSlateElement->ShowAfterDelayOnRecordPlay); }
    void   SetShowAfterDelayOnRecordPlay( FBTime_Wrapper& pValue ) { mFBHUDBloopSlateElement->ShowAfterDelayOnRecordPlay = *pValue.mFBTime; }
    FBTime_Wrapper* GetShowDuration(  ) { return FBTime_Wrapper_Factory( mFBHUDBloopSlateElement->ShowDuration); }
    void   SetShowDuration( FBTime_Wrapper& pValue ) { mFBHUDBloopSlateElement->ShowDuration = *pValue.mFBTime; }

};

class PYSDK_DLL FBHUDTimelineElement_Wrapper : public FBHUDFlashElement_Wrapper {
public:
    FBHUDTimelineElement* mFBHUDTimelineElement;
public:
    FBHUDTimelineElement_Wrapper( FBComponent* pFBComponent ) : FBHUDFlashElement_Wrapper( pFBComponent ) { mFBHUDTimelineElement = (FBHUDTimelineElement*)pFBComponent; }
    explicit FBHUDTimelineElement_Wrapper( const char* pName ) : FBHUDFlashElement_Wrapper( new FBHUDTimelineElement( pName )) { mFBHUDTimelineElement = (FBHUDTimelineElement*)mFBComponent; }
    virtual ~FBHUDTimelineElement_Wrapper( );

    FBColorAndAlpha_Wrapper* GetHeadActiveColor() { return FBColorAndAlpha_Wrapper_Factory( (FBColorAndAlpha)mFBHUDTimelineElement->HeadActiveColor ); }
    void SetHeadActiveColor( FBColorAndAlpha_Wrapper& pValue ) { mFBHUDTimelineElement->HeadActiveColor = *pValue.mFBColorAndAlpha; }
    FBColorAndAlpha_Wrapper* GetHeadIdleColor() { return FBColorAndAlpha_Wrapper_Factory( (FBColorAndAlpha)mFBHUDTimelineElement->HeadIdleColor ); }
    void SetHeadIdleColor( FBColorAndAlpha_Wrapper& pValue ) { mFBHUDTimelineElement->HeadIdleColor = *pValue.mFBColorAndAlpha; }
    FBTime_Wrapper* GetHeadDuration() { return FBTime_Wrapper_Factory( mFBHUDTimelineElement->HeadDuration ); }
    void SetHeadDuration( FBTime_Wrapper& pValue ) { mFBHUDTimelineElement->HeadDuration = *pValue.mFBTime; }
    
    FBColorAndAlpha_Wrapper* GetCutActiveColor() { return FBColorAndAlpha_Wrapper_Factory( (FBColorAndAlpha)mFBHUDTimelineElement->CutActiveColor ); }
    void SetCutActiveColor( FBColorAndAlpha_Wrapper& pValue ) { mFBHUDTimelineElement->CutActiveColor = *pValue.mFBColorAndAlpha; }
    FBColorAndAlpha_Wrapper* GetCutIdleColor() { return FBColorAndAlpha_Wrapper_Factory( (FBColorAndAlpha)mFBHUDTimelineElement->CutIdleColor ); }
    void SetCutIdleColor( FBColorAndAlpha_Wrapper& pValue ) { mFBHUDTimelineElement->CutIdleColor = *pValue.mFBColorAndAlpha; }

    FBColorAndAlpha_Wrapper* GetTailActiveColor() { return FBColorAndAlpha_Wrapper_Factory( (FBColorAndAlpha)mFBHUDTimelineElement->TailActiveColor ); }
    void SetTailActiveColor( FBColorAndAlpha_Wrapper& pValue ) { mFBHUDTimelineElement->TailActiveColor = *pValue.mFBColorAndAlpha; }
    FBColorAndAlpha_Wrapper* GetTailIdleColor() { return FBColorAndAlpha_Wrapper_Factory( (FBColorAndAlpha)mFBHUDTimelineElement->TailIdleColor ); }
    void SetTailIdleColor( FBColorAndAlpha_Wrapper& pValue ) { mFBHUDTimelineElement->TailIdleColor = *pValue.mFBColorAndAlpha; }
    FBTime_Wrapper* GetTailDuration() { return FBTime_Wrapper_Factory( mFBHUDTimelineElement->TailDuration ); }
    void SetTailDuration( FBTime_Wrapper& pValue ) { mFBHUDTimelineElement->TailDuration = *pValue.mFBTime; }
};

#endif // pyfbviewerinfos_h__
