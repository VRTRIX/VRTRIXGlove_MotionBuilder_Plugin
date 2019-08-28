#ifndef pyfbprofiletaskcycle_h__
#define pyfbprofiletaskcycle_h__
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
// FBProfileTaskCycle
// =======================================================================================
void FBProfileTaskCycle_Init();

class FBProfileTaskCycle_Wrapper;
PYSDK_DLL FBProfileTaskCycle_Wrapper* FBProfileTaskCycle_Wrapper_Factory( FBProfileTaskCycle* pFBProfileTaskCycle );

class PYSDK_DLL FBProfileTaskCycle_Wrapper {
public:
	FBProfileTaskCycle* mFBProfileTaskCycle;
public:
    FBProfileTaskCycle_Wrapper( FBProfileTaskCycle* pDC ) : mFBProfileTaskCycle( pDC ) {}
	virtual ~FBProfileTaskCycle_Wrapper( ) {}

	int	GetIndex(){ return mFBProfileTaskCycle->GetIndex(); }
	const char*	GetName(){ return mFBProfileTaskCycle->GetName(); }
	FBColor_Wrapper* GetColor();
	tuple GetAvgMinMaxUsage();
	bool IsStarted(){ return mFBProfileTaskCycle->IsStarted(); }
	int GetChildCount(){ return mFBProfileTaskCycle->GetChildCount(); }
	FBProfileTaskCycle_Wrapper*	GetChild(int pIndex){ FBProfileTaskCycle* lDC = mFBProfileTaskCycle->GetChild(pIndex); return lDC ? FBProfileTaskCycle_Wrapper_Factory(lDC) : NULL; }
};

PYSDK_DLL inline FBProfileTaskCycle_Wrapper* FBProfileTaskCycle_Wrapper_Factory( FBProfileTaskCycle* pFBProfileTaskCycle )
{
	FBProfileTaskCycle_Wrapper* lFBProfileTaskCycle = 0;
	if( pFBProfileTaskCycle )
	{
		lFBProfileTaskCycle = new FBProfileTaskCycle_Wrapper( pFBProfileTaskCycle );
	}

	return lFBProfileTaskCycle;
}

#endif // pyfbprofiletaskcycle_h__