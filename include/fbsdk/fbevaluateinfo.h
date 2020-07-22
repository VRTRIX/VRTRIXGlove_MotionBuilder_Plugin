#ifndef __FBEVALUATEINFO_H__
#define __FBEVALUATEINFO_H__
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

/** \file fbcore.h
*	Contains definitions for devices, boxes and models.
*/

#include <kaydaradef.h>
#ifndef FBSDK_DLL 
	/** \def FBSDK_DLL
	*	Be sure that FBSDK_DLL is defined only once...
	*/
	#define FBSDK_DLL K_DLLIMPORT
#endif

#include <fbsdk/fbtime.h>

// somebody at SGI defined this in their include files
// until we find which one, we remove it
#undef Status

#ifdef FBSDKUseNamespace
	namespace FBSDKNamespace {
#endif

FB_FORWARD( FBBox );
FB_FORWARD( FBAnimationNode );

////////////////////////////////////////////////////////////////////////////////////
// FBEvaluateInfo
////////////////////////////////////////////////////////////////////////////////////
FB_FORWARD( FBEvaluateInfo );

/** AnimationNodeNotify evaluation information.
*	This structure is passed to the AnimationNodeNotify calls
*	(in Constraints, Devices, and Boxes), giving the connectors
*	information with regards to the start or stop times of the
*	evaluation. In general, only the start time is of interest
*	for the current evaluation cycle. The advantage of the structure
*	is to have a common time for the evaluation of all the elements
*	in the scene.
*/
class FBSDK_DLL FBEvaluateInfo 
{
public:
	/**	Return local (scene) time.
	*	\return Local time.
	*/
	FBTime &GetLocalTime();

	/**	Return system time.
	*	\return System time.
	*/
	FBTime &GetSystemTime();

	/**	Is local time stopped? (ie: no animation).
	*	\return \b true if local time is stopped.
	*/
	bool IsStop();

	/**	Return the wanted timer sync count (internal or external).
	*	\return sync count or \b -1 if no sync is present
	*/
	int	GetSyncCount();

	/**	Return the wanted timer sync count (internal or external).
	*	\return sync count or \b -1 if no sync is present
	*/
	int GetEvaluationID();

	/**	Return the ID of the device requesting the evaluation.
	*	\return Device Id (0x00: Viewer, 0x01 .. 0x1F Devices, 0xFFF: Evaluation manager or plot)
	*/
	int GetDeviceID();

	/**	User in case of constraints that can be called from multiple thread should implement multi buffering system.
	*	\param	pBufferOwner	This should be always passed to get access to optimized buffer management.
	*	\return Buffer associated to this evaluation info.
	*	\note	For now there are no intentions to expose this into python, since it's not possible to create constraints in python.
	*/
	int GetBufferID(FBBox* pBufferOwner);
	
	/**	Return the source EvaluationInfo for background evaluation.
	*	\return Source EvaluationInfo
	*/
	FBEvaluateInfo*	GetSourceEvaluateInfo();

	/**	Return recursion level for given pConstraint
	*	\return recursion level.
	*/
	int	GetRecursionLevel(FBBox* pConstraint);

	/** Change local time 
	*	\param pTime	Assigned local time
	*/
	void Goto( FBTime pTime );
};

/** Get the displays evaluation information structure.
*	This function can be used in order to call real-time functions 
*	based on the current display evalution state.
*	\return The display evalution structure.
*/
FBSDK_DLL FBEvaluateInfo*	FBGetDisplayInfo();

/** Get the update evaluation information structure.
*	This function can be used in order to call real-time functions 
*	based on the current update evalution state.
*	\return The update evalution structure.
*/
FBSDK_DLL FBEvaluateInfo*	FBGetUpdateInfo();

//! Background Notification Function
typedef void (*kBackgroundEvaluationCallback)(const FBAnimationNode* pDst, const FBAnimationNode* pSrc, void* pCustomData);

#ifdef FBSDKUseNamespace
	}
#endif
#endif
