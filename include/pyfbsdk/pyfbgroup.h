#ifndef pyfbgroup_h__
#define pyfbgroup_h__
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
// FBGroup
// =======================================================================================
void FBGroup_Init();

class PYSDK_DLL FBGroup_Wrapper : public FBBox_Wrapper {
public:
	FBGroup* mFBGroup;
public:
	FBGroup_Wrapper( FBComponent* pFBComponent ) : FBBox_Wrapper( pFBComponent ) { mFBGroup = (FBGroup*)pFBComponent; }
	FBGroup_Wrapper( const char* pName ) : FBBox_Wrapper( new FBGroup( pName )) { mFBGroup = (FBGroup*)mFBComponent; }
	virtual ~FBGroup_Wrapper( ) {}
	void FBDelete() { mFBGroup->FBDelete(  ); }
    object Clone() { return FBWrapperFactory::TheOne().WrapFBObject( mFBGroup->Clone() ); }
	void Select(bool pSelect) { mFBGroup->Select( pSelect ); }
	object GetItems(  ) { return WrapFBObject<FBPropertyListComponent_Wrapper,FBPropertyListComponent>( &mFBGroup->Items ); }
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBGroup, Pickable, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBGroup, Show, bool);
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(FBGroup, Transformable, bool);
    bool Contains( FBComponent_Wrapper& pObject ) { return mFBGroup->Contains( pObject.mFBComponent ); }
};
#endif // pyfbgroup_h__
