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
 0.00000;0.00000;0.00000;,
 -4.56091;-1.99213;-0.55780;,
 -6.91561;-2.45008;-0.50193;,
 -5.08342;1.15866;-0.47646;,
 -10.67379;-2.64625;-0.40143;,
 -7.93637;1.99893;-0.87869;,
 -14.04633;-2.49161;-0.30424;,
 -10.18233;2.34191;-0.80888;,
 -15.72783;-1.06622;-0.23916;,
 -11.35698;2.28305;-0.77741;,
 -14.01847;0.55204;-0.27236;,
 -12.34477;1.80781;-0.28038;,
 -13.69582;0.89383;-0.26213;,
 -4.95606;1.13248;3.16267;,
 -6.78380;-2.47718;3.26426;,
 -4.43075;-2.01889;3.16197;,
 0.10349;-0.02129;2.95728;,
 -7.77931;1.96666;3.60888;,
 -10.53993;-2.67379;3.42390;,
 -10.02450;2.30943;3.70116;,
 -13.91092;-2.51945;3.56492;,
 -11.19851;2.25044;3.75104;,
 -15.59214;-1.09414;3.63805;,
 -12.21303;1.78070;3.48399;,
 -13.88382;0.52434;3.57493;,
 -13.56251;0.86642;3.54708;;
 
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
  5;
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
   0.125490;0.000000;0.166275;1.000000;;
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
   0.696471;0.636863;0.461176;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.398431;0.567843;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.166275;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  30;
  0.037607;0.032021;-0.998779;,
  0.044273;-0.020364;-0.998812;,
  0.006653;-0.075260;-0.997142;,
  -0.045035;-0.073409;-0.996285;,
  -0.316326;0.303043;-0.898945;,
  -0.294783;0.349380;-0.889403;,
  -0.020886;0.021453;-0.999552;,
  -0.214556;0.206076;-0.954724;,
  0.042108;0.006797;0.999090;,
  0.068407;-0.024567;0.997355;,
  0.065082;-0.057560;0.996219;,
  0.030920;-0.056550;0.997921;,
  -0.185123;0.238308;0.953383;,
  -0.171873;0.269255;0.947608;,
  0.049012;0.007115;0.998773;,
  -0.104804;0.159707;0.981585;,
  0.252733;0.967534;-0.001884;,
  0.222299;0.974978;-0.000764;,
  0.217458;0.976069;-0.000588;,
  0.050857;0.998691;0.005410;,
  -0.241810;0.970201;0.015449;,
  -0.493794;0.869261;0.023540;,
  -0.647528;0.761522;0.028143;,
  -0.707389;0.706194;0.029841;,
  -0.686896;0.726166;0.029269;,
  -0.365605;-0.930750;0.006096;,
  -0.646141;-0.763026;0.017120;,
  0.002963;-0.999969;-0.007301;,
  0.121529;-0.992522;-0.011395;,
  0.190576;-0.981576;-0.013732;;
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