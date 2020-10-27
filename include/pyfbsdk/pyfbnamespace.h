#ifndef pyfbnamespace_h__
#define pyfbnamespace_h__
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
#include "pyfbstringlist.h"

// =======================================================================================
// FBNamespace
// =======================================================================================
void FBNamespace_Init();

class PYSDK_DLL FBNamespace_Wrapper : public FBComponent_Wrapper {
public:
    FBNamespace* mFBNamespace;
public:
    FBNamespace_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent )    { mFBNamespace = (FBNamespace*)pFBComponent; }
    FBNamespace_Wrapper( const char* pName, FBNamespace_Wrapper* pParentNS) : FBComponent_Wrapper( new FBNamespace( pName, pParentNS ? pParentNS->mFBNamespace : NULL))   { mFBNamespace = (FBNamespace*)mFBComponent; }
    virtual ~FBNamespace_Wrapper() {}
    void   FBDelete() { mFBNamespace->FBDelete(); }
    object GetChildrenNamespaces()	{ return FBPropertyListNamespace_Wrapper_Factory( mFBNamespace->ChildrenNamespaces ); }
    int    GetContentCount() { return mFBNamespace->GetContentCount(); } 
    object GetContent(int pIndex) { return FBWrapperFactory::TheOne().WrapFBObject(mFBNamespace->GetContent(pIndex)); }
    void   GetContentList(FBComponentList_Wrapper& pContentList, FBPlugModificationFlag pModificationFlags = kFBPlugAllContent, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false) { mFBNamespace->GetContentList( *(pContentList.mFBObjectList), pModificationFlags, pRecursive, pTypeInfo, pExactTypeMatch); }
	bool   IsContentLocked() { return mFBNamespace->ContentLocked; }
	void   SetContentLocked( bool pLockState ) { mFBNamespace->ContentLocked = pLockState; }
};

#endif // pyfbset_h__