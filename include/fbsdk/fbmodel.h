#ifndef __FBMODEL_H__
#define __FBMODEL_H__
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
*    Base class for models.
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
#include <fbsdk/fbshader.h>    // FBPropertyListShader
#include <fbsdk/fbtexture.h>
#include <fbsdk/fbgeometry.h>
#include <fbsdk/fbmaterial.h>
#include <fbsdk/fbtexture.h>
#include <fbsdk/fbmath.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {;
#endif

/** Custom Storable Model Class implementation.
*    This should be placed in the source code file for a custom model class.
*/
#define FBStorableCustomModelImplementation(ClassName, Desc)\
    const char* ClassName::FbxGetObjectSubType(){ return #ClassName; }\
    HIObject RegisterStorable##ClassName##Create(HIObject /*pOwner*/, const char* pName, void* /*pData*/){\
    ClassName* Class = new ClassName(pName);\
    Class->mAllocated = true;\
    if( Class->FBCreate() ){\
    __FBRemoveModelFromScene( Class->GetHIObject() ); /* Hack in MoBu2013, we shouldn't add object to the scene/entity automatically*/\
    return Class->GetHIObject();\
    } else {\
    delete Class;\
    return NULL;}}\
    FBLibraryModule(ClassName##Storable){\
    FBString lGroup = "FbxStorable/Model";\
    FBRegisterObject(ClassName##R2, lGroup, #ClassName, Desc, RegisterStorable##ClassName##Create, true, NULL);\
    FBSetStoreableCustomModelRegistered();}\

FB_DEFINE_COMPONENT( FBSDK_DLL, Model            );
FB_DEFINE_COMPONENT( FBSDK_DLL, Cluster          );
FB_DEFINE_COMPONENT( FBSDK_DLL, ModelVertexData  );
FB_DEFINE_COMPONENT( FBSDK_DLL, PointCacheFile   );

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListModel
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModel ); 
__FB_FORWARD( FBPropertyListModel );
FB_DEFINE_LIST( FBSDK_DLL, Model );

//! <b>List:</b> Model
class FBSDK_DLL FBPropertyListModel : public FBPropertyListComponentBase
{
public:
    /**    Add a model to the property list.
    *    \param    pItem    Model to add to list.
    *    \return    Number of items in list after operation.
    */
    int     Add    ( FBModel* pItem );

    /**    Remove model \p pItem from property list.
    *    \param    pItem    Model to remove from list.
    *    \return The index of the removed element. Returns -1 if the element was not part of the list.
    */
    int  Remove    ( FBModel* pItem );

    /** Remove the model at \p pIndex.
    *    \param pIndex    Index of model to remove.
    */
    virtual void RemoveAt( int pIndex );

    /**    Get the model at \p pIndex.
    *    \param    pIndex    Index of model to get.
    *    \return Model at \p pIndex.
    */
    FBModel* operator[](int pIndex);

    /** Get the number of models.
    *    \return Number of models.
    */
    virtual int  GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
private:
    inline virtual int Add    ( FBComponent* pItem ) { return Add((FBModel*)pItem); }
    inline virtual int Remove    ( FBComponent* pItem ) { return Remove((FBModel*)pItem); }
#endif
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListDeformer
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: Texture
__FB_FORWARD( FBDeformer );

class FBSDK_DLL FBPropertyListDeformer : public FBPropertyListComponent
{
public:
    FBPropertyListDeformer();
    /** Add a texture to the property list.
    *   @param      pItem   Texture to add to the list.
    *   @return             The index of the element in the list. Returns -1 on failure.
    *   @warning            Adding a new element will invalidate any existing iterators
    *                       as the new items may not be added at the end of the list.
    */
    virtual int Add( FBDeformer* pItem );
    /** Get the texture at a specific index.
    *   @param  pIndex  Index of texture to get.
    *   @return         The texture at the specified index. Returns a NULL pointer on failure.
    */
    FBDeformer* operator[](int pIndex);

private:
    inline virtual int Add    ( FBComponent* pItem ) { return Add((FBDeformer*)pItem); }
};

////////////////////////////////////////////////////////////////////////////////////
// FBModel
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModel        );

//! Types of transformation vector/matrices possible.
enum FBModelTransformationType {   
    kModelTransformation,                   //!< Transformation.
    kModelRotation,                         //!< Rotation.
    kModelTranslation,                      //!< Translation.
    kModelScaling,                          //!< Scaling.
    kModelTransformation_Geometry,          //!< Transformation plus geometry offset  
    kModelInverse_Transformation,           //!< Inverse transformation.
    kModelInverse_Rotation,                 //!< Inverse rotation.
    kModelInverse_Translation,              //!< Inverse translation.
    kModelInverse_Scaling,                  //!< Inverse scaling.
    kModelInverse_Transformation_Geometry   //!< Inverse of transformation plus geometry offset
};

//! Modes for model shading.
enum FBModelShadingMode {    
    kFBModelShadingDefault,         //!< Default shading.
    kFBModelShadingWire,            //!< Wireframe shading.
    kFBModelShadingFlat,            //!< Flat shading.
    kFBModelShadingLight,           //!< Lighted shading.
    kFBModelShadingHard,            //!< Hard shading.
    kFBModelShadingTexture,         //!< Textured shading.
    kFBModelShadingAll,             //!< Lighted, shaded, textured shading.
};

//! Model Render pass.
enum FBModelRenderPass {    
    kFBModelRenderPassStandard,     //!< Standard pass.
    kFBModelRenderPassPick,         //!< Pick pass.
};

//! Ways to apply Rotation.
enum FBModelRotationOrder {    
    kFBEulerXYZ = 0,    //!< XYZ Euler Order
    kFBEulerXZY,        //!< XZY Euler Order
    kFBEulerYZX,        //!< YZX Euler Order
    kFBEulerYXZ,        //!< YXZ Euler Order
    kFBEulerZXY,        //!< ZXY Euler Order
    kFBEulerZYX,        //!< ZYX Euler Order
    kFBSphericXYZ        //!< Spheric XYZ Order
};

//! Model Culling Mode
enum FBModelCullingMode {
    kFBCullingOff,      //!< Culling Off
    kFBCullingOnCCW,    //!< Culling with Counter Clock Wise
    kFBCullingOnCW      //!< Culling with Clock Wise
};

enum FBModelEvaluationTaskType {
    kFBModelEvaluationTransform, //!< Model's transformation evaluation task (Global )
    kFBModelEvaluationBBox,      //!< Model's bouding box computation task (approximately for deformable model)
    kFBModelEvaluationDeform     //!< Model's deformation task (for deformable model)
};

//! Types of hierarchy traverser search type
enum FBModelHiercharyTraverserType {   
    kModelTraverserDepthFirst,				//!< Depth-first search
    kModelTraverserBreadthFirst,			//!< Breadth-first search.
};

//! Selection mode when selecting component
enum FBSelectionAction {
	kFBManipulatorReplace = 0,	//!< Replaces the current selection by the new selected components.
	kFBManipulatorAdd,			//!< Add the selected components to the current selection.
	kFBManipulatorRemove,		//!< Remove the selected components from the current selection.
	kFBManipulatorToggle,		//!< Toggle the current selection with the unselected components.
	kFBManipulatorAddAll,		//!< Add all components to the current selection.
	kFBManipulatorRemoveAll,	//!< Remove all components from the current selection.
};

FB_DEFINE_ENUM( FBSDK_DLL, ModelShadingMode       ); 
FB_DEFINE_ENUM( FBSDK_DLL, ModelTransformationType);
FB_DEFINE_ENUM( FBSDK_DLL, ModelRotationOrder     ); 

FB_FORWARD( FBCamera );

/** Model class.
*   In the MotionBuilder UI, a model can be any object in a scene, created using geometry. Models can represent simple objects
like cubes, or complex objects like characters.

FBModel is a base class which is not used so much directly,
but is the parent of well-used classes like FBCamera, FBLight, and FBModelMarker.

It also implements a number of widely-implemented functions and attributes, such as:
\li Clone(), FBDelete()
\li UI attributes such as Show, Pickable, and Visibility
\li Positional attributes such as Rotation, Scaling, and Translation
The following Python snippet shows how to create, show, rotate, and delete a cube
\code
from pyfbsdk import *
myCube = FBModelCube("cube")
myCube.Show = True
myCube.Rotation = FBVector3d(45, 45, 45)
myCube.FBDelete()
\endcode

There is a few ways to get a handle on existing models in a scene:
\li FBFindObjectsByName return a list of objects matching
a pattern (can contain *). For usage, see: FindObjectsWithWildcard.py
\li If you know the name of the model, use FBFindModelByLabelName, as demonstrated in FBComponent.py.
\li FBGetSelectedModels can get a handle to an object which is derived from FBModel.
It searches the scene for a model, based on the model's unique name and returns
a list of all the selected things in the scene.

*/

class FBSDK_DLL FBModel : public FBBox 
{
    __FBClassDeclareGroup( FBModel,FBBox );
public:
    /**    Constructor.
    *    \param    pName        Name of model.
    *    \param    pObject    For internal use only(default=NULL).
    */
    FBModel(const char* pName, HIObject pObject=NULL);
    virtual void    FBDelete();

    IQuery_Declare       (K_IMPLEMENTATION);                //!< Interface to IObject.
    ICallback_Declare    (K_IMPLEMENTATION);                //!< Interface to ICallback.

    FBPropertyListModel             Children;               //!< <b>List:</b> Children for model.

    FBPropertyListShader            Shaders;                //!< <b>List:</b> Shaders for model.
    FBPropertyListMaterial          Materials;              //!< <b>List:</b> Materials for model.
    FBPropertyListTexture           Textures;               //!< <b>List:</b> Textures with Special UseType (Other than "Color" which should connect to materials). 
    FBPropertyListDeformer          Deformers;              //!< <b>List:</b> Deformers (Skeleton Deformer or Point Cache Deformer).
    FBPropertyBool                  Icon3D;                 //!< <b>Read Write Property:</b> Is model a 3D icon?
    FBPropertyBool                  SoftSelected;           //!< <b>Read Write Property:</b> Is model Soft selected?
    FBPropertyBool                  IsDeformable;           //!< <b>Read Only Property:</b> Is model deformable?
    FBPropertyBool                  IsConstrained;          //!< <b>Read Only Property:</b> Is model constrained?
    FBPropertyBool                  SkeletonDeformable;     //!< <b>Read Write Property:</b> Model skeleton deformable.     Not Savable
    FBPropertyBool                  BlendShapeDeformable;   //!< <b>Read Write Property:</b> Model blend-shape deformable.   Not Savable 
    FBPropertyBool                  ConstrainDeformable;    //!< <b>Read Write Property:</b> Model constraint deformable.   Not Savable 
    FBPropertyBool                  PointCacheDeformable;   //!< <b>Read Write Property:</b> Model point cache deformable.  Not Savable 
    FBPropertyBool                  PointCacheRecord;       //!< <b>Read Write Property:</b> Record Point Cache for model?  Not Savable 
    FBPropertyModel                 Parent;                 //!< <b>Read Write Property:</b> Parent model.
    FBPropertyModel                 LookAt;                 //!< <b>Read Write Property:</b> Look at model (interest point).
    FBPropertyModel                 UpVector;               //!< <b>Read Write Property:</b> UpVector model.
    FBPropertyGeometry              Geometry;               //!< <b>Read Write Property:</b> Geometry for the model.
    FBPropertyInt                   GeometryUpdateId;       //!< <b>Read Only Property:</b> model geometry (vertex data) related update id. 
    FBPropertyMesh                  TessellatedMesh;        //!< <b>Read Only Property:</b> Tessellated Mesh for the model.
    FBPropertyModelVertexData       ModelVertexData;        //!< <b>Read Only Property:</b> ModelVertexData for the model.
    FBPropertyCluster               Cluster;                //!< <b>Read Only Property:</b> Link Cluster for the model.
    FBPropertyScene                 Scene;                  //!< <b>Read Only Property:</b> Scene containing the model.
    FBPropertyModelShadingMode      ShadingMode;            //!< <b>Read Write Property:</b> Shading mode for the model.
    FBPropertyAnimationNode         AnimationNode;          //!< <b>Read Only Property:</b> Animation node of the model.

    FBPropertyModelRotationOrder    RotationOrder;          //!< <b>Read Write Property:</b> Rotation order.

    // Limits
    FBPropertyBool                  RotationSpaceForLimitOnly; //!< <b>Read Write Property:</b> Apply Post Rotation Matrix only for Limits?
    FBPropertyBool                  RotationActive;         //!< <b>Read Write Property:</b> Is model using Rotation Limits?
    FBPropertyVector3d              PreRotation;            //!< <b>Read Write Property:</b> Pre Rotation (considered if RotationActive is true)
    FBPropertyVector3d              PostRotation;           //!< <b>Read Write Property:</b> Post Rotation (considered if RotationActive is true)
    FBPropertyVector3d              RotationMin;            //!< <b>Read Write Property:</b> Min Rotation Limit (considered if RotationActive is true)
    FBPropertyVector3d              RotationMax;            //!< <b>Read Write Property:</b> Max Rotation Limit (considered if RotationActive is true)
    FBPropertyBool                  RotationMinX;           //!< <b>Read Write Property:</b> Is model using Minimum Rotation Limits On X?
    FBPropertyBool                  RotationMinY;           //!< <b>Read Write Property:</b> Is model using Minimum Rotation Limits On Y?
    FBPropertyBool                  RotationMinZ;           //!< <b>Read Write Property:</b> Is model using Minimum Rotation Limits On Z?
    FBPropertyBool                  RotationMaxX;           //!< <b>Read Write Property:</b> Is model using Maximum Rotation Limits On X?
    FBPropertyBool                  RotationMaxY;           //!< <b>Read Write Property:</b> Is model using Maximum Rotation Limits On Y?
    FBPropertyBool                  RotationMaxZ;           //!< <b>Read Write Property:</b> Is model using Maximum Rotation Limits On Z?

    FBPropertyBool                  TranslationActive;      //!< <b>Read Write Property:</b> Is model using Translation Limits?
    FBPropertyVector3d              TranslationMin;         //!< <b>Read Write Property:</b> Translation Limit Min.
    FBPropertyVector3d              TranslationMax;         //!< <b>Read Write Property:</b> Translation Limit Max.
    FBPropertyBool                  TranslationMinX;        //!< <b>Read Write Property:</b> Is model using Translation Limits on Min X.
    FBPropertyBool                  TranslationMinY;        //!< <b>Read Write Property:</b> Is model using Translation Limits on Min Y.
    FBPropertyBool                  TranslationMinZ;        //!< <b>Read Write Property:</b> Is model using Translation Limits on Min Z.
    FBPropertyBool                  TranslationMaxX;        //!< <b>Read Write Property:</b> Is model using Translation Limits on Max X.
    FBPropertyBool                  TranslationMaxY;        //!< <b>Read Write Property:</b> Is model using Translation Limits on Max Y.    
    FBPropertyBool                  TranslationMaxZ;        //!< <b>Read Write Property:</b> Is model using Translation Limits on Max Z.    

    // Animatable
    FBPropertyAnimatableBool		Visibility;             //!< <b>Read Write Property:</b> Visibility of model. This can be overridden by the 'Show' property.
    FBPropertyBool                  VisibilityInheritance;  //!< <b>Read Write Property:</b>  //!< When this value is set to \c True the Visibility of this model is also applied to all its descendants
    FBPropertyAnimatableVector3d    Translation;            //!< <b>Read Write Property:</b> Lcl translation.
    FBPropertyAnimatableVector3d    Rotation;               //!< <b>Read Write Property:</b> Lcl rotation.
    FBPropertyAnimatableVector3d    Scaling;                //!< <b>Read Write Property:</b> Lcl scaling.

    FBPropertyVector3d              GeometricTranslation;   //!< <b>Read Write Property:</b> Geometric translation.
    FBPropertyVector3d              GeometricRotation;      //!< <b>Read Write Property:</b> Geometric rotation.
    FBPropertyVector3d              GeometricScaling;       //!< <b>Read Write Property:</b> Geometric scaling.

    FBPropertyBool                  QuaternionInterpolate;  //!< <b>Read Write Property:</b> Use quaternion interpolation.

    FBPropertyBool                  Show;                   //!< <b>Read Write Property:</b> Indicate if the viewer should show the object, according to its visibility value. This has a default value of 'false'.
    FBPropertyBool                  Pickable;               //!< <b>Read Write Property:</b> Indicate if a model can be picked in the viewer. This has a default value of 'true'.
    FBPropertyBool                  Transformable;          //!< <b>Read Write Property:</b> Indicate if a model can be transformable in the viewer. This has a default value of 'true'.
    FBPropertyColor                 UniqueColorId;          //!< <b> Read Only Property:</b> Unique Color Id for color based viewer picking. Color channel values are in the range [0, 1] with 1.0/255 precision.  

    FBPropertyBool					PrimaryVisibility;	    //!< <b>Read Write Property:</b> Control the geometry render state. Geometry can still cast shadows even if this is turned off.
    FBPropertyBool					CastsShadows;		    //!< <b>Read Write Property:</b> If true, the geometry will produce shadows.
    FBPropertyBool					ReceiveShadows; 	    //!< <b>Read Write Property:</b> If true, the geometry will receive shadows.

    /** Clone the model.
    *    This will duplicate the current model. 
    *    \return Newly created model.
    */
    virtual FBModel* Clone();

    /** Set a matrix for the model.
    *   \param  pMatrix         Information to use to set the model's matrix.
    *   \param  pWhat           Type of matrix to set (default=transformation).
    *   \param  pGlobalInfo     \b true if it is GlobalInfo, \b false if Local (default=true).
    *   \param  pPushUndo       \b true if this operation is undoable, don't push undo in non UI thread.
    *   \param  pEvaluateInfo   EvaluateInfo, Take Display if none specified
    */
    void SetMatrix(FBMatrix pMatrix, FBModelTransformationType pWhat=kModelTransformation,    bool pGlobalInfo=true, bool pPushUndo = false, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get a matrix from the model.
    *   \param  pWhat           Type of information requested (default=transformation).
    *   \param  pGlobalInfo     \b true if it is GlobalInfo, \b false if Local (default=true).
    *   \retval pMatrix         Matrix to fill with requested information.
    *   \param  pEvaluateInfo   EvaluateInfo, Take Display if none specified.
    */
    void GetMatrix(FBMatrix &pMatrix, FBModelTransformationType pWhat=kModelTransformation,    bool pGlobalInfo=true, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Set a vector for the model.
    *   \param  pVector         Vector to use to set values.
    *   \param  pWhat           Type of information to set (default=translation, inverses not supported).
    *   \param  pGlobalInfo     \b true if it is GlobalInfo, \b false if Local (default=true).
    *   \param  pPushUndo       \b true if this operation is undoable, don't push undo in non UI thread.
    *   \param  pEvaluateInfo   EvaluateInfo, Take Display if none specified
    */
    void SetVector(FBVector3d pVector, FBModelTransformationType pWhat=kModelTranslation,    bool pGlobalInfo=true, bool pPushUndo = false, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Get a vector from the model.
    *   \param    pWhat           Type of information requested (default=translation, inverses not supported).
    *   \param    pGlobalInfo     \b true if it is GlobalInfo, \b false if Local (default=true).
    *   \param    pEvaluateInfo   EvaluateInfo, Take Display if none specified
    *   \retval   pVector         Vector to fill with requested values.
    */
    void GetVector(FBVector3d &pVector,    FBModelTransformationType pWhat=kModelTranslation,    bool pGlobalInfo=true, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Is the model's evaluation task result ready.
    *   \param    pWhat            Type of evaluation task.
    *   \param    pEvaluateInfo    EvaluateInfo, Take Display if none specified
    *   \retval   \b true if the evaluation task result is ready in place.
    */
    bool IsEvaluationReady(FBModelEvaluationTaskType pWhat, FBEvaluateInfo* pEvaluateInfo=NULL) const;

    /** Convert Rotation Matrix to Euler Vector based on model's rotation order.
    *   \param    pMatrix		Matrix to convert.
    *   \retval   pRotation		Resulting euler vector, whose angles are stored in [X,Y,Z] order.
    */
    void MatrixToRotation(FBRVector &pRotation, const FBMatrix &pMatrix);

    /** Convert Euler Vector to Rotation Matrix based on model's rotation order.
    *   \param    pRotation	Object space rotation vector to convert, whose angles are stored in [X,Y,Z] order.
    *   \retval   pMatrix	Resulting rotation matrix.
    */
    void RotationToMatrix( FBMatrix &pMatrix, const FBRVector &pRotation);

    /** Convert local matrix to object space vector.
    *   \param    pLM	Local rotation matrix to convert
    *   \retval   pDof	Resulting object space vector.
    *	\note	Use this function when you want to convert local rotation to euler 
    *			with proper pre/post transformation and rotation order applied from this model.
    */
    void LRMToDof(FBRVector &pDof, const FBMatrix &pLM);

    /** Convert object space vector to local matrix
    *   \param    pDof	Vector to convert
    *   \retval   pLM	Resulting local rotation matrix.
    *	\note	Use this function when you want to convert euler to local rotation
    *			with proper pre/post transformation and rotation order applied from this model.
    */
    void DofToLRM(FBMatrix &pLM, const FBRVector &pDof);

    /** Set the position in the schematic view for the model.
    *   \param    pX    X position to set.
    *   \param    pY    Y position to set.
    */
    void SetSchematicPosition(int pX,int pY);

    /** Set the position in the schematic view for the model.
    *   \param    pVector2d    Position to set.
    */
    void SetSchematicPosition(FBVector2d pVector2d);

    /** Get the position in the schematic view for the model.
    *   \return    Current position for the model.
    */
    FBVector2d GetSchematicPosition();

    /** Get the bounding box of the model.
    *   Note. for deformable model, this function will provide the approximated (larger than the smallest) bounding box for performance consideration. 
    *   \retval pMin    Minimum value of the bounding box.
    *   \retval pMax    Maximum value of the bounding box.
    */
    void GetBoundingBox( FBVector3d& pMin, FBVector3d& pMax );

    /** If the model is visible. 
    *	Note. this query will consider self Visibility property, plus parent node/set Visibility. 
    *   The visibility of a model is affected by 4 parameters: 
    *   1. The model's own visibility
    *   2. The model's parent's visibility (if any)
    *   3. The visibility of the set to which model belongs (if any)
    *   4. VisibilityInheritance of the model
    *	\param pEvaluateInfo	evaluate info, 
    *	\return true if visible for the given evaluate info.
    */
    bool IsVisible(FBEvaluateInfo* pEvaluateInfo = NULL);

    /** Get Model Culling Mode.
    *   \return Model Culling Mode.
    */
    FBModelCullingMode GetCullingMode() const;

    /** Set Model Cullin Mode.
    *   \param pCullingMode Culling Mode to be set.
    */
    void SetCullingMode(FBModelCullingMode pCullingMode);

    /** Force Always Evaluate.
    *   In some case, MoBu kernel perform optimization by skipping certain evaluation tasks.
    *   This function stop skipping for this model.
    */
    void ForceAlwaysEvaluate();

    /** Return Force Always Evaluate status.
    */
    bool IsForceAlwaysEvaluate();

    /** Acquire no frustum culling request. 
    *   \return Current no frustum culling request count after function call.
    */
    int NoFrustumCullingRequire();

    /** Release no frustum culling request. 
    *   \return Current no frustum culling request count after function call.
    */
    int NoFrustumCullingRelease();

    /** Get the current Frustum Culling Status.
    *   \return \b True if model don't use frustum culling currently.
    */
    bool UseFrustumCulling();

    /** Function to overload to handle custom display
    *    \return True is this model class has custom display function ModelDisplay
    */
    virtual bool HasCustomDisplay() { return false; }

    /** Custom display function, called when HasCustomDisplay returns true;
    *    \param    pCamera                  Current camera for display.
    *    \param    pShadingMode             Shading mode to render see FBModelShadingMode.
    *    \param    pRenderPass              Actual rendering pass, see FBModelRenderPass.
    *    \param    pPickingAreaWidth        Width of picking area.
    *    \param    pPickingAreaHeight       Height of picking area.
    */
    virtual void CustomModelDisplay( FBCamera* pCamera, FBModelShadingMode pShadingMode, FBModelRenderPass pRenderPass, float pPickingAreaWidth, float pPickingAreaHeight) {}

    /** Custom picking for selection, called when HasCustomDisplay returns true;
    *    \param    pNbHits                 Number of hits.
    *    \param    pSelectBuffer           OpenGL hit buffer.
    *    \param    pCamera                 Current camera for rendering.
    *    \param    pMouseX                 Mouse X position.
    *    \param    pMouseY                 Mouse Y position.
    *    \param    pLocalRaySrc            Local picking ray source.
    *    \param    pLocalRayDir            Local picking ray direction.
    *    \param    pWorldRaySrc            World coordinate picking ray source.
    *    \param    pWorldRayDir            World coordinate picking ray direction.
    *    \param    pGlobalInverseMatrix    Inverse transformation matrix of the model.
    *    \param    pOutPickedPoint         Picked position.
    */
    virtual bool CustomModelPicking(    int pNbHits, unsigned int *pSelectBuffer, FBCamera* pCamera, 
        int pMouseX,int pMouseY,
        FBTVector* pLocalRaySrc, FBTVector* pLocalRayDir,
        FBTVector* pWorldRaySrc, FBTVector* pWorldRayDir,
        FBMatrix* pGlobalInverseMatrix,
        FBTVector* pOutPickedPoint)    { return false; }

    /** Determines the first intersection point's position and normal between ray and model surface  
    *   \remarks All coordinates specified in local model space, override this function in subclass if custom intersection method is desired. See $(INSTALLDIR)/OpenReality/Samples/miscellaneous/ormodel_template ORSDK sample project for example. 
    *   \param pRayOrigin Specifies origin of the view ray.
    *   \param pRayEnd Specifies end of the view ray.
    *   \param pIntersectPos return the first intersection point's position;
    *   \param pIntersectNormal return the first intersection point's normal;
    *   \return Returns true if at least one intersects with ray, and false if otherwise.
    */
    virtual bool ClosestRayIntersection(const FBTVector& pRayOrigin, const FBTVector& pRayEnd, FBTVector& pIntersectPos, FBNormal& pIntersectNormal);

    /**Get the list of the points selection state.
    *    \return Pointer to the list of the points selection state.
    */
    unsigned char* GetSelectedPoints();

    /**Get the number of selected points in the model.
    *    \return Number of selected points.
    */
    int GetSelectedPointsCount();

    /**
    * \name Additional Unique Color ID management.
    *
    *	To support multiple sub items per model/geo selection & picking in easy selection 
    *   mode using custom rendering routines. see OpenRealitySDK/Samples/miscellaneous/marker_template for example.
    *
    * @{
    */

    /** Request additional Unique color IDs.
    *	\param pCount  User should note that Unique Color ID resource is limited (only 24 bits), 
    *                   hence should avoid to use unnecessary large number.
    *	\return	True if Unique ColorId resource is available.
    */
    bool SetAdditionalUniqueColorIDCount(unsigned int pCount);

    /** Get additional unique color count.
    *	\return Additional Unique Color Count.
    */
    unsigned int GetAdditionalUniqueColorIDCount() const;

    /** Get Additional Unique Color Id.
    *	\param pIndex the requested unique color id index, can't be larger than GetAdditionalColorIDCount()
    *	\return Additional Unique ColorId.
    */
    FBColor GetAdditionalUniqueColorID(unsigned int pIndex) const;

    /*
    * @}
    */

    /**    Store and Retrieve function that can be overloaded.
    *    \param    pFbxObject    FBX Object that is used to communicate I/O operations.
    *    \param    pStoreWhat    Which attributes are currently stored/retrieved.
    */
    virtual bool FbxStore(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat);
    virtual bool FbxRetrieve(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat);

    /** Setup Shape Properties.
    *    Normally this function is called automatically at the next global 
    *    synchronization point after the geometry has been updated. 
    *    However you must call it explicitly to access
    *   the shape properties immediately after shapes adding/removing before
    *   next global synchronization point. 
    */    
    void SetupPropertiesForShapes();

    /** Ray cast test 
    *    \param    pCamera    	Camera to use for casting.
    *    \param    pMouseX    	Mouse X position.
    *    \param    pMouseY    	Mouse Y position.
    *    \param    pHitPosition	Ray cast position on the object.
    *    \param    pHitNormal	Normal at the ray cast position on the object.
    *	\return true if it hit the meshes, hit would contains the precise position & normal.
    */
    bool RayCast(FBCamera* pCamera, int pMouseX, int pMouseY, FBVector3d& pHitPosition,  FBVector3d& pHitNormal);

    /** Returns the class type inherited by the class of an object, for example: 'Model'.
    */
    virtual const char*    FbxGetObjectType() override;

    /** Returns the class sub type inherited by the class of an object, for example: 'Default', 'Mesh'.
    */
    virtual const char*    FbxGetObjectSubType() override;

    /**    Set a matrix for the model.
    *   \param  pMatrix         Information to use to set the model's matrix.
    *   \param  pWhat           Type of matrix to set (default=transformation).
    *   \param  pGlobalInfo     \b true if it is GlobalInfo, \b false if Local (default=true).
    *   \param  pPushUndo       \b true if this operation is undoable, don't push undo in non UI thread.
    *   \param  pEvaluateInfo   EvaluateInfo, Take Display if none specified
    *	\param	pPrecision      Indicate the precision level, used when calculating the threshold value for gimble lock. 16 * pow(10.0, -10)) is the new default value since Mobu 2016, 16 * pow(10.0, -6)) is old default value before then.
    */   
    void SetMatrixWithPrecision(FBMatrix pMatrix, FBModelTransformationType pWhat=kModelTransformation,    bool pGlobalInfo=true, bool pPushUndo = false, 
        FBEvaluateInfo* pEvaluateInfo=NULL, double pPrecision = FBMat2EulerDegenerateForPrecision10);


    /** Computes the global transform matrices between this model and all its children (all levels).
    *	The hierarchy world matrix for a model is represented as a global transform matrix
    *	applied on an arbitrary root hierarchy node (this model for instance), considered as the world reference. 
    *   \param  pMatricesArray				The matrix array (memory already allocated) to fill in with the hierarchy world matrix of all the model's children models
    *   \param  pMatricesArrayCount			The size of the matrix array
    *   \retval pHiercharyTraverserType		The hierarchy traverser type
    *   \param  pEvaluateInfo				EvaluateInfo, Take Display if none specified.
    *	\retval Number of matrices filled in the array. The value may be different than pMatricesArrayCount if the number of children models is less than the size of the matrix array.
    */
    unsigned int GetHierarchyWorldMatrices(FBMatrix* pMatricesArray, unsigned int pMatricesArrayCount, FBModelHiercharyTraverserType pHiercharyTraverserType, FBEvaluateInfo* pEvaluateInfo=NULL);

    /** Collapse the model in the schematic view.
    */
    void CollapseInSchematic();

    /** Expand the model in the schematic view.
    */
    void ExpandInSchematic();

    /** Returns if the model is collapsed or not (expanded) in the schematic view.
    *	\return true if the model is collapsed in the schematic view, false if it is expanded.
    */
    bool IsCollapsedInSchematic() const;
	
	/** Callback for component selection in custom FBModel.
	*	\param pAction	The selection mode the current viewport is in.
	*	\return User defined returned value. Must return true if the user wants the system to proceed with the FBSelectionAction or false if the user doesn't want that action to be done. For example, if the specified function returns false when a "kFBManipulatorAddAll" is specified, all the components for the model will not be added to the current list of selected object. Returning true will allow MotionBuilder to add them.
	*/
	virtual bool ManipulatorNotify(FBSelectionAction pAction) { return true; }
};

//! typedef class FBSDK_DLL
typedef class FBSDK_DLL FBArrayTemplate<FBModel*> FBModelList;

/**	Create a FBModelList object.
*	This is to get around memory management issues when mixing debug and release runtime
*   libraries on Windows. By using the FBCreateModelList/FBDestroyModelList
*   duo of functions, you ensure that the memory used in the array is allocated,
*   reallocated and freed in the same memory pool.
*/
FBSDK_DLL FBModelList* FBCreateModelList();

/** Delete a FBModelList object.
*   \param  pModelList  pointer to the object created with a call to FBCreateModelList().
*/
FBSDK_DLL void FBDestroyModelList( FBModelList* pModelList );

/**	Find a model in the scene by its label name.
*   Searches the scene for a model, based on the model's label name.
*   Label name is "NameSpaceName:ObjectName". also known as "PrefixName::ObjectName"
*   Full name is "GroupName::NameSpaceName:ObjectName".
*   \param	pModelLabelName	LabelName of model to search for. Specify it with schema like "NameSpaceName:ObjectName",or "ObjectName" if no NameSpaceName.
*   \return	A handle onto the model with Label name matching, returns 
*           NULL if no model was found by the search.
*/
FBSDK_DLL FBModel* FBFindModelByLabelName( const char* pModelLabelName );

/**	Find a model in the scene by its unique color id. 
*   A model could have a single unique ColorID, but SDK plugin user could request 
*   additional ColorID per model to support multi sub items picking. see FBModel::SetAdditionalUniqueColorIDCount().
*   \param	pColor  Color channel values are in range of [0,1] with precision 1.0/255    
*   \param  pSubItemIndex Pass out SubImtem index value if not null.  In pyfbsdk no such parameter.
*   \return	A handle onto the model with unique color id matching, returns NULL if no model was found by the search. In pyfbsdk return tuple [model, subItemIndex]
*/
FBSDK_DLL FBModel* FBFindModelByUniqueColorId( const FBColor& pColor, int* pSubItemIndex = NULL );

/**	Load a model.
*	\param	pModelName		Name of primitive model to load.
*	\return	A handle onto the model that was loaded, returns NULL if no model was found.
*/
FBSDK_DLL FBModel* FBLoadFbxPrimitivesModel( const char* pModelName );

/**	Find all models of a certain type in the scene.
*	Searches recursively from a root model for models of a certain type,
*	and adds them to a list of models.
*	\retval	pList		List to add found models to.
*	\param	pTypeInfo	Model type to look for.
*	\param	pParent		Root model to look from (default=NULL(root)).
*/
FBSDK_DLL void FBFindModelsOfType( FBModelList& pList, int pTypeInfo, FBModel* pParent=NULL );

/**	Find all models that are selected (if \p pSelected is true)
*	Searches recursively from a root model for models that are selected,
*	and adds them to a list of models.
*	\retval	pList		List to add found models to.
*	\param	pParent		Root model to look from (default=NULL(root)).
*	\param	pSelected	true to find selected models, false to find unselected models(default=true).
*   \param  pSortBySelectOrder true to sort the result by selection order, first selected model in the first part of the list; 
*							   false to sort the result by scene graph order
*/
FBSDK_DLL void FBGetSelectedModels( FBModelList& pList, FBModel* pParent=NULL, bool pSelected=true, bool pSortBySelectOrder = false );

/**	Call begin change to all models (need to be closed).
*	Useful for selection of many models that can trigger many related callbacks)
*/
FBSDK_DLL void FBBeginChangeAllModels();

/**	Call end change to all models (should be first open).
*/
FBSDK_DLL void FBEndChangeAllModels();

/**    FBModelTransactionBegin.
*    This set of functions speeds up the process of batch operations on models.
*/
FBSDK_DLL void FBModelTransactionBegin();

/**    FBModelTransactionEnd.
*    This set of functions speeds up the process of batch operations on models.
*/
FBSDK_DLL void FBModelTransactionEnd();


////////////////////////////////////////////////////////////////////////////////////
// FBModelNull
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModelNull);

//! Null object class.
class FBSDK_DLL FBModelNull : public FBModel {
    __FBClassDeclare( FBModelNull,FBModel );
public:
    /**    Constructor.
    *    \param    pName        Name of null.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBModelNull(const char* pName, HIObject pObject=NULL);

    FBPropertyDouble    Size;    //!< <b>Read Write Property:</b> Size (not related to scaling).

    /**    Store and Retrieve function that can be overloaded.
    *    \param    pFbxObject    FBX Object that is used to communicate I/O operations.
    *    \param    pStoreWhat    Which attributes are currently stored/retrieved.
    */
    virtual bool FbxStore(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat);
    virtual bool FbxRetrieve(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat);

    /** Returns the class type inherited by the class of an object, for example: 'Model'.
    */
    virtual const char* FbxGetObjectType() override;

    /** Returns the class sub type inherited by the class of an object, for example: 'Default', 'Mesh'.
    */
    virtual const char* FbxGetObjectSubType() override;
};

////////////////////////////////////////////////////////////////////////////////////
// FBModelRoot
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModelRoot);

//! Root object class.
class FBSDK_DLL FBModelRoot : public FBModel {
    __FBClassDeclare( FBModelRoot,FBModel );
public:
    /**    Constructor.
    *    \param    pName        Name of root.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBModelRoot(const char* pName, HIObject pObject=NULL);

    FBPropertyDouble    Size;    //!< <b>Read Write Property:</b> Size (not related to scaling).
};

////////////////////////////////////////////////////////////////////////////////////
// FBModelMarker
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModelMarker);

//! Resolution of marker mesh sphere and capsule (Quality).
enum FBMarkerResolutionLevel
{
    kFBMarkerLowResolution,        //!< Lowest resolution.
    kFBMarkerMediumResolution,    //!< Medium resolution.
    kFBMarkerHighResolution        //!< Highest resolution.
};

//! Look of the marker
enum FBMarkerLook
{
    kFBMarkerLookCube,            //!< Cube.
    kFBMarkerLookHardCross,        //!< Thick cross.
    kFBMarkerLookLightCross,    //!< Wireframe cross.
    kFBMarkerLookSphere,        //!< Sphere.
    kFBMarkerLookCapsule,        //!< Capsule.
    kFBMarkerLookSquare,        //!< Square.
    kFBMarkerLookCircle,        //!< Circle.
    kFBMarkerLookBone,            //!< Bone.
    kFBMarkerLookStick,            //!< Box with a sphere on one end.
    kFBMarkerLookBox,            //!< Box.
    kFBMarkerLookNone,            //!< None.
    kFBMarkerLookRigidGoal,            //!< Rigid goal.
    kFBMarkerLookRotationGoal,            //!< Rotation goal.
    kFBMarkerLookAimRollGoal,            //!< Aim & Roll goal.
};

//! Type of the marker
enum FBMarkerType
{
    kFBMarkerTypeStandard,        //!< Standard.
    kFBMarkerTypeOptical,        //!< Optical.
    kFBMarkerTypeFKEffector,    //!< FK effector.
    kFBMarkerTypeIKEffector        //!< IK effector.
};

FB_DEFINE_ENUM( FBSDK_DLL, MarkerResolutionLevel );
FB_DEFINE_ENUM( FBSDK_DLL, MarkerLook );
FB_DEFINE_ENUM( FBSDK_DLL, MarkerType );

//! Model marker class.
class FBSDK_DLL FBModelMarker : public FBModel {
    __FBClassDeclare( FBModelMarker,FBModel );
public:
    /**    Constructor.
    *    \param    pName        Name of model marker. If pObject is not NULL, pName will be ignored.
    *    \param    pObject        For internal use only (default=NULL).
    */
    FBModelMarker(const char* pName, HIObject pObject=NULL);

    FBPropertyDouble    Size;    //!< <b>Read Write Property:</b> Size (not related to scaling).
    FBPropertyDouble    Length;    //!< <b>Read Write Property:</b> Length for capsule (not related to scaling).
    FBPropertyMarkerResolutionLevel ResLevel; //!< <b>Read Write Property:</b> Resolution level of model marker.
    FBPropertyMarkerLook Look;    //!< <b>Read Write Property:</b> Look of model marker.
    FBPropertyMarkerType Type;    //!< <b>Read Write Property:</b> Type of model marker.
    FBPropertyColor        Color;    //!< <b>Read Write Property:</b> Color of model marker.
    FBPropertyVector3d  IKPivot;   //!< <b>Read Write Property:</b> marker Pivot Offset.
    FBPropertyBool      IKSync;    //!< <b>Read Write Property:</b> Must sync with IK if true.

    /**    Used when shading the controlset
    *    \param    pValue            Value between 0 and 100.  Normally the controlset opacity value is used.
    */
    void SetFKOpacity(double pValue);

    /**    Store and Retrieve function that can be overloaded.
    *    \param    pFbxObject    FBX Object that is used to communicate I/O operations.
    *    \param    pStoreWhat    Which attributes are currently stored/retrieved.
    */
    virtual bool FbxStore(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat);
    virtual bool FbxRetrieve(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat);

    /** Returns the class type inherited by the class of an object, for example: 'Model'.
    */
    virtual const char* FbxGetObjectType() override;

    /** Returns the class sub type inherited by the class of an object, for example: 'Default', 'Mesh'.
    */
    virtual const char* FbxGetObjectSubType() override;
};


////////////////////////////////////////////////////////////////////////////////////
// FBModelSkeleton
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModelSkeleton);

//! Look of the skeleton.
enum FBSkeletonLook
{
	kFBSkeletonLookBone,			//!< Bone.
	kFBSkeletonLookCube,			//!< Cube.
	kFBSkeletonLookHardCross,		//!< Thick cross.
	kFBSkeletonLookLightCross,		//!< Wireframe cross.
	kFBSkeletonLookSphere,			//!< Sphere.
	kFBSkeletonLookCapsule,			//!< Capsule.
	kFBSkeletonLookBox,				//!< Box.
	kFBSkeletonLookCircle,			//!< Circle.
	kFBSkeletonLookSquare,			//!< Square.
	kFBSkeletonLookStick,			//!< Box with a sphere on one end.
};

//! Resolution of skeleton sphere, capsule and stick (Quality).
enum FBSkeletonResolutionLevel
{
	kFBSkeletonLowResolution,		//!< Lowest resolution.
	kFBSkeletonMediumResolution,	//!< Medium resolution.
	kFBSkeletonHighResolution		//!< Highest resolution.
};

FB_DEFINE_ENUM( FBSDK_DLL, SkeletonLook );
FB_DEFINE_ENUM( FBSDK_DLL, SkeletonResolutionLevel );

//! Root object class.
class FBSDK_DLL FBModelSkeleton : public FBModel {
    __FBClassDeclare( FBModelSkeleton,FBModel );
public:
    /**    Constructor.
    *    \param    pName        Name of skeleton.
    *    \param    pObject      For internal use only(default=NULL).
    */
    FBModelSkeleton(const char* pName, HIObject pObject=NULL);

    FBPropertyDouble    				Size;    					//!< <b>Read Write Property:</b> Size (not related to scaling).
    FBPropertyColor        				Color;    					//!< <b>Read Write Property:</b> Color of skeleton node.
    FBPropertyBool        				DrawLink;   				//!< <b>Read Write Property:</b> Whether to draw link to parent node or not.
	
	FBPropertySkeletonLook				Look;						//!< <b>Read Write Property:</b> Look of skeleton node.
	FBPropertySkeletonResolutionLevel	Resolution;					//!< <b>Read Write Property:</b> Resolution of skeleton node. (Note: Only effective when the look is set to: Sphere, Capsule or Stick)
	FBPropertyDouble					Length;						//!< <b>Read Write Property:</b> Length of skeleton node. (Note: Only effective when the look is set to: Capsule)
	FBPropertyBool						LinkFollowGeometryOffset;	//!< <b>Read Write Property:</b> Whether link to parent node must follow skeleton node or not, when skeleton node has a geometry offset.
	FBPropertyBool						PreserveLinkEndPosition;	//!< <b>Read Write Property:</b> Whether skeleton node must preserve its links' end position to children nodes, when skeleton node has a geometry offset. (Note: Only effective when the look is set to: Bone, Box or Stick)

    /**    Return the list of skin model associated with this Skeleton(Bone), which could be the deformable skins 
    *   connected via cluster, or non deformable skins which are parented directly under this bone.
    *    \param    pSkinModelList        List to be appended with skin models (with no duplicated items).
    */
    void GetSkinModelList(FBModelList& pSkinModelList); 
};


////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListModelSkeleton
////////////////////////////////////////////////////////////////////////////////////
FB_DEFINE_LIST( FBSDK_DLL, ModelSkeleton );
FB_FORWARD( FBPropertyListModelSkeleton );

//! \b PropertyList: ModelSkeleton.
class FBSDK_DLL FBPropertyListModelSkeleton : public FBPropertyListComponent
{
public:
    FBPropertyListModelSkeleton();
    /**	Get the ModelSkeleton at \e pIndex.
    *	\param	pIndex	Index of ModelSkeleton to get.
    *	\return ModelSkeleton at \e pIndex.
    */
    FBModelSkeleton* operator[](int pIndex);
};


////////////////////////////////////////////////////////////////////////////////////
// FBModelCube
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModelCube );

//! Cube model class.
class FBSDK_DLL FBModelCube : public FBModel {
    __FBClassDeclare( FBModelCube, FBModel );
public:
    /**    Constructor.
    *    \param    pName        Name of cube.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBModelCube(const char* pName, HIObject pObject=NULL);
};

////////////////////////////////////////////////////////////////////////////////////
// FBModelPlane
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModelPlane );

//! Plane model class.
class FBSDK_DLL FBModelPlane : public FBModel {
    __FBClassDeclare( FBModelPlane, FBModel );
public:
    /**    Constructor.
    *    \param    pName        Name of Plane.
    *    \param    pObject      For internal use only(default=NULL).
    */
    FBModelPlane(const char* pName, HIObject pObject=NULL);
};


////////////////////////////////////////////////////////////////////////////////////
// FBCluster
////////////////////////////////////////////////////////////////////////////////////
//! Different clustering modes.
enum FBClusterMode    {
    kFBClusterNormalize,            //!< Normalize (values between 0.0 and 1.0 )
    kFBClusterAdditive,             //!< Add the values together.
    kFBClusterTotal100              //!< The balanced values will add up to 100 percent.
};
FB_DEFINE_ENUM( FBSDK_DLL, ClusterMode );

__FB_FORWARD( FBCluster );

/** Weighting interface for meshes.
*    \warning    This class is experimental.
*/
class FBSDK_DLL FBCluster : public FBComponent {
    __FBClassDeclare( FBCluster,FBComponent );

protected:
    /** Constructor. protected access, call FBModel::Cluster instead.
    *    \param    pModel    Parent model in question.
    */
    FBCluster(FBModel* pModel);
    friend class DataFBModel;

public:

    //--- Cluster-level operations
    /**    Begin cluster definition.
    *    \param    pIndex        Link index.
    *    \return    Index of last item(default=-1).
    */
    int ClusterBegin(int pIndex = -1);

    /**    End cluster definition.
    *    \return 0, (Not implemented).
    */
    int ClusterEnd();

    //--- Link-level operations
    /**    Set the name of a link.
    *    \param    pLinkNumber    Number value of link to name.
    *    \param    pName        Name of the link.
    */
    void        LinkSetName(const char *pName, int pLinkNumber);
    /**    Get the name of a link.
    *    \param    pLinkNumber    Number value of link to get name from.
    *    \return Name of link number \p pLinkNumber.
    */
    const char* LinkGetName(int pLinkNumber);
    /**    Remove a link.
    *    \param    pLinkNumber        Number value of link to rename.
    */
    void        LinkRemove(int pLinkNumber);
    /**    Get number of links.
    *    \return Number of links.
    */
    int         LinkGetCount();
    /**    Set model to a link.
    *    \param    pModel    Model to set.
    */
    void        LinkSetModel(FBModel* pModel);
    /**    Get model from a link.
    *    \param    pLinkNumber        Number value of link to get model from.
    *    \return Model at link number \p pLinkNumber.
    */
    FBModel*    LinkGetModel(int pLinkNumber);
    /**    Get model associated with link.
    *    \param    pLinkNumber        Number value of link to get associated model from.
    *    \return Model associated to link number \p pLinkNumber.
    */
    FBModel*    LinkGetAssociateModel(int pLinkNumber);
    /**    Remove all unused links.
    *    \param    pThreshold    Weight value under which links are considered unused (default=-1).
    */
    void        LinkClearUnused( double pThreshold = -1.0 );
    /**    Link at current vertex.
    *    \param    pLinkIndex        Index of link to add vertex to.
    *    \param    pPointIndex        Index of vertex to add.
    */
    void        LinkSetCurrentVertex(int pLinkIndex,int pPointIndex);
    /**    Get current vertex at link.
    *    \param    pIndex    Index of link to get vertex from.
    *    \return Index value of the current vertex associated to link at index number \p pIndex
    */
    int            LinkGetVertexIndex(int pIndex);

    //--- Vertex level operations.
    /**    Set transform of a cluster set.
    *    \param    pPosition    Position transform.
    *    \param    pRotation    Rotation transform.
    *    \param    pScaling    Scaling transform.
    */
    void        VertexSetTransform(FBVector3d pPosition,FBVector3d pRotation, FBVector3d pScaling);
    /**    Get transform  of a cluster set.
    *    \retval    pPosition    Position transform.
    *    \retval    pRotation    Rotation transform.
    *    \retval    pScaling    Scaling transform.
    */
    void        VertexGetTransform(FBVector3d& pPosition,FBVector3d& pRotation, FBVector3d& pScaling);
    /**    Add a vertex to a cluster.
    *    \param    pVertexIndex    Index of vertex to add.
    *    \param    pWeight            Weight to give to vertex.
    */
    void        VertexAdd(int pVertexIndex,double pWeight);
    /**    Remove a vertex from a cluster.
    *    \param    pVertexIndex    Index of vertex to remove.
    */
    void        VertexRemove(int pVertexIndex);
    /**    Get the number of vertices.
    *    \return Number of vertices in a cluster.
    */
    int            VertexGetCount();
    /**    Get vertex number.
    *    \param    pIndex    Index of link to get vertex from.
    *    \return Number value of vertex at link number \p pIndex
    */
    int            VertexGetNumber(int pIndex);
    /**    Get vertex weight.
    *    \param    pIndex    Index of link to get vertex from.
    *    \return Weight of vertex found at link number \p pIndex.
    */
    double        VertexGetWeight(int pIndex);
    /**    Set vertex weight.
    *    \param    pIndex        Index of link to get vertex from.
    *    \param    pWeight        Weight to give to vertex.
    */
    void        VertexSetWeight(double pWeight,int pIndex);
    /**    Clear all linked vertices.
    */
    void        VertexClear();

    FBPropertyClusterMode   ClusterMode;        //!< <b>Read Write Property:</b> Cluster mode.
    FBPropertyDouble        ClusterAccuracy;    //!< <b>Read Write Property:</b> Cluster accuracy.
};

////////////////////////////////////////////////////////////////////////////////////
// FBModelVertexData
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBModelVertexData );

class FBSDK_DLL FBModelVertexData : public FBComponent {
    __FBClassDeclare( FBModelVertexData,FBComponent );

protected:
    FBModelVertexData(FBModel* pModel);
    friend class DataFBModel;

public:

    //! Return true if the model is deformable.
    bool IsDeformable();        

    /** Queries if this model should be drawn, e.g., in custom render callback.
    *   Returns false if e.g., deformed vertex data has not been computed for this frame(thus not ready to be drawn),
    *   or if model should be hidden when Z-Depth selection tool is active.   
    */
    bool IsDrawable();

    //! Return the Vertex Count.
    int GetVertexCount();

    /**
    * \name Sub Patch Management. Each sub patch contain same type of primitives mapped with same material. 
    */
    //@{

    //! Return number of sub patches
    int GetSubPatchCount();

    //! Return the mapped material for this sub patch.
    int GetSubPatchMaterialId(int pSubPatchIndex);

    //! Return the mapped material for this sub patch.
    FBMaterial* GetSubPatchMaterial(int pSubPatchIndex);

    /** Return the primitive type for this sub patch.
    *    Most of the time, kFBGeometry_TRIANGLES will return.
    *   \param  pSubPatchIndex  Index of sub patch to be queried.
    *   \param  pIsOptimized    Out parameter, return true if this sub patch is optimized for fast rendering, custom shader & render should use the optimized subpatch only
    *   \return The primitive type of the queried sub patch.
    */
    FBGeometryPrimitiveType GetSubPatchPrimitiveType(int pSubPatchIndex, bool* pIsOptimized = NULL);

    //! Return the start offset of the indexes for this sub patch (see GetIndexArray()).
    int GetSubPatchIndexOffset(int pSubPatchIndex);

    //! Return the size of the indexes for this sub patch (see GetIndexArray()).
    int GetSubPatchIndexSize(int pSubPatchIndex);

    /** Draw Sub Patch. Must be called between Enable/DisableOGLVertexData function calls.
    *    \param pSubPatchIndex    Index of sub region to be drawn.
    *    \param pWireFrame        draw wire frame if true.
    */
    void DrawSubPatch(int pSubPatchIndex, bool pWireFrame = false);

    //@}

    /**
    * \name Sub Regions Management. Each Sub Regions are composed by one or several patches which
    *  are composed with same material.
    */
    //@{

    //! Return number of sub regions (mapping with different materials)
    int GetSubRegionCount();

    /** Return sub region's material.
    *    \param pSubRegionIndex    Index of the sub region.
    */
    FBMaterial* GetSubRegionMaterial(int pSubRegionIndex);

    /** Draw Sub Region. Must be called between Enable/DisableOGLVertexData function calls.
    *    \param pSubRegionIndex    Index of sub region to be drawn.
    *    \param pWireFrame        draw wire frame if true.
    */
    void DrawSubRegion(int pSubRegionIndex, bool pWireFrame = false);

    //@}

    /** Disables Z-Depth clip plane if this model is selected using Z-Depth HideFront selection tool.
    *   Call this function before drawing each model in custom render callback, so that the selected model is unaffected by the Z-Depth clip plane,
    *   and hence is visible when Z-Depth HideFront selection tool is active.
    *   Be sure to call PopZDepthClipOverride() after drawing each model.
    */
    void PushZDepthClipOverride();

    /** Re-enables Z-Depth clip plane if it had been disabled via PushZDepthClipOverride().
    *   Call this function after drawing each model in custom render callback, so that Z-Depth clip plane is re-enabled if it was earlier disabled
    *   via PushZDepthClipOverride().
    */
    void PopZDepthClipOverride();

    /**
    * \name Vertex Array Management
    */

    //@{
    /** Enable (Setup) OpenGL Vertex Array (Pos & Normal)*/
    void EnableOGLVertexData(bool pAfterdeform = true);

    /** Disable OpenGL Vertex Array (Pos & Normal)*/
    void DisableOGLVertexData();

    /** Request deformed vertex array mapping on CPU. 
    *   Model's deformation computation could be executed on GPU, and thus the deformed vertex data will reside in GPU memory only by default.
    *   Calling this function VertexArrayMappingRequest() will ensure the deformed vertex array to be always mapped to CPU memory.
    *    \note: this function should be called at least once before GetVertexArray(pArrayId, true) to give engine chance to process request properly.
    */
    void VertexArrayMappingRequest();

    /** Release deformed vertex array mapping on CPU.
    *   call this function if plugin don't need CPU access of the deformed vertex array to be mapped on CPU memory anymore, 
    *   hence allow the application flexbility to choose higher performance approach. 
    */
    void VertexArrayMappingRelease();

    /** The FBModel::TessellatedMesh could contain per-face mapping UVset/Normal or other layer elements. 
    *   In order to build a valid VBO buffer for accelerated rendering, those control points with multiple
    *   attribute data must be duplicated. 
    *   This function return the duplicated vertexes' ID mapping from FBModel::ModelVertexData vertex array 
    *   to its FBModel::TessellatedMesh vertex array. Note those duplicated vertexs are always appended 
    *   after the original vertex array. 
    *   \param  pDuplicatedVertexCound  return the count of those duplicated vertexs.
    *   \return A pointer to the original vertex ID mapping for those duplicated vertexs.
    */
    const int* GetVertexArrayDuplicationMap(unsigned int& pDuplicatedVertexCound);

    /** Return Index Array*/
    int* GetIndexArray();

    /** Return Index Array VBO Id*/
    unsigned int GetIndexArrayVBOId();

    /** Return Vertex Array Format 
    *    \param  pArrayId        vertex array type to return.
    *    \param  pAfterDeform    return deformed vertex array type if the model is deformable, pAfterDeform is true and deformation is occurred in CPU, otherwise return original.
    *    \return VertexArray Format.
    *    \note   Use VertexArrayMappingRequest() to toggle CPU / GPU skinning per model when necessary.
    */
    FBGeometryArrayElementType GetVertexArrayType(FBGeometryArrayID pArrayId, bool pAfterDeform = true);

    /** Return Vertex Array Pointer
    *    \param  pArrayId        vertex array type to return.
    *    \param  pAfterDeform    return deformed vertex array if the model is deformable, pAfterDeform is true and deformation is occurred in CPU, otherwise return original.
    *    \return VertexArray Pointer. Deformed position & normal vertex arrays could be NULL if not request mapping vertex array.
    *    \note   Use VertexArrayMappingRequest() to toggle CPU / GPU skinning per model when necessary.
    */
    void* GetVertexArray(FBGeometryArrayID pArrayId, bool pAfterDeform = true);

    /** Return Vertex Buffer Object (VBO) Id for the request array
    *    \param  pArrayId        vertex array type to return.
    *    \param  pAfterDeform    return deformed vertex array VBO Id if the model is deformable, pAfterDeform is true and deformation is occurred in CPU, otherwise return original.
    *    \return VertexArray VBO Id. Deformed position & normal vertex VBOId could be 0 is model use CPU skinning.
    *    \note   Use VertexArrayMappingRequest() to toggle CPU / GPU skinning per model when necessary.
    */
    unsigned int GetVertexArrayVBOId(FBGeometryArrayID pArrayId, bool pAfterDeform = true);

    /** Return Vertex Buffer Object (VBO) offset for the request array
    *    \param  pArrayId        vertex array type to return.
    *    \param  pAfterDeform    return deformed vertex array VBO offset if the model is deformable, pAfterDeform is true and deformation is occurred in CPU, otherwise return original.
    *    \return VertexArray VBO offset.
    *    \note   Use VertexArrayMappingRequest() to toggle CPU / GPU skinning per model when necessary.
    */
    void* GetVertexArrayVBOOffset(FBGeometryArrayID pArrayId, bool pAfterDeform = true);

    //@}

    /**
    * \name UVset Array Management
    */

    //@{
    /** Enable (Setup) OpenGL UV Set Array */
    void EnableOGLUVSet(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);

    /** Disable OpenGL UV Set Array*/
    void DisableOGLUVSet();

    /** Return UV Array Format. 
    *    \param  pTextureMapping    Texture Mapping Mode.
    *    \param  pUVSet            UVSet name if pTextureMapping is kFBTextureMappingUV, otherwise ignore.
    *    \return UVSet Array Format.
    */
    FBGeometryArrayElementType GetUVSetArrayFormat(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);

    /** Return UV Array Pointer
    *    \param  pTextureMapping    Texture Mapping Mode.
    *    \param  pUVSet            UVSet name if pTextureMapping is kFBTextureMappingUV, otherwise ignore.
    *    \return UVSet Array Pointer.
    */
    void* GetUVSetArray(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);

    /** Return UVSet Buffer Object (VBO) Id.
    *    \param  pTextureMapping    Texture Mapping Mode.
    *    \param  pUVSet            UVSet name if pTextureMapping is kFBTextureMappingUV, otherwise ignore.
    *    \return UVSet VBO Id.
    */
    unsigned int GetUVSetVBOId(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);

    /** Return UVSet Buffer Object (VBO) offset.
    *    \param  pTextureMapping    Texture Mapping Mode.
    *    \param  pUVSet            UVSet name if pTextureMapping is kFBTextureMappingUV, otherwise ignore.
    *    \return UVSet VBO Offset.
    */
    void* GetUVSetVBOOffset(FBTextureMapping pTextureMapping = kFBTextureMappingUV, const char* pUVSet = NULL);

    //@}
};

////////////////////////////////////////////////////////////////////////////////////
// FBDeformer
////////////////////////////////////////////////////////////////////////////////////

/**    \enum FBDeformerType                     Determine the deformer type.
* - \p kFBDeformerSkeleton                      Skeleton (Bone) driven skinning deformer.
* - \p kFBDeformerPointCache                    Pre-recorded point cache deformer.
* - \p kFBGeometryMapping_BY_POLYGON_VERTEX     There will be one mapping coordinate for each vertex, for each polygon/strip it is part of.
*                                                This means that a vertex will have as many mapping coordinates as polygons it is part of.
* - \p kFBGeometryMapping_BY_POLYGON            There can be only one mapping coordinate for the whole polygon/strip.
* - \p kFBGeometryMapping_BY_EDGE               There will be one mapping coordinate for each unique edge in the mesh.
*                                                This is meant to be used with smoothing layer elements.
* - \p kFBGeometryMapping_ALL_SAME              There can be only one mapping coordinate for the whole surface.
*/
enum FBDeformerType    
{
    kFBDeformerUnkown,
    kFBDeformerSkeleton,
    kFBDeformerPointCache
};

FB_DEFINE_ENUM( FBSDK_DLL, DeformerType                ); 

__FB_FORWARD( FBDeformer );

//! Base Model deformer class
class FBSDK_DLL FBDeformer : public FBComponent {
    __FBClassDeclare( FBDeformer,FBComponent );

public:
    /**    Constructor.
    *    \param    pName        Name of deformer.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBDeformer(const char* pName, HIObject pObject=NULL);

    FBPropertyDeformerType DeformerType;    //!< <b>Read Only Property:</b> Deformer Type.
};

////////////////////////////////////////////////////////////////////////////////////
// FBDeformerPointCache
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBDeformerPointCache );

//! Base Model deformer class
class FBSDK_DLL FBDeformerPointCache : public FBDeformer {
    __FBClassDeclare( FBDeformerPointCache,FBDeformer );

public:
    /**    Constructor.
    *    \param    pName        Name of deformer.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBDeformerPointCache(const char* pName, HIObject pObject=NULL);

    FBPropertyPointCacheFile   PointCacheFile;  //!< <b>Read Write Property:</b> Point Cache File Object.

    FBPropertyBool      Active;                  //!< <b>Read Write Property:</b> Active.

    FBPropertyInt       ChannelIndex;            //!< <b>Read Write Property:</b> Channel Index.
    FBPropertyString    ChannelName;             //!< <b>Read Only Property:</b> Channel Name.

    FBPropertyInt       ChannelCount;            //!< <b>Read Only Property:</b> Channel Count.
    FBPropertyTime      ChannelStart;            //!< <b>Read Only Property:</b> Channel Start.
    FBPropertyTime      ChannelEnd;              //!< <b>Read Only Property:</b> Channel End.
    FBPropertyBool      ChannelSampleRegular;    //!< <b>Read Only Property:</b> Channel Sample Regular.
    FBPropertyDouble    ChannelFrameRate;        //!< <b>Read Only Property:</b> Channel FrameRate.
    FBPropertyInt       ChannelPointCount;       //!< <b>Read Only Property:</b> Channel Point Count.
};

////////////////////////////////////////////////////////////////////////////////////
// FBPointCacheFile
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBPointCacheFile );

//! Base Model deformer class
class FBSDK_DLL FBPointCacheFile : public FBComponent {
    __FBClassDeclare( FBPointCacheFile,FBComponent );

public:
    /**    Constructor.
    *    \param    pName        Name of Point Cache File Object.
    *    \param    pObject        For internal use only(default=NULL).
    */
    FBPointCacheFile(const char* pName, HIObject pObject=NULL);

    FBPropertyString    CacheFileName;           //!< <b>Read Write Property:</b> Filename of media.
    FBPropertyInt       ChannelCount;            //!< <b>Read Only Property:</b> Channel Count.

    FBPropertyTime      StartTime;               //!< <b>Read Write Property:</b> Start Time.
    FBPropertyTime      StopTime;                //!< <b>Read Write Property:</b> Stop Time.
    FBPropertyDouble    PlaySpeed;               //!< <b>Read Write Property:</b> Play Speed.
    FBPropertyTime      Offset;                  //!< <b>Read Write Property:</b> Offset.
    FBPropertyBool      FreeRunning;             //!< <b>Read Write Property:</b> Free Running.
    FBPropertyBool      Loop;                    //!< <b>Read Write Property:</b> Loop.
};

#ifdef FBSDKUseNamespace
}
#endif
#endif
