#ifndef pyfbsdk_version_wrapper_h__
#define pyfbsdk_version_wrapper_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
#define PYSDK_DLL K_DLLEXPORT
#endif

// Suppress warnings from boost header files.

#ifdef _MSC_VER
	#pragma warning(disable:4100) // Unreferenced formal parameter.
	#pragma warning(disable:4244) // Conversion from 'long double' to 'double', possible loss of data.
	#pragma warning(disable:4459) // declaration of 'xxxx' hides global declaration
#endif

#include <boost/python/call_method.hpp>
#include <boost/python/class.hpp>
#include <boost/python/def.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/register_ptr_to_python.hpp>
#include <boost/python/str.hpp>

using namespace boost::python;

#include <fbsdk/fbsdk.h>

#if !defined(K_NO_UNDO)
	#include <fbsdk/fbundomanager.h>
#endif

#ifdef FB_KERNEL
	#include <fbkernel/fbkernel.h>
#endif

#include <fbsdk/fbmultilang.h>
#if !defined(K_NO_PROJECTSETTINGS)
	#include <fbsdk/fbprojectsettings.h>
#endif

namespace PYFBSDKNamespace {

#include "pyfbutils.h" 
#include "pyfbcallback.h" 
#include "pyfbpythonwrapper.h" 
#include "pyfbwrapperfactory.h" 

//////////////////////////////////////////////////////////////////
//
// CLASS: FBTime
//
//////////////////////////////////////////////////////////////////

#include "pyfbtime.h"
#include "pyfbtimespan.h"

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
// CLASS: FBMath
//
//////////////////////////////////////////////////////////////////

#include "pyfbvector.h"

//////////////////////////////////////////////////////////////////

#include "pyfbplug.h"

//////////////////////////////////////////////////////////////////
//
// CLASS: FBProperty
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include "pyfbproperty.h"
#include "pyfbpropertylist.h"

#if !defined(K_NO_PROJECTSETTINGS)
	class FBProjectSettings_Wrapper;
	FBProjectSettings_Wrapper* FBProjectSettings_Wrapper_Factory(FBProjectSettings*);
#endif

//////////////////////////////////////////////////////////////////

#include "pyfbpropertymanager.h" 
#include "pyfbcomponent.h" 
#include "pyfbnamespace.h"

#if !defined(K_NO_PROJECTSETTINGS)
	#include "pyfbprojectsettings.h"
#endif

#ifdef FB_KERNEL 
	#include "pyfbkernel.h"
#endif
};


using namespace PYFBSDKNamespace;

#endif // pyfbsdk_version_wrapper_h__
