#ifndef pyfbwrapperfactory_h__
#define pyfbwrapperfactory_h__
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

class PYSDK_DLL FBWrapperFactory
{
public:
    typedef boost::python::object (*WrappingFunc)( FBPlug* );
    typedef bool (*IsSameTypeFunc)( int );
public:
    FBWrapperFactory();
    ~FBWrapperFactory();

    static FBWrapperFactory& TheOne();

    void RegisterWrapperType( const char* pClassName, int pTypeId, int pParentId, WrappingFunc pCreator );
    
    object WrapFBObject( FBPlug* );

    void Init();
private:    
    void PrintInfo();
    void PrintBaseClassInfo();
private:
    class Impl;
    Impl* mImpl;
    
};

template<class FBObject_>
int GetTypeInfoGeneric()
{
    return FBObject_::TypeInfo;
}

template<class FBWrapper_, class FBObject_>
object WrapFBPlug( FBPlug* pPlug )
{
    return WrapFBObject<FBWrapper_, FBObject_>( dynamic_cast<FBObject_*>( pPlug ) );
}

#define REGISTER_FBWRAPPER_FORWARD( CLASSNAME ) \
    {scope l##CLASSNAME##Scope = 

#define REGISTER_FBWRAPPER( CLASSNAME ) \
    l##CLASSNAME##Scope.attr("TypeInfo") = CLASSNAME::TypeInfo;\
    l##CLASSNAME##Scope.attr("ClassGroupName") = CLASSNAME::ClassGroupName;}\
    register_ptr_to_python< boost::shared_ptr<CLASSNAME##_Wrapper> >(); \
    FBWrapperFactory::TheOne().RegisterWrapperType( #CLASSNAME, CLASSNAME::TypeInfo, CLASSNAME::__FBParentClass::TypeInfo, &WrapFBPlug<CLASSNAME##_Wrapper, CLASSNAME> ); \
    def(#CLASSNAME"_TypeInfo", GetTypeInfoGeneric< CLASSNAME > );
    
#define REGISTER_FBWRAPPER_WITH_PARENT( CLASSNAME, PARENT_ID ) \
    l##CLASSNAME##Scope.attr("TypeInfo") = CLASSNAME::TypeInfo;\
    l##CLASSNAME##Scope.attr("ClassGroupName") = CLASSNAME::ClassGroupName;}\
    register_ptr_to_python< boost::shared_ptr<CLASSNAME##_Wrapper> >(); \
    FBWrapperFactory::TheOne().RegisterWrapperType( #CLASSNAME, CLASSNAME::TypeInfo, PARENT_ID, &WrapFBPlug<CLASSNAME##_Wrapper, CLASSNAME> ); \
    def(#CLASSNAME"_TypeInfo", GetTypeInfoGeneric< CLASSNAME > );

#define REGISTER_FBWRAPPER_WITH_CREATOR( CLASSNAME, PARENT_ID, CREATOR ) \
    l##CLASSNAME##Scope.attr("TypeInfo") = CLASSNAME::TypeInfo;\
    l##CLASSNAME##Scope.attr("ClassGroupName") = CLASSNAME::ClassGroupName;}\
    register_ptr_to_python< boost::shared_ptr<CLASSNAME##_Wrapper> >(); \
    FBWrapperFactory::TheOne().RegisterWrapperType( #CLASSNAME, CLASSNAME::TypeInfo, PARENT_ID, CREATOR ); \
    def(#CLASSNAME"_TypeInfo", GetTypeInfoGeneric< CLASSNAME > );

#define REGISTER_FBWRAPPER_NO_FACTORY( CLASSNAME ) \
    l##CLASSNAME##Scope.attr("TypeInfo") = CLASSNAME::TypeInfo;\
    l##CLASSNAME##Scope.attr("ClassGroupName") = CLASSNAME::ClassGroupName;}\
    register_ptr_to_python< boost::shared_ptr<CLASSNAME##_Wrapper> >(); \
    def(#CLASSNAME"_TypeInfo", GetTypeInfoGeneric< CLASSNAME > );

#define REGISTER_FBWRAPPER_ONLY( CLASSNAME ) \
    register_ptr_to_python< boost::shared_ptr<CLASSNAME##_Wrapper> >();

//////////////////////////////////////////////////////////////////////////
// Declare macros
//////////////////////////////////////////////////////////////////////////
#define DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS(PROPNAME, PROPTYPE) \
    void        Set##PROPNAME(PROPTYPE pValue);\
    PROPTYPE    Get##PROPNAME();

#define DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(PROPNAME, PROPTYPE) \
    PROPTYPE    Get##PROPNAME();

#define DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(PROPNAME, PROPTYPE) \
    void                Set##PROPNAME( PROPTYPE##_Wrapper& pValue );\
    PROPTYPE##_Wrapper* Get##PROPNAME( void );

#define DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY(PROPNAME, PROPTYPE) \
    PROPTYPE##_Wrapper* Get##PROPNAME( void );

#define DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_DEPRECATED                         DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS
#define DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY_DEPRECATED                DECLARE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY
#define DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_DEPRECATED             DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS
#define DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY_DEPRECATED    DECLARE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY

//////////////////////////////////////////////////////////////////////////
// Define macros
//////////////////////////////////////////////////////////////////////////
#define DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(CLASSNAME, PROPNAME, PROPTYPE) \
    void        CLASSNAME##_Wrapper::Set##PROPNAME(PROPTYPE pValue) { m##CLASSNAME->PROPNAME = pValue; }\
    PROPTYPE    CLASSNAME##_Wrapper::Get##PROPNAME()                { return m##CLASSNAME->PROPNAME; }

#define DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(CLASSNAME, PROPNAME, PROPTYPE) \
    PROPTYPE    CLASSNAME##_Wrapper::Get##PROPNAME() { return m##CLASSNAME->PROPNAME; }

#define DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(CLASSNAME, PROPNAME, PROPTYPE) \
    void                CLASSNAME##_Wrapper::Set##PROPNAME(PROPTYPE##_Wrapper& pValue)  { m##CLASSNAME->PROPNAME = *pValue.m##PROPTYPE; }\
    PROPTYPE##_Wrapper* CLASSNAME##_Wrapper::Get##PROPNAME()                            { return new PROPTYPE##_Wrapper( m##CLASSNAME->PROPNAME ); }

#define DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY(CLASSNAME, PROPNAME, PROPTYPE) \
    PROPTYPE##_Wrapper* CLASSNAME##_Wrapper::Get##PROPNAME() { return new PROPTYPE##_Wrapper( m##CLASSNAME->PROPNAME ); }

#define DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_DEPRECATED                          DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS
#define DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY_DEPRECATED                 DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY
#define DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_DEPRECATED              DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS
#define DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY_DEPRECATED     DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY

//////////////////////////////////////////////////////////////////////////
// Declare & Define at the same time
//////////////////////////////////////////////////////////////////////////
#define DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS(CLASSNAME, PROPNAME, PROPTYPE) \
    void        Set##PROPNAME(PROPTYPE pValue) { m##CLASSNAME->PROPNAME = pValue; }\
    PROPTYPE    Get##PROPNAME()                { return m##CLASSNAME->PROPNAME; }

#define DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(CLASSNAME, PROPNAME, PROPTYPE) \
    PROPTYPE    Get##PROPNAME() { return m##CLASSNAME->PROPNAME; }

#define DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(CLASSNAME, PROPNAME, PROPTYPE) \
    void                Set##PROPNAME(PROPTYPE##_Wrapper& pValue)  { m##CLASSNAME->PROPNAME = *pValue.m##PROPTYPE; }\
    PROPTYPE##_Wrapper* Get##PROPNAME()                            { return new PROPTYPE##_Wrapper( m##CLASSNAME->PROPNAME ); }

#define DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY(CLASSNAME, PROPNAME, PROPTYPE) \
    PROPTYPE##_Wrapper* Get##PROPNAME() { return new PROPTYPE##_Wrapper( m##CLASSNAME->PROPNAME ); }

#define DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_DEPRECATED                          DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS
#define DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY_DEPRECATED                 DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY
#define DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_DEPRECATED              DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS
#define DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY_DEPRECATED     DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY

//////////////////////////////////////////////////////////////////////////
// Add macros
//////////////////////////////////////////////////////////////////////////
#define ADD_ORSDK_PROPERTY_PYTHON_ACCESS(CLASSNAME, PROPNAME) \
    .add_property( #PROPNAME, &CLASSNAME##_Wrapper::Get##PROPNAME, &CLASSNAME##_Wrapper::Set##PROPNAME)

#define ADD_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY(CLASSNAME, PROPNAME) \
    .add_property( #PROPNAME, &CLASSNAME##_Wrapper::Get##PROPNAME)

#define ADD_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS(CLASSNAME, PROPNAME) \
    .add_property( #PROPNAME, make_function( &CLASSNAME##_Wrapper::Get##PROPNAME, return_value_policy<manage_new_object>() ), &CLASSNAME##_Wrapper::Set##PROPNAME)

#define ADD_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY(CLASSNAME, PROPNAME) \
    .add_property( #PROPNAME, make_function( &CLASSNAME##_Wrapper::Get##PROPNAME, return_value_policy<manage_new_object>() ))

#define ADD_ORSDK_PROPERTY_PYTHON_ACCESS_DEPRECATED                             ADD_ORSDK_PROPERTY_PYTHON_ACCESS
#define ADD_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY_DEPRECATED                    ADD_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY
#define ADD_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_DEPRECATED                 ADD_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS
#define ADD_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY_DEPRECATED        ADD_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY

#endif // pyfbwrapperfactory_h__
