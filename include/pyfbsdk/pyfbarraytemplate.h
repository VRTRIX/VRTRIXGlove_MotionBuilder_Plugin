#ifndef pyfbarraytemplate_h__
#define pyfbarraytemplate_h__
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

#include "pyfbmatrix.h"
#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"

// Wrapper Initializer.
void FBArrayTemplate_Init();

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBObjectList (FBArrayTemplate<FBComponent*>)
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class PYSDK_DLL FBComponentList_Wrapper {

public:
    // FBArrayTemplate<FBComponent*>* mFBObjectList;
    FBComponentList* mFBObjectList;
    
    FBComponentList_Wrapper() : mFBObjectList( FBCreateComponentList() )
    {
    }

    // DTOR
    ~FBComponentList_Wrapper()
    {
        FBDestroyComponentList( mFBObjectList );
    }

    int GetCount()
    {
        return mFBObjectList->GetCount();
    }

    object GetObject( int lIdx )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
            return object();
        }
        return FBWrapperFactory::TheOne().WrapFBObject( mFBObjectList->operator[]( lIdx ) );
    }

    void Add( FBComponent_Wrapper* pComponent )
    {
        if( pComponent && pComponent->mFBComponent )
        {
            mFBObjectList->Add( pComponent->mFBComponent );
        }
    }

    void Clear()
    {
        mFBObjectList->Clear();
    }
};


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBModelList (FBArrayTemplate<FBModel*>)
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class FBModel_Wrapper;
class PYSDK_DLL FBModelList_Wrapper {

public:
    FBModelList* mFBModelList;

    // CTOR
    FBModelList_Wrapper() : mFBModelList( FBCreateModelList() )
    {
    };
    // DTOR
    ~FBModelList_Wrapper()
    {
        FBDestroyModelList( mFBModelList );
    };

    int GetCount()
    {
        return mFBModelList->GetCount();
    };

    object GetModel( int lIdx )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return object();
        }
        return FBModel_Wrapper_Factory( mFBModelList->operator[]( lIdx ) );
    };

	void Add( FBModel_Wrapper* pModel )
	{
		if( pModel && pModel->mFBModel )
		{
			mFBModelList->Add( pModel->mFBModel );
		}
	};

	void Clear()
	{
		mFBModelList->Clear();
	};
};


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPickInfosList (FBArrayTemplate<FBPickInfos*>)
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class PYSDK_DLL FBPickInfosList_Wrapper {

public:
    FBPickInfosList* mFBPickInfosList;

    // CTOR
    FBPickInfosList_Wrapper() : mFBPickInfosList( FBCreatePickInfosList() )
    {
    };
    // DTOR
    ~FBPickInfosList_Wrapper()
    {
        FBDestroyPickInfosList( mFBPickInfosList );
    };

    int GetCount()
    {
        return mFBPickInfosList->GetCount();
    };

    object GetPickedModel(int lIdx)
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }

        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return object();
        }
        FBPickInfos lPickInfos = mFBPickInfosList->operator[]( lIdx );
        return FBWrapperFactory::TheOne().WrapFBObject( lPickInfos.mModel );
    }

    tuple GetPickInfos( int lIdx )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return tuple();
        }
        FBPickInfos lPickInfos = mFBPickInfosList->operator[]( lIdx );
        return make_tuple( FBModel_Wrapper_Factory( lPickInfos.mModel ), FBVector3d_Wrapper_Factory( lPickInfos.mPoint ), FBVector3d_Wrapper_Factory( lPickInfos.mNormal ), lPickInfos.mSubItemIndex);
    };
};
#endif // pyfbarraytemplate_h__