#ifndef pyfbdirmap_h__
#define pyfbdirmap_h__
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
// FBDirMap
// =======================================================================================
void FBDirMap_Init();

class PYSDK_DLL FBDirMap_Wrapper {
public:
	FBDirMap* mFBDirMap;
public:
    FBDirMap_Wrapper(  ) : mFBDirMap( new FBDirMap ) {}
    virtual ~FBDirMap_Wrapper( ) { delete mFBDirMap; }

	void Add(const char *pSourceDir, const char *pTargetDir) { mFBDirMap->Add(pSourceDir,pTargetDir); }
	int GetCount() { return mFBDirMap->GetCount(); }
	str GetSource(int pIndex) { return (const char *) mFBDirMap->GetSource(pIndex); }
	str GetTarget(int pIndex) { return (const char *) mFBDirMap->GetTarget(pIndex); }
	void Clear() { mFBDirMap->Clear(); }
	str Map(const char *pPath) { return (const char *) mFBDirMap->Map(pPath); }
};
#endif // pyfbdirmap_h__

