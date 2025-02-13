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
 26;
 0.00000;0.04978;0.00000;,
 -4.56091;-2.53999;-0.55780;,
 -6.91561;-3.13532;-0.50193;,
 -5.08342;1.55604;-0.47646;,
 -10.67379;-3.39034;-0.40143;,
 -7.93637;2.64839;-0.87869;,
 -14.04633;-3.18931;-0.30424;,
 -10.18233;3.09426;-0.80888;,
 -15.72783;-1.33630;-0.23916;,
 -11.35698;3.01775;-0.77741;,
 -14.01847;0.76743;-0.27236;,
 -12.34477;2.39993;-0.28038;,
 -13.69582;1.21176;-0.26213;,
 -4.95606;1.52201;3.16267;,
 -6.78380;-3.17055;3.26426;,
 -4.43075;-2.57477;3.16197;,
 0.10349;0.02210;2.95728;,
 -7.77931;2.60644;3.60888;,
 -10.53993;-3.42614;3.42390;,
 -10.02450;3.05204;3.70116;,
 -13.91092;-3.22550;3.56492;,
 -11.19851;2.97535;3.75104;,
 -15.59214;-1.37260;3.63805;,
 -12.21303;2.36469;3.48399;,
 -13.88382;0.73142;3.57493;,
 -13.56251;1.17613;3.54708;;
 
 24;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,8,10,12;,
 4;13,14,15,16;,
 4;17,18,14,13;,
 4;19,20,18,17;,
 4;21,22,20,19;,
 4;23,24,22,21;,
 4;25,24,22,23;,
 4;13,16,0,3;,
 4;17,13,3,5;,
 4;19,17,5,7;,
 4;21,19,7,9;,
 4;23,21,9,11;,
 4;25,23,11,12;,
 4;24,25,12,10;,
 4;10,8,22,24;,
 4;20,22,8,6;,
 4;18,20,6,4;,
 4;14,18,4,2;,
 4;15,14,2,1;;
 
 MeshMaterialList {
  6;
  24;
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
  30;
  0.037624;0.024638;-0.998988;,
  0.044266;-0.015686;-0.998897;,
  0.006639;-0.057963;-0.998297;,
  -0.045077;-0.056534;-0.997383;,
  -0.336397;0.253991;-0.906822;,
  -0.317084;0.290666;-0.902758;,
  -0.020947;0.016564;-0.999643;,
  -0.228761;0.172994;-0.957988;,
  0.042108;0.005228;0.999099;,
  0.068418;-0.018909;0.997478;,
  0.065119;-0.044308;0.996893;,
  0.030942;-0.043529;0.998573;,
  -0.196054;0.195339;0.960940;,
  -0.183560;0.219532;0.958181;,
  0.048996;0.005490;0.998784;,
  -0.112599;0.131170;0.984945;,
  0.321356;0.946955;-0.002390;,
  0.284185;0.958769;-0.000976;,
  0.277412;0.960751;-0.000724;,
  0.065603;0.997821;0.007042;,
  -0.301385;0.953304;0.019472;,
  -0.592442;0.805117;0.028269;,
  -0.739032;0.672902;0.032161;,
  -0.792557;0.608880;0.033436;,
  -0.775421;0.630580;0.033041;,
  -0.431825;-0.901933;0.006673;,
  -0.740059;-0.672256;0.019609;,
  0.003846;-0.999947;-0.009490;,
  0.156670;-0.987541;-0.014720;,
  0.244687;-0.969442;-0.017629;;
  24;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,7,4;,
  4;4,7,5,5;,
  4;5,7,5,6;,
  4;9,9,8,8;,
  4;10,10,9,9;,
  4;11,11,10,10;,
  4;12,15,11,11;,
  4;13,13,15,12;,
  4;14,13,15,13;,
  4;16,17,17,16;,
  4;18,16,16,18;,
  4;19,18,18,19;,
  4;20,19,19,20;,
  4;21,20,20,21;,
  4;22,21,21,22;,
  4;23,22,22,23;,
  4;23,24,24,23;,
  4;25,26,26,25;,
  4;27,25,25,27;,
  4;28,27,27,28;,
  4;29,28,28,29;;
 }
 MeshTextureCoords {
  26;
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
