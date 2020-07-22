#ifndef pyfbstoryclipghost_h__
#define pyfbstoryclipghost_h__
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

#include "pyfbmatrix.h"
#include "pyfbplotoptions.h"
#include "pyfbevaluateinfo.h"
#include "pyfbconstraintinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbtake.h"
#include "pyfbgeometry.h"
#include "pyfbvideo.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"
#include "pyfbpose.h"
#include "pyfbconstraint.h"
#include "pyfbcamera.h"
#include "pyfbmodelmarker.h"
#include "pyfbmodelskeleton.h"
#include "pyfbmarkerset.h"
#include "pyfbskeletonstate.h"
#include "pyfbactor.h"
#include "pyfbactorface.h"
#include "pyfbkeyinggroup.h"
#include "pyfbobjectposeoptions.h"
#include "pyfbobjectposemirroroptions.h"
#include "pyfbobjectpose.h"
#include "pyfbcharacterextension.h"
#include "pyfbcharactersolver.h"
#include "pyfbcharacter.h"
#include "pyfbcharacterface.h"			// Requires FBModelList_Wrapper from pyfbarraytemplate.h
#include "pyfbcharacterposeoptions.h"
#include "pyfbcharacterpose.h"
#include "pyfbcontrolset.h"
#include "pyfbstoryfolder.h"
#include "pyfbstorytrack.h"
#include "pyfbstoryclip.h"

// =======================================================================================
// FBStoryGroupClip
// =======================================================================================
void FBStoryGroupClip_Init();

class PYSDK_DLL FBStoryGroupClip_Wrapper : public FBComponent_Wrapper {
public:
	FBStoryGroupClip* mFBStoryClip;
public:
	FBStoryGroupClip_Wrapper( FBComponent* pFBComponent ) : FBComponent_Wrapper( pFBComponent ) { mFBStoryClip = (FBStoryGroupClip*)pFBComponent; }
	FBStoryGroupClip_Wrapper( list pClipList ) : FBComponent_Wrapper( new FBStoryGroupClip( ExtractClip(pClipList) )) { mFBStoryClip = (FBStoryGroupClip*)mFBComponent; }
	virtual ~FBStoryGroupClip_Wrapper( ) {}
	void FBDelete() { mFBStoryClip->FBDelete(  ); }
    
    FBArrayTemplate<FBStoryClip*>* ExtractClip (list plist) 
    { 
        if (plist)
        {
			int lcount = extract<int>(plist.attr("__len__")()); 
			FBArrayTemplate<FBStoryClip*>* lClipArray = new FBArrayTemplate<FBStoryClip*>;
			for ( int i = 0; i < lcount; i++ )
			{
				object lObject = plist[i];
				extract<FBStoryClip_Wrapper*> lExtractor(lObject);
				if(lExtractor.check())
				{
					lClipArray->Add(lExtractor()->mFBStoryClip);
				}
			}
			return lClipArray;
		}
		return NULL;
    }

	FBTime_Wrapper* Move(FBTime_Wrapper& pDelta, bool pForce = true) { return FBTime_Wrapper_Factory( mFBStoryClip->Move( *pDelta.mFBTime, pForce )); }
	FBTime_Wrapper* MoveTo(FBTime_Wrapper& pTime, bool pForce = true) { return FBTime_Wrapper_Factory( mFBStoryClip->MoveTo( *pTime.mFBTime, pForce )); }
	void Razor(FBTime_Wrapper& pTime) { mFBStoryClip->Razor( *pTime.mFBTime ); }
	void SetStart( FBTime_Wrapper& pStart ) { mFBStoryClip->Start = *pStart.mFBTime; }
	FBTime_Wrapper* GetStart(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->Start ); }
	void SetStop( FBTime_Wrapper& pStop ) { mFBStoryClip->Stop = *pStop.mFBTime; }
	FBTime_Wrapper* GetStop(  ) { return FBTime_Wrapper_Factory( mFBStoryClip->Stop ); }
	object GetDependentClips(  ) { return WrapFBObject<FBPropertyListObject_Wrapper,FBPropertyListObject>( &mFBStoryClip->DependentClips ); }
};
#endif // pyfbstoryclip_h__
