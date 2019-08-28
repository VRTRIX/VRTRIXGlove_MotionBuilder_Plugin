/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#ifndef PYFBSDKNamespace
	#define PYFBSDKNamespace                PYFBSDK
	#define PYFBSDKNamespaceFunc( Name )    PYFBSDKNamespace::Name
#endif

#include <kmath/maths.h>	// Must be included first otherwise Boost is messing with isnan()
#include "pyfbsdk_version_wrapper.h"

