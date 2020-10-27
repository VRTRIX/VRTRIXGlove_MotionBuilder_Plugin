#ifndef pyfbcallback_h__
#define pyfbcallback_h__
/**************************************************************************
Copyright 2010 Autodesk, Inc.
All rights reserved.

Use of this software is subject to the terms of the Autodesk license agreement
provided at the time of installation or download, or which otherwise accompanies
this software in either electronic or hard copy form.

**************************************************************************/

#include <kaydaradef.h>
#include "pyfbtime.h"
#ifndef PYSDK_DLL
/** \def PYSDK_DLL
*    Be sure that PYSDK_DLL is defined only once...
*/
#define PYSDK_DLL K_DLLIMPORT
#endif

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Events callback handling: 
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void FBCallback_Init();

/** 
These events are used internally by the Python Callback mechanism. These are not meant
to be manipulated by a user.
*/
enum PYSDK_DLL FBEventName
{    
    // Normal FB event to which corresponds an event class
    kFBEventActivate,
    kFBEventShow,    
    kFBEventDragAndDrop,
    kFBEventInput,
    kFBEventMenu,
    kFBEventTreeSelect,    
    kFBEventExpose,
    kFBEventResize,
    kFBEventTransaction,
    kFBEventDoubleClick,
    kFBEventSceneChange,
    kFBEventTakeChange,
    kFBEventFileChangeMainScene,
    kFBEventFileChangeAnimationClip,
    kFBEventFileChangeFileReference,
    kFBEventFileChangePythonEditorScript,
    kFBEventConnectionNotify,
    kFBEventConnectionDataNotify,
    kFBEventConnectionStateNotify,
    kFBEventConnectionKeyingNotify,
    kFBEventHUDDisplay, 

    // Pyfbsdk for Callback processing events (only Type of event change)
    kFBEventOnClick,
    kFBEventOnClickCheck,
    kFBEventEnter,
    kFBEventExit,
    kFBEventIdle,
    kFBEventUIIdle,
    kFBEventVideoFrameRendering,
    kFBEventCallbackEvaluationPipeline,
    kFBEventCallbackRenderPipeline,
    kFBEventCallbackSynchronizationPoint,
    kFBEventChange,
    kFBEventCellChange,
    kFBEventRowClick,
    kFBEventColumnClick,
    kFBEventTreeExpanding,
    kFBEventTreeExpanded,
    kFBEventTreeCollapsing,
    kFBEventTreeCollapsed,
    kFBEventFileNewCompleted,
    kFBEventFileNew,
    kFBEventFileOpenCompleted,
    kFBEventFileOpen,
    kFBEventFileSaveCompleted,
    kFBEventFileSave,
    kFBEventFileExit,    
    kFBEventFileMerge,
    kFBEventUndoCompleted,
    kFBEventUndo,
    kFBEventRedoCompleted,
    kFBEventRedo,
    kFBEventUnbindSDK, 

    // When the time comes for integration into mainline, this should be moved up.
    // This enum is added here for SDK compatibility.
    // Normal FB event to which corresponds an event class
    kFBEventClipChange,
    kFBEventPlayerControlChange,
};

/** 
*  MoBu will auto remove those registered python FBEvent callbacks upon exception caught.
*/
class PYSDK_DLL FBEvent_Wrapper
{
public:
    FBEvent_Wrapper( FBEventName pName )
        : mName( pName )
    {
    }

    FBEventName GetType()const
    {
        return mName;
    }

    FBEventName mName;
};

#ifndef K_DISABLE_UI
/// Base for spread events.
class PYSDK_DLL FBEventSpread_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventSpread_Wrapper( FBEventName pName )
        : FBEvent_Wrapper( pName )
        , mRow( -1 )
        , mColumn( -1 )
        , mAction( -1 )
    {
    }

    int mRow;       ///< Row where the action occured.
    int mColumn;    ///< Column where the action occured.
    int mAction;    ///< Action taken by user.
};

class PYSDK_DLL FBEventTree_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventTree_Wrapper( FBEventName pName, FBEventTreeWhy pWhy )
        : FBEvent_Wrapper( pName )
        , mWhy( pWhy )
        , mTreeNode( 0 )
    {
    }

    FBEventTreeWhy mWhy;        ///< Type of Tree event Wrapper
    object    mTreeNode;        ///< Tree node touched by the event

};
/// Parameter given to callbacks of kFBEventActivate
class PYSDK_DLL FBEventActivate_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventActivate_Wrapper()
        : FBEvent_Wrapper( kFBEventActivate )
    {
    }
    kReference mData; ///< Control specific event data.
} ;

/// Parameter given to callbacks of kFBEventShow
class PYSDK_DLL FBEventShow_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventShow_Wrapper()
        : FBEvent_Wrapper( kFBEventShow )
        , mShown( false )
    {
    }

    bool mShown; ///< Tells if the control is visible now.
};

/// Parameter given to callbacks of kFBEventDragAndDrop
class FBComponent_Wrapper;
class PYSDK_DLL FBEventDragAndDrop_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventDragAndDrop_Wrapper()
        : FBEvent_Wrapper( kFBEventDragAndDrop )
        , mState( kFBDragAndDropBegin )
        , mPosX( -1 )
        , mPosY( -1 )
    {
    }

    void Add( FBComponent_Wrapper* pComponent, int pId = 0 );
    void Clear();
    void Accept();
    object Get(int pIndex);    
    int    GetCount();

    FBDragAndDropState  mState;         ///< Type of drag and drop event.
    int                 mPosX;          ///< X position of the drag.
    int                 mPosY;          ///< Y position of the drag.
    boost::python::list mData;          ///< Position of the drag.        
    boost::python::list mComponents;
};

/// Parameter given to callbacks of kFBEventInput
class PYSDK_DLL FBEventInput_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventInput_Wrapper()
        : FBEvent_Wrapper( kFBEventInput )
        , mInputType( kFBUnknownInput )
        , mX( 0 )
        , mY( 0 )
        , mMouseButton( -1 )
        , mKey( -1 )
        , mKeyState( -1 )
    {
    }

    FBInputType    mInputType;
    int            mX;
    int            mY;
    int            mMouseButton;
    int            mKey;           ///< Key pressed at input.
    int            mKeyState;      ///< Modifiers.

};

/// Parameter given to callbacks of kFBEventMenu
class PYSDK_DLL FBEventMenu_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventMenu_Wrapper()
        : FBEvent_Wrapper( kFBEventMenu )
        , mId( -1 )
    {
    }
    int mId;        ///< Id of the menu.
    str mName;    ///< Name of the selected item.
};

/// Parameter given to callbacks of kFBEventTreeSelect
class PYSDK_DLL FBEventTreeSelect_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventTreeSelect_Wrapper()
        : FBEvent_Wrapper( kFBEventTreeSelect )
    {
    }
    object mTreeNode; 
};


/// Parameter given to callbacks of kFBEventPaint
class PYSDK_DLL FBEventExpose_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventExpose_Wrapper()
        : FBEvent_Wrapper( kFBEventExpose )
    {
    }

    //FBGeometry* mGeometry; ///< The geometry being drawn.
};

/// Parameter given to callbacks of kFBEventResize
class PYSDK_DLL FBEventResize_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventResize_Wrapper()
        : FBEvent_Wrapper( kFBEventResize )
        , mWidth( 0 )
        , mHeight( 0 )
    {
    }
    int     mWidth;     ///< New width.
    int     mHeight;    ///< New height.
};


/// Parameter given to callbacks of kFBEventTransaction
class PYSDK_DLL FBEventTransaction_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventTransaction_Wrapper()
        : FBEvent_Wrapper( kFBEventTransaction )        
        , mIsBegin( true )
    {
    }
    bool mIsBegin;  ///< Is the transaction begins (else it ends)
};


/// Parameter given to callbacks of kFBEventDoubleClick
class PYSDK_DLL FBEventDblClick_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventDblClick_Wrapper()
        : FBEvent_Wrapper( kFBEventDoubleClick )
        , mSelection( -1 )
    {
    }
    int     mSelection; ///< Id of selection.
};

#endif
/// Parameter given to callbacks of kFBEventSceneChange
class PYSDK_DLL FBEventSceneChange_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventSceneChange_Wrapper()
        : FBEvent_Wrapper( kFBEventSceneChange )        
    {
    }

    FBSceneChangeType mType;    ///< Type of the EventChange event
    object mComponent;          //!< Modified component
    object mChildComponent;     //!< Child component of the event.
};

class PYSDK_DLL FBEventTakeChange_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventTakeChange_Wrapper()
        : FBEvent_Wrapper( kFBEventTakeChange )        
    {
    }

    FBTakeChangeType mType;     ///< Type of take change event.
    object mTake;               ///< The take modified.
};      

class PYSDK_DLL FBEventFileChange_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventFileChange_Wrapper( FBEventName pName )
        : FBEvent_Wrapper( pName )        
    {
    }

    FBFileMonitoringType mType;         ///< Type of file change event.
    str mPath;                          ///< File path of file change event.
}; 

class PYSDK_DLL FBEventConnectionNotify_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventConnectionNotify_Wrapper()
        : FBEvent_Wrapper( kFBEventConnectionNotify )        
    {
    }

    FBConnectionAction    Action;         //!< <b>Read Only Property:</b> Connection's action performed.
    int                   SrcIndex;       //!< <b>Read Only Property:</b> Index of the source in the destination component.
    FBConnectionType      ConnectionType; //!< <b>Read Only Property:</b> Connection's type.
    object                SrcPlug;        //!< <b>Read Only Property:</b> The source plug involved in the action.
    object                DstPlug;        //!< <b>Read Only Property:</b> The destination plug involved in the action.
    object                NewPlug;        //!< <b>Read Only Property:</b> New plug created by the action. (Mostly used by merge/replace)

};      

class PYSDK_DLL FBEventConnectionDataNotify_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventConnectionDataNotify_Wrapper()
        : FBEvent_Wrapper( kFBEventConnectionDataNotify )        
    {
    }

    FBConnectionAction    Action;          //!< <b>Read Only Property:</b> Connection's action performed.
    object                Plug;            //!< <b>Read Only Property:</b> The plug involved in the action.
};      

class PYSDK_DLL FBEventConnectionStateNotify_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventConnectionStateNotify_Wrapper()
        : FBEvent_Wrapper( kFBEventConnectionStateNotify )        
    {
    }

    FBConnectionAction    Action;          //!< <b>Read Only Property:</b> Connection's action performed.
    object                Plug;            //!< <b>Read Only Property:</b> The plug involved in the action.
};    

class PYSDK_DLL FBEventConnectionKeyingNotify_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventConnectionKeyingNotify_Wrapper()
        : FBEvent_Wrapper( kFBEventConnectionKeyingNotify )        
    {
    }

    FBConnectionAction    Action;          //!< <b>Read Only Property:</b> Connection's action performed.
    object                Plug;            //!< <b>Read Only Property:</b> The plug involved in the action.
    object                Property;        //!< <b>Read Only Property:</b> The property involved in the action.
    FBTime_Wrapper        StartTime;       //!< <b>Read Only Property:</b> For kFBKeyingDeleteKey, it represents the start time of the range of keys being deleted. For kFBKeyingKey, it represents the time at which the key was added.
    FBTime_Wrapper        StopTime;        //!< <b>Read Only Property:</b> Only available for kFBKeyingDeleteKey, it represents the stop time of the range of keys being deleted.
};      

class PYSDK_DLL FBEventVideoFrameRendering_Wrapper: public FBEvent_Wrapper
{
public:   
    FBEventVideoFrameRendering_Wrapper()
        :FBEvent_Wrapper( kFBEventVideoFrameRendering )        
    {
    }

    kLongLong FrameNumber;
    kLongLong FrameCount;
    FBEventVideoFrameRendering::EState State;
};

class PYSDK_DLL FBEventEvalGlobalCallback_Wrapper: public FBEvent_Wrapper
{
public:   
    FBEventEvalGlobalCallback_Wrapper(FBEventName pName)
        :FBEvent_Wrapper( pName )        
    {
    }

    FBGlobalEvalCallbackTiming Timing;
};

/// Parameter given to callbacks of kFBEventClipChange
class PYSDK_DLL FBEventClipChange_Wrapper : public FBEvent_Wrapper
{
public:
    FBEventClipChange_Wrapper()
        : FBEvent_Wrapper( kFBEventClipChange )        
    {
    }

    FBStoryClipChangeType mType;			///< Type of the EventChange event
};

// Parameter given to callbacks of kFBEventPlayerControlChange
class PYSDK_DLL FBEventPlayerControlChange_Wrapper : public FBEvent_Wrapper
{
public:
	FBEventPlayerControlChange_Wrapper()
		: FBEvent_Wrapper( kFBEventPlayerControlChange )        
	{
	}

	FBPlayerControlChangeType mType;		//!< Player Control OnChange event's type.
};

#endif // pyfbcallback_h__