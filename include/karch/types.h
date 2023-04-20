/*!  \file
 */

#ifndef KARCH_TYPES_H
#define KARCH_TYPES_H

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

**************************************************************************/

#ifndef KARCH_ARCH_H
	#include <karch/arch.h>
#endif

#include <cstdint>

// Common independant definitions

typedef signed char			kByte;         /* signed 8-bit integer         */
typedef unsigned char		kUByte;        /* unsigned 8-bit integer       */
typedef signed char			kSChar;
typedef unsigned char		kUChar;
typedef unsigned int		kUInt;
typedef signed short		kShort;
typedef unsigned short		kUShort;

#define K_SCHAR_MIN			(-128)
#define K_SCHAR_MAX			(127)
#define K_UCHAR_MIN			(0)
#define K_UCHAR_MAX			(255)

#define K_INT8_MIN			(-128)
#define K_INT8_MAX			(127)
#define K_UINT8_MIN			(0)
#define K_UINT8_MAX			(255)

#define K_INT16_MIN			(-32768)
#define K_INT16_MAX			(32767)
#define K_UINT16_MIN		(0)
#define K_UINT16_MAX		(65535)

#define K_INT32_MIN			(0x80000000)
#define K_INT32_MAX			(0x7fffffff)
#define K_UINT32_MIN		(0)
#define K_UINT32_MAX		(0xffffffff)

#define KARCH_LITTLE_ENDIAN

#define K_CHAR(x)			char(x)
#define K_SCHAR(x)			kSChar(x)
#define K_UCHAR(x)			kUChar(x##L)

#ifndef _T
	#define __T(x)      x
	#define _T(x)       __T(x)
#endif

#define K_SHORT(x)			kShort(x)
#define K_USHORT(x)			kUShort(x##U)
#define K_SHORT_MIN			K_SHORT(-32768)
#define K_SHORT_MAX			K_SHORT(32767)
#define K_USHORT_MIN		K_USHORT(0)
#define K_USHORT_MAX		K_USHORT(65535)

#define K_INT(x)			(x)
#define K_UINT(x)			(x##U)
#define K_INT_MIN			K_INT(0x80000000)
#define K_INT_MAX			K_INT(0x7fffffff)
#define K_UINT_MIN			K_UINT(0)
#define K_UINT_MAX			K_UINT(0xffffffff)

#ifdef __LP64__
	typedef signed int			kLong;
	typedef unsigned int		kULong;
    #define zlufmt              "%0u"
    #define lufmt               "%u"
#else
	typedef signed long			kLong;
	typedef unsigned long		kULong;
    #define zlufmt              "%0lu"
    #define lufmt               "%lu"
#endif

#define K_LONG(x)			(x)
#define K_ULONG(x)			(x##U)
#define K_LONG_MIN			K_LONG(0x80000000)
#define K_LONG_MAX			K_LONG(0x7fffffff)
#define K_ULONG_MIN			K_ULONG(0)
#define K_ULONG_MAX			K_ULONG(0xffffffff)

typedef signed long long	kLongLong;
#define K_LONGLONG(x)		((kLongLong)(x##LL))
typedef unsigned long long	kULongLong;
#define K_ULONGLONG(x)		((kULongLong)(x##ULL))

#define K_LONGLONG_MIN		K_LONGLONG(0x8000000000000000)
#define K_LONGLONG_MAX		K_LONGLONG(0x7fffffffffffffff)
#define K_ULONGLONG_MIN		K_ULONGLONG(0)
#define K_ULONGLONG_MAX		K_ULONGLONG(0xffffffffffffffff)

typedef int8_t              kInt8;
typedef uint8_t             kUInt8;

typedef int16_t             kInt16;
typedef uint16_t            kUInt16;

typedef int32_t             kInt32;
typedef uint32_t            kUInt32;

typedef int64_t             kInt64;
typedef uint64_t            kUInt64;

// Atomic definitions
#ifdef KARCH_ARCH_64
	typedef int64_t			kAtomic;
#else
	typedef int32_t			kAtomic;
#endif

// Pointer definitions
typedef uintptr_t			kReference;
#define K_REFERENCE_MAX		UINTPTR_MAX

typedef kULongLong			KMicroTime;

#endif
