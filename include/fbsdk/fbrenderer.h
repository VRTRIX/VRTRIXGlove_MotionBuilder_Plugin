#ifndef __FBRENDERER_H__
#define __FBRENDERER_H__
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

/**	\file fbrenderer.h
*	Rendering engine.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#if !defined(K_NO_MANIPULATOR)
#include <fbsdk/fbmanipulator.h>
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbmodel.h>
#include <fbsdk/fbcamera.h>
#include <fbsdk/fblight.h>
#include <fbsdk/fbshader.h>
#include <fbcontrols/fbcontrols.h>	// FBInputType

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

    __FB_FORWARD( FBRenderer );
    __FB_FORWARD( FBRendererCallback );

    FB_FORWARD( FBView );

    FB_DEFINE_COMPONENT( FBSDK_DLL, Renderer );

    FB_FORWARD( FBViewingOptions );

    //! Model display options.
    enum FBDisplayMode {
        kFBDisplayModeDefault = 0,	//!< Use default display mode.
        kFBDisplayModeTexture,		//!< Textures are displayed.
        kFBDisplayModeHardShade,	//!< Hard shading.
        kFBDisplayModeFlatShade,	//!< Flat shading.
        kFBDisplayModeWireFrame,	//!< Wire-frame rendering.
        kFBDisplayModeCount			//!< End of enum, this value indicates the number of display modes available.
    };

	/** Modes for arranging objects in schematic view.
    */
    enum FBArrangeMode { 
        kHorizontalMode,		//!< Arrange all objects horizontally.
        kVerticalMode,			//!< Arrange all objects vertically.
    };

    enum FBStereoDisplayMode   
    {
        kFBStereoDisplayCenterEye = 0,          //!< Display in Center Eye Camera, No Stereo effect
        kFBStereoDisplayLeftEye,                //!< Display in Left Eye Caerma, No Stereo effect
        kFBStereoDisplayRightEye,               //!< Display in Right Eye Caerma, No Stereo effect
        kFBStereoDisplayActive,                 //!< Display in active mode. User must enable OpenGL quad stereo buffer, and choose approriate stereo mode in video card hardware's config app.
        kFBStereoDisplayHorizontalInterlace,    //!< Display in Horizontal Interlace stereo mode.
        kFBStereoDisplayCheckerboard,           //!< Display in Checkboard Interlace stereo mode.
        kFBStereoDisplayAnaglyph,               //!< Display in Analygh stereo mode.
        kFBStereoDisplayAnaglyphLuminance,       //!< Display in Luminance Analygh stereo mode.    
        kFBStereoDisplayFreeviewParallel,       //!< Display in parallel free view stereo mode. 
        kFBStereoDisplayFreeviewCrossed,        //!< Display in crossed free view stereo mode.
        kFBStereoDisplayModeCount = 10          //!< update this count value when add new mode
    };

    //! \enum FBDisplayWhat
    /**Model display mask
    *	This mask determines what types of models are displayed by the renderer.
    */
    enum FBDisplayWhat {
        kFBDisplayNone		= 0,			//!< Nothing is displayed.
        kFBDisplayNull		= (1 << 0),		//!< Null models are displayed.
        kFBDisplayMarker	= (1 << 1),		//!< Markers are displayed.
        kFBDisplaySkeleton	= (1 << 2),		//!< Skeletons and bones are displayed.
        kFBDisplayCenter	= (1 << 3),		//!< Centers are displayed.
        kFBDisplayLight		= (1 << 4),		//!< Lights are displayed.
        kFBDisplayCamera	= (1 << 5),		//!< Cameras are displayed.
        kFBDisplay3dIcon	= (1 << 6),		//!< 3D icons are displayed (3D icons are 3D elements that do not exist in the scene).
        kFBDisplayAll		= 0xff			//!< Everything is displayed.
    };

    //! \enum FBPickingMode
    /**3D picking mode.*/
    enum FBPickingMode {
        kFBPickingModeStandard = 0,		//!< Standard picking mode.
        kFBPickingModeXRay,				//!< X-Ray picking mode (obstructed models are displayed in overlay).
        kFBPickingModeModelsOnly,		//!< Models-only mode (no nulls or skeletons are displayed).
        kFBPickingModeCount				//!< End of enum, this valued indicates the number of picking modes available.
    };

    //! \enum FBDeviceKeyboardKey
    /**Keyboard keys (for input).*/
    enum FBDeviceKeyboardKey {
        kFBDKeyPageUp,			//!< Page Up.
        kFBDKeyPageDown,		//!< Page Down.
        kFBDKeyEnd,				//!< End.
        kFBDKeyHome,			//!< Home.
        kFBDKeyArrowLeft,		//!< Left.
        kFBDKeyArrowUp,			//!< Up.
        kFBDKeyArrowRight,		//!< Right.
        kFBDKeyArrowDown,		//!< Down.
        kFBDKeyReturn,			//!< Return.
        kFBDKeyEscape,			//!< Escape.
        kFBDKeySpace,			//!< Space bar.
        kFBDKey1,				//!< '1'.
        kFBDKey2,				//!< '2'.
        kFBDKey3,				//!< '3'.
        kFBDKey4,				//!< '4'.
        kFBDKey5,				//!< '5'.
        kFBDKey6,				//!< '6'.
        kFBDKey7,				//!< '7'.
        kFBDKey8,				//!< '8'.
        kFBDKey9,				//!< '9'.
        kFBDKey0,				//!< '0'.
        kFBDKeyF1,				//!< 'F1'.
        kFBDKeyF2,				//!< 'F2'.
        kFBDKeyF3,				//!< 'F3'.
        kFBDKeyF4,				//!< 'F4'.
        kFBDKeyF5,				//!< 'F5'
        kFBDKeyF6,				//!< 'F6'.
        kFBDKeyF7,				//!< 'F7'.
        kFBDKeyF8,				//!< 'F8'.
        kFBDKeyF9,				//!< 'F9'.
        kFBDKeyF10,				//!< 'F10'.
        kFBDKeyF11,				//!< 'F11'.
        kFBDKeyF12				//!< 'F12'.
    };

    FB_DEFINE_ENUM( FBSDK_DLL, DeviceKeyboardKey );

    /** Viewing options for rendering.
    *	The FBRenderer allows to get and set those options.
    */
    class FBSDK_DLL FBViewingOptions
    {
    public:
        /** Get a reference to the current viewing camera.
        */
        FBCamera*   GetViewingCamera();

        /**	Get a reference to the display mode.
        *	\return Reference to the current display mode.
        */
        FBModelShadingMode& ShadingMode();

        /**	Get a reference to the stereo display mode.
        *	\return Reference to the current stereo display mode.
        */    
        FBStereoDisplayMode& StereoDisplayMode();

        /** Get a reference to the display mask.
        *	\return Reference to the current display mask.
        */
        int& DisplayWhat();

        /** Get a reference to the picking mode.
        *	\return Reference to the current picking mode.
        */
        FBPickingMode& PickingMode();

        /** Show Time Code when rendering.
        */
        bool& ShowTimeCode();

        /** Show Safe Area when rendering.
        */
        bool& ShowSafeArea();

        /** Show Camera Label when rendering.
        */
        bool& ShowCameraLabel();

        /** Is the rendering routine during picking status with GL selection buffer method.
        */
        bool IsInSelectionBufferPicking() const;

        /** Is the rendering routine during picking status with GL color buffer method.
        */
        bool IsInColorBufferPicking() const;

        /** Current Render callback Settings Index
        */
        unsigned int RenderCallbackPrefIndex() const;

        /** Current Viewer Pane being rendered
        *	\return Index of the pane being rendered.
        */
        int PaneIndex() const;

    private:
        FBViewingOptions();
        FBViewingOptions(const FBViewingOptions &);
        FBViewingOptions & operator =(const FBViewingOptions &);
    };


    ////////////////////////////////////////////////////////////////////////////
    // FBPickInfos
    ////////////////////////////////////////////////////////////////////////////

    /** Picking information structure.
    *   This class holds information related to the picking action on a renderer.
    *   The intersection info (Position and Normal) won't be accurate for the following type of models: 
    *   - Locators: Camera, Lights, Marker and etc. 
    *   - Custom Model inherited from FBModel. 
    *   - And GPU skinned models.  
    *   
    *   Sample C++ code:
    *
    *   \code
    *       FBPickInfosList lList;
    *       FBSystem lSystem;
    *       FBRenderer* lRenderer = lSystem.Renderer;
    *       lRenderer->Pick( 200, 200, lList );
    *   
    *       int lIdx;
    *       for( lIdx = 0; lIdx < lList.GetCount(); ++lIdx )
    *       {
    *           FBString lName = "aNull ";
    *           lName += (char*)lList[lIdx].mModel->Name;
    *   
    *           FBModelNull* lNull = new FBModelNull( lName );
    *           lNull->Visible = true;
    *           lNull->Translation = lList[lIdx].mPoint;
    *       }
    *   \endcode
    *
    */
    struct FBPickInfos 
    {
        /** FBPickInfos
        *   \param pModel a handel to the model(FBModel*).
        *   \param pPoint  position (FBVector3d).
        *   \param pNormal normal direction (FBVector3d).
        *   \param pSubItemIndex sub item index, -1 for whole object.
        */
        FBPickInfos( FBModel* pModel, FBVector3d pPoint, FBVector3d pNormal, int pSubItemIndex ) 
            : mModel( pModel ), mPoint( pPoint ), mNormal (pNormal), mSubItemIndex(pSubItemIndex) {};

        FBModel*   mModel;          //!< Model picked.
        FBVector3d mPoint;          //!< Location of the pick on the model's surface in world space.
        FBVector3d mNormal;         //!< Normal of the pick on the model's surface in world space.
        int        mSubItemIndex;   //!< Picked sub item index, -1 for whole object. 
    };

    bool operator==( const FBPickInfos& pLhs, const FBPickInfos& pRhs );

    //! typedef class FBSDK_DLL FBArrayTemplate<FBPickInfos> FBPickInfosList
    typedef class FBSDK_DLL FBArrayTemplate<FBPickInfos> FBPickInfosList;

    /**	Create a FBPickInfosList object.
    *	This is to get around memory management issues when mixing debug and release runtime
    *   libraries on Windows. By using the FBCreatePickInfosList/FBDestroyPickInfosList
    *   duo of functions, you ensure that the memory used in the array is allocated,
    *   reallocated and freed in the same memory pool.
    */
    FBSDK_DLL FBPickInfosList* FBCreatePickInfosList();

    /** Delete a FBPickInfosList object.
    *   \param  pPickInfosList  pointer to the object created with a call to FBCreatePickInfosList().
    */
    FBSDK_DLL void FBDestroyPickInfosList( FBPickInfosList* pPickInfosList );

    ////////////////////////////////////////////////////////////////////////////
    // FBRendererCallback
    ////////////////////////////////////////////////////////////////////////////

    //! Open Reality renderer callback interface
    class FBSDK_DLL FBRendererCallback : public FBComponent 
    {
        //--- Open Reality declaration.
        __FBClassDeclare( FBRendererCallback,FBComponent );
    public:

        /**	Constructor 
        */
        FBRendererCallback(const char* pName);

        /** Return Callback Name. 
        *   Need to be same with RendererCallbackLayout
        */
        virtual const char* GetCallbackName() const = 0;

        /** Return Callback Desc Name. 
        *   This Desc Name will be displayed in the render selection menu. 
        *   Need to be same with RendererCallbackLayout. 
        */
        virtual const char* GetCallbackDesc() const = 0;

        /** Return Callback Preference Count, 
        *   For adjust render settings, quality, performance and etc.)
        *   It's up to SDK plugin developer to define their own preference settings.
        *   Maximum number of Preference should be no more than 9. 
        */
        virtual unsigned int GetCallbackPrefCount() const;

        /** Return Callback Preference Name.
        *  \param pIndex    within the range of [0, GetCallbackPrefCount())
        */
        virtual const char*  GetCallbackPrefName(unsigned int pIndex) const;

        /** Callback for rendering.
        *   \param pRenderOptions   rendering options for this call.
        */
        virtual void Render(FBRenderOptions* pRenderOptions);

        /** Callback when attach RendererCallback 
        *   This callback occurs when attach this renderer callback instance one view pane. 
        */
        virtual void Attach();

        /** Callback when detach RendererCallback 
        *   This callback occurs when detach this renderer callback instance from one view pane.
        */
        virtual void Detach();

        /** Callback to ask invalidate GL resources.
        *   This callback occurs when no view pane use this renderer callback instance anymore,
        *   or some internal events request GL context invalidation.
        *   \param pViewOption  Viewing Options.
        */
        virtual void DetachDisplayContext(FBViewingOptions* pViewOption);

        FBPropertyBool SupportIDBufferPicking;                  //!< <b>Read write Property:</b> Can this Renderer Callback support IDBuffer Picking.  
        FBPropertyBool DefaultCameraFrontPlateRendering;        //!< <b>Read write Property:</b> Set true to use default camera front plate rendering; set false to disable it.
        FBPropertyBool DefaultCameraBackPlateRendering;         //!< <b>Read write Property:</b> Set true to use default camera back plate rendering; set false to disable it.
        FBPropertyBool DefaultLightGroundProjectionRendering;   //!< <b>Read write Property:</b> Set true to use default light ground projection rendering; set false to disable it.
        FBPropertyBool DefaultLightVolumeRendering;             //!< <b>Read write Property:</b> Set true to use default light volume rendering; set false to disable it.
    };

    FB_DEFINE_COMPONENT	( FBSDK_DLL, RendererCallback );

    /**	FBRendererCallback class registration.
    *	\param	UniqueNameStr	Unique name.
    *	\param	ClassName		RendererCallback class name.
    *	\param	Label			Short description.
    *	\param	Description 	Long description.
    *   \param  IconFilename    Name of the file containing the icon.
    */
#define FBRegisterRendererCallback( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
    HIObject CreateRendererCallback##ClassName( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
    { \
    ClassName *Class = new ClassName( pName ); \
    if (Class->FBCreate()) { \
    return Class->GetHIObject(); \
    } else { \
    delete Class; \
    return NULL; \
    } \
    } \
    FBLibraryModule( ClassName )	\
    {	\
    FBRegisterObject( ClassName##R1,"renderer/callback/ogl",Label,Description,CreateRendererCallback##ClassName,true, IconFilename );	\
    }

    /**	FBRendererCallback class declaration.
    *	\param	ClassName	FBRendererCallback class name.
    *	\param	Parent		Class parent.
    */
#define FBRendererCallbackDeclare( ClassName, Parent  ) \
    FBClassDeclare( ClassName,Parent); \
public: \
    ClassName(const char* pName):Parent(pName) { FBClassInit; } \
private:

    /**	FBRendererCallback class implementation.
    *	\param	ThisComponent	Class to implement.
    */
#define FBRendererCallbackImplementation( ThisComponent ) \
    FBClassImplementation( ThisComponent )


    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListRendererCallback
    ////////////////////////////////////////////////////////////////////////////////////
    //! \b PropertyList: Texture

    class FBSDK_DLL FBPropertyListRendererCallback : public FBPropertyListComponent
    {
    public:
        FBPropertyListRendererCallback();
        /** Add a RendererCallback to the property list.
        *   @param      pItem   RendererCallback to add to the list.
        *   @return             The index of the element in the list. Returns -1 on failure.
        *   @warning            Adding a new element will invalidate any existing iterators
        *                       as the new items may not be added at the end of the list.
        */
        virtual int Add( FBRendererCallback* pItem );
        /** Get the texture at a specific index.
        *   @param  pIndex  Index of RendererCallback to get.
        *   @return         The RendererCallback at the specified index. Returns a NULL pointer on failure.
        */
        FBRendererCallback* operator[](int pIndex);

    private:
        inline virtual int Add    ( FBComponent* pItem ) { return Add((FBRendererCallback*)pItem); }
    };

    ////////////////////////////////////////////////////////////////////////////
    // FBRenderer
    ////////////////////////////////////////////////////////////////////////////

    //! Open Reality renderer interface.
    class FBSDK_DLL FBRenderer : public FBComponent 
    {
        //--- Open Reality declaration.
        __FBClassDeclare( FBRenderer,FBComponent );
    public:
        /**	Constructor.
        *   Client code cannot instantiate objects of this class. The FBSystem and
        *   FBScene classes provide access to the current renderer.
        *	\param	pObject	For internal use only.
        */
        FBRenderer(HIObject pObject);

        //--- Rendering manipulation
        /** Must be called before inputing if the same renderer is used on multiple
        *   views/cameras in the same application 
        *	\param	pX	X position where to render.
        *	\param	pY	Y position where to render.
        *	\param	pW	Width of render area.
        *	\param	pH	Hight of render area.
        */
        void SetViewport(int pX,int pY,int pW,int pH);

        /** RenderBegin
        *	\param	pX	X position where to render.
        *	\param	pY	Y position where to render.
        *	\param	pW	Width of render area.
        *	\param	pH	Hight of render area.
        *  
        *	must be called before rendering can happen
        *    
        */
        bool RenderBegin(int pX,int pY,int pW,int pH);

        /** RenderEnd.
        *	\param		pView	If you want the renderer to draw artifacts, such as TimeCode, CameraLabel or SafeArea,
        *						you must provide the FBView on which the renderer draws on.
        *	\remarks	Must be called at the end of rendering.
        */
        bool RenderEnd(FBView* pView=NULL);

        /** PreRenders one frame (needed for some shaders)
        *  This functions destroys the frame buffer content and must be called every time a render is called
        *    the typical order of call must be 
        *        Renderer->Prerender
        *        // at this point the frame buffer is garbage
        *        -Clear the ogl
        *        -Do your render functions
        *        Renderer->Render
        *        
        *	\param	pLayer	Rendering layer ID(default=-1).
        *	\return	\b true if successful.
        */
        bool PreRender(int pLayer = -1);

        /** Renders one frame 
        *	\param	pLayer	Rendering layer ID(default=-1).
        *	\return	\b true if successful.
        */
        bool Render(int pLayer = -1);

        /** Setup the scene lights in OpenGL.
        *	\param pRenderOptions See FBRenderOptions for more detail.
        */
        void OGLSetupSceneLights(FBRenderOptions& pRenderOptions);

        /** \internal Display Model in OpenGL. 
        *   For Internal testing purpose only.
        *	\param pRendererOptions See FBRenderOptions for more detail.
        *   \param pModel model to be displayed.
        */
        void OGLModelDisplay(FBRenderOptions& pRenderOptions, FBModel& pModel);

        /** Set the viewing options.
        *	\param pOptions See FBViewingOptions for more detail.
        */
        bool SetViewingOptions(FBViewingOptions & pOptions);

        /** Obtain the current viewing options.
        *   \return A structure that can be queried and updated for a call to SetViewingOptions.
        */
        FBViewingOptions * GetViewingOptions();

        /** Frame the current camera either with all models or with the currently selected models.
        *	\param pAll  true to frame with all models.
        *	\return \b true if successful.
        */
        bool FrameCurrentCameraWithModels(bool pAll);

		/**	Request to arrange selected objects in schematic view .*/
		void ArrangeSelectedObjectsInSchematic();

		/**	Request to arrange a node's tree in the Schematic View, given a starting node.
		*	\param	pModel	The starting node from which the arrange operation is requested.
		*	\return True if the operation is successful, false otherwise.
		*/
		bool ArrangeObjectsInSchematicFromModel( const FBModel& pModel );

		/**	Request to arrange all objects in schematic view .
		*	\param	pMode	 Arrange mode. 
		*/
		void ArrangeAllInSchematic(FBArrangeMode pMode);

		/** Returns the bounding box (top, left, bottom, right) used by all the Schematic View nodes.
		*	\param	pConsiderCollapsedNodes	True to also consider nodes which are not visible because collapsed, false otherwise.
		*	\param	pTop					Top value of the bounding box. Will be filled once the method returns.
		*	\param	pLeft					Left value of the bounding box. Will be filled once the method returns.
		*	\param	pBottom					Bottom value of the bounding box. Will be filled once the method returns.
		*	\param	pRight					Right value of the bounding box. Will be filled once the method returns.
		*	\return True if the operation is successful, false otherwise (e.g. the Schematic View has any node in it, etc.).
		*/
		bool GetSchematicNodesBoundingBox( bool pConsiderCollapsedNodes, int& pTop, int& pLeft, int& pBottom, int& pRight );

		/** Returns the bounding box (top, left, bottom, right) of a node's tree in the Schematic View, given a starting node.
		*	\param	pModel					The starting node from which the bounding box tree is requested.
		*	\param	pConsiderCollapsedNodes	True to also consider nodes which are not visible because collapsed, false otherwise.
		*	\param	pTop					Top value of the bounding box. Will be filled once the method returns.
		*	\param	pLeft					Left value of the bounding box. Will be filled once the method returns.
		*	\param	pBottom					Bottom value of the bounding box. Will be filled once the method returns.
		*	\param	pRight					Right value of the bounding box. Will be filled once the method returns.
		*	\return True if the operation is successful, false otherwise (e.g. the starting node is not in the Schematic View, etc.).
		*/
		bool GetSchematicNodesBoundingBoxFromModel( FBModel* pModel, bool pConsiderCollapsedNodes, int& pTop, int& pLeft, int& pBottom, int& pRight );

        //--- \internal Camera manipulation, Manipulators
        /** Mouse input.
        *	\param	pX				X position.
        *	\param	pY				Y position.
        *	\param	pInputType		Type of input.
        *	\param	pButtonKey		Button/Key pressed.
        *	\param	pModifier		Modifier pressed (CTRL/ALT/SHIFT).
        *	\param	pWheelDeltaValue	Mouse wheel delta value
        *	\param	pLayer			Rendering layer ID(default=-1).
        *	\return	\b true if successful.
        */
        bool MouseInput(int pX,int pY,FBInputType pInputType,int pButtonKey,FBInputModifier pModifier,int pWheelDeltaValue=0,int pLayer = -1);

        /** Mouse input.
        *	\param	pX				X position, normalized to the range of [0, 1] in the view port dimension.
        *	\param	pY				Y position, normalized to the range of [0, 1] in the view port dimension.
        *	\param	pInputType		Type of input.
        *	\param	pButtonKey		Button/Key pressed.
        *	\param	pModifier		Modifier pressed (CTRL/ALT/SHIFT).
        *	\param	pWheelDeltaValue	Mouse wheel delta value
        *	\param	pLayer			Rendering layer ID(default=-1).
        *   \param  pPaneId         specify which pane's dimension used for normalization, default (-1) for the whole viewer.
        *	\return	\b true if successful.
        */
        bool MouseInputNormalized(float pX,float pY,FBInputType pInputType,int pButtonKey,FBInputModifier pModifier,int pWheelDeltaValue, int pLayer = -1, int pPaneId = -1);

        /** Object picking selection.
        *	\param	pX				X position.
        *	\param	pY				Y position.
        *	\param	pPickInfosList  The list of pick infos.
        *	\param  pNeedIntersectPosition	require valid intersection position if true, this will take more time to
        *							process, and not reliable with very dense mesh.
        */
        bool Pick(int pX, int pY, FBPickInfosList& pPickInfosList, bool pNeedIntersectPosition = false );

        /** Object picking selection.
        *	\param	pX				X position, normalized to the range of [0, 1] in the view port dimension.
        *	\param	pY				Y position, normalized to the range of [0, 1] in the view port dimension.
        *	\param	pPickInfosList  The list of pick infos.
        *	\param  pNeedIntersectPosition	require valid intersection position if true, this will take more time to
        *							process, and not reliable with very dense mesh.
        *   \param  pPaneId         specify which pane's dimension used for normalization, default (-1) for the whole viewer.
        */
        bool PickNormalized(float pX, float pY, FBPickInfosList& pPickInfosList, bool pNeedIntersectPosition = false, int pPaneId = -1);

        /** Object rectangle selection.
        *	\param	pX1				Left upper corner X position.
        *	\param	pY1				Left upper corner y position.
        *	\param	pX2				Right bottom corner X position.
        *	\param	pY2				Right bottom corner y position.
        *	\param	pPickInfosList  The list of pick infos.
        */
        bool RectPick(int pX1, int pY1, int pX2, int pY2, FBPickInfosList& pPickInfosList);

        /** Object rectangle selection.
        *	\param	pX1				Left upper corner X position, normalized to the range of [0, 1] in the viewport dimension.
        *	\param	pY1				Left upper corner y position, normalized to the range of [0, 1] in the viewport dimension.
        *	\param	pX2				Right bottom corner X position, normalized to the range of [0, 1] in the viewport dimension.
        *	\param	pY2				Right bottom corner y position, normalized to the range of [0, 1] in the viewport dimension.
        *	\param	pPickInfosList  The list of pick infos.
        *   \param  pPaneId         specify which pane's dimension used for normalization, default (-1) for the whole viewer.
        */
        bool RectPickNormalized(float pX1, float pY1, float pX2, float pY2, FBPickInfosList& pPickInfosList, int pPaneId = -1);

        /** Return the last picking info list in the current view pane.
        *	\param	pPickInfosList  The list of pick infos.
        *   \return number of item in the list.
        */
        int  GetLastPickInfoList(FBPickInfosList& pPickInfosList);

        /** Keyboard input.
        *	\param	pKeyIndex		Key index. (See "enum FBDeviceKeyboardKey" above for supported keys)
        *	\param	pKeyState		Key state. (True == key is down, False == key is up)
        *	\param	pIsTrigger		When setting pKeyState to True, resets key state to False right after operation.
        */
        void KeyboardInput(FBDeviceKeyboardKey pKeyIndex, bool pKeyState, bool pIsTrigger = false);

        /** Get the displayable geometry model.
        *   Those geometry models which have Show property ON are considered as "displayable".
        *   \param pIndex   displayable geometry model index to query.
        *   \return         displayable geometry model.
        */
        FBModel* GetDisplayableGeometry(int pIndex );

        /** Get the displayable light.
        *   Those light models which have Show property ON are considered as "displayable".
        *   \param pIndex   displayable light index to query.
        *   \return         displayable light.
        */
        FBLight* GetDisplayableLight(int pIndex );

        /** Get a list of displayable geometry inside given camera's frustum.
        *   This function will return conservative result. It's possible for some geometry outside of 
        *   the frustum will be considered to be visible, but it will not skip any real visible geometry. 
        *   This function should only be called in the main rendering thread.
        *   \param  pModelList          ModelList holding the return models. 
        *   \param  pCamera             use current camera if NULL.
        *   \return                     Reference to pModelList. if pModelList is NULL return a const reference to internal static FBModelList and consecutive call to this function will
        *                               invalidate the result of previous call. 
        */
        const FBModelList& GetDisplayableGeometryInCameraFrustum(FBModelList* pModelList = NULL, FBCamera* pCamera = NULL);

        /** To tell if given model is located inside camera's frustum.
        *   This function will return conservative result. It's possible for some geometry outside of 
        *   the frustum will be considered to be visible, but it will not skip any real visible geometry. 
        *   This function should only be called in the main rendering thread.
        *   \param  pGeometry           the geometry to be queried. 
        *   \param  pCamera             use current camera if NULL.
        *   \return						true if Model is inside camera frustum.
        */
        bool IsModelInsideCameraFrustum(FBModel* pGeometry, FBCamera* pCamera = NULL);

        // Properties
        FBPropertyCamera				CurrentCamera;			//!< \deprecated Use SetCameraInPane/GetCameraInPane methods instead.  
        FBPropertyBool					UseCameraSwitcher;		//!< \deprecated Use SetCameraSwitcherInPane/IsCameraSwitcherInPane methods instead.

#if !defined(K_NO_MANIPULATOR)
        FBPropertyManipulatorTransform  ManipulatorTransform;	//!< <b>Read Only Property:</b> Manipulator responsible of moving objects
        FBPropertyListManipulator		Manipulators;			//!< <b>List:</b> of manipulators.
#endif

        FBPropertyScene					Scene;					//!< <b>Read Write Property:</b> Scene that the renderer will use/draw
        FBPropertyBool					AutoEvaluate;			//!< <b>Read Write Property:</b> Indicate if a call to RenderBegin will also cause a re-evaluation of the scene.
        FBPropertyBool					EvaluateMode;			//!< <b>Read Write Property:</b> When true (default), call to Render will perform evaluation. Useful when rendering and evaluation needs to be decoupled.
        FBPropertyBool					Background;				//!< <b>Read Write Property:</b> The renderer.
        FBPropertyBool					ShowStats;				//!< <b>Read Write Property:</b> Show the stats about FPS, Evaluation rate ... like when using Shift-F in main viewer.
        FBPropertyBool                  FrustumCulling;         //!< <b>Read Write Property:</b> Turn on/off the early frustum culling optimization. 
        FBPropertyBool					DisplayNormals;			//!< <b>Read Write Property:</b> Display model normals in main viewer.
        FBPropertyBool					PickingEnabled;			//!< <b>Read Write Property:</b> Is picking in the viewer enabled?
        FBPropertyBool                  IDBufferPicking;        //!< <b>Read write Property:</b> Use ID (Color) Buffer for picking, instead of OpenGl selection buffer picking.
        FBPropertyDouble                IDBufferPickingAlpha;	//!< <b>Read write Property:</b> Those Semi-transparent (Alpha Blend) geometry(region) contribute less than this threshold, will be considered as invisible during ID picking.
        FBPropertyBool                  IDBufferDisplay;        //!< <b>Read write Property:</b> Render Model's unique Color ID into color Buffer (used for picking)
        FBPropertyBool					SelectionOverride;		//!< <b>Read write Property:</b> Add transparent color override layer on selected models if true.
        FBPropertyDouble				SelectionOverrideTransparency;	//!< <b>Read write Property:</b> Selection override layer transparency.
        FBPropertyColor					SelectionOverrideColor;	//!< <b>Read write Property:</b> Selection override layer color.    
        FBPropertyBool                  SelectionForceSnapPointsDisplay;//!< <b>Read write Property:</b> Force show all feature points (pivots and etc) on selected models if true, ignore individual model's settings.
        FBPropertyInt                   DisplaySetUpdateId;     //!< <b>Read Only Property:</b> Current DisplaySet Update Id. Add/Delete models, Show/Hide models will affect DisplaySet.
        FBPropertyInt                   RendererUpdateId;       //!< <b>Read Only Property:</b> Current Render Update Id. DisplaySet update, material change, texture changes and shader change and other operations will trigger Renderer update. 
        FBPropertyInt                   DisplayableGeometryCount;//!< <b>Read Only Property:</b> Displayable geometry count.
        FBPropertyInt                   DisplayableLightCount;  //!< <b>Read Only Property:</b> Displayable light count.
        FBPropertyListRendererCallback  RendererCallbacks;      //!< <b>List:</b> Renderer Callbacks attached.
        FBPropertyInt                   RegisteredCallbackCount;//!< <b>Read Only Property:</b> Registered Renderer Callback Count.
        FBPropertyInt                   CurrentPaneCallbackIndex;       //!< <b>Read Write Property:</b> Current Pane's Renderer Callback Index.
        FBPropertyInt                   CurrentPaneCallbackPrefIndex;   //!< <b>Read Write Property:</b> Current Pane's Renderer Callback Preference Index.
		FBPropertyBool					HideManipulatorsOnManip;		//!< <b>Read Write Property:</b> Hide manipulators UI elements while manipulating.

        /** <b>Read write Property:</b> Turn on/off advanced material setting UI widgets. 
        *   \note MoBu default render won't utilize those advanced material properties, they're provided for pipeline interop and custom plugin development purpose. 
        */
        FBPropertyBool                  AdvancedMaterialMode;   

        /** <b>Read write Property:</b> Turn on/off advanced lighting setting UI widgets. 
        *   Include UI widgets for various advanced lighting setting, includes: 
        *   Light: area light, spot light inner/outer angles, barndoors and etc.,; 
        *   Model: PrimaryVisibility, CastsShadows and ReceiveShadows.
        *   
        *   MoBu default render doesn't utilize those advanced lighting properties, they're provided 
        *   for pipeline interop and custom plugin development purpose. This property must been set 
        *   to be true before creating any scene light or model objects to allow UI widgets display properly. 
        *   
        *   it's equivalent to the config item "AdvancedLightingUISetting" at [Rendering] section"
        */
        FBPropertyBool                  AdvancedLightingMode;   

        /** Viewer texture Id.
        *   This function is returning the texture Id of the viewer pane and also making sure the opengl context is current
        *   \return						Texture Id of the viewer when Videoout is Online.
        */
        int GetViewerTextureId();

        /** Add a new clone view to call when rendering main viewer
        *   \param  pView           View to be called for expose.
        */
        void CloneViewAdd(FBView* pView);

        /** Remove a new clone view to call when rendering main viewer
        *   \param  pView           View to be called for expose.
        */
        void CloneViewRemove(FBView* pView);

        /** Viewer texture Id.
        *   This function starts/stop rendering to an additional buffer which can be accessed with GetViewerTextureId() without the need to turn VideoOut Online.
        *   \param  pState           Set On/Off texture viewer generation. If false, GetViewerTextureId() will not return a valid texture.
        */
        void CloneViewRender(int pWidth, int pHeight);

        /** Set the camera to display in the given pane index.
        *   If the Schematic View is displayed in the pane associated with the given pane index,
        *   the camera will be displayed when the Schematic View will be deactivated from this pane.
        *
        *   Note:
        *   If current pane uses Camera Switcher, it will be set to use Camera, rather than old behavior
        *   that still uses Camera Switcher and sets Camera to be Camera Switcher's current camera,
        *   which introduce a Zombie Camera Switcher problem.  By using Camera, the problem is gone.
        *   
        *   Note:
        *   To operate current camera in Camera Switcher, it is recommended to use FBCameraSwitcher().
        *
        *   \param pCamera          The camera to set.
        *   \param pPaneIndex       The pane index.
        */
        void SetCameraInPane( FBCamera* pCamera, unsigned int pPaneIndex );

        /** Return the camera displayed in the given pane index.
        *   If the Schematic View is displayed in the pane associated with the given pane index,
        *   the returned camera is the camera that would be displayed if the Schematic View was deactivated.
        *   If the Camera Switcher is on in the pane associated with the given pane index,
        *   the returned camera is the switcher's current camera.
        *   
        *   Note:
        *   To operate current camera in Camera Switcher, it is recommended to use FBCameraSwitcher().
        *
        *   \param pPaneIndex       The pane index.
        *   \return                 The camera used in the given pane index, NULL if the pane index is invalid.
        */
        FBCamera* GetCameraInPane( unsigned int pPaneIndex );

        /** Set the number of panes to display in the viewer's layout.
        *   \param pPaneCount       The number of panes to display.
        */
        void SetPaneCount( unsigned int pPaneCount );

        /** Return the number of panes displayed in the viewer's layout.
        *   \return                 The number of panes displayed.
        */
        unsigned int GetPaneCount();

		/**	Select the pane associated with the given pane index in the active viewer's layout.
		*	\param pPaneIndex		The pane index.
		*	\return					True if the operation is successful, False otherwise.
		*/
		bool SetSelectedPaneIndex( unsigned int pPaneIndex );

		/**	Return the pane index associated with the selected pane in the active viewer's layout.
		*	\return					The selected pane index.
		*/
		unsigned int GetSelectedPaneIndex() const;

        /** Set/Remove the Schematic View in the given pane index.
        *   When activating the Schematic View in the pane, if the Schematic View is already activated in another pane,
        *   the Schematic View will be removed from latter before being activated into the new pane.
        *   \param pPaneIndex       The pane index.
        *   \param pActive          True to activate the Schematic View in the given pane, False to remove it.
        */
        void SetSchematicViewInPane( unsigned int pPaneIndex, bool pActive );

        /** Return the pane index of the pane displaying the Schematic View.
        *   \return                 The pane index of the pane displaying the Schematic View, -1 if the Schematic View is currently not displayed in any pane.
        */
        int GetSchematicViewPaneIndex();

        /** Set/Remove the Camera Switcher in the given pane index.
        *   To specify which camera the Camera Switcher should be displaying, use the SetCameraInPane method.
        *   If the Schematic View is displayed in the pane associated with the given pane index,
        *   the camera switcher will be displayed (if activated) when the Schematic View will be deactivated from this pane.
        *   \param pPaneIndex       The pane index.
        *   \param pActive          True to activate the Camera Switcher in the given pane, False to remove it.
        */
        void SetCameraSwitcherInPane( unsigned int pPaneIndex, bool pActive );

        /** Return the Camera Switcher activeness in the given pane index.
        *   If the Schematic View is displayed in the pane associated with the given pane index,
        *   the returned value is the value that would be returned if the Schematic View was deactivated.
        *   \param pPaneIndex       The pane index.
        *   \return                 True if the Camera Switcher is active in the pane associated with the given pane index, False otherwise.
        */
        bool IsCameraSwitcherInPane( unsigned int pPaneIndex );
    };

#ifdef FBSDKUseNamespace
}
#endif
#endif /* this must be the last line of this file */
