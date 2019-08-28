#ifndef pyfbcharacterextension_h__
#define pyfbcharacterextension_h__
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

// =======================================================================================
// FBCharacterExtension
// =======================================================================================
void FBCharacterExtension_Init();

class PYSDK_DLL FBCharacterExtension_Wrapper : public FBKeyingGroup_Wrapper {
public:
	FBCharacterExtension* mFBCharacterExtension;
public:
	FBCharacterExtension_Wrapper( FBComponent* pFBComponent ) : FBKeyingGroup_Wrapper( pFBComponent ) { mFBCharacterExtension = (FBCharacterExtension*)pFBComponent; }
	FBCharacterExtension_Wrapper( const char* pName ) : FBKeyingGroup_Wrapper( new FBCharacterExtension( pName )) { mFBCharacterExtension = (FBCharacterExtension*)mFBComponent; }
	virtual ~FBCharacterExtension_Wrapper( ) {}
	void AddObjectProperties(FBComponent_Wrapper& pObj) { mFBCharacterExtension->AddObjectProperties( pObj.mFBComponent ); }
	void FBDelete() { mFBCharacterExtension->FBDelete(  ); }
	object GetCharacter() { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacterExtension->GetCharacter(  )); }
	object GetMirrorExtension() { return FBWrapperFactory::TheOne().WrapFBObject( mFBCharacterExtension->GetMirrorExtension(  )); }
	void GoToStancePose() { mFBCharacterExtension->GoToStancePose(  ); }
	bool IsElementSelected() { return mFBCharacterExtension->IsElementSelected(  ); }
	bool IsPropertyIncluded(FBProperty_Wrapper& pProp) { return mFBCharacterExtension->IsPropertyIncluded( pProp.mFBProperty ); }
	const char* GetLabelNameWithExtensionObject(FBComponent_Wrapper& pObj, bool pReturnObjectNameIfNotFound) { static FBString lObjectLabel; mFBCharacterExtension->GetLabelNameWithExtensionObject(lObjectLabel,pObj.mFBComponent,pReturnObjectNameIfNotFound); return (char*)lObjectLabel; }
	object GetExtensionObjectWithLabelName(const char* pLabelName) { return FBWrapperFactory::TheOne().WrapFBObject(mFBCharacterExtension->GetExtensionObjectWithLabelName(FBString(pLabelName))); }
	void RemoveObjectAndProperties(FBComponent_Wrapper& pObj) { mFBCharacterExtension->RemoveObjectAndProperties( pObj.mFBComponent ); }
	void UpdateStancePose() { mFBCharacterExtension->UpdateStancePose(  ); }
	void SetIncludePartInFullBody( bool pIncludePartInFullBody ) { mFBCharacterExtension->IncludePartInFullBody = pIncludePartInFullBody; }
	bool GetIncludePartInFullBody(  ) { return mFBCharacterExtension->IncludePartInFullBody; }
	void SetLabel( const char* pLabel ) { mFBCharacterExtension->Label = pLabel; }
	const char* GetLabel(  ) { return mFBCharacterExtension->Label; }
	void SetMirrorLabel( int pMirrorLabel ) { mFBCharacterExtension->MirrorLabel = pMirrorLabel; }
	int GetMirrorLabel(  ) { return mFBCharacterExtension->MirrorLabel; }
	void SetPlotAllowed( FBPlotAllowed pPlotAllowed ) { mFBCharacterExtension->PlotAllowed = pPlotAllowed; }
	FBPlotAllowed GetPlotAllowed(  ) { return mFBCharacterExtension->PlotAllowed; }
    void SetReferenceModel( FBModel_Wrapper& pModel) { mFBCharacterExtension->ReferenceModel = pModel.mFBModel; }
    object GetReferenceModel() { return FBModel_Wrapper_Factory(mFBCharacterExtension->ReferenceModel); }
};
#endif // pyfbcharacterextension_gen_h__