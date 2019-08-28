#ifndef pyfbset_h__
#define pyfbset_h__
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
// FBSet
// =======================================================================================
void FBSet_Init();

class PYSDK_DLL FBSet_Wrapper : public FBBox_Wrapper {
public:
	FBSet* mFBSet;
public:
	FBSet_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBSet = (FBSet*)pFBComponent; }
	FBSet_Wrapper( const char* pName ) : FBBox_Wrapper( new FBSet( pName )) { mFBSet = (FBSet*)mFBComponent; }
	virtual ~FBSet_Wrapper( ) {}
	void FBDelete() { mFBSet->FBDelete(  ); }
	void Select(bool pSelect) { mFBSet->Select( pSelect ); }
	int Contains( FBComponent_Wrapper& pObject ) { return mFBSet->Contains( pObject.mFBComponent ); }
	object GetItems(  ) { return WrapFBObject<FBPropertyListComponent_Wrapper,FBPropertyListComponent>( &mFBSet->Items ); }
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBSet, Pickable, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBSet, Transformable, bool);
	void SetVisibility( bool pVisibility ) { mFBSet->Visibility = pVisibility; }
	object GetVisibility(  ) { return WrapFBObject<FBPropertyAnimatableBool_Wrapper,FBPropertyAnimatableBool>( &mFBSet->Visibility ); }
};
#endif // pyfbset_h__