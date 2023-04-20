#ifndef HIKDRAWOBJECT_H
#define HIKDRAWOBJECT_H

struct HIKCharacter;
struct HIKCharacterState;
struct HIKEffectorSetState;
struct HIKPropertySetState;

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define FLOAT_MAX 3.402823466e+38F;

namespace HIKDrawObjectNS
{
    template <class T1, class T2> class HIKPair
    {   
        public:
            typedef T1 first_type;
            typedef T2 second_type;
            T1 first;
            T2 second;        
            HIKPair() : first(T1()), second(T2()) {}
            HIKPair(const T1& x, const T2& y) : first(x), second(y) {}
            template <class U, class V> HIKPair (const HIKPair<U,V> &p) : first(p.first), second(p.second) { }
    };

    #define HIKVECTOR_INCREMENT 32
    template < class T > class HIKVector
    { 
            T* first;          // Array of elements
            int count;          // Actual elements count in array
            int maxCount;       // Maximum elements count in array

        public: 
            HIKVector() { first = NULL; count = 0; maxCount = 0; }
            ~HIKVector() { if(first) { delete [] first; } }
            void clear() { if(first) { delete [] first; } first = NULL; count = 0; maxCount = 0; }
            T& back() const { return (first[count-1]); } 
            bool empty() const { return (count == 0); }
            T& operator[](const int index) const { return (first[index]); }
            unsigned int size() const { return count; }
            void push_back(const T& item)
            {
                if(count == maxCount)
                {
                    T* newFirst = new T[maxCount+HIKVECTOR_INCREMENT];
                    if(maxCount != 0)
                    {
                        memcpy(newFirst, first, sizeof(T)*maxCount);
                        delete [] first;
                    }
                    maxCount += HIKVECTOR_INCREMENT;
                    first = newFirst;
                }
                first[count++] = item;
            }
    }; 

	// global function to update a bounding box given a new position
	static void updateMinMax( const float in_pos[3], float io_min[3], float io_max[3] )
	{
		if( in_pos[0] < io_min[0] )
			io_min[0] = in_pos[0];
		if( in_pos[1] < io_min[1] )
			io_min[1] = in_pos[1];
		if( in_pos[2] < io_min[2] )
			io_min[2] = in_pos[2];

		if( in_pos[0] > io_max[0] )
			io_max[0] = in_pos[0];
		if( in_pos[1] > io_max[1] )
			io_max[1] = in_pos[1];
		if( in_pos[2] > io_max[2] )
			io_max[2] = in_pos[2];
	}

	// enum used by ObjectDrawContext
	typedef enum {
		DRAW_BONE,
		DRAW_NODE_AXIS,
		DRAW_NODE_SPHERE,
		DRAW_EFFECTOR_AXIS,
		DRAW_EFFECTOR_SPHERE,
		DRAW_FLOOR_CONTACT,
		DRAW_NODE_ROTLIMIT
	} EObjectDrawContextType;

	typedef enum {
		DRAW_CONTOUR,
		DRAW_NORMAL,
		DRAW_QUAD
	} EDrawFloorContactType;

	// Simple structure storing the context information about why an object got created
	// This information is essential to a client who wants to add extra geometries
	// or wants to do some selection like glPushName, glPopName
	struct ObjectDrawContext
	{
		struct DrawBoneContext
		{
			int m_ParentHIKNodeID;
			int m_ChildHIKNodeID;
		};
		struct DrawNodeAxisContext
		{
			int m_HIKNodeID;
			int m_XYZ; // 0, 1 or 2 for X, Y or Z, respectively
		};
		struct DrawNodeSphereContext
		{
			int m_HIKNodeID;
		};
		struct DrawEffectorAxisContext
		{
			int m_HIKEffectorID;
			int m_XYZ; // 0, 1 or 2 for X, Y or Z, respectively
		};
		struct DrawEffectorSphereContext
		{
			int m_HIKEffectorID;
		};
		struct DrawFloorContactContext
		{
			int m_HIKContactID; // one of HIKLeftFootFloor, HIKRightFootFloor, HIKLeftHandFloor, HIKRightHandFloor
			EDrawFloorContactType m_eType;
		};
		struct DrawRotLimitContext
		{
			int m_HIKNodeID;
			int m_RollPitchYaw; // 0, 1 or 2 for ROLL, PITCH or YAW respectively
		};
		
		EObjectDrawContextType m_eDrawType;
		union 
		{
			DrawBoneContext m_BoneContext;
			DrawNodeAxisContext m_NodeAxisContext;
			DrawNodeSphereContext m_NodeSphereContext;
			DrawEffectorAxisContext m_EffectorAxisContext;
			DrawEffectorSphereContext m_EffectorSphereContext;
			DrawFloorContactContext m_FloorContactContext;
			DrawRotLimitContext m_RotLimitContext;
		} u;
	};

	// enum used by BaseObject
	typedef enum {
		OBJECT_LINES,
		OBJECT_TRIANGLES,
		OBJECT_SPHERE
	} EObjectType;

	// Base class for all objects: lines, triangles, etc...
	// Every object can be selected individually.
	// Every object stores a bounding box.
	class BaseObject
	{
		friend class HIKDrawObject;
		friend class ObjectSet;
	public:
		BaseObject( EObjectType in_eType )
			: m_eType( in_eType )
		{
			resetBBox();
			// default color is black
			m_Color[0] = 0;
			m_Color[1] = 0;
			m_Color[2] = 0;
			m_Color[3] = 1;
		};
		virtual ~BaseObject()
		{
		};
		EObjectType getType() const
		{
			return m_eType;
		}
		void getBBox( float out_min[3], float out_max[3] ) const
		{
			out_min[0] = m_Min[0];
			out_min[1] = m_Min[1];
			out_min[2] = m_Min[2];
			out_max[0] = m_Max[0];
			out_max[1] = m_Max[1];
			out_max[2] = m_Max[2];
		}
		void resetBBox() 
		{
			m_Min[0] = FLOAT_MAX;
			m_Min[1] = FLOAT_MAX;
			m_Min[2] = FLOAT_MAX;

			m_Max[0] = - FLOAT_MAX;
			m_Max[1] = - FLOAT_MAX;
			m_Max[2] = - FLOAT_MAX;
		}
		const ObjectDrawContext & getDrawContext() const 
		{
			return m_DrawContext;
		}
		void setColor( float in_red, float in_green, float in_blue, float in_alpha )
		{
			m_Color[0] = in_red;
			m_Color[1] = in_green;
			m_Color[2] = in_blue;
			m_Color[3] = in_alpha;
		}
		void setColor( const float in_color[4] )
		{
			m_Color[0] = in_color[0];
			m_Color[1] = in_color[1];
			m_Color[2] = in_color[2];
			m_Color[3] = in_color[3];
		}
		const float * getColor( ) const
		{
			return m_Color;
		}

	private:
		BaseObject(); // disable default constructor

	private:
		float m_Min[3];
		float m_Max[3];
		float m_Color[4]; // RGBA between 0 and 1
		ObjectDrawContext m_DrawContext;
		EObjectType m_eType;
	};

	// Object of type "OBJECT_LINES"
	// The lines are not necessarily adjacent.
	// Each line stores two integers used as indexes for the VertexArray of the ObjectSet
	class LinesObject : public BaseObject
	{
		friend class HIKDrawObject;
	public:
		LinesObject();
		virtual ~LinesObject();

		void addLine( int in_StartVtxID, int in_EndVtxID );
		void setWidth( float in_fWidth )
		{
			m_Width = in_fWidth;
		}

		float getWidth() const 
		{
			return m_Width;
		}
		int getNbLines() const;
		void getLineVertices( int in_LineID, int & out_StartVtxID, int & out_EndVtxID ) const;

	private:
		typedef HIKPair<int,int> LineInfo;
        typedef HIKVector<LineInfo> LineVector;
		
        LineVector m_Lines;
		float m_Width;
	};

	// Object of type "OBJECT_TRIANGLES"
	// The triangles are not necessarily adjacent.
	// Each triangle stores three integers used as indexes for the VertexArray of the ObjectSet
	class TrianglesObject : public BaseObject
	{
		friend class HIKDrawObject;
	public:
		TrianglesObject();
		virtual ~TrianglesObject();

		void addTriangle( int in_vtxID0, int in_vtxID1, int in_vtxID2 );
		int getNbTriangles() const;
		void getTriangleVertices( int in_TriangleID, int & out_VtxID0, int & out_VtxID1, int & out_VtxID2 ) const;

	private:
		struct TriangleInfo
		{
            TriangleInfo() {;}
			TriangleInfo( int in0, int in1, int in2 )
				: v0(in0)
				, v1(in1)
				, v2(in2)
			{
			}
			int v0;
			int v1;
			int v2;
		};
        typedef HIKVector<TriangleInfo> TriangleVector;

		TriangleVector m_Triangles;
	};

	class SphereObject : public BaseObject
	{
		friend class HIKDrawObject;
	public:
		SphereObject()
			: BaseObject( OBJECT_SPHERE )
		{
		}
		virtual ~SphereObject()
		{
		}

		void setTransfo( const float in_position[3], float in_radius )
		{
			m_pos[0] = in_position[0];
			m_pos[1] = in_position[1];
			m_pos[2] = in_position[2];
			m_radius = in_radius;
		}
		const float * getPosition() const
		{
			return m_pos;
		}
		float getRadius() const
		{
			return m_radius;
		}
	private:
		float m_pos[3];
		float m_radius;
	};

	// This class stores the vertex positions of all objects found in an object set.
	class VertexArray
	{
	public:
		struct XYZ
		{
			XYZ()
			{}
			XYZ( float in_x, float in_y, float in_z )
				: x(in_x)
				, y(in_y)
				, z(in_z)
			{
			}
			float x;
			float y;
			float z;
		};
		VertexArray();
		~VertexArray();
		void clear();
		void attachExternal( float (*in_pExternalArray)[3] );
		const float * getPos( int in_index ) const;
		void setPos( int in_index, const float in_pos[3] );
		void addVertex( const float in_pos[3] ) ;
		int size() const ;
		bool HasExternalArray() const
		{
			return m_pExternalArray != NULL;
		}	

	private:
        typedef HIKVector<XYZ> VertexVector;
		
        VertexVector m_Vertices;
		int m_NbExternalVertices;
		float (*m_pExternalArray)[3];
	};

	// all objects in an object set share the same array of positions
	// For instance, a skeleton is an object set where each bone is an object
	// because a parent bone and a child bone will share the joint vertex.
	class ObjectSet
	{
		friend class HIKDrawObject;
	public:
		ObjectSet();
		~ObjectSet();

		void clear();
		int getNbVertices() const;
		const float * getVtxPosition( int in_vtxID ) const;
		void getBBox( float out_min[3], float out_max[3] ) const
		{
			out_min[0] = m_Min[0];
			out_min[1] = m_Min[1];
			out_min[2] = m_Min[2];
			out_max[0] = m_Max[0];
			out_max[1] = m_Max[1];
			out_max[2] = m_Max[2];
		}
		void updateObjectBBox( BaseObject * in_pBaseObject, const float in_pos[3] )
		{
			HIKDrawObjectNS::updateMinMax( in_pos, in_pBaseObject->m_Min, in_pBaseObject->m_Max );
			HIKDrawObjectNS::updateMinMax( in_pos, m_Min, m_Max );
		}
		void resetBBox() ;
		int getNbObjects() const ; // e.g.: how many bones for a skeleton object set ?
		const BaseObject * getObject( int in_ObjectID ) const;
		void attachExternalVertexData( float (*in_pExternalVertexData)[3] );

	private:
		VertexArray m_VertexArray;

        HIKVector<BaseObject*> m_Objects;
		int m_VtxBeingUpdated;
		int m_ObjectBeingUpdated;
		float m_Min[3];
		float m_Max[3];	
	};

	typedef enum { 
		CREATE_SKELETON_BONE = 1<<0,
		CREATE_SKELETON_NODE_AXIS = 1<<1,
		CREATE_SKELETON_NODE_SPHERE = 1<<2,
		CREATE_SKELETON_NODE_LIMITS = 1<<3,
		CREATE_SKELETON_NEXT_FLAG = 1<<4,
	} ESkeletonFlags;

	#define CREATE_SKELETON_ALL_FLAGS ( (ESkeletonFlags)( CREATE_SKELETON_NEXT_FLAG-1 ) )

	typedef enum { 
		CREATE_EFFECTOR_AXIS = 1<<0,
		CREATE_EFFECTOR_SPHERE = 1<<1,
		CREATE_EFFECTOR_NEXT_FLAG = 1<<2,
	} EEffectorsFlags;

	#define CREATE_EFFECTORS_ALL_FLAGS ( (EEffectorsFlags)( CREATE_EFFECTOR_NEXT_FLAG-1 ) )

	typedef enum {
		SQUARE_BIPYRAMID,
		SQUARE_PRISM
	} EBoneType;

	class RotLimitSettings
	{
	public:
		RotLimitSettings()
			: m_fBoneRatioForRoll( 0.4F )
			, m_fRollRadius( -16.0F ) // -16 means 1/16 of spine length
			, m_fMaxBoneLengthRatioForRollRadius( 0.4F ) // roll radius shall not exceed bone length
			, m_fYawPitchRadius( -16.0F ) // -16 means 1/16 of spine length
			, m_fMaxBoneLengthRatioForYawPitchRadius( 0.4F )	// yaw pitch radius shall not exceed 15% of bone length
																// this needs to be bigger than 10% because we use 10% for node spheres
																// and we want the limit sphere to be bigger than the node sphere
			, m_RollFullCircleResolution( 32 )
			, m_YawPitchFullCircleResolution( 32 )
			, m_YawPitchNbSteps( 32 )
		{
		};

		float getRollRadius( float in_BoneLength ) const
		{
			if( m_fMaxBoneLengthRatioForRollRadius <= 0.0F )
				return m_fRollRadius;
			float maxRadius = m_fMaxBoneLengthRatioForRollRadius * in_BoneLength;
			return m_fRollRadius > maxRadius ? maxRadius : m_fRollRadius;
		}
		float getYawPitchRadius( float in_BoneLength ) const
		{
			if( m_fMaxBoneLengthRatioForYawPitchRadius <= 0.0F )
				return m_fYawPitchRadius;
			float maxRadius = m_fMaxBoneLengthRatioForYawPitchRadius * in_BoneLength;
			return m_fYawPitchRadius > maxRadius ? maxRadius : m_fYawPitchRadius;
		}

		float m_fBoneRatioForRoll;
		float m_fRollRadius;
		float m_fMaxBoneLengthRatioForRollRadius;	// clamp m_fRollRadius to X as a max limit, where X is m_fMaxBoneLengthRatioForRollRadius*boneLength.
													// boneLength is the smallest bone coming to the node or any outgoing from the node
													// Do not do this clamping if m_fMaxBoneLengthRatioForRollRadius is zero (or negative)

		float m_fYawPitchRadius;
		float m_fMaxBoneLengthRatioForYawPitchRadius;	// clamp m_fYawPitchRadius to X as a max limit, where X is m_fMaxBoneLengthRatioForYawPitchRadius*boneLength.
														// boneLength is the smallest bone coming to the node or any outgoing from the node
														// Do not do this clamping if m_fMaxBoneLengthRatioForYawPitchRadius is zero (or negative)
		int m_RollFullCircleResolution; // tells how many segments there should be on the polyline drawn along the full roll circle
		int m_YawPitchFullCircleResolution; // tells how many segments there should be on the polyline drawn along a full yaw or pitch circle
		int m_YawPitchNbSteps;	// Tells how many yaw or pitch arcs we would draw around the whole sphere
								// In other words:
								// If there is no limit for yaw then this is the number of pitch arcs
								// If there is no limit for pitch then this is the number of yaw arcs
	};

	// This class describes the style of the geometries created by createEffectors
	class EffectorsStyle
	{
	public:
		EffectorsStyle() 
			: m_fSphereRadius( -64.0F ) // -64 means 1/64 of the spine length
			, m_fAxisLength( -10.0F ) // -10 means 1/10 of the spine length
			, m_eFlags( CREATE_EFFECTORS_ALL_FLAGS )
		{
		}
		EEffectorsFlags m_eFlags;
		float m_fSphereRadius;
		float m_fAxisLength;
	};

	// This class describes the style of the geometries created by createSkeleton
	// There is only one bone type for now and it's a square bipyramid (couldn't find a better name ... sorry)
	class SkeletonStyle
	{
		friend class HIKDrawObject;
	public:
		SkeletonStyle() 
			: m_eBoneType( SQUARE_BIPYRAMID )
			, m_fBoneRadius( -64.0F ) // -64 means 1/64 of spine length
			, m_fMaxBoneLengthRatioForBoneRadius( 0.1F ) // bone radius shall not exceed 10% of the bone length
			, m_fNodeSphereRadius( -64.0F ) // -64 means 1/64 of spine length
			, m_fMaxBoneLengthRatioForNodeSphereRadius( 0.2F ) // 1/3 of the bone length is for sphere1, 1/3 is for the bone and 1/3 is for sphere2... as a minimum...
			, m_fNodeAxisLength( -10.0F ) // -10 means 1/10 of spine length
			, m_fMaxBoneLengthRatioForNodeAxisLength( 0.6F )
			, m_Flags( CREATE_SKELETON_ALL_FLAGS )
		{ 
		}

		void setFlags( ESkeletonFlags in_Flags )
		{
			m_Flags = in_Flags;
		}

		ESkeletonFlags getFlags() const
		{
			return m_Flags;
		}

		void setBoneType( EBoneType in_eBoneType )
		{
			m_eBoneType = in_eBoneType;
		}

		EBoneType getBoneType() const 
		{ 
			return m_eBoneType; 
		}

		void setBoneRadius( float in_radius, float in_MaxBoneLengthRatioForBoneRadius = 0.0F )
		{
			m_fBoneRadius = in_radius;
			m_fMaxBoneLengthRatioForBoneRadius = in_MaxBoneLengthRatioForBoneRadius;
		}
		float getBoneRadius( float in_BoneLength ) const 
		{ 
			if( m_fMaxBoneLengthRatioForBoneRadius <= 0.0F )
				return m_fBoneRadius;
			float maxRadius = m_fMaxBoneLengthRatioForBoneRadius * in_BoneLength;
			return m_fBoneRadius > maxRadius ? maxRadius : m_fBoneRadius;
		}
		void setNodeSphereRadius( float in_radius, float in_MaxBoneLengthRatioForNodeSphereRadius = 0.0F )
		{
			m_fNodeSphereRadius = in_radius;
			m_fMaxBoneLengthRatioForNodeSphereRadius = in_MaxBoneLengthRatioForNodeSphereRadius;
		}
		float getNodeSphereRadius( float in_BoneLength ) const 
		{ 
			if( m_fMaxBoneLengthRatioForNodeSphereRadius <= 0.0F )
				return m_fNodeSphereRadius;
			float maxRadius = m_fMaxBoneLengthRatioForNodeSphereRadius * in_BoneLength;
			return m_fNodeSphereRadius > maxRadius ? maxRadius : m_fNodeSphereRadius;
		}
		void setNodeAxisLength( float in_length, float in_MaxBoneLengthRatioForNodeAxisLength = 0.0F )
		{
			m_fNodeAxisLength = in_length;
			m_fMaxBoneLengthRatioForNodeAxisLength = in_MaxBoneLengthRatioForNodeAxisLength;
		}
		float getNodeAxisLength( float in_BoneLength ) const
		{ 
			if( m_fMaxBoneLengthRatioForNodeAxisLength <= 0.0F )
				return m_fNodeAxisLength;
			float maxLength = m_fMaxBoneLengthRatioForNodeAxisLength * in_BoneLength;
			return m_fNodeAxisLength > maxLength ? maxLength : m_fNodeAxisLength;
		}
		void setRotationLimitSettings( const RotLimitSettings & in_rNewSettings )
		{
			m_RotLimitSettings = in_rNewSettings;
		}
		const RotLimitSettings & getRotationLimitSettings() const
		{
			return m_RotLimitSettings; 
		}

	private:
		EBoneType m_eBoneType;
		ESkeletonFlags m_Flags;

		float m_fBoneRadius;
		float m_fMaxBoneLengthRatioForBoneRadius;	// clamp m_fBoneRadius to X as a max limit, where X is m_fMaxBoneLengthRatioForBoneRadius*boneLength.
													// Do not do this clamping if m_fMaxBoneLengthRatioForBoneRadius is zero (or negative)
		float m_fNodeSphereRadius;
		float m_fMaxBoneLengthRatioForNodeSphereRadius; // clamp m_fNodeSphereRadius to X as a max limit, where X is m_fMaxBoneLengthRatioForNodeSphereRadius*boneLength.
														// boneLength is the smallest bone coming to the node or any outgoing from the node
														// Do not do this clamping if m_fMaxBoneLengthRatioForNodeSphereRadius is zero (or negative)

		float m_fNodeAxisLength;
		float m_fMaxBoneLengthRatioForNodeAxisLength;	// clamp m_fNodeAxisLength to X as a max limit, where X is m_fMaxBoneLengthRatioForNodeAxisLength*boneLength.
														// boneLength is the smallest bone coming to the node or any outgoing from the node
														// Do not do this clamping if m_fMaxBoneLengthRatioForNodeAxisLength is zero (or negative)

		RotLimitSettings m_RotLimitSettings;
	};

	///////////////////////////////////////////////////////////////
	// HIKDrawObject IS THE MAIN CLASS 
	// YOU INSTANTIATE IN ORDER TO GENERATE SOME DRAWING
	// GEOMETRIES FOR BONES, EFFECTORS, FLOOR CONTACTS, ETC...
	///////////////////////////////////////////////////////////////

	class HIKDrawObject
	{
	public:
		HIKDrawObject();
		~HIKDrawObject();

		//////////////////////////////////////////////
		// TO CREATE SKELETON BONES:
		//////////////////////////////////////////////
		void createSkeleton( SkeletonStyle in_Style, const HIKCharacter * in_pChar, const HIKCharacterState * in_pCharState );
		void updateSkeleton( float (*out_NewPositions)[3] );
		const ObjectSet * getSkeleton() const
		{
			return &m_Skeleton;
		}

		//////////////////////////////////////////////
		// TO CREATE EFFECTORS:
		//////////////////////////////////////////////
		void createEffectors( EffectorsStyle in_Style, const HIKCharacter * in_pChar, const HIKEffectorSetState * in_pEffectors );
		void updateEffectors( float (*out_NewPositions)[3] );
		const ObjectSet * getEffectors() const
		{
			return &m_Effectors;
		}

		//////////////////////////////////////////////
		// TO CREATE FLOOR CONTACTS:
		//////////////////////////////////////////////
		void createFloorContacts(	const HIKCharacter * in_pChar, 
									const HIKCharacterState * in_pCharState,
									const HIKEffectorSetState * in_pEffectorSetState, 
									const HIKPropertySetState * in_pPropertySetState );
		void updateFloorContacts( float (*out_NewPositions)[3] );
		const ObjectSet * getFloorContacts() const
		{
			return &m_FloorContacts;
		}

		const HIKCharacter * GetHIKCharacter() const { return m_pChar; }
		const HIKCharacterState * GetHIKCharacterState() const { return m_pCharState; }
		const HIKEffectorSetState * GetHIKEffectorSetState() const { return m_pEffectorSetState; }
		const HIKPropertySetState * GetHIKPropertySetState() const { return m_pPropertySetState; }
		
		void SetCharacterState(const HIKCharacterState * in_pCharState){m_pCharState = in_pCharState;}
		void SetEffectorSetState(const HIKEffectorSetState * in_pEffectorSetState){m_pEffectorSetState = in_pEffectorSetState;}
		void SetPropertySetState(const HIKPropertySetState * in_pPropertySetState){m_pPropertySetState = in_pPropertySetState;}

	private:
		void buildSquareBiPyramid( int in_ParentHIKNodeID, int in_ChildHIKNodeID, int startVtxID, const float start[3], int endVtxID, const float end[3], const float mat[16], float in_BoneLength );
		void buildSquarePrism( int in_ParentHIKNodeID, int in_ChildHIKNodeID, int startVtxID, const float start[3], int endVtxID, const float end[3], const float mat[16], float in_BoneLength );
		void buildAxis( int originVtxID, ObjectSet & out_ObjectSet, const float origin[3], const float mat[16], float parentBoneLength);

		void visitNodes();
		// btw: in_NodeMat and vertexID are both ignored when in_NodeID==0 (i.e.: very first call)
		void visitNode( int nodeID, const float in_ParentNodeMat[16], const float in_NodeMat[16], int vertexID, float in_ParentBoneLength );

		void drawRotationLimits( int in_NodeID, const float in_ParentNodeMat[16], const float in_NodeMat[16], float in_smallestBoneLength );
		void drawNodeSphere( int nodeID, const float in_NodeMat[16], int vertexID, float in_smallestBoneLength );

		void visitEffectors();
		void visitFloorContacts();

	private:
		ObjectSet m_Skeleton;
		ObjectSet m_Effectors;
		ObjectSet m_FloorContacts;

		typedef enum { 
			CREATE,
			UPDATE,
		} EVisitMode;

		EVisitMode m_eVisitMode;
		SkeletonStyle m_SkeletonStyle;
		EffectorsStyle m_EffectorsStyle;

		const HIKCharacter * m_pChar;
		const HIKCharacterState * m_pCharState;
		const HIKEffectorSetState * m_pEffectorSetState;
		const HIKPropertySetState * m_pPropertySetState;

		float m_CharUpVec[3]; // (1,0,0) means X up, (0,1,0) means Y up, (0,0,1) means Z up
	};

} // namespace HIKDrawObject

#endif // #ifndef HIKDRAWOBJECT_H
