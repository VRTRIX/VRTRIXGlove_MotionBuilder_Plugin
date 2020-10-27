#ifndef _FBSDK_OPENGL_H_
#define _FBSDK_OPENGL_H_
/**************************************************************************
Copyright (c) 1994 - 2008 Autodesk, Inc. and/or its licensors.
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
#if defined(KARCH_ENV_WIN32)
//	#include <windows.h> // must include before this include if needed
// Now redefining those if not already defined
	#ifndef WINGDIAPI
		#define CALLBACK		__stdcall
		#define WINAPI			__stdcall
		#define DECLSPEC_IMPORT	__declspec(dllimport)
		#define WINGDIAPI		DECLSPEC_IMPORT
		#define APIENTRY		WINAPI
	#endif
	#ifndef _WCHAR_T_DEFINED
		typedef unsigned short wchar_t;
		#define _WCHAR_T_DEFINED
	#endif
#else
	#ifndef CALLBACK
		#define CALLBACK
	#endif
#endif

#if defined(KARCH_ENV_MACOSX)
	#include <OpenGl/gl.h>
	#include <OpenGl/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#if defined(KARCH_ENV_WIN32) || defined(KARCH_ENV_WIN64)
	#ifndef GL_BGR
		#define GL_BGR									GL_BGR_EXT
	#endif
	#ifndef GL_BGRA
		#define GL_BGRA									GL_BGRA_EXT
	#endif

	#ifndef GL_EXT_abgr
		#define GL_ABGR_EXT							0x8000
		#define GL_EXT_abgr 1
	#endif
#endif

#if defined(KARCH_ENV_LINUX)
	#include <GL/glext.h>
#endif

#if defined(KARCH_ENV_MACOSX)
    #include <OpenGl/glext.h>
#endif

#ifndef GL_LIGHT_MODEL_COLOR_CONTROL
	#define GL_LIGHT_MODEL_COLOR_CONTROL 0x81F8
#endif

#ifndef GL_SEPARATE_SPECULAR_COLOR
	#define GL_SEPARATE_SPECULAR_COLOR  0x81FA
#endif

#ifndef GL_EXT_422_pixels
	#define GL_422_EXT 0x80cc
#endif

#ifndef GL_CLAMP_TO_EDGE
	#define GL_CLAMP_TO_EDGE 0x812F
#endif

#endif /* _FBSDK_OPENGL_H_ */