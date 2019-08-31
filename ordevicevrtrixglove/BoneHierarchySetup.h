#pragma once
#include <fbsdk/fbsdk.h>
#define RHandIndex 104
#define LHandIndex 84
#define BoneNum	129 
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

//7:HeadEnd
mChannel[7].mName = "HeadEnd";
mChannel[7].mParentChannel = 6;
mChannel[7].mT[0] = 3.95680720922e-14;
mChannel[7].mT[1] = 177.233939744;
mChannel[7].mT[2] = 2.46706027941;
mChannel[7].mR[0] = 5.70550942732e-15;
mChannel[7].mR[1] = 3.24611467502e-14;
mChannel[7].mR[2] = -1.27222187259e-14;

//8:joint65
mChannel[8].mName = "joint65";
mChannel[8].mParentChannel = 7;
mChannel[8].mT[0] = -5.90112876892;
mChannel[8].mT[1] = 177.695097036;
mChannel[8].mT[2] = 3.82001311736;
mChannel[8].mR[0] = 179.812445599;
mChannel[8].mR[1] = 1.07316828201;
mChannel[8].mR[2] = 170.086105378;

//9:joint66
mChannel[9].mName = "joint66";
mChannel[9].mParentChannel = 8;
mChannel[9].mT[0] = -7.13316154869;
mChannel[9].mT[1] = 177.910429068;
mChannel[9].mT[2] = 3.79658420035;
mChannel[9].mR[0] = 178.048100522;
mChannel[9].mR[1] = 4.92399420463;
mChannel[9].mR[2] = 158.344561091;

//10:joint67
mChannel[10].mName = "joint67";
mChannel[10].mParentChannel = 9;
mChannel[10].mT[0] = -8.49395127012;
mChannel[10].mT[1] = 178.450727508;
mChannel[10].mT[2] = 3.67044647194;
mChannel[10].mR[0] = 174.986739627;
mChannel[10].mR[1] = 7.44342150706;
mChannel[10].mR[2] = 145.896391589;

//11:joint61
mChannel[11].mName = "joint61";
mChannel[11].mParentChannel = 7;
mChannel[11].mT[0] = -4.4979391098;
mChannel[11].mT[1] = 178.977323628;
mChannel[11].mT[2] = 3.84511930899;
mChannel[11].mR[0] = -170.915777678;
mChannel[11].mR[1] = -19.4923217945;
mChannel[11].mR[2] = 154.397388591;

//12:joint62
mChannel[12].mName = "joint62";
mChannel[12].mParentChannel = 11;
mChannel[12].mT[0] = -5.08876943871;
mChannel[12].mT[1] = 179.260435202;
mChannel[12].mT[2] = 4.07702429362;
mChannel[12].mR[0] = -177.925584751;
mChannel[12].mR[1] = -8.07930850176;
mChannel[12].mR[2] = 165.548105637;

//13:joint63
mChannel[13].mName = "joint63";
mChannel[13].mParentChannel = 12;
mChannel[13].mT[0] = -5.71357443874;
mChannel[13].mT[1] = 179.42146121;
mChannel[13].mT[2] = 4.16861517884;
mChannel[13].mR[0] = 178.148680936;
mChannel[13].mR[1] = 3.93355277333;
mChannel[13].mR[2] = 154.771030926;

//14:joint57
mChannel[14].mName = "joint57";
mChannel[14].mParentChannel = 7;
mChannel[14].mT[0] = -1.73635721207;
mChannel[14].mT[1] = 179.698438741;
mChannel[14].mT[2] = 3.07057918267;
mChannel[14].mR[0] = -170.958823011;
mChannel[14].mR[1] = -18.4345999933;
mChannel[14].mR[2] = 153.288702164;

//15:joint58
mChannel[15].mName = "joint58";
mChannel[15].mParentChannel = 14;
mChannel[15].mT[0] = -3.17913463086;
mChannel[15].mT[1] = 180.424436678;
mChannel[15].mT[2] = 3.60894851126;
mChannel[15].mR[0] = -156.930290924;
mChannel[15].mR[1] = -21.5863784066;
mChannel[15].mR[2] = 130.820546493;

//16:joint59
mChannel[16].mName = "joint59";
mChannel[16].mParentChannel = 15;
mChannel[16].mT[0] = -3.7706265759;
mChannel[16].mT[1] = 181.109190102;
mChannel[16].mT[2] = 3.96695437468;
mChannel[16].mR[0] = -150.711107136;
mChannel[16].mR[1] = -17.3242584435;
mChannel[16].mR[2] = 117.962813488;

//17:joint54
mChannel[17].mName = "joint54";
mChannel[17].mParentChannel = 7;
mChannel[17].mT[0] = 1.36760854721;
mChannel[17].mT[1] = 179.872800923;
mChannel[17].mT[2] = 2.65408718245;
mChannel[17].mR[0] = -179.369088824;
mChannel[17].mR[1] = -1.34023626249;
mChannel[17].mR[2] = 154.788559281;

//18:joint55
mChannel[18].mName = "joint55";
mChannel[18].mParentChannel = 17;
mChannel[18].mT[0] = -0.51123498518;
mChannel[18].mT[1] = 180.75737586;
mChannel[18].mT[2] = 2.70267236145;
mChannel[18].mR[0] = -178.421223663;
mChannel[18].mR[1] = -0.940850708396;
mChannel[18].mR[2] = 120.784754538;

//19:joint51
mChannel[19].mName = "joint51";
mChannel[19].mParentChannel = 7;
mChannel[19].mT[0] = 4.29580926895;
mChannel[19].mT[1] = 179.373884297;
mChannel[19].mT[2] = 2.62460696356;
mChannel[19].mR[0] = -168.820600475;
mChannel[19].mR[1] = -5.33735407298;
mChannel[19].mR[2] = 115.205056773;

//20:joint52
mChannel[20].mName = "joint52";
mChannel[20].mParentChannel = 19;
mChannel[20].mT[0] = 3.64775894374;
mChannel[20].mT[1] = 180.750745905;
mChannel[20].mT[2] = 2.766775966;
mChannel[20].mR[0] = -179.277656633;
mChannel[20].mR[1] = -0.74975039515;
mChannel[20].mR[2] = 136.064259668;

//21:joint48
mChannel[21].mName = "joint48";
mChannel[21].mParentChannel = 7;
mChannel[21].mT[0] = 5.92639923096;
mChannel[21].mT[1] = 178.316396809;
mChannel[21].mT[2] = 2.19104443149;
mChannel[21].mR[0] = 0.668349550652;
mChannel[21].mR[1] = 15.687107134;
mChannel[21].mR[2] = 2.47043496335;

//22:joint49
mChannel[22].mName = "joint49";
mChannel[22].mParentChannel = 21;
mChannel[22].mT[0] = 6.8880319764;
mChannel[22].mT[1] = 178.357885458;
mChannel[22].mT[2] = 1.92072389204;
mChannel[22].mR[0] = -13.6451253816;
mChannel[22].mR[1] = 26.7839283444;
mChannel[22].mR[2] = -28.3119828459;

//23:joint43
mChannel[23].mName = "joint43";
mChannel[23].mParentChannel = 7;
mChannel[23].mT[0] = 8.90043735504;
mChannel[23].mT[1] = 173.985342122;
mChannel[23].mT[2] = 1.52799649195;
mChannel[23].mR[0] = 8.30729713369;
mChannel[23].mR[1] = -7.142508365;
mChannel[23].mR[2] = -49.5841288318;

//24:joint44
mChannel[24].mName = "joint44";
mChannel[24].mParentChannel = 23;
mChannel[24].mT[0] = 9.55049755584;
mChannel[24].mT[1] = 173.221952506;
mChannel[24].mT[2] = 1.65364082279;
mChannel[24].mR[0] = 9.04848396186;
mChannel[24].mR[1] = -6.59510303227;
mChannel[24].mR[2] = -54.200925092;

//25:joint45
mChannel[25].mName = "joint45";
mChannel[25].mParentChannel = 24;
mChannel[25].mT[0] = 9.96796847962;
mChannel[25].mT[1] = 172.643095096;
mChannel[25].mT[2] = 1.73615612049;
mChannel[25].mR[0] = 10.2554756105;
mChannel[25].mR[1] = -11.3144681193;
mChannel[25].mR[2] = -42.6819760281;

//26:joint46
mChannel[26].mName = "joint46";
mChannel[26].mParentChannel = 25;
mChannel[26].mT[0] = 10.4011240268;
mChannel[26].mT[1] = 172.243642877;
mChannel[26].mT[2] = 1.85404958076;
mChannel[26].mR[0] = 5.43809709;
mChannel[26].mR[1] = -13.8437121601;
mChannel[26].mR[2] = -21.6958512351;

//27:joint39
mChannel[27].mName = "joint39";
mChannel[27].mParentChannel = 7;
mChannel[27].mT[0] = 8.97385215759;
mChannel[27].mT[1] = 171.667471028;
mChannel[27].mT[2] = 0.89155180411;
mChannel[27].mR[0] = -0.491869044922;
mChannel[27].mR[1] = 9.4469342104;
mChannel[27].mR[2] = -74.424996521;

//28:joint40
mChannel[28].mName = "joint40";
mChannel[28].mParentChannel = 27;
mChannel[28].mT[0] = 9.27957533518;
mChannel[28].mT[1] = 170.570646428;
mChannel[28].mT[2] = 0.702093501388;
mChannel[28].mR[0] = 7.40223377911;
mChannel[28].mR[1] = -12.1522667738;
mChannel[28].mR[2] = -67.8990576821;

//29:joint41
mChannel[29].mName = "joint41";
mChannel[29].mParentChannel = 28;
mChannel[29].mT[0] = 9.84832859197;
mChannel[29].mT[1] = 169.170042144;
mChannel[29].mT[2] = 1.02761199845;
mChannel[29].mR[0] = 3.05368537609;
mChannel[29].mR[1] = -28.0017861241;
mChannel[29].mR[2] = -42.1909770198;

//30:joint21
mChannel[30].mName = "joint21";
mChannel[30].mParentChannel = 7;
mChannel[30].mT[0] = 1.4716501236;
mChannel[30].mT[1] = 173.086416341;
mChannel[30].mT[2] = 12.7589008327;
mChannel[30].mR[0] = 71.4311222011;
mChannel[30].mR[1] = -30.1490048927;
mChannel[30].mR[2] = -113.906679588;

//31:joint22
mChannel[31].mName = "joint22";
mChannel[31].mParentChannel = 30;
mChannel[31].mT[0] = 1.22398003338;
mChannel[31].mT[1] = 172.527692877;
mChannel[31].mT[2] = 13.1138746343;
mChannel[31].mR[0] = 64.0652195162;
mChannel[31].mR[1] = -5.19117046482;
mChannel[31].mR[2] = -107.5833638;

//32:joint23
mChannel[32].mName = "joint23";
mChannel[32].mParentChannel = 31;
mChannel[32].mT[0] = 0.824949968565;
mChannel[32].mT[1] = 171.268522329;
mChannel[32].mT[2] = 13.2338792898;
mChannel[32].mR[0] = 66.7936348045;
mChannel[32].mR[1] = 7.8477240831;
mChannel[32].mR[2] = -95.1070378813;

//33:joint24
mChannel[33].mName = "joint24";
mChannel[33].mParentChannel = 32;
mChannel[33].mT[0] = 0.718820024317;
mChannel[33].mT[1] = 170.081007071;
mChannel[33].mT[2] = 13.0695497611;
mChannel[33].mR[0] = 62.9280202622;
mChannel[33].mR[1] = 4.69644426689;
mChannel[33].mR[2] = -80.8988768467;

//34:joint35
mChannel[34].mName = "joint35";
mChannel[34].mParentChannel = 7;
mChannel[34].mT[0] = 5.21272516251;
mChannel[34].mT[1] = 172.347219563;
mChannel[34].mT[2] = 10.3050043102;
mChannel[34].mR[0] = 52.1212944317;
mChannel[34].mR[1] = 18.9383273846;
mChannel[34].mR[2] = -82.4845570463;

//35:joint36
mChannel[35].mName = "joint36";
mChannel[35].mParentChannel = 34;
mChannel[35].mT[0] = 5.41175460971;
mChannel[35].mT[1] = 170.838583077;
mChannel[35].mT[2] = 9.78286952521;
mChannel[35].mR[0] = 58.7818137537;
mChannel[35].mR[1] = 5.19800938848;
mChannel[35].mR[2] = -94.5376738054;

//36:joint37
mChannel[36].mName = "joint37";
mChannel[36].mParentChannel = 35;
mChannel[36].mT[0] = 5.3069350737;
mChannel[36].mT[1] = 169.517828074;
mChannel[36].mT[2] = 9.6623398738;
mChannel[36].mR[0] = 63.2723517565;
mChannel[36].mR[1] = -13.9757677382;
mChannel[36].mR[2] = -115.623096679;

//37:joint1
mChannel[37].mName = "joint1";
mChannel[37].mParentChannel = 7;
mChannel[37].mT[0] = 4.35654973984;
mChannel[37].mT[1] = 171.938642598;
mChannel[37].mT[2] = 10.8123600002;
mChannel[37].mR[0] = 54.0572025369;
mChannel[37].mR[1] = 1.58832545388;
mChannel[37].mR[2] = -90.4536617684;

//38:joint2
mChannel[38].mName = "joint2";
mChannel[38].mParentChannel = 37;
mChannel[38].mT[0] = 4.35139012331;
mChannel[38].mT[1] = 171.287016004;
mChannel[38].mT[2] = 10.7942907327;
mChannel[38].mR[0] = 59.4447597916;
mChannel[38].mR[1] = 4.10170151726;
mChannel[38].mR[2] = -90.0397159396;

//39:joint3
mChannel[39].mName = "joint3";
mChannel[39].mParentChannel = 38;
mChannel[39].mT[0] = 4.35083508487;
mChannel[39].mT[1] = 170.486295806;
mChannel[39].mT[2] = 10.7368704801;
mChannel[39].mR[0] = 60.9412833842;
mChannel[39].mR[1] = 1.4518377595;
mChannel[39].mR[2] = -97.4667771842;

//40:joint4
mChannel[40].mName = "joint4";
mChannel[40].mParentChannel = 39;
mChannel[40].mT[0] = 4.26974486964;
mChannel[40].mT[1] = 169.867582401;
mChannel[40].mT[2] = 10.7210552215;
mChannel[40].mR[0] = 53.1882434958;
mChannel[40].mR[1] = -5.94845566041;
mChannel[40].mR[2] = -108.931819792;

//41:joint5
mChannel[41].mName = "joint5";
mChannel[41].mParentChannel = 40;
mChannel[41].mT[0] = 3.97729503864;
mChannel[41].mT[1] = 169.014951789;
mChannel[41].mT[2] = 10.814975452;
mChannel[41].mR[0] = 46.3613721117;
mChannel[41].mR[1] = -18.8022765888;
mChannel[41].mR[2] = -126.366798359;

//42:joint11
mChannel[42].mName = "joint11";
mChannel[42].mParentChannel = 7;
mChannel[42].mT[0] = 0.162680029869;
mChannel[42].mT[1] = 172.804594136;
mChannel[42].mT[2] = 12.735790443;
mChannel[42].mR[0] = 74.9216149553;
mChannel[42].mR[1] = -16.8385652944;
mChannel[42].mR[2] = -106.113190305;

//43:joint12
mChannel[43].mName = "joint12";
mChannel[43].mParentChannel = 42;
mChannel[43].mT[0] = -0.164345006742;
mChannel[43].mT[1] = 171.672567505;
mChannel[43].mT[2] = 13.0924107418;
mChannel[43].mR[0] = 69.1990338141;
mChannel[43].mR[1] = 1.74302382564;
mChannel[43].mR[2] = -100.637318636;

//44:joint13
mChannel[44].mName = "joint13";
mChannel[44].mParentChannel = 43;
mChannel[44].mT[0] = -0.440650014705;
mChannel[44].mT[1] = 170.201444767;
mChannel[44].mT[2] = 13.0468603956;
mChannel[44].mR[0] = 75.1487053669;
mChannel[44].mR[1] = 9.06132433654;
mChannel[44].mR[2] = -81.0040967891;

//45:joint14
mChannel[45].mName = "joint14";
mChannel[45].mParentChannel = 44;
mChannel[45].mT[0] = -0.202454981768;
mChannel[45].mT[1] = 168.696844235;
mChannel[45].mT[2] = 12.8039156771;
mChannel[45].mR[0] = 75.2374039588;
mChannel[45].mR[1] = 13.4130555609;
mChannel[45].mR[2] = -63.3026317113;

//46:joint16
mChannel[46].mName = "joint16";
mChannel[46].mParentChannel = 7;
mChannel[46].mT[0] = -1.57071256638;
mChannel[46].mT[1] = 172.449870682;
mChannel[46].mT[2] = 12.575555038;
mChannel[46].mR[0] = 103.251518816;
mChannel[46].mR[1] = -10.8310097316;
mChannel[46].mR[2] = -121.981738308;

//47:joint17
mChannel[47].mName = "joint17";
mChannel[47].mParentChannel = 46;
mChannel[47].mT[0] = -2.12323993155;
mChannel[47].mT[1] = 171.213918682;
mChannel[47].mT[2] = 12.7751404228;
mChannel[47].mR[0] = 102.223235408;
mChannel[47].mR[1] = 4.2034743558;
mChannel[47].mR[2] = -100.170944201;

//48:joint18
mChannel[48].mName = "joint18";
mChannel[48].mParentChannel = 47;
mChannel[48].mT[0] = -2.36935501077;
mChannel[48].mT[1] = 169.842077303;
mChannel[48].mT[2] = 12.6727053146;
mChannel[48].mR[0] = 94.9443045192;
mChannel[48].mR[1] = 2.62823358829;
mChannel[48].mR[2] = -88.7781574125;

//49:joint19
mChannel[49].mName = "joint19";
mChannel[49].mParentChannel = 48;
mChannel[49].mT[0] = -2.34051482597;
mChannel[49].mT[1] = 168.489881536;
mChannel[49].mT[2] = 12.6106206385;
mChannel[49].mR[0] = 90.8314092758;
mChannel[49].mR[1] = 11.654428125;
mChannel[49].mR[2] = -70.103940063;

//50:joint30
mChannel[50].mName = "joint30";
mChannel[50].mParentChannel = 7;
mChannel[50].mT[0] = -2.6574151516;
mChannel[50].mT[1] = 173.050576783;
mChannel[50].mT[2] = 11.4848501201;
mChannel[50].mR[0] = 121.971072184;
mChannel[50].mR[1] = -6.19676106975;
mChannel[50].mR[2] = -108.347845886;

//51:joint31
mChannel[51].mName = "joint31";
mChannel[51].mParentChannel = 50;
mChannel[51].mT[0] = -3.11935650624;
mChannel[51].mT[1] = 171.657697954;
mChannel[51].mT[2] = 11.6441856658;
mChannel[51].mR[0] = 125.844471119;
mChannel[51].mR[1] = -9.08191044663;
mChannel[51].mR[2] = -103.09699589;

//52:joint32
mChannel[52].mName = "joint32";
mChannel[52].mParentChannel = 51;
mChannel[52].mT[0] = -3.48652999743;
mChannel[52].mT[1] = 170.079489038;
mChannel[52].mT[2] = 11.903200271;
mChannel[52].mR[0] = 115.496609399;
mChannel[52].mR[1] = -7.57381307293;
mChannel[52].mR[2] = -84.8232830663;

//53:joint33
mChannel[53].mName = "joint33";
mChannel[53].mParentChannel = 52;
mChannel[53].mT[0] = -3.35021501007;
mChannel[53].mT[1] = 168.574865633;
mChannel[53].mT[2] = 12.1040793669;
mChannel[53].mR[0] = 112.201198893;
mChannel[53].mR[1] = 7.90903308076;
mChannel[53].mR[2] = -66.7996959876;

//54:joint26
mChannel[54].mName = "joint26";
mChannel[54].mParentChannel = 7;
mChannel[54].mT[0] = -5.60287189484;
mChannel[54].mT[1] = 170.258329488;
mChannel[54].mT[2] = 10.5090009685;
mChannel[54].mR[0] = 108.216983644;
mChannel[54].mR[1] = 6.6467571658;
mChannel[54].mR[2] = -87.8184321126;

//55:joint27
mChannel[55].mName = "joint27";
mChannel[55].mParentChannel = 54;
mChannel[55].mT[0] = -5.56066489322;
mChannel[55].mT[1] = 169.150358323;
mChannel[55].mT[2] = 10.3797943142;
mChannel[55].mR[0] = 104.863551683;
mChannel[55].mR[1] = 7.10369919429;
mChannel[55].mR[2] = -80.0337016459;

//56:joint28
mChannel[56].mName = "joint28";
mChannel[56].mParentChannel = 55;
mChannel[56].mT[0] = -5.39872479418;
mChannel[56].mT[1] = 168.228780862;
mChannel[56].mT[2] = 10.2631856937;
mChannel[56].mR[0] = 122.061185815;
mChannel[56].mR[1] = 13.4003722468;
mChannel[56].mR[2] = -66.3950833673;

//57:joint76
mChannel[57].mName = "joint76";
mChannel[57].mParentChannel = 7;
mChannel[57].mT[0] = -8.46059513092;
mChannel[57].mT[1] = 172.890050984;
mChannel[57].mT[2] = 5.38523502307;
mChannel[57].mR[0] = 159.864338898;
mChannel[57].mR[1] = -8.41632807017;
mChannel[57].mR[2] = -111.761437802;

//58:joint77
mChannel[58].mName = "joint77";
mChannel[58].mParentChannel = 57;
mChannel[58].mT[0] = -8.92903662448;
mChannel[58].mT[1] = 171.716573793;
mChannel[58].mT[2] = 5.57218356376;
mChannel[58].mR[0] = 156.700995442;
mChannel[58].mR[1] = -8.38327287088;
mChannel[58].mR[2] = -108.703353391;

//59:joint78
mChannel[59].mName = "joint78";
mChannel[59].mParentChannel = 58;
mChannel[59].mT[0] = -9.37987757574;
mChannel[59].mT[1] = 170.384878233;
mChannel[59].mT[2] = 5.77937550846;
mChannel[59].mR[0] = 151.803525392;
mChannel[59].mR[1] = -10.1925448935;
mChannel[59].mR[2] = -96.2621752657;

//60:joint72
mChannel[60].mName = "joint72";
mChannel[60].mParentChannel = 7;
mChannel[60].mT[0] = -8.0809135437;
mChannel[60].mT[1] = 174.903768636;
mChannel[60].mT[2] = 4.17393178897;
mChannel[60].mR[0] = 173.724580071;
mChannel[60].mR[1] = -6.31895066809;
mChannel[60].mR[2] = -135.025061646;

//61:joint73
mChannel[61].mName = "joint73";
mChannel[61].mParentChannel = 60;
mChannel[61].mT[0] = -8.91878149283;
mChannel[61].mT[1] = 174.066633347;
mChannel[61].mT[2] = 4.30508799101;
mChannel[61].mR[0] = 160.878893033;
mChannel[61].mR[1] = -12.0850937105;
mChannel[61].mR[2] = -121.127277928;

//62:joint74
mChannel[62].mName = "joint74";
mChannel[62].mParentChannel = 61;
mChannel[62].mT[0] = -9.65613383521;
mChannel[62].mT[1] = 172.845625094;
mChannel[62].mT[2] = 4.61048846983;
mChannel[62].mR[0] = 152.039590571;
mChannel[62].mR[1] = -13.4803400156;
mChannel[62].mR[2] = -113.708733416;

//63:joint69
mChannel[63].mName = "joint69";
mChannel[63].mParentChannel = 7;
mChannel[63].mT[0] = -7.8472032547;
mChannel[63].mT[1] = 176.270750142;
mChannel[63].mT[2] = 4.01487393336;
mChannel[63].mR[0] = 170.702458534;
mChannel[63].mR[1] = -14.4178857651;
mChannel[63].mR[2] = -146.675108059;

//64:joint70
mChannel[64].mName = "joint70";
mChannel[64].mParentChannel = 63;
mChannel[64].mT[0] = -8.73852630736;
mChannel[64].mT[1] = 175.684705855;
mChannel[64].mT[2] = 4.28911763442;
mChannel[64].mR[0] = 178.106311098;
mChannel[64].mR[1] = -16.0209855171;
mChannel[64].mR[2] = -173.168602258;

//65:joint80
mChannel[65].mName = "joint80";
mChannel[65].mParentChannel = 7;
mChannel[65].mT[0] = 4.24130916595;
mChannel[65].mT[1] = 177.793043233;
mChannel[65].mT[2] = 6.61267967181;
mChannel[65].mR[0] = 32.3256994488;
mChannel[65].mR[1] = -49.8233709369;
mChannel[65].mR[2] = -39.6319040354;

//66:joint81
mChannel[66].mName = "joint81";
mChannel[66].mParentChannel = 65;
mChannel[66].mT[0] = 4.79775426958;
mChannel[66].mT[1] = 177.332189671;
mChannel[66].mT[2] = 7.46835963278;
mChannel[66].mR[0] = 29.5261382763;
mChannel[66].mR[1] = -47.1978286443;
mChannel[66].mR[2] = -37.6659672858;

//67:joint82
mChannel[67].mName = "joint82";
mChannel[67].mParentChannel = 66;
mChannel[67].mT[0] = 5.40175911089;
mChannel[67].mT[1] = 176.865934497;
mChannel[67].mT[2] = 8.29229511611;
mChannel[67].mR[0] = 9.14171394377;
mChannel[67].mR[1] = -46.4470647629;
mChannel[67].mR[2] = -12.5188591105;

//68:joint84
mChannel[68].mName = "joint84";
mChannel[68].mParentChannel = 7;
mChannel[68].mT[0] = 0.39226770401;
mChannel[68].mT[1] = 179.303976155;
mChannel[68].mT[2] = 6.32578511195;
mChannel[68].mR[0] = 179.133137313;
mChannel[68].mR[1] = -76.016469267;
mChannel[68].mR[2] = -179.106667713;

//69:joint85
mChannel[69].mName = "joint85";
mChannel[69].mParentChannel = 68;
mChannel[69].mT[0] = 0.185298925391;
mChannel[69].mT[1] = 179.300748921;
mChannel[69].mT[2] = 7.15701024579;
mChannel[69].mR[0] = 153.921360738;
mChannel[69].mR[1] = -81.0862086426;
mChannel[69].mR[2] = -153.6454453;

//70:joint86
mChannel[70].mName = "joint86";
mChannel[70].mParentChannel = 69;
mChannel[70].mT[0] = 0.0771141072083;
mChannel[70].mT[1] = 179.247152423;
mChannel[70].mT[2] = 7.92678494769;
mChannel[70].mR[0] = 109.956310144;
mChannel[70].mR[1] = -84.1126104822;
mChannel[70].mR[2] = -109.859298422;

//71:joint87
mChannel[71].mName = "joint87";
mChannel[71].mParentChannel = 70;
mChannel[71].mT[0] = 0.0538396861163;
mChannel[71].mT[1] = 179.182714558;
mChannel[71].mT[2] = 8.59119504486;
mChannel[71].mR[0] = 128.832361587;
mChannel[71].mR[1] = -62.4361632393;
mChannel[71].mR[2] = -125.511111188;

//72:joint89
mChannel[72].mName = "joint89";
mChannel[72].mParentChannel = 7;
mChannel[72].mT[0] = 0.778329372406;
mChannel[72].mT[1] = 177.703931875;
mChannel[72].mT[2] = 9.45770950274;
mChannel[72].mR[0] = 130.812978422;
mChannel[72].mR[1] = -67.2940304985;
mChannel[72].mR[2] = -128.542353002;

//73:joint90
mChannel[73].mName = "joint90";
mChannel[73].mParentChannel = 72;
mChannel[73].mT[0] = 0.501389506046;
mChannel[73].mT[1] = 177.356298516;
mChannel[73].mT[2] = 10.5199143307;
mChannel[73].mR[0] = 111.010164052;
mChannel[73].mR[1] = -62.6524431412;
mChannel[73].mR[2] = -108.836702732;

//74:joint91
mChannel[74].mName = "joint91";
mChannel[74].mParentChannel = 73;
mChannel[74].mT[0] = 0.325758453962;
mChannel[74].mT[1] = 176.841466956;
mChannel[74].mT[2] = 11.5716840988;
mChannel[74].mR[0] = 64.4202478365;
mChannel[74].mR[1] = -76.8452323271;
mChannel[74].mR[2] = -65.0086421807;

//75:joint93
mChannel[75].mName = "joint93";
mChannel[75].mParentChannel = 7;
mChannel[75].mT[0] = -3.13650131226;
mChannel[75].mT[1] = 177.7788373;
mChannel[75].mT[2] = 8.28104515032;
mChannel[75].mR[0] = 150.387341769;
mChannel[75].mR[1] = -63.631909174;
mChannel[75].mR[2] = -147.610108243;

//76:joint94
mChannel[76].mName = "joint94";
mChannel[76].mParentChannel = 75;
mChannel[76].mT[0] = -3.57652185829;
mChannel[76].mT[1] = 177.499700652;
mChannel[76].mT[2] = 9.33224478866;
mChannel[76].mR[0] = 124.62109318;
mChannel[76].mR[1] = -54.1233925417;
mChannel[76].mR[2] = -119.223337734;

//77:joint95
mChannel[77].mName = "joint95";
mChannel[77].mParentChannel = 76;
mChannel[77].mT[0] = -3.92126557115;
mChannel[77].mT[1] = 176.883443966;
mChannel[77].mT[2] = 10.3085650107;
mChannel[77].mR[0] = 124.057667176;
mChannel[77].mR[1] = -65.5036026571;
mChannel[77].mR[2] = -121.596824108;

//78:joint97
mChannel[78].mName = "joint97";
mChannel[78].mParentChannel = 7;
mChannel[78].mT[0] = -4.39332723618;
mChannel[78].mT[1] = 178.343343831;
mChannel[78].mT[2] = 6.49619455294;
mChannel[78].mR[0] = 159.251190644;
mChannel[78].mR[1] = -48.0298651796;
mChannel[78].mR[2] = -152.999175148;

//79:joint98
mChannel[79].mName = "joint98";
mChannel[79].mParentChannel = 78;
mChannel[79].mT[0] = -4.91810083388;
mChannel[79].mT[1] = 178.075948811;
mChannel[79].mT[2] = 7.15099973633;
mChannel[79].mR[0] = 178.018732777;
mChannel[79].mR[1] = -54.0675136047;
mChannel[79].mR[2] = -177.553624096;

//80:joint99
mChannel[80].mName = "joint99";
mChannel[80].mParentChannel = 79;
mChannel[80].mT[0] = -5.41043759233;
mChannel[80].mT[1] = 178.05491457;
mChannel[80].mT[2] = 7.83094474003;
mChannel[80].mR[0] = -156.202238647;
mChannel[80].mR[1] = -54.0579766465;
mChannel[80].mR[2] = 151.422292736;

//81:LeftShoulder
mChannel[81].mName = "LeftShoulder";
mChannel[81].mParentChannel = 4;
mChannel[81].mT[0] = 1.5034968853;
mChannel[81].mT[1] = 146.175534416;
mChannel[81].mT[2] = 1.49595092689;
mChannel[81].mR[0] = 2.86249921332e-14;
mChannel[81].mR[1] = -3.35604963135e-14;
mChannel[81].mR[2] = 180.0;

//82:LeftArm
mChannel[82].mName = "LeftArm";
mChannel[82].mParentChannel = 81;
mChannel[82].mT[0] = 15.1109363853;
mChannel[82].mT[1] = 146.175534416;
mChannel[82].mT[2] = 1.49595092689;
mChannel[82].mR[0] = 2.86249921332e-14;
mChannel[82].mR[1] = -3.35604963135e-14;
mChannel[82].mR[2] = 180.0;

//83:LeftForeArm
mChannel[83].mName = "LeftForeArm";
mChannel[83].mParentChannel = 82;
mChannel[83].mT[0] = 39.8006579254;
mChannel[83].mT[1] = 146.175534416;
mChannel[83].mT[2] = 1.49595092689;
mChannel[83].mR[0] = 2.86249921332e-14;
mChannel[83].mR[1] = -3.35604963135e-14;
mChannel[83].mR[2] = 180.0;

//84:LeftHand
mChannel[84].mName = "LeftHand";
mChannel[84].mParentChannel = 83;
mChannel[84].mT[0] = 63.4002061723;
mChannel[84].mT[1] = 146.175534416;
mChannel[84].mT[2] = 1.49595092689;
mChannel[84].mR[0] = 2.86249921332e-14;
mChannel[84].mR[1] = -3.35604963135e-14;
mChannel[84].mR[2] = 180.0;

//85:LeftFingerBase
mChannel[85].mName = "LeftFingerBase";
mChannel[85].mParentChannel = 84;
mChannel[85].mT[0] = 65.7180123985;
mChannel[85].mT[1] = 146.175534416;
mChannel[85].mT[2] = 1.49595092689;
mChannel[85].mR[0] = 2.86249921332e-14;
mChannel[85].mR[1] = -3.35604963135e-14;
mChannel[85].mR[2] = 180.0;

//86:LeftHandThumb1
mChannel[86].mName = "LeftHandThumb1";
mChannel[86].mParentChannel = 85;
mChannel[86].mT[0] = 67.8419734432;
mChannel[86].mT[1] = 144.232916274;
mChannel[86].mT[2] = 5.94597966418;
mChannel[86].mR[0] = -126.850694437;
mChannel[86].mR[1] = 51.1237886749;
mChannel[86].mR[2] = 136.088329002;

//87:LeftHandThumb2
mChannel[87].mName = "LeftHandThumb2";
mChannel[87].mParentChannel = 86;
mChannel[87].mT[0] = 69.0600304023;
mChannel[87].mT[1] = 143.139636895;
mChannel[87].mT[2] = 7.70757555268;
mChannel[87].mR[0] = -104.781133215;
mChannel[87].mR[1] = 38.9713777484;
mChannel[87].mR[2] = 157.240235486;

//88:LeftHandThumb3
mChannel[88].mName = "LeftHandThumb3";
mChannel[88].mParentChannel = 87;
mChannel[88].mT[0] = 70.6971349196;
mChannel[88].mT[1] = 141.904290913;
mChannel[88].mT[2] = 9.36733851284;
mChannel[88].mR[0] = -108.690357805;
mChannel[88].mR[1] = 36.1465458025;
mChannel[88].mR[2] = 150.16475485;

//89:LeftHandIndex1
mChannel[89].mName = "LeftHandIndex1";
mChannel[89].mParentChannel = 85;
mChannel[89].mT[0] = 73.7859078342;
mChannel[89].mT[1] = 147.559871115;
mChannel[89].mT[2] = 6.56137433099;
mChannel[89].mR[0] = 7.378886861e-13;
mChannel[89].mR[1] = -1.07110823322e-13;
mChannel[89].mR[2] = 180.0;

//90:LeftHandIndex2
mChannel[90].mName = "LeftHandIndex2";
mChannel[90].mParentChannel = 89;
mChannel[90].mT[0] = 76.9671718878;
mChannel[90].mT[1] = 147.559871115;
mChannel[90].mT[2] = 6.56137433099;
mChannel[90].mR[0] = 7.378886861e-13;
mChannel[90].mR[1] = -1.07110823322e-13;
mChannel[90].mR[2] = 180.0;

//91:LeftHandIndex3
mChannel[91].mName = "LeftHandIndex3";
mChannel[91].mParentChannel = 90;
mChannel[91].mT[0] = 79.5877406851;
mChannel[91].mT[1] = 147.559871115;
mChannel[91].mT[2] = 6.56137433099;
mChannel[91].mR[0] = 7.378886861e-13;
mChannel[91].mR[1] = -1.07110823322e-13;
mChannel[91].mR[2] = 180.0;

//92:LeftHandMiddle1
mChannel[92].mName = "LeftHandMiddle1";
mChannel[92].mParentChannel = 85;
mChannel[92].mT[0] = 73.8035854221;
mChannel[92].mT[1] = 148.09541609;
mChannel[92].mT[2] = 4.21910293542;
mChannel[92].mR[0] = 7.09263693966e-13;
mChannel[92].mR[1] = -3.39688884404e-13;
mChannel[92].mR[2] = 180.0;

//93:LeftHandMiddle2
mChannel[93].mName = "LeftHandMiddle2";
mChannel[93].mParentChannel = 92;
mChannel[93].mT[0] = 77.5166651598;
mChannel[93].mT[1] = 148.09541609;
mChannel[93].mT[2] = 4.21910293542;
mChannel[93].mR[0] = 7.09263693966e-13;
mChannel[93].mR[1] = -3.39688884404e-13;
mChannel[93].mR[2] = 180.0;

//94:LeftHandMiddle3
mChannel[94].mName = "LeftHandMiddle3";
mChannel[94].mParentChannel = 93;
mChannel[94].mT[0] = 80.3347989206;
mChannel[94].mT[1] = 148.09541609;
mChannel[94].mT[2] = 4.21910293542;
mChannel[94].mR[0] = 7.09263693966e-13;
mChannel[94].mR[1] = -3.39688884404e-13;
mChannel[94].mR[2] = 180.0;

//95:LeftHandRing1
mChannel[95].mName = "LeftHandRing1";
mChannel[95].mParentChannel = 85;
mChannel[95].mT[0] = 73.868587663;
mChannel[95].mT[1] = 147.822798093;
mChannel[95].mT[2] = 1.82701164289;
mChannel[95].mR[0] = 7.42659518122e-13;
mChannel[95].mR[1] = -2.60175017368e-13;
mChannel[95].mR[2] = 180.0;

//96:LeftHandRing2
mChannel[96].mName = "LeftHandRing2";
mChannel[96].mParentChannel = 95;
mChannel[96].mT[0] = 77.2557387113;
mChannel[96].mT[1] = 147.822798093;
mChannel[96].mT[2] = 1.82701164289;
mChannel[96].mR[0] = 7.42659518122e-13;
mChannel[96].mR[1] = -2.60175017368e-13;
mChannel[96].mR[2] = 180.0;

//97:LeftHandRing3
mChannel[97].mName = "LeftHandRing3";
mChannel[97].mParentChannel = 96;
mChannel[97].mT[0] = 79.941958811;
mChannel[97].mT[1] = 147.822798093;
mChannel[97].mT[2] = 1.82701164289;
mChannel[97].mR[0] = 7.42659518122e-13;
mChannel[97].mR[1] = -2.60175017368e-13;
mChannel[97].mR[2] = 180.0;

//98:LeftHandPinky1
mChannel[98].mName = "LeftHandPinky1";
mChannel[98].mParentChannel = 85;
mChannel[98].mT[0] = 73.8379736611;
mChannel[98].mT[1] = 147.037852185;
mChannel[98].mT[2] = -0.329368654797;
mChannel[98].mR[0] = 7.58562291529e-13;
mChannel[98].mR[1] = -9.62282463301e-13;
mChannel[98].mR[2] = 180.0;

//99:LeftHandPinky2
mChannel[99].mName = "LeftHandPinky2";
mChannel[99].mParentChannel = 98;
mChannel[99].mT[0] = 76.4410882242;
mChannel[99].mT[1] = 147.037852185;
mChannel[99].mT[2] = -0.329368654797;
mChannel[99].mR[0] = 7.58562291529e-13;
mChannel[99].mR[1] = -9.62282463301e-13;
mChannel[99].mR[2] = 180.0;

//100:LeftHandPinky3
mChannel[100].mName = "LeftHandPinky3";
mChannel[100].mParentChannel = 99;
mChannel[100].mT[0] = 78.4356687987;
mChannel[100].mT[1] = 147.037852185;
mChannel[100].mT[2] = -0.329368654797;
mChannel[100].mR[0] = 7.58562291529e-13;
mChannel[100].mR[1] = -9.62282463301e-13;
mChannel[100].mR[2] = 180.0;

//101:RightShoulder
mChannel[101].mName = "RightShoulder";
mChannel[101].mParentChannel = 4;
mChannel[101].mT[0] = -1.5035;
mChannel[101].mT[1] = 146.176;
mChannel[101].mT[2] = 1.49595;
mChannel[101].mR[0] = -180.0;
mChannel[101].mR[1] = 2.12742575148e-14;
mChannel[101].mR[2] = 180.0;

//102:RightArm
mChannel[102].mName = "RightArm";
mChannel[102].mParentChannel = 101;
mChannel[102].mT[0] = -15.1109;
mChannel[102].mT[1] = 146.176;
mChannel[102].mT[2] = 1.49595;
mChannel[102].mR[0] = -180.0;
mChannel[102].mR[1] = 2.12742575148e-14;
mChannel[102].mR[2] = 180.0;

//103:RightForeArm
mChannel[103].mName = "RightForeArm";
mChannel[103].mParentChannel = 102;
mChannel[103].mT[0] = -39.8007;
mChannel[103].mT[1] = 146.176;
mChannel[103].mT[2] = 1.49595;
mChannel[103].mR[0] = -180.0;
mChannel[103].mR[1] = 2.12742575148e-14;
mChannel[103].mR[2] = 180.0;

//104:RightHand
mChannel[104].mName = "RightHand";
mChannel[104].mParentChannel = 103;
mChannel[104].mT[0] = -63.4002;
mChannel[104].mT[1] = 146.176;
mChannel[104].mT[2] = 1.49595;
mChannel[104].mR[0] = -180.0;
mChannel[104].mR[1] = 2.12742575148e-14;
mChannel[104].mR[2] = 180.0;

//105:RightFingerBase
mChannel[105].mName = "RightFingerBase";
mChannel[105].mParentChannel = 104;
mChannel[105].mT[0] = -65.718;
mChannel[105].mT[1] = 146.176;
mChannel[105].mT[2] = 1.49595;
mChannel[105].mR[0] = -180.0;
mChannel[105].mR[1] = 2.12742575148e-14;
mChannel[105].mR[2] = 180.0;

//106:RightHandThumb1
mChannel[106].mName = "RightHandThumb1";
mChannel[106].mParentChannel = 105;
mChannel[106].mT[0] = -67.842;
mChannel[106].mT[1] = 144.233;
mChannel[106].mT[2] = 5.94598;
mChannel[106].mR[0] = 53.1493055634;
mChannel[106].mR[1] = -51.1237886749;
mChannel[106].mR[2] = -136.088329002;

//107:RightHandThumb2
mChannel[107].mName = "RightHandThumb2";
mChannel[107].mParentChannel = 106;
mChannel[107].mT[0] = -69.06;
mChannel[107].mT[1] = 143.14;
mChannel[107].mT[2] = 7.70758;
mChannel[107].mR[0] = 75.2188667849;
mChannel[107].mR[1] = -38.9713777484;
mChannel[107].mR[2] = -157.240235486;

//108:RightHandThumb3
mChannel[108].mName = "RightHandThumb3";
mChannel[108].mParentChannel = 107;
mChannel[108].mT[0] = -70.6971;
mChannel[108].mT[1] = 141.904;
mChannel[108].mT[2] = 9.36734;
mChannel[108].mR[0] = 71.3096421954;
mChannel[108].mR[1] = -36.1465458025;
mChannel[108].mR[2] = -150.16475485;

//109:RightHandIndex1
mChannel[109].mName = "RightHandIndex1";
mChannel[109].mParentChannel = 105;
mChannel[109].mT[0] = -73.7859;
mChannel[109].mT[1] = 147.56;
mChannel[109].mT[2] = 6.56137;
mChannel[109].mR[0] = -180.0;
mChannel[109].mR[1] = 9.48245845237e-14;
mChannel[109].mR[2] = -180.0;

//110:RightHandIndex2
mChannel[110].mName = "RightHandIndex2";
mChannel[110].mParentChannel = 109;
mChannel[110].mT[0] = -76.9672;
mChannel[110].mT[1] = 147.56;
mChannel[110].mT[2] = 6.56137;
mChannel[110].mR[0] = -180.0;
mChannel[110].mR[1] = 9.48245845237e-14;
mChannel[110].mR[2] = -180.0;

//111:RightHandIndex3
mChannel[111].mName = "RightHandIndex3";
mChannel[111].mParentChannel = 110;
mChannel[111].mT[0] = -79.5877;
mChannel[111].mT[1] = 147.56;
mChannel[111].mT[2] = 6.56137;
mChannel[111].mR[0] = -180.0;
mChannel[111].mR[1] = 9.48245845237e-14;
mChannel[111].mR[2] = -180.0;

//112:RightHandMiddle1
mChannel[112].mName = "RightHandMiddle1";
mChannel[112].mParentChannel = 105;
mChannel[112].mT[0] = -73.8036;
mChannel[112].mT[1] = 148.095;
mChannel[112].mT[2] = 4.2191;
mChannel[112].mR[0] = -180.0;
mChannel[112].mR[1] = 3.27402645606e-13;
mChannel[112].mR[2] = -180.0;

//113:RightHandMiddle2
mChannel[113].mName = "RightHandMiddle2";
mChannel[113].mParentChannel = 112;
mChannel[113].mT[0] = -77.5167;
mChannel[113].mT[1] = 148.095;
mChannel[113].mT[2] = 4.2191;
mChannel[113].mR[0] = -180.0;
mChannel[113].mR[1] = 3.27402645606e-13;
mChannel[113].mR[2] = -180.0;

//114:RightHandMiddle3
mChannel[114].mName = "RightHandMiddle3";
mChannel[114].mParentChannel = 113;
mChannel[114].mT[0] = -80.3348;
mChannel[114].mT[1] = 148.095;
mChannel[114].mT[2] = 4.2191;
mChannel[114].mR[0] = -180.0;
mChannel[114].mR[1] = 3.27402645606e-13;
mChannel[114].mR[2] = -180.0;

//115:RightHandRing1
mChannel[115].mName = "RightHandRing1";
mChannel[115].mParentChannel = 105;
mChannel[115].mT[0] = -73.8686;
mChannel[115].mT[1] = 147.823;
mChannel[115].mT[2] = 1.82701;
mChannel[115].mR[0] = -180.0;
mChannel[115].mR[1] = 2.47888778569e-13;
mChannel[115].mR[2] = -180.0;

//116:RightHandRing2
mChannel[116].mName = "RightHandRing2";
mChannel[116].mParentChannel = 115;
mChannel[116].mT[0] = -77.2557;
mChannel[116].mT[1] = 147.823;
mChannel[116].mT[2] = 1.82701;
mChannel[116].mR[0] = -180.0;
mChannel[116].mR[1] = 2.47888778569e-13;
mChannel[116].mR[2] = -180.0;

//117:RightHandRing3
mChannel[117].mName = "RightHandRing3";
mChannel[117].mParentChannel = 116;
mChannel[117].mT[0] = -79.942;
mChannel[117].mT[1] = 147.823;
mChannel[117].mT[2] = 1.82701;
mChannel[117].mR[0] = -180.0;
mChannel[117].mR[1] = 2.47888778569e-13;
mChannel[117].mR[2] = -180.0;

//118:RightHandPinky1
mChannel[118].mName = "RightHandPinky1";
mChannel[118].mParentChannel = 105;
mChannel[118].mT[0] = -73.838;
mChannel[118].mT[1] = 147.038;
mChannel[118].mT[2] = -0.329369;
mChannel[118].mR[0] = -180.0;
mChannel[118].mR[1] = 9.49996224502e-13;
mChannel[118].mR[2] = -180.0;

//119:RightHandPinky2
mChannel[119].mName = "RightHandPinky2";
mChannel[119].mParentChannel = 118;
mChannel[119].mT[0] = -76.4411;
mChannel[119].mT[1] = 147.038;
mChannel[119].mT[2] = -0.329369;
mChannel[119].mR[0] = -180.0;
mChannel[119].mR[1] = 9.49996224502e-13;
mChannel[119].mR[2] = -180.0;

//120:RightHandPinky3
mChannel[120].mName = "RightHandPinky3";
mChannel[120].mParentChannel = 119;
mChannel[120].mT[0] = -78.4357;
mChannel[120].mT[1] = 147.038;
mChannel[120].mT[2] = -0.329369;
mChannel[120].mR[0] = -180.0;
mChannel[120].mR[1] = 9.49996224502e-13;
mChannel[120].mR[2] = -180.0;

//121:LeftUpLeg
mChannel[121].mName = "LeftUpLeg";
mChannel[121].mParentChannel = 1;
mChannel[121].mT[0] = 8.61240100861;
mChannel[121].mT[1] = 93.3364129066;
mChannel[121].mT[2] = 1.82888378948;
mChannel[121].mR[0] = 0.0264600386521;
mChannel[121].mR[1] = 1.68387480388;
mChannel[121].mR[2] = 90.9003888471;

//122:LeftLeg
mChannel[122].mName = "LeftLeg";
mChannel[122].mParentChannel = 121;
mChannel[122].mT[0] = 9.26350623306;
mChannel[122].mT[1] = 51.9070786439;
mChannel[122].mT[2] = 3.0469544612;
mChannel[122].mR[0] = 0.0264592316833;
mChannel[122].mR[1] = -1.62334569064;
mChannel[122].mR[2] = 90.8988617588;

//123:LeftFoot
mChannel[123].mName = "LeftFoot";
mChannel[123].mParentChannel = 122;
mChannel[123].mT[0] = 9.91946691655;
mChannel[123].mT[1] = 11.8752676909;
mChannel[123].mT[2] = 0.785645392167;
mChannel[123].mR[0] = -94.049242617;
mChannel[123].mR[1] = 67.1995620498;
mChannel[123].mR[2] = 87.1658380361;

//124:LeftToeBase
mChannel[124].mName = "LeftToeBase";
mChannel[124].mParentChannel = 123;
mChannel[124].mT[0] = 11.4009849324;
mChannel[124].mT[1] = 2.47775734032;
mChannel[124].mT[2] = 12.8220852829;
mChannel[124].mR[0] = -95.8058310697;
mChannel[124].mR[1] = 74.3051832694;
mChannel[124].mR[2] = 85.308840598;

//125:RightUpLeg
mChannel[125].mName = "RightUpLeg";
mChannel[125].mParentChannel = 1;
mChannel[125].mT[0] = -8.61240196228;
mChannel[125].mT[1] = 93.3363656998;
mChannel[125].mT[2] = 1.82888379693;
mChannel[125].mR[0] = -179.973539961;
mChannel[125].mR[1] = -1.68387480388;
mChannel[125].mR[2] = -90.9003888471;

//126:RightLeg
mChannel[126].mName = "RightLeg";
mChannel[126].mParentChannel = 125;
mChannel[126].mT[0] = -9.26350388695;
mChannel[126].mT[1] = 51.9070887667;
mChannel[126].mT[2] = 3.04695886654;
mChannel[126].mR[0] = -179.973540768;
mChannel[126].mR[1] = 1.62334569064;
mChannel[126].mR[2] = -90.8988617588;

//127:RightFoot
mChannel[127].mName = "RightFoot";
mChannel[127].mParentChannel = 126;
mChannel[127].mT[0] = -9.91945855479;
mChannel[127].mT[1] = 11.8752549388;
mChannel[127].mT[2] = 0.785645577202;
mChannel[127].mR[0] = 85.950757383;
mChannel[127].mR[1] = -67.1995620498;
mChannel[127].mR[2] = -87.1658380361;

//128:RightToeBase
mChannel[128].mName = "RightToeBase";
mChannel[128].mParentChannel = 127;
mChannel[128].mT[0] = -11.401001981;
mChannel[128].mT[1] = 2.47775873293;
mChannel[128].mT[2] = 12.8220422784;
mChannel[128].mR[0] = 84.1941689303;
mChannel[128].mR[1] = -74.3051832694;
mChannel[128].mR[2] = -85.308840598;}

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
mLocalTranslationR[2].mValue[0] = 2.124;
mLocalTranslationR[2].mValue[1] = -1.943;
mLocalTranslationR[2].mValue[2] = -4.45003;

//3:RightHandThumb2
mLocalTranslationR[3].mValue[0] = 2.3979222353;
mLocalTranslationR[3].mValue[1] = -0.168497753999;
mLocalTranslationR[3].mValue[2] = -0.0546353397903;

//4:RightHandThumb3
mLocalTranslationR[4].mValue[0] = 2.58930891056;
mLocalTranslationR[4].mValue[1] = 0.168078813473;
mLocalTranslationR[4].mValue[2] = -0.479400193731;

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
mLocalTranslationL[2].mValue[0] = -2.12396104475;
mLocalTranslationL[2].mValue[1] = 1.94261814258;
mLocalTranslationL[2].mValue[2] = 4.4500287373;

//3:LeftHandThumb2
mLocalTranslationL[3].mValue[0] = -2.39806640211;
mLocalTranslationL[3].mValue[1] = 0.168549073178;
mLocalTranslationL[3].mValue[2] = 0.0548759553903;

//4:LeftHandThumb3
mLocalTranslationL[4].mValue[0] = -2.5891172988;
mLocalTranslationL[4].mValue[1] = -0.168078059724;
mLocalTranslationL[4].mValue[2] = 0.478774851164;

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

