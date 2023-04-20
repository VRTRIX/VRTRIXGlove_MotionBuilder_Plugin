#ifndef __FBCAMERA_H__
#define __FBCAMERA_H__
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

/** \file fbmodel.h
*    Base class for Cameras.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
    /** \def FBSDK_DLL
    *    Be sure that FBSDK_DLL is defined only once...
    */
    #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbmodel.h>
#include <fbsdk/fbhud.h>

#ifdef FBSDKUseNamespace
    namespace FBSDKNamespace {
#endif

FB_DEFINE_COMPONENT( FBSDK_DLL, Camera           );
FB_DEFINE_COMPONENT( FBSDK_DLL, CameraStereo     );

////////////////////////////////////////////////////////////////////////////////////
// FBCamera
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCamera );

//! Frame size modes.
enum FBCameraFrameSizeMode { 
    kFBFrameSizeWindow,                    //!< Frame size of window.
    kFBFrameSizeFixedRatio,                //!< Fixed ratio.
    kFBFrameSizeFixedResolution,        //!< Fixed resolution.
    kFBFrameSizeFixedWidthResolution,    //!< Fixed width resolution.
    kFBFrameSizeFixedHeightResolution    //!< Fixed height resolution.
};

//! \enum FBCameraResolutionMode
/**Resolution modes.*/
enum FBCameraResolutionMode { 
    kFBResolutionCustom,                //!< Custom resolution mode or From Camera as a render setting.
    kFBResolutionD1NTSC,                //!< D1 NTSC.
    kFBResolutionNTSC,                    //!< NTSC.
    kFBResolutionPAL,                    //!< PAL.
    kFBResolutionD1PAL,                    //!< D1 PAL.
    kFBResolutionHD,                    //!< HD 1920x1080.
    kFBResolution640x480,                //!< 640x480.
    kFBResolution320x200,                //!< 320x200.
    kFBResolution320x240,                //!< 320x240.
    kFBResolution128x128,                //!< 128x128.
    kFBResolutionFullScreen                //!< FullScreen.
};

//! \enum FBCameraApertureMode
/** Aperture modes.*/
enum FBCameraApertureMode { 
    kFBApertureVertical,                //!< Vertical aperture varies.
    kFBApertureHorizontal,                //!< Horizontal aperture varies.
    kFBApertureVertHoriz,                //!< Vertical and horizontal aperture varies.
    kFBApertureFocalLength                //!< Focal Length aperture varies.
};

//! \enum FBCameraFilmBackType
/** Filmback types.*/
enum FBCameraFilmBackType { 
    kFBFilmBackCustom,                    //!< Custom Filmback.
    kFBFilmBack16mmTheatrical,            //!< 16mm Theatrical.
    kFBFilmBackSuper16mm,                //!< Super16mm.
    kFBFilmBack35mmAcademy,                //!< 35mm Academy.
    kFBFilmBack35mmTVProjection,        //!< 35mm TV Projection.
    kFBFilmBack35mmFullAperture,        //!< 35mm Full Aperture.
    kFBFilmBack35mm185Projection,        //!< 35mm 185 Projection.
    kFBFilmBack35mmAnamorphic,            //!< 35mm Anamorphic.
    kFBFilmBack70mmProjection,            //!< 70mm Projection.
    kFBFilmBackVistaVision,                //!< Vista Vision.
    kFBFilmBackDynavision,                //!< Dynavision.
    kFBFilmBackIMAX                        //!< IMAX.
};

//! \enum FBCameraViewPlaneMode
/**Camera plane viewing modes.*/
enum FBCameraViewPlaneMode { 
    kFBViewPlaneDisabled,                //!< Camera plane disabled.
    kFBViewPlaneAlways,                    //!< Always draw camera plane.
    kFBViewPlaneWhenMedia                //!< Camera plane when media.
};

//! \enum FBCameraDistanceMode
/**Camera plane distance modes.*/
enum FBCameraDistanceMode { 
    kFBDistModeRelativeToInterest,        //!< Camera plane distance relative to interest.
    kFBDistModeAbsoluteFromCamera        //!< Camera plane distance absolute from camera.
};

//! \enum FBCameraSafeAreaMode
/** Safe area modes.*/
enum FBCameraSafeAreaMode { 
    kFBSafeAreaSquare,                    //!< Square safe area.
    kFBSafeAreaRound                    //!< Round safe area.
};

//! \enum FBCameraAntiAliasingMethod
/**Antialiasing methods.*/
enum FBCameraAntiAliasingMethod    { 
    kFBAntiAliasingSoftware,            //!< Antaliasing in software.
    kFBAntialiasingMultiSamplingOnyx    //!< Multisampling (only on Onyx).
};

//! \enum FBCameraSamplingType
/** Antialiasing sampling types.*/
enum FBCameraSamplingType { 
    kFBSamplingUniform,                    //!< Uniform sampling.
    kFBSamplingStochastic                //!< Stochastic sampling.
};

//! \enum FBCameraFocusDistanceSource
/**Focus distance sources.*/
enum FBCameraFocusDistanceSource { 
    kFBFocusDistanceCameraInterest,      //!< Interest as source.
    kFBFocusDistanceSpecificDistance,    //!< Specific distance as source.
    kFBFocusDistanceModel                //!< Another model's position as source.
};

//! \enum FBCameraType
/**Focus distance types.*/
enum FBCameraType { 
    kFBCameraTypePerspective,            //!< Interest as source.
    kFBCameraTypeOrthogonal                //!< Specific distance as source.
};

//! \enum FBCameraMatrixType
/**Camera matrix types in OpenGL convention.*/
enum FBCameraMatrixType { 
    kFBProjection,                      //!< Camera's Projection matrix.
    kFBModelView,                       //!< Camera's combined Model-View matrix.
    kFBModelViewProj,                   //!< Camera's combined Model-View-Projection matrix.
    kFBProjInverse                      //!< Camera's Projection Inverse matrix.
};

FB_DEFINE_ENUM( FBSDK_DLL, CameraType                    ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraApertureMode            ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraFilmBackType            ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraFrameSizeMode           ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraResolutionMode          ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraViewPlaneMode           ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraDistanceMode            ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraSafeAreaMode            ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraAntiAliasingMethod      ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraSamplingType            );
FB_DEFINE_ENUM( FBSDK_DLL, CameraFocusDistanceSource     ); 
FB_DEFINE_ENUM( FBSDK_DLL, CameraMatrixType              ); 

/** Creates custom cameras and manages system cameras.
    When you look at a scene in the MotionBuilder Viewer, you are using a camera view. 

    There are two types of cameras:
    \li Producer cameras. By default one of the producer cameras is used. These are always present. They can be configured but not destroyed.
    \li Custom cameras, created by the user.
    
    The SystemCamera property indicates whether a given camera
    is a producer or a custom camera.

    When you create a camera you should make it visible with the show property (inherited from FBModel).

    Use FBCameraSwitcher to get and set the current camera. For usage, see the Python sample CameraSwitcher.py.

    To see how to create a camera with a marker as an interest, see the Python sample code in FBCamera.py. For usage in C++, see the manipcamera sample.
*/
class FBSDK_DLL FBCamera : public FBModel {
    __FBClassDeclare( FBCamera,FBModel );
public:
    /**  Constructor.
    *    \param    pName        Name of camera.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBCamera(const char * pName, HIObject pObject=NULL);

    FBPropertyBool                        SystemCamera;           //!< <b>Read Only Property:</b> Indicate if this a producer (default or system) camera or a custom (user-created) camera.

    // Camera Format
    FBPropertyCameraFrameSizeMode        FrameSizeMode;          //!< <b>Read Write Property:</b> Frame size standard mode.
    FBPropertyCameraResolutionMode        ResolutionMode;         //!< <b>Read Write Property:</b> Resolution standard mode.
    FBPropertyDouble                    ResolutionWidth;        //!< <b>Read Write Property:</b> Resolution width.
    FBPropertyDouble                    ResolutionHeight;       //!< <b>Read Write Property:</b> Resolution height.
    FBPropertyDouble                    WindowWidth;            //!< <b>Read Only Property:</b> Window width.
    FBPropertyDouble                    WindowHeight;           //!< <b>Read Only Property:</b> Window height.
    FBPropertyDouble                    PixelAspectRatio;       //!< <b>Read Write Property:</b> Pixel aspect ratio.
    FBPropertyDouble                    NearPlaneDistance;      //!< <b>Read Write Property:</b> Near plane distance.
    FBPropertyDouble                    FarPlaneDistance;       //!< <b>Read Write Property:</b> Far plane distance.
    FBPropertyBool                        MouseLockCamera;        //!< <b>Read Write Property:</b> Mouse lock for camera?
    FBPropertyCameraType                Type;                   //!< <b>Read Write Property:</b> Type of camera
    FBPropertyCameraApertureMode        ApertureMode;           //!< <b>Read Write Property:</b> Aperture mode.
    FBPropertyAnimatableDouble            FieldOfView;            //!< <b>Read Write Property:</b> Field of View (used when in horizontal or vertical aperture modes).

    FBPropertyAnimatableDouble            FieldOfViewX;           //!< <b>Read Write Property:</b> Field of View X angle (used in horizontal and vertical aperture mode).
    FBPropertyAnimatableDouble            FieldOfViewY;           //!< <b>Read Write Property:</b> Field of View Y angle (used in horizontal and vertical aperture mode).
    FBPropertyAnimatableDouble            OpticalCenterX;         //!< <b>Read Write Property:</b> Optical Center X (mm).
    FBPropertyAnimatableDouble            OpticalCenterY;         //!< <b>Read Write Property:</b> Optical Center Y (mm).
    FBPropertyAnimatableDouble            FocalLength;            //!< <b>Read Write Property:</b> Focal Length.

    FBPropertyCameraFilmBackType        FilmBackType;           //!< <b>Read Write Property:</b> Film back standard type.
    FBPropertyDouble                    FilmSizeWidth;          //!< <b>Read Write Property:</b> Width of the film.
    FBPropertyDouble                    FilmSizeHeight;         //!< <b>Read Write Property:</b> Height of the film.
    FBPropertyDouble                    FilmAspectRatio;        //!< <b>Read Write Property:</b> Film aspect ratio.
    FBPropertyDouble                    SqueezeRatio;           //!< <b>Read Write Property:</b> Squeeze ratio.
    
    static const double OrthoFactor;    //!< Constant scale factor to be used with #OrthoZoom for orthographic cameras.
    
    /*! \brief <b>Read Write Property:</b> Zoom factor of an orthographic camera.

     <br>OrthoZoom is only applicable if the camera has orthographic projection (i.e., Type == FBCameraType::kFBCameraTypeOrthogonal).
     <br>This value changes when the orthographic camera is zoomed in or out.
     <br>Refer to the following code if you wish to compute the left, right, top, and bottom view planes of the camera.
     
     \code
     double lW = mCam.CameraViewportWidth;
     double lH = mCam.CameraViewportHeight;
     double lPixelRatio = mCam.PixelAspectRatio;
     const double lFactor = mCam.OrthoZoom * FBCamera::OrthoFactor;
     if( lW < lH )
     {
        mLeftPlane   =  -lFactor * lPixelRatio;
        mRightPlane  =   lFactor * lPixelRatio;
        mBottomPlane = -(lFactor * lH) / lW;
        mTopPlane    =  (lFactor * lH) / lW;
     }
     else
     {
        lW *= lPixelRatio;
        mLeftPlane   = -(lFactor * lW) / lH;
        mRightPlane  =  (lFactor * lW) / lH;
        mBottomPlane =  -lFactor;
        mTopPlane    =   lFactor;
     }
     \endcode
     */
    FBPropertyDouble OrthoZoom;
    

    // Camera Background options
    FBPropertyTexture                    BackGroundTexture;              //!< <b>Read Write Property:</b> Background Texture
    FBPropertyVideo                      BackGroundMedia;                //!< \deprecated <b>Read Write Property:</b> BackGround Image
    FBPropertyCameraViewPlaneMode        ViewBackGroundPlaneMode;        //!< <b>Read Write Property:</b> Background plane view mode
    FBPropertyBool                       BackGroundImageCenter;          //!< <b>Read Write Property:</b> Center the background image
    FBPropertyBool                       BackGroundImageFit;             //!< <b>Read Write Property:</b> Fit the background image
    FBPropertyBool                       BackGroundImageKeepRatio;       //!< <b>Read Write Property:</b> Keep the background image's ratio
    FBPropertyBool                       BackGroundImageCrop;            //!< <b>Read Write Property:</b> Crop the background image
    FBPropertyAnimatableDouble           BackGroundImageOffsetX;         //!< <b>Read Write Property:</b> Ignored if BackGroundImageFit is true. X offset, in term of percentage of the fit background image width, applied on the background image.
    FBPropertyAnimatableDouble           BackGroundImageOffsetY;         //!< <b>Read Write Property:</b> Ignored if BackGroundImageFit is true. Y offset, in term of percentage of the fit background image height, applied on the background image.
    FBPropertyAnimatableDouble           BackGroundImageScaleX;          //!< <b>Read Write Property:</b> Ignored if BackGroundImageFit is true. X scale, in term of percentage of the fit background image width, applied on the background image.
    FBPropertyAnimatableDouble           BackGroundImageScaleY;          //!< <b>Read Write Property:</b> Ignored if BackGroundImageFit and/or BackGroundImageKeepRatio is true. Y scale, in term of percentage of the fit background image height, applied on the background image. The X scale property is considered instead of this Y scale property if BackGroundImageKeepRatio is set to true.
    FBPropertyDouble                     BackGroundPlaneDistance;        //!< <b>Read Write Property:</b> Set the distance for the background plane.
    FBPropertyCameraDistanceMode         BackGroundPlaneDistanceMode;    //!< <b>Read Write Property:</b> Select mode for the background plane's distance.

    // Camera Foreground options
    FBPropertyAnimatableDouble           ForeGroundAlpha;                //!< <b>Read Write Property:</b> Opacity of foreground.
    FBPropertyDouble                     ForeGroundMaterialThreshold;    //!< <b>Read Write Property:</b> Material threshold for a transparent foreground.
    FBPropertyBool                       ForeGroundTransparent;          //!< <b>Read Write Property:</b> Is the foreground transparent?
    FBPropertyTexture                    ForeGroundTexture;              //!< <b>Read Write Property:</b> ForeGround Texture
    FBPropertyVideo                      ForeGroundMedia;                //!< \deprecated <b>Read Write Property:</b> ForeGround Image
    FBPropertyCameraViewPlaneMode        ViewForeGroundPlaneMode;        //!< <b>Read Write Property:</b> Foreground plane view mode
    FBPropertyBool                       ForeGroundImageCenter;          //!< <b>Read Write Property:</b> Center the foreground image
    FBPropertyBool                       ForeGroundImageFit;             //!< <b>Read Write Property:</b> Fit the foreground image
    FBPropertyBool                       ForeGroundImageKeepRatio;       //!< <b>Read Write Property:</b> Keep the foreground image's ratio?
    FBPropertyBool                       ForeGroundImageCrop;            //!< <b>Read Write Property:</b> Crop the foreground image
    FBPropertyAnimatableDouble           ForeGroundImageOffsetX;         //!< <b>Read Write Property:</b> Ignored if ForeGroundImageFit is true. X offset, in term of percentage of the fit foreground image width, applied on the foreground image.
    FBPropertyAnimatableDouble           ForeGroundImageOffsetY;         //!< <b>Read Write Property:</b> Ignored if ForeGroundImageFit is true. Y offset, in term of percentage of the fit foreground image height, applied on the foreground image.
    FBPropertyAnimatableDouble           ForeGroundImageScaleX;          //!< <b>Read Write Property:</b> Ignored if ForeGroundImageFit is true. X scale, in term of percentage of the fit foreground image width, applied on the foreground image.
    FBPropertyAnimatableDouble           ForeGroundImageScaleY;          //!< <b>Read Write Property:</b> Ignored if ForeGroundImageFit and/or ForeGroundImageKeepRatio is true. Y scale, in term of percentage of the fit foreground image height, applied on the foreground image. The X scale property is considered instead of this Y scale property if ForeGroundImageKeepRatio is set to true.
    FBPropertyDouble                     ForeGroundPlaneDistance;        //!< <b>Read Write Property:</b> Set the distance for the foreground plane.
    FBPropertyCameraDistanceMode         ForeGroundPlaneDistanceMode;    //!< <b>Read Write Property:</b> Select mode for the foreground plane's distance.

    // Camera View Options
    FBPropertyBool                       ViewCameraInterest;        //!< <b>Read Write Property:</b> Show the camera interest?
    FBPropertyBool                       ViewNearFarPlane;        //!< <b>Read Write Property:</b> Show near/far planes?
    FBPropertyBool                       ViewShowName;            //!< <b>Read Write Property:</b> Show name?
    FBPropertyBool                       ViewShowManipulators;    //!< <b>Read Write Property:</b> Show manipulators?
    FBPropertyBool                       ViewShowGrid;            //!< <b>Read Write Property:</b> Show grid?
    FBPropertyBool                       ViewShowAxis;            //!< <b>Read Write Property:</b> Show axis?
    FBPropertyBool                       ViewShowTimeCode;        //!< <b>Read Write Property:</b> Show time code?
    FBPropertyBool                       ViewDisplaySafeArea;    //!< <b>Read Write Property:</b> Display safe area?
    FBPropertyBool                       ViewOpticalCenter;        //!< <b>Read Write Property:</b> View optical center?
    FBPropertyCameraSafeAreaMode         SafeAreaMode;            //!< <b>Read Write Property:</b> Select mode for safe area.

    FBPropertyAnimatableColor            BackGroundColor;        //!< <b>Read Write Property:</b> Background color for camera.
    FBPropertyBool                       UseFrameColor;            //!< <b>Read Write Property:</b> Use frame color?
    FBPropertyColor                      FrameColor;                //!< <b>Read Write Property:</b> Frame color for camera.

    // Camera Render Options
        // Rendering Options
    FBPropertyBool                       UseAntiAliasing;        //!< <b>Read Write Property:</b> Use anti-aliasing?
    FBPropertyAnimatableBool             UseDepthOfField;        //!< <b>Read Write Property:</b> Use depth of field calculations?
    FBPropertyBool                       InteractiveMode;        //!< <b>Read Write Property:</b> Interactive mode?

        // Anti-aliasing Options
    FBPropertyDouble                     AntiAliasingIntensity;    //!< <b>Read Write Property:</b> Anti-aliasing intensity.
    FBPropertyCameraAntiAliasingMethod   AntiAliasingMethod;        //!< <b>Read Write Property:</b> Anti-aliasing method.
    FBPropertyInt                        NumberOfSamples;        //!< <b>Read Write Property:</b> Number of samples to oversample with.
    FBPropertyCameraSamplingType         SamplingType;            //!< <b>Read Write Property:</b> Type of over sampling.
    FBPropertyBool                       UseAccumulationBuffer;    //!< <b>Read Write Property:</b> Use accumulation buffer?
    
        // Depth of Field Options
    FBPropertyCameraFocusDistanceSource  FocusDistanceSource;      //!< <b>Read Write Property:</b> Select source for focusing.
    FBPropertyAnimatableDouble           FocusSpecificDistance;    //!< <b>Read Write Property:</b> Specfic distance for focusing.
    FBPropertyModel                      FocusModel;               //!< <b>Read Write Property:</b> Another model that determines the focus distance. 
    FBPropertyAnimatableDouble           FocusAngle;               //!< <b>Read Write Property:</b> Focus Angle (rendering dof).

        // 2D Magnifier
    FBPropertyBool                       Use2DMagnifier;            //!< <b>Read Write Property:</b> Enable/Disable the 2D Magnifier.
    FBPropertyBool                       Display2DMagnifierFrame;//!< <b>Read Write Property:</b> Enable/Disable the drawing of the 2D Magnifier frame box.
    FBPropertyAnimatableDouble           MagnifierZoom;            //!< <b>Read Write Property:</b> 2D Magnifier Zoom value.
    FBPropertyAnimatableDouble           MagnifierPosX;            //!< <b>Read Write Property:</b> 2D Magnifier X Position.
    FBPropertyAnimatableDouble           MagnifierPosY;            //!< <b>Read Write Property:</b> 2D Magnifier Y Position.

    // Other Attributes
    FBPropertyModel                      Interest;                //!< <b>Read Write Property:</b> Direct camera's interest. 
    FBPropertyAnimatableDouble           Roll;                    //!< <b>Read Write Property:</b> Camera's roll on it's Z axis.
    FBPropertyAnimatableDouble           TurnTable;                //!< <b>Read Write Property:</b> Camera's rotation around its interest.
    FBPropertyBool                       DisplayTurnTableIcon;    //!< <b>Read Write Property:</b> Enable/Disable the drawing of the Turn Table icon.

    // MotionBlur
    FBPropertyAnimatableDouble           MotionBlurIntensity;    //!< <b>Read Write Property:</b> Motion Blur Intensity.
    FBPropertyBool                       UseMotionBlur;            //!< <b>Read Write Property:</b> Enable Motion Blur.
    FBPropertyBool                       UseRealTimeMotionBlur;    //!< <b>Read Write Property:</b> Enable Real-time Motion Blur.

    // Viewport dimension (those property values are only updated & valid during custom renderer callback
    FBPropertyInt                        CameraViewportX;        //!< <b> Read Only Property:</b> Camera Viewport start position's X value
    FBPropertyInt                        CameraViewportY;        //!< <b> Read Only Property:</b> Camera Viewport start position's Y value
    FBPropertyInt                        CameraViewportWidth;    //!< <b> Read Only Property:</b> Camera Viewport width 
    FBPropertyInt                        CameraViewportHeight;   //!< <b> Read Only Property:</b> Camera Viewport height 

#ifndef K_NO_HUD
    FBPropertyListHUD                    HUDs;                   //!< <b> List :</b> HUDs present in this camera
#endif

    /**  Obtains the camera's matrix.
    *    \param     pMatrix         Matrix to fill with requested information.
    *    \param     pType           Camera Matrix type to obtain.
    *    \param     pEvalInfo       Take Display if none specified.
    */
    void GetCameraMatrix( FBMatrix& pMatrix, FBCameraMatrixType pType, FBEvaluateInfo* pEvalInfo = NULL );

    /**  Returns the world coordinates based on screen coordinates and input distance from the camera
    *    \param    pX Screen horizontal coordinate in pixel. When pRelativeToViewport is false, the range is between 0 and (WindowWidth - 1). When pRelativeToViewport is true, the range is between 0 to (CameraViewportWidth - 1). The coordinate starts at left of the region.
    *    \param    pY Screen vertical coordinate in pixel. When pRelativeToViewport is false, the range is between 0 and (WindowHeight - 1). When pRelativeToViewport is true, the range is between 0 to (CameraViewportHeight - 1). The coordinate starts at top of the region.
    *    \param    pDistanceFromCamera Distance from the camera to the resulting world coordinate position
    *    \param    pRelativeToViewport true indicates (pX,pY) is relative to the window; false indicates (pX,pY) is relative to the viewport of the camera. 
    *    \return   The world coordinates in 3D space
    */
    FBVector4d InverseProjection( int pX, int pY, double pDistanceFromCamera, bool pRelativeToViewport = false );

/*
////////////////WARNING////////////////////////////////////
BACK-COMP implementation: 
The proper implementation is to change UseDepthOfField from 
FBPropertyBool to FBPropertyAnimatableBool. This breaks 
backward compatibility and should only be done for major releases
////////////////WARNING////////////////////////////////////
*/
	void GetAnimatableFarPlane(FBPropertyAnimatableDouble *pProp);
	void GetAnimatableNearPlane(FBPropertyAnimatableDouble *pProp);
};

////////////////////////////////////////////////////////////////////////////////////
// FBCameraStereo
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCameraStereo );

//! \enum FBCameraStereoType
/* Stereo Type */
enum FBCameraStereoType 
{ 
    kFBCameraStereoNone,
    kFBCameraStereoConverged,
    kFBCameraStereoOff_Axis,
    kFBCameraStereoParallel
}; 

FB_DEFINE_ENUM( FBSDK_DLL, CameraStereoType); 

class FBSDK_DLL FBCameraStereo : public FBCamera
{
    __FBClassDeclare(FBCameraStereo, FBCamera);
public:
    /**    Constructor.
    *    \param    pName        Name of stereo camera.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBCameraStereo(const char * pName, HIObject pObject=NULL);

    FBPropertyCameraStereoType      Stereo;                         //!< <b>Read Write Property: </b> //!< This property handles the types of Stereo camera.
    FBPropertyAnimatableDouble      InteraxialSeparation;           //!< <b>Read Write Property: </b> This property handles the distance between left and right cameras.
    FBPropertyAnimatableDouble      ZeroParallax;                   //!< <b>Read Write Property: </b> This property handles the distance on the camera view axis where the zero parallax plane occurs.
    FBPropertyAnimatableDouble      ToeInAdjust;                    //!< <b>Read Write Property: </b> This property is to offset the computed toe-in effect when it's in Converged mode. 
    FBPropertyAnimatableDouble      FilmOffsetRightCam;             //!< <b>Read Write Property: </b> This property handles the film offset for the right camera.  (inch) 
    FBPropertyAnimatableDouble      FilmOffsetLeftCam;              //!< <b>Read Write Property: </b> This property handles the film offset for the left camera.   (inch) 
   
    FBPropertyCamera                RightCamera;                    //!< <b>Read Write Property: </b> This property hold the right camera connected to it.
    FBPropertyCamera                LeftCamera;                     //!< <b>Read Write Property: </b> This property hold the left camera connected to it.
    FBPropertyCamera                CenterCamera;                   //!< <b>Read Write Property: </b> This property hold the center camera connected to it. Must be either the master, left or right camera.

    FBPropertyString                PrecompFileName;                //!< <b>Read Write Property: </b> This property handles the precomp file name.
    FBPropertyString                RelativePrecompFileName;        //!< <b>Read Write Property: </b> This property handles the relative precomp file name.

    FBPropertyBool                  DisplayZeroParallaxPlane;       //!< <b>Read Write Property: </b>  Display the zero parallax plane.
    FBPropertyDouble                ZeroParallaxPlaneTransparency;  //!< <b>Read Write Property: </b>  Zero parallax plane transparency.
    FBPropertyColor                 ZeroParallaxPlaneColor;         //!< <b>Read Write Property: </b>  Zero parallax plane color.
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListCamera
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: Camera
class FBSDK_DLL FBPropertyListCamera : public FBPropertyListComponent
{
public:
    FBPropertyListCamera();
    /**    Get the model at \p pIndex.
    *    \param    pIndex    Index of camera to get.
    *    \return Camera at \p pIndex.
    */
    FBCamera* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// FBCameraSwitcher
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCameraSwitcher );

/** Camera switcher.
*   This class is a wrapper around the system's camera switcher object. There can
*   only be one switcher in a given scene. Any attempts at creating a new instance
*   will return the existing one.
*/
class FBSDK_DLL FBCameraSwitcher : public FBModel
{
    __FBClassDeclare( FBCameraSwitcher, FBBox );
public:
    /**    Constructor.
    */
    FBCameraSwitcher();

    FBPropertyCamera    CurrentCamera;        //!< <b>Read Write Property:</b> Camera currently being used by the switcher. Set to NULL to turn on evaluate switch, otherwise manual switch.
    FBPropertyInt       CurrentCameraIndex; //!< <b>Read Write Property:</b> Camera index currently being used by the switcher. Set to -1 to turn on evaluate switch.

	/** Plot the Camera Switcher animation onto a destination camera.
	*	The destination camera cannot be a system camera nor a camera currently used by the Camera Switcher.
	*	\param	pCamera		Destination camera to plot on.
	*	\return True if the plot operation has been processed successfully, false otherwise.
	*/
	bool PlotToCamera( FBCamera* pCamera );
};


#ifdef FBSDKUseNamespace
    }
#endif
#endif
