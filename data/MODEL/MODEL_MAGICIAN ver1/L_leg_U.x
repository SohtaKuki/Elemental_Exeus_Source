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
 0.95460;0.00000;-0.95460;,
 0.00000;0.00000;-1.35000;,
 1.35000;0.00000;0.00000;,
 0.95460;0.00000;0.95460;,
 0.00000;0.00000;1.35000;,
 -0.95460;0.00000;0.95460;,
 -1.35000;0.00000;0.00000;,
 -0.95460;0.00000;-0.95460;,
 1.07637;-0.03426;-1.07637;,
 0.00000;-0.03426;-1.52221;,
 1.52220;-0.03426;-0.00000;,
 1.07637;-0.03426;1.07637;,
 0.00000;-0.03426;1.52222;,
 -1.07637;-0.03426;1.07637;,
 -1.52222;-0.03426;0.00000;,
 -1.07637;-0.03426;-1.07637;,
 1.17960;-0.13181;-1.17960;,
 0.00000;-0.13181;-1.66819;,
 1.66819;-0.13181;-0.00000;,
 1.17960;-0.13181;1.17960;,
 0.00000;-0.13181;1.66820;,
 -1.17960;-0.13181;1.17960;,
 -1.66820;-0.13181;0.00000;,
 -1.17960;-0.13181;-1.17960;,
 1.24857;-0.27780;-1.24857;,
 0.00000;-0.27780;-1.76574;,
 1.76574;-0.27780;-0.00000;,
 1.24857;-0.27780;1.24857;,
 0.00000;-0.27780;1.76574;,
 -1.24857;-0.27780;1.24857;,
 -1.76574;-0.27780;0.00000;,
 -1.24857;-0.27780;-1.24857;,
 1.27279;-0.45000;-1.27279;,
 0.00000;-0.45000;-1.80000;,
 1.80000;-0.45000;-0.00000;,
 1.27279;-0.45000;1.27280;,
 0.00000;-0.45000;1.80000;,
 -1.27280;-0.45000;1.27280;,
 -1.80000;-0.45000;0.00000;,
 -1.27280;-0.45000;-1.27279;,
 1.27279;-11.55000;-1.27279;,
 0.00000;-11.55000;-1.80000;,
 1.80000;-11.55000;-0.00000;,
 1.27279;-11.55000;1.27280;,
 0.00000;-11.55000;1.80000;,
 -1.27280;-11.55000;1.27280;,
 -1.80000;-11.55000;0.00000;,
 -1.27280;-11.55000;-1.27279;,
 1.24857;-11.72220;-1.24857;,
 0.00000;-11.72220;-1.76574;,
 1.76574;-11.72220;-0.00000;,
 1.24857;-11.72220;1.24857;,
 0.00000;-11.72220;1.76574;,
 -1.24857;-11.72220;1.24857;,
 -1.76574;-11.72220;0.00000;,
 -1.24857;-11.72220;-1.24857;,
 1.17960;-11.86820;-1.17960;,
 0.00000;-11.86820;-1.66819;,
 1.66819;-11.86820;-0.00000;,
 1.17960;-11.86820;1.17960;,
 0.00000;-11.86820;1.66820;,
 -1.17960;-11.86820;1.17960;,
 -1.66820;-11.86820;0.00000;,
 -1.17960;-11.86820;-1.17960;,
 1.07637;-11.96574;-1.07637;,
 0.00000;-11.96574;-1.52221;,
 1.52220;-11.96574;-0.00000;,
 1.07637;-11.96574;1.07637;,
 0.00000;-11.96574;1.52222;,
 -1.07637;-11.96574;1.07637;,
 -1.52222;-11.96574;0.00000;,
 -1.07637;-11.96574;-1.07637;,
 0.95460;-12.00000;-0.95460;,
 0.00000;-12.00000;-1.35000;,
 1.35000;-12.00000;-0.00000;,
 0.95460;-12.00000;0.95460;,
 0.00000;-12.00000;1.35000;,
 -0.95460;-12.00000;0.95460;,
 -1.35000;-12.00000;0.00000;,
 -0.95460;-12.00000;-0.95460;,
 0.00000;-12.00000;-0.00000;;
 
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
   0.580000;0.800000;0.671200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.800000;0.499200;1.000000;;
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
  0.000000;1.000000;0.000000;,
  0.000000;0.995199;-0.097869;,
  0.069206;0.995199;-0.069204;,
  0.097873;0.995199;0.000000;,
  0.069206;0.995199;0.069204;,
  0.000000;0.995199;0.097868;,
  -0.069203;0.995199;0.069203;,
  -0.097869;0.995199;-0.000000;,
  -0.069203;0.995199;-0.069203;,
  0.000000;0.924728;-0.380628;,
  0.269141;0.924731;-0.269141;,
  0.380621;0.924731;0.000000;,
  0.269141;0.924731;0.269140;,
  -0.000000;0.924729;0.380627;,
  -0.269143;0.924729;0.269143;,
  -0.380627;0.924729;0.000000;,
  -0.269143;0.924729;-0.269143;,
  0.000000;0.709209;-0.704999;,
  0.498504;0.709215;-0.498506;,
  0.704989;0.709218;-0.000000;,
  0.498504;0.709216;0.498505;,
  0.000000;0.709209;0.704998;,
  -0.498508;0.709211;0.498508;,
  -0.704998;0.709209;0.000000;,
  -0.498508;0.709211;-0.498508;,
  0.000000;0.384547;-0.923105;,
  0.652734;0.384548;-0.652734;,
  0.923105;0.384547;-0.000000;,
  0.652734;0.384548;0.652734;,
  0.000000;0.384547;0.923105;,
  -0.652734;0.384548;0.652734;,
  -0.923106;0.384546;-0.000000;,
  -0.652734;0.384548;-0.652734;,
  0.000000;0.098175;-0.995169;,
  0.703691;0.098175;-0.703691;,
  0.995169;0.098174;-0.000000;,
  0.703691;0.098175;0.703691;,
  0.000000;0.098174;0.995169;,
  -0.703691;0.098174;0.703691;,
  -0.995169;0.098174;-0.000000;,
  -0.703691;0.098175;-0.703691;,
  0.000000;-0.098174;-0.995169;,
  0.703691;-0.098174;-0.703691;,
  0.995169;-0.098173;-0.000000;,
  0.703691;-0.098173;0.703691;,
  0.000000;-0.098173;0.995169;,
  -0.703691;-0.098173;0.703691;,
  -0.995169;-0.098173;-0.000000;,
  -0.703691;-0.098174;-0.703691;,
  0.000000;-0.384549;-0.923105;,
  0.652733;-0.384549;-0.652733;,
  0.923105;-0.384548;-0.000000;,
  0.652733;-0.384549;0.652733;,
  0.000000;-0.384548;0.923105;,
  -0.652734;-0.384549;0.652734;,
  -0.923105;-0.384547;-0.000000;,
  -0.652734;-0.384549;-0.652734;,
  0.000000;-0.709213;-0.704994;,
  0.498501;-0.709220;-0.498502;,
  0.704985;-0.709222;-0.000000;,
  0.498501;-0.709220;0.498502;,
  -0.000000;-0.709214;0.704993;,
  -0.498505;-0.709215;0.498505;,
  -0.704994;-0.709214;0.000000;,
  -0.498505;-0.709215;-0.498505;,
  0.000000;-0.924729;-0.380626;,
  0.269140;-0.924731;-0.269140;,
  0.380620;-0.924731;-0.000000;,
  0.269140;-0.924731;0.269139;,
  -0.000000;-0.924729;0.380626;,
  -0.269142;-0.924730;0.269143;,
  -0.380626;-0.924729;0.000000;,
  -0.269142;-0.924730;-0.269142;,
  0.000000;-0.995199;-0.097871;,
  0.069207;-0.995199;-0.069206;,
  0.097875;-0.995199;-0.000000;,
  0.069207;-0.995199;0.069205;,
  -0.000000;-0.995199;0.097871;,
  -0.069205;-0.995199;0.069205;,
  -0.097871;-0.995199;0.000000;,
  -0.069205;-0.995199;-0.069205;,
  0.000000;-1.000000;-0.000000;;
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