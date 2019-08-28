#ifndef __FBPROFILER_H__
#define __FBPROFILER_H__
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
#include <fbsdk/fbcore.h>

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

/** \def FBProfiler_CreateTaskCycle
*	Profiling global variable declaration for task cycle profiling in the SDK.
*	This declaration should be created in the plug-in/script file where the profiling is to occur. It needs to be registered onces per task cycle, no need to create task cycles for each class object instance.
*   \param	pClass		Name of the task cycle. Must be unique.
*   \param	pR,pG,pB	Task cycle color. Used in Profiling Center for drawing.
*/
#define FBProfiler_CreateTaskCycle( pClass, pR, pG, pB ) \
    int gProfilingIndex_##pClass = -1; \
    float gProfilingColor_##pClass[3] = { pR, pG, pB };

/** \def FBProfiling_SetupTaskCycle
*	Profiling global variable setup. This is the second step after calling FBProfiler_CreateTaskCycle.
*	Should be called only once, preferably in the constructor. Task cycle will be registered for its unique index during this call.
*   \param	pClass		Name of the task cycle. Must be the same name that was used for FBProfiler_CreateTaskCycle.
*/
#define FBProfiling_SetupTaskCycle( pClass ) \
    if(gProfilingIndex_##pClass == -1) \
		gProfilingIndex_##pClass = FBProfiler::TheOne().RegisterTaskCycle(#pClass,gProfilingColor_##pClass);

/** \def FBProfiling_TaskCycleIndex
*	Registered profiling task cycle index.
*	Returns the declared variable from FBProfiler_CreateTaskCycle based on the name of the task cycle provided. 
*   \param	pClass		Name of the task cycle.
*/
#define FBProfiling_TaskCycleIndex( pClass ) \
	gProfilingIndex_##pClass

//! Forwarding of class and type declaration.
__FB_FORWARD(FBProfiler);
FB_FORWARD(FBProfileTaskCycle);
__FB_FORWARD(FBProfileTimeEvent);
FB_FORWARD(FBEvaluateInfo);
FB_FORWARD(FBProfilerHelper);

/**	FBProfileTaskCycle.
*	Real-time profiling information for a specific task. Profiling information can be collected for:
*	- Evaluation: models, constraints, characters, story tracks
*	- Devices: DeviceIONotify, DeviceEvaluationNotify
*	- Rendering: renderer, render passes (like: Translucent, TranslucentZSort, Selected, OtherPrimitive, SelectiveLighting, etc)
*	- SDK
*	- Internal synchronization (idle callback, buffer swap, waiting on evaluation to finish before starting new rendering)
*
*	When profiling a scene within a MotionBuilder session you can discover what tasks are being performed when and for how long. 
*	You can use this information to troubleshoot lengthy or repetitive actions, and use MotionBuilder more efficiently.
*
*	A task is defined as a definite piece of work within MotionBuilder such as the evaluation of a character. 
*	If the same task is run numerous times it is called a task cycle. From within a scene, the hierary 
*	and dependents of the scene make up the task cycles. A task cycle spends its time computing a specific task within a task parent cycle. 
*
*	A task parent cycle is a hierarchy of individual task cycles, where the parent and child relationship is known to MotionBuilder 
*	and displayed in the profiling center.
*
*	For example, these are all task cycles which are all parented to each other; Eval is parent of TransformNode_Active, 
*	which is a parent of Constraint, which is a parent of Character, which is in turn a parent of TransformNode_Active. 
*
*	This is because the evaluation is called for one model which triggers evaluation of the character which then calls the evaluation of the rest of IK/FK models. 
*
*	When an evaluation starts, it calls the evaluation of the character, the time will be computed for time spent on the sample.  
*	Then possibly another character is evaluated, so again the time will be computed for the time spent on this sample. 
*	This time will be added to the previous sample since that evaluation has not finished yet.  The evaluation here is parented, 
*	since they both have started but not finished, all children samples are summed. When the evaluation stops, you change the sample for the children.
*	
*	Note: The evaluation dependency/order will be different for each scene.
*	
*	As you can see profiling of task cycles is done by collecting samples. Samples are added to one inside parent sample. 
*	The number of samples collected is controlled by the profiler buffer size property.
*
*	Here are the steps to add profiling into a constraint, a device, or any other class that uses real-time evaluation:
*	1) Declare FBProfiler_CreateTaskCycle( MyConstraint, 0.5, 0.5, 0.5 ) in MyConstraint.cxx, before the constructor and AnimationNodeNotify function.
*	2) Set up FBProfiling_SetupTaskCycle( MyConstraint ) in the constuctor MyConstraint::MyConstraint().
*	3) At the beginning of MyConstraint::AnimationNodeNotify create the variable:
		FBProfilerHelper lProfiling( FBProfiling_TaskCycleIndex( MyConstraint ), pEvaluateInfo );
	   The sample for task will start at the creation of FBProfilerHelper object and stop at the destruction of this object, when returning from AnimationNodeNotify will be done.
*/
class FBSDK_DLL FBProfileTaskCycle 
{
public:
	int				GetIndex();		//!< Get the unique registration index for each cycle.
	const char*		GetName();		//!< Get the name of task cycle.
	const float*	GetColor();		//!< Get the color of the task cycle. Used in profiling Center for drawing.

	/**	Get the task cycle's average, minimum and maximum usage. Results will vary on buffer size.
	*	When profiling is disabled all values are set to 1.
	*	\retval	pAvg	Average time spend for computation of task (in micro seconds).
	*	\retval	pMin	Minimum time spend for computation of task (in micro seconds).
	*	\retval	pMax	Maximum time spend for computation of task (in micro seconds).
	*/
	void			GetAvgMinMaxUsage(double& pAvg, double& pMin, double& pMax);

	// Sampling.
	void			Start();		//!< Start of task cycle sample. In most cases should be controlled by FBProfilerHelper.
	void			Stop();			//!< Stop of task cycle sample. In most cases should be controlled by FBProfilerHelper.
	bool			IsStarted();	//!< Test to see if sampling has started.
	
	/**	Get number of child tasks.
	*	Task cycles are organized in a hierarchy which is dependent on the scene. Samples can be cumulative in the parent task cycle, or independent.
	*	For example, all character evaluation samples will be cumulated in one evaluation cycle.
	*	\return	Number of child tasks.
	*/
	int				GetChildCount();
	
	/**	Get child task based on specific index.
	*	Can return NULL if child index is not used.
	*	\param	pIndex	Child index.
	*	\return	Child at given index.
	*/
	FBProfileTaskCycle*	GetChild(int pIndex);
private:
	//@{
	//! Private constructor.
	FBProfileTaskCycle();
	//! Private copy constructor.
	FBProfileTaskCycle(const FBProfileTaskCycle &);
	//! Private assignment.
	FBProfileTaskCycle & operator =(const FBProfileTaskCycle &);
	//@}
};

////////////////////////////////////////////////////////////////////////////////////
// FBProfileTimeEvent
////////////////////////////////////////////////////////////////////////////////////

/**	FBProfileTimeEvent.
*	Time event information is collected during sampling (activated with a property in FBProfiler ActiveSampling).
*	Events that can be collected are: render, evaluation, model evaluation, model deformation, synchronization of evaluation and rendering, playback commands, etc.
*
*	Sampling will stop when the buffers maximum size is reached (maximum is 10MB).
*
*	Currently users are not able to register any new events from ORSDK/python
*/
class FBSDK_DLL FBProfileTimeEvent
{
public:
	FBTime			GetTime();			//!< Get the time when the event occurred.
	const float*	GetColor();			//!< Get the color assigned to the event.
	
	const char*		GetTypeName();		//!< Get the event registered type name.
	const char*		GetComment();		//!< Get the comment for the event. Comments are not editable.
	int				GetThreadID();		//!< Get the thread ID used in the event execution.

	bool			IsSingleEvent();	//!< Three types of events exits: single, start and end. Some actions that takes more time to execute or when other events can occur inbetween are collected with start time event at begin and end time event at finish.
private:
	//@{
	//! Private constructor.
	FBProfileTimeEvent();
	//! Private copy constructor.
	FBProfileTimeEvent(const FBProfileTimeEvent &);
	//! Private assignment.
	FBProfileTimeEvent & operator =(const FBProfileTimeEvent &);
	//@}
};

//! Available Profiling modes.
enum FBProfilingMode
{
	kFBProfilingModeDisabled = 0,	//!< All profiling disabled, this include Viewer profiling. For the other modes, when EvaluationDepth is 0, only base information is profiled, such as FPS and evaluation rate. 
	kFBProfilingModeEvaluation,		//!< Collect profiling for all known evaluation tasks (default mode).
    kFBProfilingModeRendering,		//!< Collect profiling for all known rendering tasks. 
    kFBProfilingModeDevices,		//!< Collect profiling for device Input/Output and Device Evaluation. 
    kFBProfilingModeSDK,			//!< Collect profiling for SDK. 
    kFBProfilingModeAllLow,			//!< Collect profiling for all known tasks that doesn't increase remarkably with scene size. For large scenes this will not influence performance. 
    kFBProfilingModeAllHi			//!< Collect profiling for all known tasks . For large scenes there should be an influence on performance.
};

FB_DEFINE_ENUM(FBSDK_DLL, ProfilingMode);

////////////////////////////////////////////////////////////////////////////////////
// FBProfiler
////////////////////////////////////////////////////////////////////////////////////
/**	FBProfiler.
*	Central place to query profiling results and change profiling options.
*/
class FBSDK_DLL FBProfiler : public FBComponent {
	__FBClassDeclare( FBProfiler,FBComponent );
public:
	/**	Constructor.
	*	\param	pObject	For internal use only.
	*/
	FBProfiler(HIObject pObject=NULL);

	FBPropertyProfilingMode	ProfilingMode;		//!< <b>Read/Write Property:</b> Profiling collection modes, including disabling all profiling.
	FBPropertyInt			EvaluationDepth;	//!< <b>Read/Write Property:</b> Specify the depth of evaluation profiling for data collection (maximum value is 10).
	FBPropertyInt			BufferSize;			//!< <b>Read/Write Property:</b> Buffer size for average and timing computation (maximum value 200).
	FBPropertyBool			FrameReference;		//!< <b>Read/Write Property:</b> Draw task cycles in relation to main thread cycle time - frame cycle (percentage display).
	FBPropertyBool			ActiveSampling;		//!< <b>Read/Write Property:</b> Activate the sampling for time events. Call before quering for FBProfileTimeEvent.
	
	// Event samples.
	/**	Get number of time event samples collected during last sampling.
	*	\return Number of FBProfileTimeEvent samples gathered during sampling.
	*/
	int						GetEventSampleCount();
	/**	Only possible way to query collected FBProfileTimeEvent.
	*	\param	pIndex	Sample index.
	*	\return Sample object.
	*/
	FBProfileTimeEvent*		GetEventSample( int pIndex );
	/**	Get end time event for event at given index. This function and FBProfileTimeEvent.IsSingleEvent are useful to identify duration of event action.
	*	\param	pIndex	Sample index.
	*	\return Sample object if sample at given index is start sample.
	*/
	FBProfileTimeEvent*		GetEndEventSample( int pIndex );

	// Stats (for now only IO)
	
	/**	Stats are holding last execution time/duration of action. They are used for actions that doesn't appear frequently, like file IO.	
	*	\return Stats count. They are created when stat occurs, so open or save action needs to be done first to get any information stored in stats.
	*/
	int						GetStatCount();
	/**	Search for index of given stat name.
	*	\param	pName	Name of the sample that we are looking for.
	*	\return Stat index if found, -1 if not in the list.
	*/
	int						GetStatIndex(const char* pName);
	/**	Get information about what action is stat refering to.
	*	\param	pIndex	Index of stat.
	*	\return Stat name.
	*/
	const char*				GetStatName(int pIndex);
	/**	Get aditional information about what action is stat refering to.
	*	\param	pIndex	Index of stat.
	*	\return Stat comment.
	*/
	const char*				GetStatComment(int pIndex);

	/**	Get start time of action.
	*	\param	pIndex	Index of stat.
	*	\return Start time (in seconds).
	*/
	double					GetStatStart(int pIndex);

	/**	Get stop time of action.
	*	\param	pIndex	Index of stat.
	*	\return Stop time (in seconds).
	*/
	double					GetStatStop(int pIndex);

	/**	Get time that was spend on execution of action.
	*	\param	pIndex	Index of stat.
	*	\return Stat duration (in seconds).
	*/
	double					GetStatDuration(int pIndex);

	/**	Profiling collection can affect scene performace. This function return how costly is profiling.
	*	\return Cost of profiling the scene. (in mini seconds)
	*/
	double					GetProfilingCost();

	/**	Register a new task cycle for profiling. Pointer to name needs to stay valid during whole application session.
	*	\param	pUniqueName	Unique name for new task cycle
	*	\param	pColor	Color for new task cycle. Used in Profiling Center for drawing.
	*	\return	Index of task cycle. Will return -1 if failed. If task cycle is already registered it will return its index.
	*/
	static int				RegisterTaskCycle(const char* pUniqueName, float* pColor = NULL);

	/**	Test to see if a task cycle is already registered based on the name provided. Can also be used to verify if a name is free to be used, this included checking any conflicts with internal names.
	*	\param	pName	Task cycle name to test
	*	\return	True when name is used. False when name is not used.
	*/
	static bool				IsTaskCycleNameRegistered(const char* pName);

	/**	Get the global object for this class
	*	\return	the global object.
	*/
	static FBProfiler&		TheOne();
};

////////////////////////////////////////////////////////////////////////////////////
// FBProfilerHelper
////////////////////////////////////////////////////////////////////////////////////
/**	FBProfilerHelper.
*	Should be created in the plug-in file where the profiling is to occur. See the class description in FBProfileTaskCycle for more details.
*/
class FBSDK_DLL FBProfilerHelper
{
public:
	/**	Constructor.
	*	Profiling sample for task cycle will start here. This will create a profiling object to work with.
	*	\param	pTC_RegisterationIndex	Task Cycle registration index. Use FBProfiling_TaskCycleIndex to get this index.
	*	\param	pEvaluateInfo			Evaluation informantion for this profiling object. Required to correctly build task cycle hierarchy.
	*	\param	pParentTaskCycle		Optional, specify parent task cycles.
	*/
	FBProfilerHelper(int pTC_RegisterationIndex, FBEvaluateInfo* pEvaluateInfo, FBProfileTaskCycle* pParentTaskCycle = NULL);
	/**	Destructor.
	*	Profiling sample for task cycle will stop in here if not stopped before destruction.
	*/
	~FBProfilerHelper();
	
	//! Stop sample. Can be done manually, before destruction of the object.
	void Stop();

	//! Test to see if profiling is started. Useful to verify if profiling is in progress.
	inline bool IsStarted() { return mCurrentTaskCycle != NULL; }
private:
	//@{
	FBEvaluateInfo*		mEvaluateInfo;
	FBProfileTaskCycle*	mBackupTaskCycle;
	FBProfileTaskCycle*	mCurrentTaskCycle;
	//@}
};


////////////////////////////////////////////////////////////////////////////////////
// GLOBALS, for querying of FBProfileTaskCycle hierarchy or to be used in FBProfilerHelper constructor.
////////////////////////////////////////////////////////////////////////////////////
FBSDK_DLL FBProfileTaskCycle*	FBGetMainThreadTaskCycle();		//!< Get root task cycle.
FBSDK_DLL FBProfileTaskCycle*	FBGetRenderingTaskCycle();		//!< Get rendering task cycle.
FBSDK_DLL FBProfileTaskCycle*	FBGetEvaluationTaskCycle();		//!< Get evaluation task cycle.

#ifdef FBSDKUseNamespace
	}
#endif

#endif /* __FBPROFILER_H__ */
