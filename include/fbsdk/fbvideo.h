#ifndef __FBVIDEO_H__
#define __FBVIDEO_H__
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

/**	\file fbvideo.h
*	FBVideo and derivative classes.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbcore.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

    FB_DEFINE_COMPONENT( FBSDK_DLL, Video			);
    FB_DEFINE_COMPONENT( FBSDK_DLL, VideoIn			);
    FB_DEFINE_COMPONENT( FBSDK_DLL, VideoOut		);
    FB_DEFINE_COMPONENT( FBSDK_DLL, VideoClip		);
    FB_DEFINE_COMPONENT( FBSDK_DLL, VideoClipImage	);
    FB_DEFINE_COMPONENT( FBSDK_DLL, VideoSwitcher	);

    /** Video declaration.
    *	\param	ClassName	Name of Video class.
    *	\param	Parent		Parent class of \e ClassName.
    */
#define FBVideoDeclare( ClassName, Parent ) \
    FBClassDeclare( ClassName,Parent ); \
public: \
    ClassName(const char* pName):Parent(pName) { FBClassInit; } \
private:

    /** Video implementation.
    *	\param	ThisComponent	Name of Video class to implement.
    */
#define FBVideoImplementation( ThisComponent ) \
    FBClassImplementation( ThisComponent )

    ////////////////////////////////////////////////////////////////////////////////////
    // FBVideo
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBVideo );
    __FB_FORWARD( FBVideoClip );

    //! Video proxy modes.
    enum FBVideoProxyMode {   
        kFBVideoProxyNone,		//!< No video proxy.
        kFBVideoProxyOnPlay,	//!< Video proxy on play.
        kFBVideoProxyAlways		//!< Always video proxy.
    };

    //! Video storage modes.
    enum FBVideoStorageMode	{
        kFBVideoStorageDisk,			//!< Storage on disk.
        kFBVideoStorageMemory,			//!< Storage in memory.
        kFBVideoStorageDiskAsync		//!< Storage on disk async access.
    };

    //! Video interlace modes.
    enum FBVideoInterlaceMode {
        kFBVideoInterlaceNone,				//!< No interacling.
        kFBVideoInterlaceHalfFrameEven,		//!< Half frame (even field).
        kFBVideoInterlaceHalfFrameOdd,		//!< Half frame (odd field).
        kFBVideoInterlaceFullFrameEven,		//!< Full frame (even field).
        kFBVideoInterlaceFullFrameOdd		//!< Full frame (odd field).
    };

    //! Video color modes.
    enum FBVideoFormat {
        kFBVideoFormat_Any,
        kFBVideoFormat_Other,
        kFBVideoFormat_RGBA_32,
        kFBVideoFormat_RGB_24,
        kFBVideoFormat_BGRA_32,
        kFBVideoFormat_BGR_24,
        kFBVideoFormat_BGR_16,
        kFBVideoFormat_ABGR_32,
        kFBVideoFormat_ARGB_32,
        kFBVideoFormat_422
    };

    //! Video Resolution (1D) 
    enum FBVideoResolution
    {
        kFBVideo_RES_FULL = 0,
        kFBVideo_RES_1,
        kFBVideo_RES_2,
        kFBVideo_RES_4,
        kFBVideo_RES_8,
        kFBVideo_RES_16,
        kFBVideo_RES_32,
        kFBVideo_RES_64,
        kFBVideo_RES_128,
        kFBVideo_RES_256,
        kFBVideo_RES_512,
        kFBVideo_RES_1K,
        kFBVideo_RES_2K,
        kFBVideo_RES_4K,
        kFBVideo_RES_8K,
        kFBVideo_RES_16K
    };

	FB_DEFINE_ENUM( FBSDK_DLL, TimeMode	);
    FB_DEFINE_ENUM( FBSDK_DLL, VideoProxyMode		);
    FB_DEFINE_ENUM( FBSDK_DLL, VideoStorageMode		);
    FB_DEFINE_ENUM( FBSDK_DLL, VideoInterlaceMode	);
    FB_DEFINE_ENUM( FBSDK_DLL, VideoFormat			);
    FB_DEFINE_ENUM( FBSDK_DLL, VideoResolution      );

    /** Video media class.
    *	Similar to the FBModel class, the FBVideo class serves as a general media
    *	class for images, video clips and video memory, as well as the possibility
    *	of custom formats and custom live cards.
    *
    *   @warning    To have a valid FBVideo object, it must be constructed with
    *               a string pointing to a valid media file. After the creation,
    *               the method 'IsValid()' should be used to confirm the object's
    *               status. An invalid object cannot be used or interact with any
    *               other application object. The only property that can be read
    *               and modified is its 'Filename'. To make convert an invalid
    *               FBVideo object into a valid one, simply change its Filename
    *               property to point to a supported media file.
    */

    class FBSDK_DLL FBVideo : public FBBox {
        __FBClassDeclare( FBVideo,FBBox );
    public:
        /**	Constructor.
        *	\param	pName		Name of video media.
        *	\param	pObject		Internal parent object(default=NULL).
        *   @warning    The pName parameter must point to a valid media file, otherwise
        *               the object will not be valid. Use the method 'IsValid()' to
        *               confirm the object status.
        */
        FBVideo(const char* pName, HIObject pObject=NULL);

        FBPropertyBool					KeepOnGPU;		//!< <b>Read Write Property:</b> Don't auto flush from GPU if true. session runtime flag, won't be saved.
    };

    class FBSDK_DLL FBVideoClip : public FBVideo {
        __FBClassDeclare( FBVideoClip,FBVideo );
    public:
        /**	Constructor.
        *	\param	pName		Name of video media.
        *	\param	pObject		Internal parent object(default=NULL).
        *   @warning    The pName parameter must point to a valid media file, otherwise
        *               the object will not be valid. Use the method 'IsValid()' to
        *               confirm the object status.
        */
        FBVideoClip(const char* pName, HIObject pObject=NULL);

        virtual void FBDelete();

        /** Verifies the validity of the FBVideo object.
        *	\return \b true if data is valid.
        */
        bool IsValid();

        //--- Video (generic) properties.
        FBPropertyString				Filename;			//!< <b>Read Write Property:</b> Filename of media.
        FBPropertyString				RelativePath;		//!< <b>Read Only Property:</b> Relative path of media.
        FBPropertyVideoProxyMode		ProxyMode;			//!< <b>Read Write Property:</b> Proxy mode.
        FBPropertyVideoStorageMode		StorageMode;		//!< <b>Read Write Property:</b> Storage mode.
        FBPropertyInt					Width;				//!< <b>Read Only Property:</b> Width of image.
        FBPropertyInt					Height;				//!< <b>Read Only Property:</b> Height of image.
        FBPropertyInt					PowerOfTwoWidth;	//!< <b>Read Only Property:</b> Closest power of two value superior to width of image.
        FBPropertyInt					PowerOfTwoHeight;	//!< <b>Read Only Property:</b> Closest power of two value superior to height of image.
        FBPropertyVideoInterlaceMode	InterlaceMode;		//!< <b>Read Write Property:</b> Interlace mode.
        FBPropertyVideoFormat			Format;				//!< <b>Read Only Property:</b> Video format.

        //--- Video (clip) properties
        FBPropertyTime					TimeOffset;			//!< <b>Read Write Property:</b> Temporal offset for beginning of video.
        FBPropertyInt					StartFrame;			//!< <b>Read Write Property:</b> Frame to begin video playback from.
        FBPropertyInt					StopFrame;			//!< <b>Read Write Property:</b> Frame to end video playback at.
        FBPropertyDouble				FrameRate;			//!< <b>Read Write Property:</b> Frame rate. 
        FBPropertyDouble				PlaySpeed;			//!< <b>Read Write Property:</b> Playback speed.
        FBPropertyBool					FreeRunning;		//!< <b>Read Write Property:</b> Is free Running on?
        FBPropertyBool					Loop;				//!< <b>Read Write Property:</b> Loop video clip?

        FBPropertyTime					FrameTime;			//!< <b>Read Only Property:</b> Inverse of FPS, time per frame
        FBPropertyInt					CurrentFrame;		//!< <b>Read Write Property:</b> Current frame.
        FBPropertyInt					LastFrame;			//!< <b>Read Only Property:</b> Last frame in clip.
        FBPropertyTime					LastFrameTime;		//!< <b>Read Only Property:</b> Time of last frame
        FBPropertyTime					CurrentFrameTime;	//!< <b>Read Write Property:</b> Current time in clip.

        FBPropertyTime					CurrentFrameTimeCode;	//!< <b>Read Only Property:</b> Embedded timecode from current frame in clip. Use the method GetEmbeddedTimecode to get the timecode of a different frame than the current frame.

        /**	Draw a frame of the image to the current view.
        *	\param	pX		X position of image (default=0).
        *	\param	pY		Y position of image (default=0).
        *	\param	pW		Width of image (default=-1).
        *	\param	pH		Height of image (default=-1).
        *	\param	pFrame	Frame to draw (default=-1).
        */
        virtual void DrawImage(int pX = 0, int pY = 0, int pW = -1, int pH = -1, int pFrame = -1);

        /**	Get the current image buffer
        *	\param	pFrame	Frame to get image for (default=-1).
        *	\return	Handle to the image buffer specified by the \e pFrame parameter.
        */
        virtual unsigned char* GetImage(int pFrame = -1 );

        /** Increase Image update id after modification to trigger internal state refresh.
        */
        virtual void ImageIncUpdateID();

        /**	Get the current image buffer resized with width and height power of two.
        *	\return	Handle to the image buffer specified by the \e pFrame parameter.
        */
        virtual unsigned char* GetPowerOfTwoImage();

        /**	Get the texture ID.
        *	\return	ID of the texture
        */
        int GetTextureID();

		/**	Get the embedded timecode associated to a video clip frame.
        *	\param	pFrame		Video clip frame to get timecode for.
		*	\param	pTimeCode	The timecode object being filled by this method.
        *	\return	True if an embedded timecode is retrieved from the video clip, false otherwise. (Python: If no embedded timecode is retrieved, returns an FBTimeCode object with its time set to FBTime::Infinity).
        */
		virtual bool GetEmbeddedTimecode( int pFrame, FBTimeCode& pTimeCode );
    };

    __FB_FORWARD( FBVideoClipImage );

    class FBSDK_DLL FBVideoClipImage : public FBVideoClip {
        __FBClassDeclare( FBVideoClipImage,FBVideoClip );
    public:
        /**	Constructor.
        *	\param	pName		Name of image file.
        *	\param	pObject		Internal parent object(default=NULL).
        */
        FBVideoClipImage(const char* pName, HIObject pObject=NULL);

        /** \brief <b>Read Write Property:</b> Clip is an image sequence?
        *   \remarks When enable the image sequence property, the sequence pattern will be parsed from the filename of image file specified.
        *            A printf format will be generated from the first digits sequence by reverse searching the filename, ex: "seq01.%04da.jpg" from "seq01.0000a.jpg".
        *            All images in the same folder matching this printf pattern will be added to the image sequences.
        *            If one of the image sequences is not presenting, when playing, it will show as question marks.
        */
        FBPropertyBool					ImageSequence;
		FBPropertyBool					UseSystemFrameRate;	//!< <b>Read Write Property:</b> Clip is using system frame rate?
        FBPropertyVideoResolution       MaxMipMapResolution;//!< <b>Read Write Property:</b> Maximum MipMap resolution will be loaded into GPU.
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBVideoMemory
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBVideoMemory );

    /** FBVideoMemory allow external media source (which can't be supported by MoBu natively)
    *
    *   User could create / update OGL texture (GL_TEXTURE_2D type) externally, and pass in GL texture 
    *   object id to TextureOGLId property. 
    *
    *   See "Scripts/Samples/Video/VideoMemory.py" for usage example.
    *
    */
    class FBSDK_DLL FBVideoMemory : public FBVideo {
        __FBClassDeclare( FBVideoMemory,FBVideo );
    public:
        /**	Constructor.
        *	\param	pName		Name of video media.
        *	\param	pObject		Internal parent object(default=NULL).
        */
        FBVideoMemory(const char* pName, HIObject pObject=NULL);

        /**	Set image size to allow MoBu preview texture with proper dimension / aspect.
        *	\param	pW	Width of image.
        *	\param	pH	Height of image.
        */
        virtual void SetObjectImageSize(int pW,int pH);

        FBPropertyInt	TextureOGLId;				//!< <b>Read Write Property:</b> OpenGL texture buffer object id (GL_TEXTURE_2D type).
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBVideoIn
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBVideoIn );

    //! Video Live type
    enum FBVideoLiveType { 
        kFBVideoLiveDefault,	//!< Generic video input, type not specified
        kFBVideoLiveBasic		//!< Basic video input, like webcam and dv camera.
    };

    //! Basic video input class, supporting webcam and DV device.
    class FBSDK_DLL FBVideoIn : public FBVideo {
        __FBClassDeclare( FBVideoIn, FBVideo );
    public:
        /**	Constructor.
        *	\param	pObject		Internal parent object.
        */
        FBVideoIn(HIObject pObject=NULL);

        FBPropertyBool		Online;	    //!< <b>Read Write Property:</b> If true, the device is online and will display the current video feed.
        FBPropertyBool		Recording;	//!< <b>Read Write Property:</b> If true, the device will record during a recording session.
        FBPropertyBool		RecordAudio;//!< <b>Read Write Property:</b> If true, the device will also record audio during a recording session.
        FBPropertyString	FilePath;	//!< <b>Read Write Property:</b> Location of the generated movie file after a recording session.

        /** Set the current compressor to be used when recording.
        *	\param	pCompressorIndex      	Index of the compressor.
        *   \return True if successful. 
        */
        virtual bool 	LiveSetCompressor(int pCompressorIndex);

        /** Get the current compressor index.
        *   \return Index of the current compressor. 
        */
        virtual int  	LiveGetCompressor();

        /** Get the compressor count.
        *   \return Number of available compressor. 
        */
        virtual int  	LiveGetCompressorCount();

        /** Get the compressor name at a particular index.
        *   \return Name of the compressor. If the pCompressorIndex is higher than the number of compressor, the function will return NULL.
        */
        virtual const char* LiveGetCompressorName(int pCompressorIndex);

        /** Set the current resolution and frame rate for the device.
        *	\param	pIndex      	Index of the resolution and frame rate.
        */
        virtual void	LiveSetResolutionFR(int pIndex);

        /** Get the current resolution and frame rate index.
        *   \return Index of the current resolution and frame rate. 
        */
        virtual int		LiveGetResolutionFR();

        /** Get the number of resolution and frame rate available for the device.
        *   \return Number of available resolution and frame rate. 
        */
        virtual int  	LiveGetResolutionFRCount();

        /** Get the resolution and frame rate string description at the specified index.
        *	\param	pIndex      	Index of the resolution and frame rate.
        *   \return Name of the resolution and frame rate. 
        */
        virtual const char*	LiveGetResolutionFRName(int pIndex);

        /** Get the type of the video input device.
        *   \return Type of the video input device. 
        */
        virtual FBVideoLiveType	 LiveGetType();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBVideoOut
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBVideoOut );

    //! Video media class.
    class FBSDK_DLL FBVideoOut : public FBVideo {
        __FBClassDeclare( FBVideoOut, FBVideo );
    public:
        /**	Constructor.
        *	\param	pObject		Internal parent object.
        */
        FBVideoOut(HIObject pObject=NULL);
        FBPropertyBool		Online;	    //!< <b>Read Write Property:</b> If true, the device is online and will output display.
    };


    ////////////////////////////////////////////////////////////////////////////////////
    // FBVideoSwitcher
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBVideoSwitcher		);
    __FB_FORWARD( FBEventVideoSwitcher	);

    //! Clip end actions
    enum FBClipEnd { 
        kFBClipEndEnd,	//!< On clip end stop clip.
        kFBClipEndLoop	//!< On clip end loop clip.
    };
    //! Play modes.
    enum FBPlayMode	{ 
        kFBPlayModeNoPlay,			//!< No play (most common).
        kFBPlayModePreviewToEnd,	//!< Preview clip until end.
        kFBPlayModePlay,			//!< Play clip.
        kFBPlayModeLoop,			//!< Loop clip.
        kFBPlayModePlayToEnd		//!< Play clip to end.
    };

    FB_DEFINE_ENUM( FBSDK_DLL, ClipEnd	);
    FB_DEFINE_ENUM( FBSDK_DLL, PlayMode	);

    //! Video switcher callback event.
    class FBSDK_DLL FBEventVideoSwitcher : public FBEvent
    {
    public:
        /**	Constructor.
        *	\param	pEvent	Internal video event.
        */
        FBEventVideoSwitcher( HKEventBase pEvent );		

        FBPropertyVideoSwitcher			VideoSwitcher;		//!< <b>Read Only Property:</b> Video switcher.
        FBPropertykReference			Reference;			//!< <b>Read Only Property:</b> Data.
        FBPropertyClipEnd				EndType;			//!< <b>Read Only Property:</b> Clip end action.
    };

    //! Video Switcher class.
    class FBSDK_DLL FBVideoSwitcher : public FBVideo
    {
        __FBClassDeclare( FBVideoSwitcher, FBVideo );
    public:
        /**	Constructor.
        *	\param	pName		Name of video switcher(default=NULL).
        *	\param	pObject		For internal use only(default=NULL).
        */
        FBVideoSwitcher( const char* pName = NULL, HIObject pObject = NULL );

        /** Reset the video switcher (clear all clips).
        */
        virtual void ResetVideoSwitcher();
        /** Finish the current video.
        */
        virtual void FinishCurrentVideo();	
        /** Prepare the next frame.
        */
        virtual void PrepareNextFrame();
        /** Swap the current video.
        *	\param	pVideo		Video to use as new current.
        */
        virtual void SwapCurrent( FBVideo* pVideo );
        /** Set the next clip.
        *	\param	pVideo		Next clip to load.
        *	\param	pMode		Mode to play clip with.
        */
        virtual void SetNextClip( FBVideo* pVideo, FBPlayMode pMode );

        /**
        */
        virtual bool IsSDKSwitcher();

        FBPropertyInt					CurrentFrame;		//!< <b>Read Write Property:</b> Current frame.
        FBPropertyPlayMode				PlayMode;			//!< <b>Read Write Property:</b> Current play mode.
        FBPropertyTime					TimeRemaining;		//!< <b>Read Only Property:</b> Time remaining.

        FBPropertyVideo					CurrentVideo;		//!< <b>Read Only Property:</b> Current video.
        FBPropertyEvent					OnClipEnd;			//!< <b>Event:</b> Clip end event.
        FBPropertyDevice				DeviceOwner;		//!< <b>Read Write Property:</b> Hook onto owner device.
        FBPropertyBool					UsingSystemTime;	//!< <b>Read Write Property:</b> Using the system time?
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListVideoClip
    ////////////////////////////////////////////////////////////////////////////////////
    //! \b PropertyList: VideoClip
    class FBSDK_DLL FBPropertyListVideoClip : public FBPropertyListComponent
    {
    public:
        FBPropertyListVideoClip();
        /**	Get the video at \e pIndex.
        *	\param	pIndex	Index to get video at.
        *	\return Video at \e pIndex.
        */
        FBVideoClip* operator[](int pIndex);
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListVideoIn
    ////////////////////////////////////////////////////////////////////////////////////
    //! \b PropertyList: VideoIn
    class FBSDK_DLL FBPropertyListVideoIn : public FBPropertyListComponent
    {
    public:
        FBPropertyListVideoIn();
        /**	Get the video at \e pIndex.
        *	\param	pIndex	Index to get video at.
        *	\return Video at \e pIndex.
        */
        FBVideoIn* operator[](int pIndex);
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListVideoOut
    ////////////////////////////////////////////////////////////////////////////////////
    //! \b PropertyList: VideoOut
    class FBSDK_DLL FBPropertyListVideoOut : public FBPropertyListComponent
    {
    public:
        FBPropertyListVideoOut();
        /**	Get the video at \e pIndex.
        *	\param	pIndex	Index to get video at.
        *	\return Video at \e pIndex.
        */
        FBVideoOut* operator[](int pIndex);
    };

#ifdef FBSDKUseNamespace
}
#endif
#endif
