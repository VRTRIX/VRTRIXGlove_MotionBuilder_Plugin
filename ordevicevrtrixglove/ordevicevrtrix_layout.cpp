#include "stdafx.h"
#include "ordevicevrtrix_layout.h"

#define ORDEVICEVRTRIX_LAYOUT    ORDeviceVRTRIXLayout

//--- FiLMBOX implementation and registration
FBDeviceLayoutImplementation(    ORDEVICEVRTRIX_LAYOUT        );
FBRegisterDeviceLayout        (    ORDEVICEVRTRIX_LAYOUT,
                             ORDEVICEVRTRIXGLOVE_CLASSSTR,
                             FB_DEFAULT_SDK_ICON            );    // Icon filename (default=Open Reality icon)


/************************************************
 *	FiLMBOX constructor.
 ************************************************/
bool ORDeviceVRTRIXLayout::FBCreate()
{
	mIsParamSyncEnabled = false;
	mHandType = VRTRIX::Hand_Left;
	mFingerIndex = 0;

	//Loading config file
	m_jHandler = new JsonHandler();

	mIsAdvancedModeEnabled = m_jHandler->m_cfg.mAdvancedMode;
	mHardwareVersion = m_jHandler->m_cfg.mHardwareVersion;
	mFingerSpacing = m_jHandler->m_cfg.mFingerSpacing;
	mFinalFingerSpacing = m_jHandler->m_cfg.mFinalFingerSpacing;
	mBendUpThreshold = m_jHandler->m_cfg.mBendUpThreshold;
	mBendDownThreshold = m_jHandler->m_cfg.mBendDownThreshold;
	for (int i = 0; i < 5; ++i) {
		mProximalSlerpDownValue[i] = m_jHandler->m_cfg.mProximalSlerpDownValue[i];
		mDistalSlerpDownValue[i] = m_jHandler->m_cfg.mDistalSlerpDownValue[i];
		mProximalSlerpUpValue[i] = m_jHandler->m_cfg.mProximalSlerpUpValue[i];
		mDistalSlerpUpValue[i] = m_jHandler->m_cfg.mDistalSlerpUpValue[i];
	}
	
	for (int i = 0; i < 3; ++i) {
		mLHThumbOffset[i] = m_jHandler->m_cfg.mLHThumbOffset[i];
		mRHThumbOffset[i] = m_jHandler->m_cfg.mRHThumbOffset[i];
		mLHModelOffset[i] = m_jHandler->m_cfg.mLHModelOffset[i];
		mRHModelOffset[i] = m_jHandler->m_cfg.mRHModelOffset[i];
	}

	// Get a handle on the device.
	mDevice = ((ORDeviceVRTRIXGlove *)(FBDevice *)Device);
	mDevice->SetConfig(m_jHandler->m_cfg);
	// Create/configure UI
	UICreate	();
	UIConfigure	();
	UIReset		();

	// Add device & system callbacks
	mDevice->OnStatusChange.Add	( this,(FBCallback)&ORDeviceVRTRIXLayout::EventDeviceStatusChange  );
	mSystem.OnUIIdle.Add		( this,(FBCallback)&ORDeviceVRTRIXLayout::EventUIIdle              );

	// Set model offset on start
	mDevice->SetModelOffset(mLHModelOffset[0], mLHModelOffset[1], mLHModelOffset[2], VRTRIX::Hand_Left);
	mDevice->SetModelOffset(mRHModelOffset[0], mRHModelOffset[1], mRHModelOffset[2], VRTRIX::Hand_Right);
	return true;
}


/************************************************
 *	FiLMBOX destructor.
 ************************************************/
void ORDeviceVRTRIXLayout::FBDestroy()
{
	// Remove device & system callbacks
	mSystem.OnUIIdle.Remove		( this,(FBCallback)&ORDeviceVRTRIXLayout::EventUIIdle              );
	mDevice->OnStatusChange.Remove	( this,(FBCallback)&ORDeviceVRTRIXLayout::EventDeviceStatusChange  );
}


/************************************************
 *	Create the UI.
 ************************************************/
void ORDeviceVRTRIXLayout::UICreate()
{
	int lS, lH;		// space, height
	lS = 4;
	lH = 25;

	// Create regions
	AddRegion	( "TabPanel",	"TabPanel",		0,		kFBAttachLeft,		"",			1.00,
												0,		kFBAttachTop,		"",			1.00,
												0,		kFBAttachRight,		"",			1.00,
												lH,		kFBAttachNone,		NULL,		1.00 );
	AddRegion	( "MainLayout",	"MainLayout",	lS,		kFBAttachLeft,		"TabPanel",	1.00,
												lS,		kFBAttachBottom,	"TabPanel",	1.00,
												-lS,	kFBAttachRight,		"TabPanel",	1.00,
												-lS,	kFBAttachBottom,	"",			1.00 );

	// Assign regions
	SetControl	( "TabPanel",	mTabPanel		);
	SetControl	( "MainLayout",	mLayoutMarkers	);

	// Create sub layouts
	UICreateLayoutDisplay();
	UICreateLayoutSetup();
	UICreateLayoutOrientationAlign();
}


/************************************************
 *	Create the markers layout.
 ************************************************/
void ORDeviceVRTRIXLayout::UICreateLayoutDisplay()
{
	// Add regions
	mLayoutMarkers.AddRegion( "SpreadMarkers", "SpreadMarkers",
													0,		kFBAttachLeft,		"",		1.00,
													0,		kFBAttachTop,		"",		1.00,
													0,		kFBAttachRight,		"",		1.00,
													0,		kFBAttachBottom,	"",		1.00 );

	// Assign regions
	mLayoutMarkers.SetControl( "SpreadMarkers", mSpreadMarkers );
}


/************************************************
*    Create the setup layout.
************************************************/
void ORDeviceVRTRIXLayout::UICreateLayoutSetup()
{
	int lS, lW, lH;		// space, width, height.
	lS = 4;
	lW = 250;
	lH = 18;

	// Add regions
	mLayoutSetup.AddRegion (	"LabelSetup",	"LabelSetup",
													lS,		kFBAttachLeft,		"",		1.00,
													lS,		kFBAttachTop,		"",		1.00,
													lW,		kFBAttachNone,		NULL,	1.00,
													lH,		kFBAttachNone,		NULL,	1.00 );
	// Assign regions
	mLayoutSetup.SetControl(	"LabelSetup",	mLabelSetup );

	// Add regions
	mLayoutSetup.AddRegion (	"ButtonParamSyncEnable",	"ButtonParamSyncEnable",
													lS,		kFBAttachRight,		"LabelSetup",		1.00,
													0,		kFBAttachTop,		"LabelSetup",		1.00,
													lW,		kFBAttachNone,		NULL,	1.00,
													lH,		kFBAttachNone,		NULL,	1.00 );
	// Assign regions
	mLayoutSetup.SetControl(	"ButtonParamSyncEnable",	mButtonParamSyncEnable );


	mLayoutSetup.AddRegion( "ButtonSaveParam",		"ButtonSaveParam",
													0,		kFBAttachLeft,		"LabelSetup",	1.00,
													lS,		kFBAttachBottom,		"LabelSetup",	1.00,
													200,		kFBAttachNone,		NULL,					1.00,
													25,		kFBAttachNone,		NULL,					1.00 );
	
	mLayoutSetup.SetControl(	"ButtonSaveParam",	mButtonSaveParameter );


	int lS_y	= -15;
	lW			= 100 *2;
	lH			= 25;
	int lHlr	= 180 *2;
	int lWlr	= 260 *2;
	int lWrb	= 140*1.5;
	int lSlbx	= 30;
	int lSlby	= 12;
	int lWlb	= (80 + 50)*2;

	mLayoutSetup.AddRegion( "AlgorithmTuning",	"AlgorithmTuning",
													lS,		kFBAttachLeft,		"",						1.00,
													15,		kFBAttachBottom,	"ButtonSaveParam",	1.00,
													lWlr,	kFBAttachNone,	NULL,					1.00,
													lHlr,	kFBAttachNone,	NULL,					1.00 );

	// Add regions 
	mLayoutTuning.AddRegion( "LayoutRegionTuning",	"LayoutRegionTuning",
													5,		kFBAttachLeft,		"",						1.00,
													15,		kFBAttachTop,		"AlgorithmTuning",			1.00,
													-10,	kFBAttachWidth,		"AlgorithmTuning",			1.00,
													-30,	kFBAttachHeight,	"AlgorithmTuning",			1.00 );
	mLayoutTuning.AddRegion( "ButtonAdvancedEnable",	"ButtonAdvancedEnable",
													lS,		kFBAttachLeft,		"LayoutRegionTuning",	1.00,
													lS_y,	kFBAttachTop,		"LayoutRegionTuning",	1.00,
													lWrb,	kFBAttachNone,		NULL,					1.00,
													lH,		kFBAttachNone,		NULL,					1.00 );

	mLayoutTuning.AddRegion( "LabelHandType",		"LabelHandType",
													lSlbx,	kFBAttachLeft,		"LayoutRegionTuning",	1.00,
													lSlby,	kFBAttachTop,		"LayoutRegionTuning",	1.00,
													lWlb,	kFBAttachNone,		NULL,					1.00,
													lH,		kFBAttachNone,		NULL,					1.00 );
	
	mLayoutTuning.AddRegion( "EditHandType",		"EditHandType",
													lS,		kFBAttachRight,		"LabelHandType",	1.00,
													0,		kFBAttachTop,		"LabelHandType",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													lH,		kFBAttachNone,		NULL,					1.00 );


	mLayoutTuning.AddRegion( "LabelFingerSpacing",		"LabelFingerSpacing",
													0,		kFBAttachLeft,		"LabelHandType",	1.00,
													lS,		kFBAttachBottom,		"LabelHandType",	1.00,
													0,		kFBAttachWidth,		"LabelHandType",					1.00,
													0,		kFBAttachHeight,		"LabelHandType",					1.00 );
	
	mLayoutTuning.AddRegion( "EditFingerSpacing",		"EditFingerSpacing",
													lS,		kFBAttachRight,		"LabelFingerSpacing",	1.00,
													0,		kFBAttachTop,		"LabelFingerSpacing",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,		"LabelFingerSpacing",					1.00 );

	mLayoutTuning.AddRegion( "LabelFinalFingerSpacing",		"LabelFinalFingerSpacing",
													0,		kFBAttachLeft,		"LabelFingerSpacing",	1.00,
													lS,		kFBAttachBottom,		"LabelFingerSpacing",	1.00,
													0,		kFBAttachWidth,		"LabelFingerSpacing",					1.00,
													0,		kFBAttachHeight,		"LabelFingerSpacing",					1.00 );
	
	mLayoutTuning.AddRegion( "EditFinalFingerSpacing",		"EditFinalFingerSpacing",
													lS,		kFBAttachRight,		"LabelFinalFingerSpacing",	1.00,
													0,		kFBAttachTop,		"LabelFinalFingerSpacing",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,		"LabelFinalFingerSpacing",					1.00 );


	mLayoutTuning.AddRegion( "LabelFingerIndex",		"LabelFingerIndex",
													0,		kFBAttachLeft,		"LabelFinalFingerSpacing",	1.00,
													lS,		kFBAttachBottom,	"LabelFinalFingerSpacing",	1.00,
													0,		kFBAttachWidth,		"LabelFinalFingerSpacing",	1.00,
													0,		kFBAttachHeight,	"LabelFinalFingerSpacing",	1.00 );
	
	mLayoutTuning.AddRegion( "ListFingerIndex",		"ListFingerIndex",
													lS,		kFBAttachRight,		"LabelFingerIndex",		1.00,
													0,		kFBAttachTop,		"LabelFingerIndex",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelFingerIndex",		1.00 );
	
	
	//mLayoutTuning.AddRegion( "LabelProximalSlerpDown",		"LabelProximalSlerpDown",
	//												0,		kFBAttachLeft,		"LabelFingerIndex",		1.00,
	//												lS,		kFBAttachBottom,	"LabelFingerIndex",		1.00,
	//												0,		kFBAttachWidth,		"LabelFingerIndex",		1.00,
	//												0,		kFBAttachHeight,	"LabelFingerIndex",		1.00 );
	//mLayoutTuning.AddRegion( "EditProximalSlerpDown",		"EditProximalSlerpDown",
	//												lS,		kFBAttachRight,		"LabelProximalSlerpDown",	1.00,
	//												0,		kFBAttachTop,		"LabelProximalSlerpDown",	1.00,
	//												lW,		kFBAttachNone,		NULL,						1.00,
	//												0,		kFBAttachHeight,	"LabelProximalSlerpDown",	1.00 );
	mLayoutTuning.AddRegion( "LabelDistalSlerpDown",	"LabelDistalSlerpDown",
													0,		kFBAttachLeft,		"LabelFingerIndex",	1.00,
													lS,		kFBAttachBottom,	"LabelFingerIndex",	1.00,
													0,		kFBAttachWidth,		"LabelFingerIndex",	1.00,
													0,		kFBAttachHeight,	"LabelFingerIndex",	1.00 );
	mLayoutTuning.AddRegion( "EditDistalSlerpDown",	"EditDistalSlerpDown",
													lS,		kFBAttachRight,		"LabelDistalSlerpDown",		1.00,
													0,		kFBAttachTop,		"LabelDistalSlerpDown",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelDistalSlerpDown",		1.00 );

	
	
	//mLayoutTuning.AddRegion( "LabelProximalSlerpUp",		"LabelProximalSlerpUp",
	//												0,		kFBAttachLeft,		"LabelDistalSlerpDown",		1.00,
	//												lS,		kFBAttachBottom,	"LabelDistalSlerpDown",		1.00,
	//												0,		kFBAttachWidth,		"LabelDistalSlerpDown",		1.00,
	//												0,		kFBAttachHeight,	"LabelDistalSlerpDown",		1.00 );
	//mLayoutTuning.AddRegion( "EditProximalSlerpUp",		"EditProximalSlerpUp",
	//												lS,		kFBAttachRight,		"LabelProximalSlerpUp",	1.00,
	//												0,		kFBAttachTop,		"LabelProximalSlerpUp",	1.00,
	//												lW,		kFBAttachNone,		NULL,					1.00,
	//												0,		kFBAttachHeight,	"LabelProximalSlerpUp",					1.00 );
	mLayoutTuning.AddRegion( "LabelDistalSlerpUp",	"LabelDistalSlerpUp",
													0,		kFBAttachLeft,		"LabelDistalSlerpDown",	1.00,
													lS,		kFBAttachBottom,	"LabelDistalSlerpDown",	1.00,
													0,		kFBAttachWidth,		"LabelDistalSlerpDown",	1.00,
													0,		kFBAttachHeight,	"LabelDistalSlerpDown",	1.00 );
	mLayoutTuning.AddRegion( "EditDistalSlerpUp",	"EditDistalSlerpUp",
													lS,		kFBAttachRight,		"LabelDistalSlerpUp",		1.00,
													0,		kFBAttachTop,		"LabelDistalSlerpUp",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelDistalSlerpUp",		1.00 );

	mLayoutTuning.AddRegion( "LabelBendUpThreshold",		"LabelBendUpThreshold",
													0,		kFBAttachLeft,		"LabelDistalSlerpUp",		1.00,
													lS,		kFBAttachBottom,	"LabelDistalSlerpUp",		1.00,
													0,		kFBAttachWidth,		"LabelDistalSlerpUp",		1.00,
													0,		kFBAttachHeight,	"LabelDistalSlerpUp",		1.00 );
	mLayoutTuning.AddRegion( "EditBendUpThreshold",		"EditBendUpThreshold",
													lS,		kFBAttachRight,		"LabelBendUpThreshold",	1.00,
													0,		kFBAttachTop,		"LabelBendUpThreshold",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelBendUpThreshold",					1.00 );
	mLayoutTuning.AddRegion( "LabelBendDownThreshold",	"LabelBendDownThreshold",
													0,		kFBAttachLeft,		"LabelBendUpThreshold",	1.00,
													lS,		kFBAttachBottom,	"LabelBendUpThreshold",	1.00,
													0,		kFBAttachWidth,		"LabelBendUpThreshold",	1.00,
													0,		kFBAttachHeight,	"LabelBendUpThreshold",	1.00 );
	mLayoutTuning.AddRegion( "EditBendDownThreshold",	"EditBendDownThreshold",
													lS,		kFBAttachRight,		"LabelBendDownThreshold",		1.00,
													0,		kFBAttachTop,		"LabelBendDownThreshold",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelBendDownThreshold",		1.00 );



	mLayoutTuning.AddRegion( "LabelThumbProximalOffset",	"LabelThumbProximalOffset",
													0,		kFBAttachLeft,		"LabelDistalSlerpDown",	1.00,
													lS,		kFBAttachBottom,	"LabelDistalSlerpDown",	1.00,
													0,		kFBAttachWidth,		"LabelDistalSlerpDown",	1.00,
													0,		kFBAttachHeight,	"LabelDistalSlerpDown",	1.00 );
	mLayoutTuning.AddRegion( "EditThumbProximalOffset",		"EditThumbProximalOffset",
													lS,		kFBAttachRight,		"LabelThumbProximalOffset",		1.00,
													0,		kFBAttachTop,		"LabelThumbProximalOffset",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelThumbProximalOffset",		1.00 );

	mLayoutTuning.AddRegion( "LabelThumbMiddleOffset",		"LabelThumbMiddleOffset",
													0,		kFBAttachLeft,		"LabelThumbProximalOffset",		1.00,
													lS,		kFBAttachBottom,	"LabelThumbProximalOffset",		1.00,
													0,		kFBAttachWidth,		"LabelThumbProximalOffset",		1.00,
													0,		kFBAttachHeight,	"LabelThumbProximalOffset",		1.00 );
	mLayoutTuning.AddRegion( "EditThumbMiddleOffset",		"EditThumbMiddleOffset",
													lS,		kFBAttachRight,		"LabelThumbMiddleOffset",	1.00,
													0,		kFBAttachTop,		"LabelThumbMiddleOffset",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelThumbMiddleOffset",					1.00 );
	mLayoutTuning.AddRegion( "LabelThumbDistalOffset",	"LabelThumbDistalOffset",
													0,		kFBAttachLeft,		"LabelThumbMiddleOffset",	1.00,
													lS,		kFBAttachBottom,	"LabelThumbMiddleOffset",	1.00,
													0,		kFBAttachWidth,		"LabelThumbMiddleOffset",	1.00,
													0,		kFBAttachHeight,	"LabelThumbMiddleOffset",	1.00 );
	mLayoutTuning.AddRegion( "EditThumbDistalOffset",	"EditThumbDistalOffset",
													lS,		kFBAttachRight,		"LabelThumbDistalOffset",		1.00,
													0,		kFBAttachTop,		"LabelThumbDistalOffset",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelThumbDistalOffset",		1.00 );





	// Assign regions
	mLayoutTuning.SetControl( "ButtonAdvancedEnable",		mButtonAdvancedEnable);

	mLayoutTuning.SetControl( "LabelHandType",				mLabelHandType);
	mLayoutTuning.SetControl( "EditHandType",				mListHandType);

	mLayoutTuning.SetControl( "LabelFingerSpacing",			mLabelFingerSpacing);
	mLayoutTuning.SetControl( "EditFingerSpacing",			mEditFingerSpacing);

	mLayoutTuning.SetControl( "LabelFinalFingerSpacing",		mLabelFinalFingerSpacing);
	mLayoutTuning.SetControl( "EditFinalFingerSpacing",			mEditFinalFingerSpacing);
	
	mLayoutTuning.SetControl( "LabelFingerIndex",			mLabelFingerIndex);
	mLayoutTuning.SetControl( "ListFingerIndex",			mListFingerIndex);

	//mLayoutTuning.SetControl( "LabelProximalSlerpDown",		mLabelProximalSlerpDown);
	//mLayoutTuning.SetControl( "EditProximalSlerpDown",		mEditProximalSlerpDown);
	mLayoutTuning.SetControl( "LabelDistalSlerpDown",		mLabelDistalSlerpDown);
	mLayoutTuning.SetControl( "EditDistalSlerpDown",		mEditDistalSlerpDown);

	//mLayoutTuning.SetControl( "LabelProximalSlerpUp",		mLabelProximalSlerpUp);
	//mLayoutTuning.SetControl( "EditProximalSlerpUp",		mEditProximalSlerpUp);
	mLayoutTuning.SetControl( "LabelDistalSlerpUp",			mLabelDistalSlerpUp);
	mLayoutTuning.SetControl( "EditDistalSlerpUp",			mEditDistalSlerpUp);

	mLayoutTuning.SetControl( "LabelBendUpThreshold",		mLabelBendUpThreshold);
	mLayoutTuning.SetControl( "EditBendUpThreshold",		mEditBendUpThreshold);
	mLayoutTuning.SetControl( "LabelBendDownThreshold",		mLabelBendDownThreshold);
	mLayoutTuning.SetControl( "EditBendDownThreshold",		mEditBendDownThreshold);

	mLayoutSetup.SetControl	( "AlgorithmTuning",			mLayoutTuning);
}

void ORDeviceVRTRIXLayout::UICreateLayoutOrientationAlign()
{
	int lS, lW, lH;		// space, width, height.
	lS = 4;
	lW = 250;
	lH = 18;

	int lS_y	= -15;
	lW			= 100 *2;
	lH			= 25;
	int lHlr	= 150 *2;
	int lWlr	= 260 *2;
	int lWrb	= 140*1.5;
	int lSlbx	= 30;
	int lSlby	= 12;
	int lWlb	= (80 + 50)*2;

	mLayoutOrientationAlign.AddRegion( "LabelHardwareVersion",		"LabelHardwareVersion",
													lS,	kFBAttachLeft,		"",	1.00,
													lS,	kFBAttachTop,		"",	1.00,
													lW,	kFBAttachNone,		NULL,					1.00,
													lH,		kFBAttachNone,		NULL,					1.00 );
	
	mLayoutOrientationAlign.AddRegion( "EditHardwareVersion",		"EditHardwareVersion",
													lS,		kFBAttachRight,		"LabelHardwareVersion",	1.00,
													0,		kFBAttachTop,		"LabelHardwareVersion",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													lH,		kFBAttachNone,		NULL,					1.00 );


	mLayoutOrientationAlign.AddRegion( "LabelXAxisOffsetL",	"LabelXAxisOffsetL",
													0,		kFBAttachLeft,		"LabelHardwareVersion",	1.00,
													lS,		kFBAttachBottom,	"LabelHardwareVersion",	1.00,
													0,		kFBAttachWidth,		"LabelHardwareVersion",	1.00,
													0,		kFBAttachHeight,	"LabelHardwareVersion",	1.00 );
	mLayoutOrientationAlign.AddRegion( "EditXAxisOffsetL",		"EditXAxisOffsetL",
													lS,		kFBAttachRight,		"LabelXAxisOffsetL",		1.00,
													0,		kFBAttachTop,		"LabelXAxisOffsetL",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelXAxisOffsetL",		1.00 );

	mLayoutOrientationAlign.AddRegion( "LabelYAxisOffsetL",		"LabelYAxisOffsetL",
													0,		kFBAttachLeft,		"LabelXAxisOffsetL",		1.00,
													lS,		kFBAttachBottom,	"LabelXAxisOffsetL",		1.00,
													0,		kFBAttachWidth,		"LabelXAxisOffsetL",		1.00,
													0,		kFBAttachHeight,	"LabelXAxisOffsetL",		1.00 );
	mLayoutOrientationAlign.AddRegion( "EditYAxisOffsetL",		"EditYAxisOffsetL",
													lS,		kFBAttachRight,		"LabelYAxisOffsetL",	1.00,
													0,		kFBAttachTop,		"LabelYAxisOffsetL",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelYAxisOffsetL",					1.00 );
	mLayoutOrientationAlign.AddRegion( "LabelZAxisOffsetL",	"LabelZAxisOffsetL",
													0,		kFBAttachLeft,		"LabelYAxisOffsetL",	1.00,
													lS,		kFBAttachBottom,	"LabelYAxisOffsetL",	1.00,
													0,		kFBAttachWidth,		"LabelYAxisOffsetL",	1.00,
													0,		kFBAttachHeight,	"LabelYAxisOffsetL",	1.00 );
	mLayoutOrientationAlign.AddRegion( "EditZAxisOffsetL",	"EditZAxisOffsetL",
													lS,		kFBAttachRight,		"LabelZAxisOffsetL",		1.00,
													0,		kFBAttachTop,		"LabelZAxisOffsetL",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelZAxisOffsetL",		1.00 );


	mLayoutOrientationAlign.AddRegion( "LabelXAxisOffsetR",	"LabelXAxisOffsetR",
													0,		kFBAttachLeft,		"LabelZAxisOffsetL",	1.00,
													lS,		kFBAttachBottom,	"LabelZAxisOffsetL",	1.00,
													0,		kFBAttachWidth,		"LabelZAxisOffsetL",	1.00,
													0,		kFBAttachHeight,	"LabelZAxisOffsetL",	1.00 );
	mLayoutOrientationAlign.AddRegion( "EditXAxisOffsetR",		"EditXAxisOffsetR",
													lS,		kFBAttachRight,		"LabelXAxisOffsetR",		1.00,
													0,		kFBAttachTop,		"LabelXAxisOffsetR",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelXAxisOffsetR",		1.00 );

	mLayoutOrientationAlign.AddRegion( "LabelYAxisOffsetR",		"LabelYAxisOffsetR",
													0,		kFBAttachLeft,		"LabelXAxisOffsetR",		1.00,
													lS,		kFBAttachBottom,	"LabelXAxisOffsetR",		1.00,
													0,		kFBAttachWidth,		"LabelXAxisOffsetR",		1.00,
													0,		kFBAttachHeight,	"LabelXAxisOffsetR",		1.00 );
	mLayoutOrientationAlign.AddRegion( "EditYAxisOffsetR",		"EditYAxisOffsetR",
													lS,		kFBAttachRight,		"LabelYAxisOffsetR",	1.00,
													0,		kFBAttachTop,		"LabelYAxisOffsetR",	1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelYAxisOffsetR",					1.00 );
	mLayoutOrientationAlign.AddRegion( "LabelZAxisOffsetR",	"LabelZAxisOffsetR",
													0,		kFBAttachLeft,		"LabelYAxisOffsetR",	1.00,
													lS,		kFBAttachBottom,	"LabelYAxisOffsetR",	1.00,
													0,		kFBAttachWidth,		"LabelYAxisOffsetR",	1.00,
													0,		kFBAttachHeight,	"LabelYAxisOffsetR",	1.00 );
	mLayoutOrientationAlign.AddRegion( "EditZAxisOffsetR",	"EditZAxisOffsetR",
													lS,		kFBAttachRight,		"LabelZAxisOffsetR",		1.00,
													0,		kFBAttachTop,		"LabelZAxisOffsetR",		1.00,
													lW,		kFBAttachNone,		NULL,					1.00,
													0,		kFBAttachHeight,	"LabelZAxisOffsetR",		1.00 );

	mLayoutOrientationAlign.AddRegion( "ButtonTPoseCalibration",	"ButtonTPoseCalibration",
													0,		kFBAttachLeft,		"LabelZAxisOffsetR",	1.00,
													lS,		kFBAttachBottom,	"LabelZAxisOffsetR",	1.00,
													0,		kFBAttachWidth,		"LabelZAxisOffsetR",	1.00,
													0,		kFBAttachHeight,	"LabelZAxisOffsetR",	1.00 );
	
	mLayoutOrientationAlign.AddRegion("ButtonOKPoseCalibration", "ButtonOKPoseCalibration",
													0, kFBAttachLeft, "ButtonTPoseCalibration", 1.00,
													lS, kFBAttachBottom, "ButtonTPoseCalibration", 1.00,
													0, kFBAttachWidth, "ButtonTPoseCalibration", 1.00,
													0, kFBAttachHeight, "ButtonTPoseCalibration", 1.00);


	// Assign regions
	mLayoutOrientationAlign.SetControl( "LabelHardwareVersion",				mLabelHardwareVersion);
	mLayoutOrientationAlign.SetControl( "EditHardwareVersion",				mListHardwareVersion);

	mLayoutOrientationAlign.SetControl( "LabelXAxisOffsetL",				mLabelXAxisOffsetL);
	mLayoutOrientationAlign.SetControl( "EditXAxisOffsetL",				mEditXAxisOffsetL);
	mLayoutOrientationAlign.SetControl( "LabelYAxisOffsetL",				mLabelYAxisOffsetL);
	mLayoutOrientationAlign.SetControl( "EditYAxisOffsetL",				mEditYAxisOffsetL);
	mLayoutOrientationAlign.SetControl( "LabelZAxisOffsetL",				mLabelZAxisOffsetL);
	mLayoutOrientationAlign.SetControl( "EditZAxisOffsetL",				mEditZAxisOffsetL);


	mLayoutOrientationAlign.SetControl( "LabelXAxisOffsetR",				mLabelXAxisOffsetR);
	mLayoutOrientationAlign.SetControl( "EditXAxisOffsetR",				mEditXAxisOffsetR);
	mLayoutOrientationAlign.SetControl( "LabelYAxisOffsetR",				mLabelYAxisOffsetR);
	mLayoutOrientationAlign.SetControl( "EditYAxisOffsetR",				mEditYAxisOffsetR);
	mLayoutOrientationAlign.SetControl( "LabelZAxisOffsetR",				mLabelZAxisOffsetR);
	mLayoutOrientationAlign.SetControl( "EditZAxisOffsetR",				mEditZAxisOffsetR);

	mLayoutOrientationAlign.SetControl( "ButtonTPoseCalibration",				mButtonTPoseCalibration);
	mLayoutOrientationAlign.SetControl( "ButtonOKPoseCalibration", mButtonOKPoseCalibration);

}


/************************************************
 *	Configure the UI elements (main layout).
 ************************************************/
void ORDeviceVRTRIXLayout::UIConfigure()
{
	SetBorder ("MainLayout", kFBStandardBorder, false,true, 1, 0,90,0);

	mTabPanel.Items.SetString("Joints~Setup~Algorithm");
	mTabPanel.OnChange.Add( this, (FBCallback)&ORDeviceVRTRIXLayout::EventTabPanelChange );

	UIConfigureLayout0();
	UIConfigureLayout1();
	UIConfigureLayout2();
}


/************************************************
 *	Configure the UI elements (marker layout).
 ************************************************/
void ORDeviceVRTRIXLayout::UIConfigureLayout0()
{
}


/************************************************
 *	Configure the UI elements (setup layout).
 ************************************************/
void ORDeviceVRTRIXLayout::UIConfigureLayout1()
{
	mLabelSetup.Caption = "Algorithm tuning paramters: ";

	mButtonParamSyncEnable.Caption	= "Apply params for all fingers";
	mButtonParamSyncEnable.Style		= kFBCheckbox;
	mButtonParamSyncEnable.State		= true;
	mIsParamSyncEnabled = true;
	mButtonParamSyncEnable.OnClick.Add( this,(FBCallback) &ORDeviceVRTRIXLayout::EventButtonParamSyncEnableClick );

	mButtonSaveParameter.Caption = "Save Parameters";
	mButtonSaveParameter.Style = kFBPushButton;
	mButtonSaveParameter.OnClick.Add( this,(FBCallback) &ORDeviceVRTRIXLayout::EventButtonSaveParameter );


    mLayoutTuning.SetBorder( "LayoutRegionTuning",	kFBEmbossBorder,false,true,2,1,90.0,0);


	mButtonAdvancedEnable.Caption	= "Enable advanced mode";
	mButtonAdvancedEnable.Style		= kFBCheckbox;
	mButtonAdvancedEnable.State		= mIsAdvancedModeEnabled;
	mButtonAdvancedEnable.OnClick.Add( this,(FBCallback) &ORDeviceVRTRIXLayout::EventButtonAdvancedModeEnableClick );
	
	mLabelHandType.Caption = "Hand Type";
	mListHandType.Items.SetString("Left~Right");	
	mListHandType.Style = kFBDropDownList;
	mListHandType.OnChange.Add( this,(FBCallback) &ORDeviceVRTRIXLayout::EventHandTypeChange );

	mLabelFingerSpacing.Caption = "Finger Spacing";
	mEditFingerSpacing.Min	= -10;
	mEditFingerSpacing.Max = 10;
	mEditFingerSpacing.SmallStep = 0.02;
	mEditFingerSpacing.LargeStep = 0.1;
	mEditFingerSpacing.Value	= mFingerSpacing;
	mEditFingerSpacing.OnChange.Add(this, (FBCallback)&ORDeviceVRTRIXLayout::EventFingerSpacingChange );


	mLabelFinalFingerSpacing.Caption = "Final Finger Spacing";
	mEditFinalFingerSpacing.Min	= -10;
	mEditFinalFingerSpacing.Max = 10;
	mEditFinalFingerSpacing.SmallStep = 0.02;
	mEditFinalFingerSpacing.LargeStep = 0.1;
	mEditFinalFingerSpacing.Value	= mFinalFingerSpacing;
	mEditFinalFingerSpacing.OnChange.Add(this, (FBCallback)&ORDeviceVRTRIXLayout::EventFinalFingerSpacingChange );

	
	mLabelFingerIndex.Caption = "Finger Index";
	mListFingerIndex.Items.SetString("Index~Middle~Ring~Pinky~Thumb");	
	mListFingerIndex.Style = kFBDropDownList;
	mListFingerIndex.OnChange.Add( this,(FBCallback) &ORDeviceVRTRIXLayout::EventFingerIndexChange );

	mLayoutTuning.SetBorder( "EditProximalSlerpDown",	kFBStandardBorder, false,true, 1, 0,90,0);
	mLayoutTuning.SetBorder( "EditDistalSlerpDown",		kFBStandardBorder, false,true, 1, 0,90,0);
	mLayoutTuning.SetBorder( "EditProximalSlerpUp",	kFBStandardBorder, false,true, 1, 0,90,0);
	mLayoutTuning.SetBorder( "EditDistalSlerpUp",		kFBStandardBorder, false,true, 1, 0,90,0);

	/*mLabelProximalSlerpDown.Caption	= "Index Proximal Slerp-Down Rate:";
	mEditProximalSlerpDown.Min	= 0;
	mEditProximalSlerpDown.Max = 1;
	mEditProximalSlerpDown.SmallStep = 0.002;
	mEditProximalSlerpDown.LargeStep = 0.01;
	mEditProximalSlerpDown.Value	= mProximalSlerpDownValue[mFingerIndex];
	mEditProximalSlerpDown.OnChange.Add(this, (FBCallback)&ORDeviceVRTRIXLayout::EventProximalSlerpDownChange );
*/
	mLabelDistalSlerpDown.Caption		= "Index Distal Slerp-Down Rate:";
	mEditDistalSlerpDown.Min		= 0;
	mEditDistalSlerpDown.Max		= 1;
	mEditDistalSlerpDown.SmallStep = 0.002;
	mEditDistalSlerpDown.LargeStep = 0.01;
	mEditDistalSlerpDown.Value	= mDistalSlerpDownValue[mFingerIndex];
	mEditDistalSlerpDown.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventDistalSlerpDownChange );

	//mLabelProximalSlerpUp.Caption	= "Index Proximal Slerp-Up Rate:";
	//mEditProximalSlerpUp.Min	= 0;
	//mEditProximalSlerpUp.Max = 1;
	//mEditProximalSlerpUp.SmallStep = 0.002;
	//mEditProximalSlerpUp.LargeStep = 0.01;
	//mEditProximalSlerpUp.Value	= mProximalSlerpUpValue[mFingerIndex];
	//mEditProximalSlerpUp.OnChange.Add(this, (FBCallback)&ORDeviceVRTRIXLayout::EventProximalSlerpUpChange );

	mLabelDistalSlerpUp.Caption		= "Index Distal Slerp-Up Rate:";
	mEditDistalSlerpUp.Min		= 0;
	mEditDistalSlerpUp.Max		= 1;
	mEditDistalSlerpUp.SmallStep = 0.002;
	mEditDistalSlerpUp.LargeStep = 0.01;
	mEditDistalSlerpUp.Value	= mDistalSlerpUpValue[mFingerIndex];
	mEditDistalSlerpUp.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventDistalSlerpUpChange );

	mLabelBendUpThreshold.Caption	= "Finger Bend Up Threshold:";
	mEditBendUpThreshold.Min	= 0;
	mEditBendUpThreshold.Max = 50;
	mEditBendUpThreshold.SmallStep = 0.04;
	mEditBendUpThreshold.LargeStep = 0.2;
	mEditBendUpThreshold.Value	= mBendUpThreshold;
	mEditBendUpThreshold.OnChange.Add(this, (FBCallback)&ORDeviceVRTRIXLayout::EventBendUpThresholdChange );

	mLabelBendDownThreshold.Caption		= "Finger Bend Down Threshold:";
	mEditBendDownThreshold.Min		= -120;
	mEditBendDownThreshold.Max		= -50;
	mEditBendDownThreshold.SmallStep = 0.04;
	mEditBendDownThreshold.LargeStep = 0.2;
	mEditBendDownThreshold.Value	= mBendDownThreshold;
	mEditBendDownThreshold.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventBendDownThresholdChange );

	mLabelThumbProximalOffset.Caption = "Thumb Proximal Offset:";
	mEditThumbProximalOffset.Value = (mHandType == VRTRIX::Hand_Left) ? mLHThumbOffset[0] : mRHThumbOffset[0];
	mEditThumbProximalOffset.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventThumbProximalOffsetChange );

	mLabelThumbMiddleOffset.Caption = "Thumb Middle Offset:";
	mEditThumbMiddleOffset.Value = (mHandType == VRTRIX::Hand_Left) ? mLHThumbOffset[1] : mRHThumbOffset[1];
	mEditThumbMiddleOffset.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventThumbMiddleOffsetChange );

	mLabelThumbDistalOffset.Caption = "Thumb Distal Offset:";
	mEditThumbDistalOffset.Value = (mHandType == VRTRIX::Hand_Left) ? mLHThumbOffset[2] : mRHThumbOffset[2];
	mEditThumbDistalOffset.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventThumbDistalOffsetChange );

}


/************************************************
 *	Configure the UI elements (Orientation Align Layout).
 ************************************************/
void ORDeviceVRTRIXLayout::UIConfigureLayout2()
{
	mLabelHardwareVersion.Caption = "Hardware Version";
	mListHardwareVersion.Items.SetString("PRO7~PRO11~PRO12");	
	mListHardwareVersion.Style = kFBDropDownList;
	mListHardwareVersion.ItemIndex = mHardwareVersion;
	if (mHardwareVersion == 1) {
		mDevice->SetHardwareVersion(VRTRIX::PRO11);
	}
	mListHardwareVersion.OnChange.Add( this,(FBCallback) &ORDeviceVRTRIXLayout::EventHardwareTypeChange );

	mLabelXAxisOffsetL.Caption = "Left Hand Model X Axis:";
	mEditXAxisOffsetL.Value = mLHModelOffset[0];
	mEditXAxisOffsetL.Value.SetMin(-1);
	mEditXAxisOffsetL.Value.SetMax(1);
	mEditXAxisOffsetL.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventLHModelOffsetChange );

	mLabelYAxisOffsetL.Caption = "Left Hand Model Y Axis:";
	mEditYAxisOffsetL.Value = mLHModelOffset[1];
	mEditYAxisOffsetL.Value.SetMin(-1);
	mEditYAxisOffsetL.Value.SetMax(1);
	mEditYAxisOffsetL.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventLHModelOffsetChange );

	mLabelZAxisOffsetL.Caption = "Left Hand Model Z Axis:";
	mEditZAxisOffsetL.Value = mLHModelOffset[2];
	mEditZAxisOffsetL.Value.SetMin(-1);
	mEditZAxisOffsetL.Value.SetMax(1);
	mEditZAxisOffsetL.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventLHModelOffsetChange );

	mLabelXAxisOffsetR.Caption = "Right Hand Model X Axis:";
	mEditXAxisOffsetR.Value = mRHModelOffset[0];
	mEditXAxisOffsetR.Value.SetMin(-1);
	mEditXAxisOffsetR.Value.SetMax(1);
	mEditXAxisOffsetR.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventRHModelOffsetChange );

	mLabelYAxisOffsetR.Caption = "Right Hand Model Y Axis:";
	mEditYAxisOffsetR.Value = mRHModelOffset[1];
	mEditYAxisOffsetR.Value.SetMin(-1);
	mEditYAxisOffsetR.Value.SetMax(1);
	mEditYAxisOffsetR.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventRHModelOffsetChange );

	mLabelZAxisOffsetR.Caption = "Right Hand Model Z Axis:";
	mEditZAxisOffsetR.Value = mRHModelOffset[2];
	mEditZAxisOffsetR.Value.SetMin(-1);
	mEditZAxisOffsetR.Value.SetMax(1);
	mEditZAxisOffsetR.OnChange.Add( this, (FBCallback) &ORDeviceVRTRIXLayout::EventRHModelOffsetChange );

	mButtonTPoseCalibration.Caption	= "TPose Calibration";
	mButtonTPoseCalibration.Style		= kFBPushButton;
	mButtonTPoseCalibration.OnClick.Add( this,(FBCallback) &ORDeviceVRTRIXLayout::EventButtonTPoseCalibrationClick );

	mButtonOKPoseCalibration.Caption = "OK Pose Calibration";
	mButtonOKPoseCalibration.Style = kFBPushButton;
	mButtonOKPoseCalibration.OnClick.Add(this, (FBCallback)&ORDeviceVRTRIXLayout::EventButtonOKPoseCalibrationClick);
}
/************************************************
 *	Refresh the UI.
 ************************************************/
void ORDeviceVRTRIXLayout::UIRefresh()
{
	UIRefreshSpreadSheet();
}


/************************************************
 *	Refresh the spreadsheet content.
 ************************************************/
void ORDeviceVRTRIXLayout::UIRefreshSpreadSheet()
{
  	for(int i=0; i<mDevice->GetChannelCount();i++)
	{
		mSpreadMarkers.SetCell( i, 0, mDevice->GetDataTX(i) );
		mSpreadMarkers.SetCell( i, 1, mDevice->GetDataTY(i) );
		mSpreadMarkers.SetCell( i, 2, mDevice->GetDataTZ(i) );
		mSpreadMarkers.SetCell( i, 3, mDevice->GetDataRX(i) );
		mSpreadMarkers.SetCell( i, 4, mDevice->GetDataRY(i) );
		mSpreadMarkers.SetCell( i, 5, mDevice->GetDataRZ(i) );
	}
}


/************************************************
 *	Reset the UI values from device.
 ************************************************/
void ORDeviceVRTRIXLayout::UIReset()
{
	UIResetSpreadSheet();
}


/************************************************
 *	Re-build the spreadsheet.
 ************************************************/
void ORDeviceVRTRIXLayout::UIResetSpreadSheet()
{
	int i;

	mSpreadMarkers.Clear();

	// Spreadsheet
	int lColumnIndex = -1;
	mSpreadMarkers.GetColumn(lColumnIndex).Width = 200;

	// column 0: Translation X
	mSpreadMarkers.ColumnAdd ("PosX");
	lColumnIndex++;
	mSpreadMarkers.GetColumn(lColumnIndex).Width = 60;
	mSpreadMarkers.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

	// column 1: Translation Y
	mSpreadMarkers.ColumnAdd ("PosY");
	lColumnIndex++;
	mSpreadMarkers.GetColumn(lColumnIndex).Width = 60;
 	mSpreadMarkers.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

 	// column 2: Translation Z
	mSpreadMarkers.ColumnAdd ("PosZ");
	lColumnIndex++;
	mSpreadMarkers.GetColumn(lColumnIndex).Width = 60;
	mSpreadMarkers.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

	// column 3: Rotation X
	mSpreadMarkers.ColumnAdd ("RotX");
	lColumnIndex++;
	mSpreadMarkers.GetColumn(lColumnIndex).Width = 60;
	mSpreadMarkers.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

	// column 4: Rotation Y
	mSpreadMarkers.ColumnAdd ("RotY");
	lColumnIndex++;
	mSpreadMarkers.GetColumn(lColumnIndex).Width = 60;
 	mSpreadMarkers.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

 	// column 5: Rotation Z
	mSpreadMarkers.ColumnAdd ("RotZ");
	lColumnIndex++;
	mSpreadMarkers.GetColumn(lColumnIndex).Width = 60;
	mSpreadMarkers.GetColumn(lColumnIndex).Style = kFBCellStyleDouble;

	for (i=0;i<mDevice->GetChannelCount();i++)
	{
 		mSpreadMarkers.RowAdd( mDevice->GetChannelName(i), i );
	 	mSpreadMarkers.GetCell(i,lColumnIndex).ReadOnly = true;
	}
}


/************************************************
 *	Tab panel change callback.
 ************************************************/
void ORDeviceVRTRIXLayout::EventTabPanelChange( HISender pSender, HKEvent pEvent )
{
	switch( mTabPanel.ItemIndex )
	{
		case 0:	SetControl("MainLayout", mLayoutMarkers			);	break;
		case 1:	SetControl("MainLayout", mLayoutOrientationAlign		);	break;
		case 2:	SetControl("MainLayout", mLayoutSetup		);	break;

	}
}

void ORDeviceVRTRIXLayout::EventHardwareTypeChange(HISender pSender, HKEvent pEvent)
{
	mHardwareVersion = mListHardwareVersion.ItemIndex;
	if (mListHardwareVersion.ItemIndex == 0) {
		mDevice->SetHardwareVersion(VRTRIX::PRO7);
	}
	else if (mListHardwareVersion.ItemIndex == 1) {
		mDevice->SetHardwareVersion(VRTRIX::PRO11);
	}
	else {
		mDevice->SetHardwareVersion(VRTRIX::PRO12);
	}
}

void ORDeviceVRTRIXLayout::EventButtonAdvancedModeEnableClick(HISender pSender, HKEvent pEvent)
{
	mDevice->OnAvancedModeEnabled(mButtonAdvancedEnable.State == 1);
	mIsAdvancedModeEnabled = (mButtonAdvancedEnable.State == 1);
}

void ORDeviceVRTRIXLayout::EventHandTypeChange(HISender pSender, HKEvent pEvent)
{
	mHandType = (mListHandType.ItemIndex == 0) ? VRTRIX::Hand_Left : VRTRIX::Hand_Right;
	mEditThumbProximalOffset.Value = (mHandType == VRTRIX::Hand_Left) ? mLHThumbOffset[0] : mRHThumbOffset[0];
	mEditThumbMiddleOffset.Value = (mHandType == VRTRIX::Hand_Left) ? mLHThumbOffset[1] : mRHThumbOffset[1];
	mEditThumbDistalOffset.Value = (mHandType == VRTRIX::Hand_Left) ? mLHThumbOffset[2] : mRHThumbOffset[2];
}

void ORDeviceVRTRIXLayout::EventFingerIndexChange(HISender pSender, HKEvent pEvent)
{
	if (mFingerIndex == 4) {
		mLayoutTuning.ClearControl("LabelThumbProximalOffset");
		mLayoutTuning.ClearControl("EditThumbProximalOffset");
		mLayoutTuning.ClearControl("LabelThumbMiddleOffset");
		mLayoutTuning.ClearControl("EditThumbMiddleOffset");
		mLayoutTuning.ClearControl("LabelThumbDistalOffset");
		mLayoutTuning.ClearControl("EditThumbDistalOffset");

		mLayoutTuning.SetControl("LabelDistalSlerpUp", mLabelDistalSlerpUp);
		mLayoutTuning.SetControl("EditDistalSlerpUp", mEditDistalSlerpUp);
		mLayoutTuning.SetControl( "LabelBendUpThreshold",		mLabelBendUpThreshold);
		mLayoutTuning.SetControl( "EditBendUpThreshold",		mEditBendUpThreshold);
		mLayoutTuning.SetControl( "LabelBendDownThreshold",		mLabelBendDownThreshold);
		mLayoutTuning.SetControl( "EditBendDownThreshold",		mEditBendDownThreshold);
	}

	mFingerIndex = mListFingerIndex.ItemIndex;
	if (mListFingerIndex.ItemIndex == 0) {
		mLabelDistalSlerpDown.Caption	= "Index Distal Slerp-Down Rate:";
		mLabelDistalSlerpUp.Caption		= "Index Distal Slerp-Up Rate:";

		mEditDistalSlerpDown.Value = mDistalSlerpDownValue[mFingerIndex];
		mEditDistalSlerpUp.Value = mDistalSlerpUpValue[mFingerIndex];
	}
	else if (mListFingerIndex.ItemIndex == 1) {;
		mLabelDistalSlerpDown.Caption	= "Middle Distal Slerp-Down Rate:";
		mLabelDistalSlerpUp.Caption		= "Middle Distal Slerp-Up Rate:";

		mEditDistalSlerpDown.Value = mDistalSlerpDownValue[mFingerIndex];
		mEditDistalSlerpUp.Value = mDistalSlerpUpValue[mFingerIndex];
	}
	else if (mListFingerIndex.ItemIndex == 2) {
		mLabelDistalSlerpDown.Caption	= "Ring Distal Slerp-Down Rate:";
		mLabelDistalSlerpUp.Caption		= "Ring Distal Slerp-Up Rate:";

		mEditDistalSlerpDown.Value = mDistalSlerpDownValue[mFingerIndex];
		mEditDistalSlerpUp.Value = mDistalSlerpUpValue[mFingerIndex];
	}
	else if (mListFingerIndex.ItemIndex == 3) {
		mLabelDistalSlerpDown.Caption	= "Pinky Distal Slerp-Down Rate:";
		mLabelDistalSlerpUp.Caption		= "Pinky Distal Slerp-Up Rate:";

		mEditDistalSlerpDown.Value = mDistalSlerpDownValue[mFingerIndex];
		mEditDistalSlerpUp.Value = mDistalSlerpUpValue[mFingerIndex];
	}
	else if (mListFingerIndex.ItemIndex == 4) {;
		mLabelDistalSlerpDown.Caption	= "Thumb Proximal Slerp-Down Rate:";
		mEditDistalSlerpDown.Value = mProximalSlerpDownValue[mFingerIndex];

		mLayoutTuning.ClearControl("LabelDistalSlerpUp");
		mLayoutTuning.ClearControl("EditDistalSlerpUp");
		mLayoutTuning.ClearControl("LabelBendUpThreshold");
		mLayoutTuning.ClearControl("EditBendUpThreshold");
		mLayoutTuning.ClearControl("LabelBendDownThreshold");
		mLayoutTuning.ClearControl("EditBendDownThreshold");
		
		mLayoutTuning.SetControl( "LabelThumbProximalOffset",	mLabelThumbProximalOffset);
		mLayoutTuning.SetControl( "EditThumbProximalOffset",	mEditThumbProximalOffset);
		mLayoutTuning.SetControl( "LabelThumbMiddleOffset",	mLabelThumbMiddleOffset);
		mLayoutTuning.SetControl( "EditThumbMiddleOffset",	mEditThumbMiddleOffset);
		mLayoutTuning.SetControl( "LabelThumbDistalOffset",	mLabelThumbDistalOffset);
		mLayoutTuning.SetControl( "EditThumbDistalOffset",	mEditThumbDistalOffset);

	}
}

void ORDeviceVRTRIXLayout::EventProximalSlerpDownChange(HISender pSender, HKEvent pEvent)
{
	if (mIsParamSyncEnabled) {
		if (mListFingerIndex.ItemIndex == 4) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Thumb_Distal , VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
			mProximalSlerpDownValue[mFingerIndex] = mEditDistalSlerpDown.Value;
			return;
		}

		mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
		mProximalSlerpDownValue[0] = mEditProximalSlerpDown.Value;
		mProximalSlerpDownValue[1] = mEditProximalSlerpDown.Value;
		mProximalSlerpDownValue[2] = mEditProximalSlerpDown.Value;
		mProximalSlerpDownValue[3] = mEditProximalSlerpDown.Value;
	}
	else {
		if (mListFingerIndex.ItemIndex == 0) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
		}
		else if (mListFingerIndex.ItemIndex == 1) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
		}
		else if (mListFingerIndex.ItemIndex == 2) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
			}
		else if (mListFingerIndex.ItemIndex == 3) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
		}
		else if (mListFingerIndex.ItemIndex == 4) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Thumb_Distal , VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditProximalSlerpDown.Value);
		}
		mProximalSlerpDownValue[mFingerIndex] = mEditProximalSlerpDown.Value;
	}
}

void ORDeviceVRTRIXLayout::EventDistalSlerpDownChange(HISender pSender, HKEvent pEvent)
{
	if (mIsParamSyncEnabled) {
		if (mListFingerIndex.ItemIndex == 4) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Thumb_Distal, VRTRIX::AlgorithmConfig_ProximalSlerpDown, mEditDistalSlerpDown.Value);
			mProximalSlerpDownValue[mFingerIndex] = mEditDistalSlerpDown.Value;
			return;
		}
		mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
		mDistalSlerpDownValue[0] = mEditDistalSlerpDown.Value;
		mDistalSlerpDownValue[1] = mEditDistalSlerpDown.Value;
		mDistalSlerpDownValue[2] = mEditDistalSlerpDown.Value;
		mDistalSlerpDownValue[3] = mEditDistalSlerpDown.Value;
	}
	else {
		if (mListFingerIndex.ItemIndex == 0) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
		}
		else if (mListFingerIndex.ItemIndex == 1) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
		}
		else if (mListFingerIndex.ItemIndex == 2) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
			}
		else if (mListFingerIndex.ItemIndex == 3) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
		}
		else if (mListFingerIndex.ItemIndex == 4) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Thumb_Distal, VRTRIX::AlgorithmConfig_DistalSlerpDown, mEditDistalSlerpDown.Value);
		}
		mDistalSlerpDownValue[mFingerIndex] = mEditDistalSlerpDown.Value;
	}
}

void ORDeviceVRTRIXLayout::EventProximalSlerpUpChange(HISender pSender, HKEvent pEvent)
{
	if (mIsParamSyncEnabled) {
		mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
		mProximalSlerpUpValue[0] = mEditProximalSlerpUp.Value;
		mProximalSlerpUpValue[1] = mEditProximalSlerpUp.Value;
		mProximalSlerpUpValue[2] = mEditProximalSlerpUp.Value;
		mProximalSlerpUpValue[3] = mEditProximalSlerpUp.Value;
	}
	else {
		if (mListFingerIndex.ItemIndex == 0) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
		}
		else if (mListFingerIndex.ItemIndex == 1) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
		}
		else if (mListFingerIndex.ItemIndex == 2) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
			}
		else if (mListFingerIndex.ItemIndex == 3) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
		}
		else if (mListFingerIndex.ItemIndex == 4) {
			//mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, mEditProximalSlerpUp.Value);
		}
		mProximalSlerpUpValue[mFingerIndex] = mEditProximalSlerpUp.Value;
	}
}

void ORDeviceVRTRIXLayout::EventDistalSlerpUpChange(HISender pSender, HKEvent pEvent)
{
	if (mIsParamSyncEnabled) {
		mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
		mDevice->OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
		mDistalSlerpUpValue[0] = mEditDistalSlerpUp.Value;
		mDistalSlerpUpValue[1] = mEditDistalSlerpUp.Value;
		mDistalSlerpUpValue[2] = mEditDistalSlerpUp.Value;
		mDistalSlerpUpValue[3] = mEditDistalSlerpUp.Value;
	}
	else {
		if (mListFingerIndex.ItemIndex == 0) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
		}
		else if (mListFingerIndex.ItemIndex == 1) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
		}
		else if (mListFingerIndex.ItemIndex == 2) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
			}
		else if (mListFingerIndex.ItemIndex == 3) {
			mDevice->OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
		}
		else if (mListFingerIndex.ItemIndex == 4) {
			//mDevice->OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, mEditDistalSlerpUp.Value);
		}
		mDistalSlerpUpValue[mFingerIndex] = mEditDistalSlerpUp.Value;
	}
}

void ORDeviceVRTRIXLayout::EventButtonParamSyncEnableClick(HISender pSender, HKEvent pEvent)
{
	mIsParamSyncEnabled = (int)mButtonParamSyncEnable.State == 1;
}

void ORDeviceVRTRIXLayout::EventFingerSpacingChange(HISender pSender, HKEvent pEvent)
{
	mDevice->OnSetFingerSpacing(mEditFingerSpacing.Value);
	mFingerSpacing = mEditFingerSpacing.Value;
}

void ORDeviceVRTRIXLayout::EventFinalFingerSpacingChange(HISender pSender, HKEvent pEvent)
{
	mDevice->OnSetFinalFingerSpacing(mEditFinalFingerSpacing.Value);
	mFinalFingerSpacing = mEditFinalFingerSpacing.Value;
}

void ORDeviceVRTRIXLayout::EventBendUpThresholdChange(HISender pSender, HKEvent pEvent)
{
	mDevice->OnSetBendUpThreshold(mEditBendUpThreshold.Value);
	mBendUpThreshold = mEditBendUpThreshold.Value;
}

void ORDeviceVRTRIXLayout::EventBendDownThresholdChange(HISender pSender, HKEvent pEvent)
{
	mDevice->OnSetBendDownThreshold(mEditBendDownThreshold.Value);
	mBendDownThreshold = mEditBendDownThreshold.Value;
}

void ORDeviceVRTRIXLayout::EventThumbProximalOffsetChange(HISender pSender, HKEvent pEvent)
{
	if (mHandType == VRTRIX::Hand_Left) {
		mLHThumbOffset[0] = mEditThumbProximalOffset.Value;
		VRTRIX::VRTRIXVector_t offset = { (float)mLHThumbOffset[0].mValue[0], (float)mLHThumbOffset[0].mValue[1], (float)mLHThumbOffset[0].mValue[2] };
		mDevice->OnSetThumbOffset(offset, VRTRIX::Thumb_Proximal, VRTRIX::Hand_Left);
	}
	else {
		mRHThumbOffset[0] = mEditThumbProximalOffset.Value;
		VRTRIX::VRTRIXVector_t offset = { (float)mRHThumbOffset[0].mValue[0], (float)mRHThumbOffset[0].mValue[1],(float)mRHThumbOffset[0].mValue[2] };
		mDevice->OnSetThumbOffset(offset, VRTRIX::Thumb_Proximal, VRTRIX::Hand_Right);
	}
}

void ORDeviceVRTRIXLayout::EventThumbMiddleOffsetChange(HISender pSender, HKEvent pEvent)
{
	if (mHandType == VRTRIX::Hand_Left) {
		mLHThumbOffset[1] = mEditThumbMiddleOffset.Value;
		VRTRIX::VRTRIXVector_t offset = { (float)mLHThumbOffset[1].mValue[0], (float)mLHThumbOffset[1].mValue[1],(float)mLHThumbOffset[1].mValue[2] };
		mDevice->OnSetThumbOffset(offset, VRTRIX::Thumb_Intermediate, VRTRIX::Hand_Left);
	}
	else {
		mRHThumbOffset[1] = mEditThumbMiddleOffset.Value;
		VRTRIX::VRTRIXVector_t offset = { (float)mRHThumbOffset[1].mValue[0], (float)mRHThumbOffset[1].mValue[1],(float)mRHThumbOffset[1].mValue[2] };
		mDevice->OnSetThumbOffset(offset, VRTRIX::Thumb_Intermediate, VRTRIX::Hand_Right);
	}
}

void ORDeviceVRTRIXLayout::EventThumbDistalOffsetChange(HISender pSender, HKEvent pEvent)
{
	if (mHandType == VRTRIX::Hand_Left) {
		mLHThumbOffset[2] = mEditThumbDistalOffset.Value;
		VRTRIX::VRTRIXVector_t offset = { (float)mLHThumbOffset[2].mValue[0], (float)mLHThumbOffset[2].mValue[1],(float)mLHThumbOffset[2].mValue[2] };
		mDevice->OnSetThumbOffset(offset, VRTRIX::Thumb_Distal, VRTRIX::Hand_Left);
	}
	else {
		mRHThumbOffset[2] = mEditThumbDistalOffset.Value;
		VRTRIX::VRTRIXVector_t offset = { (float)mRHThumbOffset[2].mValue[0], (float)mRHThumbOffset[2].mValue[1],(float)mRHThumbOffset[2].mValue[2] };
		mDevice->OnSetThumbOffset(offset, VRTRIX::Thumb_Distal, VRTRIX::Hand_Right);
	}
}

void ORDeviceVRTRIXLayout::EventLHModelOffsetChange(HISender pSender, HKEvent pEvent)
{
	mDevice->SetModelOffset((FBVector3d)mEditXAxisOffsetL.Value, (FBVector3d)mEditYAxisOffsetL.Value, (FBVector3d)mEditZAxisOffsetL.Value, VRTRIX::Hand_Left);
	mLHModelOffset[0] = (FBVector3d)mEditXAxisOffsetL.Value;
	mLHModelOffset[1] = (FBVector3d)mEditYAxisOffsetL.Value;
	mLHModelOffset[2] = (FBVector3d)mEditZAxisOffsetL.Value;
}

void ORDeviceVRTRIXLayout::EventRHModelOffsetChange(HISender pSender, HKEvent pEvent)
{
	mDevice->SetModelOffset((FBVector3d)mEditXAxisOffsetR.Value, (FBVector3d)mEditYAxisOffsetR.Value, (FBVector3d)mEditZAxisOffsetR.Value, VRTRIX::Hand_Right);
	mRHModelOffset[0] = (FBVector3d)mEditXAxisOffsetR.Value;
	mRHModelOffset[1] = (FBVector3d)mEditYAxisOffsetR.Value;
	mRHModelOffset[2] = (FBVector3d)mEditZAxisOffsetR.Value;
}

void ORDeviceVRTRIXLayout::EventButtonTPoseCalibrationClick(HISender pSender, HKEvent pEvent)
{
	mDevice->OnTPoseCalibration();
}

void ORDeviceVRTRIXLayout::EventButtonOKPoseCalibrationClick(HISender pSender, HKEvent pEvent)
{
	mDevice->OnOKPoseCalibration();
}


void ORDeviceVRTRIXLayout::EventButtonSaveParameter(HISender pSender, HKEvent pEvent)
{
	m_jHandler->m_cfg.mAdvancedMode = mIsAdvancedModeEnabled;
	m_jHandler->m_cfg.mHardwareVersion = mHardwareVersion;
	m_jHandler->m_cfg.mFingerSpacing = mFingerSpacing;
	m_jHandler->m_cfg.mFinalFingerSpacing = mFinalFingerSpacing;
	m_jHandler->m_cfg.mBendUpThreshold = mBendUpThreshold;
	m_jHandler->m_cfg.mBendDownThreshold = mBendDownThreshold;
	for (int i = 0; i < 5; ++i) {
		m_jHandler->m_cfg.mProximalSlerpDownValue[i] = mProximalSlerpDownValue[i];
		m_jHandler->m_cfg.mDistalSlerpDownValue[i] = mDistalSlerpDownValue[i];
		m_jHandler->m_cfg.mProximalSlerpUpValue[i] = mProximalSlerpUpValue[i];
		m_jHandler->m_cfg.mDistalSlerpUpValue[i] = mDistalSlerpUpValue[i];
	}
	
	for (int i = 0; i < 3; ++i) {
		m_jHandler->m_cfg.mLHThumbOffset[i] = mLHThumbOffset[i];
		m_jHandler->m_cfg.mRHThumbOffset[i] = mRHThumbOffset[i];
		m_jHandler->m_cfg.mLHModelOffset[i] = mLHModelOffset[i];
		m_jHandler->m_cfg.mRHModelOffset[i] = mRHModelOffset[i];
	}
	if (m_jHandler->writeBack()) {
		FBMessageBox("Parameter Saving", "Data glove parameters have been saved!", "OK" );
	}
	else {
		FBMessageBox("Parameter Saving", "Failed to save parameters!", "OK" );
	}
}


/************************************************
 *	Device status change callback.
 ************************************************/
void ORDeviceVRTRIXLayout::EventDeviceStatusChange( HISender pSender, HKEvent pEvent )
{
	UIReset();
}


/************************************************
 *	UI Idle callback.
 ************************************************/
void ORDeviceVRTRIXLayout::EventUIIdle( HISender pSender, HKEvent pEvent )
{
	if( mDevice->Online )
	{
		UIRefresh();
	}
}

