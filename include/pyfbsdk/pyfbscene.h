#ifndef pyfbscene_h__
#define pyfbscene_h__
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

#include "pyfbstringlist.h"
#include "pyfbarraytemplate.h"	// Requires FBModel_Wrapper from class_f_b_model_gen.h.

// =======================================================================================
// FBScene
// =======================================================================================
void FBScene_Init();

class PYSDK_DLL FBScene_Wrapper : public FBComponent_Wrapper {
public:
    FBScene* mFBScene;
public:
    FBScene_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBScene = (FBScene*)pFBComponent; }
    virtual ~FBScene_Wrapper( ) { }
    void Clear() 
    {
        PyErr_WarnEx( PyExc_UserWarning, "Deprecated FBScene.Clear: Use FBApplication.FileNew instead.", 1 );
        mFBScene->Clear(  );
    }
    bool Evaluate() { return mFBScene->Evaluate(  ); }
    bool CandidateEvaluationAndResolve () { return mFBScene->CandidateEvaluationAndResolve(); }
    bool EvaluateDeformations() { return mFBScene->EvaluateDeformations(  ); }
    void FBDelete() { mFBScene->FBDelete(  ); }
    int  NamespaceGetChildrenList(FBStringList_Wrapper& pNamespaceList, const char* pNamespace = NULL, bool pRecursive = true ) { mFBScene->NamespaceGetChildrenList(*(pNamespaceList.mFBStringList), pNamespace, pRecursive); return pNamespaceList.mFBStringList->GetCount();}
    object NamespaceGet(const char* pNamespace) { return FBWrapperFactory::TheOne().WrapFBObject( mFBScene->NamespaceGet(pNamespace)); }
    object NamespaceGetOwnerFileReference(const char* pNamespace) { return FBWrapperFactory::TheOne().WrapFBObject( mFBScene->NamespaceGetOwnerFileReference(pNamespace)); }
    bool NamespaceExist(const char* pNamespace) { return mFBScene->NamespaceExist(pNamespace); }
    bool NamespaceEmpty(const char* pNamespace) { return mFBScene->NamespaceEmpty(pNamespace); }
    void NamespaceGetContentList(FBComponentList_Wrapper& pContentList, const char* pNamespace, FBPlugModificationFlag pModificationFlags = kFBPlugAllContent, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false) { mFBScene->NamespaceGetContentList( *(pContentList.mFBObjectList), pNamespace, pModificationFlags, pRecursive, pTypeInfo, pExactTypeMatch); }
    void NamespaceSelectContent(const char* pNamespace, bool pSelect, FBPlugModificationFlag pModificationFlags = kFBPlugAllContent, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false) { mFBScene->NamespaceSelectContent( pNamespace, pSelect, pModificationFlags, pRecursive, pTypeInfo, pExactTypeMatch); }
    bool NamespaceRename(const char* pNamespace, const char* pNewNamespace, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false) { return mFBScene->NamespaceRename(pNamespace, pNewNamespace, pRecursive, pTypeInfo, pExactTypeMatch); }
    bool NamespaceDelete(const char* pNamespace) { return mFBScene->NamespaceDelete(pNamespace); }
    bool NamespaceCleanup() { return mFBScene->NamespaceCleanup(); }
    bool NamespaceDeleteContent(const char* pNamespace, FBPlugModificationFlag pModificationFlags = kFBPlugAllContent, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false) { return mFBScene->NamespaceDeleteContent(pNamespace, pModificationFlags, pRecursive, pTypeInfo, pExactTypeMatch); }
    bool NamespaceImport(const char* pNamespace, const char* pFilePath, bool pAsFileReference = false )  { return mFBScene->NamespaceImport(pNamespace, pFilePath, pAsFileReference); }
    bool NamespaceImportToMultiple(const FBStringList_Wrapper& pDstNamespaceList, const char* pFilePath, bool pAsFileReference = false )  { return mFBScene->NamespaceImportToMultiple(*(pDstNamespaceList.mFBStringList), pFilePath, pAsFileReference); }
    bool NamespaceExport(const char* pNamespace, const char* pFilePath, bool pASCIIFormat = false)  { return mFBScene->NamespaceExport(pNamespace, pFilePath, pASCIIFormat); }
    FBStringList_Wrapper* GetScriptsPaths()
    {
        FBStringList lList;
        mFBScene->GetScriptsPaths( lList );
        return FBStringList_Wrapper_Factory( lList ); 
    }

#ifndef K_NO_ACTOR
    object GetActorFaces(  ){ return FBPropertyListActorFace_Wrapper_Factory( mFBScene->ActorFaces ); }
    object GetActors(  )    { return FBPropertyListActor_Wrapper_Factory( mFBScene->Actors ); }
#endif
    object GetAudioClips(  ){ return FBPropertyListAudioClip_Wrapper_Factory( mFBScene->AudioClips ); }
    object GetCameras()     { return FBPropertyListCamera_Wrapper_Factory( mFBScene->Cameras ); }
    object GetCharacterExtensions(  ) { return FBPropertyListCharacterExtension_Wrapper_Factory( mFBScene->CharacterExtensions ); }
    object GetCharacterFaces(){ return FBPropertyListCharacterFace_Wrapper_Factory( mFBScene->CharacterFaces ); }
    object GetCharacterPoses(){ return FBPropertyListCharacterPose_Wrapper_Factory( mFBScene->CharacterPoses ); }
    object GetCharacters()  { return FBPropertyListCharacter_Wrapper_Factory( mFBScene->Characters ); }
    object GetComponents()  { return WrapFBObject<FBPropertyListComponent_Wrapper,FBPropertyListComponent>( &mFBScene->Components ); }
    object GetConstraints() { return FBPropertyListConstraint_Wrapper_Factory( mFBScene->Constraints ); }
    object GetControlSets() { return FBPropertyListControlSet_Wrapper_Factory( mFBScene->ControlSets ); }
    object GetDevices()     { return FBPropertyListDevice_Wrapper_Factory( mFBScene->Devices ); }
#if !defined(K_NO_FOLDER)
    object GetFolders(  )   { return FBPropertyListFolder_Wrapper_Factory( mFBScene->Folders ); }
#endif
    object GetGroups(  )    { return FBPropertyListGroup_Wrapper_Factory( mFBScene->Groups ); }
#if !defined(K_NO_MANIPULATOR)
    object GetHandles(  )   { return FBPropertyListHandle_Wrapper_Factory( mFBScene->Handles ); }
#endif
#if !defined(K_NO_HUD)
    object GetHUDs(  )      { return FBPropertyListHUD_Wrapper_Factory( mFBScene->HUDs ); }
#endif
    object GetLights(  )    { return FBPropertyListLight_Wrapper_Factory( mFBScene->Lights ); }
    object GetMarkerSets(  ){ return FBPropertyListMarkerSet_Wrapper_Factory( mFBScene->MarkerSets ); }
    object GetCharacterMarkerSets(  ){ return FBPropertyListCharacterMarkerSet_Wrapper_Factory( mFBScene->CharacterMarkerSets ); }
    object GetMaterials(  ) { return FBPropertyListMaterial_Wrapper_Factory( mFBScene->Materials ); }
    object GetMotionClips( ){ return FBPropertyListMotionClip_Wrapper_Factory( mFBScene->MotionClips ); }
#if !defined(K_NO_NOTE)
    object GetNotes(  ) { return FBPropertyListNote_Wrapper_Factory( mFBScene->Notes ); }
#endif
#if !defined(K_NO_POSE)
    object GetPoses(  ) { return FBPropertyListPose_Wrapper_Factory( mFBScene->Poses ); }
    object GetObjectPoses(  ) { return FBPropertyListObjectPose_Wrapper_Factory( mFBScene->ObjectPoses ); }
#endif
    object GetPhysicalProperties(  ) { return FBPropertyListPhysicalProperties_Wrapper_Factory( mFBScene->PhysicalProperties ); }
    object GetRenderer(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBScene->Renderer ); }
#if !defined(K_NO_PROJECTSETTINGS)
    FBProjectSettings_Wrapper* GetProjectSettings(  ) { return FBProjectSettings_Wrapper_Factory(mFBScene->ProjectSettings); }
#endif
    object GetRootModel(  ) { return FBModel_Wrapper_Factory( mFBScene->RootModel ); }
    object GetSets(  ) { return FBPropertyListSet_Wrapper_Factory( mFBScene->Sets ); }
    object GetNamespaces()	{ return FBPropertyListNamespace_Wrapper_Factory( mFBScene->Namespaces ); }
    object GetFileReferences()	{ return FBPropertyListFileReference_Wrapper_Factory( mFBScene->FileReferences ); }
    object GetShaders(  ) { return FBPropertyListShader_Wrapper_Factory( mFBScene->Shaders ); }
    object GetDeformers(  ) { return FBPropertyListDeformer_Wrapper_Factory( mFBScene->Deformers ); }
    object GetConstraintSolvers(  ) { return FBPropertyListConstraintSolver_Wrapper_Factory( mFBScene->ConstraintSolvers ); }
    object GetTakes(  ) { return FBPropertyListTake_Wrapper_Factory( mFBScene->Takes ); }
    object GetTextures(  ) { return FBPropertyListTexture_Wrapper_Factory( mFBScene->Textures ); }
#ifndef FB_KERNEL 
    object GetUserObjects(  ) { return WrapFBObject<FBPropertyListUserObject_Wrapper,FBPropertyListUserObject>( &mFBScene->UserObjects ); }    
#endif
    object GetVideoClips(  ) { return FBPropertyListVideoClip_Wrapper_Factory( mFBScene->VideoClips ); }

    object GetKeyingGroups()   { return FBPropertyListKeyingGroup_Wrapper_Factory( mFBScene->KeyingGroups); }
    object GetModelSkeletons()   { return FBPropertyListModelSkeleton_Wrapper_Factory( mFBScene->ModelSkeletons); }
    object GetModelOpticals()   { return FBPropertyListModelOptical_Wrapper_Factory( mFBScene->ModelOpticals); }

    object OnChange();
    object OnTakeChange();
protected:
    FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbscene_h__