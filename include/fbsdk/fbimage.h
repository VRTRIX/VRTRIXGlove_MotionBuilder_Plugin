#ifndef __FBIMAGE_H__
#define __FBIMAGE_H__
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

/**	\file fbimage.h
*	Image interface for FBSDK
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBImage );
FB_DEFINE_COMPONENT( FBSDK_DLL, Image );

//! Image formats.
enum FBImageFormat {
	kFBImageFormatRGBA32,
	kFBImageFormatRGB24,
	kFBImageFormatBGRA32,
	kFBImageFormatBGR24,
	kFBImageFormatBGR16,
	kFBImageFormatABGR32,
	kFBImageFormatARGB32,
	kFBImageFormatUnknown
};

//! Image types.
enum FBImageType {
	kFBImageTypeFrame,
	kFBImageTypeField
};

//! Image field interleave types.
enum FBImageInterleaveType {
	kFBImageInterleaveTypeFullFrame,
	kFBImageInterleaveTypeOdd,
	kFBImageInterleaveTypeEven,
	kFBImageInterleaveTypeAverage
};

//! Image interpolation types.
enum FBImageInterpolationType {
	kFBImageInterpolationTypeNone,
	kFBImageInterpolationTypeDuplicate,
	kFBImageInterpolationTypeLinear
};

FB_DEFINE_ENUM(FBSDK_DLL, ImageFormat);
FB_DEFINE_ENUM(FBSDK_DLL, ImageType);
FB_DEFINE_ENUM(FBSDK_DLL, ImageInterleaveType);
FB_DEFINE_ENUM(FBSDK_DLL, ImageInterpolationType);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBImage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Image class.
*	Utility class used to load and get manipulate image data from disk or memory.
*/
class FBSDK_DLL FBImage : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBImage, FBComponent);

public:
	/**	Constructor.
	*	\param	pFileName Path to the image file. If pObject is not NULL, pFileName will be ignored.
	*	\param	pObject For internal use only.
	*/
	FBImage(const char* pFileName, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	/** Cleanup image data, making it black.
	*/
	void Cleanup();


	/**	Init.
	*	\param	pFormat	Image format used to initialize data buffer.
	*	\param	pWidth	Image width in pixels.
	*	\param	pHeight	Image height in pixels.
	*/
	
	bool Init(FBImageFormat pFormat, int pWidth, int pHeight);


	/** Access image data buffer, allow modifications.
    *   \deprecated for naming consistence purpose, use GetBufferAddress() instead.
	*	\return	Pointer to the image data, values ranging from 0 to 255.
	*/
	K_DEPRECATED_2014 unsigned char* GetDataBuffer();

	/** Access image data buffer, allow modifications.
	*	\return	Pointer to the image data, values ranging from 0 to 255.
	*/
	unsigned char* GetBufferAddress();

    /** Convert the image data format to another format.
	*	\param	pNewFormat	The new format to convert the image to.
	*	\return	Return true if the convert was successful.
	*/
	bool ConvertFormat(FBImageFormat pNewFormat);

	/** Convert the image size.
	*	\param	pWidth	New width of the image.
	*	\param	pHeight	New height of the image.
	*	\return	Return true if the convert was successful.
	*/
	bool ConvertSize(int pWidth, int pHeight);

	/** Flip the image vertically.
	*/
	void VerticalFlip();

	/** Write image data to a TIF file on disk.
	*	\param	pFileName	Full TIF file path name of the file to write.
	*	\param	pComments	Comments appended to the TIF file.
	*	\param	pCompressed	If true, the image data in the file will be compressed.
	*	\return	Return true if the image was successfully written on disk.
	*/
	bool WriteToTif(const char* pFileName, const char* pComments, bool pCompressed);

	/** Query TIF file about its compressed status.
	*	\param	pFileName	Full TIF file path name of the file to query.
	*	\return Return true if the TIF file image data is compressed.
	*/
	bool IsCompressedTif(const char* pFileName);

	FBPropertyInt						Width;				//!< <b>Read Write Property:</b> Width of the image in pixels.
	FBPropertyInt						Height;				//!< <b>Read Write Property:</b> Height of the image in pixels.
	FBPropertyInt						Depth;				//!< <b>Read Write Property:</b> Color depth of the image.
	FBPropertyImageFormat				Format;				//!< <b>Read Write Property:</b> Image data format.
	FBPropertyImageType					Type;				//!< <b>Read Only Property:</b> Image type, refering to either frame or field.
	FBPropertyImageInterleaveType		InterleaveType;		//!< <b>Read Only Property:</b> Image interleave type. Only meaningful if image type is field.
	FBPropertyImageInterpolationType	InterpolationType;	//!< <b>Read Only Property:</b> Image interpolation type.
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FBSDKUseNamespace
	}
#endif

#endif /* this must be the last line of this file */
