xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 82;
 0.00000;0.00000;0.00000;,
 0.03903;-0.61032;-0.53110;,
 0.05205;-0.05502;-0.80645;,
 0.00315;-0.80811;0.05536;,
 -0.03458;-0.53247;0.60939;,
 -0.05205;0.05504;0.80645;,
 -0.03901;0.61037;0.53110;,
 -0.00313;0.80814;-0.05536;,
 0.03459;0.53251;-0.60939;,
 0.02348;-0.68835;-0.60017;,
 0.03818;-0.06222;-0.91063;,
 -0.01696;-0.91133;0.06111;,
 -0.05950;-0.60057;0.68581;,
 -0.07918;0.06191;0.90801;,
 -0.06449;0.68804;0.59754;,
 -0.02403;0.91101;-0.06372;,
 0.01850;0.60024;-0.68844;,
 -0.03070;-0.75483;-0.66133;,
 -0.01459;-0.06865;-1.00158;,
 -0.07504;-0.99920;0.06335;,
 -0.12165;-0.65865;0.74797;,
 -0.14323;0.06738;0.99148;,
 -0.12712;0.75355;0.65124;,
 -0.08278;0.99793;-0.07345;,
 -0.03617;0.65737;-0.75807;,
 -0.11529;-0.79966;-0.70530;,
 -0.09824;-0.07337;-1.06544;,
 -0.16223;-1.05832;0.06176;,
 -0.21157;-0.69784;0.78642;,
 -0.23440;0.07064;1.04416;,
 -0.21736;0.79693;0.68402;,
 -0.17041;1.05562;-0.08304;,
 -0.12109;0.69513;-0.80769;,
 -0.21742;-0.81600;-0.72537;,
 -0.20004;-0.07560;-1.09250;,
 -0.26527;-1.07969;0.05657;,
 -0.31555;-0.71221;0.79528;,
 -0.33884;0.07119;1.05803;,
 -0.32144;0.81156;0.69090;,
 -0.27360;1.07527;-0.09104;,
 -0.22330;0.70780;-0.82976;,
 -6.86359;-0.87084;-1.15057;,
 -6.84621;-0.13049;-1.51770;,
 -6.91144;-1.13456;-0.36863;,
 -6.96173;-0.76704;0.37008;,
 -6.98501;0.01631;0.63283;,
 -6.96762;0.75674;0.26570;,
 -6.91978;1.02042;-0.51624;,
 -6.86947;0.65293;-1.25495;,
 -6.96768;-0.85623;-1.14369;,
 -6.95064;-0.12992;-1.50383;,
 -7.01463;-1.11485;-0.37662;,
 -7.06396;-0.75441;0.34802;,
 -7.08680;0.01408;0.60578;,
 -7.06975;0.74038;0.24563;,
 -7.02282;0.99905;-0.52143;,
 -6.97348;0.63858;-1.24609;,
 -7.05792;-0.81282;-1.11091;,
 -7.04181;-0.12667;-1.45115;,
 -7.10226;-1.05722;-0.38622;,
 -7.14887;-0.71664;0.29840;,
 -7.17045;0.00936;0.54192;,
 -7.15434;0.69553;0.20166;,
 -7.10999;0.93994;-0.52302;,
 -7.06339;0.59936;-1.20764;,
 -7.12057;-0.74729;-1.05721;,
 -7.10586;-0.12119;-1.36768;,
 -7.16102;-0.97030;-0.39595;,
 -7.20354;-0.65954;0.22877;,
 -7.22322;0.00295;0.45097;,
 -7.20853;0.62906;0.14050;,
 -7.16806;0.85208;-0.52078;,
 -7.12553;0.54130;-1.14548;,
 -7.14603;-0.66960;-0.99077;,
 -7.13302;-0.11434;-1.26612;,
 -7.18192;-0.86742;-0.40431;,
 -7.21964;-0.59180;0.14972;,
 -7.23708;-0.00427;0.34678;,
 -7.22407;0.55103;0.07143;,
 -7.18819;0.74882;-0.51503;,
 -7.15046;0.47318;-1.06906;,
 -7.18504;-0.05931;-0.45967;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;;
 
 MeshMaterialList {
  6;
  88;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.125600;0.000000;0.166400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.696800;0.636800;0.460800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.580392;0.800000;0.671373;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.800000;0.498824;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.251200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  82;
  0.997926;0.008249;0.063843;,
  0.999424;0.001546;-0.033903;,
  0.997849;-0.065556;-0.000660;,
  0.993514;-0.089442;0.070216;,
  0.988961;-0.056113;0.137144;,
  0.986857;0.014842;0.160915;,
  0.988430;0.081907;0.127664;,
  0.992760;0.105817;0.056842;,
  0.997316;0.072525;-0.010078;,
  0.947277;-0.018254;-0.319896;,
  0.941136;-0.279203;-0.190549;,
  0.924273;-0.372139;0.085039;,
  0.906561;-0.242601;0.345387;,
  0.898368;0.033476;0.437965;,
  0.904491;0.294403;0.308581;,
  0.921354;0.387318;0.033029;,
  0.939084;0.257806;-0.227281;,
  0.753071;-0.042056;-0.656593;,
  0.741736;-0.525346;-0.416940;,
  0.710478;-0.697486;0.093459;,
  0.677636;-0.457619;0.575669;,
  0.662430;0.053753;0.747193;,
  0.673794;0.537040;0.507533;,
  0.705075;0.709127;-0.002886;,
  0.737889;0.469269;-0.485083;,
  0.443076;-0.059559;-0.894503;,
  0.428241;-0.692383;-0.580703;,
  0.387362;-0.917753;0.087640;,
  0.344354;-0.603672;0.719027;,
  0.324442;0.065902;0.943607;,
  0.339306;0.698711;0.629821;,
  0.380243;0.924084;-0.038519;,
  0.423222;0.609994;-0.669919;,
  0.161909;-0.066829;-0.984540;,
  0.145883;-0.749049;-0.646254;,
  0.101831;-0.992025;0.074280;,
  0.055472;-0.653407;0.754971;,
  0.034010;0.068434;0.997076;,
  0.050017;0.750663;0.658789;,
  0.094120;0.993645;-0.061733;,
  0.140497;0.655025;-0.742430;,
  -0.033991;-0.068443;-0.997076;,
  -0.050068;-0.750664;-0.658784;,
  -0.094177;-0.993639;0.061746;,
  -0.140460;-0.655027;0.742435;,
  -0.161871;0.066811;0.984548;,
  -0.145909;0.749044;0.646253;,
  -0.101825;0.992025;-0.074280;,
  -0.055426;0.653410;-0.754972;,
  -0.324451;-0.065906;-0.943604;,
  -0.339333;-0.698717;-0.629799;,
  -0.380224;-0.924091;0.038539;,
  -0.423161;-0.610024;0.669929;,
  -0.443062;0.059549;0.894511;,
  -0.428295;0.692359;0.580692;,
  -0.387417;0.917729;-0.087638;,
  -0.344365;0.603662;-0.719030;,
  -0.662445;-0.053759;-0.747179;,
  -0.673758;-0.537074;-0.507545;,
  -0.704992;-0.709209;0.002904;,
  -0.737846;-0.469316;0.485103;,
  -0.753071;0.042060;0.656594;,
  -0.741734;0.525342;0.416949;,
  -0.710515;0.697450;-0.093446;,
  -0.677679;0.457586;-0.575644;,
  -0.898342;-0.033469;-0.438020;,
  -0.904485;-0.294399;-0.308605;,
  -0.921349;-0.387332;-0.033013;,
  -0.939071;-0.257834;0.227304;,
  -0.947279;0.018250;0.319891;,
  -0.941135;0.279211;0.190544;,
  -0.924260;0.372171;-0.085047;,
  -0.906534;0.242640;-0.345431;,
  -0.986851;-0.014831;-0.160949;,
  -0.988431;-0.081894;-0.127663;,
  -0.992763;-0.105787;-0.056837;,
  -0.997316;-0.072516;0.010082;,
  -0.999425;-0.001552;0.033884;,
  -0.997850;0.065540;0.000636;,
  -0.993511;0.089465;-0.070229;,
  -0.988952;0.056166;-0.137184;,
  -0.997927;-0.008243;-0.063834;;
  88;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  3;73,74,81;,
  3;74,75,81;,
  3;75,76,81;,
  3;76,77,81;,
  3;77,78,81;,
  3;78,79,81;,
  3;79,80,81;,
  3;80,73,81;;
 }
 MeshTextureCoords {
  82;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}