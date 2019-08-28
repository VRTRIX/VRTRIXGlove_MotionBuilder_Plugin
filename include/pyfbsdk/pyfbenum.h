#ifndef pyfbenum_h__
#define pyfbenum_h__
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
// GLOBAL ENUMS: 
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Enums Initializer
void FBEnum_Init();

#endif // pyfbenum_h__
