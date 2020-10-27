#ifndef __FBFBXOPTIONS_H__
#define __FBFBXOPTIONS_H__
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

/**	\file fbfbx.h
*	FBX file format interface.
*	This file contains the necessary data structures and classes to
*	interface with the FBX file format, allowing the user to save device
*	settings, tool preferences and other customizable features in a
*	scene.
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


//! \enum FBElementAction
/** Enumeration that describe the different actions available on a scene element
*   depending on the current context.
*/
enum FBElementAction { 
    kFBElementActionSave   ,       //!< Save the element (when saving).
    kFBElementActionAppend ,       //!< Append the elements to the current scene elements (when loading or merging).
    kFBElementActionMerge  ,       //!< Merge the elements from the file in the current scene (when merging).
    kFBElementActionDiscard,       //!< Do not consider the element (when loading, merging and saving).
};
FB_DEFINE_ENUM( FBSDK_DLL, ElementAction ); // FBPropertyElementAction

/** This enumeration indicate the how to set the take start and end points on after a load.
*/
enum FBTakeSpanOnLoad { 
    kFBLeaveAsIs     , //!< Use the current take's start and end point as defined before the load.
    kFBImportFromFile, //!< Set the current take's span according what is set in the loaded file.
    kFBFrameAnimation, //!< Have the take's span match the first and last key in the take.
};
FB_DEFINE_ENUM( FBSDK_DLL, TakeSpanOnLoad ); // FBPropertyTakeSpanOnLoad

/** This enumeration is used to choose how to load an animation file on a character.
*/
enum FBCharacterLoadAnimationMethod { 
    kFBCharacterLoadConnect       , //!< Only connect the loaded character as an input.
    kFBCharacterLoadCopy          , //!< Copy keys from loaded character to target character.
    kFBCharacterLoadRetarget      , //!< Retarget (copy and correct) keys from loaded character to target character.
    kFBCharacterLoadPlotIfSampled , //!< If loaded animation seems sampled, plot animation from loaded character to target character; else retarget.
    kFBCharacterLoadPlot            //!< Plot animation from loaded character to target character.
};
FB_DEFINE_ENUM(FBSDK_DLL, CharacterLoadAnimationMethod);

enum FBFileFormatAndVersion
{
    kFBFBX2010,                             //!< It's FBX Version 6. Note: it's not equivalent to MotionBuilder 2010 Native FBX format.
    kFBFBX2011,                             //!< FBX Version 2011. 
    kFBFBX2012,                             //!< FBX Version 2012. 
    kFBFBX2013,                             //!< FBX Version 2013. 
    kFBFBX2014_2015,                        //!< FBX Version 2014/2015. 
    kFBFBX2016,                             //!< FBX Version 2016. 
	kFBFBX2018,                             //!< FBX Version 2018. 
	kFBFBX2019,                             //!< FBX Version 2019. 
	kFBFBX2020,                             //!< FBX Version 2020.     
	kFBDefaultFormatAndVersion = kFBFBX2020 //!< Default Format and Version
};
FB_DEFINE_ENUM(FBSDK_DLL, FileFormatAndVersion);

//! \enum FBOptionsContext
/** Enumeration that describe the different context available when serializing options to a string
*/
enum FBOptionsContext { 
    kFBOptionsContextSave ,			//!< Serialize options within a save context.
    kFBOptionsContextSaveSelection ,//!< Serialize options within a save selection context.
    kFBOptionsContextLoad ,			//!< Serialize options within a load context.
    kFBOptionsContextMultiLoad ,	//!< Serialize options within a multi-load context.
    kFBOptionsContextMerge,			//!< Serialize options within a merge context.
};

__FB_FORWARD( FBFbxOptions );

//! Customize file loading and saving.
class FBSDK_DLL FBFbxOptions : public FBComponent {
	__FBClassDeclare( FBFbxOptions, FBComponent );
public:
	/**	Constructor.
    * Create a FBFbxOption to be used in FBApplication Save/Load with default settings. 
    *   \param  pLoad If true, will init option for a default Load (Append all elements and animation). If false will initialized options for a default Save (Save all elements and animation).        
    *   \param  pFilePathToLoad If pLoad is true, the client code should pass the file path to load to collect the take info; ignore when pLoad is false.
	*	\param	pObject	For internal use only.
	*/

	FBFbxOptions( bool pLoad, const char * pFilePathToLoad = NULL, HIObject pObject = NULL);

    /**	Set All Options.
    * Initialize all loading/saving properties to ElementAction and animation specified.
    *   \param  pElementAction Default value for all FBPropertyElementAction properties.
    *   \param  pAnimation Default value for all Animation properties.
    */
    void SetAll( FBElementAction pElementAction, bool pAnimation );

     /** Serialize all options to a string
    * Serialize all options to a string specifying a context
	*   \param  pString The string containing all settings, target of serializing
    *   \param  context The context to be used when serializing
    */
    void SaveToString(FBString& pString, FBOptionsContext context );

    /**	Set all options from string
    * Set all parameters from a formatted string (previously serialized with SaveToString)
    *   \param  pString The string containing all settings. See SaveToFile
	*   \param  context The context to be used when de-serializing
    */
    void SetFromString( const char* pString, FBOptionsContext context );

    /** @name Load/Save options.
    *   \warning These options are not present in the history file. Thus will not be affected by 'SetOptionsFromHistory()' and 'SetHistoryFromOptions()'.
    */
    //@{    
	FBPropertyBool  UpdateRecentFiles;     //!< <b>Read Write Property:</b> Set to true to update recent file list.

    /** @name Load specific options.
    *   \warning These options are not present in the history file. Thus will not be affected by 'SetOptionsFromHistory()' and 'SetHistoryFromOptions()'.
    */
    //@{    
    FBPropertyTakeSpanOnLoad    TakeSpan;               //!< <b>Read Write Property:</b> Indicate how the take start and end point should be set. By default it is read from the file.
    //@}


    /** @name Save specific options.
    *   All of these options are false by default, except for 'EmbedMedia' which is true by default.
    *   \warning These options are not present in the history file. Thus will not be affected by 'SetOptionsFromHistory()' and 'SetHistoryFromOptions()'.
    */
    //@{
    FBPropertyFileFormatAndVersion FileFormatAndVersion;//!< <b>Read Write Property:</b> File format and version chosen to save the scene.
    FBPropertyBool              EmbedMedia;             //!< <b>Read Write Property:</b> Embed all media in the FBX file itself. When saving in ASCII mode it is not possible to embed media.
    FBPropertyBool				SaveSelectedModelsOnly; //!< <b>Read Write Property:</b> Indicate that only the selected models will be saved.
    FBPropertyBool				KeepTransformHierarchy; //!< <b>Read Write Property:</b> Indicate whether we keep transform hierarchy when SaveSelectedModelsOnly is true. Default value is false to ensure consistent behavior with SaveSelected operation via file menu.
    FBPropertyBool              UseASCIIFormat;         //!< <b>Read Write Property:</b> Indicate if the resulting FBX file will be in binary or ASCII mode.
	FBPropertyInt               CacheSize;              //!< <b>Read Write Property:</b> The Cached buffer size used to accelerate IO system.
    FBPropertyBool				CompressArray;			//!< <b>Read Write Property:</b> Indicate if the perform compression on the arrays values.
	FBPropertyInt				CompressMinSize;		//!< <b>Read Write Property:</b> Indicate if the minimum item size for compressing arrays.
	FBPropertyInt				CompressLevel;			//!< <b>Read Write Property:</b> The allowed level range for Compression is [0-9] where 0 equals no compression and 9 is as-much-as-we-can.
    //@}


    /** @name Scene settings options.
    */
    //@{
    FBPropertyBool				BaseCameras;            //!< <b>Read Write Property:</b> Consider base camera settings.
    FBPropertyBool				CameraSwitcherSettings; //!< <b>Read Write Property:</b> Consider camera switcher settings.
    FBPropertyBool              CurrentCameraSettings;  //!< <b>Read Write Property:</b> Consider current camera settings.
    FBPropertyBool				GlobalLightingSettings; //!< <b>Read Write Property:</b> Consider global Lighting settings.
    FBPropertyBool				TransportSettings;      //!< <b>Read Write Property:</b> Consider transport control settings.
    //@}

    /** @name Scene segmentation options
    */
    //@{
	FBPropertyBool				FileReference;			//!< <b>Read Write property:</b> Load/Save scene as FileReference.
    FBPropertyBool              FileReferenceEdit;      //!< <b>Read Write Property:</b> Load/Save the edits made to referenced objects or not.
    FBPropertyString            NamespaceList;		    //!< <b>Read Write Property:</b> A list of namespaces separated by '~'. On Load, duplicate the loaded objects into each namespace in the list. If the SetMultiLoadNamespaceList method is also called, this property is ignored.
    //@}

    /** @name Layer merge options
    */
    //@{
	FBPropertyBool				RemoveEmptyLayer;			//!< <b>Read Write property:</b> Remove empty animation layers that are in additive mode, without child or parent.
	FBPropertyBool				ConsiderMuteSolo;			//!< <b>Read Write property:</b> Consider the mute/solo settings to identify identical layer when merging.
    //@}

    /** @name Element settings options.
    */
    //@{
    FBPropertyElementAction     Actors;               //!< <b>Read Write Property:</b> Handling of the Actors elements.
    FBPropertyElementAction     ActorFaces;           //!< <b>Read Write Property:</b> Handling of the Actor Faces elements.
    FBPropertyElementAction     Audio;                //!< <b>Read Write Property:</b> Handling of the Audio elements.
    FBPropertyElementAction     Bones;                //!< <b>Read Write Property:</b> Handling of the Bones elements.
    FBPropertyElementAction     Cameras;              //!< <b>Read Write Property:</b> Handling of the Cameras elements.
    FBPropertyElementAction     Characters;           //!< <b>Read Write Property:</b> Handling of the Characters elements.
    FBPropertyElementAction     CharacterFaces;       //!< <b>Read Write Property:</b> Handling of the Character Faces elements.
    FBPropertyElementAction     CharacterExtensions;  //!< <b>Read Write Property:</b> Handling of the Character Extensions.
    FBPropertyElementAction     Constraints;          //!< <b>Read Write Property:</b> Handling of the Constraints elements.
    FBPropertyElementAction     Devices;              //!< <b>Read Write Property:</b> Handling of the Devices elements.
    FBPropertyElementAction     FileReferences;       //!< <b>Read Write Property:</b> Handling of the FileReferences elements.
    FBPropertyElementAction     Groups;               //!< <b>Read Write Property:</b> Handling of the Groups elements.
    FBPropertyElementAction     KeyingGroups;		  //!< <b>Read Write Property:</b> Handling of the Keying Groups elements.
    FBPropertyElementAction     Lights;               //!< <b>Read Write Property:</b> Handling of the Lights elements.
    FBPropertyElementAction     Materials;            //!< <b>Read Write Property:</b> Handling of the Materials elements.
    FBPropertyElementAction     Models;               //!< <b>Read Write Property:</b> Handling of the Models elements.
    FBPropertyElementAction     Notes;                //!< <b>Read Write Property:</b> Handling of the Notes elements.
    FBPropertyElementAction     OpticalData;          //!< <b>Read Write Property:</b> Handling of the Optical Data elements.
    FBPropertyElementAction     PhysicalProperties;   //!< <b>Read Write Property:</b> Handling of the Physical Properties elements.
    FBPropertyElementAction     Poses;                //!< <b>Read Write Property:</b> Handling of the Poses elements.
    FBPropertyElementAction     Scripts;              //!< <b>Read Write Property:</b> Handling of the Scripts elements.
    FBPropertyElementAction     Sets;                 //!< <b>Read Write Property:</b> Handling of the Sets elements.
    FBPropertyElementAction     Shaders;              //!< <b>Read Write Property:</b> Handling of the Shaders elements.
    FBPropertyElementAction     Solvers;              //!< <b>Read Write Property:</b> Handling of the Solvers elements.
    FBPropertyElementAction     Story;                //!< <b>Read Write Property:</b> Handling of the Story elements.
    FBPropertyElementAction     Textures;             //!< <b>Read Write Property:</b> Handling of the Textures elements.
    FBPropertyElementAction     Video;                //!< <b>Read Write Property:</b> Handling of the Video elements.
    //@}


    /** @name Element animation settings options.
    *   Not all elements type have animation associated with them.
    */
    //@{
    FBPropertyBool   ActorFacesAnimation;        //!< <b>Read Write Property:</b> Handling of the Actor Faces animation.
    FBPropertyBool   BonesAnimation;             //!< <b>Read Write Property:</b> Handling of the Bones animation.
    FBPropertyBool   CamerasAnimation;           //!< <b>Read Write Property:</b> Handling of the Cameras animation.
    FBPropertyBool   CharactersAnimation;        //!< <b>Read Write Property:</b> Handling of the Characters animation.
    FBPropertyBool   CharacterFacesAnimation;    //!< <b>Read Write Property:</b> Handling of the Character Faces animation.
    FBPropertyBool   ConstraintsAnimation;       //!< <b>Read Write Property:</b> Handling of the Constraints animation.
    FBPropertyBool   DevicesAnimation;           //!< <b>Read Write Property:</b> Handling of the Devices animation.
    FBPropertyBool   LightsAnimation;            //!< <b>Read Write Property:</b> Handling of the Lights animation.
    FBPropertyBool   MaterialsAnimation;         //!< <b>Read Write Property:</b> Handling of the Materials animation.
    FBPropertyBool   ModelsAnimation;            //!< <b>Read Write Property:</b> Handling of the Models animation.
    FBPropertyBool   NotesAnimation;             //!< <b>Read Write Property:</b> Handling of the Notes animation.
    FBPropertyBool   PhysicalPropertiesAnimation;   //!< <b>Read Write Property:</b> Handling of the Physical Properties animation.
    FBPropertyBool   ShadersAnimation;           //!< <b>Read Write Property:</b> Handling of the Shaders animation.
    FBPropertyBool   SolversAnimation;           //!< <b>Read Write Property:</b> Handling of the Solvers animation.
    FBPropertyBool   StoryAnimation;             //!< <b>Read Write Property:</b> Handling of the Story animation (animatable properties on story objects).
    FBPropertyBool   TexturesAnimation;          //!< <b>Read Write Property:</b> Handling of the Textures animation.
    //@}    

    /** @name Save Character & Animation settings options.
    */
    //@{
    FBPropertyBool  SaveCharacter;                  //!< <b>Read Write Property:</b> Set to true if the character should be saved when call FBApplication::SaveCharacterRigAndAnimation.
    FBPropertyBool  SaveControlSet;                 //!< <b>Read Write Property:</b> Set to true if the rig (and its children) should be saved  when call FBApplication::SaveCharacterRigAndAnimation.
    FBPropertyBool  SaveCharacterExtensions;        //!< <b>Read Write Property:</b> Set to true if the character extensions (and their children) should be saved  when call FBApplication::SaveCharacterRigAndAnimation.
    FBPropertyBool  ClearSelectionBeforeSave;                //!< <b>Read Write Property:</b> Set to true if the current selected objects shouldn't saved when call FBApplication::SaveCharacterRigAndAnimation.
    //@}  



    /** @name Load Character & Animation settings options.
    */
    //@{
    FBPropertyCharacterLoadAnimationMethod  TransferMethod;                 //!< <b>Read Write Property:</b> How should the animation should be transfered on the target rig.
    FBPropertyBool  ProcessAnimationOnExtension;    //!< <b>Read Write Property:</b> Set to true if animation on character extensions should also be transferred.
    FBPropertyBool  ReplaceControlSet;              //!< <b>Read Write Property:</b> Set to true if the character extensions (and their children) should be saved  when call FBApplication::SaveCharacterRigAndAnimation.
    FBPropertyBool  ResetDOF;                       //!< <b>Read Write Property:</b> Set to true if we should change the limits on the target rig.    
    FBPropertyBool  ResetHierarchy;                 //!< <b>Read Write Property:</b> Set to true if we should reset the character hierarchy.
    FBPropertyBool  RemoveConstraintReference;      //!< <b>Read Write Property:</b> Set to true if we should remove constraint reference.
    FBPropertyBool  CopyCharacterExtensions;        //!< <b>Read Write Property:</b> pCopyMissingExtensions  Set to true if the character extensions on the rig in the file should be copied to the target rig.
    FBPropertyBool  RetargetOnBaseLayer;            //!< <b>Read Write Property:</b> If the transfer method is retarget, set this parameter to control where the retarget correction will be made (on base layer or on another layer).
    FBPropertyBool  IgnoreConflicts;                //!< <b>Read Write Property:</b> Set to true to ignore conflicts between objects in character extensions and objects in the scene. Conflicting objects will be merged in the extension
    //@}  

    /** @name Dialog UI options.
    */
    //@{
    FBPropertyBool  ShowFileDialog;                  //!< <b>Read Write Property:</b> Set to true if want to pop up dialog for FileName, Format, Embed, Compression, UseTakeName, OneTakePerFile.
    FBPropertyBool  ShowOptionsDialog;               //!< <b>Read Write Property:</b> Set to true if want to pop up options dialog for detail settings.
    FBPropertyBool  SetPropertyStaticIfPossible;     //!< <b>Read Write Property:</b> Set to false if want to keep properties' animated flag even when they are not really animated(no keyframe data) while retrieving/storing. 
    //@}  

    /** @name Setup take Info to loaded or saved.
    *   You need to use the appropriate constructor to fill up those take info before call these functions.
    */
    //@{

    /**	Return the count of takes in the scene to saved or the file to loaded.
    *   \warning You need to use appropriate constructor to be able to take infos.
    */
    int GetTakeCount() const;                  
    
    /** Return if true if the take will be saved or Loaded
    *   \param  pTakeIndex index of take to get.
    */
    bool GetTakeSelect(int pTakeIndex) const;

    /** Return if true if the take will be saved or Loaded
    *   \param  pTakeIndex index of take to set
    *   \param  pSelect set true if should be saved or loaded.
    */
    void SetTakeSelect(int pTakeIndex, bool pSelect);

    /** Take Original Name
    *   \param  pTakeIndex index of take to get.
    */
     const char* GetTakeName(int pTakeIndex) const;

    /** Take Original Name
    *   \param  pTakeIndex index of take to set.
    *   \param  pName take name to set
    */
    void SetTakeName(int pTakeIndex,  const char* pName);

    /** Take Description
    *   \param  pTakeIndex index of take to get.
    */
    const char* GetTakeDescription(int pTakeIndex) const;

    /** Take Description
    *   \param  pTakeIndex index of take to set.
    *   \param  pDescription take description to set
    */
    void SetTakeDescription(int pTakeIndex,  const char* pDescription);

    /** Take Destination Name upon save or load
    *   \param  pTakeIndex index of take to get.
    */
     const char* GetTakeDestinationName(int pTakeIndex) const;

    /** Take Destination Name upon save or load
    *   \param  pTakeIndex index of take to set.
    *   \param  pDestinationName take description to set
    */
    void SetTakeDestinationName(int pTakeIndex,  const char* pDestinationName);
    //@}

    /** Get take key range
    *   \param  pTakeIndex index of take to get.
    *   \return A time range, keys inside that time range will be kept. Keys outside that time range will be removed when importing the animation, by default the time range is FBTime::MinusInfinity -> FBTime::Infinity
	*	\remark Valid only on load/merge, not when saving a file.
    */
	FBTimeSpan GetTakeKeyRange(int pTakeIndex);
    //@}

    /** Set take key range
    *   \param  pTakeIndex index of take to set.
    *   \param  pKeyTimeSpan Timespan indicating the time range to keep the keys. Keys that are outside the time range for this take will be removed, by default the time range is FBTime::MinusInfinity -> FBTime::Infinity
	*	\remark Valid only on load/merge, not when saving a file.
    */
	void SetTakeKeyRange(int pTakeIndex,  FBTimeSpan pKeyTimeSpan);
    //@}

    /** SetNamespaceList upon save or load
	*	On Load, if the SetMultiLoadNamespaceList method is also called, the NamespaceList property is ignored.
    *   \param  pNamespaceList  namespace list to set
    */
    void SetNamespaceList(const FBStringList& pNamespaceList);

    /** GetNamespaceList upon save or load
    *   \return  namespace list
    */
    FBStringList GetNamespaceList();

	
	/** Sets the list of objects that will be saved. This needs to be set before 
	*	calling FBApplication::FileSave.
	*	The list is affecting only one save operation. Once the save is completed, the list is cleared.
    *   \param  pObjectsToSave	The objects to save.
	*/
	void SetObjectsToSave( FBArrayTemplate<FBComponent *> *pObjectsToSave );

	/** Sets the list of namespaces that will be used when merging multiple scenes (see FBApplication::FileMerge).
	The number of namespaces contained in this list must match the number of files merged, otherwise the merge operation will abort.
	The first namespace in the list will be applied on the first merged scene,
	the second namespace in the list will be applied on the second merged scene, and so one and so forth.
	This list is affecting only the merge operation.
	When merging multiple scenes, if this list of namespaces is set, the FBFbxOptions::NamespaceList property value is ignored.
	\param  pMultiLoadNamespaceList The multi load namespace list to set.
	
	@code
	# This example shows how to merge multiple scenes, each scene in its own user specified namespace:

	# Create an Load FBFbxOptions object
	fbxLoadOptions = FBFbxOptions( True )

	# Create a list of namespaces (2 items here, so the number of scenes to merge must also be 2)
	# and set the list in the FBFbxOptions object
	myNS = FBStringList( "MyFirstNS~MySecondNS" )
	fbxLoadOptions.SetMultiLoadNamespaceList( myNS )

	# Create a list of scenes to merge
	myScenesToMerge = FBStringList( "C:\Temp\MyFirstScene.fbx~C:\Temp\AnotherScene.fbx" )

	# Let's merge those scenes. The namespaces will be applied on the scenes' contents.
	print FBApplication().FileMerge( myScenesToMerge, False, fbxLoadOptions )
	@endcode
	*/
	void SetMultiLoadNamespaceList( const FBStringList& pMultiLoadNamespaceList );

	/** Returns the list of namespaces that will be used when merging multiple scenes (see FBApplication::FileMerge).
	This list is affecting only the merge operation.
	When merging multiple scenes, if this list of namespaces is set, the FBFbxOptions::NamespaceList property value is ignored.
	\return The multi load namespace list currently set.
	*/
	FBStringList GetMultiLoadNamespaceList();
};

#ifdef FBSDKUseNamespace
	}
#endif

#endif
