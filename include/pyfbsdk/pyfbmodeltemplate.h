#ifndef pyfbmodeltemplate_h__
#define pyfbmodeltemplate_h__
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
#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbboxplaceholder.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbmodelplaceholder.h"

// =======================================================================================
// FBModelTemplate
// =======================================================================================
void FBModelTemplate_Init();

class PYSDK_DLL FBModelTemplate_Wrapper : public FBComponent_Wrapper {
public:
	FBModelTemplate* mFBModelTemplate;
public:
	FBModelTemplate_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBModelTemplate = (FBModelTemplate*)pFBComponent; }
	virtual ~FBModelTemplate_Wrapper( ) {}
	object GetBindings(  ) { return FBPropertyListModelTemplateBinding_Wrapper_Factory( mFBModelTemplate->Bindings ); }
	object GetChildren(  ) { return FBPropertyListModelTemplate_Wrapper_Factory( mFBModelTemplate->Children ); }
	void SetDefaultRotation( FBVector3d_Wrapper& pDefaultRotation ) { mFBModelTemplate->DefaultRotation = *pDefaultRotation.mFBVector3d; }
	FBVector3d_Wrapper* GetDefaultRotation(  ) { return FBVector3d_Wrapper_Factory( mFBModelTemplate->DefaultRotation ); }
	void SetDefaultScaling( FBVector3d_Wrapper& pDefaultScaling ) { mFBModelTemplate->DefaultScaling = *pDefaultScaling.mFBVector3d; }
	FBVector3d_Wrapper* GetDefaultScaling(  ) { return FBVector3d_Wrapper_Factory( mFBModelTemplate->DefaultScaling ); }
	void SetDefaultTranslation( FBVector3d_Wrapper& pDefaultTranslation ) { mFBModelTemplate->DefaultTranslation = *pDefaultTranslation.mFBVector3d; }
	FBVector3d_Wrapper* GetDefaultTranslation(  ) { return FBVector3d_Wrapper_Factory( mFBModelTemplate->DefaultTranslation ); }
	void SetModel( FBModel_Wrapper& pModel ) { mFBModelTemplate->Model = pModel.mFBModel; }
	object GetModel(  ) { return FBModel_Wrapper_Factory( mFBModelTemplate->Model ); }
	void SetPrefix( const char* pPrefix ) { mFBModelTemplate->Prefix = pPrefix; }
	const char* GetPrefix(  ) { return mFBModelTemplate->Prefix; }
};
#endif // pyfbmodeltemplate_h__