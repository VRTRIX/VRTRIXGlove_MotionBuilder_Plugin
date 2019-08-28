#ifndef pyfbapplication_h__
#define pyfbapplication_h__
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

#include "pyfbmatrix.h"
#include "pyfbplotoptions.h"
#if !defined(K_NO_RENDERER)
	#include "pyfbvideograboptions.h"
	#include "pyfbaudiorenderoptions.h"
#endif
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbtake.h"
#include "pyfbvideo.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbconstraint.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"
#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbkeyinggroup.h"
#include "pyfbcharacterextension.h"
#include "pyfbcharactersolver.h"
#include "pyfbcharacter.h"
#include "pyfbcamera.h"
#include "pyfbfbxoptions.h"
#include "pyfbbatchoptions.h"

// =======================================================================================
// FBApplication
// =======================================================================================
void FBApplication_Init();

class PYSDK_DLL FBApplication_Wrapper : public FBComponent_Wrapper {
public:
	FBApplication* mFBApplication;
public:
	FBApplication_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBApplication = (FBApplication*)pFBComponent; }
	FBApplication_Wrapper(  ) : FBComponent_Wrapper( &FBApplication::TheOne() ) { mFBApplication = (FBApplication*)mFBComponent; }
	virtual ~FBApplication_Wrapper( );
	bool ExecuteScript(const char* pFilename) { return mFBApplication->ExecuteScript( pFilename ); }
    FBBatchStatus FileBatch(FBBatchOptions_Wrapper& pBatchOptions, FBPlotOptions_Wrapper* pPlotOptions = NULL) { return mFBApplication->FileBatch( pBatchOptions.mFBBatchOptions, pPlotOptions ? pPlotOptions->mFBPlotOptions : 0 ); }
	void FileExit(bool pSave = false) { mFBApplication->FileExit( pSave ); }
	bool FileExport(const char* pFilename) { return mFBApplication->FileExport( pFilename ); }
    bool FileImport(const char* pFilename, bool pMatchModels = false, bool pCreateUnmatchedModels = true) { return mFBApplication->FileImport( pFilename, pMatchModels, pCreateUnmatchedModels ); }
	bool FileExportBatch(const char* pName, FBTake_Wrapper& pTake, FBBatchOptions_Wrapper& pBatchOptions, FBModelList_Wrapper& pExportModels) { return mFBApplication->FileExportBatch( pName, pTake.mFBTake, pBatchOptions.mFBBatchOptions, *pExportModels.mFBModelList ); }
	bool FileImportBatch(const char* pName, FBBatchOptions_Wrapper& pBatchOptions, FBModel_Wrapper& pReference) { return mFBApplication->FileImportBatch( pName, pBatchOptions.mFBBatchOptions, pReference.mFBModel ); }
    bool IsValidBatchFile(const char* pFilename) { return mFBApplication->IsValidBatchFile( pFilename ); }
    bool FileAppend(const char * pFilename, bool pShowUIMsg=false, FBFbxOptions_Wrapper* pOptions = NULL) { return mFBApplication->FileAppend( pFilename, pShowUIMsg, pOptions ? pOptions->mFBFbxOptions : NULL ); }
	bool FileMerge (const char * pFilename, bool pShowUIMsg=false, FBFbxOptions_Wrapper* pOptions = NULL) { return mFBApplication->FileMerge( pFilename, pShowUIMsg, pOptions ? pOptions->mFBFbxOptions : NULL ); }
	bool FileMerge(FBStringList_Wrapper& pPathlist, bool pShowUIMsg=false, FBFbxOptions_Wrapper* pOptions = NULL);
	bool FileNew() { return mFBApplication->FileNew(  ); }
	bool FileOpen(const char * pFilename, bool pShowUIMsg=false, FBFbxOptions_Wrapper* pOptions = NULL) { return mFBApplication->FileOpen( pFilename, pShowUIMsg, pOptions ? pOptions->mFBFbxOptions : NULL ); }
    bool FileOpenFromMemory( kReference pBuffer, kULong pBufferLength ) { return mFBApplication->FileOpen((void*)pBuffer, pBufferLength); }
    object GetMaxFrameCount(kReference pBuffer, kULong pBufferLength, int pTimeScale);
#if !defined(K_NO_RENDERER)
	bool FileRender(FBVideoGrabOptions_Wrapper* pRenderOptions = NULL) { return mFBApplication->FileRender( pRenderOptions ? pRenderOptions->mFBVideoGrabOptions : 0 ); }
	bool AudioRender(FBAudioRenderOptions_Wrapper* pAudioRenderOptions = NULL) { return mFBApplication->AudioRender( pAudioRenderOptions ? pAudioRenderOptions->mFBAudioRenderOptions : NULL); }
#endif
	bool FileSave(const char * pFilename = NULL, FBFbxOptions_Wrapper* pOptions = NULL) { return mFBApplication->FileSave( pFilename, pOptions ? pOptions->mFBFbxOptions : NULL  ); }
	bool Maximize() { return mFBApplication->Maximize(  ); }
	bool Minimize(bool pBlocking = true) { return mFBApplication->Minimize( pBlocking ); }
    void UpdateAllWidgets() { mFBApplication->UpdateAllWidgets(); }
    void FlushEventQueue() { mFBApplication->FlushEventQueue(); }
	void SwitchViewerCamera(FBCamera_Wrapper& pCamera);
    void SetCurrentActor( FBActor_Wrapper* pCurrentActor ) { mFBApplication->CurrentActor = pCurrentActor ? pCurrentActor->mFBActor : NULL; }
    object GetCurrentActor(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBApplication->CurrentActor ); }
    void SetCurrentCharacter( FBCharacter_Wrapper* pCurrentCharacter ) { mFBApplication->CurrentCharacter = pCurrentCharacter ? pCurrentCharacter->mFBCharacter : NULL; }
	object GetCurrentCharacter(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBApplication->CurrentCharacter ); }
	void SetFBXFileName( const char* pFBXFileName ) { mFBApplication->FBXFileName = pFBXFileName; }
	const char* GetFBXFileName(  ) { return mFBApplication->FBXFileName; }   
    bool SaveCharacterRigAndAnimation( const char* pFileName, FBCharacter_Wrapper& pCharacter, FBFbxOptions_Wrapper& pFbxOptions) { return mFBApplication->SaveCharacterRigAndAnimation(pFileName, pCharacter.mFBCharacter, pFbxOptions.mFBFbxOptions); }
    bool LoadAnimationOnCharacter(const char * pFileName, FBCharacter_Wrapper& pCharacter, FBFbxOptions_Wrapper& pFbxOptions, FBPlotOptions_Wrapper& pPlotOptions) { return mFBApplication->LoadAnimationOnCharacter( pFileName, pCharacter.mFBCharacter, pFbxOptions.mFBFbxOptions, pPlotOptions.mFBPlotOptions); }
	bool OneClickSendAsNewScene(FBOneClickApplication pApplication) { return mFBApplication->OneClickSendAsNewScene(pApplication); }
	bool OneClickUpdateCurrentScene() { return mFBApplication->OneClickUpdateCurrentScene(); }
	bool OneClickAddToCurrentScene() { return mFBApplication->OneClickAddToCurrentScene(); }
	void OneClickSelectPreviouslySentObject() { mFBApplication->OneClickSelectPreviouslySentObject(); }
	FBOneClickApplication OneClickIsConnectedTo() { return mFBApplication->OneClickIsConnectedTo(); }
    object OnFileNewCompleted();
    object OnFileNew();
    object OnFileOpenCompleted();
    object OnFileOpen();
    object OnFileSaveCompleted();
    object OnFileSave();
    object OnFileExit();
    object OnFileMerge();

protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbapplication_h__
