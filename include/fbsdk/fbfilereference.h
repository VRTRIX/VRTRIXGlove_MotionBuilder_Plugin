#ifndef __FBFILEREFERENCE_H__
#define __FBFILEREFERENCE_H__
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

/**	\file fbfilereference.h
*	FileReference interface for FBSDK
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <kaydara.h>

#include <fbsdk/fbcomponent.h>
#include <fbsdk/fbnamespace.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBFileReference );
FB_DEFINE_COMPONENT( FBSDK_DLL, FileReference );

FB_FORWARD( FBPropertyListFileReference );

FB_DEFINE_LIST( FBSDK_DLL, FileReference );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! <b>List:</b> FileReference
class FBSDK_DLL FBPropertyListFileReference : public FBPropertyListComponent
{
public:
	FBPropertyListFileReference();
	/**	Get the FileReference object at \e pIndex.
	*	\param	pIndex	Index of FileReference to get.
	*	\return FileReference at \e pIndex.
	*/
	FBFileReference* operator[](int pIndex);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBFileReference
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Objects Containing class.
*	This class is an interface to manipulate object's containing in the scene.
*/
class FBSDK_DLL FBFileReference : public FBNamespace
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBFileReference, FBNamespace);

    void Init();

protected:

    /**	Constructor. For internal use only.
	*	\param	pMultiLevelNamespace	FileReference name. This name will be used as namespace itself. 
    *                                   it should follow such pattern "NS1[:NS2[:NS3]]]", where content inside [] is optional
	*	\param	pObject	                For internal use only.
	*/
	FBFileReference(const char* pMultiLevelNamespace, HIObject pObject);

public:

	/**	Constructor. Create a new direct children FileReference object 
	*	\param	pSingleLevelNamespace	FileReference name. This name will be used as namespace itself. 
    *                                   this name string shouldn't contain namespace string separator ":". 
	*	\param	pParentNSObj	        the parent namespace object. if NULl means to create top level namespace.
	*/
    FBFileReference(const char* pSingleLevelNamespace, FBNamespace* pParentNSObj);

	FBPropertyString				ReferenceFilePath;		//!< <b>Read Write Property: </b> File Reference file path.
	FBPropertyBool					IsLoaded;				//!< <b>Read Write Property: </b> File Reference Load/Unload.
	
    /** Save the current status of the referenced content back to disk.
    *   If pFilePath is ReferenceFilePath, we're saving all the modification back to the original 
    *   referenced file. Otherwise, we will export the referenced file plus modification to another file.
    *   \param pFilePath    File path to export. 
    *   \return             true if successful.
    */
    bool BakeRefEditToFile(const char* pFilePath = NULL);

    /** Revert the modification on the referenced object/property to original state.
    *   \param pPlug                the plug to revert, revert all if NULL.
    *   \param pModificationFlag    the modification type to revert.
    */
    void RevertRefEdit(FBPlug* pPlug = NULL, FBPlugModificationFlag pModificationFlag = kFBAllModifiedMask);

    /** Apply specified reference edits from python script file.
    *   \param pRefEditPyScriptFilePath  Reference edits Python script file path.
    */
    void ApplyRefEditPyScriptFromFile( const char* pRefEditPyScriptFilePath );

    /** Apply specified reference edits from Python script string.
    *   \param pRefEditPyScript  Reference edits Python script.
    */
    void ApplyRefEditPyScriptFromString( const char* pRefEditPyScript );

    /** Duplicate/Clone the FileRef object and its referenced content (with/without refEdit).
    *   \param pDstNameSpaceList    the list of target new namespace(s) for duplication. These new namespace(s) must be residing in editable scene segments.
    *   \param pWithRefEdit         false by default,  duplication won't include the existing ref edit. otherwise  ref edit will be applied on the instantiated FileRef in someway.
    *   \return                     true if successful, false is fail.
    */
    bool DuplicateFileRef(const FBStringList& pDstNameSpaceList, bool pWithRefEdit = false);

    /** Return the RefEdit for given RefFile Path.
    *   \param  pFilePath   The Ref File Path to query against, default to be current Ref File.
    *   \return             RefEdit as string   
    */
    const char* GetRefEdit(const char* pFilePath = NULL);

    /** Clear the cached RefEdit for the given ref file path.
    *   \param  pFilePath   The Ref File Path to query against, default to be current Ref File.
    *   \return             \b True if the RefEdit for the given Ref File Path is cached and cleared properly.
    */
    bool ClearRefEdit(const char* pFilePath);

    /** Clear all cached Ref edit.
    *   \return             \b True if the RefEdits are cleared properly.
    */
    bool ClearAllRefEdit();

    /** Swap the Ref File Path and apply ref edit.
    *   \param  pFilePath               The new Ref File path to be used
    *   \param  pApplyAvailableRefEdit  Apply the cached Ref Edit (if exist) for the Ref File to be used if \b True.
    *   \param  pMergeCurrentRefEdit    Merge the current RefEdit to if \b True if the reference items' name are matching. 
    *   \return                         \b True if swap successfully. 
    */
    bool SwapReferenceFilePath(const char* pFilePath, bool pApplyAvailableRefEdit = true, bool pMergeCurrentRefEdit = true);

    /** Return a list of ref file path which has cached Ref Edit.
    *   \param pRefFileList             the output parameter to collect the Ref File Path.
    */
    void GetRefFileList(FBStringList& pRefFileList) const;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FBSDKUseNamespace
	}
#endif


#endif /* this must be the last line of this file */
