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
 127;
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 7.19773;-0.03507;-4.15561;,
 8.31122;-0.03507;-0.00000;,
 0.00000;0.00000;0.00000;,
 4.15561;-0.03507;-7.19773;,
 0.00000;0.00000;0.00000;,
 0.00000;-0.03507;-8.31122;,
 0.00000;0.00000;0.00000;,
 -4.15561;-0.03507;-7.19773;,
 0.00000;0.00000;0.00000;,
 -7.19773;-0.03507;-4.15561;,
 0.00000;0.00000;0.00000;,
 -8.31122;-0.03507;0.00000;,
 0.00000;0.00000;0.00000;,
 -7.19773;-0.03507;4.15561;,
 0.00000;0.00000;0.00000;,
 -4.15561;-0.03507;7.19773;,
 0.00000;0.00000;0.00000;,
 0.00000;-0.03507;8.31122;,
 0.00000;0.00000;0.00000;,
 4.15561;-0.03507;7.19773;,
 0.00000;0.00000;0.00000;,
 7.19773;-0.03507;4.15561;,
 2.36887;2.79977;-1.36767;,
 2.73534;2.79977;0.00000;,
 1.36767;2.79977;-2.36887;,
 0.00000;2.79977;-2.73534;,
 -1.36767;2.79977;-2.36887;,
 -2.36887;2.79977;-1.36767;,
 -2.73534;2.79977;0.00000;,
 -2.36887;2.79977;1.36767;,
 -1.36767;2.79977;2.36887;,
 0.00000;2.79977;2.73534;,
 1.36767;2.79977;2.36887;,
 2.36887;2.79977;1.36767;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;13.28680;0.00000;,
 0.00000;3.04882;0.00000;,
 1.35299;2.66822;-1.35299;,
 0.00000;2.66822;-1.91342;,
 0.00000;3.04882;0.00000;,
 1.91342;2.66822;0.00000;,
 0.00000;3.04882;0.00000;,
 1.35299;2.66822;1.35299;,
 0.00000;3.04882;0.00000;,
 0.00000;2.66822;1.91342;,
 0.00000;3.04882;0.00000;,
 -1.35299;2.66822;1.35299;,
 0.00000;3.04882;0.00000;,
 -1.91342;2.66822;0.00000;,
 0.00000;3.04882;0.00000;,
 -1.35299;2.66822;-1.35299;,
 0.00000;3.04882;0.00000;,
 0.00000;2.66822;-1.91342;,
 2.50000;1.58435;-2.50000;,
 0.00000;1.58435;-3.53553;,
 3.53553;1.58435;0.00000;,
 2.50000;1.58435;2.50000;,
 0.00000;1.58435;3.53553;,
 -2.50000;1.58435;2.50000;,
 -3.53553;1.58435;0.00000;,
 -2.50000;1.58435;-2.50000;,
 0.00000;1.58435;-3.53553;,
 3.26641;-0.03777;-3.26641;,
 0.00000;-0.03777;-4.61940;,
 4.61940;-0.03777;-0.00000;,
 3.26641;-0.03777;3.26641;,
 0.00000;-0.03777;4.61940;,
 -3.26641;-0.03777;3.26641;,
 -4.61940;-0.03777;0.00000;,
 -3.26641;-0.03777;-3.26641;,
 0.00000;-0.03777;-4.61940;,
 3.53553;-1.95118;-3.53553;,
 0.00000;-1.95118;-5.00000;,
 5.00000;-1.95118;-0.00000;,
 3.53553;-1.95118;3.53553;,
 0.00000;-1.95118;5.00000;,
 -3.53553;-1.95118;3.53553;,
 -5.00000;-1.95118;0.00000;,
 -3.53553;-1.95118;-3.53553;,
 0.00000;-1.95118;-5.00000;,
 3.26641;-3.86460;-3.26641;,
 0.00000;-3.86460;-4.61940;,
 4.61940;-3.86460;-0.00000;,
 3.26641;-3.86460;3.26641;,
 0.00000;-3.86460;4.61940;,
 -3.26641;-3.86460;3.26641;,
 -4.61940;-3.86460;0.00000;,
 -3.26641;-3.86460;-3.26641;,
 0.00000;-3.86460;-4.61940;,
 2.50000;-5.48672;-2.50000;,
 0.00000;-5.48672;-3.53553;,
 3.53553;-5.48672;-0.00000;,
 2.50000;-5.48672;2.50000;,
 0.00000;-5.48672;3.53553;,
 -2.50000;-5.48672;2.50000;,
 -3.53553;-5.48672;0.00000;,
 -2.50000;-5.48672;-2.50000;,
 0.00000;-5.48672;-3.53553;,
 1.35299;-6.57058;-1.35299;,
 0.00000;-6.57058;-1.91342;,
 1.91342;-6.57058;-0.00000;,
 1.35299;-6.57058;1.35299;,
 0.00000;-6.57058;1.91342;,
 -1.35299;-6.57058;1.35299;,
 -1.91342;-6.57058;0.00000;,
 -1.35299;-6.57058;-1.35299;,
 0.00000;-6.57058;-1.91342;,
 0.00000;-6.95118;-0.00000;,
 0.00000;-6.95118;-0.00000;,
 0.00000;-6.95118;-0.00000;,
 0.00000;-6.95118;-0.00000;,
 0.00000;-6.95118;-0.00000;,
 0.00000;-6.95118;-0.00000;,
 0.00000;-6.95118;-0.00000;,
 0.00000;-6.95118;-0.00000;;
 
 136;
 4;0,1,2,3;,
 4;3,2,1,0;,
 4;1,4,5,2;,
 4;2,5,4,1;,
 4;4,6,7,5;,
 4;5,7,6,4;,
 4;6,8,9,7;,
 4;7,9,8,6;,
 4;8,10,11,9;,
 4;9,11,10,8;,
 4;10,12,13,11;,
 4;11,13,12,10;,
 4;12,14,15,13;,
 4;13,15,14,12;,
 4;14,16,17,15;,
 4;15,17,16,14;,
 4;16,18,19,17;,
 4;17,19,18,16;,
 4;18,20,21,19;,
 4;19,21,20,18;,
 4;20,22,23,21;,
 4;21,23,22,20;,
 4;22,0,3,23;,
 4;23,3,0,22;,
 4;3,2,24,25;,
 4;25,24,2,3;,
 4;2,5,26,24;,
 4;24,26,5,2;,
 4;5,7,27,26;,
 4;26,27,7,5;,
 4;7,9,28,27;,
 4;27,28,9,7;,
 4;9,11,29,28;,
 4;28,29,11,9;,
 4;11,13,30,29;,
 4;29,30,13,11;,
 4;13,15,31,30;,
 4;30,31,15,13;,
 4;15,17,32,31;,
 4;31,32,17,15;,
 4;17,19,33,32;,
 4;32,33,19,17;,
 4;19,21,34,33;,
 4;33,34,21,19;,
 4;21,23,35,34;,
 4;34,35,23,21;,
 4;23,3,25,35;,
 4;35,25,3,23;,
 4;25,24,36,37;,
 4;37,36,24,25;,
 4;24,26,38,36;,
 4;36,38,26,24;,
 4;26,27,39,38;,
 4;38,39,27,26;,
 4;27,28,40,39;,
 4;39,40,28,27;,
 4;28,29,41,40;,
 4;40,41,29,28;,
 4;29,30,42,41;,
 4;41,42,30,29;,
 4;30,31,43,42;,
 4;42,43,31,30;,
 4;31,32,44,43;,
 4;43,44,32,31;,
 4;32,33,45,44;,
 4;44,45,33,32;,
 4;33,34,46,45;,
 4;45,46,34,33;,
 4;34,35,47,46;,
 4;46,47,35,34;,
 4;35,25,37,47;,
 4;47,37,25,35;,
 3;48,49,50;,
 3;51,52,49;,
 3;53,54,52;,
 3;55,56,54;,
 3;57,58,56;,
 3;59,60,58;,
 3;61,62,60;,
 3;63,64,62;,
 4;50,49,65,66;,
 4;49,52,67,65;,
 4;52,54,68,67;,
 4;54,56,69,68;,
 4;56,58,70,69;,
 4;58,60,71,70;,
 4;60,62,72,71;,
 4;62,64,73,72;,
 4;66,65,74,75;,
 4;65,67,76,74;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;,
 4;71,72,81,80;,
 4;72,73,82,81;,
 4;75,74,83,84;,
 4;74,76,85,83;,
 4;76,77,86,85;,
 4;77,78,87,86;,
 4;78,79,88,87;,
 4;79,80,89,88;,
 4;80,81,90,89;,
 4;81,82,91,90;,
 4;84,83,92,93;,
 4;83,85,94,92;,
 4;85,86,95,94;,
 4;86,87,96,95;,
 4;87,88,97,96;,
 4;88,89,98,97;,
 4;89,90,99,98;,
 4;90,91,100,99;,
 4;93,92,101,102;,
 4;92,94,103,101;,
 4;94,95,104,103;,
 4;95,96,105,104;,
 4;96,97,106,105;,
 4;97,98,107,106;,
 4;98,99,108,107;,
 4;99,100,109,108;,
 4;102,101,110,111;,
 4;101,103,112,110;,
 4;103,104,113,112;,
 4;104,105,114,113;,
 4;105,106,115,114;,
 4;106,107,116,115;,
 4;107,108,117,116;,
 4;108,109,118,117;,
 3;111,110,119;,
 3;110,112,120;,
 3;112,113,121;,
 3;113,114,122;,
 3;114,115,123;,
 3;115,116,124;,
 3;116,117,125;,
 3;117,118,126;;
 
 MeshMaterialList {
  6;
  136;
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
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
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
  154;
  -0.004220;-0.999991;0.000000;,
  -0.003654;-0.999991;0.002110;,
  -0.002110;-0.999991;0.003654;,
  0.000000;-0.999991;0.004220;,
  0.002110;-0.999991;0.003654;,
  0.003654;-0.999991;0.002110;,
  0.004220;-0.999991;-0.000000;,
  0.003654;-0.999991;-0.002110;,
  0.002110;-0.999991;-0.003654;,
  0.000000;-0.999991;-0.004220;,
  -0.002110;-0.999991;-0.003654;,
  -0.003654;-0.999991;-0.002110;,
  -0.234222;-0.972183;0.000000;,
  -0.202842;-0.972183;0.117111;,
  -0.117111;-0.972183;0.202842;,
  0.000000;-0.972183;0.234222;,
  0.117111;-0.972183;0.202842;,
  0.202842;-0.972183;0.117111;,
  0.234222;-0.972183;-0.000000;,
  0.202842;-0.972183;-0.117111;,
  0.117111;-0.972183;-0.202842;,
  0.000000;-0.972183;-0.234222;,
  -0.117111;-0.972183;-0.202842;,
  -0.202842;-0.972183;-0.117111;,
  0.775390;0.631482;0.000000;,
  0.671507;0.631482;-0.387696;,
  0.387696;0.631482;-0.671507;,
  0.000000;0.631482;-0.775390;,
  -0.387696;0.631482;-0.671507;,
  -0.671507;0.631482;-0.387696;,
  -0.775390;0.631482;0.000000;,
  -0.671507;0.631482;0.387696;,
  -0.387696;0.631482;0.671507;,
  0.000000;0.631482;0.775390;,
  0.387696;0.631482;0.671507;,
  0.671507;0.631482;0.387696;,
  0.967626;0.252387;0.000000;,
  0.837988;0.252386;-0.483814;,
  0.483814;0.252386;-0.837988;,
  0.000000;0.252387;-0.967626;,
  -0.483814;0.252386;-0.837988;,
  -0.837988;0.252386;-0.483814;,
  -0.967626;0.252387;0.000000;,
  -0.837988;0.252386;0.483814;,
  -0.483814;0.252386;0.837988;,
  0.000000;0.252387;0.967626;,
  0.483814;0.252386;0.837988;,
  0.837988;0.252386;0.483814;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.924735;-0.380612;,
  0.269133;0.924735;-0.269133;,
  0.380612;0.924735;0.000000;,
  0.269133;0.924735;0.269133;,
  0.000000;0.924735;0.380612;,
  -0.269133;0.924735;0.269133;,
  -0.380612;0.924735;0.000000;,
  -0.269133;0.924735;-0.269133;,
  0.000000;0.709229;-0.704978;,
  0.498495;0.709229;-0.498495;,
  0.704978;0.709229;0.000000;,
  0.498495;0.709229;0.498495;,
  0.000000;0.709229;0.704978;,
  -0.498495;0.709229;0.498495;,
  -0.704978;0.709229;0.000000;,
  -0.498495;0.709229;-0.498495;,
  0.000000;0.384550;-0.923104;,
  0.652733;0.384550;-0.652733;,
  0.923104;0.384550;0.000000;,
  0.652733;0.384550;0.652733;,
  0.000000;0.384550;0.923104;,
  -0.652733;0.384550;0.652733;,
  -0.923104;0.384550;0.000000;,
  -0.652733;0.384550;-0.652733;,
  0.000000;0.000001;-1.000000;,
  0.707107;0.000001;-0.707107;,
  1.000000;0.000001;0.000000;,
  0.707107;0.000001;0.707107;,
  0.000000;0.000001;1.000000;,
  -0.707107;0.000001;0.707107;,
  -1.000000;0.000001;0.000000;,
  -0.707107;0.000001;-0.707107;,
  0.000000;-0.384550;-0.923104;,
  0.652733;-0.384550;-0.652733;,
  0.923104;-0.384550;-0.000000;,
  0.652733;-0.384550;0.652733;,
  0.000000;-0.384550;0.923104;,
  -0.652733;-0.384550;0.652733;,
  -0.923104;-0.384550;0.000000;,
  -0.652733;-0.384550;-0.652733;,
  0.000000;-0.709231;-0.704976;,
  0.498493;-0.709231;-0.498493;,
  0.704976;-0.709231;-0.000000;,
  0.498493;-0.709231;0.498493;,
  0.000000;-0.709231;0.704976;,
  -0.498493;-0.709231;0.498493;,
  -0.704976;-0.709231;0.000000;,
  -0.498493;-0.709231;-0.498493;,
  0.000000;-0.924736;-0.380610;,
  0.269132;-0.924736;-0.269132;,
  0.380610;-0.924736;-0.000000;,
  0.269132;-0.924736;0.269132;,
  0.000000;-0.924736;0.380610;,
  -0.269132;-0.924736;0.269132;,
  -0.380610;-0.924736;0.000000;,
  -0.269132;-0.924736;-0.269132;,
  0.000000;-1.000000;-0.000000;,
  0.234222;0.972183;0.000000;,
  0.202842;0.972183;-0.117111;,
  0.003654;0.999991;-0.002110;,
  0.004220;0.999991;0.000000;,
  0.117111;0.972183;-0.202842;,
  0.002110;0.999991;-0.003654;,
  0.000000;0.972183;-0.234222;,
  0.000000;0.999991;-0.004220;,
  -0.117111;0.972183;-0.202842;,
  -0.002110;0.999991;-0.003654;,
  -0.202842;0.972183;-0.117111;,
  -0.003654;0.999991;-0.002110;,
  -0.234222;0.972183;0.000000;,
  -0.004220;0.999991;0.000000;,
  -0.202842;0.972183;0.117111;,
  -0.003654;0.999991;0.002110;,
  -0.117111;0.972183;0.202842;,
  -0.002110;0.999991;0.003654;,
  0.000000;0.972183;0.234222;,
  0.000000;0.999991;0.004220;,
  0.117111;0.972183;0.202842;,
  0.002110;0.999991;0.003654;,
  0.202842;0.972183;0.117111;,
  0.003654;0.999991;0.002110;,
  -0.775390;-0.631482;0.000000;,
  -0.671507;-0.631482;0.387696;,
  -0.387696;-0.631482;0.671507;,
  0.000000;-0.631482;0.775390;,
  0.387696;-0.631482;0.671507;,
  0.671507;-0.631482;0.387696;,
  0.775390;-0.631482;-0.000000;,
  0.671507;-0.631482;-0.387696;,
  0.387696;-0.631482;-0.671507;,
  0.000000;-0.631482;-0.775390;,
  -0.387696;-0.631482;-0.671507;,
  -0.671507;-0.631482;-0.387696;,
  -0.967626;-0.252387;0.000000;,
  -0.837988;-0.252386;0.483814;,
  -0.483814;-0.252386;0.837988;,
  0.000000;-0.252387;0.967626;,
  0.483814;-0.252386;0.837988;,
  0.837988;-0.252386;0.483814;,
  0.967626;-0.252387;-0.000000;,
  0.837988;-0.252386;-0.483814;,
  0.483814;-0.252386;-0.837988;,
  0.000000;-0.252387;-0.967626;,
  -0.483814;-0.252386;-0.837988;,
  -0.837988;-0.252386;-0.483814;;
  136;
  4;0,1,13,12;,
  4;106,107,108,109;,
  4;1,2,14,13;,
  4;107,110,111,108;,
  4;2,3,15,14;,
  4;110,112,113,111;,
  4;3,4,16,15;,
  4;112,114,115,113;,
  4;4,5,17,16;,
  4;114,116,117,115;,
  4;5,6,18,17;,
  4;116,118,119,117;,
  4;6,7,19,18;,
  4;118,120,121,119;,
  4;7,8,20,19;,
  4;120,122,123,121;,
  4;8,9,21,20;,
  4;122,124,125,123;,
  4;9,10,22,21;,
  4;124,126,127,125;,
  4;10,11,23,22;,
  4;126,128,129,127;,
  4;11,0,12,23;,
  4;128,106,109,129;,
  4;106,107,25,24;,
  4;130,131,13,12;,
  4;107,110,26,25;,
  4;131,132,14,13;,
  4;110,112,27,26;,
  4;132,133,15,14;,
  4;112,114,28,27;,
  4;133,134,16,15;,
  4;114,116,29,28;,
  4;134,135,17,16;,
  4;116,118,30,29;,
  4;135,136,18,17;,
  4;118,120,31,30;,
  4;136,137,19,18;,
  4;120,122,32,31;,
  4;137,138,20,19;,
  4;122,124,33,32;,
  4;138,139,21,20;,
  4;124,126,34,33;,
  4;139,140,22,21;,
  4;126,128,35,34;,
  4;140,141,23,22;,
  4;128,106,24,35;,
  4;141,130,12,23;,
  4;24,25,37,36;,
  4;142,143,131,130;,
  4;25,26,38,37;,
  4;143,144,132,131;,
  4;26,27,39,38;,
  4;144,145,133,132;,
  4;27,28,40,39;,
  4;145,146,134,133;,
  4;28,29,41,40;,
  4;146,147,135,134;,
  4;29,30,42,41;,
  4;147,148,136,135;,
  4;30,31,43,42;,
  4;148,149,137,136;,
  4;31,32,44,43;,
  4;149,150,138,137;,
  4;32,33,45,44;,
  4;150,151,139,138;,
  4;33,34,46,45;,
  4;151,152,140,139;,
  4;34,35,47,46;,
  4;152,153,141,140;,
  4;35,24,36,47;,
  4;153,142,130,141;,
  3;48,50,49;,
  3;48,51,50;,
  3;48,52,51;,
  3;48,53,52;,
  3;48,54,53;,
  3;48,55,54;,
  3;48,56,55;,
  3;48,49,56;,
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
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,73,81,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,81,89,96;,
  4;89,90,98,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,89,97,104;,
  3;97,98,105;,
  3;98,99,105;,
  3;99,100,105;,
  3;100,101,105;,
  3;101,102,105;,
  3;102,103,105;,
  3;103,104,105;,
  3;104,97,105;;
 }
 MeshTextureCoords {
  127;
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
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}