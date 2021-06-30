#pragma once

#include "VRTRIXDataGloveClient.h"
#include <Eigen/Dense>
#include "statushandle.h"
#include "JsonHandler.h"
//#include "BoneHierarchySetup.h"

#define Scale	1
struct SkeletonNodeInfo
{
	std::string	mName;
	int			mParentChannel;
	double		mDefaultT[3];
	double		mDefaultR[3];
	double		mT[3];
	double		mR[3];
};

class ORHardwareVRTRIXGlove
{
public:
	ORHardwareVRTRIXGlove();
	virtual ~ORHardwareVRTRIXGlove();
    
	bool Init();

	//--- Opens and closes Kinect. returns true if successful
	bool	Open();								//!< Open Kinect.
	bool	Close();							//!< Close Kinect.
	bool	GetSetupInfo	(std::string filePath = ""); //!< Get the setup information.

	//--- Hardware communication
	bool	StartDataStream	();						//!< Put the device in streaming mode.
	bool	StopDataStream	();						//!< Take the device out of streaming mode.

	bool	FetchMocapData	(FBTime &pTime);		//!< Fetch a data from Kinect.

    void    GetSkeletonJointsOrder(FBBodyNodeId* &pSkeletonJointsOrder);

    FBString GetHardWareName();
    double   GetAverageSensorFloorOffset();
    void     SetSensorFloorOffsetSet();

	//--- Channel & Channel data management
	int		GetChannelCount	()					{	return mChannelCount;						}
	const char*	GetChannelName	(int pChannel)	{	return mChannel[pChannel].mName.c_str();	}
	int		GetChannelParent(int pChannel)		{	return mChannel[pChannel].mParentChannel;	}
	FBVector3d GetDefaultT	(int pChannel)		{	SkeletonNodeInfo& lSI = mChannel[pChannel]; return FBVector3d(lSI.mDefaultT[0],lSI.mDefaultT[1],lSI.mDefaultT[2]);		}
	FBVector3d GetDefaultR	(int pChannel)		{	SkeletonNodeInfo& lSI = mChannel[pChannel]; return FBVector3d(lSI.mDefaultR[0],lSI.mDefaultR[1],lSI.mDefaultR[2]);		}
	double	GetDataTX		(int pChannel)		{ return mChannel[pChannel].mT[0]; }
	double	GetDataTY		(int pChannel)		{ return mChannel[pChannel].mT[1]; }
	double	GetDataTZ		(int pChannel)		{ return mChannel[pChannel].mT[2]; }
	double	GetDataRX       (int pChannel)      { return mChannel[pChannel].mR[0]; }
	double	GetDataRY		(int pChannel)		{ return mChannel[pChannel].mR[1]; }
	double	GetDataRZ		(int pChannel)		{ return mChannel[pChannel].mR[2]; }

	void SetConfigPath(std::string configPath);
	void SetConfig(IDataGloveConfig config);
	void GetConfig(IDataGloveConfig& config);
	void SetServerIP(std::string IP);
	std::string GetServerIP();
	void SetDeviceID(int deviceID);
	int GetDeviceID();
	void SetHardwareVersion(VRTRIX::GLOVEVERSION version);
	void SetModelOffset(FBVector3d xAxis, FBVector3d yAxis, FBVector3d zAxis, VRTRIX::HandType type);
	void OnTPoseCalibration();
	void OnOKPoseCalibration();
	void OnSaveHardwareCalibration();
	void OnAvancedModeEnabled(bool bIsEnabled);
	void OnReceivedNewPose(VRTRIX::Pose pose);
	//void OnReceivedCalibratedResult(VRTRIX::HandEvent event);
	void OnSetAlgorithmParameters(VRTRIX::Joint finger, VRTRIX::AlgorithmConfig type, double value);
	void OnSetFingerSpacing(double value);
	void OnSetFinalFingerSpacing(double value);
	void OnSetBendUpThreshold(double value);
	void OnSetBendDownThreshold(double value);
	void OnSetThumbOffset(VRTRIX::VRTRIXVector_t offset, VRTRIX::Joint joint, VRTRIX::HandType type);
	void OnSetFingerOffset(VRTRIX::VRTRIXVector_t offset, VRTRIX::Joint joint, VRTRIX::HandType type);
	//void OnLoadAlignParam(IDataGloveConfig config, VRTRIX::HandType type);

	void OnRegisterCallback(void* device);

private:
	void HandHierarchySetup(std::vector<FBTVector>& mLocalTranslationR, std::vector<FBTVector>& mLocalTranslationL, std::string filePath = "");
	void SkeletonHierarchySetup(std::vector<SkeletonNodeInfo> &mChannel, std::string filePath = "");
	void parseHandHierarchySetup(Json::Value &cfg_root, std::vector<FBTVector>& mLocalTranslationR, std::vector<FBTVector>& mLocalTranslationL);
	void parseSkeletonHierarchySetup(Json::Value &cfg_root, std::vector<SkeletonNodeInfo> &mChannel);

private:
	std::string m_serverIP;
	int m_deviceID;
	std::string m_configPath;
	IDataGloveConfig    m_cfg;
	std::vector<SkeletonNodeInfo>	mChannel;//!< Channel data & info.
	std::vector<FBTVector>	mLocalTranslationL;
	std::vector<FBTVector>	mLocalTranslationR;
	int			mChannelCount;								//!< Channel count.
	int			mHandJointCount;
	void*		mFBDevice;

	VRTRIX::GLOVEVERSION	mHardwareVersion;
	VRTRIX::IVRTRIXDataGloveClient*     m_pLeftHandDataGlove;
	VRTRIX::IVRTRIXDataGloveClient*     m_pRightHandDataGlove;
	VRTRIX::IVRTRIXIMUEventHandler* pLHEventHandler;
	VRTRIX::IVRTRIXIMUEventHandler* pRHEventHandler;
	VRTRIX::PortInfo		m_LHportInfo;
	VRTRIX::PortInfo		m_RHportInfo;
	VRTRIX::Pose			m_LHPose;
	VRTRIX::Pose			m_RHPose;
	std::vector<VRTRIX::VRTRIXQuaternion_t> m_LHIMUData;
	std::vector<VRTRIX::VRTRIXQuaternion_t> m_RHIMUData;
	std::vector<VRTRIX::VRTRIXVector_t> m_LHFingerOffset;
	std::vector<VRTRIX::VRTRIXVector_t> m_RHFingerOffset;
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

	int						RHandIndex;
	int						LHandIndex;
	std::string				RHandBoneName;
	std::string				LHandBoneName;

public:
    FBMocapJointsState* mKinectMocapJointsState;
	bool					m_bIsLHConnected;
	bool					m_bIsRHConnected;
	std::string				SkeletonRootName;
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
		ORHardwareVRTRIXGlove* pGlove = (ORHardwareVRTRIXGlove*)pUserParam;
		if (event.stat == VRTRIX::HandStatus_Connected) {
			event.type == VRTRIX::Hand_Left ? pGlove->m_bIsLHConnected = true : pGlove->m_bIsRHConnected = true;
		}

		if (event.stat == VRTRIX::HandStatus_Disconnected) {
			event.type == VRTRIX::Hand_Left ? pGlove->m_bIsLHConnected = false : pGlove->m_bIsRHConnected = false;
		}

		//if (event.stat == VRTRIX::HandStatus_Calibrated) {
		//	pGlove->OnReceivedCalibratedResult(event);
		//}
	}
};


