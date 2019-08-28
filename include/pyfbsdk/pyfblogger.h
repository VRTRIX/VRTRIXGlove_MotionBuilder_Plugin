#ifndef pyfblogger_h__
#define pyfblogger_h__
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
// FBProfiler
// =======================================================================================
void FBLogger_Init();

class PYSDK_DLL FBLogger_Wrapper : public FBComponent_Wrapper {
public:
	FBLogger* mFBLogger;

public:
	FBLogger_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBLogger = (FBLogger*)pFBComponent; }
	FBLogger_Wrapper(  );

    object GetLog();
    bool EnableByID(int pTypeInfo, bool pEnable) { return FBLogger::TheOne().Enable(pTypeInfo, pEnable); }
    bool EnableByName(const char* pClassName, bool pEnable) { return FBLogger::TheOne().Enable(pClassName, pEnable); }
    void DisableClear() { FBLogger::TheOne().DisableClear(); }
    object DumpObject(FBPlug_Wrapper& pObject, int pDepth);

    virtual ~FBLogger_Wrapper( );

	
};
#endif // pyfbprofiler_h__