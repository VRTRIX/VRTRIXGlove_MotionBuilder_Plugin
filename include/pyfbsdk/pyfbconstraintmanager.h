#ifndef pyfbconstraintmanager_h__
#define pyfbconstraintmanager_h__
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
// FBConstraintManager
// =======================================================================================
void FBConstraintManager_Init();

class PYSDK_DLL FBConstraintManager_Wrapper : public FBComponent_Wrapper {
public:
	FBConstraintManager* mFBConstraintManager;
public:
	FBConstraintManager_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBConstraintManager = (FBConstraintManager*)pFBComponent; }
	FBConstraintManager_Wrapper() : FBComponent_Wrapper( &FBConstraintManager::TheOne() ) { mFBConstraintManager = (FBConstraintManager*)mFBComponent; }
    virtual ~FBConstraintManager_Wrapper( ) {}

	object TypeCreateConstraintByIndex(int pTypeIndex) { return FBConstraint_Wrapper_Factory( mFBConstraintManager->TypeCreateConstraint( pTypeIndex )); }
    object TypeCreateConstraintByName(const char* pName) { return FBConstraint_Wrapper_Factory( mFBConstraintManager->TypeCreateConstraint( pName )); }
	
    int TypeGetCount() { return mFBConstraintManager->TypeGetCount(  ); }
	const char * TypeGetName(int pTypeIndex) 
    { 
        ValidateIndexAccess( pTypeIndex, this, &FBConstraintManager_Wrapper::TypeGetCount );
        return mFBConstraintManager->TypeGetName( pTypeIndex ); 
    }
};
#endif // pyfbconstraintmanager_h__

