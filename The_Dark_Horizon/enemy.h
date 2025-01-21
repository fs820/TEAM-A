#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "modelEnemy.h"
#include "motionEnemy.h"

// マクロ定義
#define MAX_ENEMY (32)		// 敵の最大数

// エネミーの構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 rot;	// 向き
	D3DXVECTOR3 move;	// 移動量

	ModelEnemy aModelEnemy[10];	// モデルパーツ
	MOTION_ENEMY motion;		// モーション
	CHARPARAM charparam;		// キャラクターパラメータ
}ENEMY;

// エネミーの管理構造体
typedef struct
{
	int nNumEnemy;	// エネミーの総数自身の間合い
}ENEMY_MANAGER;

// プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);
#endif // !_ENEMY_H_
