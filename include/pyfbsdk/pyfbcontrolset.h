#ifndef pyfbcontrolset_h__
#define pyfbcontrolset_h__
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

#include "pyfbmatrix.h"
#include "pyfbplotoptions.h"
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbpose.h"
#include "pyfbconstraint.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"
#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbactorface.h"
#include "pyfbkeyinggroup.h"
#include "pyfbobjectposeoptions.h"
#include "pyfbobjectposemirroroptions.h"
#include "pyfbobjectpose.h"
#include "pyfbcharacterextension.h"
#include "pyfbcharactersolver.h"
#include "pyfbcharacter.h"
#include "pyfbcharacterface.h"			// Requires FBModelList_Wrapper from pyfbarraytemplate.h
#include "pyfbcharacterposeoptions.h"

// =======================================================================================
// FBControlSet
// =======================================================================================
void FBControlSet_Init();

class PYSDK_DLL FBControlSet_Wrapper : public FBComponent_Wrapper {
public:
	FBControlSet* mFBControlSet;
public:
	FBControlSet_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBControlSet = (FBControlSet*)pFBComponent; }
	FBControlSet_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBControlSet( pName )) { mFBControlSet = (FBControlSet*)mFBComponent; SetAllocated(); }
	virtual ~FBControlSet_Wrapper( ) {}
    FBControlSetType GetControlSetType( ) { return mFBControlSet->ControlSetType; }
    void SetControlSetType( FBControlSetType pControlSetType ) { mFBControlSet->ControlSetType = pControlSetType; }
    object GetReferenceModel( ) { return FBModel_Wrapper_Factory( mFBControlSet->GetReferenceModel() ); }
    const char* GetReferenceName( ) { return mFBControlSet->GetReferenceName(); }
    int	GetIKEffectorIndex(FBModel_Wrapper& pModel) { return mFBControlSet->GetIKEffectorIndex(pModel.mFBModel); }
    object GetIKEffectorModel(FBEffectorId pNodeIndex, int pPivotIndex = 0) { return FBModel_Wrapper_Factory( mFBControlSet->GetIKEffectorModel(pNodeIndex, pPivotIndex) ); }
    int	GetIKEffectorPivotCount(FBEffectorId pEffectorIndex) { return mFBControlSet->GetIKEffectorPivotCount(pEffectorIndex); }
    const char* GetIKEffectorName(FBEffectorId pEffectorIndex) { return mFBControlSet->GetIKEffectorName(pEffectorIndex); }
    int	GetFKIndex(FBModel_Wrapper& pModel) { return mFBControlSet->GetFKIndex(pModel.mFBModel); }
    object GetFKModel(FBBodyNodeId pIndex) { return FBModel_Wrapper_Factory( mFBControlSet->GetFKModel(pIndex) ); }
    const char* GetFKName(FBBodyNodeId pIndex) { return mFBControlSet->GetFKName(pIndex); }
    bool GetUseAxis( ) { return mFBControlSet->UseAxis; }
    void SetUseAxis( bool pUseAxis ) { mFBControlSet->UseAxis = pUseAxis; }
};
#endif // pyfbcontrolset_h__