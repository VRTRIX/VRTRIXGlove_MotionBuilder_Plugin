#ifndef pyfbgenericmenu_h__
#define pyfbgenericmenu_h__
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

#include "pyfbgenericmenuitem.h"

// =======================================================================================
// FBGenericMenu
// =======================================================================================
void FBGenericMenu_Init();

class PYSDK_DLL FBGenericMenu_Wrapper : public FBComponent_Wrapper {
public:
	FBGenericMenu* mFBGenericMenu;
public:
    FBGenericMenu_Wrapper(FBComponent* pComponent);
    FBGenericMenu_Wrapper();

	void FBDelete();

    object GetFirstItem();
    object GetLastItem();
    object GetNextItem(FBGenericMenuItem_Wrapper&);
    object GetPrevItem(FBGenericMenuItem_Wrapper&);

    object GetItem( int pItemId );

    object InsertFirst(const char* pItemName, int pItemId, FBGenericMenu_Wrapper* pMenu = NULL);
    object InsertLast(const char* pItemName, int pItemId, FBGenericMenu_Wrapper* pMenu = NULL);
    object InsertAfter(FBGenericMenuItem_Wrapper& pAfterItem, const char* pItemName, int pItemId, FBGenericMenu_Wrapper* pMenu = NULL);
    object InsertBefore(FBGenericMenuItem_Wrapper& pBeforeItem, const char* pItemName, int pItemId, FBGenericMenu_Wrapper* pMenu = NULL);

    void DeleteItem(FBGenericMenuItem_Wrapper&);

    object Execute(int pX, int pY, bool pRightAlign = true);

    object OnMenuActivate();
protected:
    FBPropertyEvent* GetPropertyEvent(FBEventName pEventName);
};
#endif // pyfbgenericmenu_h__

