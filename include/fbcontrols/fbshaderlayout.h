#ifndef __FBSHADERLAYOUT_H__
#define __FBSHADERLAYOUT_H__
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

/**	\file fbshaderlayout.h
*	FBShader layout file.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

// Core includes
#include <fbsdk/fbshader.h>

// UI includes
#include <fbcontrols/fbcontrols.h>

// Namespace declaration
#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

/** Register a Shader layout class
*	\param	ClassName		Name of Shader layout class.
*	\param	UniqueNameStr	Unique name of class.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterShaderLayout( ClassName,UniqueNameStr, IconFilename ) \
	HIObject RegisterShaderLayout##ClassName( HIObject /*pOwner*/,const char * /*pName*/,void *pData) \
	{\
		ClassName *Class = new ClassName( (FBShader*)FBGetFBComponent((HIObject)pData) ); \
		Class->mAllocated = true; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
	FBLibraryModule( ClassName )	\
	{	\
		FBRegisterObject( ClassName,"renderer/usershader/ui",UniqueNameStr,UniqueNameStr" Shader Layout",RegisterShaderLayout##ClassName, true, IconFilename );	\
	}

/**	Shader layout declaration.
*	\param	ClassName	Name of Shader layout class.
*	\param	Parent		Parent of Shader layout class. 
*/
#define FBShaderLayoutDeclare( ClassName,Parent ) \
	FBClassDeclare( ClassName,Parent ); \
  public: \
    ClassName(FBShader* pShader):Parent(pShader) { FBClassInit; } \
  private:

/** Shader layout implementation.
*	\param	ThisComponent	Name of Shader layout class to implement.
*/
#define FBShaderLayoutImplementation( ThisComponent ) \
	FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBShaderLayout - Layout for a shader.
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBShaderLayout		);
FB_DEFINE_COMPONENT( FBSDK_DLL, ShaderLayout	);
//! Shader layout class.
class FBSDK_DLL FBShaderLayout : public FBLayout 
{
	__FBClassDeclare( FBShaderLayout,FBLayout );

public:
	/**	Constructor.
	*	\param pShader Shader to association with Shader layout.
	*/
	FBShaderLayout( FBShader* pShader = NULL );

	FBPropertyShader Shader;					//!< Property : Shader
};

#ifdef FBSDKUseNamespace
	}
#endif
#endif
