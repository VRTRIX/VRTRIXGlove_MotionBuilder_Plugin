#ifndef pyfbcharacterpose_h__
#define pyfbcharacterpose_h__
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
// FBCharacterPose
// =======================================================================================
void FBCharacterPose_Init();

class PYSDK_DLL FBCharacterPose_Wrapper : public FBPose_Wrapper {
public:
	FBCharacterPose* mFBCharacterPose;
public:
	FBCharacterPose_Wrapper( FBComponent* pFBComponent ) : FBPose_Wrapper( pFBComponent ) { mFBCharacterPose = (FBCharacterPose*)pFBComponent; }
	FBCharacterPose_Wrapper( const char* pName ) : FBPose_Wrapper( new FBCharacterPose( pName )) { mFBCharacterPose = (FBCharacterPose*)mFBComponent; }
	
	virtual ~FBCharacterPose_Wrapper( ) {}
	void ClearCharacterExtensionsPose() { mFBCharacterPose->ClearCharacterExtensionsPose(  ); }
	void ClearCharacterPose() { mFBCharacterPose->ClearCharacterPose(  ); }
	void ClearPose() { mFBCharacterPose->ClearPose(  ); }
	void CopyFrom(FBCharacterPose_Wrapper& pFromPose) { mFBCharacterPose->CopyFrom( *(pFromPose.mFBCharacterPose) ); }
	void CopyPose(FBCharacter_Wrapper& pCharacter) { mFBCharacterPose->CopyPose( *(pCharacter.mFBCharacter) ); }
	void CopyPoseCharacter(FBCharacter_Wrapper& pCharacter) { mFBCharacterPose->CopyPoseCharacter( *(pCharacter.mFBCharacter) ); }
	void CopyPoseCharacterExtension(FBCharacterExtension_Wrapper& pCharacterExtension) { mFBCharacterPose->CopyPoseCharacterExtension( *(pCharacterExtension.mFBCharacterExtension) ); }
	void CopyPoseCharacterExtensions(FBCharacter_Wrapper& pCharacter) { mFBCharacterPose->CopyPoseCharacterExtensions( *(pCharacter.mFBCharacter) ); }
	void CopyPoseCharacterExtensionsFrom(FBCharacterPose_Wrapper& pFromPose) { mFBCharacterPose->CopyPoseCharacterExtensionsFrom( *(pFromPose.mFBCharacterPose) ); }
	void CopyPoseCharacterFrom(FBCharacterPose_Wrapper& pFromPose) { mFBCharacterPose->CopyPoseCharacterFrom( *(pFromPose.mFBCharacterPose) ); }
	void CopyPoseDataFrom(FBCharacterPose_Wrapper& pFromPose) { mFBCharacterPose->CopyPoseDataFrom( *(pFromPose.mFBCharacterPose) ); }
	const char* GetCharacterExtensionNameFromPose(FBObjectPose_Wrapper& pCharacterExtensionPose) { return mFBCharacterPose->GetCharacterExtensionNameFromPose( *(pCharacterExtensionPose.mFBObjectPose) ); }
	object GetCharacterExtensionPoseAt(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBCharacterPose_Wrapper::GetCharacterExtensionPoseCount );
        return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacterPose->GetCharacterExtensionPoseAt( pIndex )); 
    }
	object GetCharacterExtensionPose(const char * pCharacterExtensionName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacterPose->GetCharacterExtensionPose( pCharacterExtensionName )); }
	int GetCharacterExtensionPoseCount() { return mFBCharacterPose->GetCharacterExtensionPoseCount(  ); }
	void GetMirrorPlaneEquation(FBVector4d_Wrapper& pMirrorPlaneEquation, FBCharacter_Wrapper& pCharacter, FBCharacterPoseOptions_Wrapper& pCharacterPoseOptions) { mFBCharacterPose->GetMirrorPlaneEquation( *pMirrorPlaneEquation.mFBVector4d, *(pCharacter.mFBCharacter), *(pCharacterPoseOptions.mFBCharacterPoseOptions) ); }
	object GetOrCreateCharacterExtensionPose(const char * pCharacterExtensionName) { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacterPose->GetOrCreateCharacterExtensionPose( pCharacterExtensionName )); }
	bool IsCharacterExtensionPoseStored(const char * pCharacterExtensionName) { return mFBCharacterPose->IsCharacterExtensionPoseStored( pCharacterExtensionName ); }
	bool IsCharacterPoseStored() { return mFBCharacterPose->IsCharacterPoseStored(  ); }
	void PastePose(FBCharacter_Wrapper& pCharacter, FBCharacterPoseOptions_Wrapper& pCharacterPoseOptions) { mFBCharacterPose->PastePose( *(pCharacter.mFBCharacter), *(pCharacterPoseOptions.mFBCharacterPoseOptions) ); }
	void PastePoseCharacter(FBCharacter_Wrapper& pCharacter, FBCharacterPoseOptions_Wrapper& pCharacterPoseOptions) { mFBCharacterPose->PastePoseCharacter( *(pCharacter.mFBCharacter), *(pCharacterPoseOptions.mFBCharacterPoseOptions) ); }
	void PastePoseCharacterExtension(FBCharacterExtension_Wrapper& pCharacterExtension, FBCharacterPoseOptions_Wrapper& pCharacterPoseOptions) { mFBCharacterPose->PastePoseCharacterExtension( *(pCharacterExtension.mFBCharacterExtension), *(pCharacterPoseOptions.mFBCharacterPoseOptions) ); }
	void PastePoseCharacterExtensions(FBCharacter_Wrapper& pCharacter, FBCharacterPoseOptions_Wrapper& pCharacterPoseOptions) { mFBCharacterPose->PastePoseCharacterExtensions( *(pCharacter.mFBCharacter), *(pCharacterPoseOptions.mFBCharacterPoseOptions) ); }
	void RemoveCharacterExtensionPoseAt(int pIndex) 
    { 
        ValidateIndexAccess( pIndex, this, &FBCharacterPose_Wrapper::GetCharacterExtensionPoseCount );
        mFBCharacterPose->RemoveCharacterExtensionPoseAt( pIndex ); 
    }
	void RemoveCharacterExtensionPose(const char * pCharacterExtensionName) { mFBCharacterPose->RemoveCharacterExtensionPose( pCharacterExtensionName ); }
    void GetExtraBoneTransform(FBVector3d_Wrapper &pT, FBVector3d_Wrapper &pR, FBVector3d_Wrapper &pS, int pIndex ) { mFBCharacterPose->GetExtraBoneTransform( *(pT.mFBVector3d), *(pR.mFBVector3d), *(pS.mFBVector3d), pIndex ); }
    void GetExtraBoneTransformOffset(FBVector3d_Wrapper &pT, FBVector3d_Wrapper &pR, FBVector3d_Wrapper &pS, int pIndex ) { mFBCharacterPose->GetExtraBoneTransformOffset( *(pT.mFBVector3d), *(pR.mFBVector3d), *(pS.mFBVector3d), pIndex ); }
    void GetExtraBoneParentRotationOffset( FBVector3d_Wrapper &pR, int pIndex ) { mFBCharacterPose->GetExtraBoneParentRotationOffset( *(pR.mFBVector3d), pIndex ); }
    void ApplyPoseCandidate() { mFBCharacterPose->ApplyPoseCandidate( ); }
    //ExtraBones
    list GetExtraBones() 
    {
        list lReturnList;
        for(int index = 0; index<mFBCharacterPose->GetExtraBoneCount();index++)
        {
            lReturnList.append(FBWrapperFactory::TheOne().WrapFBObject(mFBCharacterPose->GetExtraBoneModelAt(index)));
        }
        return lReturnList;
    }
};
#endif // pyfbcharacterpose_h__