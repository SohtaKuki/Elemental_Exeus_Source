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
 91;
 0.00000;0.00000;0.00000;,
 -6.76742;2.09993;3.38189;,
 -6.76742;-12.30007;2.48054;,
 0.00000;-12.30007;-0.00000;,
 -16.36742;2.09993;3.38189;,
 -16.36742;-12.30007;1.95955;,
 -25.96742;2.09993;3.38189;,
 -25.96742;-12.30007;2.09904;,
 -32.45712;-0.36414;0.82695;,
 -32.45712;-12.30007;0.82695;,
 -6.76742;-26.70007;2.48054;,
 0.00000;-26.70007;-0.00000;,
 -16.36742;-26.70007;1.95955;,
 -25.96742;-26.70007;2.09904;,
 -32.45712;-26.70007;0.82695;,
 -32.45712;-0.36414;0.82695;,
 -35.56743;-0.36414;-2.85254;,
 -35.56743;-12.30007;-2.85254;,
 -32.45712;-12.30007;0.82695;,
 -35.56743;-0.36414;-10.53254;,
 -35.56743;-12.30007;-10.53254;,
 -31.36272;-0.36414;-12.32678;,
 -31.36272;-12.30007;-12.32678;,
 -35.56743;-26.70007;-2.85254;,
 -32.45712;-26.70007;0.82695;,
 -34.44020;-26.70007;-10.53254;,
 -31.36272;-26.70007;-12.32678;,
 -31.36272;-0.36414;-12.32678;,
 -25.96743;2.09993;-15.89683;,
 -25.96743;-12.30007;-15.89683;,
 -31.36272;-12.30007;-12.32678;,
 -16.36742;2.09993;-15.89683;,
 -16.36742;-12.30007;-18.11040;,
 -6.76742;2.09993;-15.89683;,
 -6.76742;-12.30007;-15.89683;,
 -0.48499;0.00000;-13.26634;,
 -0.48499;-12.30007;-13.26634;,
 -25.96743;-26.70007;-15.89683;,
 -31.36272;-26.70007;-12.32678;,
 -16.36742;-26.70007;-18.11040;,
 -6.76742;-26.70007;-15.89683;,
 -0.48499;-26.70007;-13.26634;,
 -0.48499;0.00000;-13.26634;,
 2.83258;0.00000;-10.53255;,
 2.83258;-12.30007;-10.53255;,
 -0.48499;-12.30007;-13.26634;,
 2.83258;0.00000;-2.85254;,
 2.83258;-12.30007;-2.85254;,
 0.00000;0.00000;0.00000;,
 0.00000;-12.30007;-0.00000;,
 1.35370;-26.70007;-10.53255;,
 -0.48499;-26.70007;-13.26634;,
 2.83258;-26.70007;-2.85254;,
 0.00000;-26.70007;-0.00000;,
 -6.76742;2.09993;-15.89683;,
 -6.76742;2.09993;-10.53254;,
 2.83258;0.00000;-10.53255;,
 -16.36742;2.09993;-10.53254;,
 -25.96743;2.09993;-15.89683;,
 -25.96743;2.09993;-10.53254;,
 -35.56743;-0.36414;-10.53254;,
 -6.76742;2.09993;-2.85254;,
 2.83258;0.00000;-2.85254;,
 -16.36742;2.09993;-2.85254;,
 -25.96742;2.09993;-2.85254;,
 -35.56743;-0.36414;-2.85254;,
 -6.76742;2.09993;3.38189;,
 0.00000;0.00000;0.00000;,
 -16.36742;2.09993;3.38189;,
 -25.96742;2.09993;3.38189;,
 -32.45712;-0.36414;0.82695;,
 2.77258;-26.71332;-11.07130;,
 -6.63638;-26.71332;-11.07130;,
 -6.63638;-26.71332;-16.32883;,
 -0.47894;-26.71332;-13.75066;,
 -16.04534;-26.71332;-11.07130;,
 -16.04534;-26.71332;-18.39610;,
 -25.45431;-26.71332;-11.07130;,
 -25.45431;-26.71332;-16.32883;,
 -34.86327;-26.71332;-11.07129;,
 -30.74218;-26.71332;-12.82982;,
 2.77258;-26.71332;-2.68032;,
 -6.63638;-26.71332;-3.54413;,
 -16.04534;-26.71332;-3.54413;,
 -25.45430;-26.71332;-3.54413;,
 -35.81165;-26.71332;-2.94441;,
 -0.00365;-26.71332;0.40627;,
 -6.63638;-26.71332;2.56627;,
 -16.04534;-26.71332;2.56627;,
 -25.45430;-26.71332;2.56627;,
 -32.32484;-26.71332;1.36723;;
 
 52;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;5,7,13,12;,
 4;7,9,14,13;,
 4;15,16,17,18;,
 4;16,19,20,17;,
 4;19,21,22,20;,
 4;18,17,23,24;,
 4;17,20,25,23;,
 4;20,22,26,25;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;31,33,34,32;,
 4;33,35,36,34;,
 4;30,29,37,38;,
 4;29,32,39,37;,
 4;32,34,40,39;,
 4;34,36,41,40;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;46,48,49,47;,
 4;45,44,50,51;,
 4;44,47,52,50;,
 4;47,49,53,52;,
 4;42,54,55,56;,
 4;54,31,57,55;,
 4;31,58,59,57;,
 4;58,21,60,59;,
 4;56,55,61,62;,
 4;55,57,63,61;,
 4;57,59,64,63;,
 4;59,60,65,64;,
 4;62,61,66,67;,
 4;61,63,68,66;,
 4;63,64,69,68;,
 4;64,65,70,69;,
 4;71,72,73,74;,
 4;72,75,76,73;,
 4;75,77,78,76;,
 4;77,79,80,78;,
 4;81,82,72,71;,
 4;82,83,75,72;,
 4;83,84,77,75;,
 4;84,85,79,77;,
 4;86,87,82,81;,
 4;87,88,83,82;,
 4;88,89,84,83;,
 4;89,90,85,84;;
 
 MeshMaterialList {
  7;
  52;
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
   0.432800;0.432800;0.432800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.068800;0.068800;0.068800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.677600;0.652800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.040800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.354400;0.354400;0.354400;1.000000;;
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  62;
  0.559831;-0.014378;0.828482;,
  0.185164;-0.055556;0.981136;,
  -0.009876;-0.086948;0.996164;,
  -0.130614;-0.068391;0.989072;,
  0.549862;-0.007208;0.835224;,
  0.166660;-0.027759;0.985624;,
  -0.014873;-0.043525;0.998942;,
  -0.110048;-0.034147;0.993340;,
  0.539735;0.000000;0.841835;,
  0.148013;0.000000;0.988985;,
  -0.019843;0.000000;0.999803;,
  -0.089398;0.000000;0.995996;,
  -0.538943;-0.021945;0.842057;,
  -0.939070;0.000000;0.343726;,
  -1.000000;0.000000;0.000000;,
  -0.523023;-0.011042;0.852247;,
  -0.945048;-0.010389;0.326768;,
  -0.999151;-0.019387;-0.036350;,
  -0.506653;0.000000;0.862150;,
  -0.950695;-0.020923;0.309422;,
  -0.831007;-0.031117;-0.555391;,
  -0.474100;0.000000;-0.880471;,
  -0.341661;0.038465;-0.939036;,
  -0.000000;0.075225;-0.997167;,
  0.251875;0.037781;-0.967022;,
  -0.487762;-0.003858;-0.872968;,
  -0.368493;0.019122;-0.929434;,
  -0.000000;0.038007;-0.999277;,
  0.279476;0.018833;-0.959968;,
  -0.501268;-0.007707;-0.865258;,
  -0.394558;0.000000;-0.918871;,
  -0.000000;0.000000;-1.000000;,
  0.306557;0.000000;-0.951852;,
  0.516601;0.000000;-0.856226;,
  0.904417;0.000000;-0.426650;,
  0.924550;0.000000;0.381060;,
  0.547021;-0.008388;-0.837077;,
  0.909548;-0.022508;-0.414990;,
  0.933094;-0.013794;0.359368;,
  0.577093;-0.016878;-0.816504;,
  0.913871;-0.043945;-0.403619;,
  0.941114;-0.027872;0.336940;,
  0.120617;0.992184;-0.031965;,
  0.000000;1.000000;0.000000;,
  -0.146703;0.986935;-0.066621;,
  0.117961;0.992669;0.026327;,
  -0.138974;0.989950;0.026172;,
  0.000000;-1.000000;0.000000;,
  -0.392482;0.000000;-0.919760;,
  -0.420910;-0.007697;-0.907070;,
  0.264427;0.956046;-0.126705;,
  0.133690;0.988951;-0.064060;,
  0.239630;0.968785;-0.063504;,
  -0.167710;0.976693;-0.133958;,
  -0.327603;0.907857;-0.261672;,
  -0.290974;0.947562;-0.132137;,
  0.234378;0.970737;0.052309;,
  -0.275390;0.959933;0.051863;,
  0.128400;0.990319;0.052736;,
  0.254315;0.961465;0.104450;,
  -0.152603;0.986894;0.052460;,
  -0.301207;0.947920;0.103545;;
  52;
  4;0,1,5,4;,
  4;1,2,6,5;,
  4;2,3,7,6;,
  4;3,12,15,7;,
  4;4,5,9,8;,
  4;5,6,10,9;,
  4;6,7,11,10;,
  4;7,15,18,11;,
  4;12,13,16,15;,
  4;13,14,17,16;,
  4;48,21,25,49;,
  4;15,16,19,18;,
  4;16,17,20,19;,
  4;49,25,29,20;,
  4;21,22,26,25;,
  4;22,23,27,26;,
  4;23,24,28,27;,
  4;24,33,36,28;,
  4;25,26,30,29;,
  4;26,27,31,30;,
  4;27,28,32,31;,
  4;28,36,39,32;,
  4;33,34,37,36;,
  4;34,35,38,37;,
  4;35,0,4,38;,
  4;36,37,40,39;,
  4;37,38,41,40;,
  4;38,4,8,41;,
  4;50,51,42,52;,
  4;51,43,43,42;,
  4;43,53,44,43;,
  4;53,54,55,44;,
  4;52,42,45,56;,
  4;42,43,43,45;,
  4;43,44,46,43;,
  4;44,55,57,46;,
  4;56,45,58,59;,
  4;45,43,43,58;,
  4;43,46,60,43;,
  4;46,57,61,60;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;,
  4;47,47,47,47;;
 }
 MeshTextureCoords {
  91;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.250000;,
  0.000000;0.250000;,
  0.666670;0.000000;,
  0.666670;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.333330;0.500000;,
  0.000000;0.500000;,
  0.666670;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.250000;,
  0.000000;0.250000;,
  0.666670;0.000000;,
  0.666670;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.333330;0.500000;,
  0.000000;0.500000;,
  0.666670;0.500000;,
  1.000000;0.500000;,
  0.250000;0.000000;,
  0.250000;0.333330;,
  0.000000;0.333330;,
  0.500000;0.333330;,
  0.750000;0.000000;,
  0.750000;0.333330;,
  1.000000;0.333330;,
  0.250000;0.666670;,
  0.000000;0.666670;,
  0.500000;0.666670;,
  0.750000;0.666670;,
  1.000000;0.666670;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.250000;0.666670;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.666670;,
  0.500000;1.000000;,
  0.750000;0.666670;,
  0.750000;1.000000;,
  1.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;0.333330;,
  0.250000;0.333330;,
  0.500000;0.333330;,
  0.750000;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;;
 }
}
