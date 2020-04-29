#ifndef __FBMOTIONFILEOPTIONS_H__
#define __FBMOTIONFILEOPTIONS_H__
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

__FB_FORWARD( FBMotionFileOptions );

//! Different model selection available.
enum FBModelSelection {	
	kFBNone,							//!< No selection mode specified.	
	kFBCreateModels,					//!< Will create the models in the motion file, used when there is no model to match in the scene.	
	kFBSelectedModels,					//!< Will Merges data with only the selected nodes or models.
	kFBSelectedModelAndChildren,		//!< Will try to match the models from the file to those selected in the scene, as well as the children of the selected models.
	kFBPrefixGroupContainingModel,		//!< Will finds the top node with the same prefix and imports the motion as if you selected kFBInHierarchy. If the selected node has the prefix, this merge option is the same as selecting kFBSelectedModelAndChildren. If no nodes are found with the prefix, this merge option operates the same as kFBSelectedModels. Only available when one model is selected.
	kFBInHierarchy,						//!< Will find the root node and will try to merge the data on the hierarchy, only useful if one model is selected.
	kFBAllModels,						//!< Will imports motion into the hierarchies of all models in your scene. This is the only merge option when nothing is selected.
};

FB_DEFINE_ENUM( FBSDK_DLL, ModelSelection ); // FBPropertyModelSelection 

//! Customize motion file loading.
class FBSDK_DLL FBMotionFileOptions : public FBComponent {
	__FBClassDeclare( FBMotionFileOptions, FBComponent );
public:
	/**	Constructor.
    * Create a FBMotionFileOptions to be used when importing a motion file. Pass file paths to get the appropriate information about those files, modify the options and then call the file import process.
    * Not all options are usable at the same time, some of them are for specific motion type. You can see the valid configuration by looking at the motion file dialog (accessible from File/Motion File Import...).
	*	\param	pObject	For internal use only.
    *   \param  pStringList The client needs to pass a list of files path to load to collect the motion file information.
	*/
	FBMotionFileOptions(FBStringList* pStringList, HIObject pObject=NULL);

	FBPropertyBool CreateInsteadOfMerge; //!< <b>Read Write Property:</b> If set to true, the motion will imported/models will be created in the scene, if set to false, the motion will be merged.

	//! Common settings when merging, unused with the CreateInsteadOfMerge property is set to true.
	FBPropertyModelSelection ModelSelection; //!< <b>Read Write Property:</b> Indicates if we create the models or how we try to match the models from the motion file to those in the scene.

	FBPropertyBool IgnoreModelType;			//!< <b>Read Write Property:</b> If set to true, model type will not be considered when finding a matching model in the scene.
	FBPropertyBool CreateUnmatchedModels;	//!< <b>Read Write Property:</b> If set to true, nodes will be created to match the hierarchical structure of the imported file.
	FBPropertyBool ImportScaling;			//!< <b>Read Write Property:</b> If set to true, scaling values will be imported.
	FBPropertyBool ImportDOF;				//!< <b>Read Write Property:</b> If set to true, the DOF value will be imported from the file.

	FBPropertyTakeSpanOnLoad TakeStartEnd;	//!< <b>Read Write Property:</b> Indicates how the start/end value of the take will be modified.

	//! Settings based on file type
	FBPropertyBool CreateReferenceNode;				//!< <b>Read Write Property:</b> If set to true, a reference node will be created. Used for asf/amc, bvh, htr files.
	FBPropertyBool KeepDummyNode;					//!< <b>Read Write Property:</b> If set to true, dummy bones from the file are not removed. Used for asf/amc files.
	FBPropertyBool SetLimits;						//!< <b>Read Write Property:</b> If set to true, use motion limits. Used for asf/amc files.
	FBPropertyBool BaseTranslationOnRotationOffset; //!< <b>Read Write Property:</b> If set to true, the base translation will be imported as Rotation Pivot offset. Used for htr, asf/amc
	FBPropertyBool BaseRotationOnPreRotation;		//!< <b>Read Write Property:</b> If set to true, the base rotation will be imported as Pre Rotation. Used for htr, asf/amc files.
	FBPropertyBool CreateOpticalSegments;			//!< <b>Read Write Property:</b> If set to true, optical segments will be created. Used for trc, c3d files.
	FBPropertyBool CreateUnusedOpticalSegments;		//!< <b>Read Write Property:</b> If set to true, unused optical segments will be created. Used for trc, c3d files.
	FBPropertyBool SetOccludedToLastValidPosition;	//!< <b>Read Write Property:</b> If set to true, occluded segments will be set to their last valid position. Used for trc, c3d files.
	FBPropertyBool KeepActorPrefix;					//!< <b>Read Write Property:</b> If set to true, the Actor prefix will be kept when naming each optical marker. Used with c3d files.

    /**	Return the take count in the file to be loaded.
    *   \warning You need to use an appropriate constructor with the file path to be able to get the take information.
    *   \return Take count
    */
    int GetTakeCount() const;                  
    
    /** Return true if the take will be loaded
    *   \param  pTakeIndex Index of take.
    *   \return True is the take will be loaded
    */
    bool GetTakeSelect(int pTakeIndex) const;

    /** Indicate if the take will be loaded
    *   \param  pTakeIndex Index of take to set.
    *   \param  pSelect Set to true if the take should be loaded.
    */
    void SetTakeSelect(int pTakeIndex, bool pSelect);

    /** Get the take name
    *   \param  pTakeIndex Index of take to get the name.
    *   \return Take name
    */
     const char* GetTakeName(int pTakeIndex) const;

    /** Set the take name
    *   \param  pTakeIndex Index of take to set.
    *   \param  pName Take name to set
    */
    void SetTakeName(int pTakeIndex, const char* pName);

    /** Return the Take Start time
    *   \param  pTakeIndex Index of take to get the start time.
    *   \return Start time of the take
    */
    FBTime GetTakeStart(int pTakeIndex);

    /** Set the Take Start time
    *   \param  pTakeIndex Index of take to set.
    *   \param  pStartTime Time of the first frame of the take
    *	\remark	Changing the start time of the take will also change the stop time, since the duration is constant. Please change the samples count to change the length of the motion.
   */
    void SetTakeStart(int pTakeIndex, FBTime pStartTime);

    /** Return the Take Stop time
    *   \param  pTakeIndex Index of take to get the stop time.
    *   \return Stop time of the take
    */
    FBTime GetTakeStop(int pTakeIndex);

    /** Set the Take Stop time
    *   \param  pTakeIndex Index of take to set.
    *   \param  pStopTime Time of the last frame of the take
	*	\remark	Changing the stop time of the take will also change the start time, since the duration is constant. Please change the samples count to change the length of the motion.
   */
    void SetTakeStop(int pTakeIndex, FBTime pStopTime);

    /** Return the number of samples
    *   \param  pTakeIndex Index of take to get the samples count.
    *   \return Number of samples
   */
    int GetTakeSamples(int pTakeIndex);

    /** Set the number of samples for a particular take
    *   \param  pTakeIndex Index of take to set.
    *   \param  pSamplesCount Number of samples
	*	\remark	Must be set to a value bigger than 0 and smaller than the number of samples in the file. The stop time of the motion will be changed based on the new samples count.
   */
    void SetTakeSamples(int pTakeIndex, int pSamplesCount);

    /** Return the sampling rate mode
    *   \param  pTakeIndex Index of take to get the sampling rate mode
    *   \return Sample rate mode
	*	\remark	Use GetTakeSamplingRate if you have a custom sampling rate to get the actual rate.
   */
    FBTimeMode GetTakeSamplingRateMode(int pTakeIndex);

    /** Return the actual sampling rate as a double, useful when you have a custom sampling rate
    *   \param  pTakeIndex Index of take to get the sampling rate
    *   \return Sample rate
   */
    double GetTakeSamplingRate(int pTakeIndex);

    /** Set the sampling rate for a particular take
    *   \param  pTakeIndex Index of take to set.
    *   \param  pTimeMode Time mode to set.
    *   \param  pCustomSamplingRate Custom sampling rate if pTimeMode is set to kFBTimeModeCustom, unused otherwise (default is 30.0)
	*	\remark	Changing the sampling rate will change the stop time of the motion.
   */
    void SetTakeSamplingRate(int pTakeIndex, FBTimeMode pTimeMode, double pCustomSamplingRate=30.0);
};

#ifdef FBSDKUseNamespace
	}
#endif

#endif
