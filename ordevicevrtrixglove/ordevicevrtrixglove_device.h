#pragma once

#include <fbsdk/fbsdk.h>
#include "orhardwarevrtrixglove.h"

//--- Registration defines
#define ORDEVICEVRTRIXGLOVE_CLASSNAME		ORDeviceVRTRIXGlove
#define	ORDEVICEVRTRIXGLOVE_CLASSSTR		"ORDeviceVRTRIXGlove"

enum OperationStatus
{
    eAskForCreateModelBinding,
    eAskForPressOnline,
    eAskForPressSetupRecording,
    eAskForPressCalibration,
    eAskForDoCalibration,
    eReadyForRecording,
};

//! Data channel class.
class DataChannel
{
public:
	//! Constructor.
	DataChannel()
	{
		mTAnimNode		= NULL;
		mRAnimNode		= NULL;
		mModelTemplate	= NULL;
	}

	//! Destructor.
	~DataChannel()
	{
	}

public:
	FBAnimationNode*	mTAnimNode;			//!< Position animation node.
	FBAnimationNode*	mRAnimNode;			//!< Rotation animation node.
	FBModelTemplate*	mModelTemplate;		//!< Joint model template driven by the data channel.
};

class ORDeviceVRTRIXGlove : public FBDevice
{
	//--- Declaration
	FBDeviceDeclare( ORDeviceVRTRIXGlove, FBDevice );

public:
	virtual bool FBCreate() override;
	virtual void FBDestroy() override;

    //--- Standard device virtual functions evaluation
	virtual bool DeviceOperation	( kDeviceOperations pOperation									) override;		//!< Operate device.
	virtual bool AnimationNodeNotify( FBAnimationNode* pAnimationNode,FBEvaluateInfo* pEvaluateInfo	) override;		//!< Real-time evaluation function.
	virtual void DeviceIONotify		( kDeviceIOs  pAction, FBDeviceNotifyInfo &pDeviceNotifyInfo	) override;		//!< Hardware I/O notification.
	virtual void DeviceTransportNotify( kTransportMode pMode, FBTime pTime, FBTime pSystem ) override;				//!< Transport notification.

	//--- Recording of frame information
	virtual void	RecordingDoneAnimation( FBAnimationNode* pAnimationNode) override;
	void	DeviceRecordFrame			(FBTime &pTime,FBDeviceNotifyInfo &pDeviceNotifyInfo);

	//--- Load/Save.
	virtual bool FbxStore	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat ) override;	//!< FBX Storage.
	virtual bool FbxRetrieve( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat ) override;	//!< FBX Retrieval.

	//--- Initialisation/Shutdown
    bool	Init	();		//!< Initialize device.
    bool	Start	();		//!< Start device.
    bool	Stop	();		//!< Stop device.
    bool	Reset	();		//!< Reset device.
    bool	Done	();		//!< Device removal.

	//--- Get data from hardware.
	double GetDataTX(int pChannelIndex)			{	return mHardware.GetDataTX(pChannelIndex);		}
	double GetDataTY(int pChannelIndex)			{	return mHardware.GetDataTY(pChannelIndex);		}
	double GetDataTZ(int pChannelIndex)			{	return mHardware.GetDataTZ(pChannelIndex);		}
	double GetDataRX(int pChannelIndex)			{	return mHardware.GetDataRX(pChannelIndex);		}
	double GetDataRY(int pChannelIndex)			{	return mHardware.GetDataRY(pChannelIndex);		}
	double GetDataRZ(int pChannelIndex)			{	return mHardware.GetDataRZ(pChannelIndex);		}

	//--- Set Hardware version on start
	void SetHardwareVersion(VRTRIX::GLOVEVERSION version) { return mHardware.SetHardwareVersion(version); }
	//--- Set model offset on start
	void SetModelOffset(FBVector3d xAxis, FBVector3d yAxis, FBVector3d zAxis, VRTRIX::HandType type) { return mHardware.SetModelOffset(xAxis, yAxis, zAxis, type); }
	//--- Perform T Pose calibration on start
	void OnTPoseCalibration() { return mHardware.OnTPoseCalibration(); }
	//--- Algorithm Tuning for hardware.
	void OnAvancedModeEnabled(bool isEnabled) { return mHardware.OnAvancedModeEnabled(isEnabled); }
	void OnSetAlgorithmParameters(VRTRIX::Joint finger, VRTRIX::AlgorithmConfig type, double value) { return mHardware.OnSetAlgorithmParameters(finger, type, value); }
	void OnSetFingerSpacing(double value) { return mHardware.OnSetFingerSpacing(value); }
	void OnSetBendUpThreshold(double value) { return mHardware.OnSetBendUpThreshold(value); }
	void OnSetBendDownThreshold(double value) { return mHardware.OnSetBendDownThreshold(value); }
	void OnSetThumbOffset(VRTRIX::VRTRIXVector_t value, VRTRIX::Joint joint, VRTRIX::HandType type) { return mHardware.OnSetThumbOffset(value, joint, type); }

	//--- Joint set management.
	void	DefineHierarchy				();				//!< Define model template hierarchy.
	void	Bind();										//!< Bind models
	void	UnBind();									//!< Unbind models

	//--- Channel list manipulation.
	int		GetChannelCount()					{	return mHardware.GetChannelCount();				}
	int		GetChannelParent(int pMarkerIndex)	{	return mHardware.GetChannelParent(pMarkerIndex);}
	const char*	GetChannelName(int pMarkerIndex){	return mHardware.GetChannelName(pMarkerIndex);	}

    //--- Model Template binding and unbinding notification callback.
    virtual bool ModelTemplateBindNotify( FBModel* pModel,int pIndex, FBModelTemplate* pModelTemplate );
    virtual bool ModelTemplateUnBindNotify( int pIndex, FBModelTemplate* pModelTemplate );

    //--- Setup character and story track
    bool    SetupRecording();
    void    PrepareSetupRecording(FBString pClipDirectory);
	bool	SetupMocapCharacter		();				//!< Test if characterization process can be start.

    //--- Operation Status
    OperationStatus    GetOperationState();
    void    SetOperationState(OperationStatus pState);

	//--- Stop displaying process to local message on model unbind
	void	EventUIIdle( HISender pSender, HKEvent pEvent );

private:
    //--- Info update
    void    UpdateInfo(FBString pInfo, FBString pStatus);

    // Process global data on template models to local
    void    ProcessGlobalToLocal();
    void    SetupLocalGlobal(bool pGlobal);

    // Speech
    void    ResetRecording();

public:
    ORHardwareVRTRIXGlove       mHardware;					//!< Hardware abstraction object.
    FBModelTemplate*			mRootTemplate;				//!< Root model binding.

private:
	FBSystem					mSystem;
    FBCharacter*                mMocapCharacter;
    FBCharacter*                mTargetCharacter;

	DataChannel					mChannels[BoneNum];	//!< Data channels.
	FBPropertyBool				UseReferenceTransformation;             // !< Apply reference transformation on incoming global data.
	bool						mHierarchyIsDefined;                    //!< True if the hierarchy is already defined

	FBPlayerControl				mPlayerControl;                         //!< To get play mode for recording.
	FBApplication				mApplication;
	bool						mHasAnimationToTranspose;
	bool						mPlotting;

    // Setup recording
    FBString                    mClipDirectory;
    bool                        mReadyToSetupRecording;
    const char*                 mMocapCharacterName;

    // Operation status
    OperationStatus             mOperationState;
};

