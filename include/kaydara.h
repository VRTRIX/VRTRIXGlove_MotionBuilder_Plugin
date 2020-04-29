#ifndef _KAYDARA_H
#define _KAYDARA_H
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

// *** if you update this version, make sure to update the other version value in src/motionbuilder/motionbuilder/resource.h
#define K_KERNEL_VERSION	18000 
// ***

#define K_NO_PROJECTSETTINGS

/* Product definitions using the Kernel */
#if defined(FB_KERNEL)
	#if defined(K_QUICKTIME_PLUGIN)
		#define K_NO_FILTER
		#define	K_NO_PHYSICS
	#endif

#ifndef FB_KERNEL_WITH_UI
	#define K_CONFIG_MEMORY
	#define	K_NO_MANIPULATOR		
	#define	K_NO_UI
	#define	K_DISABLE_UI
	#define K_NO_HUD
#endif	

    #define	K_NO_RENDERER		
	#define K_NO_VIEWCUBE
	#define K_NO_STEERINGWHEEL
	#define	K_NO_ASSETMNG
	#define	K_NO_DECK
	#define	K_NO_FOLDER
	#define	K_NO_IMAGEOPERATOR
	#define	K_NO_NOTE
	#define	K_NO_OPTICAL
	#define	K_NO_PYTHON
	#define	K_NO_UNDO
	#define K_NO_CONSTRUCTION_HISTORY
	#define	K_NO_CIP
	#define	K_NO_STEREO
	#define K_NO_CGFX_SHADER
	#define K_NO_ONECLICK
//	#define K_NO_STATIC_FONTS	// OpenGL fonts
// Others not used
//		#define	K_NO_ACTOR
//      #define	K_NO_CHARACTER
//	    #define	K_NO_POSE
#endif

#if (_MSC_VER >= 1400) // The Visual C++ 2005 compiler version is 1400
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
#endif

// Memory extra debugging information
// Comment out the next line if a redefinition of the new operator is use.
#define MEMORY_DEBUG

// Profiling for the application.
// Comment this to remove all profiling code.
#define KPROFILING_CODE_ENABLE

#if defined(_DEBUG) && !defined(NDEBUG) && !defined(__CUDACC__)
	#if defined(_MSC_VER) && !defined(_MFC_VER)
		#ifdef MEMORY_DEBUG
            #undef __cdecl
			#define MEMORY_DEBUG_ACTIVE 1
			#define _CRTDBG_MAP_ALLOC 1
			#include <stdio.h>
			#include <string.h>
			#include <stdlib.h>
			#include <crtdbg.h>
			#include <malloc.h>
            #include <new>
            #include <xdebug>
            #include <xlocale>
            #include <xiosbase>
            #include <xlocnum>
            #include <xlocmon>
            #include <xtree>

			#define KaydaraNew new( _NORMAL_BLOCK, __FILE__, __LINE__)
			#ifndef new
				#define new KaydaraNew
			#endif
		#else
			#include <malloc.h>
		#endif
	#endif
#endif	

#ifndef FB_KERNEL
	#if !defined(K_ENABLE_STREAM_FCURVE)
		#define K_ENABLE_STREAM_FCURVE
	#endif
#endif

#include <karch/arch.h>
#include <karch/types.h>

#ifndef K_NO_QUICKTIME
	#if defined(KARCH_ENV_LINUX) || defined(KARCH_ENV_CYGWIN) || defined(KARCH_ENV_MING32) || (defined(KARCH_ENV_MACOSX) && defined(KARCH_ARCH_X64))
		#define K_NO_QUICKTIME	// No QuickTime implementions for those platforms
	#endif
#endif

#ifndef K_NO_ADVANCEDCONSTRAINTS
	#if defined(KARCH_ENV_CYGWIN) || defined(KARCH_ENV_MING32)
		#define K_NO_ADVANCEDCONSTRAINTS	// No advance constraints
	#endif
#endif

#ifndef K_NO_PHYSICS
	#if defined(KARCH_ENV_CYGWIN) || defined(KARCH_ENV_MING32)
		#define	K_NO_PHYSICS
	#endif
#endif

#ifndef NULL
	#if defined __GNUG__
		#define NULL (__null)
	#else	
    	#ifdef __cplusplus
    		#define NULL    0
    	#else
    		#define NULL    ((void *)0)
    	#endif
    #endif
#endif

#if !defined( _MAX_PATH ) && defined( KARCH_ENV_UNIX )
	#define _MAX_PATH 1024
#endif

#define K_MAX_TEXT_LENGTH 1020 // Max text length, to be used when declaring fixed width char ptrs directly

#define K_FORWARD( ClassName ) class ClassName; typedef ClassName *H##ClassName
#define K_FORWARD_HI( ClassName ) class ClassName; typedef ClassName *H##ClassName; typedef H##ClassName HI##ClassName

#define K_SAFE_FREE_PTR( p )            if( p ){ free( p );     (p) = NULL; }
#define K_SAFE_DELETE_PTR( p )			if( p ){ delete (p);    (p) = NULL; }
#define K_SAFE_DELETE_ARRAY_PTR( a )	if( a ){ delete [] (a); (a) = NULL; }

#define K_SAFE_DESTROY_OBJECT( p )		{ if( p ){ (p)->Destroy(); (p) = NULL; } }


#ifdef KARCH_ENV_WIN
	//#define snprintf _snprintf // for stdio.h platform compatibility
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN  // Defined to speed up compilation
	#endif
#else
	#include <ctype.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdarg.h>
	#include <assert.h>
	#include <strings.h>
#endif

#if defined(KARCH_DEV_MSC)
	#if (_MSC_VER >= 1400) // The Visual C++ 2005 compiler version is 1400
		//RR: macros defined for the conformant ISO C++ since now the following functions
		// are deprecated

		#ifndef stricmp
			#define stricmp		_stricmp
		#endif
		#ifndef strnicmp
			#define strnicmp	_strnicmp
		#endif
		#ifndef itoa
			#define itoa		_itoa
		#endif
		#ifndef getcwd
			#define getcwd		_getcwd
		#endif
		#ifndef getpid
			#define getpid		_getpid
		#endif
		#ifndef fileno
			#define fileno		_fileno
		#endif
		#ifndef fdopen
			#define fdopen		_fdopen
		#endif
	#endif
#else
	#define _MSC_EMULATOR

	#if (GCC_VERSION <= 40700) || !defined(__GXX_EXPERIMENTAL_CXX0X__)	// override is supported in GCC 4.7 and higher
		#define override		//	Indicates that a method must be an override of a base-class version
	#endif

	#define sealed			//	Prevents classes from being used as base classes
	#define abstract	=0	//	Indicates functions or classes are abstract 

	#if !defined(_TRUNCATE)
		#define _TRUNCATE ((size_t)-1)
	#endif
	inline int strcpy_s( char* dst,size_t bufsize,const char* src ) 
	{
		strcpy( dst,src );
		return 0;
	}
	template <size_t bufsize> int strcpy_s( char (&dst)[bufsize], const char *src )
	{
		return strcpy_s( dst,bufsize,src );
	}

	inline int strncpy_s( char* dst,size_t bufsize,const char* src,size_t count )
	{
		strncpy( dst,src,count );
		return 0;
	}
	template <size_t bufsize> int strncpy_s( char (&dst)[bufsize], const char *src, size_t count )
	{
		return strncpy_s( dst,bufsize,src,count );
	}

	inline int vsprintf_s( char *buffer, size_t bufsize, const char *format, va_list args )
	{
		return vsprintf( buffer,format, args ); 
	}
	template <size_t bufsize> int vsprintf_s( char (&buffer)[bufsize], const char *format, va_list args )
	{
		return vsprintf_s( buffer,bufsize,format, args ); 
	}

	inline int sprintf_s( char *buffer, size_t bufsize, const char *format, ... )
	{
		va_list	Arguments;
		va_start( Arguments, format);     /* Initialize variable arguments. */
		int result = vsprintf_s( buffer,bufsize,format, Arguments ); 
		va_end( Arguments );			/* Reset variable arguments.      */
		return result;
	}
	template <size_t bufsize> int sprintf_s( char (&buffer)[bufsize], const char *format, ... )
	{
		va_list	Arguments;
		va_start( Arguments, format);     /* Initialize variable arguments. */
		int result = vsprintf_s( buffer,bufsize,format, Arguments ); 
		va_end( Arguments );			/* Reset variable arguments.      */
		return result;
	}

	inline int strcat_s( char *dst, size_t bufsize, const char *src )
	{
		strcat( dst,src );
		return 0;
	}
	template <size_t bufsize> int strcat_s( char (&dst)[bufsize], const char *src )
	{
		return strcat_s( dst,bufsize,src );
	}

	#ifndef strtok_s
		#define strtok_s( token,sep,context )	strtok( token,sep )
	#endif

	#ifndef strncat_s
		#define strncat_s( dst,bufsize,src,len ) strncat( dst,src,len )
	#endif

	#ifndef localtime_s
		#define localtime_s( _Tm,_Time ) _Tm = localtime( _Time )
	#endif

	#ifndef _stricmp
		#define _stricmp	strcasecmp
	#endif
	#ifndef strcmpi
		#define strcmpi strcasecmp
	#endif
	#ifndef _strcmpi
		#define _strcmpi strcasecmp
	#endif
	#ifndef stricmp
		#define stricmp strcasecmp
	#endif
	#ifndef strncmpi
		#define strncmpi strncasecmp
	#endif
	#ifndef strnicmp
		#define strnicmp strncasecmp
	#endif

	#ifndef _atoi64
		#define _atoi64( str ) strtoll( str,NULL,10 )
	#endif

	#ifndef _isnan
		#define _isnan( x ) isnan( x )
	#endif

	inline char* _itoa(int pValue, char* pString, int pRadix)
	{
		assert(pRadix==10);
		if (pString) sprintf(pString,"%d", pValue);
		return pString;
	}

	#ifndef itoa
		#define itoa		_itoa
	#endif
#endif

#if defined(KARCH_ENV_LINUX)
	#include <malloc.h>
#endif

#if defined(KARCH_ENV_MACOSX)
	#include <stdlib.h>
#endif

// Compiler specific
#if defined(KARCH_DEV_MSC) && !defined(KARCH_DEV_INTEL)
	#pragma warning(disable : 4097)	// warning C4097: typedef-name 'ClassType' used as synonym for class-name 'KTextTag'
	#pragma warning(disable : 4100)	// warning C4100: '?' : unreferenced formal parameter
	#pragma warning(disable : 4201)	// nonstandard extension used : nameless struct/union (Level 4) portability  
	#pragma warning(disable : 4244)	// conversion from 'const double' to 'float', possible loss of data 
	#pragma warning(disable : 4481)	// warning C4481: nonstandard extension used: override specifier 'override'
	#pragma warning(disable : 4514)	// unreferenced inline function has been removed (Level 4) optimizer  
	#pragma warning(disable : 4660)	// template-class specialization 'identifier' is already instantiated (Level 2) compiler
	#pragma warning(disable : 4710)	// function (X) not expanded  ??? may be good to know
	#pragma warning(disable : 4711)	// function (X) selected for automatic inline expansion
	#pragma warning(disable : 4725)	// instruction may be inaccurate on some Pentiums
	#pragma warning(disable : 4251) // needs to have dll-interface to be used by clients of class

	#pragma warning(error : 4002)	// too many actual parameters for macro 'identifier'
	#pragma warning(error : 4130)	// warning C4130: '==' : logical operation on address of string constant
	#pragma warning(error : 4238)	// warning C4238: nonstandard extension used : class rvalue used as lvalue
	#pragma warning(error : 4265)	// warning C4265: 'class': class has virtual functions, but destructor is not virtual
	#pragma warning(error : 4289)	// warning C4289: nonstandard extension used : 'var' : loop control variable declared in the for-loop is used outside the for-loop scope
	#pragma warning(error : 4311)	// warning C4311: 'type cast' : pointer truncation from 'x *' to 'y'
	#pragma warning(error : 4373)	// warning C4373: '%$S': virtual function overrides '%$pS', previous versions of the compiler did not override when parameters only differed by const/volatile qualifiers
	#pragma warning(error : 4431)	// warning C4431: missing type specifier - int assumed. Note: C no longer supports default-int
	#pragma warning(error : 4510)	// warning C4510: 'class' : default constructor could not be generated
	#pragma warning(error : 4551)	// warning C4551: function call missing argument list
	#pragma warning(error : 4553)	// warning C4553: '==' : operator has no effect; did you intend '='?
	#pragma warning(error : 4700)	// warning C4700: (level 1 and 4) local variable 'name' used without having been initialized
	#pragma warning(error : 4701)	// warning C4700: (level 4) local variable 'name' may be used without having been initialized
	#pragma warning(error : 4407)	// warning C4407: cast between different pointer to member representations, compiler may generate incorrect code
	#pragma warning(error : 4946)	// warning C4946: reinterpret_cast used between related classes: 'class1' and 'class2'
	#pragma warning(error : 4996)	// warning C4996: 'function': was declared deprecated
#endif

#define K_LOCAL_CLASS

// Deprecated macro, to remind people to stop using certain functions / attributes. 
// Retirement policy, instead of directly remove certain functions / attributes, we
// should declare them to be deprecated first, and then safely removed them at next 
// major release. We add major release version number suffix to the macro to indicate 
// the timing.

#if defined(KARCH_DEV_GNUC) // GNU compiler
    #define K_DEPRECATED_2014 __attribute__((deprecated))
    #define K_DEPRECATED_2015 __attribute__((deprecated))
	#define K_DEPRECATED_2016 __attribute__((deprecated))
	#define K_DEPRECATED_2017 __attribute__((deprecated))
	#define K_DEPRECATED_2018 __attribute__((deprecated))
#elif defined(KARCH_DEV_MSC) || defined(KARCH_DEV_INTEL) // Microsoft or Intel compiler
    #define K_DEPRECATED_2014 __declspec(deprecated)
    #define K_DEPRECATED_2015 __declspec(deprecated)
	#define K_DEPRECATED_2016 __declspec(deprecated)
	#define K_DEPRECATED_2017 __declspec(deprecated)
	#define K_DEPRECATED_2018 __declspec(deprecated)
#else // Unknown compiler
    #define K_DEPRECATED_2014
    #define K_DEPRECATED_2015
	#define K_DEPRECATED_2016
	#define K_DEPRECATED_2017
	#define K_DEPRECATED_2018
#endif

#endif // _KAYDARA_H_




