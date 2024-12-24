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
 138;
 0.00000;0.00000;0.00000;,
 6.35750;0.00000;0.00000;,
 6.35750;0.00000;-6.80000;,
 0.00000;0.00000;-6.80000;,
 -2.21460;-20.00000;-8.83361;,
 8.57210;-20.00000;-8.83361;,
 8.57210;-20.00000;2.03361;,
 -2.21460;-20.00000;2.03361;,
 0.00000;0.00000;-6.80000;,
 6.35750;0.00000;-6.80000;,
 6.35750;-0.32219;-7.57782;,
 0.00000;-0.32219;-7.57782;,
 6.35750;-1.10000;-7.90000;,
 0.00000;-1.10000;-7.90000;,
 -2.21460;-19.67782;-10.07666;,
 8.57210;-19.67782;-10.07666;,
 8.57210;-20.00000;-8.83361;,
 -2.21460;-18.90000;-10.59155;,
 8.57210;-18.90000;-10.59155;,
 0.00000;-0.32219;0.77782;,
 6.35750;-0.32219;0.77782;,
 6.35750;0.00000;0.00000;,
 0.00000;-1.10000;1.10000;,
 6.35750;-1.10000;1.10000;,
 -2.21460;-20.00000;2.03361;,
 8.57210;-20.00000;2.03361;,
 8.57210;-19.67782;3.27666;,
 -2.21460;-19.67782;3.27666;,
 8.57210;-18.90000;3.79155;,
 -2.21460;-18.90000;3.79155;,
 6.99147;-0.32219;-0.00000;,
 6.99147;-0.32219;-6.80000;,
 7.25407;-1.10000;-0.00000;,
 7.25407;-1.10000;-6.80000;,
 9.64775;-19.67782;-8.83361;,
 9.64775;-19.67782;2.03361;,
 10.09330;-18.90000;-8.83361;,
 10.09330;-18.90000;2.03361;,
 -0.63397;-0.32219;-6.80000;,
 -0.63397;-0.32219;0.00000;,
 -0.89657;-1.10000;-6.80000;,
 -0.89657;-1.10000;0.00000;,
 -3.29025;-19.67782;2.03361;,
 -3.29025;-19.67782;-8.83361;,
 -3.73580;-18.90000;2.03361;,
 -3.73580;-18.90000;-8.83361;,
 6.99147;-1.10000;-7.57782;,
 -0.63397;-1.10000;-7.57782;,
 9.64775;-18.90000;-10.07666;,
 6.99147;-1.10000;0.77782;,
 -3.29025;-18.90000;-10.07666;,
 9.64775;-18.90000;3.27666;,
 -0.63397;-1.10000;0.77782;,
 -3.29025;-18.90000;3.27666;,
 8.29633;-15.61300;-10.09452;,
 8.57210;-18.90000;-10.59155;,
 -2.21460;-18.90000;-10.59155;,
 -1.93498;-15.56712;-10.08758;,
 8.29633;-15.61300;3.29452;,
 -1.93498;-15.56712;3.28758;,
 8.57210;-18.90000;3.79155;,
 9.74045;-15.61948;1.65882;,
 10.09330;-18.90000;2.03361;,
 10.09330;-18.90000;-8.83361;,
 9.74045;-15.61948;-8.45882;,
 -3.37663;-15.56066;1.65210;,
 -3.37663;-15.56066;-8.45210;,
 -3.73580;-18.90000;-8.83361;,
 8.29633;-15.61300;-10.09452;,
 9.31745;-15.61758;-9.61586;,
 9.74045;-15.61948;-8.45882;,
 8.29633;-15.61300;3.29452;,
 9.31745;-15.61758;2.81586;,
 9.74045;-15.61948;1.65882;,
 -1.93498;-15.56712;-10.08758;,
 -2.95441;-15.56255;-9.60813;,
 -3.37663;-15.56066;-8.45210;,
 -1.93498;-15.56712;3.28758;,
 -2.95441;-15.56255;2.80813;,
 -3.37663;-15.56066;1.65210;,
 -1.71944;-12.99795;-9.69909;,
 8.07694;-12.99795;-9.69909;,
 8.07694;-12.99795;2.89909;,
 -1.71944;-12.99795;2.89909;,
 9.45848;-12.99795;-8.15931;,
 9.45848;-12.99795;1.35931;,
 -3.10098;-12.99795;1.35931;,
 -3.10098;-12.99795;-8.15931;,
 8.07694;-12.99795;-9.69909;,
 9.05384;-12.99795;-9.24810;,
 9.45848;-12.99795;-8.15931;,
 9.05384;-12.99795;2.44810;,
 8.07694;-12.99795;2.89909;,
 9.45848;-12.99795;1.35931;,
 -2.69634;-12.99795;-9.24810;,
 -1.71944;-12.99795;-9.69909;,
 -3.10098;-12.99795;-8.15931;,
 -1.71944;-12.99795;2.89909;,
 -2.69634;-12.99795;2.44810;,
 -3.10098;-12.99795;1.35931;,
 -1.49143;-10.28014;-9.28813;,
 6.35750;-1.10000;-7.90000;,
 7.84893;-10.28014;-9.28813;,
 7.84893;-10.28014;2.48813;,
 6.35750;-1.10000;1.10000;,
 0.00000;-1.10000;1.10000;,
 -1.49143;-10.28014;2.48813;,
 9.16616;-10.28014;-7.84881;,
 7.25407;-1.10000;-6.80000;,
 9.16616;-10.28014;1.04881;,
 -2.80866;-10.28014;1.04881;,
 -0.89657;-1.10000;0.00000;,
 -0.89657;-1.10000;-6.80000;,
 -2.80866;-10.28014;-7.84881;,
 7.84893;-10.28014;-9.28813;,
 8.78035;-10.28014;-8.86657;,
 9.16616;-10.28014;-7.84881;,
 8.78035;-10.28014;2.06656;,
 7.84893;-10.28014;2.48813;,
 9.16616;-10.28014;1.04881;,
 -2.42285;-10.28014;-8.86657;,
 -1.49143;-10.28014;-9.28813;,
 -2.80866;-10.28014;-7.84881;,
 -1.49143;-10.28014;2.48813;,
 -2.42285;-10.28014;2.06656;,
 -2.80866;-10.28014;1.04881;,
 -0.16620;-0.44520;0.03619;,
 -1.50928;2.24427;1.25720;,
 -1.44787;2.24351;-7.89307;,
 -0.10480;-0.44597;-6.04821;,
 7.21639;-0.44520;0.05023;,
 8.35392;2.24427;1.39331;,
 -1.58834;2.24351;1.33190;,
 -0.09648;-0.44597;-0.01117;,
 7.12955;-0.44520;-6.67206;,
 8.47263;2.24427;-7.89307;,
 8.41123;2.24351;1.25720;,
 7.06815;-0.44597;-0.58766;;
 
 101;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;14,15,16,4;,
 4;17,18,15,14;,
 4;19,20,21,0;,
 4;22,23,20,19;,
 4;24,25,26,27;,
 4;27,26,28,29;,
 4;9,21,30,31;,
 4;31,30,32,33;,
 4;25,16,34,35;,
 4;35,34,36,37;,
 4;0,8,38,39;,
 4;39,38,40,41;,
 4;4,24,42,43;,
 4;43,42,44,45;,
 3;9,31,10;,
 3;31,33,46;,
 3;46,10,31;,
 3;10,46,12;,
 3;11,38,8;,
 3;47,40,38;,
 3;38,11,47;,
 3;13,47,11;,
 3;15,34,16;,
 3;48,36,34;,
 3;34,15,48;,
 3;18,48,15;,
 3;20,30,21;,
 3;49,32,30;,
 3;30,20,49;,
 3;23,49,20;,
 3;4,43,14;,
 3;43,45,50;,
 3;50,14,43;,
 3;14,50,17;,
 3;25,35,26;,
 3;35,37,51;,
 3;51,26,35;,
 3;26,51,28;,
 3;0,39,19;,
 3;39,41,52;,
 3;52,19,39;,
 3;19,52,22;,
 3;27,42,24;,
 3;53,44,42;,
 3;42,27,53;,
 3;29,53,27;,
 4;54,55,56,57;,
 4;58,59,29,60;,
 4;61,62,63,64;,
 4;65,66,67,44;,
 4;68,69,48,18;,
 4;69,70,36,48;,
 4;71,28,51,72;,
 4;72,51,37,73;,
 4;74,17,50,75;,
 4;75,50,45,76;,
 4;77,78,53,29;,
 4;78,79,44,53;,
 4;80,81,54,57;,
 4;82,83,59,58;,
 4;84,85,61,64;,
 4;86,87,66,65;,
 4;88,89,69,68;,
 4;89,90,70,69;,
 4;91,92,71,72;,
 4;93,91,72,73;,
 4;94,95,74,75;,
 4;96,94,75,76;,
 4;97,98,78,77;,
 4;98,99,79,78;,
 4;100,13,101,102;,
 4;100,102,81,80;,
 4;103,104,105,106;,
 4;103,106,83,82;,
 4;107,108,32,109;,
 4;107,109,85,84;,
 4;110,111,112,113;,
 4;110,113,87,86;,
 4;114,12,46,115;,
 4;114,115,89,88;,
 4;115,46,33,116;,
 4;115,116,90,89;,
 4;117,49,23,118;,
 4;117,118,92,91;,
 4;119,32,49,117;,
 4;119,117,91,93;,
 4;120,47,13,121;,
 4;120,121,95,94;,
 4;122,40,47,120;,
 4;122,120,94,96;,
 4;123,22,52,124;,
 4;123,124,98,97;,
 4;124,52,41,125;,
 4;124,125,99,98;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;;
 
 MeshMaterialList {
  6;
  101;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
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
  87;
  -0.229509;0.954468;0.190571;,
  0.229509;0.954468;0.190571;,
  -0.229509;0.954468;-0.190571;,
  0.229509;0.954468;-0.190571;,
  -0.218552;0.278784;-0.935155;,
  0.218552;0.278784;-0.935155;,
  -0.217018;-0.204253;-0.954560;,
  0.217034;-0.204254;-0.954556;,
  -0.143946;-0.981630;-0.125225;,
  0.143946;-0.981630;-0.125225;,
  -0.143946;-0.981630;0.125225;,
  0.143946;-0.981630;0.125225;,
  -0.217018;-0.204253;0.954560;,
  0.217034;-0.204254;0.954556;,
  -0.218553;0.278784;0.935155;,
  0.218553;0.278784;0.935155;,
  0.950037;0.267668;0.160573;,
  0.966417;-0.193449;0.169162;,
  0.950037;0.267668;-0.160573;,
  0.966417;-0.193449;-0.169162;,
  -0.966414;-0.193449;0.169177;,
  -0.950037;0.267668;0.160573;,
  -0.966414;-0.193449;-0.169177;,
  -0.950037;0.267668;-0.160573;,
  -0.332083;0.666978;-0.666980;,
  0.332083;0.666978;-0.666980;,
  -0.252906;-0.795345;-0.550877;,
  0.252906;-0.795345;-0.550877;,
  -0.332083;0.666978;0.666980;,
  0.332083;0.666978;0.666980;,
  -0.252906;-0.795345;0.550877;,
  0.252906;-0.795345;0.550877;,
  0.735098;0.627150;0.257512;,
  0.735098;0.627150;-0.257512;,
  0.599586;-0.771381;0.213234;,
  0.599586;-0.771381;-0.213234;,
  -0.735098;0.627151;0.257512;,
  -0.735098;0.627151;-0.257512;,
  -0.599586;-0.771380;0.213234;,
  -0.599586;-0.771380;-0.213233;,
  0.705693;-0.321583;-0.631334;,
  0.708767;0.344666;-0.615512;,
  0.705693;-0.321582;0.631334;,
  0.708768;0.344666;0.615511;,
  -0.705675;-0.321582;-0.631353;,
  -0.708767;0.344666;-0.615512;,
  -0.705675;-0.321582;0.631353;,
  -0.708767;0.344666;0.615511;,
  -0.214588;0.162962;-0.963014;,
  0.214616;0.162964;-0.963007;,
  -0.214588;0.162962;0.963014;,
  0.214616;0.162964;0.963007;,
  0.977007;0.125385;0.172442;,
  0.977007;0.125385;-0.172442;,
  -0.977001;0.125388;0.172471;,
  -0.977001;0.125388;-0.172471;,
  0.728207;0.166659;-0.664785;,
  0.728207;0.166659;0.664785;,
  -0.728167;0.166661;-0.664829;,
  -0.728167;0.166661;0.664829;,
  -0.211250;0.162763;-0.963785;,
  0.211263;0.162765;-0.963782;,
  -0.211251;0.162764;0.963785;,
  0.211264;0.162765;0.963782;,
  0.976455;0.125693;0.175319;,
  0.976455;0.125693;-0.175318;,
  -0.976452;0.125696;0.175334;,
  -0.976452;0.125696;-0.175334;,
  0.723858;0.166871;-0.669465;,
  0.723859;0.166872;0.669465;,
  -0.723838;0.166872;-0.669486;,
  -0.723839;0.166872;0.669486;,
  -0.213386;0.171929;-0.961721;,
  0.213386;0.171929;-0.961721;,
  -0.213388;0.171930;0.961720;,
  0.213388;0.171930;0.961720;,
  0.969918;0.172403;0.171863;,
  0.969918;0.172403;-0.171862;,
  -0.969918;0.172403;0.171863;,
  -0.969918;0.172403;-0.171862;,
  0.722153;0.199650;-0.662295;,
  0.722154;0.199650;0.662294;,
  -0.722153;0.199650;-0.662295;,
  -0.722154;0.199650;0.662294;,
  -0.894622;-0.446761;-0.007472;,
  -0.006479;-0.446714;0.894653;,
  0.894622;-0.446761;0.007472;;
  101;
  4;0,1,3,2;,
  4;8,9,11,10;,
  4;2,3,25,24;,
  4;24,25,5,4;,
  4;26,27,9,8;,
  4;6,7,27,26;,
  4;28,29,1,0;,
  4;14,15,29,28;,
  4;10,11,31,30;,
  4;30,31,13,12;,
  4;3,1,32,33;,
  4;33,32,16,18;,
  4;11,9,35,34;,
  4;34,35,19,17;,
  4;0,2,37,36;,
  4;36,37,23,21;,
  4;8,10,38,39;,
  4;39,38,20,22;,
  3;3,33,25;,
  3;33,18,41;,
  3;41,25,33;,
  3;25,41,5;,
  3;24,37,2;,
  3;45,23,37;,
  3;37,24,45;,
  3;4,45,24;,
  3;27,35,9;,
  3;40,19,35;,
  3;35,27,40;,
  3;7,40,27;,
  3;29,32,1;,
  3;43,16,32;,
  3;32,29,43;,
  3;15,43,29;,
  3;8,39,26;,
  3;39,22,44;,
  3;44,26,39;,
  3;26,44,6;,
  3;11,34,31;,
  3;34,17,42;,
  3;42,31,34;,
  3;31,42,13;,
  3;0,36,28;,
  3;36,21,47;,
  3;47,28,36;,
  3;28,47,14;,
  3;30,38,10;,
  3;46,20,38;,
  3;38,30,46;,
  3;12,46,30;,
  4;49,7,6,48;,
  4;51,50,12,13;,
  4;52,17,19,53;,
  4;54,55,22,20;,
  4;49,56,40,7;,
  4;56,53,19,40;,
  4;51,13,42,57;,
  4;57,42,17,52;,
  4;48,6,44,58;,
  4;58,44,22,55;,
  4;50,59,46,12;,
  4;59,54,20,46;,
  4;60,61,49,48;,
  4;63,62,50,51;,
  4;65,64,52,53;,
  4;66,67,55,54;,
  4;61,68,56,49;,
  4;68,65,53,56;,
  4;69,63,51,57;,
  4;64,69,57,52;,
  4;70,60,48,58;,
  4;67,70,58,55;,
  4;62,71,59,50;,
  4;71,66,54,59;,
  4;72,4,5,73;,
  4;72,73,61,60;,
  4;75,15,14,74;,
  4;75,74,62,63;,
  4;77,18,16,76;,
  4;77,76,64,65;,
  4;78,21,23,79;,
  4;78,79,67,66;,
  4;73,5,41,80;,
  4;73,80,68,61;,
  4;80,41,18,77;,
  4;80,77,65,68;,
  4;81,43,15,75;,
  4;81,75,63,69;,
  4;76,16,43,81;,
  4;76,81,69,64;,
  4;82,45,4,72;,
  4;82,72,60,70;,
  4;79,23,45,82;,
  4;79,82,70,67;,
  4;74,14,47,83;,
  4;74,83,71,62;,
  4;83,47,21,78;,
  4;83,78,66,71;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;;
 }
 MeshTextureCoords {
  138;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
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
  1.000000;0.815340;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.812760;,
  1.000000;0.184660;,
  0.000000;0.187240;,
  1.000000;0.000000;,
  0.815700;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.815700;1.000000;,
  0.187600;0.000000;,
  0.187600;1.000000;,
  0.000000;1.000000;,
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
  0.000000;0.668420;,
  1.000000;0.668420;,
  1.000000;0.331580;,
  0.000000;0.331580;,
  0.668420;1.000000;,
  0.668420;0.000000;,
  0.331580;0.000000;,
  0.331580;1.000000;,
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
  0.000000;0.515740;,
  1.000000;0.000000;,
  1.000000;0.515740;,
  1.000000;0.484260;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.484260;,
  0.515740;1.000000;,
  0.000000;1.000000;,
  0.515740;0.000000;,
  0.484260;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.484260;1.000000;,
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
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}