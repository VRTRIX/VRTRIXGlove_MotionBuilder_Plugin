#pragma once
#include "JsonHandler.h"

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

class BoneSetup
{
public:
	BoneSetup() {}
	~BoneSetup() {}
	void parseSkeletonHierarchySetup(Json::Value &cfg_root, std::vector<SkeletonNodeInfo> &mChannel) {
		Json::Value hierarchy = cfg_root["SkeletonHierarchy"];
		for (int i = 0; i < (int)hierarchy.size(); ++i) {
			SkeletonNodeInfo node;
			node.mName = hierarchy[i]["mName"].asString();
			if (node.mName == RHandBoneName) RHandIndex = i;
			if (node.mName == LHandBoneName) LHandIndex = i;
			node.mParentChannel = hierarchy[i]["mParentChannel"].asInt();
			node.mT[0] = hierarchy[i]["mPose"][0].asDouble();
			node.mT[1] = hierarchy[i]["mPose"][1].asDouble();
			node.mT[2] = hierarchy[i]["mPose"][2].asDouble();
			node.mR[0] = hierarchy[i]["mPose"][3].asDouble();
			node.mR[1] = hierarchy[i]["mPose"][4].asDouble();
			node.mR[2] = hierarchy[i]["mPose"][5].asDouble();
			mChannel.push_back(node);
		}
	}

	void parseHandHierarchySetup(Json::Value &cfg_root, std::vector<FBTVector>& mLocalTranslationR, std::vector<FBTVector>& mLocalTranslationL) {
		Json::Value hierarchy = cfg_root["HandHierarchy"];
		for (int i = 0; i < (int)hierarchy.size() / 2; ++i) {
			FBTVector mValue;
			mValue[0] = hierarchy[i]["mLocalTranslationR"][0].asDouble();
			mValue[1] = hierarchy[i]["mLocalTranslationR"][1].asDouble();
			mValue[2] = hierarchy[i]["mLocalTranslationR"][2].asDouble();
			mLocalTranslationR.push_back(mValue);
		}
		for (int i = (int)hierarchy.size() / 2; i < (int)hierarchy.size(); ++i) {
			FBTVector mValue;
			mValue[0] = hierarchy[i]["mLocalTranslationL"][0].asDouble();
			mValue[1] = hierarchy[i]["mLocalTranslationL"][1].asDouble();
			mValue[2] = hierarchy[i]["mLocalTranslationL"][2].asDouble();
			mLocalTranslationL.push_back(mValue);
		}
		RHandBoneName = hierarchy[0]["mName"].asString();
		LHandBoneName = hierarchy[(int)hierarchy.size() / 2]["mName"].asString();
	}

	void SkeletonHierarchySetup(std::vector<SkeletonNodeInfo> &mChannel, int gloveID) {
		Json::Value cfg_root;
		char result[MAX_PATH];
		std::string current_dir = std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
		std::string::size_type pos = current_dir.find_last_of("\\/");
		current_dir = current_dir.substr(0, pos) + "\\plugins\\config\\SkeletonHierarchy" + std::to_string(gloveID) + ".json";
		std::ifstream cfgfile(current_dir);
		if (cfgfile) // Verify that the file was open successfully
		{
			cfgfile >> cfg_root;
			parseSkeletonHierarchySetup(cfg_root, mChannel);
		}
	}

	void HandHierarchySetup(std::vector<FBTVector>& mLocalTranslationR, std::vector<FBTVector>& mLocalTranslationL, int gloveID) {
		Json::Value cfg_root;
		char result[MAX_PATH];
		std::string current_dir = std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
		std::string::size_type pos = current_dir.find_last_of("\\/");
		current_dir = current_dir.substr(0, pos) + "\\plugins\\config\\HandHierarchy" + std::to_string(gloveID) + ".json";
		std::ifstream cfgfile(current_dir);
		if (cfgfile) // Verify that the file was open successfully
		{
			cfgfile >> cfg_root;
			parseHandHierarchySetup(cfg_root, mLocalTranslationR, mLocalTranslationL);
		}
	}
public:
	int RHandIndex;
	int LHandIndex;
	std::string RHandBoneName;
	std::string LHandBoneName;
};