#ifndef pyfbstringlist_h__
#define pyfbstringlist_h__
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
// FBStringList
// =======================================================================================
void FBStringList_Init();

class FBStringList_Wrapper;
PYSDK_DLL FBStringList_Wrapper* FBStringList_Wrapper_Factory( FBStringList* pFBStringList );
class PYSDK_DLL FBStringList_Wrapper 
{
    int GetIndex( int pIndex )
    {
        if( pIndex < 0 ) 
        {
            pIndex += GetCount();
        }
        if( pIndex < 0 || pIndex >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return -1;
        }
        return pIndex;
    }
public:
	FBStringList* mFBStringList;
    bool mAllocated;
public:
    FBStringList_Wrapper( FBStringList* pFBStringList ) : mFBStringList( pFBStringList ), mAllocated( false ) {}
    FBStringList_Wrapper( const char* pString, const char pSeparator ) : mFBStringList( new FBStringList(pString, pSeparator) ), mAllocated( true ) {}
    FBStringList_Wrapper( const char* pString ) : mFBStringList( new FBStringList(pString, '~') ), mAllocated( true ) {}
    FBStringList_Wrapper( ) : mFBStringList( new FBStringList ), mAllocated( true ) {}
    virtual ~FBStringList_Wrapper();
	int Add(const char * S, kReference pRef = 0) { return mFBStringList->Add( S, pRef ); }
	void Clear() { mFBStringList->Clear(  ); }
	int Find(kReference pRef) { return mFBStringList->Find( pRef ); }
	int Find(const char *pString, bool pCaseSensitive = true, bool pStartWith = false) { return mFBStringList->Find( pString, pCaseSensitive, pStartWith ); }
	const char* GetAt(int pIndex) { return mFBStringList->GetAt( GetIndex( pIndex )); }
	int GetCount() { return mFBStringList->GetCount(  ); }
	kReference GetReferenceAt(int pIndex) { return mFBStringList->GetReferenceAt( GetIndex( pIndex )); }
	int IndexOf(const char * S) { return mFBStringList->IndexOf( S ); }
	void InsertAt(int pIndex, const char * S, kReference pRef = 0) { mFBStringList->InsertAt( GetIndex( pIndex ), S , pRef ); }
	int Remove(const char * S) { return mFBStringList->Remove( S ); }
	void RemoveAt(int pIndex) { mFBStringList->RemoveAt( GetIndex( pIndex )); }
	bool SetAt(int pIndex, const char * pString) { return mFBStringList->SetAt( GetIndex( pIndex ), pString ); }
	void SetReferenceAt(int pIndex, kReference pRef) { mFBStringList->SetReferenceAt( GetIndex( pIndex ), pRef ); }
	void Sort() { mFBStringList->Sort(  ); }
    const char* AsString(const char pSeparator = '~') const;
    bool SetString(const char* pString, const char pSeparator = '~');
};

PYSDK_DLL inline FBStringList_Wrapper* FBStringList_Wrapper_Factory( FBStringList* pFBStringList )
{
	return new FBStringList_Wrapper( pFBStringList );
}

PYSDK_DLL inline FBStringList_Wrapper* FBStringList_Wrapper_Factory( const FBStringList& pFBStringList )
{
     FBStringList_Wrapper* lStrList = new FBStringList_Wrapper();
     lStrList->mFBStringList->SetString(pFBStringList.AsString());
     return lStrList;
}

#endif // pyfbstringlist_h__
