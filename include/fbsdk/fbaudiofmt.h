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

/** Get default audio format. 
*    \return  An audio format object. 
*/
FBSDK_DLL FBAudioFmt FBAudioFmt_GetDefaultFormat();

/** Append the rendering audio format using the specified settings. For example, to set audio format to 2 channels, 16 bit, 44100 rate, use the following function: AudioFormat = FBAudioFmt_AppendFormat(0, 2, 16, 44100)
*    \param  pFormat    Audio format to use. Set this to 0 if there is no audio format to be appended.
*    \param  pChannels  Number of channels. Valid values are 0, 1, 2, 4, 8.
*    \param  pBits      Bit depth. Valid values are 0, 8, 16, 24, 32.
*    \param  pRate      Audio rate. Valid values are 0, 8000, 11025, 12000, 12500, 16000, 22050, 24000, 25000, 32000, 44100, 48000, 50000, 64000, 88200, 96000, 100000.
*    \return An audio format object with the specified format. 
*
*   Python sample code:
*   @code

    from pyfbsdk import *

    def printFormat( AudioFormat ):
        print "Audio Render Format: ", AudioFormat
        print "Audio Channels: ", FBAudioFmt_GetChannelValue( AudioFormat )
        print "Audio Bit Depth: ", FBAudioFmt_GetBitsValue( AudioFormat )
        print "Audio Rate: ", FBAudioFmt_GetRateValue( AudioFormat )
        print ""

    # Given an AudioFormat, modify the rate from the old rate to 48000 while
    # keeping the other settings intact
    AudioFormat = FBAudioFmt_GetDefaultFormat()
    print "Old Format:"
    printFormat( AudioFormat )

    oldrate = FBAudioFmt_GetRateValue( AudioFormat )
    AudioFormat = FBAudioFmt_RemoveFormat(AudioFormat, 0, 0, oldrate)
    print "Format after removing Audio Rate:"
    printFormat( AudioFormat )

    AudioFormat = FBAudioFmt_AppendFormat(AudioFormat, 0, 0, 48000)
    print "New Format after modifying Audio Rate to 48000"
    printFormat( AudioFormat )

*   @endcode
*/
FBSDK_DLL FBAudioFmt FBAudioFmt_AppendFormat(FBAudioFmt pFormat, int pChannels, int pBits, int pRate);

/** Append the rendering audio format with another audio format.
*    \param  pFormat    Audio format to use. 
*    \param  pSrcFormat Audio format to be appended.
*    \return An audio format object with the specified format. 
*/
FBSDK_DLL FBAudioFmt FBAudioFmt_AppendFormat(FBAudioFmt pFormat, const FBAudioFmt pSrcFormat);

/** Remove channels, bit depth, or rate from the specified audio format object. Please refer to python example in FBAudioFmt_AppendFormat.
*    \param  pFormat    Audio format to use.
*    \param  pChannels  Number of channels to remove. Set this to 0 if you don't want to remove the channel.
*    \param  pBits      Bit depth to remove. Set this to 0 if you don't want to remove bit depth.
*    \param  pRate      Audio rate to remove. Set this to 0 if you don't want to remove audio rate.
*    \return An audio format object without the specified format settings passed in parameter.
*/
FBSDK_DLL FBAudioFmt FBAudioFmt_RemoveFormat(FBAudioFmt pFormat, int pChannels, int pBits, int pRate);

/** Remove audio format from another audio format object. 
*    \param  pFormat    Audio format to use.
*    \param  pSrcFormat Audio format to remove.
*    \return An audio format object without the specified format settings passed in parameter.
*/
FBSDK_DLL FBAudioFmt FBAudioFmt_RemoveFormat(FBAudioFmt pFormat, const FBAudioFmt pSrcFormat);

/** Get the channel value of the Audio format object.
*    \param  pFormat    Audio format to use.
*    \return Channel value as an integer value.
*/
FBSDK_DLL int FBAudioFmt_GetChannelValue(FBAudioFmt pFormat);

/** Get the bit depth value of the Audio format object.
*    \param  pFormat    Audio format to use.
*    \return Bit depth value as an integer value.
*/
FBSDK_DLL int FBAudioFmt_GetBitsValue(FBAudioFmt pFormat);

/** Get the bytes value of the Audio format object.
*    \param  pFormat    Audio format to use.
*    \return Bytes value as an integer value.
*/
FBSDK_DLL int FBAudioFmt_GetBytesValue(FBAudioFmt pFormat);

/** Get the rate value of the Audio format object.
*    \param  pFormat    Audio format to use.
*    \return Audio rate value as an integer value.
*/
FBSDK_DLL int FBAudioFmt_GetRateValue(FBAudioFmt pFormat);

/** Test if the given audio format object contains the channel, bit depth, and rate.
*    \param  pFormat    Audio format to test.
*    \param  pChannels  Number of channels to test.
*    \param  pBits      Bit depth to test.
*    \param  pRate      Audio rate to test.
*    \return True if the given audio format object contains the channel, bit depth, and rate.
*/
FBSDK_DLL bool FBAudioFmt_TestFormat(const FBAudioFmt pSrcFormat, int pChannels, int pBits, int pRate);

/** Converts an FBAudioChannelMode enum value to its FBAudioFmt object equivalent.
*    \param  pChannelMode    The channel mode enum value.
*    \return The FBAudioFmt object equivalent to the input channel mode enum value.
*/
FBSDK_DLL FBAudioFmt FBAudioFmt_ConvertChannelMode( FBAudioChannelMode pChannelMode );

/** Converts an FBAudioBitDepthMode enum value to its FBAudioFmt object equivalent.
*    \param  pBitDepthMode    The bit depth mode enum value.
*    \return The FBAudioFmt object equivalent to the input bit depth mode enum value.
*/
FBSDK_DLL FBAudioFmt FBAudioFmt_ConvertBitDepthMode( FBAudioBitDepthMode pBitDepthMode );

/** Converts an FBAudioRateMode enum value to its FBAudioFmt object equivalent.
*    \param  pRateMode    The rate mode enum value.
*    \return The FBAudioFmt object equivalent to the input rate mode enum value.
*/
FBSDK_DLL FBAudioFmt FBAudioFmt_ConvertRateMode( FBAudioRateMode pRateMode );

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
