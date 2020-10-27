#ifndef pyfbkeycontrol_h__
#define pyfbkeycontrol_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#include "pyfbarraytemplate.h"

#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

// =======================================================================================
// FBKeyControl
// =======================================================================================
void FBKeyControl_Init();

class PYSDK_DLL FBKeyControl_Wrapper : public FBComponent_Wrapper {
public:
	FBKeyControl* mFBKeyControl;
public:
	FBKeyControl_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBKeyControl = (FBKeyControl*)pFBComponent; }
	FBKeyControl_Wrapper(  ) : FBComponent_Wrapper( new FBKeyControl(  )) { mFBKeyControl = (FBKeyControl*)mFBComponent; SetAllocated(); }
	virtual ~FBKeyControl_Wrapper( ) {}
	void SetAutoKey( bool pAutoKey ) { mFBKeyControl->AutoKey = pAutoKey; }
	bool GetAutoKey(  ) { return mFBKeyControl->AutoKey; }
    void MoveKeys( FBTimeSpan_Wrapper &pTimeSpan, FBModel_Wrapper &pPivot, FBVector3d_Wrapper &pT, FBVector3d_Wrapper &pR, FBVector3d_Wrapper &pS, FBTime_Wrapper &pTime, FBModelList_Wrapper *pModelList = NULL) 
    { 
        mFBKeyControl->MoveKeys( *pTimeSpan.mFBTimeSpan, pPivot.mFBModel, *pT.mFBVector3d, *pR.mFBVector3d, *pS.mFBVector3d, *pTime.mFBTime, pModelList ? pModelList->mFBModelList : NULL ); 
    }
	void SetNewKeyInterpolationType(FBNewKeyInterpolationType pInterpolation) { mFBKeyControl->NewKeyInterpolationType = pInterpolation; }
	FBNewKeyInterpolationType GetNewKeyInterpolationType() { return mFBKeyControl->NewKeyInterpolationType; }
};
#endif // pyfbkeycontrol_h__