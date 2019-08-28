#ifndef pyfbspreadcell_h__
#define pyfbspreadcell_h__
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
// FBSpreadCell
// =======================================================================================
void FBSpreadCell_Init();

class FBSpread_Wrapper;
class PYSDK_DLL FBSpreadCell_Wrapper : public FBSpreadPart_Wrapper {
public:
	FBSpreadCell* mFBSpreadCell;
public:	
	FBSpreadCell_Wrapper( FBSpread_Wrapper* pSpread, int pRow, int pCol );
    ~FBSpreadCell_Wrapper() { delete mFBSpreadCell; }
};
#endif // pyfbspreadcell_h__