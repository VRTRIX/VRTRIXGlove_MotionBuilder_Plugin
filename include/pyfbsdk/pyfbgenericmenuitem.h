#ifndef pyfbgenericmenuitem_h__
#define pyfbgenericmenuitem_h__
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

// =======================================================================================
// FBDevice
// =======================================================================================
void FBGenericMenuItem_Init();

class PYSDK_DLL FBGenericMenuItem_Wrapper : public FBComponent_Wrapper {
public:
	FBGenericMenuItem* mFBGenericMenuItem;
public:
    FBGenericMenuItem_Wrapper(FBComponent* pComponent)
        : FBComponent_Wrapper(pComponent)
    {
        mFBGenericMenuItem = dynamic_cast<FBGenericMenuItem*>(pComponent);
    }

    const char* GetCaption()
    {
        return mFBGenericMenuItem->Caption;
    }
    void SetCaption(const char* pValue)
    {
        mFBGenericMenuItem->Caption = pValue;
    }
    int GetId()
    {
        return mFBGenericMenuItem->Id;
    }
    void SetId(int pId)
    {
        mFBGenericMenuItem->Id = pId;
    }
    bool GetEnable()
    {
        return mFBGenericMenuItem->Enable;
    }
    void SetEnable(bool pEnable)
    {
        mFBGenericMenuItem->Enable = pEnable;
    }
    object GetMenu()
    {
        return FBWrapperFactory::TheOne().WrapFBObject( mFBGenericMenuItem->Menu );
    }
};
#endif // pyfbgenericmenuitem_h__

