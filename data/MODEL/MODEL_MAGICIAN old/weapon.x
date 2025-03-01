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
 52;
 0.56109;-19.49805;-0.00000;,
 2.59944;-43.68651;-0.00000;,
 1.54301;-43.48486;-0.00000;,
 0.70136;-32.40324;-0.00000;,
 1.83232;-19.35777;-0.00000;,
 2.00766;-11.98244;-0.00000;,
 0.14027;-12.06354;-0.00000;,
 2.11725;0.07234;0.00000;,
 0.00000;0.00000;0.00000;,
 2.16109;2.65863;0.00000;,
 -0.46904;2.83397;0.00000;,
 0.84602;3.97370;0.00000;,
 -1.25808;4.67507;0.00000;,
 3.73917;5.37644;0.00000;,
 1.63506;6.51616;0.00000;,
 3.65150;8.62027;0.00000;,
 0.32000;7.91890;0.00000;,
 -0.03069;9.84766;0.00000;,
 -2.83616;8.97095;0.00000;,
 -2.04712;11.68876;0.00000;,
 -0.90740;14.14355;0.00000;,
 -4.06356;11.77643;0.00000;,
 2.51177;16.24765;0.00000;,
 -1.78411;16.42300;0.00000;,
 -0.90757;14.14397;0.00000;,
 2.16109;13.44218;0.00000;,
 0.70136;-32.40324;2.81786;,
 1.54301;-43.48486;2.81786;,
 2.59944;-43.68651;2.81786;,
 0.56109;-19.49805;2.81786;,
 1.83232;-19.35777;2.81786;,
 0.14027;-12.06354;2.81786;,
 2.00766;-11.98244;2.81786;,
 0.00000;0.00000;2.81786;,
 2.11725;0.07234;2.81786;,
 -0.46904;2.83397;2.81786;,
 2.16109;2.65863;2.81786;,
 -1.25808;4.67507;2.81786;,
 0.84602;3.97370;2.81786;,
 1.63506;6.51616;2.81786;,
 3.73917;5.37644;2.81786;,
 0.32000;7.91890;2.81786;,
 3.65150;8.62027;2.81786;,
 -0.03069;9.84766;2.81786;,
 -2.04712;11.68876;2.81786;,
 -2.83616;8.97095;2.81786;,
 -4.06356;11.77643;2.81786;,
 -0.90740;14.14355;2.81786;,
 -1.78411;16.42300;2.81786;,
 2.51177;16.24765;2.81786;,
 2.16109;13.44218;2.81786;,
 -0.90757;14.14397;2.81786;;
 
 60;
 4;0,1,2,3;,
 4;4,1,2,0;,
 4;5,4,0,6;,
 4;7,5,6,8;,
 4;9,7,8,10;,
 4;11,9,10,12;,
 4;13,11,12,14;,
 4;15,13,14,16;,
 3;15,16,17;,
 4;18,19,17,16;,
 4;20,18,21,19;,
 4;22,20,21,23;,
 4;24,20,22,25;,
 4;26,27,28,29;,
 4;29,27,28,30;,
 4;31,29,30,32;,
 4;33,31,32,34;,
 4;35,33,34,36;,
 4;37,35,36,38;,
 4;39,37,38,40;,
 4;41,39,40,42;,
 3;43,41,42;,
 4;41,43,44,45;,
 4;44,46,45,47;,
 4;48,46,47,49;,
 4;50,49,47,51;,
 4;0,29,28,1;,
 4;1,28,27,2;,
 4;2,27,26,3;,
 4;3,26,29,0;,
 4;4,30,28,1;,
 4;1,28,27,2;,
 4;2,27,29,0;,
 4;5,32,30,4;,
 4;0,29,31,6;,
 4;7,34,32,5;,
 4;6,31,33,8;,
 4;9,36,34,7;,
 4;8,33,35,10;,
 4;11,38,36,9;,
 4;10,35,37,12;,
 4;13,40,38,11;,
 4;12,37,39,14;,
 4;15,42,40,13;,
 4;14,39,41,16;,
 4;17,43,42,15;,
 4;18,45,44,19;,
 4;19,44,43,17;,
 4;16,41,45,18;,
 4;20,47,45,18;,
 4;18,45,46,21;,
 4;21,46,44,19;,
 4;19,44,47,20;,
 4;20,47,46,21;,
 4;21,46,48,23;,
 4;23,48,49,22;,
 4;24,51,47,20;,
 4;22,49,50,25;,
 4;25,50,51,24;,
 3;47,46,44;;
 
 MeshMaterialList {
  5;
  60;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  39;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.996468;0.083972;0.000000;,
  0.998330;0.057764;0.000000;,
  -0.187497;-0.982265;0.000000;,
  -0.998298;-0.058326;0.000000;,
  -0.999061;-0.043323;0.000000;,
  -0.999348;-0.036101;0.000000;,
  0.999992;0.003876;0.000000;,
  0.999865;-0.016429;-0.000000;,
  -0.999419;-0.034079;0.000000;,
  0.999915;-0.013020;-0.000000;,
  -0.996146;-0.087710;0.000000;,
  0.927089;0.374840;0.000000;,
  -0.959815;-0.280634;0.000000;,
  0.707107;0.707107;0.000000;,
  -0.919146;-0.393918;0.000000;,
  0.436274;-0.899814;-0.000000;,
  -0.536876;0.843661;0.000000;,
  0.999635;0.027017;0.000000;,
  -0.729539;-0.683939;0.000000;,
  -0.539379;-0.842063;0.000000;,
  0.506278;0.862370;0.000000;,
  0.316226;0.948684;0.000000;,
  -0.997893;-0.064883;0.000000;,
  -0.936385;0.350975;0.000000;,
  0.381773;0.924256;0.000000;,
  -0.316227;-0.948684;0.000000;,
  0.953955;-0.299950;-0.000000;,
  0.936981;-0.349382;-0.000000;,
  -0.999762;0.021829;0.000000;,
  0.043436;0.999056;0.000000;,
  -0.907009;0.421110;0.000000;,
  0.600000;-0.800000;-0.000000;,
  -0.897789;0.440425;0.000000;,
  0.040784;0.999168;0.000000;,
  0.927197;0.374574;0.000000;,
  0.992278;-0.124033;-0.000000;,
  -0.222941;-0.974832;0.000000;;
  60;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  3;1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,3,3;,
  4;4,4,4,4;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;8,8,3,3;,
  4;4,4,4,4;,
  4;5,5,7,7;,
  4;9,9,8,8;,
  4;7,7,10,10;,
  4;11,11,9,9;,
  4;10,10,12,12;,
  4;13,13,11,11;,
  4;12,12,14,14;,
  4;15,15,13,13;,
  4;14,14,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,21,21;,
  4;22,22,23,23;,
  4;24,24,25,25;,
  4;26,26,22,22;,
  4;21,21,27,27;,
  4;28,28,29,29;,
  4;24,24,30,30;,
  4;31,31,26,26;,
  4;25,25,32,32;,
  4;28,28,33,33;,
  4;30,30,34,34;,
  4;35,35,35,35;,
  4;36,36,28,28;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  3;1,1,1;;
 }
 MeshTextureCoords {
  52;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
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
