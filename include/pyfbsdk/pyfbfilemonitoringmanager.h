#ifndef pyfbfilemonitoringmanager_h__
#define pyfbfilemonitoringmanager_h__
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
    *    Be sure that PYSDK_DLL is defined only once...
    */
    #define PYSDK_DLL K_DLLIMPORT
#endif

// =======================================================================================
// FBFileMonitoringManager
// =======================================================================================
void FBFileMonitoringManager_Init();

class PYSDK_DLL FBFileMonitoringManager_Wrapper : public FBComponent_Wrapper {
public:
    FBFileMonitoringManager* mFBFileMonitoringManager;
public:
    FBFileMonitoringManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBFileMonitoringManager = (FBFileMonitoringManager*)pFBComponent; }
    FBFileMonitoringManager_Wrapper(  ) : FBComponent_Wrapper( &FBFileMonitoringManager::TheOne() ) { mFBFileMonitoringManager = (FBFileMonitoringManager*)mFBComponent; }
    virtual ~FBFileMonitoringManager_Wrapper( ) { }


    void AddFileToMonitor(const char* pFilePath, FBFileMonitoringType pFileMonitoringType ){ mFBFileMonitoringManager->AddFileToMonitor(FBString(pFilePath),  pFileMonitoringType ); }
    void RemoveFileFromMonitor(const char* pFilePath){ mFBFileMonitoringManager->RemoveFileFromMonitor(FBString(pFilePath)); }

    void PauseFileMonitoring(bool pPause = true){ mFBFileMonitoringManager->PauseFileMonitoring(pPause); }
    void CleanFileMonitoring(bool pIncludePythonEditorScripts = true){ mFBFileMonitoringManager->CleanFileMonitoring(pIncludePythonEditorScripts); }

    object OnFileChangeMainScene();
    object OnFileChangeAnimationClip();
    object OnFileChangeFileReference();
    object OnFileChangePythonEditorScript();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbfilemonitoringmanager_h__