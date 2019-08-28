#ifndef __FBLIGHT_H__
#define __FBLIGHT_H__
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

/** \file fbmodel.h
*    Base class for Lights.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
    /** \def FBSDK_DLL
    *    Be sure that FBSDK_DLL is defined only once...
    */
    #define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbmodel.h>

#ifdef FBSDKUseNamespace
    namespace FBSDKNamespace {
#endif

FB_DEFINE_COMPONENT( FBSDK_DLL, Light            );

////////////////////////////////////////////////////////////////////////////////////
// FBLight
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBLight );

//! Light types
enum FBLightType    { 
    kFBLightTypePoint = 0,  //!< Point light.
    kFBLightTypeInfinite,   //!< Infinite light (plane).
    kFBLightTypeSpot,       //!< Spot light.
    kFBLightTypeArea            //!< Area light. 
};

FB_DEFINE_ENUM( FBSDK_DLL, LightType    );

//! Light attenuation types
enum FBAttenuationType    { 
    kFBAttenuationNone = 0,     //!< No attenuation.
    kFBAttenuationLinear,       //!< Linear attenuation.
    kFBAttenuationQuadratic,    //!< Quadratic attenuation.
    kFBAttenuationCubic         //!< Cubic attenuation.
};

FB_DEFINE_ENUM( FBSDK_DLL, AttenuationType    );

//! Light class.
class FBSDK_DLL FBLight : public FBModel 
{
    __FBClassDeclare( FBLight,FBModel );
public:
    /**    Constructor.
    *    \param    pName        Name of light.
    *    \param    pObject      For internal use only(default=NULL).
    */
    FBLight(const char* pName, HIObject pObject=NULL);

    //! Area light shapes.
    enum EAreaLightShapes {
        eRectangle,        //!< Rectangle.
        eSphere            //!< Sphere.
    };

    typedef FBPropertyBaseEnum<EAreaLightShapes> PropertyAreaLightShapes;   

    // Light parameters

    /** <b>Read Write Property:</b> Type of light. 
    *   MoBu default renderer don't support Area Light, it's useful for pipeline interop with other DCC tools, 
    *   and custom renderer (or shader) plugin development. 
    *   \note To use Area Light, please set FBRenderer::AdvancedLightingMode property, or modify config 
    *           "AdvancedLightingUISetting" at [Rendering] section. 
    */
    FBPropertyLightType           LightType;                  
	PropertyAreaLightShapes       AreaLightShape;             //!< <b>Read Write Property:</b> Area light shape.
    FBPropertyAttenuationType     AttenuationType;            //!< <b>Read Write Property:</b> Type of attenuation for the light.
    FBPropertyAnimatableDouble    Intensity;                  //!< <b>Read Write Property:</b> Light intensity.
    FBPropertyAnimatableDouble    InnerAngle;                 //!< <b>Read Write Property:</b> Inner Cone angle for light.
    FBPropertyAnimatableDouble    OuterAngle;                 //!< <b>Read Write Property:</b> Outer Cone angle for light.
    FBPropertyAnimatableDouble    ConeAngle;                  //!< <b> DEPRECATED </b> Equivalent to OuterAngle.
    FBPropertyAnimatableDouble    FogIntensity;               //!< <b>Read Write Property:</b> Intensity of the fog (spot light).
    FBPropertyAnimatableColor     DiffuseColor;               //!< <b>Read Write Property:</b> Color: Diffuse color.
    FBPropertyBool                CastLightOnObject;          //!< <b>Read Write Property:</b> Cast light on object?    
    FBPropertyBool                CastShadows;                //!< <b>Read Write Property:</b> Cast shadows on object?    

    // Effects and Gobos
    FBPropertyBool                DrawGroundProjection;       //!< <b>Read Write Property:</b> Draw ground projection of gobo?
    FBPropertyBool                DrawVolumetricLight;        //!< <b>Read Write Property:</b> Draw volumetric light with gobo?
    FBPropertyBool                DrawFrontFacingVolumetric;  //!< <b>Read Write Property:</b> Draw front facing volumetric light?
    FBPropertyVideo               GoboMedia;                  //!< <b>Read Write Property:</b> Media to use as a Gobo with the light.

    FBPropertyBool                EnableBarnDoor;             //!< <b>Read Write Property:</b> Whether or not enable barn door.
    FBPropertyDouble              LeftBarnDoor;               //!< <b>Read Write Property:</b> Angle of left barn door.
    FBPropertyDouble              RightBarnDoor;              //!< <b>Read Write Property:</b> Angle of right barn door.
    FBPropertyDouble              TopBarnDoor;                //!< <b>Read Write Property:</b> Angle of top barn door.
    FBPropertyDouble              BottomBarnDoor;             //!< <b>Read Write Property:</b> Angle of bottom barn door.
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListLight
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: Light
class FBSDK_DLL FBPropertyListLight : public FBPropertyListComponent
{
public:
    FBPropertyListLight();
    /**    Get the model at \p pIndex.
    *    \param    pIndex    Index of light to get.
    *    \return Light at \p pIndex.
    */
    FBLight* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// FBGlobalLight
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBGlobalLight );

//! Fog falloff modes.
enum FBFogMode    
{ 
    kFBFogModeLinear,                //!< Linear falloff.
    kFBFogModeExponential,           //!< Exponential falloff.
    kFBFogModeSquareExponential      //!< Squared exponential falloff.
};

FB_DEFINE_ENUM( FBSDK_DLL, FogMode );

//! Global light class.
class FBSDK_DLL FBGlobalLight : public FBBox
{
    __FBClassDeclare( FBGlobalLight, FBBox );

    //! Constructor. protected 
    FBGlobalLight();

public:

    FBPropertyAnimatableColor    AmbientColor;        //!< <b>Read Write Property:</b> Ambient light color.

    // Fog
    FBPropertyBool                FogEnable;          //!< <b>Read Write Property:</b> Enable fog?
    FBPropertyAnimatableColor     FogColor;           //!< <b>Read Write Property:</b> Fog color.
    FBPropertyAnimatableDouble    FogBegin;           //!< <b>Read Write Property:</b> Begin fog distance.
    FBPropertyAnimatableDouble    FogEnd;             //!< <b>Read Write Property:</b> End fog distance.
    FBPropertyAnimatableDouble    FogDensity;         //!< <b>Read Write Property:</b> Fog density.
    FBPropertyFogMode             FogMode;             //!< <b>Read Write Property:</b> Fog falloff mode.

    /**    Get the global Light object
    *    \return    the global Light object.
    */
    static FBGlobalLight& TheOne();
};

#ifdef FBSDKUseNamespace
    }
#endif
#endif
