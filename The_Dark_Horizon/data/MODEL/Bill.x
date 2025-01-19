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
 361;
 0.00000;226.70435;-21.55608;,
 24.33659;226.70435;-21.14193;,
 24.33659;199.03553;-21.14193;,
 0.00000;199.03553;-21.55608;,
 47.73788;226.70435;-19.91523;,
 47.73788;199.03553;-19.91523;,
 69.30482;226.70435;-17.92322;,
 69.30482;199.03553;-17.92322;,
 88.20801;226.70435;-15.24243;,
 88.20801;199.03553;-15.24243;,
 103.72185;226.70435;-11.97590;,
 103.72185;199.03553;-11.97590;,
 115.24961;226.70435;-8.24913;,
 115.24961;199.03553;-8.24913;,
 122.34835;226.70435;-4.20539;,
 122.34835;199.03553;-4.20539;,
 124.74503;226.70435;0.00000;,
 124.74503;199.03553;0.00000;,
 122.34835;226.70435;4.20539;,
 122.34835;199.03553;4.20539;,
 115.24962;226.70435;8.24913;,
 115.24962;199.03553;8.24913;,
 103.72185;226.70435;11.97590;,
 103.72185;199.03553;11.97590;,
 88.20801;226.70435;15.24243;,
 88.20801;199.03553;15.24243;,
 69.30471;226.70435;17.92322;,
 69.30471;199.03553;17.92322;,
 47.73788;226.70435;19.91523;,
 47.73788;199.03553;19.91523;,
 24.33659;226.70435;21.14193;,
 24.33659;199.03553;21.14193;,
 -0.00004;226.70435;21.55608;,
 -0.00004;199.03553;21.55608;,
 -24.33666;226.70435;21.14193;,
 -24.33666;199.03553;21.14193;,
 -47.73792;226.70435;19.91523;,
 -47.73792;199.03553;19.91523;,
 -69.30489;226.70435;17.92322;,
 -69.30489;199.03553;17.92322;,
 -88.20837;226.70435;15.24243;,
 -88.20837;199.03553;15.24243;,
 -103.72185;226.70435;11.97590;,
 -103.72185;199.03553;11.97590;,
 -115.24962;226.70435;8.24913;,
 -115.24962;199.03553;8.24913;,
 -122.34835;226.70435;4.20534;,
 -122.34835;199.03553;4.20534;,
 -124.74503;226.70435;-0.00004;,
 -124.74503;199.03553;-0.00004;,
 -122.34835;226.70435;-4.20539;,
 -122.34835;199.03553;-4.20539;,
 -115.24961;226.70435;-8.24918;,
 -115.24961;199.03553;-8.24918;,
 -103.72185;226.70435;-11.97596;,
 -103.72185;199.03553;-11.97596;,
 -88.20801;226.70435;-15.24248;,
 -88.20801;199.03553;-15.24248;,
 -69.30463;226.70435;-17.92324;,
 -69.30463;199.03553;-17.92324;,
 -47.73782;226.70435;-19.91523;,
 -47.73782;199.03553;-19.91523;,
 -24.33635;226.70435;-21.14193;,
 -24.33635;199.03553;-21.14193;,
 0.00000;226.70435;-21.55608;,
 0.00000;199.03553;-21.55608;,
 24.33659;171.36756;-21.14193;,
 0.00000;171.36756;-21.55608;,
 47.73788;171.36756;-19.91523;,
 69.30482;171.36756;-17.92322;,
 88.20801;171.36756;-15.24243;,
 103.72185;171.36756;-11.97590;,
 115.24961;171.36756;-8.24913;,
 122.34835;171.36756;-4.20539;,
 124.74503;171.36756;0.00000;,
 122.34835;171.36756;4.20539;,
 115.24962;171.36756;8.24913;,
 103.72185;171.36756;11.97590;,
 88.20801;171.36756;15.24243;,
 69.30471;171.36756;17.92322;,
 47.73788;171.36756;19.91523;,
 24.33659;171.36756;21.14193;,
 -0.00004;171.36756;21.55608;,
 -24.33666;171.36756;21.14193;,
 -47.73792;171.36756;19.91523;,
 -69.30489;171.36756;17.92322;,
 -88.20837;171.36756;15.24243;,
 -103.72185;171.36756;11.97590;,
 -115.24962;171.36756;8.24913;,
 -122.34835;171.36756;4.20534;,
 -124.74503;171.36756;-0.00004;,
 -122.34835;171.36756;-4.20539;,
 -115.24961;171.36756;-8.24918;,
 -103.72185;171.36756;-11.97596;,
 -88.20801;171.36756;-15.24248;,
 -69.30463;171.36756;-17.92324;,
 -47.73782;171.36756;-19.91523;,
 -24.33635;171.36756;-21.14193;,
 0.00000;171.36756;-21.55608;,
 24.33659;143.69944;-21.14193;,
 0.00000;143.69944;-21.55608;,
 47.73788;143.69944;-19.91523;,
 69.30482;143.69944;-17.92322;,
 88.20801;143.69944;-15.24243;,
 103.72185;143.69944;-11.97590;,
 115.24961;143.69944;-8.24913;,
 122.34835;143.69944;-4.20539;,
 124.74503;143.69944;0.00000;,
 122.34835;143.69944;4.20539;,
 115.24962;143.69944;8.24913;,
 103.72185;143.69944;11.97590;,
 88.20801;143.69944;15.24243;,
 69.30471;143.69944;17.92322;,
 47.73788;143.69944;19.91523;,
 24.33659;143.69944;21.14193;,
 -0.00004;143.69944;21.55608;,
 -24.33666;143.69944;21.14193;,
 -47.73792;143.69944;19.91523;,
 -69.30489;143.69944;17.92322;,
 -88.20837;143.69944;15.24243;,
 -103.72185;143.69944;11.97590;,
 -115.24962;143.69944;8.24913;,
 -122.34835;143.69944;4.20534;,
 -124.74503;143.69944;-0.00004;,
 -122.34835;143.69944;-4.20539;,
 -115.24961;143.69944;-8.24918;,
 -103.72185;143.69944;-11.97596;,
 -88.20801;143.69944;-15.24248;,
 -69.30463;143.69944;-17.92324;,
 -47.73782;143.69944;-19.91523;,
 -24.33635;143.69944;-21.14193;,
 0.00000;143.69944;-21.55608;,
 24.33659;116.03106;-21.14193;,
 0.00000;116.03106;-21.55608;,
 47.73788;116.03106;-19.91523;,
 69.30482;116.03106;-17.92322;,
 88.20801;116.03106;-15.24243;,
 103.72185;116.03106;-11.97590;,
 115.24961;116.03106;-8.24913;,
 122.34835;116.03106;-4.20539;,
 124.74503;116.03106;0.00000;,
 122.34835;116.03106;4.20539;,
 115.24962;116.03106;8.24913;,
 103.72185;116.03106;11.97590;,
 88.20801;116.03106;15.24243;,
 69.30471;116.03106;17.92322;,
 47.73788;116.03106;19.91523;,
 24.33659;116.03106;21.14193;,
 -0.00004;116.03106;21.55608;,
 -24.33666;116.03106;21.14193;,
 -47.73792;116.03106;19.91523;,
 -69.30489;116.03106;17.92322;,
 -88.20837;116.03106;15.24243;,
 -103.72185;116.03106;11.97590;,
 -115.24962;116.03106;8.24913;,
 -122.34835;116.03106;4.20534;,
 -124.74503;116.03106;-0.00004;,
 -122.34835;116.03106;-4.20539;,
 -115.24961;116.03106;-8.24918;,
 -103.72185;116.03106;-11.97596;,
 -88.20801;116.03106;-15.24248;,
 -69.30463;116.03106;-17.92324;,
 -47.73782;116.03106;-19.91523;,
 -24.33635;116.03106;-21.14193;,
 0.00000;116.03106;-21.55608;,
 24.33659;88.36328;-21.14193;,
 0.00000;88.36328;-21.55608;,
 47.73788;88.36328;-19.91523;,
 69.30482;88.36328;-17.92322;,
 88.20801;88.36328;-15.24243;,
 103.72185;88.36328;-11.97590;,
 115.24961;88.36328;-8.24913;,
 122.34835;88.36328;-4.20539;,
 124.74503;88.36328;0.00000;,
 122.34835;88.36328;4.20539;,
 115.24962;88.36328;8.24913;,
 103.72185;88.36328;11.97590;,
 88.20801;88.36328;15.24243;,
 69.30471;88.36328;17.92322;,
 47.73788;88.36328;19.91523;,
 24.33659;88.36328;21.14193;,
 -0.00004;88.36328;21.55608;,
 -24.33666;88.36328;21.14193;,
 -47.73792;88.36328;19.91523;,
 -69.30489;88.36328;17.92322;,
 -88.20837;88.36328;15.24243;,
 -103.72185;88.36328;11.97590;,
 -115.24962;88.36328;8.24913;,
 -122.34835;88.36328;4.20534;,
 -124.74503;88.36328;-0.00004;,
 -122.34835;88.36328;-4.20539;,
 -115.24961;88.36328;-8.24918;,
 -103.72185;88.36328;-11.97596;,
 -88.20801;88.36328;-15.24248;,
 -69.30463;88.36328;-17.92324;,
 -47.73782;88.36328;-19.91523;,
 -24.33635;88.36328;-21.14193;,
 0.00000;88.36328;-21.55608;,
 24.33659;60.69502;-21.14193;,
 0.00000;60.69502;-21.55608;,
 47.73788;60.69502;-19.91523;,
 69.30482;60.69502;-17.92322;,
 88.20801;60.69502;-15.24243;,
 103.72185;60.69502;-11.97590;,
 115.24961;60.69502;-8.24913;,
 122.34835;60.69502;-4.20539;,
 124.74503;60.69502;0.00000;,
 122.34835;60.69502;4.20539;,
 115.24962;60.69502;8.24913;,
 103.72185;60.69502;11.97590;,
 88.20801;60.69502;15.24243;,
 69.30471;60.69502;17.92322;,
 47.73788;60.69502;19.91523;,
 24.33659;60.69502;21.14193;,
 -0.00004;60.69502;21.55608;,
 -24.33666;60.69502;21.14193;,
 -47.73792;60.69502;19.91523;,
 -69.30489;60.69502;17.92322;,
 -88.20837;60.69502;15.24243;,
 -103.72185;60.69502;11.97590;,
 -115.24962;60.69502;8.24913;,
 -122.34835;60.69502;4.20534;,
 -124.74503;60.69502;-0.00004;,
 -122.34835;60.69502;-4.20539;,
 -115.24961;60.69502;-8.24918;,
 -103.72185;60.69502;-11.97596;,
 -88.20801;60.69502;-15.24248;,
 -69.30463;60.69502;-17.92324;,
 -47.73782;60.69502;-19.91523;,
 -24.33635;60.69502;-21.14193;,
 0.00000;60.69502;-21.55608;,
 24.33659;33.02717;-21.14193;,
 0.00000;33.02717;-21.55608;,
 47.73788;33.02717;-19.91523;,
 69.30482;33.02717;-17.92322;,
 88.20801;33.02717;-15.24243;,
 103.72185;33.02717;-11.97590;,
 115.24961;33.02717;-8.24913;,
 122.34835;33.02717;-4.20539;,
 124.74503;33.02717;0.00000;,
 122.34835;33.02717;4.20539;,
 115.24962;33.02717;8.24913;,
 103.72185;33.02717;11.97590;,
 88.20801;33.02717;15.24243;,
 69.30471;33.02717;17.92322;,
 47.73788;33.02717;19.91523;,
 24.33659;33.02717;21.14193;,
 -0.00004;33.02717;21.55608;,
 -24.33666;33.02717;21.14193;,
 -47.73792;33.02717;19.91523;,
 -69.30489;33.02717;17.92322;,
 -88.20837;33.02717;15.24243;,
 -103.72185;33.02717;11.97590;,
 -115.24962;33.02717;8.24913;,
 -122.34835;33.02717;4.20534;,
 -124.74503;33.02717;-0.00004;,
 -122.34835;33.02717;-4.20539;,
 -115.24961;33.02717;-8.24918;,
 -103.72185;33.02717;-11.97596;,
 -88.20801;33.02717;-15.24248;,
 -69.30463;33.02717;-17.92324;,
 -47.73782;33.02717;-19.91523;,
 -24.33635;33.02717;-21.14193;,
 0.00000;33.02717;-21.55608;,
 24.33659;5.35886;-21.14193;,
 0.00000;5.35886;-21.55608;,
 47.73788;5.35886;-19.91523;,
 69.30482;5.35886;-17.92322;,
 88.20801;5.35886;-15.24243;,
 103.72185;5.35886;-11.97590;,
 115.24961;5.35886;-8.24913;,
 122.34835;5.35886;-4.20539;,
 124.74503;5.35886;0.00000;,
 122.34835;5.35886;4.20539;,
 115.24962;5.35886;8.24913;,
 103.72185;5.35886;11.97590;,
 88.20801;5.35886;15.24243;,
 69.30471;5.35886;17.92322;,
 47.73788;5.35886;19.91523;,
 24.33659;5.35886;21.14193;,
 -0.00004;5.35886;21.55608;,
 -24.33666;5.35886;21.14193;,
 -47.73792;5.35886;19.91523;,
 -69.30489;5.35886;17.92322;,
 -88.20837;5.35886;15.24243;,
 -103.72185;5.35886;11.97590;,
 -115.24962;5.35886;8.24913;,
 -122.34835;5.35886;4.20534;,
 -124.74503;5.35886;-0.00004;,
 -122.34835;5.35886;-4.20539;,
 -115.24961;5.35886;-8.24918;,
 -103.72185;5.35886;-11.97596;,
 -88.20801;5.35886;-15.24248;,
 -69.30463;5.35886;-17.92324;,
 -47.73782;5.35886;-19.91523;,
 -24.33635;5.35886;-21.14193;,
 0.00000;5.35886;-21.55608;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;226.70435;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;,
 0.00000;5.35886;0.00000;;
 
 320;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;3,2,66,67;,
 4;2,5,68,66;,
 4;5,7,69,68;,
 4;7,9,70,69;,
 4;9,11,71,70;,
 4;11,13,72,71;,
 4;13,15,73,72;,
 4;15,17,74,73;,
 4;17,19,75,74;,
 4;19,21,76,75;,
 4;21,23,77,76;,
 4;23,25,78,77;,
 4;25,27,79,78;,
 4;27,29,80,79;,
 4;29,31,81,80;,
 4;31,33,82,81;,
 4;33,35,83,82;,
 4;35,37,84,83;,
 4;37,39,85,84;,
 4;39,41,86,85;,
 4;41,43,87,86;,
 4;43,45,88,87;,
 4;45,47,89,88;,
 4;47,49,90,89;,
 4;49,51,91,90;,
 4;51,53,92,91;,
 4;53,55,93,92;,
 4;55,57,94,93;,
 4;57,59,95,94;,
 4;59,61,96,95;,
 4;61,63,97,96;,
 4;63,65,98,97;,
 4;67,66,99,100;,
 4;66,68,101,99;,
 4;68,69,102,101;,
 4;69,70,103,102;,
 4;70,71,104,103;,
 4;71,72,105,104;,
 4;72,73,106,105;,
 4;73,74,107,106;,
 4;74,75,108,107;,
 4;75,76,109,108;,
 4;76,77,110,109;,
 4;77,78,111,110;,
 4;78,79,112,111;,
 4;79,80,113,112;,
 4;80,81,114,113;,
 4;81,82,115,114;,
 4;82,83,116,115;,
 4;83,84,117,116;,
 4;84,85,118,117;,
 4;85,86,119,118;,
 4;86,87,120,119;,
 4;87,88,121,120;,
 4;88,89,122,121;,
 4;89,90,123,122;,
 4;90,91,124,123;,
 4;91,92,125,124;,
 4;92,93,126,125;,
 4;93,94,127,126;,
 4;94,95,128,127;,
 4;95,96,129,128;,
 4;96,97,130,129;,
 4;97,98,131,130;,
 4;100,99,132,133;,
 4;99,101,134,132;,
 4;101,102,135,134;,
 4;102,103,136,135;,
 4;103,104,137,136;,
 4;104,105,138,137;,
 4;105,106,139,138;,
 4;106,107,140,139;,
 4;107,108,141,140;,
 4;108,109,142,141;,
 4;109,110,143,142;,
 4;110,111,144,143;,
 4;111,112,145,144;,
 4;112,113,146,145;,
 4;113,114,147,146;,
 4;114,115,148,147;,
 4;115,116,149,148;,
 4;116,117,150,149;,
 4;117,118,151,150;,
 4;118,119,152,151;,
 4;119,120,153,152;,
 4;120,121,154,153;,
 4;121,122,155,154;,
 4;122,123,156,155;,
 4;123,124,157,156;,
 4;124,125,158,157;,
 4;125,126,159,158;,
 4;126,127,160,159;,
 4;127,128,161,160;,
 4;128,129,162,161;,
 4;129,130,163,162;,
 4;130,131,164,163;,
 4;133,132,165,166;,
 4;132,134,167,165;,
 4;134,135,168,167;,
 4;135,136,169,168;,
 4;136,137,170,169;,
 4;137,138,171,170;,
 4;138,139,172,171;,
 4;139,140,173,172;,
 4;140,141,174,173;,
 4;141,142,175,174;,
 4;142,143,176,175;,
 4;143,144,177,176;,
 4;144,145,178,177;,
 4;145,146,179,178;,
 4;146,147,180,179;,
 4;147,148,181,180;,
 4;148,149,182,181;,
 4;149,150,183,182;,
 4;150,151,184,183;,
 4;151,152,185,184;,
 4;152,153,186,185;,
 4;153,154,187,186;,
 4;154,155,188,187;,
 4;155,156,189,188;,
 4;156,157,190,189;,
 4;157,158,191,190;,
 4;158,159,192,191;,
 4;159,160,193,192;,
 4;160,161,194,193;,
 4;161,162,195,194;,
 4;162,163,196,195;,
 4;163,164,197,196;,
 4;166,165,198,199;,
 4;165,167,200,198;,
 4;167,168,201,200;,
 4;168,169,202,201;,
 4;169,170,203,202;,
 4;170,171,204,203;,
 4;171,172,205,204;,
 4;172,173,206,205;,
 4;173,174,207,206;,
 4;174,175,208,207;,
 4;175,176,209,208;,
 4;176,177,210,209;,
 4;177,178,211,210;,
 4;178,179,212,211;,
 4;179,180,213,212;,
 4;180,181,214,213;,
 4;181,182,215,214;,
 4;182,183,216,215;,
 4;183,184,217,216;,
 4;184,185,218,217;,
 4;185,186,219,218;,
 4;186,187,220,219;,
 4;187,188,221,220;,
 4;188,189,222,221;,
 4;189,190,223,222;,
 4;190,191,224,223;,
 4;191,192,225,224;,
 4;192,193,226,225;,
 4;193,194,227,226;,
 4;194,195,228,227;,
 4;195,196,229,228;,
 4;196,197,230,229;,
 4;199,198,231,232;,
 4;198,200,233,231;,
 4;200,201,234,233;,
 4;201,202,235,234;,
 4;202,203,236,235;,
 4;203,204,237,236;,
 4;204,205,238,237;,
 4;205,206,239,238;,
 4;206,207,240,239;,
 4;207,208,241,240;,
 4;208,209,242,241;,
 4;209,210,243,242;,
 4;210,211,244,243;,
 4;211,212,245,244;,
 4;212,213,246,245;,
 4;213,214,247,246;,
 4;214,215,248,247;,
 4;215,216,249,248;,
 4;216,217,250,249;,
 4;217,218,251,250;,
 4;218,219,252,251;,
 4;219,220,253,252;,
 4;220,221,254,253;,
 4;221,222,255,254;,
 4;222,223,256,255;,
 4;223,224,257,256;,
 4;224,225,258,257;,
 4;225,226,259,258;,
 4;226,227,260,259;,
 4;227,228,261,260;,
 4;228,229,262,261;,
 4;229,230,263,262;,
 4;232,231,264,265;,
 4;231,233,266,264;,
 4;233,234,267,266;,
 4;234,235,268,267;,
 4;235,236,269,268;,
 4;236,237,270,269;,
 4;237,238,271,270;,
 4;238,239,272,271;,
 4;239,240,273,272;,
 4;240,241,274,273;,
 4;241,242,275,274;,
 4;242,243,276,275;,
 4;243,244,277,276;,
 4;244,245,278,277;,
 4;245,246,279,278;,
 4;246,247,280,279;,
 4;247,248,281,280;,
 4;248,249,282,281;,
 4;249,250,283,282;,
 4;250,251,284,283;,
 4;251,252,285,284;,
 4;252,253,286,285;,
 4;253,254,287,286;,
 4;254,255,288,287;,
 4;255,256,289,288;,
 4;256,257,290,289;,
 4;257,258,291,290;,
 4;258,259,292,291;,
 4;259,260,293,292;,
 4;260,261,294,293;,
 4;261,262,295,294;,
 4;262,263,296,295;,
 3;297,1,0;,
 3;298,4,1;,
 3;299,6,4;,
 3;300,8,6;,
 3;301,10,8;,
 3;302,12,10;,
 3;303,14,12;,
 3;304,16,14;,
 3;305,18,16;,
 3;306,20,18;,
 3;307,22,20;,
 3;308,24,22;,
 3;309,26,24;,
 3;310,28,26;,
 3;311,30,28;,
 3;312,32,30;,
 3;313,34,32;,
 3;314,36,34;,
 3;315,38,36;,
 3;316,40,38;,
 3;317,42,40;,
 3;318,44,42;,
 3;319,46,44;,
 3;320,48,46;,
 3;321,50,48;,
 3;322,52,50;,
 3;323,54,52;,
 3;324,56,54;,
 3;325,58,56;,
 3;326,60,58;,
 3;327,62,60;,
 3;328,64,62;,
 3;329,265,264;,
 3;330,264,266;,
 3;331,266,267;,
 3;332,267,268;,
 3;333,268,269;,
 3;334,269,270;,
 3;335,270,271;,
 3;336,271,272;,
 3;337,272,273;,
 3;338,273,274;,
 3;339,274,275;,
 3;340,275,276;,
 3;341,276,277;,
 3;342,277,278;,
 3;343,278,279;,
 3;344,279,280;,
 3;345,280,281;,
 3;346,281,282;,
 3;347,282,283;,
 3;348,283,284;,
 3;349,284,285;,
 3;350,285,286;,
 3;351,286,287;,
 3;352,287,288;,
 3;353,288,289;,
 3;354,289,290;,
 3;355,290,291;,
 3;356,291,292;,
 3;357,292,293;,
 3;358,293,294;,
 3;359,294,295;,
 3;360,295,296;;
 
 MeshMaterialList {
  1;
  320;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.448800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  86;
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.034687;0.000000;-0.999398;,
  0.072175;0.000000;-0.997392;,
  0.116227;0.000000;-0.993223;,
  0.173321;0.000000;-0.984865;,
  0.257180;0.000000;-0.966363;,
  0.403409;0.000000;-0.915020;,
  0.707036;0.000000;-0.707177;,
  1.000000;0.000000;0.000000;,
  0.707036;0.000000;0.707177;,
  0.403410;0.000000;0.915019;,
  0.257180;0.000000;0.966364;,
  0.173321;0.000000;0.984865;,
  0.116226;0.000000;0.993223;,
  0.072175;0.000000;0.997392;,
  0.034687;0.000000;0.999398;,
  -0.000000;0.000000;1.000000;,
  -0.034687;0.000000;0.999398;,
  -0.072175;0.000000;0.997392;,
  -0.116225;0.000000;0.993223;,
  -0.173322;0.000000;0.984865;,
  -0.257182;0.000000;0.966363;,
  -0.403412;0.000000;0.915018;,
  -0.707038;0.000000;0.707176;,
  -1.000000;0.000000;-0.000002;,
  -0.707037;0.000000;-0.707177;,
  -0.403412;0.000000;-0.915018;,
  -0.257180;0.000000;-0.966364;,
  -0.173320;0.000000;-0.984866;,
  -0.116225;0.000000;-0.993223;,
  -0.072174;0.000000;-0.997392;,
  -0.034687;0.000000;-0.999398;,
  -0.000000;0.000000;-1.000000;,
  0.116227;0.000000;-0.993223;,
  0.403409;0.000000;-0.915020;,
  0.173321;0.000000;0.984865;,
  -0.116225;0.000000;0.993223;,
  -0.257180;0.000000;-0.966364;,
  -0.034687;0.000000;-0.999398;,
  0.072175;0.000000;-0.997392;,
  0.173321;0.000000;-0.984865;,
  0.257180;0.000000;-0.966364;,
  0.707036;0.000000;-0.707177;,
  0.707036;0.000000;0.707177;,
  0.403410;0.000000;0.915020;,
  0.257180;0.000000;0.966364;,
  0.116226;0.000000;0.993223;,
  -0.000000;0.000000;1.000000;,
  -0.257182;0.000000;0.966363;,
  -1.000000;0.000000;-0.000002;,
  -0.707037;0.000000;-0.707177;,
  -0.403412;0.000000;-0.915018;,
  -0.173320;0.000000;-0.984866;,
  -0.116225;0.000000;-0.993223;,
  0.257180;0.000000;-0.966364;,
  0.403410;0.000000;0.915020;,
  0.257180;0.000000;0.966363;,
  -0.116225;0.000000;0.993223;,
  -0.403412;0.000000;0.915018;,
  -1.000000;0.000000;-0.000002;,
  -0.707037;0.000000;-0.707177;,
  -0.403412;0.000000;-0.915018;,
  -0.116225;0.000000;-0.993223;,
  0.034687;0.000000;-0.999398;,
  0.403409;0.000000;-0.915020;,
  0.707036;0.000000;0.707177;,
  0.403410;0.000000;0.915019;,
  -0.000000;0.000000;1.000000;,
  -0.403412;0.000000;-0.915018;,
  0.173321;0.000000;-0.984865;,
  0.403410;0.000000;0.915020;,
  -0.034687;0.000000;-0.999398;,
  0.116227;0.000000;-0.993223;,
  -0.072175;0.000000;0.997392;,
  -1.000000;0.000000;-0.000002;,
  -0.173322;0.000000;0.984865;,
  -0.707038;0.000000;0.707176;,
  -1.000000;0.000000;-0.000002;,
  -0.034687;0.000000;-0.999398;,
  -0.000000;0.000000;-1.000000;,
  0.072175;0.000000;-0.997392;,
  0.116227;0.000000;-0.993223;,
  0.173321;0.000000;-0.984865;,
  0.034687;0.000000;0.999398;,
  0.000000;-1.000000;-0.000000;;
  320;
  4;1,2,2,33;,
  4;2,3,3,2;,
  4;3,4,34,3;,
  4;4,5,5,34;,
  4;5,6,6,5;,
  4;6,7,35,6;,
  4;7,8,8,35;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,36,12;,
  4;13,14,14,36;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,37,19;,
  4;20,21,21,37;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,38,27;,
  4;28,29,29,38;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,39,31;,
  4;32,1,33,39;,
  4;33,2,2,33;,
  4;2,3,40,2;,
  4;3,34,34,40;,
  4;34,5,41,34;,
  4;5,6,42,41;,
  4;6,35,7,42;,
  4;35,8,43,7;,
  4;8,9,9,43;,
  4;9,10,44,9;,
  4;10,11,45,44;,
  4;11,12,46,45;,
  4;12,36,36,46;,
  4;36,14,47,36;,
  4;14,15,15,47;,
  4;15,16,16,15;,
  4;16,17,48,16;,
  4;17,18,18,48;,
  4;18,19,19,18;,
  4;19,37,37,19;,
  4;37,21,21,37;,
  4;21,22,49,21;,
  4;22,23,23,49;,
  4;23,24,24,23;,
  4;24,25,50,24;,
  4;25,26,51,50;,
  4;26,27,52,51;,
  4;27,38,38,52;,
  4;38,29,53,38;,
  4;29,30,54,53;,
  4;30,31,31,54;,
  4;31,39,39,31;,
  4;39,33,33,39;,
  4;33,2,2,1;,
  4;2,40,40,2;,
  4;40,34,34,40;,
  4;34,41,41,34;,
  4;41,42,55,41;,
  4;42,7,35,55;,
  4;7,43,8,35;,
  4;43,9,9,8;,
  4;9,44,10,9;,
  4;44,45,56,10;,
  4;45,46,57,56;,
  4;46,36,36,57;,
  4;36,47,47,36;,
  4;47,15,15,47;,
  4;15,16,16,15;,
  4;16,48,17,16;,
  4;48,18,18,17;,
  4;18,19,19,18;,
  4;19,37,58,19;,
  4;37,21,21,58;,
  4;21,49,49,21;,
  4;49,23,59,49;,
  4;23,24,24,59;,
  4;24,50,60,24;,
  4;50,51,61,60;,
  4;51,52,62,61;,
  4;52,38,38,62;,
  4;38,53,29,38;,
  4;53,54,63,29;,
  4;54,31,31,63;,
  4;31,39,39,31;,
  4;39,33,1,39;,
  4;1,2,64,1;,
  4;2,40,3,64;,
  4;40,34,34,3;,
  4;34,41,41,34;,
  4;41,55,42,41;,
  4;55,35,65,42;,
  4;35,8,8,65;,
  4;8,9,9,8;,
  4;9,10,66,9;,
  4;10,56,67,66;,
  4;56,57,12,67;,
  4;57,36,36,12;,
  4;36,47,47,36;,
  4;47,15,15,47;,
  4;15,16,16,15;,
  4;16,17,68,16;,
  4;17,18,18,68;,
  4;18,19,19,18;,
  4;19,58,58,19;,
  4;58,21,21,58;,
  4;21,49,22,21;,
  4;49,59,23,22;,
  4;59,24,24,23;,
  4;24,60,60,24;,
  4;60,61,61,60;,
  4;61,62,69,61;,
  4;62,38,38,69;,
  4;38,29,53,38;,
  4;29,63,54,53;,
  4;63,31,31,54;,
  4;31,39,39,31;,
  4;39,1,1,39;,
  4;1,64,2,1;,
  4;64,3,3,2;,
  4;3,34,34,3;,
  4;34,41,70,34;,
  4;41,42,6,70;,
  4;42,65,7,6;,
  4;65,8,43,7;,
  4;8,9,9,43;,
  4;9,66,10,9;,
  4;66,67,71,10;,
  4;67,12,12,71;,
  4;12,36,36,12;,
  4;36,47,47,36;,
  4;47,15,15,47;,
  4;15,16,16,15;,
  4;16,68,68,16;,
  4;68,18,18,68;,
  4;18,19,19,18;,
  4;19,58,20,19;,
  4;58,21,21,20;,
  4;21,22,49,21;,
  4;22,23,23,49;,
  4;23,24,24,23;,
  4;24,60,50,24;,
  4;60,61,61,50;,
  4;61,69,52,61;,
  4;69,38,28,52;,
  4;38,53,29,28;,
  4;53,54,63,29;,
  4;54,31,31,63;,
  4;31,39,72,31;,
  4;39,1,1,72;,
  4;1,2,2,33;,
  4;2,3,3,2;,
  4;3,34,73,3;,
  4;34,70,41,73;,
  4;70,6,42,41;,
  4;6,7,35,42;,
  4;7,43,8,35;,
  4;43,9,9,8;,
  4;9,10,66,9;,
  4;10,71,11,66;,
  4;71,12,12,11;,
  4;12,36,36,12;,
  4;36,47,47,36;,
  4;47,15,15,47;,
  4;15,16,16,15;,
  4;16,68,68,16;,
  4;68,18,18,68;,
  4;18,19,74,18;,
  4;19,20,37,74;,
  4;20,21,21,37;,
  4;21,49,22,21;,
  4;49,23,23,22;,
  4;23,24,24,23;,
  4;24,50,75,24;,
  4;50,61,51,75;,
  4;61,52,52,51;,
  4;52,28,38,52;,
  4;28,29,29,38;,
  4;29,63,30,29;,
  4;63,31,31,30;,
  4;31,72,72,31;,
  4;72,1,33,72;,
  4;33,2,2,1;,
  4;2,3,3,2;,
  4;3,73,34,3;,
  4;73,41,70,34;,
  4;41,42,6,70;,
  4;42,35,7,6;,
  4;35,8,43,7;,
  4;8,9,9,43;,
  4;9,66,10,9;,
  4;66,11,11,10;,
  4;11,12,12,11;,
  4;12,36,36,12;,
  4;36,47,47,36;,
  4;47,15,15,47;,
  4;15,16,16,15;,
  4;16,68,17,16;,
  4;68,18,18,17;,
  4;18,74,19,18;,
  4;74,37,58,19;,
  4;37,21,76,58;,
  4;21,22,49,76;,
  4;22,23,23,49;,
  4;23,24,77,23;,
  4;24,75,78,77;,
  4;75,51,61,78;,
  4;51,52,62,61;,
  4;52,38,38,62;,
  4;38,29,53,38;,
  4;29,30,54,53;,
  4;30,31,31,54;,
  4;31,72,79,31;,
  4;72,33,1,79;,
  4;1,2,2,80;,
  4;2,3,81,2;,
  4;3,34,82,81;,
  4;34,70,83,82;,
  4;70,6,6,83;,
  4;6,7,7,6;,
  4;7,43,8,7;,
  4;43,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,36,13,12;,
  4;36,47,14,13;,
  4;47,15,15,14;,
  4;15,16,84,15;,
  4;16,17,17,84;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,58,20,19;,
  4;58,76,21,20;,
  4;76,49,22,21;,
  4;49,23,23,22;,
  4;23,77,24,23;,
  4;77,78,75,24;,
  4;78,61,51,75;,
  4;61,62,69,51;,
  4;62,38,38,69;,
  4;38,53,29,38;,
  4;53,54,63,29;,
  4;54,31,31,63;,
  4;31,79,39,31;,
  4;79,1,80,39;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;,
  3;85,85,85;;
 }
 MeshTextureCoords {
  361;
  0.000000;0.000000;,
  0.031250;0.000000;,
  0.031250;0.125000;,
  0.000000;0.125000;,
  0.062500;0.000000;,
  0.062500;0.125000;,
  0.093750;0.000000;,
  0.093750;0.125000;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.156250;0.000000;,
  0.156250;0.125000;,
  0.187500;0.000000;,
  0.187500;0.125000;,
  0.218750;0.000000;,
  0.218750;0.125000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.281250;0.000000;,
  0.281250;0.125000;,
  0.312500;0.000000;,
  0.312500;0.125000;,
  0.343750;0.000000;,
  0.343750;0.125000;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.406250;0.000000;,
  0.406250;0.125000;,
  0.437500;0.000000;,
  0.437500;0.125000;,
  0.468750;0.000000;,
  0.468750;0.125000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.531250;0.000000;,
  0.531250;0.125000;,
  0.562500;0.000000;,
  0.562500;0.125000;,
  0.593750;0.000000;,
  0.593750;0.125000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.656250;0.000000;,
  0.656250;0.125000;,
  0.687500;0.000000;,
  0.687500;0.125000;,
  0.718750;0.000000;,
  0.718750;0.125000;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.781250;0.000000;,
  0.781250;0.125000;,
  0.812500;0.000000;,
  0.812500;0.125000;,
  0.843750;0.000000;,
  0.843750;0.125000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.906250;0.000000;,
  0.906250;0.125000;,
  0.937500;0.000000;,
  0.937500;0.125000;,
  0.968750;0.000000;,
  0.968750;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.031250;0.250000;,
  0.000000;0.250000;,
  0.062500;0.250000;,
  0.093750;0.250000;,
  0.125000;0.250000;,
  0.156250;0.250000;,
  0.187500;0.250000;,
  0.218750;0.250000;,
  0.250000;0.250000;,
  0.281250;0.250000;,
  0.312500;0.250000;,
  0.343750;0.250000;,
  0.375000;0.250000;,
  0.406250;0.250000;,
  0.437500;0.250000;,
  0.468750;0.250000;,
  0.500000;0.250000;,
  0.531250;0.250000;,
  0.562500;0.250000;,
  0.593750;0.250000;,
  0.625000;0.250000;,
  0.656250;0.250000;,
  0.687500;0.250000;,
  0.718750;0.250000;,
  0.750000;0.250000;,
  0.781250;0.250000;,
  0.812500;0.250000;,
  0.843750;0.250000;,
  0.875000;0.250000;,
  0.906250;0.250000;,
  0.937500;0.250000;,
  0.968750;0.250000;,
  1.000000;0.250000;,
  0.031250;0.375000;,
  0.000000;0.375000;,
  0.062500;0.375000;,
  0.093750;0.375000;,
  0.125000;0.375000;,
  0.156250;0.375000;,
  0.187500;0.375000;,
  0.218750;0.375000;,
  0.250000;0.375000;,
  0.281250;0.375000;,
  0.312500;0.375000;,
  0.343750;0.375000;,
  0.375000;0.375000;,
  0.406250;0.375000;,
  0.437500;0.375000;,
  0.468750;0.375000;,
  0.500000;0.375000;,
  0.531250;0.375000;,
  0.562500;0.375000;,
  0.593750;0.375000;,
  0.625000;0.375000;,
  0.656250;0.375000;,
  0.687500;0.375000;,
  0.718750;0.375000;,
  0.750000;0.375000;,
  0.781250;0.375000;,
  0.812500;0.375000;,
  0.843750;0.375000;,
  0.875000;0.375000;,
  0.906250;0.375000;,
  0.937500;0.375000;,
  0.968750;0.375000;,
  1.000000;0.375000;,
  0.031250;0.500000;,
  0.000000;0.500000;,
  0.062500;0.500000;,
  0.093750;0.500000;,
  0.125000;0.500000;,
  0.156250;0.500000;,
  0.187500;0.500000;,
  0.218750;0.500000;,
  0.250000;0.500000;,
  0.281250;0.500000;,
  0.312500;0.500000;,
  0.343750;0.500000;,
  0.375000;0.500000;,
  0.406250;0.500000;,
  0.437500;0.500000;,
  0.468750;0.500000;,
  0.500000;0.500000;,
  0.531250;0.500000;,
  0.562500;0.500000;,
  0.593750;0.500000;,
  0.625000;0.500000;,
  0.656250;0.500000;,
  0.687500;0.500000;,
  0.718750;0.500000;,
  0.750000;0.500000;,
  0.781250;0.500000;,
  0.812500;0.500000;,
  0.843750;0.500000;,
  0.875000;0.500000;,
  0.906250;0.500000;,
  0.937500;0.500000;,
  0.968750;0.500000;,
  1.000000;0.500000;,
  0.031250;0.625000;,
  0.000000;0.625000;,
  0.062500;0.625000;,
  0.093750;0.625000;,
  0.125000;0.625000;,
  0.156250;0.625000;,
  0.187500;0.625000;,
  0.218750;0.625000;,
  0.250000;0.625000;,
  0.281250;0.625000;,
  0.312500;0.625000;,
  0.343750;0.625000;,
  0.375000;0.625000;,
  0.406250;0.625000;,
  0.437500;0.625000;,
  0.468750;0.625000;,
  0.500000;0.625000;,
  0.531250;0.625000;,
  0.562500;0.625000;,
  0.593750;0.625000;,
  0.625000;0.625000;,
  0.656250;0.625000;,
  0.687500;0.625000;,
  0.718750;0.625000;,
  0.750000;0.625000;,
  0.781250;0.625000;,
  0.812500;0.625000;,
  0.843750;0.625000;,
  0.875000;0.625000;,
  0.906250;0.625000;,
  0.937500;0.625000;,
  0.968750;0.625000;,
  1.000000;0.625000;,
  0.031250;0.750000;,
  0.000000;0.750000;,
  0.062500;0.750000;,
  0.093750;0.750000;,
  0.125000;0.750000;,
  0.156250;0.750000;,
  0.187500;0.750000;,
  0.218750;0.750000;,
  0.250000;0.750000;,
  0.281250;0.750000;,
  0.312500;0.750000;,
  0.343750;0.750000;,
  0.375000;0.750000;,
  0.406250;0.750000;,
  0.437500;0.750000;,
  0.468750;0.750000;,
  0.500000;0.750000;,
  0.531250;0.750000;,
  0.562500;0.750000;,
  0.593750;0.750000;,
  0.625000;0.750000;,
  0.656250;0.750000;,
  0.687500;0.750000;,
  0.718750;0.750000;,
  0.750000;0.750000;,
  0.781250;0.750000;,
  0.812500;0.750000;,
  0.843750;0.750000;,
  0.875000;0.750000;,
  0.906250;0.750000;,
  0.937500;0.750000;,
  0.968750;0.750000;,
  1.000000;0.750000;,
  0.031250;0.875000;,
  0.000000;0.875000;,
  0.062500;0.875000;,
  0.093750;0.875000;,
  0.125000;0.875000;,
  0.156250;0.875000;,
  0.187500;0.875000;,
  0.218750;0.875000;,
  0.250000;0.875000;,
  0.281250;0.875000;,
  0.312500;0.875000;,
  0.343750;0.875000;,
  0.375000;0.875000;,
  0.406250;0.875000;,
  0.437500;0.875000;,
  0.468750;0.875000;,
  0.500000;0.875000;,
  0.531250;0.875000;,
  0.562500;0.875000;,
  0.593750;0.875000;,
  0.625000;0.875000;,
  0.656250;0.875000;,
  0.687500;0.875000;,
  0.718750;0.875000;,
  0.750000;0.875000;,
  0.781250;0.875000;,
  0.812500;0.875000;,
  0.843750;0.875000;,
  0.875000;0.875000;,
  0.906250;0.875000;,
  0.937500;0.875000;,
  0.968750;0.875000;,
  1.000000;0.875000;,
  0.031250;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.093750;1.000000;,
  0.125000;1.000000;,
  0.156250;1.000000;,
  0.187500;1.000000;,
  0.218750;1.000000;,
  0.250000;1.000000;,
  0.281250;1.000000;,
  0.312500;1.000000;,
  0.343750;1.000000;,
  0.375000;1.000000;,
  0.406250;1.000000;,
  0.437500;1.000000;,
  0.468750;1.000000;,
  0.500000;1.000000;,
  0.531250;1.000000;,
  0.562500;1.000000;,
  0.593750;1.000000;,
  0.625000;1.000000;,
  0.656250;1.000000;,
  0.687500;1.000000;,
  0.718750;1.000000;,
  0.750000;1.000000;,
  0.781250;1.000000;,
  0.812500;1.000000;,
  0.843750;1.000000;,
  0.875000;1.000000;,
  0.906250;1.000000;,
  0.937500;1.000000;,
  0.968750;1.000000;,
  1.000000;1.000000;,
  0.015620;0.000000;,
  0.046880;0.000000;,
  0.078120;0.000000;,
  0.109380;0.000000;,
  0.140620;0.000000;,
  0.171880;0.000000;,
  0.203120;0.000000;,
  0.234380;0.000000;,
  0.265620;0.000000;,
  0.296880;0.000000;,
  0.328120;0.000000;,
  0.359380;0.000000;,
  0.390620;0.000000;,
  0.421880;0.000000;,
  0.453120;0.000000;,
  0.484380;0.000000;,
  0.515620;0.000000;,
  0.546880;0.000000;,
  0.578120;0.000000;,
  0.609380;0.000000;,
  0.640620;0.000000;,
  0.671880;0.000000;,
  0.703120;0.000000;,
  0.734380;0.000000;,
  0.765620;0.000000;,
  0.796880;0.000000;,
  0.828120;0.000000;,
  0.859380;0.000000;,
  0.890620;0.000000;,
  0.921880;0.000000;,
  0.953120;0.000000;,
  0.984380;0.000000;,
  0.015620;1.000000;,
  0.046880;1.000000;,
  0.078120;1.000000;,
  0.109380;1.000000;,
  0.140620;1.000000;,
  0.171880;1.000000;,
  0.203120;1.000000;,
  0.234380;1.000000;,
  0.265620;1.000000;,
  0.296880;1.000000;,
  0.328120;1.000000;,
  0.359380;1.000000;,
  0.390620;1.000000;,
  0.421880;1.000000;,
  0.453120;1.000000;,
  0.484380;1.000000;,
  0.515620;1.000000;,
  0.546880;1.000000;,
  0.578120;1.000000;,
  0.609380;1.000000;,
  0.640620;1.000000;,
  0.671880;1.000000;,
  0.703120;1.000000;,
  0.734380;1.000000;,
  0.765620;1.000000;,
  0.796880;1.000000;,
  0.828120;1.000000;,
  0.859380;1.000000;,
  0.890620;1.000000;,
  0.921880;1.000000;,
  0.953120;1.000000;,
  0.984380;1.000000;;
 }
}
