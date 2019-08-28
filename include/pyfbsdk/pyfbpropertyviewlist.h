#ifndef pyfbpropertyviewlist_h__
#define pyfbpropertyviewlist_h__
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

#include "pyfbpropertyviewdefinition.h"

// =======================================================================================
// FBPropertyViewList
// =======================================================================================
void FBPropertyViewList_Init();

class FBPropertyViewList_Wrapper;
PYSDK_DLL FBPropertyViewList_Wrapper* FBPropertyViewList_Wrapper_Factory( FBPropertyViewList* pPropertyViewList );

class PYSDK_DLL FBPropertyViewList_Wrapper {
public:
	FBPropertyViewList* mFBPropertyViewList;
public:
    FBPropertyViewList_Wrapper(FBPropertyViewList* pFBPropertyViewList) : mFBPropertyViewList( pFBPropertyViewList ) {}
	virtual ~FBPropertyViewList_Wrapper() { }

	bool IsEditable(){ return mFBPropertyViewList->IsEditable(); }

	FBPropertyViewDefinition_Wrapper* AddPropertyView(FBProperty_Wrapper& pProperty, const char* pHierarchy)
	{
		return FBPropertyViewDefinition_Wrapper_Factory(mFBPropertyViewList->AddPropertyView(pProperty.mFBProperty, pHierarchy));
	}

	bool RemovePropertyView(FBPropertyViewDefinition_Wrapper* pPropertyViewDefinition)
	{
			return pPropertyViewDefinition ? mFBPropertyViewList->RemovePropertyView(pPropertyViewDefinition->mFBPropertyViewDefinition) : false;
	}

	FBPropertyViewDefinition_Wrapper* FindPropertyView(const char* pPropertyName)
	{
		return FBPropertyViewDefinition_Wrapper_Factory(mFBPropertyViewList->FindPropertyView(pPropertyName));
	}
};

PYSDK_DLL inline FBPropertyViewList_Wrapper* FBPropertyViewList_Wrapper_Factory( FBPropertyViewList* pPropertyViewList )
{
	FBPropertyViewList_Wrapper* lPropertyViewList = 0;
	if( pPropertyViewList )
	{
		lPropertyViewList = new FBPropertyViewList_Wrapper( pPropertyViewList );
	}

	return lPropertyViewList;
}

#endif // pyfbpropertyviewlist_h__