#ifndef __FBTEXTURE_H__
#define __FBTEXTURE_H__
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

/**	\file fbhud.h
*	HUD (Head Up Display)
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbcore.h>
#include <fbsdk/fbproperties.h>
#include <fbsdk/fbvideo.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif


////////////////////////////////////////////////////////////////////////////////////
// FBTexture
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBTexture );

/**    Texture Use Type.
*    How the texture is used.
*/

enum FBTextureUseType    {
    kFBTextureUseAll,					//!< All textures.
    kFBTextureUseColor,					//!< standard color type, work with material.
    kFBTextureUseShadowMap,				//!< Shadow Map, work with model
    kFBTextureUseLightMap,				//!< Light Map, work with model
    kFBTextureUseSphericalReflexionMap, //!< Spherical Reflexion Map, work with model
    kFBTextureUseSphereReflexionMap,    //!< Sphere Reflexion Map, work with model
    kFBTextureUseBumpNormalMap		    //!< Bump Normal Map, work with model
};

/**    Texture mapping modes.
*    How the texture is mapped.
*/
enum FBTextureMapping    {
    kFBTextureNoMapping,			//!< No mapping.
    kFBTextureMappingUV,			//!< UV mapping.
    kFBTextureMappingXY,			//!< XY mapping.
    kFBTextureMappingYZ,			//!< YZ mapping.
    kFBTextureMappingXZ,			//!< XZ mapping
    kFBTextureMappingSpherical,     //!< Spherical mapping.
    kFBTextureMappingCylindrical,   //!< Cylindrical mapping.
    kFBTextureMappingEnvironment,	//!< Environment mapping.
    kFBTextureMappingProjection     //!< Projection mapping.
};

/**    Texture blend modes.
*    How the texture is blended with another.
*/
enum FBTextureBlendMode    { 
    kFBTextureBlendTranslucent,     //!< Layer transparency.
    kFBTextureBlendAdditive,        //!< Layer addition.
    kFBTextureBlendModulate,        //!< Layer multiplication.
    kFBTextureBlendModulate2,       //!< Layer multiplication + brightness.
};

FB_DEFINE_ENUM( FBSDK_DLL, TextureUseType    );
FB_DEFINE_ENUM( FBSDK_DLL, TextureMapping    );
FB_DEFINE_ENUM( FBSDK_DLL, TextureBlendMode    );

//! Texture class.
// This class is used to encapsulate an underlying media that is used to texture a model.
//
FB_FORWARD(FBRenderOptions);

FB_DEFINE_COMPONENT( FBSDK_DLL, Texture );

class FBSDK_DLL FBTexture : public FBBox {
    __FBClassDeclare( FBTexture,FBBox );
public:
    /**    Constructor.
    *    \param    pName        Name of the texture media.  If pName is a valid path, FBTexture will create a FBVideo object which is used in the Video property; else just a ordinary name.
    *    \param    pObject        For internal use only.
    */
    FBTexture(const char* pName, HIObject pObject=NULL);
    virtual void FBDelete();

    /** Clone the texture.
    *    This will duplicated the current texture. 
    *    \return Newly created texture.
    */
    FBTexture* Clone();

    FBPropertyInt               Width;           //!< <b>Read Only Property:</b> Width of texture.
    FBPropertyInt               Height;          //!< <b>Read Only Property:</b> Height of texture.
    FBPropertyTextureUseType    UseType;         //!< <b>Read Write Property:</b> Texture Use Type.
    FBPropertyTextureMapping    Mapping;         //!< <b>Read Write Property:</b> Texture mapping.
    FBPropertyTextureBlendMode  BlendMode;       //!< <b>Read Write Property:</b> Texture blend mode.
    FBPropertyAnimatableVector3d    Translation; //!< <b>Read Write Property:</b> Translation coordinates.
    FBPropertyAnimatableVector3d    Rotation;    //!< <b>Read Write Property:</b> Rotation coordinates.
    FBPropertyAnimatableVector3d    Scaling;     //!< <b>Read Write Property:</b> Scaling coordinates.
    FBPropertyAnimatableDouble      Alpha;       //!< <b>Read Write Property:</b> Texture alpha value.
    FBPropertyBool              SwapUV;          //!< <b>Read Write Property:</b> Swap UV coordinates?
    FBPropertyInt               CroppingX[2];    //!< <b>Read Write Property:</b> X cropping.
    FBPropertyInt               CroppingY[2];    //!< <b>Read Write Property:</b> Y cropping.
    FBPropertyVideo             Video;           //!< <b>Read Write Property:</b> Media used for texturing.
    FBPropertyBool              TakeBased;       //!< <b>Read Write Property:</b> A video is linked to a take, changing the take will change the connected video.
    FBPropertyInt	            TextureOGLId;	 //!< <b>Read Only:</b> OpenGL texture buffer object Id. 

    void    OGLInit(FBRenderOptions* pRenderOptions = NULL);
    unsigned int GetTextureObject();
    double* GetMatrix();
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListTexture
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: Texture

class FBSDK_DLL FBPropertyListTexture : public FBPropertyListComponent
{
public:
    FBPropertyListTexture();
    /** Add a texture to the property list.
    *   @param      pItem   Texture to add to the list.
    *   @return             The index of the element in the list. Returns -1 on failure.
    *   @warning            Adding a new element will invalidate any existing iterators
    *                       as the new items may not be added at the end of the list.
    */
    virtual int Add( FBTexture* pItem );
    /** Get the texture at a specific index.
    *   @param  pIndex  Index of texture to get.
    *   @return         The texture at the specified index. Returns a NULL pointer on failure.
    */
    FBTexture* operator[](int pIndex);

private:
    inline virtual int Add    ( FBComponent* pItem ) { return Add((FBTexture*)pItem); }
};

////////////////////////////////////////////////////////////////////////////////////
// FBLayeredTexture
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBLayeredTexture );

/** LayeredTexture class.
* This class is used to encapsulate list of textures. 
* User could subclass this class to support customized blending & compostion modes.
* See $(INSTALLDIR)/OpenRealitySDK/Samples/miscellaneous/texture_template/ for example.
*/
class FBSDK_DLL FBLayeredTexture : public FBTexture {
    __FBClassDeclare( FBLayeredTexture,FBTexture );
public:
    /**    Constructor.
    *    \param    pName        Name of texture media. Can be a NULL pointer. If set, this will create a FBVideo object used as the Video property.
    *    \param    pObject      For internal use only.
    */
    FBLayeredTexture(const char* pName, HIObject pObject=NULL);
    virtual void FBDelete();

    /** Clone the current texture.
    *    Duplicates the current texture. 
    *    \return Newly created texture.
    */
    FBLayeredTexture* Clone();

    /** Virtual function to be override if custom layer blend method needed.
    *   Upon callback occurs, MotionBuilder already setup GL Render-To-Texture frame buffer target. 
    *   plugin code is responsible to fill up RTT buffer accordingly. 
    *   \param  pTime                   time in action time referential 
    *   \param  pTimeInCurrentTimeRef   time in current time ref
    *   \param  pWidth                  width of the RTT frame buffer target
    *   \param  pHeight                 height of the RTT frame buffer target
    *   \note   If not override in subclass, the internal layer composition logic will be used. 
    */
    virtual void TextureLayerComposition(FBTime pTime,FBTime pTimeInCurrentTimeRef, int pWidth, int pHeight);

    /** Set layer config dirty to trigger new composition */
    void SetLayerConfigDirty();

    FBPropertyAnimatableColorAndAlpha   BackgroundColor;    //!< <b>Read/Write Property:</b> Animatable Background color which is used to clear color buffer before composition. 
    FBPropertyListTexture               Layers;             //!< <b>Read/Write Property:</b> Textures Layers. 
};

/** Custom Storeable Texture Class implementation. (only LayeredTexture is supported for now).
*/
#define FBStorableCustomTextureImplementation(ClassName, Type)\
    const char* ClassName::FbxGetObjectSubType(){ return #ClassName; }\
    HIObject RegisterStorable##ClassName##Create(HIObject /*pOwner*/, const char* pName, void* /*pData*/){\
    ClassName* Class = new ClassName(pName);\
    Class->mAllocated = true;\
    if( Class->FBCreate() ){\
    return Class->GetHIObject();\
    } else {\
    delete Class;\
    return NULL;}}\
    FBLibraryModule(ClassName##Storable){\
    FBString lGroup = "FbxStorable/";\
    lGroup += #Type;\
    FBRegisterObject(ClassName##R2, lGroup, #ClassName, "", RegisterStorable##ClassName##Create, true, NULL);\
    FBSetStoreableCustomTextureRegistered();}\


#ifdef FBSDKUseNamespace
}
#endif

#endif /* this must be the last line of this file */