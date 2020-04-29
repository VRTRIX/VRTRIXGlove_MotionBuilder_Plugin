#ifndef __FBPROPERTIES_H__
#define __FBPROPERTIES_H__
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

/**	\file fbproperties.h
*	Property classes.
*	Properties are callback variables that insert a layer of abstraction between
*	the internal objects and the software development kit.
*/

#include <kaydaradef.h>

#ifndef FBSDK_DLL
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <fbsdk/fbplug.h>
#include <fbsdk/fbarray.h>
#include <fbsdk/fbstring.h>
#include <fbsdk/fbtime.h>
#include <fbsdk/fbevaluateinfo.h>

K_FORWARD( KEventBase );
K_FORWARD( KObject );
K_FORWARD( KProperty );
K_FORWARD( KEvaluationProperty );
K_FORWARD( KDataType );
K_FORWARD( IFBObject );
K_FORWARD( IRegister );

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {
#endif

    //! \enum FBPropertyType
    /**Property types
    */
    enum FBPropertyType
    {
        kFBPT_unknown,	//!< unknow.
        kFBPT_int,		//!< int.
        kFBPT_int64,	//!< int 64 bits.
        kFBPT_uint64,	//!< unsigned int 64 bits.
        kFBPT_bool,		//!< bool.
        kFBPT_float,	//!< float.
        kFBPT_double,	//!< double.
        kFBPT_charptr,	//!< charptr.
        kFBPT_enum,		//!< enum.
        kFBPT_Time,		//!< time.
        kFBPT_TimeCode,	//!< timecode.
        kFBPT_object,	//!< object.
        kFBPT_event,	//!< event.
        kFBPT_stringlist,//!< stringlist.
        kFBPT_Vector4D,	//!< vector4d.
        kFBPT_Vector3D,	//!< vector3d.
        kFBPT_ColorRGB,	//!< colorrgb.
        kFBPT_ColorRGBA,//!< colorrgba.
        kFBPT_Action,	//!< action.
        kFBPT_Reference,//!< reference.
        kFBPT_TimeSpan,	//!< timespan.
        kFBPT_kReference,//!< kReference.
        kFBPT_Vector2D	//!< vector2d.
    };

    //! \enum FBDataAsStringFlag
    /**  FBDataAsStringFlag
    */
    enum FBDataAsStringFlag
    {
        kFBDataAsStringUI              = 0,        //!< Convert data to string type for UI display
        kFBDataAsStringPersistence     = 1,        //!< Convert data to string type for storage
    };

    /** Available flags for FBProperty objects.
    *   @note   Property flags are not saved into FBX files.
    */
    enum FBPropertyFlag
    {
        kFBPropertyFlagNotSet = 0,
        kFBPropertyFlagHideProperty = (1 << 0),       //!< This flag is used to show/hide the property in the propertiview. However, when turn on/off HidePropertry flag, this property won't show/hide unless you reload the UI.  The nodes hidden by this flag are removed from UI.
        kFBPropertyFlagForceStaticProperty = (1 << 1),
        kFBPropertyFlagDisableProperty = (1 << 2),
        kFBPropertyFlagSlavedProperty = (1 << 3),     //!< This is property is connected and slaved by other same type of master property, and it always ask value from its master property.
        kFBPropertyFlagAnimated = (1 << 4),
        kFBPropertyFlagNotSavable = (1 << 5),         //!< Should not be saved to or loaded from an FBX file
        kFBPropertyFlagReadOnly = (1 << 6),
        kFBPropertyFlagNotUserDeletable = (1 << 7),
        kFBValueAllocated = (1 << 8),                 //!< The value has been allocated and must be delete in destructor.
        kFBDynamicHidden = (1 << 9),                  //!< This flag is used to show/hide the property in the propertiview. When turn on/ff DynamicHidden flag, this property will show/hide.  The nodes hidden by this flag still exist in UI.
        kFBSlaveSetByMaster = (1 << 10),              //!< Slave property can be modified, valid only when the master property is modified
        kFBLoadedUserProperty = (1 << 11)             //!< This property is loaded from file
    };

    /**	Define a component and give it the ability to be a property.
    *	\param	DllTag		Associated DLL.
    *	\param	Type		Component to register as a property.
    */
#define FB_DEFINE_COMPONENT( DllTag, Type )                                             \
    class FB##Type;																		\
    typedef class DllTag FBPropertyBase< FB##Type*,kFBPT_object > FBPropertyBase##Type; \
    typedef class DllTag FBPropertyBaseComponent< FB##Type* > FBProperty##Type

    /**	Define an enum and give it the ability to be a property.
    *	\param	DllTag		Associated DLL.
    *	\param	Type		Enum to register as a property.
    */
#define FB_DEFINE_ENUM( DllTag, Type ) \
    typedef class DllTag FBPropertyBaseEnum< enum FB##Type > FBProperty##Type;

    /**	Define a private enum and give it the ability to be a property.
    *	\param	EnumName	Name of the Enum to register as a property.
    */
#define FB_DEFINE_CLASS_ENUM( EnumName ) \
    typedef class FBPropertyBaseEnum< enum __FBClassType::e##EnumName > Property##EnumName;

    /** Define a component list.
    *	\param	DllTag		Associated DLL.
    *	\param	Type		Component to use as a list item.
    */
#define FB_DEFINE_LIST( DllTag, Type )	\
    typedef class DllTag FBPropertyBaseList< FB##Type* > FBPropertyBaseList##Type;

    /** function pointer */
    typedef void (*fbGetSetHandler)(void);
    /** function pointer */
    typedef void (*fbExternalGetSetHandler)(HIObject pObject);

    FB_FORWARD( FBComponent );
    __FB_FORWARD( FBProperty );

    /** <b>Property:</b> Base property class.
    *	A property is a holder for function callbacks into the internals
    *	of the application.

    You cannot instantiate FBProperty objects. To reference a property:
    \li Use an instance of an FBComponent object. 	The methods FBComponent::PropertyCreate
    and FBComponent::PropertyRemove can be used to modify an object's set of properties. 
    When accessing a FBProperty object via its containing object, you can get or set 
    (assuming it is not read-only) its value directly, for example in Python: myObject.Visibility = True. 
    \li FBPropertyManager exists in all FBComponent objects, and contains an array of
    all the registered properties. Use FBProperty::Find to find a property by name. 
    When accessing a property reference directly, its value is obtained via its 'Data' member.
    \code
    myProp = myObject.PropertyList.Find( 'Visibility' )
    if myProp: myProp.Data = True
    \endcode

    To see how to create a custom property in Python, see CustomProperty.py.
    */

    class FBSDK_DLL FBProperty : public FBPlug
    {
        FBClassDeclare( FBProperty, FBPlug );

    protected:
        /*! mName Property unique name. */
        FBString		mName;
        /*! mParent Parent of the property.	*/
        void*			mParent;

    public:
        //! Constructor.
        FBProperty();    

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        //! IObject_Declare Interface to IObject.
        IObject_Declare(K_IMPLEMENTATION);		

        //! Initialize internal pointer.
        FBProperty* InitInternal( KProperty* pProperty );

        //! Get property.
        KProperty* GetInternal() const;

        //! Get property value.
        void* GetValuePtr() const;

        //! Creation of internal property.
        FBProperty* CreateInternal( FBComponent* pParent, const char* pName, fbExternalGetSetHandler pGet = NULL, fbExternalGetSetHandler pSet = NULL);

        //! Creation of user texture connect property.
        FBProperty* CreateTextureConnectable( FBComponent* pParent, const char* pName );

        //! Set internal property
        void SetInternal( KProperty* pInternal );
#endif

        //! Set property enable status
        void SetEnable( bool pValue );

        /**	Get the property's name.
        *	\return	The property's name.
        */
        const char* GetName();

        /**	Set the property's name.
        *	\param	pName	New name for the property.
        */
        void SetName(const char *pName);

        /**	Get the property's type.
        *	\return	The property's type.
        */
        virtual FBPropertyType GetPropertyType( );

        /**	Get the property's type name.
        *	\return	The property's type name.
        */
        const char* GetPropertyTypeName();

        /**	Get the property datatype pointer.
        *	\return Datatype of property (NULL in the case of the FBProperty is not internal).
        */
        virtual KDataType* GetDataType();

        //@{
        /**	Set the value of the property, passing the type as an argument.
        *	\param	pData	Value to affect property with.
        */
        virtual void SetData( void*	pData );
        //@}

        //@{
        /**	Get the value of a property.
        *	\retval	pData	Value to fill with property's current value.
        *   \param  pSize	  Size of pData buffer
        *   \param  pEvalInfo Used only with animated properties
        */
        virtual void GetData( void*	pData, int pSize, FBEvaluateInfo *pEvalInfo = NULL ) const;
        //@}

        /**	Get the property as an integer.
        *	\return The integer version of the property.
        */	
        int			AsInt();

        /**	Set the property from an integer.
        *	\param	pInt Int to set property from.
        *	\return True if it was possible.
        */	
        bool		SetInt(int pInt);

        /**	Get the property value as a string.
        *   \param  pFlag Indicates the returned string to be used for UI or storage. It defaults to kFBDataAsStringUI.
        *	\return The string version of the property.
        */	
        virtual const char* AsString( FBDataAsStringFlag pFlag = kFBDataAsStringUI );

        /**	Set the property value from a string.
        *	\param	pString String to set property value from, with format same as AsString(kFBDataAsStringPersistence)
        *	\return True if it was possible.
        */
        virtual bool SetString( const char* pString );

        /** Get the property original value (before any modification) as string.
        *   \return returns the original value of the property in string with format same as AsString(kDataAsStringPersistence)
        */
        const char* OriValueAsString();

        /** Get the property animated flag status*/
        bool IsAnimated() const;

        /** Get the property original animated flag status (before any modification)
        */
        bool OriIsAnimated() const;

        //@{
        /**	Verify if property is of this type.
        *	\return	\b true if property is of type.
        */
        virtual bool IsList();
        virtual bool IsAnimatable();
        bool IsInternal() const;
        bool IsUserProperty();
        bool IsTextureConnectableProperty();
        bool IsReferenceProperty();
        //@}

        /** Indicate if minimum value clamping will be applied on user input value.
        *	\return	\b true if property the value will be clamped to a minimum value.
        */
        bool IsMinClamp();	

        /** Indicate if maximum value clamping will be applied on user input value.
        *	\return	\b true if property the value will be clamped to a maximum value.
        */
        bool IsMaxClamp();

        /** Indicate if a property was created on retrieve because it didn't exist.
        *   \warning if there is no call to AcceptTemporaryProperty(), is will be converted to a user property after the file is retrieved.
        *	\return	\b true if property is temporary.
        */
        bool IsTemporaryProperty();

        /** Accept a temporary property as a dynamic property.
        *   \warning if there is no call to AcceptTemporaryProperty(), is will be converted to a user property after the file is retrieved.
        *	\return	\b true if property was temporary and converted to a user property.
        */
        bool AcceptTemporaryProperty(const char* pEnumList[] = NULL, fbExternalGetSetHandler pGet=NULL, fbExternalGetSetHandler pSet=NULL);

        /** Indicate if is an instance of FBPropertyListObject.
        *   \warning A FBPropertyListObject will also return true on a call to 'IsList()'.
        */
        bool IsObjectList();

        /**	Is property read-only?
        *	\return	\b true if property is read-only.
        */
        virtual bool IsReadOnly();

        /**	Return the string of an enum value.
        *	\param	pIndex	Enum value to get string for.
        *	\return	String value of enum specified by \p pIndex.
        */
        virtual const char* EnumList( int pIndex );

        /**	String list for enum properties.
        *	\param	pCreateIt	Create a new list if necessary.
        *	\return	the pointer to the string list..
        */
        FBStringList* GetEnumStringList(bool pCreateIt = false);

        /**	Notify system that the enum list was modified.
        */
        void NotifyEnumStringListChanged();

        /** ModifyPropertyFlag.
        *	\param	pFlag	The flag to switch to True or False.
        *	\param	pValue	The value to set about this flag.
        *   @warning    Flags are not saved into or read from a FBX file.
        */
        void			ModifyPropertyFlag(FBPropertyFlag pFlag, bool pValue);

        /** GetPropertyFlags.
        *	\return	Return all flags at once.
        */
        FBPropertyFlag	GetPropertyFlags();

        /** GetPropertyFlag
        *	\param	pFlag	Flag to test if it is True or False.
        *	\return			If the flag is True, the function returns True and vice-versa.
        *   @warning    Flags are not saved into or read from a FBX file.
        */
        bool			GetPropertyFlag(FBPropertyFlag pFlag);

        /** SetMinMax
        *	\param	pMin	Minimum value of the property.
        *	\param	pMax	Maximum value of the property.
        *	\param	pForceMinClamp	Force clamping to minimum value of the property.
        *	\param	pForceMaxClamp	Force clamping to maximum value of the property.
        */
        void	SetMinMax( double pMin, double pMax, bool pForceMinClamp = false, bool pForceMaxClamp = false );

        /** SetMin
        *	\param	pMin	Minimum value of the property.
        *	\param	pForceMinClamp	Force clamping to minimum value of the property.
        */
        void	SetMin( double pMin, bool pForceMinClamp = false );

        /** SetMax
        *	\param	pMax	Maximum value of the property.
        *	\param	pForceMaxClamp	Force clamping to maximum value of the property.
        */
        void	SetMax( double pMax, bool pForceMaxClamp = false );

        /** GetMin
        *	\return			Minimum value for the property.
        */
        double	GetMin();

        /** GetMax
        *	\return			Maximum value for the property.
        */
        double	GetMax();

        /**	Get the parent of the object.
        *	\return Parent object.
        */
        inline void* GetParent()	{ return mParent; } 

        /**
        * \name Interface for property locking mechanism.
        *   Locking a property or any number of its channel(s) prevents the user from modifying animation on this property.  
        *   This means that the user can't add, remove or edit any key on any layer of a locked property/channel.  It also 
        *   means that the user can't change the current value of the property.  However, a locked property allows existing 
        *   animation to flow through.  This means that the value of a locked property can change through time as its being 
        *   driven by existing animation and/or constraints. 
        */
        //@{

        /** GetSubMemberCount
        *	\return	Number of sub-members.
        */
        int 	GetSubMemberCount() const;

        /** AllowsLocking
        *	\return	\b true if property can be locked
        */
        bool	AllowsLocking() const;

        /** HasSomethingLocked
        *	\return	\b true if property or any of its members is locked
        */
        bool	HasSomethingLocked() const;

        /** IsLocked
        *	\return	\b true if property is locked
        */
        bool	IsLocked() const;

        /** IsMemberLocked
        *	\param	pIndex	Index of the sub-member of the property to check.
        *	\return	\b true if property sub-member is locked
        */
        bool	IsMemberLocked( int pIndex ) const;

        /** SetLocked
        *	\param	pLocked	True if the property is to be locked, false if it is to be unlocked.
        */
        void	SetLocked( bool pLocked );

        /** SetMemberLocked
        *	\param	pIndex	Index of the sub-member of the property to lock or unlock.
        *	\param	pLocked	True if the sub-member is to be locked, false if it is to be unlocked.
        */
        void	SetMemberLocked( int pIndex , bool pLocked );

        //@}

    private:
        //	FBProperty(FBProperty&); // Make sure no copy constructor is use
    };

	/**	Cast property using it's IObject interface into the proper type.
	*	\param	pProperty		Property pointer to be cast into the proper type.
	*	\param	pAutoCreate		Create object if it doesn't exist? (default = false)
	*	\return	SDK object for \p pProperty.
	*/
	template<class T> inline T* FBCast(FBProperty* pProperty, bool pAutoCreate = false)
	{
		HIObject lProperty = pProperty ? FBGetFBObject(pProperty->GetHIObject(), pAutoCreate) : NULL;
		// Should also validate type but not available for now
		return (T*)lProperty;
	}

    __FB_FORWARD( FBPropertyAnimatable );
    FB_FORWARD( FBBox );
    FB_FORWARD( FBAnimationNode );
    FB_FORWARD( FBTake );

    ///////////////////////////////////////////////////////////////////////////////
    // PropertyEvent
    ///////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD(FBPropertyEvent);

    /** \b PropertyEvent: Base event class.
    *
    *   User could register custom callback function to FBPropertyEvent and perform necessary custom tasks. 
    *
    *   Multiple callbacks could be registered to single event, and they will called in the reverse 
    *   order of registration. 
    *
    *   User could add python callbacks via pyfbsdk (if exposed). Those python callbacks which throws exceptions
    *    will be unregistered automatically
    */
    class FBSDK_DLL FBPropertyEvent : public FBProperty
    {
    protected:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        /*! Internal callback register.*/
        HIRegister	mParentRegister;
        /*! Type of event. */
        int			mType;				
        /*! SubType of event. */
        int			mSubType;
#endif
    public:
        //! Constructor
        FBPropertyEvent();

        /**	Property initialization function.
        *	\param	pComponent	Owner component.
        *	\param	pParent		Internal register interface of object owner.
        *	\param	pName		Name of FBPropertyEvent
        *	\param	pType		Type of event.
        *	\param	pSubType	SubType of event(default=K_INT_MAX).
        *	\return	Pointer to this FBPropertyEvent
        */
        FBPropertyEvent *Init( FBComponent* pComponent, HIRegister pParent,const char *pName, int pType, int pSubType=K_INT_MAX );	

        /**	Property initialization function, for global events.
        *	\param	pName				Name of FBPropertyEvent
        *	\param	pGlobalEventName	Name of global event.
        *	\return	Pointer to this FBPropertyEvent
        */
        FBPropertyEvent *InitGlobal( const char* pName, const char* pGlobalEventName );	

        //! Destructor.
        virtual ~FBPropertyEvent();

        //@{
        /**	Add/Remove a callback.
        *	\param	pOwner		Callback owner.
        *	\param	pHandler	Callback handler.
        */
        virtual void Add		( HICallback pOwner, kICallbackHandler pHandler );
        virtual void Remove		( HICallback pOwner, kICallbackHandler pHandler );
        //@}

        //! Invalidate parent, removing internal register parent.
        virtual void InvalidateParent();

        /**	Get the property's type.
        *	\return	The property's type.
        */
        virtual FBPropertyType GetPropertyType() override { return kFBPT_event; }

    private:

        DataFBPropertyEvent* mLocalPtr;	//!< Internal data.
    };

    //! \b PropertyEvent: UI idle event.
    class FBSDK_DLL FBPropertyEventUIIdle : public FBPropertyEvent
    {
    public:
        virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
        virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
    };

    //! \b PropertyEvent: Video Frame Rendering Event
    class FBSDK_DLL FBPropertyEventVideoFrameRendering : public FBPropertyEvent
    {
    public:
        virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
        virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
    };

    //! \b PropertyEvent: Global ConnectionNotify event.
    class FBSDK_DLL FBPropertyEventConnectionNotify : public FBPropertyEvent
    {
    public:
        virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
        virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
    };

    //! \b PropertyEvent: Global ConnectionDataNotify event.
    class FBSDK_DLL FBPropertyEventConnectionDataNotify : public FBPropertyEvent
    {
    public:
        virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
        virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
    };

    //! \b PropertyEvent: Global ConnectionStateNotify event.
    class FBSDK_DLL FBPropertyEventConnectionStateNotify : public FBPropertyEvent
    {
    public:
        virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
        virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
    };

    //! \b PropertyEvent: Global KeyingNotify event.
    class FBSDK_DLL FBPropertyEventConnectionKeyingNotify : public FBPropertyEvent
    {
    public:
        virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
        virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
    };

    /** \internal
    *	Base template class for all standard properties
    */
    template <class tType, FBPropertyType pPT> class FBPropertyBase : public FBProperty 
    { 
    protected: 
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        void  (* Set)(void *, tType);	//!< Set function pointer.
        tType (* Get)(void *);			//!< Get function pointer.
#endif
    public: 

        //! Property Value Type
        typedef tType ValueType;

        //! Constructor
        inline FBPropertyBase()	{ Set = NULL; Get = NULL; }  

        /** Constructor
        *	\param pValue FBPropertyBase.
        */
        inline FBPropertyBase(const FBPropertyBase<tType,pPT> &pValue)	{ operator=((tType)pValue ); }

        //! Destructor
        ~FBPropertyBase() 
        {	  
        }

        /**	Initialization function.
        *	\param	pParent		Parent object.
        *	\param	pName		Name of base enum.
        *	\param	pGet		Get function (default=NULL).
        *	\param	pSet		Set function (default=NULL).
        *	\return	Pointer to this object.
        */
        inline FBPropertyBase *Init( void* pParent, const char *pName,tType (* pGet)(void *)=NULL,void (* pSet)(void *,tType)=NULL  )
        {  
            mParent = pParent;	
            mName	= pName ;	
            Get		= pGet; 	
            Set		= pSet; 	
            return this;
        } 

        //@{
        /**	Overloaded = operator.
        *	Set the value of the current object using the Set function.
        *	\param	pValue	Value to set for object.
        */
        inline void operator=(tType pValue)					{ SetData( &pValue ); }
        //@}

        //@{
        /**	Overloaded = operator.
        *	Set the value of the current object with another property value of the same type.
        *	\param	pProperty	Property to use to set the value.
        */
        inline void operator=(const FBPropertyBase<tType,pPT> &pProperty)	{ operator=((tType)pProperty ); }
        //@}

        /**	Overloaded cast to \b tType operator.
        *	Get the value of the current object using Get fuction.
        *	\return	\b tType cast of current object.
        */
        inline operator tType() const						{ tType Value; GetData( &Value,sizeof(Value) ); return Value; } 

        /**	Get the property's type.
        *	\return	The property's type.
        */
        virtual FBPropertyType GetPropertyType( ) override { return pPT; }

		/**	Set the value of the internal property.
        *	\param	pValue Value to set to internal property.
        */
        inline virtual void SetPropertyValue( tType pValue )
        {
            if(IsInternal() && GetValuePtr())
            {
                *(tType*)GetValuePtr() = pValue;
            }
        }

        /**	Get the value of the internal property.
        *	\return Property value.
        */
        inline tType GetPropertyValue( )
        {
            if(IsInternal() && GetValuePtr())
            {
                return *(tType*)GetValuePtr();
            } else
            {
                return (tType)0;
            }
        }

        /**	Is this class read-only?
        *	If there is an existing set function, this class is read/write, otherwise it is read-only.
        *	\return \b true if it is read-only.
        */
        inline virtual bool IsReadOnly()  { return IsInternal() ? (FBProperty::IsReadOnly()) : (Set == NULL); }

        /**	Get value.
        *	\retval	pValue Value to fill with current object value.
        */
        inline virtual void GetData(void* pData, int pSize, FBEvaluateInfo *pEvalInfo = NULL) const
        {
            if(Get)
            { 
                *((tType*)pData) = (*Get)(mParent); 
            } 
            else if (IsInternal())
            {
                FBProperty::GetData( pData, pSize, pEvalInfo );
            } 
            else
            {
                assert(Get != NULL || IsInternal());
                *((tType*)pData) = (tType)0; 
            }
        }
        /**	Set value.
        *	\param	pData	Integer to use to set.
        */
        inline virtual void SetData(void* pData)
        { 
            if(Set) 
            { 
                (*Set)( mParent,*(tType*)pData ); 
            } 
            else if (IsInternal())
            {
                FBProperty::SetData( pData );
            } 
            else
            { 
                assert( Set != NULL || IsInternal() ); 
            } 
        } 
    };

    /** \internal
    *   Base template class for enum properties.
    *   Note: Index values of enum type must start from 0 and increase sequentially.
    */
    template <class tType> class FBPropertyBaseEnum : public FBPropertyBase<tType,kFBPT_enum>
    {
    public: 
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        /** String list. */
        static const char *mStrings[];
#endif
        //! Constructor.
        inline FBPropertyBaseEnum(){}  

        //! Destructor.
        inline ~FBPropertyBaseEnum()
        {

        }  

        /** FBPropertyBaseEnum
        *	\param pValue FBPropertyBaseEnum.
        */
        inline FBPropertyBaseEnum(const FBPropertyBaseEnum<tType> &pValue)	{ operator=((tType)pValue ); }

        //@{
        /**	Overloaded = operator.
        *	Set the value of the current object using Set function.
        *	\param	pValue	Value to set for object.
        */
        inline void operator=(tType pValue)					{ SetData( &pValue ); }
        //@}

        /**	Overloaded cast to \b tType operator.
        *	Get the value of the current object using Get function.
        *	\return	\b tType cast of current object.
        */
        inline operator tType() const						{ tType Value; GetData( &Value,sizeof(Value) ); return Value; } 

        virtual const char* EnumList( int pIndex ) override	
        { 	
            if( FBPropertyBaseEnum::IsInternal() )
            {
                return FBProperty::EnumList( pIndex );
            }
			// NOTE: 
			// --> replacing test for if(mStrings) by if(mStrings[0])
			// This is safe to do as we should always have at least 1 item
			// in the list based on our base class implementation. And 
			// the compiler should throw a linker error if mStrings is not found. 
			// mStrings[0] == NULL for enum kDefaultEnum but mStrings can never be NULL
            else if(mStrings[0])
            {
                return mStrings[pIndex]; 
            }
            else
            {
                assert(mStrings[0] || FBPropertyBaseEnum::IsInternal());
                return NULL;
            }
        }

        /**	Get as string.
        *   \param  pFlag Specifies the purpose of returned string it defaults to kFBDataAsStringUI.
        *	\return String list.
        */
        virtual const char* AsString( FBDataAsStringFlag pFlag = kFBDataAsStringUI ) override { return EnumList( FBPropertyBaseEnum::AsInt() );}

        /**	Set enum value by equivalent string
        *	\param	pString String to set for enum property, with format same as AsString(kFBDataAsStringPersistence)
        *   \return True if success.
        */
        virtual bool SetString( const char *pString ) override
        {
            int			Count=0;
            const char *	tmpstr;
            while ((tmpstr=EnumList( Count ))!=NULL) {
                if (strcmp(tmpstr,pString)==0) {
                    FBPropertyBaseEnum::SetData( &Count );
                    return true;
                }
                Count++;
            }
            return false;
        }

    };


    /**	\internal
    *	Base template class for list properties.
    */
    class FBSDK_DLL FBPropertyBasicList : public FBProperty
    {
    public:
        //! Constructor.
        FBPropertyBasicList();
        ~FBPropertyBasicList();
        /**	Constructor.
        *	\param pParent	Parent for property list.
        *	\param pName	Name of property list.
        */
        FBPropertyBasicList( HIObject pParent, const char *pName );
        /**	Initialization function.
        *	\param pParent	Parent of property list.
        *	\param pName	Name of property list.
        */
        FBProperty* Init( void* pParent, const char *pName );

        //!	Remove all properties from the list.
        void RemoveAll();

        /**	Get the number of properties in the list.
        *	\return The number of properties in the list.
        *   \warning <b>overload required</b>.
        */
        virtual int GetCount()=0;

        /**	Remove property at \p pIndex.
        *	\param pIndex Index where property is to be removed.
        *   \warning <b>overload required</b>.
        */
        virtual void RemoveAt( int pIndex )=0;

        /**	Is this a list?
        *	\return \b true if this is a list.
        */
        virtual bool IsList();
    };

    /**	\internal
    *	Base template class for list properties.
    */
    template <class tType> class FBPropertyBaseList : public FBPropertyBasicList
    {
    public:
        //! Constructor.
        FBPropertyBaseList( ):FBPropertyBasicList( ) {}

        //! Destructor.
        ~FBPropertyBaseList( )
        {

        }
        /**	Constructor.
        *	\param pParent	Parent for property list.
        *	\param pName	Name of property list.
        */
        FBPropertyBaseList( HIObject pParent, const char *pName ):FBPropertyBasicList( pParent, pName ) {}

    public:  
        //***
        //--- These functions require overloads in derived classes. 
        //***

        /**	Add a property to the list.
        *	\param pItem Property to add.
        *	\return Index where property was inserted.
        *   \warning <b>overload required</b>.
        */
        virtual int Add( tType pItem )=0;

        /**	[] operator overload.
        *	\param pIndex Index of property to access.
        *	\return Property at \p pIndex.
        *   \warning <b>overload required</b>.
        */
        virtual tType operator[]( int pIndex )=0;

    public: 
        //***
        //--- These functions can be optionally overloaded in derived classes.
        //***

        /**	Locate a property in the list.
        *	\param pItem Property to find in the list.
        *	\return Index where \p pItem can be found.
        */
        inline virtual int Find( tType pItem )		
        { 
            int Index;
            for(Index=0; Index<GetCount(); Index++ ) 
            {
                if( operator[](Index)==pItem ) 
                {
                    return Index; 
                }
            }
            return -1;
        }

        /**	Remove \p pItem from the list.
        *	\param pItem Property to remove from the list.
        *	\return Index where property was removed.
        */
        inline virtual int Remove( tType pItem )		
        {
            int Index = Find( pItem ); 
            if (Index!=-1)
            {
                RemoveAt( Index );
            }
            return Index;
        }

        /**	Get a property at \p pIndex.
        *	\param pIndex Index to access.
        *	\return Property at \p pIndex.
        */
        inline virtual tType GetAt(int pIndex)	
        {
            return operator[](pIndex); 
        }
    };

    /** \enum kDefaultEnum Patch to use the base enum for casting values .*/
    enum kDefaultEnum { 
        kDefaultItemNone	//!< None
    };


    typedef class FBSDK_DLL FBPropertyBaseEnum< enum kDefaultEnum > FBPropertyEnum;
    /** \fn typedef class FBSDK_DLL FBPropertyBaseEnum< enum kDefaultEnum > FBPropertyEnum
    * A typedef Definition
    */

    FB_FORWARD( FBPropertyStringList );

    //! <b>Property:</b> StringList
    class FBSDK_DLL FBPropertyStringList : public FBProperty
    {
    public:
        //! Constructor.
        FBPropertyStringList();

        //! Destructor.
        virtual ~FBPropertyStringList();

        /**	Property initialization function.
        *	\param	pComponent	Owner component.
        *	\param	pName		Name of FBPropertyStringList
        *	\return	Pointer to this FBPropertyStringList
        */
        FBPropertyStringList* Init( FBComponent* pComponent, const char *pName );

    public:
        /**	Get the reference at \p pIndex.
        *	\param	pIndex	Index to get reference at.
        *	\return	Reference stored at \p pIndex.
        */
        kReference  GetReferenceAt( int pIndex );
        /**	Set reference at \p pIndex.
        *	\param	pIndex	Index to set reference at.
        *	\param	pRef	Reference to store.
        */
        void SetReferenceAt( int pIndex,kReference pRef );

        /**	Find the index of a reference.
        *	\param	pRef	Reference to find in list.
        *	\return	Index where reference is stored.
        */
        int	Find( kReference pRef );

        /**	Find the index of a string.
        *	\param	S	String to find in list.
        *	\return	Index of string \p S.
        */
        int	Find( const char *S );

        /**	Get the string stored at \p pIndex.
        *	\param	pIndex	Index to access
        *	\return	String stored at \p pIndex.
        */
        virtual const char *GetAt( int pIndex );

        /** [] operator overload.
        *	Return the string stored at \p pIndex.
        *	\param	pIndex	Index to access.
        *	\return String stored at \p pIndex.
        */
        const char *operator[](int pIndex);

        //! Sort list ascending.
        void Sort( );

        /**	Get the number of items in the list.
        *	\return Number of strings stored in the list.
        */
        int GetCount();

        /**	Remove a string from the list.
        *	\param	S	String to remove from the list.
        *	\return	Index where item was found.
        */
        int	Remove( const char *S );

    public:  // Needs to be overriden for special behaviors
        /**	Add a string to the list.
        *	\param	S		String to add to list.
        *	\param	pRef	Reference to stored with string (default = 0)
        *	\return	Index where item was stored.
        */
        virtual int	Add( const char *S,kReference pRef = 0 );

        //! Clear the list (remove all the items).
        virtual void Clear();

        /**	Remove an entry at \p pIndex.
        *	\param	pIndex	Index where item is to be removed from.
        */
        virtual void RemoveAt( int pIndex );

        /**	Get the index of a string.
        *	\param	S	String to look for.
        *	\return	Index where string \p S was found.
        */
        virtual int	IndexOf(const char *S);

        /**	Insert an entry at \p pIndex.
        *	\param	pIndex	Index where item is to be inserted.
        *	\param	S		String to insert.
        *	\param	pRef	Reference to store with string.
        */
        virtual void InsertAt( int pIndex, const char *S,kReference pRef = 0 );

        /**	Set the string at \p pIndex.
        *	\param	pIndex		Index where string is to be set.
        *	\param	pString		String to set value at \p pIndex with.
        *	\return \b true if success.
        */
        virtual bool SetAt( int pIndex,const char *pString );

        /**	Is this class a list?
        *	\return \b true (this class is a list).
        */
        virtual bool IsList() override;

        /**	Get as string.
        *   \param  pFlag Specifies the purpose of returned string it defaults to kFBDataAsStringUI.
        *	\return String list.
        */
        virtual const char* AsString( FBDataAsStringFlag pFlag = kFBDataAsStringUI ) override;

        /**	Set string for list.
        *	\param	pString String to set for list, with format same as AsString(kFBDataAsStringPersistence)
        *   \return True if it was possible.
        */
        virtual bool SetString( const char *pString ) override;

        /**	Get the property's type.
        *	\return	The property's type.
        */
        virtual FBPropertyType GetPropertyType() override { return kFBPT_stringlist; }
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPropertyManager
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBPropertyManager );

    /** Property Manager.
    *	The property manager exists in all FBComponent objects, and
    *	contains an array of all the registered properties. These properties
    *	may be SDK properties, internal properties or both.
    */
    class FBSDK_DLL FBPropertyManager 
    {
    public:
        //! Constructor.
        FBPropertyManager();

        //! Destructor.
        ~FBPropertyManager();

        /**	Add a property to the property manager.
        *	\param	Property	Handle to property to add.
        *	\return	Index in list where \p Property was added.
        */
        int Add( FBProperty* Property );

        /**	Overloaded [] operator.
        *	Access the property at \p pIndex.
        *	\param	pIndex	Index of property to access.
        *	\return	Property stored at \p pIndex.
        */
        FBProperty* operator[](int pIndex);

        /**	Get the number of properties stored in property manager.
        *	\return	Number of properties in manager.
        */
        int	GetCount();

        /**	Find a property, based on its name.
        *   
        *	\param	pPropertyName       Name of property to look for.
        *	\param	pMultilangLookup    When searching, indicate if the name lookup should also be done on the property name as shown in the GUI. (default = true)
        *	\return	Handle to property found.
        */
        FBProperty* Find( const char *pPropertyName, bool pMultilangLookup=true );

		/** This function will query the property list for properties fulfilling a particular name pattern
		*	\param	pPropertyNamePattern	Indicate the name pattern to search. This pattern can contain any amount of *. (ex: *tr*mod*scene )
		*	\param	pPropList               List that contains the resulting properties matching the pattern
        *	\param	pMultilangLookup		When searching, indicate if the name lookup should also be done on the property name as shown in the GUI. (default = true)
		*	\note The script FindPropertiesWithWildcard.py shows how to use this function.
		*/
		void FindPropertiesByName( const char* pPropertyNamePattern, FBArrayTemplate<FBProperty*>& pPropList, bool pMultilangLookup=true );

        /** Remove a property.
        *	\param pProperty	Property to remove.
        *	\return Index where property was found.
        */
        int Remove( FBProperty* pProperty );

        /** \internal
        *	Add a property to PropertyCache.
        *	\param pProperty	Property to add to cache.
        */
        void AddToCache( FBProperty* pProperty );

        /** \internal
        *	Remove a property from PropertyCache.
        *	\param pProperty	Property to remove from cache.
        */
        void RemoveFromCache( KProperty* pProperty );

        /** \internal
        *	Find a property in PropertyCache.
        *	\param pProperty	Property to find.
        *	\return Property from cache.
        */
        FBProperty* FindInCache( KProperty* pProperty );

    private:
        /** \internal
        *	Clear cache.
        */
        void ClearCache();

        /** \internal
        *	Set the parent object.
        *	\param pParent	Parent object pointer.
        */
        void SetParent( HIObject pParent );

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        KObject*						mObject;		//!< Object reference
        FBArrayTemplate< FBProperty* >	mPropertyCache;	//!< Array of allocated property mappers.
        FBArrayTemplate< FBProperty* >	mPropertyLocal;	//!< Array of static property mappers.
#endif
        friend class FBComponent;
        friend class FBVisualComponent;
    };

    /**	\internal
    *	Base template class for component properties.
    */
    template <class tType> class FBPropertyBaseComponent : public FBPropertyBase< tType, kFBPT_object > 
    {
    public:
        //!< Type information.
        int *TypeInfo;	
    public:
        //!Constructor
        inline FBPropertyBaseComponent() {}

        /** Constructor
        *	\param pValue Value to set for component.
        */
        inline FBPropertyBaseComponent(const FBPropertyBaseComponent<tType> &pValue)	{ FBPropertyBase< tType,kFBPT_object >::operator=((tType)pValue ); }

        //! Destructor
        ~FBPropertyBaseComponent()
        {
        }

        //@{
        /**	Overloaded = operator
        *	\param	pValue	Value to set for component.
        */
        inline void operator=(tType pValue)								{ FBPropertyBase< tType,kFBPT_object >::operator=(pValue); } 
        //@}

        /**	Overloaded -> operator
        *	\return	Dereferenced pointer to this object.
        */
        inline tType operator -> ()									{ return FBPropertyBase< tType,kFBPT_object >::operator tType(); } 

        /**	Overloaded cast to \b tType operator.
        *	\return	\b tType cast of current object.
        */
        inline operator tType() const									{ return FBPropertyBase< tType,kFBPT_object >::operator tType(); } 
    };

    /**	Implement a property based on a component
    *	\param	DllTag		Associated DLL.
    *	\param	Type	Class to implement.
    */
#if defined(KARCH_DEV_INTEL)
#define FBImplementPropertyComponent( DllTag, Type ) 
#else
#define FBImplementPropertyComponent( DllTag, Type ) \
    template class DllTag FBSDKNamespaceFunc(FBPropertyBase)< FB##Type*,kFBPT_object >;	\
    template class DllTag FBSDKNamespaceFunc(FBPropertyBaseComponent)< FB##Type* >;
#endif

    /**	Implement a property based on an enumeration
    *	\param	DllTag		Associated DLL.
    *	\param	Type	Class to implement.
    */
#if defined(KARCH_DEV_INTEL)
#define FBImplementPropertyEnum( DllTag, Type )	// On SGI by having mString defined for each enum already instantiates the template.
#define FBImplementClassPropertyEnum( DllTag, Class, EnumName )
#else
#define FBImplementPropertyEnum( DllTag, Type ) \
    template class DllTag FBSDKNamespaceFunc(FBPropertyBaseEnum)< enum FB##Type >
#define FBImplementClassPropertyEnum( DllTag, Class, EnumName ) \
    template class DllTag FBSDKNamespaceFunc(FBPropertyBaseEnum)< enum Class::E##EnumName >
#endif

    /** Implement a property list for a component
    *	\param	DllTag		Associated DLL.
    *	\param	Type	Class to implement list for.
    */
#if defined(KARCH_DEV_INTEL)
#define FBImplementPropertyList( DllTag, Type )
#else
#define FBImplementPropertyList( DllTag, Type ) \
    template class DllTag FBSDKNamespaceFunc(FBPropertyBaseList) < FB##Type* >
#endif


    //!	\b Property class: const char * (String).
    class FBSDK_DLL FBPropertyString : public FBPropertyBase< const char *, kFBPT_charptr > 
    {
    public:

        //@{
        /**	Overloaded = operator.
        *	Set the value of the current object using the Set function.
        *	\param	pValue	Value to set for object.
        */
        inline void operator=(const char* pValue)					{ SetData( &pValue ); }
        //@}

        /**	Overloaded cast to \b tType operator.
        *	Get the value of the current object using Get function.
        *	\return	\b tType cast of current object.
        */
        inline operator const char* () const							{ char* Value; GetData( &Value,sizeof(Value) ); return Value; } 

        inline bool operator==(const char* pValue) const                { char* Value; GetData( &Value,sizeof(Value) ); return (Value == pValue) || (strcmp(Value, pValue) == 0); }
        inline bool operator!=(const char* pValue) const                { return ! operator==(pValue); }

        /**	Set the value of the internal property.
        *	\param	pValue Value to set to internal property.
        */
        virtual void SetPropertyValue( const char* pValue ) override;
    };

    //!	<b>Property:</b> bool
    typedef class FBSDK_DLL FBPropertyBase< bool,kFBPT_bool > FBPropertyBool;

    /**	<b>Property:</b> Action
    *	Action property to trigger function.
    */
    class FBSDK_DLL FBPropertyAction : public FBPropertyBase< bool, kFBPT_Action > 
    {
    public:
        //!Constructor
        inline FBPropertyAction() {}

        //! Destructor
        ~FBPropertyAction()
        {
        }

        /**	Overloaded () operator
        *	\return	true if function call succeed.
        */
        bool operator ()();
    };

    //!	<b>Property:</b> int
    typedef class FBSDK_DLL FBPropertyBase< int,kFBPT_int > FBPropertyInt;

    //!	<b>Property:</b> int
    typedef class FBSDK_DLL FBPropertyBase< long long,kFBPT_int64 > FBPropertyInt64;

    //!	<b>Property:</b> int
    typedef class FBSDK_DLL FBPropertyBase< unsigned long long,kFBPT_uint64 > FBPropertyUInt64;

    //!	<b>Property:</b> double
    typedef class FBSDK_DLL FBPropertyBase< double,kFBPT_double > FBPropertyDouble;

    //!	<b>Property:</b> float
    typedef class FBSDK_DLL FBPropertyBase< float,kFBPT_float > FBPropertyFloat;

    //!	<b>Property:</b> FBTime
    typedef class FBSDK_DLL FBPropertyBase< FBTime,kFBPT_Time > FBPropertyTime;

    //!	<b>Property:</b> FBTimeCode
    typedef class FBSDK_DLL FBPropertyBase< FBTimeCode,kFBPT_TimeCode > FBPropertyTimeCode;

    //!	<b>Property:</b> FBTimeSpan
    typedef class FBSDK_DLL FBPropertyBase< FBTimeSpan,kFBPT_TimeSpan > FBPropertyTimeSpan;

    //!	<b>Property:</b> kReference
    typedef class FBSDK_DLL FBPropertyBase< kReference,kFBPT_kReference >	FBPropertykReference;

    //!	<b>Property:</b> FBProperty *
    typedef class FBSDK_DLL FBPropertyBase< FBProperty*,kFBPT_Reference >			FBPropertyReference;
    //!	<b>Property:</b> FBPropertyBase(FBComponent*)
    typedef class FBSDK_DLL FBPropertyBase< FBComponent*,kFBPT_object >			_FBPropertyBaseComponent;
    //!	<b>Property:</b> FBPropertyBaseComponent(FBComponent*)
    typedef class FBSDK_DLL FBPropertyBaseComponent< FBComponent* > FBPropertyComponent;
    //!	<b>Property:</b> FBPropertyBase(FBPlug*)
    typedef class FBSDK_DLL FBPropertyBase< FBPlug*,kFBPT_object >           _FBPropertyBasePlug;
    //!	<b>Property:</b> FBPropertyBaseComponent(FBPlug*)
    typedef class FBPropertyBaseComponent< FBPlug* >  FBPropertyPlug;

    /**	Initialize a property: default.
    *	\param	Param		Owner name.
    *	\param	Type		Type of variable.
    *	\param	PropName	Variable name.
    *	\param	Get			Get function pointer.
    *	\param	Set			Set function pointer.
    */
#define FBPropertyInit( Param,Type,PropName,Get,Set ) \
    { \
    PropertyAdd(PropName.Init( (void*)Param,#PropName,(Type (*)(void *))Get,(void (*)(void *,Type))Set )); \
    }

    /**	Initialize a property: list.
    *	\param	Param		Owner name.
    *	\param	PropName	Variable name.
    */
#define FBPropertyInitList( Param,PropName ) \
    { \
    PropertyAdd(PropName.Init( Param,#PropName )); \
    }

    /**	Initialize a property: string list.
    *	\param	Param		Owner name.
    *	\param	PropName	Variable name .
    */
#define FBPropertyInitStringList( Param,PropName ) \
    { \
    PropertyAdd(PropName.Init( Param, #PropName )); \
    }

    /**	Initialize a property: event.
    *	\param	Param		Owner name.
    *	\param	Type		Event Type.
    *	\param	SubType		Event SubType.
    *	\param  PropName	Variable name.
    */
#define FBPropertyInitEvent( Param,Type,SubType,PropName ) \
    { \
    PropertyAdd(PropName.Init( this, IQ(Param,IRegister),#PropName,Type,SubType )); \
    }

    /**	Initialize a property: global event.
    *	\param	GlobalEventName		Name of the global eventEvent Type.
    *	\param  PropName			Variable name.
    */
#define FBPropertyInitEventGlobal( GlobalEventName,PropName ) \
    { \
    PropertyAdd(PropName.InitGlobal( #PropName,GlobalEventName )); \
    }

    /** Mapping to internal properties. */
#define FBPropertyInitInternal( Parent, PropName, MBProperty ) \
    {\
    PropertyAdd(PropName.InitInternal( MBProperty ));\
    }

    /** Mapping to internal enum properties. */
#define FBPropertyInitInternalEnum( Param,Type,PropName,MBProperty,Get,Set  ) \
    {\
    PropName.InitInternal( MBProperty ); \
    PropertyAdd(PropName.Init( (void*)Param,#PropName,(Type (*)(void *))Get,(void (*)(void *,Type))Set )); \
    }

    /** Publish a property
    \param Parent		Owner name.
    \param Prop			Variable
    \param PropName		Variable Name.
    \param Get			Get function pointer.
    \param Set			Set function pointer.
    */
#define FBPropertyPublish( Parent,Prop,PropName,Get,Set ) \
    { \
    PropertyAdd(Prop.CreateInternal( Parent,PropName,(fbExternalGetSetHandler)Get,(fbExternalGetSetHandler)Set )); \
    }

    /**	Initialize a property: user texture connect property. Only support Color, ColorAndAlpha, Number, Vector, Vector2, Vector4 data type for  user texture connectable property!
    \remarks            Need initialize the property before assign a value for it, otherwise may get assert failure.
    \param Parent		Owner name.
    \param Prop			Variable
    \param PropName		Variable Name.
    */
#define FBPropertyInitTextureConnectable( Parent,Prop,PropName ) \
    { \
    PropertyAdd(Prop.CreateTextureConnectable( Parent,PropName )); \
    }

    typedef class FBSDK_DLL FBPropertyBase< FBColor,kFBPT_ColorRGB >	FBPropertyColor;
    /** \fn typedef class FBSDK_DLL FBPropertyBase< FBColor,kFBPT_ColorRGB >	FBPropertyColor
    * FBPropertyColor type definition.
    */

    typedef class FBSDK_DLL FBPropertyBase< FBColorAndAlpha,kFBPT_ColorRGBA >	FBPropertyColorAndAlpha;
    /** \fn typedef class FBSDK_DLL FBPropertyBase< FBColorAndAlpha,kFBPT_ColorRGBA >	FBPropertyColorAndAlpha
    * FBPropertyColorAndAlpha type definition.
    */

    typedef class FBSDK_DLL FBPropertyBase< FBVector2d,kFBPT_Vector2D >	FBPropertyVector2d;
    /** \fn typedef class FBPropertyBase< FBVector2d,kFBPT_Vector2D > FBPropertyVector2d
    * FBPropertyVector2d type definition.
    */

    typedef class FBSDK_DLL FBPropertyBase< FBVector3d,kFBPT_Vector3D >	FBPropertyVector3d;
    /** \fn typedef class FBPropertyBase< FBVector3d,kFBPT_Vector3D > FBPropertyVector3d 
    * FBPropertyVector3d type definition.
    */


    typedef class FBSDK_DLL FBPropertyBase< FBVector4d,kFBPT_Vector4D >	FBPropertyVector4d;
    /** \fn typedef class FBPropertyBase< FBColor,kFBPT_Vector4D > FBPropertyVector4d 
    *	FBPropertyVector4d type definition.
    */

    //!	Animatable property base class.
    class FBSDK_DLL FBPropertyAnimatable : public FBProperty
    {
    public:
        /**	Constructor
        */
        FBPropertyAnimatable();

        /** Destructor.
        */
        virtual ~FBPropertyAnimatable();

    public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        //! Initialize internal pointer.
        FBPropertyAnimatable* InitInternal( KEvaluationProperty* pProperty );
#endif
        /**	Initialization function (custom).
        *	\param	pOwner	Owner box object.
        *	\param	pName	Name of property to add.
        *	\param	pType	Type name (string) of property.
        *	\param	pInit	Initialization value.
        *	\return	this, once initialized.
        */
        FBPropertyAnimatable* Init( FBBox* pOwner, const char* pName, const char* pType, double* pInit );

        /**	Destruction function, for internal connectors.
        *	Used in the case of custom properties in order to remove the connectors.
        */
        void Destroy();

        /**	Get the property datatype pointer.
        *	\return Datatype of property.
        */
        virtual KDataType* GetDataType() override;

        /**	Get the property datatype name.
        *	\return Datatype of property as a character string.
        */
        const char* GetDataTypeName();

        /**	Is the property focused (keyable).
        *	\return Current focus (keyable) state for the property.
        */
        bool IsFocused();

        /** Set the property's focus (keyable) state.
        *	\param	pState	Focus (keyable) state to set for the property.
        */
        void SetFocus( bool pState );

        /**	Key the property.
        */
        void Key();

        /**	Key the property at time (t).
        *   @param pTime    Time at which to insert the key.
        */
        void KeyAt( FBTime pTime );

        /**	Remove the key at time (t).
        *   @param pTime    Time at which to insert the key.
        */
        void KeyRemoveAt( FBTime pTime );

        /**	Get the data size (number of values) for the connector.
        *	\return	Data size.
        */
        int GetDataSize() const;

        //@{
        /**	Certify that the property is animatable.
        *	\return	\b true because it is necessarely an animatable property.
        */
        virtual bool IsAnimatable() override { return true; }

        /**	Is the property animated.
        *	This is true if the property has an FCurve associated to it.
        *	\return	\b true if animated, \b false if not animated.
        */
        bool IsAnimated();

        /**	Set the animation state of the property.
        *	\param	pState	State of animation for property, true to animate, false to remove curves.
        *	\param	pCheckLocked	Decides whether to check the locked status.
        */
        void SetAnimated( bool pState, bool pCheckLocked = false );

        /**	Get the animation node for the property.
        *	\param	pTake to get the animation node from.
        *	\return	Animation node for property. NULL is returned if property is not animated.
        */
        FBAnimationNode* GetAnimationNode(FBTake* pTake=NULL);

        /**	Get the owner box.
        *	\return Handle to the owning box (i.e. model).
        */
        FBBox* GetBox();

        /**	Set the value of the property, passing the type as an argument.
        *	\param	pData	Value to affect property with.
        */
        virtual void SetData( void* pData ) override;

        /**	Get the value of a property.
        *	\retval	pValue	Value to fill with property's current value.
        */
        virtual void GetData( void* pData, int pSize, FBEvaluateInfo* pEvalInfo = NULL ) const override;

		/**	Set the candidate.
		*	\param	pData		Value of data to candidate.
		*   \param  pSize       The size of the current type of data.
        *	\param	pEvalInfo	Candidate time.
		*/
		void SetCandidate( void* pData, int pSize, FBEvaluateInfo* pEvalInfo = NULL );

		/**	Set the global candidate (useful for model TRS).
		*	\param	pData		Value of data to candidate.
		*   \param  pSize       The Size of the current type of data.
        *	\param	pEvalInfo	Candidate time.
		*/
		void SetGlobalCandidate( void* pData, int pSize, FBEvaluateInfo* pEvalInfo = NULL );


        /**
        * \name Interface for animatable property mute mechanism.
        *   Muting an animatable property (or its channels) prevents animation from flowing through a property (or its channels). 
        *   This means that value of a muted property (or its channels) will be the value upon muting, instead of changing 
        *   over time as it is being driven by its existing animation and/or constraints.   
        *   User however can still modify the muted property to add/remove/edit existing keys.
        */
        //@{

        /** AllowsMuting
        *	\return	\b true if property can be muted
        */
        bool	AllowsMuting() const;

        /** HasSomethingMuted
        *	\return	\b true if property or any of its members is muted
        */
        bool	HasSomethingMuted() const;

        /** IsMuted
        *	\return	\b true if property is muted
        */
        bool	IsMuted() const;

        /** IsMemberMuted
        *	\param	pIndex	Index of the sub-member of the property to check.
        *	\return	\b true if property sub-member is muted
        */
        bool	IsMemberMuted( int pIndex ) const;

        /** SetMuted
        *	\param	pMuted	True if the property is to be muted, false if it is to be unmuted.
        */
        void	SetMuted( bool pMuted );

        /** SetMemberMuted
        *	\param	pIndex	Index of the sub-member of the property to mute or unmute.
        *	\param	pMuted	True if the sub-member is to be muted, false if it is to be unmuted.
        */
        void	SetMemberMuted( int pIndex , bool pMuted );

        //@}

    };

    /**	\internal
    *	Base template class for animatable properties
    */
    template <class tType, FBPropertyType pPT> class FBPropertyBaseAnimatable : public FBPropertyAnimatable
    {
    public:

        //! Property Value Type
        typedef tType ValueType;

        //! Constructors.
        FBPropertyBaseAnimatable( );
        FBPropertyBaseAnimatable( const FBPropertyBaseAnimatable<tType,pPT> &pValue);

        //! Destructor.
        ~FBPropertyBaseAnimatable( );

        //@{
        /**	Overloaded = operator
        *	\param	pValue	Value to set for property.
        */
        void operator=(tType pValue);
        //@}

        /**	Overloaded cast to \b tType operator.
        *	\return	\b tType cast of current object.
        */
        operator tType() const;

        /**	Get the property's type.
        *	\return	The property's type.
        */
        virtual FBPropertyType GetPropertyType( ) override { return pPT; }
    };


    typedef class FBSDK_DLL FBPropertyBaseAnimatable< bool,kFBPT_Action > FBPropertyAnimatableAction;
    /** \fn typedef FBPropertyBaseAnimatable< bool,kFBPT_Action > FBPropertyAnimatableAction 
    *	FBPropertyAnimatableAction type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< bool,kFBPT_bool > FBPropertyAnimatableBool;
    /** \fn typedef FBPropertyBaseAnimatable< bool,kFBPT_bool > FBPropertyAnimatableBool 
    *	FBPropertyAnimatableBool type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< int,kFBPT_int > FBPropertyAnimatableInt;
    /** \fn typedef FBPropertyBaseAnimatable< int,kFBPT_in > FBPropertyAnimatableInt
    *	FBPropertyAnimatableInt type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< long long,kFBPT_int64 > FBPropertyAnimatableInt64;
    /** \fn typedef FBPropertyBaseAnimatable< long long,kFBPT_int64 > FBPropertyAnimatableInt64
    *	FBPropertyAnimatableInt64 type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< unsigned long long,kFBPT_uint64 > FBPropertyAnimatableUInt64;
    /** \fn typedef FBPropertyBaseAnimatable< unsigned long long,kFBPT_uint64 > FBPropertyAnimatableUInt64
    *	FBPropertyAnimatableUInt64 type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< int,kFBPT_enum > FBPropertyAnimatableEnum;
    /** \fn typedef FBPropertyBaseAnimatable< int,kFBPT_enum > FBPropertyAnimatableEnum
    *	FBPropertyBaseAnimatableEnum type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< double,kFBPT_double >	 FBPropertyAnimatableDouble;
    /** \fn typedef FBPropertyBaseAnimatable< double,kFBPT_double >	FBPropertyAnimatableDouble
    *	FBPropertyBaseAnimatableDouble type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< FBTime,kFBPT_Time >	 FBPropertyAnimatableTime;
    /** \fn typedef FBPropertyBaseAnimatable< FBTime,kFBPT_time >	FBPropertyAnimatableTime
    *	FBPropertyBaseAnimatableTime type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< FBTimeCode,kFBPT_TimeCode >	FBPropertyAnimatableTimeCode;
    /** \fn typedef FBPropertyBaseAnimatable< FBTimeCode,kFBPT_timecode >	FBPropertyAnimatableTimeCode
    *	FBPropertyBaseAnimatableTimeCode type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< FBVector2d,kFBPT_Vector2D > FBPropertyAnimatableVector2d;
    /** \fn typedef FBPropertyBaseAnimatable< FBVector2d,kFBPT_Vector2D > FBPropertyAnimatableVector2d
    *	FBPropertyAnimatableVector2D type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< FBVector3d,kFBPT_Vector3D > FBPropertyAnimatableVector3d;
    /** \fn typedef FBPropertyBaseAnimatable< FBVector3d,kFBPT_Vector3D > FBPropertyAnimatableVector3d
    *	FBPropertyAnimatableVector3D type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< FBVector4d,kFBPT_Vector4D > FBPropertyAnimatableVector4d;
    /** \fn typedef FBPropertyBaseAnimatable< FBVector4d,kFBPT_Vector4D > FBPropertyAnimatableVector4d
    *	FBPropertyAnimatableVector4D type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< FBColor,kFBPT_ColorRGB >	FBPropertyAnimatableColor;
    /** \fn typedef FBPropertyBaseAnimatable< FBColor,kFBPT_ColorRGB > FBPropertyAnimatableColor
    *	FBPropertyAnimatableColor type definition.
    */
    typedef class FBSDK_DLL FBPropertyBaseAnimatable< FBColorAndAlpha,kFBPT_ColorRGBA >	FBPropertyAnimatableColorAndAlpha;
    /** \fn typedef FBPropertyBaseAnimatable< FBColorAndAlpha,kFBPT_ColorRGBA > FBPropertyAnimatableColorAndAlpha
    *	FBPropertyAnimatableColorAndAlpha type definition.
    */


    /**	\internal
    *	Base template class for enum properties.
    */
    template <class tType> class FBPropertyBaseAnimatableEnum : public  FBPropertyBaseAnimatable<int,kFBPT_enum>
    {
    public: 
#ifndef DOXYGEN_SHOULD_SKIP_THIS
        /** String list. */
        static const char *mStrings[];
#endif

        //! Constructor.
        inline FBPropertyBaseAnimatableEnum(){}  

        //! Destructor.
        inline ~FBPropertyBaseAnimatableEnum()
        {
        }  

        /** FBPropertyBaseAnimatableEnum
        *	\param pValue FBPropertyBaseAnimatableEnum.
        */
        inline FBPropertyBaseAnimatableEnum(const FBPropertyBaseAnimatableEnum<tType> &pValue)	{ operator=((tType)pValue ); }

        //@{
        /**	Overloaded = operator.
        *	Set the value of the current object using Set function.
        *	\param	pValue	Value to set for object.
        */
        inline void operator=(tType pValue)					{ SetData( &pValue ); }
        //@}

        /**	Overloaded cast to \b tType operator.
        *	Get the value of the current object using Get fuction.
        *	\return	\b tType cast of current object.
        */
        inline operator tType() const						{ tType Value; GetData( &Value,sizeof(Value) ); return Value; } 

        virtual const char* EnumList( int pIndex ) override
        { 	
            if( IsInternal() )
            {
                return FBProperty::EnumList( pIndex );
            }
			// NOTE: 
			// --> replacing test for if(mStrings) by if(mStrings[0])
			// This is safe to do as we should always have at least 1 item
			// in the list based on our base class implementation. And 
			// the compiler should throw a linker error if mStrings is not found. 
			// mStrings[0] == NULL for enum kDefaultEnum but mStrings can never be NULL
            else if(mStrings[0])
            {
                return mStrings[pIndex]; 
            }
            else
            {
                assert(mStrings[0] || IsInternal());
                return NULL;
            }
        }

        /**	Get as string.
        *   \param  pFlag Specifies the purpose of returned string it defaults to kFBDataAsStringUI.
        *	\return Enum value as string.
        */
        virtual const char* AsString( FBDataAsStringFlag pFlag = kFBDataAsStringUI ) override { return EnumList( AsInt() );}

        /**	Set string as enum value
        *	\param	pString String to set, with format same as AsString(kFBDataAsStringPersistence)
        *   \return True if success.
        */
        virtual bool SetString( const char *pString ) override
        {
            int			Count=0;
            const char *	tmpstr;
            while ((tmpstr=EnumList( Count ))!=NULL) {
                if (strcmp(tmpstr,pString)==0) {
                    SetData( &Count );
                    return true;
                }
                Count++;
            }
            return false;
        }


    };

    ////////////////////////////////////////////////////////////////////////////////////
    // Global
    ////////////////////////////////////////////////////////////////////////////////////
#ifdef FBSDKUseNamespace
}
#endif

#endif
