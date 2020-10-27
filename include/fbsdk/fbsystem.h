#ifndef __FBSYSTEM_H__
#define __FBSYSTEM_H__
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

/**	\file fbsystem.h
*	Basic system interaction.
*	The FBSystem file contains the necessary data structure to 
*	interface with the underlying system.
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
#include <fbsdk/fbdata.h>	// FBPropertyListTake

#include <fbsdk/fbio.h>		// FBPropertyListCommPort
#include <fbsdk/fbshader.h>
#include <fbsdk/fbmodel.h>
#include <fbsdk/fbevaluateinfo.h>
#if !defined(K_NO_CONSTRUCTION_HISTORY)
    #include <fbsdk/fbconstructionhistory.h>
#endif

// For 'lean version' we don't need the plugin headers.
#if !defined(K_NO_AUDIO)
#include <fbsdk/fbaudio.h>
#endif

#if !defined(K_NO_VIDEO)
#include <fbsdk/fbvideo.h>
#endif

#if !defined(K_NO_DECK)
#include <fbsdk/fbdeck.h>			// FBPropertyListDeck
#endif

#if !defined(K_NO_ASSETMNG)
#include <fbsdk/fbassetmng.h>	// FBPropertyAssetMng
#endif

#if !defined(K_NO_MANIPULATOR)
#include <fbsdk/fbmanipulator.h>	// FBPropertyListManipulator
#endif

#ifdef FBSDKUseNamespace
namespace FBSDKNamespace {;
#endif

#if !defined(K_NO_CHARACTER)
    FB_FORWARD( FBCharacter );
#endif

    struct FBVideoGrabOptions;

    FB_DEFINE_COMPONENT( FBSDK_DLL, Take );
    FB_DEFINE_COMPONENT( FBSDK_DLL, Renderer );

	//! \b Event: Video Frame offline Rendering Event.
    class FBSDK_DLL FBEventVideoFrameRendering: public FBEvent 
    {
    public:
        /**	Constructor.
        *	\param pEvent Base event (internal) to obtain information from.
        */
        FBEventVideoFrameRendering( HKEventBase pEvent );

        //! video rendering state
        typedef enum{
            eBeginRendering = 1,  //!< State before video renderer renders all the frames
            eRendering,           //!< State before video renderer renders each frame
            eEndRendering         //!< State after  video renderer renders all the frames
        }EState;

        /**	returns the frame number the video renderer is about to render.
        *	\return	the frame number.
        */
        kInt64 GetFrameNumber();

        /**	returns the total number of frames the video renderer is rendering.
        *	\return	the total number of frames.
        */
        kInt64 GetFrameCount();

        /**	returns the current state of the video renderer.
        *	\return	the current state.
        */
        FBEventVideoFrameRendering::EState GetState();

    private:
        kInt64  mFrameNumber;    //!< <b>Read Only Property:</b> Current frame number
        kInt64  mFrameCount;     //!< <b>Read Only Property:</b> Frame count
        EState  mState;          //!< <b>Read Only Property:</b> Current rendering state
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBSystem
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBSystem );

    /**	Provides access to the underlying system, and the MotionBuilder scene.
    *	Use this class to access system properties such as the computer name, 
    the system time, and the MotionBuilder application version.

    It is also used to get access to the scene (FBScene) and the current take (FBTake), 
    as in the following Python snippet:

    \code
    myScene = FBSystem().Scene
    for take in myScene.Takes:
        print take.Name
    \endcode

    The Python sample FBSystemEvents.py shows how to register a callback to FBSystem.

    */
    class FBSDK_DLL FBSystem : public FBComponent {
        __FBClassDeclare( FBSystem,FBComponent );
    public:
        /**	Constructor.
        */
        FBSystem();

        FBPropertyString                        ConfigPath;                 // < <b>Read Only Property:</b> Location where the config folder is.
        FBPropertyString                        UserConfigPath;             // < <b>Read Only Property:</b> Location where the user config folder is.
        FBPropertyString                        ApplicationPath;            //!< <b>Read Only Property:</b> Location where the application is installed.
        FBPropertyString                        TempPath;					//!< <b>Read Only Property:</b> Temporary path returned by the OS.
        
        FBPropertyEventUIIdle					OnUIIdle;					//!< <b>Event:</b> User-interface idle event. Useful callback for less frequent GUI refresh and etc. lightweight tasks (occur once per several frames). 
        FBPropertyEventVideoFrameRendering      OnVideoFrameRendering;      //!< <b>Event:</b> A video frame rendering event occurred when the scene is being off-line rendered into video files.
        
        FBPropertyEventConnectionNotify			OnConnectionNotify;			//!< <b>Event:</b> A connection event occurred between objects in the system.
        FBPropertyEventConnectionDataNotify		OnConnectionDataNotify;		//!< <b>Event:</b> A data event occurred between objects in the system.
        FBPropertyEventConnectionStateNotify	OnConnectionStateNotify;	//!< <b>Event:</b> A state change event occurred between objects in the system.
        FBPropertyEventConnectionKeyingNotify	OnConnectionKeyingNotify;	//!< <b>Event:</b> A keying event occurred when objects are being keyed.

        FBPropertyString						ComputerName;				//!< <b>Read Only Property:</b> Computer name.
        FBPropertyDouble						Version;					//!< <b>Read Only Property:</b> Application version.
        FBPropertyString						BuildId;				    //!< <b>Read Only Property:</b> Unique build Id string.
        FBPropertyString						BuildVersion;				//!< <b>Read Only Property:</b> Unique build version string. The format of the build version information is: Major.Minor.Revision.BuildNumber. All sub-parts of the build version string are containing only numeric characters.


		FBPropertyBool							SuspendMessageBoxes;		//!< <b>Read Write Property:</b> While true, all the message boxes, that would normally be displayed, are suspended.
																			//!< This property should be used as a temporary solution for unwanted message boxes, while running a script for example.
																			//!< For system wide usage, the -suspendMessages argument, set when launching MotionBuilder, should be used instead.


        FBPropertyTime							SystemTime;					//!< <b>Read Only Property:</b> System time.
        FBPropertyTime							LocalTime;					//!< <b>Read Only Property:</b> Local time in take.
        FBPropertyTake							CurrentTake;				//!< <b>Read Write Property:</b> Current take.

        FBPropertyScene							Scene;						//!< <b>Read Only Property:</b> Scene.
#if !defined(K_NO_CONSTRUCTION_HISTORY)
		FBPropertyConstructionHistory			ConstructionHistory;		//!< <b>Read Only Property:</b> Construction History.
#endif
        FBPropertyModel							SceneRootModel;				//!< <b>Read Only Property:</b> Scene root model. 
        FBPropertyModel							RootModel;					//!< <b>Read Only Property:</b> Root model.
        FBPropertyString						PathImages;					//!< <b>Read Only Property:</b> Path to images.
        FBPropertyString						PathMeshs;					//!< <b>Read Only Property:</b> Path to meshes

#if !defined(K_NO_AUDIO)
        FBPropertyListAudioIn					AudioInputs;				//!< <b>List:</b> Available audio inputs.
        FBPropertyListAudioOut					AudioOutputs;				//!< <b>List:</b> Available audio outputs.
#endif

#if !defined(K_NO_VIDEO)
        FBPropertyListVideoIn					VideoInputs;				//!< <b>List:</b> Available video inputs.
        FBPropertyListVideoOut					VideoOutputs;				//!< <b>List:</b> Available video outputs.
#endif																	

        FBPropertyListCommPort					CommPorts;					//!< <b>List:</b> Comm Ports available.
        FBPropertyRenderer						Renderer;					//!< <b>Read Only Property:</b> Default renderer.

        FBPropertyDouble						FrameRate;					//!< <b>Read Only Property:</b> The frame rate of the viewer.
        FBPropertyDouble						ProcessMemory;				//!< <b>Read Only Property:</b> The size (MB) of process's working set memory.
        FBPropertyDouble						ProcessMemoryPeak;			//!< <b>Read Only Property:</b> The size (MB) of process's peak memory.
        FBPropertyVector2d						DesktopSize;				//!< <b>Read Only Property:</b> The width and height of the desktop.
        FBPropertyBool							FullScreenViewer;			//!< <b>Read Write Property:</b> Indicates that the viewer is in full screen mode.

#if !defined(K_NO_ASSETMNG)
        FBPropertyAssetMng						AssetManager;				//!< <b>Read Only Property:</b> Current asset manager.
#endif

#if !defined(K_NO_MANIPULATOR)
        FBPropertyListManipulator				Manipulators;	//!< <b>List:</b> of manipulators.
#endif

        /**	Load a library (DLL) into memory
        *	\param	pPath	Library path.
        *	\return	true if successful.
        */
        static bool  LibraryLoad(const char *pPath);
        /**	Get the the address of a function in a specified library
        *	\param	pPath			Library path.
        *	\param	pFunctionName	Function name.
        *	\return	true if successful.
        */
        static void* LibraryGetProcAddress(const char *pPath, const char *pFunctionName);
        /**	Free a library (DLL) from memory
        *	\param	pPath	Library path.
        *	\return	true if successful.
        */
        static bool  LibraryFree(const char *pPath);

        /** Get current work directory
        *   \return current work directory.
        */
        static FBString	CurrentDirectory();

        /** Return the full path.
        *   \param pRelativeFilePath    The relative file path
        *   \return                     Full file path based on combining the current directory
        */
        static FBString MakeFullPath(const char* pRelativeFilePath);

        /**	Get the global FBSystem object
        *	\return	the global object.
        */
        static FBSystem& TheOne();

        /**	Returns the command line arguments for SDK.
        *   This function returns portion of the command line arguments within a pair of delimiters (--sdk-begin & --sdk-end). Example:
        *
        *   >>> motionbuilder -console -g500,500 -suspendMessages --sdk-begin --department mocap --usage on-stage --sdk-end C:/temp/sample.fbx 
        *
        *   Note that "-console", "-suspendMessages" and "C:\temp\sample.fbx" are for MotionBuilder itself hence are consumed accordingly.
        *   Only those arguments between --sdk-begin and --sdk-end are accessible with this function. In this example, they will be 
        *   "--department mocap --usage on-stage"
        *
        *   This SDK command line argument is useful for plugin deployment and management in large production facility, where different department
        *   or different workflow may require a different set of plugins or functionality/behavior dynamically. 
        *   
        *   Python users also have access to this through official built-in module sys.argv which could be parsed easily via argparse module.   
        *   
        *	\return	the command line arguments
        */
        const FBStringList &GetCommandLineArgs() const;

         /** Returns the python startup path.
         *
         *  User could put python script in the startup folders, and MotionBuilder will search scripts from those folders and run them at startup. 
         *  By default, there are two startup folders: $(UserConfigDir)/config/PythonStartup and $(MoBuInstDir)/bin/config/PythonStartup.
         *  Users could append additional paths by setting environment variable "MOTIONBUILDER_PYTHON_STARTUP" before launching application.
         *
         *  \return the python startup path
        */
        const FBStringList& GetPythonStartupPath() const;

        /** Returns the plugin path.
         *  By default, MotionBuilder searches C++ plug-ins and load them at start-up.
         *  Users could provide additional plugin paths by setting environment variable "MOTIONBUILDER_PLUGIN_PATH" before running MotionBuilder.
         *  \return the plugin path
        */
        const FBStringList& GetPluginPath() const;

		//! Array index of each plug-in item information (see the GetLoadedPluginItemInfo() member function).
		typedef enum {
			ePluginItemDescription,		//!< Plug-in item's description
			ePluginItemFileName,		//!< Plug-in item's filename
			ePluginItemIconName			//!< Plug-in item's icon name
		} EPluginItemInfo;

		/** Returns a string list containing the names of all the loaded plug-in.
		 *	\return the names of all the loaded plug-in.
		*/
		const FBStringList& GetLoadedPluginItemsName() const;

		/** Returns a string list containing the information of the specified plug-in item's name.
		 *	A specific plug-in item information can be retrieved from the returned string list with a EPluginItemInfo enum value.
		 *	\return the information of the specified plug-in item's name.
		*/
		const FBStringList& GetLoadedPluginItemInfo( const char* pPluginItemName ) const;

		/** Returns a string list containing the groups list in which the specified plug-in item's name belongs to.
		 *	\return the groups list in which the specified plug-in item's name belongs to.
		*/
		const FBStringList& GetLoadedPluginItemGroups( const char* pPluginItemName ) const;
    };

#ifndef K_NO_TRIGGER
    ////////////////////////////////////////////////////////////////////////////////////
    // FBTriggerManager
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBTriggerManager );
    /**	Trigger engine management.
    *	This simple class interfaces the basic triggering functions.
    */
    class FBSDK_DLL FBTriggerManager :public FBComponent 
    {
        __FBClassDeclare( FBTriggerManager, FBComponent );
    public:
        /**	Constructor.
        */
        FBTriggerManager();

        /**	Get the number of groups.
        *	\return Group count.
        */
        int GetGroupCount();

        /**	Get the name of a trigger group.
        *	\param	pIndex	Index of group to get name for.
        *	\return	Name of group.
        */
        char* GetGroupName( int pIndex );

        /**	Get the active status of a trigger group.
        *	\param	pIndex	Index of group to get status for.
        *	\return	Active status of group.
        */
        bool GetGroupActive( int pIndex );

        /**	Disable or enable a trigger group.
        *	\param	pIndex	Index of trigger group.
        *	\param	pState	New state for group.
        */
        void SetGroupActive( int pIndex, bool pState );

        FBPropertyBool		Active;		//!< <b>Read Write Property:</b> Active status of engine.
    };
#endif


    ////////////////////////////////////////////////////////////////////////////////////
    // FBKeyControl
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBKeyControl );

    /**	Key control.
    *	Interface to use the key controls tool.
    */
    class FBSDK_DLL FBKeyControl : public FBComponent
    {
        __FBClassDeclare(FBKeyControl, FBComponent);

    public:
        /**	Constructor.
        *	\param	pObject		Internal parent object(default=NULL).
        */
        FBKeyControl(HIObject pObject=NULL);

	/**	Move animation keys in space, with respect to a pivot object. 
	*	Equivalent to using the "Move Keys" button in the Key Controls panel.
    *   Only keys that are part of the current animation layer will get affected.
	*	\param	pTimeSpan	The time span in which the animation keys will be modified
	*	\param	pPivot		The pivot object to use as a reference. The pivot needs to be part of 
	*						pModelList (or the current keying group) otherwise the move keys operation 
	*						will abort
	*	\param	pT			The global translation to apply to the pivot
	*	\param	pR			The global Euler rotation to apply to the pivot (deg)
	*	\param	pS			The global scaling factors to apply to the pivot
	*	\param	pTime		The time at which the transformation values are applied to the pivot object
	*	\param	pModelList	List of models for which the animation will be modified. Optional parameter.
	*						If not supplied, the models in the current keying group will be used
	*/
	void MoveKeys( FBTimeSpan pTimeSpan, FBModel *pPivot, FBVector3d pT, FBVector3d pR, FBVector3d pS, FBTime pTime, FBModelList *pModelList = NULL );

        FBPropertyBool	AutoKey;	//!< <b>Read Write Property:</b> Enable/Disable Auto Key feature (key when moving 3D objects).
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBPointCacheManager
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBPointCacheManager );

    /**	Point Cache Manager
    *	Interface to the point cache manager.
    */
    class FBSDK_DLL FBPointCacheManager : public FBComponent
    {
        __FBClassDeclare(FBPointCacheManager, FBComponent);

        /**	Constructor.
        *	\param	pObject		Internal parent object(default=NULL).
        *   \Note   protect
        */
        FBPointCacheManager(HIObject pObject=NULL);

    public:
        FBPropertyListObject   Models;                  //!< <b>Read Write Property:</b> Models to be recorded

        FBPropertyBool         ApplyGlobalTransform;    //!< <b>Read Write Property:</b> Include no-deformable models and the global transform to Vertex Cache when true. 
        FBPropertyAction       SetTransformReference;   //!< <b> Action Property:</b> Set the model's current transformation as the reference.

        FBPropertyBool         ApplyCacheOnNewModel;    //!< <b>Read Write Property:</b> Duplicated the cached models, and assoicated the point cache to the new models. 
        FBPropertyModel        NewModelRoot;            //!< <b>Read Write Property:</b> Valid only when ApplyCacheOnNewModel is on. Create New Models under NewModelRoot. otherwise, a NULL model will be created. 

        FBPropertyBool         AllowCacheResampling;    //!< <b>Read Write Property:</b> Allow the resample models's existing point cache deformation when true.
        FBPropertyBool         AlwaysAskForPath;        //!< <b>Read Write Property:</b> Always ask for the point cache file save path when true.
        FBPropertyString       DefaultPath;             //!< <b>Read Write Property:</b> Default point cache file save path.
        FBPropertyBool         CacheNormal;             //!< <b>Read Write Property:</b> Cache normal when true.
        FBPropertyBool         CacheAABBox;             //!< <b>Read Write Property:</b> Cache AABBox (Axis Aligned Bounding Box) when true.
        FBPropertyBool         CreateMultiChannelCache; //!< <b>Read Write Property:</b> Create a single multiple channel point cache file for all models when true.
        FBPropertyBool         CreateFilePerFrameCache; //!< <b>Read Write Property:</b> Create the point cache file for each frame when true.
        FBPropertyInt          SaveEveryFrame;          //!< <b>Read Write Property:</b> Recording Frequency.

        /**	Get the global object for this class
        *	\return	the global object.
        */
        static FBPointCacheManager& TheOne();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBFileMonitoringManager
    ////////////////////////////////////////////////////////////////////////////////////
    __FB_FORWARD( FBFileMonitoringManager );
    /**
    *	File Monitoring Type.
    */
    enum FBFileMonitoringType	{
        kFBFileMonitoring_InvalidIndex, //!< Invalid value
        kFBFileMonitoring_MAINSCENE,    //!< Main Scene change monitoring.
        kFBFileMonitoring_ANIMATIONCLIP,//!< Animation clip change monitoring.
        kFBFileMonitoring_FILEREFERENCE,//!< File Reference change monitoring.
        kFBFileMonitoring_PYTHONEDITORSCRIPT, //!< Python Editor Script change monitoring.
    };

    FB_DEFINE_ENUM( FBSDK_DLL, FileMonitoringType );

    __FB_FORWARD( FBEventFileChange );

    /** File change event class.
    *	This event occurs every time a monitored file changed:
    */
    class FBSDK_DLL FBEventFileChange: public FBEvent 
    {
    public:

        /**	Constructor.
        *	\param pEvent Base event (internal) to obtain information from.
        */
        FBEventFileChange( HKEventBase pEvent );		

        FBPropertyFileMonitoringType	Type;		 //!< <b>Read Only Property:</b> Type of file change event.
        FBPropertyString                Path;		 //!< <b>Read Only Property:</b> The path of changed file.
    };

    /**	File Change Monitoring
    *	Interface to the file change monitoring.
    */
    class FBSDK_DLL FBFileMonitoringManager : public FBComponent
    {
        __FBClassDeclare(FBFileMonitoringManager, FBComponent);

        /**	Constructor.
        *	\param	pObject		Internal parent object(default=NULL).
        *   \Note   protect
        */
        FBFileMonitoringManager(HIObject pObject=NULL);

    public:
        /**	Add file to monitor.
        *	\param	pFilePath	The file path to monitor.
        *	\param	pFileMonitoringType	The monitor type of this file.
        */
        void AddFileToMonitor(FBString pFilePath, FBFileMonitoringType pFileMonitoringType );

        /**	Remove file from monitoring.
        *	\param	pFilePath	The file path to be removed.
        */
        void RemoveFileFromMonitor(FBString pFilePath);

        /**	Pause file from monitoring, except for Python Editor script files loaded.
        *	\param	pPause	True to pause the file monitoring, false to resume.
        */
        void PauseFileMonitoring(bool pPause = true);

        /**	Clean files and directories currently been monitored.
        *	\param	pIncludePythonEditorScripts	True to also clean the monitoring of Python Editor script files loaded, false otherwise.
        */
        void CleanFileMonitoring(bool pIncludePythonEditorScripts = true);

    public:
        FBPropertyEvent    OnFileChangeMainScene;			//!< <b>Event:</b> Main scene file change event.
        FBPropertyEvent    OnFileChangeAnimationClip;		//!< <b>Event:</b> Animation clip file change event.
        FBPropertyEvent    OnFileChangeFileReference;		//!< <b>Event:</b> File Reference file change event.
        FBPropertyEvent    OnFileChangePythonEditorScript;	//!< <b>Event:</b> Python Editor Script file change event.
        /**	Get the global object for this class
        *	\return	the global object.
        */
        static FBFileMonitoringManager& TheOne();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBCriticalSection
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBCriticalSection );

    /**	High priority critical section class.
    *	This class permits the user to operate critical operations, freezing the system for 
    *	a high priority thread.
    */
    class FBSDK_DLL FBCriticalSection
    {
        void *mPtr;		//!< Internal data.
    public:
        //! Constructor.
        FBCriticalSection();

        //! Destructor.
        ~FBCriticalSection();

        /**	Initialize critical section operations.
        *	\return	true if successful.
        */
        bool Init();

        //! Enter section.
        void Enter();

        //! Leave section.
        void Leave();
    };

    ////////////////////////////////////////////////////////////////////////////////////
    // FBFastLock
    ////////////////////////////////////////////////////////////////////////////////////
    FB_FORWARD( FBFastLock );

    /** FBFastLock.
    *	This is the fastest thread lock available since its only a simple
    *	spinlock (1 instruction, test and set), BUT, note that this is not
    *	reentrant. i.e. The same thread cannot call lock two consecutive
    *	times or the thread will spinlock forever.
    */
    class FBSDK_DLL FBFastLock 
    {
        void *mPtr;		//!< Internal data.
    public:
        //! Constructor
        FBFastLock();

        //! Destructor
        ~FBFastLock();

        //! Enter lock.
        void Lock();

        //! Exit lock.
        void Unlock();
    };


    ////////////////////////////////////////////////////////////////////////////////////
    // Global utility functions
    ////////////////////////////////////////////////////////////////////////////////////

    /**	Sleep function
    *	Puts system to sleep for specified time.
    *	\param	MilliSeconds	Time to sleep for.
    */
    FBSDK_DLL void FBSleep( kULong MilliSeconds );

    /** \defgroup FBTrace The Trace utility functions 
    *   By passing the argument "-console" when launching MotionBuilder, it is possible to
    *   print formatted messages, as a printf would. On Mac OSX / Linux, the strings are simply sent to stderr.
    *   Upon Python Editor open, those formatted messages will be forwarded to Python console as well.
    *
    *   Global trace detailed level (kFBNORMAL_TRACE by default) could be controlled via 
    *   FBTraceSetLevel() / FBTraceGetLevel() functions, which affect all the trace output targets, 
    *   User could use pythonidelib.SetTraceLevel() / GetTraceLevel() to further adjust python console's 
    *   trace level as well (kFBNO_TRACE by default).
    *
    *   @{
    */

    /** Trace Level.
    *   \note there are value gap between CRITIICAL, NORMAL and ALL. SDK user could define custom trace level by providing in between values. 
    */
    enum FBTraceLevel
    {
        kFBNO_TRACE           = 0,    //<! Tracing disabled
        kFBCRITICAL_TRACE     = 1,    //<! Critical traces
        kFBNORMAL_TRACE       = 10,   //<! Descriptive traces
        kFBALL_TRACE          = 20    //<! Default value, all traces. 
    };

    /** Set Global Trace Detailed Level which affects all the output targets.
    *   \param  pNewLevel  Any trace message with detailed level higher than this new level will be ignored, 
    *           valid value range [kFBNO_TRACE, kFBALL_TRACE]
    *   \note   Python console trace current output level could be further adjusted via pythonidelib.SetTraceLevel(). 
    */
    FBSDK_DLL   void FBTraceSetLevel( unsigned int pNewLevel );

    /** Get Global Trace Detailed Level which affects all the output targets.
    *   \return Current global trace detailed level.
    *   \note   Python console trace current output level could be queried via pythonidelib.GetTraceLevel().
    */
    FBSDK_DLL   unsigned int FBTraceGetLevel(); 

    /**	This function prints useful debugging strings in the console with kFBNORMAL_TRACE output detailed level. 
    *   \param pFormatString    A printf-style format string, to use the following arguments in the list.
    *   \warning    There is currently a limitation which sets the maximum length of the resulting
    *               string to be limited to 2048 bytes.
    *   \warning    Not thread safe, as an static array is used internally.
    */
    FBSDK_DLL void FBTrace( const char* pFormatString, ... );

    /**	This function prints useful debugging strings in the console.
    *   \param pLevel           to control trace output detailed level, valid value range [kFBCRITICAL_TRACE, kFBALL_TRACE]
    *   \param pFormatString    A printf-style format string, to use the following arguments in the list.
    *   \warning    There is currently a limitation which sets the maximum length of the resulting
    *               string to be limited to 2048 bytes.
    *   \warning    Not thread safe, as an static array is used internally.
    */
    FBSDK_DLL void FBTraceWithLevel( unsigned int pLevel, const char* pFormatString, ... );

    /** Trace Stub Function type define */
    typedef void (*FBTraceStubFct)(unsigned int pLevel, const char *pStr);

    /** Register custom trace stub function. 
    *   \param pFct Custom trace stub function.
    *   \return True if register successfully.
    */
    FBSDK_DLL   bool FBRegisterTraceStubFct(FBTraceStubFct pFct);

    /** Unregister custom trace stub function. 
    *   \param pFct Custom trace stub function.
    *   \return True if un-register successfully.
    */
    FBSDK_DLL   bool FBUnRegisterTraceStubFct(FBTraceStubFct pFct);

    /** 
    *   @}
    */
    
    /** \defgroup Object creation / deletion log utility functions. 
    *   This set of utility functions are useful for tracing the object creation / deletion. 
    *   It help to identify potential memory leak inside SDK plugin, or even inside MoBu 
    *   for particular client workflow. 
    *
    *   see Sctipts/Samples/Utilities/DebugMemoryLeak.py for usage example.
    *   @{
    */
    
    /** Enable object creation / deletion logging. Default logging if off
    *   This logging may hurt performance slightly. use it only for debug purpose.
    *   \param pEnable  true to enable logging.
    */
    FBSDK_DLL void FBObjectLifeLogEnable(bool pEnable);
    
    /** Get the global static object unique ID counter.
    *   Each new created object will be assigned this global unique ID.
    *   Object.UniqueID = GlobalUniqueID++
    */
    FBSDK_DLL unsigned int  FBObjectGetGlobalUniqueId();

    /** Print those living objects created when logging is enabled.
    *   \param pStartUniqueId Any living object has been logged and with its uniqueId no less 
    *                   than pStartUniqueId will be printed out.
    */
    FBSDK_DLL void FBObjectPrintLivings(unsigned int pStartUniqueId);

    /** Get current total living object count.
    */
    FBSDK_DLL unsigned int  FBObjectGetLivingCount();

    /**
*   @}FBeval
    */

    /**	Get the given file's full path.
    *	\retval pFullPath If the given file path is not root path, return the new path with the given file path behind the given root path,
    *	if the given path is root path, directly return the given path.
    *	\param pRootPath The given root path.
    *	\param pFilePath The given file path.
    */
    FBSDK_DLL void FBMakeFullPath( FBString &pFullPath, const char *pRootPath, const char *pFilePath );

    /**	Loop over directory content. Call file and directory visitor function callbacks.
    */
    class FBSDK_DLL FBVisitDirectoryCallback
    {
    public:
        virtual ~FBVisitDirectoryCallback();
        virtual void FileVisited(const char*  pSrc) const;
        virtual void DirectoryVisited(const char*  pSrc) const;
        bool DoIt( const char* pSrcPath, bool pRecursive ) const;
    };

/**	FBDirMap: Allows to map a directory to another directory. For example, one could
              map all the files located in the Widows folder "o:\MyScenes\" to the Linux
			  folder "/usr/data/Scenes/" by calling:
			    FBDirMap::Add("o:\\MyScenes","/usr/data/Scenes")
              
			  Directories will remained mapped until the end of the application, 
			  or until the Clear method is called.
              The mapping is case-sensitive on all platforms.

			  Environment variables tokens can be specified using the $(env_var) format.
			  Environment variables are expanded at the time paths are added to the 
			  map.
    */
FB_FORWARD( FBDirMap );
class FBSDK_DLL FBDirMap
{
public:
	virtual ~FBDirMap();
	/**	Adds an entry in the map. Environment variables can be specified for the target path
	using the $(env_var) syntax.
	Environment variables are expanded before the paths get added to the map.
	An error in the formatting of the paths (environment variable tokens) will abort the 
	expansion and both given paths will remained unchanged.

		\param	pSourceDir The source directory
		\param	pTargetDir The target directory
	*/
	static void Add(FBString pSourceDir, FBString pTargetDir);

	/**	Returns the number of items in the map
	*/
	static int GetCount();

	/** Returns the source directory for the element at specified index
	*/
	static FBString GetSource(int pIndex);

	/** Returns the target directory for the element at specified index
	*/
	static FBString GetTarget(int pIndex);

	/** Clears the map
	*/
	static void Clear();

	/**	Iterates through all the mapped directories. If one of the mapped directory's
	    source is found in the given path, that part of the path will be replaced
		by the mapped directory's target. Only the first occurrence is processed.

		\param	pPath The path to process
	*/
	static FBString Map(FBString pPath);
};

#ifdef FBSDKUseNamespace
}
#endif
#endif

