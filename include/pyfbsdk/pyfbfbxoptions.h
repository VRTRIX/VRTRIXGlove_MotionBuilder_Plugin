#ifndef pyfbfbxoptions_h__
#define pyfbfbxoptions_h__
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

#include "pyfbbox.h"

// =======================================================================================
// FBFbxManager
// =======================================================================================
void FBFbxOptions_Init();

class FBFbxOptions_Wrapper : public FBComponent_Wrapper {
public:
	FBFbxOptions* mFBFbxOptions;
public:
	FBFbxOptions_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBFbxOptions = (FBFbxOptions*)pFBComponent; }
	FBFbxOptions_Wrapper( bool pLoad ) : FBComponent_Wrapper( new FBFbxOptions( pLoad, NULL)) { mFBFbxOptions = (FBFbxOptions*)mFBComponent; SetAllocated(); }
    FBFbxOptions_Wrapper( bool pLoad, const char* pFileToLoad ) : FBComponent_Wrapper( new FBFbxOptions( pLoad, pFileToLoad)) { mFBFbxOptions = (FBFbxOptions*)mFBComponent; SetAllocated(); }
	virtual ~FBFbxOptions_Wrapper( ) { }
    void SetAll( FBElementAction pAction, bool pAnimation ) { mFBFbxOptions->SetAll( pAction, pAnimation); }
    void SetFromString( const char* pString ) { mFBFbxOptions->SetFromString( pString,kFBOptionsContextMerge); }
    const char* SaveToString() { static FBString lValue; mFBFbxOptions->SaveToString(lValue,kFBOptionsContextMerge); return (char*)lValue; }
	void SetCameraSwitcherSettings( bool pCameraSwitcherSettings ) { mFBFbxOptions->CameraSwitcherSettings = pCameraSwitcherSettings; }
    bool GetCameraSwitcherSettings(  ) { return mFBFbxOptions->CameraSwitcherSettings; }
    void SetBaseCameras( bool pBaseCameras ) { mFBFbxOptions->BaseCameras = pBaseCameras; }
    bool GetBaseCameras(  ) { return mFBFbxOptions->BaseCameras; }    
    void SetCharacterFacesAnimation( bool pCharacterFacesAnimation ) { mFBFbxOptions->CharacterFacesAnimation = pCharacterFacesAnimation; }
    bool GetCharacterFacesAnimation(  ) { return mFBFbxOptions->CharacterFacesAnimation; }
    void SetCurrentCameraSettings( bool pCurrentCameraSettings ) { mFBFbxOptions->CurrentCameraSettings = pCurrentCameraSettings; }
    bool GetCurrentCameraSettings(  ) { return mFBFbxOptions->CurrentCameraSettings; }
    void SetGlobalLightingSettings( bool pGlobalLightingSettings ) { mFBFbxOptions->GlobalLightingSettings = pGlobalLightingSettings; }
    bool GetGlobalLightingSettings(  ) { return mFBFbxOptions->GlobalLightingSettings; }    

	void SetTakeSpan( FBTakeSpanOnLoad pTakeSpan ) { mFBFbxOptions->TakeSpan = pTakeSpan; }
	FBTakeSpanOnLoad GetTakeSpan(  ) { return mFBFbxOptions->TakeSpan; }    

	void SetActors( FBElementAction pActors ) { mFBFbxOptions->Actors = pActors; }
    FBElementAction GetActors(  ) { return mFBFbxOptions->Actors; }	

	void SetActorFaces( FBElementAction pActorFaces ) { mFBFbxOptions->ActorFaces = pActorFaces; }
	FBElementAction GetActorFaces(  ) { return mFBFbxOptions->ActorFaces; }
	void SetActorFacesAnimation( bool pActorFacesAnimation ) { mFBFbxOptions->ActorFacesAnimation = pActorFacesAnimation; }
	bool GetActorFacesAnimation(  ) { return mFBFbxOptions->ActorFacesAnimation; }

    void SetBones( FBElementAction pBones ) { mFBFbxOptions->Bones = pBones; }
    FBElementAction GetBones(  ) { return mFBFbxOptions->Bones; }
    void SetBonesAnimation( bool pBonesAnim ) { mFBFbxOptions->BonesAnimation = pBonesAnim; }
    bool GetBonesAnimation(  ) { return mFBFbxOptions->BonesAnimation; }
	
	void SetAudio( FBElementAction pAudio ) { mFBFbxOptions->Audio = pAudio; }
	FBElementAction GetAudio(  ) { return mFBFbxOptions->Audio; }	

	void SetCameras( FBElementAction pCameras ) { mFBFbxOptions->Cameras = pCameras; }
	FBElementAction GetCameras(  ) { return mFBFbxOptions->Cameras; }
	void SetCamerasAnimation( bool pCamerasAnimation ) { mFBFbxOptions->CamerasAnimation = pCamerasAnimation; }
	bool GetCamerasAnimation(  ) { return mFBFbxOptions->CamerasAnimation; }
	
	void SetCharacterExtensions( FBElementAction pCharacterExtensions ) { mFBFbxOptions->CharacterExtensions = pCharacterExtensions; }
	FBElementAction GetCharacterExtensions(  ) { return mFBFbxOptions->CharacterExtensions; }

	void SetCharacterFaces( FBElementAction pCharacterFaces ) { mFBFbxOptions->CharacterFaces = pCharacterFaces; }
	FBElementAction GetCharacterFaces(  ) { return mFBFbxOptions->CharacterFaces; }
	
	void SetCharacters( FBElementAction pCharacters );
	FBElementAction GetCharacters(  );
	void SetCharactersAnimation( bool pCharactersAnimation ) { mFBFbxOptions->CharactersAnimation = pCharactersAnimation; }
	bool GetCharactersAnimation(  ) { return mFBFbxOptions->CharactersAnimation; }
    	
	void SetConstraints( FBElementAction pConstraints ) { mFBFbxOptions->Constraints = pConstraints; }
	FBElementAction GetConstraints(  ) { return mFBFbxOptions->Constraints; }	
    void SetConstraintsAnimation( bool pConstraintsAnimation ) { mFBFbxOptions->ConstraintsAnimation = pConstraintsAnimation; }
    bool GetConstraintsAnimation(  ) { return mFBFbxOptions->ConstraintsAnimation; }

	void SetDevices( FBElementAction pDevices ) { mFBFbxOptions->Devices = pDevices; }
	FBElementAction GetDevices(  ) { return mFBFbxOptions->Devices; }
    void SetDevicesAnimation( bool pDevicesAnimation ) { mFBFbxOptions->DevicesAnimation = pDevicesAnimation; }
    bool GetDevicesAnimation(  ) { return mFBFbxOptions->DevicesAnimation; }

    void SetFileReferences( FBElementAction pFileReferences ) { mFBFbxOptions->FileReferences = pFileReferences; }
    FBElementAction GetFileReferences(  ) { return mFBFbxOptions->FileReferences; }

	void SetGroups( FBElementAction pGroups ) { mFBFbxOptions->Groups = pGroups; }
	FBElementAction GetGroups(  ) { return mFBFbxOptions->Groups; }

    void SetKeyingGroups( FBElementAction pGroups ) { mFBFbxOptions->KeyingGroups = pGroups; }
    FBElementAction GetKeyingGroups(  ) { return mFBFbxOptions->KeyingGroups; }

	void SetLights( FBElementAction pLights ) { mFBFbxOptions->Lights = pLights; }
	FBElementAction GetLights(  ) { return mFBFbxOptions->Lights; }
	void SetLightsAnimation( bool pLightsAnimation ) { mFBFbxOptions->LightsAnimation = pLightsAnimation; }
	bool GetLightsAnimation(  ) { return mFBFbxOptions->LightsAnimation; }

	void SetMaterials( FBElementAction pMaterials ) { mFBFbxOptions->Materials = pMaterials; }
	FBElementAction GetMaterials(  ) { return mFBFbxOptions->Materials; }
	void SetMaterialsAnimation( bool pMaterialsAnimation ) { mFBFbxOptions->MaterialsAnimation = pMaterialsAnimation; }
	bool GetMaterialsAnimation(  ) { return mFBFbxOptions->MaterialsAnimation; }

	void SetModels( FBElementAction pModels ) { mFBFbxOptions->Models = pModels; }
	FBElementAction GetModels(  ) { return mFBFbxOptions->Models; }
	void SetModelsAnimation( bool pModelsAnimation ) { mFBFbxOptions->ModelsAnimation = pModelsAnimation; }
	bool GetModelsAnimation(  ) { return mFBFbxOptions->ModelsAnimation; }

	void SetNotes( FBElementAction pNotes ) { mFBFbxOptions->Notes = pNotes; }
	FBElementAction GetNotes(  ) { return mFBFbxOptions->Notes; }
	void SetNotesAnimation( bool pNotesAnimation ) { mFBFbxOptions->NotesAnimation = pNotesAnimation; }
	bool GetNotesAnimation(  ) { return mFBFbxOptions->NotesAnimation; }

    void SetOpticalData( FBElementAction pOtical ) { mFBFbxOptions->OpticalData = pOtical; }
    FBElementAction GetOpticalData(  ) { return mFBFbxOptions->OpticalData; }	

    void SetPhysicalProperties( FBElementAction pProp ) { mFBFbxOptions->PhysicalProperties = pProp; }
    FBElementAction GetPhysicalProperties(  ) { return mFBFbxOptions->PhysicalProperties; }
    void SetPhysicalPropertiesAnimation( bool pPropAnim ) { mFBFbxOptions->PhysicalPropertiesAnimation = pPropAnim; }
    bool GetPhysicalPropertiesAnimation(  ) { return mFBFbxOptions->PhysicalPropertiesAnimation; }

	void SetPoses( FBElementAction pPoses ) { mFBFbxOptions->Poses = pPoses; }
	FBElementAction GetPoses(  ) { return mFBFbxOptions->Poses; }	

	void SetScripts( FBElementAction pScripts ) { mFBFbxOptions->Scripts = pScripts; }
	FBElementAction GetScripts(  ) { return mFBFbxOptions->Scripts; }
	
	void SetSets( FBElementAction pSets ) { mFBFbxOptions->Sets = pSets; }
	FBElementAction GetSets(  ) { return mFBFbxOptions->Sets; }

	void SetShaders( FBElementAction pShaders ) { mFBFbxOptions->Shaders = pShaders; }
	FBElementAction GetShaders(  ) { return mFBFbxOptions->Shaders; }
	void SetShadersAnimation( bool pShadersAnimation ) { mFBFbxOptions->ShadersAnimation = pShadersAnimation; }
	bool GetShadersAnimation(  ) { return mFBFbxOptions->ShadersAnimation; }

    void SetSolvers( FBElementAction pSolvers ) { mFBFbxOptions->Solvers = pSolvers; }
    FBElementAction GetSolvers(  ) { return mFBFbxOptions->Solvers; }
    void SetSolversAnimation( bool pSolversAnim ) { mFBFbxOptions->SolversAnimation = pSolversAnim; }
    bool GetSolversAnimation(  ) { return mFBFbxOptions->SolversAnimation; }
	
	void SetStory( FBElementAction pStory ) { mFBFbxOptions->Story = pStory; }
	FBElementAction GetStory(  ) { return mFBFbxOptions->Story; }
    void SetStoryAnimation( bool pStoryAnim ) { mFBFbxOptions->StoryAnimation = pStoryAnim; }
    bool GetStoryAnimation(  ) { return mFBFbxOptions->StoryAnimation; }

    void SetTextures( FBElementAction pTextures ) { mFBFbxOptions->Textures = pTextures; }
    FBElementAction GetTextures(  ) { return mFBFbxOptions->Textures; }	
    void SetTexturesAnimation( bool pTexturesAnimation ) { mFBFbxOptions->TexturesAnimation = pTexturesAnimation; }
    bool GetTexturesAnimation(  ) { return mFBFbxOptions->TexturesAnimation; }

    void SetVideo( FBElementAction pVideo ) { mFBFbxOptions->Video = pVideo; }
    FBElementAction GetVideo(  ) { return mFBFbxOptions->Video; }	
	
    void SetTransferMethod(FBCharacterLoadAnimationMethod pMethod) { mFBFbxOptions->TransferMethod = pMethod; }
    FBCharacterLoadAnimationMethod GetTransferMethod() const { return mFBFbxOptions->TransferMethod; }

    void SetProcessAnimationOnExtension(bool pProcessAnimationOnExtension) { mFBFbxOptions->ProcessAnimationOnExtension = pProcessAnimationOnExtension; }
    bool GetProcessAnimationOnExtension() const { return mFBFbxOptions->ProcessAnimationOnExtension; }

    void SetReplaceControlSet(bool pReplaceControlSet) { mFBFbxOptions->ReplaceControlSet = pReplaceControlSet; }
    bool GetReplaceControlSet() const { return mFBFbxOptions->ReplaceControlSet; }

    void SetResetDOF(bool pResetDOF) { mFBFbxOptions->ResetDOF = pResetDOF; }
    bool GetResetDOF() const { return mFBFbxOptions->ResetDOF; }

    void SetResetHierarchy(bool pResetHierarchy) { mFBFbxOptions->ResetHierarchy = pResetHierarchy; }
    bool GetResetHierarchy() const { return mFBFbxOptions->ResetHierarchy; }

    void SetRemoveConstraintReference(bool pRemoveConstraintReference) { mFBFbxOptions->RemoveConstraintReference = pRemoveConstraintReference; }
    bool GetRemoveConstraintReference() const { return mFBFbxOptions->RemoveConstraintReference; }

    void SetCopyCharacterExtensions(bool pCopyCharacterExtensions) { mFBFbxOptions->CopyCharacterExtensions = pCopyCharacterExtensions; }
    bool GetCopyCharacterExtensions() const { return mFBFbxOptions->CopyCharacterExtensions; }

    void SetRetargetOnBaseLayer(bool pRetargetOnBaseLayer) { mFBFbxOptions->RetargetOnBaseLayer = pRetargetOnBaseLayer; }
    bool GetRetargetOnBaseLayer() const { return mFBFbxOptions->RetargetOnBaseLayer; }

    void SetIgnoreConflicts(bool pIgnoreConflicts) { mFBFbxOptions->IgnoreConflicts = pIgnoreConflicts; }
    bool GetIgnoreConflicts() const { return mFBFbxOptions->IgnoreConflicts; }

    void SetSaveCharacter( bool pSaveCharacter ) { mFBFbxOptions->SaveCharacter = pSaveCharacter; }
    bool GetSaveCharacter(  ) { return mFBFbxOptions->SaveCharacter; }

    void SetSaveControlSet( bool pSaveControlSet ) { mFBFbxOptions->SaveControlSet = pSaveControlSet; }
    bool GetSaveControlSet(  ) { return mFBFbxOptions->SaveControlSet; }

    void SetSaveCharacterExtensions( bool pSaveCharacterExtensions ) { mFBFbxOptions->SaveCharacterExtensions = pSaveCharacterExtensions; }
    bool GetSaveCharacterExtensions(  ) { return mFBFbxOptions->SaveCharacterExtensions; }

    void SetClearSelectionBeforeSave( bool pClearSelectionBeforeSave ) { mFBFbxOptions->ClearSelectionBeforeSave = pClearSelectionBeforeSave; }
    bool GetClearSelectionBeforeSave(  ) { return mFBFbxOptions->ClearSelectionBeforeSave; }

    void SetShowFileDialog( bool pShowFileDialog ) { mFBFbxOptions->ShowFileDialog = pShowFileDialog; }
    bool GetShowFileDialog(  ) { return mFBFbxOptions->ShowFileDialog; }

    void SetShowOptionsDialog( bool pShowOptionsDialog ) { mFBFbxOptions->ShowOptionsDialog = pShowOptionsDialog; }
    bool GetShowOptionsDialog(  ) { return mFBFbxOptions->ShowOptionsDialog; }

	int GetTakeCount() const { return mFBFbxOptions->GetTakeCount(); }           

    bool GetTakeSelect(int pTakeIndex) const { return mFBFbxOptions->GetTakeSelect(pTakeIndex); }
    void SetTakeSelect(int pTakeIndex, bool pSelect) { mFBFbxOptions->SetTakeSelect(pTakeIndex, pSelect); }
   
    const char* GetTakeName(int pTakeIndex) const {return mFBFbxOptions->GetTakeName(pTakeIndex); }
    void SetTakeName(int pTakeIndex,  const char* pName) { mFBFbxOptions->SetTakeName(pTakeIndex, pName); }
   
    const char* GetTakeDescription(int pTakeIndex) const { return mFBFbxOptions->GetTakeDescription(pTakeIndex); }
    void SetTakeDescription(int pTakeIndex,  const char* pDescription) { return mFBFbxOptions->SetTakeDescription(pTakeIndex, pDescription); }
   
    const char* GetTakeDestinationName(int pTakeIndex) const { return mFBFbxOptions->GetTakeDestinationName(pTakeIndex); }
    void SetTakeDestinationName(int pTakeIndex,  const char* pDestinationName) { mFBFbxOptions->SetTakeDestinationName(pTakeIndex, pDestinationName); }

	FBTimeSpan_Wrapper* GetTakeKeyRange(int pTakeIndex) const { return FBTimeSpan_Wrapper_Factory(mFBFbxOptions->GetTakeKeyRange(pTakeIndex)); }
    void SetTakeKeyRange(int pTakeIndex,  FBTimeSpan_Wrapper &pKeyTimeSpan) { mFBFbxOptions->SetTakeKeyRange(pTakeIndex, *pKeyTimeSpan.mFBTimeSpan); }

	void SetObjectsToSave( list pObjectsToSave )
	{ 
		FBArrayTemplate<FBComponent *> lObjectsToSave;
		for ( int itr = 0; itr < len(pObjectsToSave); ++itr ) {
			object lObject = (pObjectsToSave)[itr];
			extract<FBComponent_Wrapper*> lExtractor(lObject);

			// Make sure this is a valid object, and that it is not a "None" object
			if ( lExtractor.check() && lExtractor() ) 
			{
				FBComponent *lComponent = lExtractor()->mFBComponent;
				if ( lComponent ) 
				{
					lObjectsToSave.Add( lComponent );
				}
			}
		}

		mFBFbxOptions->SetObjectsToSave( &lObjectsToSave );
	}

	void SetMultiLoadNamespaceList( const FBStringList_Wrapper& pMultiLoadNamespaceList )
	{
		mFBFbxOptions->SetMultiLoadNamespaceList( *pMultiLoadNamespaceList.mFBStringList );
	}

	FBStringList_Wrapper* GetMultiLoadNamespaceList()
	{
		return FBStringList_Wrapper_Factory( mFBFbxOptions->GetMultiLoadNamespaceList() );
	}

    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UpdateRecentFiles, bool);

	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(TransportSettings, bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(EmbedMedia, bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(CacheSize, int);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(UseASCIIFormat, bool);
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FileReference, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FileReferenceEdit, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(NamespaceList, const char* );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ConsiderMuteSolo, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(RemoveEmptyLayer, bool );
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FileFormatAndVersion, FBFileFormatAndVersion);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SaveSelectedModelsOnly, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(KeepTransformHierarchy, bool);
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SetPropertyStaticIfPossible, bool);

};
#endif // pyfbfbxoptions_h__