#ifndef pyfbanimationlayer_h__
#define pyfbanimationlayer_h__
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
// FBAnimationLayer
// =======================================================================================
void FBAnimationLayer_Init();

class PYSDK_DLL FBAnimationLayer_Wrapper : public FBComponent_Wrapper {
public:
	FBAnimationLayer* mFBAnimationLayer;
public:
	FBAnimationLayer_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAnimationLayer = (FBAnimationLayer*)pFBComponent; }
	FBAnimationLayer_Wrapper( const char* pName, int pLayerID ) : FBComponent_Wrapper( new FBAnimationLayer( pName, pLayerID )) { mFBAnimationLayer = (FBAnimationLayer*)mFBComponent; }
	virtual ~FBAnimationLayer_Wrapper( ) {}
	void	FBDelete() { mFBAnimationLayer->FBDelete(  ); }
	void	AddChildLayer( FBAnimationLayer_Wrapper& pAnimationLayer ) { mFBAnimationLayer->AddChildLayer(pAnimationLayer.mFBAnimationLayer); }
	object	GetChildLayer( int pIndex ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAnimationLayer->GetChildLayer(pIndex) ); }
	int		GetChildCount() { return mFBAnimationLayer->GetChildCount(); }
	void	SetParentLayer( FBAnimationLayer_Wrapper& pParentLayer ) { mFBAnimationLayer->SetParentLayer(pParentLayer.mFBAnimationLayer); }
	object	GetParentLayer() { return FBWrapperFactory::TheOne().WrapFBObject( mFBAnimationLayer->GetParentLayer() ); }
	int		GetLayerIndex() { return mFBAnimationLayer->GetLayerIndex(); }

	list GetCompleteChildHierarchy(FBComponent_Wrapper& pLayerObject)
    {
        list lResult;
        FBArrayTemplate<FBAnimationLayer*> pChildLayer;
        mFBAnimationLayer->GetCompleteChildHierarchy( &pChildLayer );
        for( int lIdx = 0; lIdx < pChildLayer.GetCount(); ++lIdx )
        {            
            lResult.append( FBWrapperFactory::TheOne().WrapFBObject( pChildLayer[lIdx] ) );
        }

        return lResult;
    }

	void SetSolo( bool pSolo ) { mFBAnimationLayer->Solo = pSolo; }
	bool GetSolo(  ) { return mFBAnimationLayer->Solo; }
	void SetMute( bool pMute ) { mFBAnimationLayer->Mute = pMute; }
	bool GetMute(  ) { return mFBAnimationLayer->Mute; }
	void SetLock( bool pLock) { mFBAnimationLayer->Lock = pLock; }
	bool GetLock(  ) { return mFBAnimationLayer->Lock; }
	void SetWeight( double pWeight) { mFBAnimationLayer->Weight = pWeight; }
	double GetWeight(  ) { return mFBAnimationLayer->Weight; }
	void SetLayerMode( FBLayerMode pLayerMode) { mFBAnimationLayer->LayerMode = pLayerMode; }
	FBLayerMode GetLayerMode(  ) { return mFBAnimationLayer->LayerMode; }
	void SetLayerRotationMode( FBLayerRotationMode pLayerMode) { mFBAnimationLayer->LayerRotationMode = pLayerMode; }
	FBLayerRotationMode GetLayerRotationMode(  ) { return mFBAnimationLayer->LayerRotationMode; }
	void SelectLayer( bool pSelect, bool pExclusiveSelection ) { mFBAnimationLayer->SelectLayer(pSelect, pExclusiveSelection); }
	bool IsSelected( ) { return mFBAnimationLayer->IsSelected(); }
};
#endif // pyfbanimationlayer_h__
