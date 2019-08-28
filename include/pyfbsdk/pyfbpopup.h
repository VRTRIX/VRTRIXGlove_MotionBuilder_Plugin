#ifndef pyfbpopup_h__
#define pyfbpopup_h__
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
#include "pyfblayout.h"

// =======================================================================================
// FBPopup
// =======================================================================================
void FBPopup_Init();

class PYSDK_DLL FBPopup_Wrapper : public FBLayout_Wrapper {
public:
	FBPopup* mFBPopup;
public:
	FBPopup_Wrapper( FBComponent* pFBComponent );
	FBPopup_Wrapper();
	virtual ~FBPopup_Wrapper( );
	void SetCaption( const char* pCaption );
	const char* GetCaption(  );
	void SetModal( bool pModal );
	bool IsModal(  );
    void Show(FBVisualComponent_Wrapper* pParent = NULL );
    void Close(bool pOk );

    virtual void SetLeft( int pLeft );
    virtual int  GetLeft(  );
    virtual void SetTop( int pTop );
    virtual int  GetTop(  );
    virtual void SetWidth( int pWidth );
    virtual int  GetWidth(  );
    virtual void SetHeight( int pHeight );
    virtual int  GetHeight(  );
};
#endif // pyfbpopup_h__

