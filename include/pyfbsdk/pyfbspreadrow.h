#ifndef pyfbspreadrow_h__
#define pyfbspreadrow_h__
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
#include "pyfbspreadpart.h"
#include "pyfbspread.h"

// =======================================================================================
// FBSpreadRow
// =======================================================================================
void FBSpreadRow_Init();

class FBSpread_Wrapper;
class PYSDK_DLL FBSpreadRow_Wrapper : public FBSpreadPart_Wrapper {
public:
	FBSpreadRow* mFBSpreadRow;
public:	
	FBSpreadRow_Wrapper( FBSpread_Wrapper* pSpread, kReference pRow );
	virtual ~FBSpreadRow_Wrapper( ) { delete mFBSpreadRow; }
	bool EditCaption() { return mFBSpreadRow->EditCaption(  ); }
	void Remove() { mFBSpreadRow->Remove(  ); }
	void SetCaption( const char* pCaption ) { mFBSpreadRow->Caption = pCaption; }
	const char* GetCaption(  ) { return mFBSpreadRow->Caption; }
	void SetParent( kReference pParent ) { mFBSpreadRow->Parent = pParent; }
	kReference GetParent(  ) { return mFBSpreadRow->Parent; }
	void SetRowSelected( bool pSelected ) { mFBSpreadRow->RowSelected = pSelected; }
	bool GetRowSelected(  ) { return mFBSpreadRow->RowSelected; }
};
#endif // pyfbspreadrow_h__