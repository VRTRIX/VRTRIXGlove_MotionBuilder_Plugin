#ifndef pyfbpropertylist_h__
#define pyfbpropertylist_h__
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

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListComponent
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListComponent_Init();
class FBComponent_Wrapper;

class PYSDK_DLL FBPropertyListBase_Wrapper {

public:

    long GetCount();                                               // __len__
    object GetItem( object pKey );					               // __getitem__
    void SetItem( object pKey, object pObject );	               // __setitem__
    void RemoveAtIndex( long lIdx );                               // __delitem__
    bool Contains( object pObject );                               // __contains__

    void Append( object pObject );                                 // append(), pObject should be unique object, no duplication allowed.
    void Extend( object pListObject );                             // extend()
    long Count( object pObject );                                  // count()
    long Index1( object pObject);                                  // index() 1 arg
    long Index2( object pObject, long pStart );                    // index() 2 args
    long Index3( object pObject, long pStart, long pStop );        // index() 3 args
    void Insert( long pIndex, object pObject );                    // insert()
    object Pop0();                                                 // pop() 0 arg
    object Pop1( object pIdx );                                    // pop() 1 arg
    void Remove( object pObject );                                 // remove()
    void RemoveAll();                                              // removeAll()
    void Reverse();                                                // reverse()
    void Sort0();                                                  // sort() 0 arg
    void Sort1( object pSortFnc );                                 // sort() 1 arg
    void Sort2( object pSortFnc, object pKeyFnc );                 // sort() 2 args
    void Sort3( object pSortFnc, object pKeyFnc, bool pReverse );  // sort() 3 args
    object GetAt(int lIdx);

protected:

    // CTOR
    FBPropertyListBase_Wrapper() = default;
    
    // DTOR
    virtual ~FBPropertyListBase_Wrapper() = default;
    virtual object GetAtSelf( int lIdx ) = 0;
    virtual int GetCountSelf() = 0;
    virtual void AppendSelf( object pObject ) = 0;
    virtual void RemoveSelf( object pItem ) = 0;
    virtual void RemoveAllSelf() = 0;
    virtual void RemoveAtSelf( int lIdx ) = 0;
    virtual int FindSelf( object pObject ) = 0;
};


class PYSDK_DLL FBPropertyListComponent_Wrapper : public FBProperty_Wrapper, public FBPropertyListBase_Wrapper
{

public:

    FBPropertyListComponentBase* mFBPropertyListComponent;

    // CTOR
    FBPropertyListComponent_Wrapper( FBPropertyListComponentBase* pFBPropertyListComponent ) 
        : FBProperty_Wrapper( pFBPropertyListComponent )
        , mFBPropertyListComponent( pFBPropertyListComponent )
    {
    };
    // DTOR
    ~FBPropertyListComponent_Wrapper()
    {
    };

protected:


    virtual object GetAtSelf( int lIdx );
    virtual int GetCountSelf();
    virtual void AppendSelf( object pObject );
    virtual void RemoveSelf( object pItem );
    virtual void RemoveAllSelf();
    virtual void RemoveAtSelf( int lIdx );
    virtual int FindSelf( object pObject );

private:

    FBComponent* GetComponent( object pObject );
};

// PropertyList Macro Wrapper

#define DefinePropertyListBase( ObjectName,ItemName ) \
	void FBPropertyList##ObjectName##_Init(); \
	class FB##ItemName##_Wrapper; \
	PYSDK_DLL object FB##ItemName##_Wrapper_Factory( FB##ItemName* ); \
	class PYSDK_DLL FBPropertyList##ObjectName##_Wrapper : public FBPropertyListComponent_Wrapper { \
	public: \
		FBPropertyList##ObjectName##_Wrapper( FBPropertyListComponentBase* pFBPropertyListComponent ) : FBPropertyListComponent_Wrapper( pFBPropertyListComponent ) {} \
	    ~FBPropertyList##ObjectName##_Wrapper() { } \
	};\
	PYSDK_DLL inline object FBPropertyList##ObjectName##_Wrapper_Factory( FBPropertyList##ObjectName& pFBPropertyList##ObjectName) \
	{ \
    return WrapFBObject<FBPropertyList##ObjectName##_Wrapper, FBPropertyList##ObjectName>( &pFBPropertyList##ObjectName );\
	}
    


#define DefinePropertyList( ObjectName ) DefinePropertyListBase( ObjectName,ObjectName )



#define ImplementPropertyList( ClassName ) \
    void FBPropertyList##ClassName##_Init() \
{ \
    class_<FBPropertyList##ClassName##_Wrapper, bases<FBPropertyListComponent_Wrapper> >("FBPropertyList"#ClassName,no_init) \
    ;\
    REGISTER_FBWRAPPER_ONLY( FBPropertyList##ClassName );\
}



DefinePropertyList( Actor );
DefinePropertyList( ActorFace );
DefinePropertyList( AudioClip );
DefinePropertyList( AudioIn );
DefinePropertyList( AudioOut );
DefinePropertyList( Camera );
DefinePropertyList( ControlSet );
DefinePropertyList( Character );
DefinePropertyList( CharacterExtension );
DefinePropertyList( CharacterFace );
DefinePropertyList( CharacterPose );
#if !defined(K_NO_DECK)
	DefinePropertyList( Deck );
#endif
DefinePropertyList( Device );
DefinePropertyList( Folder );
DefinePropertyList( Group );
#if !defined(K_NO_MANIPULATOR)
	DefinePropertyList( Handle );
#endif
#if !defined(K_NO_HUD)
    DefinePropertyList( HUDElement );
	DefinePropertyList( HUD );
#endif
DefinePropertyList( Light );
DefinePropertyList( MarkerSet );
DefinePropertyList( CharacterMarkerSet );
DefinePropertyList( Material );
DefinePropertyList( Model );
DefinePropertyList( MotionClip );
#if !defined(K_NO_NOTE)
	DefinePropertyList( Note );
#endif
DefinePropertyList( ObjectPose );
DefinePropertyList( PhysicalProperties );
DefinePropertyList( Pose );
DefinePropertyList( Set );
DefinePropertyList( Namespace );
DefinePropertyList( FileReference );
DefinePropertyList( Shader );
DefinePropertyList( ConstraintSolver );
DefinePropertyList( StoryFolder );
DefinePropertyList( StoryTrack );
DefinePropertyList( StoryClip );
DefinePropertyListBase( StoryDetails,Component );
DefinePropertyListBase( StorySubTrack,StoryTrack );
DefinePropertyListBase( Pivot,Model );
DefinePropertyList( Take );
DefinePropertyList( Texture );
DefinePropertyList( Deformer );
#ifndef FB_KERNEL 
	DefinePropertyList( UserObject );
#endif
DefinePropertyList( VideoClip );
DefinePropertyList( VideoIn );
DefinePropertyList( VideoOut );
DefinePropertyList( Constraint );
DefinePropertyList( Box );
DefinePropertyList( KeyingGroup );
DefinePropertyList( ModelSkeleton );
DefinePropertyList( ModelOptical );

//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyStringList
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyStringList_Wrapper : public FBProperty_Wrapper, public FBPropertyListBase_Wrapper
{
public:
	FBPropertyStringList* mFBPropertyString;
	FBPropertyStringList_Wrapper( FBPropertyStringList* pFBPropertyString );
	virtual ~FBPropertyStringList_Wrapper( );

    kReference GetReferenceAt( int lIdx );
    void SetReferenceAt( int lIdx, kReference );
    int FindFromReference( kReference );
private:

    const char* GetString( object pObject );
        
    virtual object GetAtSelf( int lIdx );
    virtual int GetCountSelf();
    virtual void AppendSelf( object pObject );
    virtual void RemoveSelf( object pItem );
    virtual void RemoveAtSelf( int lIdx );
    virtual void RemoveAllSelf();
    virtual int FindSelf( object pObject );
};

PYSDK_DLL object FBPropertyStringList_Wrapper_Factory( FBPropertyStringList& pFBPropertyString );
void FBPropertyStringList_Init();

//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyList_Wrapper
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyList_Wrapper : public FBPropertyListBase_Wrapper
{
public:
    FBArrayTemplate<FBProperty*>* mFBPropertyArray;

    FBPropertyList_Wrapper( FBArrayTemplate<FBProperty*>* pFBArray )
        : mFBPropertyArray( pFBArray )
    {
    }

    ~FBPropertyList_Wrapper()
    {
        if ( mFBPropertyArray != NULL )
        {
            delete mFBPropertyArray;
            mFBPropertyArray = NULL;
        }
    }

protected:
    virtual object  GetAtSelf( int lIdx );
    virtual int     GetCountSelf();
    virtual void    AppendSelf( object pObject );
    virtual void    RemoveSelf( object pItem );
    virtual void    RemoveAllSelf();
    virtual void    RemoveAtSelf( int lIdx );
    virtual int     FindSelf( object pObject );

private:
    FBProperty* GetProperty( object pObject );
};

void FBPropertyList_Init();


#if !defined(K_NO_UI) 
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListTreeNode_Wrapper
//
//////////////////////////////////////////////////////////////////
class PYSDK_DLL FBPropertyListTreeNode_Wrapper : public FBProperty_Wrapper, public FBPropertyListBase_Wrapper
{
public:
    FBPropertyListTreeNode* mFBPropertyListTreeNode;

    FBPropertyListTreeNode_Wrapper( FBPropertyListTreeNode* pFBPropertyListTreeNode )
        : FBProperty_Wrapper( pFBPropertyListTreeNode )
    {
        mFBPropertyListTreeNode = pFBPropertyListTreeNode;
    }

    ~FBPropertyListTreeNode_Wrapper()
    {
        mFBPropertyListTreeNode = NULL;
    }

protected:
    virtual object  GetAtSelf( int lIdx );
    virtual int     GetCountSelf();
    virtual void    AppendSelf( object pObject );
    virtual void    RemoveSelf( object pItem );
    virtual void    RemoveAllSelf();
    virtual void    RemoveAtSelf( int lIdx );
    virtual int     FindSelf( object pObject );

private:
    FBTreeNode* GetTreeNode( object pObject );
};
#endif

PYSDK_DLL object FBPropertyListTreeNode_Wrapper_Factory( FBPropertyListTreeNode& pFBPropertyListTreeNode );
void FBPropertyListTreeNode_Init();
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListFCurveKey
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListFCurveKey_Init();

class FBFCurveKey_Wrapper;
PYSDK_DLL FBFCurveKey_Wrapper* FBFCurveKey_Wrapper_Factory( const FBFCurveKey& pFBFCurveKey );
class PYSDK_DLL FBPropertyListFCurveKey_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListFCurveKey* mFBPropertyListFCurveKey;

    // CTOR
    FBPropertyListFCurveKey_Wrapper( FBPropertyListFCurveKey* pFBPropertyListFCurveKey ) 
        : FBProperty_Wrapper( pFBPropertyListFCurveKey )
        , mFBPropertyListFCurveKey( pFBPropertyListFCurveKey )
    {
    };
    // DTOR
    ~FBPropertyListFCurveKey_Wrapper()
    {
    };

    int GetCount()
    {
        
        return mFBPropertyListFCurveKey->GetCount();
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    FBFCurveKey_Wrapper* GetFCurveKey( int lIdx )
    {
        
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return NULL;
        }
        return FBFCurveKey_Wrapper_Factory( mFBPropertyListFCurveKey->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListFCurveKey_Wrapper_Factory( FBPropertyListFCurveKey& pFBPropertyListFCurveKey)
{    
    return WrapFBObject<FBPropertyListFCurveKey_Wrapper, FBPropertyListFCurveKey>( &pFBPropertyListFCurveKey );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListOpticalSegment
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListOpticalSegment_Init();

class FBOpticalSegment_Wrapper;
PYSDK_DLL FBOpticalSegment_Wrapper* FBOpticalSegment_Wrapper_Factory( FBOpticalSegment pFBOpticalSegment );
class PYSDK_DLL FBPropertyListOpticalSegment_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListOpticalSegment* mFBPropertyListOpticalSegment;

    // CTOR
    FBPropertyListOpticalSegment_Wrapper( FBPropertyListOpticalSegment* pFBPropertyListOpticalSegment ) 
        : FBProperty_Wrapper( pFBPropertyListOpticalSegment )
        , mFBPropertyListOpticalSegment( pFBPropertyListOpticalSegment )
    {
    };
    // DTOR
    ~FBPropertyListOpticalSegment_Wrapper()
    {
    };

    int GetCount()
    {

        return mFBPropertyListOpticalSegment->GetCount();
    };
	/////////////////////////////
	/////////////////////////////
	//
	// NOT SWIG COMPATIBLE!!!!
	//
	/////////////////////////////
	/////////////////////////////
    FBOpticalSegment_Wrapper* GetOpticalSegment( int lIdx )
    {

        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
            return NULL;
        }
        return FBOpticalSegment_Wrapper_Factory( mFBPropertyListOpticalSegment->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListOpticalSegment_Wrapper_Factory( FBPropertyListOpticalSegment& pFBPropertyListOpticalSegment)
{    
    return WrapFBObject<FBPropertyListOpticalSegment_Wrapper, FBPropertyListOpticalSegment>( &pFBPropertyListOpticalSegment );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListMarkerSegment
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListMarkerSegment_Init();

class FBOpticalSegment_Wrapper;
class PYSDK_DLL FBPropertyListMarkerSegment_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListMarkerSegment* mFBPropertyListMarkerSegment;

    // CTOR
    FBPropertyListMarkerSegment_Wrapper( FBPropertyListMarkerSegment* pFBPropertyListMarkerSegment ) 
        : FBProperty_Wrapper( pFBPropertyListMarkerSegment )
        , mFBPropertyListMarkerSegment( pFBPropertyListMarkerSegment )
    {
    };
    // DTOR
    ~FBPropertyListMarkerSegment_Wrapper()
    {
    };

    int GetCount()
    {

        return mFBPropertyListMarkerSegment->GetCount();
    };
	/////////////////////////////
	/////////////////////////////
	//
	// NOT SWIG COMPATIBLE!!!!
	//
	/////////////////////////////
	/////////////////////////////
    FBOpticalSegment_Wrapper* GetOpticalSegment( int lIdx )
    {

        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
            return NULL;
        }
        return FBOpticalSegment_Wrapper_Factory( mFBPropertyListMarkerSegment->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListMarkerSegment_Wrapper_Factory( FBPropertyListMarkerSegment& pFBPropertyListMarkerSegment )
{    
    return WrapFBObject<FBPropertyListMarkerSegment_Wrapper, FBPropertyListMarkerSegment>( &pFBPropertyListMarkerSegment );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListOpticalGap
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListOpticalGap_Init();

class FBOpticalGap_Wrapper;
PYSDK_DLL FBOpticalGap_Wrapper* FBOpticalGap_Wrapper_Factory( FBOpticalGap pFBOpticalGap );
class PYSDK_DLL FBPropertyListOpticalGap_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListOpticalGap* mFBPropertyListOpticalGap;

    // CTOR
    FBPropertyListOpticalGap_Wrapper( FBPropertyListOpticalGap* pFBPropertyListOpticalGap ) 
        : FBProperty_Wrapper( pFBPropertyListOpticalGap )
        , mFBPropertyListOpticalGap( pFBPropertyListOpticalGap )
    {
    };
    // DTOR
    ~FBPropertyListOpticalGap_Wrapper()
    {
    };

    int GetCount()
    {

        return mFBPropertyListOpticalGap->GetCount();
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    FBOpticalGap_Wrapper* GetOpticalGap( int lIdx )
    {

        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
            return NULL;
        }
        return FBOpticalGap_Wrapper_Factory( mFBPropertyListOpticalGap->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListOpticalGap_Wrapper_Factory( FBPropertyListOpticalGap& pFBPropertyListOpticalGap)
{    
    return WrapFBObject<FBPropertyListOpticalGap_Wrapper, FBPropertyListOpticalGap>( &pFBPropertyListOpticalGap );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListModelMarkerOptical
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListModelMarkerOptical_Init();

class FBModelMarkerOptical_Wrapper;
class PYSDK_DLL FBPropertyListModelMarkerOptical_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListModelMarkerOptical* mFBPropertyListModelMarkerOptical;

    // CTOR
    FBPropertyListModelMarkerOptical_Wrapper( FBPropertyListModelMarkerOptical* pFBPropertyListModelMarkerOptical ) 
        : FBProperty_Wrapper( pFBPropertyListModelMarkerOptical )
        , mFBPropertyListModelMarkerOptical( pFBPropertyListModelMarkerOptical )
    {
    };
    // DTOR
    ~FBPropertyListModelMarkerOptical_Wrapper()
    {
    };

    int GetCount()
    {

        return mFBPropertyListModelMarkerOptical->GetCount();
	};
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    object GetModelMarkerOptical( int lIdx )
    {

        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
            return object();
        }
		return FBWrapperFactory::TheOne().WrapFBObject( mFBPropertyListModelMarkerOptical->operator[]( lIdx )  );
    };
};

PYSDK_DLL inline object FBPropertyListModelMarkerOptical_Wrapper_Factory( FBPropertyListModelMarkerOptical& pFBPropertyListModelMarkerOptical)
{    
    return WrapFBObject<FBPropertyListModelMarkerOptical_Wrapper, FBPropertyListModelMarkerOptical>( &pFBPropertyListModelMarkerOptical );
	
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListDeviceOpticalMarker
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListDeviceOpticalMarker_Init();

class FBDeviceOpticalMarker_Wrapper;
class PYSDK_DLL FBPropertyListDeviceOpticalMarker_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListDeviceOpticalMarker* mFBPropertyListDeviceOpticalMarker;

    // CTOR
    FBPropertyListDeviceOpticalMarker_Wrapper( FBPropertyListDeviceOpticalMarker* pFBPropertyListDeviceOpticalMarker ) 
        : FBProperty_Wrapper( pFBPropertyListDeviceOpticalMarker )
        , mFBPropertyListDeviceOpticalMarker( pFBPropertyListDeviceOpticalMarker )
    {
    };
    // DTOR
    ~FBPropertyListDeviceOpticalMarker_Wrapper()
    {
    };

    int GetCount()
    {
        return mFBPropertyListDeviceOpticalMarker->GetCount();
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    object GetDeviceOpticalMarker( int lIdx )
    {
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
            return object();
        }
        return FBWrapperFactory::TheOne().WrapFBObject( mFBPropertyListDeviceOpticalMarker->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListDeviceOpticalMarker_Wrapper_Factory( FBPropertyListDeviceOpticalMarker& pFBPropertyListDeviceOpticalMarker)
{    
    return WrapFBObject<FBPropertyListDeviceOpticalMarker_Wrapper, FBPropertyListDeviceOpticalMarker>( &pFBPropertyListDeviceOpticalMarker );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListRigidBodyMarkers
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListRigidBodyMarkers_Init();

class FBModelMarkerOptical_Wrapper;
class PYSDK_DLL FBPropertyListRigidBodyMarkers_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListRigidBodyMarkers* mFBPropertyListRigidBodyMarkers;

    // CTOR
    FBPropertyListRigidBodyMarkers_Wrapper( FBPropertyListRigidBodyMarkers* pFBPropertyListRigidBodyMarkers ) 
        : FBProperty_Wrapper( pFBPropertyListRigidBodyMarkers )
        , mFBPropertyListRigidBodyMarkers( pFBPropertyListRigidBodyMarkers )
    {
    };
    // DTOR
    ~FBPropertyListRigidBodyMarkers_Wrapper()
    {
    };

    int GetCount()
    {

        return mFBPropertyListRigidBodyMarkers->GetCount();
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    object GetRigidBodyMarker( int lIdx )
    {

        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
            return object();
        }
		return FBWrapperFactory::TheOne().WrapFBObject( mFBPropertyListRigidBodyMarkers->operator[]( lIdx )  );
    };
};

PYSDK_DLL inline object FBPropertyListRigidBodyMarkers_Wrapper_Factory( FBPropertyListRigidBodyMarkers& pFBPropertyListRigidBodyMarkers )
{    
    return WrapFBObject<FBPropertyListRigidBodyMarkers_Wrapper, FBPropertyListRigidBodyMarkers>( &pFBPropertyListRigidBodyMarkers );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListRigidBody
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListRigidBody_Init();

class FBRigidBody_Wrapper;
PYSDK_DLL FBRigidBody_Wrapper* FBRigidBody_Wrapper_Factory( FBRigidBody pFBRigidBody );
class PYSDK_DLL FBPropertyListRigidBody_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListRigidBody* mFBPropertyListRigidBody;

    // CTOR
    FBPropertyListRigidBody_Wrapper( FBPropertyListRigidBody* pFBPropertyListRigidBody ) 
        : FBProperty_Wrapper( pFBPropertyListRigidBody )
        , mFBPropertyListRigidBody( pFBPropertyListRigidBody )
    {
    };
    // DTOR
    ~FBPropertyListRigidBody_Wrapper()
    {
    };

    int GetCount()
    {

        return mFBPropertyListRigidBody->GetCount();
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    FBRigidBody_Wrapper* GetRigidBody( int lIdx )
	{

        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
            return NULL;
        }
        return FBRigidBody_Wrapper_Factory( mFBPropertyListRigidBody->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListRigidBody_Wrapper_Factory( FBPropertyListRigidBody& pFBPropertyListRigidBody)
{    
    return WrapFBObject<FBPropertyListRigidBody_Wrapper, FBPropertyListRigidBody>( &pFBPropertyListRigidBody );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListAnimationNode
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListAnimationNode_Init();
class FBAnimationNode_Wrapper;
class PYSDK_DLL FBPropertyListAnimationNode_Wrapper  : public FBProperty_Wrapper {

public:
    FBPropertyListAnimationNode* mFBPropertyListAnimationNode;

    // CTOR
    FBPropertyListAnimationNode_Wrapper( FBPropertyListAnimationNode* pFBPropertyListAnimationNode ) 
        : FBProperty_Wrapper( pFBPropertyListAnimationNode )
        , mFBPropertyListAnimationNode( pFBPropertyListAnimationNode )
    {
    };
    // DTOR
    ~FBPropertyListAnimationNode_Wrapper()
    {
    };

    int GetCount()
    {
        
        return mFBPropertyListAnimationNode->GetCount();
    };

	object FindByLabel( const char* pNodeLabel )
    {
        
        return FBWrapperFactory::TheOne().WrapFBObject(mFBPropertyListAnimationNode->FindByLabel( pNodeLabel ));
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    object GetAnimationNode( int lIdx )
    {
        
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return object();
        }
        return FBWrapperFactory::TheOne().WrapFBObject( mFBPropertyListAnimationNode->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListAnimationNode_Wrapper_Factory( FBPropertyListAnimationNode& pFBPropertyListAnimationNode)
{
    return WrapFBObject<FBPropertyListAnimationNode_Wrapper, FBPropertyListAnimationNode>( &pFBPropertyListAnimationNode );    
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListModelTemplate
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListModelTemplate_Init();

class FBModelTemplate_Wrapper;

class PYSDK_DLL FBPropertyListModelTemplate_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListModelTemplate* mFBPropertyListModelTemplate;

    // CTOR
    FBPropertyListModelTemplate_Wrapper( FBPropertyListModelTemplate* pFBPropertyListModelTemplate ) 
        : FBProperty_Wrapper( pFBPropertyListModelTemplate )
        , mFBPropertyListModelTemplate( pFBPropertyListModelTemplate )
    {
    };

    // DTOR
    ~FBPropertyListModelTemplate_Wrapper()
    {
    };

    int GetCount()
    {
        
        return mFBPropertyListModelTemplate->GetCount();
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    object GetModelTemplate( int lIdx )
    {
        
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return object();
        }
        return FBWrapperFactory::TheOne().WrapFBObject( mFBPropertyListModelTemplate->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListModelTemplate_Wrapper_Factory( FBPropertyListModelTemplate& pFBPropertyListModelTemplate)
{    
    return WrapFBObject<FBPropertyListModelTemplate_Wrapper, FBPropertyListModelTemplate>( &pFBPropertyListModelTemplate );    
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListModelTemplateBinding
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListModelTemplateBinding_Init();

class FBAnimationNode_Wrapper;
PYSDK_DLL object FBModelTemplateBinding_Wrapper_Factory( FBAnimationNode* pFBAnimationNode );
class PYSDK_DLL FBPropertyListModelTemplateBinding_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListModelTemplateBinding* mFBPropertyListModelTemplateBinding;

    // CTOR
    FBPropertyListModelTemplateBinding_Wrapper( FBPropertyListModelTemplateBinding* pFBPropertyListModelTemplateBinding ) 
        : FBProperty_Wrapper( pFBPropertyListModelTemplateBinding )
        , mFBPropertyListModelTemplateBinding( pFBPropertyListModelTemplateBinding )
    {
    };
    // DTOR
    ~FBPropertyListModelTemplateBinding_Wrapper()
    {
    };

    int GetCount()
    {
        
        return mFBPropertyListModelTemplateBinding->GetCount();
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    object GetModelTemplateBinding( int lIdx )
    {
        
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return object();
        }
        return FBWrapperFactory::TheOne().WrapFBObject( mFBPropertyListModelTemplateBinding->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListModelTemplateBinding_Wrapper_Factory( FBPropertyListModelTemplateBinding& pFBPropertyListModelTemplateBinding)
{    
    return WrapFBObject<FBPropertyListModelTemplateBinding_Wrapper, FBPropertyListModelTemplateBinding>( &pFBPropertyListModelTemplateBinding );    
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListDeviceInstrument
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListDeviceInstrument_Init();
class FBDeviceInstrument_Wrapper;
class PYSDK_DLL FBPropertyListDeviceInstrument_Wrapper : public FBProperty_Wrapper {

public:
    FBPropertyListDeviceInstrument* mFBPropertyListDeviceInstrument;

    // CTOR
    FBPropertyListDeviceInstrument_Wrapper( FBPropertyListDeviceInstrument* pFBPropertyListDeviceInstrument ) 
        : FBProperty_Wrapper( pFBPropertyListDeviceInstrument )
        , mFBPropertyListDeviceInstrument( pFBPropertyListDeviceInstrument )
    {
    };
    // DTOR
    ~FBPropertyListDeviceInstrument_Wrapper()
    {
    };

    int GetCount()
    {
        
        return mFBPropertyListDeviceInstrument->GetCount();
    };
    /////////////////////////////
    /////////////////////////////
    //
    // NOT SWIG COMPATIBLE!!!!
    //
    /////////////////////////////
    /////////////////////////////
    object GetDeviceInstrument( int lIdx )
    {
        
        if( lIdx < 0 ) {
            lIdx += GetCount();
        }
        if( lIdx < 0 || lIdx >= GetCount()) {
            PyErr_SetString(PyExc_IndexError,"list index out of range");
            throw_error_already_set();
			return object();
        }
        return FBWrapperFactory::TheOne().WrapFBObject( mFBPropertyListDeviceInstrument->operator[]( lIdx ) );
    };
};

PYSDK_DLL inline object FBPropertyListDeviceInstrument_Wrapper_Factory( FBPropertyListDeviceInstrument& pFBPropertyListDeviceInstrument)
{    
    return WrapFBObject<FBPropertyListDeviceInstrument_Wrapper, FBPropertyListDeviceInstrument>( &pFBPropertyListDeviceInstrument );    
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListObject
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListObject_Init();

class PYSDK_DLL FBPropertyListObject_Wrapper : public FBPropertyListComponent_Wrapper {
public:
    // CTOR
    FBPropertyListObject_Wrapper( FBPropertyListObject* pFBPropertyListObject );

    // DTOR
    virtual ~FBPropertyListObject_Wrapper();

    virtual void SetSingleConnect(bool pSingleConnect);
    virtual bool GetSingleConnect();
};

#if !defined(K_NO_MANIPULATOR)
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// CLASS: FBPropertyListManipulator
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Wrapper Initializer.
void FBPropertyListManipulator_Init();

class FBManipulator_Wrapper;
class PYSDK_DLL FBPropertyListManipulator_Wrapper 
	: public FBProperty_Wrapper
{
public:
	FBPropertyListManipulator* mFBPropertyListManipulator;

public:
	FBPropertyListManipulator_Wrapper( FBPropertyListManipulator& pFBPropertyListManipulator ) 
		: FBProperty_Wrapper( &pFBPropertyListManipulator )
		, mFBPropertyListManipulator( &pFBPropertyListManipulator )
	{
	}

	~FBPropertyListManipulator_Wrapper()
	{
	}

	int GetCount()
	{
		return mFBPropertyListManipulator->GetCount();
	}

	object GetManipulator( int pIndex )
	{
		if( pIndex < 0 ) 
		{
			pIndex += GetCount();
		}

		if( pIndex < 0 || pIndex >= GetCount()) 
		{
			PyErr_SetString(PyExc_IndexError,"list index out of range");
			throw_error_already_set();
			return object();
		}

		return FBWrapperFactory::TheOne().WrapFBObject( mFBPropertyListManipulator->operator[]( pIndex ) );
	}
};
#endif

#endif // pyfbpropertylist_h__