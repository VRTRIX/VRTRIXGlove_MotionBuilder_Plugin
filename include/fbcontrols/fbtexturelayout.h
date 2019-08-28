#ifndef __FBTEXTURELAYOUT_H__
#define __FBTEXTURELAYOUT_H__
/**************************************************************************
 Copyright (c) 1994 - 2012 Autodesk, Inc. and/or its licensors.
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

/**    \file fbtexturelayout.h
*    FBTexture layout file.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
    /** \def FBSDK_DLL
    *    Be sure that FBSDK_DLL is defined only once...
    */
    #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbtexture.h>

// UI includes
#include <fbcontrols/fbcontrols.h>

// Namespace declaration
#ifdef FBSDKUseNamespace
    namespace FBSDKNamespace {
#endif

/** Register a Texture layout class
*    \param    ClassName       Name of Texture layout class.
*    \param    UniqueNameStr   Unique name of class. Need to be same as return value of FbxGetObjectSubType()
*    \param    IconFilename    Filename of associated icon.
*/
#define FBRegisterTextureLayout( ClassName,UniqueNameStr, IconFilename ) \
    HIObject RegisterTextureLayout##ClassName( HIObject /*pOwner*/,const char * /*pName*/,void *pData) \
    {\
        ClassName *Class = new ClassName( (FBTexture*)FBGetFBObject((HIObject)pData) ); \
        Class->mAllocated = true; \
        if (Class->FBCreate()) { \
            return Class->GetHIObject(); \
        } else { \
            delete Class; \
            return NULL; \
        } \
    } \
    \
    FBLibraryModule( ClassName )    \
    {    \
        FBRegisterObject( ClassName,"UI_Associated_ClassName",UniqueNameStr,UniqueNameStr" Texture Layout",RegisterTextureLayout##ClassName, true, IconFilename );    \
    }

/**    Texture layout declaration.
*    \param    ClassName    Name of Texture layout class.
*    \param    Parent        Parent of Texture layout class. 
*/
#define FBTextureLayoutDeclare( ClassName,Parent ) \
    FBClassDeclare( ClassName,Parent ); \
  public: \
    ClassName(FBTexture* pTexture):Parent(pTexture) { FBClassInit; } \
  private:

/** Texture layout implementation.
*    \param    ThisComponent    Name of Texture layout class to implement.
*/
#define FBTextureLayoutImplementation( ThisComponent ) \
    FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBTexture
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBTextureLayout );


//! Custom Texture layout class.
class FBSDK_DLL FBTextureLayout : public FBLayout
{
    __FBClassDeclare( FBTextureLayout,FBLayout );

public:
    /**    Constructor.
    *    \param pTexture Texture to association with Texture layout.
    */
    FBTextureLayout( FBTexture* pTexture = NULL );

    FBPropertyTexture    Texture;        //!< <b>Property:</b> Texture.
};

#ifdef FBSDKUseNamespace
    }
#endif
#endif
