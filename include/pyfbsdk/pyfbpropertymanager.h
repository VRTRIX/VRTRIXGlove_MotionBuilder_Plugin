#ifndef pyfbpropertymanager_h__
#define pyfbpropertymanager
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
// FBPropertyManager
// =======================================================================================
void FBPropertyManager_Init();

class FBPropertyManager_Wrapper;
PYSDK_DLL FBPropertyManager_Wrapper* FBPropertyManager_Wrapper_Factory( FBPropertyManager* pFBPropertyManager );
class PYSDK_DLL FBPropertyManager_Wrapper {
public:
	FBPropertyManager* mFBPropertyManager;
public:
	FBPropertyManager_Wrapper( FBPropertyManager* pFBPropertyManager );	
	virtual ~FBPropertyManager_Wrapper( );
	object Find(const char * pPropertyName, bool pInternalSearch = true)
    {
        object lResult;
        FBProperty* lProperty = mFBPropertyManager->Find( pPropertyName, pInternalSearch );
        if( lProperty ) {
            lResult = FBProperty_Wrapper_Factory( *lProperty );
        }
        return lResult;
    }

	void FindPropertiesByName(const char * pPropertyNamePattern, list pPropList, bool pMultilangLookup = true)
    {
		FBArrayTemplate<FBProperty *> lPropList;
        mFBPropertyManager->FindPropertiesByName( pPropertyNamePattern, lPropList, pMultilangLookup );

		for(int i = 0; i < lPropList.GetCount(); i++)
        {
            pPropList.append(FBProperty_Wrapper_Factory(lPropList[i]));
        }
    }

	int GetCount() { return mFBPropertyManager->GetCount(  ); }

	object GetFBProperty( int pIndex ) {
        if( pIndex < 0 ) {
            pIndex += GetCount();
        }
        if( pIndex < 0 || pIndex >= GetCount()) {
            PyErr_SetString( PyExc_IndexError, "list index out of range" );
            throw_error_already_set();
			return object();
        }
        return FBProperty_Wrapper_Factory( *mFBPropertyManager->operator[]( pIndex ));
    }
};

PYSDK_DLL inline FBPropertyManager_Wrapper* FBPropertyManager_Wrapper_Factory( FBPropertyManager* pFBPropertyManager )
{
	return new FBPropertyManager_Wrapper( pFBPropertyManager );
}
#endif // pyfbpropertymanager_h__