#ifndef _FB_SHADER_H_
#define _FB_SHADER_H_
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

/** \file fbshader.h
*
*   Declaration for the classes FBShaderManager, FBShader,
*   FBPropertyListShader and other subclasses.
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

K_FORWARD( KRenderOptions );
K_FORWARD( KModelRenderInfo );
K_FORWARD( KShaderModelInfo );

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

	/**	Shader class registration.
	*	\param	UniqueNameStr	Unique name.
	*	\param	ClassName		Shader class name.
	*	\param	Label			Short description.
	*	\param	Description 	Long description.
	*   \param  IconFilename    Name of the file containing the icon.
	*/
#define FBRegisterShader( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
	HIObject RegisterShader##ClassName( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	ClassName *Class = new ClassName( pName ); \
	Class->UniqueName = UniqueNameStr; \
	Class->ShaderDescription = Description; \
	if (Class->FBCreate()) { \
	return Class->GetHIObject(); \
	} else { \
	delete Class; \
	return NULL; \
	} \
} \
	FBLibraryModule( ClassName )	\
	{	\
	FBRegisterObject( ClassName##R1,"renderer/usershader/ogl",Label,Description,RegisterShader##ClassName,true, IconFilename );	\
	FBRegisterObject( ClassName##R2,"FbxStorable/Shader",UniqueNameStr,Description,RegisterShader##ClassName,true, IconFilename );	\
}

	/**	Shader class declaration.
	*	\param	ClassName	Shader class name.
	*	\param	Parent		Class parent.
	*/
#define FBShaderDeclare( ClassName, Parent  ) \
	FBClassDeclare( ClassName,Parent); \
public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
private:

	/**	Shader class implementation.
	*	\param	ThisComponent	Class to implement.
	*/
#define FBShaderImplementation( ThisComponent ) \
	FBClassImplementation( ThisComponent )

	////////////////////////////////////////////////////////////////////////////
	// FBShaderManager
	////////////////////////////////////////////////////////////////////////////
	FB_FORWARD( FBShaderManager );
	FB_FORWARD( FBShader );
    FB_FORWARD( FBMaterial );
    FB_FORWARD( FBCamera );

	/** Shader manager.
	*
	*   This class provides access to the list of available shaders, both
	*   system shaders and user shaders. The list comes in two versions:
	*     -# @ref ShaderTypeNames : which gives the internal names of the shaders,
	*     -# @ref ShaderTypeNamesLocalized : uses the GUI names of the shaders.
	*     .
	*
	*   Both of these lists will have the same number of elements. The strings
	*   at position i in the lists refer to the same shader type. In cases where
	*   there is no localized version of the shader name, the internal name
	*   will be used in @ref ShaderTypeNamesLocalized, thus ensuring consistency
	*   between the two lists.
	*      
	*   It also provides a generic shader creation method that uses the shader
	*   type name, internal or localized, to create the new shader instance.
	*
	*   The destruction of shaders is achieved by calling the FBDelete method
	*   of a shader instance.
	*
	*   The list of all the instantiated shaders can be obtained from instances
	*   of classes FBSystem or FBScene. Both classes have a Shaders property
	*   which lists the existing shader instances.
	*
	*   Strings are used instead of enum, define or typedef values to refer to
	*   shader types as this proves to be more flexible.
	*   
	*   @warning    The system has a default shader of type 'Lighted'. Do
	*               not attempt to destroy it.
	*   
	*   @warning    The use of localized names in shader creation is non portable
	*               as it is dependent of the current language used by the
	*               application. The name may also change from one version
	*               to another. Using the internal name is the only way to
	*               ensure portable shader creation.
	*   
	*   Sample C++ code:
	*   
	*   @code

	// This could be a constant value in the code, coming from a custom
	// registry or simply coming from one of the list ShaderTypeNames
	// or ShaderTypeNamesLocalized.
	const char* lDesiredShaderTypeName = "MyShader";

	// Shader creation.
	FBShader* lShader = NULL;
	FBShaderManager lShaderManager;

	if( lShaderManager.ShaderTypeNames.Find( lDesiredShaderTypeName ) != -1 ||
	lShaderManager.ShaderTypeNamesLocalized.Find( lDesiredShaderTypeName ) != -1 )
	{
	lShader = lShaderManager.CreateShader( lDesiredShaderTypeName );

	// Change its name, as the default name will be the type name.
	if( lShader )
	{
	lShader->Name = "My new shader";
	}
	else
	{
	// Warn about creation failure on a correctly registered
	// shader type.
	}
	}
	else
	{
	// Warn about an unknown shader type.
	}

	//
	// Do some work with the shader...
	// 

	if( lShader )
	{
	lShader->FBDelete();
	}

	*   @endcode
	*  
	*   @note   In the previous code sample, the lookup in the manager list is
	*           not necessary, as the call to CreateShader would have failed
	*           nonetheless and returned a NULL pointer.
	*
	*
	*   Sample Python code:
	*
	*   @code

	from pyfbsdk import *

	lShaderManager = FBShaderManager()

	# This code will create one instance of each of the
	# available shader type, changing its name to add the
	# 'My ' prefix.
	for lShaderTypeName in lShaderManager.ShaderTypeNames:
	lShader = lShaderManager.CreateShader( lShaderTypeName )
	if lShader:
	lShader.Name = "My %s" % lShader.Name
	print "Created new shader '%s'" % lShader.Name
	else:
	print "Unable to create shader of type '%s'" % lShaderTypeName

	*   @endcode
	*/
	class FBSDK_DLL FBShaderManager
	{
		/** Disabled copy constructor.
		*
		*   Voluntarily making the copy constructor unavailable.
		*/
		FBShaderManager( const FBShaderManager& );

		/** Disabled assignment operator.
		*
		*   Voluntarily making the assignment operator unavailable.
		*/
		FBShaderManager& operator=( const FBShaderManager& );

	public:

		//! Constructor.
		FBShaderManager();

		/** Destructor.
		*
		*   @warning    The destructor is non-virtual, meaning that this class is not
		*               meant to be used as a base class.
		*/
		~FBShaderManager();

		/** Creates a shader according to the shader type provided.
		*
		*   This method provides a generic way of creating shaders using the
		*   type name, internal or localized. The name of the new shader will
		*   be the same as the type name used, subject to changes according to
		*   the system's unique name policy.
		*
		*   @param pShaderTypeName  Name of the type of shader desired.
		*   @return A pointer to the newly created shader object, or a NULL
		*           pointer if the type name was not recognised.
		*/
		FBShader* CreateShader( const char* pShaderTypeName );

		/** List of available shaders.
		*
		*   This list does provide the complete list of available shaders, both
		*   system defined and user defined.
		*
		*   @warning    This list should not be modified. Changes to its value
		*               will not affect the shaders supported.
		*/
		FBStringList ShaderTypeNames;

		/** List of available shaders.
		*
		*   This list also provides the complete list of available shaders, but
		*   uses the localized named, as they can be seen in the GUI.
		*
		*   The names in this list are a direct match to the items in the
		*   list ShaderTypeNames for a given index.
		*
		*   This list is provided as a convenience, to avoid having to use
		*   the localization mechanism to match internal and GUI name.
		*
		*   @warning    Using localized names is potentially non portable as
		*               the name lookup is not done across all the supported
		*               languages. It is only done for the current language.
		*               In other words, using the English name to create a
		*               shader when the current language is not English will
		*               probably not succeed.
		*
		*   @warning    This list should not be modified. Changes to its value
		*               will not affect the shaders supported.
		*/
		FBStringList ShaderTypeNamesLocalized;
	};


	////////////////////////////////////////////////////////////////////////////
	// FBShader - Shader layer on top of internals.
	////////////////////////////////////////////////////////////////////////////

	FB_FORWARD( FBShaderModelInfo );
	class FBSDK_DLL FBShaderModelInfo
	{
	public:
		FBShaderModelInfo(FBShader* pShader, HKModelRenderInfo pInfo, int pSubRegionIndex);
		virtual ~FBShaderModelInfo();

		//! To be overloaded, always be called when Model or Shader version out of date.
		virtual void UpdateModelShaderInfo(int pShader_Version);

		//! Get Model
        FBModel* GetFBModel() { return mFBModel; }

        //! Get Material
        FBMaterial* GetFBMaterial();

        int GetSubRegionIndex();

		//! Get Internal ShaderModelInfo object
		KShaderModelInfo* GetShaderModelInfo() const { return mLocalPtr; }

		//! Get Last updated model version id
		int GetModelVersion() const;

		//! GetLast updated shader version.
		int GetShaderVersion() const;

		//! if application viewing mode request texture or not.
		bool GetOriginalTextureFlag() const;

        //! Get the geometry array ids for rendering.
        unsigned int GetGeometryArrayIds() const; 

        //! Get the geometry array ids for rendering.
        void SetGeometryArrayIds(unsigned int pArrayIds); 

	private:
		KShaderModelInfo* mLocalPtr;
        FBModel*    mFBModel;
	};

	//! FBRenderOptions
	FB_FORWARD( FBViewingOptions );
    FB_FORWARD( FBRenderOptions );

	class FBSDK_DLL FBRenderOptions
	{
	public:
		FBRenderOptions(HKRenderOptions pOptions);

        /** Get the rendering camera */
        FBCamera* GetRenderingCamera();

		/** Get Render Frame ID.
		*	\return	This return a new ID each time a new frame is drawn.
		*/
		int GetRenderFrameId() const;

        /** Get IDBuffer Rendering request status (for display or picking)
        *   \return true if need to render Model (or subitem)'s UniqueColorID into GL Color Buffer.
        */
        bool IsIDBufferRendering() const;

        /** Get IDBuffer Picking Alpha threshold.
        *   \return ID Buffer picking alpha threshold value.
        */
        float GetIDBufferPickingAlphaThreshold() const;

        /** Check if the render request comes from offline render mode (as opposed to viewport refresh).
        *   \return true if the render comes from offline render mode.
        */
        bool IsOfflineRendering() const;

        FBViewingOptions* GetViewerOptions() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
		/** Pointer to render options. */
		HKRenderOptions mRenderOptions;
#endif
	};

	//! \enum FBRenderingPass
	/** Rendering Pass. Use with FBShader::RenderingPass properties to make the shader
	*  be called at any pass. Passes will be called in the order of the enum.
	*/
	enum FBRenderingPass {
		kFBPassInvalid                  = 0,        //!< No pass selected.
		kFBPassPreRender                = 1 << 0,   //!< Before anything.
		kFBPassFlat                     = 1 << 1,   //!< Lighting off.
		kFBPassLighted                  = 1 << 2,   //!< Lighting on.
		kFBPassMatte                    = 1 << 3,   //!< Alpha > 0.5 will show up.
		kFBPassZTranslucent             = 1 << 4,   //!< Writes to depth buffer. 
		kFBPassZTranslucentAlphaTest    = 1 << 5,   //!< Writes to depth buffer where Alpha > 0.5.
		kFBPassTranslucent              = 1 << 6,   //!< Models are blended.
		kFBPassAddColor                 = 1 << 7,   //!< Models are blended additively.
		kFBPassTranslucentZSort         = 1 << 8,   //!< Models are sorted and blended. 
		kFBPassPostRender               = 1 << 9    //!< After everything.
	};
	FB_DEFINE_ENUM( FBSDK_DLL, RenderingPass );

	/** Shader transparency computation.
	*   There are different way to compute transparency, and this lists
	*   the supported options.
	*/
	enum FBAlphaSource
	{
		kFBAlphaSourceNoAlpha               ,   //!< No transparency.
		kFBAlphaSourceAccurateAlpha         ,   //!< Accurate Transparency.
		kFBAlphaSourceTransluscentAlpha     ,   //!< Translucent.
		kFBAlphaSourceMatteAlpha            ,   //!< Matte.
		kFBAlphaSource2DTransparency        ,   //!< 2D Transparency.
		kFBAlphaSourceAdditiveAlpha         ,   //!< Additive Transparency.
		kFBAlphaSourceTransluscentZSortAlpha,   //!< Translucent(Models Z Sort).
	};
	FB_DEFINE_ENUM( FBSDK_DLL, AlphaSource );

	/** Shader Capacity.
	*/
    enum FBShaderCapacity
    { 
        kFBShaderCapacityNone            = 0,
        kFBShaderCapacityMaterialEffect  = 1 << 0,     //!< This shader is acting as a material effect, should sitting behind the material central network, only affect the same materail mapped regions of the whole model.
        kFBShaderCapacityDrawInstanced   = 1 << 1,     //!< This shader can support GL_ARB_draw_instanced extension, and thus could benefit from Geometry instancing when upload transformation matrix. 
        kFBShaderCapacityDrawShadow      = 1 << 2,     //!< This shader will able to draw different shape thus generate different shadow than original solid geometry.
        kFBShaderCapactiyDrawTextureLayer= 1 << 3      //!< This shader will able to draw additional texture layer (for example, live shadow or reflection).
    };
    FB_DEFINE_ENUM( FBSDK_DLL, ShaderCapacity );

    /** Shader Pass Action Callback.
    * ORSDK shader should request which pass action should be hooked up for callback.
    */
    enum FBShaderPassActionCallback
    {
        kFBShaderPassActionNone         = 0,  
        kFBShaderPassTypeBegin          = 1 << 0,
        kFBShaderPassTypeEnd            = 1 << 1,
        kFBShaderPassInstanceBegin      = 1 << 2, 
        kFBShaderPassInstanceEnd        = 1 << 3, 
        kFBShaderPassMaterialBegin      = 1 << 4, 
        kFBShaderPassMaterialEnd        = 1 << 5,
        kFBShaderPassGeometryBegin      = 1 << 6,
        kFBShaderPassGeometryEnd        = 1 << 7,
        kFBShaderPassModelsDraw         = 1 << 8,
        kFBShaderPassModelDraw          = 1 << 9
    };
    FB_DEFINE_ENUM( FBSDK_DLL, ShaderPassActionCallback );

	FB_FORWARD( FBRenderer );
	__FB_FORWARD( FBShader );
	FB_DEFINE_COMPONENT	( FBSDK_DLL, Shader );
	FB_DEFINE_LIST		( FBSDK_DLL, Shader );

	//! Shader class.
	class FBSDK_DLL FBShader : public FBBox
	{
		//--- Open Reality declaration.
		__FBClassDeclare( FBShader, FBBox );

	public:
		/** Protected constructor.
		*	\param	pName	Shader name.
		*	\param	pObject Internal parent object to own shader(default=NULL).
		*/
		FBShader( const char* pName, HIObject pObject=NULL);

		IObject_Declare(override);		// Interface to IObject.

		/** Create a new shader-model information object.
		*	\param	pModelRenderInfo 	Internal Model Render Info.
		*   \param  pSubRegionIndex
		*	\return	Newly allocated shader-model information object.
		*/
		virtual FBShaderModelInfo* NewShaderModelInfo(HKModelRenderInfo pModelRenderInfo, int pSubRegionIndex);

		/** Update shader-model information when model, material & texture mapping or shader setting change.
		*	\param	pOptions	Render options.
		*	\param	pInfo		Shader-model information object to be updated.
		*/
        virtual void UpdateModelShaderInfo( FBRenderOptions* pOptions, FBShaderModelInfo* pInfo );

		/** Destroy shader-model information object callback.
		*	\param	pOptions	Render options.
		*	\param	pInfo		Shader-model information object to destroy.
		*/
		virtual void DestroyShaderModelInfo( FBRenderOptions* pOptions, FBShaderModelInfo* pInfo );

		/** Replace all shader in \e pModel.
		*	\param	pModel	Model to replace all shader to.
		*	\return	True if the operation is successful, false otherwise.
		*/
		virtual bool ReplaceAll( FBModel* pModel );

		/** Append shader to \e pModel.
		*	\param	pModel	Model to append shader to.
		*	\return	True if the operation is successful, false otherwise.
		*/
		virtual bool Append( FBModel* pModel );

		/** Does the shader need a begin render call.
		*	\remark	Re-implement this function and return true if you need it. This method is called once per shader on each render pass.
		*/
		virtual bool ShaderNeedBeginRender();

		/** Pre-rendering of shaders that is called only one time for a shader instance.
		*	\remark	ShaderBeginRender is called as many times as the number of models affected 
		*			by the instance of the shader in a given render pass. (ShaderNeedBeginRender 
		*			must return true for this function to be called).
		*/
		virtual void ShaderBeginRender( FBRenderOptions* pOptions, FBShaderModelInfo* pInfo );

		/**	Real-time shading callback for shader without kFBShaderCapacityMaterialEffect. This is called after all the calls to ShaderBeginRender.
		*	\param	pOptions	Render options.
		*	\param	pPass		Rendering pass.
		*	\param	pInfo		Shader-model information.
		*/
		virtual void ShadeModel( FBRenderOptions* pOptions, FBShaderModelInfo* pInfo, FBRenderingPass pPass );

        /** Draw custom shadow shape callback for shader with kFBShaderCapacityDrawShadow but without kFBShaderCapacityMaterialEffect.
        *	\param	pRenderOptions	Render options.
        *	\param	pInfo		Shader-model information.
        */
        virtual void ShadeModelShadow(FBRenderOptions* pRenderOptions, FBShaderModelInfo* pInfo);

		/**
		* \name Real-time shading callbacks for kFBMaterialEffectShader. 
		*/
		//@{

		/** For all the shader instances of the same type, to setup the common state for all this type of shaders. 
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*/
		virtual void ShaderPassTypeBegin    ( FBRenderOptions* pRenderOptions, FBRenderingPass pPass);  

		/** For all the shader instances of the same type, to clean the common state for all this type of shaders 
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*/
		virtual void ShaderPassTypeEnd      ( FBRenderOptions* pRenderOptions, FBRenderingPass pPass);     

		/** For all the models associated with this shader instance, to setup the common state for this shader instance. 
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*/
		virtual void ShaderPassInstanceBegin( FBRenderOptions* pRenderOptions, FBRenderingPass pPass);  

		/** For all the models associated with this shader instance, to clean the common state for this shader instance.
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*/
		virtual void ShaderPassInstanceEnd  ( FBRenderOptions* pRenderOptions, FBRenderingPass pPass);  

		/** For all the models mapped with this material and associated with this shader instance, to setup the common material state for this shader instance.
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*	\param	pInfo		Shader-model information.
		*/
		virtual void ShaderPassMaterialBegin( FBRenderOptions* pRenderOptions, FBRenderingPass pPass, FBShaderModelInfo* pInfo);  

		/** For all the models mapped with this material and associated with this shader instance, to clean the common material state for this shader instance.
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*	\param	pInfo		Shader-model information.
		*/
		virtual void ShaderPassMaterialEnd  ( FBRenderOptions* pRenderOptions, FBRenderingPass pPass, FBShaderModelInfo* pInfo);  

		/** For all the models instanced from the same geometry, to setup the common VBO state for this shader instance.
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*	\param	pInfo		Shader-model information.
		*/
		virtual void ShaderPassGeometryBegin( FBRenderOptions* pRenderOptions, FBRenderingPass pPass, FBShaderModelInfo* pInfo);  

		/** For all the models instanced from the same geometry, to clean the common VBO state for this shader instance.
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*	\param	pInfo		Shader-model information.
		*/
		virtual void ShaderPassGeometryEnd  ( FBRenderOptions* pRenderOptions, FBRenderingPass pPass, FBShaderModelInfo* pInfo);
	
		/** For all the models with the same material/geometry mappings, inside this functions, we only need to setup modelview matrix, and draw the meshes. 
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*	\param  pInfoArray  An array of Shader-model information to be displayed.
		*/
		virtual void ShaderPassModelsDraw ( FBRenderOptions* pRenderOptions, FBRenderingPass pPass, const FBArrayTemplate<FBShaderModelInfo*>& pInfoArray);

        /** Callback for Cg/CgFx shader to setup WorldMaitrx/WorldMatrixIT parameters. 
		*	\param	pRenderOptions	Render options.
		*	\param	pPass		Rendering pass.
		*	\param	pInfo		Shader-model information.
        */
        virtual void ShaderPassModelDraw ( FBRenderOptions* pRenderOptions, FBRenderingPass pPass, FBShaderModelInfo* pInfo);

		/** Shadow draw pass begin notify for shader with kFBShaderCapacityMaterialEffect and kFBShaderCapacityDrawShow.
		*	\param	pRenderOptions	Render options.
		*/
		virtual void ShaderPassDrawShadowBegin( FBRenderOptions* pRenderOptions);

		/** Shadow draw pass end notify for shader with kFBShaderCapacityMaterialEffect and kFBShaderCapacityDrawShow.
		*	\param	pRenderOptions	Render options.
		*/
		virtual void ShaderPassDrawShadowEnd ( FBRenderOptions* pRenderOptions);

        //! Get Shader Pass Action Callback registration;
        FBShaderPassActionCallback   GetShaderPassActionCallback() const;
        //! Set Shader Pass Action Callback registration;
        void         SetShaderPassActionCallback( FBShaderPassActionCallback pCallback);
   
		//@}

		/**	Clone shader.
		*	\param	pNewShader	Shader to copy data to.
		*/
		virtual void CloneShaderParameter( FBShader* pNewShader );

		/**	Detach the display context from the shader.
		*	\param	pOptions	Render options.
		*	\param	pInfo		Shader-model information object.
		*/
		virtual void DetachDisplayContext( FBRenderOptions* pOptions, FBShaderModelInfo* pInfo );

		/** Storage of information into the FBX file format.
		*	\param	pFbxObject	Object to interface with FBX file format.
		*	\return	\b true if successful, \b false otherwise.
		*/
		virtual bool FbxStore	(FBFbxObject* pFbxObject);

		/** Retrieval of information into the FBX file format.
		*	\param	pFbxObject	Object to interface with FBX file format.
		*	\param	pRenderer	Renderer being restored.
		*	\return	\b true if successful, \b false otherwise.
		*/
		virtual bool FbxRetrieve(FBFbxObject* pFbxObject, FBRenderer* pRenderer);

		const char*	ShaderDescription;	//!< Description.

        /** Invalidate Shader version to trigger model-shader informaton to be updated.*/
        void    InvalidateShaderVersion ();

		/** Return Shader Version*/
		int     GetShaderVersion        ()  const;

        /** Return Shader Capacity (bitwise value)*/
        FBShaderCapacity GetShaderCapacity( ) const;

        /** Return true if shader has certain capacity*/
        bool         HasShaderCapacity    (FBShaderCapacity pCapacity);  

        /** Set Shader Capacity (bitwise value).
        *   Only when the shader is not connected to any model, this function will take effect. otherwise, it will be ignored.
        */
        void         SetShaderCapacity    (FBShaderCapacity pCapacity, bool pOn);

        /** Get shader maximum size for draw instanced*/
        int          GetDrawInstancedMaximumSize() const;

        /** Set shader maximum size for draw instanced*/
        void         SetDrawInstancedMaximumSize(int pMaxSize);

        /** Callback for uploading the modelview array when draw instanced.
        *   \param pModelViewMatrixArray    pointer of 4x4 column major modelview matrix array, length is 4*4*pCount;
        *   \param pCount                   number of modelview matrixs in the array.
        */
        virtual void UploadModelViewMatrixArrayForDrawInstanced(const double* pModelViewMatrixArray, int pCount);


	public:
		/** <b>Read Write Property:</b> Is the shader Enabled
		*/
		FBPropertyBool              Enable;

		/** <b>Read Write Property:</b> Rendering pass object are shaded in.
		*  Set the property to kFBPassFlat if you want to be called at the first pass,
		*  kFBPassPostRender at the second pass, kFBPassFlat | kFBPassPostRender at both.
		*  The current pass will be the third argument of ShadeModel()
		*/
		FBPropertyRenderingPass		RenderingPass;

	protected:
		/** In order to be called at the right passes, a shader must set the result of
		*   GetRenderingPassNeededForAlpha() to RenderingPass for a given transparency
		*   type. It should not be called at rendering time.
		*	\param	pTransparency	Transparency type.
		*	\return	a mask of all rendering passes needed for DrawGeometry() to work correctly.
		*/
		static FBRenderingPass GetRenderingPassNeededForAlpha(FBAlphaSource pTransparency);
	};

	////////////////////////////////////////////////////////////////////////////////////
	// FBPropertyListShader - List of shaders
	////////////////////////////////////////////////////////////////////////////////////
	//! \b PropertyList: Shader
	class FBSDK_DLL FBPropertyListShader : public FBPropertyListComponent
	{
	public:
		FBPropertyListShader();
		/** Get the shader from list at \e pIndex.
		*	\param	pIndex	Index to get shader at.
		*	\return Shader at \e pIndex.
		*/
		FBShader* operator[](int pIndex);
	};

	////////////////////////////////////////////////////////////////////////////
	// FBShaderLighted
	////////////////////////////////////////////////////////////////////////////
	FB_FORWARD( FBShaderLighted );
	FB_DEFINE_COMPONENT( FBSDK_DLL, ShaderLighted );

	/** Lighted shader class.
	*
	*   This type of shader is the default type used by the application. It allows
	*   users to control luminosity, contrast and specularity as well as how
	*   the transparency is computed, should it be used.
	*
	*   There are two methods to create a FBShaderLighted object: using the 
	*   FBShaderManager, or simply by instantiating a class object explicitely.
	*
	*   @note       Please consult the application documentation for more infos on
	*               shader properties and their effects.
	*
	*   @warning    This class should not serve as a base class for another class.
	*
	*
	*   Sample C++ code:
	*   
	*   @code

	// Creation of a lighted shader, and setting it to use
	// the constrast and specularity.
	FBShaderLighted* lShader = new FBShaderLighted( "New Shader" );

	lShader->UseContrast  = true;
	lShader->UseSpecular  = true;
	lShader->Specular     = 35.0;
	lShader->Transparency = kFBAlphaSourceTransluscentAlpha;

	// Use the shader.
	FBModel* lModel = FBFindModelByLabelName( "Cube" );
	if( lModel )
	{
	lShader->ReplaceAll( lModel );
	}

	// Do some more things...

	// And then delete it when no longer necessary;
	lShader->FBDelete();

	*   @endcode
	*
	*
	*   The following sample code does the same task, but in Python.
	*
	*   Sample Python code:
	*
	*   @code

	from pyfbsdk import *

    # Creating the shader.
    lShader = FBShaderLighted( 'New Python Shader' )
    lShader.UseContrast  = True
    lShader.UseSpecular  = True
    lShader.Specular     = 35.0
    lShader.Transparency = FBAlphaSource.kFBAlphaSourceTransluscentAlpha

	# User the shader
	lModel = FBFindModelByLabelName( 'Cube' )
    if lModel <> None:
	    lModel.Show = True
        lShader.ReplaceAll( lModel )

	*   @endcode
	*/
	class FBSDK_DLL FBShaderLighted : public FBShader
	{
		//--- Open Reality declaration.
		FBClassDeclare( FBShaderLighted, FBShader );

	public:
		/** Constructor.
		*   \param  pName   Name of shader.
		*   \param  pObject Internal parent object to own shader(default=NULL).
		*/
		FBShaderLighted( const char* pName, HIObject pObject=NULL );

		FBPropertyBool             UseContrast;   //!< <b>Read Write Property:</b> Activate the Contrast option.
		FBPropertyDouble           Contrast;      //!< <b>Read Write Property:</b> Changes the contrast of the object when it reflects light.

		FBPropertyBool             UseLuminosity; //!< <b>Read Write Property:</b> Activate the Luminosity option.
		FBPropertyDouble           Luminosity;    //!< <b>Read Write Property:</b> Changes the brightness of the object when reflecting light.

		FBPropertyBool             UseSpecular;   //!< <b>Read Write Property:</b> Activate the Specularity option.
		FBPropertyDouble           Specular;      //!< <b>Read Write Property:</b> Changes an object's level of shininess when it reflects light by affecting the specular highlight.

		FBPropertyAlphaSource      Transparency;  //!< <b>Read Write Property:</b> Indicates the computation method of the transparency.
		FBPropertyAnimatableDouble Alpha;         //!< <b>Read Write Property:</b> Controls the actual effect of the shader on the object. At 0.0 it does nothing, and at 1.0 it fully affects the object.
	};


	////////////////////////////////////////////////////////////////////////////
	// FBShaderShadowLive
	////////////////////////////////////////////////////////////////////////////
	FB_FORWARD( FBShaderShadowLive );
	FB_DEFINE_COMPONENT( FBSDK_DLL, ShaderShadowLive );

	/** Shadow types.
	*   The different types of shadow mapping.
	*/
	enum FBShadowType
	{ 
		kFBShadowTypeShadowTranslucentPlanar              ,    //!< Use this shadow type to create darkened shadow areas only on planar surfaces.
		kFBShadowTypeShadowProjectiveTexture   ,    //!< Uses a texture projection to create a shadow.
		kFBShadowTypeLightMapProjectiveTexture ,    //!< Uses a texture projection as a shadow.
		kFBShadowTypeZShadowProjectiveTexture  ,    //!< Similar to the Projective Shadow, except that it uses a boolean algorithm to create a self-shadow.
		kFBShadowTypeZLightMapProjectiveTexture,    //!< Similar to the Projective Light Map except that it uses a boolean algorithm to create a self-shadow.
		kFBShadowTypeShadowOpaquePlanar		   ,	//!< Similar to the Planar Shadow, except that it treats all objects as opaque.
	};
	FB_DEFINE_ENUM( FBSDK_DLL, ShadowType );

	/** Shadow calculation methods.
	*/
	enum FBShadowFrameType
	{
		kFBShadowFrameTypeShadowReceiver,   //!< Bases the shadow calculation on the shadow of the receiver.
		kFBShadowFrameTypeShadowCaster  ,   //!< Bases the shadow calculation on the shadow of the caster.
		kFBShadowFrameTypeShadowCubeMap ,   //!< Undocumented or unsupported.
	};
	FB_DEFINE_ENUM( FBSDK_DLL, ShadowFrameType );


	/** Shader Shadow Live class.
	*
	*   Use the Live Shadow shader to apply real-time shadows to models. You can
	*   specify shadow intensity as well as the lights and objects that cast shadows
	*   in a scene.
	*
	*   There are two methods to create a FBShaderShadowLive object: using the 
	*   FBShaderManager, or simply by instantiating a class object explicitely.
	*
	*   @note       Please consult the application documentation for more infos on
	*               shader properties and their effects.
	*
	*   @warning    This class should not serve as a base class for another class.
	*
	*
	*   Sample C++ code:
	*   
	*   @code

	// Create a shadow shader.
	FBShaderShadowLive* lShader = new FBShaderShadowLive( "New Shader" );

	// Add a cube in its list of affected objects.
	FBModel* lModel = FBFindModelByLabelName( "Cube" )
	if( lModel )
	{
	lShaderShadowLive.Add( lCube );
	}

	*   @endcode
	*
	*
	*   Sample Python code:
	*
	*   @code

	from pyfbsdk import *

	# Create shader.
	lShader = FBShaderShadowLive( 'New Python Shader' )

	# Find a cube to put in our list of affected objects.
	lModel = FBFindModelByLabelName( 'Cube' )
	if lModel:
	lShader.ShadowCasterProperty.append( lModel )

	*   @endcode
	*/
	class FBSDK_DLL FBShaderShadowLive : public FBShader
	{
		//--- Open Reality declaration.
		FBClassDeclare( FBShaderShadowLive, FBShader );

	public:
		/** Constructor.
		*   \param  pName    Name of shader.
		*   \param  pObject  Internal parent object to own shader (default is NULL).
		*/
		FBShaderShadowLive( const char* pName, HIObject pObject=NULL );

		FBPropertyShadowType       ShadowType;      //!< <b>Read Write Property:</b> Indicate which shadow type is desired.
		FBPropertyAnimatableDouble ShadowIntensity; //!< <b>Read Write Property:</b> Controls the darkness of shadows cast by a selected object.
		FBPropertyBool             LocalShadow;     //!< <b>Read Write Property:</b> Creates an accurate projection of a shadow for each object.
		FBPropertyBool             UseGobo;         //!< <b>Read Write Property:</b> Includes the gobo in the shadow map calculation.
		FBPropertyDouble           ShadowZOffset;   //!< <b>Read Write Property:</b> Specifies the offset of the Live Shadow shader's plane from the original selected plane.
		FBPropertyShadowFrameType  ShadowFrameType; //!< <b>Read Write Property:</b> Used to select the shadow calculation method.

		FBPropertyListObject       Lights;          //!< <b>List:</b> List of light object which will produce shadows.
		FBPropertyListObject       Models;          //!< <b>List:</b> List of object which when lighted will cast a shadow.

	};


#ifdef FBSDKUseNamespace
}
#endif
#endif /* _FB_SHADER_H_ */
