#ifndef _KAYDARA_OPENGL_H_
#define _KAYDARA_OPENGL_H_
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
#if defined(_WIN32)
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

#include <GL/gl.h>
#include <GL/glu.h>

#if defined(_WIN32)
	#define GL_TEXTURE_MAX_ANISOTROPY_EXT			0x84FE
	#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT		0x84FF
#endif

#endif /* _KAYDARA_OPENGL_H_ */
