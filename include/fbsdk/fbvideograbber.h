#ifndef __FBVIDEOGRABBER_H__
#define __FBVIDEOGRABBER_H__
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

/**	\file fbvideograbber.h
*	Video grabbing.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbaudiofmt.h>
#include <fbsdk/fbimage.h>
#include <fbsdk/fbcamera.h>
#include <fbsdk/fbrenderer.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBVideoGrabber );
FB_DEFINE_COMPONENT( FBSDK_DLL, VideoGrabber );

//! Enum FBVideoRenderViewingMode
enum FBVideoRenderViewingMode	{
	FBViewingModeStandard,		//!< Standard
	FBViewingModeModelsOnly,	//!< Model Only
	FBViewingModeXRay, 			//!< X-Ray
	FBViewingModeCurrent,		//!< Current
	FBViewingModeCount			//!< Count
};		
//! Enum FBVideoRenderFieldMode
enum FBVideoRenderFieldMode		{
	FBFieldModeNoField,		//!< No Field
	FBFieldModeField0,		//!< Field 0
	FBFieldModeField1,		//!< Field 1
	FBFieldModeHalfField0,	//!< Half Field 0
	FBFieldModeHalfField1,  //!< Half Field 1
	FBFieldModeCount		//!< Count
};		
//! Enum FBVideoRenderDepth
enum FBVideoRenderDepth		{
	FBVideoRender24Bits,		//!< 24 bits
	FBVideoRender32Bits,		//!< 32 bits
	FBVideoRenderDepthCount		//!< Depth Count
};	
//! Type of locations where the audio is rendered when rendering a scene using a video format.
enum FBAudioOutputLocation		{
	FBAudioOutputLocationEmbedded,				//!< The audio is embedded within the video output file.
	FBAudioOutputLocationStandalone,			//!< The audio is rendered in a standalone output file.
	FBAudioOutputLocationEmbeddedAndStandalone,	//!< The audio is embedded within the video output file and is also rendered in a standalone output file.
	FBAudioOutputLocationCount					//!< Count
};

/** Video Grabbing Options structure.
*	Contain options to control how the grabbing process will occur.
*/
struct FBSDK_DLL FBVideoGrabOptions
{
	FBTimeSpan					mTimeSpan;				//!< Start and stop selection time to grab.
	FBTime						mTimeSteps;				//!< Time step length between each grab.
	FBCameraResolutionMode		mCameraResolution;		//!< Camera Resolution.
	FBVideoRenderDepth			mBitsPerPixel;			//!< Video grab color depth.
	FBVideoRenderFieldMode		mFieldMode;				//!< Video grab field mode.
	FBVideoRenderViewingMode	mViewingMode;			//!< Video grab viewing mode.
    FBStereoDisplayMode         mStereoDisplayMode;     //!< Video grab stereo display mode. default (kFBStereoDisplayModeCount) to use current viewpane's setting. 
    int                         mRendererCallbackIndex; //!< Specify renderer callback index. Set to -1 to use MotionBuilder default renderer, or any valid non-negative index corresponding to registered custom callback. Any other invalid values, e.g., -2 (default value) means that the renderer attached to the current viewpane will be used. 
    int                         mRendererCallbackPrefIndex; //!< Specify custom renderer callback's preference index.
	FBString					mOutputFileName;		//!< Grabbing destination file. When the image files are being rendered, the hash letters (###) specified in the file name will be replaced with the frame number. Zeros will be inserted when the digits of the frame number is less than the number of hash letters. All hash letters will NOT be altered except the one closest to the file extension.
	bool						mShowSafeArea;			//!< If true, display safe area. NOTE: If you use your own FBView, set also this option in FBViewingOptions.
	bool						mShowTimeCode;			//!< If true, display time code information. NOTE: If you use your own FBView, set also this option in FBViewingOptions.
	bool						mShowCameraLabel;		//!< If true, display camera label information. NOTE: If you use your own FBView, set also this option in FBViewingOptions.
	bool						mAntiAliasing;			//!< If true, video frames will be anti-aliased.
	bool						mRenderAudio;			//!< If true and there's audio in the scene, render the audio as well.
	FBAudioFmt					mAudioRenderFormat;		//!< Audio render format.
    int                         mStillImageCompression;	//!< Compression ratio for image(jpg) 0-100 where 0=Greatest compression, 100=Least Compression. For tif/tiff images, if different than 100, lossless compression will be applied.
	FBAudioOutputLocation		mAudioOutputLocation;	//!< Audio output location when rendering using a video format (for still image formats & SWF (Flash) format, the audio is always rendered in a standalone file).
	bool						mAudioUseCustomStandaloneFileName;	//!< If true and if the audio is rendered in a standalone output file, the audio file is generated at the file location specified by mAudioCustomStandaloneFileName, otherwise the audio file is generated in the same directory as the rendered images/video files based on their names.
	FBString					mAudioCustomStandaloneFileName;		//!< Destination for the custom audio standalone file, if mAudioUseCustomStandaloneFileName is set to true.
};

/** Video Grabbing Statistics structure.
*	Contain statistics about the current video grabbing process.
*/
struct FBVideoGrabStats
{
	int		mTotalFrameCount;			//!< Total frame count to grab.
	int		mRemainingFrameCount;		//!< Remaining frame count to grab.
	FBTime	mTotalTimeElapsed;			//!< Current total time elapsed since grabbing has started.
	FBTime	mEstimatedTime;				//!< Estimated time to complete grab.
	FBTime	mEstimatedTimeRemaining;	//!< Remaining estimated time to complete grab.
	FBTime	mTimePerFrame;				//!< Time it took to render and grab previous frame.
};

/** Video Grabber class.
*	Used to grab video frames generated with the FBRenderer.
*/
class FBSDK_DLL FBVideoGrabber : public FBComponent 
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBVideoGrabber, FBComponent);
  public:

	/**	Constructor.
	*	\param	pObject	For internal use only.
	*/
	FBVideoGrabber(HIObject pObject=NULL);

	//--- Grabbing options management
	/** SetOptions.
	*	\param pOptions Struct that contain all grabbing options.
	*/
	void SetOptions(FBVideoGrabOptions* pOptions);

	/** GetOptions give you a copy of current grabbing options.
	*	\return Struct that contain all grabbing options.
	*/
	FBVideoGrabOptions GetOptions();

	/** SetDefaultOptions.
	*	This function reset all grabbing options to the default value.
	*/
	void ResetOptions();

	//--- Rendering functions setup
	/** SetRefreshViewFunc.
	*	Set the callback function to be called for each frame render.
	*
	*	\param pThis Pointer to the callback receiver.
	*	\param pCallbackFuncPtr Pointer to the callback function.
	*/
	void SetRefreshViewFunc(void* pThis, void(*pCallbackFuncPtr)(void*));

	/** SetPostRenderFrameCallback.
	*	Set the callback function to be called after each frame is rendered.
	*
	*	\param pThis Pointer to the callback receiver.
	*	\param pCallbackFuncPtr Pointer to the callback function.
	*/
	void SetPostRenderFrameCallback(void* pThis, void(*pCallbackFuncPtr)(void*));

	//--- Grabbing control
	/** BeginGrab.
	*	Begin video grabbing session.
	*
	*	\return \b True if we can begin the grab session.
	*/
	bool BeginGrab();

	/** Grab.
	*	Grab all specified video frames.
	*/
	void Grab();

	/** EndGrab.
	*	Close video grabbing session.
	*/
	void EndGrab();

	/** Render a snapshot of the actual display.
	*	\param	pWidth
	*	\param	pHeight
	*	\param	pCameraLabel
	*	\param	pTimeCode
	*	\param	pSafeArea
	*	\param	pAxis
	*	\param	pGrid
	*	\param	pFrontPlate
	*	\param	pBackPlate
	*	\return	An FBimage containing data of the rendered snapshot.
	*/

	FBImage* RenderSnapshot(int pWidth=-1, int pHeight=-1, bool pCameraLabel=false, bool pTimeCode=false, bool pSafeArea=false, bool pAxis=false, bool pGrid=false, bool pFrontPlate=false, bool pBackPlate=false);
	
	//--- Grabbing statistics query
	/** GetStatistics.
	*	\return Struct that contain all grabbing statistics.
	*/
	FBVideoGrabStats GetStatistics();
	
	//--- Errors management
	/** GetLastErrorMsg.
	*	\return If an error occured, this function returns the last error message, otherwise an empty string.
	*/
	const char* GetLastErrorMsg();
};


#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
