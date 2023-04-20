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
FB_DEFINE_ENUM( FBSDK_DLL, PlotAllowed );

/*! Sync mode for Constraints' Activeness and Models' visibility belonging to the Character Extension. */
enum FBSyncActivationAndVisibilityMode
{
	kFBSyncMode_None,						/*!< No particular sync activity. Default mode. */
	kFBSyncMode_WithContolRig,				/*!< Enable Constraints' Activeness and Models' visibility when the attached character is driven by its control rig, otherwise disable/hide them. */
	kFBSyncMode_WithOthersThanControlRig,	/*!< Enable Constraints' Activeness and Models' visibility when the attached character is driven by something else than its control rig, otherwise disable/hide them. */
};
FB_DEFINE_ENUM( FBSDK_DLL, SyncActivationAndVisibilityMode );

/*!  Character Extension Stance Pose mode when the stance pose is activated on a character. */
enum FBCharacterExtensionStancePoseMode
{
	kFBStancePose_Never,						/*!< Character extension will never go in stance pose. */
	kFBStancePose_Selected,						/*!< Character extension will go in stance pose if it is selected. */
	kFBStancePose_Reference_Selected,			/*!< Character extension will go in stance pose if its reference is selected. */
	kFBStancePose_Self_Or_Reference_Selected,	/*!< Character extension will go in stance pose if it is selected or if its reference is selected. */
	kFBStancePose_Always						/*!< Character extension will always go in stance pose. */
};
FB_DEFINE_ENUM( FBSDK_DLL, CharacterExtensionStancePoseMode );

FB_DEFINE_COMPONENT( FBSDK_DLL, CharacterExtension );
FB_DEFINE_LIST( FBSDK_DLL, CharacterExtension );
FB_FORWARD(FBPropertyListCharacterExtension);

/*! Character extension Retarget Mode */
enum FBCharacterExtensionRetargetMode
{
    kFBRetargetModeOff,/*!< Off. */  
    kFBRetargetModeAuto,/*!< Auto Mapping. */
    kFBRetargetModeManual/*!< Manually Assign. */
};
FB_DEFINE_ENUM( FBSDK_DLL, CharacterExtensionRetargetMode );


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
	virtual void FBDelete() override;

	FBPropertyBool				IncludePartInFullBody;		//!< <b>Read Write Property:</b> Include or not this extension when the Full Body mode is active.
	FBPropertyBool				IncludePartInBodyPart;		//!< <b>Read Write Property:</b> Include or not this extension when the Body Part mode is active.
	FBPropertyString			Label;		                //!< <b>Read Write Property:</b> The logical name of the extension, use for mirroring.
	FBPropertyInt				MirrorLabel;	            //!< <b>Read Write Property:</b> Enum that indicate which extension is used as mirror, 0 is none, 1 is self, 2-n represent the (ith - 2)character extension in the attached character excluding self.
	FBPropertyPlotAllowed		PlotAllowed;	            //!< <b>Read Write Property:</b> Controls if objects in the set are transformable.
    FBPropertyModel             ReferenceModel;             //!< <b>Read Write Property:</b> Controls the referential of the extension.
    FBPropertyCharacterExtensionRetargetMode		RetargetMode;		//!< <b>Read Write Property:</b> Character extension retarget mode.
	FBPropertySyncActivationAndVisibilityMode		SyncActivationAndVisibilityMode;		//!< <b>Read Write Property:</b> The "Sync Activation & Visibility" mode.
	FBPropertyCharacterExtensionStancePoseMode		StancePoseMode;		//!< <b>Read Write Property:</b> Character extension stance pose mode.
	
	
	/** Update the stance pose to the current position of the character extension element.
	*/
	void UpdateStancePose();

	/** Reset object position to the stance.
	*/
    void GoToStancePose();

	/** Return stance pose.
	*	\return stance pose.
	*/
    FBObjectPose* GetStancePose();


	/** Return the character extension determined by MirrorLabel.
	*	\return character extension determined by MirrorLabel.
	*/
	FBCharacterExtension* GetMirrorExtension();

	/** Return the attached Character.
	*	\return attached Character.
	*/
	FBCharacter*      GetCharacter();


	/** Add TR Properties from Object.
	*	\param pObj Object to add TR properties.
	*/
	void	AddObjectProperties( FBComponent* pObj );

	/** Remove TR Properties from Object.
	*	\param pObj Object to remove TR properties.
	*/
	void	RemoveObjectAndProperties( FBComponent* pObj );


	/** Return true if one object in object dependency list is selected.
	*	\return true if one object in object dependency list is selected.
	*/
	bool	IsElementSelected();

	/** Return true if the property is in character extension.
    *	\param pProp Property to check.
	*	\return true if the property is in character extension.
	*/
    bool    IsPropertyIncluded( FBProperty* pProp );


	/** Find the label name that was used to store object pose.
	*	\param pLabelName	                The label name that was used to store object pose.
    *	\param pObj	                        The extension object.
    *	\param pReturnObjectNameIfNotFound	If the value is true, if the object is not found, pLabelName will be set to the object name; otherwise pLabelName will be set to empty string. By default the value is false.
	*/
	void			GetLabelNameWithExtensionObject( FBString& pLabelName, FBComponent* pObj, bool pReturnObjectNameIfNotFound = false );

	/** Find stored object based on label name.
	*	\param pLabelName	The label name.
	*	\return			    The extension object.
	*/
	FBComponent*	GetExtensionObjectWithLabelName( const FBString& pLabelName );


	/** Return the character extension that is used to drive this extension during retargeting.
	*	\return			The character extension that is used to drive this extension during retargeting.
	*/
    FBCharacterExtension* GetSourceExtension();

	/** Set the character extension to drive this extension during retargeting. Only applicable if RetargetMode is Assign.
    *   \remarks Only applicable if RetargetMode is Assign.
	*	\param pSourceExtension	The source extension to drive this extension during retargeting. 
	*/
    void    SetSourceExtension( FBCharacterExtension* pSourceExtension );

	/** Return the enum that indicate which extension is used as a source during retargeting, 0 is none, 1-n represent the (ith - 1)character extension in the source character. 
	*	\return			The enum that indicate which extension is used as a source during retargeting, 0 is none, 1-n represent the (ith - 1)character extension in the source character. 
	*/
    int     GetSourceExtensionIndex();

	/** Set the enum that indicate which extension is used as a source during retargeting, 0 is none, 1-n represent the (ith - 1)character extension in the source character. Only applicable if RetargetMode is Manually Assign.
    *   \remarks Only applicable if RetargetMode is Manually Assign.
	*	\param pSrcExtIndex	Enum that indicate which extension is used as a source during retargeting, 0 is none, 1-n represent the (ith - 1)character extension in the source character.
	*/
    void    SetSourceExtensionIndex( int pSrcExtIndex ); 


	/** Return the total number of retarget properties.
	*	\return			The total number of retarget properties.
	*/
    int         GetRetargetPropertyCount();

	/** Return the reference property of the given index.
	*	\param pPropIndex	Index to query.
	*	\return			    Reference property of the given index.
	*/
    FBProperty* GetRetargetReferenceProperty( int pPropIndex );

	/** Return the source property of the given index (the source property is the property that drives the reference property during retargeting).
	*	\param pPropIndex	Index to query.
	*	\return			    Source property (the property that drives the reference property during retargeting) of the given index.
	*/
    FBProperty* GetRetargetSourceProperty( int pPropIndex ); 

	/** Set the source property for retargeting. Only applicable if RetargetMode is Manually Assign.
    *   \remarks Only applicable if RetargetMode is Manually Assign.
	*	\param pPropIndex	Index to set.
    *	\param pSourceProp	Source property to set.
	*/
    void        SetRetargetSourceProperty( int pPropIndex, FBProperty* pSourceProp );

	/** Remove the source property for retargeting. Only applicable if RetargetMode is Manually Assign.
    *   \remarks Only applicable if RetargetMode is Manually Assign.
    *	\param pPropIndex	Index to remove.
	*/
    void        RemoveRetargetSourceProperty( int pPropIndex );


	/** RetargetAnimation
	*	\param pEvalInfo	Evaluate info.
	*/
	void	    RetargetAnimation( FBEvaluateInfo* pEvalInfo );
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FBSDKUseNamespace
	}
#endif
#endif /* this must be the last line of this file */
