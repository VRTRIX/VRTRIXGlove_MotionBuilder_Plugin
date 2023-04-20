#ifndef __FBGEOMETRY_H__
#define __FBGEOMETRY_H__
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

/** \file fbgeometry.h
*    Base class for Geometry.
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

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

    FB_DEFINE_COMPONENT( FBSDK_DLL, Geometry         );
    FB_DEFINE_COMPONENT( FBSDK_DLL, Mesh             );

    enum FBGeometryPrimitiveType
    {
        kFBGeometry_POINTS              = 0x0000, //GL_POINTS,
        kFBGeometry_LINES               = 0x0001, //GL_LINES,
        kFBGeometry_LINE_LOOP           = 0x0002, //GL_LINE_LOOP,
        kFBGeometry_LINE_STRIP          = 0x0003, //GL_LINE_STRIP,
        kFBGeometry_TRIANGLES           = 0x0004, //GL_TRIANGLES,
        kFBGeometry_TRIANGLE_STRIP      = 0x0005, //GL_TRIANGLE_STRIP,
        kFBGeometry_TRIANGLE_FAN        = 0x0006, //GL_TRIANGLE_FAN,
        kFBGeometry_QUADS               = 0x0007, //GL_QUADS,
        kFBGeometry_QUADS_STRIP         = 0x0008, //GL_QUAD_STRIP,
        kFBGeometry_POLYGON             = 0x0009, //GL_POLYGON,
    };

    //! ID to use when requesting a specific array of data for a model
    enum FBGeometryArrayID 
    { 
        kFBGeometryArrayID_Point          =  1 << 0,    //!< ID to the Point array 
        kFBGeometryArrayID_Normal         =  1 << 1,    //!< ID to the Normal by Point array 
        kFBGeometryArrayID_Tangent        =  1 << 2,    //!< ID to the Tangent array 
        kFBGeometryArrayID_Binormal       =  1 << 3,    //!< ID to the Binormal array 
        kFBGeometryArrayID_Color          =  1 << 4     //!< ID to the Vertex Color Array
    };

    //! Type of data when requesting an array
    enum FBGeometryArrayElementType {
        kFBGeometryArrayElementType_Unknown,
        kFBGeometryArrayElementType_Integer, 
        kFBGeometryArrayElementType_Float,
        kFBGeometryArrayElementType_Float2,
        kFBGeometryArrayElementType_Float3,     //!< Each element is an array of 3 float
        kFBGeometryArrayElementType_Float4,      //!< Each element is an array of 4 float
        kFBGeometryArrayElementType_FloatMatrix4x4,
        kFBGeometryArrayElementType_IntegerArrayPointer
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBGeometry
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBGeometry );


    /**    \enum FBGeometryMappingMode               Determine how the element is mapped on a surface.
    * - \p kFBGeometryMapping_NONE                  The mapping is undetermined.
    * - \p kFBGeometryMapping_BY_CONTROL_POINT      There will be one mapping coordinate for each surface control point/vertex.
    * - \p kFBGeometryMapping_BY_POLYGON_VERTEX     There will be one mapping coordinate for each vertex, for each polygon/strip it is part of.
    *                                                This means that a vertex will have as many mapping coordinates as polygons it is part of.
    * - \p kFBGeometryMapping_BY_POLYGON            There can be only one mapping coordinate for the whole polygon/strip.
    * - \p kFBGeometryMapping_BY_EDGE               There will be one mapping coordinate for each unique edge in the mesh.
    *                                                This is meant to be used with smoothing layer elements.
    * - \p kFBGeometryMapping_ALL_SAME              There can be only one mapping coordinate for the whole surface.
    */
    enum FBGeometryMappingMode
    {
        kFBGeometryMapping_NONE,
        kFBGeometryMapping_BY_CONTROL_POINT,
        kFBGeometryMapping_BY_POLYGON_VERTEX,
        kFBGeometryMapping_BY_POLYGON,
        kFBGeometryMapping_BY_EDGE,
        kFBGeometryMapping_ALL_SAME
    } ;

    /** \enum FBGeometryReferenceMode     Determine how the mapping information is stored in the array of coordinate.
    * - \p kFBGeometryReference_DIRECT    This indicates that the mapping information for the n'th element is found in the n'th place of DirectArray.
    * - \p kFBGeometryReference_INDEX,    This indicates that the mapping information for the n'th element is found in the n'th place of IndexArray.
    * - \p kFBGeometryReference_INDEX_TO_DIRECT     This indicates that the KLayerElementTemplate::mIndexArray
    *                                                contains, for the n'th element, an index in the KLayerElementTemplate::mDirectArray
    *                                                array of mapping elements. eINDEX_TO_DIRECT is usually useful to store coordinates
    *                                                for eBY_POLYGON_VERTEX mapping mode elements. Since the same coordinates are usually
    *                                                repeated a large number of times, it saves spaces to store the coordinate only one time
    *                                                and refer to them with an index. Materials and Textures are also referenced with this
    *                                                mode and the actual Material/Texture can be accessed via the KLayerElementTemplate::mDirectArray
    */
    enum FBGeometryReferenceMode
    {
        kFBGeometryReference_DIRECT,
        kFBGeometryReference_INDEX,
        kFBGeometryReference_INDEX_TO_DIRECT    
    };

    FB_DEFINE_ENUM( FBSDK_DLL, GeometryMappingMode ); 
    FB_DEFINE_ENUM( FBSDK_DLL, GeometryReferenceMode ); 

    enum kFBGeometryUpdateFlags
    {
        kFBGeometryUpdateNone                = 0,        //!< no update done
        kFBGeometryUpdateAll                 = 1 << 0,   //!< control point add/remove, topology change, cluster/shape change and such events requiring regenerate optimized strip.
        kFBGeometryUpdatePositionAndNormal   = 1 << 1,   //!< only control point's position & normal change, so only update those values in the strip.
        kFBGeometryUpdateSkinWeight          = 1 << 2,   //!< update skin weight
        kFBGeometryUpdateInverseNormal       = 1 << 3,   //!< inverse normal request.    
        kFBGeometryUpdateMappingMode         = 1 << 4,   //!< mapping mode request from associated shading network change.
    };

    /** Geometry class.
    *
    *   This class groups all geometry related elements which are shared across
    *   the different subclasses (FBMesh, FBSurface, FBNurbs and FBPatch).
    *   Geometry Material always use kFBGeometryReference_INDEX mode. While
    *   Normal, UV could have different combination of mapping and reference modes.
    * 
    *   Geometries created with SDK can support FBGeometryMapping_ALL_SAME or kFBGeometryMapping_BY_POLYGON for material, 
    *   and kFBGeometryMapping_BY_CONTROL_POINT for Normal, Tangent, Binormal, Color and UV. Only one set of UV could be supported. 
    *
    *   Geometries passed from FBXSDK pipeline could have various complex 
    *   mapping/reference mode combination for material, normal and UV.
    *   And could potentially contains multiple set of UVs.
    */
    class FBSDK_DLL FBGeometry : public FBComponent {
        __FBClassDeclare( FBGeometry,FBComponent );

    protected:
        /**  Constructor.
        *    \param    pName        Name of Geometry.
        *    \param    pObject        For internal use only(default=NULL).
        */
        FBGeometry(const char* pName, HIObject pObject=NULL);

    public:
        /**
        * \name Simple Geometry Editing Interface:
        *        Geometries created with SDK can only use the kFBGeometryMapping_ALL_SAME 
        *        or kFBGeometryMapping_BY_POLYGON mapping mode for material, 
        *        kFBGeometryMapping_BY_CONTROL_POINT / kFBGeometryReference_DIRECT for 
        *        Normal, UV, Color, Tangent and Binormal. And only support one set of UV 
        */
        //@{

        /**    Begin geometry editing.
        *    \return    \b true if successful.
        */
        bool        GeometryBegin();

        /**    End geometry editing.
        *    \return    \b true if successful.
        */
        bool        GeometryEnd();

        /**    Is geometry editing enabled
        *    \return    \b true if enabled.
        */
        bool        IsEditingEnabled() const;
        //@}

        /**    Resize or Reserve vertex, normal and UV array for performance. 
        *    \param  pSize    Number of vertices to resize or reserve.
        *    \param  pResize \b True, for the geometry with known vertex count, we should resize the arrays to fixed size, 
        *                    and call VertexSet() afterwards; 
        *                    \b False, While for dynamic size geometry, we should only reserve the arrays with the estimated 
        *                    optimal size, then call VertexAdd() to dynamically increase the vertex count.
        *    \param  pInitUV            init Vertex UV array if true
        *    \param  pInitVertexColor   Init Vertex Color Array if true.
        */
        void        VertexInit    (int pSize, bool pResize, bool pInitUV = true, bool pInitVertexColor = false);

        /**    Clear all Vertex arrays.
        *   Call this function to clear Position, Normal, UV, Color and etc vertex arrays, 
        *   and it won't affect geometry's topology (polygon, Surface and etc.,).
        *    \return    \b true if successful.
        */
        bool        VertexClear    ();

        /**    Add a vertex.
        *    \param    pVertex        Vertex values used to add vertex.
        *    \return    Index where vertex was added.
        *    \remark    Set Normal with default value
        */
        int         VertexAdd    (FBVertex pVertex);

        /**   Add a vertex.
        *    \param    pVertex        Vertex values used to add vertex.
        *    \param    pNormal        Normal values used to add vertex.
        *    \return    Index where vertex was added.
        */
        int         VertexAdd    (FBVertex pVertex, FBNormal pNormal);

        /**    Add a vertex.
        *    \param    pVertex        Vertex values used to add vertex.
        *    \param    pNormal        Normal values used to add vertex.
        *    \param    pUV            UV values used to add vertex.
        *    \return    Index where vertex was added.
        */
        int         VertexAdd    (FBVertex pVertex, FBNormal pNormal, FBUV pUV);

        /**    Add a vertex.
        *    \param    pVertex        Vertex values used to add vertex.
        *    \param    pNormal        Normal values used to add vertex.
        *    \param    pUV            UV values used to add vertex.
        *   \param  pVertexColor Color values used to add vertex.
        *    \return    Index where vertex was added.
        */
        int         VertexAdd    (FBVertex pVertex, FBNormal pNormal, FBUV pUV, FBColorF pVertexColor);

        /**  Add a vertex.
        *    \param    px    X coordinate of vertex to add.
        *    \param    py    Y coordinate of vertex to add.
        *    \param    pz    Z coordinate of vertex to add.
        *    \return    Index where vertex was added.
        *    \remark    Set Normal with default value
        */
        int         VertexAdd    (double px, double py, double pz);
        int         VertexAdd    (double px, double py, double pz, double nx, double ny, double nz);
        int         VertexAdd    (double px, double py, double pz, double nx, double ny, double nz, double UVu, double UVv);
        int         VertexAdd    (double px, double py, double pz, double nx, double ny, double nz, double UVu, double UVv, double pRed, double pGreen, double pBlue, double pAlpha);

        /**  Set a vertex
        *    \param    pVertex        Vertex values used to set vertex.
        *    \param    pIndex        Index of vertex to affect (default=-1).
        *    \return    \b true if successful.
        */
        bool        VertexSet    (FBVertex pVertex,int pIndex=-1);

        /**   Set a vertex
        *    \param    px        X coordinate to set.
        *    \param    py        Y coordinate to set.
        *    \param    pz        Z coordinate to set.        
        *    \param    pIndex    Index of vertex to set(default=-1).
        *    \return    \b true if successful.
        */
        bool        VertexSet    (double px, double py, double pz,int pIndex=-1);

        /**    Set a normal at a vertex.
        *    \param    pVertex        Normal to set.
        *    \param    pIndex        Index of vertex to set Normal at(default=-1).
        *    \return    \b true if successful.
        */
        bool        VertexNormalSet(FBNormal pVertex,int pIndex=-1);

        /**     Set a normal at a vertex.
        *    \param    px        X coordinate of normal.
        *    \param    py        Y coordinate of normal.
        *    \param    pz        Z coordinate of normal.        
        *    \param    pIndex    Index of vertex to set Normal at(default=-1).
        *    \return    \b true if successful.
        */
        bool        VertexNormalSet(double px, double py, double pz,int pIndex=-1);


        /**     Set a UV coordinate.
        *    \param    pUV                UV coordinate to set.
        *    \param    pIndex            Index of Vertex to affect with UV coordinate(default=-1).
        *    \return    \b true if successful.
        */
        bool        VertexUVSet(FBUV pUV, int pIndex=-1);

        /**     Set a UV coordinate.
        *    \param    pU                U coordinate to set.
        *    \param    pV                V coordinate to set.
        *    \param    pIndex            Index of Vertex to affect with UV coordinate(default=-1).
        *    \return    \b true if successful.
        */
        bool        VertexUVSet(float pU, float pV, int pIndex=-1);

        /**     Set a Vertex Color
        *    \param    pColor            Vertex Color to set.
        *    \param    pIndex            Index of Vertex to affect with pColor(default=-1).
        *    \return    \b true if successful.
        */
        bool        VertexColorSet(FBColorF pColor, int pIndex=-1);

        /**     Set a UV coordinate.
        *    \param    pRed            Red   Color Channel to set, range [0, 1].
        *    \param    pGreen            Green Color Channel to set, range [0, 1].
        *    \param    pBlue            Blue  Color Channel to set, range [0, 1].
        *    \param    pAlpha            Alpha Color Channel to set, range [0, 1].
        *    \param    pIndex            Index of Vertex to affect with Red, Green, Blue and Alpha (default=-1).
        *    \return    \b true if successful.
        */
        bool        VertexColorSet(float pRed, float pGreen, float pBlue, float pAlpha, int pIndex=-1);

        //@}

        /**
        * \name Query interface for Vertex's Position, Normal, UV of default set. 
        */
        //@{

        /**    Get the number of vertices in the geometry.
        *    \return    Number of vertices in the geometry.
        */
        int         VertexCount    () const;

        /**    Get a vertex
        *    \param    pIndex    Index of vertex to get.
        *    \return    Vertex stored at \p pIndex.
        */
        FBVertex    VertexGet    (int pIndex) const;

        /**  Get a pointer to the array of vertexes.
        *    \return      pointer to the array of vertexes, or \c NULL if the array has not been allocated.
        */
        FBVertex*    GetVertexes() const;

        /**     Get a normal at a vertex.
        *    \param    pIndex    Vertex to get normal at(default=-1).
        *    \return    Normal of vertex at \p pIndex.
        */
        FBNormal    VertexNormalGet(int pIndex=-1) const;

        /**     Get a UV coordinate.
        *    \param    pIndex            Index of Vertex to get UV coordinate for(default=-1).
        *    \return    UV coordinate of vertex at \p UVSetIndex.
        */
        FBUV        VertexUVGet(int pIndex=-1) const;

        /**     Get a Vertex Color.
        *    \param    pIndex            Index of Vertex to get Color for(default=-1).
        *    \return    Color of vertex at \p UVSetIndex.
        */
        FBColorF    VertexColorGet(int pIndex=-1) const;

        //@}


        /**
        * \name Interface for direct manipulating Geometry Position, Normal, Color, UV and Material arrays.
        */
        //@{

        /**  Init geometry vertex arrays. 
        *    Init position, normal and UV arrays (tangent, bi-normal and color on demand) with 
        *    kFBGeometryMapping_BY_CONTROL_POINT / kFBGeometryReference_DIRECT mode.
        *    Will call VertexArrayClear() internally. 
        *    User should then call GetXXXDirectyArray() to edit the vertex attributes directly.
        *   \param pVertexcount     number of control points (vertex)
        *   \param pUniqueMaterial  User could specify per polygon mapping mode for mesh
        *   \param pFBGeometryArrayIDs  Request to init other attribute arrays, bitwise combined value of FBGeometryArrayID enum items, 
        *                               currently support Tangent, Binormal and VertexColor. Only useful for mesh.
        */
        bool        VertexArrayInit (int pVertexcount, bool pUniqueMaterial, unsigned int pFBGeometryArrayIDs = 0);

        /**   Clear all geometry vertex arrays. 
        *   Call this function to clear Position, Normal, UV, Color and etc vertex arrays, 
        *   and it won't affect geometry's topology (polygon, Surface and etc.,).
        *    \return    \b true if successful.
        */
        bool        VertexArrayClear();

        /** Get a pointer to the position array.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param    pOutArrayCount    To return the length the array.
        *    \return   Pointer to index array of normals, or \c NULL if the array hasn't been allocated yet.
        */
        FBVertex*       GetPositionsArray(int& pOutArrayCount) const;

        FBPropertyGeometryMappingMode       NormalMappingMode;          //!< <b>Read Only Property:</b> Normal mapping mode.
        FBPropertyGeometryReferenceMode     NormalReferenceMode;        //!< <b>Read Only Property:</b> Normal reference mode.

        /**  Get a pointer to the index array of normals.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return   Pointer to index array of normals, or \c NULL if the array hasn't been allocated yet.
        */
        int*            GetNormalsIndexArray(int& pOutArrayCount) const;

        /** Get a pointer to the direct array of normals. 
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return   Pointer to direct array of normals, or \c NULL if the array hasn't been allocated yet.
        */
        FBNormal*       GetNormalsDirectArray(int& pOutArrayCount) const;

        FBPropertyGeometryMappingMode       TangentMappingMode;          //!< <b>Read Only Property:</b> Tangent mapping mode.
        FBPropertyGeometryReferenceMode     TangentReferenceMode;        //!< <b>Read Only Property:</b> Tangent reference mode.

        /** Get a pointer to the index array of tangents.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return   Pointer to index array of tangents, or \c NULL if the array hasn't been allocated yet.
        */
        int*            GetTangentsIndexArray(int& pOutArrayCount) const;

        /** Get a pointer to the direct array of tangents. 
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return   Pointer to direct array of tangents, or \c NULL if the array hasn't been allocated yet.
        */
        FBNormal*       GetTangentsDirectArray(int& pOutArrayCount) const;

        FBPropertyGeometryMappingMode       BinormalMappingMode;          //!< <b>Read Only Property:</b> Binormal mapping mode.
        FBPropertyGeometryReferenceMode     BinormalReferenceMode;        //!< <b>Read Only Property:</b> Binormal reference mode.

        /** Get a pointer to the index array of binormals.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return   Pointer to index array of binormals, or \c NULL if the array hasn't been allocated yet.
        */
        int*            GetBinormalsIndexArray(int& pOutArrayCount) const;

        /** Get a pointer to the direct array of binormals.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return   Pointer to direct array of binormals, or \c NULL if the array hasn't been allocated yet.
        */
        FBNormal*       GetBinormalsDirectArray(int& pOutArrayCount) const;

        FBPropertyGeometryMappingMode    VertexColorMappingMode;        //!< <b>Read Only Property:</b> Vertex Color mapping mode.
        FBPropertyGeometryReferenceMode  VertexColorReferenceMode;      //!< <b>Read Only Property:</b> Vertex Color reference mode.

        /** Get a pointer to the index array of vertex color.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return   Pointer to index array of vertex color, or \c NULL if the array hasn't been allocated yet.
        */
        int*            GetVertexColorsIndexArray(int& pOutArrayCount) const;

        /** Get a pointer to the direct array of vertex color.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return   Pointer to direct array of vertex colors, or \c NULL if the array hasn't been allocated yet.
        */
        FBColorF*       GetVertexColorsDirectArray(int& pOutArrayCount) const;

        /** Get available UVSet name
        *    \return StringList contain all the available UVSets' name.
        */
        FBStringList    GetUVSets() const;

        /** Get UVSet mapping mode.
        *    \param  pUVSetName        The name of UVset, NULL for the first UVset.
        *    \return Mapping mode of the UVset.
        */
        FBGeometryMappingMode    GetUVSetMappingMode(const char* pUVSetName = NULL) const;

        /** Get UVSet reference mode.
        *    \param  pUVSetName        The name of UVset, NULL for the first UVset.
        *    \return Reference mode of the UVset.
        */
        FBGeometryReferenceMode GetUVSetReferenceMode(const char* pUVSetName = NULL) const;

        /** Get a pointer to the index array of UVset.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \param  pUVSetName        The name of UVset, NULL for the first UVset.
        *    \return Pointer to index array of UVSet, or \c NULL if the array hasn't been allocated yet.
        */
        int*        GetUVSetIndexArray(int& pOutArrayCount, const char* pUVSetName = NULL) const;

        /** Get a pointer to the direct array of UVset
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \param  pUVSetName        The name of UVset, NULL for the first UVset.
        *    \return    pointer to the array of UV, or \c NULL is the array hasn't been allocated yet.
        */
        FBUV*       GetUVSetDirectArray(int& pOutArrayCount, const char* pUVSetName = NULL) const;

        FBPropertyGeometryMappingMode    MaterialMappingMode;    //!< <b>Read Property:</b> Material mapping mode.

        /** Get a pointer to the index array of Material.
        *   Modify array value will be only effective when geometry editing is enabled. \see GeometryBegin()/GeometryEnd()
        *    \param  pOutArrayCount    To return the length the array.
        *    \return Pointer to index array of Material, or \c NULL if the array hasn't been allocated yet.
        */
        int*        GetMaterialIndexArray(int& pOutArrayCount) const;
        //@}


        /**
        * \name Vertex Selection/Manipulation Interface.
        */
        //@{

        /**    Get the selected state of a vertex.        
        *    \param    pIndex    The index of the vertex
        *    \return    true if the vertex is selected, false if not
        */
        bool VertexGetSelected(int pIndex);
        
        /**    Set the selected state of a vertex.
        *    \param    pIndex    The index of the vertex
        *    \param    pState    The true to selected, false to deselect
        *    \return    true if the vertex is selected, false if not
        */
        bool VertexSetSelected(int pIndex,bool pState);

        /**    Get the visible state of a vertex.
        *    \param    pIndex    The index of the vertex
        *    \return    true if the vertex is visible, false if not
        */
        bool VertexGetVisible(int pIndex);

        /**    Set the visible state of a vertex.
        *    \param    pIndex    The index of the vertex
        *    \param    pState    true to be visible
        *    \return    true if the vertex is visible, false if not
        */
        bool VertexSetVisible(int pIndex,bool pState);

        /**    Get the Transformable state of a vertex.
        *    \param    pIndex    The index of the vertex
        *    \return    true if the vertex is Transformable, false if not
        */
        bool VertexGetTransformable(int pIndex);
        //@}

        /**
        * \name Shape Management Interface
        */
        //@{

        /** Get Shape Count. */
        int ShapeGetCount() const;

        /** Return the shape Name */
        const char* ShapeGetName(int pShapeIdx) const;

        /** Add new shape
        *    \param pName the shape name
        *    \return the index of the new shape, -1 if the shape adding fail.
        */
        int ShapeAdd(const char* pName);

        /** Clears all the shapes*/
        void ShapeClearAll();

        /**  Init the shape.
        *    \param pShapeIdx    The index of the shape to be initialized
        *    \param pDiffSize    Total number of different point (pos or normal) compared to base geometry.
        *    \param pWithNormal    Currently normal won't be considered during shape blending. 
        */
        void ShapeInit(int pShapeIdx, int pDiffSize, bool pWithNormal = false);

        /** Return the shape's total diff points count
        *    \param pShapeIdx    The index of the shape
        */
        int ShapeGetDiffPointCount(int pShapeIdx) const;

        /** Set the differentiate point.
        *    \param pShapeIdx    The index of the shape
        *    \param pDiffIndex    The index of the diff point in this shape.
        *    \param pOriIndex    The index of the diff point in the original geometry.
        *    \param pPosDiff        The position differentiation.
        */
        bool ShapeSetDiffPoint(int pShapeIdx, int pDiffIndex, int pOriIndex, const FBVertex& pPosDiff);

        /** Set the differentiate point.
        *    \param pShapeIdx    The index of the shape
        *    \param pDiffIndex    The index of the diff point in this shape.
        *    \param pOriIndex    The index of the diff point in the original geometry.
        *    \param pPosDiff        The position differentiation.
        *    \param pNormalDiff    The normal differentiation.
        */
        bool ShapeSetDiffPoint(int pShapeIdx, int pDiffIndex, int pOriIndex, const FBVertex& pPosDiff, const FBNormal& pNormalDiff);

        /** Get the differentiate point.
        *    \param pShapeIdx    The index of the shape
        *    \param pDiffIndex    The index of the diff point in this shape.
        *    \param pOriIndex    The index of the diff point in the original geometry.
        *    \param pPosDiff        The position differentiation.
        */
        bool ShapeGetDiffPoint(int pShapeIdx, int pDiffIndex, int& pOriIndex, FBVertex& pPosDiff) const;

        /** Get the differentiate point.
        *    \param pShapeIdx    The index of the shape
        *    \param pDiffIndex    The index of the diff point in this shape.
        *    \param pOriIndex    The index of the diff point in the original geometry.
        *    \param pPosDiff        The position differentiation.
        *    \param pNormalDiff    The normal differentiation.
        */
        bool ShapeGetDiffPoint(int pShapeIdx, int pDiffIndex, int& pOriIndex, FBVertex& pPosDiff, FBNormal& pNormalDiff) const;

        //@}

        /**
        * \name Geometry Editing Notification
        */
        //@{

        /** The geometry has change, update the necessary flags.
        *    \param    pFlags        flags for the kind of update that was done.
        *    \param    pFirstIndex    Correspond to the start index of modification of points or normals.
        *    \param    pLastIndex    Correspond to the last index of modification of points or normals.
        */
        void ModifyNotify( kFBGeometryUpdateFlags pFlags=kFBGeometryUpdateAll, int pFirstIndex=-1, int pLastIndex=-1 );

        //@}
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBMesh
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBMesh );

    //! Mesh class.
    class FBSDK_DLL FBMesh : public FBGeometry {
        __FBClassDeclare( FBMesh,FBGeometry );

    public:
        /**    Constructor.
        *    \param    pName        Name of Mesh.
        *    \param    pObject        For internal use only(default=NULL).
        */
        FBMesh(const char* pName, HIObject pObject=NULL);

        /**    Add Triangle List, 
        *    Must be called in-between FBGeometry::GeometryBegin() / GeometryEnd()
        *    It's user's responsibility to make sure to input valid index values, otherwise afterwards behavior will be undefined.  
        *    \param     pIndexArraySize Size of pIndexArray, Added triangle count is floor(max(pIndexArraySize, 0) / 3)
        *    \param     pIndexArray     Index array of triangle list.
        *    \param     pMaterialId     Index of material for this polygon. Only effective when MaterialMappingMode is kFBGeometryMapping_BY_POLYGON mode.
        *    \note      The indexes' value in input pIndexArray won't be validated, and the behavior is undefined if out of range. 
        */
        bool TriangleListAdd(int pIndexArraySize, int* pIndexArray, int pMaterialId=0);

        /**    Add Triangle Strip
        *    Must be called in-between FBGeometry::GeometryBegin() / GeometryEnd()
        *    It's user's responsibility to make sure to input valid index values, otherwise afterwards behavior will be undefined.  
        *    \param     pIndexArraySize Size of pIndexArray, Added triangle count is max(pIndexArraySize - 2, 0) 
        *    \param     pIndexArray     Index array of triangle strip.
        *    \param     pMaterialId     Index of material for this polygon. Only effective when MaterialMappingMode is kFBGeometryMapping_BY_POLYGON mode.
        *    \note      The indexes' value in input pIndexArray won't be validated, and the behavior is undefined if out of range. 
        */
        bool TriangleStripAdd(int pIndexArraySize, int* pIndexArray, int pMaterialId=0);

        /**    Add Polygon List
        *    Must be called in-between FBGeometry::GeometryBegin() / GeometryEnd()
        *    It's user's responsibility to make sure to input valid index values, otherwise afterwards behavior will be undefined.  
        *    \param     pPolygonSize    Size of polygon, 3 mean triangle, 4 for quadrilateral, and so on. minimum input value is 3.  
        *    \param     pIndexArraySize Size of pIndexArray, Added polygon count is floor(max(pIndexArraySize, 0) / pPolygonSize)
        *    \param     pIndexArray     Index array of triangle strip.
        *    \param     pMaterialId     Index of material for this polygon. Only effective when MaterialMappingMode is kFBGeometryMapping_BY_POLYGON mode.
        *    \note      The indexes' value in input pIndexArray won't be validated, and the behavior is undefined if out of range. 
        */
        bool PolygonListAdd(int pPolygonSize, int pIndexArraySize, int* pIndexArray, int pMaterialId=0);

        /**     Begin Polygon definition.
        *    \param     pMaterialId      Index of material for this polygon. Only effective when MaterialMappingMode is kFBGeometryMapping_BY_POLYGON mode. 
        *    \return    Number of existing polygons in Mesh
        */
        int PolygonBegin(int pMaterialId=0);

        /**    Add a vertex.
        *    \param    pVertex        Index in mesh of vertex to add to polygon, must be in range of [0, ControlPointCount)
        *    \return    \b true if successful.
        */
        bool PolygonVertexAdd(int pVertex);

        /**    End Polygon definition.
        *    Clean up and associate vertices internally.
        *    \return    Current number of polygons.
        *    \note      MoBu expect each polygon to contain at least 3 vertices, the behavior is undefined if user add less than 3 vertices polygon. 
        */
        int PolygonEnd();

        /**    Get Polygon vertex count
        *    \param    pPolygonIndex    Index of polygon to get vertex count from.
        *    \return    Number of vertices in polygon at \p pPolygonIndex.
        */
        int PolygonVertexCount(int pPolygonIndex) const;

        /**    Get global (for the mesh) index of a vertex from a polygon
        *    \param    pPolygonIndex            Index of polygon in question.
        *    \param    pVertexPolygonIndex      Polygon vertex index.
        *    \return    Index in mesh of vertex.
        */
        int PolygonVertexIndex(int pPolygonIndex, int pVertexPolygonIndex) const;

        /**    Get number of polygons in mesh.
        *    \return    Number of polygons in mesh.
        */
        int PolygonCount() const;

        /**  Get the array of polygon vertex (i.e. index to control points).
        *   This array is a concatenation of the list of polygon vertices
        *   of all the polygons. Example: a mesh made of 2 triangles [1,2,3]
        *   and [2,3,4] results in [1,2,3,2,3,4]. The first polygon starts at
        *   position 0 and the second at position 3.
        *   
        *   \param  pArraySize Polygon vertex array size.
        *   \return Readonly polygon vertex array.
        */
        const int* PolygonVertexArrayGet(int& pArraySize) const;

        /** Determines if the mesh is composed entirely of triangles.
        *   \return true if all polygons are triangles, false otherwise
        */
        bool IsTriangleMesh() const;

        /**  Get a Material ID for the given Polygon index.
        *    \param  pIndex Polygon's index to get material ID at (default=-1).
        *    \return        ID of material of vertex at \p pIndex.
        */
        int PolygonMaterialIdGet(int pIndex=-1) const;

        /** Compute Mesh Vertex Normal 
        *    \param pCW \b True for clock wise normal, otherwise for counter-clock wise
        */
        void ComputeVertexNormals(bool pCW = false);

        /** Inverse Normal */
        void InverseNormal();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBSurface
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBSurface );

    //! Surface modes
    enum FBSurfaceMode
    {
        kFBSurfaceModeRaw,               //!< Raw data.
        kFBSurfaceModeLowNoNormals,      //!< Low quality, no normals.
        kFBSurfaceModeLow,               //!< Low quality.
        kFBSurfaceModeHighNoNormals,     //!< High quality, no normals.
        kFBSurfaceModeHigh               //!< High quality.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, SurfaceMode );

    //! Surface types.
    enum FBSurfaceType
    {
        kFBSurfaceTypeBezier,            //!< Bezier surface.
        kFBSurfaceTypeBezierQuadric,     //!< Bezier Quadric surface.
        kFBSurfaceTypeCardinal,          //!< Cardinal surface.
        kFBSurfaceTypeBspline,           //!< BSpline surface.
        kFBSurfaceTypeLinear,            //!< Linear surface.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, SurfaceType );


    //! Surface class.
    class FBSDK_DLL FBSurface : public FBGeometry
    {
        __FBClassDeclare( FBSurface, FBGeometry );

    public:
        /**    Constructor.
        *    \param    pName        Name of Surface.
        *    \param    pObject        For internal use only(default=NULL).
        */    
        FBSurface(const char* pName, HIObject pObject=NULL);

        virtual void    SurfaceBegin();
        virtual void    SurfaceEnd();
        virtual void    SurfaceEditBegin();
        virtual void    SurfaceEditEnd();
        virtual bool    GetSurfaceCapped( int pUorV, int pDirection );
        virtual int     GetVertexCount( int pUorVorGlobal = -1 );
        virtual void    ControlPointsBegin() = 0;
        virtual void    SetControlPoint( int pIndex, double pX, double pY, double pZ, double pW );
        virtual void    GetControlPoint( int pIndex, double &pX, double &pY, double &pZ, double &pW );
        virtual void    ControlPointsEnd();

        /**    Get the selected state of a vertex.
        *    \param    pU    The u index of the vertex.
        *    \param    pV    The v index of the vertex.
        *    \return    true if the vertex is selected, false if not.
        */
        bool VertexGetSelected(int pU,int pV);
        /**    Set the selected state of a vertex.
        *    \param    pU    The u index of the vertex.
        *    \param    pV    The v index of the vertex.
        *   \param  pState  Set the select state.
        *    \return    true if the vertex is selected, false if not.
        */
        bool VertexSetSelected(int pU,int pV,bool pState);

        /**    Get the visible state of a vertex.
        *    \param    pU    The u index of the vertex.
        *    \param    pV    The v index of the vertex.
        *    \return    true if the vertex is visible, false if not.
        */
        bool VertexGetVisible(int pU,int pV);

        /**    Set the visible state of a vertex.
        *    \param    pU    The u index of the vertex.
        *    \param    pV    The v index of the vertex.
        *   \param  pState  Set the visible state.
        *    \return    true if the vertex is visible, false if not.
        */
        bool VertexSetVisible(int pU,int pV,bool pState);

        /**    Get the Transformable state of a vertex.
        *    \param    pU    The u index of the vertex.
        *    \param    pV    The v index of the vertex.
        *    \return    true if the vertex is Transformable, false if not.
        */
        bool VertexGetTransformable(int pU,int pV);


        FBPropertyInt            USize;        //!< <b>Read Write Property:</b> Size in U directions.
        FBPropertyInt            VSize;        //!< <b>Read Write Property:</b> Size in V directions.
        FBPropertyInt            UStep;        //!< <b>Read Write Property:</b> Step in U directions.
        FBPropertyInt            VStep;        //!< <b>Read Write Property:</b> Step in V directions.
        FBPropertyBool           UClosed;      //!< <b>Read Write Property:</b> U Closed.
        FBPropertyBool           VClosed;      //!< <b>Read Write Property:</b> V Closed
        FBPropertySurfaceMode    SurfaceMode;  //!< <b>Read Write Property:</b> Surface mode.

    private:
        void FBSurfaceInitProperties();
    };

    //! Surface types.
    enum FBNurbType
    {
        kFBNurbTypePeriodic,    //!< Periodic Type Nurb
        kFBNurbTypeClosed,      //!< Closed Type Nurb.
        kFBNurbTypeOpen,        //!< Open Type Nurb.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, NurbType );


    ////////////////////////////////////////////////////////////////////////////////////
    // FBNurbs
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBNurbs );

    //! Nurbs class.
    class FBSDK_DLL FBNurbs : public FBSurface
    {
        __FBClassDeclare( FBNurbs, FBSurface );

    public:
        /**    Constructor.
        *    \param    pName        Name of Nurbs.
        *    \param    pObject        For internal use only(default=NULL).
        */
        FBNurbs(const char* pName, HIObject pObject=NULL);

        /** Begin NURBS definition.
        */
        virtual void    SurfaceBegin() override;

        /** End NURBS definition.
        */
        virtual void    SurfaceEnd() override;

        /**    Begin NURBS surface edition
        */
        virtual void    SurfaceEditBegin() override;
        /**    End NURBS surface edition
        */
        virtual void    SurfaceEditEnd() override;
        /**    Begin NURBS control points edition
        */
        virtual void    ControlPointsBegin() override;
        /**    End NURBS control points edition
        */
        virtual void    ControlPointsEnd() override;
        /**    Set weight of control point
        *    \param    pIndex Index of control point to set weight at.
        *    \param    pWeight Weight of control point.
        */
        virtual void    SetControlWeight( int pIndex, double pWeight );
        /**    Get weight of control point
        *    \param    pIndex Index of control point to get weight from.
        *    \return    Weight of control point at index \p pIndex.
        */
        virtual double    GetControlWeight( int pIndex );
        /**    Set multiplicity (number of "instances") of control point.
        *    \param    pUorV    \b 1 if V multiplicity, \b 0 if U multlipicity.
        *    \param    pIndex    Index of control point to set multiplicity for.
        *    \param    pMultiplicity Multiplicity value for control point at \p pIndex.
        */
        virtual void    SetControlMultiplicity( int pUorV, int pIndex, int    pMultiplicity    );
        /**    Get multiplicity (number of "instances") of control point.
        *    \param    pUorV    \b 1 if V multiplicity, \b 0 if U multlipicity.
        *    \param    pIndex    Index of control point to get multiplicity for.
        */
        virtual int        GetControlMultiplicity( int pUorV, int pIndex );
        /**    Set knot vector value of control point.
        *    \param    pUorV    \b 1 if V knot vector, \b 0 if U knot vector.
        *    \param    pIndex    Index of control point to set knot value for.
        *    \param    pKnotValue Knot value for control point at \p pIndex.
        */
        virtual void    SetControlKnotValue( int pUorV, int pIndex, double    pKnotValue        );
        /**    Get knot vector value of control point.
        *    \param    pUorV    \b 1 if V knot vector, \b 0 if U knot vector.
        *    \param    pIndex    Index of control point to set knot value for.
        */
        virtual double    GetControlKnotValue( int pUorV, int pIndex );
        /**    Number of knot vectors
        *    \param    pUorV    \b 1 if V knot vector, \b 0 if U knot vector.
        *    \return    Number of knot vectors on NURBS surface
        */
        virtual int        GetKnotCount( int pUorV );

        FBPropertyInt            UOrder;            //!< <b>Read Write Property:</b> Nurbs U order.
        FBPropertyInt            VOrder;            //!< <b>Read Write Property:</b> Nurbs V order.
        FBPropertyNurbType       UNurbType;        //!< <b>Read Write Property:</b> Nurbs Type for U direction.
        FBPropertyNurbType       VNurbType;        //!< <b>Read Write Property:</b> Nurbs Type for V direction.

    private:
        void FBNurbsInitProperties();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPatch
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBPatch );

    //! Patch class.
    class FBSDK_DLL FBPatch : public FBSurface
    {
        __FBClassDeclare( FBPatch, FBSurface );

    public:
        /**    Constructor.
        *    \param    pName        Name of Patch.
        *    \param    pObject        For internal use only(default=NULL).
        */
        FBPatch(const char* pName, HIObject pObject=NULL);

        /** Begin Patch definition
        */
        virtual void SurfaceBegin() override;

        /** End Patch definition
        */
        virtual void SurfaceEnd() override;

        /**    Begin patch surface edit.
        */
        virtual void SurfaceEditBegin() override;

        /**    End patch surface edit.
        */
        virtual void SurfaceEditEnd() override;

        /** Begin control points edition
        */
        virtual void ControlPointsBegin() override;
        /** End control points edition
        */
        virtual void ControlPointsEnd() override;


        FBPropertySurfaceType    USurfaceType;        //!< <b>Read Write Property:</b> Patch mode for U direction.
        FBPropertySurfaceType    VSurfaceType;        //!< <b>Read Write Property:</b> Patch mode for V direction.

    private:
        void FBPatchInitProperties();

    };

#ifdef FBSDKUseNamespace
}
#endif
#endif
