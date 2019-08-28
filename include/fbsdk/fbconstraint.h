#ifndef __FBCONSTRAINT_H__
#define __FBCONSTRAINT_H__
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

/**	\file fbconstraint.h
*	Contraint classes.
*	Classes from this file permit the user to derive, create and control
*	constraints via the software development kit.
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

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

FB_DEFINE_COMPONENT( FBSDK_DLL, Constraint );

/**	Register the constraint.
*	\param	UniqueNameStr	Unique name.
*	\param	ClassName		Name of the constraint class.
*	\param	Label			Short description of constraint.
*	\param	Description		Long description of constraint.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterConstraint( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
	HIObject RegisterConstraint##ClassName##Create( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName(pName); \
		Class->UniqueName = UniqueNameStr; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
\
	FBLibraryModule( ClassName ) \
	{	\
		FBRegisterObject( ClassName##R1,"Constraints",Label,Description,RegisterConstraint##ClassName##Create,true, IconFilename ); \
		FBRegisterObject( ClassName##R2,"FbxStorable/Constraint",UniqueNameStr,Description,RegisterConstraint##ClassName##Create,true, IconFilename ); \
	}

/** Constraint class declaration.
*	\param	ClassName	Constraint class name.
*	\param	Parent		Parent class name.
*	\warning The class must inherit directly from FBConstraint.
*/
#define FBConstraintDeclare( ClassName, Parent ) \
	FBClassDeclare( ClassName, Parent ); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/** Constraint class implementation.
*	\param	ThisComponent The name of the class to implement.
*/
#define FBConstraintImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

////////////////////////////////////////////////////////////////////////////////////
// FBConstraintInfo
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBConstraintInfo );

/** Constraint information class.
*	This data structure is passed to the real-time evaluation callback
*	for a constraint (AnimationNodeNotify()).
*/
class FBSDK_DLL FBConstraintInfo 
{
public:
	/**	Was a 'snap' requested?
	*	\return \b true if 'snap' was requeststed.
	*/
	bool GetSnapRequested();

	/**	Was a 'zero' requested?
	*	\return \b true if 'zero' was requeststed.
	*/
	bool GetZeroRequested();
};

////////////////////////////////////////////////////////////////////////////////////
// FBConstraint
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBConstraint);

//! Base class for constraints.
class FBSDK_DLL FBConstraint : public FBBox {
	__FBClassDeclare( FBConstraint,FBBox );
public:
	/** Constructor.
	*	\param	pName		Name of constraint.
	*	\param	pObject		For internal use only (default is NULL).
	*/
	FBConstraint(const char* pName, HIObject pObject=NULL);

    IObject_Declare(K_IMPLEMENTATION);			// Interface to IObject

	virtual void ActiveChanged();				//!< Notification for Activation Status Change.

	virtual void RemoveAllAnimationNodes();		//!< Remove animation nodes.
	virtual void SetupAllAnimationNodes();		//!< Setup animation nodes.

	virtual void SnapSuggested();				//!< Suggest 'snap'.
	virtual void FreezeSuggested();				//!< Suggest 'freeze'.

	/** Disable constraint on \e pModel
	*	\param	pModel	 Model on which constraint should be disabled.
	*	\return \b true if successful.
	*/
	virtual bool Disable( FBModel* pModel );	

	/** Enable constraint on \e pModel
	*	\param	pModel	 Model on which constraint should be enable.
	*	\return \b true if successful.
	*/
	virtual bool Enable( FBModel* pModel );	

	/** Notification callback for connectors.
	*	\param	pAnimationNode		Animation node being notified.
	*	\param	pEvaluateInfo		Information for evaluation.
	*	\param	pConstraintInfo		Information for constraint.
	*	\return \b true if successful.
	*/
	virtual bool AnimationNodeNotify( FBAnimationNode* pAnimationNode, FBEvaluateInfo* pEvaluateInfo, FBConstraintInfo* pConstraintInfo );

	//@{
	/** Animation Node Creations (IN/OUT).
	*	Used to create the connectors (in or out) on an animation node. This function will return a 
	*	newly created animation	node, connected to the model specified by \e pModel.
	*	\param	pUserId		User specified reference number.
	*	\param	pModel		Model to associate with animation node.
	*	\param	pAttribute	Attribute of model to animate (i.e. Translation, Lcl Translation, etc.)
	*	\return Newly created IN/OUT animation node.
	*/
	FBAnimationNode* AnimationNodeOutCreate	( kReference pUserId, FBModel* pModel, const char* pAttribute );
	FBAnimationNode* AnimationNodeInCreate	( kReference pUserId, FBModel* pModel, const char* pAttribute );
	/** Animation Node Creations (IN).
	*	Used to create the In connectors on an animation node. This function will return a 
	*	newly created animation	node, connected to the model specified by \e pProperty.
	*	\param	pUserId		User specified reference number.
	*	\param	pProperty	Property of model to animate (must be animatable)
	*	\return Newly created IN animation node.
	*/
	FBAnimationNode* AnimationNodeInCreate	( kReference pUserId, FBProperty* pProperty );
	//@}

	/** Save current state of \e pModel.
	*	\param	pModel	Model to save.
	*	\param	pS		Scaling information?
	*	\param	pR		Rotation information?
	*	\param	pT		Translation information?
	*/
	virtual void SaveModelState( FBModel* pModel, bool pS, bool pR, bool pT );

	/** Restore the saved model state onto \e pModel.
	*	\param	pModel	Model to affect with previous state.
	*/
	virtual void RestoreModelState( FBModel* pModel );

	/**	Freeze current model state.
	*	\param	pModel	Model to freeze constraint on.
	*	\param	pS		Scaling freeze?
	*	\param	pR		Rotation freeze?
	*	\param	pT		Translation freeze?
	*/
	virtual void FreezeSRT( FBModel* pModel, bool pS, bool pR, bool pT );

	/** Clone the constraint.
	*	\return Newly created (and copied) constraint.
	*/
	virtual FBConstraint* Clone();

	/** Return the number of reference groups.
	*	\return Number of reference groups.
	*/
	int	ReferenceGroupGetCount();

	/**	Add a group of references
	*	\param	pGroupName		Name of reference group to add.
	*	\param	pMaxItemCount	Maximum number of items in \e pGroupName.
	*	\return Index of new reference group.
	*/
	int	ReferenceGroupAdd( const char* pGroupName, int pMaxItemCount );

	/**	Get the name of the reference group.
	*	\param	pGroupIndex	Index of the reference group to get the name for.
	*	\return The name of the reference group \e pGroupIndex.
	*/
	const char* ReferenceGroupGetName( int pGroupIndex );

	/**	Get the maximum number of items that can exist in 
	*	the reference group in question.
	*	\param	pGroupIndex	Index of reference group.
	*	\return	Maximum number of items that can be added to the reference group.
	*/
	int ReferenceGroupGetMaxCount( int pGroupIndex );

	/** Get a reference.
	*	\param	pGroupIndex	Index of reference group containing desired reference.
	*	\param	pItemIndex	Index of reference in group to get (default is 0).
	*	\return Model at specified reference.
	*/
	FBModel* ReferenceGet( int pGroupIndex,	int pItemIndex=0 );

	/**	Get number of references in a specified group.
	*	\param	pGroupIndex Index of group to query the number of references.
	*	\return	Number of references in specified group.
	*/
	int ReferenceGetCount( int pGroupIndex );

	/**	Add a reference to a specified group.
	*	\param	pGroupIndex	Group to add reference to.
	*	\param	pModel		Model to place at new reference.
	*	\return	\b true if successful.
	*	\warning If you try to add a model to a group that is already full, 
	*	the success of the operation will be false and the reference will not be added.
	*/
	bool ReferenceAdd( int pGroupIndex, FBModel* pModel );

	/**	Remove a reference to \e pModel from the group at \e pGroupIndex.
	*	\param	pGroupIndex	Index to remove reference from.
	*	\param	pModel		Model to remove reference from.
	*	\return	\b true if successful.
	*/
	bool ReferenceRemove( int pGroupIndex, FBModel* pModel );

	/** Remove All References. */
	void ReferenceRemoveAll();

	//@{
	/** Notification callbacks for when a reference is added or removed.
	*	\param	pGroupIndex	Index of group where reference was affected.
	*	\param	pModel		Model to which reference was associated.
	*	\return \b true if successful.
	*/
	virtual bool ReferenceAddNotify		( int pGroupIndex, FBModel* pModel );
	virtual bool ReferenceRemoveNotify	( int pGroupIndex, FBModel* pModel );
	//@}

	/**	Deformation pre-notification function
    *   This function pass the evaluation information for deformation (if timing is required). And user should provide
    *   the estimation of the bounding volume of the model after deformation. This estimation will be used to determine 
    *   the model's visibility in the camera's frustum. Only those potential visible models will receive the following 
    *   DeformerNotify() callback.
	*	\param	pModel		    Model to deform.
	*	\param	pEvaluateInfo	Information for evaluation.
	*	\param	pBBoxMin	    (In/Out) The estimation of min vertex of the bounding box before & after deformation
    *	\param	pBBoxMax	    (In/Out) The estimation of max vertex of the bounding box before & after deformation
    *   \return \b true if the deformer provide valid bbox estimation and wish reduce the following deformation if possible,
    *           \b false if deformer wish to continue deformation without considering frustum visibility.
	*/
	virtual bool DeformerPreNotify(	FBModel* pModel, FBEvaluateInfo* pEvaluateInfo, FBVertex*  pBBoxMin,FBVertex*  pBBoxMax);

	/**	Deformation notification function
	*	\param	pModel		Model to deform.
	*	\param	pSrcVertex	Source vertex array (i.e. vertex to deform).
	*	\param	pSrcNormal	Normals at source vertex array.
	*	\param	pCount		Number of vertices in source/destination arrays
	*	\param	pDstVertex	Destination vertex array (i.e. where source vertex gets deformed to)
	*	\param	pDstNormal	Normals at destination vertex array.
	*	\return \b true if successful.
	*/
	virtual bool DeformerNotify(	FBModel* pModel, const FBVertex*  pSrcVertex, const FBVertex* pSrcNormal,
									int pCount, 
									FBVertex*  pDstVertex,FBVertex*  pDstNormal);

	//@{
	/** Bind/Unbind \e pModel to deformation constraint.
	*	These functions are used for adding/removing a deformation binding to/from \e pModel
	*	if the constraint is a deformation constraint.
	*	\param	pModel Model to bind/unbind.
	*	\return \b true if successful.
	*/
	virtual bool DeformerBind	( FBModel* pModel );
	virtual bool DeformerUnBind	( FBModel* pModel );
	//@}

	//@{ 
	/**	Store/Retrieve data to/from FBX files.
	*	\param	pFbxObject	Interface to FBX format.
	*	\param	pStoreWhat	Attributes to store in FBX file.
	*	\return \b true if successful.
	*/
	virtual bool FbxStore	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
	virtual bool FbxRetrieve( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );
	//@}

	FBPropertyBool				Deformer;			//!< <b>Read Write Property:</b> Is a deformer constraint?
	FBPropertyBool				HasLayout;			//!< <b>Read Write Property:</b> Does the constraint have a layout?
	FBPropertyString			Description;		//!< <b>Read Write Property:</b> Long description of constraint.

	FBPropertyBool				Active;				//!< <b>Read Write Property:</b> Active state.
	FBPropertyBool				Lock;				//!< <b>Read Write Property:</b> Lock state.
	FBPropertyAction			Snap;				//!< <b>Function Property:</b> Snap constraint.
	FBPropertyAnimatableDouble	Weight;				//!< <b>Read Write Property:</b> Weight of constraint.
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListConstraint
////////////////////////////////////////////////////////////////////////////////////
//! \b PropertyList: Contraint
class FBSDK_DLL FBPropertyListConstraint : public FBPropertyListComponent
{
public:
	FBPropertyListConstraint();
	/**	Get the constraint at \e pIndex.
	*	\param	pIndex	Index of deck.
	*	\return Handle to Constraint at \e pIndex.
	*/
	FBConstraint* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListBox
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBBox ); 
__FB_FORWARD( FBPropertyListBox );
FB_DEFINE_LIST( FBSDK_DLL, Box );

//! <b>List:</b> Box informations for constraint relation.
class FBSDK_DLL FBPropertyListBox : public FBPropertyListComponentBase
{
public:
	/**	Add a FBBox object to the property list.
	*	\param	pItem	object to add to list.
	*	\return	Number of items in list after operation.
    *   \warning does nothing : call SetAsSource or ConstrainObject on the Relation Constraint.
	*/
	int	 Add( FBBox* pItem );
	/**	Remove FBBox object from property list.
	*	\param	pIndex	Index of object to get.
	*/
	virtual void RemoveAt( int pIndex );
	/**	Get the FBBox object at \e pIndex.
	*	\param	pIndex	Index of object to get.
	*	\return the box at \e pIndex.
	*/
	virtual FBBox* operator[](int pIndex);
	/** Get the number of objects.
	*	\return Number of objects.
	*/
	virtual int  GetCount();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
	inline virtual FBComponent* GetAt(int pIndex) { return (FBComponent*)operator[](pIndex); }
private:
	inline virtual int Add	( FBComponent* pItem ) { return Add((FBBox*)pItem); }
#endif
};

////////////////////////////////////////////////////////////////////////////////////
// FBBoxPlaceHolder
////////////////////////////////////////////////////////////////////////////////////
FB_DEFINE_COMPONENT( FBSDK_DLL, Box );
__FB_FORWARD( FBBoxPlaceHolder );

/** Wrapper around a specific instance of a FBBox object.
*   This class is mainly used with a constraint relation to have multiple boxes
*   that are a representation of the same underlying box. The underlying box will
*   usually be a device.
*   \warning Instantiation of FBBoxPlaceHolder should be left to the the system.
*/
class FBSDK_DLL FBBoxPlaceHolder : public FBBox {
	__FBClassDeclare( FBBoxPlaceHolder, FBBox );
public:
	/** Constructor.
	*	\param	pObject		For internal use only.
	*/
	FBBoxPlaceHolder(HIObject pObject);

    FBPropertyBox Box;      //!< <b>Read Only Property:</b> Underlying box object.
};

////////////////////////////////////////////////////////////////////////////////////
// FBModelPlaceHolder
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBModel );
__FB_FORWARD( FBModelPlaceHolder );

/** Wrapper around a specific instance of a FBModel object.
*   This class is mainly used with a constraint relation to have multiple boxes
*   that are a representation of the same underlying model.
*   \warning Instantiation of FBModelPlaceHolder should be left to the the system.
*/
class FBSDK_DLL FBModelPlaceHolder : public FBBoxPlaceHolder {
	__FBClassDeclare( FBModelPlaceHolder, FBBoxPlaceHolder );
public:
	/** Constructor.
	*	\param	pObject		For internal use only.
	*/
	FBModelPlaceHolder(HIObject pObject);

    FBPropertyModel Model;                  //!< <b>Read Only Property:</b> Underlying model object.
    FBPropertyBool  UseGlobalTransforms;    //!< <b>Read Write Property:</b> Indicate if the translations are expressed in local or global mode.
};

////////////////////////////////////////////////////////////////////////////////////
// FBConstraintRelation
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBConstraintRelation);

/** ConstraintRelation class.
*   This class exposes the relation constraint and allows addition of new boxes
*   and removal of existing ones.
*/
class FBSDK_DLL FBConstraintRelation : public FBConstraint {
	__FBClassDeclare( FBConstraintRelation, FBConstraint );
public:
	/** Constructor.
	*	\param	pName		Name of constraint.
	*	\param	pObject		For internal use only (default is NULL).
	*/
	FBConstraintRelation(const char* pName, HIObject pObject=NULL);

    IObject_Declare(K_IMPLEMENTATION);			// Interface to IObject

    /** Create a sender box.
    *   Use an existing FBBox object to create a sender in the relation.
    *   \param pSource Source box to insert in the constraint.
    *   \return A place holder box for the object.
    */
    FBBox* SetAsSource    ( FBBox* pSource );

    /** Create a receiver box.
    *   Use an existing FBBox object to create a receiver in the relation.
    *   \param pConstrainedObject Destination box to insert in the constraint.
    *   \return A place holder box for the object.
    */
    FBBox* ConstrainObject( FBBox* pConstrainedObject ); // Receiver

    /** Create a function box.
    *   Ask the constraint to create new function box.
    *   \param pGroup Name of the group under which the function is located in the Constraint Relation GUI (case-sensitive!).
    *   \param pName Name of the function, as seen in the GUI (case-sensitive!).
    *   \return The newly created function box, or NULL if the name/group combination was invalid.
    */
    FBBox* CreateFunctionBox( const char* pGroup, const char* pName );

    /** Get a box position in the GUI.
    *   Get the position of a box within the constraint layout view.
    *   \param pBox Box from which the information will be queried.
    *   \param pX   X position.
    *   \param pY   Y position.
    *   \return A boolean value indicating success (True) or failure (False).
    *   \warning Should the function return False, the X and Y values will not be set.
    */
    bool GetBoxPosition( FBBox* pBox, int& pX, int& pY );

    /** Set a box position in the GUI.
    *   Set the position of a box within the constraint layout view.
    *   \param pBox Box which needs to be moved.
    *   \param pX   New X position.
    *   \param pY   New Y position.
    *   \return A boolean value indicating success (True) or failure (False).
    */
    bool SetBoxPosition( FBBox* pBox, int pX, int pY );

    FBPropertyListBox   Boxes;      //!< <b>List:</b> Boxes used in this constraint.
};

////////////////////////////////////////////////////////////////////////////////////
// FBConstraintSolver
////////////////////////////////////////////////////////////////////////////////////
FB_DEFINE_COMPONENT( FBSDK_DLL, ConstraintSolver );

/**	Register the constraint.
*	\param	UniqueNameStr	Unique name.
*	\param	ClassName		Name of the constraint class.
*	\param	Label			Short description of constraint.
*	\param	Description		Long description of constraint.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterConstraintSolver( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
	HIObject RegisterConstraintSolver##ClassName##Create( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName(pName); \
		Class->UniqueName = UniqueNameStr; \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
\
	FBLibraryModule( ClassName ) \
	{	\
		FBRegisterObject( ClassName##R1,"Browsing/Templates/Solvers",Label,Description,RegisterConstraintSolver##ClassName##Create,true, IconFilename ); \
		FBRegisterObject( ClassName##R2,"FbxStorable/Constraint",UniqueNameStr,Description,RegisterConstraintSolver##ClassName##Create,true, IconFilename ); \
	}

/** Constraint class declaration.
*	\param	ClassName	Constraint class name.
*	\param	Parent		Parent class name.
*	\warning The class must inherit directly from FBConstraint.
*/
#define FBConstraintSolverDeclare( ClassName, Parent ) \
	FBClassDeclare( ClassName, Parent ); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/** Constraint class implementation.
*	\param	ThisComponent The name of the class to implement.
*/
#define FBConstraintSolverImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

__FB_FORWARD( FBConstraintSolver );

//! Base class for constraint solver.
class FBSDK_DLL FBConstraintSolver : public FBConstraint {
	__FBClassDeclare( FBConstraintSolver,FBConstraint );
public:

	FBConstraintSolver(const char* pName, HIObject pObject=NULL);

	static bool BackgroundEvaluate( FBModel* pModel, FBComponent* pTrackOrTake, FBTime pTime, FBVector3d& pT, FBVector3d& pR, FBVector3d& pS, FBEvaluateInfo* pEvaluateInfo = NULL, bool pGlobal = true );
	
	/**	Start background evaluation. Needs to be released as soon as possible. 
	*	\param	pSourceEvaluateInfo	Source evaluation. Needs to be valid one.
	*	\param	pEvaluateCandidates	Notify that we want to be able to resolve candidates - this can be called only from main thread (on other threads won't work)
	*	\return Background evaluation info that will work with new ID and in secured buffers.
	*	\note	Example of usage can be found in /OpenRealitySDK/samples/constraints/CharacterSolver/HIK2014Solver
	*/
	FBEvaluateInfo* BackgroundEvaluateInfoBegin(FBEvaluateInfo* pSourceEvaluateInfo, bool pEvaluateCandidates=false);

	/**	Start recursive background evaluation. Needs to be released as soon as possible. 
	*	\param	pSourceEvaluateInfo	Source evaluation. Needs to be valid one.
	*	\param	pForceUpdateLocals	Evaluate local transformation, even if only global was requested
	*	\return Background evaluation info that will work with new ID and in secured buffers.
	*	\note	Example of usage can be found in /OpenRealitySDK/Samples/constraints/CharacterSolver/HIK2014Solver
	*/
    FBEvaluateInfo* BackgroundEvaluateInfoRecursiveBegin(FBEvaluateInfo* pSourceEvaluateInfo, bool pForceUpdateLocals=false);

	//! Release background evaluation info - very important.
	void			BackgroundEvaluateInfoEnd(FBEvaluateInfo* pBackgroundEvaluateInfo);

	/**	Enable evaluation notification
	*	\param	pBackgroundEvaluateInfo	Background evaluation that was started for this object and for which we want to change enable/disable notification callback
	*	\param	pFunction				Callback function, will be called when FBAnimationNode of this constraint is being evaluated. Passing NULL disable notification.
	*	\param	pCustomData				Customer can pass custom data to callback.
	*	\return Confirms that change was made to pBackgroundEvaluateInfo
	*	\note	Example of usage can be found in /OpenRealitySDK/Samples/constraints/CharacterSolver/HIK2014Solver
	*/
	bool			BackgroundEvaluateInfoNotify(FBEvaluateInfo* pBackgroundEvaluateInfo, kBackgroundEvaluationCallback pFunction, void* pCustomData=NULL);

	void MultiThreaded( bool pActive );
	bool IsMultiThreaded();

	FBPropertyInt	SampleRecordingPrecision;			//!< <b>Read Write Property:</b> Sample Recording Precision?
	FBPropertyBool	SyncAnimationPlay;					//!< <b>Read Write Property:</b> Sync animation play speed with solver? (for computation expensive scenes this will cause none Realtime play)

	virtual void LiveChanged();
};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListConstraintSolver
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBPropertyListConstraintSolver );

//! \b PropertyList: Constraint solver
class FBSDK_DLL FBPropertyListConstraintSolver : public FBPropertyListComponent
{
public:
	FBPropertyListConstraintSolver();
    /**	Get the model template at \e pIndex.
	*	\param	pIndex	Index of model template to get.
	*	\return Model template at \e pIndex.
	*/
	FBConstraint* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// FBPhysicalProperties
////////////////////////////////////////////////////////////////////////////////////
FB_DEFINE_COMPONENT( FBSDK_DLL, PhysicalProperties );

/**	Register the constraint.
*	\param	UniqueNameStr	Unique name.
*	\param	ClassName		Name of the constraint class.
*	\param	Label			Short description of constraint.
*	\param	Description		Long description of constraint.
*	\param	IconFilename	Filename of associated icon.
*/
#define FBRegisterPhysicalProperties( UniqueNameStr, ClassName, Label, Description, IconFilename ) \
	HIObject RegisterPhysicalProperties##ClassName##Create( HIObject /*pOwner*/,const char* pName,void * /*pData*/) \
	{ \
	  ClassName *Class = new ClassName(pName); \
		if (Class->FBCreate()) { \
			return Class->GetHIObject(); \
		} else { \
			delete Class; \
			return NULL; \
		} \
	} \
\
	FBLibraryModule( ClassName ) \
	{	\
		FBRegisterObject( ClassName##R1,"Browsing/Templates/Physical Properties",Label,Description,RegisterPhysicalProperties##ClassName##Create,true, IconFilename ); \
		FBRegisterObject( ClassName##R2,"FbxStorable/Physical Properties",UniqueNameStr,Description,RegisterPhysicalProperties##ClassName##Create,true, IconFilename ); \
	}

/** Constraint class declaration.
*	\param	ClassName	Constraint class name.
*	\param	Parent		Parent class name.
*	\warning The class must inherit directly from FBConstraint.
*/
#define FBPhysicalPropertiesDeclare( ClassName, Parent ) \
	FBClassDeclare( ClassName, Parent ); \
  public: \
	ClassName(const char* pName):Parent(pName) { FBClassInit; } \
  private:

/** Constraint class implementation.
*	\param	ThisComponent The name of the class to implement.
*/
#define FBPhysicalPropertiesImplementation( ThisComponent ) \
		FBClassImplementation( ThisComponent )

__FB_FORWARD( FBPhysicalProperties );

/** 
*   Base class for physical properties attach to a model.
*/
class FBSDK_DLL FBPhysicalProperties : public FBBox {
	__FBClassDeclare( FBPhysicalProperties,FBBox );
public:

	FBPhysicalProperties(const char* pName, HIObject pObject=NULL);

};

////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListPhysicalProperties
////////////////////////////////////////////////////////////////////////////////////
FB_DEFINE_LIST( FBSDK_DLL, PhysicalProperties );
FB_FORWARD( FBPropertyListPhysicalProperties );

//! \b PropertyList: Physical properties
class FBSDK_DLL FBPropertyListPhysicalProperties : public FBPropertyListComponent
{
public:
	FBPropertyListPhysicalProperties();
    /**	Get the model template at \e pIndex.
	*	\param	pIndex	Index of model template to get.
	*	\return Model template at \e pIndex.
	*/
	FBPhysicalProperties* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////
// FBConstraintManager
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBConstraintManager );

//! Constraint manager.
class FBSDK_DLL FBConstraintManager : public FBComponent
{
	__FBClassDeclare( FBConstraintManager, FBComponent );
public:
	/** Constructor.
    *   \deprecated This public constructor to be protected in the future. Use TheOne() function instead.
    */
	K_DEPRECATED_2014 FBConstraintManager();

    /**	Get the global FBConstraintManager object
    *	\return	the global object.
    */
    static FBConstraintManager& TheOne();

	/**	Get the name of a registered type of constraint.
	*	This will search in the registry for a constraint at the index \e pTypeIndex.
    *
	*	\param	pTypeIndex	Index of a constraint type.
	*	\return	Name of constraint type.
	*/
	const char*		TypeGetName				( int pTypeIndex ) const;

	/**	Get the number of registered constraint types.
	*	\return Number of registered constraint types.
	*/
	int				TypeGetCount			() const;

	/**	Create a constraint by index.
	*	Given the index in the registry, this function create an instance of this constraint.
    *   The newly created constraint will be automatically added to the scene.
    *
	*	\param	pTypeIndex	Index of constraint type, must in range [0, TypeGetCount() ). 
	*	\return	The newly created constraint, or NULL if pIndex is out of range. 
	*/
	FBConstraint* TypeCreateConstraint( int pTypeIndex );

	/**	Create a constraint by name.
	*	Given the constraint type name in the registry, this function create an instance of this constraint. 
    *   The newly created constraint will be automatically added to the scene.
    *
	*	\param	pName the name of the constraint to be created. 
	*	\return	The newly created constraint, or NULL if pName doesn't match any registered constraints. 
	*/
	FBConstraint* TypeCreateConstraint( const char* pName );
};


#ifdef FBSDKUseNamespace
    }
#endif
#endif
