#pragma once
#include <iostream>
#include <json/value.h>
#include <json/json.h>
#include <fbsdk/fbsdk.h>
#include <fstream>
#include <string>
#include <windows.h>

struct IDataGloveConfig {
	bool mAdvancedMode;
	int mHardwareVersion;
	double mFingerSpacing;
	double mFinalFingerSpacing;
	double mBendUpThreshold;
	double mBendDownThreshold;
	FBVector3d mLHThumbOffset[3];
	FBVector3d mRHThumbOffset[3];
	FBVector3d mLHModelOffset[3];
	FBVector3d mRHModelOffset[3];
	double mProximalSlerpDownValue[5];
	double mDistalSlerpDownValue[5];
	double mProximalSlerpUpValue[5];
	double mDistalSlerpUpValue[5];
	std::vector<VRTRIX::VRTRIXQuaternion_t> mLHIMUAlignmentTPosePitch;
	std::vector<VRTRIX::VRTRIXQuaternion_t> mLHIMUAlignmentOKPosePitch;
	std::vector<VRTRIX::VRTRIXQuaternion_t> mLHIMUAlignmentYaw;
	std::vector<VRTRIX::VRTRIXQuaternion_t> mRHIMUAlignmentTPosePitch;
	std::vector<VRTRIX::VRTRIXQuaternion_t> mRHIMUAlignmentOKPosePitch;
	std::vector<VRTRIX::VRTRIXQuaternion_t> mRHIMUAlignmentYaw;
	VRTRIX::VRTRIXQuaternion_t mLHWristOffset;
	VRTRIX::VRTRIXQuaternion_t mRHWristOffset;
};

class JsonHandler
{
public:
	JsonHandler()
	{
		Json::Value cfg_root;
		char result[ MAX_PATH ];
		current_dir =  std::string( result, GetModuleFileNameA( NULL, result, MAX_PATH ) );
	    std::string::size_type pos = current_dir.find_last_of( "\\/" );
		current_dir = current_dir.substr( 0, pos)+ "\\plugins\\DataGloveConfig.json";
		std::ifstream cfgfile(current_dir);
		if (cfgfile) // Verify that the file was open successfully
		{
			cfgfile >> cfg_root;
			parseDisplayCfg(cfg_root);
		}
		else {
			std::cerr << "File could not be opened!\n"; // Report error
														//std::cerr << "Error! " << strerror(errno) << std::endl; // Get some info as to why
		}
	}

	~JsonHandler()
	{
	}
	double round_nplaces(double value, int to)
	{
		double places = pow(10.0, to);
		return round(value * places) / places;
	}

	//// Read Json Matrix and return as FBVector3d
	void ReadJsonMatrix(Json::Value jsonMat, FBVector3d mat[3])
	{
		int rows = jsonMat.size();
		int cols = jsonMat[0].size();

		if (rows != 3 || cols != 3) return;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				mat[i].mValue[j] = jsonMat[i][j].asDouble();
			}
		}
	}

	//// Read Json Matrix and return as double array
	void ReadJsonVector(Json::Value jsonVec, double vec[5])
	{
		int size = jsonVec.size();
		if (size != 5) return;
		for (int i = 0; i < size; i++)
		{
			vec[i] = jsonVec[i].asDouble();
		}
	}

	//// Read Json Matrix and return as std vector
	void ReadJsonVector(Json::Value jsonMat, std::vector<VRTRIX::VRTRIXQuaternion_t>& vec)
	{
		int rows = jsonMat.size();
		int cols = jsonMat[0].size();

		if (rows != VRTRIX::Joint_MAX || cols != 4) return;
		for (int i = 0; i < rows; i++)
		{
			VRTRIX::VRTRIXQuaternion_t quat = { jsonMat[i][1].asFloat(), jsonMat[i][2].asFloat(), jsonMat[i][3].asFloat(), jsonMat[i][0].asFloat() };
			vec.push_back(quat);
		}
	}

	//// Read Json Matrix and return as quaternion
	void ReadJsonQuat(Json::Value jsonMat, VRTRIX::VRTRIXQuaternion_t& quat)
	{
		int size = jsonMat.size();

		if (size != 4) return;
		quat = { jsonMat[1].asFloat(), jsonMat[2].asFloat(), jsonMat[3].asFloat(), jsonMat[0].asFloat() };
	}

	//// Read FBVector3d and return as Json Matrix
	Json::Value WriteJsonMatrix(FBVector3d mat[3])
	{
		Json::Value jsonMat;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				jsonMat[i][j] = mat[i].mValue[j];
			}
		}
		return jsonMat;
	}

	//// Write TrackingVector3_t and return as Json Matrix
	Json::Value WriteJsonVec(double vec[5])
	{
		Json::Value jsonVec;
		for (int i = 0; i < 5; i++)
		{
			jsonVec[i] = vec[i];
		}
		return jsonVec;
	}

	//// Write vector and return as Json Matrix
	Json::Value WriteJsonVec(std::vector<VRTRIX::VRTRIXQuaternion_t>& vec)
	{
		Json::Value jsonMat;
		for (int i = 0; i < VRTRIX::Joint_MAX; i++)
		{
			jsonMat[i][0] = vec[i].qw;
			jsonMat[i][1] = vec[i].qx;
			jsonMat[i][2] = vec[i].qy;
			jsonMat[i][3] = vec[i].qz;
		}
		return jsonMat;
	}

	//// Write quaternion and return as Json Matrix
	Json::Value WriteJsonQuat(VRTRIX::VRTRIXQuaternion_t quat)
	{
		Json::Value jsonMat;
		jsonMat[0] = quat.qw;
		jsonMat[1] = quat.qx;
		jsonMat[2] = quat.qy;
		jsonMat[3] = quat.qz;
		return jsonMat;
	}

	void parseDisplayCfg(const Json::Value &cfg_root) {
		m_cfg.mAdvancedMode = cfg_root["mAdvancedMode"].asBool();
		m_cfg.mHardwareVersion = cfg_root["mHardwareVersion"].asUInt();
		m_cfg.mFingerSpacing = round_nplaces(cfg_root["mFingerSpacing"].asDouble(), 1);
		m_cfg.mFinalFingerSpacing = round_nplaces(cfg_root["mFinalFingerSpacing"].asDouble(), 1);
		m_cfg.mBendUpThreshold = round_nplaces(cfg_root["mBendUpThreshold"].asDouble(), 1);
		m_cfg.mBendDownThreshold = round_nplaces(cfg_root["mBendDownThreshold"].asDouble(), 1);
		ReadJsonMatrix(cfg_root["mLHThumbOffset"], m_cfg.mLHThumbOffset);
		ReadJsonMatrix(cfg_root["mRHThumbOffset"], m_cfg.mRHThumbOffset);
		ReadJsonMatrix(cfg_root["mLHModelOffset"], m_cfg.mLHModelOffset);
		ReadJsonMatrix(cfg_root["mRHModelOffset"], m_cfg.mRHModelOffset);
		ReadJsonVector(cfg_root["mProximalSlerpDownValue"], m_cfg.mProximalSlerpDownValue);
		ReadJsonVector(cfg_root["mDistalSlerpDownValue"], m_cfg.mDistalSlerpDownValue);
		ReadJsonVector(cfg_root["mProximalSlerpUpValue"], m_cfg.mProximalSlerpUpValue);
		ReadJsonVector(cfg_root["mDistalSlerpUpValue"], m_cfg.mDistalSlerpUpValue);

		ReadJsonVector(cfg_root["mLHIMUAlignmentTPosePitch"], m_cfg.mLHIMUAlignmentTPosePitch);
		ReadJsonVector(cfg_root["mLHIMUAlignmentOKPosePitch"], m_cfg.mLHIMUAlignmentOKPosePitch);
		ReadJsonVector(cfg_root["mLHIMUAlignmentYaw"], m_cfg.mLHIMUAlignmentYaw);
		ReadJsonVector(cfg_root["mRHIMUAlignmentTPosePitch"], m_cfg.mRHIMUAlignmentTPosePitch);
		ReadJsonVector(cfg_root["mRHIMUAlignmentOKPosePitch"], m_cfg.mRHIMUAlignmentOKPosePitch);
		ReadJsonVector(cfg_root["mRHIMUAlignmentYaw"], m_cfg.mRHIMUAlignmentYaw);
	
		ReadJsonQuat(cfg_root["mLHWristOffset"], m_cfg.mLHWristOffset);
		ReadJsonQuat(cfg_root["mRHWristOffset"], m_cfg.mRHWristOffset);
	}

	bool writeBack(IDataGloveConfig& cfg) {
		Json::Value root;
		root["mAdvancedMode"] = cfg.mAdvancedMode;
		root["mHardwareVersion"] = cfg.mHardwareVersion;
		root["mFingerSpacing"] = cfg.mFingerSpacing;
		root["mFinalFingerSpacing"] = cfg.mFinalFingerSpacing;
		root["mBendUpThreshold"] = cfg.mBendUpThreshold;
		root["mBendDownThreshold"] = cfg.mBendDownThreshold;

		root["mLHThumbOffset"] = WriteJsonMatrix(cfg.mLHThumbOffset);
		root["mRHThumbOffset"] = WriteJsonMatrix(cfg.mRHThumbOffset);
		root["mLHModelOffset"] = WriteJsonMatrix(cfg.mLHModelOffset);
		root["mRHModelOffset"] = WriteJsonMatrix(cfg.mRHModelOffset);

		root["mProximalSlerpDownValue"] = WriteJsonVec(cfg.mProximalSlerpDownValue);
		root["mDistalSlerpDownValue"] = WriteJsonVec(cfg.mDistalSlerpDownValue);
		root["mProximalSlerpUpValue"] = WriteJsonVec(cfg.mProximalSlerpUpValue);
		root["mDistalSlerpUpValue"] = WriteJsonVec(cfg.mDistalSlerpUpValue);

		root["mLHIMUAlignmentTPosePitch"] = WriteJsonVec(cfg.mLHIMUAlignmentTPosePitch);
		root["mLHIMUAlignmentOKPosePitch"] = WriteJsonVec(cfg.mLHIMUAlignmentOKPosePitch);
		root["mLHIMUAlignmentYaw"] = WriteJsonVec(cfg.mLHIMUAlignmentYaw);
		root["mRHIMUAlignmentTPosePitch"] = WriteJsonVec(cfg.mRHIMUAlignmentTPosePitch);
		root["mRHIMUAlignmentOKPosePitch"] = WriteJsonVec(cfg.mRHIMUAlignmentOKPosePitch);
		root["mRHIMUAlignmentYaw"] = WriteJsonVec(cfg.mRHIMUAlignmentYaw);

		root["mLHWristOffset"] = WriteJsonQuat(cfg.mLHWristOffset);
		root["mRHWristOffset"] = WriteJsonQuat(cfg.mRHWristOffset);

		std::ofstream file_id;
		file_id.open(current_dir);
		if (file_id.fail()) {
			return false;
		}
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4996) // Deriving from deprecated class
#endif
		Json::StyledWriter writer;
		file_id << writer.write(root);
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
		file_id.close();
		return true;
	}

	bool writeBack() {
		return writeBack(m_cfg);
	}

public:
	IDataGloveConfig m_cfg;
	std::string current_dir;
};
