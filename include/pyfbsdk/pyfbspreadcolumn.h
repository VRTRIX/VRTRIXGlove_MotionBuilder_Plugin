#ifndef pyfbspreadcolumn_h__
#define pyfbspreadcolumn_h__
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
// FBSpreadColumn
// =======================================================================================
void FBSpreadColumn_Init();
class FBSpread_Wrapper;
class PYSDK_DLL FBSpreadColumn_Wrapper : public FBSpreadPart_Wrapper {
public:
	FBSpreadColumn* mFBSpreadColumn;
public:    
    FBSpreadColumn_Wrapper( FBSpread_Wrapper* pSpread, int pCol );

	virtual ~FBSpreadColumn_Wrapper( );
	void SetCaption( const char* pCaption );
	const char* GetCaption(  ) { return mFBSpreadColumn->Caption; }
	void SetJustify( FBTextJustify pJustify ) { mFBSpreadColumn->Justify = pJustify; }
	FBTextJustify GetJustify(  ) { return mFBSpreadColumn->Justify; }
	void SetWidth( int pWidth ) { mFBSpreadColumn->Width = pWidth; }
	int GetWidth(  ) { return mFBSpreadColumn->Width; }
};
#endif // pyfbspreadcolumn_h__