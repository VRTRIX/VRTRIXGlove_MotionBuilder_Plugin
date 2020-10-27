#ifndef __FBCORE_H__
#define __FBCORE_H__
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

/** \file fbcore.h
*	Contains definitions for devices, boxes and models.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbfbx.h>
#include <fbsdk/fbtime.h>
#include <fbsdk/fbdata.h>
#include <fbsdk/fbevaluateinfo.h>


// somebody at SGI defined this in their include files
// until we find which one, we remove it
#undef Status

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

    FB_DEFINE_COMPONENT( FBSDK_DLL, ModelTemplate	);
    FB_DEFINE_COMPONENT( FBSDK_DLL, Device			);
    FB_DEFINE_COMPONENT( FBSDK_DLL, Path3D			);
    FB_DEFINE_COMPONENT( FBSDK_DLL, Scene			);
    FB_DEFINE_COMPONENT( FBSDK_DLL, Model			);
    FB_DEFINE_COMPONENT( FBSDK_DLL, Device			);

    // ========================================================================================== 
    // Global definition
    // ==========================================================================================
    /** \fn kFBObjectCreatorFnc
    *	\param	pOwner	Object that own this new object
    *	\param	pName	Name of the object
    *	\param	pData	Data put in the object
    */
    typedef HIObject (* kFBObjectCreatorFnc)(HIObject pOwner,const char* pName,void *pData);

    // ==========================================================================================
    // Declaration definition
    // ==========================================================================================
    /** Box declaration.
    *	\param	ClassName	Name of box class.
    *	\param	Parent		Parent class of \e ClassName.
    */
#define FBBoxDeclare( ClassName, Parent ) \
    FBClassDeclare( ClassName,Parent ); \
public: \
    ClassName(const char* pName):Parent(pName) { FBClassInit; } \
private:

    /** Box implementation.
    *	\param	ThisComponent	Name of box class to implement.
    */
#define FBBoxImplementation( ThisComponent ) \
    FBClassImplementation( ThisComponent )

    /**	Device declaration.
    *	\param	ClassName	Name of device class.
    *	\param	Parent		Parent class of \e ClassName. 
    */
#define FBDeviceDeclare( ClassName, Parent ) \
    FBClassDeclare( ClassName,Parent ); \
public: \
    ClassName(const char* pName):Parent(pName) { FBClassInit; } \
private:

    /** Device implementation.
    *	\param	ThisComponent	Name of device class to implement.
    */
#define FBDeviceImplementation( ThisComponent ) \
    FBClassImplementation( ThisComponent )

    // ==========================================================================================
    // Register definition
    // ==========================================================================================
    /** Register a box class
    *	\param	UniqueNameStr	Unique name of class.
    *	\param	ClassName		Name of box class.
    *	\param	FolderName		Directory structure within the application.
    *	\param	Label			Short description.
    *	\param	Description		Long description.
    *   \param  IconFilename    Name of the file containing the icon.
    */
#define FBRegisterBox( UniqueNameStr, ClassName, FolderName, Label, Description, IconFilename ) \
    HIObject RegisterBox##ClassName##Create( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
    { \
    ClassName *Class = new ClassName(pName); \
    Class->mAllocated = true; \
    Class->UniqueName = UniqueNameStr; \
    if (Class->FBCreate()) { \
    return Class->GetHIObject(); \
    } else { \
    delete Class; \
    return NULL; \
    } \
    } \
    \
    FBLibraryModule( ClassName )	\
    {\
    FBRegisterObject(ClassName##R1,"Boxes",UniqueNameStr,Description,RegisterBox##ClassName##Create,true, IconFilename );\
    FBRegisterObject(ClassName##R2,"Boxes/Functions/" FolderName,Label,Description,RegisterBox##ClassName##Create,true, IconFilename );\
    FBRegisterObject(ClassName##R3,"FbxStorable/Box",UniqueNameStr,Description,RegisterBox##ClassName##Create,true, IconFilename ); \
    }

    /** Register a device class
    *	\param	UniqueNameStr	Unique name of class.
    *	\param	ClassName		Name of device class.
    *	\param	Label			Short description.
    *	\param	Description		Long description.
    *   \param  IconFilename    Name of the file containing the icon.
    */
#define FBRegisterDevice( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
    HIObject RegisterDevice##ClassName##Create( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
    { \
    ClassName *Class = new ClassName(pName); \
    Class->mAllocated = true; \
    Class->UniqueName = UniqueNameStr; \
    if (Class->FBCreate()) { \
    return Class->GetHIObject(); \
    } else { \
    delete Class; \
    return NULL; \
    } \
    } \
    \
    FBLibraryModule( ClassName )	\
    {	\
    FBRegisterObject(ClassName##R1,"Boxes/Devices",Label,Description,RegisterDevice##ClassName##Create,true, IconFilename );\
    FBRegisterObject(ClassName##R2,"FbxStorable/Device",UniqueNameStr,Description,RegisterDevice##ClassName##Create,true, IconFilename ); \
    }

    /** Register an online device class
    *	\param	UniqueNameStr	Unique name of class.
    *	\param	ClassName		Name of device class.
    *	\param	Label			Short description.
    *	\param	Description		Long description.
    *   \param  IconFilename    Name of the file containing the icon.
    */
#define FBRegisterOnlineDevice( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
    HIObject RegisterDevice##ClassName##Create( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
    { \
    ClassName *Class = new ClassName(pName); \
    Class->mAllocated = true; \
    Class->UniqueName = UniqueNameStr; \
    if (Class->FBCreate()) { \
    return Class->GetHIObject(); \
    } else { \
    delete Class; \
    return NULL; \
    } \
    } \
    \
    FBLibraryModule( ClassName )	\
    {	\
    if( FBGetLicense() >= kFBLicenseOnline )	\
    {	\
    FBRegisterObject(ClassName##R1,"Boxes/Devices",Label,Description,RegisterDevice##ClassName##Create, true, IconFilename );\
    FBRegisterObject(ClassName##R2,"FbxStorable/Device",UniqueNameStr,Description,RegisterDevice##ClassName##Create, true, IconFilename ); \
    }	\
    }


    ////////////////////////////////////////////////////////////////////////////////////
    // FBBox
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBBox );
    FB_FORWARD( FBFbxObject );

    /** A box is a fundamental building block in the application architecture.
    *	All animatable elements are derived in some way from the main box class, either
    *	by deriving directly or owning a box.
    */
    class FBSDK_DLL FBBox : public FBComponent {
        __FBClassDeclare( FBBox,FBComponent );
    public:
        /**	Constructor.
        *	\param	pName		Box name.
        *	\param	pObject		For internal use only (default is NULL).
        */
        FBBox(const char* pName, HIObject pObject=NULL);

	    //! Resolving action for candidates
        enum ECandidateAction
        {
	        eCandidateAccept,						//!< Let the standard system take care of the candidate
	        eCandidateIntercept,					//!< Intercept the candidate 
	        eCandidateInterceptAfterEvaluation  	//!< Ask for an evaluation before using the candidate
        };

        //@{
        /**	Creation of IN/OUT Animation Nodes
        *	\param	pUserId		User-defined reference number.
        *	\param	pName		Name of animation node.
        *	\param	pDataType	Type of data being animated.
        *	\param	pIsPublic	Determine if the animation node is published, that means whether to show it in property editor and have input / output in relation constraints editor (default is false).
        *	\param	pMin		Minimum values for data (default is NULL).
        *	\param	pMax		Maximum values for data (default is NULL).
        *	\param	pUserData	Is this user data? False means the property is NOT animated, user cannot change the data. Especially for device, it doesn't make sense to make it animated, unless you want to record the device data. (default is \b false).
        *	\return A handle to the newly created animation node.
        */
        virtual FBAnimationNode* AnimationNodeInCreate	(kReference pUserId,const char * pName ,const char * pDataType,bool pIsPublic=false,double *pMin=NULL,double *pMax=NULL,bool pUserData=false);
        virtual FBAnimationNode* AnimationNodeOutCreate	(kReference pUserId,const char * pName ,const char * pDataType,bool pIsPublic=false,double *pMin=NULL,double *pMax=NULL,bool pUserData=false);
        //@}

        /**	Evaluation of non TRS nodes that needs to be evaluated.
        *	This function is called by the real-time engine in order to process animation information.
        *	\param	pEvaluateInfo	Information concerning the evaluation of the animation (time, etc.)
        *	\return \b true if animation node notification is successful.
        */
        virtual bool EvaluateAnimationNodes( FBEvaluateInfo* pEvaluateInfo );

        /**	Notification function for animation thread.
        *	This function is called by the real-time engine in order to process animation information.
        *	\param	pAnimationNode	Node containing the modified information.
        *	\param	pEvaluateInfo	Information concerning the evaluation of the animation (time, etc.)
        *	\return \b true if animation node notification is successful.
        */
        virtual bool AnimationNodeNotify( FBAnimationNode* pAnimationNode, FBEvaluateInfo* pEvaluateInfo );

        /**	Function is call when candidate needs to be resolved (like global to local).
        *	\param	pAnimationNode	Node containing the information to resolve.
        *	\param	pEvaluateInfo	Information concerning the evaluation of the animation (time, etc.)
        *	\return \b function should return true (not used for now).
        */
		virtual bool ResolveCandidate( FBAnimationNode* pAnimationNode, FBEvaluateInfo* pEvaluateInfo );

        /**	Function is call when a global candidate is set on an animation node.
        *	\param	pAnimationNode	Node containing the information to resolve.
        *	\param	pEvaluateInfo	Information concerning the evaluation of the animation (time, etc.)
        *	\return \b Action to take with the candidate.
        */
		virtual ECandidateAction SetGlobalCandidate( FBAnimationNode* pAnimationNode, double* pData, FBEvaluateInfo* pEvaluateInfo );

        /**	Function is call when a non-global candidate is set on an animation node.
        *	\param	pAnimationNode	Node containing the information to resolve.
        *	\param	pEvaluateInfo	Information concerning the evaluation of the animation (time, etc.)
        *	\return \b Action to take with the candidate.
        */
		virtual ECandidateAction SetStdCandidate( FBAnimationNode* pAnimationNode, double* pData, FBEvaluateInfo* pEvaluateInfo );

        //@{
        /** Storage/Retrieval of information into the FBX file format.
        *	\param	pFbxObject	Object to interface with FBX file format.
        *	\param	pStoreWhat	Attributes to store in FBX file.
        *	\return	\b true if successful.
        */
        virtual bool FbxStore(	FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
        virtual bool FbxRetrieve(FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
        //@}

        /**	Destroy an animation node.
        *	\param	pAnimationNode	Handle to the animation node to be destroyed.
        *	\return \b true if destruction was successful.
        */
        virtual bool AnimationNodeDestroy( FBAnimationNode* pAnimationNode );

        /** Is the animation node user data?
        *	\param	pAnimationNode	Handle to the animation to be queried.
        *	\return \b true if node is user data.
        */
        virtual bool AnimationNodeIsUserData( FBAnimationNode* pAnimationNode );

		/** This call will disable all out animation nodes from being pull by system (animation thread) for given pEvaluateInfo.
        *	\param	pEvaluateInfo	Evaluation synchronization object (contains evaluation id).
		*	\note This can be also done per individual AnimationNode -> FBAnimationNode::DisableIfNotWritten 
        */
        virtual void AnimationNodesOutDisableIfNotWritten( FBEvaluateInfo* pEvaluateInfo );

        //@{
        /**	Get the (IN/OUT) animation node for this box.
        *	\return A handle to the animation node for this box.
        */
        virtual FBAnimationNode* AnimationNodeInGet();
        virtual FBAnimationNode* AnimationNodeOutGet();
        //@}

        const char* UniqueName;					//!< internal Unique name.
        virtual const char* FbxGetObjectSubType();//!< returns UniqueName if not overloaded.
        virtual const char* FbxGetObjectType();	//!< Object Type "Box".

        IObject_Declare(K_IMPLEMENTATION);	// Interface to IObject.

		/** Get the number of animation node outputs for this box.
		*	\return The number of animation node outputs for this box.
		*/
		virtual int GetOutConnectorCount() const;

		/** Get the number of animation node inputs for this box.
		*	\return The number of animation node inputs for this box.
		*/
		virtual int GetInConnectorCount() const;

		/** Get the animation node output associated with the given index.
		*	\param	pIndex	The animation node output associated with the given index.
		*	\return The animation node output, or NULL if the pIndex value is invalid.
		*/
		virtual FBAnimationNode* GetOutConnector( int pIndex ) const;

		/** Get the animation node input associated with the given index.
		*	\param	pIndex	The animation node input associated with the given index.
		*	\return The animation node input, or NULL if the pIndex value is invalid.
		*/
		virtual FBAnimationNode* GetInConnector( int pIndex ) const;

        FBPropertyBool Animatable;          //!< <b>Read Write Property:</b> Is the box animatable.
        FBPropertyBool Live;				//!< <b>Read Write Property:</b> Is live?
        FBPropertyBool RecordMode;			//!< <b>Read Write Property:</b> Is recording?
    };


#ifndef K_NO_UI

    ////////////////////////////////////////////////////////////////////////////////////
    // FBHandle
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBHandle );

    /** FBHandle class exposes the Handle object of the application.
    *   \note This is a terminal class and should not be used as a base for a new class.
    */
    class FBSDK_DLL FBHandle : public FBBox {
        __FBClassDeclare( FBHandle, FBBox );

    public:
        /** Public constructor.
        *   This constructor is used to create a new object.
        *   \param pName Object name.
        *   \param pObject For internal use only.
        */
        FBHandle( const char* pName, HIObject pObject=NULL );

        /** Meta selection.
        *   With this method, the handle itself is selected as well as
        *   all the models that are manipulated by the handle.
        */
        void Select();

        FBPropertyListObject Follow;                //!< <b>List:</b> Object to be followed by the handle. Should have a cardinality of 1.
        FBPropertyListObject Manipulate;            //!< <b>List:</b> Objects manipulated by the handle.
        FBPropertyListObject ManipulateTranslation; //!< <b>List:</b> Objects manipulated by the handle. Only their translation is affected.
        FBPropertyListObject ManipulateRotation;    //!< <b>List:</b> Objects manipulated by the handle. Only their rotation is affected.
        FBPropertyListObject ManipulateScaling;     //!< <b>List:</b> Objects manipulated by the handle. Only their scaling is affected.
        FBPropertyListObject Image;                 //!< <b>List:</b> Image to be used in the handle display. Only the image at position 0 is used.

    private:
        //@{
        /** Restricted methods.
        *   Voluntarily making the copy constructor and assignment
        *   operator unavailable.
        */
        FBHandle( const FBHandle& );
        FBHandle& operator=( const FBHandle& );
        //@}
    };


    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListHandle
    ////////////////////////////////////////////////////////////////////////////////////
    FB_DEFINE_LIST( FBSDK_DLL, Handle );
    FB_FORWARD( FBPropertyListHandle );

    //! \b PropertyList: Handle.
    class FBSDK_DLL FBPropertyListHandle : public FBPropertyListComponent
    {
    public:
        FBPropertyListHandle();
        /**	Get the model template at \e pIndex.
        *	\param	pIndex	Index of model template to get.
        *	\return Model template at \e pIndex.
        */
        FBHandle* operator[](int pIndex);
    };

#endif

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListModelTemplate
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD	( FBModelTemplate	);
    __FB_FORWARD	( FBPropertyListModelTemplate	);
    FB_DEFINE_LIST	( FBSDK_DLL, ModelTemplate		);

    //! \b PropertyList: ModelTemplate.
    class FBSDK_DLL FBPropertyListModelTemplate : public FBPropertyListComponentBase
    {
    public:
        /**	Add a model template to the property list.
        *	\param	pItem	Model template to add to list.
        *	\return	Number of items in list after operation.
        */
        int	 Add	( FBModelTemplate* pItem );
        /** Remove the model template at \e pIndex.
        *	\param pIndex	Index of model template to remove.
        */
        virtual void RemoveAt( int pIndex );
        /**	Get the model template at \e pIndex.
        *	\param	pIndex	Index of model template to get.
        *	\return Model template at \e pIndex.
        */
        FBModelTemplate* operator[](int pIndex);
        /** Get the number of model templates.
        *	\return Number of model templates.
        */
        virtual int GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
    private:
        inline virtual int Add	( FBComponent* pItem ) { return Add((FBModelTemplate*)pItem); }
#endif
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListModelTemplateBinding
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBModelTemplateBinding );
    __FB_FORWARD( FBPropertyListModelTemplateBinding );
    //! typedef class FBSDK_DLL FBPropertyBaseList< FBAnimationNode* > FBPropertyBaseListModelTemplateBinding
    typedef class FBSDK_DLL FBPropertyBaseList< FBAnimationNode* > FBPropertyBaseListModelTemplateBinding;

    //! \b PropertyList: ModelTemplateBinding.
    class FBSDK_DLL FBPropertyListModelTemplateBinding : public FBPropertyListComponentBase
    {
    public:
        /**	Add an animation node to the model template binding property list.
        *	\param	pItem	Animation Node to add to list.
        *	\return Index where \e pItem was inserted.
        */
        virtual int Add( FBAnimationNode* pItem );

        /** Remove the binding at \e pIndex.
        *	\param pIndex	Index of binding to remove.
        */
        virtual void RemoveAt( int pIndex );
        /**	Get the binding at \e pIndex.
        *	\param	pIndex	Index of binding to get.
        *	\return Binding at \e pIndex.
        */
        FBAnimationNode* operator[](int pIndex);

        /** Get the number of bindings.
        *	\return Number of bindings.
        */
        virtual int  GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
    private:
        inline virtual int Add	( FBComponent* pItem ) { return Add((FBAnimationNode*)pItem); }
#endif
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBModelTemplate
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBModelTemplate);

    /** Model template styles
    *	When creating model templates, this parameter will
    *	affect the actual model created (associated with the
    *	model template).
    */
    enum FBModelTemplateStyle { 
        kFBModelTemplateNone,				//!< No style.
        kFBModelTemplateNull,				//!< Null.
        kFBModelTemplateMarker,				//!< Marker.
        kFBModelTemplateRoot,				//!< Root (3 axes).
        kFBModelTemplateSensor,				//!< Yellow magnetic sensor.
        kFBModelTemplateSkeleton,			//!< Skeleton limb.
        kFBModelTemplateCamera,				//!< Camera.
        kFBModelTemplateGeometry,			//!< Generic geometry.
        kFBModelTemplateCameraInterest,		//!< Camera interest.
        kFBModelTemplateLight,				//!< Light.
        kFBModelTemplateOptical				//!< Optical model (not supported yet).
    };

    /** Model template class.
    *	Model templates are 'placeholders' for animation input from devices. These generic
    *	'models' can be any type of element, and permit the abstraction of the input
    *	from the actual type of model. In order to animate a model, one should bind the model 
    *	to an animation node.
    */
    class FBSDK_DLL FBModelTemplate : public FBComponent {
        __FBClassDeclare( FBModelTemplate,FBComponent );

        /**	Initialization function.
        */
        void Init();
    public:
        /**	Constructor from parent object.
        *	\internal
        *	\param pObject	For internal use only.
        */
        FBModelTemplate(HIObject pObject=NULL);

        /** Constructor (no parent) from prefix, name, and style.
        *	\param	pPrefix 	Location of model template in application object directory structure.
        *	\param	pName		Name of model template.
        *	\param	pStyle		Style of model template.
        */
        FBModelTemplate(const char *pPrefix,const char *pName, FBModelTemplateStyle pStyle);

        FBPropertyListModelTemplate			Children;				//!< <b>List:</b> Children for object hierarchy.
        FBPropertyListModelTemplateBinding	Bindings;				//!< <b>List:</b> Bindings for animation interface.

        FBPropertyString					Prefix;					//!< <b>Read Write Property:</b> Prefix of model template.
        FBPropertyModel						Model;					//!< <b>Read Write Property:</b> Model being interfaced.
        FBPropertyVector3d					DefaultTranslation;		//!< <b>Read Write Property:</b> Default translation.
        FBPropertyVector3d					DefaultRotation;		//!< <b>Read Write Property:</b> Default rotation.
        FBPropertyVector3d					DefaultScaling;			//!< <b>Read Write Property:</b> Default scaling.

        friend class FBDevice;
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListDevice
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD	( FBDevice );
    __FB_FORWARD	( FBPropertyListDevice );

    //! \b PropertyList: Device
    class FBSDK_DLL FBPropertyListDevice : public FBPropertyListComponent
    {
    public:
        FBPropertyListDevice();
        /**	Get the device at \e pIndex.
        *	\param	pIndex	Index of device to get.
        *	\return Device at \e pIndex.
        */
        FBDevice* operator[](int pIndex);
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBDeviceNotifyInfo
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBDeviceNotifyInfo );

    /** Device Input and Output Notification information structure.
    *	This structure is passed to the real-time device IO
    *	callback DeviceIONotify. It furnishes the device callback
    *	with the system time, local time, and sync counts for the current 
    *	device cycle.
    */
    class FBSDK_DLL FBDeviceNotifyInfo 
    {
    public:
        /**	Get system time.
        *	\return Current system time.
        */
        FBTime &GetSystemTime();

        /**	Get local time.
        *	\return Current local time.
        */
        FBTime &GetLocalTime();

        /** Set local time 
        Allows the device to override the local time of the
        system. SDK users can utilize this function to retreive the
        value from the MotionBuilder graph at a specific time.
        */
        void SetLocalTime( const FBTime & ); 

        /**	Return the wanted timer sync count (internal or external)
        *	\return sync count or \b -1 if no sync is present
        */
        int GetSyncCount();

        /**	Return the evaluation info used to do device evaluation
        *	\return evaluation info used used to do device evaluation
        */
        FBEvaluateInfo& GetEvaluateInfo();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBDeviceInstrument
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBDeviceInstrument );
    /** Instrument abstraction layer.
    */
    class FBSDK_DLL FBDeviceInstrument : public FBComponent
    {
        __FBClassDeclare( FBDeviceInstrument, FBComponent );
    public:
        /** Constructor.
        *	\param	pDevice		Parent device.
        */
        FBDeviceInstrument(FBDevice* pDevice);
        /**	Write data to instrument's connectors.
        *	In the evaluation engine callback, this will take the data in the
        *	instrument's temporary data holders and write it to the connectors.
        *	\param	pEvaluateInfo	Evaluation information structure.
        *	\return \b true if successful.
        */
        virtual bool InstrumentWriteData( FBEvaluateInfo* pEvaluateInfo	);
        /**	Record the data to the function curves for the instrument.
        *	\param	pRecordTime		Time to record data at.
        *	\param	pNotifyInfo		Device notification information structure.
        */
        virtual void InstrumentRecordFrame( FBTime pRecordTime, FBDeviceNotifyInfo& pNotifyInfo );
        //@{
        /** Storage/Retrieval of information into the FBX file format.
        *	\param	pFbxObject	Object to interface with FBX file format.
        *	\param	pStoreWhat	Attributes to store in FBX file.
        *	\return	\b true if successful.
        */
        virtual bool FbxStore( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
        virtual bool FbxRetrieve( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
        //@}

        FBPropertyDevice			Device;			//!< <b>Read Write Property:</b> Handle to owner device.
        FBPropertyBool				Active;			//!< <b>Read Write Property:</b> Is instrument active?
        FBPropertyModelTemplate		ModelTemplate;	//!< <b>Read Write Property:</b> Model template to build instruments' structure.
    };
    FB_DEFINE_COMPONENT( FBSDK_DLL, DeviceInstrument );

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyListDeviceInstrument
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBPropertyListDeviceInstrument );
    FB_DEFINE_LIST( FBSDK_DLL, DeviceInstrument );
    /**	List of instruments.
    */
    class FBSDK_DLL FBPropertyListDeviceInstrument : public FBPropertyListComponentBase
    {
    public:
        /**	Add an instrument to the property list.
        *	\param	pItem	Instrument to add to list.
        *	\return	Number of items in list.
        */
        virtual int	 Add	( FBDeviceInstrument* pItem );
        /** Remove the instrument at \e pIndex.
        *	\param pIndex	Index of instrument to remove.
        */
        virtual void RemoveAt( int pIndex );
        /**	Get the model template at \e pIndex.
        *	\param	pIndex	Index of instruments to get.
        *	\return Instrument at \e pIndex.
        */
        FBDeviceInstrument* operator[](int pIndex);
        /** Get the number of instruments.
        *	\return Number of instruments.
        */
        virtual int GetCount();
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
    private:
        inline virtual int Add	( FBComponent* pItem ) { return Add((FBDeviceInstrument*)pItem); }
#endif
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBSyncReference
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBSyncReference );
    /** Application sync.
    */
    class FBSDK_DLL FBSyncReference : public FBComponent
    {
        __FBClassDeclare( FBSyncReference, FBComponent );
    public:
        /**	Constructor.
        *	\param	pName		Synchronization reference name.
        *	\param	pObject		For internal use only (default is NULL).
        */
        FBSyncReference(const char* pName, HIObject pObject=NULL);

        /**	Notify sync.
        *	\param	pSyncId		Synchronization id.
        */
        void	Sync(int pSyncId);

        /**	Return sync count.
        *
        */
        int	GetSyncCount();

        /**	Last sync time.
        *
        */
        FBTime	GetTimeOfLastSync();

        /**	Next sync time.
        *
        */
        FBTime	GetTimeOfNextSync();

        FBPropertyBool				Active;					//!< <b>Read Write Property:</b> Activate sync.
        FBPropertyTime				SamplingPeriod;			//!< <b>Read Write Property:</b> Sampling period.
    };
    FB_DEFINE_COMPONENT( FBSDK_DLL, SyncReference );


    ////////////////////////////////////////////////////////////////////////////////////
    // FBDevice
    ////////////////////////////////////////////////////////////////////////////////////
    /** Recording types.
    *	The different values for this will control the way the keys are added when the 
    *	device is being recorded. There are four different types of recording keys for devices:
    *	- Hardware Timestamping.	This case is when the hardware provides timestamps with each packet.
    *	- Hardware Frequency.		The hardware is guaranteed to provide packets at a given frequency.
    *	- Auto Frequency			Packets are coming in at a fixed, unknown frequency. The recorded
    *								data will be resampled to be equidistant.
    *	- Software Timestamping.	The application will provide a timestamp for each packet depending on when it 
    *								receives the data.
    */
    enum FBDeviceSamplingMode	{ 
        kFBHardwareTimestamp,		//!< Device supplies timestamp.
        kFBHardwareFrequency,		//!< Device is running at known, fixed frequency.
        kFBAutoFrequency,			//!< Device is running at unknown, fixed frequency.
        kFBSoftwareTimestamp		//!< The software will timestamp packets as they arrive.
    };
    FB_DEFINE_ENUM( FBSDK_DLL, DeviceSamplingMode );

    /** Communications type.
    *	Different base types of communications. There is always the 'other' type in order
    *	to use another type of communication.
    */
    enum FBCommType {
        kFBCommTypeNone			= 0,		//!< A non-communicating device.
        kFBCommTypeSerial		= 1<<0,		//!< Serial communications.
        kFBCommTypeNetworkTCP	= 1<<1,		//!< Network (TCP) device.
        kFBCommTypeNetworkUDP	= 1<<2,		//!< Network (UDP) device.
        kFBCommTypeSharedMemory	= 1<<3,		//!< Accessing shared memory.
        kFBCommTypeSimulator	= 1<<4,		//!< Software simulator.
        kFBCommTypeOther		= 1<<5		//!< Any other type of communications.
    };

    typedef class FBSDK_DLL FBArrayTemplate<FBModel*> FBModelList;
    __FB_FORWARD( FBDevice );

    //! Base Device class. Cannot be instantiated from Python.
    class FBSDK_DLL FBDevice : public FBBox {
        __FBClassDeclare( FBDevice,FBBox );
    public:
        /** Types of operations for device.
        *	These are parameters for the DeviceSendCommand() function.
        */
        enum kDeviceOperations { 
            kOpInit,			//!< Initalize device (creation).
            kOpStart,			//!< Start device (online).
            kOpAutoDetect,		//!< Autodetect (automatic).
            kOpStop,			//!< Stop device (offline).
            kOpReset,			//!< Reset device (stop->start).
            kOpDone				//!< Remove device (destruction).
        };

        /** Types of I/O for device.
        *	These are states of the engine for the DeviceIONotify callback.
        */
        enum kDeviceIOs { 
            kIOStopModeRead,	//!< Read from device (Transport=stopped).
            kIOPlayModeRead,	//!< Read from device (Transport=playing).
            kIOStopModeWrite,	//!< Write to device (Transport=stopped).
            kIOPlayModeWrite	//!< Write to device (Transport=playing).
        };

        /** Transport control types for device.
        *	These are states of the engine for the DeviceEvaluationNofity callback.
        */
        enum kTransportMode	   { 		
            kPreparePlay,		//!< Preparing to play
            kPlayReady,			//!< Ready to play.
            kPlayStop,			//!< Stopping play.
            kStop,				//!< Play stopped.
            kPlay,				//!< Playing.
            kJog,				//!< Jog.
            kPlayReverse		//!< Playing Reverse.
        };

        /**	Constructor
        *	\param	pName	Name of device.
        *	\param	pObject	For internal use only (default is NULL).
        */
        FBDevice(const char * pName,HIObject pObject=NULL);

        // See FBBox class
        virtual bool FBCreate	();
        virtual void FBDestroy	();

        // See FBBox class
        virtual FBAnimationNode* AnimationNodeInCreate (kReference pUserId,const char * pName ,const char * pDataType,bool pIsPublic=true,double *pMin=NULL,double *pMax=NULL,bool pUserData=false);
        virtual FBAnimationNode* AnimationNodeOutCreate(kReference pUserId,const char * pName ,const char * pDataType,bool pIsPublic=true,double *pMin=NULL,double *pMax=NULL,bool pUserData=false);

        /**	Operate device.
        *	This is an operation such as Init, Start, Done, Reset, etc.
        *	\param	pOperation Operation to have device perform.
        *	\return Current state : <b true if online.
        */
        virtual bool DeviceOperation( kDeviceOperations pOperation );

        /**	Real-Time engine thread: Tranport notifications.
        *	The device I/O thread calls this function when there is a transport change.
        *	\param	pMode	Transport mode.
        *	\param	pTime	Local time.
        *	\param	pSystem System time.
        */
        virtual void DeviceTransportNotify( kTransportMode pMode, FBTime pTime, FBTime pSystem );

        /**	Real-Time engine thread: Device I/O.
        *	The device I/O thread calls this function (required) which is a highly optimized non-blocking function
        *	registering input/output information from/to the device.
        *	\param	pAction             Different reading/writing actions for the device.
        *	\param	pDeviceNotifyInfo   Access to the system and local time.
        */
        virtual void DeviceIONotify( kDeviceIOs  pAction, FBDeviceNotifyInfo& pDeviceNotifyInfo );

        /** Real-Time engine thread: Output device evaluation.
        *	\param	pMode			Transport mode.
        *	\param	pEvaluateInfo	Access to the system and local time.
        *	\return \b true if successful.
        */
        virtual bool DeviceEvaluationNotify( kTransportMode pMode,FBEvaluateInfo* pEvaluateInfo );

        /** Model Template binding notification callback.
        *	\param	pModel			Model being bound to model template.
        *	\param	pIndex			Index of model template where binding is occuring.
        *	\param	pModelTemplate	Model being affected with binding.
        *	\return \b true if successful.
        */
        virtual bool ModelTemplateBindNotify( FBModel* pModel,int pIndex, FBModelTemplate* pModelTemplate );

        /** Model Template unbinding notification callback.
        *	\param	pIndex			Index in \e pModelTemplate where unbinding has occured.
        *	\param	pModelTemplate	Model template from which binding is removed.
        *	\return \b true if successful.
        */
        virtual bool ModelTemplateUnBindNotify( int pIndex, FBModelTemplate* pModelTemplate );

        /** Create a new model binding.
        *	\return \b The model root that has been created or NULL is an error occured.
        */
        FBModel* ModelBindingCreate();

        /** Get the list of all the possible root models for binding.
        *	\retval	pList		List to add found models to.
        */
        void ModelBindingRootsList(FBModelList& pList);

        /**	Notification function for animation thread.
        *	This function is called by the real-time engine in order to process animation information.
        *	\param	pAnimationNode	Node containing the modified information.
        *	\param	pEvaluateInfo	Information concerning the evaluation of the animation (time, etc.)
        *	\return \b true if animation node notification is successful.
        */
        virtual bool AnimationNodeNotify( FBAnimationNode* pAnimationNode, FBEvaluateInfo* pEvaluateInfo ) override;

        virtual const char* FbxGetObjectType() override;	//!< Object Type "Device".

        //@{
        /** Storage/Retrieval of information into the FBX file format.
        *	\param	pFbxObject	Object to interface with FBX file format.
        *	\param	pStoreWhat	Attributes to store in FBX file.
        *	\return	\b true if successful.
        */
        virtual bool FbxStore	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat ) override;
        virtual bool FbxRetrieve( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat ) override;
        //@}

        /**	Send a command to the device.
        *	This function will send the Init, Start, etc. commands to the device.
        *	\param	pOperation	Operation for device to perform.
        */
        virtual void DeviceSendCommand( kDeviceOperations pOperation );

        IObject_Declare( K_IMPLEMENTATION );				// Interface to IObject

        FBPropertyString				Status;					//!< <b>Read Write Property:</b> Device information: status.
        FBPropertyString				Information;			//!< <b>Read Write Property:</b> Device information: information.
        FBPropertyString				HardwareVersionInfo;	//!< <b>Read Write Property:</b> Device information: hardware version.
        FBPropertyTime					SamplingPeriod;			//!< <b>Read Write Property:</b> Set this to how many times a device is to be evaluated in one second. There is no theoretical maximum value but practically you should consider scene complexity, system resources, network speed, etc. If set to 0: the device is evaluated on the sync signal. When the sync occurs; the device is scheduled to be evaluated. If you do not set, the sampling period is based on the internal variable from the [Sync] section of the .Application.txt file (NTSC, PAL, CINEMA).
        FBPropertyBool					Online;					//!< <b>Read Write Property:</b> Is online?

        FBPropertyEvent					OnStatusChange;			//!< <b>Event:</b> Status of device changed.

        FBModelTemplate					ModelTemplate;			//!< <b>Component:</b> Root of model template structure.
        FBPropertyModel					ModelBindingRoot;		//!< <b>Component:</b> Root of model currently binded model hierarchy.

        FBPropertyDeviceSamplingMode	SamplingMode;			//!< <b>Read Write Property:</b> Mode to use to record device.
        FBPropertyInt					CommType;				//!< <b>Read Write Property:</b> Type of communications.

        FBPropertyListDeviceInstrument	Instruments;	//!< <b>List:</b> List of instruments.

        FBPropertyTime					RecordingStartTime;		//!< <b>Read Only Property:</b> The time at which the recording started.
        FBPropertyTime					RecordingStopTime;		//!< <b>Read Only Property:</b> The time at which the recording stopped.

        //! Acknowlege that one sample was received (for statistical purposes).
        void AckOneSampleReceived();

        //! Acknowlege that one \b bad sample was received (for statistical purposes).
        void AckOneBadSampleReceived();

        //! Acknowlege that one sample was sent (for statistical purposes).
        void AckOneSampleSent();

        /**	When recording, initialize animation.
        *	\param	pAnimationNode	Animation node to read information from.
        */
        virtual void RecordingInitAnimation(FBAnimationNode* pAnimationNode);

        /** When recording, finish animation.
        *	\param	pAnimationNode	Animation node to write information to.
        */
        virtual void RecordingDoneAnimation(FBAnimationNode* pAnimationNode);

        friend class __FBDevice;
        friend class DataFBDeviceOptical;
    };

#ifndef FBSDK_LEAN_AND_MEAN

    __FB_FORWARD( FBDeviceGlove );

    //! Base Glove class.
    class FBSDK_DLL FBDeviceGlove : public FBDevice {
        __FBClassDeclare( FBDeviceGlove, FBDevice );
    public:
        /** Hand model parts.
        */
        enum kHandModelPart {   // Parents :

            kPartRoot,          // No parent
            kPartPalm,          // kPartRoot

            // Thumb
            kPartThumbA,        // kPartPalm
            kPartThumbB,        // kPartThumbA
            kPartThumbC,        // kPartThumbB
            kPartThumbD,        // kPartThumbC

            // Index
            kPartIndexA,        // kPartPalm
            kPartIndexB,        // kPartIndexA
            kPartIndexC,        // kPartIndexB
            kPartIndexD,        // kPartIndexC

            // Middle
            kPartMiddleA,       // kPartPalm
            kPartMiddleB,       // kPartMiddleA
            kPartMiddleC,       // kPartMiddleB
            kPartMiddleD,       // kPartMiddleC

            // Ring
            kPartRingA,         // kPartPalm
            kPartRingB,         // kPartRingA
            kPartRingC,         // kPartRingB
            kPartRingD,         // kPartRingC

            // Little
            kPartLittleA,       // kPartPalm
            kPartLittleB,       // kPartLittleA
            kPartLittleC,       // kPartLittleB
            kPartLittleD,       // kPartLittleC

            kPartMax
        };

        /**
        *  Base GloveChannel.
        */
        class FBSDK_DLL GloveChannel
        {   
        public:
            /** Constructor.
            *   \param  pAnimNode       The animation node associated to this channel.
            */
            GloveChannel( FBAnimationNode* pAnimNode );

            /** Destructor,
            */
            virtual ~GloveChannel();

            /** Get the channel name.
            *   \return The channel name.
            */
            FBString        GetName ();

            /** Set the channel name.
            *   \param  pName   The new channel name.
            */
            void            SetName ( FBString pName );

        protected:
            FBString                Name;              //!< Name of channel.

        public:
            bool 		            Enabled;           //!< \b true if this channel is enabled.
            FBAnimationNode*        AnimNode;          //!< Animation node.    
        };


        /**	Constructor
        *	\param	pName	    Name of device.
        *	\param	pObject 	For internal use only (default is NULL).
        */
        FBDeviceGlove( const char* pName, HIObject pObject=NULL );

        /**	When recording, initialize animation.
        *	\param	pAnimationNode	Animation node to read information from.
        */
        virtual void RecordingInitAnimation( FBAnimationNode* pAnimationNode );

        /** When recording, finish animation.
        *	\param	pAnimationNode	Animation node to write information to.
        */
        virtual void RecordingDoneAnimation( FBAnimationNode* pAnimationNode );

    protected:
        /** Initialize the hand model geometry. You should set the LeftHand property prior to using this
        *   method, so that the geometry gets initialized correctly. Also call this function if you
        *	changed the value of LeftHand property.
        */
        void InitializeModelGeometry();

        /** Bring the vector in parameter to a valid angle range of rotation for 
        *   a given part of the hand model.
        *   The input vector should have relative values between 0.0 (min) and 1.0 (max).
        *   The output vector is an euler local rotation vector with limits applied.
        *   This vector can then be used to constraint the rotation of the hand part model.
        *   \param  pPartIndex  The hand part.
        *   \param  pVector     The vector to modify.
        */
        void VectorToModelPartAngle( kHandModelPart pPartIndex, FBVector3d& pVector );

        /** Obtain the rotation animation node of a part of the hand model.
        *   \param  pPartIndex       The hand part.
        *   \return The animation node of the given hand part.
        */
        FBAnimationNode* GetModelRotationNode( kHandModelPart pPartIndex );

    public:
        FBArrayTemplate<GloveChannel*>      Channels;       //!< Glove channels.

        FBPropertyBool                      LeftHand;       //!< <b>Read Write Property:</b> Left or right hand glove.
    };

#endif

#ifdef FBSDKUseNamespace
}
#endif
#endif
