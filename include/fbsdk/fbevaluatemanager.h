#ifndef __FBEVALUATEMANAGER_H__
#define __FBEVALUATEMANAGER_H__
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

/**	\file fbevaluatemanager.h
*	This file contains evaluate manager interface
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

//! <b> DEPRICATED use ParallelEvaluation on FBEvaluateManager instead</b>Available DAG parallel schedule algorithm
enum FBParallelScheduleType
{
    kFBParallelScheduleSerial,      //!< No parallel schedule, use sequential evaluation order instead.
    kFBParallelScheduleSimple,      //!< Simple parallel schedule, mainly analyze the task dependency based on Motion Hierarchy (scene graph), but don't across active constraint. 
    kFBParallelScheduleAdvanced,    //!< Advanced parallel schedule, task dependency analyzation will be able to across ative constraint, and plus motion hierarchy. 
};

FB_DEFINE_ENUM(FBSDK_DLL, ParallelScheduleType);

/** Global Evaluation callback timing. 
*	Let the user to register callback function at different stage of background evaluation.
*/
enum FBGlobalEvalCallbackTiming
{
    kFBGlobalEvalCallbackBeforeDAG,		//!< Invoked before any DAG (Transformation & Deformation) evaluation tasks started in evaluation pipeline / thread.
    kFBGlobalEvalCallbackAfterDAG,		//!< Invoked after all DAG (Transformation & Deformation) evaluation tasks finished in evaluation pipeline / thread. 
    kFBGlobalEvalCallbackAfterDeform,	//!< Invoked after all deformation tasks finsished in evaluation pipeline / thread. 
    kFBGlobalEvalCallbackSyn,           //!< Invoked when both evluation & rendering pipelines / threads are stopped. Useful for some complicated scene change tasks to avoid race condition. 
    kFBGlobalEvalCallbackBeforeRender,  //!< Invoked in rendering pipleline, before any rendering tasks start (immediately after clearing GL back buffer).
    kFBGlobalEvalCallbackAfterRender    //!< Invoked in rendering pipleline, after any rendering tasks finsish (just before swapping GL back/front buffer).
};

typedef void (*kFBEvaluationGlobalFunctionCallback)(FBEvaluateInfo* pEvaluteInfo);

//! \b Event: Global Evaluation pipeline critical timing callback event.
class FBSDK_DLL FBEventEvalGlobalCallback: public FBEvent 
{
public:
    /**	Constructor.
    *	\param pEvent Base event (internal) to obtain information from.
    */
    FBEventEvalGlobalCallback( HKEventBase pEvent );	

    /** Get Callback Timing. */
    FBGlobalEvalCallbackTiming GetTiming() const;
};

//! \b PropertyEvent: Callback at evaluation pipeline (for kFBGlobalEvalCallbackBeforeDAG, kFBGlobalEvalCallbackAfterDAG and kFBGlobalEvalCallbackAfterDeform)
class FBSDK_DLL FBPropertyEventCallbackEvalPipeline : public FBPropertyEvent
{
public:
    virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
    virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
};

//! \b PropertyEvent: Callback at evaluation pipeline (for kFBGlobalEvalCallbackBeforeRender, kFBGlobalEvalCallbackBeforeRender)
class FBSDK_DLL FBPropertyEventCallbackRenderPipeline : public FBPropertyEvent
{
public:
    virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
    virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
};

//! \b PropertyEvent: Callback at synchronization point (for kFBGlobalEvalCallbackSyn)
class FBSDK_DLL FBPropertyEventCallbackSynPoint : public FBPropertyEvent
{
public:
    virtual void Add	( HICallback pOwner, kICallbackHandler pHandler );
    virtual void Remove	( HICallback pOwner, kICallbackHandler pHandler );
};

/**	Evaluate Manager.
*	Interface to schedule the DAG (Directed Acyclic Graph) tasks to multi-core/CPU (or GPU) to accelerate 
*   evaluate process. Provide callback on some critical paths / times to allow customize the application. 
*/
__FB_FORWARD( FBEvaluateManager );
class FBSDK_DLL FBEvaluateManager : public FBComponent 
{
    __FBClassDeclare( FBEvaluateManager,FBComponent );

    /**	Constructor.
    *   Protected constructor, use TheOne() access instead. 
    *	\param	pObject		Internal parent object(default=NULL).
    */
    FBEvaluateManager(HIObject pObject=NULL);

public:
    FBPropertyBool                  ParallelPipeline;            //!< <b>Read/Write Property:</b> true if transformation is evaluated in parallel.
    FBPropertyBool                  ParallelDeformation;         //!< <b>Read/Write Property:</b> true if deformation is evaluated in parallel.
    FBPropertyBool                  UseGPUDeformation;           //!< <b>Read/Write Property:</b> true if GPU deformation is used.
    FBPropertyBool                  FrameSkipOptimization;       //!< <b>Read/Write Property:</b> if true, apply frame skip optimization during playback. off-line rendering don't use frame skip optimization.
    FBPropertyParallelScheduleType  ParallelScheduleType;        //!< <b> DEPRICATED </b><b>Read/Write Property:</b> choose between serial and parallel DAG schedule algorithm. kFBParallelScheduleSimple and kFBParallelScheduleAdvanced will set ParallelEvalution to true. kFBParallelScheduleSerial will set ParallelEvalution to false
    FBPropertyBool                  ParallelEvaluation;          //!< <b>Read/Write Property:</b> true if parallel DAG schedule algorithm is being used. false when serial algorithm is being used.

    FBPropertyInt                   NodeCount;        	         //!< <b>Read only Property:</b> Number of nodes to evaluate.
    FBPropertyInt                   DeviceCount;			     //!< <b>Read only Property:</b> Number of devices to evaluate.

    //! Invalidate the DAG and trigger parallel scheduling at the next frame.
    void InvalidateDAG();

    /** Check if the application main loop is in interactive or offline render mode.
    *   \return true if is application is is interactive mode.
    */
    bool IsInteractiveMode() const;

    /** \name Callback function management for critical timing in the pipeline.
    *       User could register two set of callback functions, one is to use global free function 
    *       via RegisterEvaluationGlobalFunction / UnregisterEvaluationGlobalFunction, the other 
    *       is to use class (with ICallback interface) member function via FBPropertyEvent 
    *       (OnEvaluationPipelineEvent, OnRenderingPipelineEvent and OnSynchronizationEvent). 
    *       Global free functions will be called first before all registered ICallback member functions. 
    *       Users are expected to use these per frame callback for lightweight tasks, otherwise 
    *       performance may be dropped. 
    */
    //@{

    /** Register free callback function to critical timings / stages in the pipeline.
    *	\param pCallback	free function to be registered
    *	\param pTiming		callback timing to be registered
    *   \note  Global callback functions calling order is same as registration order, which is different from FBPropertyEvent callbacks. 
    */
    void RegisterEvaluationGlobalFunction  (kFBEvaluationGlobalFunctionCallback pCallback, FBGlobalEvalCallbackTiming pTiming);

    /** Register free callback function to critical timings / stages in the pipeline.
    *	\param pCallback	free callback to be unregistered
    *	\param pTiming		callback timing to be unregistered
    */
    void UnregisterEvaluationGlobalFunction(kFBEvaluationGlobalFunctionCallback pCallback, FBGlobalEvalCallbackTiming pTiming);

    /** <b> For callback events at evaluation pipeline.</b> 
    *   This callback will be invoked from different thread than the main thread in parallel pipeline setup. 
    *   And this property is not exposed to pyfbsdk because pyfbsdk doesn't support multi-thread properly yet.
    */
    FBPropertyEventCallbackEvalPipeline     OnEvaluationPipelineEvent;   
    FBPropertyEventCallbackRenderPipeline   OnRenderingPipelineEvent;    //!< <b> For callback events at rendering pipeline.</b>
    FBPropertyEventCallbackSynPoint         OnSynchronizationEvent;      //!< <b> For callback events at synchronization point.</b>

    //@}

    /**	Get the global object for this class
    *	\return	the global object.
    */
    static FBEvaluateManager& TheOne();
};


/**	Debug function for MT dependency debug.
*	When enabled log file will be created and updated each time MultiThreaded scheduling is happening (scene rebuild)
*	\param	pEnable	ON/OFF switch. This is not stored in config (should be changed only for debug purpose, because slow down rebuild process )
*/
FBSDK_DLL void FBSchedulingDependencyOutput( bool pEnable );

#ifdef FBSDKUseNamespace
} // namespace FBSDKNamespace
#endif

#endif