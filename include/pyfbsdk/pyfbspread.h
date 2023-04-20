#ifndef pyfbspread_h__
#define pyfbspread_h__
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
#include "pyfbspreadrow.h"
#include "pyfbspreadcolumn.h"
#include "pyfbspreadcell.h"

// =======================================================================================
// FBSpread
// =======================================================================================
void FBSpread_Init();

class PYSDK_DLL FBSpread_Wrapper : public FBVisualComponent_Wrapper {
public:
	FBSpread* mFBSpread;
public:
	FBSpread_Wrapper( FBComponent* pFBComponent );
	FBSpread_Wrapper();
	virtual ~FBSpread_Wrapper( ) {  }
	void Clear() { mFBSpread->Clear(  ); }
	void Home() { mFBSpread->Home(  ); }
	void ColumnAdd(const char * pString, kReference pRef = 0) { mFBSpread->ColumnAdd( pString, pRef ); }

	object GetSpreadCell(kReference pRef, int pColumn);
    object GetCellValue(kReference pRef, int pColumn);
	object GetCellView(kReference pRef, int pColumn);
	object GetColumn(int pColumn);
	object GetCurrentCell();
	object GetRow(kReference pRef);

	void RowAdd(const char * pString, kReference pRef = 0) { mFBSpread->RowAdd( pString, pRef ); }
	void RowSort(bool pAscending = true) { mFBSpread->RowSort( pAscending ); }
	void SetCellValue(kReference pRef, int pColumn, object);
	void SetCellView(kReference pRef, int pColumn, FBVisualComponent_Wrapper& pView);
	void SetCaption( const char* pCaption ) { mFBSpread->Caption = pCaption; }
	const char* GetCaption(  ) { return mFBSpread->Caption; }
	void SetColumn( int pColumn ) { mFBSpread->Column = pColumn; }
	int GetColumn(  ) { return mFBSpread->Column; }
	void SetMultiSelect( bool pMultiSelect ) { mFBSpread->MultiSelect = pMultiSelect; }
	bool GetMultiSelect(  ) { return mFBSpread->MultiSelect; }
	void SetRow( kReference pRow ) { mFBSpread->Row = pRow; }
	kReference GetRow(  ) { return mFBSpread->Row; }

    object OnCellChange();
    object OnRowClick();
    object OnColumnClick();
    object OnDragAndDrop();
protected:
    virtual FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbspread_h__