#ifndef pyfbpropertyviewdefinition_h__
#define pyfbpropertyviewdefinition_h__
/**************************************************************************
 Copyright 2012 Autodesk, Inc.
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
// FBPropertyViewDefinition
// =======================================================================================
void FBPropertyViewDefinition_Init();

class FBPropertyViewDefinition_Wrapper;
PYSDK_DLL FBPropertyViewDefinition_Wrapper* FBPropertyViewDefinition_Wrapper_Factory( FBPropertyViewDefinition* pPropertyViewDefinition );

class PYSDK_DLL FBPropertyViewDefinition_Wrapper {
public:
	FBPropertyViewDefinition* mFBPropertyViewDefinition;
public:
    FBPropertyViewDefinition_Wrapper(FBPropertyViewDefinition* pPropertyViewDefinition) : mFBPropertyViewDefinition( pPropertyViewDefinition ) {}
	virtual ~FBPropertyViewDefinition_Wrapper() { }

	bool IsOpen(){ return mFBPropertyViewDefinition->IsOpen(); }
	bool IsSaved(){ return mFBPropertyViewDefinition->IsSaved(); }
	bool IsFolder(){ return mFBPropertyViewDefinition->IsFolder(); }
	void SetOpen(bool pTrue, bool pApplyUpHierarchy){ mFBPropertyViewDefinition->SetOpen(pTrue, pApplyUpHierarchy); }
	void SetSaved(bool pTrue, bool pApplyUpHierarchy){ mFBPropertyViewDefinition->SetSaved(pTrue, pApplyUpHierarchy); }
};

PYSDK_DLL inline FBPropertyViewDefinition_Wrapper* FBPropertyViewDefinition_Wrapper_Factory( FBPropertyViewDefinition* pPropertyViewDefinition )
{
	FBPropertyViewDefinition_Wrapper* lPropertyViewDefinition = 0;
	if( pPropertyViewDefinition )
	{
		lPropertyViewDefinition = new FBPropertyViewDefinition_Wrapper( pPropertyViewDefinition );
	}

	return lPropertyViewDefinition;
}

#endif // pyfbpropertyviewdefinition_h__