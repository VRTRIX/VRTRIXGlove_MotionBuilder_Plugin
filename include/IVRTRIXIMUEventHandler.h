//============= Copyright (c) VRTRIX INC, All rights reserved. ================
//
// Purpose: Contains the VRTRIX glove event handler base class. Some useful enums
//			and structs are also defined here.
//
//=============================================================================

#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#define IMU_NUM 6
#define BUF_SIZE 100

namespace VRTRIX {
	//! HandType enum.
	/*! Enum values of hand type. */
	enum HandType {
		Hand_None,
		Hand_Other,
		Hand_Left,
		Hand_Right,
		Hand_Both,  // Currently not supported
	};

	//! Data glove initMode enum.
	/*! Enum values of glove initialization mode. */
	enum InitMode
	{
		InitMode_None,
		InitMode_Normal,
		InitMode_Advanced,
		InitMode_GloveStatusChecking,
	};


	//! GLOVEVERSION enum.
	/*! Enum values of data gloves hardware version. */
	enum GLOVEVERSION {
		PRO7,
		PRO11,
		PRO12
	};

	//! Joint enum.
	/*! Enum values of data gloves supported hand joints. */
	enum Joint {
		Wrist_Joint,
		Thumb_Proximal,
		Thumb_Intermediate,
		Thumb_Distal,
		Index_Proximal,
		Index_Intermediate,
		Index_Distal,
		Middle_Proximal,
		Middle_Intermediate,
		Middle_Distal,
		Ring_Proximal,
		Ring_Intermediate,
		Ring_Distal,
		Pinky_Proximal,
		Pinky_Intermediate,
		Pinky_Distal,
		Joint_MAX = 16
	};


	//! Finger bend state enum.
	/*! Enum values of data gloves finger bending state. */
	enum VRTRIXFingerBendState {
		VRTRIXFinger_None,
		VRTRIXFinger_BendUp,
		VRTRIXFinger_BendDown,
		VRTRIXFinger_BendUpStop,
		VRTRIXFinger_BendDownStop,
	};

	//! Data gloves status enum.
	/*! Enum values of data gloves hardware status. */
	enum HandStatus
	{
		HandStatus_None,
		HandStatus_Connected,
		HandStatus_Disconnected,
		HandStatus_PortOpened,
		HandStatus_PortClosed,
		HandStatus_PortInterrupted,
		HandStatus_ChannelHopping,
		HandStatus_LowBattery,
		HandStatus_BatteryFull,
		HandStatus_Paired,
		HandStatus_MagAbnormal,
		HandStatus_Calibrated,
	};


	//! Initialization error enum.
	/*!	Enum values to pass into InitDataGlove to identify what kind of initialization error is arised.*/
	enum EInitError
	{
		InitError_None,
		InitError_Unknown,
		InitError_PortBusy,
		InitError_ConnectionRefused,
		InitError_ConnectionReset,
		InitError_NoSuchDevice,
	};

	//! IMU error enum.
	/*!	Enum values to pass into methods to identify what kind of IMU error is arised. */
	enum EIMUError
	{
		IMUError_None,
		IMUError_Unknown,
		IMUError_ConnectionAborted,
		IMUError_ConnectionInterrupted,
		IMUError_ConnectionBusy,
		IMUError_NotConnected,
		IMUError_TimedOut,
		IMUError_PortNotFound,
		IMUError_PortAccessDenied,
		IMUError_DataNotValid,
	};


	//! Algorithm config type enum.
	/*!	Enum values to pass into algorithm tuning methods.*/
	enum AlgorithmConfig
	{
		AlgorithmConfig_ProximalSlerpUp,
		AlgorithmConfig_ProximalSlerpDown,
		AlgorithmConfig_DistalSlerpUp,
		AlgorithmConfig_DistalSlerpDown,
		AlgorithmConfig_FingerSpcaing,
		AlgorithmConfig_FingerBendUpThreshold,
		AlgorithmConfig_FingerBendDownThreshold,
		AlgorithmConfig_ThumbOffset,
		AlgorithmConfig_FinalFingerSpacing,
		AlgorithmConfig_ThumbSlerpOffset,
		AlgorithmConfig_Max = 10,
	};

	//! Serial port information need for data streaming.
	struct PortInfo {
		/*! Baud Rate */
		int baud_rate;

		/*! Index number of data glove ports */
		int index = 16;

		/*! Hand Type */
		HandType type;

		/*! Address of the serial port (this can be passed to the constructor of Serial). */
		char port[BUF_SIZE];

		/*! Human readable description of serial device if available. */
		char description[BUF_SIZE];

		/*! Hardware ID (e.g. VID:PID of USB serial devices) or "n/a" if not available. */
		char hardware_id[BUF_SIZE];

		/*! Instance ID */
		char instance_id[BUF_SIZE];
	};

	//! Quaternion data structure used in C++ API.
	struct VRTRIXQuaternion_t
	{
		float qx; //!< x component in quaternion
		float qy; //!< y component in quaternion
		float qz; //!< z component in quaternion
		float qw; //!< w component in quaternion
		friend std::ostream& operator << (std::ostream &o, const VRTRIXQuaternion_t a) {
			o << "[" << std::setiosflags(std::ios::fixed) << std::setprecision(4)
				<< a.qx << "," << a.qy << "," << a.qz << "," << a.qw << "]" << std::endl;
			return o;
		}	//!< member operator override
	};

	//! 3D Vector data structure used in C++ API.
	struct VRTRIXVector_t
	{
		float x; //!< x component in vector
		float y; //!< y component in vector
		float z; //!< z component in vector
		friend std::ostream& operator << (std::ostream &o, const VRTRIXVector_t a) {
			o << "[" << std::setiosflags(std::ios::fixed) << std::setprecision(4)
				<< a.x << "," << a.y << "," << a.z << "]" << std::endl;
			return o;
		}	//!< member operator override
	};


	//! Glove pose data structure used in C++ API.
	struct Pose
	{
		VRTRIXQuaternion_t imuData[Joint_MAX]; //!< IMU data in quaternion (Global coordinate)
		HandType type; //!< Glove hand type
		int dataRate; //!< Glove data rate (Hz)
		int channel; //!< Glove radio channel (1-99)
		int calScore[IMU_NUM]; //!< IMU calibration score. Lower score means better calibration results.
		int radioStrength; //!< Glove wireless radio strength
		double battery; //!< Glove battery percentage
	};

	//! Saved current alignment params.
	struct AlignmentParameter {
		VRTRIXQuaternion_t IMUAlignmentYaw[Joint_MAX]; //!<Finger yaw alignment param
		VRTRIXQuaternion_t IMUAlignmentTPosePitch[Joint_MAX]; //!<Finger t-pose pitch alignment param
		VRTRIXQuaternion_t IMUAlignmentOKPosePitch[Joint_MAX]; //!<Finger ok-pose pitch alignment param
	};

	//! Glove hand event data structure used in C++ API.
	struct HandEvent {
		HandStatus stat; //!< Glove hardware status
		HandType type;	//!< Glove hand type
		AlignmentParameter param; //!< Glove calibration parameters
	};

	//!  VRTRIX IMU event handler class. 
	/*!
		Interface class that define the function header for handling the IMU event including pose data receiving and other events.
	*/
	class IVRTRIXIMUEventHandler
	{
	public:
		/** Uninitialization (Destructor)
		*/
		virtual ~IVRTRIXIMUEventHandler(void) {};


		/** OnReceivedNewPose event call back function implement
		*
		* @param pose: Pose struct returned by the call back function
		* @param pUserParam: user defined parameter
		* @returns void
		*/
		virtual void OnReceivedNewPose(Pose pose, void* pUserParam) = 0;

		/** OnReceivedNewEvent event call back function implement
		*
		* @param event: Event struct returned by the call back function
		* @param pUserParam: user defined parameter
		* @returns void
		*/
		virtual void OnReceivedNewEvent(HandEvent event, void* pUserParam) = 0;
	};
}// namespace VRTRIX
