#pragma once
#include <fbsdk/fbsdk.h>
#define RHandIndex 31
#define LHandIndex 12
#define BoneNum	55 
#define HandBoneNum 16 
#define Scale	100

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

//1:Hips
mChannel[1].mName = "Hips";
mChannel[1].mParentChannel = 0;
mChannel[1].mT[0] = 0.0;
mChannel[1].mT[1] = 95.2000021935;
mChannel[1].mT[2] = 0.200000009499;
mChannel[1].mR[0] = -89.9999999974;
mChannel[1].mR[1] = -89.9999214528;
mChannel[1].mR[2] = -2.55914885715e-09;

//2:Spine
mChannel[2].mName = "Spine";
mChannel[2].mParentChannel = 1;
mChannel[2].mT[0] = 0.0;
mChannel[2].mT[1] = 95.2000021935;
mChannel[2].mT[2] = 0.200000009499;
mChannel[2].mR[0] = 90.000158005;
mChannel[2].mR[1] = -7.01671653859e-15;
mChannel[2].mR[2] = 90.0;

//3:Spine1
mChannel[3].mName = "Spine1";
mChannel[3].mParentChannel = 2;
mChannel[3].mT[0] = 1.2302179826e-05;
mChannel[3].mT[1] = 105.117702484;
mChannel[3].mT[2] = -0.858722464221;
mChannel[3].mR[0] = 89.9999213637;
mChannel[3].mR[1] = -7.30050938227e-08;
mChannel[3].mR[2] = 89.9999152931;

//4:Spine2
mChannel[4].mName = "Spine2";
mChannel[4].mParentChannel = 3;
mChannel[4].mT[0] = 2.90497099828e-05;
mChannel[4].mT[1] = 116.454291344;
mChannel[4].mT[2] = -0.867749480096;
mChannel[4].mR[0] = 89.9999213124;
mChannel[4].mR[1] = -2.86448505331e-07;
mChannel[4].mR[2] = 89.9999152932;

//5:Spine3
mChannel[5].mName = "Spine3";
mChannel[5].mParentChannel = 4;
mChannel[5].mT[0] = 4.57978690926e-05;
mChannel[5].mT[1] = 127.790892124;
mChannel[5].mT[2] = -0.87677654687;
mChannel[5].mR[0] = 89.9999173698;
mChannel[5].mR[1] = -1.14022214728e-06;
mChannel[5].mR[2] = 89.9999152963;

//6:Spine4
mChannel[6].mName = "Spine4";
mChannel[6].mParentChannel = 5;
mChannel[6].mT[0] = 6.25463692928e-05;
mChannel[6].mT[1] = 139.127480984;
mChannel[6].mT[2] = -0.885803444716;
mChannel[6].mR[0] = 89.9999111613;
mChannel[6].mR[1] = 5.67325152369e-07;
mChannel[6].mR[2] = 89.9999153013;

//7:Neck
mChannel[7].mName = "Neck";
mChannel[7].mParentChannel = 6;
mChannel[7].mT[0] = 8.07757449856e-05;
mChannel[7].mT[1] = 151.01190806;
mChannel[7].mT[2] = -0.347208448481;
mChannel[7].mR[0] = 89.9998887287;
mChannel[7].mR[1] = 3.53881731856e-07;
mChannel[7].mR[2] = 89.9999184626;

//8:Head
mChannel[8].mName = "Head";
mChannel[8].mParentChannel = 7;
mChannel[8].mT[0] = -5.91094100972e-06;
mChannel[8].mT[1] = 160.875427733;
mChannel[8].mT[2] = 0.315097860624;
mChannel[8].mR[0] = 89.9998954574;
mChannel[8].mR[1] = 3.2737350599e-07;
mChannel[8].mR[2] = 89.9999054356;

//9:LeftShoulder
mChannel[9].mName = "LeftShoulder";
mChannel[9].mParentChannel = 7;
mChannel[9].mT[0] = 3.0301778885;
mChannel[9].mT[1] = 149.08755587;
mChannel[9].mT[2] = -0.414911053584;
mChannel[9].mR[0] = -90.0449536453;
mChannel[9].mR[1] = 0.405138261366;
mChannel[9].mR[2] = 0.0948268311908;

//10:LeftArm
mChannel[10].mName = "LeftArm";
mChannel[10].mParentChannel = 9;
mChannel[10].mT[0] = 16.1974300605;
mChannel[10].mT[1] = 149.109336304;
mChannel[10].mT[2] = -0.508018271965;
mChannel[10].mR[0] = -90.0449528081;
mChannel[10].mR[1] = 0.405136486848;
mChannel[10].mR[2] = 0.0948216564488;

//11:LeftForeArm
mChannel[11].mName = "LeftForeArm";
mChannel[11].mParentChannel = 10;
mChannel[11].mT[0] = 48.5238723791;
mChannel[11].mT[1] = 149.162846923;
mChannel[11].mT[2] = -0.736601496359;
mChannel[11].mR[0] = -90.0449528081;
mChannel[11].mR[1] = 0.405136478771;
mChannel[11].mR[2] = 0.0948216564551;

//12:LeftHand
mChannel[12].mName = "LeftHand";
mChannel[12].mParentChannel = 11;
mChannel[12].mT[0] = 71.9114474719;
mChannel[12].mT[1] = 149.201540307;
mChannel[12].mT[2] = -0.90197722882;
mChannel[12].mR[0] = 179.955735458;
mChannel[12].mR[1] = 0.405132308546;
mChannel[12].mR[2] = 0.0948213195402;

//13:LeftHandThumb1
mChannel[13].mName = "LeftHandThumb1";
mChannel[13].mParentChannel = 12;
mChannel[13].mT[0] = 74.8901665987;
mChannel[13].mT[1] = 148.976325594;
mChannel[13].mT[2] = 3.38410527446;
mChannel[13].mR[0] = 179.955721315;
mChannel[13].mR[1] = 0.405142565743;
mChannel[13].mR[2] = 0.0948021078693;

//14:LeftHandThumb2
mChannel[14].mName = "LeftHandThumb2";
mChannel[14].mParentChannel = 13;
mChannel[14].mT[0] = 79.1086464671;
mChannel[14].mT[1] = 148.983305535;
mChannel[14].mT[2] = 3.3542755628;
mChannel[14].mR[0] = 179.955721318;
mChannel[14].mR[1] = 0.40514254262;
mChannel[14].mR[2] = 0.0948021012169;

//15:LeftHandThumb3
mChannel[15].mName = "LeftHandThumb3";
mChannel[15].mParentChannel = 14;
mChannel[15].mT[0] = 81.8213760316;
mChannel[15].mT[1] = 148.987805967;
mChannel[15].mT[2] = 3.33509367583;
mChannel[15].mR[0] = 179.955721321;
mChannel[15].mR[1] = 0.405142519497;
mChannel[15].mR[2] = 0.0948020945645;

//16:LeftHandIndex1
mChannel[16].mName = "LeftHandIndex1";
mChannel[16].mParentChannel = 12;
mChannel[16].mT[0] = 81.0613884829;
mChannel[16].mT[1] = 149.634315757;
mChannel[16].mT[2] = 1.09361786189;
mChannel[16].mR[0] = 179.955745838;
mChannel[16].mR[1] = 0.405119673035;
mChannel[16].mR[2] = 0.0948701823978;

//17:LeftHandIndex2
mChannel[17].mName = "LeftHandIndex2";
mChannel[17].mParentChannel = 16;
mChannel[17].mT[0] = 85.525861467;
mChannel[17].mT[1] = 149.641719946;
mChannel[17].mT[2] = 1.0620502721;
mChannel[17].mR[0] = 179.955745892;
mChannel[17].mR[1] = 0.405119689751;
mChannel[17].mR[2] = 0.0948701757146;

//18:LeftHandIndex3
mChannel[18].mName = "LeftHandIndex3";
mChannel[18].mParentChannel = 17;
mChannel[18].mT[0] = 88.0669015236;
mChannel[18].mT[1] = 149.645915475;
mChannel[18].mT[2] = 1.04408309547;
mChannel[18].mR[0] = 179.955745892;
mChannel[18].mR[1] = 0.405119813282;
mChannel[18].mR[2] = 0.0948697420512;

//19:LeftHandMiddle1
mChannel[19].mName = "LeftHandMiddle1";
mChannel[19].mParentChannel = 12;
mChannel[19].mT[0] = 80.7368363661;
mChannel[19].mT[1] = 149.70989887;
mChannel[19].mT[2] = -1.05796468833;
mChannel[19].mR[0] = 179.955728752;
mChannel[19].mR[1] = 0.40513402748;
mChannel[19].mR[2] = 0.0948408554576;

//20:LeftHandMiddle2
mChannel[20].mName = "LeftHandMiddle2";
mChannel[20].mParentChannel = 19;
mChannel[20].mT[0] = 85.510307315;
mChannel[20].mT[1] = 149.717800333;
mChannel[20].mT[2] = -1.09171814116;
mChannel[20].mR[0] = 179.955728753;
mChannel[20].mR[1] = 0.405134039091;
mChannel[20].mR[2] = 0.0948404218808;

//21:LeftHandMiddle3
mChannel[21].mName = "LeftHandMiddle3";
mChannel[21].mParentChannel = 20;
mChannel[21].mT[0] = 88.3289357444;
mChannel[21].mT[1] = 149.722465949;
mChannel[21].mT[2] = -1.11164885148;
mChannel[21].mR[0] = 179.955728756;
mChannel[21].mR[1] = 0.405134051038;
mChannel[21].mR[2] = 0.0948404218716;

//22:LeftHandRing1
mChannel[22].mName = "LeftHandRing1";
mChannel[22].mParentChannel = 12;
mChannel[22].mT[0] = 80.5206938386;
mChannel[22].mT[1] = 149.156537862;
mChannel[22].mT[2] = -3.15811726996;
mChannel[22].mR[0] = 179.955748985;
mChannel[22].mR[1] = 0.405179571166;
mChannel[22].mR[2] = 0.0948237777092;

//23:LeftHandRing2
mChannel[23].mName = "LeftHandRing2";
mChannel[23].mParentChannel = 22;
mChannel[23].mT[0] = 85.2484687992;
mChannel[23].mT[1] = 149.164362276;
mChannel[23].mT[2] = -3.19155117611;
mChannel[23].mR[0] = 179.955748983;
mChannel[23].mR[1] = 0.405179549756;
mChannel[23].mR[2] = 0.0948229172599;

//24:LeftHandRing3
mChannel[24].mName = "LeftHandRing3";
mChannel[24].mParentChannel = 23;
mChannel[24].mT[0] = 87.7450032045;
mChannel[24].mT[1] = 149.168493975;
mChannel[24].mT[2] = -3.2092062799;
mChannel[24].mR[0] = 179.955748983;
mChannel[24].mR[1] = 0.40517952902;
mChannel[24].mR[2] = 0.0948224837078;

//25:LeftHandPinky1
mChannel[25].mName = "LeftHandPinky1";
mChannel[25].mParentChannel = 12;
mChannel[25].mT[0] = 79.9638393089;
mChannel[25].mT[1] = 148.343538648;
mChannel[25].mT[2] = -5.05054674083;
mChannel[25].mR[0] = 179.955752323;
mChannel[25].mR[1] = 0.405148435058;
mChannel[25].mR[2] = 0.0948189858273;

//26:LeftHandPinky2
mChannel[26].mName = "LeftHandPinky2";
mChannel[26].mParentChannel = 25;
mChannel[26].mT[0] = 82.940157143;
mChannel[26].mT[1] = 148.34845225;
mChannel[26].mT[2] = -5.07159317282;
mChannel[26].mR[0] = 179.955752326;
mChannel[26].mR[1] = 0.405148449623;
mChannel[26].mR[2] = 0.0948198462805;

//27:LeftHandPinky3
mChannel[27].mName = "LeftHandPinky3";
mChannel[27].mParentChannel = 26;
mChannel[27].mT[0] = 85.1108018731;
mChannel[27].mT[1] = 148.352056414;
mChannel[27].mT[2] = -5.08694246648;
mChannel[27].mR[0] = 179.955752329;
mChannel[27].mR[1] = 0.405148463511;
mChannel[27].mR[2] = 0.0948207067341;

//28:RightShoulder
mChannel[28].mName = "RightShoulder";
mChannel[28].mParentChannel = 7;
mChannel[28].mT[0] = -3.03002229618;
mChannel[28].mT[1] = 149.087564494;
mChannel[28].mT[2] = -0.41490363755;
mChannel[28].mR[0] = -89.9444413131;
mChannel[28].mR[1] = 1.2393307789;
mChannel[28].mR[2] = -179.540383558;

//29:RightArm
mChannel[29].mName = "RightArm";
mChannel[29].mParentChannel = 28;
mChannel[29].mT[0] = -16.1941171675;
mChannel[29].mT[1] = 148.981962227;
mChannel[29].mT[2] = -0.699701842907;
mChannel[29].mR[0] = -89.9444414542;
mChannel[29].mR[1] = 1.23932923107;
mChannel[29].mR[2] = -179.540387616;

//30:RightForeArm
mChannel[30].mName = "RightForeArm";
mChannel[30].mParentChannel = 29;
mChannel[30].mT[0] = -48.5128160883;
mChannel[30].mT[1] = 148.722704162;
mChannel[30].mT[2] = -1.39889900379;
mChannel[30].mR[0] = -89.9444414542;
mChannel[30].mR[1] = 1.2393291732;
mChannel[30].mR[2] = -179.540387616;

//31:RightHand
mChannel[31].mName = "RightHand";
mChannel[31].mParentChannel = 30;
mChannel[31].mT[0] = -71.8947905939;
mChannel[31].mT[1] = 148.535135799;
mChannel[31].mT[2] = -1.90475499189;
mChannel[31].mR[0] = 0.0547440218888;
mChannel[31].mR[1] = 1.23933593881;
mChannel[31].mR[2] = -179.546540492;

//32:RightHandThumb1
mChannel[32].mName = "RightHandThumb1";
mChannel[32].mParentChannel = 31;
mChannel[32].mT[0] = -74.9333091199;
mChannel[32].mT[1] = 148.281735867;
mChannel[32].mT[2] = 2.33755167194;
mChannel[32].mR[0] = 0.0547631710026;
mChannel[32].mR[1] = 1.23934426314;
mChannel[32].mR[2] = -179.546518014;

//33:RightHandThumb2
mChannel[33].mName = "RightHandThumb2";
mChannel[33].mParentChannel = 32;
mChannel[33].mT[0] = -79.1507865336;
mChannel[33].mT[1] = 148.248354875;
mChannel[33].mT[2] = 2.24630822912;
mChannel[33].mR[0] = 0.0547631698472;
mChannel[33].mR[1] = 1.23934421822;
mChannel[33].mR[2] = -179.546518067;

//34:RightHandThumb3
mChannel[34].mName = "RightHandThumb3";
mChannel[34].mParentChannel = 33;
mChannel[34].mT[0] = -81.8628612912;
mChannel[34].mT[1] = 148.226900947;
mChannel[34].mT[2] = 2.18763332588;
mChannel[34].mR[0] = 0.0547627433429;
mChannel[34].mR[1] = 1.23934406672;
mChannel[34].mR[2] = -179.546518975;

//35:RightHandIndex1
mChannel[35].mName = "RightHandIndex1";
mChannel[35].mParentChannel = 31;
mChannel[35].mT[0] = -81.0765322052;
mChannel[35].mT[1] = 148.88048876;
mChannel[35].mT[2] = -0.0426734972172;
mChannel[35].mR[0] = 0.0547330213726;
mChannel[35].mR[1] = 1.23932303819;
mChannel[35].mR[2] = -179.546589288;

//36:RightHandIndex2
mChannel[36].mName = "RightHandIndex2";
mChannel[36].mParentChannel = 35;
mChannel[36].mT[0] = -85.5399441132;
mChannel[36].mT[1] = 148.84517869;
mChannel[36].mT[2] = -0.139236383271;
mChannel[36].mR[0] = 0.054732970706;
mChannel[36].mR[1] = 1.23932303265;
mChannel[36].mR[2] = -179.546590088;

//37:RightHandIndex3
mChannel[37].mName = "RightHandIndex3";
mChannel[37].mParentChannel = 36;
mChannel[37].mT[0] = -88.0803708025;
mChannel[37].mT[1] = 148.825074614;
mChannel[37].mT[2] = -0.194196784217;
mChannel[37].mR[0] = 0.0547329192694;
mChannel[37].mR[1] = 1.23932302611;
mChannel[37].mR[2] = -179.546590462;

//38:RightHandMiddle1
mChannel[38].mName = "RightHandMiddle1";
mChannel[38].mParentChannel = 31;
mChannel[38].mT[0] = -80.7214252165;
mChannel[38].mT[1] = 148.959039738;
mChannel[38].mT[2] = -2.189317592;
mChannel[38].mR[0] = 0.0547500179863;
mChannel[38].mR[1] = 1.23933776071;
mChannel[38].mR[2] = -179.546560399;

//39:RightHandMiddle2
mChannel[39].mName = "RightHandMiddle2";
mChannel[39].mParentChannel = 38;
mChannel[39].mT[0] = -85.4937616451;
mChannel[39].mT[1] = 148.921270612;
mChannel[39].mT[2] = -2.29256490459;
mChannel[39].mR[0] = 0.0547500138799;
mChannel[39].mR[1] = 1.2393376934;
mChannel[39].mR[2] = -179.546559972;

//40:RightHandMiddle3
mChannel[40].mName = "RightHandMiddle3";
mChannel[40].mParentChannel = 39;
mChannel[40].mT[0] = -88.3117103421;
mChannel[40].mT[1] = 148.89896884;
mChannel[40].mT[2] = -2.35353039941;
mChannel[40].mR[0] = 0.0547499989985;
mChannel[40].mR[1] = 1.23933762627;
mChannel[40].mR[2] = -179.546559118;

//41:RightHandRing1
mChannel[41].mName = "RightHandRing1";
mChannel[41].mParentChannel = 31;
mChannel[41].mT[0] = -80.4694501676;
mChannel[41].mT[1] = 148.40762978;
mChannel[41].mT[2] = -4.28598609314;
mChannel[41].mR[0] = 0.0547291211029;
mChannel[41].mR[1] = 1.23938396831;
mChannel[41].mR[2] = -179.546542795;

//42:RightHandRing2
mChannel[42].mName = "RightHandRing2";
mChannel[42].mParentChannel = 41;
mChannel[42].mT[0] = -85.1960888879;
mChannel[42].mT[1] = 148.370208941;
mChannel[42].mT[2] = -4.388248164;
mChannel[42].mR[0] = 0.0547291166154;
mChannel[42].mR[1] = 1.23938406362;
mChannel[42].mR[2] = -179.546542848;

//43:RightHandRing3
mChannel[43].mName = "RightHandRing3";
mChannel[43].mParentChannel = 42;
mChannel[43].mT[0] = -87.6920262765;
mChannel[43].mT[1] = 148.350466801;
mChannel[43].mT[2] = -4.44224892522;
mChannel[43].mR[0] = 0.0547291129063;
mChannel[43].mR[1] = 1.23938458588;
mChannel[43].mR[2] = -179.546543328;

//44:RightHandPinky1
mChannel[44].mName = "RightHandPinky1";
mChannel[44].mParentChannel = 31;
mChannel[44].mT[0] = -79.8773559507;
mChannel[44].mT[1] = 147.599879093;
mChannel[44].mT[2] = -6.16993932137;
mChannel[44].mR[0] = 0.054727572701;
mChannel[44].mR[1] = 1.23935195122;
mChannel[44].mR[2] = -179.546537595;

//45:RightHandPinky2
mChannel[45].mName = "RightHandPinky2";
mChannel[45].mParentChannel = 44;
mChannel[45].mT[0] = -82.8529685889;
mChannel[45].mT[1] = 147.576328377;
mChannel[45].mT[2] = -6.23431654958;
mChannel[45].mR[0] = 0.0547275793707;
mChannel[45].mR[1] = 1.23935193327;
mChannel[45].mR[2] = -179.546537595;

//46:RightHandPinky3
mChannel[46].mName = "RightHandPinky3";
mChannel[46].mParentChannel = 45;
mChannel[46].mT[0] = -85.0230825498;
mChannel[46].mT[1] = 147.559152843;
mChannel[46].mT[2] = -6.28126583718;
mChannel[46].mR[0] = 0.0547275760353;
mChannel[46].mR[1] = 1.2393519154;
mChannel[46].mR[2] = -179.546537595;

//47:LeftUpLeg
mChannel[47].mName = "LeftUpLeg";
mChannel[47].mParentChannel = 3;
mChannel[47].mT[0] = 10.3183991328;
mChannel[47].mT[1] = 95.1999869372;
mChannel[47].mT[2] = 0.199989944067;
mChannel[47].mR[0] = 90.0000836453;
mChannel[47].mR[1] = -5.12286662722e-06;
mChannel[47].mR[2] = -90.0000870929;

//48:LeftLeg
mChannel[48].mName = "LeftLeg";
mChannel[48].mParentChannel = 47;
mChannel[48].mT[0] = 10.3183278252;
mChannel[48].mT[1] = 48.2888873841;
mChannel[48].mT[2] = 0.199994115147;
mChannel[48].mR[0] = 90.0000836453;
mChannel[48].mR[1] = -5.12286744144e-06;
mChannel[48].mR[2] = -90.0000870929;

//49:LeftFoot
mChannel[49].mName = "LeftFoot";
mChannel[49].mParentChannel = 48;
mChannel[49].mT[0] = 10.3182688342;
mChannel[49].mT[1] = 9.48048429789;
mChannel[49].mT[2] = 0.199997585041;
mChannel[49].mR[0] = 90.0000842146;
mChannel[49].mR[1] = -7.741032418e-06;
mChannel[49].mR[2] = -90.000084729;

//50:LeftToeBase
mChannel[50].mName = "LeftToeBase";
mChannel[50].mParentChannel = 49;
mChannel[50].mT[0] = 10.318235129;
mChannel[50].mT[1] = 0.724486179183;
mChannel[50].mT[2] = 14.3219974213;
mChannel[50].mR[0] = -177.204297237;
mChannel[50].mR[1] = -89.9999156841;
mChannel[50].mR[2] = 177.20421305;

//51:RightUpLeg
mChannel[51].mName = "RightUpLeg";
mChannel[51].mParentChannel = 3;
mChannel[51].mT[0] = -10.318400799;
mChannel[51].mT[1] = 95.200017447;
mChannel[51].mT[2] = 0.200018245245;
mChannel[51].mR[0] = 90.0000836453;
mChannel[51].mR[1] = -4.69598048871e-06;
mChannel[51].mR[2] = -90.0000871873;

//52:RightLeg
mChannel[52].mName = "RightLeg";
mChannel[52].mParentChannel = 51;
mChannel[52].mT[0] = -10.3184721839;
mChannel[52].mT[1] = 48.2889178938;
mChannel[52].mT[2] = 0.200022090094;
mChannel[52].mR[0] = 90.0000836453;
mChannel[52].mR[1] = -4.69598130293e-06;
mChannel[52].mR[2] = -90.0000871873;

//53:RightFoot
mChannel[53].mName = "RightFoot";
mChannel[53].mParentChannel = 52;
mChannel[53].mT[0] = -10.3185319839;
mChannel[53].mT[1] = 9.48051182739;
mChannel[53].mT[2] = 0.200025270843;
mChannel[53].mR[0] = 90.0000830384;
mChannel[53].mR[1] = 2.5042522255e-06;
mChannel[53].mR[2] = -90.0000846937;

//54:RightToeBase
mChannel[54].mName = "RightToeBase";
mChannel[54].mParentChannel = 53;
mChannel[54].mT[0] = -10.3185653938;
mChannel[54].mT[1] = 0.724510884732;
mChannel[54].mT[2] = 14.3220252249;
mChannel[54].mR[0] = 174.752268401;
mChannel[54].mR[1] = -89.9999166115;
mChannel[54].mR[2] = -174.752353224;}

static void HandHierarchySetup(FBTVector* mLocalTranslationR, FBTVector* mLocalTranslationL) {
//0:RightHand
mLocalTranslationR[0].mValue[0] = -71.8947905939;
mLocalTranslationR[0].mValue[1] = 148.535135799;
mLocalTranslationR[0].mValue[2] = -1.90475499189;

//1:RightHandThumb1
mLocalTranslationR[1].mValue[0] = 0.0294796228409;
mLocalTranslationR[1].mValue[1] = 0.00233459472656;
mLocalTranslationR[1].mValue[2] = 0.0430685430765;

//2:RightHandThumb2
mLocalTranslationR[2].mValue[0] = 0.0421860218048;
mLocalTranslationR[2].mValue[1] = 0.0;
mLocalTranslationR[2].mValue[2] = 3.72529029846e-09;

//3:RightHandThumb3
mLocalTranslationR[3].mValue[0] = 0.0271279811859;
mLocalTranslationR[3].mValue[1] = -1.19209289551e-07;
mLocalTranslationR[3].mValue[2] = 0.0;

//4:RightHandIndex1
mLocalTranslationR[4].mValue[0] = 0.0913630127907;
mLocalTranslationR[4].mValue[1] = -0.00416040420532;
mLocalTranslationR[4].mValue[2] = 0.0206056926399;

//5:RightHandIndex2
mLocalTranslationR[5].mValue[0] = 0.0446459650993;
mLocalTranslationR[5].mValue[1] = -1.19209289551e-07;
mLocalTranslationR[5].mValue[2] = 0.0;

//6:RightHandIndex3
mLocalTranslationR[6].mValue[0] = 0.0254110097885;
mLocalTranslationR[6].mValue[1] = 0.0;
mLocalTranslationR[6].mValue[2] = 0.0;

//7:RightHandMiddle1
mLocalTranslationR[7].mValue[0] = 0.0882709622383;
mLocalTranslationR[7].mValue[1] = -0.00493836402893;
mLocalTranslationR[7].mValue[2] = -0.000931932125241;

//8:RightHandMiddle2
mLocalTranslationR[8].mValue[0] = 0.0477360486984;
mLocalTranslationR[8].mValue[1] = 0.0;
mLocalTranslationR[8].mValue[2] = 1.62981450558e-09;

//9:RightHandMiddle3
mLocalTranslationR[9].mValue[0] = 0.0281869769096;
mLocalTranslationR[9].mValue[1] = 0.0;
mLocalTranslationR[9].mValue[2] = -3.72529029846e-09;

//10:RightHandRing1
mLocalTranslationR[10].mValue[0] = 0.0862489938736;
mLocalTranslationR[10].mValue[1] = 0.000575423240662;
mLocalTranslationR[10].mValue[2] = -0.0219525452703;

//11:RightHandRing2
mLocalTranslationR[11].mValue[0] = 0.0472789406776;
mLocalTranslationR[11].mValue[1] = 1.19209289551e-07;
mLocalTranslationR[11].mValue[2] = 5.58793544769e-09;

//12:RightHandRing3
mLocalTranslationR[12].mValue[0] = 0.0249660015106;
mLocalTranslationR[12].mValue[1] = -1.19209289551e-07;
mLocalTranslationR[12].mValue[2] = -1.86264514923e-09;

//13:RightHandPinky1
mLocalTranslationR[13].mValue[0] = 0.0808010101318;
mLocalTranslationR[13].mValue[1] = 0.00868141651154;
mLocalTranslationR[13].mValue[2] = -0.0409221015871;

//14:RightHandPinky2
mLocalTranslationR[14].mValue[0] = 0.0297639966011;
mLocalTranslationR[14].mValue[1] = 0.0;
mLocalTranslationR[14].mValue[2] = -3.72529029846e-09;

//15:RightHandPinky3
mLocalTranslationR[15].mValue[0] = 0.0217068791389;
mLocalTranslationR[15].mValue[1] = 0.0;
mLocalTranslationR[15].mValue[2] = 7.45058059692e-09;

//0:LeftHand
mLocalTranslationL[0].mValue[0] = 71.9114474719;
mLocalTranslationL[0].mValue[1] = 149.201540307;
mLocalTranslationL[0].mValue[2] = -0.90197722882;

//1:LeftHandThumb1
mLocalTranslationL[1].mValue[0] = 0.0294796228409;
mLocalTranslationL[1].mValue[1] = 0.00233471393585;
mLocalTranslationL[1].mValue[2] = -0.0430685542524;

//2:LeftHandThumb2
mLocalTranslationL[2].mValue[0] = 0.0421859622002;
mLocalTranslationL[2].mValue[1] = 0.0;
mLocalTranslationL[2].mValue[2] = 0.0;

//3:LeftHandThumb3
mLocalTranslationL[3].mValue[0] = 0.0271280407906;
mLocalTranslationL[3].mValue[1] = -1.19209289551e-07;
mLocalTranslationL[3].mValue[2] = -3.72529029846e-09;

//4:LeftHandIndex1
mLocalTranslationL[4].mValue[0] = 0.0913630723953;
mLocalTranslationL[4].mValue[1] = -0.00416040420532;
mLocalTranslationL[4].mValue[2] = -0.0206056982279;

//5:LeftHandIndex2
mLocalTranslationL[5].mValue[0] = 0.0446459054947;
mLocalTranslationL[5].mValue[1] = -1.19209289551e-07;
mLocalTranslationL[5].mValue[2] = 1.86264514923e-09;

//6:LeftHandIndex3
mLocalTranslationL[6].mValue[0] = 0.0254110693932;
mLocalTranslationL[6].mValue[1] = 1.19209289551e-07;
mLocalTranslationL[6].mValue[2] = 0.0;

//7:LeftHandMiddle1
mLocalTranslationL[7].mValue[0] = 0.088271021843;
mLocalTranslationL[7].mValue[1] = -0.00493824481964;
mLocalTranslationL[7].mValue[2] = 0.000931933522224;

//8:LeftHandMiddle2
mLocalTranslationL[8].mValue[0] = 0.0477359890938;
mLocalTranslationL[8].mValue[1] = 0.0;
mLocalTranslationL[8].mValue[2] = 0.0;

//9:LeftHandMiddle3
mLocalTranslationL[9].mValue[0] = 0.0281870365143;
mLocalTranslationL[9].mValue[1] = 0.0;
mLocalTranslationL[9].mValue[2] = 4.65661287308e-10;

//10:LeftHandRing1
mLocalTranslationL[10].mValue[0] = 0.0862489938736;
mLocalTranslationL[10].mValue[1] = 0.000575542449951;
mLocalTranslationL[10].mValue[2] = 0.021952547133;

//11:LeftHandRing2
mLocalTranslationL[11].mValue[0] = 0.0472790002823;
mLocalTranslationL[11].mValue[1] = 0.0;
mLocalTranslationL[11].mValue[2] = -1.86264514923e-09;

//12:LeftHandRing3
mLocalTranslationL[12].mValue[0] = 0.0249660015106;
mLocalTranslationL[12].mValue[1] = 0.0;
mLocalTranslationL[12].mValue[2] = 0.0;

//13:LeftHandPinky1
mLocalTranslationL[13].mValue[0] = 0.0808009505272;
mLocalTranslationL[13].mValue[1] = 0.00868165493011;
mLocalTranslationL[13].mValue[2] = 0.0409221053123;

//14:LeftHandPinky2
mLocalTranslationL[14].mValue[0] = 0.0297639369965;
mLocalTranslationL[14].mValue[1] = 1.19209289551e-07;
mLocalTranslationL[14].mValue[2] = 0.0;

//15:LeftHandPinky3
mLocalTranslationL[15].mValue[0] = 0.0217069983482;
mLocalTranslationL[15].mValue[1] = -1.19209289551e-07;
mLocalTranslationL[15].mValue[2] = 0.0;
}
