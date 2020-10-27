#ifndef pyfbplotpopup_h__
#define pyfbplotpopup_h__
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

#include "pyfbplotoptions.h"
#include "pyfbvisualcomponent.h"

// =======================================================================================
// FBFCurveEditor
// =======================================================================================
void FBPlotPopup_Init();

class PYSDK_DLL FBPlotPopup_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBPlotPopup* mFBPlotPopup;
public:
	FBPlotPopup_Wrapper( FBComponent* pFBComponent );
	FBPlotPopup_Wrapper();
	virtual ~FBPlotPopup_Wrapper( )								{  }
	
	bool Popup(const char* pWindowName)							{ return mFBPlotPopup->Popup(pWindowName); }
	
	FBPlotOptions_Wrapper* GetPlotOptions()						{ return FBPlotOptions_Wrapper_Factory(mFBPlotPopup->GetPlotOptions()); }
	void SetPlotOptions(FBPlotOptions_Wrapper* pOptions)		{ mFBPlotPopup->SetPlotOptions(*pOptions->mFBPlotOptions); }

	bool GetEnablePlotTranslationOnRootOnly()					{ return (bool)mFBPlotPopup->EnablePlotTranslationOnRootOnly; }
	void SetEnablePlotTranslationOnRootOnly(bool pEnable)		{ mFBPlotPopup->EnablePlotTranslationOnRootOnly = pEnable; }
	
	bool GetEnableSmartPlotControls()							{ return (bool)mFBPlotPopup->EnableSmartPlotControls; }
	void SetEnableSmartPlotControls(bool pEnable)				{ mFBPlotPopup->EnableSmartPlotControls = pEnable; }
	
	bool GetEnablePlotCharacterExtension()						{ return (bool)mFBPlotPopup->EnablePlotCharacterExtension; }
	void SetEnablePlotCharacterExtension(bool pEnable)			{ mFBPlotPopup->EnablePlotCharacterExtension = pEnable; }
	
	bool GetEnablePlotLockedProperties()						{ return (bool)mFBPlotPopup->EnablePlotLockedProperties; }
	void SetEnablePlotLockedProperties(bool pEnable)			{ mFBPlotPopup->EnablePlotLockedProperties = pEnable; }

	bool GetEnablePlotAuxEffectors()							{ return (bool)mFBPlotPopup->EnablePlotAuxEffectors; }
	void SetEnablePlotAuxEffectors(bool pEnable)				{ mFBPlotPopup->EnablePlotAuxEffectors = pEnable; }

	bool GetEnableEvaluateDeformation()							{ return (bool)mFBPlotPopup->EnableEvaluateDeformation; }
	void SetEnableEvaluateDeformation(bool pEnable)				{ mFBPlotPopup->EnableEvaluateDeformation = pEnable; }
};
#endif // pyfbplotpopup_h__