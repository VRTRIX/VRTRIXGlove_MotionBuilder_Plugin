#ifndef __FBPAPPLICATION_H__
#define __FBPAPPLICATION_H__
/**************************************************************************
Copyright (c) 1994 - 2013 Autodesk, Inc. and/or its licensors.
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

/**	\file fbapplication.h
*	this file contain FBApplication class interface
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
/** \def FBSDK_DLL
*	Be sure that FBSDK_DLL is defined only once...
*/
#define FBSDK_DLL K_DLLIMPORT
#endif

// Essential includes
#include <fbsdk/fbcomponent.h>

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {;
#endif

////////////////////////////////////////////////////////////////////////////////////
// FBBatchOptions
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBBatchOptions );

//! Different process type for the batch.
enum FBBatchProcessType
{
    kFBBatchProcessTypeLoad,	//!< Load the files and plot the character with every take.
    kFBBatchProcessTypeSave,	//!< Save the takes in different files.
    kFBBatchProcessTypeConvert	//!< Does the load and save.
};
FB_DEFINE_ENUM( FBSDK_DLL, BatchProcessType );

//! Different file formats for the batch.
enum FBBatchFileFormat
{
    kFBBatchFileFormatTRC,	    //!< File format for Motion Analysis TRC.
    kFBBatchFileFormatC3D,		//!< File format for Vicon C3D.
    kFBBatchFileFormatAMC,		//!< File format for Acclaim AMC.
    kFBBatchFileFormatBVH,		//!< File format for Biovision BVH.
    kFBBatchFileFormatHTR,		//!< File format for Motion Analysis HTR.
    kFBBatchFileFormatFBX		//!< File format for FBX (animation only).
};
FB_DEFINE_ENUM( FBSDK_DLL, BatchFileFormat );

//! Different actions to perform when a take already exist while in a batch process.
enum FBBatchOnTakeExist
{
    kFBBatchOnTakeExistOverwrite,	//!< Overwrite the take.
    kFBBatchOnTakeExistSkip			//!< Skip the take.
};
FB_DEFINE_ENUM( FBSDK_DLL, BatchOnTakeExist );

//! Different actions to perform when a scene already contains batch takes while in a batch process.
enum FBBatchOnContainsBatchTakes
{
    kFBBatchOnContainsBatchTakesSaveBatchTakesOnly,	//!< Save only the batch takes.
    kFBBatchOnContainsBatchTakesSaveAllTakes		//!< Save all the takes.
};
FB_DEFINE_ENUM( FBSDK_DLL, BatchOnContainsBatchTakes );

//! Different return values of the Batch process.
enum FBBatchStatus
{
    kFBBatchStatusSuccess,
    kFBBatchStatusError,
    kFBBatchStatusCharacterNotSpecified,
    kFBBatchStatusCharacterNotCharacterized,
    kFBBatchStatusCharacterHasNoReference,
    kFBBatchStatusInputActorNotSpecified,
    kFBBatchStatusActorInputMarkersetNotSpecified,
    kFBBatchStatusActorInputMarkersetHasNoReferenceModel,
    kFBBatchStatusActorInputMarkersetNotCorrectlyAssociated,
    kFBBatchStatusInputCharacterNotCharacterized,
    kFBBatchStatusInputCharacterHasNoReference,
    kFBBatchStatusInputDirectoryNotValid,
    kFBBatchStatusAsfSkeletonFileNotSpecified,
    kFBBatchStatusCantOpenAsfSkeletonFile,
    kFBBatchStatusOutputDirectoryNotValid
};

//! Option parameters for the batch process.
class FBSDK_DLL FBBatchOptions
{
public:

    /** Constructor.
    */
    FBBatchOptions();

    FBBatchFileFormat		mInputFileFormat;			//!< File format of the input files.	
    FBBatchFileFormat		mOutputFileFormat;			//!< File format of the output files.

    FBBatchProcessType		mProcessType;				//!< What process should be done? Load, Save or Both.

    FBString				mInputDirectory;            //!< The directory containning the input files.
    FBString				mOutputDirectory;           //!< The directory containning the output files.
    FBString				mSkeletonFile;              //!< The Skeleton file (for Acclaim AMC files).

#if !defined(K_NO_CHARACTER)
    FBCharacter*			mCharacter;					//!< The character to receive the animation.
#endif

    bool					mStartAnimationAtZero;		//!< Set the time of all loaded files to 0.
    bool					mFrameAnimation;			//!< Set timeline start and end time to corespond with the start and end of animation.
    bool					mOverwriteScaling;			//!< Set the scaling to a default setting of 1.0.
    bool					mKeepDummyBones;			//!< To keep dummy bones.
    bool					mWriteRate;					//!< Write frame rate in Acclaim AMC files.
    bool					mWriteTranslation;			//!< Write translation animation data included with Acclaim AMC files.
    bool					mPlotToCharacter;			//!< To plot the animation on the character.
    bool					mPlotToControlSet;			//!< To plot the animation on the control set.
    bool					mUseSingleTake;				//!< Use only one take to convert all files.
    bool					mUseBatchSuffix;			//!< Add a batch suffix to the name of the files.
    bool					mKeepCharacterConstraint;	//!< To keep the character constaint when saving.

    FBBatchOnTakeExist			mOnTakeExistAction;				//!< Action to perform when a take already exist while in a batch process.
    FBBatchOnContainsBatchTakes	mOnContainsBatchTakesAction;	//!< Action to perform when a scene already contains batch takes while in a batch process.
};


////////////////////////////////////////////////////////////////////////////////////
// FBPlotOptions
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBPlotOptions );

//! Rotation filters
enum FBRotationFilter
{
    kFBRotationFilterNone,
    kFBRotationFilterGimbleKiller,
    kFBRotationFilterUnroll
};
FB_DEFINE_ENUM( FBSDK_DLL, RotationFilter );

//! The tangent mode for plotted curve
enum FBPlotTangentMode
{
    kFBPlotTangentModeSmooth,
    kFBPlotTangentModeSmoothClamp,
    kFBPlotTangentModeSpline,
    kFBPlotTangentModeSplineClamp,
    kFBPlotTangentModeAuto
};
FB_DEFINE_ENUM( FBSDK_DLL, RotationFilter );

//! Option parameters for plotting
class FBSDK_DLL FBPlotOptions
{
public:

    /** Constructor.
    */
    FBPlotOptions();

    bool				mPlotAllTakes;					//!< Should we plot all takes?
    bool				mPlotOnFrame;					//!< Should we plot on frame?
    FBTime				mPlotPeriod;					//!< The plot period (1/fps).
    FBRotationFilter	mRotationFilterToApply;			//!< The rotation filter to apply.
    FBPlotTangentMode   mPlotTangentMode;               //!< The tangent mode for plotted curve.
    bool				mUseConstantKeyReducer;			//!< Should we use a constant key reducer with the filter?
    bool				mConstantKeyReducerKeepOneKey;	//!< Should the constant key reducer keep at least one key?
    bool				mPlotTranslationOnRootOnly;		//!< Should we plot the translation on root only?
    bool				mPreciseTimeDiscontinuities;	//!< Should we use precise time dicontinuities?
    bool				mPlotLockedProperties;			//!< Should we plot locked properties?
};

#if !defined(K_NO_AUDIO)
////////////////////////////////////////////////////////////////////////////////////
// FBAudioRenderOptions
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBAudioRenderOptions );

/** Audio Render Options structure.
*	Contain options to control how the audio rendering will occur.
*/
class FBSDK_DLL FBAudioRenderOptions
{
public:

    /** Constructor.
    */
    FBAudioRenderOptions();

    FBTimeSpan				TimeSpan;		//!< <b>Property:</b> Start and stop selection time to render.
    FBAudioChannelMode		ChannelMode;	//!< <b>Property:</b> Audio render channel number, 1 for Mono(left channel right channel render mixed to one channel), 2 for Stereo(left channel right channel render separately).
    FBAudioBitDepthMode		BitDepthMode;	//!< <b>Property:</b> Bit depth for one sample of audio. 8 bits and 16 bits available for audio render, 16 bits default.
    FBAudioRateMode			RateMode;		//!< <b>Property:</b> Rate mode for number of samples per second. 44100 hz default,8000, 11025,12000,16000,22050,24000,32000,44100,48000,64000,88200,96000 available for audio render.
    FBString				OutputFileName;	//!< <b>Property:</b> Audio Render destination file.
};
#endif

__FB_FORWARD( FBApplication );
#if !defined(K_NO_CHARACTER)
__FB_FORWARD( FBCharacter );
#endif
#if !defined(K_NO_ACTOR)
__FB_FORWARD( FBActor );
#endif
#if !defined(K_NO_CHARACTER)
FB_DEFINE_COMPONENT( FBSDK_DLL, Character );
#endif
#if !defined(K_NO_ACTOR)
FB_DEFINE_COMPONENT( FBSDK_DLL, Actor );
#endif

//! Different viewer modes for the 3D viewer.
enum FBViewerMode {	
    kFBViewerModeOneWindow,		//!< View one pane.
    kFBViewerModeTwoWindow,		//!< View two panes.
    kFBViewerModeThreeWindow,	//!< View three panes.
    kFBViewerModeFourWindow,	//!< View four panes.
    kFBViewerModeSchematic		//!< Schematic view.
};

#if !defined(K_NO_ONECLICK)
//! Possible application for One-Click interop with MotionBuilder.
enum FBOneClickApplication
{
    kFBOneClickNone, //!< No application.
    kFBOneClickMaya, //!< Maya.
    kFBOneClick3dsMax, //!< 3ds Max.
    kFBOneClickSoftimage, //!< Softimage.
};
#endif

/** FBApplication is used mainly to manage files.
It provides functionality like that in the MotionBuilder file menu, for example, open file, save file. 

Note that event registration is instanced-based. When an FBApplication object is destroyed, all the
event callbacks are unregistered. If you want to have a tool to be notified of events, it needs to have a FBApplication
data member.
*/
class FBSDK_DLL FBApplication : public FBComponent 
{
    __FBClassDeclare( FBApplication,FBComponent );
public:
    /**	Constructor.
    *	\param	pObject	Internal parent object(default=NULL).
    */
    FBApplication(HIObject pObject=NULL);

    FBPropertyEvent	OnFileNewCompleted;		//!< <b>Event:</b> A File New has been completed.
    FBPropertyEvent	OnFileNew;				//!< <b>Event:</b> A File New has been requested, nothing has been destroyed yet.
    FBPropertyEvent	OnFileOpenCompleted;	//!< <b>Event:</b> A File Open has been completed.
    FBPropertyEvent	OnFileOpen;				//!< <b>Event:</b> A File Open has been requested, nothing has been loaded yet.
    FBPropertyEvent	OnFileMerge;			//!< <b>Event:</b> A File Merge has been requested, nothing has been loaded yet.
    FBPropertyEvent	OnFileSaveCompleted;	//!< <b>Event:</b> A File Save has been completed.
    FBPropertyEvent	OnFileSave;				//!< <b>Event:</b> A File Save has been requested, nothing has been saved yet.
    FBPropertyEvent	OnFileExit;				//!< <b>Event:</b> A File Exit as been requested, nothing has been destroyed yet.

    /**	Minimize window.
    *	\param	pBlocking	Is the minimization blocking operation (default = true).
    *	\return	Operation was successful (true or false).
    */
    bool Minimize(bool pBlocking=true);

    /**	Maximize window (minimized).
    *	\return Operation was successful (true or false).
    */
    bool Maximize();

    /**	Request to refresh display of all UI widgets.*/
    void UpdateAllWidgets();

    /** Flush event queue.
    *   Processes all pending events for the calling thread until there are no more events to process.
    *   You can call this function occasionally when your code is busy performing a long operation (e.g. copying a file).
    */
    void FlushEventQueue();

    /**	Command FILE->NEW in the menus.
    *	\param	pAskUser            Set to true to cause a save dialog to popup. Default is false.
    *	\param	pClearSceneName     Set to true to clear the scene name, set to false to retain it. Default is true.
    *	\return	true if successful.
    */
    bool FileNew(bool  pAskUser = false, bool pClearSceneName = true);

    /**	Open a file, replacing the current scene.
    *	Command File->Open in the menus.
    *	\param	pFilename	File to open.
    *	\param  pShowUIMsg  Set false if don't want to popup any UI dialog or messages (default=false).
    *	\param  pOptions    Provide finer control on file open options (default=NULL). if not null, 
    *                       Option dialog will only show if both option's ShowOptionsDialog property and pShowUIMsg are true.
    *   \return true if file open successfully.
    */
    bool FileOpen( const char* pFilename, bool pShowUIMsg = false, FBFbxOptions* pOptions = NULL );

    /** Open a file from memory. 
    *   \warning this is advanced & not supported function, use with caution. 
    *   \param pBuffer  the memory buffer for the file. Raw memory address is expected in pyfbsdk. 
    *   \param pBufferLength the memory buffer size.
    *   \return true if file opened successfully.
    */
    bool FileOpen( void* pBuffer, kULong pBufferLength );		

    /** Get max frame count from a scene file in memory. 
    *   \warning this is advanced & not supported function, use with caution. 
    *   \param pBuffer  the memory buffer for the file. Raw memory address is expected in pyfbsdk. 
    *   \param pBufferLength the memory buffer size.
    *   \param pFrameCount out parameter to hold max frame count. this parameter is not needed in pyfbsdk. 
    *   \param pTimeScale   Time scale. 
    *   \return true if file opened successfully. In pyfbsdk, a tuple (bool, kLong) will return instead, the first one is ORSDK function return value, the second is for max frame count. 
    */
    bool GetMaxFrameCount(void* pBuffer, kULong pBufferLength, kLong* pFrameCount, int pTimeScale);	

    /**	Merge a file with the current scene.
    *	Command File->Merge in the menus.
    *	\param	pFilename	File to merge.
    *	\param  pShowUIMsg  Set false if don't want to popup any UI dialog or messages (default=false).
    *	\param  pOptions    Provide finer control on file open options (default=NULL). if not null, 
    *                       Option dialog will only show if both option's ShowOptionsDialog property and pShowUIMsg are true.
    *	\return	true if successful.
    */
    bool FileMerge( const char* pFilename, bool pShowUIMsg = false, FBFbxOptions* pOptions = NULL );

    /**	Merge multiple files with the current scene.
    *	Command File->Merge in the menus.
    *	\param	pPathlist	Files to merge.
    *	\param  pShowUIMsg  Set false if don't want to popup any UI dialog or messages (default=false).
    *	\param  pOptions    Provide finer control on file open options (default=NULL). if not null, 
    *                       Option dialog will only show if both option's ShowOptionsDialog property and pShowUIMsg are true.
    *	\return	true if successful.
    */
    bool FileMerge( FBStringList& pPathlist, bool pShowUIMsg = false, FBFbxOptions* pOptions = NULL );

    /**	Append a file to the current scene.
    *	Same as File->Merge in the menus with all options set to append.
    *	In earlier versions of MotionBuilder, a namespace could be specified with a parameter in this function, or FBFbxOptions::CustomImportNamespace,
    *       Now this is now done with FBFbxOptions::NamespaceList.
    *	\param	pFilename	File to merge.
    *	\param  pShowUIMsg  Set false if don't want to popup any UI dialog or messages (default=false).
    *	\param  pOptions    Provide finer control on file open options (default=NULL). if not null, 
    *                       Option dialog will only show if both option's ShowOptionsDialog property and pShowUIMsg are true.
    *	\return	true if successful.
    */
    bool FileAppend( const char* pFilename, bool pShowUIMsg = false, FBFbxOptions* pOptions = NULL );

    /** Save the file under another name.
    *	Command File->SaveAs in the menus.
    *	\param	pFilename	Save file as \p pFilename. A value of NULL will use the current file name.
    *	\param  pOptions    Provide finer control on file save options (default=NULL)
    *	\return	true if successful.
    */
    bool FileSave( const char* pFilename = NULL, FBFbxOptions* pOptions = NULL );

    /**	Quit application.
    *	Command File->Exit in the menus.
    *	\param	pSave	true if file is saved on exit(default=false).
    */
    void FileExit( bool pSave = false );

    /**	Import a motion file.
    *	Command File->Motion File Import... in the menus.
    *	\param	pFilename		The file to import. To import two files at the same time (ex: .amc & .asf), separate the two files path with a comma ("Path1,Path2").
    *	\param	pMatchModels	If there is already a model in the scene with the same name, the model will not be created and we replace the animation of the given model.
    *	\param	pCreateUnmatchedModels	Whether unmatched models will be created. This flag matters only when \p pMatchModels is true. when \p pMatchModels is false, all the models are created.
    *	\return					True if the import succeeded.
    *	\remark					No models selected, all the models in the scene will be checked for a potential name match.
    *	\remark					If there are models selected in the scene, only these models will be checked for a potential name match.
    *	\remark					If only one model is selected (ex: hips), this models and its hierarchy will be used.
    *	\remark					The data will be imported in the current take.
    *	\remark					The last two parameter are only used for motion files.
    *	\remark					For now, you cannot import custom file types.
    *	\remark					Currently, only the default import options are used.
    *	\warning				The signature of this function might change in the future to support import options.
    */
    bool FileImport( FBString pFilename, bool pMatchModels = false, bool pCreateUnmatchedModels = true );

    /**	Export a motion file.
    *	Command File->Motion File Export... in the menus.
    *	\param	pFilename		The file to create. To create two files at the same time (ex: .amc & .asf), separate the two files path with a comma ("Path1,Path2").
    *	\return					True if the export succeeded.
    *	\remark					If the file exists, it will be overwritten.
    *	\remark					current take is use.
    *	\remark					The last parameter is only used for motion files.
    *	\remark					For now, you cannot export custom file types.
    *	\remark					Currently, only the default export options are used.
    *	\warning				The signature of this function might change in the future to support export options.
    */
    bool FileExport( FBString pFilename );

    /**	Start a batch.
    *	Command File->Batch... in the menus.
    *	\param	pBatchOptions	The options for the batch process (same as in the batch UI).
    *	\param	pPlotOptions	The options for plotting (same as in the plot UI)(default=NULL).
    *	\return					The status of the operation.
    */
    FBBatchStatus FileBatch( FBBatchOptions* pBatchOptions, FBPlotOptions* pPlotOptions = NULL );

    /**	Import a motion file using batch options.
    *	Import used for loading files in batch process.
    *	\param	pName			The name of the file without extension. Extension and path will be taken from batch options.
    *	\param	pBatchOptions	The options for the import.
    *	\param	pReference		Reference model for the import.
    *	\return					True if the import succeeded.
    *	\remark					Not all options have to be set, only those that belong to process.
    */
    bool FileImportBatch( const char* pName, FBBatchOptions* pBatchOptions, FBModel* pReference );

    /**	Export a motion file using batch options.
    *	Export used for saving files in batch process.
    *	\param	pName			The name of the file without extension. Extension and path will be taken from batch options.
    *	\param	pTake			Animation take to the export.
    *	\param	pBatchOptions	The options for the export.
    *	\param	pExportModels	Models to the export.
    *	\return					True if the export succeeded.
    *	\remark					Not all options have to be set, only those that belong to process.
    */
    bool FileExportBatch( const char* pName, FBTake* pTake, FBBatchOptions* pBatchOptions, FBModelList &pExportModels );

#if !defined(K_NO_CHARACTER)

    /** Save the rig and its animation in a file.
    *   \param  pFileName  File name.
    *   \param  pCharacter  Character to save.
    *   \param  pFbxOptions  The options for the character rig and animation export
    *   \warning    After save, the current scene selection will be reset.
    */
    bool SaveCharacterRigAndAnimation( const char* pFileName, FBCharacter* pCharacter, FBFbxOptions* pFbxOptions);

    /** Load a rig and its animation from a file.
    *   \param  pFileName  File name.
    *   \param  pCharacter  Target character.
    *   \param  pFbxOptions  The options for the character rig and animation load
    *   \param  pPlotOptions  If the animation should be plotted on the target rig, these plot options will be used. Set to NULL if animation will not be plotted.
    *   \return \b true if successful.
    */
    bool LoadAnimationOnCharacter( const char* pFileName, FBCharacter* pCharacter,  FBFbxOptions* pFbxOptions, FBPlotOptions* pPlotOptions);
#endif

    /**	Verify motion file readability.
    *	\param	pFilename		The file to test.
    *	\return					True if file was opened successfully (file is closed at the end).
    */
    bool IsValidBatchFile( const char* pFilename );

#if !defined(K_NO_ONECLICK)
    /**	Send the current scene as a new scene in the specified application.
    *	\param	pApplication	The application that will receive the scene.
    *	\return					True if transfer successful.
    */
    bool OneClickSendAsNewScene( FBOneClickApplication pApplication );

    /**	Send the scene to update the current scene in the specified application.
    *	\return					True if transfer successful.
    */
    bool OneClickUpdateCurrentScene();

    /**	Send the scene and add it to the current scene in the specified application.
    *	\return					True if transfer successful.
    */
    bool OneClickAddToCurrentScene();

    /**	Select, in MotionBuilder, the object that were sent.
    */
    void OneClickSelectPreviouslySentObject();

    /**	Return the other application that MotionBuilder is connected to.
    *	\return					The application that MotionBuilder is connected to.
    */
    FBOneClickApplication OneClickIsConnectedTo();
#endif

    /** Render current scene to media file.
    *	Command FILE->RENDER in the menus.
    *	\param	pRenderOptions	The options used when rendering the scene. If you don't specify them, current one are used.
    *	\return					True if the file was rendered successfully otherwise False and FBVideoGrabber.GetLastErrorMsg() contains the description of the error.
    *	\remark					Render options can be changed if they are not valid.
    *	\warning				If the destination media file exist, it will be overwritten by default.
    */
    bool FileRender( FBVideoGrabOptions* pRenderOptions = NULL );

#if !defined(K_NO_AUDIO)
    /** Render audio of current scene to media file, currently WAV file only.
    *	\param	pAudioRenderOptions	The options used when rendering audio of the scene. Default value: 2 channels, 16 bits, 44100 hz, the begin and end time span for current time referential, Default file name is "Output.wav" in the last audio output path, ro the default document path if the last path doesn't exist.
    *	\return						True if the file was rendered successfully
    *	\warning If the destination media file exist, it will be overwritten by default. If the destination media file is opened by other application, the audio render process may not success because of not able to open it.
    */
    bool AudioRender( FBAudioRenderOptions* pAudioRenderOptions  = NULL);
#endif

    /**	Execute a python script file.
    *	\param	pFilename		The script file to execute.
    *	\return					True if the script file was found and executed.
    *	\remark					This function can only be used in the UI thread.
    */
    bool ExecuteScript(FBString pFilename);

    /**	Switch the current viewer's camera.
    *	\param	pCamera			Camera to switch current viewer to.
	*	\remark					This method is deprecated. Use FBRenderer.SetCameraInPane instead.
    */
    K_DEPRECATED_2016 void SwitchViewerCamera( FBCamera &pCamera );

public:
    FBPropertyString        FBXFileName;            //!< <b>Read Write Property:</b> Current scene filename.
#if !defined(K_NO_ACTOR)
    FBPropertyActor         CurrentActor;           //!< <b>Read Write Property:</b> Indicate the current actor, as used by the character tool. Can be NULL. If not null, CurrentCharacter must be null, as the character tool works on only one item at a time.
#endif
#if !defined(K_NO_CHARACTER)
    FBPropertyCharacter     CurrentCharacter;       //!< <b>Read Write Property:</b> Indicate the current character, as used by the character tool. Can be NULL. If not null, CurrentActor must be null, as the character tool works on only one item at a time.
#endif
    /**	Get the global object for this class
    *	\return	the global object.
    */
    static FBApplication& TheOne();
};

/** \defgroup File Merge Transaction Optimization. 
*   File Reference and scene assembly workflow load many small files which contain individual entities (model, material, 
*   texture, character, props and etc.,). And it's a quite time consuming process with normal workflow. 
*   The following set of merge transaction functions could be used to improve the performance effectively. 
*   
*   A single file load / merge operation mainly includes the following three major stages:
*   -# Loading file from disk to memory;
*   -# Translate/interpret the file content into the application scene object models;
*   -# Post processing (scene object preparation, UI refresh and etc).
*   
*   The last step (post processing) often is quite heavy. With the merge transaction, however this step could be executed only once for 
*   multiple consecutive file merge operations. for example:
*   [code]
*       MergeTransacionBegin()
*       File_Merge(filepath1)
*       File_Merge(filepath1)
*       File_Merge(filepath1)
*       ...
*       MergeTransactionEnd()
*   [/code]
*   This Merge Transaction could be nested. 
*
*   @{
*/

/**  Call to begin the transaction for merging multiple files. 
*   Useful to consecutively merge multiple files into scene. 
*   \note The transaction need to be closed by calling FBMergeTransactionEnd().
*/
FBSDK_DLL void FBMergeTransactionBegin();

/**  Call to end the merge transaction.
*/
FBSDK_DLL void FBMergeTransactionEnd();

/**  Call to tell if system is during Merge transaction.
*/
FBSDK_DLL bool FBMergeTransactionIsOn();

/**  Call to begin the transaction for merging multiple files and applying File Reference edit at the same time. 
*    Useful to consecutively merge multiple files into scene with FileRef edit operation in between.
*   \note The transaction need to be closed by calling FBMergeTransactionFileRefEditEnd().
*/
FBSDK_DLL void FBMergeTransactionFileRefEditBegin();

/**  Call to end merge transaction with File Reference edit. 
*/
FBSDK_DLL void FBMergeTransactionFileRefEditEnd();

/**  Call to tell if system is during File Reference Edit Merge transaction. 
*/
FBSDK_DLL bool FBMergeTransactionFileRefEditIsOn();

/** 
*   @}
*/

#ifdef FBSDKUseNamespace
} // namespace FBSDKNamespace
#endif

#endif