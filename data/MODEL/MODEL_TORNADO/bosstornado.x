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
 76;
 -1.19500;134.37168;0.00000;,
 -1.19500;134.37168;-80.00000;,
 -57.76352;134.37168;-56.56856;,
 -81.19500;134.37168;0.00000;,
 -57.76352;134.37168;56.56856;,
 -1.19500;134.37168;80.00000;,
 55.37357;134.37168;56.56852;,
 78.80500;134.37168;0.00000;,
 55.37357;134.37168;-56.56852;,
 -1.19500;1.12263;0.00000;,
 -1.19500;1.12263;-36.00000;,
 24.26084;1.12263;-25.45584;,
 34.80500;1.12263;0.00000;,
 24.26084;1.12263;25.45584;,
 -1.19500;1.12263;36.00000;,
 -26.65084;1.12263;25.45584;,
 -37.19500;1.12263;0.00000;,
 -26.65084;1.12263;-25.45584;,
 -1.19500;10.45851;-18.04340;,
 -13.97228;10.51136;-12.77728;,
 -57.76352;134.37168;-56.56856;,
 -1.19500;134.37168;-80.00000;,
 -13.97228;10.51136;-12.77728;,
 -19.27576;10.53323;0.00000;,
 -81.19500;134.37168;0.00000;,
 -19.27576;10.53323;0.00000;,
 -13.97228;10.51132;12.77728;,
 -57.76352;134.37168;56.56856;,
 -13.97228;10.51132;12.77728;,
 -1.19500;10.45851;18.04340;,
 -1.19500;134.37168;80.00000;,
 -1.19500;10.45851;18.04340;,
 11.54500;10.40587;12.74000;,
 55.37357;134.37168;56.56852;,
 11.54500;10.40587;12.74000;,
 16.81120;10.38412;0.00000;,
 78.80500;134.37168;0.00000;,
 16.81120;10.38412;0.00000;,
 11.54500;10.40587;-12.74000;,
 55.37357;134.37168;-56.56852;,
 11.54500;10.40587;-12.74000;,
 -1.19500;10.45851;-18.04340;,
 -1.19500;134.37168;-80.00000;,
 -1.19500;20.95136;-13.69268;,
 -1.19500;33.12264;0.00000;,
 8.51912;20.91124;-9.71412;,
 24.26084;1.12263;-25.45584;,
 -1.19500;1.12263;-36.00000;,
 8.51912;20.91124;-9.71412;,
 -1.19500;33.12264;0.00000;,
 12.56168;20.89448;0.00000;,
 34.80500;1.12263;0.00000;,
 12.56168;20.89448;0.00000;,
 -1.19500;33.12264;0.00000;,
 8.51916;20.91119;9.71416;,
 24.26084;1.12263;25.45584;,
 8.51916;20.91119;9.71416;,
 -1.19500;33.12264;0.00000;,
 -1.19500;20.95136;13.69268;,
 -1.19500;1.12263;36.00000;,
 -1.19500;20.95136;13.69268;,
 -1.19500;33.12264;0.00000;,
 -10.84548;20.99120;9.65048;,
 -26.65084;1.12263;25.45584;,
 -10.84548;20.99120;9.65048;,
 -1.19500;33.12264;0.00000;,
 -14.82436;21.00768;0.00000;,
 -37.19500;1.12263;0.00000;,
 -14.82436;21.00768;0.00000;,
 -1.19500;33.12264;0.00000;,
 -10.84548;20.99124;-9.65048;,
 -26.65084;1.12263;-25.45584;,
 -10.84548;20.99124;-9.65048;,
 -1.19500;33.12264;0.00000;,
 -1.19500;20.95136;-13.69268;,
 -1.19500;1.12263;-36.00000;;
 
 40;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,5,6;,
 3;0,6,7;,
 3;0,7,8;,
 3;0,8,1;,
 3;9,10,11;,
 3;9,11,12;,
 3;9,12,13;,
 3;9,13,14;,
 3;9,14,15;,
 3;9,15,16;,
 3;9,16,17;,
 3;9,17,10;,
 4;18,19,20,21;,
 4;22,23,24,20;,
 4;25,26,27,24;,
 4;28,29,30,27;,
 4;31,32,33,30;,
 4;34,35,36,33;,
 4;37,38,39,36;,
 4;40,41,42,39;,
 3;43,44,45;,
 4;43,45,46,47;,
 3;48,49,50;,
 4;48,50,51,46;,
 3;52,53,54;,
 4;52,54,55,51;,
 3;56,57,58;,
 4;56,58,59,55;,
 3;60,61,62;,
 4;60,62,63,59;,
 3;64,65,66;,
 4;64,66,67,63;,
 3;68,69,70;,
 4;68,70,71,67;,
 3;72,73,74;,
 4;72,74,75,71;;
 
 MeshMaterialList {
  3;
  40;
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
   0.527200;0.690400;0.561600;0.600000;;
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
   0.436000;0.364000;0.731200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.532151;0.846649;-0.000000;,
  -0.000000;-0.447214;-0.894427;,
  -0.632455;-0.447214;-0.632456;,
  -0.894427;-0.447214;-0.000000;,
  -0.632455;-0.447214;0.632456;,
  0.000000;-0.447214;0.894427;,
  0.632456;-0.447214;0.632455;,
  0.894427;-0.447214;-0.000000;,
  0.632456;-0.447214;-0.632455;,
  -0.000000;0.747409;-0.664364;,
  0.469776;0.747410;-0.469776;,
  0.664364;0.747409;-0.000000;,
  0.469776;0.747410;0.469776;,
  -0.000001;0.747409;0.664364;,
  -0.469776;0.747409;0.469777;,
  -0.664364;0.747410;0.000001;,
  -0.469775;0.747409;-0.469777;,
  0.469776;0.747409;-0.469776;,
  -0.000000;0.747409;-0.664364;,
  0.664364;0.747409;-0.000000;,
  0.469776;0.747409;0.469776;,
  -0.000001;0.747409;0.664364;,
  -0.532152;0.846649;0.000001;,
  -0.469776;0.747409;0.469777;,
  -0.664364;0.747409;0.000001;,
  -0.469776;0.747409;-0.469777;;
  40;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,3,3,10;,
  3;11,2,12;,
  4;11,12,19,20;,
  3;12,2,13;,
  4;12,13,21,19;,
  3;13,2,14;,
  4;13,14,22,21;,
  3;14,2,15;,
  4;14,15,23,22;,
  3;15,24,16;,
  4;15,16,25,23;,
  3;16,24,17;,
  4;16,17,26,25;,
  3;17,24,18;,
  4;17,18,27,26;,
  3;18,24,11;,
  4;18,11,20,27;;
 }
 MeshTextureCoords {
  76;
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
  0.048400;0.225540;,
  0.076620;0.225870;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.125000;0.225870;,
  0.153250;0.226010;,
  0.250000;1.000000;,
  0.201630;0.226010;,
  0.229850;0.225870;,
  0.375000;1.000000;,
  0.278230;0.225870;,
  0.306390;0.225540;,
  0.500000;1.000000;,
  0.354790;0.225540;,
  0.382880;0.225210;,
  0.625000;1.000000;,
  0.431300;0.225210;,
  0.459400;0.225080;,
  0.750000;1.000000;,
  0.507840;0.225080;,
  0.536030;0.225210;,
  0.875000;1.000000;,
  0.584460;0.225210;,
  0.612770;0.225540;,
  1.000000;1.000000;,
  0.038730;0.380350;,
  0.062500;0.000000;,
  0.086350;0.381610;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.125000;0.381610;,
  0.125000;0.000000;,
  0.172770;0.382130;,
  0.250000;1.000000;,
  0.211380;0.382130;,
  0.187500;0.000000;,
  0.259050;0.381610;,
  0.375000;1.000000;,
  0.297700;0.381610;,
  0.250000;0.000000;,
  0.345090;0.380350;,
  0.500000;1.000000;,
  0.383820;0.380350;,
  0.312500;0.000000;,
  0.430970;0.379110;,
  0.625000;1.000000;,
  0.469780;0.379110;,
  0.375000;0.000000;,
  0.516970;0.378590;,
  0.750000;1.000000;,
  0.555810;0.378590;,
  0.437500;0.000000;,
  0.603360;0.379110;,
  0.875000;1.000000;,
  0.642170;0.379110;,
  0.500000;0.000000;,
  0.690180;0.380350;,
  1.000000;1.000000;;
 }
}