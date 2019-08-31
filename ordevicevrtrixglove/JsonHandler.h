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

	//// Read TrackingVector3_t and return as Json Matrix
	Json::Value WriteJsonVec(double vec[5])
	{
		Json::Value jsonVec;
		for (int i = 0; i < 5; i++)
		{
			jsonVec[i] = vec[i];
		}
		return jsonVec;
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
	}

	bool writeBack() {
		Json::Value root;
		root["mAdvancedMode"] = m_cfg.mAdvancedMode;
		root["mHardwareVersion"] = m_cfg.mHardwareVersion;
		root["mFingerSpacing"] = m_cfg.mFingerSpacing;
		root["mFinalFingerSpacing"] = m_cfg.mFinalFingerSpacing;
		root["mBendUpThreshold"] = m_cfg.mBendUpThreshold;
		root["mBendDownThreshold"] = m_cfg.mBendDownThreshold;

		root["mLHThumbOffset"] = WriteJsonMatrix(m_cfg.mLHThumbOffset);
		root["mRHThumbOffset"] = WriteJsonMatrix(m_cfg.mRHThumbOffset);
		root["mLHModelOffset"] = WriteJsonMatrix(m_cfg.mLHModelOffset);
		root["mRHModelOffset"] = WriteJsonMatrix(m_cfg.mRHModelOffset);

		root["mProximalSlerpDownValue"] = WriteJsonVec(m_cfg.mProximalSlerpDownValue);
		root["mDistalSlerpDownValue"] = WriteJsonVec(m_cfg.mDistalSlerpDownValue);
		root["mProximalSlerpUpValue"] = WriteJsonVec(m_cfg.mProximalSlerpUpValue);
		root["mDistalSlerpUpValue"] = WriteJsonVec(m_cfg.mDistalSlerpUpValue);

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

public:
	IDataGloveConfig m_cfg;
	std::string current_dir;
};
