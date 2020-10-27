#ifndef pyfbfcurveeditorutility_h__
#define pyfbfcurveeditorutility_h__
/**************************************************************************
 Copyright 2017 Autodesk, Inc.
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

#include "pyfbfcurveeditor.h"

// =======================================================================================
// FBFCurveEditorUtility
// =======================================================================================
void FBFCurveEditorUtility_Init();

class PYSDK_DLL FBFCurveEditorUtility_Wrapper : public FBComponent_Wrapper {
public:
	FBFCurveEditorUtility* mFBFCurveEditorUtility;
public:
	FBFCurveEditorUtility_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBFCurveEditorUtility = (FBFCurveEditorUtility*)pFBComponent; }
    FBFCurveEditorUtility_Wrapper() : FBComponent_Wrapper( &FBFCurveEditorUtility::TheOne()) { mFBFCurveEditorUtility = (FBFCurveEditorUtility*)mFBComponent; }
	virtual ~FBFCurveEditorUtility_Wrapper( ) {}
	bool Frame(bool pSelectedKeysOnly, FBFCurveEditor_Wrapper* pEditor = NULL) { return mFBFCurveEditorUtility->Frame(pSelectedKeysOnly, pEditor ? pEditor->mFBFCurveEditor : NULL); }
	bool SetTimeSpan(FBTimeSpan_Wrapper &pTimeSpan, FBFCurveEditor_Wrapper* pEditor = NULL) { return mFBFCurveEditorUtility->SetTimeSpan(*pTimeSpan.mFBTimeSpan, pEditor ? pEditor->mFBFCurveEditor : NULL); }
	FBTimeSpan_Wrapper* GetTimeSpan1(FBFCurveEditor_Wrapper* pEditor) 
	{ 
		FBTimeSpan lTS = mFBFCurveEditorUtility->GetTimeSpan(pEditor ? pEditor->mFBFCurveEditor : NULL);
		return FBTimeSpan_Wrapper_Factory(lTS);
	}
	FBTimeSpan_Wrapper* GetTimeSpan2()
	{
		return GetTimeSpan1( nullptr );
	}

	bool GetObjects(list pObjectList) 
	{ 
		//clear the list just in case
		int lCount = extract<int>(pObjectList.attr("__len__")());
		for(int i = 0; i < lCount; i++)
		{
			pObjectList.pop();
		}

		FBComponentList lComponentList;
		if(mFBFCurveEditorUtility->GetObjects(lComponentList))
		{
			for(int i = 0; i < lComponentList.GetCount(); i++)
			{
				pObjectList.append( FBWrapperFactory::TheOne().WrapFBObject( lComponentList.GetAt(i) ) );
			}
			return true;			
		}
		return false;
	}

	bool GetProperties(list pProperties, bool pSelectedOnly, FBFCurveEditor_Wrapper* pEditor = NULL) 
	{ 	
		//clear the list just in case
		int lCount = extract<int>(pProperties.attr("__len__")());
		for(int i = 0; i < lCount; i++)
		{
			pProperties.pop();
		}

        FBArrayTemplate<FBProperty *> lPropertiesArray;
		if(mFBFCurveEditorUtility->GetProperties(lPropertiesArray, pSelectedOnly, pEditor ? pEditor->mFBFCurveEditor : NULL))
		{
			for(int i = 0; i < lPropertiesArray.GetCount(); i++)
			{
				pProperties.append( FBWrapperFactory::TheOne().WrapFBObject( lPropertiesArray.GetAt(i) ) );
			}
			return true;	
		}
		return false;
	}

};
#endif // pyfbfcurveeditorutility_h__

