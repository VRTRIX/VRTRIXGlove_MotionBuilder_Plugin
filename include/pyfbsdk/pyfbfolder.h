#ifndef pyfbfolder_h__
#define pyfbfolder_h__
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
// FBFolder
// =======================================================================================
void FBFolder_Init();

class PYSDK_DLL FBFolder_Wrapper : public FBComponent_Wrapper {
public:
	FBFolder* mFBFolder;
public:
	FBFolder_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBFolder = (FBFolder*)pFBComponent; }
	FBFolder_Wrapper( const char* pName, FBComponent_Wrapper& pComponent ) : FBComponent_Wrapper( new FBFolder( pName,pComponent.mFBComponent )) { mFBFolder = (FBFolder*)mFBComponent; }
	virtual ~FBFolder_Wrapper( ) {}
	void FBDelete() { mFBFolder->FBDelete(  ); }
	object GetItems(  ) { return WrapFBObject<FBPropertyListComponent_Wrapper,FBPropertyListComponent>( &mFBFolder->Items ); }
};
#endif // pyfbfolder_h__
