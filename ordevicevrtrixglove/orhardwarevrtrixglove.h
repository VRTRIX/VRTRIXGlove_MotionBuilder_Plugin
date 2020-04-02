#pragma once
#include <VRTRIX_IMU.h>
#include <fbsdk/fbsdk.h>
#include "statushandle.h"
#include "BoneHierarchySetup.h"
#include <Eigen/Dense>
#include "JsonHandler.h"

class ORHardwareVRTRIXGlove
{
public:
	ORHardwareVRTRIXGlove();
	virtual ~ORHardwareVRTRIXGlove();
    
	bool Init();

	//--- Opens and closes Kinect. returns true if successful
	bool	Open();								//!< Open Kinect.
	bool	Close();							//!< Close Kinect.
	bool	GetSetupInfo	();						//!< Get the setup information.

	//--- Hardware communication
	bool	StartDataStream	();						//!< Put the device in streaming mode.
	bool	StopDataStream	();						//!< Take the device out of streaming mode.

	bool	FetchMocapData	(FBTime &pTime);		//!< Fetch a data from Kinect.
	FBRVector VRTRIXQuaternionToEuler(VRTRIX::VRTRIXQuaternion_t quat, VRTRIX::HandType type, VRTRIX::Joint joint);
    void    GetSkeletonJointsOrder(FBBodyNodeId* &pSkeletonJointsOrder);

    FBString GetHardWareName();
    double   GetAverageSensorFloorOffset();
    void     SetSensorFloorOffsetSet();

	//--- Channel & Channel data management
	int		GetChannelCount	()					{	return mChannelCount;						}
	const char*	GetChannelName	(int pChannel)	{	return mChannel[pChannel].mName;	}
	int		GetChannelParent(int pChannel)		{	return mChannel[pChannel].mParentChannel;	}
	FBVector3d GetDefaultT	(int pChannel)		{	SkeletonNodeInfo& lSI = mChannel[pChannel]; return FBVector3d(lSI.mDefaultT[0],lSI.mDefaultT[1],lSI.mDefaultT[2]);		}
	FBVector3d GetDefaultR	(int pChannel)		{	SkeletonNodeInfo& lSI = mChannel[pChannel]; return FBVector3d(lSI.mDefaultR[0],lSI.mDefaultR[1],lSI.mDefaultR[2]);		}
	double	GetDataTX		(int pChannel)		{	return mChannel[pChannel].mT[0];		}
	double	GetDataTY		(int pChannel)		{	return mChannel[pChannel].mT[1];		}
	double	GetDataTZ		(int pChannel)		{	return mChannel[pChannel].mT[2];		}
	double	GetDataRX       (int pChannel)      {	return mChannel[pChannel].mR[0];		}
	double	GetDataRY		(int pChannel)		{	return mChannel[pChannel].mR[1];		}
	double	GetDataRZ		(int pChannel)		{	return mChannel[pChannel].mR[2];		}

	void SetConfig(IDataGloveConfig config);
	void SetHardwareVersion(VRTRIX::GLOVEVERSION version);
	void SetModelOffset(FBVector3d xAxis, FBVector3d yAxis, FBVector3d zAxis, VRTRIX::HandType type);
	void OnTPoseCalibration(VRTRIX::AlignmentParameter& m_LHAlignParam, VRTRIX::AlignmentParameter& m_RHAlignParam);
	void OnAvancedModeEnabled(bool bIsEnabled);
	void OnReceivedNewPose(VRTRIX::Pose pose);
	void OnSetAlgorithmParameters(VRTRIX::Joint finger, VRTRIX::AlgorithmConfig type, double value);
	void OnSetFingerSpacing(double value);
	void OnSetFinalFingerSpacing(double value);
	void OnSetBendUpThreshold(double value);
	void OnSetBendDownThreshold(double value);
	void OnSetThumbOffset(VRTRIX::VRTRIXVector_t offset, VRTRIX::Joint joint, VRTRIX::HandType type);
	void OnLoadAlignParam(IDataGloveConfig config, VRTRIX::HandType type);

private:
	IDataGloveConfig    m_cfg;
	SkeletonNodeInfo	mChannel[BoneNum];//!< Channel data & info.
	FBTVector	mLocalTranslationL[HandBoneNum];
	FBTVector	mLocalTranslationR[HandBoneNum];
	int			mChannelCount;								//!< Channel count.
	
	VRTRIX::GLOVEVERSION	mHardwareVersion;
	VRTRIX::IVRTRIXIMU*     m_pLeftHandDataGlove;
	VRTRIX::IVRTRIXIMU*     m_pRightHandDataGlove;
	VRTRIX::IVRTRIXIMUEventHandler* pLHEventHandler;
	VRTRIX::IVRTRIXIMUEventHandler* pRHEventHandler;
	VRTRIX::PortInfo		m_LHportInfo;
	VRTRIX::PortInfo		m_RHportInfo;
	VRTRIX::Pose			m_LHPose;
	VRTRIX::Pose			m_RHPose;
	std::vector<VRTRIX::VRTRIXQuaternion_t> m_LHIMUData;
	std::vector<VRTRIX::VRTRIXQuaternion_t> m_RHIMUData;
	Eigen::Matrix3d			m_LHModelOffset;
	Eigen::Matrix3d			m_RHModelOffset;
	Eigen::Quaterniond		m_LHOffset;
	Eigen::Quaterniond		m_RHOffset;
	bool					m_bIsLHCalibrated;
	bool					m_bIsRHCalibrated;
	bool					m_bIsLHDataReady;
	bool					m_bIsRHDataReady;
    bool                    mInitSuccessful;
    bool                    mOpened;
	HANDLE                  m_hNextSkeletonEvent;
    double                  mAverageSensorFloorOffset;
    bool                    mSensorFloorOffsetSet;

public:
    FBMocapJointsState* mKinectMocapJointsState;
};

class CVRTRIXIMUEventHandler :public VRTRIX::IVRTRIXIMUEventHandler
{
	/** OnReceivedNewPose event call back function implement
	*
	* @param pose: Pose struct returned by the call back function
	* @param pUserParam: user defined parameter
	* @returns void
	*/
	void OnReceivedNewPose(VRTRIX::Pose pose, void* pUserParam) {

		ORHardwareVRTRIXGlove* pGlove = (ORHardwareVRTRIXGlove*)pUserParam;
		pGlove->OnReceivedNewPose(pose);
	}

	/** OnReceivedNewEvent event call back function implement
	*
	* @param event: Event struct returned by the call back function
	* @param pUserParam: user defined parameter
	* @returns void
	*/
	void OnReceivedNewEvent(VRTRIX::HandEvent event, void* pUserParam) {
		switch (event.stat) {
		case(VRTRIX::HandStatus_LowBattery): {
			std::cout << "Low Battery!" << std::endl;
			break;
		}
		case(VRTRIX::HandStatus_BatteryFull): {
			std::cout << "Battery Full!" << std::endl;
			break;
		}
		case(VRTRIX::HandStatus_Paired): {
			std::cout << "Data Glove Paired!" << std::endl;
			break;
		}
		case(VRTRIX::HandStatus_MagAbnormal): {
			std::cout << "Magnetic Abnormal Detected!" << std::endl;
			break;
		}
		default: break;
		}
	}
};


