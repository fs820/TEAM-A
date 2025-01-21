#ifndef _MODELENEMY_H_
#define _MODELENEMY_H_

#include "main.h"

#define MAX_MODEL_TEXTURE (6)	// モデルのテクスチャの最大枚数
// モデル構造体
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[MAX_MODEL_TEXTURE];	// テクスチャへのポンタ
	LPD3DXMESH pMesh;					// メッシュ(頂点情報へのポインタ)
	LPD3DXBUFFER pBuffMat;				// マテリアルへのポインタ
	DWORD dwNumMat;						// マテリアルの数
	int nIdxModelEnemyParent;			// 親モデルのインデックス
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 offSet;					// オフセット
	D3DXVECTOR3 rot;					// 向き
	D3DXMATRIX mtxWorld;				// ワールドマトリックス

}ModelEnemy;

//プロトタイプ宣言
void SetModelEnemy(char astr[], ModelEnemy* pModelEnemy, int nModelEnemyNum);	// モデルの設定 
void PartsSet(FILE* pFile, ModelEnemy* model);//  
void EndPartsSet(ModelEnemy* pModelEnemy, ModelEnemy model, int nIndex);// 

#endif // !_MODEL_H_
