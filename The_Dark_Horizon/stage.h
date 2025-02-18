//---------------------------------------
//
//モデル表示処理の定義・宣言[stage.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _STAGE_H_
#define _STAGE_H_

#include"main.h"
#include"game.h"

#define STAGE_MAX (256)
#define XFILE_MAX (64)
#define TEXTURE_MAX (32)
#define NAME_MAX (64)
#define COLLISION_TILL (0.8f)
#define STAGE_SCALE_MAX (20.0f)
#define STAGE_SCALE_MIN (0.5f)

//Xファイルパス構造体
typedef struct
{
	char aName[NAME_MAX];
}String;

//Xファイルパス構造体
typedef struct
{
	int XfileNum;
	String Pass[XFILE_MAX];
}XFILE;

//プレイヤー構造体
typedef struct
{
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	LPDIRECT3DTEXTURE9 apTexture[TEXTURE_MAX];
	DWORD dwNumMat;//マテリアル数
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	float fLength;
	float fAngle;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	int nNumVtx;
	DWORD sizeFVF;
	BYTE* pVtxBuff;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nTypeNumber;
	bool bUse;
}Stage;

void InitStage(void);//ポリゴンの初期化処理
void UninitStage(void);//ポリゴンの終了処理
void UpdateStage(void);//ポリゴンの更新処理
void DrawStage(void);//ポリゴンの描画処理
void SetStageManager(XFILE Xfile);
int SetStage(int nNumber, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
void EndStage(int nEndNumber);
Stage* GetStage(void);
int GetXfileNum(void);
bool CollisionStage(Stage** pStage);
String GetXfileName(int nNumber);

#endif _STAGE_H_