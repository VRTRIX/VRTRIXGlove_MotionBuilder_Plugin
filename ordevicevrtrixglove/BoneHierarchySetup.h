#pragma once
#include <fbsdk/fbsdk.h>
#define RHandIndex 30
#define LHandIndex 10
#define BoneNum	55 
#define HandBoneNum 17 

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
mChannel[0].mT[2] = 1.39929032326;
mChannel[0].mR[0] = 0.0;
mChannel[0].mR[1] = -0.0;
mChannel[0].mR[2] = 0.0;

//1:Hips
mChannel[1].mName = "Hips";
mChannel[1].mParentChannel = 0;
mChannel[1].mT[0] = 0.0;
mChannel[1].mT[1] = 98.1700057983;
mChannel[1].mT[2] = 1.76273387671;
mChannel[1].mR[0] = -90.0;
mChannel[1].mR[1] = -0.0;
mChannel[1].mR[2] = 0.0;

//2:Spine
mChannel[2].mName = "Spine";
mChannel[2].mParentChannel = 1;
mChannel[2].mT[0] = 1.89487795101e-16;
mChannel[2].mT[1] = 109.934700012;
mChannel[2].mT[2] = 1.49364078045;
mChannel[2].mR[0] = -180.0;
mChannel[2].mR[1] = -1.62305733751e-14;
mChannel[2].mR[2] = 90.0;

//3:Spine1
mChannel[3].mName = "Spine1";
mChannel[3].mParentChannel = 2;
mChannel[3].mT[0] = 4.83012068128e-15;
mChannel[3].mT[1] = 120.387275696;
mChannel[3].mT[2] = 1.87506434321;
mChannel[3].mR[0] = -180.0;
mChannel[3].mR[1] = 6.91347759879;
mChannel[3].mR[2] = 90.0;

//4:Spine2
mChannel[4].mName = "Spine2";
mChannel[4].mParentChannel = 3;
mChannel[4].mT[0] = 1.13218413095e-14;
mChannel[4].mT[1] = 130.496538568;
mChannel[4].mT[2] = 1.70672001419;
mChannel[4].mR[0] = -180.0;
mChannel[4].mR[1] = 9.87687751705;
mChannel[4].mR[2] = 90.0;

//5:Neck
mChannel[5].mName = "Neck";
mChannel[5].mParentChannel = 4;
mChannel[5].mT[0] = 2.6894233522e-14;
mChannel[5].mT[1] = 153.331051649;
mChannel[5].mT[2] = 1.2656732117;
mChannel[5].mR[0] = -180.0;
mChannel[5].mR[1] = -18.8529620515;
mChannel[5].mR[2] = 90.0;

//6:Head
mChannel[6].mName = "Head";
mChannel[6].mParentChannel = 5;
mChannel[6].mT[0] = 3.40564780687e-14;
mChannel[6].mT[1] = 160.130200959;
mChannel[6].mT[2] = 2.46706027941;
mChannel[6].mR[0] = -180.0;
mChannel[6].mR[1] = -1.27222187259e-14;
mChannel[6].mR[2] = 90.0;

//7:LeftShoulder
mChannel[7].mName = "LeftShoulder";
mChannel[7].mParentChannel = 4;
mChannel[7].mT[0] = 1.5034968853;
mChannel[7].mT[1] = 146.175534416;
mChannel[7].mT[2] = 1.49595092689;
mChannel[7].mR[0] = 2.86249921332e-14;
mChannel[7].mR[1] = -5.7506252011e-15;
mChannel[7].mR[2] = 180.0;

//8:LeftArm
mChannel[8].mName = "LeftArm";
mChannel[8].mParentChannel = 7;
mChannel[8].mT[0] = 15.1109363853;
mChannel[8].mT[1] = 146.175534416;
mChannel[8].mT[2] = 1.49595092689;
mChannel[8].mR[0] = 2.86249921332e-14;
mChannel[8].mR[1] = -5.7506252011e-15;
mChannel[8].mR[2] = 180.0;

//9:LeftForeArm
mChannel[9].mName = "LeftForeArm";
mChannel[9].mParentChannel = 8;
mChannel[9].mT[0] = 39.8006579254;
mChannel[9].mT[1] = 146.175534416;
mChannel[9].mT[2] = 1.49595092689;
mChannel[9].mR[0] = 2.86249921332e-14;
mChannel[9].mR[1] = -5.7506252011e-15;
mChannel[9].mR[2] = 180.0;

//10:LeftHand
mChannel[10].mName = "LeftHand";
mChannel[10].mParentChannel = 9;
mChannel[10].mT[0] = 63.4002061723;
mChannel[10].mT[1] = 146.175534416;
mChannel[10].mT[2] = 1.49595092689;
mChannel[10].mR[0] = 2.86249921332e-14;
mChannel[10].mR[1] = -5.7506252011e-15;
mChannel[10].mR[2] = 180.0;

//11:LeftFingerBase
mChannel[11].mName = "LeftFingerBase";
mChannel[11].mParentChannel = 10;
mChannel[11].mT[0] = 65.7180123985;
mChannel[11].mT[1] = 146.175534416;
mChannel[11].mT[2] = 1.49595092689;
mChannel[11].mR[0] = 2.86249921332e-14;
mChannel[11].mR[1] = -5.7506252011e-15;
mChannel[11].mR[2] = 180.0;

//12:LeftHandThumb1
mChannel[12].mName = "LeftHandThumb1";
mChannel[12].mParentChannel = 11;
mChannel[12].mT[0] = 66.7556360326;
mChannel[12].mT[1] = 143.969593694;
mChannel[12].mT[2] = 5.27379633818;
mChannel[12].mR[0] = -36.8506944366;
mChannel[12].mR[1] = 51.1237886749;
mChannel[12].mR[2] = 136.088329002;

//13:LeftHandThumb2
mChannel[13].mName = "LeftHandThumb2";
mChannel[13].mParentChannel = 12;
mChannel[13].mT[0] = 67.7406866937;
mChannel[13].mT[1] = 143.021271718;
mChannel[13].mT[2] = 6.96980915322;
mChannel[13].mR[0] = -14.7811332151;
mChannel[13].mR[1] = 38.9713777484;
mChannel[13].mR[2] = 157.240235486;

//14:LeftHandThumb3
mChannel[14].mName = "LeftHandThumb3";
mChannel[14].mParentChannel = 13;
mChannel[14].mT[0] = 70.169298767;
mChannel[14].mT[1] = 142.00238345;
mChannel[14].mT[2] = 9.100346644;
mChannel[14].mR[0] = -18.6903578046;
mChannel[14].mR[1] = 36.1465458025;
mChannel[14].mR[2] = 150.16475485;

//15:LeftHandIndex1
mChannel[15].mName = "LeftHandIndex1";
mChannel[15].mParentChannel = 11;
mChannel[15].mT[0] = 73.7859078342;
mChannel[15].mT[1] = 147.559871115;
mChannel[15].mT[2] = 6.56137433099;
mChannel[15].mR[0] = 7.378886861e-13;
mChannel[15].mR[1] = -7.93009522099e-14;
mChannel[15].mR[2] = 180.0;

//16:LeftHandIndex2
mChannel[16].mName = "LeftHandIndex2";
mChannel[16].mParentChannel = 15;
mChannel[16].mT[0] = 76.9671718878;
mChannel[16].mT[1] = 147.559871115;
mChannel[16].mT[2] = 6.56137433099;
mChannel[16].mR[0] = 7.378886861e-13;
mChannel[16].mR[1] = -7.93009522099e-14;
mChannel[16].mR[2] = 180.0;

//17:LeftHandIndex3
mChannel[17].mName = "LeftHandIndex3";
mChannel[17].mParentChannel = 16;
mChannel[17].mT[0] = 79.5877406851;
mChannel[17].mT[1] = 147.559871115;
mChannel[17].mT[2] = 6.56137433099;
mChannel[17].mR[0] = 7.378886861e-13;
mChannel[17].mR[1] = -7.93009522099e-14;
mChannel[17].mR[2] = 180.0;

//18:LeftHandMiddle1
mChannel[18].mName = "LeftHandMiddle1";
mChannel[18].mParentChannel = 11;
mChannel[18].mT[0] = 73.8035854221;
mChannel[18].mT[1] = 148.09541609;
mChannel[18].mT[2] = 4.21910293542;
mChannel[18].mR[0] = 7.09263693966e-13;
mChannel[18].mR[1] = -3.11879013292e-13;
mChannel[18].mR[2] = 180.0;

//19:LeftHandMiddle2
mChannel[19].mName = "LeftHandMiddle2";
mChannel[19].mParentChannel = 18;
mChannel[19].mT[0] = 77.5166651598;
mChannel[19].mT[1] = 148.09541609;
mChannel[19].mT[2] = 4.21910293542;
mChannel[19].mR[0] = 7.09263693966e-13;
mChannel[19].mR[1] = -3.11879013292e-13;
mChannel[19].mR[2] = 180.0;

//20:LeftHandMiddle3
mChannel[20].mName = "LeftHandMiddle3";
mChannel[20].mParentChannel = 19;
mChannel[20].mT[0] = 80.3347989206;
mChannel[20].mT[1] = 148.09541609;
mChannel[20].mT[2] = 4.21910293542;
mChannel[20].mR[0] = 7.09263693966e-13;
mChannel[20].mR[1] = -3.11879013292e-13;
mChannel[20].mR[2] = 180.0;

//21:LeftHandRing1
mChannel[21].mName = "LeftHandRing1";
mChannel[21].mParentChannel = 11;
mChannel[21].mT[0] = 73.868587663;
mChannel[21].mT[1] = 147.822798093;
mChannel[21].mT[2] = 1.82701164289;
mChannel[21].mR[0] = 7.42659518122e-13;
mChannel[21].mR[1] = -2.32365146255e-13;
mChannel[21].mR[2] = 180.0;

//22:LeftHandRing2
mChannel[22].mName = "LeftHandRing2";
mChannel[22].mParentChannel = 21;
mChannel[22].mT[0] = 77.2557387113;
mChannel[22].mT[1] = 147.822798093;
mChannel[22].mT[2] = 1.82701164289;
mChannel[22].mR[0] = 7.42659518122e-13;
mChannel[22].mR[1] = -2.32365146255e-13;
mChannel[22].mR[2] = 180.0;

//23:LeftHandRing3
mChannel[23].mName = "LeftHandRing3";
mChannel[23].mParentChannel = 22;
mChannel[23].mT[0] = 79.941958811;
mChannel[23].mT[1] = 147.822798093;
mChannel[23].mT[2] = 1.82701164289;
mChannel[23].mR[0] = 7.42659518122e-13;
mChannel[23].mR[1] = -2.32365146255e-13;
mChannel[23].mR[2] = 180.0;

//24:LeftHandPinky1
mChannel[24].mName = "LeftHandPinky1";
mChannel[24].mParentChannel = 11;
mChannel[24].mT[0] = 73.8379736611;
mChannel[24].mT[1] = 147.037852185;
mChannel[24].mT[2] = -0.329368654797;
mChannel[24].mR[0] = 7.58562291529e-13;
mChannel[24].mR[1] = -9.34472592188e-13;
mChannel[24].mR[2] = 180.0;

//25:LeftHandPinky2
mChannel[25].mName = "LeftHandPinky2";
mChannel[25].mParentChannel = 24;
mChannel[25].mT[0] = 76.4410882242;
mChannel[25].mT[1] = 147.037852185;
mChannel[25].mT[2] = -0.329368654797;
mChannel[25].mR[0] = 7.58562291529e-13;
mChannel[25].mR[1] = -9.34472592188e-13;
mChannel[25].mR[2] = 180.0;

//26:LeftHandPinky3
mChannel[26].mName = "LeftHandPinky3";
mChannel[26].mParentChannel = 25;
mChannel[26].mT[0] = 78.4356687987;
mChannel[26].mT[1] = 147.037852185;
mChannel[26].mT[2] = -0.329368654797;
mChannel[26].mR[0] = 7.58562291529e-13;
mChannel[26].mR[1] = -9.34472592188e-13;
mChannel[26].mR[2] = 180.0;

//27:RightShoulder
mChannel[27].mName = "RightShoulder";
mChannel[27].mParentChannel = 4;
mChannel[27].mT[0] = -1.5035;
mChannel[27].mT[1] = 146.176;
mChannel[27].mT[2] = 1.49595;
mChannel[27].mR[0] = -180.0;
mChannel[27].mR[1] = 2.12742575148e-14;
mChannel[27].mR[2] = 180.0;

//28:RightArm
mChannel[28].mName = "RightArm";
mChannel[28].mParentChannel = 27;
mChannel[28].mT[0] = -15.1109;
mChannel[28].mT[1] = 146.176;
mChannel[28].mT[2] = 1.49595;
mChannel[28].mR[0] = -180.0;
mChannel[28].mR[1] = 2.12742575148e-14;
mChannel[28].mR[2] = 180.0;

//29:RightForeArm
mChannel[29].mName = "RightForeArm";
mChannel[29].mParentChannel = 28;
mChannel[29].mT[0] = -39.8007;
mChannel[29].mT[1] = 146.176;
mChannel[29].mT[2] = 1.49595;
mChannel[29].mR[0] = -180.0;
mChannel[29].mR[1] = 2.12742575148e-14;
mChannel[29].mR[2] = 180.0;

//30:RightHand
mChannel[30].mName = "RightHand";
mChannel[30].mParentChannel = 29;
mChannel[30].mT[0] = -63.4002;
mChannel[30].mT[1] = 146.176;
mChannel[30].mT[2] = 1.49595;
mChannel[30].mR[0] = -180.0;
mChannel[30].mR[1] = 2.12742575148e-14;
mChannel[30].mR[2] = 180.0;

//31:RightFingerBase
mChannel[31].mName = "RightFingerBase";
mChannel[31].mParentChannel = 30;
mChannel[31].mT[0] = -65.718;
mChannel[31].mT[1] = 146.176;
mChannel[31].mT[2] = 1.49595;
mChannel[31].mR[0] = -180.0;
mChannel[31].mR[1] = 2.12742575148e-14;
mChannel[31].mR[2] = 180.0;

//32:RightHandThumb1
mChannel[32].mName = "RightHandThumb1";
mChannel[32].mParentChannel = 31;
mChannel[32].mT[0] = -66.7556;
mChannel[32].mT[1] = 143.97;
mChannel[32].mT[2] = 5.2738;
mChannel[32].mR[0] = 143.149305563;
mChannel[32].mR[1] = -51.1237886749;
mChannel[32].mR[2] = -136.088329002;

//33:RightHandThumb2
mChannel[33].mName = "RightHandThumb2";
mChannel[33].mParentChannel = 32;
mChannel[33].mT[0] = -67.7407;
mChannel[33].mT[1] = 143.021;
mChannel[33].mT[2] = 6.96981;
mChannel[33].mR[0] = 165.218866785;
mChannel[33].mR[1] = -38.9713777484;
mChannel[33].mR[2] = -157.240235486;

//34:RightHandThumb3
mChannel[34].mName = "RightHandThumb3";
mChannel[34].mParentChannel = 33;
mChannel[34].mT[0] = -70.1693;
mChannel[34].mT[1] = 142.002;
mChannel[34].mT[2] = 9.10035;
mChannel[34].mR[0] = 161.309642195;
mChannel[34].mR[1] = -36.1465458025;
mChannel[34].mR[2] = -150.16475485;

//35:RightHandIndex1
mChannel[35].mName = "RightHandIndex1";
mChannel[35].mParentChannel = 31;
mChannel[35].mT[0] = -73.7859;
mChannel[35].mT[1] = 147.56;
mChannel[35].mT[2] = 6.56137;
mChannel[35].mR[0] = -180.0;
mChannel[35].mR[1] = 9.48245845237e-14;
mChannel[35].mR[2] = -180.0;

//36:RightHandIndex2
mChannel[36].mName = "RightHandIndex2";
mChannel[36].mParentChannel = 35;
mChannel[36].mT[0] = -76.9672;
mChannel[36].mT[1] = 147.56;
mChannel[36].mT[2] = 6.56137;
mChannel[36].mR[0] = -180.0;
mChannel[36].mR[1] = 9.48245845237e-14;
mChannel[36].mR[2] = -180.0;

//37:RightHandIndex3
mChannel[37].mName = "RightHandIndex3";
mChannel[37].mParentChannel = 36;
mChannel[37].mT[0] = -79.5877;
mChannel[37].mT[1] = 147.56;
mChannel[37].mT[2] = 6.56137;
mChannel[37].mR[0] = -180.0;
mChannel[37].mR[1] = 9.48245845237e-14;
mChannel[37].mR[2] = -180.0;

//38:RightHandMiddle1
mChannel[38].mName = "RightHandMiddle1";
mChannel[38].mParentChannel = 31;
mChannel[38].mT[0] = -73.8036;
mChannel[38].mT[1] = 148.095;
mChannel[38].mT[2] = 4.2191;
mChannel[38].mR[0] = -180.0;
mChannel[38].mR[1] = 3.27402645606e-13;
mChannel[38].mR[2] = -180.0;

//39:RightHandMiddle2
mChannel[39].mName = "RightHandMiddle2";
mChannel[39].mParentChannel = 38;
mChannel[39].mT[0] = -77.5167;
mChannel[39].mT[1] = 148.095;
mChannel[39].mT[2] = 4.2191;
mChannel[39].mR[0] = -180.0;
mChannel[39].mR[1] = 3.27402645606e-13;
mChannel[39].mR[2] = -180.0;

//40:RightHandMiddle3
mChannel[40].mName = "RightHandMiddle3";
mChannel[40].mParentChannel = 39;
mChannel[40].mT[0] = -80.3348;
mChannel[40].mT[1] = 148.095;
mChannel[40].mT[2] = 4.2191;
mChannel[40].mR[0] = -180.0;
mChannel[40].mR[1] = 3.27402645606e-13;
mChannel[40].mR[2] = -180.0;

//41:RightHandRing1
mChannel[41].mName = "RightHandRing1";
mChannel[41].mParentChannel = 31;
mChannel[41].mT[0] = -73.8686;
mChannel[41].mT[1] = 147.823;
mChannel[41].mT[2] = 1.82701;
mChannel[41].mR[0] = -180.0;
mChannel[41].mR[1] = 2.47888778569e-13;
mChannel[41].mR[2] = -180.0;

//42:RightHandRing2
mChannel[42].mName = "RightHandRing2";
mChannel[42].mParentChannel = 41;
mChannel[42].mT[0] = -77.2557;
mChannel[42].mT[1] = 147.823;
mChannel[42].mT[2] = 1.82701;
mChannel[42].mR[0] = -180.0;
mChannel[42].mR[1] = 2.47888778569e-13;
mChannel[42].mR[2] = -180.0;

//43:RightHandRing3
mChannel[43].mName = "RightHandRing3";
mChannel[43].mParentChannel = 42;
mChannel[43].mT[0] = -79.942;
mChannel[43].mT[1] = 147.823;
mChannel[43].mT[2] = 1.82701;
mChannel[43].mR[0] = -180.0;
mChannel[43].mR[1] = 2.47888778569e-13;
mChannel[43].mR[2] = -180.0;

//44:RightHandPinky1
mChannel[44].mName = "RightHandPinky1";
mChannel[44].mParentChannel = 31;
mChannel[44].mT[0] = -73.838;
mChannel[44].mT[1] = 147.038;
mChannel[44].mT[2] = -0.329369;
mChannel[44].mR[0] = -180.0;
mChannel[44].mR[1] = 9.49996224502e-13;
mChannel[44].mR[2] = -180.0;

//45:RightHandPinky2
mChannel[45].mName = "RightHandPinky2";
mChannel[45].mParentChannel = 44;
mChannel[45].mT[0] = -76.4411;
mChannel[45].mT[1] = 147.038;
mChannel[45].mT[2] = -0.329369;
mChannel[45].mR[0] = -180.0;
mChannel[45].mR[1] = 9.49996224502e-13;
mChannel[45].mR[2] = -180.0;

//46:RightHandPinky3
mChannel[46].mName = "RightHandPinky3";
mChannel[46].mParentChannel = 45;
mChannel[46].mT[0] = -78.4357;
mChannel[46].mT[1] = 147.038;
mChannel[46].mT[2] = -0.329369;
mChannel[46].mR[0] = -180.0;
mChannel[46].mR[1] = 9.49996224502e-13;
mChannel[46].mR[2] = -180.0;

//47:LeftUpLeg
mChannel[47].mName = "LeftUpLeg";
mChannel[47].mParentChannel = 1;
mChannel[47].mT[0] = 8.61240100861;
mChannel[47].mT[1] = 93.3364129066;
mChannel[47].mT[2] = 1.82888378948;
mChannel[47].mR[0] = 0.0264600386521;
mChannel[47].mR[1] = 1.68387480388;
mChannel[47].mR[2] = 90.9003888471;

//48:LeftLeg
mChannel[48].mName = "LeftLeg";
mChannel[48].mParentChannel = 47;
mChannel[48].mT[0] = 9.26350623306;
mChannel[48].mT[1] = 51.9070786439;
mChannel[48].mT[2] = 3.0469544612;
mChannel[48].mR[0] = 0.0264592316833;
mChannel[48].mR[1] = -1.62334569064;
mChannel[48].mR[2] = 90.8988617588;

//49:LeftFoot
mChannel[49].mName = "LeftFoot";
mChannel[49].mParentChannel = 48;
mChannel[49].mT[0] = 9.91946691655;
mChannel[49].mT[1] = 11.8752676909;
mChannel[49].mT[2] = 0.785645392167;
mChannel[49].mR[0] = -94.049242617;
mChannel[49].mR[1] = 67.1995620498;
mChannel[49].mR[2] = 87.1658380361;

//50:LeftToeBase
mChannel[50].mName = "LeftToeBase";
mChannel[50].mParentChannel = 49;
mChannel[50].mT[0] = 11.4009849324;
mChannel[50].mT[1] = 2.47775734032;
mChannel[50].mT[2] = 12.8220852829;
mChannel[50].mR[0] = -95.8058310697;
mChannel[50].mR[1] = 74.3051832694;
mChannel[50].mR[2] = 85.308840598;

//51:RightUpLeg
mChannel[51].mName = "RightUpLeg";
mChannel[51].mParentChannel = 1;
mChannel[51].mT[0] = -8.61240196228;
mChannel[51].mT[1] = 93.3363656998;
mChannel[51].mT[2] = 1.82888379693;
mChannel[51].mR[0] = -179.973539961;
mChannel[51].mR[1] = -1.68387480388;
mChannel[51].mR[2] = -90.9003888471;

//52:RightLeg
mChannel[52].mName = "RightLeg";
mChannel[52].mParentChannel = 51;
mChannel[52].mT[0] = -9.26350388695;
mChannel[52].mT[1] = 51.9070887667;
mChannel[52].mT[2] = 3.04695886654;
mChannel[52].mR[0] = -179.973540768;
mChannel[52].mR[1] = 1.62334569064;
mChannel[52].mR[2] = -90.8988617588;

//53:RightFoot
mChannel[53].mName = "RightFoot";
mChannel[53].mParentChannel = 52;
mChannel[53].mT[0] = -9.91945855479;
mChannel[53].mT[1] = 11.8752549388;
mChannel[53].mT[2] = 0.785645577202;
mChannel[53].mR[0] = 85.950757383;
mChannel[53].mR[1] = -67.1995620498;
mChannel[53].mR[2] = -87.1658380361;

//54:RightToeBase
mChannel[54].mName = "RightToeBase";
mChannel[54].mParentChannel = 53;
mChannel[54].mT[0] = -11.401001981;
mChannel[54].mT[1] = 2.47775873293;
mChannel[54].mT[2] = 12.8220422784;
mChannel[54].mR[0] = 84.1941689303;
mChannel[54].mR[1] = -74.3051832694;
mChannel[54].mR[2] = -85.308840598;
}

static void HandHierarchySetup(FBTVector* mLocalTranslationR, FBTVector* mLocalTranslationL) {
//0:RightHand
mLocalTranslationR[0].mValue[0] = -63.4002;
mLocalTranslationR[0].mValue[1] = 146.176;
mLocalTranslationR[0].mValue[2] = 1.49595;

//1:RightFingerBase
mLocalTranslationR[1].mValue[0] = 2.3178;
mLocalTranslationR[1].mValue[1] = 2.84217094304e-14;
mLocalTranslationR[1].mValue[2] = 8.881784197e-16;

//2:RightHandThumb1
mLocalTranslationR[2].mValue[0] = 1.0376;
mLocalTranslationR[2].mValue[1] = -2.206;
mLocalTranslationR[2].mValue[2] = -3.77785;

//3:RightHandThumb2
mLocalTranslationR[3].mValue[0] = 2.1788695618;
mLocalTranslationR[3].mValue[1] = -0.000600688066214;
mLocalTranslationR[3].mValue[2] = 4.40786303813e-05;

//4:RightHandThumb3
mLocalTranslationR[4].mValue[0] = 3.38757430024;
mLocalTranslationR[4].mValue[1] = -0.000108790765125;
mLocalTranslationR[4].mValue[2] = -9.84822704453e-06;

//5:RightHandIndex1
mLocalTranslationR[5].mValue[0] = 8.0679;
mLocalTranslationR[5].mValue[1] = 1.384;
mLocalTranslationR[5].mValue[2] = -5.06542;

//6:RightHandIndex2
mLocalTranslationR[6].mValue[0] = 3.1813;
mLocalTranslationR[6].mValue[1] = 0.0;
mLocalTranslationR[6].mValue[2] = 2.6645352591e-15;

//7:RightHandIndex3
mLocalTranslationR[7].mValue[0] = 2.6205;
mLocalTranslationR[7].mValue[1] = 0.0;
mLocalTranslationR[7].mValue[2] = 1.7763568394e-15;

//8:RightHandMiddle1
mLocalTranslationR[8].mValue[0] = 8.0856;
mLocalTranslationR[8].mValue[1] = 1.919;
mLocalTranslationR[8].mValue[2] = -2.72315;

//9:RightHandMiddle2
mLocalTranslationR[9].mValue[0] = 3.7131;
mLocalTranslationR[9].mValue[1] = 0.0;
mLocalTranslationR[9].mValue[2] = 1.7763568394e-15;

//10:RightHandMiddle3
mLocalTranslationR[10].mValue[0] = 2.8181;
mLocalTranslationR[10].mValue[1] = 0.0;
mLocalTranslationR[10].mValue[2] = 8.881784197e-16;

//11:RightHandRing1
mLocalTranslationR[11].mValue[0] = 8.1506;
mLocalTranslationR[11].mValue[1] = 1.647;
mLocalTranslationR[11].mValue[2] = -0.33106;

//12:RightHandRing2
mLocalTranslationR[12].mValue[0] = 3.3871;
mLocalTranslationR[12].mValue[1] = 0.0;
mLocalTranslationR[12].mValue[2] = 1.7763568394e-15;

//13:RightHandRing3
mLocalTranslationR[13].mValue[0] = 2.6863;
mLocalTranslationR[13].mValue[1] = 0.0;
mLocalTranslationR[13].mValue[2] = 1.11022302463e-15;

//14:RightHandPinky1
mLocalTranslationR[14].mValue[0] = 8.12;
mLocalTranslationR[14].mValue[1] = 0.862;
mLocalTranslationR[14].mValue[2] = 1.825319;

//15:RightHandPinky2
mLocalTranslationR[15].mValue[0] = 2.6031;
mLocalTranslationR[15].mValue[1] = 0.0;
mLocalTranslationR[15].mValue[2] = 1.55431223448e-15;

//16:RightHandPinky3
mLocalTranslationR[16].mValue[0] = 1.9946;
mLocalTranslationR[16].mValue[1] = 0.0;
mLocalTranslationR[16].mValue[2] = 9.43689570931e-16;

//0:LeftHand
mLocalTranslationL[0].mValue[0] = 63.4002061723;
mLocalTranslationL[0].mValue[1] = 146.175534416;
mLocalTranslationL[0].mValue[2] = 1.49595092689;

//1:LeftFingerBase
mLocalTranslationL[1].mValue[0] = -2.3178062262;
mLocalTranslationL[1].mValue[1] = 0.0;
mLocalTranslationL[1].mValue[2] = 4.4408920985e-16;

//2:LeftHandThumb1
mLocalTranslationL[2].mValue[0] = -1.03762363414;
mLocalTranslationL[2].mValue[1] = 2.20594072222;
mLocalTranslationL[2].mValue[2] = 3.77784541129;

//3:LeftHandThumb2
mLocalTranslationL[3].mValue[0] = -2.17855430156;
mLocalTranslationL[3].mValue[1] = 5.68434188608e-14;
mLocalTranslationL[3].mValue[2] = -5.68434188608e-14;

//4:LeftHandThumb3
mLocalTranslationL[4].mValue[0] = -3.38754777148;
mLocalTranslationL[4].mValue[1] = 2.84217094304e-14;
mLocalTranslationL[4].mValue[2] = 7.1054273576e-14;

//5:LeftHandIndex1
mLocalTranslationL[5].mValue[0] = -8.06789543575;
mLocalTranslationL[5].mValue[1] = -1.38433669837;
mLocalTranslationL[5].mValue[2] = 5.0654234041;

//6:LeftHandIndex2
mLocalTranslationL[6].mValue[0] = -3.1812640536;
mLocalTranslationL[6].mValue[1] = 0.0;
mLocalTranslationL[6].mValue[2] = 1.42108547152e-14;

//7:LeftHandIndex3
mLocalTranslationL[7].mValue[0] = -2.62056879724;
mLocalTranslationL[7].mValue[1] = 0.0;
mLocalTranslationL[7].mValue[2] = -8.881784197e-15;

//8:LeftHandMiddle1
mLocalTranslationL[8].mValue[0] = -8.0855730236;
mLocalTranslationL[8].mValue[1] = -1.91988167329;
mLocalTranslationL[8].mValue[2] = 2.72315200853;

//9:LeftHandMiddle2
mLocalTranslationL[9].mValue[0] = -3.71307973772;
mLocalTranslationL[9].mValue[1] = 0.0;
mLocalTranslationL[9].mValue[2] = -1.86517468137e-14;

//10:LeftHandMiddle3
mLocalTranslationL[10].mValue[0] = -2.81813376077;
mLocalTranslationL[10].mValue[1] = 0.0;
mLocalTranslationL[10].mValue[2] = -1.50990331349e-14;

//11:LeftHandRing1
mLocalTranslationL[11].mValue[0] = -8.15057526457;
mLocalTranslationL[11].mValue[1] = -1.64726367662;
mLocalTranslationL[11].mValue[2] = 0.331060716007;

//12:LeftHandRing2
mLocalTranslationL[12].mValue[0] = -3.38715104831;
mLocalTranslationL[12].mValue[1] = 0.0;
mLocalTranslationL[12].mValue[2] = 1.84297022088e-14;

//13:LeftHandRing3
mLocalTranslationL[13].mValue[0] = -2.68622009962;
mLocalTranslationL[13].mValue[1] = 5.68434188608e-14;
mLocalTranslationL[13].mValue[2] = 8.881784197e-16;

//14:LeftHandPinky1
mLocalTranslationL[14].mValue[0] = -8.11996126259;
mLocalTranslationL[14].mValue[1] = -0.862317768267;
mLocalTranslationL[14].mValue[2] = -1.82531958168;

//15:LeftHandPinky2
mLocalTranslationL[15].mValue[0] = -2.6031145631;
mLocalTranslationL[15].mValue[1] = -2.84217094304e-14;
mLocalTranslationL[15].mValue[2] = -2.57016630201e-14;

//16:LeftHandPinky3
mLocalTranslationL[16].mValue[0] = -1.99458057454;
mLocalTranslationL[16].mValue[1] = 2.84217094304e-14;
mLocalTranslationL[16].mValue[2] = -1.0325074129e-14;
}

