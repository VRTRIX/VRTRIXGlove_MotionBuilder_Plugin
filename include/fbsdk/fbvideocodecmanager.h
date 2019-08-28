#ifndef __FBVIDEOCODEC_MANAGER_H__
#define __FBVIDEOCODEC_MANAGER_H__
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

/**	\file fbvideocodecmanager.h
*	Video codec selector and preference manager.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbstring.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif
    
    //! Enum FBVideoRenderDepth
    enum FBVideoCodecMode		{
        FBVideoCodecAsk,		        //!< Pop codec selection dialog each render
        FBVideoCodecUncompressed,		//!< Assume uncompressed codec
        FBVideoCodecStored		        //!< Pop dialog and stored its value         
    };	

    /** Video Codec manager class.
    *	Use to set or get codec used and codec params
    */
    class FBSDK_DLL FBVideoCodecManager
    {
        //--- Open Reality declaration.        
    public:

        /** GetCodecIdList.
        *	Get all codec id available for a given file format.
        *
        *	\param pFileFormatInfo: file format description string (AVI, MOV...)
        *	\param pCodecList Codec list id
        */
        static void GetCodecIdList( const char* pFileFormatInfo, FBStringList& pCodecList );

        /** GetVideoCodecMode.
        *	Get the current codec mode. This decide how the system behaves when ask to render a file (codec dialog, uncompress, use default codec)
        */
        static FBVideoCodecMode GetVideoCodecMode();

        /** SetVideoCodecMode.
        *	Get the current codec mode.        
            \param pVideoCodecMode: the codec mode to apply to the whole system
        */
        static void SetVideoCodecMode( FBVideoCodecMode pVideoCodecMode );
        
        /** SetDefaultCodec.
        *	Set the default codec id for a given file format. This is the codec that will be used if codec mode is FBVideoCodecUseDefault
            \param pFileFormatInfo: file format description string (AVI, MOV...)
        *	\param pCodecId: the codec id to set as default
        */
        static void SetDefaultCodec( const char* pFileFormatInfo, const char* pCodecId );

        /** GetDefaultCodec.
        *	Get the default codec id for a given file format. This is the codec that will be used if codec mode is FBVideoCodecUseDefault
            \param pFileFormatInfo: file format description string (AVI, MOV...)        
        */
        static const char* GetDefaultCodec( const char* pFileFormatInfo );
        
		/**	Register external video format suffix. Only alphabetic and number is allowed in provided suffix, and can not be empty suffix or the system exist suffixes.
         *  This will allow this suffix to be appeared in the filters of file dialog when importing video, also allow to create a texture/video object
         *  with a path containing this suffix via SDK.  However it will the custom SDK plug-in developer's responsibility to load the file into memory.
         *	\remarks After register an external video format, and save a scene with this kind of video. when start MotionBuilder next time and before load the scene back,
         *	\remarks It is necessary to call RegisterExternalVideoFormat to register this kind of video format again, otherwise this kind of video will not be loaded.
         *	\param	pFormatSuffix	Suffix/File extension of external video file format
         *	\return	true if register successful
         */
        static bool RegisterExternalVideoFormat( const char* pFormatSuffix );
    };


#ifdef FBSDKUseNamespace
}
#endif
#endif /* this must be the last line of this file */