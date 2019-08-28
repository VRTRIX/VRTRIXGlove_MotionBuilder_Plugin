#ifndef __FBCHARACTEREXTENSION_H__
#define __FBCHARACTEREXTENSION_H__
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

/**	\file fbcharacterextension.h
*	Character extension interface for FBSDK.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbkeyinggroup.h>
#include <fbsdk/fbmodel.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

__FB_FORWARD( FBCharacterExtension );
__FB_FORWARD( FBCharacter );
__FB_FORWARD( FBObjectPose );

 /*! FBPlotAllowed*/
enum FBPlotAllowed
{
	kFBPlotAllowed_None,/*!< kFBPlotAllowed_None. */  
	kFBPlotAllowed_Skeleton,/*!< kFBPlotAllowed_Skeleton */  
	kFBPlotAllowed_ControlRig,/*!< kFBPlotAllowed_ControlRig */  
	kFBPlotAllowed_Both/*!< kFBPlotAllowed_Both */  
};

FB_DEFINE_ENUM		( FBSDK_DLL, PlotAllowed );
FB_DEFINE_COMPONENT( FBSDK_DLL, CharacterExtension );
FB_DEFINE_LIST( FBSDK_DLL, CharacterExtension );
FB_FORWARD(FBPropertyListCharacterExtension);



/** Character extension property list.
*/
class FBSDK_DLL FBPropertyListCharacterExtension : public FBPropertyListComponent
{
  public:
	FBPropertyListCharacterExtension();
	/**	Get the CharacterExtension at \e pIndex.
	*	\param	pIndex	Index of Character to get a handle on.
	*	\return Character at \e pIndex.
	*/
	virtual FBCharacterExtension* operator[]( int pIndex );
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FBGroup
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Objects Grouping class.
*	This class is an interface to manipulate object's grouping in the scene.
*/
class FBSDK_DLL FBCharacterExtension : public FBKeyingGroup
{
	//--- Open Reality declaration.
	__FBClassDeclare(FBCharacterExtension, FBKeyingGroup);
public:




	/**	Constructor.
	*	\param	pName	Group name.
	*	\param	pObject	For internal use only.
	*/
	FBCharacterExtension(const char* pName, HIObject pObject=NULL);

	/** Virtual FBDelete function.
	*/
	virtual void FBDelete();

	FBPropertyBool				IncludePartInFullBody;		//!< <b>Read Write Property:</b> Include or not this extension when fullBody is active.
	FBPropertyString			Label;		                //!< <b>Read Write Property:</b> The logical name of the extension, use for mirroring.
	FBPropertyInt				MirrorLabel;	            //!< <b>Read Write Property:</b> Enum that indicate which extension is used as mirror, 0 is none, 1 is self, 2-n represent the (ith - 2)character extension in the attached character excluding self.
	FBPropertyPlotAllowed		PlotAllowed;	            //!< <b>Read Write Property:</b> Controls if objects in the set are transformable.
    FBPropertyModel             ReferenceModel;             //!< <b>Read Write Property:</b> Controls the referential of the extension.
	
	
	void UpdateStancePose(); //! Update the stance pose to the current position of the character extension element.
	void GoToStancePose(); //! Reset object position to the stance.
    FBObjectPose* GetStancePose(); //! Return stance pose.


	FBCharacterExtension* GetMirrorExtension(); //! return the character extension determined by MirrorLabel
	FBCharacter*      GetCharacter();  //! Return the attached Character 


	void	AddObjectProperties( FBComponent* pObj );		//! Add TR Properties from Object.
	void	RemoveObjectAndProperties( FBComponent* pObj );	//! Remove TR Properties from Object.

	bool	IsElementSelected();  //! return true if one object in object dependency list is selected.
    bool    IsPropertyIncluded( FBProperty* pProp ); //! return true if the property is in character extension.

	void			GetLabelNameWithExtensionObject( FBString& pLabelName, FBComponent* pObj, bool pReturnObjectNameIfNotFound = false );	//! Find the label name that was used to store object pose.
	FBComponent*	GetExtensionObjectWithLabelName( const FBString& pLabelName );	//! Find stored object based on label name.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
