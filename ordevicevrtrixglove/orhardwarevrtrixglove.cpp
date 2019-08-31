#include "stdafx.h"
#include "orhardwarevrtrixglove.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define RADTODEGREE 180.0f/M_PI
#define DEGREETORAD M_PI/180.0f

static FBMatrix VRTRIXQuaternionToFBMatrix(VRTRIX::VRTRIXQuaternion_t quat);
static Eigen::Quaterniond CalculateStaticOffset(Eigen::Quaterniond target, Eigen::Quaterniond rot);
static Eigen::Quaterniond MBEuler2Quat(FBVector3d euler);
static Eigen::Vector3d QuatRotation(Eigen::Vector3d orig, Eigen::Quaterniond rot);
static void GetTransformOnRigidBody(FBTVector& transform, VRTRIX::VRTRIXQuaternion_t rotation, FBTVector offset, VRTRIX::HandType type);
/************************************************
 *    Constructor.
 ************************************************/
ORHardwareVRTRIXGlove::ORHardwareVRTRIXGlove() :
	mChannelCount(0),
	m_hNextSkeletonEvent(INVALID_HANDLE_VALUE),
	mOpened(false),
	//mKinectMocapJointsState(NULL),
	mAverageSensorFloorOffset(0.0),
	mHardwareVersion(VRTRIX::DK2),
	m_LHOffset(Eigen::Quaterniond::Identity()), 
	m_RHOffset(Eigen::Quaterniond::Identity()),
    mSensorFloorOffsetSet(false),
    mInitSuccessful(false),
	m_bIsLHDataReady(false),
	m_bIsRHDataReady(false),
	m_bIsLHCalibrated(false),
	m_bIsRHCalibrated(false)
{
    
}


/************************************************
 *    Destructor.
 ************************************************/
ORHardwareVRTRIXGlove::~ORHardwareVRTRIXGlove()
{
    if (m_hNextSkeletonEvent && (m_hNextSkeletonEvent != INVALID_HANDLE_VALUE))
    {
        CloseHandle(m_hNextSkeletonEvent);
    }
    //if (mKinectMocapJointsState)
    //{
    //    delete mKinectMocapJointsState;
    //}
}

bool ORHardwareVRTRIXGlove::Init()
{
	VRTRIX::EInitError eInitError;
	//Initialize event handler.
	pLHEventHandler = new CVRTRIXIMUEventHandler();	
	pRHEventHandler = new CVRTRIXIMUEventHandler();
	
	//Initialize data glove.
	m_pLeftHandDataGlove = InitDataGlove(eInitError, VRTRIX::InitMode_Normal, mHardwareVersion);
	if (eInitError != VRTRIX::InitError_None) {
		std::cout << "Error: " << eInitError << std::endl;
		mInitSuccessful = false;
		return false;
	}

	m_pRightHandDataGlove = InitDataGlove(eInitError, VRTRIX::InitMode_Normal, mHardwareVersion);
	if (eInitError != VRTRIX::InitError_None) {
		std::cout << "Error: " << eInitError << std::endl;
		mInitSuccessful = false;
		return false;
	}

	//Register event call back and perform events handling/pose updating.
	m_pLeftHandDataGlove->RegisterIMUDataCallback(pLHEventHandler, this);
	m_pRightHandDataGlove->RegisterIMUDataCallback(pRHEventHandler, this);

	mInitSuccessful = true;
    return true;
}


/************************************************
 *    Open device communications.
 ************************************************/
bool ORHardwareVRTRIXGlove::Open()
{
    if( !mInitSuccessful )
        return false;
	
	VRTRIX::EIMUError eIMUError;
	//Prepare PortInfo struct and open the data streaming serial port of glove.
	//Note: the default baud_rate is 1000000 and should NOT be changed.
	m_LHportInfo.baud_rate = 1000000;
	m_LHportInfo.type = VRTRIX::Hand_Left;
	m_pLeftHandDataGlove->OpenPort(eIMUError, m_LHportInfo);

	if (eIMUError == VRTRIX::IMUError_None) {
		//Print out full port information
		std::cout << "PORT DESCIPTION: " << m_LHportInfo.description << std::endl;
		std::cout << "PORT HARDWARE ID: " << m_LHportInfo.hardware_id << std::endl;
		std::cout << "PORT INSTANCE ID: " << m_LHportInfo.instance_id << std::endl;
		std::cout << "PORT NAME: " << m_LHportInfo.port << std::endl;
		std::cout << "PORT BAUD RATE: " << m_LHportInfo.baud_rate << std::endl;
	}
	else {
		return false;
	}

	m_RHportInfo.baud_rate = 1000000;
	m_RHportInfo.type = VRTRIX::Hand_Right;
	m_pRightHandDataGlove->OpenPort(eIMUError, m_RHportInfo);

	if (eIMUError == VRTRIX::IMUError_None) {
		//Print out full port information
		std::cout << "PORT DESCIPTION: " << m_RHportInfo.description << std::endl;
		std::cout << "PORT HARDWARE ID: " << m_RHportInfo.hardware_id << std::endl;
		std::cout << "PORT INSTANCE ID: " << m_RHportInfo.instance_id << std::endl;
		std::cout << "PORT NAME: " << m_RHportInfo.port << std::endl;
		std::cout << "PORT BAUD RATE: " << m_RHportInfo.baud_rate << std::endl;
	}
	else {
		return false;
	}
	return true;
}

/************************************************
 *    Start data streaming from device.
 ************************************************/
bool ORHardwareVRTRIXGlove::StartDataStream()
{
    if (!mOpened)
    {
		VRTRIX::EIMUError eIMUError;
		m_pLeftHandDataGlove->StartDataStreaming(eIMUError, m_LHportInfo);
		if (eIMUError != VRTRIX::IMUError_None) {
			m_pLeftHandDataGlove->ClosePort(eIMUError);
			UnInit(m_pLeftHandDataGlove);
			return false;
		}
		m_pRightHandDataGlove->StartDataStreaming(eIMUError, m_RHportInfo);
        if (eIMUError != VRTRIX::IMUError_None) {
			m_pRightHandDataGlove->ClosePort(eIMUError);
			UnInit(m_pRightHandDataGlove);
			return false;
		}
		mOpened = true;

		OnAvancedModeEnabled(m_cfg.mAdvancedMode);
		OnSetFingerSpacing(m_cfg.mFingerSpacing);
		OnSetFinalFingerSpacing(m_cfg.mFinalFingerSpacing);
		OnSetBendUpThreshold(m_cfg.mBendUpThreshold);
		OnSetBendDownThreshold(m_cfg.mBendDownThreshold);
		
		VRTRIX::VRTRIXVector_t offset = { (float)m_cfg.mLHThumbOffset[0].mValue[0], (float)m_cfg.mLHThumbOffset[0].mValue[1],(float)m_cfg.mLHThumbOffset[0].mValue[2] };	
		OnSetThumbOffset(offset, VRTRIX::Thumb_Proximal, VRTRIX::Hand_Left);
	    
		offset = { (float)m_cfg.mLHThumbOffset[1].mValue[0], (float)m_cfg.mLHThumbOffset[1].mValue[1],(float)m_cfg.mLHThumbOffset[1].mValue[2] };	
		OnSetThumbOffset(offset, VRTRIX::Thumb_Intermediate, VRTRIX::Hand_Left);
	
		offset = { (float)m_cfg.mLHThumbOffset[2].mValue[0], (float)m_cfg.mLHThumbOffset[2].mValue[1],(float)m_cfg.mLHThumbOffset[2].mValue[2] };	
		OnSetThumbOffset(offset, VRTRIX::Thumb_Distal, VRTRIX::Hand_Left);
	
		offset = { (float)m_cfg.mRHThumbOffset[0].mValue[0], (float)m_cfg.mRHThumbOffset[0].mValue[1],(float)m_cfg.mRHThumbOffset[0].mValue[2] };	
		OnSetThumbOffset(offset, VRTRIX::Thumb_Proximal, VRTRIX::Hand_Right);
	    
		offset = { (float)m_cfg.mRHThumbOffset[1].mValue[0], (float)m_cfg.mRHThumbOffset[1].mValue[1],(float)m_cfg.mRHThumbOffset[1].mValue[2] };	
		OnSetThumbOffset(offset, VRTRIX::Thumb_Intermediate, VRTRIX::Hand_Right);
	
		offset = { (float)m_cfg.mRHThumbOffset[2].mValue[0], (float)m_cfg.mRHThumbOffset[2].mValue[1],(float)m_cfg.mRHThumbOffset[2].mValue[2] };	
		OnSetThumbOffset(offset, VRTRIX::Thumb_Distal, VRTRIX::Hand_Right);
	
		OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, m_cfg.mProximalSlerpDownValue[0]);
		OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, m_cfg.mProximalSlerpDownValue[1]);
		OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, m_cfg.mProximalSlerpDownValue[2]);
		OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpDown, m_cfg.mProximalSlerpDownValue[3]);
		OnSetAlgorithmParameters(VRTRIX::Thumb_Distal , VRTRIX::AlgorithmConfig_ProximalSlerpDown, m_cfg.mProximalSlerpDownValue[4]);
	
		OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, m_cfg.mProximalSlerpUpValue[0]);
		OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, m_cfg.mProximalSlerpUpValue[1]);
		OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, m_cfg.mProximalSlerpUpValue[2]);
		OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_ProximalSlerpUp, m_cfg.mProximalSlerpUpValue[3]);
		OnSetAlgorithmParameters(VRTRIX::Thumb_Distal , VRTRIX::AlgorithmConfig_ProximalSlerpUp, m_cfg.mProximalSlerpUpValue[4]);
	
		OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, m_cfg.mDistalSlerpUpValue[0]);
		OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, m_cfg.mDistalSlerpUpValue[1]);
		OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, m_cfg.mDistalSlerpUpValue[2]);
		OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpUp, m_cfg.mDistalSlerpUpValue[3]);
		OnSetAlgorithmParameters(VRTRIX::Thumb_Distal , VRTRIX::AlgorithmConfig_DistalSlerpUp, m_cfg.mDistalSlerpUpValue[4]);
	
		OnSetAlgorithmParameters(VRTRIX::Index_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, m_cfg.mDistalSlerpDownValue[0]);
		OnSetAlgorithmParameters(VRTRIX::Middle_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, m_cfg.mDistalSlerpDownValue[1]);
		OnSetAlgorithmParameters(VRTRIX::Ring_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, m_cfg.mDistalSlerpDownValue[2]);
		OnSetAlgorithmParameters(VRTRIX::Pinky_Intermediate, VRTRIX::AlgorithmConfig_DistalSlerpDown, m_cfg.mDistalSlerpDownValue[3]);
		OnSetAlgorithmParameters(VRTRIX::Thumb_Distal , VRTRIX::AlgorithmConfig_DistalSlerpDown, m_cfg.mDistalSlerpDownValue[4]);

		return true;
    }
    return false;
}

/************************************************
 *    Close device communications.
 ************************************************/
bool ORHardwareVRTRIXGlove::Close()
{
    if (NULL != m_pLeftHandDataGlove)
    {
		VRTRIX::EIMUError eIMUError;
		m_pLeftHandDataGlove->ClosePort(eIMUError);
		UnInit(m_pLeftHandDataGlove);
    }

    if (NULL != m_pRightHandDataGlove)
    {
		VRTRIX::EIMUError eIMUError;
		m_pRightHandDataGlove->ClosePort(eIMUError);
		UnInit(m_pRightHandDataGlove);
    }
	mOpened = false;
	m_bIsLHCalibrated = false;
	m_bIsRHCalibrated = false;
    return true;
}


/************************************************
 *    Stop data streaming from device.
 ************************************************/
bool ORHardwareVRTRIXGlove::StopDataStream()
{
    if (NULL != m_pLeftHandDataGlove)
    {
		VRTRIX::EIMUError eIMUError;
		m_pLeftHandDataGlove->ClosePort(eIMUError);
		UnInit(m_pLeftHandDataGlove);
    }

    if (NULL != m_pRightHandDataGlove)
    {
		VRTRIX::EIMUError eIMUError;
		m_pRightHandDataGlove->ClosePort(eIMUError);
		UnInit(m_pRightHandDataGlove);
    }
	mOpened = false;
	m_bIsLHCalibrated = false;
	m_bIsRHCalibrated = false;
    return true;
}

/************************************************
 *    Get device setup information.
 ************************************************/
bool ORHardwareVRTRIXGlove::GetSetupInfo()
{
    //The initial skeleton hierarchy    
	mChannelCount    = BoneNum;
	SkeletonHierarchySetup(mChannel);
    for(int i = 0; i < mChannelCount; i++)
    {
        memcpy(mChannel[i].mDefaultT,mChannel[i].mT, sizeof(double)*3);
        memcpy(mChannel[i].mDefaultR,mChannel[i].mR, sizeof(double)*3);
    }
	HandHierarchySetup(mLocalTranslationR, mLocalTranslationL);
	//mKinectMocapJointsState = new FBMocapJointsState(mChannelCount);
    return true;
}

void ORHardwareVRTRIXGlove::GetSkeletonJointsOrder(FBBodyNodeId* &pSkeletonJointsOrder)
{
    pSkeletonJointsOrder = new FBBodyNodeId[mChannelCount];

    pSkeletonJointsOrder[0] = kFBHipsNodeId;
    pSkeletonJointsOrder[1] = kFBWaistNodeId;
    pSkeletonJointsOrder[2] = kFBNeckNodeId;
    pSkeletonJointsOrder[3] = kFBHeadNodeId;

    pSkeletonJointsOrder[4] = kFBLeftShoulderNodeId;
    pSkeletonJointsOrder[5] = kFBLeftElbowNodeId;
    pSkeletonJointsOrder[6] = kFBLeftWristNodeId;
    pSkeletonJointsOrder[7] = kFBLeftHandNodeId;

    pSkeletonJointsOrder[8] = kFBRightShoulderNodeId;
    pSkeletonJointsOrder[9] = kFBRightElbowNodeId;
    pSkeletonJointsOrder[10] = kFBRightWristNodeId;
    pSkeletonJointsOrder[11] = kFBRightHandNodeId;

    pSkeletonJointsOrder[12] = kFBLeftHipNodeId;
    pSkeletonJointsOrder[13] = kFBLeftKneeNodeId;
    pSkeletonJointsOrder[14] = kFBLeftAnkleNodeId;
    pSkeletonJointsOrder[15] = kFBLeftFootNodeId;

    pSkeletonJointsOrder[16] = kFBRightHipNodeId;
    pSkeletonJointsOrder[17] = kFBRightKneeNodeId;
    pSkeletonJointsOrder[18] = kFBRightAnkleNodeId;
    pSkeletonJointsOrder[19] = kFBRightFootNodeId;

	pSkeletonJointsOrder[22] = kFBRightThumbANodeId;
    pSkeletonJointsOrder[23] = kFBRightThumbBNodeId;
    pSkeletonJointsOrder[24] = kFBRightThumbCNodeId;

    pSkeletonJointsOrder[25] = kFBRightIndexANodeId;
    pSkeletonJointsOrder[26] = kFBRightIndexBNodeId;
    pSkeletonJointsOrder[27] = kFBRightIndexCNodeId;

    pSkeletonJointsOrder[28] = kFBRightMiddleANodeId;
	pSkeletonJointsOrder[29] = kFBRightMiddleBNodeId;
	pSkeletonJointsOrder[30] = kFBRightMiddleCNodeId;

    pSkeletonJointsOrder[31] = kFBRightRingANodeId;
    pSkeletonJointsOrder[32] = kFBRightRingBNodeId;
	pSkeletonJointsOrder[33] = kFBRightRingCNodeId;

	pSkeletonJointsOrder[34] = kFBRightPinkyANodeId;
    pSkeletonJointsOrder[35] = kFBRightPinkyBNodeId;
    pSkeletonJointsOrder[36] = kFBRightPinkyCNodeId;

	pSkeletonJointsOrder[37] = kFBLeftThumbANodeId;
    pSkeletonJointsOrder[38] = kFBLeftThumbBNodeId;
    pSkeletonJointsOrder[39] = kFBLeftThumbCNodeId;

    pSkeletonJointsOrder[40] = kFBLeftIndexANodeId;
    pSkeletonJointsOrder[41] = kFBLeftIndexBNodeId;
    pSkeletonJointsOrder[42] = kFBLeftIndexCNodeId;

    pSkeletonJointsOrder[43] = kFBLeftMiddleANodeId;
	pSkeletonJointsOrder[44] = kFBLeftMiddleBNodeId;
	pSkeletonJointsOrder[45] = kFBLeftMiddleCNodeId;

    pSkeletonJointsOrder[46] = kFBLeftRingANodeId;
    pSkeletonJointsOrder[47] = kFBLeftRingBNodeId;
	pSkeletonJointsOrder[48] = kFBLeftRingCNodeId;

	pSkeletonJointsOrder[49] = kFBLeftPinkyANodeId;
    pSkeletonJointsOrder[50] = kFBLeftPinkyBNodeId;
    pSkeletonJointsOrder[51] = kFBLeftPinkyCNodeId;

}

FBString ORHardwareVRTRIXGlove::GetHardWareName()
{
    return FBString("VRTRIXDataGloves");
}

double ORHardwareVRTRIXGlove::GetAverageSensorFloorOffset()
{
    return mAverageSensorFloorOffset;
}

void ORHardwareVRTRIXGlove::SetSensorFloorOffsetSet()
{
    mSensorFloorOffsetSet = true;
}

void ORHardwareVRTRIXGlove::SetConfig(IDataGloveConfig config)
{
	if (config.mHardwareVersion == 0 || config.mHardwareVersion == 1) {
		mHardwareVersion = VRTRIX::DK2;
	}
	else {
		mHardwareVersion = VRTRIX::PRO;
	}
	SetModelOffset(config.mLHModelOffset[0], config.mLHModelOffset[1], config.mLHModelOffset[2], VRTRIX::Hand_Left);
	SetModelOffset(config.mRHModelOffset[0], config.mRHModelOffset[1], config.mRHModelOffset[2], VRTRIX::Hand_Right);
	m_cfg = config;
}

void ORHardwareVRTRIXGlove::SetHardwareVersion(VRTRIX::GLOVEVERSION version)
{
	mHardwareVersion = version;
}

void ORHardwareVRTRIXGlove::SetModelOffset(FBVector3d xAxis, FBVector3d yAxis, FBVector3d zAxis, VRTRIX::HandType type)
{
	if (type == VRTRIX::Hand_Left) {
		Eigen::Vector3d XAxisL(xAxis[0], xAxis[1], xAxis[2]);
		Eigen::Vector3d YAxisL(yAxis[0], yAxis[1], yAxis[2]);
		Eigen::Vector3d ZAxisL(zAxis[0], zAxis[1], zAxis[2]);
		Eigen::Matrix3d offset;
		offset << XAxisL, YAxisL, ZAxisL;
		//if (abs(offset.determinant() - 1.0f) < 1e-6) {
			m_LHModelOffset = offset;
		//}
	}
	else if (type == VRTRIX::Hand_Right) {
		Eigen::Vector3d XAxisR(xAxis[0], xAxis[1], xAxis[2]);
		Eigen::Vector3d YAxisR(yAxis[0], yAxis[1], yAxis[2]);
		Eigen::Vector3d ZAxisR(zAxis[0], zAxis[1], zAxis[2]);
		Eigen::Matrix3d offset;
		offset << XAxisR, YAxisR, ZAxisR;
		//if (abs(offset.determinant() - 1.0f) < 1e-6) {
			m_RHModelOffset = offset;
		//}
	}
}

void ORHardwareVRTRIXGlove::OnTPoseCalibration()
{
	m_bIsLHCalibrated = false;
	m_bIsRHCalibrated = false;
}

void ORHardwareVRTRIXGlove::OnAvancedModeEnabled(bool bIsEnabled)
{
	VRTRIX::EIMUError error;
	m_pLeftHandDataGlove->SwitchToAdvancedMode(error, bIsEnabled);
	m_pRightHandDataGlove->SwitchToAdvancedMode(error, bIsEnabled);
}

void ORHardwareVRTRIXGlove::OnReceivedNewPose(VRTRIX::Pose pose)
{
	if (pose.type == VRTRIX::Hand_Left) {
		m_bIsLHDataReady = true;
		for (int i = 0; i < VRTRIX::Joint_MAX; ++i) {
			Eigen::Vector3d rotatedAxis = m_LHModelOffset * Eigen::Vector3d(pose.imuData[i].qx, pose.imuData[i].qy, pose.imuData[i].qz);
			Eigen::Quaterniond rot(-pose.imuData[i].qw, rotatedAxis[0], rotatedAxis[1], rotatedAxis[2]);
			if (!m_bIsLHCalibrated && i == (int)VRTRIX::Wrist_Joint) {
				Eigen::Quaterniond target = MBEuler2Quat(mChannel[LHandIndex].mDefaultR);
				m_LHOffset = CalculateStaticOffset(target, rot);
				m_bIsLHCalibrated = true;
			}
			rot = m_LHOffset * rot;
			m_LHPose.imuData[i] = { (float)rot.x(), (float)rot.y(), (float)rot.z(), (float)rot.w() };
		}
	}
	else if (pose.type == VRTRIX::Hand_Right) {
		m_bIsRHDataReady = true;
		for (int i = 0; i < VRTRIX::Joint_MAX; ++i) {
			Eigen::Vector3d rotatedAxis = m_RHModelOffset * Eigen::Vector3d(pose.imuData[i].qx, pose.imuData[i].qy, pose.imuData[i].qz);
			Eigen::Quaterniond rot(-pose.imuData[i].qw, rotatedAxis[0], rotatedAxis[1], rotatedAxis[2]);
			if (!m_bIsRHCalibrated && i == (int)VRTRIX::Wrist_Joint) {
				Eigen::Quaterniond target = MBEuler2Quat(mChannel[RHandIndex].mDefaultR);
				m_RHOffset = CalculateStaticOffset(target, rot);
				m_bIsRHCalibrated = true;
			}
			rot = m_RHOffset * rot;
			m_RHPose.imuData[i] = { (float)rot.x(), (float)rot.y(), (float)rot.z(), (float)rot.w() };
		}
	}
}

void ORHardwareVRTRIXGlove::OnSetAlgorithmParameters(VRTRIX::Joint finger, VRTRIX::AlgorithmConfig type, double value)
{	
    if( !mInitSuccessful ) return;
	VRTRIX::EIMUError eIMUError;
	m_pLeftHandDataGlove->AlgorithmTuning(eIMUError, finger, type, value);
	m_pRightHandDataGlove->AlgorithmTuning(eIMUError, finger, type, value);
}

void ORHardwareVRTRIXGlove::OnSetFingerSpacing(double value)
{
	if( !mInitSuccessful ) return;
	VRTRIX::EIMUError eIMUError;
	m_pLeftHandDataGlove->AlgorithmTuning(eIMUError, VRTRIX::Joint_MAX, VRTRIX::AlgorithmConfig_FingerSpcaing, value);
	m_pRightHandDataGlove->AlgorithmTuning(eIMUError, VRTRIX::Joint_MAX, VRTRIX::AlgorithmConfig_FingerSpcaing, value);
}

void ORHardwareVRTRIXGlove::OnSetFinalFingerSpacing(double value)
{
	if( !mInitSuccessful ) return;
	VRTRIX::EIMUError eIMUError;
	m_pLeftHandDataGlove->AlgorithmTuning(eIMUError, VRTRIX::Joint_MAX, VRTRIX::AlgorithmConfig_FinalFingerSpacing, value);
	m_pRightHandDataGlove->AlgorithmTuning(eIMUError, VRTRIX::Joint_MAX, VRTRIX::AlgorithmConfig_FinalFingerSpacing, value);
}

void ORHardwareVRTRIXGlove::OnSetBendUpThreshold(double value)
{	
	if( !mInitSuccessful ) return;
	VRTRIX::EIMUError eIMUError;
	m_pLeftHandDataGlove->AlgorithmTuning(eIMUError, VRTRIX::Joint_MAX, VRTRIX::AlgorithmConfig_FingerBendUpThreshold, value);
	m_pRightHandDataGlove->AlgorithmTuning(eIMUError, VRTRIX::Joint_MAX, VRTRIX::AlgorithmConfig_FingerBendUpThreshold, value);
}

void ORHardwareVRTRIXGlove::OnSetBendDownThreshold(double value)
{
	if( !mInitSuccessful ) return;
	VRTRIX::EIMUError eIMUError;
	m_pLeftHandDataGlove->AlgorithmTuning(eIMUError, VRTRIX::Joint_MAX, VRTRIX::AlgorithmConfig_FingerBendDownThreshold, value);
	m_pRightHandDataGlove->AlgorithmTuning(eIMUError, VRTRIX::Joint_MAX, VRTRIX::AlgorithmConfig_FingerBendDownThreshold, value);
}

void ORHardwareVRTRIXGlove::OnSetThumbOffset(VRTRIX::VRTRIXVector_t offset, VRTRIX::Joint joint, VRTRIX::HandType type)
{
	if( !mInitSuccessful ) return;
	VRTRIX::EIMUError eIMUError;
	switch (type) {
	case(VRTRIX::Hand_Left): {
		m_pLeftHandDataGlove->AlgorithmTuning(eIMUError, joint, VRTRIX::AlgorithmConfig_ThumbOffset, 0, offset);
		break;
	}
	case(VRTRIX::Hand_Right): {
		m_pRightHandDataGlove->AlgorithmTuning(eIMUError, joint, VRTRIX::AlgorithmConfig_ThumbOffset, 0, offset);
		break;
	}
	}
}
/************************************************
 *    Fetch one frame skeleton data from the Kinect.
 ************************************************/
bool ORHardwareVRTRIXGlove::FetchMocapData(FBTime &pTime)
{
	bool bIsRHFetched = false, bIsLHFetched = false;
	if (m_bIsRHDataReady) {

		//0:RightHand
		FBRVector rot = VRTRIXQuaternionToEuler(m_RHPose.imuData[VRTRIX::Wrist_Joint], VRTRIX::Hand_Right, VRTRIX::Wrist_Joint);
		mChannel[RHandIndex].mR[0] = rot[0];
		mChannel[RHandIndex].mR[1] = rot[1];
		mChannel[RHandIndex].mR[2] = rot[2];
		mChannel[RHandIndex].mT[0] = mLocalTranslationR[0][0];
		mChannel[RHandIndex].mT[1] = mLocalTranslationR[0][1];
		mChannel[RHandIndex].mT[2] = mLocalTranslationR[0][2];

		for (int i = 0; i < HandBoneNum - 1; ++i) {
			FBRVector rot = VRTRIXQuaternionToEuler(m_RHPose.imuData[(VRTRIX::Joint)i], VRTRIX::Hand_Right, (VRTRIX::Joint)i);

			mChannel[RHandIndex + i + 1].mR[0] = rot[0];
			mChannel[RHandIndex + i + 1].mR[1] = rot[1];
			mChannel[RHandIndex + i + 1].mR[2] = rot[2];

			int parent = mChannel[RHandIndex + i + 1].mParentChannel;
			FBTVector translation = { mChannel[parent].mT[0], mChannel[parent].mT[1], mChannel[parent].mT[2], 1 };
			if (parent == RHandIndex) {
				GetTransformOnRigidBody(translation, m_RHPose.imuData[parent - RHandIndex], mLocalTranslationR[i + 1], VRTRIX::Hand_Right);
			}
			else {
				GetTransformOnRigidBody(translation, m_RHPose.imuData[parent - RHandIndex - 1], mLocalTranslationR[i + 1], VRTRIX::Hand_Right);
			}
			mChannel[RHandIndex + i + 1].mT[0] = translation[0];
			mChannel[RHandIndex + i + 1].mT[1] = translation[1];
			mChannel[RHandIndex + i + 1].mT[2] = translation[2];
		}
		m_bIsRHDataReady = false;
		bIsRHFetched = true;
	}
	if (m_bIsLHDataReady) {

		FBRVector rot = VRTRIXQuaternionToEuler(m_LHPose.imuData[VRTRIX::Wrist_Joint], VRTRIX::Hand_Left, VRTRIX::Wrist_Joint);
	    mChannel[LHandIndex].mR[0] = rot[0];
	    mChannel[LHandIndex].mR[1] = rot[1];
	    mChannel[LHandIndex].mR[2] = rot[2];
		mChannel[LHandIndex].mT[0] = mLocalTranslationL[0][0];
	    mChannel[LHandIndex].mT[1] = mLocalTranslationL[0][1];
	    mChannel[LHandIndex].mT[2] = mLocalTranslationL[0][2];


		for (int i = 0; i < HandBoneNum - 1; ++i) {
			FBRVector rot = VRTRIXQuaternionToEuler(m_LHPose.imuData[(VRTRIX::Joint)i], VRTRIX::Hand_Left, (VRTRIX::Joint)i);

			mChannel[LHandIndex + i + 1].mR[0] = rot[0];
			mChannel[LHandIndex + i + 1].mR[1] = rot[1];
			mChannel[LHandIndex + i + 1].mR[2] = rot[2];

			int parent = mChannel[LHandIndex + i + 1].mParentChannel;

			FBTVector translation = { mChannel[parent].mT[0], mChannel[parent].mT[1], mChannel[parent].mT[2], 1};
			if (parent == LHandIndex) {
				GetTransformOnRigidBody(translation, m_LHPose.imuData[parent-LHandIndex], mLocalTranslationL[i+1], VRTRIX::Hand_Left);
			}
			else {
				GetTransformOnRigidBody(translation, m_LHPose.imuData[parent-LHandIndex-1], mLocalTranslationL[i+1], VRTRIX::Hand_Left);
			}
			mChannel[LHandIndex + i + 1].mT[0] = translation[0];
			mChannel[LHandIndex + i + 1].mT[1] = translation[1];
			mChannel[LHandIndex + i + 1].mT[2] = translation[2];
		}
		m_bIsLHDataReady = false;
		bIsLHFetched = true;
	}
	return bIsLHFetched || bIsRHFetched;
}


/** Convert VRTRIX Quat to Euler.(z-y-x convention)
	*
	* @param quat: VRTRIX Quaternion
	* @returns euler angle in FBRVector
	*/
FBRVector ORHardwareVRTRIXGlove::VRTRIXQuaternionToEuler(VRTRIX::VRTRIXQuaternion_t quat, VRTRIX::HandType type, VRTRIX::Joint joint)
{
	double r_w = quat.qw, r_x = quat.qx, r_y = quat.qy, r_z = quat.qz;

	//Get Euler Angle(case zyx) from quaternions
	double sinr = 2.0f * (r_y * r_z + r_w * r_x);
	double cosr = 1.0f - 2.0f * (r_x * r_x + r_y * r_y);
	double roll = atan2(sinr, cosr) * 180 / M_PI;

	double sinp = 2.0f * (r_w * r_y - r_x * r_z);
	double pitch;
	if (fabs(sinp) >= 1) {
		pitch = copysign(M_PI / 2, sinp) * 180 / M_PI;
	}
	else {
		pitch = asin(sinp) * 180 / M_PI;
	}
	double siny = 2.0f * (r_x * r_y + r_w * r_z);
	double cosy = 1.0f - 2.0f * (r_y * r_y + r_z * r_z);
	double yaw = atan2(siny, cosy) * 180 / M_PI;

	return FBRVector(roll, pitch, yaw);

}

/** Convert VRTRIX Quat to Matrix.(Absolute Pose Output)
	*
	* @param quat: VRTRIX Quaternion
	* @returns matrix in FBMatrix
	*/
static FBMatrix VRTRIXQuaternionToFBMatrix(VRTRIX::VRTRIXQuaternion_t quat)
{
    FBMatrix lMatrix;
    lMatrix(0,0) =  1-2*quat.qy*quat.qy-2*quat.qz*quat.qz;
	lMatrix(0,1) =  2 * quat.qx*quat.qy - 2 * quat.qz*quat.qw;
    lMatrix(0,2) =  2*quat.qx*quat.qz+2*quat.qy*quat.qw;

    lMatrix(1,0) =  2*quat.qx*quat.qy+2*quat.qz*quat.qw;
    lMatrix(1,1) =  1-2*quat.qx*quat.qx-2*quat.qz*quat.qz;
    lMatrix(1,2) =  2 * quat.qy*quat.qz - 2 * quat.qx*quat.qw;

    lMatrix(2,0) =  2 * quat.qx*quat.qz - 2 * quat.qy*quat.qw;
    lMatrix(2,1) =  2*quat.qy*quat.qy+2*quat.qx*quat.qw;
    lMatrix(2,2) =  1-2*quat.qx*quat.qx-2*quat.qy*quat.qy;

    lMatrix(3,3) =  1;
    return lMatrix;
}

static Eigen::Quaterniond CalculateStaticOffset(Eigen::Quaterniond target, Eigen::Quaterniond rot)
{
    return target * rot.inverse();
}

Eigen::Quaterniond MBEuler2Quat(FBVector3d euler)
{
	// Abbreviations for the various angular functions
    double cy = cos(euler[2] * 0.5 * DEGREETORAD);
    double sy = sin(euler[2] * 0.5 * DEGREETORAD);
    double cp = cos(euler[1] * 0.5 * DEGREETORAD);
    double sp = sin(euler[1] * 0.5 * DEGREETORAD);
    double cr = cos(euler[0] * 0.5 * DEGREETORAD);
    double sr = sin(euler[0] * 0.5 * DEGREETORAD);

    Eigen::Quaterniond q;
    q.w() = cy * cp * cr + sy * sp * sr;
    q.x() = cy * cp * sr - sy * sp * cr;
    q.y() = sy * cp * sr + cy * sp * cr;
    q.z() = sy * cp * cr - cy * sp * sr;

    return q;
}

/** Calculate transform of a rigid body given its original pose and the transform from the original points to the points need to be calculated
*
* @param transform: input/output transform of the tracked object.
* @param rotation: input rotation of the tracked object (Quaternions).
* @param offset: input offset of the tracked object that need to be performed.
* @returns void
*/
static void GetTransformOnRigidBody(FBTVector& transform, VRTRIX::VRTRIXQuaternion_t rotation, FBTVector offset, VRTRIX::HandType type) 
{
	Eigen::Quaterniond rot(rotation.qw, rotation.qx, rotation.qy, rotation.qz);
	Eigen::Vector3d transformOffset(offset[0], offset[1], offset[2]);
	transformOffset = QuatRotation(transformOffset, rot);
	transform[0] = transform[0] + transformOffset[0];
	transform[1] = transform[1] + transformOffset[1];
	transform[2] = transform[2] + transformOffset[2];
}


/** Rotate a given vector with a given rotation described in quaternion
*
* @param orig: the given vector
* @param rot: the given rotation in quaternion
* @returns the rotated vector.
*/
static Eigen::Vector3d QuatRotation(Eigen::Vector3d orig, Eigen::Quaterniond rot) {
	Eigen::Quaterniond p;
	p.w() = 0;
	p.vec() = orig;
	Eigen::Quaterniond rotatedP = rot * p * rot.inverse();
	return rotatedP.vec();
}

