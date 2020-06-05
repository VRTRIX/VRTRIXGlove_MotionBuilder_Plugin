// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the VRTRIXDATAGLOVECLIENT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// VRTRIXDATAGLOVECLIENT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once
#ifdef VRTRIXDATAGLOVECLIENT_EXPORTS
#define VRTRIXDATAGLOVECLIENT_API __declspec(dllexport)
#else
#define VRTRIXDATAGLOVECLIENT_API __declspec(dllimport)
#endif

#include "IVRTRIXIMUEventHandler.h"

namespace VRTRIX
{
	//!  VRTRIX Data Glove interface class. 
	/*!
		Interface class that contains most APIs for calling
	*/
	class IVRTRIXDataGloveClient
	{
	public:
		virtual ~IVRTRIXDataGloveClient() {};
		/** Connect VRTRIX Data Glove using TCP protocol
		* @param eError: return the error during data streaming, if any.
		* @param info: struct contains port information.
		* @returns void.
		*/
		virtual void ConnectDataGlove(EIMUError &eError, PortInfo info) = 0;

		/** Stop the data streaming and disconnect the tcp connection
		*
		* @param eError: return the error during closing the connection, if any.
		* @returns void
		*/
		virtual void DisconnectDataGlove(EIMUError &eError) = 0;

		/** Perform hardware calibrate process.
		*	Note: All data gloves have performed IN-FACTORY hardware calibration, no need to do it again
		*   unless the environment magnetic field has been changed dramatically.
		* @param eError: return the error during calibration, if any.
		* @returns void.
		*/
		virtual void HardwareCalibrate(EIMUError &eError) = 0;

		/** Trigger a haptic pulse to the glove.
		* @param eError: return the error during vibration, if any.
		* @returns void.
		*/
		virtual void Vibrate(EIMUError &eError) = 0;

		/** Trigger a period of haptic pulse to the glove.
		* @param eError: return the error during vibration, if any.
		* @param msDurationMillisec: the duration of pulse in millisecond
		* @returns void.
		*/
		virtual void VibratePeriod(EIMUError & eError, int msDurationMillisec) = 0;

		/** Toggle vibration status (on -> off, off -> on)
		* @param eError: return the error during toggle vibration, if any.
		* @returns void.
		*/
		virtual void ToggleVibration(EIMUError & eError) = 0;

		/** Align the fingers' orientations to hand.
		*
		* @param eError: return the error during software alignment, if any.
		* @returns void
		*/
		virtual void SoftwareAlign(EIMUError &eError) = 0;

		/** Switch to advanced mode during runtime
		*
		* @param eError: return the error during switching to advanced mode during runtime, if any.
		* @param advancedMode: advanced mode flag.
		* @returns void
		*/
		virtual void SwitchToAdvancedMode(EIMUError & eError, bool advancedMode) = 0;

		/** Switch data glove hardware version
		*
		* @param eError: return the error during switch hardware version, if any.
		* @param version: hardware version specified
		* @returns void
		*/
		virtual void SwitchHardwareVersion(EIMUError & eError, GLOVEVERSION version) = 0;

		/** Set radio channel limit
		*
		* @param eError: return the error during set radio channel limit, if any.
		* @param upperBound: top bound of radio channel used for glove (should be less than 100 and greater than 0)
		* @param lowerBound: low bound of radio channel used for glove (should be less than 100 and greater than 0)
		* @returns void
		*/
		virtual void SetRadioChannelLimit(EIMUError & eError, int upperBound, int lowerBound) = 0;

		/** Trigger a radio channel hopping
		*
		* @param eError: return the error during channel hopping, if any.
		* @param channel: radio channel specified
		* @returns void
		*/
		virtual void ChannelHopping(EIMUError & eError, int channel) = 0;

		/** Slerp algorithm tuning
		*
		* @param eError: return the error during slerp algorithm tuning, if any.
		* @param finger: finger joint name (use intermediate joint of each finger to tune algorithm).
		* @param type: algorithm configuration type.
		* @param value: value to tune.
		* @param vec: vector to tune the offset.
		* @returns void
		*/
		virtual void AlgorithmTuning(EIMUError & eError, Joint finger, AlgorithmConfig type, double value = 0, VRTRIXVector_t vec = { 0,0,0 }) = 0;

		/** Register data call back event handler class.
		*
		* @param pEventHandler: the call back event handler class.
		* @param pUserParam: the user-defined pointer.
		* @returns void
		*/
		virtual void RegisterIMUDataCallback(IVRTRIXIMUEventHandler* &pEventHandler, void* pUserParam = NULL) = 0;
	};

	/** Initialization of the data glove.
	*
	* @param eError: Initialization errror return..
	* @param advancedMode: The mode of initialization, default set to false.
	*		 Note that the advanced mode only need to set true when yaw rotation need to perform
	* @returns a interfacce pointer of IMU system.
	*/
	VRTRIXDATAGLOVECLIENT_API IVRTRIXDataGloveClient* InitDataGlove(EInitError &eError, InitMode mode = InitMode_Normal, GLOVEVERSION version = DK2);

	/** Uninit VRTRIXIMU.dll. Any interface pointers from the interface are
	* invalid after this point.
	*
	* @param m_pIMU: the IMU system pointer to close.
	*/
	VRTRIXDATAGLOVECLIENT_API void UnInit(IVRTRIXDataGloveClient * &pDataGlove);

}

