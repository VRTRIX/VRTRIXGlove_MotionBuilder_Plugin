#ifndef pyfbtake_h__
#define pyfbtake_h__
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

#include "pyfbplotoptions.h"
#include "pyfbbox.h"

// =======================================================================================
// FBTake
// =======================================================================================
void FBTake_Init();

class PYSDK_DLL FBTake_Wrapper : public FBComponent_Wrapper {
public:
    FBTake* mFBTake;
public:
    FBTake_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBTake = (FBTake*)pFBComponent; }
    FBTake_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBTake( pName )) { mFBTake = (FBTake*)mFBComponent; }
    virtual ~FBTake_Wrapper( ) {}
    void ClearAllProperties(bool pOnSelectedObjectsOnly, bool pOnLockedProperties = false) { mFBTake->ClearAllProperties( pOnSelectedObjectsOnly , pOnLockedProperties ); }
    void ClearAllPropertiesOnCurrentLayer() { mFBTake->ClearAllPropertiesOnCurrentLayer(); }
    void FBDelete() { mFBTake->FBDelete(  ); }
    object CopyTake(const char * pNewTakeName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBTake->CopyTake( pNewTakeName )); }
    void PlotAllTakesOnSelected(FBTime_Wrapper& pPlotPeriod) { mFBTake->PlotAllTakesOnSelected( *pPlotPeriod.mFBTime ); }
    void PlotAllTakesOnSelectedProperties(FBTime_Wrapper& pPlotPeriod) { mFBTake->PlotAllTakesOnSelectedProperties( *pPlotPeriod.mFBTime ); }
    void CreateNewLayer() { mFBTake->CreateNewLayer(); }
    void RemoveLayer(int pLayerIndex) { mFBTake->RemoveLayer(pLayerIndex); }
    object GetLayer(int pLayerID) { return FBWrapperFactory::TheOne().WrapFBObject( mFBTake->GetLayer( pLayerID)); }
    object GetLayerByName(const char* pName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBTake->GetLayerByName( pName)); }
    void SetCurrentLayer(int pLayerIndex) { mFBTake->SetCurrentLayer(pLayerIndex); }
    int GetCurrentLayer() { return mFBTake->GetCurrentLayer(); }
    int GetLayerCount() { return mFBTake->GetLayerCount(); }
    bool MoveCurrentLayerUp() { return mFBTake->MoveCurrentLayerUp(); }
    bool MoveCurrentLayerDown() { return mFBTake->MoveCurrentLayerDown(); }
    void DuplicateSelectedLayers() { mFBTake->DuplicateSelectedLayers(); }
    void MergeLayers(FBAnimationLayerMergeOptions pMergeOptions, bool pDeleteMergedLayers, FBMergeLayerMode pMergeMode, bool pMergeLockedProperties = false) { mFBTake->MergeLayers(pMergeOptions, pDeleteMergedLayers, pMergeMode, pMergeLockedProperties); }

    // COMMENT MERGE PREIVEW
#ifdef MERGE_PREVIEW
    bool CanDoMergePreview() { return mFBTake->CanDoMergePreview(); }
    bool IsInMergePreviewMode() { return mFBTake->IsInMergePreviewMode(); }
    bool DoMergePreview() { return mFBTake->DoMergePreview(); }
    void QuitMergePreview() { mFBTake->QuitMergePreview(); }
#endif

    void PlotTakeOnSelected(FBTime_Wrapper& pPlotPeriod) { mFBTake->PlotTakeOnSelected( *pPlotPeriod.mFBTime ); }
    void PlotTakeOnSelectedProperties(FBTime_Wrapper& pPlotPeriod) { mFBTake->PlotTakeOnSelectedProperties( *pPlotPeriod.mFBTime ); }
    void PlotTakeOnSelected_Options(FBPlotOptions_Wrapper& pPlotOptions) { mFBTake->PlotTakeOnSelected( pPlotOptions.mFBPlotOptions ); }
    void PlotTakeOnSelectedProperties_Options(FBPlotOptions_Wrapper& pPlotOptions) { mFBTake->PlotTakeOnSelectedProperties( pPlotOptions.mFBPlotOptions ); }
    void SetComments( const char* pComments ) { mFBTake->Comments = pComments; }
    const char* GetComments(  ) { return mFBTake->Comments; }
    void SetLocalTimeSpan( FBTimeSpan_Wrapper& pLocalTimeSpan ) { mFBTake->LocalTimeSpan = *pLocalTimeSpan.mFBTimeSpan; }
    FBTimeSpan_Wrapper* GetLocalTimeSpan(  ) { return FBTimeSpan_Wrapper_Factory( mFBTake->LocalTimeSpan ); }
    void SetReferenceTimeSpan( FBTimeSpan_Wrapper& pReferenceTimeSpan ) { mFBTake->ReferenceTimeSpan = *pReferenceTimeSpan.mFBTimeSpan; }
    FBTimeSpan_Wrapper* GetReferenceTimeSpan(  ) { return FBTimeSpan_Wrapper_Factory( mFBTake->ReferenceTimeSpan ); }
	int AddTimeMark( FBTime_Wrapper& pTime ) { return mFBTake->AddTimeMark( *pTime.mFBTime ); }
	bool DeleteTimeMark( int pIndex ) { return mFBTake->DeleteTimeMark( pIndex ); }
	void DeleteAllTimeMarks() { mFBTake->DeleteAllTimeMarks(); }
	int GetTimeMarkCount() { return mFBTake->GetTimeMarkCount(); }
	FBTime_Wrapper* GetTimeMarkTime( int pIndex ) { return FBTime_Wrapper_Factory( mFBTake->GetTimeMarkTime( pIndex ) ); }
	int SetTimeMarkTime( int pIndex, FBTime_Wrapper& pTime ) { return  mFBTake->SetTimeMarkTime( pIndex, *pTime.mFBTime ); }
	const char* GetTimeMarkName( int pIndex ) { return mFBTake->GetTimeMarkName( pIndex ); }
	bool SetTimeMarkName( int pIndex, const char* pName ) { return mFBTake->SetTimeMarkName( pIndex, pName ); }
	FBTimeMarkAction GetTimeMarkAction( int pIndex ) { return mFBTake->GetTimeMarkAction( pIndex ); }
	bool SetTimeMarkAction( int pIndex, FBTimeMarkAction pAction ) { return mFBTake->SetTimeMarkAction( pIndex, pAction ); }
	FBColor_Wrapper* GetTimeMarkColor( int pIndex ) { return FBColor_Wrapper_Factory( mFBTake->GetTimeMarkColor( pIndex ) ); }
	bool SetTimeMarkColor( int pIndex, FBColor_Wrapper& pColor ) { return mFBTake->SetTimeMarkColor( pIndex, *pColor.mFBColor ); }
	int GetNextTimeMarkIndex() { return mFBTake->GetNextTimeMarkIndex(); }
	int GetPreviousTimeMarkIndex() { return mFBTake->GetPreviousTimeMarkIndex(); }
	void SetLayerRealSelection( bool pValue ) { mFBTake->SetLayerRealSelection( pValue ); }
	bool GetLayerRealSelection(  ) { return mFBTake->GetLayerRealSelection(); }

    void ConvertListToBoxArray( list *pList, FBArrayTemplate<FBBox *> *pBoxArray )
    {
        if ( !pList || !pBoxArray ) {
            return;
        }
        for ( int itr = 0; itr < len(*pList); ++itr ) {
            object lObject = (*pList)[itr];
            extract<FBBox_Wrapper*> lExtractor(lObject);

            // Make sure this is a valid object, and that it is not a "None" object
            if ( lExtractor.check() && lExtractor() ) 
            {
                FBBox *lBBox = lExtractor()->mFBBox;
                if ( lBBox ) 
                {
                    pBoxArray->Add( lBBox );
                }
            }
        }
    }

    void ConvertListToPropertyArray( list *pList, FBArrayTemplate<FBProperty *> *pPropertyArray ) 
    {
        if ( !pList || !pPropertyArray ) {
            return;
        }

        for ( int itr = 0; itr < len(*pList); ++itr ) {
            object lObject = (*pList)[itr];
            extract<FBProperty_Wrapper*> lExtractor(lObject);

            // Make sure this is a valid object, and that it is not a "None" object
            if ( lExtractor.check() && lExtractor() ) 
            {
                FBProperty *lProperty = lExtractor()->mFBProperty;
                if ( lProperty ) 
                {
                    pPropertyArray->Add( lProperty );
                }
            }
        }
    }

    void PlotTakeOnObjects_Options(FBPlotOptions_Wrapper& pPlotOptions, list pObjectsToPlot ) 
    { 
        // Convert Boost Python list to FBArrayTemplate
        FBArrayTemplate<FBBox *> lObjectsToPlot;
        ConvertListToBoxArray( &pObjectsToPlot, &lObjectsToPlot );

        mFBTake->PlotTakeOnObjects( pPlotOptions.mFBPlotOptions, &lObjectsToPlot ); 
    }

    void PlotTakeOnObjects(FBTime_Wrapper& pPlotPeriod, list pObjectsToPlot ) 
    { 
        // Convert Boost Python list to FBArrayTemplate
        FBArrayTemplate<FBBox *> lObjectsToPlot;
        ConvertListToBoxArray( &pObjectsToPlot, &lObjectsToPlot );

        mFBTake->PlotTakeOnObjects( *pPlotPeriod.mFBTime, &lObjectsToPlot ); 
    }

    void PlotAllTakesOnObjects(FBTime_Wrapper& pPlotPeriod, list pObjectsToPlot ) 
    { 
        // Convert Boost Python list to FBArrayTemplate
        FBArrayTemplate<FBBox *> lObjectsToPlot;
        ConvertListToBoxArray( &pObjectsToPlot, &lObjectsToPlot );

        mFBTake->PlotAllTakesOnObjects( *pPlotPeriod.mFBTime, &lObjectsToPlot ); 
    }

    void PlotTakeOnProperties( FBTime_Wrapper& pPlotPeriod, list pPropertiesToPlot ) 
    { 
        // Convert Boost Python list to FBArrayTemplate
        FBArrayTemplate<FBProperty *> lPropertiesToPlot;
        ConvertListToPropertyArray( &pPropertiesToPlot, &lPropertiesToPlot );

        mFBTake->PlotTakeOnProperties( *pPlotPeriod.mFBTime, &lPropertiesToPlot ); 
    }

    void PlotAllTakesOnProperties( FBTime_Wrapper& pPlotPeriod, list pPropertiesToPlot ) 
    { 
        // Convert Boost Python list to FBArrayTemplate
        FBArrayTemplate<FBProperty *> lPropertiesToPlot;
        ConvertListToPropertyArray( &pPropertiesToPlot, &lPropertiesToPlot );

        mFBTake->PlotAllTakesOnProperties( *pPlotPeriod.mFBTime, &lPropertiesToPlot ); 
    }
};
#endif // pyfbtake_h__