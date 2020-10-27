#ifndef pyfbanimationstack_h__
#define pyfbanimationstack_h__
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
// FBAnimationStack
// =======================================================================================
void FBAnimationStack_Init();

class PYSDK_DLL FBAnimationStack_Wrapper : public FBComponent_Wrapper {
public:
	FBAnimationStack* mFBAnimationStack;
public:
	FBAnimationStack_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAnimationStack = (FBAnimationStack*)pFBComponent; }
	FBAnimationStack_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBAnimationStack( pName )) { mFBAnimationStack = (FBAnimationStack*)mFBComponent; }
	virtual ~FBAnimationStack_Wrapper( ) {}
	void	FBDelete() { mFBAnimationStack->FBDelete(  ); }
};
#endif // pyfbanimationstack_h__
