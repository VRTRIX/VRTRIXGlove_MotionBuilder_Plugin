#ifndef __FBOPTICAL_H__
#define __FBOPTICAL_H__
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

/**	\file fboptical.h
*	Generic optical motion capture device interface.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#ifndef FB_KERNEL

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbmodel.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

    __FB_FORWARD( FBModelOptical );

    FB_DEFINE_COMPONENT( FBSDK_DLL, ModelOptical			);
    FB_DEFINE_COMPONENT( FBSDK_DLL, ModelMarkerOptical	);
    FB_DEFINE_COMPONENT( FBSDK_DLL, RigidBody			);
    FB_DEFINE_COMPONENT( FBSDK_DLL, Take );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBOpticalSegement
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBOpticalSegment );
    //! Optical segment class.
    class FBSDK_DLL FBOpticalSegment : public FBComponent
    {
        __FBClassDeclare( FBOpticalSegment, FBComponent );
    public:
        /** Constructor.
        *	\param	pOptical	Optical model(default=NULL).
        */
        FBOpticalSegment(FBModelOptical* pOptical=NULL);

        /**	Constructor
        *	\param	pSegment	Optical segment to copy information from.
        */
        FBOpticalSegment( const FBOpticalSegment &pSegment );

        /**	Overloaded == operator.
        *	\param	pValue	Segment to compare with.
        *	\return	\b true if equal.
        */
        bool operator==(const FBOpticalSegment &pValue) const;

        /** Overloaded = operator.
        *	\param	pValue	Segment to copy.
        *	\return Copied segment.
        */
        FBOpticalSegment& operator=(const FBOpticalSegment& pValue);

        /** Reset the marker segment.
        */
        virtual void Reset();

        /**	Cut the segment for the marker at a given time.
        *	\param	pTime	Time to cut segment at.
        */
        virtual void Cut( FBTime& pTime );

        /** Check if valid (if item exists).
        *	\return	\b true if segment is valid.
        */
        virtual bool IsValid();

        // original
        FBPropertyTimeSpan				OriginalTimeSpan;	//!< <b>Property:</b> Original timespan for segment.
        FBPropertyTimeSpan				TimeSpan;			//!< <b>Property:</b> Current segment timespan.
        FBPropertyAnimationNode			Data;				//!< <b>Property:</b> Segment curve data.
        FBPropertyBool					Used;				//!< <b>Property:</b> Is segment used?

        // from marker
        FBPropertyModelMarkerOptical	Marker;				//!< <b>Property:</b> Optical marker.
        FBPropertyTimeSpan				MarkerTimeSpan;		//!< <b>Property:</b> Marker/Segment timespan.

        friend class FBPropertyListOpticalSegment;
        friend class FBPropertyListMarkerSegment;

    private:
        void FBOpticalSegmentInitProperties();
    };
    FB_DEFINE_COMPONENT	( FBSDK_DLL, OpticalSegment );
    FB_DEFINE_ARRAY		( FBSDK_DLL, OpticalSegment );
    FB_DEFINE_LIST		( FBSDK_DLL, OpticalSegment );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListMarkerSegment
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBPropertyListMarkerSegment );

    //! \b PropertyList: Device optical marker
    class FBSDK_DLL FBPropertyListMarkerSegment : public FBPropertyBaseList< FBOpticalSegment >
    {
    private:
        FBArrayTemplate< FBOpticalSegment* > mItems;
        virtual int Add( FBOpticalSegment pItem );
        virtual void Refresh();
    public:
        FBPropertyListMarkerSegment();
        virtual ~FBPropertyListMarkerSegment();
        /**	Remove property at \e pIndex.
        *	\param pIndex  Index where property is to be removed.
        */
        virtual void RemoveAt ( int pIndex );

        /**	[] operator overload.
        *	\param pIndex  Index of property to access.
        *	\return Property at \e pIndex.
        */
        virtual FBOpticalSegment operator[]( int pIndex );

        /**	Get the number of properties in the list.
        *	\return The number of properties in the list.
        */
        virtual int GetCount();

        /**	Get the segment index at a given time.
        *	\param pTime	Time to search for segment index.
        *	\return Index of segment found, -1 if no segment found at \e pTime.
        */
        virtual int GetIndexAt( FBTime& pTime );
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListOpticalSegment
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBPropertyListOpticalSegment );
    FB_DEFINE_LIST( FBSDK_DLL, OpticalSegment );

    //! \b PropertyList: Device optical marker
    class FBSDK_DLL FBPropertyListOpticalSegment : public FBPropertyBaseList< FBOpticalSegment >
    {
    private:
        FBArrayTemplate< FBOpticalSegment* > mItems;
        virtual int Add( FBOpticalSegment pItem );
        virtual void Refresh();
    public:
        FBPropertyListOpticalSegment();
        virtual ~FBPropertyListOpticalSegment();
        /**	Remove property at \e pIndex.
        *	\param pIndex  Index where property is to be removed.
        */
        virtual void RemoveAt( int pIndex );

        /**	[] operator overload.
        *	\param pIndex  Index of property to access.
        *	\return Property at \e pIndex.
        */
        virtual FBOpticalSegment operator[]( int pIndex );

        /**	Get the number of properties in the list.
        *	\return The number of properties in the list.
        */
        virtual int GetCount();

        /**	Add a segment to the optical model.
        *	\param pData	Segment data to add.
        *	\return Index of inserted segment.
        */
        virtual int Add( FBAnimationNode* pData );
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // Gap mode
    ////////////////////////////////////////////////////////////////////////////////////
    //! Gap interpolation modes.
    enum FBGapMode	{
        kFBGapRigidBody,	//!< Use rigid body information.
        kFBGapConstant,		//!< Constant interpolation.
        kFBGapLinear,		//!< Linear interpolation.
        kFBGapBezier,		//!< Bezier interpolation.
        kFBGapCurve,		//!< Cubic/curve interpolation.
        kFBGapSample		//!< Sampled data.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, GapMode );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBOpticalGap
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBOpticalGap );
    //! Optical Gap class.
    class FBSDK_DLL FBOpticalGap : public FBComponent
    {
        __FBClassDeclare( FBOpticalGap, FBComponent );
    public:
        /**	Constructor.
        *	\param	pMarker 	Model marker(default=NULL).
        */
        FBOpticalGap(FBModelMarkerOptical* pMarker=NULL);

        /** Constructor (copy).
        *	\param	pGap		Gap to copy data from.
        */
        FBOpticalGap(const FBOpticalGap& pGap);

        /**	Overloaded == operator.
        *	\param	pValue	Gap to compare with.
        *	\return	\b true if equal.
        */
        bool operator==(const FBOpticalGap &pValue) const;

        /** Overloaded = operator.
        *	\param	pValue	Gap to copy.
        *	\return Copied gap.
        */
        FBOpticalGap& operator=(const FBOpticalGap& pValue);

        /**	Insert a control key for the gap.
        *	\param pTime  Insert time for the control key.
        */
        virtual void InsertControlKey( FBTime& pTime );

        /** Check if valid (if item exists).
        *	\return	\e true if segment is valid.
        */
        virtual bool IsValid();

        FBPropertyTimeSpan			TimeSpan;			//!< <b>Property:</b> Current timespan.
        FBPropertyGapMode			Interpolation;		//!< <b>Property:</b> Gap mode.
        FBPropertyAnimationNode		Data;				//!< <b>Property:</b> Gap curve data.

        friend class FBPropertyListOpticalGap;

    private:
        void FBOpticalGapInitProperties();
    };
    FB_DEFINE_COMPONENT	( FBSDK_DLL, OpticalGap );
    FB_DEFINE_ARRAY		( FBSDK_DLL, OpticalGap );
    FB_DEFINE_LIST		( FBSDK_DLL, OpticalGap );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListOpticalGap
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBPropertyListOpticalGap );

    //! \b PropertyList: Device optical marker
    class FBSDK_DLL FBPropertyListOpticalGap : public FBPropertyBaseList< FBOpticalGap >
    {
    private:
        FBArrayTemplate< FBOpticalGap* > mItems;
        virtual int		Add( FBOpticalGap pItem );
        virtual void	RemoveAt( int pIndex );
        virtual void	Refresh();
    public:
        FBPropertyListOpticalGap();
        virtual ~FBPropertyListOpticalGap();
        /**	[] operator overload.
        *	\param pIndex  Index of property to access.
        *	\return Property at \e pIndex.
        */
        virtual FBOpticalGap operator[]( int pIndex );

        /**	Get the number of properties in the list.
        *	\return The number of properties in the list.
        */
        virtual int GetCount();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBModelMarkerOptical
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBModelMarkerOptical);
    //! Optical model marker class.
    class FBSDK_DLL FBModelMarkerOptical : public FBModelMarker 
    {
        __FBClassDeclare( FBModelMarkerOptical,FBModelMarker );
    public:
        /**	Constructor.
        *   If no optical model is given, be sure to add one before accessing the Segments and Gaps properties.
        *	\param	pName		Name of optical marker(default=NULL).
        *	\param	pOptical	Optical model(default=NULL).
        *	\param	pObject 	Internal parent object(default=NULL).
        */
        FBModelMarkerOptical(const char *pName = NULL, FBModelOptical* pOptical=NULL, HIObject pObject=NULL );

        /**	Begin import of optical data.
        *	Sample communication with optical device and return the number of samples that were
        *	taken during the sampling period for statistical purposes.
        *	\return	The number of samples taken.
        */
        virtual int ImportBegin();

        /**	Import a key of optical data.
        *	\param	pX			X position.
        *	\param	pY			Y position.
        *	\param	pZ			Z position(default=0.0).
        *	\param	pOcclusion	Occlusion value(default=0.0).
        *	\return	\b true if successful.
        */
        virtual bool ImportKey( double pX, double pY, double pZ=0.0, double pOcclusion=0.0 );

        /**	End importation and clean up data.
        *	Interpolates optical data to create a curve from the input key frams.
        *	\return	\b true if successful.
        */
        virtual bool ImportEnd();

        /**	Begin export of optical data.
        *	Sample communication with optical device and return the number of samples that were
        *	taken during the sampling period for statistical purposes.
        *	\return	Number of frames to export.
        */
        virtual int  ExportBegin();

        /**	Export a key of optical data.
        *	\retval	pX.			X position.
        *	\retval	pY.			Y position.
        *	\retval	pZ.			Z position(default=NULL).
        *	\retval	pOcclusion.	Occlusion value(default=NULL).
        *	\return	\b true if successful.
        */
        virtual bool ExportKey( double *pX, double *pY, double *pZ=NULL, double *pOcclusion=NULL );

        /**	End exportation from optical model.
        *	\return	\b true if successful.
        */
        virtual bool ExportEnd();

        /** Set the current optical model.
        *	\param	pOptical	New optical model.
        */
        virtual void SetModelOptical( FBModelOptical* pOptical );

        /**	Insert segmented data.
        *	\param pTData	Translation data.
        *	\param pOData	Occlusion data.
        */
        virtual void InsertSegmentedData( FBAnimationNode* pTData, FBAnimationNode* pOData );

        /**	Get the rigid body for the marker.
        *	\return	Rigid body for marker (check IsValid())
        */
        virtual FBRigidBody	GetRigidBody();

        FBPropertyModelOptical			Optical;		//!< <b>Property:</b> Optical model.
        FBPropertyListMarkerSegment		Segments;		//!< <b>Property:</b> Marker segments.
        FBPropertyListOpticalGap		Gaps;			//!< <b>Property:</b> Gaps.
        FBPropertyColor					Color;			//!< <b>Property:</b> Marker color.
        FBPropertyBool					Done;			//!< <b>Property:</b> Done?
        FBPropertyAnimationNode			Data;			//!< <b>Property:</b> Data.
    private:
        void FBModelMarkerOpticalInitProperties();
    };
    FB_DEFINE_ARRAY	( FBSDK_DLL, ModelMarkerOptical );
    FB_DEFINE_LIST	( FBSDK_DLL, ModelMarkerOptical );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListModelMarkerOptical
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBPropertyListModelMarkerOptical );

    //! \b PropertyList: Device optical marker
    class FBSDK_DLL FBPropertyListModelMarkerOptical : public FBPropertyBaseList< FBModelMarkerOptical* >
    {
    private:
        FBArrayTemplate< FBModelMarkerOptical* > mItems;
    public:
        FBPropertyListModelMarkerOptical();
        virtual ~FBPropertyListModelMarkerOptical();
        //! Refresh marker list.
        virtual void Refresh ();

        /**	Remove property at \e pIndex.
        *	\param pIndex  Index where property is to be removed.
        */
        virtual void RemoveAt( int pIndex );

        /**	[] operator overload.
        *	\param pIndex  Index of property to access.
        *	\return Property at \e pIndex.
        */
        virtual FBModelMarkerOptical* operator[]( int pIndex );

        /**	Get the number of properties in the list.
        *	\return The number of properties in the list.
        */
        virtual int GetCount ();

        /**	Add a new optical marker to the list
        *	\param	pName	Name of new optical marker(default=NULL).
        */
        virtual int Add( const char* pName = NULL );

        /** Add a new optical marker to the list.
        *	\param	pItem	New marker to add to list.
        */
        virtual int	Add( FBModelMarkerOptical* pItem );
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListRigidBodyMarkers
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBPropertyListRigidBodyMarkers );
    FB_DEFINE_LIST( FBSDK_DLL, ModelMarkerOptical );

    //! \b PropertyList: Device optical marker
    class FBSDK_DLL FBPropertyListRigidBodyMarkers : public FBPropertyBaseList< FBModelMarkerOptical* >
    {
    private:
        FBArrayTemplate< FBModelMarkerOptical* > mItems;
    public:
        FBPropertyListRigidBodyMarkers();
        virtual ~FBPropertyListRigidBodyMarkers();
        //! Refresh marker list.
        virtual void Refresh();

        /**	Remove property at \e pIndex.
        *	\param pIndex  Index where property is to be removed.
        */
        virtual void RemoveAt( int pIndex );

        /**	[] operator overload.
        *	\param pIndex  Index of property to access.
        *	\return Property at \e pIndex.
        */
        virtual FBModelMarkerOptical* operator[]( int pIndex );

        /**	Get the number of properties in the list.
        *	\return The number of properties in the list.
        */
        virtual int GetCount ();

    public:
        /**	Add a new optical marker to the list
        *	\param	pName	Name of new optical marker(default=NULL).
        */
        virtual int Add( const char* pName = NULL );
        /** Add a new optical marker to the list.
        *	\param	pItem	New marker to add to list.
        *	\return Number of markers in list after operation.
        */
        virtual int	Add( FBModelMarkerOptical* pItem );
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // Rigid body mode
    ////////////////////////////////////////////////////////////////////////////////////
    //! Rigid body modes.
    enum FBRigidBodyMode {
        kFBRigidBodyFast,	//!< Fast rigid body mode.
        kFBRigidBodyBest	//!< Best rigid body mode.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, RigidBodyMode );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBRigidBody
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBRigidBody );
    //! Rigid body class.
    class FBSDK_DLL FBRigidBody : public FBComponent
    {
        __FBClassDeclare( FBRigidBody, FBComponent );
    public:
        /** Constructor.
        *	\param	pOptical	Optical model(default=NULL).
        */
        FBRigidBody(FBModelOptical* pOptical=NULL);

        /**	Constructor
        *	\param	pRigidBody	Rigid body to copy information from.
        */
        FBRigidBody( const FBRigidBody &pRigidBody );

        /**	Overloaded == operator.
        *	\param	pValue	Segment to compare with.
        *	\return	\b true if equal.
        */
        bool operator==(const FBRigidBody &pValue) const;

        /** Overloaded = operator.
        *	\param	pValue	Segment to copy.
        *	\return Copied segment.
        */
        FBRigidBody& operator=(const FBRigidBody& pValue);

        /**	Snap the rigid body.
        */
        virtual void Snap();

        /**	Compute the rigid body animation.
        */
        virtual void ComputeAnimation();

        /** Check if valid (if item exists).
        *	\return	\e true if segment is valid.
        */
        virtual bool IsValid();

        FBPropertyListRigidBodyMarkers		Markers;		//!< <b>Property:</b> List of markers composing the rigid body.
        FBPropertyModel						Model;			//!< <b>Property:</b> Rigid body model.
        FBPropertyAnimationNode				QualityData;	//!< <b>Property:</b> Quality of rigid body.
        FBPropertyBool						Done;			//!< <b>Property:</b> Done?
        FBPropertyRigidBodyMode				Mode;			//!< <b>Property:</b> Rigid body mode.
        FBPropertyInt						SmoothWidth;	//!< <b>Property:</b> Smoothing width.

        friend class FBPropertyListRigidBody;
    private:
        void FBRigidBodyInitProperties();

    };
    FB_DEFINE_ARRAY	( FBSDK_DLL, RigidBody	);
    FB_DEFINE_LIST	( FBSDK_DLL, RigidBody );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListRigidBody
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBPropertyListRigidBody );

    //! \b PropertyList: Device optical marker
    class FBSDK_DLL FBPropertyListRigidBody : public FBPropertyBaseList< FBRigidBody >
    {
    private:
        FBArrayTemplate< FBRigidBody* >	mItems;
        virtual int		Add		( FBRigidBody pItem );
        virtual void	Refresh ();
    public:
        FBPropertyListRigidBody();
        virtual ~FBPropertyListRigidBody();
        /**	Remove property at \e pIndex.
        *	\param pIndex  Index where property is to be removed.
        */
        virtual void RemoveAt( int pIndex );

        /**	[] operator overload.
        *	\param pIndex  Index of property to access.
        *	\return Property at \e pIndex.
        */
        virtual FBRigidBody operator[]( int pIndex );

        /**	Get the number of properties in the list.
        *	\return The number of properties in the list.
        */
        virtual int GetCount();

        /**	Add a new rigid body to the list.
        *	\param	pList	List of models to compose the rigid body.
        *	\param	pName	Name of rigid body(default=NULL).
        *	\return	Number of rigid bodies in list.
        */
        virtual int Add( FBModelList& pList, const char* pName=NULL);
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBModelOptical
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBModelOptical );
    //! Optical model class.
    class FBSDK_DLL FBModelOptical : public FBModel 
    {
        __FBClassDeclare( FBModelOptical,FBModel );
    public:
        /**	Constructor.
        *	\param	pName		Name of optical model.
        *	\param	pObject 	Internal parent object(default=NULL).
        */
        FBModelOptical(const char * pName, HIObject pObject=NULL);

        /**	Setup importation for optical model.
        *	\return	\b true if successful.
        */
        virtual bool ImportSetup();

        /**	Setup exportation from optical model.
        *	\return	\b true if successful.
        */
        virtual bool ExportSetup();

        /** Clear the segments (by default only the unused).
        *	\param	pUnUsedOnly 	Clear only the unused segments if \b true(default=true).
        */
        virtual void ClearSegments( bool pUnUsedOnly = true );

        /** Create a new rigid body from the given optical markers.
        *	\param	pRigidBodyName 	The name for the new rigid body to create. If left empty, the default "Rigid Body" name will be used.
        *	\param	pMarkers 		The optical markers for creating the new rigid body.
        *	\return	The created rigid body if successful, and invalid rigid body otherwise. You can use the FBRigidBody.IsValid() method to test if the returned rigid body object is valid or not.
        */
        FBRigidBody CreateRigidBody( const char* pRigidBodyName, FBArrayTemplate<FBModelMarkerOptical*> pMarkers );

        FBPropertyDouble					MarkerSize;			//!< <b>Read Write Property:</b> Size of markers.
        FBPropertyTime						SamplingStart;		//!< <b>Read Write Property:</b> Sampling start time.
        FBPropertyTime						SamplingStop;		//!< <b>Read Write Property:</b>Sampling stop time.
        FBPropertyTime						SamplingPeriod;		//!< <b>Read Write Property:</b>Sampling period.

        FBPropertyListModelMarkerOptical	Markers;			//!< <b>List:</b> Markers.
        FBPropertyListOpticalSegment		Segments;			//!< <b>List:</b> Segments.
        FBPropertyListRigidBody				RigidBodies;		//!< <b>List:</b> Rigid bodies.
    };


    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListModelOptical
    ////////////////////////////////////////////////////////////////////////////////////
    FB_DEFINE_LIST( FBSDK_DLL, ModelOptical );
    FB_FORWARD( FBPropertyListModelOptical );

    //! \b PropertyList: ModelOptical.
    class FBSDK_DLL FBPropertyListModelOptical : public FBPropertyListComponent
    {
    public:
        FBPropertyListModelOptical();
        /**	Get the ModelOptical at \e pIndex.
        *	\param	pIndex	Index of ModelOptical to get.
        *	\return ModelOptical at \e pIndex.
        */
        FBModelOptical* operator[](int pIndex);
    };


    ////////////////////////////////////////////////////////////////////////////////////
    // FBGenerationMode
    ////////////////////////////////////////////////////////////////////////////////////
    //! Generation modes for optical model.
    enum FBGenerationMode	{
        kFBGenerationNone,	//!< No re-generation.
        kFBGenerationFast	//!< Fast re-generation.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, GenerationMode );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBControllerMode
    ////////////////////////////////////////////////////////////////////////////////////
    //! Controller modes for optical model.
    enum FBControllerMode	{
        kFBControllerNone,			//!< No controller mode.
        kFBControllerLabelling,		//!< Labelling controller.
        kFBControllerSegment,		//!< Segment controller.
        kFBControllerRigidBody		//!< Rigid body controller.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, ControllerMode );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBSegmentMode
    ////////////////////////////////////////////////////////////////////////////////////
    //! Segment modes.
    enum FBSegmentMode	{
        kFBSegmentMarker,			//!< Use marker.
        kFBSegmentRigidBody,		//!< Use rigid body.
        kFBSegmentAll				//!< Use all.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, SegmentMode );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBInsertSegmentMode
    ////////////////////////////////////////////////////////////////////////////////////
    //! Insert segment modes
    enum FBInsertSegmentMode	{
        kFBInsertSegmentWhole,		//!< Insert whole.
        kFBInsertSegmentToEnd,		//!< Insert to end.
        kFBInsertSegmentFromStart	//!< Insert from start.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, InsertSegmentMode );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBModelOpticalAdvanced
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBModelOpticalAdvanced );
    //! Advanced optical model information.
    class FBSDK_DLL FBModelOpticalAdvanced : public FBComponent
    {
        __FBClassDeclare( FBModelOpticalAdvanced,FBComponent );
    public:
        /**	Constructor
        *	\param	pOptical	Optical model.
        */
        FBModelOpticalAdvanced( FBModelOptical* pOptical );

        //!	Accept all segments.
        virtual void AcceptAllSegments();

        //!	Accept current segment
        virtual void AcceptSegment();

        //!	Skip segment
        virtual void SkipSegment();

        //!	Automatic build
        virtual void AutomaticBuild();

        //! Crop segment animation.
        virtual void CropSegmentsAnimation();

        FBPropertyAnimationNode			Quality;				//!< <b>Property:</b> Rigid body quality.
        FBPropertyBool					ShowRigidQuality;		//!< <b>Property:</b> Show the rigid quality?
        FBPropertyGenerationMode		GenerationMode;			//!< <b>Property:</b> Optical genration mode.
        FBPropertyControllerMode		ControllerMode;			//!< <b>Property:</b> Controller mode.
        FBPropertySegmentMode			SegmentMode;			//!< <b>Property:</b> Segment mode.
        FBPropertyInsertSegmentMode		InsertSegmentMode;		//!< <b>Property:</b> Insert segment mode.
        FBPropertyBool					PlayToNextSegment;		//!< <b>Property:</b> Play to next segment ?
        FBPropertyBool					AutoPlayToNextSegment;	//!< <b>Property:</b> Automatic play to next segment ?
        FBPropertyDouble				MaxMatchDistance;		//!< <b>Property:</b> Max matching distance.
        FBPropertyBool					Active;					//!< <b>Property:</b> Optical engine for model active?
        FBPropertyTake					UsedTake;				//!< <b>Property:</b> Take used by optical model.
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBDeviceOpticalMarker
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBDeviceOpticalMarker );
    /** Device optical marker.
    *	A device optical marker represents the input locations for interfacing optical hardware.
    *	This type of marker corresponds uniquely to the input (from the hardware) and will be
    *	represented on-screen by a \b FBModelMarkerOptical.
    */
    class FBSDK_DLL FBDeviceOpticalMarker : public FBComponent {
        __FBClassDeclare( FBDeviceOpticalMarker,FBComponent );
    public:
        /**	Constructor.
        *	\param	pName	Name of optical marker.
        */
        FBDeviceOpticalMarker(const char *pName);

        /**	Set data for optical marker.
        *	\param	pX			X position for marker.
        *	\param	pY			Y position for marker.
        *	\param	pZ			Z position for marker(default=0.0).
        *	\param	pOcclusion	Occulsion information for marker(default=0.0).
        */
        void SetData(double pX, double pY, double pZ=0.0, double pOcclusion=0.0);

        FBPropertyBool			IsUsed;			//!< <b>Property:</b> Is marker used?
        FBPropertyVector3d		Position;		//!< <b>Property:</b> Current position of marker.
        FBPropertyDouble		Occlusion;		//!< <b>Property:</b> Occulsion data for marker.
        FBPropertyModel			Model;			//!< <b>Property:</b> Model marker access.
    };
    FB_DEFINE_ARRAY	( FBSDK_DLL, DeviceOpticalMarker );
    FB_DEFINE_LIST	( FBSDK_DLL, DeviceOpticalMarker );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListDeviceOpticalMarker
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBPropertyListDeviceOpticalMarker );

    //! \b PropertyList: Device optical marker
    class FBSDK_DLL FBPropertyListDeviceOpticalMarker : public FBPropertyBaseList< FBDeviceOpticalMarker* >
    {
        FBArrayTemplate<FBDeviceOpticalMarker*> mItems;			//!< List of items (private).
        virtual int	 Add	( FBDeviceOpticalMarker* pItem );	//!< Add an item (private)
    public:
        FBPropertyListDeviceOpticalMarker();
        virtual ~FBPropertyListDeviceOpticalMarker();
        /**	Remove a marker
        *	\param	pIndex	Index of marker to remove.
        */
        virtual void RemoveAt( int pIndex );
        /**	Get a marker.
        *	\param	pIndex	Index of marker.
        *	\return	Marker at \e pIndex.
        */
        virtual FBDeviceOpticalMarker* operator[](int pIndex);
        /**	Get the marker count.
        *	\return	Number of markers.
        */
        virtual int GetCount();

        /**	Add a marker by name.
        *	\param	pName	Name of new marker(default=NULL).
        *	\return	Number of markers after operation.
        */
        virtual int	Add( const char *pName=NULL );
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBDeviceOptical
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBDeviceOptical );
    //! Optical device class.
    class FBSDK_DLL FBDeviceOptical : public FBDevice 
    {
        __FBClassDeclare( FBDeviceOptical,FBDevice );
    public:
        friend class FBDeviceOpticalLayout;
        //IObject_Declare						( override );
        /**	Constructor.
        *	\param	pName		Unique name of optical device.
        *	\param	pObject 	Internal parent object.
        */
        FBDeviceOptical(const char* pName, HIObject pObject=NULL);

        FBPropertyListDeviceOpticalMarker	Markers;					//!< <b>List:</b> Markers.
        FBPropertyBool						SupportOcclusion;			//!< <b>Property:</b> Does the device support occulsion?
        FBPropertyBool						AutoAntialiasing;			//!< <b>Property:</b> Is it auto-antialiasing?
        FBPropertyDouble					DampingTime;				//!< <b>Property:</b> Damping time for device.
        FBPropertyModel						ModelOptical;				//!< <b>Property:</b> Optical model for manipulation.

        FBPropertyBool						ForceOpticalSamplingRate;	//!< <b>Property:</b> Force the use of the optical sampling rate?
        FBPropertyDouble					OpticalSamplingRate;		//!< <b>Property:</b> Resampling rate for optical device.
        FBPropertyBool						UseMarkerTimeStamp;			//!< <b>Property:</b> Use the individual marker timestamps?

        FBPropertyBool						SkipFrame;					//!< <b>Property:</b> Skip Record Frame
        FBPropertyTime						MarkerTimeStamp;			//!< <b>Property:</b> TimeStamp for marker.

        //----Does marker management----
        //! Begin device setup.
        void DeviceOpticalBeginSetup();		
        //! End device setup.
        void DeviceOpticalEndSetup();		

        /**	Evaluate all optical markers for the device.
        *	Pure virtual device-specific call to eval marker positions.
        *	\param	pDeviceNotifyInfo	Notification information when thread was called.
        *	\remarks	This function is the device evaluation function, called by the real-time engine.
        */
        virtual void DeviceOpticalEvalAllMarkers(FBDeviceNotifyInfo &pDeviceNotifyInfo);

        /**	Record a frame of information from device.
        *	Virtual function that derived class may overide
        *	\param	pTime				Time of evaluation.
        *	\param	pDeviceNotifyInfo	Notification information when thread was called.
        */
        virtual void DeviceOpticalRecordFrame(FBTime &pTime,FBDeviceNotifyInfo &pDeviceNotifyInfo);

        //--- See base class ---

        // Standard FBX interface functions
        virtual bool FbxStore(FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat) override;
        virtual bool FbxRetrieve(FBFbxObject* pFbxObject,kFbxObjectStore pStoreWhat) override;

        // Standard device virtual functions creation/destruction
        virtual bool FBCreate() override;
        virtual void FBDestroy() override;

        // Standard device virtual function device operation notify
        virtual bool DeviceOperation( kDeviceOperations pOperation ) override;

        // Standard device virtual functions evaluation
        virtual bool AnimationNodeNotify(FBAnimationNode* pAnimationNode,FBEvaluateInfo* pEvaluateInfo) override;
        virtual void DeviceIONotify(kDeviceIOs pAction,FBDeviceNotifyInfo &pDeviceNotifyInfo) override;

        // Standard device virtual functions recording for animation.
        virtual void RecordingInitAnimation(FBAnimationNode* pAnimationNode) override;
        virtual void RecordingDoneAnimation(FBAnimationNode* pAnimationNode) override;
    };

#ifdef FBSDKUseNamespace
}
#endif

#endif
#endif
