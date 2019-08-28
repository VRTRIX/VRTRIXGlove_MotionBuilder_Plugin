#ifndef _KAYDARA_LIB_H_
#define _KAYDARA_LIB_H_
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

#include <kaydara.h>
#include <kaydaradef.h>

enum kFBDllOperation { kFBDllLoad, kFBDllUnLoad };

#define FB_MANUAL_DLL_INIT(Name) \
	extern void EntryPoint##Name(kFBDllOperation STARTUP); \
	EntryPoint##Name(kFBDllLoad); \

#if defined(K_NODLL)
	#ifndef FB_KERNEL
		#define FB_DLL_INIT(DLLNAME,STARTUP)\
		int DummyEntryPoint##DLLNAME();\
		static int StatEntryPoint##DLLNAME = DummyEntryPoint##DLLNAME();\
		void EntryPoint##DLLNAME(kFBDllOperation STARTUP);\
		int DummyEntryPoint##DLLNAME()\
		{ \
			EntryPoint##DLLNAME(kFBDllLoad);\
			return 0; \
		} \
		void EntryPoint##DLLNAME(kFBDllOperation STARTUP)
	#else
		#define FB_DLL_INIT(DLLNAME,STARTUP)\
			void EntryPoint##DLLNAME(kFBDllOperation STARTUP)
	#endif
#else
	#if defined(KARCH_ENV_WIN32)
		#define FB_DLL_INIT(DLLNAME,STARTUP)\
			__declspec(dllexport) void EntryPoint##DLLNAME(kFBDllOperation STARTUP);\
				int/*BOOL*/ __stdcall/*WINAPI*/ DllMain(void*/*HINSTANCE*/ hinstDLL,unsigned long/*DWORD*/ fdwReason, void*/*LPVOID*/ lpvReserved )\
				{ \
					switch (fdwReason) \
					{ \
					case 1/*DLL_PROCESS_ATTACH*/: EntryPoint##DLLNAME(kFBDllLoad); break; \
					case 0/*DLL_PROCESS_DETACH*/: EntryPoint##DLLNAME(kFBDllUnLoad); break; \
					} \
					return 1/*TRUE*/; \
				}\
			void EntryPoint##DLLNAME(kFBDllOperation STARTUP)
	#elif defined (KARCH_DEV_GNUC)
		#define FB_DLL_INIT( DllName,Startup ) \
		void EntryPoint##DllName(kFBDllOperation Startup); \
		void __attribute__((constructor)) KdsoInit##DllName ( void ) \
			{ \
			EntryPoint##DllName(kFBDllLoad);\
			}\
		void __attribute__ ((destructor)) KdsoDone##DllName ( void ) \
			{ \
			EntryPoint##DllName(kFBDllUnLoad);\
			}\
		void EntryPoint##DllName(kFBDllOperation Startup)
	#else
		#define FB_DLL_INIT( DllName,Startup ) \
		void EntryPoint##DllName(kFBDllOperation Startup); \
		extern "C" void KdsoInit##DllName( void ) \
		{ \
			EntryPoint##DllName(kFBDllLoad);\
		}\
		extern "C" void KdsoDone##DllName( void ) \
		{ \
			EntryPoint##DllName(kFBDllUnLoad);\
		}\
        class Init##DllName { public: Init##DllName ()  {KdsoInit##DllName (); } ~Init##DllName ()  {KdsoDone##DllName (); } }; \
        static Init##DllName Flakel##DllName; \
		void EntryPoint##DllName(kFBDllOperation Startup)

	#endif
#endif

#define FB_EXT_INIT(libname)

#endif /* _KAYDARA_LIB_H_ */
