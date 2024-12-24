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
 269;
 0.00000;0.00000;0.00000;,
 0.00000;7.20000;4.00000;,
 2.82843;0.00000;1.17157;,
 0.00000;7.20000;4.00000;,
 4.00000;0.00000;4.00000;,
 0.00000;7.20000;4.00000;,
 2.82843;0.00000;6.82843;,
 0.00000;7.20000;4.00000;,
 -0.00000;0.00000;8.00000;,
 0.00000;7.20000;4.00000;,
 -2.82843;0.00000;6.82843;,
 0.00000;7.20000;4.00000;,
 -4.00000;0.00000;4.00000;,
 0.00000;7.20000;4.00000;,
 -2.82843;0.00000;1.17157;,
 0.00000;7.20000;4.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;4.00000;,
 0.00000;0.00000;0.00000;,
 2.82843;0.00000;1.17157;,
 4.00000;0.00000;4.00000;,
 2.82843;0.00000;6.82843;,
 -0.00000;0.00000;8.00000;,
 -2.82843;0.00000;6.82843;,
 -4.00000;0.00000;4.00000;,
 -2.82843;0.00000;1.17157;,
 3.20000;1.88400;4.00000;,
 3.37574;2.30826;4.00000;,
 2.38701;2.30826;1.61299;,
 2.26274;1.88400;1.73726;,
 3.80000;2.48400;4.00000;,
 2.68701;2.48400;1.31299;,
 4.22426;2.30826;4.00000;,
 2.98701;2.30826;1.01299;,
 4.40000;1.88400;4.00000;,
 3.11127;1.88400;0.88873;,
 4.22426;1.45974;4.00000;,
 2.98701;1.45974;1.01299;,
 3.80000;1.28400;4.00000;,
 2.68701;1.28400;1.31299;,
 3.37574;1.45974;4.00000;,
 2.38701;1.45974;1.61299;,
 3.20000;1.88400;4.00000;,
 2.26274;1.88400;1.73726;,
 0.00000;2.30826;0.62426;,
 0.00000;1.88400;0.80000;,
 0.00000;2.48400;0.20000;,
 0.00000;2.30826;-0.22426;,
 -0.00000;1.88400;-0.40000;,
 0.00000;1.45974;-0.22426;,
 0.00000;1.28400;0.20000;,
 0.00000;1.45974;0.62426;,
 0.00000;1.88400;0.80000;,
 -2.38701;2.30826;1.61299;,
 -2.26274;1.88400;1.73726;,
 -2.68701;2.48400;1.31299;,
 -2.98701;2.30826;1.01299;,
 -3.11127;1.88400;0.88873;,
 -2.98701;1.45974;1.01299;,
 -2.68701;1.28400;1.31299;,
 -2.38701;1.45974;1.61299;,
 -2.26274;1.88400;1.73726;,
 -3.37574;2.30826;4.00000;,
 -3.20000;1.88400;4.00000;,
 -3.80000;2.48400;4.00000;,
 -4.22426;2.30826;4.00000;,
 -4.40000;1.88400;4.00000;,
 -4.22426;1.45974;4.00000;,
 -3.80000;1.28400;4.00000;,
 -3.37574;1.45974;4.00000;,
 -3.20000;1.88400;4.00000;,
 -2.38701;2.30826;6.38701;,
 -2.26274;1.88400;6.26274;,
 -2.68701;2.48400;6.68701;,
 -2.98701;2.30826;6.98701;,
 -3.11127;1.88400;7.11127;,
 -2.98701;1.45974;6.98701;,
 -2.68701;1.28400;6.68701;,
 -2.38701;1.45974;6.38701;,
 -2.26274;1.88400;6.26274;,
 0.00000;2.30826;7.37574;,
 0.00000;1.88400;7.20000;,
 0.00000;2.48400;7.80000;,
 0.00000;2.30826;8.22426;,
 0.00000;1.88400;8.40000;,
 0.00000;1.45974;8.22426;,
 0.00000;1.28400;7.80000;,
 0.00000;1.45974;7.37574;,
 0.00000;1.88400;7.20000;,
 2.38701;2.30826;6.38701;,
 2.26274;1.88400;6.26274;,
 2.68701;2.48400;6.68701;,
 2.98701;2.30826;6.98701;,
 3.11127;1.88400;7.11127;,
 2.98701;1.45974;6.98701;,
 2.68701;1.28400;6.68701;,
 2.38701;1.45974;6.38701;,
 2.26274;1.88400;6.26274;,
 3.37574;2.30826;4.00000;,
 3.20000;1.88400;4.00000;,
 3.80000;2.48400;4.00000;,
 4.22426;2.30826;4.00000;,
 4.40000;1.88400;4.00000;,
 4.22426;1.45974;4.00000;,
 3.80000;1.28400;4.00000;,
 3.37574;1.45974;4.00000;,
 3.20000;1.88400;4.00000;,
 3.21600;3.14000;4.00000;,
 3.39174;3.56427;4.00000;,
 2.40301;3.56427;1.61299;,
 2.27874;3.14000;1.73726;,
 3.81600;3.74000;4.00000;,
 2.70301;3.74000;1.31299;,
 4.24026;3.56427;4.00000;,
 3.00301;3.56427;1.01299;,
 4.41600;3.14000;4.00000;,
 3.12727;3.14000;0.88873;,
 4.24026;2.71574;4.00000;,
 3.00301;2.71574;1.01299;,
 3.81600;2.54000;4.00000;,
 2.70301;2.54000;1.31299;,
 3.39174;2.71574;4.00000;,
 2.40301;2.71574;1.61299;,
 3.21600;3.14000;4.00000;,
 2.27874;3.14000;1.73726;,
 0.01600;3.56427;0.62426;,
 0.01600;3.14000;0.80000;,
 0.01600;3.74000;0.20000;,
 0.01600;3.56427;-0.22426;,
 0.01600;3.14000;-0.40000;,
 0.01600;2.71574;-0.22426;,
 0.01600;2.54000;0.20000;,
 0.01600;2.71574;0.62426;,
 0.01600;3.14000;0.80000;,
 -2.37101;3.56427;1.61299;,
 -2.24674;3.14000;1.73726;,
 -2.67101;3.74000;1.31299;,
 -2.97101;3.56427;1.01299;,
 -3.09527;3.14000;0.88873;,
 -2.97101;2.71574;1.01299;,
 -2.67101;2.54000;1.31299;,
 -2.37101;2.71574;1.61299;,
 -2.24674;3.14000;1.73726;,
 -3.35974;3.56427;4.00000;,
 -3.18400;3.14000;4.00000;,
 -3.78400;3.74000;4.00000;,
 -4.20826;3.56427;4.00000;,
 -4.38400;3.14000;4.00000;,
 -4.20826;2.71574;4.00000;,
 -3.78400;2.54000;4.00000;,
 -3.35974;2.71574;4.00000;,
 -3.18400;3.14000;4.00000;,
 -2.37101;3.56427;6.38701;,
 -2.24674;3.14000;6.26274;,
 -2.67101;3.74000;6.68701;,
 -2.97101;3.56427;6.98701;,
 -3.09527;3.14000;7.11127;,
 -2.97101;2.71574;6.98701;,
 -2.67101;2.54000;6.68701;,
 -2.37101;2.71574;6.38701;,
 -2.24674;3.14000;6.26274;,
 0.01600;3.56427;7.37574;,
 0.01600;3.14000;7.20000;,
 0.01600;3.74000;7.80000;,
 0.01600;3.56427;8.22426;,
 0.01600;3.14000;8.40000;,
 0.01600;2.71574;8.22426;,
 0.01600;2.54000;7.80000;,
 0.01600;2.71574;7.37574;,
 0.01600;3.14000;7.20000;,
 2.40301;3.56427;6.38701;,
 2.27874;3.14000;6.26274;,
 2.70301;3.74000;6.68701;,
 3.00301;3.56427;6.98701;,
 3.12727;3.14000;7.11127;,
 3.00301;2.71574;6.98701;,
 2.70301;2.54000;6.68701;,
 2.40301;2.71574;6.38701;,
 2.27874;3.14000;6.26274;,
 3.39174;3.56427;4.00000;,
 3.21600;3.14000;4.00000;,
 3.81600;3.74000;4.00000;,
 4.24026;3.56427;4.00000;,
 4.41600;3.14000;4.00000;,
 4.24026;2.71574;4.00000;,
 3.81600;2.54000;4.00000;,
 3.39174;2.71574;4.00000;,
 3.21600;3.14000;4.00000;,
 3.21600;4.53200;4.00000;,
 3.39174;4.95627;4.00000;,
 2.40301;4.95627;1.61299;,
 2.27874;4.53200;1.73726;,
 3.81600;5.13200;4.00000;,
 2.70301;5.13200;1.31299;,
 4.24026;4.95627;4.00000;,
 3.00301;4.95627;1.01299;,
 4.41600;4.53200;4.00000;,
 3.12727;4.53200;0.88873;,
 4.24026;4.10774;4.00000;,
 3.00301;4.10774;1.01299;,
 3.81600;3.93200;4.00000;,
 2.70301;3.93200;1.31299;,
 3.39174;4.10774;4.00000;,
 2.40301;4.10774;1.61299;,
 3.21600;4.53200;4.00000;,
 2.27874;4.53200;1.73726;,
 0.01600;4.95627;0.62426;,
 0.01600;4.53200;0.80000;,
 0.01600;5.13200;0.20000;,
 0.01600;4.95627;-0.22426;,
 0.01600;4.53200;-0.40000;,
 0.01600;4.10774;-0.22426;,
 0.01600;3.93200;0.20000;,
 0.01600;4.10774;0.62426;,
 0.01600;4.53200;0.80000;,
 -2.37101;4.95627;1.61299;,
 -2.24674;4.53200;1.73726;,
 -2.67101;5.13200;1.31299;,
 -2.97101;4.95627;1.01299;,
 -3.09527;4.53200;0.88873;,
 -2.97101;4.10774;1.01299;,
 -2.67101;3.93200;1.31299;,
 -2.37101;4.10774;1.61299;,
 -2.24674;4.53200;1.73726;,
 -3.35974;4.95627;4.00000;,
 -3.18400;4.53200;4.00000;,
 -3.78400;5.13200;4.00000;,
 -4.20826;4.95627;4.00000;,
 -4.38400;4.53200;4.00000;,
 -4.20826;4.10774;4.00000;,
 -3.78400;3.93200;4.00000;,
 -3.35974;4.10774;4.00000;,
 -3.18400;4.53200;4.00000;,
 -2.37101;4.95627;6.38701;,
 -2.24674;4.53200;6.26274;,
 -2.67101;5.13200;6.68701;,
 -2.97101;4.95627;6.98701;,
 -3.09527;4.53200;7.11127;,
 -2.97101;4.10774;6.98701;,
 -2.67101;3.93200;6.68701;,
 -2.37101;4.10774;6.38701;,
 -2.24674;4.53200;6.26274;,
 0.01600;4.95627;7.37574;,
 0.01600;4.53200;7.20000;,
 0.01600;5.13200;7.80000;,
 0.01600;4.95627;8.22426;,
 0.01600;4.53200;8.40000;,
 0.01600;4.10774;8.22426;,
 0.01600;3.93200;7.80000;,
 0.01600;4.10774;7.37574;,
 0.01600;4.53200;7.20000;,
 2.40301;4.95627;6.38701;,
 2.27874;4.53200;6.26274;,
 2.70301;5.13200;6.68701;,
 3.00301;4.95627;6.98701;,
 3.12727;4.53200;7.11127;,
 3.00301;4.10774;6.98701;,
 2.70301;3.93200;6.68701;,
 2.40301;4.10774;6.38701;,
 2.27874;4.53200;6.26274;,
 3.39174;4.95627;4.00000;,
 3.21600;4.53200;4.00000;,
 3.81600;5.13200;4.00000;,
 4.24026;4.95627;4.00000;,
 4.41600;4.53200;4.00000;,
 4.24026;4.10774;4.00000;,
 3.81600;3.93200;4.00000;,
 3.39174;4.10774;4.00000;,
 3.21600;4.53200;4.00000;;
 
 208;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;10,11,12;,
 3;12,13,14;,
 3;14,15,16;,
 3;17,18,19;,
 3;17,19,20;,
 3;17,20,21;,
 3;17,21,22;,
 3;17,22,23;,
 3;17,23,24;,
 3;17,24,25;,
 3;17,25,18;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;29,28,44,45;,
 4;28,31,46,44;,
 4;31,33,47,46;,
 4;33,35,48,47;,
 4;35,37,49,48;,
 4;37,39,50,49;,
 4;39,41,51,50;,
 4;41,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;63,62,71,72;,
 4;62,64,73,71;,
 4;64,65,74,73;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;72,71,80,81;,
 4;71,73,82,80;,
 4;73,74,83,82;,
 4;74,75,84,83;,
 4;75,76,85,84;,
 4;76,77,86,85;,
 4;77,78,87,86;,
 4;78,79,88,87;,
 4;81,80,89,90;,
 4;80,82,91,89;,
 4;82,83,92,91;,
 4;83,84,93,92;,
 4;84,85,94,93;,
 4;85,86,95,94;,
 4;86,87,96,95;,
 4;87,88,97,96;,
 4;90,89,98,99;,
 4;89,91,100,98;,
 4;91,92,101,100;,
 4;92,93,102,101;,
 4;93,94,103,102;,
 4;94,95,104,103;,
 4;95,96,105,104;,
 4;96,97,106,105;,
 4;107,108,109,110;,
 4;108,111,112,109;,
 4;111,113,114,112;,
 4;113,115,116,114;,
 4;115,117,118,116;,
 4;117,119,120,118;,
 4;119,121,122,120;,
 4;121,123,124,122;,
 4;110,109,125,126;,
 4;109,112,127,125;,
 4;112,114,128,127;,
 4;114,116,129,128;,
 4;116,118,130,129;,
 4;118,120,131,130;,
 4;120,122,132,131;,
 4;122,124,133,132;,
 4;126,125,134,135;,
 4;125,127,136,134;,
 4;127,128,137,136;,
 4;128,129,138,137;,
 4;129,130,139,138;,
 4;130,131,140,139;,
 4;131,132,141,140;,
 4;132,133,142,141;,
 4;135,134,143,144;,
 4;134,136,145,143;,
 4;136,137,146,145;,
 4;137,138,147,146;,
 4;138,139,148,147;,
 4;139,140,149,148;,
 4;140,141,150,149;,
 4;141,142,151,150;,
 4;144,143,152,153;,
 4;143,145,154,152;,
 4;145,146,155,154;,
 4;146,147,156,155;,
 4;147,148,157,156;,
 4;148,149,158,157;,
 4;149,150,159,158;,
 4;150,151,160,159;,
 4;153,152,161,162;,
 4;152,154,163,161;,
 4;154,155,164,163;,
 4;155,156,165,164;,
 4;156,157,166,165;,
 4;157,158,167,166;,
 4;158,159,168,167;,
 4;159,160,169,168;,
 4;162,161,170,171;,
 4;161,163,172,170;,
 4;163,164,173,172;,
 4;164,165,174,173;,
 4;165,166,175,174;,
 4;166,167,176,175;,
 4;167,168,177,176;,
 4;168,169,178,177;,
 4;171,170,179,180;,
 4;170,172,181,179;,
 4;172,173,182,181;,
 4;173,174,183,182;,
 4;174,175,184,183;,
 4;175,176,185,184;,
 4;176,177,186,185;,
 4;177,178,187,186;,
 4;188,189,190,191;,
 4;189,192,193,190;,
 4;192,194,195,193;,
 4;194,196,197,195;,
 4;196,198,199,197;,
 4;198,200,201,199;,
 4;200,202,203,201;,
 4;202,204,205,203;,
 4;191,190,206,207;,
 4;190,193,208,206;,
 4;193,195,209,208;,
 4;195,197,210,209;,
 4;197,199,211,210;,
 4;199,201,212,211;,
 4;201,203,213,212;,
 4;203,205,214,213;,
 4;207,206,215,216;,
 4;206,208,217,215;,
 4;208,209,218,217;,
 4;209,210,219,218;,
 4;210,211,220,219;,
 4;211,212,221,220;,
 4;212,213,222,221;,
 4;213,214,223,222;,
 4;216,215,224,225;,
 4;215,217,226,224;,
 4;217,218,227,226;,
 4;218,219,228,227;,
 4;219,220,229,228;,
 4;220,221,230,229;,
 4;221,222,231,230;,
 4;222,223,232,231;,
 4;225,224,233,234;,
 4;224,226,235,233;,
 4;226,227,236,235;,
 4;227,228,237,236;,
 4;228,229,238,237;,
 4;229,230,239,238;,
 4;230,231,240,239;,
 4;231,232,241,240;,
 4;234,233,242,243;,
 4;233,235,244,242;,
 4;235,236,245,244;,
 4;236,237,246,245;,
 4;237,238,247,246;,
 4;238,239,248,247;,
 4;239,240,249,248;,
 4;240,241,250,249;,
 4;243,242,251,252;,
 4;242,244,253,251;,
 4;244,245,254,253;,
 4;245,246,255,254;,
 4;246,247,256,255;,
 4;247,248,257,256;,
 4;248,249,258,257;,
 4;249,250,259,258;,
 4;252,251,260,261;,
 4;251,253,262,260;,
 4;253,254,263,262;,
 4;254,255,264,263;,
 4;255,256,265,264;,
 4;256,257,266,265;,
 4;257,258,267,266;,
 4;258,259,268,267;;
 
 MeshMaterialList {
  6;
  208;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.131765;0.131765;0.131765;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\seamless-golden-background_115032-4953.jpg";
   }
  }
  Material {
   0.536471;0.536471;0.536471;1.000000;;
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
   0.752941;0.592941;0.015686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.229020;0.213333;0.401569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  125;
  -0.000000;0.485643;-0.874157;,
  0.618123;0.485643;-0.618123;,
  0.874157;0.485643;0.000000;,
  0.618123;0.485643;0.618123;,
  -0.000000;0.485643;0.874157;,
  -0.618123;0.485643;0.618122;,
  -0.874157;0.485643;-0.000000;,
  -0.618123;0.485643;-0.618123;,
  0.778932;0.537741;-0.322644;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;-0.000000;,
  -0.698872;0.715247;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.698872;0.715247;0.000000;,
  1.000000;0.000000;0.000000;,
  0.698872;-0.715247;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.698872;-0.715247;-0.000000;,
  -0.707107;0.000000;0.707107;,
  -0.494177;0.715247;0.494177;,
  -0.000000;1.000000;0.000000;,
  0.494177;0.715247;-0.494177;,
  0.707107;0.000000;-0.707107;,
  0.494177;-0.715247;-0.494177;,
  -0.000000;-1.000000;0.000000;,
  -0.494177;-0.715247;0.494177;,
  0.000000;0.000000;1.000000;,
  0.000000;0.715247;0.698872;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;0.715247;-0.698872;,
  0.000000;0.000000;-1.000000;,
  -0.000000;-0.715247;-0.698872;,
  -0.000000;-1.000000;-0.000000;,
  0.000000;-0.715247;0.698872;,
  0.707107;0.000000;0.707107;,
  0.494177;0.715247;0.494177;,
  -0.000000;1.000000;-0.000000;,
  -0.494177;0.715247;-0.494177;,
  -0.707107;0.000000;-0.707107;,
  -0.494177;-0.715247;-0.494177;,
  -0.000000;-1.000000;-0.000000;,
  0.494177;-0.715247;0.494177;,
  1.000000;0.000000;-0.000000;,
  0.698872;0.715247;-0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.698872;0.715247;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.698872;-0.715247;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.698872;-0.715247;-0.000000;,
  0.707107;0.000000;-0.707107;,
  0.494177;0.715247;-0.494177;,
  0.000000;1.000000;-0.000000;,
  -0.494177;0.715247;0.494177;,
  -0.707107;0.000000;0.707107;,
  -0.494177;-0.715247;0.494177;,
  0.000000;-1.000000;-0.000000;,
  0.494177;-0.715247;-0.494177;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.715247;-0.698872;,
  0.000000;1.000000;0.000000;,
  0.000000;0.715247;0.698872;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.715247;0.698872;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.715247;-0.698872;,
  -0.707107;0.000000;-0.707107;,
  -0.494177;0.715247;-0.494177;,
  0.000000;1.000000;0.000000;,
  0.494177;0.715247;0.494177;,
  0.707107;0.000000;0.707107;,
  0.494177;-0.715247;0.494177;,
  0.000000;-1.000000;0.000000;,
  -0.494177;-0.715247;-0.494177;,
  -1.000000;0.000000;-0.000000;,
  -0.698872;0.715247;-0.000000;,
  -0.698872;-0.715247;-0.000000;,
  -0.707107;0.000000;0.707107;,
  -0.494177;0.715247;0.494177;,
  0.494177;0.715247;-0.494177;,
  0.707107;0.000000;-0.707107;,
  -0.494177;-0.715247;0.494177;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.715247;0.698872;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;0.715247;-0.698872;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.715247;-0.698872;,
  -0.000000;-1.000000;-0.000000;,
  0.000000;-0.715247;0.698872;,
  0.707107;0.000000;0.707107;,
  0.494177;0.715247;0.494177;,
  0.000000;1.000000;0.000000;,
  -0.494177;0.715247;-0.494177;,
  -0.707107;0.000000;-0.707107;,
  -0.494177;-0.715247;-0.494177;,
  0.000000;-1.000000;0.000000;,
  0.494177;-0.715247;0.494177;,
  1.000000;0.000000;-0.000000;,
  0.698872;0.715247;-0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.698872;0.715247;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.698872;-0.715247;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.698872;-0.715247;-0.000000;,
  0.707107;0.000000;-0.707107;,
  0.494177;0.715247;-0.494177;,
  0.000000;1.000000;-0.000000;,
  -0.494177;0.715247;0.494177;,
  -0.494177;-0.715247;0.494177;,
  0.000000;-1.000000;-0.000000;,
  0.494177;-0.715247;-0.494177;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.715247;-0.698872;,
  0.000000;1.000000;0.000000;,
  0.000000;0.715247;0.698872;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.715247;0.698872;,
  0.000000;-1.000000;0.000000;,
  -0.000000;-0.715247;-0.698872;,
  -0.707107;0.000000;-0.707107;,
  -0.494177;0.715247;-0.494177;,
  -0.494177;-0.715247;-0.494177;,
  -0.322644;0.537741;0.778932;;
  208;
  3;0,8,1;,
  3;1,8,2;,
  3;2,8,3;,
  3;3,124,4;,
  3;4,124,5;,
  3;5,124,6;,
  3;6,7,7;,
  3;7,7,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,10,18,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,18,26,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,26,34,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,34,42,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,42,50,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,50,58,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,58,66,73;,
  4;66,67,11,10;,
  4;67,68,12,11;,
  4;68,69,13,12;,
  4;69,70,14,13;,
  4;70,71,15,14;,
  4;71,72,16,15;,
  4;72,73,17,16;,
  4;73,66,10,17;,
  4;74,75,78,77;,
  4;75,12,20,78;,
  4;12,13,79,20;,
  4;13,14,80,79;,
  4;14,15,23,80;,
  4;15,16,24,23;,
  4;16,76,81,24;,
  4;76,74,77,81;,
  4;77,78,83,82;,
  4;78,20,84,83;,
  4;20,79,85,84;,
  4;79,80,86,85;,
  4;80,23,87,86;,
  4;23,24,88,87;,
  4;24,81,89,88;,
  4;81,77,82,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,82,90,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,90,98,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,18,109;,
  4;102,103,110,18;,
  4;103,104,111,110;,
  4;104,105,112,111;,
  4;105,98,106,112;,
  4;106,107,114,113;,
  4;107,108,115,114;,
  4;108,109,116,115;,
  4;109,18,117,116;,
  4;18,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,106,113,120;,
  4;113,114,122,121;,
  4;114,115,68,122;,
  4;115,116,69,68;,
  4;116,117,70,69;,
  4;117,118,71,70;,
  4;118,119,72,71;,
  4;119,120,123,72;,
  4;120,113,121,123;,
  4;121,122,75,74;,
  4;122,68,12,75;,
  4;68,69,13,12;,
  4;69,70,14,13;,
  4;70,71,15,14;,
  4;71,72,16,15;,
  4;72,123,76,16;,
  4;123,121,74,76;,
  4;74,75,78,77;,
  4;75,12,20,78;,
  4;12,13,79,20;,
  4;13,14,80,79;,
  4;14,15,23,80;,
  4;15,16,24,23;,
  4;16,76,81,24;,
  4;76,74,77,81;,
  4;77,78,83,82;,
  4;78,20,84,83;,
  4;20,79,85,84;,
  4;79,80,86,85;,
  4;80,23,87,86;,
  4;23,24,88,87;,
  4;24,81,89,88;,
  4;81,77,82,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,82,90,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,90,98,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,18,109;,
  4;102,103,110,18;,
  4;103,104,111,110;,
  4;104,105,112,111;,
  4;105,98,106,112;,
  4;106,107,114,113;,
  4;107,108,115,114;,
  4;108,109,116,115;,
  4;109,18,117,116;,
  4;18,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,106,113,120;,
  4;113,114,122,121;,
  4;114,115,68,122;,
  4;115,116,69,68;,
  4;116,117,70,69;,
  4;117,118,71,70;,
  4;118,119,72,71;,
  4;119,120,123,72;,
  4;120,113,121,123;,
  4;121,122,75,74;,
  4;122,68,12,75;,
  4;68,69,13,12;,
  4;69,70,14,13;,
  4;70,71,15,14;,
  4;71,72,16,15;,
  4;72,123,76,16;,
  4;123,121,74,76;;
 }
 MeshTextureCoords {
  269;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
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
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;;
 }
}