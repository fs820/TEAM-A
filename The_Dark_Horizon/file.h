//---------------------------------------
//
//セーブ・ロード処理の定義・宣言[file.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _FILE_H_
#define _FILE_H_

#include"main.h"

#define MAX_DATA (10)//保存するスコアの数
#define ROT_INA (D3DX_PI/180.0f)

//プロトタイプ宣言
int* Soat(int* pData);//ソート処理
void SaveFile(int* pData);//セーブ処理
int* LoadFile(void);//ロード処理
void LoadStageManager(void);//ロード処理
void LoadStage(void);//ロード処理
void SaveStage(void);//セーブ処理
void LoadPlayer(void);//ロード処理

#endif _DATA_H_
