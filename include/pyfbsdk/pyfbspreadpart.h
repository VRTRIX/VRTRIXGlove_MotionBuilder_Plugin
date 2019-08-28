#ifndef pyfbspreadpart_h__
#define pyfbspreadpart_h__
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
// FBSpreadPart
// =======================================================================================
void FBSpreadPart_Init();

class FBSpreadPart_Wrapper;

class PYSDK_DLL FBSpreadPart_Wrapper : public FBComponent_Wrapper {
public:
	FBSpreadPart* mFBSpreadPart;
public:
	virtual ~FBSpreadPart_Wrapper( ) { mFBSpreadPart = 0; }
	int GetColumn(  ) { return mFBSpreadPart->Column; }
	void SetEnabled( bool pEnabled ) { mFBSpreadPart->Enabled = pEnabled; }
	bool GetEnabled(  ) { return mFBSpreadPart->Enabled; }
	void SetJustify( FBTextJustify pJustify ) { mFBSpreadPart->Justify = pJustify; }
	FBTextJustify GetJustify(  ) { return mFBSpreadPart->Justify; }
	void SetReadOnly( bool pReadOnly ) { mFBSpreadPart->ReadOnly = pReadOnly; }
	bool GetReadOnly(  ) { return mFBSpreadPart->ReadOnly; }
	int GetRow(  ) { return mFBSpreadPart->Row; }
	void SetStyle( FBCellStyle pStyle ) { mFBSpreadPart->Style = pStyle; }
	FBCellStyle GetStyle(  ) { return mFBSpreadPart->Style; }

    virtual void ContentDestroy();
protected:

	FBSpreadPart_Wrapper( FBSpreadPart* pFBComponent );
    FBSpread* GetSpread() { return mFBSpreadPart->GetSpread(); }
};
#endif // pyfbspreadpart_h__