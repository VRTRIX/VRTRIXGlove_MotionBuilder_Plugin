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
		#ifndef KARCH_ENV_MING32
			typedef unsigned short wchar_t;
		#endif
		#define _WCHAR_T_DEFINED
	#endif
#else
	#ifdef __sgi
		#define glDeleteTextures	glDeleteTexturesEXT
		#define glGenTextures		glGenTexturesEXT
		#define glBindTexture		glBindTextureEXT
		#define glCopyTexImage2D	glCopyTexImage2DEXT
		#define glCopyTexSubImage2D glCopyTexSubImage2DEXT
		#define glTexSubImage2D		glTexSubImage2DEXT
		#define glIsTexture 		glIsTextureEXT
		#define glCopyTexImage2D	glCopyTexImage2DEXT
		#define GL_BGRA_EXT			GL_BGRA				// On SGI only this is not an extension				
		#define GL_BGR_EXT			GL_BGR				// On SGI only this is not an extension						
	#endif
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
	#if defined(KARCH_ENV_MING32)
		#include <GL/glext.h>
	#endif
	#ifdef GL_EXT_bgra
		#define GL_BGR									GL_BGR_EXT
		#define GL_BGRA									GL_BGRA_EXT
	#endif
	#define GL_POST_COLOR_MATRIX_COLOR_TABLE_EXT	0x80D2		// glEnable

	#ifndef GL_EXT_abgr
		#define GL_ABGR_EXT							0x8000
		#define GL_EXT_abgr 1
	#endif

	#ifndef GL_LIGHT_MODEL_COLOR_CONTROL_EXT
		#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT		0x81F8		// glLightModel OpenGL 1.2
	#endif

	#ifndef GL_SINGLE_COLOR_EXT
		#define GL_SINGLE_COLOR_EXT						0x81F9		// glLightModel OpenGL 1.2
	#endif
	
	#ifndef GL_SEPARATE_SPECULAR_COLOR_EXT
		#define GL_SEPARATE_SPECULAR_COLOR_EXT			0x81FA		// glLightModel OpenGL 1.2
	#endif

	#define	GL_DISPLAY_CGP							0x6001
	#define	GL_GLTARGET_CGP							0x6003
#endif

#if defined(KARCH_ENV_LINUX)
	#include <GL/glext.h>
	#define GL_POST_COLOR_MATRIX_COLOR_TABLE_EXT	GL_POST_COLOR_MATRIX_COLOR_TABLE
#endif

#if defined(KARCH_ENV_IRIX)
	#define GL_POST_COLOR_MATRIX_COLOR_TABLE_EXT    GL_POST_COLOR_MATRIX_COLOR_TABLE
#endif

#if defined(KARCH_ENV_MACOSX)
    #include <OpenGl/glext.h>
	#define GL_POST_COLOR_MATRIX_COLOR_TABLE_EXT	GL_POST_COLOR_MATRIX_COLOR_TABLE
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