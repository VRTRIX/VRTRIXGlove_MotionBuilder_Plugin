#ifndef pyfbtool_h__
#define pyfbtool_h__
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

#include "pyfbvisualcomponent.h"
#include "pyfblayout.h"

// =======================================================================================
// FBTool
// =======================================================================================
void FBTool_Init();

class PYSDK_DLL FBTool_Wrapper : public FBLayout_Wrapper {
public:
	FBTool* mFBTool;
public:
	FBTool_Wrapper( FBComponent* pFBComponent ) : FBLayout_Wrapper( pFBComponent ) { mFBTool = (FBTool*)pFBComponent; }
	FBTool_Wrapper( const char* pName, bool pRegisterTool = true );	
    ~FBTool_Wrapper();	

    void SetStartSizeX(int pX) { mFBTool->StartSize[0] = pX; }
    void SetStartSizeY(int pY) { mFBTool->StartSize[1] = pY; }
    void SetMinSizeX(int pX) { mFBTool->MinSize[0] = pX; }
    void SetMinSizeY(int pY) { mFBTool->MinSize[1] = pY; }
    void SetMaxSizeX(int pX) { mFBTool->MaxSize[0] = pX; }
    void SetMaxSizeY(int pY) { mFBTool->MaxSize[1] = pY; }
    void SetStartPosX(int pX) { mFBTool->StartPos[0] = pX; }
    void SetStartPosY(int pY) { mFBTool->StartPos[1] = pY; }
    int GetStartSizeX() { return mFBTool->StartSize[0]; }
    int GetStartSizeY() { return mFBTool->StartSize[1]; }
    int GetMinSizeX() { return mFBTool->MinSize[0]; }
    int GetMinSizeY() { return mFBTool->MinSize[1]; }
    int GetMaxSizeX() { return mFBTool->MaxSize[0]; }
    int GetMaxSizeY() { return mFBTool->MaxSize[1]; }
    int GetStartPosX() { return mFBTool->StartPos[0]; }
    int GetStartPosY() { return mFBTool->StartPos[1]; }
    const char* GetToolName() { return mFBTool->Name; }
	FBToolPossibleDockPosition GetPossibleDockPosition() { return mFBTool->GetPossibleDockPosition(); }
	void SetPossibleDockPosition(FBToolPossibleDockPosition pFlags) { mFBTool->SetPossibleDockPosition(pFlags); }
};
#endif // pyfbtool_h__