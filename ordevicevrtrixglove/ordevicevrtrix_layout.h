#pragma once
#include "ordevicevrtrixglove_device.h"
#include "JsonHandler.h"

class ORDeviceVRTRIXLayout: public FBDeviceLayout
{
    //--- FiLMBOX declaration.
    FBDeviceLayoutDeclare( ORDeviceVRTRIXLayout, FBDeviceLayout );

public:
	//--- FiLMBOX Creation/Destruction.
	virtual bool FBCreate();			//!< FiLMBOX constructor.
	virtual void FBDestroy();			//!< FiLMBOX destructor.

	// UI Management
	void	UICreate				();		// Create & assign UI regions
	void		UICreateLayoutDisplay   ();
	void		UICreateLayoutSetup		();
	void		UICreateLayoutOrientationAlign();
	void	UIConfigure				();		// Configure UI options
	void		UIConfigureLayout0	();
	void		UIConfigureLayout1	();
	void		UIConfigureLayout2	();
	void	UIRefresh				();		// Refresh on idle
	void		UIRefreshSpreadSheet();
	void	UIReset					();		// Reset from device values
	void		UIResetSpreadSheet	();
	void	LoadConfigFile          (int index);

	// Main Layout: Events
	void	EventDeviceStatusChange					( HISender pSender, HKEvent pEvent );
	void	EventUIIdle								( HISender pSender, HKEvent pEvent );
	void	EventTabPanelChange						( HISender pSender, HKEvent pEvent );
	
	void    EventServerIPChange						(HISender pSender, HKEvent pEvent);
	void    EventDeviceIDChange						(HISender pSender, HKEvent pEvent);
	void    EventHardwareTypeChange					( HISender pSender, HKEvent pEvent );
	void	EventButtonAdvancedModeEnableClick		( HISender pSender, HKEvent pEvent );
	void	EventHandTypeChange						( HISender pSender, HKEvent pEvent );
	void	EventFingerIndexChange					( HISender pSender, HKEvent pEvent );
	
	void	EventProximalSlerpDownChange			( HISender pSender, HKEvent pEvent );
	void	EventDistalSlerpDownChange				( HISender pSender, HKEvent pEvent );
	void	EventProximalSlerpUpChange				( HISender pSender, HKEvent pEvent );
	void	EventDistalSlerpUpChange				( HISender pSender, HKEvent pEvent );
	void	EventButtonParamSyncEnableClick			( HISender pSender, HKEvent pEvent );
	void	EventFingerSpacingChange				( HISender pSender, HKEvent pEvent );
	void	EventFinalFingerSpacingChange			( HISender pSender, HKEvent pEvent );
	void	EventBendUpThresholdChange				( HISender pSender, HKEvent pEvent );
	void	EventBendDownThresholdChange				( HISender pSender, HKEvent pEvent );
	
	void	EventFingerProximalOffsetChange				( HISender pSender, HKEvent pEvent );
	//void	EventMiddleOffsetChange						( HISender pSender, HKEvent pEvent );
	//void	EventRingOffsetChange						( HISender pSender, HKEvent pEvent );
	//void	EventPinkyOffsetChange						( HISender pSender, HKEvent pEvent );

	void	EventThumbProximalOffsetChange				( HISender pSender, HKEvent pEvent );
	void	EventThumbMiddleOffsetChange				( HISender pSender, HKEvent pEvent );
	void	EventThumbDistalOffsetChange				( HISender pSender, HKEvent pEvent );

	void	EventLHModelOffsetChange				( HISender pSender, HKEvent pEvent);
	void	EventRHModelOffsetChange				( HISender pSender, HKEvent pEvent );

	void	EventButtonTPoseCalibrationClick		( HISender pSender, HKEvent pEvent);
	void    EventButtonOKPoseCalibrationClick		(HISender pSender, HKEvent pEvent);
	void    EventButtonSaveHardwareCalibrationClick		(HISender pSender, HKEvent pEvent);
	void	EventButtonSaveParameter				( HISender pSender, HKEvent pEvent);

private:
	FBTabPanel			mTabPanel;

	FBLayout			mLayoutMarkers;
		FBSpread			mSpreadMarkers;

	FBLayout			mLayoutSetup;
		FBLabel				mLabelSetup;
		FBButton			mButtonParamSyncEnable;
		//Save Parameter Button
		FBButton			mButtonSaveParameter;

	FBLayout			mLayoutTuning;
		FBButton			mButtonAdvancedEnable;
			FBLabel				mLabelHandType;
			FBList				mListHandType;
			FBLabel				mLabelFingerSpacing;
			FBEditNumber		mEditFingerSpacing;
			FBLabel				mLabelFinalFingerSpacing;
			FBEditNumber		mEditFinalFingerSpacing;
			FBLabel				mLabelFingerIndex;
			FBList				mListFingerIndex;
			FBLabel				mLabelProximalSlerpDown;
			FBEditNumber		mEditProximalSlerpDown;
			FBLabel				mLabelDistalSlerpDown;
			FBEditNumber		mEditDistalSlerpDown;
			FBLabel				mLabelProximalSlerpUp;
			FBEditNumber		mEditProximalSlerpUp;
			FBLabel				mLabelDistalSlerpUp;
			FBEditNumber		mEditDistalSlerpUp;
			FBLabel				mLabelBendUpThreshold;
			FBLabel				mLabelBendUpThreshold2;
			FBEditNumber		mEditBendUpThreshold;
			FBLabel				mLabelBendDownThreshold;
			FBEditNumber		mEditBendDownThreshold;
			
			FBLabel				mLabelProximalOffset;
			FBEditVector		mEditProximalOffset;
			FBLabel				mLabelThumbProximalOffset;
			FBEditVector		mEditThumbProximalOffset;
			FBLabel				mLabelThumbMiddleOffset;
			FBEditVector		mEditThumbMiddleOffset;
			FBLabel				mLabelThumbDistalOffset;
			FBEditVector		mEditThumbDistalOffset;

	FBLayout			mLayoutOrientationAlign;
			//FBLayout			mLayoutAlign;
			FBLabel				mLabelServerIP;
			FBEdit				mEditServerIP;
			FBLabel				mLabelDeviceID;
			FBList				mListDeviceID;
			FBLabel				mLabelHardwareVersion;
			FBList				mListHardwareVersion;
			
			//Left Hand Model Offset
			FBLabel				mLabelXAxisOffsetL;
			FBEditVector		mEditXAxisOffsetL;
			FBLabel				mLabelYAxisOffsetL;
			FBEditVector		mEditYAxisOffsetL;
			FBLabel				mLabelZAxisOffsetL;
			FBEditVector		mEditZAxisOffsetL;

			//Right Hand Model Offset
			FBLabel				mLabelXAxisOffsetR;
			FBEditVector		mEditXAxisOffsetR;
			FBLabel				mLabelYAxisOffsetR;
			FBEditVector		mEditYAxisOffsetR;
			FBLabel				mLabelZAxisOffsetR;
			FBEditVector		mEditZAxisOffsetR;

			//T Pose & OK Pose Calibration Button
			FBButton			mButtonTPoseCalibration;
			FBButton			mButtonOKPoseCalibration;
			FBButton			mButtonSaveHardwareCalibration;

private:
	VRTRIX::HandType		mHandType;					//!< Hand Type
	int						mFingerIndex;				//!< Finger Index
	int						mHardwareVersion;			//!< Hardware version of data glove
	int						mDeviceID;					//!< Data Glove device ID
	std::string				mDeviceIP;					//!< Data Glove device IP	
	bool					mIsParamSyncEnabled;		//!< Whether apply parameters for all fingers.
	bool					mIsAdvancedModeEnabled;		//!< Whether the advanced mode is enabled.
	double					mFingerSpacing;				//!< Finger spacing when advanced mode is NOT enabled.
	double					mFinalFingerSpacing;		//!< Final finger spacing when making a fist
	double					mBendUpThreshold;			//!< Finger bend up stop threshold
	double					mBendDownThreshold;			//!< Finger bend down stop threshold
	double					mProximalSlerpDownValue[5];		//!< Proximal joint slerp-down value array.
	double					mDistalSlerpDownValue[5];		//!< Distal joint slerp-down value array.
	double					mProximalSlerpUpValue[5];		//!< Proximal joint slerp-up value array.
	double					mDistalSlerpUpValue[5];		//!< Distal joint slerp value-up array.

	FBVector3d				mLHIndexOffset[3];
	FBVector3d				mRHIndexOffset[3];

	FBVector3d				mLHMiddleOffset[3];
	FBVector3d				mRHMiddleOffset[3];

	FBVector3d				mLHRingOffset[3];
	FBVector3d				mRHRingOffset[3];

	FBVector3d				mLHPinkyOffset[3];
	FBVector3d				mRHPinkyOffset[3];

	FBVector3d				mLHThumbOffset[3];			//!< Left Hand Thumb offset vector array
	FBVector3d				mRHThumbOffset[3];			//!< Right Hand Thumb offset vector array

	FBVector3d				mLHModelOffset[3];			//!< Left Hand Model Offset
	FBVector3d				mRHModelOffset[3];			//!< Right Hand Model Offset

	FBSystem				mSystem;					//!< System interface.
	ORDeviceVRTRIXGlove*	mDevice;					//!< Handle onto device.

	JsonHandler * m_jHandler;
};

