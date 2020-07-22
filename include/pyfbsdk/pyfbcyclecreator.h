#ifndef pyfbcyclecreator_h__
#define pyfbcyclecreator_h__
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

#include "pyfbtime.h"
#include "pyfbcharacter.h"
#include "pyfbmodel.h"

// =======================================================================================
// FBCycleCreator
// =======================================================================================

void FBCycleCreator_Init();

class PYSDK_DLL FBCycleCreator_Wrapper : public FBComponent_Wrapper {
public:
    FBCycleCreator* mFBCycleCreator;
public:
    FBCycleCreator_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent )  { mFBCycleCreator = (FBCycleCreator*)pFBComponent; }
    FBCycleCreator_Wrapper(  );
    virtual ~FBCycleCreator_Wrapper( );
    bool CreateCycle(   FBTime_Wrapper pStartTime, 
                        FBTime_Wrapper pEndTime,
                        FBCharacter_Wrapper* pChar = NULL, 
                        bool pMoveStartToZero = false,
                        bool pAddZeroKey = true, 
                        const char* pNewTakeName = "", 
                        FBModel_Wrapper* pReferencedIK = NULL, 
                        bool pPasteTx = true, 
                        bool pPasteTy = false,
                        bool pPasteTz = true, 
                        bool pPasteR = true,
                        bool pPasteG = true )
    {
        FBCharacter* lChar = (pChar != NULL) ? ( pChar->mFBCharacter ) : NULL;
        FBModel* lModel = ( pReferencedIK != NULL ) ? ( pReferencedIK->mFBModel ) : NULL;

        return mFBCycleCreator->CreateCycle(pStartTime.Get(), 
                                            pEndTime.Get(),
                                            lChar /*= NULL*/,
                                            pMoveStartToZero /*= false*/, 
                                            pAddZeroKey /*= true */,
                                            pNewTakeName /*= ""*/,
                                            lModel /*= NULL*/,
                                            pPasteTx /*= true*/,
                                            pPasteTy /*= false*/,
                                            pPasteTz /*= true*/,
                                            pPasteR /*= true*/,
                                            pPasteG /*= true*/);
    }
};

#endif // pyfbcyclecreator_h__
