#ifndef pyfbaudioclip_h__
#define pyfbaudioclip_h__
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

#include "pyfbaudioout.h"
#include "pyfbtake.h"

// =======================================================================================
// FBAudioClip
// =======================================================================================
void FBAudioClip_Init();

class PYSDK_DLL FBAudioClip_Wrapper : public FBComponent_Wrapper {
public:
    FBAudioClip* mFBAudioClip;
public:
    FBAudioClip_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBAudioClip = (FBAudioClip*)pFBComponent; }
    FBAudioClip_Wrapper( const char* pName ) : FBComponent_Wrapper( new FBAudioClip( pName ))
    {
        if ( mFBComponent->mDummyObject != NULL )
        {
            throw( "Error occurred when creating FBAudioClip!" );
        }

        mFBAudioClip = (FBAudioClip*)mFBComponent; 
    }

    virtual ~FBAudioClip_Wrapper( ) { }
    void FBDelete() { mFBAudioClip->FBDelete(  ); }

    bool IsMediaReady() { return mFBAudioClip->IsMediaReady(); }
    bool Play(FBTriggerStyle pStyle = kFBTriggerStyleContinue, FBAudioOut_Wrapper* pDestination = NULL) { return mFBAudioClip->Play( pStyle, pDestination ? pDestination->mFBAudioOut : NULL); }
    void Stop(FBAudioOut_Wrapper* pDestination = NULL) { mFBAudioClip->Stop( pDestination ? pDestination->mFBAudioOut : NULL ); }


    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( FBAudioClip, Path, const char* );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY_DEPRECATED( FBAudioClip, Filename, const char* );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( FBAudioClip, RelativePath, const char* );

    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( FBAudioClip, Format, int );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( FBAudioClip, Bits, int );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( FBAudioClip, Rate, int );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY( FBAudioClip, Channels, int );

    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBAudioClip, AccessMode, FBAccessMode );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBAudioClip, UseChannel, FBUseChnMode );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_READONLY_DEPRECATED( FBAudioClip, UseChannelMode, FBUseChnMode );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBAudioClip, ClipSpeed, double );

    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY( FBAudioClip, SrcIn,  FBTime );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY( FBAudioClip, SrcDuration, FBTime );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_READONLY( FBAudioClip, SrcEnd,  FBTime );

    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS( FBAudioClip, DstIn,  FBTime );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_DEPRECATED( FBAudioClip, InPoint,  FBTime );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS( FBAudioClip, DstDuration,  FBTime );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_DEPRECATED( FBAudioClip, Duration, FBTime );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS( FBAudioClip, DstEnd,  FBTime );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_CUSTOM_TYPE_ACCESS_DEPRECATED( FBAudioClip, EndPoint, FBTime );

	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBAudioClip, ConstrainDstToTake,	bool );
	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS_DEPRECATED( FBAudioClip, TakeSetsInPoint,	bool );
	DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBAudioClip, Scrubbing,			bool );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBAudioClip, LockClipSpeed,		bool );

    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBAudioClip, Pitch,                double );
    DECLARE_DEFINE_ORSDK_PROPERTY_PYTHON_ACCESS( FBAudioClip, LockPitchToSpeed,     bool ); 

    void        SetCurrentTake  ( object pTake );
    object      GetCurrentTake  ( void );

    void        SetDestination  ( object pDestination );
    object      GetDestination  ( void );
};
#endif // pyfbaudioclip_h__
