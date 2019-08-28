#ifndef pyfbconstraintinfo_h__
#define pyfbconstraintinfo_h__
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
// FBConstraintInfo
// =======================================================================================
void FBConstraintInfo_Init();

class PYSDK_DLL FBConstraintInfo_Wrapper {
public:
	FBConstraintInfo* mFBConstraintInfo;
public:	
    FBConstraintInfo_Wrapper() { mFBConstraintInfo = new FBConstraintInfo; }
    virtual ~FBConstraintInfo_Wrapper( ) { delete mFBConstraintInfo; }
	bool GetSnapRequested() { return mFBConstraintInfo->GetSnapRequested(  ); }
	bool GetZeroRequested() { return mFBConstraintInfo->GetZeroRequested(  ); }
};
#endif // pyfbconstraintinfo_h__

