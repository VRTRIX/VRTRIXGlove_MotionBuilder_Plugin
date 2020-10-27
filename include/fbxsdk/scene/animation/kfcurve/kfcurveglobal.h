/****************************************************************************************
 
   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.
 
   This computer source code and related instructions and comments are the unpublished
   confidential and proprietary information of Autodesk, Inc. and are protected under
   applicable copyright and trade secret law.  They may not be disclosed to, copied or
   used by any third party without the prior written consent of Autodesk, Inc.
 
****************************************************************************************/

//! \file kfcurveglobal.h
#ifndef _FBXSDK_SCENE_ANIMATION_KFCURVE_GLOBAL_H_
#define _FBXSDK_SCENE_ANIMATION_KFCURVE_GLOBAL_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxarray.h>
#include <fbxsdk/core/base/fbxtime.h>
#include <fbxsdk/scene/animation/kfcurve/kfcurve.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxMultiMap;
class KFCurveNode;

/*****************************************************************************************************************************
** WARNING! Anything beyond these lines is for internal use, may not be documented and is subject to change without notice! **
*****************************************************************************************************************************/
#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define KFCURVE_INTEPOLATION_INFINITE 1000
#define KFCURVE_OVERSHOOT_INTERPOLATION 500.0 

/**KSmartPlotOptions
*/
class FBXSDK_DLL KSmartPlotOptions
{

public: 

	//! Enable the SmartPlot
	bool	mUseSmartPlot;

	//! Enable the Break Tangent post plot operation (these settings will also be used by the fidelity check)
	bool	mUseBreakTangent;
	double	mBreakTangentThreshold;
	FbxTime	mEpsilonTime;

	//! Enable the Increase Fidelity post plot operation
	bool	mUseIncreaseFidelity;
	double	mFidelityTolerance;
	bool	mFidelityUseBreakTangent;
	int		mFidelitySegmentCount;
	bool	mFidelitySyncAddedKeys;

	//! Use the reference curve as the result instead of the smart plot curve. Used for debug. Is also the most exact plot we can have in MB.
	bool	mShowReferenceCurve;

	//! Constructor. All values will be set to default.
	KSmartPlotOptions();
};

/**KMergeLayerOptions
  */
class FBXSDK_DLL KMergeLayerOptions
{

public: 

	//! Start time. Merge in this interval.
	FbxTime mStart;

    //! Stop time. Merge in this interval.
	FbxTime mStop;
	
	//! Plot period. Used only when not smart plotting.
	FbxTime mPlotPeriod;

	//! Smart Merge options
	KSmartPlotOptions mSmartPlotOptions;

	//! Constructor. All values will be set to default.
	KMergeLayerOptions();
};

// TimeWarp Utility

//!
FBXSDK_DLL void KFCurve_SetTWSet (FbxMultiMap* pSet);

//!
FBXSDK_DLL KFCurveNode* KFCurve_FindTWFromNickNumber (int pNickNumber);

//!
FBXSDK_DLL bool KFCurve_FindNickNumberFromTW (int& pNickNumber, KFCurveNode* pTWNode);

// ControlCurve Utility

enum 
{	
//	eKFCURVE_PLOT_SourceCurvesKeep					= 1<<0 ,
	eKFCURVE_PLOT_SourceCurvesDestroy				= 1<<1 ,
	eKFCURVE_PLOT_SourceCurvesZeroDuringPlotTime	= 1<<2 ,
	eKFCURVE_PLOT_DestinationCurveMergeWithResult	= 1<<3 ,
	eKFCURVE_PLOT_DestinationCurveReplaceByResult	= 1<<4 ,
	eKFCURVE_PLOT_ForCache							= 1<<5 ,
};

/** Plots inside a curve node. 
*
*	Plot is risky for rotations because they are not commutative, so make sure
*	layers to be plot are successive !!!
*
*	\param pParentNode				The node containing all layers.
*	\param pSourceLayers			Layers to be plotted.
*	\param pDestLayer				Layers to be plotted on this layer.
*	\param pOptions				Flags  to set the behavior.
*	\param pStart					Start time of the plot.
*	\param pStop					Stop  time of the plot.
*   \param pPlotPeriod
*   \param pDestinationNode
*   \param pTotalNode
*   \param pUseTimeWarp
*   \param pSmartPlotOptions
*/
FBXSDK_DLL void KFCurve_PlotInLayers 
(	
	KFCurveNode* pParentNode, 
	FbxArray<int> *pSourceLayers, // if pointer is NULL, all layers are considered
	int pDestLayer,
	FbxUInt pOptions, 
	FbxTime pStart, 
	FbxTime pStop, 
	FbxTime pPlotPeriod,
	KFCurveNode* pDestinationNode,
	KFCurveNode* pTotalNode,	// If this node is set, function calculates layer to 
	bool pUseTimeWarp,
	KSmartPlotOptions* pSmartPlotOptions = NULL
);

/******************************************************************/
//
//	Helpers
//
/******************************************************************/

// Vectorial conversions tools

/** Calculate the euler rotation required to align axis pAB-pA on pAB-pB.
*	\param pAB		The intersection of the 2 axis.
*	\param pA		A point on axis to be aligned.
*	\param pB		A point on reference axis.
*	\param pAngles Resulting euler angles.
*	\return how the operation succeed.
*/
FBXSDK_DLL bool AxisAlignmentInEulerAngle(double pAB[3], double pA[3], double pB[3], double pAngles[3]);

// bob 23-05-2001 - old call found in kmodelutility are forwarded to those one
FBXSDK_DLL FbxTime	KFCURVE_GetPlotPeriod();
FBXSDK_DLL void	KFCURVE_SetPlotPeriod(FbxTime pPlotPeriod);

//
//	For plotting to be on frame or free... i.e. start at the beginning of the take or on frame.
//
FBXSDK_DLL bool	KFCURVE_GetPlotOnFrame();
FBXSDK_DLL void	KFCURVE_SetPlotOnFrame( bool pPlotOnFrame );

//
// bob 23-05-2001 - the rotation correction filter that should be applied after a plot
//
enum { KFCurveApplyNone = 0, KFCurveApplyGimbleKiller, KFCurveApplyUnroll };

FBXSDK_DLL int		KFCURVE_GetRotationFilterToApply();
FBXSDK_DLL void	KFCURVE_SetRotationFilterToApply(int pRotationFilterToApply);
FBXSDK_DLL void	KFCURVE_ApplyRotationFilter( KFCurveNode* pCurveNode, FbxTime pStart	= FBXSDK_TIME_MINUS_INFINITE, FbxTime pStop	= FBXSDK_TIME_INFINITE );

FBXSDK_DLL double	KFCURVE_GetRotationFilterUnrollQuality();
FBXSDK_DLL void	KFCURVE_SetRotationFilterUnrollQuality( double pQuality );

FBXSDK_DLL bool	KFCURVE_GetRotationFilterUnrollTestForPath();
FBXSDK_DLL void	KFCURVE_SetRotationFilterUnrollTestForPath( bool pTestForPath );

FBXSDK_DLL double	KFCURVE_GetButterworthFilterInternalRate();
FBXSDK_DLL void	KFCURVE_SetButterworthFilterInternalRate( double pButterworthFilterInternalRate );

//
// the constant key reducer to be applied on Plot
//
FBXSDK_DLL bool	KFCURVE_GetUseConstantKeyReducer();
FBXSDK_DLL void	KFCURVE_SetUseConstantKeyReducer( bool pUseConstantKeyReducer );
FBXSDK_DLL void   KFCURVE_ApplyConstantKeyReducer( KFCurveNode* pCurveNode, FbxTime pStart	= FBXSDK_TIME_MINUS_INFINITE, FbxTime pStop	= FBXSDK_TIME_INFINITE );
//
// keep at least one key after applying the filter (else, there will only be a candidate on the curve)
//
FBXSDK_DLL bool	KFCURVE_GetConstantKeyReducerKeepOneKey();
FBXSDK_DLL void	KFCURVE_SetConstantKeyReducerKeepOneKey( bool pConstantKeyReducerKeepOneKey );

//
// the constant key reducer to be applied on Device record
//
FBXSDK_DLL bool	KFCURVE_GetUseConstantKeyReducerOnDevices();
FBXSDK_DLL void	KFCURVE_SetUseConstantKeyReducerOnDevices( bool pUseConstantKeyReducerOnDevices );

//
FBXSDK_DLL double	KFCURVE_GetUseConstantKeyReducerTranslationThreshold();
FBXSDK_DLL void	KFCURVE_SetUseConstantKeyReducerTranslationThreshold( double pConstantKeyReducerTranslationThreshold );

//
FBXSDK_DLL double	KFCURVE_GetUseConstantKeyReducerRotationThreshold();
FBXSDK_DLL void	KFCURVE_SetUseConstantKeyReducerRotationThreshold( double pConstantKeyReducerRotationThreshold );

//
FBXSDK_DLL double	KFCURVE_GetUseConstantKeyReducerScalingThreshold();
FBXSDK_DLL void	KFCURVE_SetUseConstantKeyReducerScalingThreshold( double pConstantKeyReducerScalingThreshold );

//
FBXSDK_DLL double	KFCURVE_GetUseConstantKeyReducerDefaultThreshold();
FBXSDK_DLL void	KFCURVE_SetUseConstantKeyReducerDefaultThreshold( double pConstantKeyReducerDefaultThreshold );

//
// tell if we should "Plot Translation On Root Only" or not (Antoine 2003-05-02)
//
FBXSDK_DLL bool	KFCURVE_GetPlotTranslationOnRootOnly();
FBXSDK_DLL void	KFCURVE_SetPlotTranslationOnRootOnly( bool pPlotTranslationOnRootOnly );

//
FBXSDK_DLL bool KFCURVE_GetPreciseTimeDiscontinuities();
FBXSDK_DLL void KFCURVE_SetPreciseTimeDiscontinuities( bool pPreciseTimeDiscontinuities );

//
FBXSDK_DLL bool KFCURVE_GetTCB4051EvalMode();
FBXSDK_DLL void KFCURVE_SetTCB4051EvalMode( bool pTCB4051EvalMode );

// Functions to convert bezier tan to the new automatic parametrisation
FBXSDK_DLL void KFCURVE_ComputeAutoFromBezier(double &pLeftParam, double &pRightParam, double &pLeftTan,   double &pRightTan,   double &pToLeftKey, double &pToRightKey);
FBXSDK_DLL void KFCURVE_ComputeBezierFromAuto(double &pLeftTan,   double &pRightTan,   double &pLeftParam, double &pRightParam, double &pToLeftKey, double &pToRightKey);

FBXSDK_DLL void KFCURVE_ComputeLeftAutoFromBezier(double &pLeftParam, double &pLeftTan,   double &pToLeftKey, double &pToRightKey);
FBXSDK_DLL void KFCURVE_ComputeLeftBezierFromAuto(double &pLeftTan,   double &pLeftParam, double &pToLeftKey, double &pToRightKey);

FBXSDK_DLL void KFCURVE_ComputeRightAutoFromBezier(double &pRightParam, double &pRightTan,   double &pToLeftKey, double &pToRightKey);
FBXSDK_DLL void KFCURVE_ComputeRightBezierFromAuto(double &pRightTan,	  double &pRightParam, double &pToLeftKey, double &pToRightKey);

FBXSDK_DLL void KFCURVE_ComputeAutoFromBezierForKey(double &pLeftParam, double &pRightParam, double &pLeftTan,   double &pRightTan,   KFCurve* pCurve, int pIndex);
FBXSDK_DLL void KFCURVE_ComputeBezierFromAutoForKey(double &pLeftTan,   double &pRightTan  , double &pLeftParam, double &pRightParam, KFCurve* pCurve, int pIndex);

FBXSDK_DLL void KFCURVE_ComputeLeftAutoFromBezierForKey(double &pLeftParam, double &pLeftTan,   KFCurve* pCurve, int pIndex);
FBXSDK_DLL void KFCURVE_ComputeLeftBezierFromAutoForKey(double &pLeftTan,   double &pLeftParam, KFCurve* pCurve, int pIndex);

FBXSDK_DLL void KFCURVE_ComputeRightAutoFromBezierForKey(double &pRightParam, double &pRightTan,   KFCurve* pCurve, int pIndex);
FBXSDK_DLL void KFCURVE_ComputeRightBezierFromAutoForKey(double &pRightTan  , double &pRightParam, KFCurve* pCurve, int pIndex);

FBXSDK_DLL void KFCURVE_ComputeToLeftAndToRight(double &pToLeft, double &pToRight, KFCurve* pCurve , int pIndex);
FBXSDK_DLL void KFCURVE_ComputeProgressiveClampedTangents(double& pLeftTangent, double& pRightTangent, KFCurve* pCurve, int pIndex);

/** Compare the FCurve with the reference FCurve and break the tangents when necessary so that both FCurves match.
* \param pFCurveNode			FCurveNode to modify.
* \param pReferenceFCurveNode	FCurveNode we use as the reference.
* \param pEpsilonTime			Epsilon time used to evaluate the tangents.
* \param pTangentThreshold	Threshold used when comparing tangents. If the difference is over the threshold, we break the tangent.
*/
FBXSDK_DLL void KFCURVE_BreakTangents( KFCurveNode* pFCurveNode, KFCurveNode* pReferenceFCurveNode, FbxTime pEpsilonTime, double pTangentThreshold );

FBXSDK_DLL void KFCURVE_ComputeTCBFromBezierForKey( double &pT, double &pC ,double &pB , double pLTan, double pRTan, KFCurve* pCurve, int pIndex );

/** Compare the FCurve with the reference FCurve and add keys when necessary so that both FCurves match.
* \param pFCurveNode					FCurveNode to modify.
* \param pReferenceFCurveNode			FCurveNode we use as the reference.
* \param pFidelityThreshold			Threshold used when comparing values. If the difference is over the threshold, we add a new key.
* \param pSegmentCount				Number of segments we divide the curve between every pairs of keys.
* \param pBreakTangents				True if we should break the tangents when they don't match the reference.
* \param pEpsilonTime					Epsilon time used to evaluate the tangents.
* \param pTangentThreshold			Threshold used when comparing tangents. If the difference is over the threshold, we break the tangent.
* \param pSyncAddedKeys				True if fidelity keys should be added to all FCurves of a vector.
* \param pSyncWithFCurves				For internal use, leave to NULL.
* \param pSyncWithReferenceFCurves	For internal use, leave to NULL.
*/
FBXSDK_DLL void KFCURVE_IncreaseFidelity( KFCurveNode* pFCurveNode, KFCurveNode* pReferenceFCurveNode, double pFidelityThreshold, int pSegmentCount, bool pBreakTangents, FbxTime pEpsilonTime, double pTangentThreshold, bool pSyncAddedKeys = false, FbxArray<KFCurve*>* pSyncWithFCurves = NULL, FbxArray<KFCurve*>* pSyncWithReferenceFCurves = NULL );


/**  Determined if all the keys in the underlying KFCurveNode have the same interpolation type
* \param pFCurveNode		FCurveNode to check.
* \param pInterpolation	The interpolation type we are querying for.
* \param pAllLayer		True if check is in all layers.
* \return					True if the all all have pInterpolation type.
*/
FBXSDK_DLL bool KFCURVE_IsAllSameInterpolation( KFCurveNode* pFCurveNode, kFCurveInterpolation pInterpolation, bool pAllLayer);

/** Smart merge version for curves that have only constant keys. The current implementation of SmartMerge does not work very well with
* different types of constant keys.
* \param pDstNode		The Destination KFCurveNode in which all layers will be merged.
* \param pSrcNode		Multi-layered KFCurveNode that has to be merged
* \param pStart		Merge start time
* \param pStop		Merge stop time
*/
FBXSDK_DLL void KFCURVE_ConstantCurveMerge(KFCurveNode* pDstNode,KFCurveNode* pSrcNode, FbxTime pStart, FbxTime pStop);

#endif /* !DOXYGEN_SHOULD_SKIP_THIS *****************************************************************************************/

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_ANIMATION_KFCURVE_GLOBAL_H_ */
