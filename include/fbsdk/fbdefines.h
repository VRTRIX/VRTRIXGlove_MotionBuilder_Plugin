#ifndef __FBDEFINES_H__
#define __FBDEFINES_H__
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

/** \file fbdefines.h
*   The purpose of this file is to hold all of the SDK general-purpose
*   preprocessor definitions.
*/

#include <kaydaradef.h>

#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
    #define FBSDK_DLL K_DLLIMPORT
#endif

// Global includes
#include <fbsdk/fbtypes.h>

#ifdef FBSDKUseNamespace
    namespace FBSDKNamespace {
#endif

/** Class initialization.
*   This should be placed as the first line in the constructor of a class
*   derived from FBComponent.
*/
#define FBClassInit

/** Class implementation.
*   This should be placed in the source code file for a class that derives
*   from FBComponent.
*   It is absolutely necessary in order to identify the class type.
*/
#define FBClassImplementation( Name )						\
    Name::~Name()				{ }                         \
    const char* Name::ClassName(){ return #Name; }			\
    int Name::GetTypeId()		{ return TypeInfo; }        \
    bool Name::Is( int pTypeId ){ return (pTypeId==TypeInfo) ? true : ParentClass::Is( pTypeId ); }  \
	void Name::FBDelete()		{ ParentClass::FBDelete(); }									\
    int Name::TypeInfo=FBPlug::mGlobalTypeInfo++;

/** Class declaration.
*   Overloads the necessary functions when a class inherits from
*   FBComponent (or its derivatives).
*   \param Name     Name of class to declare.
*   \param Parent   Parent class to associate with \e Name.
*/
#define FBClassDeclare( Name,Parent )   \
public:                                       \
    typedef Parent ParentClass;               \
    virtual const char *ClassName() override ;\
    static int TypeInfo;                      \
    virtual bool Is( int pTypeId )  override ;\
    virtual void FBDelete()         override ;\
    virtual int GetTypeId()         override ;\
    virtual ~Name();                          \
/** Return to the default scope (private) */\
private:                            

#ifdef FBSDKUseNamespace
    }
#endif

#endif
