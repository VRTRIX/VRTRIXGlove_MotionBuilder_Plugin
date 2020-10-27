/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file keventbase.h
#ifndef _FBXSDK_SCENE_ANIMATION_KFCURVE_EVENTBASE_H_
#define _FBXSDK_SCENE_ANIMATION_KFCURVE_EVENTBASE_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

#define K_EVENT_BASE 0x200

class KEventBase;

#define K_EVENT_NONE			0x000
#define K_EVENT_VALUE_CHANGED	0x206

typedef  int   kEventType;

/** Base class for event management.
  */
class FBXSDK_DLL KEventBase
{
protected:
    kEventType mType;
    bool       mBreakEvent;

public:
    KEventBase()			{ mType = K_EVENT_BASE; mBreakEvent = false; }
    kEventType GetType() const	{ return mType; }

    /** Stop treating event. 
      */
    void    SetBreakEvent()  {  mBreakEvent = true;}

    /** Get break event. 
      * \return \c true if event are not going to be treated next, false otherwise.
      */
    bool    GetBreakEvent() const { return mBreakEvent; } 

};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_ANIMATION_KFCURVE_EVENTBASE_H_ */
