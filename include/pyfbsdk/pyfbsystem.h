#ifndef pyfbsystem_h__
#define pyfbsystem_h__
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

#include "pyfbtake.h"

// =======================================================================================
// FBSystem
// =======================================================================================
void FBSystem_Init();

class PYSDK_DLL FBSystem_Wrapper : public FBComponent_Wrapper {
public:
	FBSystem* mFBSystem;
public:
	FBSystem_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBSystem = (FBSystem*)pFBComponent; }
	FBSystem_Wrapper(  ) : FBComponent_Wrapper( &FBSystem::TheOne() ) { mFBSystem = (FBSystem*)mFBComponent; }
	virtual ~FBSystem_Wrapper( ) { }
    object OnUIIdle(  );
    object OnVideoFrameRendering();
    object OnConnectionNotify(  );	
    object OnConnectionDataNotify(  );
    object OnConnectionStateNotify(  );
	object OnConnectionKeyingNotify(  );
	const char* GetApplicationPath(  ) { return mFBSystem->ApplicationPath; }
    FBStringList_Wrapper* GetCommandLineArgs() { return FBStringList_Wrapper_Factory( mFBSystem->GetCommandLineArgs() ); }
    FBStringList_Wrapper* GetPythonStartupPath() { return FBStringList_Wrapper_Factory( mFBSystem->GetPythonStartupPath() ); }
    FBStringList_Wrapper* GetPluginPath() { return FBStringList_Wrapper_Factory( mFBSystem->GetPluginPath() ); }
	FBStringList_Wrapper* GetLoadedPluginItemsName() { return FBStringList_Wrapper_Factory( mFBSystem->GetLoadedPluginItemsName() ); }
	FBStringList_Wrapper* GetLoadedPluginItemInfo( const char* pPluginItemName ) { return FBStringList_Wrapper_Factory( mFBSystem->GetLoadedPluginItemInfo( pPluginItemName ) ); }
	FBStringList_Wrapper* GetLoadedPluginItemGroups( const char* pPluginItemName ) { return FBStringList_Wrapper_Factory( mFBSystem->GetLoadedPluginItemGroups( pPluginItemName ) ); }
#if !defined(K_NO_ASSETMNG)
	object GetAssetManager(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBSystem->AssetManager ); }
#endif
	object GetAudioInputs(  ) { return FBPropertyListAudioIn_Wrapper_Factory( mFBSystem->AudioInputs ); }
	object GetAudioOutputs(  ) { return FBPropertyListAudioOut_Wrapper_Factory( mFBSystem->AudioOutputs ); }
    object GetCameras(  );
    object GetMaterials(  );	
    object GetShaders(  );
    object GetTextures(  );
    object GetTakes(  );
    object GetLights(  );
    object GetDevices(  );
	const char* GetComputerName(  ) { return mFBSystem->ComputerName; }
    const char* GetBuildId(  ) { return mFBSystem->BuildId; }
	const char* GetBuildVersion(  ) { return mFBSystem->BuildVersion; }
	void SetCurrentTake( FBTake_Wrapper& pCurrentTake ) { mFBSystem->CurrentTake = pCurrentTake.mFBTake; }
	object GetCurrentTake(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBSystem->CurrentTake ); }
	FBVector2d_Wrapper* GetDesktopSize(  ) { return FBVector2d_Wrapper_Factory( mFBSystem->DesktopSize ); }	
	double GetFrameRate(  ) { return mFBSystem->FrameRate; }
	double GetProcessMemory() { return mFBSystem->ProcessMemory; }
	double GetProcessMemoryPeak() { return mFBSystem->ProcessMemoryPeak; }
    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(FullScreenViewer,   bool);
	FBTime_Wrapper* GetLocalTime(  ) { return FBTime_Wrapper_Factory( mFBSystem->LocalTime ); }
	const char* GetPathImages(  ) { return mFBSystem->PathImages; }
	const char* GetPathMeshs(  ) { return mFBSystem->PathMeshs; }
	object GetRenderer(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBSystem->Renderer ); }
	object GetRootModel(  ) { return FBModel_Wrapper_Factory( mFBSystem->RootModel ); }
	object GetScene(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBSystem->Scene ); }
	object GetSceneRootModel(  ) { return FBModel_Wrapper_Factory( mFBSystem->SceneRootModel ); }
	FBTime_Wrapper* GetSystemTime(  ) { return FBTime_Wrapper_Factory( mFBSystem->SystemTime ); }
	object GetVideoInputs(  ) { return FBPropertyListVideoIn_Wrapper_Factory( mFBSystem->VideoInputs ); }
	object GetVideoOutputs(  ) { return FBPropertyListVideoOut_Wrapper_Factory( mFBSystem->VideoOutputs ); }
	double GetVersion(  ) { return mFBSystem->Version; }
	const char* GetConfigPath( ) { return mFBSystem->ConfigPath; }
	const char* GetUserConfigPath ( ) { return mFBSystem->UserConfigPath; }
    const char* CurrentDirectory() { static FBString lValue = mFBSystem->CurrentDirectory(); return (char*)lValue; }
    const char* MakeFullPath(const char* pRelativeFilePath) { static FBString lValue = mFBSystem->MakeFullPath(pRelativeFilePath); return (char*)lValue; }
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(SuspendMessageBoxes,   bool);

#if !defined(K_NO_MANIPULATOR)
	DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY( Manipulators, FBPropertyListManipulator )
#endif

protected:
    FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbsystem_h__