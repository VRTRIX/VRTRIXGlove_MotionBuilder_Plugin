#ifndef __FBCONTROLS_H__
#define __FBCONTROLS_H__
/**************************************************************************
Copyright (c) 1994 - 2009 Autodesk, Inc. and/or its licensors.
All Rights Reserved.

The coded instructions, statements, computer programs, and/or related 
material (collectively the "Data") in these files contain unpublished 
information proprietary to Autodesk, Inc. and/or its licensors, which is 
protected by Canada and United States of America federal copyright law 
and by international treaties.

The Data may not be disclosed or distributed to third parties, in whole 
or in part, without the prior written consent of Autodesk, Inc. 
("Autodesk").

THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO 
WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR 
ARISING BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES 
OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
PURPOSE OR USE. WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT 
WARRANT THAT THE OPERATION OF THE DATA WILL BE UNINTERRUPTED OR ERROR 
FREE.

IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS 
OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR 
EXPENSES OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE 
DAMAGES OR OTHER SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS 
OF PROFITS, REVENUE OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR 
DAMAGES OF ANY KIND), HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF 
LIABILITY, WHETHER DERIVED FROM CONTRACT, TORT (INCLUDING, BUT NOT 
LIMITED TO, NEGLIGENCE), OR OTHERWISE, ARISING OUT OF OR RELATING TO THE 
DATA OR ITS USE OR ANY OTHER PERFORMANCE, WHETHER OR NOT AUTODESK HAS 
BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS OR DAMAGE.

**************************************************************************/

/**	\file fbcontrols.h
*	Contains the user interface components for the SDK.
*	All of the user interface elements available for use with the SDK are 
*	defined in this file. These elements (for the most part) derive from 
*	the FBVisualComponent base class and provide the functionality 
*	required to develop an interface for a plugin.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
//! FBSDKDLL_ K_DLLEXPORT
#define FBSDK_DLL K_DLLEXPORT
#endif

#include <fbxsdk/fbxsdk_nsbegin.h>
	class FbxAnimCurveNode;
	class FbxAnimStack;
	class FbxProperty;
#include <fbxsdk/fbxsdk_nsend.h>

#include <fbsdk/fbcomponent.h>

K_FORWARD( IKtLayoutRegion );
K_FORWARD( IKtObject );
K_FORWARD( IKtView );

class QWidget;

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

FB_DEFINE_COMPONENT( FBSDK_DLL, Layout				);
FB_DEFINE_COMPONENT( FBSDK_DLL, VisualComponent	    );
FB_DEFINE_COMPONENT( FBSDK_DLL, View				);

#ifdef K_DISABLE_UI //{

#else // }{

FB_DEFINE_COMPONENT( FBSDK_DLL, TreeNode			);

//! SPLIT_WIDTH
#define SPLIT_WIDTH				10

/** Register a control
*	\param	ClassName		Control class name to register.
*	\param	Path			Internal path to store control.
*	\param	Label			Short description of control.
*	\param	Description		Long description of control.
*	\param	IconFilename	Filename of associated icon.
*	\warning The application path to specify is not a directory structure path.
*/
#define FBRegisterControl( ClassName, Path, Label, Description, IconFilename ) \
    HIObject RegisterControl##ClassName( HIObject /*pOwner*/,const char * /*pName*/,void * /*pData*/) \
{\
    ClassName *Class = new ClassName; \
    return Class->GetHIObject(); \
} \
    FBLibraryModule( ClassName )\
{\
    FBRegisterObject( ClassName,Path,Label,Description,RegisterControl##ClassName, true, IconFilename );\
    FBRegisterObject( ClassName##1,"FBSDK",Label,Description,RegisterControl##ClassName, true, IconFilename );\
}

////////////////////////////////////////////////////////////////////////////////////
// General
////////////////////////////////////////////////////////////////////////////////////

//! General directions for UI components.
enum FBOrientation { 
    kFBHorizontal,		//!< Horizontal 
    kFBVertical			//!< Vertical	
};

FB_DEFINE_ENUM( FBSDK_DLL, Orientation ); 

#endif //K_DISABLE_UI


////////////////////////////////////////////////////////////////////////////////////
// Input type, modifiers, and keys
////////////////////////////////////////////////////////////////////////////////////
//! Types of input events.
enum FBInputType {
    kFBKeyPress,            //!< A keyboard key was pressed.
    kFBKeyRelease,          //!< A keyboard key was released.
    kFBButtonPress,         //!< A mouse button was pressed.
    kFBButtonRelease,       //!< A mouse button was released.
    kFBMotionNotify,        //!< The mouse has been moved.
    kFBButtonDoubleClick,   //!< A mouse button was double clicked.
    kFBMouseEnter,          //!< The mouse pointer is entering the window.
    kFBMouseLeave,          //!< The mouse pointer is leaving the window.
    kFBMouseWheelNotify,    //!< The mouse wheel has moved.
    kFBDragging,            //!< The mouse is dragging items.
    kFBDropping,            //!< The mouse is dropping items.
    kFBKeyPressRaw,         //!< A keyboard key was pressed.
    kFBKeyReleaseRaw,       //!< A keyboard key was released.
    kFBUnknownInput         //!< The internal event could not be translated.
};

//! Input Modifiers (Ctrl, Alt, Shift).
enum FBInputModifier {	
    kFBKeyNone	= 0,		//!< No modifier.
    kFBKeyShift	= 1 << 0,	//!< Shift was pressed.
    kFBKeyCtrl	= 1 << 1,	//!< Control was pressed.
    kFBKeyAlt	= 1 << 2	//!< Alt was pressed.
};	

//! Keyboard inputs.
enum FBInputKey 	{	
    kFBKeyReturn	= 0x0D,			//!< Return.
    kFBKeyBackSpace	= 0x08,			//!< Backspace.
    kFBKeyTab		= 0x09,			//!< Tab.
    kFBKeyEscape	= 0x1B,			//!< Escape.

    kFBKeyPageUp	= 0x121,		//!< Page Up.
    kFBKeyPageDown	= 0x122,		//!< Page Down.
    kFBKeyEnd		= 0x123,		//!< End.
    kFBKeyHome		= 0x124,		//!< Home.
    kFBKeyLeft		= 0x125,		//!< Left.
    kFBKeyUp		= 0x126,		//!< Up.
    kFBKeyRight		= 0x127,		//!< Right.
    kFBKeyDown		= 0x128,		//!< Down.

    kFBKeyIns		= 0x12D,		//!< Insert.
    kFBKeyDel		= 0x12E,		//!< Delete.

    kFBKeyF1		= 0x170,		//!< F1.
    kFBKeyF2		= 0x171,		//!< F2.
    kFBKeyF3		= 0x172,		//!< F3.
    kFBKeyF4		= 0x173,		//!< F4.
    kFBKeyF5		= 0x174,		//!< F5.
    kFBKeyF6		= 0x175,		//!< F6.
    kFBKeyF7		= 0x176,		//!< F7.
    kFBKeyF8		= 0x177,		//!< F8.
    kFBKeyF9		= 0x178,		//!< F9.
    kFBKeyF10		= 0x179,		//!< F10.
    kFBKeyF11		= 0x17A,		//!< F11.
    kFBKeyF12		= 0x17B			//!< F12.
};

FB_DEFINE_ENUM( FBSDK_DLL, InputType		);
FB_DEFINE_ENUM( FBSDK_DLL, InputModifier	);
FB_DEFINE_ENUM( FBSDK_DLL, InputKey			);

//! FBColor
enum FBColorIndex
{
    // "Traditional" colors
    kFBColorIndexBackground,	//!< Background color.
    kFBColorIndexBackground1,	//!< Background 1 color.
    kFBColorIndexForeground,	//!< Foreground color.
    kFBColorIndexForeground1,	//!< Foreground 1 color.
    kFBColorIndexForeground2,	//!< Foreground 2 color.
    kFBColorIndexAlternate1,	//!< Alternate 1 color.
    kFBColorIndexAlternate2,	//!< Alternate 2 color.
    kFBColorIndexHighlight,		//!< Highlight color.
    kFBColorIndexShadow,		//!< Shadow color.
    kFBColorIndexWhite,			//!< White color.
    kFBColorIndexBlack,			//!< Black color.
    kFBColorIndexLtGray,		//!< Light Gray color.
    kFBColorIndexGray,			//!< Gray color.
    kFBColorIndexDkGray,		//!< Dark Gray color.
    kFBColorIndexRed,			//!< Red color.
    kFBColorIndexGreen,			//!< Green color.
    kFBColorIndexBlue,			//!< Blue color.
    // Colors to be defined and used by skins
    kFBColorIndexStdButton1,	//!< Standard Button 1 color.
    kFBColorIndexStdButton2,	//!< Standard Button 2 color.
    kFBColorIndexFlatButtonActive1,	//!< Flat Button Active 1 color.
    kFBColorIndexFlatButtonActive2,	//!< Flat Button Active 2 color.
    kFBColorIndexFlatButtonPassive1,//!< Flat Button Passive 1 color.
    kFBColorIndexFlatButtonPassive2,//!< Flat Button Passive 2 color.
    kFBColorIndexStdCheckboxClear1,//!< Standard Checkbox Clear 1 color.
    kFBColorIndexStdCheckboxClear2,//!< Standard Checkbox Clear 2 color.
    kFBColorIndexStdCheckboxAmbig1,//!< Standard Checkbox Ambig 1 color.
    kFBColorIndexStdCheckboxAmbig2,//!< Standard Checkbox Ambig 2 color.
    kFBColorIndexStdCheckboxDisabled1,//!< Standard Checkbox Disabled 1 color.
    kFBColorIndexStdCheckboxDisabled2,//!< Standard Checkbox Disabled 2 color.
    kFBColorIndexStdField1,		//!< Standard Field 1 color.
    kFBColorIndexStdField2,		//!< Standard Field 2 color.
    kFBColorIndexStdScrollActive1,		//!< Standard Scroll Active 1 color.
    kFBColorIndexStdScrollActive2,		//!< Standard Scroll Active 2 color.
    kFBColorIndexStdScrollPassive1,		//!< Standard Scroll Passive 1 color.
    kFBColorIndexStdScrollPassive2,		//!< Standard Scroll Passive 2 color.
    kFBColorIndexStdScrollCursor,		//!< Standard Scroll Cursor color.
    kFBColorIndexStdListBg1,			//!< Standard List Background 1 color.
    kFBColorIndexStdListBgSelected1,	//!< Standard List Background Selected 1 color.
    kFBColorIndexStdListBgSelected2,	//!< Standard List Background Selected 2 color.
    kFBColorIndexStdListBgFocusSelected1,	//!< Standard List Background Focus Selected 1 color.
    kFBColorIndexStdListText,			//!< Standard List Text color.
    kFBColorIndexStdListTextSelected,	//!< Standard List Text Selected color.
    kFBColorIndexStdListTextDragover,	//!< Standard List Text Dragover color.
    kFBColorIndexStdListLine,			//!< Standard List Line color.
    kFBColorIndexStdTabActive1,			//!< Standard Tab Active 1 color.
    kFBColorIndexStdTabActive2,			//!< Standard Tab Active 1 color.
    kFBColorIndexStdTabPassive1,		//!< Standard Tab Passive 1 color.
    kFBColorIndexStdTabPassive2,		//!< Standard Tab Passive 1 color.
    kFBColorIndexFlatTabBg1,			//!< Flat Tab Background 1 color.
    kFBColorIndexFlatTabTextSelected,	//!< Flat Tab Text Selected color.
    kFBColorIndexDisabled1,				//!< Disabled 1 color.
    kFBColorIndexDisabled2,				//!< Disabled 2 color.
    kFBColorIndexSelected,				//!< Selected color.
    kFBColorIndexTimelineOutside,		//!< Timeline Outside color.
    kFBColorIndexTimelineOutside1,		//!< Timeline Outside 1 color.
    kFBColorIndexTimelineCenter,		//!< Timeline Center color.
    kFBColorIndexTimelineCenter1,		//!< Timeline Center 1 color.
    kFBColorIndexTimelineCenter2,		//!< Timeline Center 2 color.
    kFBColorIndexTimelineShadow,		//!< Timeline Shadow color.		
    kFBColorIndexTimelineHighlight,		//!< Timeline Highlight color.
    kFBColorIndexTimelineManipulator,		//!< Timeline Manipulator color.
    kFBColorIndexStdListBgFocusSelected2,
    kFBColorIndexTreeBgTitle,			//!< Tree Background Title color.
    kFBColorIndexTreeBgSubtitle,		//!< Tree Background Subtitle color.
    kFBColorIndexTreeBgSubtitleLine,	//!< Tree Background SubtitleLine color.
    kFBColorIndexTreeBgNode,			//!< Tree Background Node color.
    kFBColorIndexTreeEditboxBg,			//!< Tree Editbox Background color.
    kFBColorIndexTreeSplitter,			//!< Tree Splitter color.
    kFBColorIndexTreeKeyingGroup,		//!< Tree Keying Group color.
    kFBColorIndexTreeOddRow,			//!< Tree Odd Row color.
    kFBColorIndexTreeSelect,			//!< Tree Select color.
    kFBColorIndexTreeKeyingSelect,		//!< Tree Keying Select color.
    kFBColorIndexDkGreen,				//!< Dark Green color.
    // Total number of colors
    kFBColorIndexSize					//!< Color Index Size color.
};


#ifndef K_DISABLE_UI

////////////////////////////////////////////////////////////////////////////////////
// FBVisualComponent
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBLayout );
__FB_FORWARD( FBVisualComponent );

FB_FORWARD( FBStringList );

FB_DEFINE_COMPONENT( FBSDK_DLL, FBVisualComponent );

//! Types of attachments between UI regions.
enum FBAttachType {	
    kFBAttachLeft,		//!< Attach to left		[min(x1,x2)]	
    kFBAttachRight,		//!< Attach to right	[max(x1,x2)]	
    kFBAttachTop,		//!< Attach to top		[min(y1,y2)]	
    kFBAttachBottom,	//!< Attach to bottom	[max(y1,y2)]	
    kFBAttachWidth,		//!< Attach to width	[abs(x2-x1)]	
    kFBAttachHeight,	//!< Attach to height	[abs(y2-y1)]	
    kFBAttachCenter,	//!< Attach to center	[center(x1,y1,x2,y2)]	
    kFBAttachNone		//!< No attachment.						
};
FB_DEFINE_ENUM( FBSDK_DLL, AttachType ); 

//! Different border types available.
enum FBBorderStyle {	
    kFBNoBorder,					//!< No border.						
    kFBStandardBorder,				//!< Standard border.				
    kFBEmbossBorder,				//!< Embossed border.				
    kFBEmbossSmoothBorder,			//!< Smooth border.					
    kFBEmbossEdgeSmoothBorder,		//!< Edged smooth border.			
    kFBEmbossSmoothEdgeBorder,		//!< Smoothed edges border.			
    kFBStandardSmoothBorder,		//!< Standard smooth border.			
    kFBStandardEdgeSmoothBorder,	//!< Standard edged smooth border.	
    kFBStandardSmoothEdgeBorder,	//!< Standard smoothed edges border.
    kFBHighlightBorder,				//!< Highlight border.				
    kFBPickingBorder				//!< Picking border.				
};
FB_DEFINE_ENUM( FBSDK_DLL, BorderStyle ); // FBPropertyBorderStyle 

/**	Visual Component base class.
*	All of the user interface elements available in the SDK derive from this class.
*/
class FBSDK_DLL FBVisualComponent : public FBComponent {
    __FBClassDeclare( FBVisualComponent,FBComponent );
protected:
    friend class FBLayout;
    friend class FBRenderer;

    /**	Get internal toolkit object.
    *	\return Handle to internal toolkit object.
    */
    virtual HIKtObject GetHIKtObject();
public:
    //! Constructor.
    FBVisualComponent(HIObject pObject);

    IObject_Declare(override);		// Interface to IObject
    ICallback_Declare(override);		// Interface to ICallback

    /**	Get internal toolkit object.
    *	\return Handle to internal toolkit object.
    */
    virtual HIKtView GetKtView();

    /** Get internal QWidget.
    *   \return Handle to internal QWidget object.
    */
    QWidget* GetQWidgetAddress();

    /** Add a child component.
    *	\param	pChild	Visual component to add as a child.
    *	\param	pId		User reference number to associate with \e pChild(default=0).
    *	\return	Operation was successful (\b true or \b false).
    */
    virtual bool AddChild( FBVisualComponent* pChild,int pId=0);

    /** Get a child component.
    *	\param	pId User reference number to look for child with(default=0).
    *	\return Handle to child (NULL if not found).
    */
    virtual FBVisualComponent* GetChild( int pId=0 );

    /** Refresh component. 
    *	\param pNow Refresh immediately if \b true (default = \b false).
    */
    virtual void Refresh(bool pNow=false);

    //! Exposed view callback function.
    virtual void ViewExpose();

    /** Input callback function.
    *	\param pMouseX		Mouse X position.
    *	\param pMouseY		Mouse Y position.
    *	\param pAction		Mouse action.
    *	\param pButtonKey	Keyboard input.
    *	\param pModifier	Keyboard input modifier.
    */
    virtual void ViewInput(int pMouseX,int pMouseY,FBInputType pAction,int pButtonKey,int pModifier);

    /**	Is component a view?
    *	\return \b true if component is a view.
    */
    virtual bool IsView();

    /** Region information structure.
    *	Contains region attachment and relative value information.
    */
    struct __Region
    {        
        FBPropertyString            Name;		//!< <b>Property:</b> Region name.

        FBPropertyInt				X;			//!< <b>Property:</b> Region X offset.
        FBPropertyInt				Y;			//!< <b>Property:</b> Region Y offset.
        FBPropertyInt				Width;		//!< <b>Property:</b> Region width offset.
        FBPropertyInt				Height;		//!< <b>Property:</b> Region height offset.

        //! Structure for attachment ratio.
        struct FBSDK_DLL __Ratio
        {
            FBPropertyFloat			X;		//!< <b>Property:</b> Ratio for X attachment.
            FBPropertyFloat			Y;		//!< <b>Property:</b> Ratio for Y attachment.
            FBPropertyFloat			Width;	//!< <b>Property:</b> Ratio for Width attachment.
            FBPropertyFloat			Height;	//!< <b>Property:</b> Ratio for Height attachment.
        } Ratio;

        //! Structure for attachment types.
        struct FBSDK_DLL __AttachType
        {
            FBPropertyAttachType	X;		//!< <b>Property:</b> X Attachment type.
            FBPropertyAttachType	Y;		//!< <b>Property:</b> Y Attachment type.
            FBPropertyAttachType	Width;	//!< <b>Property:</b> Width Attachment type.
            FBPropertyAttachType	Height;	//!< <b>Property:</b> Height Attachment type.
        } AttachType;

        //! Structure for attachment components.
        struct FBSDK_DLL __AttachTo
        {
            FBPropertyVisualComponent	X;		//!< <b>Property:</b> X Attachment source.
            FBPropertyVisualComponent	Y;		//!< <b>Property:</b> Y Attachment source.
            FBPropertyVisualComponent	Width;	//!< <b>Property:</b> Width Attachment source.
            FBPropertyVisualComponent	Height;	//!< <b>Property:</b> Height Attachment source.
        } AttachTo;

        //! Structure for absolute positions
        struct FBSDK_DLL __Pos
        {
            FBPropertyInt	X[2];			//!< <b>Property:</b> Region X position (0=min,1=max).
            FBPropertyInt	Y[2];			//!< <b>Property:</b> Region Y position (0=min,1=max).
        } Position;

    } Region;

    //! Border information structure.
    struct FBSDK_DLL __Border
    {
        FBPropertyString		Caption;			//!< <b>Property:</b> Caption to display in border.
        FBPropertyBool			ShowCaption;		//!< <b>Property:</b> Show caption?
        FBPropertyBorderStyle	Style;				//!< <b>Property:</b> Style of border.
        FBPropertyBool			InSet;				//!< <b>Property:</b> Is border inset?
        FBPropertyInt			Width;				//!< <b>Property:</b> Width of border.
        FBPropertyInt			Spacing;			//!< <b>Property:</b> Spacing of border.
        FBPropertyFloat			MaxAngle;			//!< <b>Property:</b> Max angle for rounding.
        FBPropertyInt			CornerRadius;		//!< <b>Property:</b> Corner radius (rounded).
    } Border;

    FBPropertyString		    Caption;			//!< <b>Property:</b> Widget caption.
    FBPropertyBool			    Visible;			//!< <b>Read Write Property:</b> Is visual component visible?
    FBPropertyBool			    ReadOnly;			//!< <b>Read Write Property:</b> Is visual component read only?
    FBPropertyBool			    Enabled;			//!< <b>Read Write Property:</b> Is visual enabled?
    FBPropertyString		    Hint;				//!< <b>Read Write Property:</b> Hint to show.

    FBPropertyInt		        Left;				//!< <b>Read Write Property:</b> Left coordinate.
    FBPropertyInt		        Top;				//!< <b>Read Write Property:</b> Top coordinate.
    FBPropertyInt		        Width;				//!< <b>Read Write Property:</b> Width.
    FBPropertyInt		        Height;				//!< <b>Read Write Property:</b> Height.

    FBPropertyEvent             OnEnter;		    //!< <b>Event:</b> On mouse enter.
    FBPropertyEvent             OnExit;		        //!< <b>Event:</b> On mouse exit.
};


////////////////////////////////////////////////////////////////////////////////////
// FBEventInput
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventInput );

//! Input event class.
class FBSDK_DLL FBEventInput : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent	 Base event (internal) to obtain information from.
    */
    FBEventInput( HKEventBase pEvent );		

    FBPropertyInputType InputType;		    //!< <b>Read Only Property:</b> Input type.
    FBPropertyInt		X;				    //!< <b>Read Only Property:</b> Mouse X Position.
    FBPropertyInt		Y;				    //!< <b>Read Only Property:</b> Mouse Y Position.
    FBPropertyInt		MouseButton;	    //!< <b>Read Only Property:</b> Mouse Button.
    FBPropertyInt		Key;			    //!< <b>Read Only Property:</b> Input key.
    FBPropertyInt		KeyState;		    //!< <b>Read Only Property:</b> State of key.
    FBPropertyInt		Pressure;		    //!< <b>Read Only Property:</b> Pressure.
    FBPropertyInt		MouseWheelDelta;	//!< <b>Read Only Property:</b> Wheel Delta.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventTransaction
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventTransaction );

//! Transaction event
class FBSDK_DLL FBEventTransaction : public FBEvent
{
public:
    FBPropertyBool		IsBeginTransaction;	    //!< <b>Read Only Property:</b> Tells if the transaction is at begin.

    /** Constructor.
    *	\param	pEvent	Base event object.
    */
    FBEventTransaction( HKEventBase pEvent);
};
////////////////////////////////////////////////////////////////////////////////////
// FBEventDragAndDrop
////////////////////////////////////////////////////////////////////////////////////
//__FB_FORWARD( FBDragAndDrop );
__FB_FORWARD( FBEventDragAndDrop );

//! State of Drag and Drop.
enum FBDragAndDropState {	
    kFBDragAndDropBegin,	//!< Begin a drag and drop sequence.
    kFBDragAndDropDrag,		//!< Dragging.
    kFBDragAndDropDrop,		//!< Dropping.
    kFBDragAndDropEnd,		//!< End of drag and drop.
    kFBDragOnEmpty,			//!< Empty the drag and drop stack.
    kFBDragOnEmptyDrop		//!< Dropping empty stack.
};

FB_DEFINE_ENUM( FBSDK_DLL, DragAndDropState ); 

//! Drag and drop interface.
class FBSDK_DLL FBEventDragAndDrop : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventDragAndDrop ( HKEventBase pEvent );

    virtual ~FBEventDragAndDrop()=default;

    /** Accept a drag and drop sequence.
    *	This will cause the region in question to accept a drag and drop action when this
    *	event occurs.
    */
    virtual void Accept();

    /**	Add an item to the drag and drop list.
    *	\param pComponent Item to add to the list.
    *	\param pId User-defined reference for the item (default = 0 ).
    */
    virtual void Add( FBComponent* pComponent, int pId=0);

    /** Get the FBComponent specified by \e pIndex from the Drag and Drop list.
    *	\param	pIndex	Index in list where to get FBComponent.
    *	\return	Handle to FBComponent in list at \e pIndex.
    */
    virtual FBComponent* Get( int pIndex );

    //! Clear drag and drop list.
    virtual void Clear();			

    /**	Get the number of items in the DragAndDrop list.
    *	\return Number of items in DragAndDrop list.
    */
    virtual int GetCount();

    //-- Properties
    FBPropertyDragAndDropState	State;		//!< <b>Property:</b> Drag and drop sub-event.
    FBPropertyInt				PosX;		//!< <b>Property:</b> X position of mouse.
    FBPropertyInt				PosY;		//!< <b>Property:</b> Y position of mouse.
    FBPropertykReference		Data[2];	//!< <b>Property:</b> User specified reference. (for example, FBSpread:row)
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventShow
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventShow );

//! Show event class.
class FBSDK_DLL FBEventShow : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventShow( HKEventBase pEvent );		

    FBPropertyBool	Shown;		//!< <b>Read Only Property:</b> Was layer just shown?
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventActivate
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventActivate );

//! Activation event.
class FBSDK_DLL FBEventActivate : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventActivate( HKEventBase pEvent );

    FBPropertykReference Data;				//!< <b>Read Write Property:</b> Generic data of event.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventExpose
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventExpose );

//! Event sent when a control needs to be displayed.
class FBSDK_DLL FBEventExpose : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventExpose( HKEventBase pEvent );

    //FBGeometry* Data;				//!< <b>Read Write Property:</b> Generic data of event.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventResize
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventResize );

//! Event sent to a control that resizes.
class FBSDK_DLL FBEventResize : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventResize( HKEventBase pEvent );

    FBPropertyInt Width;	//!< <b>Property:</b> New Width of the window.
    FBPropertyInt Height;	//!< <b>Property:</b> New Height of the window.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEventMenu
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD(FBEventMenu);
__FB_FORWARD(FBMenuItem);

/**	Menu Item class declaration.
*	\param	ClassName	Name of menu item class to declare.
*	\param	Parent		Name of menu item class's parent class.
*/
#define FBMenuItemDeclare( ClassName,Parent ) \
    FBClassDeclare( ClassName,Parent ); \
public: \
    ClassName():Parent() { FBClassInit; FBCreate(); } \
	static ClassName* g##ClassName; \
private:

/**	Menu item class implementation.
*	\param	ClassName	Menu item class to implement.
*/
#define FBMenuItemImplementation( ClassName ) \
    FBClassImplementation( ClassName ) \
	ClassName* ClassName::g##ClassName = nullptr

/**	Menu item registration.
*	\param	ClassName	Menu item class to register.
*/
#define FBRegisterMenuItem( ClassName ) \
    HIObject RegisterMenuItem##ClassName( HIObject /*pOwner*/,const char * /*pName*/,void * /*pData*/) \
{\
    return NULL;\
}\
    FBLibraryModule( ClassName )	\
{	\
}

/**	Menu item activation.
*	\param	ClassName	Menu item class to activate.
*/
#define FBMenuItemActivation( ClassName )	\
    ClassName::g##ClassName = new ClassName;			\
    ClassName::g##ClassName->Activate()

/**	Get the handle of a menu item.
*	\param	ClassName	Menu item class to get a handle for.
*	\retval	Handle		Handle to the menu item.	
*/
#define FBMenuItemHandle( ClassName, Handle )	\
    Handle = ClassName::g##ClassName

//! Types of menu items available.
enum FBMenuItemType {	
    kFBMenuItemMotionImport,	//!< Motion Files->Import.
    kFBMenuItemSceneImport, 	//!< Scenes->Import.
    kFBMenuItemMotionExport,	//!< Motion Files->Export.
    kFBMenuItemSceneExport		//!< Scenes->Export.
};

FB_DEFINE_ENUM( FBSDK_DLL, MenuItemType );

//! Menu event
class FBSDK_DLL FBEventMenu : public FBEvent
{
public:
    FBPropertyInt		Id;			//!< <b>Read Write Property:</b> Id number for menu item.
    FBPropertyString	Name;		//!< <b>Read Write Property:</b> Name of menu item.

    /** Constructor.
    *	\param	pEvent	Base event object.
    */
    FBEventMenu( HKEventBase pEvent);
};

//! Menu Item.
class FBSDK_DLL FBMenuItem : public FBVisualComponent
{
    __FBClassDeclare( FBMenuItem, FBVisualComponent );

public:
    //! Constructor.
    FBMenuItem();

    /**	Initialization function.
    *	\param	pType			Type of menu item to be set.
    *	\param	pExtension		File extension to use as filter for popup.
    *	\param	pLabel			Short description of file format (usually one word identifier)
    *	\param	pDescription	Long description of file format
    */
    void Set(FBMenuItemType	pType, const char* pExtension, const char* pLabel, const char* pDescription);

    /** Is menu item active?
    *	\return \b true if menu item has been registered (activated).
    */
    bool IsActive();

    /** Activate menu item.
    *	This will register the callback functions for the menu item, as well as make the item
    *	itself appear in the menu. Once activated, you have no more control over the 
    *	menu item, seeing as it will be registered and cannot be activated twice.
    *	This function should be the last one you call when activating the menu item.
    *	\param	pState	Activate if \b true (default = \b true).
    */
    void Activate( bool pState = true );

    /** Internal callback function for activated menu item.
    *	Registers internally the menu item.
    *	\param	pSender	Sending register.
    *	\param	pEvent	Event being sent.
    */
    virtual void OnItemSelectEvent(HIRegister pSender, HKEvent pEvent);

public:
    FBPropertyComponent			Component;			//!< <b>Read Write Property:</b> Component handle.
    FBPropertyString			Extension;			//!< <b>Read Write Property:</b> Default extension.
    FBPropertyString			Label;				//!< <b>Read Write Property:</b> Label of the menu item.
    FBPropertyString			Description;		//!< <b>Read Write Property:</b> Description of the menu item.
    FBPropertyMenuItemType		Type;				//!< <b>Read Write Property:</b> Type of menu item.

    FBPropertyString			Path;				//!< <b>Read Write Property:</b> Default path to open file dialog to.

public:
    /**	The callback function for when the menu item is selected.
    *	In order to use this class correctly, you must create a class that inherits directly
    *	from this class, overloading this virtual function. This function will then be called 
    *	when the menu item is selected.
    *	\param	pFilename	Filename from popup (default = NULL).
    *	\return	Operation was successful (\b true or \b false).
    */
    virtual	bool Execute(const char *pFilename=NULL)	= 0;
};

////////////////////////////////////////////////////////////////////////////////////
// FBLayout
////////////////////////////////////////////////////////////////////////////////////

/** Used to build the user interface.
*	Layouts manage areas of the screen called regions. Regions contain UI
*	components such as buttons, viewers, and edit boxes.
*   Regions are added to layouts.
*   When a UI component is bound to a region, the region defines
*	how big it is and how it behaves when the layout is resized.
*
*	<b>Types of Layouts</b>
*	<ul>
*	<li>Device
*	<li>Constraint</li>
*	<li>Manipulator</li>
*	<li>Shader</li>
*	</ul>
*
*   A region is first defined using the FBLayout::AddRegion() function. Once a region is defined and the
*   corresponding UI component is created, and the component is bound to its region with FBLayout::SetControl().
*   You can use the FBSystem::OnUIIdle() in your layout to update real-time UI components
*	such as guages and status indicators.
*   In Python, FBBoxLayout and FBGridLayout take care of most of the region handling. They are used to create 
*   basic control layouts for simple tools.
*   If you have a lot of content you can use FBScrollBox to manage it. For an example, see the Python sample Scrollbox.py.*
*   Also see the Python sample Layout.py, and the C++ sample ortooluidemo.
*/
class FBSDK_DLL FBLayout : public FBVisualComponent {
    __FBClassDeclare( FBLayout,FBVisualComponent );
public:

    //! Type of split style (sub-division) for layout.
    enum FBSplitStyle 
    {	
        kFBNoSplit	= 0,	//!< No split.
        kFBHSplit	= 1,	//!< Horizontal split.
        kFBVSplit	= 2,	//!< Vertical split.
        kFBHVSplit	= 3		//!< Horizontal and Vertical split.
    };

    //! Constructor.
    FBLayout(HIObject pObject=NULL);

    /**	Add a region to the layout.
    *	\param	pName		Name of region.
    *	\param	pTitle		Title to display.
    *
    *	\param	pX			X: Position.
    *	\param	pXType		X: Type of attachment.
    *	\param	pXRelative	X: Item to attach to.
    *	\param	pMultX		X: Multiplier of relative value.
    *
    *	\param	pY			Y: Position.
    *	\param	pYType		Y: Type of attachment.
    *	\param	pYRelative	Y: Item to attach to.
    *	\param	pMultY		Y: Multiplier of relative value.
    *
    *	\param	pW			W: Width of region.
    *	\param	pWType		W: Type of attachment.
    *	\param	pWRelative	W: Item to attach to.
    *	\param	pMultW		W: Multiplier of relative value.
    *
    *	\param	pH			H: Height of region.
    *	\param	pHType		H: Type of attachment.
    *	\param	pHRelative	H: Item to attach to.
    *	\param	pMultH		H: Multiplier of relative value.
    *
    *	\return	Operation was successful (\b true or \b false).
    */
    virtual bool AddRegion(	const char *pName,	const char *pTitle,
        int pX,	FBAttachType pXType,	const char *pXRelative,	float pMultX,
        int pY,	FBAttachType pYType,	const char *pYRelative,	float pMultY,
        int pW,	FBAttachType pWType,	const char *pWRelative,	float pMultW,
        int pH,	FBAttachType pHType,	const char *pHRelative,	float pMultH);

    /**	Move a region.
    *	\param	pName		Name of region to move.
    *	\param	pX			New X position.
    *	\param	pY			New Y position.
    *	\return	Operation was successful (true or false).
    */
    virtual bool MoveRegion( const char *pName, int pX, int pY );

    /**	Change a region's size.
    *	\param	pName		Name of region to resize.
    *	\param	pW			New region width.
    *	\param	pH			New region height.
    *	\return	Operation was successful (true or false).
    */
    virtual bool SizeRegion( const char *pName, int pW, int pH );

    /**	Remove a region.
    *	\param	pName		Name of region to remove.
    *	\return	Operation was successful (true or false).
    */
    virtual bool RemoveRegion( const char *pName );

    /** Rename a region.
    *	\param	pOldName	Region's old name.
    *	\param	pNewName	Region's new name.
    *	\return	Operation was successful (true or false).
    */
    virtual bool RenameRegion( const char *pOldName, const char *pNewName );

    /**	Verify if a region with pName exists.
    *	\param	pName		Name of region to check.
    *	\return	Operation was successful (true or false).
    */
    virtual bool GetRegion( const char *pName );

    /**	Get region \e pName information (position and size)
    *	\param	pName		Name of region.
    *	\param	pComputed	Is the information retrieved relative or absolute?
    *	\retval	pX			Position in X of the region.
    *	\retval	pY			Position in Y of the region.
    *	\retval pW			Width of the region.
    *	\retval pH			Height of the region.
    *	\return	Operation was successful (true or false).
    */
    virtual bool GetRegionPositions	(	const char *pName,	bool pComputed,
        int *pX,		int *pY, 
        int *pW=NULL,	int *pH=NULL	);

    //@{
    /**	Set control of a region to a visual component.
    *	\param	pName		Name of region to affect.
    *	\param	pComponent	Component to control region.
    *	\return	Operation was successful (true or false).
    */
    virtual bool SetControl( const char *pName, FBVisualComponent* pComponent );
    virtual bool SetControl( const char *pName, FBVisualComponent &pComponent );
    //@}

    /**	Remove a control from a region in a visual component.
    *	\param	pName		Name of region to remove control.
    */
    virtual void ClearControl(const char *pName);

    /**	Get control of a region in a visual component.
    *	\param	pName		Name of region to find.
    *	\return	The component if it is found.
    */
    virtual FBVisualComponent* GetControl(const char *pName);

    /** Set or Get internal toolkit: object.
    *	\param	pName		Name of region.
    *	\return	Handle to internal toolkit object.
    */
    virtual HIKtObject GetHIKtObject( const char *pName );

    /** Set internal toolkit view.
    *	\param	pName		Name of region.
    *	\param	pView		View to set as view for region.
    *	\return	Operation was successful (true or false).
    */
    virtual bool SetHIKtView( const char *pName, HIKtView pView );

    /** Get internal toolkit view.
    *	\internal
    *	\param	pName		Name of region.
    *	\return	Handle to internal toolkit view object.
    */
    virtual HIKtView GetHIKtView( const char *pName );

    //@{
    /**	Set view.
    *	\param	pName		Name of Region.
    *	\param	pComponent	Component to set as view.
    *	\return	Operation was successful (true or false).
    */
    virtual bool SetView( const char *pName, FBVisualComponent* pComponent );
    virtual bool SetView( const char *pName, FBVisualComponent &pComponent );
    //@}

    /** Set border properties for a region.
    *	\param	pName			Name of Region to change border properties.
    *	\param	pType			Border style to use.
    *	\param	pShowTitle		Show region title?
    *	\param	pInSet			Is region inset?
    *	\param	pWidth			Border width.
    *	\param	pSpacing		Border spacing.
    *	\param	pMaxAngle		Max angle for rounding.
    *	\param	pCornerRadius	Corner radius for rounding.
    *	\return	Operation was successful (true or false).
    */
    virtual bool SetBorder	(	const char *pName,	FBBorderStyle pType,	bool pShowTitle,
        bool pInSet,		int pWidth,				int pSpacing,
        float pMaxAngle,	int pCornerRadius );

    /**	Set a region's splitstyle.
    *	\param	pName		Name of Region to set splitstyle.
    *	\param	pRegionType	Split style give to region.
    *	\return	Operation was successful (true or false).
    */
    virtual bool SetSplitStyle ( const char *pName, FBSplitStyle pRegionType );

    /**	Get a region's splitstyle.
    *	\param	pName		Name of Region to get splitstyle from.
    *	\return Split style of specified region.
    */
    virtual FBSplitStyle GetSplitStyle ( const char *pName );

    /** Set a region's title.
    *	\param	pName		Name of region to change title.
    *	\param	pTitle		New title for region.
    *	\return	Operation was successful (true or false).
    */
    virtual bool SetRegionTitle ( const char *pName, const char* pTitle );

    /** Suspend all automatic layout recomputation
    *	\param	pAutoRestructure		If true, Suspend all automatic layout recomputation, else restore it.
    */
    void SetAutoRestructure( bool pAutoRestructure );

    /** Force a recomputation of all region placements in the layout.
    *	
    */
    void Restructure( bool pNoMove );

    IObject_Declare(override);		// Interface to IObject.

    //--- Events
    FBPropertyEvent		OnInput;		//!< <b>Event:</b> Input.
    FBPropertyEvent		OnPaint;		//!< <b>Event:</b> Paint layout.
    FBPropertyEvent		OnIdle;			//!< <b>Event:</b> Idle.
    FBPropertyEvent		OnShow;			//!< <b>Event:</b> Show layout.
    FBPropertyEvent		OnResize;		//!< <b>Event:</b> Resize layout.
};

////////////////////////////////////////////////////////////////////////////////////
// FBTabPanel
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBTabPanel );

//! Tab panel.
class FBSDK_DLL FBTabPanel : public FBVisualComponent {
    __FBClassDeclare( FBTabPanel,FBVisualComponent );
public:
    //! Constructor.
    FBTabPanel();

    FBPropertyStringList	Items;			//!< <b>List:</b> Names for tab panels.
    FBPropertyInt			ItemIndex;		//!< <b>Read Write Property:</b> Current tab panel.
    FBPropertyInt           TabStyle;       //!< <b>Read Write Property:</b> Style of the tab panel, 0 creates normal tabs, 1 creates buttons to activate tabs.
    FBPropertyLayout		Layout;			//!< <b>Read Write Property:</b> Layout for current tab panel.
    FBPropertyEvent			OnChange;		//!< <b>Event:</b> Tab panel change.
};

////////////////////////////////////////////////////////////////////////////////////
// FBButton
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBButton );

/** Style of buttons.
*	\warning Not all button styles are completely functional.
*/
enum FBButtonStyle {	
    kFBPushButton,		//!< Normal button.
    kFBBitmapButton,	//!< Button with bitmap on it.
    kFBRadioButton,		//!< Radio button.
    kFB2States,			//!< 2 state button (2 colors).
    kFBCheckbox=kFB2States,		//!< Check box.
    kFBBitmap2States	//!< 2 state button with 2 bitmaps.
};

/** Possible button states.
*   Currently, only two button states are possible.
*/
enum FBButtonState {
    kFBButtonState0,    //!< State is 0, usually meaning not active
    kFBButtonState1     //!< State is 1, usually meaning active
};

FB_DEFINE_ENUM( FBSDK_DLL, ButtonStyle ); 

//! Text justification styles.
enum FBTextJustify {	
    kFBTextJustifyLeft,		//!< Left justify.
    kFBTextJustifyRight,	//!< Right justify.
    kFBTextJustifyCenter	//!< Center alignment.
};

FB_DEFINE_ENUM( FBSDK_DLL, TextJustify );

//! Text appearance styles.
enum FBTextStyle {	
    kFBTextStyleNone        = 0,		//!< Normal.
    kFBTextStyleBold        = 1 << 0,	    //!< Bold.
    kFBTextStyleItalic      = 1 << 1,	    //!< Italic.
    kFBTextStyleUnderlined  = 1 << 2	//!< Underlined.
};

FB_DEFINE_ENUM( FBSDK_DLL, TextStyle );

//! Button look.
enum FBButtonLook {
    kFBLookNormal,
    kFBLookColorChange,
    kFBLookPush,
    kFBLookFlat,
    kFBLookAlphaBackground=99
};

FB_DEFINE_ENUM( FBSDK_DLL, ButtonLook ); 

/** Used to create and manage buttons in a user interface.
*   This class includes functionality to create buttons in a user interface and add a callback.
*   In MotionBuilder, buttons are created within regions, which are in turn created in layouts with FBLayout.
*   For usage, see the Python sample Button.py.
*	See also: FBButtonStyle, FBTextJustify, FBButtonLook.
*/
class FBSDK_DLL FBButton : public FBVisualComponent {
    __FBClassDeclare( FBButton,FBVisualComponent );
public:
    //! Constructor.
    FBButton();

    /** Queries the color associated with a button state.
    *   This method is only useful for buttons of style kFB2States.
    *	\param	pState	The state to be queried.
    *	\return The color vector.
    */
    FBColor GetStateColor( FBButtonState pState );

    /** Returns whether or not the item \e pIndex is currently selected.
    *	\param	pState	The state to be set.
    *	\param	pColor	The desired color vector.
    */
    void    SetStateColor( FBButtonState pState, const FBColor& pColor );

    /** Sets the image used to generate a kFBBitmap2States
    *	\param	pUpImage	The image used when button is unpushed
    *	\param	pDownImage	The image used when button is pushed
    \param	pThirdImage	
    \param	pFromResources	Add resource path to image path.
    */
    void    SetImageFileNames( const char* pUpImage, const char* pDownImage = 0, const char* pThirdImage = 0, bool pFromResources = false );

    /** Sets a link to another button
    *	\param	pButton	Target button
    */
    void    HookToButton(FBButton* pButton);

    FBPropertyInt			State;			//!< <b>Read Write Property:</b> Current state of button.
    FBPropertyButtonStyle	Style;			//!< <b>Read Write Property:</b> Button style.
    FBPropertyTextJustify	Justify;	    //!< <b>Read Write Property:</b> Current state of button.
    FBPropertyButtonLook	Look;			//!< <b>Read Write Property:</b> Current state of button.

    FBPropertyEvent			OnClick;		//!< <b>Event:</b> Button clicked.
    FBPropertyEvent			OnDragAndDrop;	//!< <b>Event:</b> Something was dragged.
};

////////////////////////////////////////////////////////////////////////////////////
// FBArrowButton
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBArrowButton );

/** Creates a button which opens a layout to display content.

When pushed a layout to display content (another control
or a layout) is opened. A small arrow to the left of the button title, shows whether the content is shown
(points down) or not (points to the title).
*/
class FBSDK_DLL FBArrowButton : public FBVisualComponent {
    __FBClassDeclare( FBArrowButton, FBVisualComponent );
public:
    //! Constructor.
    FBArrowButton();

    /** Sets the content to be hidden/shown by button. The FBArrowButton must already have been added to a layout before calling
    this method.
    \param  pTitle          Title of the content managed by the FBArrowButton
    \param	pContent        Content that the FBArrowButton displays or hides
    \param	pContentWidth   Width of the content
    \param	pContentHeight  Height of the content
    */
    void SetContent( const char* pTitle, FBVisualComponent* pContent, int pContentWidth, int pContentHeight );
};

////////////////////////////////////////////////////////////////////////////////////
// FBScrollBox
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBScrollBox);

/**
Scroll Box

This class provides a layout that will be automatically managed with a scrollbar according
to the specified width and height. This provides a way to add dynamic UI control.
*/
class FBSDK_DLL FBScrollBox : public FBVisualComponent {
    __FBClassDeclare( FBScrollBox, FBVisualComponent );
public:
    //! Constructor.
    FBScrollBox();

    /** Sets the content width. This zone will be available to be scrolled horizontally.
    \param  pContentWidth	Content Width.
    */
    void SetContentWidth( int pContentWidth );

    /** Sets the content height. This zone will be available to be scrolled vertically.
    \param  pContentHeight	Content Height.
    */
    void SetContentHeight(int pContentHeight );

    /**
    Returns an empty layout in which you can add scrollable content.
    \return A Layout in which you can add your content.
    */
    FBLayout* GetContent();
private:
    FBLayout mLayout;
};


////////////////////////////////////////////////////////////////////////////////////
// FBLabel
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBLabel );

//! Text label.
class FBSDK_DLL FBLabel : public FBVisualComponent {
    __FBClassDeclare( FBLabel,FBVisualComponent );
public:
    //! Constructor.
    FBLabel();

    /**
    Sets the label text color.
    \param  pColorRGBA          New text color.
    */
    void SetTextColor(const FBColorAndAlpha& pColorRGBA);

    /**
    Sets whether a background is drawn for the label.
    \param  pDrawBackGround          Background drawing enable or not.
    */
    void SetBackgroundDrawing(bool pDrawBackGround);

    FBPropertyTextJustify	Justify;		//!< <b>Read Write Property:</b> Text justification for label.
    FBPropertyTextStyle     Style;          //!< <b>Read Write Property:</b> Text style appearance.
    FBPropertyBool          WordWrap;       //!< <b>Read Write Property:</b> Enable wordwrap on text drawing.
};

////////////////////////////////////////////////////////////////////////////////////
// FBImageContainer
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBImageContainer );

//! Image.
class FBSDK_DLL FBImageContainer : public FBVisualComponent {
    __FBClassDeclare( FBImageContainer,FBVisualComponent );
public:
    //! Constructor.
    FBImageContainer();

	FBPropertyString		Filename;		//!< <b>Read Write Property:</b> Filename for image.
	FBPropertyInt			ImageWidth;		//!< \deprecated <b>Read Write Property:</b> Image width. Useless property to be removed. 
	FBPropertyInt			ImageHeight;	//!< \deprecated <b>Read Write Property:</b> Image height. Useless property to be removed. 

    FBPropertyEvent			OnDragAndDrop;	//!< <b>Event:</b> Drag and drop.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEdit
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEdit );

//! Text edit box.
class FBSDK_DLL FBEdit : public FBVisualComponent {
    __FBClassDeclare( FBEdit,FBVisualComponent );
public:
    //! Constructor.
    FBEdit(HIObject pObject=NULL);

    FBPropertyString		Text;			//!< <b>Read Write Property:</b> Text displayed.
    FBPropertyBool			PasswordMode;	//!< <b>Read Write Property:</b> Set password mode for this edit box.

    FBPropertyEvent			OnChange;		//!< <b>Event:</b> Text changed.
    FBPropertyEvent			OnTransaction;  //!< <b>Event:</b> Transaction begin/end (continuous value changes). This event property doesn't exist in pyfbsdk.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEditNumber
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEditNumber );

//! Number edit box.
class FBSDK_DLL FBEditNumber : public FBVisualComponent {
    __FBClassDeclare( FBEditNumber,FBVisualComponent );
public:
    //! Constructor.
    FBEditNumber();

    FBPropertyDouble		Value;			//!< <b>Read Write Property:</b> Current value.
    FBPropertyDouble		Min;			//!< <b>Read Write Property:</b> Minimum value.
    FBPropertyDouble		Max;			//!< <b>Read Write Property:</b> Maximum value.
    FBPropertyDouble		Precision;		//!< <b>Read Write Property:</b> Precision of value.
    FBPropertyDouble		LargeStep;		//!< <b>Read Write Property:</b> Large step value.
    FBPropertyDouble		SmallStep;		//!< <b>Read Write Property:</b> Small step value.

    FBPropertyEvent			OnChange;		//!< <b>Event:</b> Number changed.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEditColor
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEditColor );

//! Color edit widget.
class FBSDK_DLL FBEditColor : public FBVisualComponent {
    __FBClassDeclare( FBEditColor,FBVisualComponent );
public:
    //! Constructor.
    FBEditColor();

    FBPropertyColor			Value;			//!< <b>Read Write Property:</b> Current value of color.
    FBPropertyInt			ColorMode;		//!< <b>Read Write Property:</b> 3 for RGB, 4 for RGBA (Default = 3)

    FBPropertyEvent			OnChange;		//!< <b>Event:</b> Color changed.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEditVector
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEditVector );

//! Vector edit widget.
class FBSDK_DLL FBEditVector : public FBVisualComponent {
    __FBClassDeclare( FBEditVector,FBVisualComponent );
public:
    //! Constructor.
    FBEditVector();

    FBPropertyVector3d		Value;			//!< <b>Read Write Property:</b> Current value of vector.

    FBPropertyEvent			OnChange;		//!< <b>Event:</b> Vector value changed.
};

__FB_FORWARD( FBEventDblClick );

//! Input event class.
class FBSDK_DLL FBEventDblClick : public FBEvent
{
public:
    /**	Constructor.
    *	\param pEvent	 Base event (internal) to obtain information from.
    */
    FBEventDblClick( HKEventBase pEvent );		

    FBPropertyInt		Selection;	//!< <b>Read Only Property:</b> Id of selection.
};

////////////////////////////////////////////////////////////////////////////////////
// FBList
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBList );

//! List style or direction.
enum FBListStyle { 
    kFBDropDownList,	//!< Drop down list.
    kFBVerticalList		//!< Vertical list.
};

FB_DEFINE_ENUM( FBSDK_DLL, ListStyle );	// FBPropertyListStyle

//! List of items.
class FBSDK_DLL FBList : public FBVisualComponent {
    __FBClassDeclare( FBList,FBVisualComponent );
public:
    //! Constructor.
    FBList();

    FBPropertyStringList	Items;			//!< <b>List:</b> Names of items in list.

    FBPropertyInt			ItemIndex;		//!< <b>Read Write Property:</b> Current item index.
    FBPropertyBool			MultiSelect;	//!< <b>Read Write Property:</b> Can multiple items be selected?
    FBPropertyBool			ExtendedSelect;	//!< <b>Read Write Property:</b> Extended selection state?
    FBPropertyListStyle		Style;			//!< <b>Read Write Property:</b> Style or direction of list.

    FBPropertyEvent			OnChange;		//!< <b>Event:</b> List changed.
    FBPropertyEvent			OnDragAndDrop;	//!< <b>Event:</b> Drag and drop event.

    /** Returns whether or not the item \e pIndex is currently selected.
    *	\param	pIndex	Index to see if select or not.
    *	\return \b true if item at \e pIndex is selected.
    */
    virtual bool IsSelected( int pIndex );

    /** Set the current selected state of item at \e pIndex to \e pSelected.
    *	\param	pIndex		Index to affect item at.
    *	\param	pSelected	State to set item at \e pIndex to.
    */
    virtual void Selected( int pIndex, bool pSelected );
};

////////////////////////////////////////////////////////////////////////////////////
// FBSlider
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBSlider );

//! Slider.
class FBSDK_DLL FBSlider : public FBVisualComponent {
    __FBClassDeclare( FBSlider,FBVisualComponent );
public:
    //! Constructor.
    FBSlider();

    FBPropertyDouble		Min;				//!< <b>Read Write Property:</b> Minimum value.
    FBPropertyDouble		Max;				//!< <b>Read Write Property:</b> Maximum value.
    FBPropertyDouble		Value;				//!< <b>Read Write Property:</b> Current value.
    FBPropertyOrientation	Orientation;		//!< <b>Read Write Property:</b> Slider orientation.
    FBPropertyDouble		LargeStep;		    //!< <b>Read Write Property:</b> Large step value.
    FBPropertyDouble		SmallStep;		    //!< <b>Read Write Property:</b> Small step value.

    FBPropertyEvent			OnChange;			//!< <b>Event:</b> Slider value changed.
    FBPropertyEvent			OnTransaction;  	//!< <b>Event:</b> Transaction begin/end (continuous value changes). This event property doesn't exist in pyfbsdk.
};

////////////////////////////////////////////////////////////////////////////////////
// FBLayoutRegion
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBLayoutRegion );

//! Layout region.
class FBSDK_DLL FBLayoutRegion : public FBVisualComponent {
    __FBClassDeclare( FBLayoutRegion,FBVisualComponent );
public:
    //! Constructor.
    FBLayoutRegion();
};

////////////////////////////////////////////////////////////////////////////////////
// FBThermometer
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBThermometer );

//! Thermometer.
class FBSDK_DLL FBThermometer : public FBVisualComponent {
    __FBClassDeclare( FBThermometer,FBVisualComponent );
public:
    //! Constructor.
    FBThermometer();

    FBPropertyFloat		Min;			//!< <b>Read Write Property:</b> Minimum value.
    FBPropertyFloat		Max;			//!< <b>Read Write Property:</b> Maximum value.
    FBPropertyFloat		Value;			//!< <b>Read Write Property:</b> Current value.

    /**
    Reset bounds and value.
    */
    void Clear();
};

////////////////////////////////////////////////////////////////////////////////////
// FBSpread
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBSpread );

//! Different styles of spreadsheet cell styles.
enum FBCellStyle  {	
    kFBCellStyleDefault,		//!< Default cell style.
    kFBCellStyleString,			//!< String.
    kFBCellStyleDouble,			//!< Double.
    kFBCellStyleInteger,		//!< Integer.
    kFBCellStyleButton,			//!< Button.
    kFBCellStyle2StatesButton,	//!< 2 state button.
    kFBCellStyle3StatesButton,	//!< 3 state button.
    kFBCellStyleMenu,			//!< Menu.
    kFBCellStyleVoid,			//!< Void (no value).
    kFBCellStyleView,			//!< View (user definable, you need to specify the view using FBSpread::SetCellView()).
    kFBCellStyleTime            //!< Time.
};

FB_DEFINE_ENUM( FBSDK_DLL, CellStyle ); // FBPropertyCellStyle

__FB_FORWARD( FBSpreadPart );

/** Spreadsheet part.
*	\remarks Due to protected constructor, this can only be created by a child object.
*/
class FBSDK_DLL FBSpreadPart : public FBComponent {
    __FBClassDeclare( FBSpreadPart,FBComponent );
protected:
    /**	Constructor.
    *	\param		pParent	Parent Spreadsheet.
    *	\remarks	This constructor is protected, therefore only children of this object may be created.
    */
    FBSpreadPart( FBSpread* pParent );

public:
    FBPropertyInt			Row;			//!< <b>Read Only Property:</b> Row number.
    FBPropertyInt			Column;			//!< <b>Read Only Property:</b> Column number.
    FBPropertyBool			ReadOnly;		//!< <b>Read Write Property:</b> Is SpreadPart read-only?
    FBPropertyBool			Enabled;		//!< <b>Read Write Property:</b> Is SpreadPart enabled?
    FBPropertyCellStyle		Style;			//!< <b>Read Write Property:</b> Style of cell
    FBPropertyTextJustify	Justify;		//!< <b>Read Write Property:</b> Text justification for SpreadPart

    /**
    Returns the Spread control this part belongs to.
    */
    FBSpread* GetSpread();
};

__FB_FORWARD( FBSpreadCell );

//! Spreadsheet cell.
class FBSDK_DLL FBSpreadCell : public FBSpreadPart {
    __FBClassDeclare( FBSpreadCell, FBSpreadPart );
public:

    /**	Constructor.
    *	\param	pParent	Parent spreadsheet.
    *	\param	pRow	Row to which cell belongs.
    *	\param	pCol	Column to which cell belongs.
    */
    FBSpreadCell( FBSpread* pParent, kReference pRow, int pCol );
};

__FB_FORWARD( FBSpreadRow );

//! Spreadsheet row.
class FBSDK_DLL FBSpreadRow : public FBSpreadPart {
    __FBClassDeclare( FBSpreadRow,FBSpreadPart );
public:
    /**	Constructor.
    *	\param	pParent	Parent spreadsheet.
    *	\param	pRow	User-defined reference to assign to row.
    */
    FBSpreadRow( FBSpread* pParent, kReference pRow );

    //! Remove (destroy) row.
    virtual void Remove();

    /**	Edit the row caption.
    *	This will initiate the UI edit of a row caption.
    *	\return	Operation was successful (\b true or \b false).
    */
    virtual bool EditCaption();

    FBPropertyString		Caption;		//!< <b>Read Write Property:</b> Caption to display with row.
    FBPropertykReference	Parent;			//!< <b>Read Write Property:</b> Parent of row (reference).
    FBPropertyBool			RowSelected;	//!< <b>Read Write Property:</b> Is row selected? 
};

__FB_FORWARD( FBSpreadColumn );

//! Spreadsheet column.
class FBSDK_DLL FBSpreadColumn : public FBSpreadPart {
    __FBClassDeclare( FBSpreadColumn,FBSpreadPart );
public:
    /**	Constructor.
    *	\param	pParent	Parent spreadsheet.
    *	\param	pCol	Column number.
    */
    FBSpreadColumn( FBSpread* pParent, int pCol );

    FBPropertyString		Caption;		//!< <b>Read Write Property:</b> Caption of the column.
    FBPropertyInt			Width;			//!< <b>Read Write Property:</b> Column width.
    FBPropertyTextJustify	Justify;		//!< <b>Read Write Property:</b> Text justification.
};

//! Base spreadsheet class.
class FBSDK_DLL FBSpread : public FBVisualComponent {
    __FBClassDeclare( FBSpread,FBVisualComponent );
public:
    /** Constructor.
    */
    FBSpread();

    FBPropertyString		Caption;		//!< <b>Read Write Property:</b> Caption to display for spreadsheet.
    FBPropertykReference	Row;			//!< <b>Read Write Property:</b> Current row.
    FBPropertyInt			Column;			//!< <b>Read Write Property:</b> Current column.
    FBPropertyBool			MultiSelect;	//!< <b>Read Write Property:</b> Can there be multiple selections?

    FBPropertyEvent			OnCellChange;	//!< <b>Event:</b> Cell value changed.
    FBPropertyEvent			OnRowClick;		//!< <b>Event:</b> Row clicked.
    FBPropertyEvent			OnColumnClick;	//!< <b>Event:</b> Column clicked.
    FBPropertyEvent			OnDragAndDrop;	//!< <b>Event:</b> Drag and drop event.

    /** Add a row.
    *	\param	pString		Text to display with row.
    *	\param	pRef		User-defined reference for row(default=0).
    */
    virtual void RowAdd( const char * pString, kReference pRef=0 );

    /** Sort rows.
    *	\param	pAscending	If \b true, sort ascending.
    */
    virtual void RowSort( bool pAscending=true );

    /**	Add a column.
    *	\param	pString		Text to display with column.
    *	\param	pRef		User-define column reference number(default=0).
    */
    virtual void ColumnAdd( const char * pString, kReference pRef=0 );

    /** Get the current cell.
    *	\return	A copy of the the current cell.
    */
    virtual FBSpreadCell GetCurrentCell();

    /**	Get a cell from row and column numbers.
    *	\param	pRef		Row reference.
    *	\param	pColumn		Column number.
    *	\return	A copy of the cell.
    */
    virtual FBSpreadCell GetCell( kReference pRef,int pColumn );

    /**	Get a column from a column number.
    *	\param	pColumn		Column number.
    *	\return A copy of column.
    */
    virtual FBSpreadColumn GetColumn( int pColumn );

    /**	Get a row from a row reference.
    *	\param	pRef	Reference to a row.
    *	\return	A copy of the row.
    */
    virtual FBSpreadRow GetRow( kReference pRef );

    /** Set a cell's value.
    *	\param	pRef		Row of cell.
    *	\param	pColumn		Column of cell.
    *	\param	pString		Cell's new value.
    */
    virtual void SetCell( kReference pRef,int pColumn, const char*        pString );

    //@{
    /** Set a cell's value.
    *	\param	pRef		Row of cell.
    *	\param	pColumn		Column of cell.
    *	\param	pValue		Cell's new value.
    */
    virtual void SetCell( kReference pRef,int pColumn, int		    pValue );
    virtual void SetCell( kReference pRef,int pColumn, kLongLong    pValue );
    virtual void SetCell( kReference pRef,int pColumn, double	    pValue );
    //@}

    /**	Get a cell's value.
    *	\param	pRef		Row of cell.
    *	\param	pColumn		Column of cell.
    *	\retval	pString		String value of cell.
    */
    virtual void GetCell( kReference pRef,int pColumn, const char* &pString );

    //@{
    /**	Get a cell's value.
    *	\param	pRef		Row of cell.
    *	\param	pColumn		Column of cell.
    *	\retval	pValue		Numeric value of cell.
    */
    virtual void GetCell( kReference pRef,int pColumn, int		    &pValue );
    virtual void GetCell( kReference pRef,int pColumn, kLongLong    &pValue );
    virtual void GetCell( kReference pRef,int pColumn, double	    &pValue );
    //@}

    /** Set a cell's internal toolkit view.
    *	\param	pRef		Row of cell.
    *	\param	pColumn		Column of cell.
    *	\param	pView		View to use to set cell's view.
    */
    virtual void SetCellView( kReference pRef,int pColumn, HIKtView pView );

    /**	Get a cell's internal toolkit view.
    *	\param	pRef		Row of cell.
    *	\param	pColumn		Column of cell.
    *	\retval pView		Handle of view.
    */
    virtual void GetCellView( kReference pRef,int pColumn, HIKtView &pView );

    /** Clear spreadsheet
    *	This function will empty spreadsheet of all its rows, columns and cells.
    */
    virtual void Clear();
};

__FB_FORWARD( FBEventSpread );

//! Spreadsheet event.
class FBSDK_DLL FBEventSpread : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventSpread( HKEventBase pEvent );

    FBPropertyInt Row;				//!< <b>Read Only Property:</b> Row of event.
    FBPropertyInt Column;			//!< <b>Read Only Property:</b> Column of event.

    /** <b>Read Only Property:</b> Action associated to the spread event. 
    *	This value is not always set and depends on the action being performed on the spreadsheet.
    */
    FBPropertyInt Action;
};

////////////////////////////////////////////////////////////////////////////////////
// FBVisualContainer
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBVisualContainer );
__FB_FORWARD( FBImage );

//! Different icon positions possible.
enum FBIconPosition {	
    kFBIconLeft,		//!< Icon on left of text.
    kFBIconTop,			//!< Icon on top of text.
};

FB_DEFINE_ENUM( FBSDK_DLL, IconPosition ); // FBPropertyIconPosition

//! Used to create a container for a tool UI.
class FBSDK_DLL FBVisualContainer : public FBVisualComponent {
    __FBClassDeclare( FBVisualContainer,FBVisualComponent );
public:
    /** Constructor.
    */
    FBVisualContainer();

	/**	Set an item's icon.
	*	\param	pRef					Reference to item in container.
	*	\param	pImage					Handle to image to use.
	*	\param	pUseACopyOfTheImage		Create a copy of the image?(default=true)
	*	\return	Operation was successful (\b true or \b false).
	*/
	bool ItemIconSet( kReference pRef, FBImage* pImage, bool pUseACopyOfTheImage=true );

    /**	Set an item's icon.
    *	\param	pRef		Reference to item in container.
    *	\param	pFilename	Name of file where image is located.
    *	\return	Operation was successful (\b true or \b false).
    */
    virtual bool ItemIconSet( kReference pRef, const char *pFilename );

    /**	Edit a container item.
    *	\param	pRef	 Reference of container to edit.
    *	\return	Operation was successful (\b true or \b false).
    */
    virtual bool ItemNameEdit( kReference pRef );

    /** Get the selected item.
    *	\return Index of current selection.
    */
    virtual int GetSelection();

    FBPropertyStringList	Items;					//!< <b>List:</b> Names of items in container.

    FBPropertyInt			ItemIndex;				//!< <b>Read Write Property:</b> Current item selected.
    FBPropertyOrientation	Orientation;			//!< <b>Read Write Property:</b> Orientation of container.
    FBPropertyBool			ItemWrap;				//!< <b>Read Write Property:</b> Are items wrapped when enough space is available?
    FBPropertyIconPosition	IconPosition;			//!< <b>Read Write Property:</b> Where the icon is positioned for the items.
    FBPropertyInt			ItemWidth;				//!< <b>Read Write Property:</b> Item width.
    FBPropertyInt			ItemHeight;				//!< <b>Read Write Property:</b> Item height.

    FBPropertyEvent			OnChange;				//!< <b>Event:</b> Container contents changed.
    FBPropertyEvent			OnDblClick;				//!< <b>Event:</b> Double click.
    FBPropertyEvent			OnDragAndDrop;			//!< <b>Event:</b> Drag and Drop event.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEditTimeCode
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEditTimeCode );

class FBSDK_DLL FBEditTimeCode : public FBVisualComponent {
    __FBClassDeclare( FBEditTimeCode,FBVisualComponent );
public:
    /** Constructor.
    */
    FBEditTimeCode();

    FBPropertyTime			Value;			//!< <b>Read Write Property:</b> Current timecode value.

    FBPropertyEvent			OnChange;		//!< <b>Event:</b> Timecode changed.
};

////////////////////////////////////////////////////////////////////////////////////
// FBTree
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBTreeNode		);
__FB_FORWARD( FBTree			);

////////////////////////////////////////////////////////////////////////////////////
// FBEventTreeClick
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEventTree );

//! Tree node different event type.
enum FBEventTreeWhy
{
    kFBEventTreeExpand,
    kFBEventTreeCollapse,
    kFBEventTreeHideNode,
    kFBEventTreeUnhideNode
};

FB_DEFINE_ENUM( FBSDK_DLL, EventTreeWhy ); // FBPropertyEventTreeWhy

//! FBTree node event
class FBSDK_DLL FBEventTree : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventTree( HKEventBase pEvent );

    FBPropertyEventTreeWhy  Why;        //!< <b>Read Write Property:</b> Reason of the event.
    FBPropertyTreeNode      TreeNode;	//!< <b>Read Write Property:</b> Tree node.
};

__FB_FORWARD( FBEventTreeSelect );

//! FBTree selection event
class FBSDK_DLL FBEventTreeSelect : public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventTreeSelect( HKEventBase pEvent );
    FBPropertyTreeNode TreeNode;		    //!< <b>Read Write Property:</b> Selected tree node.
};

//! A node in the tree view.
class FBSDK_DLL FBTreeNode : public FBComponent 
{
    __FBClassDeclare( FBTreeNode,FBComponent );
public:
    /** Constructor
    *   \param  pTree   Parent tree.
    *   \param  pObject Internal object.
    */
    FBTreeNode(FBTree* pTree, HIObject pObject);

    FBPropertykReference	Reference;      //!< <b>Read Write Property:</b> Data to be associated to this node.
    FBPropertyBool			Checked;		//!< <b>Read Write Property:</b> Is FBTreeNode checked.
};

//! PropertyList of nodes in the tree view.
class FBSDK_DLL FBPropertyListTreeNode: public FBPropertyBaseList< FBTreeNode* >
{
private:
    FBArrayTemplate< FBTreeNode* > mItems;

public:
    FBPropertyListTreeNode();

    virtual ~FBPropertyListTreeNode();

    virtual void Refresh ();

    /**	Add a property to the list.
    *	\param pItem Property to add.
    *	\return Index where property was inserted.
    */
    virtual int Add( FBTreeNode* pNode );

    /**	Remove property at \e pIndex.
    *	\param pIndex  Index where property is to be removed.
    */
    virtual void RemoveAt( int pIndex );

    /**	[] operator overload.
    *	\param pIndex  Index of property to access.
    *	\return Property at \e pIndex.
    */
    virtual FBTreeNode* operator[]( int pIndex );

    /**	Get the number of properties in the list.
    *	\return The number of properties in the list.
    */
    virtual int GetCount ();
};

//! Tree list view.
class FBSDK_DLL FBTree : public FBVisualComponent 
{
    __FBClassDeclare( FBTree,FBVisualComponent );
public:
    //! Constructor.
    FBTree();

    /**	Get the root node.
    *   \return the root node of the tree.
    */
    FBTreeNode* GetRoot();

    /**	Clear the tree (remove all nodes).
    */
    void Clear();

    /**	Insert node at the end.
    *   \param  pNode   Node under which the new node will appear.
    *   \param  pName   Text to display for this node.
    *   \return the newly created node.
    */
    FBTreeNode* InsertLast( FBTreeNode* pNode, const char* pName );

    FBPropertyEvent		OnSelect;           //!< <b>Event:</b> A node was selected.  Use FBEventTreeSelect to cast event.

    FBPropertyEvent		OnClick;            //!< <b>Event:</b> Click on a node of the tree. Use OnSelect.
    FBPropertyEvent		OnClickCheck;       //!< <b>Event:</b> Click on a node checkbox of the tree.
    FBPropertyEvent		OnDblClick;         //!< <b>Event:</b> Double-Click on a node of the tree. Use FBEventTreeSelect to cast event.
    FBPropertyEvent		OnDeselect;         //!< <b>Event:</b> Deselection on a node of the tree.
    FBPropertyEvent		OnExpanded;         //!< <b>Event:</b> Click on the "+" sign before a non-leaf node
    FBPropertyEvent		OnExpanding;        //!< <b>Event:</b> Is fired before the node expand. To refuse expanding set AllowExpansion to false.
    FBPropertyEvent		OnCollapsed;        //!< <b>Event:</b> Click on the "-" sign before a non-leaf node.
    FBPropertyEvent		OnCollapsing;       //!< <b>Event:</b> Fired before the node collapse. To refuse collapsing, set AllowCollapse to false.
    FBPropertyEvent		OnChange;           //!< <b>Event:</b> Change of the selection.
    FBPropertyEvent		OnDragAndDrop;      //!< <b>Event:</b> Drag and drop of an element.
    FBPropertyEvent		OnEditNode;         //!< <b>Event:</b> Called upon node edition.

    FBPropertyInt			SelectedCount;      //!< <b>Read Only Property:</b> Count of selected items.
    FBPropertyInt			VisibleItemCount;   //!< <b>Read Only Property:</b> Count of visible items.
    FBPropertyBool			AllowExpansion;     //!< <b>Read Write Property:</b> When OnExpanding occurs, set this to true to allow expansion.
    FBPropertyBool			AllowCollapse;      //!< <b>Read Write Property:</b> When OnCollapsing occurs, set this to true to allow collapse.  
    FBPropertyBool			MultiDrag;          //!< <b>Read Write Property:</b> Tells whether multiple drag/drop is allowed or not.
    FBPropertyBool			AutoScroll;         //!< <b>Read Write Property:</b> If AutoScroll property is True then the tree window will be automatically scrolled when the user drags item(s) over the boundaries of the tree. 
    FBPropertyInt			Indent;             //!< <b>Read Write Property:</b> Use Indent to determine how far child nodes are indented from their parent nodes when the parent is expanded.   
    FBPropertyBool			CheckBoxes;         //!< <b>Read Write Property:</b> Draw check boxe for each node.  
    FBPropertyBool			ShowLines;			//!< <b>Read Write Property:</b> On node selection, will draw entire line selected	
    FBPropertyInt			ItemHeight;         //!< <b>Read Write Property:</b> Height of an item.
    FBPropertyBool			MultiSelect;        //!< <b>Read Write Property:</b> Tells whether multiple selection is allowed or not. 
    FBPropertyBool			EditNodeOn2Select;  //!< <b>Read Write Property:</b> Set to true, to allow automatic node editing on second select.  
    FBPropertyInt			TreeHeight;         //!< <b>Read Only Property:</b> Height of the tree.  
    FBPropertyInt			TreeWidth;          //!< <b>Read Only Property:</b> Width of the tree.
    FBPropertyBool			SelectionActive;    //!< <b>Read Write Property:</b> Tells whether selection is allowed or not.
    FBPropertyBool			DeselectOnCollapse; //!< <b>Read Write Property:</b> Tells whether node are deselected if parent node is collapsed.
    FBPropertyBool			NoSelectOnDrag;     //!< <b>Read Write Property:</b> Tells whether node are selected if drag is start and node is not already selected.  
    FBPropertyBool			NoSelectOnRightClick;  //!< <b>Read Write Property:</b> Tells whether node are selected if right click on node.
    FBPropertyBool			HighlightOnRightClick; //!< <b>Read Write Property:</b> Hightlight node on right click. 
    FBPropertyBool			AutoScrollOnExpand;    //!< <b>Read Write Property:</b> Allow automatic scroll on expand, default is true.
    FBPropertyBool			AutoExpandOnDragOver;  //!< <b>Read Write Property:</b> Allow automatic expand on drag over, default is false.
    FBPropertyBool			AutoExpandOnDblClick;  //!< <b>Read Write Property:</b> Allow automatic expand on double click, default is false.
    FBPropertyListTreeNode  SelectedNodes;         //!< <b>Read Only Property:</b> List of selected nodes.
};

////////////////////////////////////////////////////////////////////////////////////
// FBView
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBView );

//! Generic view.
class FBSDK_DLL FBView : public FBVisualComponent {
    __FBClassDeclare( FBView,FBVisualComponent );
public:
    /** Constructor
    */
    FBView();

    IObject_Declare(override);	// Interface to IObject

    /**	Create an OpenGL pbuffer.
    *	\return	Operation was successful (\b true or \b false).
    */
	bool CreatePBuffer();

	/**	Refresh view.
    *	\param	pNow		If \b true, refresh immediately (default = \b false).
    */
    virtual void Refresh(bool pNow=false) override;

    /** Checks if object is a view.
    *	\return	Is object a view? (\b true or \b false)
    */
    virtual bool IsView() override;

    /**	Draw a string in the view.
    *	\param	pText		Text to draw.
    *	\param	pX			X position of string.
    *	\param	pY			Y position of string.
    *	\param	pEnable		Is string enabled? (default =-1)
    */
    virtual void DrawString(const char *pText,float pX,float pY, int pEnable=-1);

    /**	Set view's viewport
    *	\param	pX	Viewport X value.
    *	\param	pY	Viewport Y value.
    *	\param	pW	Viewport W (width) value.
    *	\param	pH	Viewport H (height) value.
    *	\return	Operation was successful (\b true or \b false).
    */
    virtual bool SetViewport(int pX,int pY,int pW,int pH);

    FBPropertyBool		GraphicOGL;   	//!< <b>Read Only Property:</b> Indicates if the view is OpenGL.
    FBPropertyBool		DoubleBuffer;   //!< <b>Read Only Property:</b> Indicates if the view is double buffered.
};

////////////////////////////////////////////////////////////////////////////////////
// FBProgress
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBProgress );

//! Progress bar.
class FBSDK_DLL FBProgress : public FBVisualComponent {
    __FBClassDeclare( FBProgress,FBVisualComponent );
public:
    /** Constructor.
    */
    FBProgress();

    /** Start progress, must be called before set Text & Percent property
    */
    void ProgressBegin();
    /** End progress, must be called to reset progress bar UI to normal status after finishing the task.
    */
    void ProgressDone();

    /** Return true if User is pressing and holding "ESC" key to request the cancellation. 
    *   Must be called in between ProgressBegin()/ProgressDone().
    */
    bool UserRequestCancell();

    FBPropertyString	Caption;	//!< <b>Read Write Property:</b> Caption to be displayed for progress bar.
    FBPropertyString	Text;		//!< <b>Read Write Property:</b> Text to display on progress bar. Must be used in between ProgressBegin()/ProgressDone()
    FBPropertyInt		Percent;	//!< <b>Read Write Property:</b> Percent completed for the operation. Must be used called in between ProgressBegin()/ProgressDone()
};

////////////////////////////////////////////////////////////////////////////////////
// FBPopup
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBPopup );

/** Popup window.
*	This class lets a window (inheriting from FBLayout) be created for another interface.
*/
class FBSDK_DLL FBPopup : public FBLayout {
    __FBClassDeclare( FBPopup,FBLayout );
public:
    /** Constructor.
    */
    FBPopup();

    /**	Show popup.
    *	\param	pParent		Parent object for popup
    *	\return	Operation was successful (\b true or \b false).
    */
    virtual bool Show( FBVisualComponent* pParent=NULL );

    /**	Close popup.
    *	\param	pOk		Equivalent of \b OK button clicked if \b true (default = \b false).
    */
    virtual void Close(bool pOk=false);

    FBPropertyString		Caption;	//!< <b>Read Write Property:</b> Caption to display in popup.
    FBPropertyBool			Modal;		//!< <b>Read Write Property:</b> Modal?
};

////////////////////////////////////////////////////////////////////////////////////
// FBFilePopup
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBFilePopup );

//! Different types of file popup windows.
enum FBFilePopupStyle { 
    kFBFilePopupOpen,		//!< Open file popup (Shows 'Open Directory').
    kFBFilePopupSave		//!< Save file popup (Shows 'Save Directory').
};

FB_DEFINE_ENUM( FBSDK_DLL, FilePopupStyle ); // FBPropertyFilePopupStyle

//! File Popup (for open/save).
class FBSDK_DLL FBFilePopup : public FBVisualComponent {
    __FBClassDeclare( FBFilePopup,FBVisualComponent );
public:
    /** Constructor.
    */
    FBFilePopup();

    /**	Execute file popup.
    *	\return	\b true if \b OK is clicked by user.
    */
    virtual bool Execute();

    FBPropertyString			Caption;		//!< <b>Read Write Property:</b> Caption to put in popup window.
    FBPropertyString			FileName;		//!< <b>Read Write Property:</b> File selected.
    FBPropertyString			Path;			//!< <b>Read Write Property:</b> Path of file selected.
    FBPropertyString			FullFilename;	//!< <b>Read Only Property:</b> Full filename (path and file).
    FBPropertyString			Filter;			//!< <b>Read Write Property:</b> Filter to use for popup window file selection.
    FBPropertyFilePopupStyle	Style;			//!< <b>Read Write Property:</b> Style of file popup.
};

////////////////////////////////////////////////////////////////////////////////////
// FBFolderPopup
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBFolderPopup );

//! Folder Popup (for selecting a directory).
class FBSDK_DLL FBFolderPopup : public FBVisualComponent {
    __FBClassDeclare( FBFolderPopup,FBVisualComponent );
public:
    /** Constructor.
    */
    FBFolderPopup();

    /**	Execute folder popup.
    *	\return	\b true if \b OK is clicked by user.
    */
    virtual bool Execute();

    FBPropertyString			Caption;		//!< <b>Read Write Property:</b> Caption to put in popup window.
    FBPropertyString			Path;			//!< <b>Read Write Property:</b> Path of folder selected.
};

/**	Dialog popup box.
*	Opens a message box containing a message and up to three buttons. Waits for the user to click a button.
*	\param	pBoxTitle			Title of message box.
*
*	\param	pMessage			Message to place in box.
*	\param	pButton1Str			String for first button (Cannot be NULL).
*	\param	pButton2Str			String for second button (NULL will not create a button).
*	\param	pButton3Str			String for third button (NULL will not create a button).
*	\param	pDefaultButton		Indicates the default (pre-selected) button (default is 0).
*	\param	pScrolledMessage	Scroll message (default is 0).
*	\return	The number of the button selected.
*/
FBSDK_DLL int FBMessageBox( const char* pBoxTitle, const char* pMessage, const char* pButton1Str, const char* pButton2Str=NULL, const char* pButton3Str=NULL, int pDefaultButton=0, int pScrolledMessage=0);

/**	Dialog popup box with a check box.
*	Opens a message box containing a message, up to three buttons and a check box. Waits for the user to click a button.
*
*	\param	pBoxTitle			Title of message box.
*	\param	pMessage			Message to place in box.
*	\param	pButton1Str			String for first button (Cannot be NULL).
*	\param	pButton2Str			String for second button (NULL will not create a button).
*	\param	pButton3Str			String for third button (NULL will not create a button).
*	\param	pCheckBoxStr		Check box string (Cannot be NULL).
*	\retval	pCheckBoxValue		Check box value.
*	\param	pDefaultButton		Indicates the default (pre-selected) button (default is 0).
*	\param	pScrolledMessage	Scroll message (default is 0).
*	\return	The number of the button selected.
*/
FBSDK_DLL int FBMessageBoxWithCheck( const char* pBoxTitle, const char* pMessage, const char* pButton1Str, const char* pButton2Str, const char* pButton3Str, const char* pCheckBoxStr, bool& pCheckBoxValue, int pDefaultButton=0, int pScrolledMessage=0);

//! User input types for a popup
enum FBPopupInputType{
    kFBPopupBool,		//!< Boolean input.
    kFBPopupChar,		//!< Character input.
    kFBPopupString,		//!< String input.
    kFBPopupInt,		//!< Integer input.
    kFBPopupFloat,		//!< Float input.
    kFBPopupDouble,		//!< Double input.
    kFBPopupPassword	//!< Password input (String with '*'s).
};

/**	Dialog popup box to get user input.
*	Opens a message box, with up to three buttons, asking the user to enter data. 
*	The type of data to be entered is specified by the \e pValue and \e pValueType parameters.
*
*	\param	pBoxTitle			Title of message box.
*	\param	pMessage			Message to place in box.
*	\retval	pValue				Value entered by user (must correspond with pValueType).
*	\param	pValueType			Type of pointer specified in pValue.
*	\param	pButton1Str			String for first button (Cannot be NULL).
*	\param	pButton2Str			String for second button (NULL will not create a button).
*	\param	pButton3Str			String for third button (NULL will not create a button).
*	\param	pDefaultButton		Indicates the default (pre-selected) button(default=0).
*	\param	pLastButtonCancel	Indicates the last button is Cancel (if more than one button) so pValue won't be updated if the last button is clicked.
*	\return	The number of the button selected.
*/
FBSDK_DLL int FBMessageBoxGetUserValue( const char* pBoxTitle, const char* pMessage, void* pValue, FBPopupInputType pValueType, const char* pButton1Str, const char* pButton2Str=NULL, const char* pButton3Str=NULL, int pDefaultButton=0, bool pLastButtonCancel = true );

////////////////////////////////////////////////////////////////////////////////////
// FBMemo
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBMemo );

//! Multi-line text input
class FBSDK_DLL FBMemo : public FBEdit {
    __FBClassDeclare( FBMemo,FBEdit );
public:
    //! Constructor.
    FBMemo();

    /**	Set the content of the memo.
    *	\param pLines Content of the memo from will be set to it.
    */
    void SetStrings(FBStringList* pLines);

    /**	Get the content of the memo.
    *	\param pLines Content of the memo will be copied to it.
    */
    void GetStrings(FBStringList* pLines);
};

////////////////////////////////////////////////////////////////////////////////////
// FBWebView
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBWebView );

//! Web viewer
class FBSDK_DLL FBWebView : public FBVisualComponent {
    __FBClassDeclare( FBWebView,FBVisualComponent );
public:
    //! Constructor.
    FBWebView();

    /**	Load the specified Url.
    *	\param pURL url to load in the WebView.
    */
    void Load(const char* pURL);
};


////////////////////////////////////////////////////////////////////////////////////
// FBFCurveEditor
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBFCurveEditor );

//! FCurve editor.
class FBSDK_DLL FBFCurveEditor : public FBVisualComponent {
    __FBClassDeclare( FBFCurveEditor,FBVisualComponent );
public:
    //! Constructor.
    FBFCurveEditor();

    /**	Add an animation node to the editor.
    *	\param pNode Animation node to show in the editor.
    */
    void AddAnimationNode(FBAnimationNode* pNode);
    /**	Remove an animation node from the editor.
    *	\param pNode Animation node to hide from editor.
    */
    void RemoveAnimationNode(FBAnimationNode* pNode);

    /**	Add an animatable property to the editor.
    *	\param pProperty Property to show in the editor.
    */
    void AddProperty(FBPropertyAnimatable* pProperty);
    /**	Remove animatable property  from the editor.
    *	\param pProperty Property to hide from editor.
    */
    void RemoveProperty(FBPropertyAnimatable* pProperty);

    /**	Clear the editor.
    */
    void Clear();
};

////////////////////////////////////////////////////////////////////////////////////
// FBFCurveEvent
////////////////////////////////////////////////////////////////////////////////////

/**
*	This enum indicates what event happened in the FCurve Editor.
*/
enum FBFCurveEditorEventType	{
	kFBUnspecified,				//!< Unspecified event
	kFBGhostKeep,				//!< Ghost Keep button pressed
	kFBGhostSwap,				//!< Ghost Swap button pressed
	kFBGhostClear,				//!< Ghost Clear button pressed
};

FB_DEFINE_ENUM( FBSDK_DLL, FCurveEditorEventType );

//! This class is used when receiving a callback about an interaction that the user has done in the FCurve Editor.
class FBSDK_DLL FBFCurveEditorEvent : public FBEvent 
{
public:
	/**	Constructor.
	*	\param pEvent Base event (internal) to obtain information from.
	*/
	FBFCurveEditorEvent( HKEventBase pEvent );
	
	FBPropertyFCurveEditorEventType	EventType;    //!< <b>Read Only Property:</b> Event type, please see the FBFCurveEditorEventType for the possible types.
};

////////////////////////////////////////////////////////////////////////////////////
// FBFCurveEditorUtility
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBFCurveEditorUtility );

/**	FBFCurveEditor Utility class
*	Utility class allowing different operations on a FBFCurveEditor or on the main FCurveEditor
*/
class FBSDK_DLL FBFCurveEditorUtility : public FBComponent 
{
    __FBClassDeclare( FBFCurveEditorUtility, FBComponent );
	
public:
	/**	Add external FCurves to the FCurve Editor, all layers will be copied.
	*	\param	pObjectName		Name of the object that will contain the property/curves.
	*	\param	pPropertyName	Name of the property that will contain the curves. A search will be done to see if that property exists, if so, it will be used, otherwise a new one will be created.
	*	\param	pPropertyType	Property type for the new property.
	*	\param	pFCurve			Original FCurves to be copied.
	*	\param	pEditor			Pointer to a FBFCurveEditor for adding the FCurve to that custom editor, if required. The default FCurve Editor will always add the external FCurves.
    *	\return	A pointer to a FBProperty object if successful, NULL otherwise.
    */
	FBProperty* AddExternalCurves(const char* pObjectName, const char* pPropertyName, const FBPropertyType pPropertyType, FBAnimationNode* pFCurve, FBFCurveEditor* pEditor = NULL);

	/**	Add external FCurves to the FCurve Editor, all layers will be copied.
	*	\param	pObjectName		Name of the object that will contain the property/curves.
	*	\param	pPropertyName	Name of the property that will contain the curves. A search will be done to see if that property exists, if so, it will be used, otherwise a new one will be created
	*	\param	pProperty		Property containing the original FCurves; all layers will be copied.
	*	\param	pEditor			Pointer to a FBFCurveEditor for adding the FCurve to that custom editor, if required. The default FCurve Editor will always add the external FCurves.
    *	\return	A pointer to a FBProperty object if successful, NULL otherwise.
    */
	FBProperty* AddExternalCurves(const char* pObjectName, const char* pPropertyName, FBProperty* pProperty, FBFCurveEditor* pEditor = NULL);

	/**	Add external FCurves to the FCurve Editor, only the base layer will be copied.
	*	\param	pObjectName		Name of the object that will contain the property/curves.
	*	\param	pPropertyName	Name of the property that will contain the curves. A search will be done to see if that property exists, if so, it will be used, otherwise a new one will be created
	*	\param	pPropertyType	Property type for the new property.
	*	\param	pFCurve			Original FCurves to be copied.
	*	\param	pEditor			Pointer to a FBFCurveEditor for adding the FCurve to that custom editor, if required. The default FCurve Editor will always add the external FCurves.
    *	\return	A pointer to a FBProperty object if successful, NULL otherwise.
    */
	FBProperty* AddExternalCurves(const char* pObjectName, const char* pPropertyName, const FBPropertyType pPropertyType, FBXSDK_NAMESPACE::FbxAnimCurveNode* pFCurve, FBFCurveEditor* pEditor = NULL);

	/**Add external FCurves to the FCurve Editor, all layers will be copied if the stack is provided.
	*	\param	pObjectName		Name of the object that will contain the property/curves.
	*	\param	pPropertyName	Name of the property that will contain the curves. A search will be done to see if that property exists, if so, it will be used, otherwise a new one will be created
	*	\param	pProperty		Property containing the original FCurves.
	*	\param	pStack			Animation stack for getting all the animation layers, NULL to use only the base layer.
	*	\param	pEditor			Pointer to a FBFCurveEditor for adding the FCurve to that custom editor, if required. The default FCurve Editor will always add the external FCurves.
    *	\return	A pointer to a FBProperty object if successful, NULL otherwise.
    */
	FBProperty* AddExternalCurves(const char* pObjectName, const char* pPropertyName, FBXSDK_NAMESPACE::FbxProperty* pProperty, FBXSDK_NAMESPACE::FbxAnimStack* pStack = NULL, FBFCurveEditor* pEditor = NULL);

	/**	Remove external FCurve from the FCurve Editor.
	*	\param	pProperty		Property to remove.
    *	\return	True if successful, false otherwise.
    */
	bool RemoveExternalCurves(FBProperty * pProperty);

	/**	Update the FCurve for a particular property, without creating a new property. All layers will be copied.
	*	\param	pProperty		Property to update.
	*	\param	pFCurve			Original FCurves to be copied.
    *	\return	True if successful, false otherwise.
    */
	bool UpdateCurves(FBProperty* pProperty, FBAnimationNode* pFCurve);

	/**	Update the FCurve for a particular property, without creating a new property. All layers will be copied.
	*	\param	pProperty		Property to update.
	*	\param	pSrcProperty	Original FCurves from the property to be copied.
    *	\return	True if successful, false otherwise.
    */
	bool UpdateCurves(FBProperty* pProperty, FBProperty* pSrcProperty);

	/**	Update the FCurve for a particular property, without creating a new property. Only the base layer will be copied.
	*	\param	pProperty		Property to update.
	*	\param	pFCurve			Original FCurves to be copied.
    *	\return	True if successful, false otherwise.
    */
	bool UpdateCurves(FBProperty* pProperty, FBXSDK_NAMESPACE::FbxAnimCurveNode* pFCurve);

	/**	Update the FCurve for a particular property, without creating a new property. All layers will be copied if the stack is provided.
	*	\param	pProperty		Property to update.
	*	\param	pFbxProperty	Property to get the curves from.
	*	\param	pStack			Animation stack for getting all the animation layers, NULL to use only the base layer.
    *	\return	True if successful, false otherwise.
    */
	bool UpdateCurves(FBProperty* pProperty, FBXSDK_NAMESPACE::FbxProperty* pFbxProperty, FBXSDK_NAMESPACE::FbxAnimStack* pStack);

	/**	Get the FCurve of a particular property. This will copy all layers.
	*	\param	pProperty		Property to get the curves from.
	*	\param	pFCurve			FCurve that will receive the data from the property.
    *	\return	True if successful, false otherwise.
    */
	bool GetCurves(FBProperty* pProperty, FBAnimationNode* pFCurve);

	/**	Get the FCurve of a particular property. This will copy all layers.
	*	\param	pProperty		Property to get the curves from.
	*	\param	pDestProperty	Property that will receive the data from the source property.
    *	\return	True if successful, false otherwise.
    */
	bool GetCurves(FBProperty* pProperty, FBProperty* pDestProperty);

	/**	Get the FCurve of a particular property. Only the base layer will be copied.
	*	\param	pProperty		Property to get the curves from.
	*	\param	pFCurve			FCurve that will receive the data from the property.
    *	\return	True if successful, false otherwise.
    */
	bool GetCurves(FBProperty* pProperty, FBXSDK_NAMESPACE::FbxAnimCurveNode* pFCurve);

	/**	Get the FCurve of a particular property. All layers will be copied if the stack is provided.
	*	\param	pProperty		Property to get the curves from.
	*	\param	pFbxProperty	Property that will receive the data from the property.
	*	\param	pStack			Animation stack for getting all the animation layers, NULL to use only the base layer.
    *	\return	True if successful, false otherwise.
    */
	bool GetCurves(FBProperty* pProperty, FBXSDK_NAMESPACE::FbxProperty* pFbxProperty, FBXSDK_NAMESPACE::FbxAnimStack* pStack);

	/**	Frame keys in the FCurve Editor interface.
	*	\param	pSelectedKeysOnly	If true, only the selected keys will be framed, otherwise all keys will be framed.
	*	\param	pEditor				Pointer to a FBFCurveEditor for framing the keys in that custom editor, NULL to frame in the default editor.
	*	\note	pEditor is currently not supported in this implementation, as the FBFCurveEditor is still in development.
    *	\return	True if successful, false otherwise.
    */
	bool Frame(bool pSelectedKeysOnly, FBFCurveEditor* pEditor = NULL);

	/**	Get all the objects displayed in the left pane of the FCurve Editor.
	*	\param	pObjectList			A list that will be filled with the objects displayed in the FCurve Editor.
    *	\return	True if successful, false otherwise.
    */
	bool GetObjects(FBArrayTemplate<FBComponent *> &pObjectList);

	/**	Get the displayed properties.
	*	\param	pPropertyList		Array that will contain the properties displayed.
	*	\param	pSelectedOnly		If true, only the selected properties will be returned.
   	*	\param	pEditor				Pointer to a FBFCurveEditor for getting the properties in that custom editor, NULL to frame in the default editor.
	*	\return	True if successful, false otherwise.
    */
	bool GetProperties(FBArrayTemplate<FBProperty*> &pProperties, bool pSelectedOnly, FBFCurveEditor* pEditor = NULL);

	/**	Get the displayed time range of the FCurve Editor.
	*	\param	pEditor				Pointer to a FBFCurveEditor where the time span will be get, NULL to get the time span from the default editor.
	*	\return	FCurve Editor time span, default FBTimeSpan if not successful.
    */
	FBTimeSpan GetTimeSpan(FBFCurveEditor* pEditor = NULL);

	/**	Set the displayed time range of the FCurve Editor.
	*	\param	pTimeSpan			The time span that will be set.
	*	\param	pEditor				Pointer to a FBFCurveEditor where the time span will be set, NULL to set the time span on the default editor.
    *	\return	True if successful, false otherwise.
    */
	bool SetTimeSpan(FBTimeSpan pTimeSpan, FBFCurveEditor* pEditor = NULL);

    /** Register to FCurve Editor event.
    *	\param	pOwner	    Owner of the callback that will be called when an event is sent from the FCurve Editor.
    *	\param	pHandler	Callback to call when receiving an event.
 	*	\param	pEditor		Pointer to a FBFCurveEditor to receive the event from that editor, NULL to receive those from the default editor.
    *	\return	True if successful, false otherwise.
   */
    bool RegisterToFCurveEditorEvent(HICallback pOwner, kICallbackHandler pHandler, FBFCurveEditor* pEditor = NULL);

    /** Unregister to FCurve Editor event.
    *	\param	pOwner	    Owner of the callback to unregister.
    *	\param	pHandler	Callback to unregister.
 	*	\param	pEditor		Pointer to the FBFCurveEditor that should be unregistered, NULL to unregister the default editor.
    *	\return	True if successful, false otherwise.
	*/
    bool UnregisterToFCurveEditorEvent(HICallback pOwner, kICallbackHandler pHandler, FBFCurveEditor* pEditor = NULL);

	/**	Get the global object for this class
    *	\return	the global object.
    */
    static FBFCurveEditorUtility& TheOne();

private:
	/**	Constructor.
    *   Protected constructor, use TheOne() access instead. 
    */
    FBFCurveEditorUtility();
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyConnectionEditor
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBPropertyConnectionEditor );

//! Property Connection Editor.
class FBSDK_DLL FBPropertyConnectionEditor : public FBVisualComponent {
    __FBClassDeclare( FBPropertyConnectionEditor,FBVisualComponent );
public:
    //! Constructor.
    FBPropertyConnectionEditor();

    /**	Launch a tree of object connections.
    */
    void PopupTree();

    /**	Launch a list of connected objects.
    */
    void PopupList();

    FBPropertyReference Property;   //!< <b>Read Write Property:</b> Property to edit connections. Set to NULL to disable.
};

////////////////////////////////////////////////////////////////////////////////////
// FBEditProperty
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEditProperty );

/** Property editor widget.
*   This widget allows users to edit the values of a property without having to
*   manually customize the GUI depending on the type of the property being edited.
*   
*   SDK objects can have three types of properties:
*       - An internal property which maps to an actual property that can be seen
*         in the property editor tool of the application. This type of property
*         is usually obtained from the PropertyList data member.
*       - SDK-only property which does not maps onto an existing property of the
*         encapsulated object. The existence of these types of property is
*         often to make the object interface simpler. All the FBPropertyList-types
*         will fall into this category, except for FBPropertyListObjects.
*       - SDK property which maps onto an existing object property, but does so
*         indirectly using function calls instead of direct property access. This
*         is usually for historical reason. In this case the property will usually
*         be present twice in the PropertyList: once as an SDK-Only property and
*         another time as an internal property.
*
*   Another limitation of this widget is that it can only display non hidden
*   internal properties. To get around this issue, the property flag can be
*   changed to unhide it. Doing so will also cause the property to be visible
*   via the property tool.
*
*   @code
*       // In a tool header file...
*       FBEditProperty mEditProperty;
*
*       // In a tool source file...
*       FBModel* lModel = FBFindModelByLabelName( "ModelName" );
*       if( lModel )
*       {
*           FBProperty* lProperty = lModel->PropertyList.Find( "RotationOrder" );
*           if( lProperty &&
*               lProperty->IsInternal() &&
*               !lProperty->GetPropertyFlag( kFBPropertyFlagHideProperty ))
*           {
*               mEditProperty.Property = lProperty;
*           }
*       }
*   @endcode
*   
*/
class FBSDK_DLL FBEditProperty : public FBVisualComponent {
    __FBClassDeclare( FBEditProperty, FBVisualComponent );
public:
    //! Constructor.
    FBEditProperty();

    FBPropertyReference Property;   //!< <b>Read Write Property:</b> Property to edit. Set to NULL to disable.

    FBPropertyDouble    SliderMin;  //!< <b>Read Write Property:</b> Should the property be editable using a slider, set the minimum value atainable with the slider.
    FBPropertyDouble    SliderMax;  //!< <b>Read Write Property:</b> Should the property be editable using a slider, set the maximum value atainable with the slider.
    FBPropertyDouble    SmallInc;   //!< <b>Read Write Property:</b> Indicate the small increment applied when click-draging on the property value (usually right-click-dragging)
    FBPropertyDouble    LargeInc;   //!< <b>Read Write Property:</b> Indicate the large increment applied when click-draging on the property value (usually left-click-dragging)
    FBPropertyDouble    Precision;  //!< <b>Read Write Property:</b> Used to specify the width and precision of the value shown. A value of 7.2 indicates to show at minimum 7 numbers, with 2 decimals.
    FBPropertyInt       CaptionSize;//!< <b>Read Write Property:</b> Indicate how much width should the Property Editor reserve for displaying the property name. 
};


////////////////////////////////////////////////////////////////////////////////////
// FBEditPropertyModern
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBEditPropertyModern );

/** Property editor widget.
*   This is a more modern version of the widget FBEditProperty which is used in the
*   property editor tool of the application.
*
*   See class FBEditProperty for more details.
*/
class FBSDK_DLL FBEditPropertyModern : public FBVisualComponent {
    __FBClassDeclare( FBEditPropertyModern, FBVisualComponent );
public:
    //! Constructor.
    FBEditPropertyModern();

    /** Set the background color index.
    *   Use the system-defined color palette to set the backgound color.
    *   By default the color used is kFBColorIndexStdListBg1
    */
    void SetBackgroundColorIndex( FBColorIndex pIndex );

    FBPropertyReference Property;   //!< <b>Read Write Property:</b> Property to edit. Set to NULL to disable.

    FBPropertyDouble    SliderMin;  //!< <b>Read Write Property:</b> Should the property be editable using a slider, set the minimum value atainable with the slider.
    FBPropertyDouble    SliderMax;  //!< <b>Read Write Property:</b> Should the property be editable using a slider, set the maximum value atainable with the slider.
    FBPropertyDouble    SmallInc;   //!< <b>Read Write Property:</b> Indicate the small increment applied when click-draging on the property value (usually right-click-dragging)
    FBPropertyDouble    LargeInc;   //!< <b>Read Write Property:</b> Indicate the large increment applied when click-draging on the property value (usually left-click-dragging)
    FBPropertyDouble    Precision;  //!< <b>Read Write Property:</b> Used to specify the width and precision of the value shown. A value of 7.2 indicates to show at minimum 7 numbers, with 2 decimals.
};

////////////////////////////////////////////////////////////////////////////////////
// FBBrowsingProperty
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBBrowsingProperty );

//! Property browsing.
class FBSDK_DLL FBBrowsingProperty : public FBVisualComponent {
    __FBClassDeclare( FBBrowsingProperty,FBVisualComponent );
public:
    /** Constructor.
    */
    FBBrowsingProperty();

    /** Add an object whose properties will be displayed.
    *	\param	pObject	Object whose properties will be displayed in the property brwoser.
    */
    void AddObject(FBPlug* pObject);

    /** Remove an object from the property browser.
    *	\param	pObject	Object to remove.
    */
    void RemoveObject(FBPlug* pObject);

    /** Get the number of object displayed in the property browser.
    *	\return	Object currently displayed in the property browser.
    */
    int ObjectGetCount();

    /** Return the object at the specified index.
    *	\param	pIndex	Index of the object to get.
    *	\return	Object at the index specified currently displayed in the property browser.
    */
    FBPlug* ObjectGet(int pIndex);

    /** Add custom button in the header of the property browser.
    *	\param	pCaption	Text to be displayed in the button.
    *	\param	pOwner	    Owner of the callback that will be called when the button is pushed.
    *	\param	pHandler	Callback to call when the button is pushed.
    *	\return	Index of the button added (first button will be 0, second one will be 1...).
    */
    int AddButtonInToolbar(const char* pCaption, HICallback pOwner, kICallbackHandler pHandler);

};

////////////////////////////////////////////////////////////////////////////////////
// FBWidgetHolder
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBWidgetHolder );


/** Native Widget Holder (can be used to embed native Qt Widget inside MoBu UI elements)
*   A Widget holder provides a bridge to instantiate a Native Qt widget into MB framework.
*   This will be used to allow user to create UI with QT designer and hook their
*   created UI into MB.        
*   
*   To allow a FBWidgetHolder to work properly, you need to specify a Creator function.
*   This function will be called when needed to instantiate the native Widget. 
*   
*   Or override WidgetCreate(QWidget* pParent) function in the subclass. 
*
*   \ref $(INSTALLDIR)/bin/config/Scripts/UI/ToolNativeWidgetHolder.py for python usage example.
*/
class FBSDK_DLL FBWidgetHolder : public FBVisualComponent {
    __FBClassDeclare( FBWidgetHolder, FBVisualComponent );
public:

    //! typedef QWidget* (*WidgetCreator)(QWidget* pParent);
    typedef QWidget* (*WidgetCreator)(QWidget* pParent);

    /** Constructor.
    */
    FBWidgetHolder();

    /** Add a function that creates a native widget (a QWidget on Qt platform)
    *   On Qt, this creator function will take a void* (which can be cast as a QWidget) as the Widget parent
    *   On Qt, this creator function should return a void* (which will be a QWidget) that will be the newly created widget
    *
    *	\param	pCreatorFunction	The creator function
    *
    */
    void SetCreator(WidgetCreator pCreatorFunction );

    /** virtual function to be override in subclass. 
    *   This function will be invoked if WidgetCreator is not set.
    */
    virtual QWidget* WidgetCreate(QWidget* pParent);
};

////////////////////////////////////////////////////////////////////////////////////
// FBPlotPopup
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBPlotOptions );
__FB_FORWARD( FBPlotPopup );

//! Plot Popup (for setting options only).
class FBSDK_DLL FBPlotPopup : public FBVisualComponent {
    __FBClassDeclare( FBPlotPopup,FBVisualComponent );
public:
    /** Constructor.
    */
    FBPlotPopup();

    /**	Execute plot popup.
    *	\return	\b true if \b OK is clicked by user.
    */
    virtual bool Popup(const char* pWindowName);

    /**	Get plot options.
    *	\return	plot options.
    */
    FBPlotOptions	GetPlotOptions();

    FBPropertyBool			EnablePlotTranslationOnRootOnly;	//!< <b>Read Write Property:</b> Enable Plot Translation On Root Only option for popup.
    FBPropertyBool			EnableSmartPlotControls;			//!< <b>Read Write Property:</b> Enable Smart Plot option for popup.
    FBPropertyBool			EnablePlotCharacterExtension;		//!< <b>Read Write Property:</b> Enable Plot Character Extension option for popup.
    FBPropertyBool			EnablePlotLockedProperties;			//!< <b>Read Write Property:</b> Enable Plot Locked Properties option for popup.
    FBPropertyBool			EnablePlotAuxEffectors;				//!< <b>Read Write Property:</b> Enable Plot Aux Effectors option for popup.
    FBPropertyBool			EnableEvaluateDeformation;			//!< <b>Read Write Property:</b> Enable Evaluate Deformation option for popup.

    /**	Set plot options.
	*	\param	pPlotOptions		Set the plot options that will be used when displaying the plot popup. First use the GetPlotOptions(), change the options and use the SetPlotOptions() to set them before calling the Popup() function.
    */
	void SetPlotOptions(const FBPlotOptions& pPlotOptions);
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyViewManager, FBPropertyViewList and FBPropertyViewDefinition
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBPropertyViewList	);
FB_FORWARD( FBPropertyViewDefinition	);
__FB_FORWARD( FBPropertyViewManager		);

//! Property view set type.
enum FBPropertyViewType
{
	kFBViewGlobal = 0,		//!< Global property view.
	kFBViewByObjectType,	//!< Class type property view.
	kFBViewByObject			//!< Object property view.
};

/**	FBProperty View List.
*	Hold list of description for view set.
*/
class FBSDK_DLL FBPropertyViewList
{
public:
	//! Is property view list editable.
	bool IsEditable();

	/**	Add property view.
	*	\param	pProperty		Property to add.
	*	\param	pHierarchy		Hierarchy under which property view should be created, each level name is separated by dot (for example "Degrees of Freedom.Translation").
    *	\return	created object (should not be called on non editable view list).
    */
	FBPropertyViewDefinition* AddPropertyView(FBProperty* pProperty, const char* pHierarchy);

	/**	Remove property view from view list.
	*	\param	pPropertyViewDefinition		Property view definition to destroy.
    *	\return	true when pPropertyViewDefinition got removed and free (should not be called on non editable view list).
    */
	bool RemovePropertyView(FBPropertyViewDefinition* pPropertyViewDefinition);

	//! Find property view for pPropertyName in this list.
	FBPropertyViewDefinition* FindPropertyView(const char* pPropertyName);
private:
	//@{
	//! Private constructor.
	FBPropertyViewList();
	//! Private copy constructor.
	FBPropertyViewList(const FBPropertyViewList &);
	//! Private assignment.
	FBPropertyViewList & operator =(const FBPropertyViewList &);
	//@}
};

/**	FBProperty View.
*	View definition for one property.
*/
class FBSDK_DLL FBPropertyViewDefinition 
{
public:
	//! Is property view open at run time.
	bool IsOpen();
	//! Is property view saved on view manager store.
	bool IsSaved();
	//! Is view a folder.
	bool IsFolder(); 
	
	//! Set view open/closed at run time.
	void SetOpen(bool pTrue, bool pApplyUpHierarchy);
	//! Set view to be saved on view manager store.
	void SetSaved(bool pTrue, bool pApplyUpHierarchy);

private:
	//@{
	//! Private constructor.
	FBPropertyViewDefinition();
	//! Private copy constructor.
	FBPropertyViewDefinition(const FBPropertyViewDefinition &);
	//! Private assignment.
	FBPropertyViewDefinition & operator =(const FBPropertyViewDefinition &);
	//@}
};

/**	FBProperty View Manager.
*	Interface to create new property views.
*	There are two ways of creating properties view:
*	- on library load using AddPropertyView, RemovePropertyView, HidePropertyView - example can be found in \OpenRealitySDK\Samples\constraints\CharacterSolver\HIK2014Solver
*	- while application is running using FBPropertyViewList - example can be found in \bin\config\Scripts\Samples\Properties\PropertyViewManager.py
*/
class FBSDK_DLL FBPropertyViewManager : public FBComponent 
{
    __FBClassDeclare( FBPropertyViewManager, FBComponent );

public:
	// ----- VIEW LIST ----- 

	/**	Create new property view list.
	*	\param	pObject			Property view set attached to.
	*	\param	pViewType		Property view set type.
	*	\param	pName			Name for new view list.
    *	\return	created object.
    */
	FBPropertyViewList* CreatePropertyList(FBComponent* pObject, FBPropertyViewType pViewType, const char* pName);

	/**	Remove property view list (only if editable).
	*	\param	pObject			Property view set attached to.
	*	\param	pViewType		Property view set type.
	*	\param	pName			Name for property view list.
    *	\return	True if successful.
    */
	bool RemovePropertyList(FBComponent* pObject, FBPropertyViewType pViewType, const char* pName);

	/**	Find property view list.
	*	\param	pObject			Property view set attached to.
	*	\param	pViewType		Property view set type.
	*	\param	pName			Name of view set.
	*	\return	Found property view set object or NULL.
    */
	FBPropertyViewList* FindPropertyList(FBComponent* pObject, FBPropertyViewType pViewType, const char* pName);

	// ----- GLOBAL VIEW (ALL) ----- 

	/**	Add property view to global ('All') view set.
	*	\param	pClassName		Property owner class name (pClassName if won't be found, a new entry for this class is created).
	*	\param	pPropertyName	Property name.
	*	\param	pHierarchy		Hierarchy under which property view should be created, each level name is separated by dot (for example "Degrees of Freedom.Translation").
	*	\note	This call should be used on library registration, doesn't cause tool refresh.
    *	\return	created object.
    */
	FBPropertyViewDefinition* AddPropertyView(const char* pClassName, const char* pPropertyName, const char* pHierarchy);
	
	/**	Remove property view from global ('All') view set.
	*	\param	pClassName		Property owner class name.
	*	\param	pPropertyName	Property name.
    *	\return	true if succeed (should not be call on system views).
	*	\note	This call should be used on library registration, doesn't cause tool refresh.
    */
	bool RemovePropertyView(const char* pClassName, const char* pPropertyName);

	/**	Hide property view in global ('All') view set.
	*	\param	pClassName		Property owner class name.
	*	\param	pPropertyName	Property name.
	*	\param	pHide			Show/Hide.
	*	\note	This call should be used on library registration, doesn't cause tool refresh.
    */
	void HidePropertyView(const char* pClassName, const char* pPropertyName, bool pHide);

	// ----- REFRESH ----- 

	/**	Force refresh of browsing property tool.
    */
	void RefreshPropertyViews();

	/**	Get the global object for this class
    *	\return	the global object.
    */
    static FBPropertyViewManager& TheOne();

private:
	/**	Constructor.
    *   Protected constructor, use TheOne() access instead. 
    *	\param	pObject		Internal parent object(default=NULL).
    */
    FBPropertyViewManager(HIObject pObject=NULL);
};

#endif //}

#ifdef FBSDKUseNamespace
}
#endif

#endif
