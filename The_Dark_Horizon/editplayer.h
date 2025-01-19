#ifndef _EDITPLAYER_H_
#define _EDITPLAYER_H_

#include "main.h"
#include "stage.h"

#define MAX_EDITPLAYER_TEX_NUM (6)		// テクスチャの数
#define EDITPLAYER_MOVE_MAX (20.0f)		// エディットプレイヤーの移動量
#define EDITPLAYER_GRAVITY_MAX (10.0f)	// エディットプレイヤーの重力量

//エディットタイプの列挙型定義
typedef enum
{
	MESH = 0,          // 起伏
	OBJECT,            // オブジェクト設置
	EDIT_MAX
}EDITTYPE;

// エディットプレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 posOld;	// 古い位置
	D3DXVECTOR3 move;	// 移動量
	D3DXVECTOR3 rot;	// 向き
	D3DXVECTOR3 rotDest;// 目的の向き
	float movement;		// 移動量
	float graviment;	// 重力量
	float jumpment;		// ジャンプ量
	EDITTYPE Type;      // エディットタイプ
	Stage* pStage;      //ステージポインタ
	bool bDisp;			// 映すかどうか

	LPDIRECT3DTEXTURE9 apTexture[MAX_EDITPLAYER_TEX_NUM];	// テクスチャへのポンタ
	LPD3DXMESH pMesh;		// メッシュ(頂点情報へのポインタ)
	LPD3DXBUFFER pBuffMat;	// マテリアルへのポインタ
	DWORD dwNumMat;			// マテリアルの数
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
}EDITPLAYER;

void InitEditPlayer();			// エディットプレイヤーの初期化
void UninitEditPlayer();		// エディットプレイヤーの終了
void UpdateEditPlayer();		// エディットプレイヤーの更新
void DrawEditPlayer();			// エディットプレイヤーの描画
void EditPlayerManagerMesh();   // エディットプレイヤーの管理(Mesh)
void EditPlayerManagerObject(); // エディットプレイヤーの管理(Object)
EDITPLAYER* GetEditPlayer();	// エディットプレイヤーの取得
#endif // !_EDITPLAYER_H_
