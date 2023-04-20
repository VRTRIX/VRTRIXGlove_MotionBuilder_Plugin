#ifndef __FBMATERIAL_H__
#define __FBMATERIAL_H__
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

/** \file fbmaterial.h
*    Base class for Material.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
    /** \def FBSDK_DLL
    *    Be sure that FBSDK_DLL is defined only once...
    */
    #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcore.h>
#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbtexture.h>

#ifdef FBSDKUseNamespace
    namespace FBSDKNamespace {
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBMaterial
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBMaterial );

//! Various Material texture channels' type.
enum FBMaterialTextureType {        
    kFBMaterialTextureEmissive,
    kFBMaterialTextureEmissiveFactor,
    kFBMaterialTextureAmbient,
    kFBMaterialTextureAmbientFactor,
    kFBMaterialTextureDiffuse,
    kFBMaterialTextureDiffuseFactor,
    kFBMaterialTextureSpecular,
    kFBMaterialTextureSpecularFactor,
    kFBMaterialTextureShiness,
    kFBMaterialTextureBump,
    kFBMaterialTextureNormalMap,
    kFBMaterialTextureTransparent,
    kFBMaterialTextureTransparentFactor,
    kFBMaterialTextureReflection,
    kFBMaterialTextureReflectionFactor,
    kFBMaterialTextureDisplacementColor
};

FB_DEFINE_COMPONENT( FBSDK_DLL, Material         );

//! Material class.
class FBSDK_DLL FBMaterial : public FBBox {
    __FBClassDeclare( FBMaterial,FBBox );
public:
    /**    Constructor.
    *    \param    pName        Name of material.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBMaterial(const char* pName, HIObject pObject=NULL);

    /** Clone the material.
    *    This will duplicated the current material. 
    *    \return Newly created material.
    */
    FBMaterial* Clone();

    FBPropertyAnimatableColor    Ambient;            //!< <b>Read Write Property:</b> Ambient color.
    FBPropertyAnimatableDouble   AmbientFactor;        //!< <b>Read Write Property:</b> Ambient Factor value.
    
    FBPropertyAnimatableColor    Emissive;            //!< <b>Read Write Property:</b> Emissive color.
    FBPropertyAnimatableDouble   EmissiveFactor;        //!< <b>Read Write Property:</b> Emissive Factor value.
    
    FBPropertyAnimatableColor    Diffuse;            //!< <b>Read Write Property:</b> Diffuse color.
    FBPropertyAnimatableDouble   DiffuseFactor;      //!< <b>Read Write Property:</b> Diffuse Factor value.
    
    FBPropertyAnimatableColor    TransparentColor;   //!< <b>Read Write Property:</b> Transparent color.
    FBPropertyAnimatableDouble   TransparencyFactor; //!< <b>Read Write Property:</b> Transparency Factor value.
    
    FBPropertyAnimatableColor    Bump;                //!< <b>Read Write Property:</b> Bump.
    FBPropertyAnimatableColor    NormalMap;            //!< <b>Read Write Property:</b> Normal Map.
    FBPropertyAnimatableDouble   BumpFactor;            //!< <b>Read Write Property:</b> Bump Factor value.

    FBPropertyAnimatableColor    Specular;            //!< <b>Read Write Property:</b> Specular color.
    FBPropertyAnimatableDouble   SpecularFactor;        //!< <b>Read Write Property:</b> Specular Factor value.
    FBPropertyAnimatableDouble   Shininess;            //!< <b>Read Write Property:</b> Shininess value.
    
    FBPropertyAnimatableColor    Reflection;            //!< <b>Read Write Property:</b> Reflection color.
    FBPropertyAnimatableDouble   ReflectionFactor;    //!< <b>Read Write Property:</b> Reflection Factor value.

    FBPropertyAnimatableColor    DisplacementColor;    //!< <b>Read Write Property:</b> Displacement color.
    FBPropertyAnimatableDouble   DisplacementFactor;    //!< <b>Read Write Property:</b> Displacement Factor value.

    /** Retrieve associated texture.
    *   @param  pType  MaterialTextureType to get connected texture from (default is Diffuse is not specified).
    */   
    FBTexture* GetTexture(FBMaterialTextureType pType = kFBMaterialTextureDiffuse);

    /** Set associated texture.
    *    @param pTexture        texture to be connected.
    *    @param pType        MaterialTextureType to set connected texture to.
    */
    void SetTexture(FBTexture* pTexture, FBMaterialTextureType pType = kFBMaterialTextureDiffuse);

    /** Setup OpenGL fixed pipeline material settings */
    void OGLInit();

    /** Return Material Name. Need to be same with FBMaterialLayout*/
    virtual const char* GetMaterialName() const;

    /** Return Material Desc Name. Need to be same with FBMaterialLayout*/
    virtual const char* GetMaterialDesc() const;

    /**    Store and Retrieve function that can be overloaded.
    *    \param    pFbxObject    FBX Object that is used to communicate I/O operations.
    *    \param    pStoreWhat    Which attributes are currently stored/retrieved.
    */
    virtual bool FbxStore(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat) override;
    virtual bool FbxRetrieve(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat) override;

    /** Returns the class type inherited by the class of an object, for example: 'Material'.
    *	\return The class type inherited by the class of an object.
    */
    virtual const char*    FbxGetObjectType() override;

    /** Returns the class sub type inherited by the class of an object, for example: 'Default', 'Custom Material', 'FBMaterial'.
    *	\return The class sub type inherited by the class of an object.
    */
    virtual const char*    FbxGetObjectSubType() override;

protected:
    /** Create user custom texture connect property for custom material derived from FBMaterial only.
    *	\param pName The name of the property.
    *	\param pType Type of the property. See enum FBPropertyType.
    *	\param pDataType DataType of the property.
    *	\param pAnimatable To specify if the property can be animated..
    *	\return The custom property created.
    *   \remark Only support Color, ColorAndAlpha, Number, Vector, Vector2, Vector4 data type for  user texture connect property.
    */
    FBProperty* CreateTextureConnectableUserProperty(const char* pName, FBPropertyType pType, const char* pDataType, bool pAnimatable);
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListMaterial
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: Material
class FBSDK_DLL FBPropertyListMaterial : public FBPropertyListComponent
{
public:
    FBPropertyListMaterial();
    /** Get the material at a specific index.
    *   @param  pIndex  Index of material to get.
    *   @return         The material at the specified index. Returns a NULL pointer on failure.
    */
    FBMaterial* operator[](int pIndex);
};

/** Custom Storable Material Class implementation.
*    This should be placed in the source code file for a custom material class.
*/

#define FBStorableCustomMaterialImplementation(ClassName, Type)\
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
    FBSetStoreableCustomMaterialRegistered();}\


#ifdef FBSDKUseNamespace
    }
#endif
#endif
