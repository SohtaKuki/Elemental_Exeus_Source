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
 92;
 50.00000;7.02326;-25.17632;,
 50.00000;7.02326;-30.00000;,
 50.00000;10.13200;-30.00000;,
 50.00000;10.13200;-25.17632;,
 -50.00000;6.59881;-25.17632;,
 -50.00000;10.13200;-25.17632;,
 -50.00000;10.13200;-30.00000;,
 -50.00000;6.59881;-30.00000;,
 50.00000;10.13200;24.81792;,
 50.00000;10.13200;30.00000;,
 50.00000;7.02326;30.00000;,
 50.00000;7.02326;24.81792;,
 -50.00000;6.59881;24.81792;,
 -50.00000;6.59881;30.00000;,
 -50.00000;10.13200;30.00000;,
 -50.00000;10.13200;24.81792;,
 50.00000;-67.04548;-30.00000;,
 50.00000;-67.04548;-25.17632;,
 50.00000;-69.86800;-25.17632;,
 50.00000;-69.86800;-30.00000;,
 -50.00000;-67.04548;-25.17632;,
 -50.00000;-67.04548;-30.00000;,
 -50.00000;-69.86800;-30.00000;,
 -50.00000;-69.86800;-25.17632;,
 50.00000;-67.04548;30.00000;,
 50.00000;-69.86800;30.00000;,
 50.00000;-69.86800;24.81792;,
 50.00000;-67.04548;24.81792;,
 -50.00000;-67.04548;30.00000;,
 -50.00000;-67.04548;24.81792;,
 -50.00000;-69.86800;24.81792;,
 -50.00000;-69.86800;30.00000;,
 -45.89138;6.63132;-30.00000;,
 -50.00000;6.59881;-30.00000;,
 -50.00000;10.13200;-30.00000;,
 -45.91041;10.13200;-30.00000;,
 -45.89137;6.63132;30.00000;,
 -45.91040;10.13200;30.00000;,
 -50.00000;10.13200;30.00000;,
 -50.00000;6.59881;30.00000;,
 -45.91041;10.13200;-30.00000;,
 -50.00000;10.13200;-30.00000;,
 -50.00000;10.13200;-25.17632;,
 -45.91041;10.13200;-25.17632;,
 -45.73642;-69.86800;-25.17632;,
 -50.00000;-69.86800;-25.17632;,
 -50.00000;-69.86800;-30.00000;,
 -45.73642;-69.86800;-30.00000;,
 -45.91040;10.13200;30.00000;,
 -45.91040;10.13200;24.81792;,
 -50.00000;10.13200;24.81792;,
 -45.73641;-69.86800;30.00000;,
 -50.00000;-69.86800;24.81792;,
 -45.73641;-69.86800;24.81792;,
 -45.73642;-69.86800;-30.00000;,
 -50.00000;-69.86800;-30.00000;,
 -50.00000;-67.04548;-30.00000;,
 -45.75409;-67.04548;-30.00000;,
 -45.73641;-69.86800;30.00000;,
 -45.75409;-67.04548;30.00000;,
 -50.00000;-67.04548;30.00000;,
 -50.00000;-69.86800;30.00000;,
 46.17742;10.13200;-30.00000;,
 50.00000;10.13200;-30.00000;,
 50.00000;7.02326;-30.00000;,
 46.21751;6.99228;-30.00000;,
 46.21751;6.99228;30.00000;,
 50.00000;7.02326;30.00000;,
 50.00000;10.13200;30.00000;,
 46.17742;10.13200;30.00000;,
 46.17742;10.13200;-25.17632;,
 50.00000;10.13200;-25.17632;,
 50.00000;10.13200;-30.00000;,
 46.17742;10.13200;-30.00000;,
 46.55747;-69.86800;-30.00000;,
 50.00000;-69.86800;-30.00000;,
 50.00000;-69.86800;-25.17632;,
 46.55747;-69.86800;-25.17632;,
 46.17742;10.13200;30.00000;,
 50.00000;10.13200;24.81792;,
 46.17742;10.13200;24.81792;,
 46.55746;-69.86800;24.81792;,
 50.00000;-69.86800;24.81792;,
 46.55746;-69.86800;30.00000;,
 46.51884;-67.04548;-30.00000;,
 50.00000;-67.04548;-30.00000;,
 50.00000;-69.86800;-30.00000;,
 46.55747;-69.86800;-30.00000;,
 46.55746;-69.86800;30.00000;,
 50.00000;-69.86800;30.00000;,
 50.00000;-67.04548;30.00000;,
 46.51884;-67.04548;30.00000;;
 
 54;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,0,3;,
 4;12,13,14,15;,
 4;12,15,5,4;,
 4;16,1,0,17;,
 4;16,17,18,19;,
 4;20,4,7,21;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;24,27,11,10;,
 4;27,26,18,17;,
 4;27,17,0,11;,
 4;28,13,12,29;,
 4;28,29,30,31;,
 4;29,12,4,20;,
 4;29,20,23,30;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,14;,
 4;49,43,42,50;,
 4;51,31,52,53;,
 4;53,52,45,44;,
 4;54,55,56,57;,
 4;57,56,33,32;,
 4;58,59,60,61;,
 4;59,36,39,60;,
 4;62,63,64,65;,
 4;62,65,32,35;,
 4;66,67,68,69;,
 4;66,69,37,36;,
 4;70,71,72,73;,
 4;70,73,40,43;,
 4;74,75,76,77;,
 4;74,77,44,47;,
 4;78,9,79,80;,
 4;78,80,49,48;,
 4;80,79,71,70;,
 4;80,70,43,49;,
 4;81,82,25,83;,
 4;81,83,51,53;,
 4;77,76,82,81;,
 4;77,81,53,44;,
 4;84,85,86,87;,
 4;84,87,54,57;,
 4;65,64,85,84;,
 4;65,84,57,32;,
 4;88,89,90,91;,
 4;88,91,59,58;,
 4;91,90,67,66;,
 4;91,66,36,59;;
 
 MeshMaterialList {
  2;
  54;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  0;;
  Material {
   0.436078;0.345098;0.800000;1.000000;;
   24.000000;
   0.460000;0.460000;0.460000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.150588;0.116078;0.345098;1.000000;;
   5.000000;
   0.800000;0.800000;0.800000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;;
  54;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;;
 }
 MeshTextureCoords {
  92;
  0.128520;0.105180;,
  0.000000;0.105180;,
  0.000000;0.000000;,
  0.128520;0.000000;,
  0.871480;0.109720;,
  0.871480;0.000000;,
  1.000000;0.000000;,
  1.000000;0.109720;,
  0.913630;0.000000;,
  1.000000;0.000000;,
  1.000000;0.105180;,
  0.913630;0.105180;,
  0.086370;0.109720;,
  0.000000;0.109720;,
  0.000000;0.000000;,
  0.086370;0.000000;,
  0.000000;0.898400;,
  0.128520;0.898400;,
  0.128520;1.000000;,
  0.000000;1.000000;,
  0.871480;0.898400;,
  1.000000;0.898400;,
  1.000000;1.000000;,
  0.871480;1.000000;,
  1.000000;0.898400;,
  1.000000;1.000000;,
  0.913630;1.000000;,
  0.913630;0.898400;,
  0.000000;0.898400;,
  0.086370;0.898400;,
  0.086370;1.000000;,
  0.000000;1.000000;,
  0.076530;0.109370;,
  0.000000;0.109720;,
  0.000000;0.000000;,
  0.076360;0.000000;,
  0.923470;0.109370;,
  0.923640;0.000000;,
  1.000000;0.000000;,
  1.000000;0.109720;,
  0.076360;1.000000;,
  0.000000;1.000000;,
  0.000000;0.871480;,
  0.076360;0.871480;,
  0.077960;0.128520;,
  0.000000;0.128520;,
  0.000000;0.000000;,
  0.077960;0.000000;,
  0.076360;0.000000;,
  0.076360;0.086370;,
  0.000000;0.086370;,
  0.077960;1.000000;,
  0.000000;0.913630;,
  0.077960;0.913630;,
  0.077960;1.000000;,
  0.000000;1.000000;,
  0.000000;0.898400;,
  0.077800;0.898400;,
  0.922040;1.000000;,
  0.922200;0.898400;,
  1.000000;0.898400;,
  1.000000;1.000000;,
  0.926600;0.000000;,
  1.000000;0.000000;,
  1.000000;0.105180;,
  0.926970;0.105510;,
  0.073030;0.105510;,
  0.000000;0.105180;,
  0.000000;0.000000;,
  0.073400;0.000000;,
  0.926600;0.871480;,
  1.000000;0.871480;,
  1.000000;1.000000;,
  0.926600;1.000000;,
  0.930110;0.000000;,
  1.000000;0.000000;,
  1.000000;0.128520;,
  0.930110;0.128520;,
  0.926600;0.000000;,
  1.000000;0.086370;,
  0.926600;0.086370;,
  0.930110;0.913630;,
  1.000000;0.913630;,
  0.930110;1.000000;,
  0.929760;0.898400;,
  1.000000;0.898400;,
  1.000000;1.000000;,
  0.930110;1.000000;,
  0.069890;1.000000;,
  0.000000;1.000000;,
  0.000000;0.898400;,
  0.070240;0.898400;;
 }
}
