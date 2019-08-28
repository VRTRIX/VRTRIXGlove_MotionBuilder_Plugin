#ifndef pyfbfilereference_h__
#define pyfbfilereference_h__
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

#include "pyfbarraytemplate.h"
#include "pyfbnamespace.h"
#include "pyfbstringlist.h"

// =======================================================================================
// FBFileReference
// =======================================================================================
void FBFileReference_Init();

class PYSDK_DLL FBFileReference_Wrapper : public FBNamespace_Wrapper {
public:
	FBFileReference* mFBFileReference;
public:
	FBFileReference_Wrapper( FBComponent* pFBComponent ) : FBNamespace_Wrapper( pFBComponent )    { mFBFileReference = (FBFileReference*)pFBComponent; }
	FBFileReference_Wrapper( const char* pName, FBNamespace_Wrapper* pParentNS ) : FBNamespace_Wrapper( new FBFileReference( pName, pParentNS ? pParentNS->mFBNamespace : NULL))   { mFBFileReference = (FBFileReference*)mFBComponent; }
	virtual ~FBFileReference_Wrapper() {}
	void    FBDelete() { mFBFileReference->FBDelete(); }
    bool    BakeRefEditToFile(const char* pFilePath) { return mFBFileReference->BakeRefEditToFile(pFilePath); }
    void    RevertRefEdit(FBPlug_Wrapper* pPlug = NULL, FBPlugModificationFlag pModificationFlag = kFBAllModifiedMask) { mFBFileReference->RevertRefEdit( pPlug ? pPlug->mFBPlug : NULL, pModificationFlag); }
    void    ApplyRefEditPyScriptFromFile( const char* pRefEditPyScriptFilePath ) { return mFBFileReference->ApplyRefEditPyScriptFromFile( pRefEditPyScriptFilePath ); }
    void    ApplyRefEditPyScriptFromString( const char* pRefEditPyScript ) { return mFBFileReference->ApplyRefEditPyScriptFromString( pRefEditPyScript ); }
    bool    DuplicateFileRef(FBStringList_Wrapper& pDstNameSpaceList, bool pWithRefEdit = false) { return mFBFileReference->DuplicateFileRef( *(pDstNameSpaceList.mFBStringList), pWithRefEdit);}
    const char*  GetRefEdit( const char* pFilePath = NULL) { return mFBFileReference->GetRefEdit(pFilePath); }
    bool ClearRefEdit(const char* pFilePath) { return mFBFileReference->ClearRefEdit(pFilePath); }
    bool ClearAllRefEdit() { return mFBFileReference->ClearAllRefEdit(); }
    bool SwapReferenceFilePath(const char* pFilePath, bool pApplyAvailableRefEdit = true, bool pMergeCurrentRefEdit = true) { return mFBFileReference->SwapReferenceFilePath(pFilePath, pApplyAvailableRefEdit, pMergeCurrentRefEdit); }
    void GetRefFileList(FBStringList_Wrapper& pRefFileList) const { mFBFileReference->GetRefFileList(*(pRefFileList.mFBStringList)); }


    DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(ReferenceFilePath,	const char*)
	DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(IsLoaded,			bool)
};

#endif // pyfbset_h__