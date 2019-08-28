#ifndef __FBAUDIOFMT_H__
#define __FBAUDIOFMT_H__
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

/**	\file fbaudiofmt.h
*	Audio formats definition.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbtypes.h>

/*! \var FBAudioFmt
 *  A type definition for FBAudioFmt. 
 */
typedef int			FBAudioFmt;

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

//! Enum FBAudioChannelMode
enum FBAudioChannelMode	{
	kFBAudioChannelModeMono,	//!< 1 channel, Wave file render support.
	kFBAudioChannelModeStereo,	//!< 2 channels, Wave file render support.
	kFBAudioChannelMode_4,		//!< 4 channels, Wave file render not support.
	kFBAudioChannelMode_8,		//!< 8 channels, Wave file render not support. 
};		
//! Enum FBAudioBitDepthMode
enum FBAudioBitDepthMode {
	kFBAudioBitDepthMode_8,		//!< 8 bits, Wave file render support.
	kFBAudioBitDepthMode_16,	//!< 16 bits, Wave file render support.
	kFBAudioBitDepthMode_24,	//!< 24 bits, Wave file render not support.
	kFBAudioBitDepthMode_FP,	//!< FP type audio, Wave file render not support.
};		
//! Enum FBAudioRateMode
enum FBAudioRateMode {
	kFBAudioRateMode_8000,		//!< 8000 hz, Wave file render support.
	kFBRAudioateMode_11025,		//!< 11025 hz, Wave file render support.
	kFBAudioRateMode_12000,		//!< 12000 hz, Wave file render support.
	kFBAudioRateMode_12500,		//!< 12500 hz, Wave file render not support.
	kFBAudioRateMode_16000,		//!< 16000 hz, Wave file render support.
	kFBAudioRateMode_22050,		//!< 22050 hz, Wave file render support.
	kFBAudioRateMode_24000,		//!< 24000 hz, Wave file render support.
	kFBAudioRateMode_25000,		//!< 25000 hz, Wave file render not support.
	kFBAudioRateMode_32000,		//!< 32000 hz, Wave file render support.
	kFBAudioRateMode_44100,		//!< 44100 hz, Wave file render support.
	kFBAudioRateMode_48000,		//!< 48000 hz, Wave file render support.
	kFBAudioRateMode_50000,		//!< 50000 hz, Wave file render not support.
	kFBAudioRateMode_64000,		//!< 64000 hz, Wave file render support.
	kFBAudioRateMode_88200,		//!< 88200 hz, Wave file render support.
	kFBAudioRateMode_96000,		//!< 96000 hz, Wave file render support.
	kFBAudioRateMode_100000,	//!< 100000 hz, Wave file render not support.
};	

FBSDK_DLL FBAudioFmt FBAudioFmt_GetDefaultFormat();

FBSDK_DLL FBAudioFmt FBAudioFmt_AppendFormat(FBAudioFmt pFormat, int pChannels, int pBits, int pRate);
FBSDK_DLL FBAudioFmt FBAudioFmt_AppendFormat(FBAudioFmt pFormat, const FBAudioFmt pSrcFormat);

FBSDK_DLL FBAudioFmt FBAudioFmt_RemoveFormat(FBAudioFmt pFormat, int pChannels, int pBits, int pRate);
FBSDK_DLL FBAudioFmt FBAudioFmt_RemoveFormat(FBAudioFmt pFormat, const FBAudioFmt pSrcFormat);

FBSDK_DLL int FBAudioFmt_GetChannelValue(FBAudioFmt pFormat);
FBSDK_DLL int FBAudioFmt_GetBitsValue(FBAudioFmt pFormat);
FBSDK_DLL int FBAudioFmt_GetBytesValue(FBAudioFmt pFormat);
FBSDK_DLL int FBAudioFmt_GetRateValue(FBAudioFmt pFormat);

FBSDK_DLL bool FBAudioFmt_TestFormat(const FBAudioFmt pSrcFormat, int pChannels, int pBits, int pRate);

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
