#ifndef pyfbpythonwrapper_h__
#define pyfbpythonwrapper_h__
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

/**
	FBPythonGuard: Auto-class that calls PyGILState_Ensure/PyGILState_Release to prevent crashes when doing Python calls
*/
class FBPythonGuard
{
public:
    FBPythonGuard();
    ~FBPythonGuard();
private:
    PyGILState_STATE mGILState{ (PyGILState_STATE)-1 };
};

void FBPythonWrapper_Init();

/**
    Base class for object that needs to be unbind when their 
    FB SDK counterpart is destroyed. When use with Wrapper_Factory 
    It ensures that if the same FBSDK Object is wrapped more
    than once, the same PyObject and Wrapper will be used.
*/
class PYSDK_DLL FBPythonWrapper : public FBScriptWrapper
{
public:
    PyObject* mSelf;
    FBWrapperHolder* mHolder;
public:
    explicit FBPythonWrapper( FBWrapperHolder* pHolder );
    virtual ~FBPythonWrapper();
    virtual void ContentDestroy();

    object OnUnbind();
    
    object GetWrapperEvent( FBEventName );

	void SetSelf(PyObject* pSelf);
    const PyObject *GetSelf() const { return mSelf; }
    PyObject *GetSelf() { return mSelf; }

	void SetAllocated( bool pAllocated = true );
    bool IsAllocated()const;

    static int GetNbWrapper();
    static int GetNbUnboundWrapper();
protected:
    friend class __FBCallback;
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
private:
    bool mAllocated;
};

template<class FBWrapper_>
object ManagedPythonObject( FBWrapper_* pFBObject )
{
    return object( boost::shared_ptr<FBWrapper_>( pFBObject ) );
};

template<class FBWrapper_>
object CreateManagedPythonObject( FBWrapper_* pFBObject )
{
    boost::shared_ptr<FBWrapper_> lPtr( pFBObject );

    object lPyObject( lPtr );

    FBPythonWrapper* lPyWrapper = dynamic_cast<FBPythonWrapper*>( pFBObject );
    if ( lPyWrapper )
    {
        lPtr->mSelf = lPyObject.ptr();
    }    

    return lPyObject;
};

template<class FBWrapper_, class FBObject_>
object CreateFBPythonWrapper( FBObject_* pFBObject )
{
    assert( pFBObject );
    return CreateManagedPythonObject<FBWrapper_>( new FBWrapper_( pFBObject ) );
}


PYSDK_DLL object FBScriptWrapperToPythonObject( FBScriptWrapper* pWrapper );

template<class FBWrapper_, class FBObject_>
object WrapFBObject( FBObject_* pFBObject )
{
    if ( pFBObject )
    {
        FBScriptWrapper* lWrapper = pFBObject->GetWrapper();
        if ( !lWrapper )
        {        
            return CreateFBPythonWrapper<FBWrapper_, FBObject_>( pFBObject );
        }
        return FBScriptWrapperToPythonObject( lWrapper );
    }
    else
    {
        return object();
    }    
}

template<class FBWrapper_>
class Wrapper_Container_Ref : public FBWrapper_
{
public:
    explicit Wrapper_Container_Ref( PyObject* pObject )
        : FBWrapper_()
    {
		FBWrapper_::SetSelf(pObject);
        Py_INCREF(pObject);
    }
};


template<class FBWrapper_, class P1>
class Wrapper_Container_Ref_1 : public FBWrapper_
{
public:
    explicit Wrapper_Container_Ref_1( PyObject* pObject, P1 p1 )
        : FBWrapper_(p1)
    {
        FBWrapper_::SetSelf(pObject);
        Py_INCREF(pObject);
    }
};


template<class FBWrapper_>
class Wrapper_Container : public FBWrapper_
{
public:
    explicit Wrapper_Container( PyObject* pObject )
        : FBWrapper_()
    {
        // this.mSelf; /* = pObject;*/
        FBWrapper_::SetSelf(pObject);
    }
};

template<class FBWrapper_, class P1>
class Wrapper_Container_1 : public FBWrapper_
{
public:
    explicit Wrapper_Container_1( PyObject* pObject, P1 p1 )
        : FBWrapper_( p1 )
    {
		FBWrapper_::SetSelf(pObject);
		//this.mSelf = pObject;
    }
};

template<class FBWrapper_, class P1, class P2>
class Wrapper_Container_2 : public FBWrapper_
{
public:
    Wrapper_Container_2( PyObject* pObject, P1 p1, P2 p2 )
        : FBWrapper_( p1, p2 )
    {
		FBWrapper_::SetSelf(pObject);
        //this.mSelf = pObject;
    }
};

template<class FBWrapper_, class P1, class P2, class P3>
class Wrapper_Container_3 : public FBWrapper_
{
public:
    Wrapper_Container_3( PyObject* pObject, P1 p1, P2 p2, P3 p3 )
        : FBWrapper_( p1, p2, p3 )
    {
		FBWrapper_::SetSelf(pObject);
        //this.mSelf = pObject;
    }
};

template<class FBWrapper_, class P1>
class Wrapper_Container_1_Opt : public FBWrapper_
{
public:
    Wrapper_Container_1_Opt( PyObject* pObject, P1 p1 )
        : FBWrapper_( p1 )
    {
		FBWrapper_::SetSelf(pObject);
        //this.mSelf = pObject;
    }

    explicit Wrapper_Container_1_Opt( PyObject* pObject )
        : FBWrapper_()
    {
		FBWrapper_::SetSelf(pObject);
        //this.mSelf = pObject;
    }
};

template<class FBWrapper_, class P1, class P2> 
class Wrapper_Container_2_Opt : public FBWrapper_
{
public:
    Wrapper_Container_2_Opt( PyObject* pObject, P1 p1, P2 p2 )
        : FBWrapper_( p1, p2 )
    {
        FBWrapper_::SetSelf(pObject);
        //this.mSelf = pObject;
    }

    explicit Wrapper_Container_2_Opt( PyObject* pObject, P1 p1 )
        : FBWrapper_( p1 )
    {
        FBWrapper_::SetSelf(pObject);
        //this.mSelf = pObject;
    }
};

// Functions for calling python from C++ where we don't wish the errors to propagate
template <typename R>
R FBCallPythonCatch(PyObject *pObject, const char *pName, R pErrorValue)
{
	FBPythonGuard lPythonGuard;

    try
    {
        return call_method<R>(pObject, pName);
    } 
    catch(const error_already_set&) 
    {
        PyErr_Print();
        // Stop the error propagating to the next python use
        PyErr_Clear();
        return pErrorValue;
    } 
}


inline void FBCallPythonCatch(PyObject *pObject, const char *pName)
{
	FBPythonGuard lPythonGuard;

    try
    {
        call_method<void>(pObject, pName);
    } 
    catch(const error_already_set&) 
    {
        PyErr_Print();
        // Stop the error propagating to the next python use
        PyErr_Clear();
    } 
}


template <typename R, typename P1>
R FBCallPythonCatch1(PyObject *pObject, const char *pName, P1 const &pParam1, R pErrorValue)
{
	FBPythonGuard lPythonGuard;

    try
    {
        return call_method<R>(pObject, pName, pParam1);
    } 
    catch(const error_already_set&) 
    {
        PyErr_Print();
        // Stop the error propagating to the next python use
        PyErr_Clear();
        return pErrorValue;
    } 
}

template <typename P1>
void FBCallPythonCatch1(PyObject *pObject, const char *pName, P1 const &pParam1)
{
	FBPythonGuard lPythonGuard;

    try
    {
        call_method<void>(pObject, pName, pParam1);
    } 
    catch(const error_already_set&) 
    {
        PyErr_Print();
        // Stop the error propagating to the next python use
        PyErr_Clear();
    } 
}

template <typename R, typename P1, typename P2>
R FBCallPythonCatch2(PyObject *pObject, const char *pName, P1 const &pParam1, P2 const &pParam2, R pErrorValue)
{
	FBPythonGuard lPythonGuard;

    try
    {
        return call_method<R>(pObject, pName, pParam1, pParam2);
    } 
    catch(const error_already_set&) 
    {
        PyErr_Print();
        // Stop the error propagating to the next python use
        PyErr_Clear();
        return pErrorValue;
    } 
}

template <typename P1, typename P2>
void FBCallPythonCatch2(PyObject *pObject, const char *pName, P1 const &pParam1, P2 const &pParam2)
{
	FBPythonGuard lPythonGuard;

    try
    {
        call_method<void>(pObject, pName, pParam1, pParam2);
    } 
    catch(const error_already_set&) 
    {
        PyErr_Print();
        // Stop the error propagating to the next python use
        PyErr_Clear();
    } 
}
#endif // pyfbpythonwrapper_h__
