#ifndef pyfbwidgetholder_h__
#define pyfbwidgetholder_h__
/**************************************************************************
 Copyright 2011 Autodesk, Inc.
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

#include "pyfbvisualcomponent.h"

void FBWidgetHolder_Init();

class PYSDK_DLL FBWidgetHolder_Wrapper : public FBVisualComponent_Wrapper
{
public:
	FBWidgetHolder* mFBWidgetHolder;

public:
	FBWidgetHolder_Wrapper( FBComponent* pFBComponent ) : FBVisualComponent_Wrapper( pFBComponent ) { mFBWidgetHolder = (FBWidgetHolder*)pFBComponent; }
	FBWidgetHolder_Wrapper( void );	

    ~FBWidgetHolder_Wrapper();
};
#endif // pyfbwidgetholder_h__
