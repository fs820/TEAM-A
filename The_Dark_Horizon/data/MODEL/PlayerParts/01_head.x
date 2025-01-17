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
 142;
 0.00000;19.29966;-0.01608;,
 1.47103;18.90846;-2.30505;,
 0.00000;18.90846;-2.73698;,
 0.00000;19.29966;-0.01608;,
 2.47501;18.90846;-1.14638;,
 0.00000;19.29966;-0.01608;,
 2.69320;18.90846;0.37114;,
 0.00000;19.29966;-0.01608;,
 2.05631;18.90846;1.76572;,
 0.00000;19.29966;-0.01608;,
 0.76656;18.90846;2.59460;,
 0.00000;19.29966;-0.01608;,
 -0.76657;18.90846;2.59459;,
 0.00000;19.29966;-0.01608;,
 -2.05632;18.90846;1.76572;,
 0.00000;19.29966;-0.01608;,
 -2.69320;18.90846;0.37114;,
 0.00000;19.29966;-0.01608;,
 -2.47501;18.90846;-1.14638;,
 0.00000;19.29966;-0.01608;,
 -1.47103;18.90846;-2.30505;,
 0.00000;19.29966;-0.01608;,
 0.00000;18.90846;-2.73698;,
 2.82288;17.76654;-4.40857;,
 0.00000;17.76654;-5.23744;,
 4.74951;17.76654;-2.18511;,
 5.16821;17.76654;0.72699;,
 3.94604;17.76654;3.40318;,
 1.47103;17.76654;4.99377;,
 -1.47103;17.76654;4.99377;,
 -3.94604;17.76654;3.40318;,
 -5.16821;17.76654;0.72699;,
 -4.74951;17.76654;-2.18511;,
 -2.82288;17.76654;-4.40857;,
 0.00000;17.76654;-5.23744;,
 3.94604;15.96641;-6.15624;,
 0.00000;15.96641;-7.31490;,
 7.22453;15.96641;1.02265;,
 6.63924;15.96641;-3.04812;,
 5.51608;15.96641;4.76363;,
 2.05631;15.96641;6.98708;,
 -2.05632;15.96641;6.98708;,
 -5.51608;15.96641;4.76362;,
 -7.22453;15.96641;1.02264;,
 -6.63924;15.96641;-3.04812;,
 0.00000;15.96641;-7.31490;,
 -3.94604;15.96641;-6.15624;,
 4.74951;13.65390;-7.40647;,
 0.00000;13.65390;-8.80105;,
 7.99109;13.65390;-3.66549;,
 6.63924;13.65390;5.73685;,
 8.69555;13.65390;1.23415;,
 2.47501;13.65390;8.41303;,
 -2.47501;13.65390;8.41303;,
 -6.63924;13.65390;5.73685;,
 -8.69555;13.65390;1.23415;,
 -4.74951;13.65390;-7.40647;,
 -7.99109;13.65390;-3.66549;,
 0.00000;13.65390;-8.80105;,
 5.16821;11.01637;-8.05798;,
 0.00000;11.01637;-9.57550;,
 8.69555;11.01637;-3.98721;,
 9.46212;11.01637;1.34436;,
 7.22452;11.01637;6.24400;,
 2.69320;11.01637;9.15611;,
 -2.69320;11.01637;9.15611;,
 -7.22453;11.01637;6.24400;,
 -9.46212;11.01637;1.34436;,
 -8.69555;11.01637;-3.98721;,
 -5.16821;11.01637;-8.05798;,
 0.00000;11.01637;-9.57550;,
 5.16821;8.26751;-8.05798;,
 0.00000;8.26751;-9.57550;,
 8.69555;8.26751;-3.98721;,
 9.46212;8.26751;1.34436;,
 7.22452;8.26751;6.24400;,
 2.69320;8.26751;9.15611;,
 -2.69320;8.26751;9.15611;,
 -7.22453;8.26751;6.24400;,
 -9.46212;8.26751;1.34436;,
 -8.69555;8.26751;-3.98721;,
 -5.16821;8.26751;-8.05798;,
 0.00000;8.26751;-9.57550;,
 4.74951;5.62998;-7.40647;,
 0.00000;5.62998;-8.80105;,
 7.99109;5.62998;-3.66549;,
 8.69555;5.62998;1.23415;,
 6.63924;5.62998;5.73685;,
 2.47501;5.62998;8.41303;,
 -2.47501;5.62998;8.41303;,
 -6.63924;5.62998;5.73685;,
 -8.69555;5.62998;1.23415;,
 -7.99109;5.62998;-3.66549;,
 -4.74951;5.62998;-7.40647;,
 0.00000;5.62998;-8.80105;,
 3.94604;3.31749;-6.15624;,
 0.00000;3.31749;-7.31490;,
 6.63924;3.31749;-3.04812;,
 5.51608;3.31749;4.76363;,
 7.22452;3.31749;1.02265;,
 2.05631;3.31749;6.98708;,
 -2.05632;3.31749;6.98708;,
 -5.51608;3.31749;4.76362;,
 -7.22453;3.31749;1.02264;,
 -3.94604;3.31749;-6.15624;,
 -6.63924;3.31749;-3.04812;,
 0.00000;3.31749;-7.31490;,
 2.82288;1.51735;-4.40857;,
 0.00000;1.51735;-5.23744;,
 5.16821;1.51735;0.72699;,
 4.74951;1.51735;-2.18511;,
 3.94604;1.51735;3.40318;,
 1.47103;1.51735;4.99377;,
 -1.47103;1.51735;4.99377;,
 -3.94604;1.51735;3.40318;,
 -5.16821;1.51735;0.72699;,
 -4.74951;1.51735;-2.18511;,
 0.00000;1.51735;-5.23744;,
 -2.82288;1.51735;-4.40857;,
 1.47103;0.37543;-2.30505;,
 0.00000;0.37543;-2.73698;,
 2.47501;0.37543;-1.14638;,
 2.69320;0.37543;0.37114;,
 2.05631;0.37543;1.76572;,
 0.76656;0.37543;2.59460;,
 -0.76657;0.37543;2.59460;,
 -2.05632;0.37543;1.76572;,
 -2.69320;0.37543;0.37114;,
 -2.47501;0.37543;-1.14638;,
 -1.47103;0.37543;-2.30505;,
 0.00000;0.37543;-2.73698;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;,
 0.00000;-0.01577;-0.01608;;
 
 129;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 4;2,1,23,24;,
 4;1,4,25,23;,
 4;4,6,26,25;,
 4;6,8,27,26;,
 4;8,10,28,27;,
 4;10,12,29,28;,
 4;12,14,30,29;,
 4;14,16,31,30;,
 4;16,18,32,31;,
 4;18,20,33,32;,
 4;20,22,34,33;,
 4;24,23,35,36;,
 4;25,26,37,38;,
 4;26,27,39,37;,
 4;27,28,40,39;,
 4;28,29,41,40;,
 4;29,30,42,41;,
 4;30,31,43,42;,
 4;31,32,44,43;,
 4;33,34,45,46;,
 4;36,35,47,48;,
 4;35,38,49,47;,
 4;37,39,50,51;,
 4;39,40,52,50;,
 4;40,41,53,52;,
 4;41,42,54,53;,
 4;42,43,55,54;,
 4;44,46,56,57;,
 4;46,45,58,56;,
 4;48,47,59,60;,
 4;47,49,61,59;,
 4;49,51,62,61;,
 4;51,50,63,62;,
 4;50,52,64,63;,
 4;52,53,65,64;,
 4;53,54,66,65;,
 4;54,55,67,66;,
 4;55,57,68,67;,
 4;57,56,69,68;,
 4;56,58,70,69;,
 4;60,59,71,72;,
 4;59,61,73,71;,
 4;61,62,74,73;,
 4;62,63,75,74;,
 4;63,64,76,75;,
 4;64,65,77,76;,
 4;65,66,78,77;,
 4;66,67,79,78;,
 4;67,68,80,79;,
 4;68,69,81,80;,
 4;69,70,82,81;,
 4;72,71,83,84;,
 4;71,73,85,83;,
 4;73,74,86,85;,
 4;74,75,87,86;,
 4;75,76,88,87;,
 4;76,77,89,88;,
 4;77,78,90,89;,
 4;78,79,91,90;,
 4;79,80,92,91;,
 4;80,81,93,92;,
 4;81,82,94,93;,
 4;84,83,95,96;,
 4;83,85,97,95;,
 4;86,87,98,99;,
 4;87,88,100,98;,
 4;88,89,101,100;,
 4;89,90,102,101;,
 4;90,91,103,102;,
 4;92,93,104,105;,
 4;93,94,106,104;,
 4;96,95,107,108;,
 4;97,99,109,110;,
 4;99,98,111,109;,
 4;98,100,112,111;,
 4;100,101,113,112;,
 4;101,102,114,113;,
 4;102,103,115,114;,
 4;103,105,116,115;,
 4;104,106,117,118;,
 4;108,107,119,120;,
 4;107,110,121,119;,
 4;110,109,122,121;,
 4;109,111,123,122;,
 4;111,112,124,123;,
 4;112,113,125,124;,
 4;113,114,126,125;,
 4;114,115,127,126;,
 4;115,116,128,127;,
 4;116,118,129,128;,
 4;118,117,130,129;,
 3;120,119,131;,
 3;119,121,132;,
 3;121,122,133;,
 3;122,123,134;,
 3;123,124,135;,
 3;124,125,136;,
 3;125,126,137;,
 3;126,127,138;,
 3;127,128,139;,
 3;128,129,140;,
 3;129,130,141;,
 3;118,116,105;,
 3;118,105,104;,
 3;97,110,107;,
 3;97,107,95;,
 3;86,99,97;,
 3;86,97,85;,
 3;38,37,51;,
 3;38,51,49;,
 3;38,35,23;,
 3;38,23,25;,
 3;44,57,55;,
 3;44,55,43;,
 3;44,32,33;,
 3;44,33,46;,
 3;91,92,105;,
 3;91,105,103;;
 
 MeshMaterialList {
  3;
  129;
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
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
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
  0,
  1,
  0,
  1,
  0,
  0,
  1,
  0,
  1,
  1,
  0,
  0,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
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
   0.800000;0.000000;0.200800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  112;
  -0.000000;1.000000;0.000000;,
  0.000000;0.959625;-0.281282;,
  0.152073;0.959625;-0.236629;,
  0.255863;0.959625;-0.116848;,
  0.278418;0.959625;0.040030;,
  0.212578;0.959625;0.184200;,
  0.079246;0.959625;0.269887;,
  -0.079247;0.959625;0.269888;,
  -0.212578;0.959625;0.184200;,
  -0.278419;0.959625;0.040030;,
  -0.255863;0.959625;-0.116848;,
  -0.152073;0.959625;-0.236629;,
  0.000000;0.841672;-0.539989;,
  0.337192;0.825169;-0.453208;,
  0.491191;0.841672;-0.224319;,
  0.534492;0.841673;0.076848;,
  0.408096;0.841672;0.353617;,
  0.152132;0.841672;0.518116;,
  -0.152133;0.841672;0.518116;,
  -0.408097;0.841672;0.353617;,
  -0.534493;0.841672;0.076848;,
  -0.491191;0.841672;-0.224319;,
  -0.337192;0.825169;-0.453208;,
  0.000000;0.655482;-0.755211;,
  0.408298;0.655482;-0.635324;,
  0.690589;0.655457;-0.305717;,
  0.747524;0.655482;0.107477;,
  0.570750;0.655482;0.494558;,
  0.212767;0.655482;0.724620;,
  -0.212768;0.655482;0.724619;,
  -0.570750;0.655482;0.494558;,
  -0.747524;0.655482;0.107477;,
  -0.690589;0.655457;-0.305717;,
  -0.408298;0.655482;-0.635324;,
  0.000000;0.415975;-0.909376;,
  0.491646;0.415975;-0.765016;,
  0.827198;0.415974;-0.377769;,
  0.893930;0.441365;0.078016;,
  0.687261;0.415974;0.595515;,
  0.256201;0.415974;0.872540;,
  -0.256201;0.415974;0.872540;,
  -0.687261;0.415975;0.595515;,
  -0.893930;0.441365;0.078015;,
  -0.827198;0.415974;-0.377769;,
  -0.491646;0.415975;-0.765016;,
  0.000000;0.142540;-0.989789;,
  0.535120;0.142540;-0.832664;,
  0.900344;0.142540;-0.411173;,
  0.979714;0.142540;0.140862;,
  0.748033;0.142539;0.648174;,
  0.278856;0.142540;0.949696;,
  -0.278856;0.142540;0.949696;,
  -0.748033;0.142540;0.648174;,
  -0.979715;0.142540;0.140861;,
  -0.900344;0.142540;-0.411174;,
  -0.535120;0.142540;-0.832664;,
  0.000000;-0.142540;-0.989789;,
  0.535120;-0.142540;-0.832664;,
  0.900344;-0.142540;-0.411174;,
  0.979715;-0.142539;0.140862;,
  0.748033;-0.142539;0.648174;,
  0.278856;-0.142539;0.949696;,
  -0.278856;-0.142540;0.949696;,
  -0.748033;-0.142540;0.648174;,
  -0.979715;-0.142540;0.140861;,
  -0.900344;-0.142540;-0.411174;,
  -0.535120;-0.142540;-0.832664;,
  0.000000;-0.415977;-0.909375;,
  0.491645;-0.415977;-0.765015;,
  0.827197;-0.415976;-0.377768;,
  0.893928;-0.441368;0.078016;,
  0.687260;-0.415976;0.595515;,
  0.256200;-0.415976;0.872539;,
  -0.256200;-0.415977;0.872539;,
  -0.687260;-0.415977;0.595514;,
  -0.893929;-0.441368;0.078015;,
  -0.827197;-0.415976;-0.377768;,
  -0.491645;-0.415977;-0.765015;,
  0.000000;-0.655482;-0.755210;,
  0.408297;-0.655483;-0.635324;,
  0.690589;-0.655458;-0.305716;,
  0.747523;-0.655483;0.107478;,
  0.570750;-0.655483;0.494557;,
  0.212767;-0.655483;0.724619;,
  -0.212767;-0.655483;0.724619;,
  -0.570750;-0.655483;0.494557;,
  -0.747523;-0.655483;0.107477;,
  -0.690589;-0.655457;-0.305717;,
  -0.408297;-0.655483;-0.635324;,
  0.000000;-0.841671;-0.539991;,
  0.337193;-0.825168;-0.453209;,
  0.491193;-0.841671;-0.224319;,
  0.534494;-0.841671;0.076848;,
  0.408097;-0.841671;0.353618;,
  0.152133;-0.841671;0.518117;,
  -0.152133;-0.841671;0.518117;,
  -0.408098;-0.841671;0.353618;,
  -0.534494;-0.841671;0.076848;,
  -0.491192;-0.841671;-0.224319;,
  -0.337193;-0.825168;-0.453209;,
  0.000000;-0.959625;-0.281282;,
  0.152073;-0.959625;-0.236629;,
  0.255864;-0.959625;-0.116848;,
  0.278419;-0.959625;0.040031;,
  0.212579;-0.959625;0.184201;,
  0.079247;-0.959625;0.269888;,
  -0.079247;-0.959625;0.269888;,
  -0.212579;-0.959625;0.184200;,
  -0.278419;-0.959625;0.040030;,
  -0.255864;-0.959625;-0.116848;,
  -0.152073;-0.959625;-0.236629;,
  0.000000;-1.000000;0.000000;;
  129;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,1,11;,
  4;1,2,13,12;,
  4;2,3,14,13;,
  4;3,4,15,14;,
  4;4,5,16,15;,
  4;5,6,17,16;,
  4;6,7,18,17;,
  4;7,8,19,18;,
  4;8,9,20,19;,
  4;9,10,21,20;,
  4;10,11,22,21;,
  4;11,1,12,22;,
  4;12,13,24,23;,
  4;14,15,26,25;,
  4;15,16,27,26;,
  4;16,17,28,27;,
  4;17,18,29,28;,
  4;18,19,30,29;,
  4;19,20,31,30;,
  4;20,21,32,31;,
  4;22,12,23,33;,
  4;23,24,35,34;,
  4;24,25,36,35;,
  4;26,27,38,37;,
  4;27,28,39,38;,
  4;28,29,40,39;,
  4;29,30,41,40;,
  4;30,31,42,41;,
  4;32,33,44,43;,
  4;33,23,34,44;,
  4;34,35,46,45;,
  4;35,36,47,46;,
  4;36,37,48,47;,
  4;37,38,49,48;,
  4;38,39,50,49;,
  4;39,40,51,50;,
  4;40,41,52,51;,
  4;41,42,53,52;,
  4;42,43,54,53;,
  4;43,44,55,54;,
  4;44,34,45,55;,
  4;45,46,57,56;,
  4;46,47,58,57;,
  4;47,48,59,58;,
  4;48,49,60,59;,
  4;49,50,61,60;,
  4;50,51,62,61;,
  4;51,52,63,62;,
  4;52,53,64,63;,
  4;53,54,65,64;,
  4;54,55,66,65;,
  4;55,45,56,66;,
  4;56,57,68,67;,
  4;57,58,69,68;,
  4;58,59,70,69;,
  4;59,60,71,70;,
  4;60,61,72,71;,
  4;61,62,73,72;,
  4;62,63,74,73;,
  4;63,64,75,74;,
  4;64,65,76,75;,
  4;65,66,77,76;,
  4;66,56,67,77;,
  4;67,68,79,78;,
  4;68,69,80,79;,
  4;70,71,82,81;,
  4;71,72,83,82;,
  4;72,73,84,83;,
  4;73,74,85,84;,
  4;74,75,86,85;,
  4;76,77,88,87;,
  4;77,67,78,88;,
  4;78,79,90,89;,
  4;80,81,92,91;,
  4;81,82,93,92;,
  4;82,83,94,93;,
  4;83,84,95,94;,
  4;84,85,96,95;,
  4;85,86,97,96;,
  4;86,87,98,97;,
  4;88,78,89,99;,
  4;89,90,101,100;,
  4;90,91,102,101;,
  4;91,92,103,102;,
  4;92,93,104,103;,
  4;93,94,105,104;,
  4;94,95,106,105;,
  4;95,96,107,106;,
  4;96,97,108,107;,
  4;97,98,109,108;,
  4;98,99,110,109;,
  4;99,89,100,110;,
  3;100,101,111;,
  3;101,102,111;,
  3;102,103,111;,
  3;103,104,111;,
  3;104,105,111;,
  3;105,106,111;,
  3;106,107,111;,
  3;107,108,111;,
  3;108,109,111;,
  3;109,110,111;,
  3;110,100,111;,
  3;99,98,87;,
  3;99,87,88;,
  3;80,91,90;,
  3;80,90,79;,
  3;70,81,80;,
  3;70,80,69;,
  3;25,26,37;,
  3;25,37,36;,
  3;25,24,13;,
  3;25,13,14;,
  3;32,43,42;,
  3;32,42,31;,
  3;32,21,22;,
  3;32,22,33;,
  3;75,76,87;,
  3;75,87,86;;
 }
 MeshTextureCoords {
  142;
  0.045450;0.000000;,
  0.090910;0.090910;,
  0.000000;0.090910;,
  0.136360;0.000000;,
  0.181820;0.090910;,
  0.227270;0.000000;,
  0.272730;0.090910;,
  0.318180;0.000000;,
  0.363640;0.090910;,
  0.409090;0.000000;,
  0.454550;0.090910;,
  0.500000;0.000000;,
  0.545450;0.090910;,
  0.590910;0.000000;,
  0.636360;0.090910;,
  0.681820;0.000000;,
  0.727270;0.090910;,
  0.772730;0.000000;,
  0.818180;0.090910;,
  0.863640;0.000000;,
  0.909090;0.090910;,
  0.954550;0.000000;,
  1.000000;0.090910;,
  0.090910;0.181820;,
  0.000000;0.181820;,
  0.181820;0.181820;,
  0.272730;0.181820;,
  0.363640;0.181820;,
  0.454550;0.181820;,
  0.545450;0.181820;,
  0.636360;0.181820;,
  0.727270;0.181820;,
  0.818180;0.181820;,
  0.909090;0.181820;,
  1.000000;0.181820;,
  0.090910;0.272730;,
  0.000000;0.272730;,
  0.272730;0.272730;,
  0.181820;0.272730;,
  0.363640;0.272730;,
  0.454550;0.272730;,
  0.545450;0.272730;,
  0.636360;0.272730;,
  0.727270;0.272730;,
  0.818180;0.272730;,
  1.000000;0.272730;,
  0.909090;0.272730;,
  0.090910;0.363640;,
  0.000000;0.363640;,
  0.181820;0.363640;,
  0.363640;0.363640;,
  0.272730;0.363640;,
  0.454550;0.363640;,
  0.545450;0.363640;,
  0.636360;0.363640;,
  0.727270;0.363640;,
  0.909090;0.363640;,
  0.818180;0.363640;,
  1.000000;0.363640;,
  0.090910;0.454550;,
  0.000000;0.454550;,
  0.181820;0.454550;,
  0.272730;0.454550;,
  0.363640;0.454550;,
  0.454550;0.454550;,
  0.545450;0.454550;,
  0.636360;0.454550;,
  0.727270;0.454550;,
  0.818180;0.454550;,
  0.909090;0.454550;,
  1.000000;0.454550;,
  0.090910;0.545450;,
  0.000000;0.545450;,
  0.181820;0.545450;,
  0.272730;0.545450;,
  0.363640;0.545450;,
  0.454550;0.545450;,
  0.545450;0.545450;,
  0.636360;0.545450;,
  0.727270;0.545450;,
  0.818180;0.545450;,
  0.909090;0.545450;,
  1.000000;0.545450;,
  0.090910;0.636360;,
  0.000000;0.636360;,
  0.181820;0.636360;,
  0.272730;0.636360;,
  0.363640;0.636360;,
  0.454550;0.636360;,
  0.545450;0.636360;,
  0.636360;0.636360;,
  0.727270;0.636360;,
  0.818180;0.636360;,
  0.909090;0.636360;,
  1.000000;0.636360;,
  0.090910;0.727270;,
  0.000000;0.727270;,
  0.181820;0.727270;,
  0.363640;0.727270;,
  0.272730;0.727270;,
  0.454550;0.727270;,
  0.545450;0.727270;,
  0.636360;0.727270;,
  0.727270;0.727270;,
  0.909090;0.727270;,
  0.818180;0.727270;,
  1.000000;0.727270;,
  0.090910;0.818180;,
  0.000000;0.818180;,
  0.272730;0.818180;,
  0.181820;0.818180;,
  0.363640;0.818180;,
  0.454550;0.818180;,
  0.545450;0.818180;,
  0.636360;0.818180;,
  0.727270;0.818180;,
  0.818180;0.818180;,
  1.000000;0.818180;,
  0.909090;0.818180;,
  0.090910;0.909090;,
  0.000000;0.909090;,
  0.181820;0.909090;,
  0.272730;0.909090;,
  0.363640;0.909090;,
  0.454550;0.909090;,
  0.545450;0.909090;,
  0.636360;0.909090;,
  0.727270;0.909090;,
  0.818180;0.909090;,
  0.909090;0.909090;,
  1.000000;0.909090;,
  0.045450;1.000000;,
  0.136360;1.000000;,
  0.227270;1.000000;,
  0.318180;1.000000;,
  0.409090;1.000000;,
  0.500000;1.000000;,
  0.590910;1.000000;,
  0.681820;1.000000;,
  0.772730;1.000000;,
  0.863640;1.000000;,
  0.954550;1.000000;;
 }
}
