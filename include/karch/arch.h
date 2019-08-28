/*!  \file arch.h
 */

#ifndef KARCH_ARCH_H
#define KARCH_ARCH_H

/**************************************************************************************

 Copyright (C) 2001 - 2009 Autodesk, Inc. and/or its licensors.
 All Rights Reserved.

 The coded instructions, statements, computer programs, and/or related material 
 (collectively the "Data") in these files contain unpublished information 
 proprietary to Autodesk, Inc. and/or its licensors, which is protected by 
 Canada and United States of America federal copyright law and by international 
 treaties. 
 
 The Data may not be disclosed or distributed to third parties, in whole or in
 part, without the prior written consent of Autodesk, Inc. ("Autodesk").

 THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
 ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO
 WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR ARISING
 BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES OF TITLE, 
 NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR USE. 
 WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT WARRANT THAT THE OPERATION
 OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE. 
 
 IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS
 OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR EXPENSES
 OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE DAMAGES OR OTHER
 SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS OF PROFITS, REVENUE
 OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR DAMAGES OF ANY KIND),
 HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF LIABILITY, WHETHER DERIVED
 FROM CONTRACT, TORT (INCLUDING, BUT NOT LIMITED TO, NEGLIGENCE), OR OTHERWISE,
 ARISING OUT OF OR RELATING TO THE DATA OR ITS USE OR ANY OTHER PERFORMANCE,
 WHETHER OR NOT AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS
 OR DAMAGE. 

**************************************************************************************/

/*
 *	Intel IA32 Architecture
 */
#define KARCH_ARCH_X86		600

/*
 *	AMD x64 Architecture
 */
#define KARCH_ARCH_AMD64_GENERIC	800

/*
 *	Intel IA64 Architecture
 */
#define KARCH_ARCH_ITANIUM			1000

#if defined(__linux__) || defined(__CYGWIN__) //////////////////////////////////////////////// LINUX and CYGWIN
	#define KARCH_DEV_GNUC			__GNUC__
	#define KARCH_ENV_UNIX			1
	#define KARCH_ENV_POSIX			1

	#if defined(__linux__) 
		#define KARCH_ENV_LINUX			1
	#elif defined(__CYGWIN__)
		#define KARCH_ENV_CYGWIN		1
	#endif

	#if defined(__GNUC__)
		#define KARCH_DEV_GNUC	__GNUC__

		#if (__GNUC__ < 4)
			#error "Compiler is too old !!!"
		#endif

		#define GCC_VERSION		(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

		// CPU Determination.
		#if defined(__ia64__)
			#define KARCH_CPU_IA64		KARCH_ARCH_ITANIUM
		#elif defined(__x86_64)
			#define KARCH_CPU_AMD64 	KARCH_ARCH_AMD64_GENERIC
		#elif defined(__i386__)
			#define KARCH_CPU_IA32	 	KARCH_ARCH_X86
		#else
			#error "Architecture not supported"
		#endif

		// ARCH Determination.
		#if defined(KARCH_CPU_IA64)
			#define KARCH_ARCH_IA64			KARCH_CPU_IA64
			#define KARCH_ARCH_64			1
		#elif defined(KARCH_CPU_AMD64)
			#define KARCH_ARCH_AMD64		KARCH_CPU_AMD64
			#define KARCH_ARCH_64			1
		#elif defined(KARCH_CPU_IA32)
			#define KARCH_ARCH_IA32			KARCH_CPU_IA32
		#endif
	#else
		#error "Compiler not supported"
	#endif
#elif defined(_XBOX)
	#define KARCH_ENV_WIN				1
	#define KARCH_ENV_WIN32				_WIN32
	#define KARCH_ENV_XBOX				_XBOX
	#define KARCH_DEV_MSC				_MSC_VER
	#define KARCH_ARCH_IA32				_M_IX86	
	#define KARCH_CPU_IA32				KARCH_ARCH_X86	

#elif defined(_WIN32) || defined(_WIN64) //////////////////////////////////////////////// WIN32/WIN64
	#define KARCH_ENV_WIN				1
	#define KARCH_ENV_WIN32				_WIN32
	#if defined(_WINNT)
		#define KARCH_ENV_WINNT			_WINNT
	#endif
	#if !defined(_WIN32_WINNT)
		#define _WIN32_WINNT	0x0502		// Latest change is for SetDllDirectory()
    #endif
    #if !defined(WINVER)
	    #define WINVER			0x0502
    #endif

	#ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
		#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
	#endif
	#ifndef _CRT_NONSTDC_NO_WARNINGS
		#define _CRT_NONSTDC_NO_WARNINGS 1
	#endif
	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS 1
	#endif
	#ifndef _CRT_SECURE_NO_DEPRECATE
		#define _CRT_SECURE_NO_DEPRECATE 1
	#endif

	// Use a newer version of comctl32.dll tooltips for Sketchbook
	#if defined _M_IX86
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif defined _M_IA64
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif defined _M_X64
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#else
		#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#endif

	#if defined(__MINGW32__)
		#define KARCH_ENV_MING32	__MINGW32__
	#endif
	#if defined(__ICL)
		#define KARCH_DEV_INTEL		__ICL
	#endif
	#if defined(_MSC_VER)
		#define KARCH_DEV_MSC		_MSC_VER
	#elif defined(__GNUC__)
		#define KARCH_DEV_GNUC			__GNUC__
		// CPU Determination.
		#if defined(__ia64__)
			#define KARCH_CPU_IA64		KARCH_ARCH_ITANIUM
		#elif defined(__x86_64)
			#define KARCH_CPU_AMD64 	KARCH_ARCH_AMD64_GENERIC
		#elif !defined(__i386__)
			#define KARCH_CPU_IA32	 	KARCH_ARCH_X86
		#else
			#error "Architecture not supported"
		#endif
	#else
		#error "Compiler not supported"
	#endif
	#if defined(_M_IX86)
		#define KARCH_ARCH_IA32			_M_IX86
		#define KARCH_CPU_IA32			KARCH_ARCH_X86
	#elif defined(_M_X64)
		#define KARCH_ARCH_X64			_M_X64
		#define KARCH_CPU_X64			KARCH_ARCH_AMD64
		#define KARCH_ENV_WIN64			_WIN64
		#define KARCH_ARCH_64			1
	#elif defined(_M_IA64)
		#define KARCH_ARCH_IA64			_M_IA64
		#define KARCH_CPU_IA64			KARCH_ARCH_ITANIUM
		#define KARCH_ENV_WIN64			_WIN64
		#define KARCH_ARCH_64           1
	#else
		#error "Architecture not supported"
	#endif

#elif defined(__MACH__)

	#if defined(__i386__)
		#define KARCH_CPU_IA32		KARCH_ARCH_X86
	 	#define KARCH_ARCH_IA32		KARCH_CPU_IA32
	#elif defined(__x86_64__)
	 	#define KARCH_ARCH_X64		_M_X64
		#define KARCH_ARCH_64		1
	#elif defined(__arm__)
		#define KARCH_ARCH_ARM
		#define KARCH_CPU_ARM
		#define K_REQUIRE_DATA_ALIGNMENT
	#else
		#error "Architecture not supported"
	#endif
	
    #define KARCH_DEV_MACOSX
    #define KARCH_ENV_MACOSX
    #define KARCH_DEV_GNUC			__GNUC__
	#define KARCH_ENV_UNIX			1
	#define KARCH_ENV_POSIX			1

#else	//////////////////////////////////////////////// GENERIC
	#error "Environment not supported"
#endif

#endif /* KARCH_ARCH_H */
