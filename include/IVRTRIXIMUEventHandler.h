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
#define IMU_NUM 6

namespace VRTRIX {
    //! HandType enum.
    /*! Enum values of hand type. */
	enum HandType {
		Hand_None = 0,	   
		Hand_Other = 1,  
		Hand_Left = 2,
		Hand_Right = 3, 
		Hand_Both = 4,  // Currently not supported
	};

    //! Data glove initMode enum.
    /*! Enum values of glove initialization mode. */
	enum InitMode
	{
		InitMode_None = 0,
		InitMode_Normal = 1,
		InitMode_Advanced = 2,
		InitMode_GloveStatusChecking = 3,
	};


    //! GLOVEVERSION enum.
    /*! Enum values of data gloves hardware version. */
	enum GLOVEVERSION {
		DK1,
		DK2,
		PRO
	};

    //! Joint enum.
    /*! Enum values of data gloves supported hand joints. */
	enum Joint {
		Wrist_Joint = 0,
		Thumb_Proximal = 1,
		Thumb_Intermediate = 2,
		Thumb_Distal = 3,
		Index_Proximal = 4,
		Index_Intermediate = 5,
		Index_Distal = 6,
		Middle_Proximal = 7,
		Middle_Intermediate = 8,
		Middle_Distal = 9,
		Ring_Proximal = 10,
		Ring_Intermediate = 11,
		Ring_Distal = 12,
		Pinky_Proximal = 13,
		Pinky_Intermediate = 14,
		Pinky_Distal = 15,
		Joint_MAX = 16
	};


    //! Finger bend state enum.
    /*! Enum values of data gloves finger bending state. */
	enum VRTRIXFingerBendState {
		VRTRIXFinger_None = 0,
		VRTRIXFinger_BendUp = 1,
		VRTRIXFinger_BendDown = 2,
		VRTRIXFinger_BendUpStop = 3,
		VRTRIXFinger_BendDownStop = 4,
	};

    //! Data gloves status enum.
    /*! Enum values of data gloves hardware status. */
	enum HandStatus 
	{
		HandStatus_None,
		HandStatus_Idle,
		HandStatus_Running,
		HandStatus_LowBattery,
		HandStatus_BatteryFull,
		HandStatus_Paired,
		HandStatus_MagAbnormal,
	};


    //! Initialization error enum.
    /*!	Enum values to pass into InitDataGlove to identify what kind of initialization error is arised.*/
	enum EInitError
	{
		InitError_None = 0,
		InitError_Unknown = 1,
		InitError_PortBusy = 2,
		InitError_ConnectionRefused = 3,
		InitError_ConnectionReset = 4,
		InitError_NoSuchDevice = 5,
	};

    //! IMU error enum.
    /*!	Enum values to pass into methods to identify what kind of IMU error is arised. */
	enum EIMUError
	{
		IMUError_None = 0,
		IMUError_Unknown = 1,
		IMUError_ConnectionAorted = 2,
		IMUError_ConnectionInterrupted = 3,
		IMUError_ConnectionBusy = 4,
		IMUError_NotConnected = 5,
		IMUError_TimedOut = 6,
		IMUError_PortNotFound = 7,
		IMUError_PortAccessDenied = 8,
		IMUError_DataNotValid = 9,
	};

	
    //! Algorithm config type enum.
    /*!	Enum values to pass into algorithm tuning methods.*/
	enum AlgorithmConfig
	{
		AlgorithmConfig_ProximalSlerpUp = 0,
		AlgorithmConfig_ProximalSlerpDown = 1,
		AlgorithmConfig_DistalSlerpUp = 2,
		AlgorithmConfig_DistalSlerpDown = 3,
		AlgorithmConfig_FingerSpcaing = 4,
		AlgorithmConfig_FingerBendUpThreshold = 5,
		AlgorithmConfig_FingerBendDownThreshold = 6,
		AlgorithmConfig_ThumbOffset = 7,
		AlgorithmConfig_FinalFingerSpacing = 8,
		AlgorithmConfig_Max = 9,
	};

	//! Serial port information need for data streaming.
	struct PortInfo {
		/*! Baud Rate */
		int baud_rate;

		/*! Hand Type */
		HandType type;

		/*! Address of the serial port (this can be passed to the constructor of Serial). */
		std::string port;

		/*! Human readable description of serial device if available. */
		std::string description;

		/*! Hardware ID (e.g. VID:PID of USB serial devices) or "n/a" if not available. */
		std::string hardware_id;

		/*! Instance ID */
		std::string instance_id;
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
				<< a.qx << "," << a.qy << "," << a.qz << "," << a.qw  << "]" << std::endl;
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
				<< a.x << "," << a.y << "," << a.z  << "]" << std::endl;
			return o;
		}	//!< member operator override
	};


	//! Glove pose data structure used in C++ API.
	struct Pose
	{
		VRTRIXQuaternion_t imuData[Joint_MAX]; //!< IMU data in quaternion (Global coordinate)
		HandType type; //!< Glove hand type
		int calScore[IMU_NUM]; //!< IMU calibration score. Lower score means better calibration results.
		int radioStrength; //!< Glove wireless radio strength
		double battery; //!< Glove battery percentage
	};


	//! Glove hand event data structure used in C++ API.
	struct HandEvent {
		HandStatus stat; //!< Glove hardware status
		HandType type;	//!< Glove hand type
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
