#ifndef pyfbpropertyconnectioneditor_h__
#define pyfbpropertyconnectioneditor_h__
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

// =======================================================================================
// FBPropertyConnectionEditor
// =======================================================================================
void FBPropertyConnectionEditor_Init();

class PYSDK_DLL FBPropertyConnectionEditor_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBPropertyConnectionEditor* mFBPropertyConnectionEditor;
public:
	FBPropertyConnectionEditor_Wrapper( FBComponent* pFBComponent );
	FBPropertyConnectionEditor_Wrapper();
	virtual ~FBPropertyConnectionEditor_Wrapper( ) {  }
	void SetProperty( FBProperty_Wrapper* pProperty );
	object GetProperty(  ) { return FBProperty_Wrapper_Factory( static_cast<FBProperty*>(mFBPropertyConnectionEditor->Property) ); }
	void PopupTree() { mFBPropertyConnectionEditor->PopupTree( ); }
	void PopupList() { mFBPropertyConnectionEditor->PopupList( ); }
};
#endif // pyfbpropertyconnectioneditor_h__