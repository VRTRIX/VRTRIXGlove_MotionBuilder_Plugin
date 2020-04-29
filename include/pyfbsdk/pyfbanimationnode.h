#ifndef pyfbanimationnode_h__
#define pyfbanimationnode_h__
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

#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"

// =======================================================================================
// FBAnimationNode
// =======================================================================================
void FBAnimationNode_Init();


class PYSDK_DLL FBAnimationNode_Wrapper : public FBComponent_Wrapper {
public:
	FBAnimationNode* mFBAnimationNode;
public:
	FBAnimationNode_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAnimationNode = (FBAnimationNode*)pFBComponent; }
	FBAnimationNode_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBAnimationNode( pName )) { mFBAnimationNode = (FBAnimationNode*)mFBComponent; }
	virtual ~FBAnimationNode_Wrapper( ) {}
	const char* GetLabel();
	void  SetLabel(const char* pLabelName);

	FBTime_Wrapper* ConvertGlobalToNodeTime(FBTime_Wrapper& pKeyTime) { return FBTime_Wrapper_Factory( mFBAnimationNode->ConvertGlobalToNodeTime( *(pKeyTime.mFBTime) )); }
	FBTime_Wrapper* ConvertNodeToGlobalTime(FBTime_Wrapper& pKeyTime) { return FBTime_Wrapper_Factory( mFBAnimationNode->ConvertNodeToGlobalTime( *(pKeyTime.mFBTime) )); }
	object GetAnimationToRecord() { return FBWrapperFactory::TheOne().WrapFBObject( mFBAnimationNode->GetAnimationToRecord(  )); }
	object GetAnimationToPlay() { return FBWrapperFactory::TheOne().WrapFBObject( mFBAnimationNode->GetAnimationToPlay(  )); }
	int  GetDataDoubleArrayCount() { return mFBAnimationNode->GetDataDoubleArrayCount(  ); }
	int  GetSizeOfData() { return mFBAnimationNode->GetSizeOfData(  ); }
	bool IsKey() { return mFBAnimationNode->IsKey(  ); }
	void KeyAdd(const FBTime_Wrapper& pTime, double pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto);
	void KeyAdd(double pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto);
	void KeyAdd(const FBTime_Wrapper& pTime, list pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto);
	void KeyAdd(list pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto);
	void KeyCandidate() { mFBAnimationNode->KeyCandidate(  ); }
	void KeyCandidate(FBTime_Wrapper& pTime) { mFBAnimationNode->KeyCandidate( *(pTime.mFBTime) ); }
	void KeyRemove() { mFBAnimationNode->KeyRemove(  ); }
	void KeyRemoveAt(FBTime_Wrapper& pTime) { mFBAnimationNode->KeyRemoveAt( *(pTime.mFBTime) ); }
	bool SetCandidate(list pData, bool pCheckLocked = false);
	void SetBufferType(bool pGlobal){ mFBAnimationNode->SetBufferType(pGlobal); }
	list ReadData_1( FBEvaluateInfo_Wrapper* pEvaluateInfo = NULL, bool pConvertGlobalToLocal = false );
	list ReadData_2( const FBTime_Wrapper& pTime, bool pConvertGlobalToLocal = false );
	list ReadLastEvalData();
	FBAnimationNodeConnectorType GetConnectorType() { return mFBAnimationNode->ConnectorType; }
	int  WriteData(list pData, FBEvaluateInfo_Wrapper* pEvaluateInfo = NULL);
    void SetFCurve( FBFCurve_Wrapper& pFCurve ) { mFBAnimationNode->FCurve = pFCurve.mFBFCurve; }
	object GetFCurve(  ) { return FBWrapperFactory::TheOne().WrapFBObject( mFBAnimationNode->FCurve ); }
	int  GetKeyCount(  ) { return mFBAnimationNode->KeyCount; }
	void SetLive( bool pLive ) { mFBAnimationNode->Live = pLive; }
	bool GetLive(  ) { return mFBAnimationNode->Live; }
	object GetNodes(  ) { return FBPropertyListAnimationNode_Wrapper_Factory( mFBAnimationNode->Nodes ); }
	//void SetOnChange( FBEventAnimationNode_Wrapper* pOnChange ) { mFBAnimationNode->OnChange = *(pOnChange->mFBEventAnimationNode); }
	//FBEventAnimationNode_Wrapper* GetOnChange(  ) { return FBEventAnimationNode_Wrapper_Factory( mFBAnimationNode->OnChange ); }
	void SetRecordMode( bool pRecordMode ) { mFBAnimationNode->RecordMode = pRecordMode; }
	bool GetRecordMode(  ) { return mFBAnimationNode->RecordMode; }
//	void SetReference( FBkReference pReference ) { mFBAnimationNode->Reference = pReference; }
//	FBkReference GetReference(  ) { return mFBAnimationNode->Reference; }
	const char* GetUserName(  ) { return mFBAnimationNode->UserName; }
	void SetDefaultInterpolation( FBInterpolation pInterpolation ) { mFBAnimationNode->DefaultInterpolation = pInterpolation; }
	FBInterpolation GetDefaultInterpolation(  ) { return mFBAnimationNode->DefaultInterpolation; }
    void KeyAdd_1(const FBTime_Wrapper& pTime, double pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto);
	void KeyAdd_2(double pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto);
	void KeyAdd_3(const FBTime_Wrapper& pTime, list pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto);
	void KeyAdd_4(list pData, FBInterpolation pInterpolation=kFBInterpolationCubic, FBTangentMode pTangentMode=kFBTangentModeAuto);
};
#endif // pyfbanimationnode_h__
