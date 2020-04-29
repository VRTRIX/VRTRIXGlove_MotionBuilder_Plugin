#ifndef __FBHUD_H__
#define __FBHUD_H__
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

/**	\file fbhud.h
*	HUD (Head Up Display)
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbproperties.h>
#include <fbsdk/fbtexture.h>

#ifndef K_NO_HUD

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

//! \enum FBHUDElementHAlignment
/* HUD horizontal alignment.*/
enum FBHUDElementHAlignment {
	kFBHUDLeft,			//!< Left alignment.
	kFBHUDRight,		//!< Right alignment
	kFBHUDCenter,		//!< Center.
};

FB_DEFINE_ENUM( FBSDK_DLL, HUDElementHAlignment );

//! \enum FBHUDElementVAlignment
/* HUD vertical alignment.*/
enum FBHUDElementVAlignment {
	kFBHUDBottom,					//!< Bottom alignment.
	kFBHUDTop,						//!< Top alignment.
	kFBHUDVCenter = kFBHUDCenter,	//!< Center.
};

FB_DEFINE_ENUM( FBSDK_DLL, HUDElementVAlignment );

FB_FORWARD(FBViewingOptions);

__FB_FORWARD( FBHUDElement ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUDElement );

/** Heads Up display.
*   Display scene related information on a camera output. Rendered on video out, output renderings.
*/
class FBSDK_DLL FBHUDElement : public FBBox 
{
    //--- Open Reality declaration.
    __FBClassDeclare( FBHUDElement, FBBox );

protected:
	/** Constructor. 
    *   \note   This constructor shouldn't be accessed directly except for subclass, see OpenReality Miscellaneous/orhudelement_template sample project for example.
    *	\param	pName		Name of new FBHUDElement.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
    */
	FBHUDElement( const char* pName, HIObject pObject=NULL );

public:
    FBPropertyBool Visibility;	                    //!< \deprecated <b>Read Write Property:</b> Specifies if the HUD element will be displayed or not.
    FBPropertyBool Show;                            //!<  <b>Read Write Property:</b> Specifies if the HUD element will be displayed or not.
    FBPropertyHUDElementHAlignment Justification;	//!< <b>Read Write Property:</b> Specifies if the justification of the HUD element is Left, Right, or Center.
    FBPropertyHUDElementHAlignment HorizontalDock;	//!< <b>Read Write Property:</b> Specifies if the HUD element will be horizontally docked to the Left, Right, or Center.
    FBPropertyHUDElementVAlignment VerticalDock;	//!< <b>Read Write Property:</b> Specifies if the HUD element will be vertically docked to the Bottom, Top, or Center.
    FBPropertyDouble X;								//!< <b>Read Write Property:</b> Specifies the horizontal position of the HUD element, relative to dock position and justification.
    FBPropertyDouble Y;								//!< <b>Read Write Property:</b> Specifies the vertical position of the HUD element, relative to dock position and justification.
    FBPropertyBool PositionByPercent;				//!< <b>Read Write Property:</b> When set to true, X and Y position values are in percentage, relative to the corresponding camera view dimension. Otherwise, they are absolute pixel values.
    FBPropertyBool ScaleByPercent;					//!< <b>Read Write Property:</b> When set to true, Scale is in percentage, relative to the corresponding camera view dimension. Otherwise, it is an absolute value.
    FBPropertyDouble Width;                         //!< <b>Read Write Property:</b> Specifies the width of HUD element on the screen. It's in pixel when ScaleByPercent is false and percentage when ScaleByPercent is true.
    FBPropertyDouble Height;                        //!< <b>Read Write Property:</b> Specifies the height of HUD element on the screen. It's in pixel when ScaleByPercent is false and percentage when ScaleByPercent is true.
    FBPropertyBool ScaleUniformly;                  //!< <b>Read Write Property:</b> Specifies whether the width and height of HUD element will be scaled uniformly according to the initial aspect ratio.

    /** HUD element rectangle for drawing in the view.
    */
    struct Rect
    {
        double mX;              //!< Element display region left bottom corner's X coordinate. 
        double mY;              //!< Element display region left bottom corner's Y coordinate. 
        double mWidth;          //!< Element display region width. 
        double mHeight;         //!< Element display region height.
        double mWidthScale;     //!< Element display region width scale factor compared with intrinsic width value.
        double mHeightScale;    //!< Element display region height scale factor compared with intrinsic height value.
    };

    /**     Callback for getting HUD element intrinsic dimension which is opposed to the actual display dimension.
    *   \param pViewingOptins Viewing Options. 
    *   \param pWidth   intrinsic width value, return by reference. 
    *   \param pHeight  intrinsic height value, return by reference. 
    */
    virtual void GetIntrinsicDimension(FBViewingOptions* pViewingOptins, int& pWidth, int & pHeight);

    /**     Callback for drawing HUD element.
    *   \param pViewingOption Viewing Options. 
    *   \param pRect HUD element display dimension.
    */
    virtual void DrawElement(FBViewingOptions* pViewingOption, Rect& pRect);

    /**    Store function that can be overloaded.
    *    \param    pFbxObject    FBX Object that is used to communicate I/O operations.
    *    \param    pStoreWhat    Which attributes are currently stored/retrieved.
    */
    virtual bool FbxStore(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat);

    /**    Retrieve function that can be overloaded.
    *    \param    pFbxObject    FBX Object that is used to communicate I/O operations.
    *    \param    pStoreWhat    Which attributes are currently stored/retrieved.
    */
    virtual bool FbxRetrieve(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat);
};

/** Custom Storable HUDELement Class implementation.
*    This should be placed in the source code file for a custom HUDElement class.
*    See OpenReality sample project orhudelement_template for usage example.
*/
#define FBStorableCustomHUDElementImplementation(ClassName, Desc)\
    const char* ClassName::FbxGetObjectSubType(){ return #ClassName; }\
    HIObject RegisterStorable##ClassName##Create(HIObject /*pOwner*/, const char* pName, void* /*pData*/){\
    ClassName* Class = new ClassName(pName);\
    Class->mAllocated = true;\
    if( Class->FBCreate() ){\
    return Class->GetHIObject();\
    } else {\
    delete Class;\
    return NULL;}}\
    FBLibraryModule(ClassName##Storable){\
    FBString lGroup = "FbxStorable/HUDElement";\
    FBRegisterObject(ClassName##R2, lGroup, #ClassName, Desc, RegisterStorable##ClassName##Create, true, NULL);\
    }\

  
////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListHUDElement
////////////////////////////////////////////////////////////////////////////////////
FB_DEFINE_LIST( FBSDK_DLL, HUDElement );
FB_FORWARD( FBPropertyListHUDElement );

//! \b PropertyList: Handle.
class FBSDK_DLL FBPropertyListHUDElement : public FBPropertyListComponent
{
public:
	FBPropertyListHUDElement();
    /**	Get the model template at \e pIndex.
	*	\param	pIndex	Index of model template to get.
	*	\return Model template at \e pIndex.
	*/
	FBHUDElement* operator[](int pIndex);
};

__FB_FORWARD( FBHUDTextElement ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUDTextElement );


/** Heads Up display.
*   Text element. Render text with a background rectangle to the HUD.
*/
class FBSDK_DLL FBHUDTextElement : public FBHUDElement 
{
    //--- Open Reality declaration.
    __FBClassDeclare( FBHUDTextElement , FBHUDElement );

public:
	/** Constructor.
	*	\param	pName		Name of new HUD text element.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBHUDTextElement( const char* pName, HIObject pObject=NULL );

    /** Returns a list of supported fonts.
    */
    FBStringList* GetFontList();

public:
    FBPropertyString                Content;                //!< <b>Read Write Property:</b> C like format to display like in printf.
    FBPropertyString                Font;                   //!< <b>Read Write Property:</b> Specifies the font.
    FBPropertyColorAndAlpha         Color;                  //!< <b>Read Write Property:</b> Text color.
    FBPropertyColorAndAlpha         BackgroundColor;        //!< <b>Read Write Property:</b> Background text color.
    FBPropertyBool                  ForceTimeCodeDisplay;   //!< <b>Read Write Property:</b> Specifies if the display of time-related reference property will be in timecode format.
    FBPropertyBool                  AdjustWidthToFitText;   //!< <b>Read Write Property:</b> If On it it will adjust the width of a text element so that a text character's aspect ratio does not change as the content grows or shrinks.
};


__FB_FORWARD( FBHUDRectElement ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUDRectElement );

/** Heads Up display.
*   Rectangle HUD element.
*/
class FBSDK_DLL FBHUDRectElement : public FBHUDElement 
{
    //--- Open Reality declaration.
    __FBClassDeclareGroup( FBHUDRectElement , FBHUDElement );

public:
	/** Constructor.
	*   \param  pName   Name of new HUD rectangle element.
    *   \param  pObject For internal use only. This parameter does not need to be specified by the developer.
	*/
	FBHUDRectElement( const char* pName, HIObject pObject=NULL );

public:
    FBPropertyColorAndAlpha         Color;              //!< <b>Read Write Property:</b> Color of the rectangluar region.
};


__FB_FORWARD( FBHUDTextureElement ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUDTextureElement );

/** Heads Up display.
*   Texture HUD element. Display a texture on a rectangle on the HUD.
**/
class FBSDK_DLL FBHUDTextureElement : public FBHUDElement 
{
    //--- Open Reality declaration.
    __FBClassDeclare( FBHUDTextureElement , FBHUDElement );
public:
	/** Constructor.
	*	\param	pName		Name of new HUD texture element.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBHUDTextureElement( const char* pName, HIObject pObject=NULL );

public:

	FBPropertyListTexture Texture;		 //!< <b>Read Write Property:</b> Texture to display.
};


__FB_FORWARD( FBHUDFlashElement ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUDFlashElement );

/** Heads Up display.
* Flash HUD element. Display a flash (swf) file rendered on the HUD.
*/
class FBSDK_DLL FBHUDFlashElement : public FBHUDElement 
{
    //--- Open Reality declaration.
    __FBClassDeclare( FBHUDFlashElement , FBHUDElement );
public:
	/** Constructor.
	*	\param	pName		Name of new HUD flash element.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBHUDFlashElement( const char* pName, HIObject pObject=NULL );

public:

	FBPropertyString FilePath;		 //!< <b>Read Write Property:</b> Path to load the swf file from
};

__FB_FORWARD( FBHUDBloopSlateElement ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUDBloopSlateElement );

/** Heads Up display.
* Bloop Slate HUD element. Display a bloop slate (swf) file rendered on the HUD.
*/
class FBSDK_DLL FBHUDBloopSlateElement : public FBHUDFlashElement
{
    __FBClassDeclare( FBHUDBloopSlateElement, FBHUDFlashElement );

public:
    /** Constructor.
	*	\param	pName		Name of new HUD flash element.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
    FBHUDBloopSlateElement( const char* pName, HIObject pObject=NULL );

public:

    FBPropertyColorAndAlpha BackgroundColor;            //!< <b>Read Write Property:</b> Bloop slate background color, by default it is 100% transparent.
    FBPropertyColorAndAlpha ForegroundColor;            //!< <b>Read Write Property:</b> Bloop slate foreground color.
    FBPropertyBool          Enable;                     //!< <b>Read Write Property:</b> Bloop slate will appear if set to true.
    FBPropertyTime          ShowAfterDelayOnRecordPlay; //!< <b>Read Write Property:</b> Delay before the bloop slate is displayed after recording has started.
    FBPropertyTime          ShowDuration;               //!< <b>Read Write Property:</b> Time that the bloop slate will be displayed.
};

__FB_FORWARD( FBHUDTimelineElement ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUDTimelineElement );

/** Heads Up display.
* HUD Timeline element. Displays a timeline that shows Head, Cut, Tail regions, and current time cursor.
* The drawing is defined in the flash file(timeline.swf).
*/
class FBSDK_DLL FBHUDTimelineElement : public FBHUDFlashElement
{
    __FBClassDeclare( FBHUDTimelineElement, FBHUDFlashElement );

public:
    /** Constructor.
	*	\param	pName		Name of new HUD flash element.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
    FBHUDTimelineElement( const char* pName, HIObject pObject=NULL );

public:

    FBPropertyColorAndAlpha HeadActiveColor;    //!< <b>Read Write Property:</b> Specifies color of the Head region when it is active.
    FBPropertyColorAndAlpha HeadIdleColor;      //!< <b>Read Write Property:</b> Specifies color of the Head region when it is idle.
    FBPropertyTime HeadDuration;                //!< <b>Read Write Property:</b> Specifies duration of the Head region.

    FBPropertyColorAndAlpha CutActiveColor;     //!< <b>Read Write Property:</b> Specifies color of the Cut region when it is active.
    FBPropertyColorAndAlpha CutIdleColor;       //!< <b>Read Write Property:</b> Specifies color of the Cut region when it is idle.

    FBPropertyColorAndAlpha TailActiveColor;    //!< <b>Read Write Property:</b> Specifies color of the Tail region when it is active.
    FBPropertyColorAndAlpha TailIdleColor;      //!< <b>Read Write Property:</b> Specifies color of the Tail region when it is idle.
    FBPropertyTime TailDuration;                //!< <b>Read Write Property:</b> Specifies duration of the Tail region.    
};

__FB_FORWARD( FBHUD ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUD );

/** Heads Up display.
*
*   Display scene related information to the screen. This information will also be present in the
*   rendered frames when creating AVIs or QuickTime files.
*
*/
class FBSDK_DLL FBHUD : public FBBox 
{
    //--- Open Reality declaration.
    __FBClassDeclare( FBHUD, FBBox );
public:
	/** Constructor.
	*	\param	pName		Name of new HUD.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBHUD( const char* pName, HIObject pObject=NULL );

    enum EStockElement {
        eRecordLight,
        eFlashElement,
        eTextElement,
        eRectElement,
        eTextureElement,
        eBloopSlate,
        eTimeline
    };

	/** Creates a stock HUD Element.
	*	\param  pType	View to be called for expose.
	*	\param  pName	Name for the HUD Element to create.
	*	\return			The created HUD Element.
	*/
	FBHUDElement* CreateElement( EStockElement pType, const char* pName );

	/** Creates a custom HUD Element.
	*	\param  pHUDElementClassName	The HUD Element class name (mainly, the ClassName parameter of the FBStorableCustomHUDElementImplementation macro).
	*	\param  pName					Name for the custom HUD Element to create.
	*	\return The created custom HUD Element.
	*/
	FBHUDElement* CreateCustomElement( const char* pHUDElementClassName, const char* pName );

public:
    FBPropertyBool              Visibility; //!< <b>Read Write Property:</b> Indicate if the information will be displayed or not.
	FBPropertyEvent	            OnDisplay;	//!< <b>Event:</b> Callback just before HUD is displayed to update custom values
    FBPropertyListHUDElement    Elements;   //!< <b>List:</b> Elements present in the HUD.
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListHUD
////////////////////////////////////////////////////////////////////////////////////
FB_DEFINE_LIST( FBSDK_DLL, HUD );
FB_FORWARD( FBPropertyListHUD );

//! \b PropertyList: Handle.
class FBSDK_DLL FBPropertyListHUD : public FBPropertyListComponent
{
public:
	FBPropertyListHUD();
    /**	Get the model template at \e pIndex.
	*	\param	pIndex	Index of model template to get.
	*	\return Model template at \e pIndex.
	*/
	FBHUD* operator[](int pIndex);
};

/** Heads Up display manager.
*
*   Manages the HUDs that are present in the scene. For example, you can use the HUD Manager to 
*   choose which HUD is drawn by default on cameras that do not have a HUD explicitly assigned.
*
*/
__FB_FORWARD( FBHUDManager ); 
FB_DEFINE_COMPONENT( FBSDK_DLL, HUDManager );
class FBSDK_DLL FBHUDManager: public FBComponent
{
    __FBClassDeclare( FBHUDManager, FBComponent );

	/**	Constructor.
	*	\param	pObject		Internal parent object(default = NULL).
    *   \Note   Constructor has private access. Use FBHUDManager::TheOne() to access this singleton manager.
	*/
	FBHUDManager(HIObject pObject = NULL);

public:
    FBPropertyHUD DefaultHUD;       //!< <b>Read Write Property:</b> Specifies the HUD to be displayed on cameras that do not have HUD explicitly assigned.

	/**	Access to the singleton Heads Up Display(HUD) Manager
	*	\return	HUD Manager
	*/
    static FBHUDManager& TheOne();
};

#ifdef FBSDKUseNamespace
}
#endif

#endif //K_NO_HUD

#endif /* this must be the last line of this file */