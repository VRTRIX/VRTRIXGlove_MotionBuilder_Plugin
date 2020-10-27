#ifndef pyfbglobal_h__
#define pyfbglobal_h__
/**************************************************************************
 Copyright 2010 Autodesk, Inc.
 All rights reserved.
 
 Use of this software is subject to the terms of the Autodesk license agreement
 provided at the time of installation or download, or which otherwise accompanies
 this software in either electronic or hard copy form.
 
**************************************************************************/

#include <kaydaradef.h>
#ifndef PYSDK_DLL
	/** \def PYSDK_DLL
	*	Be sure that PYSDK_DLL is defined only once...
	*/
	#define PYSDK_DLL K_DLLIMPORT
#endif

#include "pyfbmatrix.h"
#include "pyfbevaluateinfo.h"
#include "pyfbfcurve.h"
#include "pyfbanimationnode.h"
#include "pyfbbox.h"
#include "pyfbgeometry.h"
#include "pyfbmodel.h"
#include "pyfbarraytemplate.h"	// Requires FBModel_Wrapper from class_f_b_model_gen.h.
#include "pyfbprofiletaskcycle.h"
#include "pyfbevaluateinfo.h"

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTIONS: 
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// Globals Initializer
void FBGlobal_Init();

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetMultiLangText
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline  const char* FBGetMultiLangText_Wrapper_1( const FBPlug_Wrapper* pContext, const char* pKey, bool pFlagReturnKey = false )
{
    return FBGetMultiLangText( pContext ? pContext->mFBPlug : NULL, pKey, pFlagReturnKey ); 
}

PYSDK_DLL inline  const char* FBGetMultiLangText_Wrapper_2( const char* pContext, const char* pKey, bool pFlagReturnKey = false )
{
    return FBGetMultiLangText( pContext, pKey, pFlagReturnKey ); 
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBConnect
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline bool FBConnect_Wrapper( FBPlug_Wrapper* pSrc, FBPlug_Wrapper* pDst, FBConnectionType pConnectionType=kFBConnectionTypeNone )
{
    return FBConnect( pSrc ? pSrc->mFBPlug : 0, pDst ? pDst->mFBPlug : 0, pConnectionType );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBDisconnect
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline bool FBDisconnect_Wrapper( FBPlug_Wrapper* pSrc, FBPlug_Wrapper* pDst )
{
    return FBDisconnect( pSrc ? pSrc->mFBPlug : 0, pDst ? pDst->mFBPlug : 0 );
}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBSleep
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBSleep_Wrapper( unsigned long pMilliseconds )
{
    FBSleep( pMilliseconds );
};

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBSchedulingDependencyOutput
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBSchedulingDependencyOutput_Wrapper( bool pEnable )
{
	FBSchedulingDependencyOutput( pEnable );
};


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBFindModelByLabelName
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
class FBModel_Wrapper;
PYSDK_DLL object FBModel_Wrapper_Factory( FBModel* );

inline object FBFindModelByLabelName_Wrapper( const char* pLabelName )
{
    return FBModel_Wrapper_Factory( FBFindModelByLabelName( pLabelName ));
};

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBFindModelByUniqueColorId
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

inline tuple FBFindModelByUniqueColorId_Wrapper( const FBColor_Wrapper& pColor )
{
    int lSubItemIndex = -1;
    object lModel = FBModel_Wrapper_Factory( FBFindModelByUniqueColorId( *pColor.mFBColor,  &lSubItemIndex ));
    return make_tuple(lModel, lSubItemIndex); 
};

#if !defined(K_DISABLE_UI)
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBPopNormalTool
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline bool FBPopNormalTool_Wrapper( const char* pName, bool pSetFocus = true )
{
    return FBPopNormalTool( pName, pSetFocus );
};
#endif

#ifndef K_QUICKTIME_PLUGIN
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBLoadFbxPrimitivesModel
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class FBModel_Wrapper;
PYSDK_DLL inline object FBLoadFbxPrimitivesModel_Wrapper( const char* pName )
{
    return FBModel_Wrapper_Factory( FBLoadFbxPrimitivesModel( pName ) );
};
#endif


PYSDK_DLL inline object FBCreateObject_Wrapper( const char* pGroupName, const char* pEntryName, const char* pName, int nth = 0 )
{
    return FBWrapperFactory::TheOne().WrapFBObject(FBCreateObject( pGroupName, pEntryName, pName, NULL, nth ));
}

PYSDK_DLL inline  int			FBObject_GetGroupCount_Wrapper          ()                  { return FBObject_GetGroupCount(); }
PYSDK_DLL inline  const char*	FBObject_GetGroupName_Wrapper           ( int pGroupIndex ) { return FBObject_GetGroupName( pGroupIndex); }
PYSDK_DLL inline  int			FBObject_GetEntryCount_Wrapper          ( int pGroupIndex ) { return FBObject_GetEntryCount( pGroupIndex); }
PYSDK_DLL inline  const char*	FBObject_GetEntryName_Wrapper           ( int pGroupIndex, int pIndex )              { return FBObject_GetEntryName( pGroupIndex, pIndex ); }
PYSDK_DLL inline  const char*	FBObject_GetEntryDescription_Wrapper    ( int pGroupIndex, int pIndex, int nth = 0 ) { return FBObject_GetEntryDescription( pGroupIndex, pIndex, nth); }
PYSDK_DLL inline  const char*	FBObject_GetEntryDLLName_Wrapper        ( int pGroupIndex, int pIndex, int nth = 0 ) { return FBObject_GetEntryDLLName(pGroupIndex, pIndex, nth); }
PYSDK_DLL inline  const char*	FBObject_GetIconName_Wrapper            ( int pGroupIndex, int pIndex, int nth = 0 ) { return FBObject_GetIconName( pGroupIndex, pIndex, nth); }
PYSDK_DLL inline  bool			FBObject_GetMultiplicity_Wrapper        ( int pGroupIndex, int pIndex, int nth = 0 ) { return FBObject_GetMultiplicity( pGroupIndex, pIndex, nth); }

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetSelectedModels
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class FBModelList_Wrapper;
class FBModel_Wrapper;
PYSDK_DLL inline void FBGetSelectedModels_Wrapper( FBModelList_Wrapper& pList, FBModel_Wrapper* pParent=NULL, bool pSelected=true, bool pSortBySelectOrder = false )
{
    FBGetSelectedModels( *pList.mFBModelList, pParent ? (pParent->mFBModel) : NULL, pSelected, pSortBySelectOrder );
}

PYSDK_DLL inline void FBFindObjectsByName_Wrapper( const char* pNameSpaceName, FBComponentList_Wrapper& pList,  bool pIncludeNamespace = true, bool pModelsOnly = false )
{
    FBFindObjectsByName ( pNameSpaceName, *pList.mFBObjectList, pIncludeNamespace, pModelsOnly );
}

PYSDK_DLL inline int FBDeleteObjectsByName_Wrapper( const char* pNamePattern, const char* pNameSpace = NULL, const char* pGroupName = NULL)
{
    return FBDeleteObjectsByName( pNamePattern, pNameSpace, pGroupName );
}

inline object FBFindObjectByFullName_Wrapper( const char* pObjectFullName )
{
    return FBWrapperFactory::TheOne().WrapFBObject( FBFindObjectByFullName ( pObjectFullName ) );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBMergeTransactionBegin, FBMergeTransactionEnd
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBMergeTransactionBegin_Wrapper()
{
    FBMergeTransactionBegin();
}

PYSDK_DLL inline void FBMergeTransactionEnd_Wrapper()
{
    FBMergeTransactionEnd();
}

PYSDK_DLL inline bool FBMergeTransactionIsOn_Wrapper()
{
    return FBMergeTransactionIsOn();
}

PYSDK_DLL inline void FBMergeTransactionFileRefEditBegin_Wrapper()
{
    FBMergeTransactionFileRefEditBegin();
}

PYSDK_DLL inline void FBMergeTransactionFileRefEditEnd_Wrapper()
{
    FBMergeTransactionFileRefEditEnd();
}

PYSDK_DLL inline bool FBMergeTransactionFileRefEditIsOn_Wrapper()
{
    return FBMergeTransactionFileRefEditIsOn();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBTrace
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline void FBTraceSetLevel_Wrapper( unsigned int pNewLevel )
{
    FBTraceSetLevel(pNewLevel);
}

PYSDK_DLL inline unsigned int FBTraceGetLevel_Wrapper()
{
    return FBTraceGetLevel();
}

PYSDK_DLL inline void FBTrace_Wrapper( const char* pMessage)
{
    FBTrace("%s",pMessage);
}

PYSDK_DLL inline void FBTraceWithLevel_Wrapper( unsigned int pLevel, const char* pMessage)
{
    FBTraceWithLevel(pLevel, "%s", pMessage);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBObjectLifeLogEnable
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline  void FBObjectLifeLogEnable_Wrapper(bool pEnable)
{
    FBObjectLifeLogEnable(pEnable);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBObjectGetGlobalUniqueId
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline  unsigned int  FBObjectGetGlobalUniqueId_Wrapper()
{
    return FBObjectGetGlobalUniqueId();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBObjectPrintLivings
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline  void FBObjectPrintLivings_Wrapper(unsigned int pStartUniqueId)
{
    FBObjectPrintLivings(pStartUniqueId);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBObjectGetLivingCount
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline  unsigned int  FBObjectGetLivingCount_Wrapper()
{
    return FBObjectGetLivingCount();
}

#if !defined(K_DISABLE_UI)
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBMessageBox
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline int FBMessageBox_Wrapper( const char* pBoxTitle, const char* pMessage, const char* pButton1Str, const char* pButton2Str=0, const char* pButton3Str=0, int pDefaultButton=0, int pScrolledMessage=0 )
{
    return FBMessageBox( pBoxTitle, pMessage, pButton1Str, pButton2Str, pButton3Str, pDefaultButton, pScrolledMessage );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBMessageBoxWithCheck
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL tuple FBMessageBoxWithCheck_Wrapper( const char* pBoxTitle, const char* pMessage, const char* pButton1Str, const char* pButton2Str, const char* pButton3Str, const char* pCheckBoxStr, bool pCheckBoxValue, int pDefaultButton=0 , int pScrolledMessage=0 );

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBMessageBoxGetUserValue
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL tuple FBMessageBoxGetUserValue_Wrapper( const char* pBoxTitle, const char* pMessage, object pValue, FBPopupInputType pValueType, const char* pButton1Str, const char* pButton2Str=0, const char* pButton3Str=0, int pDefaultButton=0, bool pLastButtonCancel = true );
#endif

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBModelTransactionBegin
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBModelTransactionBegin_Wrapper()
{
    FBModelTransactionBegin();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBModelTransactionEnd
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline void FBModelTransactionEnd_Wrapper()
{
    FBModelTransactionEnd();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_GetDefaultFormat
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBAudioFmt FBAudioFmt_GetDefaultFormat_Wrapper()
{
    return FBAudioFmt_GetDefaultFormat();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_AppendFormat
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBAudioFmt FBAudioFmt_AppendFormat_Wrapper( FBAudioFmt pDestFormat, int pChannels, int pBits, int pRate )
{
    return FBAudioFmt_AppendFormat( pDestFormat, pChannels, pBits, pRate );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_AppendFormat
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBAudioFmt FBAudioFmt_AppendFormat_Wrapper( FBAudioFmt pDestFormat, FBAudioFmt pSrcFormat )
{
    return FBAudioFmt_AppendFormat( pDestFormat, pSrcFormat );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_RemoveFormat
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBAudioFmt FBAudioFmt_RemoveFormat_Wrapper( FBAudioFmt pFormat, int pChannels, int pBits, int pRate )
{
    return FBAudioFmt_RemoveFormat( pFormat, pChannels, pBits, pRate );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_RemoveFormat
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBAudioFmt FBAudioFmt_RemoveFormat_Wrapper( FBAudioFmt pDestFormat, FBAudioFmt pSrcFormat )
{
    return FBAudioFmt_RemoveFormat( pDestFormat, pSrcFormat );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_GetChannelValue
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline int FBAudioFmt_GetChannelValue_Wrapper( FBAudioFmt pFormat )
{
    return FBAudioFmt_GetChannelValue( pFormat );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_GetBitsValue
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline int FBAudioFmt_GetBitsValue_Wrapper( FBAudioFmt pFormat )
{
    return FBAudioFmt_GetBitsValue( pFormat );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_GetBytesValue
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline int FBAudioFmt_GetBytesValue_Wrapper( FBAudioFmt pFormat )
{
    return FBAudioFmt_GetBytesValue( pFormat );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_GetRateValue
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline int FBAudioFmt_GetRateValue_Wrapper( FBAudioFmt pFormat )
{
    return FBAudioFmt_GetRateValue( pFormat );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_TestFormat
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline bool FBAudioFmt_TestFormat_Wrapper( FBAudioFmt pSrcFormat, int pChannels, int pBits, int pRate )
{
    return FBAudioFmt_TestFormat( pSrcFormat, pChannels, pBits, pRate );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_ConvertChannelMode
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBAudioFmt FBAudioFmt_ConvertChannelMode_Wrapper( FBAudioChannelMode pChannelMode )
{
	return FBAudioFmt_ConvertChannelMode( pChannelMode );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_ConvertBitDepthMode
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBAudioFmt FBAudioFmt_ConvertBitDepthMode_Wrapper( FBAudioBitDepthMode pBitDepthMode )
{
	return FBAudioFmt_ConvertBitDepthMode( pBitDepthMode );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBAudioFmt_ConvertRateMode
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBAudioFmt FBAudioFmt_ConvertRateMode_Wrapper( FBAudioRateMode pRateMode )
{
	return FBAudioFmt_ConvertRateMode( pRateMode );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetCharacterFloorContactsVisibility
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline bool FBGetCharacterFloorContactsVisibility_Wrapper( )
{
    return FBGetCharacterFloorContactsVisibility();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBSetCharacterFloorContactsVisibility
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline void FBSetCharacterFloorContactsVisibility_Wrapper(bool pShow)
{
    FBSetCharacterFloorContactsVisibility(pShow);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetCharacterFingerTipsVisibility
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline bool FBGetCharacterFingerTipsVisibility_Wrapper( )
{
    return FBGetCharacterFingerTipsVisibility();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBSetCharacterFingerTipsVisibility
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline void FBSetCharacterFingerTipsVisibility_Wrapper(bool pShow)
{
    FBSetCharacterFingerTipsVisibility(pShow);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetCharactersKeyingMode
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline FBCharacterKeyingMode FBGetCharactersKeyingMode_Wrapper( )
{
    return FBGetCharactersKeyingMode();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetEffectorBodyPart
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline FBBodyPartId FBGetEffectorBodyPart_Wrapper( FBEffectorId pEffectorId )
{
    return FBGetEffectorBodyPart( pEffectorId );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetCharacterExternalSolverCount
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline int FBGetCharacterExternalSolverCount_Wrapper()
{
    return FBGetCharacterExternalSolverCount();
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetCharacterExternalSolverName
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline const char* FBGetCharacterExternalSolverName_Wrapper( int pIndex )
{
    return FBGetCharacterExternalSolverName( pIndex );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetCharacterExternalSolverIndex
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
PYSDK_DLL inline int FBGetCharacterExternalSolverIndex_Wrapper( const char* pName )
{
    return FBGetCharacterExternalSolverIndex( pName );
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetMainThreadTaskCycle, FBGetRenderingTaskCycle, FBGetEvaluationTaskCycle
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
#if defined(KPROFILING_CODE_ENABLE)
	PYSDK_DLL inline FBProfileTaskCycle_Wrapper* FBGetMainThreadTaskCycle_Wrapper()
	{
		return FBProfileTaskCycle_Wrapper_Factory(FBGetMainThreadTaskCycle());
	}

	PYSDK_DLL inline FBProfileTaskCycle_Wrapper* FBGetRenderingTaskCycle_Wrapper()
	{
		return FBProfileTaskCycle_Wrapper_Factory(FBGetRenderingTaskCycle());
	}

	PYSDK_DLL inline FBProfileTaskCycle_Wrapper* FBGetEvaluationTaskCycle_Wrapper()
	{
		return FBProfileTaskCycle_Wrapper_Factory(FBGetEvaluationTaskCycle());
	}
#endif

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION: FBGetDisplayInfo
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

PYSDK_DLL inline FBEvaluateInfo_Wrapper* FBGetDisplayInfo_Wrapper()
{
	return FBEvaluateInfo_Wrapper_Factory(FBGetDisplayInfo());
}


#endif // pyfbglobal_h__
