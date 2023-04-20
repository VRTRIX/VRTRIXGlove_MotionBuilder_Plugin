#ifndef __FBPOSE_H__
#define __FBPOSE_H__
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

/** \file fbpose.h
*	Access to poses.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif


FB_DEFINE_COMPONENT( FBSDK_DLL, Pose );

///////////////////////////////////////////////////////////////////////////////////
// FBPose
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBPose );

//! Types of pose.
enum FBPoseType 
{
	kFBBindPose,	//!< Bind pose.
	kFBRestPose,	//!< Rest pose.
};

FB_DEFINE_ENUM( FBSDK_DLL, PoseType );

//! Pose class.
class FBSDK_DLL FBPose : public FBComponent
{
	__FBClassDeclare( FBPose, FBComponent );

public:
	/**	Constructor.
	*	\param	pName		Name of pose.
	*	\param	pObject 	For internal use only (default=NULL).
	*/
	FBPose( const char *pName, HIObject pObject = NULL );
    
    IQuery_Declare(override);

    //! Returns the number of pose nodes stored.
	int GetNodeCount();

	/** Add a new pose node.
	* 	\param pObject			The object for which we are creating the pose information.
	* 	\param pMatrix			The transformation of the object we want to save.
	* 	\param pIsLocalMatrix	Is the matrix a local matrix?
	*/
	int AddNode( FBModel* pObject, FBMatrix* pMatrix = NULL, bool pIsLocalMatrix = false );

	/** Remove the pose node at specified index.
	* 	\param pIndex Index of the node to be removed.
	*/
	void RemoveNode( int pIndex );

	/** Set the pose node object.
	* 	\param pIndex	Index of the node.
	* 	\param pObject	Object to associate with this pose node.
	*/
	void SetNodeObject( int pIndex, FBModel* pObject );

	/** Get the pose node object.
	* 	\param pIndex Index of the node.
	*	\return a pointer to the node's Object.
	* 	\remark if the index is invalid a null pointer is returned.
	*/
	FBModel* GetNodeObject( int pIndex );

	/** Get the pose node at specified index.
	* 	\param pIndex Index of the node.
	* 	\remark if the index is invalid a reference to an empty string is returned.
	* 	\remark The reference will become undefined if this object is destroyed.
	*/
	FBString GetNodeName( int pIndex ) const;

	/** Set the pose node matrix.
	*	\param pIndex	Index of the node.
	*	\param pMatrix	Matrix to set for this pose node.
	*/
	void SetNodeMatrix( int pIndex, FBMatrix* pMatrix );

	/** Get the pose node matrix.
	*	\param pIndex Index of the node.
	*	\return a reference to the node's Matrix.
	*	\remark if the index is invalid a reference to an identiy matrix is returned.
	*	\remark The reference will become undefined if this object is destroyed.
	*/
	FBMatrix GetNodeMatrix( int pIndex ) const;

	/** Get the global pose node matrix.
	*	\param pIndex Index of the node.
	*	\return a reference to the node's Global Matrix.
	*	\remark if the index is invalid a reference to an identiy matrix is returned.
	*	\remark The reference will become undefined if this object is destroyed.
	*/
	FBMatrix GetNodeMatrixGlobal( int pIndex ) const;

	/** Set the type of the Matrix for a given node.
	*	\param pIndex				Index of the node.
	*	\param pIsNodeLocalMatrix	True if the matrix of the node is a local matrix.
	*/
    void SetIsNodeLocalMatrix( int pIndex, bool pIsNodeLocalMatrix );

	/** Get the type of the Matrix for a given node.
	*	\param pIndex Index of the node.
	*	\return true if the matrix is defined in Local coordinate space.
	*	\remark If this object is configured to hold BindPose data, this method will always return false.
	*/
    bool IsNodeLocalMatrix( int pIndex );

	/** Look in this pose if the given node is present.
	*	\param pNodeName Name of the node we are looking for.
	*	\return -1 if the node is not in the list or it's position.
	*/
  	int Find( FBString pNodeName );

	/** Create an image thumbnail for the current pose.
	*/
	void CreatePoseThumbnail();

public:
	FBPropertyPoseType			Type;			//!< <b>Read Only Property:</b> Type of the pose (bind pose or rest pose)
};


////////////////////////////////////////////////////////////////////////////////////
// FBPropertyListPose
////////////////////////////////////////////////////////////////////////////////////
__FB_FORWARD( FBPropertyListPose );

//! <b>List:</b> Model
class FBSDK_DLL FBPropertyListPose : public FBPropertyListComponent
{
public:
	FBPropertyListPose();
	/**	Get the pose at \e pIndex.
	*	\param	pIndex	Index of pose to get.
	*	\return pose at \e pIndex.
	*/
	FBPose* operator[](int pIndex);
};


#ifdef FBSDKUseNamespace
    }
#endif
#endif
