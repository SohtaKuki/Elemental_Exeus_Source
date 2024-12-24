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
 59;
 0.00000;0.00000;0.00000;,
 51.96153;-14.62329;-30.00000;,
 0.00000;-14.62329;-60.00000;,
 0.00000;0.00000;0.00000;,
 51.96153;-14.62329;30.00000;,
 0.00000;0.00000;0.00000;,
 -0.00001;-14.62329;60.00000;,
 0.00000;0.00000;0.00000;,
 -51.96153;-14.62329;29.99999;,
 0.00000;0.00000;0.00000;,
 -51.96153;-14.62329;-29.99999;,
 0.00000;0.00000;0.00000;,
 0.00000;-14.62329;-60.00000;,
 90.00000;-54.57524;-51.96152;,
 0.00000;-54.57524;-82.27999;,
 90.00000;-54.57524;51.96153;,
 -0.00001;-54.57524;103.92306;,
 -90.00001;-54.57524;51.96152;,
 -90.00001;-54.57524;-51.96152;,
 0.00000;-54.57524;-82.27999;,
 103.92306;-109.15054;-59.99999;,
 0.00000;-109.15054;-91.86492;,
 103.92305;-109.15054;60.00001;,
 -0.00001;-109.15054;120.00000;,
 -103.92306;-109.15054;59.99999;,
 -103.92306;-109.15054;-59.99999;,
 0.00000;-109.15054;-91.86492;,
 90.00000;-163.72577;-51.96152;,
 0.00000;-163.72577;-82.27998;,
 90.00000;-163.72577;51.96153;,
 -0.00001;-163.72577;103.92305;,
 -90.00001;-163.72577;51.96151;,
 -90.00000;-163.72577;-51.96152;,
 0.00000;-163.72577;-82.27998;,
 51.96153;-203.67771;-30.00000;,
 0.00000;-203.67771;-60.00001;,
 51.96153;-203.67771;30.00001;,
 -0.00001;-203.67771;60.00001;,
 -51.96154;-203.67771;30.00000;,
 -51.96154;-203.67771;-30.00000;,
 0.00000;-203.67771;-60.00001;,
 0.00000;-218.30108;-0.00000;,
 0.00000;-218.30108;-0.00000;,
 0.00000;-218.30108;-0.00000;,
 0.00000;-218.30108;-0.00000;,
 0.00000;-218.30108;-0.00000;,
 0.00000;-218.30108;-0.00000;,
 9.58870;-79.51021;-84.07573;,
 46.28001;-66.78135;-70.14396;,
 48.41373;-66.78135;-75.76340;,
 11.72241;-79.51021;-89.69517;,
 38.01620;-82.69241;-73.28175;,
 40.14993;-82.69241;-78.90118;,
 -10.87853;-79.51021;-88.81363;,
 -47.73193;-66.78135;-75.31647;,
 -45.66480;-66.78135;-69.67223;,
 -8.81139;-79.51021;-83.16940;,
 -39.43162;-82.69241;-78.35638;,
 -37.36448;-82.69241;-72.71214;;
 
 46;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 4;2,1,13,14;,
 4;1,4,15,13;,
 4;4,6,16,15;,
 4;6,8,17,16;,
 4;8,10,18,17;,
 4;10,12,19,18;,
 4;14,13,20,21;,
 4;13,15,22,20;,
 4;15,16,23,22;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 4;21,20,27,28;,
 4;20,22,29,27;,
 4;22,23,30,29;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;25,26,33,32;,
 4;28,27,34,35;,
 4;27,29,36,34;,
 4;29,30,37,36;,
 4;30,31,38,37;,
 4;31,32,39,38;,
 4;32,33,40,39;,
 3;35,34,41;,
 3;34,36,42;,
 3;36,37,43;,
 3;37,38,44;,
 3;38,39,45;,
 3;39,40,46;,
 4;47,48,49,50;,
 4;51,47,50,52;,
 4;48,51,52,49;,
 3;48,47,51;,
 3;49,52,50;,
 4;53,54,55,56;,
 4;57,53,56,58;,
 4;54,57,58,55;,
 3;54,53,57;,
 3;55,58,56;;
 
 MeshMaterialList {
  4;
  46;
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.517600;0.504800;0.423200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.784000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  46;
  -0.000000;1.000000;-0.000000;,
  -0.000000;0.833194;-0.552980;,
  0.408757;0.870162;-0.275200;,
  0.400528;0.886624;0.231245;,
  -0.000000;0.886624;0.462490;,
  -0.400529;0.886624;0.231245;,
  -0.408757;0.870162;-0.275200;,
  0.000000;0.394345;-0.918962;,
  0.702157;0.498520;-0.508383;,
  0.729817;0.538353;0.421360;,
  -0.000000;0.538353;0.842720;,
  -0.729817;0.538353;0.421360;,
  -0.702157;0.498520;-0.508383;,
  0.000000;-0.000000;-1.000000;,
  0.306285;-0.000000;-0.951940;,
  0.866025;-0.000000;0.500000;,
  -0.000000;-0.000000;1.000000;,
  -0.866025;-0.000000;0.500000;,
  -1.000000;-0.000000;-0.000000;,
  0.000000;-0.394345;-0.918962;,
  0.333033;-0.371834;-0.866503;,
  0.729816;-0.538353;0.421360;,
  -0.000000;-0.538353;0.842719;,
  -0.729816;-0.538353;0.421360;,
  -0.775750;-0.560653;-0.289620;,
  0.000000;-0.833194;-0.552981;,
  0.408758;-0.870162;-0.275200;,
  0.400529;-0.886624;0.231246;,
  -0.000000;-0.886624;0.462491;,
  -0.400529;-0.886624;0.231245;,
  -0.408758;-0.870162;-0.275200;,
  0.000000;-1.000000;0.000000;,
  -0.288414;0.951223;-0.109512;,
  -0.097304;-0.994569;-0.036947;,
  0.289688;0.951223;-0.106095;,
  0.097734;-0.994569;-0.035794;,
  1.000000;-0.000000;0.000000;,
  -0.306285;-0.000000;-0.951940;,
  0.875015;-0.484095;0.000000;,
  -0.300850;-0.187542;-0.935049;,
  0.817228;-0.485642;0.310306;,
  -0.354974;-0.000000;0.934876;,
  0.354975;-0.000001;-0.934876;,
  -0.820839;-0.485643;0.300623;,
  -0.343901;0.000001;-0.939006;,
  0.343901;-0.000000;0.939006;;
  46;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,6,12,11;,
  4;6,1,7,12;,
  4;7,8,14,13;,
  4;8,9,15,36;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,12,18,17;,
  4;12,7,13,37;,
  4;13,14,20,19;,
  4;36,15,21,38;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,18,24,23;,
  4;37,13,19,39;,
  4;19,20,26,25;,
  4;38,21,27,26;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,24,30,29;,
  4;24,19,25,30;,
  3;25,26,31;,
  3;26,27,31;,
  3;27,28,31;,
  3;28,29,31;,
  3;29,30,31;,
  3;30,25,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;40,40,40,40;,
  3;41,41,41;,
  3;42,42,42;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;43,43,43,43;,
  3;44,44,44;,
  3;45,45,45;;
 }
 MeshTextureCoords {
  59;
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
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