#ifndef __FBNAMESPACE_H__
#define __FBNAMESPACE_H__
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

__FB_FORWARD( FBNamespace );
FB_DEFINE_COMPONENT( FBSDK_DLL, Namespace );

FB_FORWARD( FBPropertyListNamespace );

FB_DEFINE_LIST( FBSDK_DLL, Namespace );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! <b>List:</b> Namespace
class FBSDK_DLL FBPropertyListNamespace : public FBPropertyListComponent
{
public:
	FBPropertyListNamespace();
	/**	Get the Namespace object at \e pIndex.
	*	\param	pIndex	Index of Namespace to get.
	*	\return Namespace at \e pIndex.
	*/
	FBNamespace* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBNamespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Objects Containing class.
*	This class is an interface to manipulate object's containing in the scene.
*/
class FBSDK_DLL FBNamespace : public FBComponent
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBNamespace, FBComponent);

    void Init();

protected:

	/**	Constructor. For Internal use only.
	*	\param	pMultiLevelNamespace	FBNamespace name. This name will be used as namespace itself. 
    *                                   it should follow such pattern "NS1[:NS2[:NS3]]]", where content inside [] is optional.
	*	\param	pObject	                For internal use only.
	*/
	FBNamespace(const char* pMultiLevelNamespace, HIObject pObject);

public:

    /**	Constructor. Create a new direct children namespace object 
	*	\param	pSingleLevelNamespace	FBNamespace name. This name will be used as namespace itself. 
    *                                   this name string shouldn't contain namespace string separator ":". 
	*	\param	pParentNSObj	        the parent namespace object. if NULl means to create top level namespace.
	*/
    FBNamespace(const char* pSingleLevelNamespace, FBNamespace* pParentNSObj);

    /** Get the namespace content objects count (Not Recursive).
    *   return  content objects count inside this namespace (not recursive)
    */
    int         GetContentCount() const;

    /** Get the namespace content object count (Not Recursive).
    *   \param pIndex  content object index to query.
    *   return  content object inside this namespace (not recursive)
    */
    FBComponent* GetContent(int pIndex) const;

	/** Get List of the namespace content.
	*	\param	pContentList	the list of content to return.
	*	\param	pModificationFlags	bitwise combination of kFBConnectionSrcObjectModified,  kFBConnectionDstObjectModified, kFBConnectionSrcPropertyModified, kFBConnectionDstPropertyModified flags. kFBAllContent means all the content.
	*	\param	pRecursive	    \b True only work on the direct children level namespace, otherwise will work on the whole children namespace hierarchy recursively.
    *	\param  pTypeInfo		the typeInfo of the type of interested object, 0 for all the objects. 
    *   \param  pExactTypeMatch if \b True, the derived typeInfo won't be considered (For example, FBCamera won't be considered when passing FBModel::TypeInfo).
	*/
	void GetContentList(FBComponentList& pContentList, FBPlugModificationFlag pModificationFlags = kFBPlugAllContent, bool pRecursive = true, int pTypeInfo = FBPlug::TypeInfo, bool pExactTypeMatch = false);

	FBPropertyListNamespace		    ChildrenNamespaces;			//!< <b>List:</b> Direct Children Namespace Objects.
};

//////////////////////////////////////////////////////////////////////////

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
