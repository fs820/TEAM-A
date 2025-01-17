#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

// メッシュフィールドの種類
typedef enum
{
	MESHFIELD_TYPE_NOMAL = 0,
	MESHFIELD_TYPE_MAX
}MESHFIELD_TYPE;

#define MESHFIELD_WIDTH (5000)		// メッシュフィールドの高さ
#define MESHFIELD_DEPTH (5000)		// メッシュフィールドの奥行
#define MESHFIELD_DIVISION_X (40)																						// 横
#define MESHFIELD_DIVISION_Z (40)																						// 縦
#define MESHFIELD_PLYGON_HID (4 * (MESHFIELD_DIVISION_Z - 1))															// 縮退ポリゴン
#define MESHFIELD_PLYGON_APP ((MESHFIELD_DIVISION_X * MESHFIELD_DIVISION_Z) * 2)										// 見えるポリゴン
#define MESHFIELD_PLYGON_AII (((MESHFIELD_DIVISION_X * MESHFIELD_DIVISION_Z) * 2) + (4 * (MESHFIELD_DIVISION_Z - 1)))	// 合計ポリゴン
#define MESHFIELD_VERTEX ((MESHFIELD_DIVISION_X + 1) * (MESHFIELD_DIVISION_Z + 1))										// 頂点数
#define MESHFIELD_INDEX (MESHFIELD_PLYGON_AII + 2)																		// インデックス数

// メッシュフィールドの構造体
typedef struct
{
	D3DXVECTOR3 pos;							// 位置
	D3DXVECTOR3 rot;							// 向き
	D3DXVECTOR3 aNor[MESHFIELD_PLYGON_AII];		// ポリゴンの法線
	D3DXMATRIX mtxWorld;						// ワールドマトリックス
	int nType;									// タイプ
	bool bUse;									// 使用しているかどうか
}MESHFIELD;

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
bool CollisionMeshField(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove);
void VertexMoveMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius);
void ResetNorVectolMeshField();
void SaveInfoMeshField();
void LoadInfoMeshField();
#endif // !_POLYGON_H_
