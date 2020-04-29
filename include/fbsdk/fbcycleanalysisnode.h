#ifndef __FBCYCLEANALYSISNODE_H__
#define __FBCYCLEANALYSISNODE_H__

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

enum FBRootRMode
{
    kFBRootRAbsoluteDifference,
    kFBRootRRelativeDifference,
};
FB_DEFINE_ENUM( FBSDK_DLL, RootRMode );

enum FBRootHMode
{
    kFBRootHAbsoluteDifference,
    kFBRootHRelativeDifference,
};
FB_DEFINE_ENUM( FBSDK_DLL, RootHMode );

enum FBRootXZMode
{
    kFBRootXZAbsoluteDifference,
    kFBRootXZRelativeDifference,
};
FB_DEFINE_ENUM( FBSDK_DLL, RootXZMode );

enum FBRootSpeedMode
{
    kFBRootSpeedAbsoluteDifference,
    kFBRootSpeedRelativeDifference,
};
FB_DEFINE_ENUM( FBSDK_DLL, RootSpeedMode );

__FB_FORWARD( FBCycleAnalysisNode );

////////////////////////////////////////////////////////////////////////////////////
// FBCycleAnalysisNode
////////////////////////////////////////////////////////////////////////////////////

//! Cycle Analysis class.
class FBSDK_DLL FBCycleAnalysisNode : public FBBox 
{
    __FBClassDeclare( FBCycleAnalysisNode, FBBox );
	//--- Open Reality declaration.

public:
	/** Constructor.
	*	\param	pName		Name of new cycle analysis node.
	*	\param	pObject		For internal use only.
	*						This parameter does not need to be specified by the developer.
	*/
	FBCycleAnalysisNode(const char* pName, HIObject pObject=NULL);

    IQuery_Declare(K_IMPLEMENTATION);			// Interface to IObject  

    FBRootRMode     CycleAnalysisRootRMode;		//!< <b>Read Write Property:</b> The current RootR mode.
    FBRootHMode     CycleAnalysisRootHMode;		//!< <b>Read Write Property:</b> The current RootH mode.
    FBRootXZMode    CycleAnalysisRootXZMode;		//!< <b>Read Write Property:</b> The current RootXZ mode.
    FBRootSpeedMode CycleAnalysisRootSpeedMode;		//!< <b>Read Write Property:</b> The current RootSpeed mode.

    void SetRootRMode( FBRootRMode pRootRMode );
    FBRootRMode GetRootRMode();
    void SetRootHMode( FBRootHMode pRootHMode );
    FBRootHMode GetRootHMode();
    void SetRootXZMode( FBRootXZMode pRootXZMode );
    FBRootXZMode GetRootXZMode();
    void SetRootSpeedMode( FBRootSpeedMode pRootSpeedMode );
    FBRootSpeedMode GetRootSpeedMode();

    FBPropertyBool			RealTime;			//!< <b>Read Only Property:</b> Real time.
    FBPropertyRootRMode		RootRMode;			//!< <b>Read Only Property:</b> RootR Mode.
    FBPropertyRootHMode		RootHMode;			//!< <b>Read Only Property:</b> RootH Mode.
    FBPropertyRootXZMode	RootXZMode;			//!< <b>Read Only Property:</b> RootXZ Mode.
    FBPropertyRootSpeedMode	RootSpeedMode;		//!< <b>Read Only Property:</b> Root Speed Mode.

    FBFCurve* GetPoseFCurve();
    FBFCurve* GetRootRFCurve();
    FBFCurve* GetRootHFCurve();
    FBFCurve* GetRootXZFCurve();
    FBFCurve* GetRootSpeedFCurve();

private:
    FBFCurve* mPoseFCurve;

};

FB_DEFINE_COMPONENT( FBSDK_DLL, CycleAnalysis );

#ifdef FBSDKUseNamespace
    }
#endif

#endif //__FBCYCLEANALYSISNODE_H__