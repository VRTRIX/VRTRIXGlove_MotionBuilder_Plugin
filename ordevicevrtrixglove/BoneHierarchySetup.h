#pragma once
#include <fbsdk/fbsdk.h>
#define RHandIndex 34
#define LHandIndex 11
#define BoneNum	60 
#define HandBoneNum 20 
#define Scale	1

struct SkeletonNodeInfo
{
	const char*	mName;
	int			mParentChannel;
	double		mDefaultT[3];
	double		mDefaultR[3];
	double		mT[3];
	double		mR[3];
};

static void SkeletonHierarchySetup(SkeletonNodeInfo* mChannel) {
	//0:Reference
	mChannel[0].mName = "Reference";
	mChannel[0].mParentChannel = -1;
	mChannel[0].mT[0] = 0.0;
	mChannel[0].mT[1] = 0.0;
	mChannel[0].mT[2] = 0.0;
	mChannel[0].mR[0] = 0.0;
	mChannel[0].mR[1] = -0.0;
	mChannel[0].mR[2] = 0.0;

	//1:Robot_Hips
	mChannel[1].mName = "Robot_Hips";
	mChannel[1].mParentChannel = 0;
	mChannel[1].mT[0] = 0.0;
	mChannel[1].mT[1] = 111.388595581;
	mChannel[1].mT[2] = -1.24851226807;
	mChannel[1].mR[0] = 0.0;
	mChannel[1].mR[1] = -0.0;
	mChannel[1].mR[2] = 0.0;

	//2:Robot_Spine
	mChannel[2].mName = "Robot_Spine";
	mChannel[2].mParentChannel = 1;
	mChannel[2].mT[0] = -1.76845802e-13;
	mChannel[2].mT[1] = 120.997894287;
	mChannel[2].mT[2] = -1.24851202965;
	mChannel[2].mR[0] = 0.0;
	mChannel[2].mR[1] = -0.0;
	mChannel[2].mR[2] = 0.0;

	//3:Robot_Spine1
	mChannel[3].mName = "Robot_Spine1";
	mChannel[3].mParentChannel = 2;
	mChannel[3].mT[0] = 2.16137735964e-14;
	mChannel[3].mT[1] = 132.256072998;
	mChannel[3].mT[2] = -1.24851202965;
	mChannel[3].mR[0] = 0.0;
	mChannel[3].mR[1] = -0.0;
	mChannel[3].mR[2] = 0.0;

	//4:Robot_Spine2
	mChannel[4].mName = "Robot_Spine2";
	mChannel[4].mParentChannel = 3;
	mChannel[4].mT[0] = -1.89137341043e-14;
	mChannel[4].mT[1] = 144.289138794;
	mChannel[4].mT[2] = -1.24851202965;
	mChannel[4].mR[0] = 0.0;
	mChannel[4].mR[1] = -0.0;
	mChannel[4].mR[2] = 0.0;

	//5:Robot_Spine3
	mChannel[5].mName = "Robot_Spine3";
	mChannel[5].mParentChannel = 4;
	mChannel[5].mT[0] = -3.63953455589e-15;
	mChannel[5].mT[1] = 156.012207031;
	mChannel[5].mT[2] = 1.19209289329e-07;
	mChannel[5].mR[0] = 0.0;
	mChannel[5].mR[1] = -0.0;
	mChannel[5].mR[2] = 0.0;

	//6:Robot_Neck
	mChannel[6].mName = "Robot_Neck";
	mChannel[6].mParentChannel = 5;
	mChannel[6].mT[0] = -1.55189209194e-14;
	mChannel[6].mT[1] = 168.082366943;
	mChannel[6].mT[2] = -1.24851202965;
	mChannel[6].mR[0] = 0.0;
	mChannel[6].mR[1] = -0.0;
	mChannel[6].mR[2] = 0.0;

	//7:Robot_Head
	mChannel[7].mName = "Robot_Head";
	mChannel[7].mParentChannel = 6;
	mChannel[7].mT[0] = 1.56642921019e-14;
	mChannel[7].mT[1] = 178.086425781;
	mChannel[7].mT[2] = -1.24851202965;
	mChannel[7].mR[0] = 0.0;
	mChannel[7].mR[1] = -0.0;
	mChannel[7].mR[2] = 0.0;

	//8:Robot_LeftShoulder
	mChannel[8].mName = "Robot_LeftShoulder";
	mChannel[8].mParentChannel = 5;
	mChannel[8].mT[0] = 4.90493822098;
	mChannel[8].mT[1] = 160.075286865;
	mChannel[8].mT[2] = -1.24851214886;
	mChannel[8].mR[0] = 0.0;
	mChannel[8].mR[1] = -0.0;
	mChannel[8].mR[2] = 0.0;

	//9:Robot_LeftArm
	mChannel[9].mName = "Robot_LeftArm";
	mChannel[9].mParentChannel = 8;
	mChannel[9].mT[0] = 20.5537762642;
	mChannel[9].mT[1] = 160.075286865;
	mChannel[9].mT[2] = -1.24851214886;
	mChannel[9].mR[0] = 0.0;
	mChannel[9].mR[1] = -0.0;
	mChannel[9].mR[2] = 0.0;

	//10:Robot_LeftForeArm
	mChannel[10].mName = "Robot_LeftForeArm";
	mChannel[10].mParentChannel = 9;
	mChannel[10].mT[0] = 46.4298062325;
	mChannel[10].mT[1] = 160.075286865;
	mChannel[10].mT[2] = -1.24851214886;
	mChannel[10].mR[0] = 0.0;
	mChannel[10].mR[1] = -0.0;
	mChannel[10].mR[2] = 0.0;

	//11:Robot_LeftHand
	mChannel[11].mName = "Robot_LeftHand";
	mChannel[11].mParentChannel = 10;
	mChannel[11].mT[0] = 74.8318333626;
	mChannel[11].mT[1] = 160.075286865;
	mChannel[11].mT[2] = -1.24851214886;
	mChannel[11].mR[0] = 0.0;
	mChannel[11].mR[1] = -0.0;
	mChannel[11].mR[2] = 0.0;

	//12:Robot_LeftHandThumb1
	mChannel[12].mName = "Robot_LeftHandThumb1";
	mChannel[12].mParentChannel = 11;
	mChannel[12].mT[0] = 78.2105031013;
	mChannel[12].mT[1] = 160.332763672;
	mChannel[12].mT[2] = 2.98708498478;
	mChannel[12].mR[0] = 0.0;
	mChannel[12].mR[1] = -0.0;
	mChannel[12].mR[2] = 0.0;

	//13:Robot_LeftHandThumb2
	mChannel[13].mName = "Robot_LeftHandThumb2";
	mChannel[13].mParentChannel = 12;
	mChannel[13].mT[0] = 83.209297657;
	mChannel[13].mT[1] = 160.345443726;
	mChannel[13].mT[2] = 2.97451913357;
	mChannel[13].mR[0] = 0.0;
	mChannel[13].mR[1] = -0.0;
	mChannel[13].mR[2] = 0.0;

	//14:Robot_LeftHandThumb3
	mChannel[14].mName = "Robot_LeftHandThumb3";
	mChannel[14].mParentChannel = 13;
	mChannel[14].mT[0] = 86.6817784309;
	mChannel[14].mT[1] = 160.337478638;
	mChannel[14].mT[2] = 2.98464119434;
	mChannel[14].mR[0] = 0.0;
	mChannel[14].mR[1] = -0.0;
	mChannel[14].mR[2] = 0.0;

	//15:Robot_LeftInHandIndex
	mChannel[15].mName = "Robot_LeftInHandIndex";
	mChannel[15].mParentChannel = 11;
	mChannel[15].mT[0] = 79.207092762;
	mChannel[15].mT[1] = 160.764526367;
	mChannel[15].mT[2] = 1.43683135509;
	mChannel[15].mR[0] = 0.0;
	mChannel[15].mR[1] = -0.0;
	mChannel[15].mR[2] = 0.0;

	//16:Robot_LeftHandIndex1
	mChannel[16].mName = "Robot_LeftHandIndex1";
	mChannel[16].mParentChannel = 15;
	mChannel[16].mT[0] = 86.2939610481;
	mChannel[16].mT[1] = 160.640869141;
	mChannel[16].mT[2] = 2.79330396652;
	mChannel[16].mR[0] = 0.0;
	mChannel[16].mR[1] = -0.0;
	mChannel[16].mR[2] = 0.0;

	//17:Robot_LeftHandIndex2
	mChannel[17].mName = "Robot_LeftHandIndex2";
	mChannel[17].mParentChannel = 16;
	mChannel[17].mT[0] = 91.2001957893;
	mChannel[17].mT[1] = 160.401794434;
	mChannel[17].mT[2] = 2.78098487854;
	mChannel[17].mR[0] = 0.0;
	mChannel[17].mR[1] = -0.0;
	mChannel[17].mR[2] = 0.0;

	//18:Robot_LeftHandIndex3
	mChannel[18].mName = "Robot_LeftHandIndex3";
	mChannel[18].mParentChannel = 17;
	mChannel[18].mT[0] = 93.9795689583;
	mChannel[18].mT[1] = 160.228668213;
	mChannel[18].mT[2] = 2.79196619987;
	mChannel[18].mR[0] = 0.0;
	mChannel[18].mR[1] = -0.0;
	mChannel[18].mR[2] = 0.0;

	//19:Robot_LeftInHandMiddle
	mChannel[19].mName = "Robot_LeftInHandMiddle";
	mChannel[19].mParentChannel = 11;
	mChannel[19].mT[0] = 79.4241337776;
	mChannel[19].mT[1] = 160.77734375;
	mChannel[19].mT[2] = -0.2205773592;
	mChannel[19].mR[0] = 0.0;
	mChannel[19].mR[1] = -0.0;
	mChannel[19].mR[2] = 0.0;

	//20:Robot_LeftHandMiddle1
	mChannel[20].mName = "Robot_LeftHandMiddle1";
	mChannel[20].mParentChannel = 19;
	mChannel[20].mT[0] = 86.4469609261;
	mChannel[20].mT[1] = 160.66317749;
	mChannel[20].mT[2] = 0.20580753684;
	mChannel[20].mR[0] = 0.0;
	mChannel[20].mR[1] = -0.0;
	mChannel[20].mR[2] = 0.0;

	//21:Robot_LeftHandMiddle2
	mChannel[21].mName = "Robot_LeftHandMiddle2";
	mChannel[21].mParentChannel = 20;
	mChannel[21].mT[0] = 91.7951588631;
	mChannel[21].mT[1] = 160.298843384;
	mChannel[21].mT[2] = 0.190128579736;
	mChannel[21].mR[0] = 0.0;
	mChannel[21].mR[1] = -0.0;
	mChannel[21].mR[2] = 0.0;

	//22:Robot_LeftHandMiddle3
	mChannel[22].mName = "Robot_LeftHandMiddle3";
	mChannel[22].mParentChannel = 21;
	mChannel[22].mT[0] = 95.1445088387;
	mChannel[22].mT[1] = 160.040115356;
	mChannel[22].mT[2] = 0.204416528344;
	mChannel[22].mR[0] = 0.0;
	mChannel[22].mR[1] = -0.0;
	mChannel[22].mR[2] = 0.0;

	//23:Robot_LeftInHandRing
	mChannel[23].mName = "Robot_LeftInHandRing";
	mChannel[23].mParentChannel = 11;
	mChannel[23].mT[0] = 79.3990483284;
	mChannel[23].mT[1] = 160.810501099;
	mChannel[23].mT[2] = -1.42448747158;
	mChannel[23].mR[0] = 0.0;
	mChannel[23].mR[1] = -0.0;
	mChannel[23].mR[2] = 0.0;

	//24:Robot_LeftHandRing1
	mChannel[24].mName = "Robot_LeftHandRing1";
	mChannel[24].mParentChannel = 23;
	mChannel[24].mT[0] = 85.6944966316;
	mChannel[24].mT[1] = 160.78024292;
	mChannel[24].mT[2] = -2.07660531998;
	mChannel[24].mR[0] = 0.0;
	mChannel[24].mR[1] = -0.0;
	mChannel[24].mR[2] = 0.0;

	//25:Robot_LeftHandRing2
	mChannel[25].mName = "Robot_LeftHandRing2";
	mChannel[25].mParentChannel = 24;
	mChannel[25].mT[0] = 90.3526997566;
	mChannel[25].mT[1] = 160.422927856;
	mChannel[25].mT[2] = -2.07428336143;
	mChannel[25].mR[0] = 0.0;
	mChannel[25].mR[1] = -0.0;
	mChannel[25].mR[2] = 0.0;

	//26:Robot_LeftHandRing3
	mChannel[26].mName = "Robot_LeftHandRing3";
	mChannel[26].mParentChannel = 25;
	mChannel[26].mT[0] = 93.5854878426;
	mChannel[26].mT[1] = 160.190414429;
	mChannel[26].mT[2] = -2.07240271568;
	mChannel[26].mR[0] = 0.0;
	mChannel[26].mR[1] = -0.0;
	mChannel[26].mR[2] = 0.0;

	//27:Robot_LeftInHandPinky
	mChannel[27].mName = "Robot_LeftInHandPinky";
	mChannel[27].mParentChannel = 11;
	mChannel[27].mT[0] = 79.1231541634;
	mChannel[27].mT[1] = 160.712417603;
	mChannel[27].mT[2] = -2.87921237946;
	mChannel[27].mR[0] = 0.0;
	mChannel[27].mR[1] = -0.0;
	mChannel[27].mR[2] = 0.0;

	//28:Robot_LeftHandPinky1
	mChannel[28].mName = "Robot_LeftHandPinky1";
	mChannel[28].mParentChannel = 27;
	mChannel[28].mT[0] = 84.7414021492;
	mChannel[28].mT[1] = 160.675796509;
	mChannel[28].mT[2] = -4.35901927948;
	mChannel[28].mR[0] = 0.0;
	mChannel[28].mR[1] = -0.0;
	mChannel[28].mR[2] = 0.0;

	//29:Robot_LeftHandPinky2
	mChannel[29].mName = "Robot_LeftHandPinky2";
	mChannel[29].mParentChannel = 28;
	mChannel[29].mT[0] = 88.4775242805;
	mChannel[29].mT[1] = 160.471115112;
	mChannel[29].mT[2] = -4.34833431244;
	mChannel[29].mR[0] = 0.0;
	mChannel[29].mR[1] = -0.0;
	mChannel[29].mR[2] = 0.0;

	//30:Robot_LeftHandPinky3
	mChannel[30].mName = "Robot_LeftHandPinky3";
	mChannel[30].mParentChannel = 29;
	mChannel[30].mT[0] = 90.8347554207;
	mChannel[30].mT[1] = 160.293167114;
	mChannel[30].mT[2] = -4.36021184921;
	mChannel[30].mR[0] = 0.0;
	mChannel[30].mR[1] = -0.0;
	mChannel[30].mR[2] = 0.0;

	//31:Robot_RightShoulder
	mChannel[31].mName = "Robot_RightShoulder";
	mChannel[31].mParentChannel = 5;
	mChannel[31].mT[0] = -4.90494060516;
	mChannel[31].mT[1] = 160.075012207;
	mChannel[31].mT[2] = -1.2485101223;
	mChannel[31].mR[0] = 0.0;
	mChannel[31].mR[1] = -0.0;
	mChannel[31].mR[2] = 0.0;

	//32:Robot_RightArm
	mChannel[32].mName = "Robot_RightArm";
	mChannel[32].mParentChannel = 31;
	mChannel[32].mT[0] = -20.5538005829;
	mChannel[32].mT[1] = 160.075012207;
	mChannel[32].mT[2] = -1.2485101223;
	mChannel[32].mR[0] = 0.0;
	mChannel[32].mR[1] = -0.0;
	mChannel[32].mR[2] = 0.0;

	//33:Robot_RightForeArm
	mChannel[33].mName = "Robot_RightForeArm";
	mChannel[33].mParentChannel = 32;
	mChannel[33].mT[0] = -46.4298057556;
	mChannel[33].mT[1] = 160.075012207;
	mChannel[33].mT[2] = -1.2485101223;
	mChannel[33].mR[0] = 0.0;
	mChannel[33].mR[1] = -0.0;
	mChannel[33].mR[2] = 0.0;

	//34:Robot_RightHand
	mChannel[34].mName = "Robot_RightHand";
	mChannel[34].mParentChannel = 33;
	mChannel[34].mT[0] = -74.8318023682;
	mChannel[34].mT[1] = 160.075012207;
	mChannel[34].mT[2] = -1.2485101223;
	mChannel[34].mR[0] = 0.0;
	mChannel[34].mR[1] = -0.0;
	mChannel[34].mR[2] = 0.0;

	//35:Robot_RightHandThumb1
	mChannel[35].mName = "Robot_RightHandThumb1";
	mChannel[35].mParentChannel = 34;
	mChannel[35].mT[0] = -78.2105026245;
	mChannel[35].mT[1] = 160.333023071;
	mChannel[35].mT[2] = 2.9870903492;
	mChannel[35].mR[0] = 0.0;
	mChannel[35].mR[1] = -0.0;
	mChannel[35].mR[2] = 0.0;

	//36:Robot_RightHandThumb2
	mChannel[36].mName = "Robot_RightHandThumb2";
	mChannel[36].mParentChannel = 35;
	mChannel[36].mT[0] = -83.2093429565;
	mChannel[36].mT[1] = 160.327255249;
	mChannel[36].mT[2] = 2.96469163895;
	mChannel[36].mR[0] = 0.0;
	mChannel[36].mR[1] = -0.0;
	mChannel[36].mR[2] = 0.0;

	//37:Robot_RightHandThumb3
	mChannel[37].mName = "Robot_RightHandThumb3";
	mChannel[37].mParentChannel = 36;
	mChannel[37].mT[0] = -86.6817092896;
	mChannel[37].mT[1] = 160.330123901;
	mChannel[37].mT[2] = 2.94448637962;
	mChannel[37].mR[0] = 0.0;
	mChannel[37].mR[1] = -0.0;
	mChannel[37].mR[2] = 0.0;

	//38:Robot_RightInHandIndex
	mChannel[38].mName = "Robot_RightInHandIndex";
	mChannel[38].mParentChannel = 34;
	mChannel[38].mT[0] = -79.2071075439;
	mChannel[38].mT[1] = 160.765029907;
	mChannel[38].mT[2] = 1.43683004379;
	mChannel[38].mR[0] = 0.0;
	mChannel[38].mR[1] = -0.0;
	mChannel[38].mR[2] = 0.0;

	//39:Robot_RightHandIndex1
	mChannel[39].mName = "Robot_RightHandIndex1";
	mChannel[39].mParentChannel = 38;
	mChannel[39].mT[0] = -86.2940139771;
	mChannel[39].mT[1] = 160.641021729;
	mChannel[39].mT[2] = 2.79330062866;
	mChannel[39].mR[0] = 0.0;
	mChannel[39].mR[1] = -0.0;
	mChannel[39].mR[2] = 0.0;

	//40:Robot_RightHandIndex2
	mChannel[40].mName = "Robot_RightHandIndex2";
	mChannel[40].mParentChannel = 39;
	mChannel[40].mT[0] = -91.2002334595;
	mChannel[40].mT[1] = 160.402023315;
	mChannel[40].mT[2] = 2.8021402359;
	mChannel[40].mR[0] = 0.0;
	mChannel[40].mR[1] = -0.0;
	mChannel[40].mR[2] = 0.0;

	//41:Robot_RightHandIndex3
	mChannel[41].mName = "Robot_RightHandIndex3";
	mChannel[41].mParentChannel = 40;
	mChannel[41].mT[0] = -93.979637146;
	mChannel[41].mT[1] = 160.229019165;
	mChannel[41].mT[2] = 2.80088829994;
	mChannel[41].mR[0] = 0.0;
	mChannel[41].mR[1] = -0.0;
	mChannel[41].mR[2] = 0.0;

	//42:Robot_RightInHandMiddle
	mChannel[42].mName = "Robot_RightInHandMiddle";
	mChannel[42].mParentChannel = 34;
	mChannel[42].mT[0] = -79.4241104126;
	mChannel[42].mT[1] = 160.777023315;
	mChannel[42].mT[2] = -0.220577955246;
	mChannel[42].mR[0] = 0.0;
	mChannel[42].mR[1] = -0.0;
	mChannel[42].mR[2] = 0.0;

	//43:Robot_RightHandMiddle1
	mChannel[43].mName = "Robot_RightHandMiddle1";
	mChannel[43].mParentChannel = 42;
	mChannel[43].mT[0] = -86.4469070435;
	mChannel[43].mT[1] = 160.663040161;
	mChannel[43].mT[2] = 0.20580714941;
	mChannel[43].mR[0] = 0.0;
	mChannel[43].mR[1] = -0.0;
	mChannel[43].mR[2] = 0.0;

	//44:Robot_RightHandMiddle2
	mChannel[44].mName = "Robot_RightHandMiddle2";
	mChannel[44].mParentChannel = 43;
	mChannel[44].mT[0] = -91.7951889038;
	mChannel[44].mT[1] = 160.299041748;
	mChannel[44].mT[2] = 0.191819682717;
	mChannel[44].mR[0] = 0.0;
	mChannel[44].mR[1] = -0.0;
	mChannel[44].mR[2] = 0.0;

	//45:Robot_RightHandMiddle3
	mChannel[45].mName = "Robot_RightHandMiddle3";
	mChannel[45].mParentChannel = 44;
	mChannel[45].mT[0] = -95.14453125;
	mChannel[45].mT[1] = 160.040023804;
	mChannel[45].mT[2] = 0.200409114361;
	mChannel[45].mR[0] = 0.0;
	mChannel[45].mR[1] = -0.0;
	mChannel[45].mR[2] = 0.0;

	//46:Robot_RightInHandRing
	mChannel[46].mName = "Robot_RightInHandRing";
	mChannel[46].mParentChannel = 34;
	mChannel[46].mT[0] = -79.3990097046;
	mChannel[46].mT[1] = 160.810028076;
	mChannel[46].mT[2] = -1.42449009418;
	mChannel[46].mR[0] = 0.0;
	mChannel[46].mR[1] = -0.0;
	mChannel[46].mR[2] = 0.0;

	//47:Robot_RightHandRing1
	mChannel[47].mName = "Robot_RightHandRing1";
	mChannel[47].mParentChannel = 46;
	mChannel[47].mT[0] = -85.6945114136;
	mChannel[47].mT[1] = 160.780029297;
	mChannel[47].mT[2] = -2.07661008835;
	mChannel[47].mR[0] = 0.0;
	mChannel[47].mR[1] = -0.0;
	mChannel[47].mR[2] = 0.0;

	//48:Robot_RightHandRing2
	mChannel[48].mName = "Robot_RightHandRing2";
	mChannel[48].mParentChannel = 47;
	mChannel[48].mT[0] = -90.3457717896;
	mChannel[48].mT[1] = 160.342254639;
	mChannel[48].mT[2] = -2.06399846077;
	mChannel[48].mR[0] = 0.0;
	mChannel[48].mR[1] = -0.0;
	mChannel[48].mR[2] = 0.0;

	//49:Robot_RightHandRing3
	mChannel[49].mName = "Robot_RightHandRing3";
	mChannel[49].mParentChannel = 48;
	mChannel[49].mT[0] = -93.574760437;
	mChannel[49].mT[1] = 160.061325073;
	mChannel[49].mT[2] = -2.07948231697;
	mChannel[49].mR[0] = 0.0;
	mChannel[49].mR[1] = -0.0;
	mChannel[49].mR[2] = 0.0;

	//50:Robot_RightInHandPinky
	mChannel[50].mName = "Robot_RightInHandPinky";
	mChannel[50].mParentChannel = 34;
	mChannel[50].mT[0] = -79.1231002808;
	mChannel[50].mT[1] = 160.712020874;
	mChannel[50].mT[2] = -2.87920999527;
	mChannel[50].mR[0] = 0.0;
	mChannel[50].mR[1] = -0.0;
	mChannel[50].mR[2] = 0.0;

	//51:Robot_RightHandPinky1
	mChannel[51].mName = "Robot_RightHandPinky1";
	mChannel[51].mParentChannel = 50;
	mChannel[51].mT[0] = -84.7414016724;
	mChannel[51].mT[1] = 160.676025391;
	mChannel[51].mT[2] = -4.35902070999;
	mChannel[51].mR[0] = 0.0;
	mChannel[51].mR[1] = -0.0;
	mChannel[51].mR[2] = 0.0;

	//52:Robot_RightHandPinky2
	mChannel[52].mName = "Robot_RightHandPinky2";
	mChannel[52].mParentChannel = 51;
	mChannel[52].mT[0] = -88.4775924683;
	mChannel[52].mT[1] = 160.472122192;
	mChannel[52].mT[2] = -4.37626171112;
	mChannel[52].mR[0] = 0.0;
	mChannel[52].mR[1] = -0.0;
	mChannel[52].mR[2] = 0.0;

	//53:Robot_RightHandPinky3
	mChannel[53].mName = "Robot_RightHandPinky3";
	mChannel[53].mParentChannel = 52;
	mChannel[53].mT[0] = -90.8347854614;
	mChannel[53].mT[1] = 160.294372559;
	mChannel[53].mT[2] = -4.3672337532;
	mChannel[53].mR[0] = 0.0;
	mChannel[53].mR[1] = -0.0;
	mChannel[53].mR[2] = 0.0;

	//54:Robot_LeftUpLeg
	mChannel[54].mName = "Robot_LeftUpLeg";
	mChannel[54].mParentChannel = 1;
	mChannel[54].mT[0] = 10.553150177;
	mChannel[54].mT[1] = 102.582305908;
	mChannel[54].mT[2] = -2.10686445236;
	mChannel[54].mR[0] = 0.0;
	mChannel[54].mR[1] = -0.0;
	mChannel[54].mR[2] = 0.0;

	//55:Robot_LeftLeg
	mChannel[55].mName = "Robot_LeftLeg";
	mChannel[55].mParentChannel = 54;
	mChannel[55].mT[0] = 11.7535543442;
	mChannel[55].mT[1] = 56.9315834045;
	mChannel[55].mT[2] = -3.62307357788;
	mChannel[55].mR[0] = 0.0;
	mChannel[55].mR[1] = -0.0;
	mChannel[55].mR[2] = 0.0;

	//56:Robot_LeftFoot
	mChannel[56].mName = "Robot_LeftFoot";
	mChannel[56].mParentChannel = 55;
	mChannel[56].mT[0] = 11.3097925186;
	mChannel[56].mT[1] = 10.219959259;
	mChannel[56].mT[2] = -3.87397694588;
	mChannel[56].mR[0] = 0.0;
	mChannel[56].mR[1] = -0.0;
	mChannel[56].mR[2] = 0.0;

	//57:Robot_RightUpLeg
	mChannel[57].mName = "Robot_RightUpLeg";
	mChannel[57].mParentChannel = 1;
	mChannel[57].mT[0] = -10.553150177;
	mChannel[57].mT[1] = 102.582305908;
	mChannel[57].mT[2] = -2.10686445236;
	mChannel[57].mR[0] = 0.0;
	mChannel[57].mR[1] = -0.0;
	mChannel[57].mR[2] = 0.0;

	//58:Robot_RightLeg
	mChannel[58].mName = "Robot_RightLeg";
	mChannel[58].mParentChannel = 57;
	mChannel[58].mT[0] = -11.7535543442;
	mChannel[58].mT[1] = 56.9315834045;
	mChannel[58].mT[2] = -3.62307357788;
	mChannel[58].mR[0] = 0.0;
	mChannel[58].mR[1] = -0.0;
	mChannel[58].mR[2] = 0.0;

	//59:Robot_RightFoot
	mChannel[59].mName = "Robot_RightFoot";
	mChannel[59].mParentChannel = 58;
	mChannel[59].mT[0] = -11.3097925186;
	mChannel[59].mT[1] = 10.219959259;
	mChannel[59].mT[2] = -3.87397694588;
	mChannel[59].mR[0] = 0.0;
	mChannel[59].mR[1] = -0.0;
	mChannel[59].mR[2] = 0.0;
}

static void HandHierarchySetup(FBTVector* mLocalTranslationR, FBTVector* mLocalTranslationL) {
	//0:Robot_RightHand
	mLocalTranslationR[0].mValue[0] = -74.8318023682;
	mLocalTranslationR[0].mValue[1] = 160.075012207;
	mLocalTranslationR[0].mValue[2] = -1.2485101223;

	//1:Robot_RightHandThumb1
	mLocalTranslationR[1].mValue[0] = -3.37870025635;
	mLocalTranslationR[1].mValue[1] = 0.258010864258;
	mLocalTranslationR[1].mValue[2] = 4.2356004715;

	//2:Robot_RightHandThumb2
	mLocalTranslationR[2].mValue[0] = -4.99884033203;
	mLocalTranslationR[2].mValue[1] = -0.00576782226562;
	mLocalTranslationR[2].mValue[2] = -0.0223987102509;

	//3:Robot_RightHandThumb3
	mLocalTranslationR[3].mValue[0] = -3.47236633301;
	mLocalTranslationR[3].mValue[1] = 0.00286865234375;
	mLocalTranslationR[3].mValue[2] = -0.0202052593231;

	//4:Robot_RightInHandIndex
	mLocalTranslationR[4].mValue[0] = -4.37530517578;
	mLocalTranslationR[4].mValue[1] = 0.690017700195;
	mLocalTranslationR[4].mValue[2] = 2.68534016609;

	//5:Robot_RightHandIndex1
	mLocalTranslationR[5].mValue[0] = -7.08690643311;
	mLocalTranslationR[5].mValue[1] = -0.124008178711;
	mLocalTranslationR[5].mValue[2] = 1.35647058487;

	//6:Robot_RightHandIndex2
	mLocalTranslationR[6].mValue[0] = -4.90621948242;
	mLocalTranslationR[6].mValue[1] = -0.238998413086;
	mLocalTranslationR[6].mValue[2] = 0.00883960723877;

	//7:Robot_RightHandIndex3
	mLocalTranslationR[7].mValue[0] = -2.77940368652;
	mLocalTranslationR[7].mValue[1] = -0.173004150391;
	mLocalTranslationR[7].mValue[2] = -0.00125193595886;

	//8:Robot_RightInHandMiddle
	mLocalTranslationR[8].mValue[0] = -4.59230804443;
	mLocalTranslationR[8].mValue[1] = 0.702011108398;
	mLocalTranslationR[8].mValue[2] = 1.02793216705;

	//9:Robot_RightHandMiddle1
	mLocalTranslationR[9].mValue[0] = -7.02279663086;
	mLocalTranslationR[9].mValue[1] = -0.113983154297;
	mLocalTranslationR[9].mValue[2] = 0.426385104656;

	//10:Robot_RightHandMiddle2
	mLocalTranslationR[10].mValue[0] = -5.34828186035;
	mLocalTranslationR[10].mValue[1] = -0.363998413086;
	mLocalTranslationR[10].mValue[2] = -0.0139874666929;

	//11:Robot_RightHandMiddle3
	mLocalTranslationR[11].mValue[0] = -3.34934234619;
	mLocalTranslationR[11].mValue[1] = -0.259017944336;
	mLocalTranslationR[11].mValue[2] = 0.00858943164349;

	//12:Robot_RightInHandRing
	mLocalTranslationR[12].mValue[0] = -4.56720733643;
	mLocalTranslationR[12].mValue[1] = 0.735015869141;
	mLocalTranslationR[12].mValue[2] = -0.175979971886;

	//13:Robot_RightHandRing1
	mLocalTranslationR[13].mValue[0] = -6.29550170898;
	mLocalTranslationR[13].mValue[1] = -0.0299987792969;
	mLocalTranslationR[13].mValue[2] = -0.652119994164;

	//14:Robot_RightHandRing2
	mLocalTranslationR[14].mValue[0] = -4.65126037598;
	mLocalTranslationR[14].mValue[1] = -0.437774658203;
	mLocalTranslationR[14].mValue[2] = 0.0126116275787;

	//15:Robot_RightHandRing3
	mLocalTranslationR[15].mValue[0] = -3.22898864746;
	mLocalTranslationR[15].mValue[1] = -0.28092956543;
	mLocalTranslationR[15].mValue[2] = -0.0154838562012;

	//16:Robot_RightInHandPinky
	mLocalTranslationR[16].mValue[0] = -4.2912979126;
	mLocalTranslationR[16].mValue[1] = 0.637008666992;
	mLocalTranslationR[16].mValue[2] = -1.63069987297;

	//17:Robot_RightHandPinky1
	mLocalTranslationR[17].mValue[0] = -5.6183013916;
	mLocalTranslationR[17].mValue[1] = -0.0359954833984;
	mLocalTranslationR[17].mValue[2] = -1.47981071472;

	//18:Robot_RightHandPinky2
	mLocalTranslationR[18].mValue[0] = -3.7361907959;
	mLocalTranslationR[18].mValue[1] = -0.203903198242;
	mLocalTranslationR[18].mValue[2] = -0.0172410011292;

	//19:Robot_RightHandPinky3
	mLocalTranslationR[19].mValue[0] = -2.35719299316;
	mLocalTranslationR[19].mValue[1] = -0.177749633789;
	mLocalTranslationR[19].mValue[2] = 0.00902795791626;

	//0:Robot_LeftHand
	mLocalTranslationL[0].mValue[0] = 74.8318333626;
	mLocalTranslationL[0].mValue[1] = 160.075286865;
	mLocalTranslationL[0].mValue[2] = -1.24851214886;

	////1:Robot_LeftHandThumb1
	//mLocalTranslationL[1].mValue[0] = 3.37866973877;
	//mLocalTranslationL[1].mValue[1] = 0.257476806641;
	//mLocalTranslationL[1].mValue[2] = 4.23559713364;

	//1:Robot_LeftHandThumb1
	mLocalTranslationL[1].mValue[0] = 4.10187839645;
	mLocalTranslationL[1].mValue[1] = 0.257476806641;
	mLocalTranslationL[1].mValue[2] = 4.73020429638;

	//2:Robot_LeftHandThumb2
	mLocalTranslationL[2].mValue[0] = 4.99879455566;
	mLocalTranslationL[2].mValue[1] = 0.0126800537109;
	mLocalTranslationL[2].mValue[2] = -0.0125658512115;

	//3:Robot_LeftHandThumb3
	mLocalTranslationL[3].mValue[0] = 3.47248077393;
	mLocalTranslationL[3].mValue[1] = -0.00796508789062;
	mLocalTranslationL[3].mValue[2] = 0.0101220607758;

	//4:Robot_LeftInHandIndex
	mLocalTranslationL[4].mValue[0] = 4.37525939941;
	mLocalTranslationL[4].mValue[1] = 0.689239501953;
	mLocalTranslationL[4].mValue[2] = 2.68534350395;

	//5:Robot_LeftHandIndex1
	mLocalTranslationL[5].mValue[0] = 7.08686828613;
	mLocalTranslationL[5].mValue[1] = -0.123657226562;
	mLocalTranslationL[5].mValue[2] = 1.35647261143;

	//6:Robot_LeftHandIndex2
	mLocalTranslationL[6].mValue[0] = 4.90623474121;
	mLocalTranslationL[6].mValue[1] = -0.239074707031;
	mLocalTranslationL[6].mValue[2] = -0.0123190879822;

	//7:Robot_LeftHandIndex3
	mLocalTranslationL[7].mValue[0] = 2.77937316895;
	mLocalTranslationL[7].mValue[1] = -0.173126220703;
	mLocalTranslationL[7].mValue[2] = 0.0109813213348;

	//8:Robot_LeftInHandMiddle
	mLocalTranslationL[8].mValue[0] = 4.59230041504;
	mLocalTranslationL[8].mValue[1] = 0.702056884766;
	mLocalTranslationL[8].mValue[2] = 1.02793478966;

	//9:Robot_LeftHandMiddle1
	mLocalTranslationL[9].mValue[0] = 7.02282714844;
	mLocalTranslationL[9].mValue[1] = -0.114166259766;
	mLocalTranslationL[9].mValue[2] = 0.42638489604;

	//10:Robot_LeftHandMiddle2
	mLocalTranslationL[10].mValue[0] = 5.34819793701;
	mLocalTranslationL[10].mValue[1] = -0.364334106445;
	mLocalTranslationL[10].mValue[2] = -0.0156789571047;

	//11:Robot_LeftHandMiddle3
	mLocalTranslationL[11].mValue[0] = 3.34934997559;
	mLocalTranslationL[11].mValue[1] = -0.258728027344;
	mLocalTranslationL[11].mValue[2] = 0.0142879486084;

	//12:Robot_LeftInHandRing
	mLocalTranslationL[12].mValue[0] = 4.56721496582;
	mLocalTranslationL[12].mValue[1] = 0.735214233398;
	mLocalTranslationL[12].mValue[2] = -0.175975322723;

	//13:Robot_LeftHandRing1
	mLocalTranslationL[13].mValue[0] = 6.29544830322;
	mLocalTranslationL[13].mValue[1] = -0.0302581787109;
	mLocalTranslationL[13].mValue[2] = -0.652117848396;

	//14:Robot_LeftHandRing2
	mLocalTranslationL[14].mValue[0] = 4.658203125;
	mLocalTranslationL[14].mValue[1] = -0.357315063477;
	mLocalTranslationL[14].mValue[2] = 0.00232195854187;

	//15:Robot_LeftHandRing3
	mLocalTranslationL[15].mValue[0] = 3.23278808594;
	mLocalTranslationL[15].mValue[1] = -0.232513427734;
	mLocalTranslationL[15].mValue[2] = 0.00188064575195;

	//16:Robot_LeftInHandPinky
	mLocalTranslationL[16].mValue[0] = 4.29132080078;
	mLocalTranslationL[16].mValue[1] = 0.637130737305;
	mLocalTranslationL[16].mValue[2] = -1.6307002306;

	//17:Robot_LeftHandPinky1
	mLocalTranslationL[17].mValue[0] = 5.61824798584;
	mLocalTranslationL[17].mValue[1] = -0.03662109375;
	mLocalTranslationL[17].mValue[2] = -1.47980690002;

	//18:Robot_LeftHandPinky2
	mLocalTranslationL[18].mValue[0] = 3.73612213135;
	mLocalTranslationL[18].mValue[1] = -0.204681396484;
	mLocalTranslationL[18].mValue[2] = 0.010684967041;

	//19:Robot_LeftHandPinky3
	mLocalTranslationL[19].mValue[0] = 2.35723114014;
	mLocalTranslationL[19].mValue[1] = -0.177947998047;
	mLocalTranslationL[19].mValue[2] = -0.0118775367737;
}
