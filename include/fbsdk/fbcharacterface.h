#ifndef __FBCHARACTERFACE_H__
#define __FBCHARACTERFACE_H__
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

/** \file fbcharacterface.h
*	Contains definitions for actor faces and character faces <b>In Development</b>.
*	\warning
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbconstraint.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif


////////////////////////////////////////////////////////////////////////////////
// FBActorFace - Representation of an actor face
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBActor );
__FB_FORWARD( FBActorFace );
FB_DEFINE_COMPONENT( FBSDK_DLL, ActorFace );

/**	Used to plot actor face animation.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBActorFace : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBActorFace, FBComponent );
public:
	/** Constructor.
	*	\param	pName		Name of new actor face.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBActorFace(const char* pName, HIObject pObject=NULL);

	/** Plot the animation of the actor face.
	*	\return	True if the operation completed successfully.
	*/
	virtual bool PlotAnimation( );

	IObject_Declare(override);		// Interface to IObject.

    /** Actual Actor Face destructor.
    *   This method is used to delete the actual actor face object represented by an instance of FBActorFace.
    */
    virtual void FBDelete() override;
};


////////////////////////////////////////////////////////////////////////////////////
// FBCharacterFace - Representation of a character
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBCharacterFace );
FB_DEFINE_COMPONENT( FBSDK_DLL, Character );

/**	Animates a character face using an actor as input.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBCharacterFace : public FBConstraint
{
	//--- Open Reality declaration.
	__FBClassDeclare( FBCharacterFace, FBConstraint );
public:
	/** Constructor.
	*	\param	pName		Name of new character.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBCharacterFace(const char* pName, HIObject pObject=NULL);

	IObject_Declare(override);				// Interface to IObject.

	FBPropertyActorFace				InputActorFace;	//!< <b>Read Write Property:</b> The index of the actor used for the input.
	FBPropertyBool					ActiveInput;	//!< <b>Read Write Property:</b> Is the character input active?

	/** Plot the animation of the character face.
	*	\return	True if the operation completed successfully.
	*/
	virtual bool PlotAnimation( );

    /** Actual Character Face destructor.
    *   This method is used to delete the actual character face object represented by an instance of FBCharacterFace.
    */
    virtual void FBDelete() override;

	/** Set the character face back to its rest shape.
	*/
	void GotoRest();

	/** Add a blendshape model group for each input model.
	*	\param pList List of models to create a blendshape model group.
	*	\param pName Unused. Instead, use the ShapeGroupGetName member function to set the name of each added blendshape model group individually.
	*	\return True if the operation completed successfully, false otherwise.
	*/
	bool ShapeGroupAdd( FBModelList* pList, const char* pName = NULL );

	/** Remove a blendshape model group.
	*	\param pShapeGrpId Index of the blendshape group to remove.
	*	\return True if the operation completed successfully.
	*/
	bool ShapeGroupRemove( int pShapeGrpId );

	/** Find a blendshape group by name.
	*	\param pName Name to search for.
	*	\return \b Index of the blendshape group, \b -1 if not found.
	*/
	int ShapeGroupFindByName( const char* pName );

	/** Retrieve the total number of blendshape groups on this character face.
	*	\return Number of blendshape groups on this character face.
	*/
	int ShapeGroupGetCount();

	/** Retrieve the name of a blendshape group.
	*	\param pShapeGrpId Index of the blendshape group to query.
	*	\return Name of the blendshape group.
	*/
	const char* ShapeGroupGetName( int pShapeGrpId );

	/** Set the name of a blendshape group.
	*	\param pShapeGrpId Index of the blendshape group to modify.
	*	\param pName Name to set on the blendshape group.
	*	\return True if the operation completed successfully.
	*/
	bool ShapeGroupSetName( int pShapeGrpId, const char* pName );

	/** Find a shape in a blendshape group by name.
	*	\param pShapeGrpId Index of the blendshape group to search.
	*	\param pName Name to search for.
	*	\return \b Index of the shape, \b -1 if not found.
	*/
	int ShapeFindByName( int pShapeGrpId, const char* pName );

	/** Retrieve the total number of shapes in a blendshape group.
	*	\param pShapeGrpId Index of the blendshape group to query.
	*	\return Number of shapes in the specified blendshape group.
	*/
	int ShapeGetCount( int pShapeGrpId );

	/** Retrieve the name of the shape in a blendshape group.
	*	\param pShapeGrpId Index of the blendshape group to query.
	*	\param pShapeId Index of the shape in the blendshape group to query.
	*	\return Name of the specified shape.
	*/
	const char* ShapeGetName( int pShapeGrpId, int pShapeId );

	/** Set the name of the shape in a blendshape group.
	*	\param pShapeGrpId Index of the blendshape group to query.
	*	\param pShapeId Index of the shape in the blendshape group to set.
	*	\param pName Name to set on the shape.
	*	\return True if the operation completed successfully.
	*/
	bool ShapeSetName( int pShapeGrpId, int pShapeId, const char* pName );

	/** Add a cluster group to the character face.
	*	\param pList List of clusters to add to this group.
	*	\param pName Optional name to assign to this cluster group.
	*	\return \b Index of the new cluster group \b -1 if the operation failed to complete.
	*/
	int ClusterGroupAdd( FBModelList* pList, const char* pName = NULL );

	/** Remove a cluster group from the character face.
	*	\param pClusterGrpId Index of the cluster group to remove.
	*	\return True if the operation completed successfully.
	*/
	bool ClusterGroupRemove( int pClusterGrpId );

	/** Find a cluster group by name.
	*	\param pName Name to search for on the face.
	*	\return \b Index of the matching cluster group. \b -1 if not found.
	*/
	int ClusterGroupFindByName( const char* pName );

	/** Retrieve the total number of cluster groups.
	*	\return Number of cluster groups on the face.
	*/
	int ClusterGroupGetCount();

	/** Retrieve the name of a cluster group
	*	\param pClusterGrpId Index of the cluster group to query.
	*	\return Name of the specified cluster group.
	*/
	const char* ClusterGroupGetName( int pClusterGrpId );

	/** Set the name of a cluster group.
	*	\param pClusterGrpId Index of the cluster group to modify.
	*	\param pName New name for the cluster group.
	*	\return True of the operation completed successfully.
	*/
	bool ClusterGroupSetName( int pClusterGrpId, const char* pName );

	/** Set a cluster group's rest pose to the current pose.
	*	\param pClusterGrpId Index of the cluster group to modify.
	*	\return True if the operation completed succesfully.
	*/
	bool ClusterGroupSnapRest( int pClusterGrpId );

	/** Add a cluster shape to a cluster group.
	*	\param pClusterGrpId Index of the cluster group to modify.
	*	\param pName Optional name to assign to the shape.
	*	\return \b Index of the new shape. \b -1 if the operation failed to complete.
	*/
	int ClusterShapeAdd( int pClusterGrpId, const char* pName = NULL );

	/** Remove a cluster shape from a cluster group.
	*	\param pClusterGrpId Index of the cluster group to modify.
	*	\param pClusterShapeId Index of the shape in the cluster group to remove.
	*	\return True of the operation completed succesfully.
	*/
	bool ClusterShapeRemove( int pClusterGrpId, int pClusterShapeId );

	/** Find a cluster shape in a cluster group by name.
	*	\param pClusterGrpId Index of the cluster group to search.
	*	\param pName Name to search for in the cluster group.
	*	\return \b Index of the matching shape. \b -1 if not found.
	*/
	int ClusterShapeFindByName( int pClusterGrpId, const char* pName );

	/** Retrieve the total number of shapes in a cluster group.
	*	\param pClusterGrpId Index of the cluster group to query.
	*	\return Number of shapes in the specified cluster group.
	*/
	int ClusterShapeGetCount( int pClusterGrpId );

	/** Retrieve the name of a shape in a cluster group.
	*	\param pClusterGrpId Index of the cluster group to query.
	*	\param pClusterShapeId Index of the cluster shape to query.
	*	\return Name of the specified shape.
	*/
	const char* ClusterShapeGetName( int pClusterGrpId, int pClusterShapeId );

	/** Set the name of a shape in a cluster group.
	*	\param pClusterGrpId Index of the cluster group to modify.
	*	\param pClusterShapeId Index of the cluster shape to modify.
	*	\param pName Name to assign to the cluster shape.
	*	\return True if the operation completed successfully.
	*/
	bool ClusterShapeSetName( int pClusterGrpId, int pClusterShapeId, const char* pName );

	/** Record the current pose of the cluster group to a cluster shape.
	*	\param pClusterGrpId Index of the cluster group to record.
	*	\param pClusterShapeId Index of the cluster shape to record the pose.
	*	\return True if the operation completed successfully.
	*/
	bool ClusterShapeSnap( int pClusterGrpId, int pClusterShapeId );

	/** Add an expression to the face.
	*	\param pName Optional name to assign to the new expression.
	*	\return \b Index of the new expression. \b -1 if the operation failed to complete.
	*/
	int ExpressionAdd( const char* pName );

	/** Remove an expression from the face.
	*	\param pExpressionId Index of the expression to remove.
	*	\return True if the operation completed successfully.
	*/
	bool ExpressionRemove( int pExpressionId );

	/** Find an expression on the face by name.
	*	\param pName Name of the expression to search for.
	*	\return \b Index of the matching expression. \b -1 if not found.
	*/
	int ExpressionFindByName( const char* pName );

	/** Retrieve the total number of expressions on the face.
	*	\return Number of expressions on the face.
	*/
	int ExpressionGetCount();

	/** Retrieve the name of an expression.
	*	\param pExpressionId Index of the expression to query.
	*	\return Name of the specified expression.
	*/
	const char* ExpressionGetName( int pExpressionId );

	/** Set the name of an expression.
	*	\param pExpressionId Index of the expression to modify.
	*	\param pName Name to assign to the expression.
	*	\return True if the operation completed successfully.
	*/
	bool ExpressionSetName( int pExpressionId, const char* pName );

	/** Assign the weight of a shape to an expression
	*	\param pExpressionId Index of the expression to modify.
	*	\param pGrpId Index of the blendshape or cluster group containing the shape of interest.
	*	\param pShapeId Index of the blendshape or cluster shape to weight.
	*	\param pValue Weight of the shape to assign to this expression.
	*				  A weight of 0.0 represents 0%, while a weight of 1.5 represents 150%.
	*				  The weight cannot be less than 0.0; if so, the weight will be clamped to 0.0.
	*	\return True if the operation completed successfully.
	*/
	bool ExpressionSetShapeWeight( int pExpressionId, int pGrpId, int pShapeId, float pValue = 0.0f );

	/** Retrieve the weight of a shape to an expression
	*	\param pExpressionId Index of the expression.
	*	\param pGrpId Index of the blendshape or cluster group containing the shape of interest.
	*	\param pShapeId Index of the blendshape or cluster shape.
	*	\return Weight of the desired shape to an expression.
	*			A weight of 0.0 represents 0%, while a weight of 1.0 represents 100%.
	*			Returns 0.0 if the weight cannot be found.
	*/
	double ExpressionGetShapeWeight( int pExpressionId, int pGrpId, int pShapeId );
};



////////////////////////////////////////////////////////////////////////////////////
// Property List: ActorFace
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: Actor face.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBPropertyListActorFace : public FBPropertyListComponent
{
  public:
	FBPropertyListActorFace();
	/**	Get the actor face at \e pIndex.
	*	\param	pIndex	Index of actor face to get a handle on.
	*	\return Actor at \e pIndex.
	*/
	FBActorFace* operator[]( int pIndex );
};


////////////////////////////////////////////////////////////////////////////////////
// Property List: Character face
////////////////////////////////////////////////////////////////////////////////////
/** \b PropertyList: Character face.
*	<b>These classes are under development and may change dramatically 
*	between versions.</b>
*/
class FBSDK_DLL FBPropertyListCharacterFace : public FBPropertyListComponent
{
  public:
    FBPropertyListCharacterFace();
	/**	Get the Character face at \e pIndex.
	*	\param	pIndex	Index of Character face to get a handle on.
	*	\return Character face at \e pIndex.
	*/
	FBCharacterFace* operator[]( int pIndex );
};


#ifdef FBSDKUseNamespace
	}
#endif
#endif /* _FBCHARACTERFACE_H_ */
