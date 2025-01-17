//***********************************************
//
// メッシュフィールドを生成する処理
// Aouther Tetsuji Yamamoto
// 
//***********************************************
#include "meshfield.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	// インデックスへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturMeshfield = NULL;		// テクスチャのポインタ
MESHFIELD g_meshField;				// メッシュフィールドの情報

//**************************************
// メッシュフィールドの初期化
//**************************************
void InitMeshfield(void)
{
	int nCntMeshFeild = 0;	// メッシュフィールドの個数を数える変数
	int nCntVtx = 0;		// メッシュフィールドの頂点数を数える変数
	int nCntIdx = 0;		// インデックスをカウントする変数
	int nCntIdxGuide = 0;

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield, NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\field002.jpg",
		&g_pVtxTexturMeshfield);

	// 各種変数の初期化--------------------------------------------------------------------------------
	// 頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	g_meshField.pos = D3DXVECTOR3(-2500.0f, 0.0f, 2500.0f);	// 位置
	g_meshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	g_meshField.nType = -1;								// 種類
	g_meshField.bUse = false;							// 使用しているかどうか

	for (int nCntZ = 0; nCntZ <= MESHFIELD_DIVISION_Z; nCntZ++)
	{// Zの分割数回す
		for (int nCntX = 0; nCntX <= MESHFIELD_DIVISION_X; nCntX++)
		{// Xの分割数回す

			float fposX = ((float)MESHFIELD_WIDTH / (float)MESHFIELD_DIVISION_X) * (float)nCntX;
			float fposZ = ((float)MESHFIELD_DEPTH / (float)MESHFIELD_DIVISION_Z) * (float)nCntZ;
			float fTexX = 1.0f / (float)MESHFIELD_DIVISION_X * nCntX;
			float fTexY = 1.0f / (float)MESHFIELD_DIVISION_Z * nCntZ;

			// 頂点座標の設定
			pVtx[nCntVtx].pos.x = g_meshField.pos.x + fposX;
			pVtx[nCntVtx].pos.y = g_meshField.pos.y + 0.0f;
			pVtx[nCntVtx].pos.z = g_meshField.pos.z + (-fposZ);

			// 各頂点の法線の設定,面に対して垂直
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtx].tex.x = fTexX;
			pVtx[nCntVtx].tex.y = fTexY;

			// 頂点数を一つ進める
			nCntVtx++;
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffMeshfield->Unlock();

	// インデックスを求める----------------------------------------------------------------------
	int nIdxA = MESHFIELD_DIVISION_X + 1;					// 左側インデックス
	int nIdxB = 0;											// 右側インデックス
	int nIdxEX[MESHFIELD_INDEX] = {};	// インデックス一時保存用
	int nCntIdxEX = 0;										// 保存用インデックスのカウンター

	// インデック情報へのポインタ
	WORD* pIdx;

	// インデックスバッファをロック
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < MESHFIELD_DIVISION_Z; nCntA++)
	{// Zの分割数分回す
		for (int nCntB = 0; nCntB <= MESHFIELD_DIVISION_X; nCntB++)
		{// Xの分割数分回す
			pIdx[nCntIdx] = nIdxA;
			pIdx[nCntIdx + 1] = nIdxB;
			nIdxEX[nCntIdxEX] = nIdxA;
			nIdxEX[nCntIdxEX + 1] = nIdxB;
			nCntIdx += 2;
			nCntIdxEX += 2;
			nIdxA++;
			nIdxB++;
		}

		if (nCntA < MESHFIELD_DIVISION_Z - 1)
		{// 安全装置
			pIdx[nCntIdx] = nIdxB - 1;
			pIdx[nCntIdx + 1] = nIdxA;
			nIdxEX[nCntIdxEX] = nIdxB - 1;
			nIdxEX[nCntIdxEX + 1] = nIdxA;
			nCntIdx += 2;
			nCntIdxEX += 2;
		}
	}
	nIdxB = nIdxA;											// 次のインデックスを算出
	nIdxA = nIdxA + MESHFIELD_DIVISION_X + 1;				// 次のインデックスを算出
	nCntIdx = 0;											// インデックスカウンターリセット
	nCntIdxEX = (MESHFIELD_INDEX) * (nCntMeshFeild + 1);	// 次の保存用インデックスカウンターを算出
	pIdx += MESHFIELD_INDEX;								// インデックス数分回す

// インデックスバッファのアンロック
	g_pIdxBuffMeshfield->Unlock();

	// 法線を求める--------------------------------------------------------------------------------
	// 頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);
	nCntIdxEX = 0;			// 一時保存用インデックスカウンターリセット

	for (int nCntPoliOll = 0; nCntPoliOll < MESHFIELD_PLYGON_AII; nCntPoliOll++)
	{// すべてのポリゴン分回す
		for (int nCntPoliApp = 0; nCntPoliApp < MESHFIELD_DIVISION_X * 2; nCntPoliApp++)
		{// 見えるポリゴン分回す
			D3DXVECTOR3 vecLineA = {};	// 一辺のベクトル
			D3DXVECTOR3 vecLineB = {};	// 一辺のベクトル
			D3DXVECTOR3 vecNor = {};	// 法線ベクトル

			if ((nCntPoliApp + 1) % 2 == 0)
			{// 割り切れる、左回り
				vecLineA = pVtx[nIdxEX[nCntIdxEX + 2]].pos - pVtx[nIdxEX[nCntIdxEX]].pos;	// 一辺のベクトル
				vecLineB = pVtx[nIdxEX[nCntIdxEX + 1]].pos - pVtx[nIdxEX[nCntIdxEX]].pos;	// 一辺のベクトル
			}
			else
			{// 割り切れない、右回り
				vecLineA = pVtx[nIdxEX[nCntIdxEX + 1]].pos - pVtx[nIdxEX[nCntIdxEX]].pos;	// 一辺のベクトル
				vecLineB = pVtx[nIdxEX[nCntIdxEX + 2]].pos - pVtx[nIdxEX[nCntIdxEX]].pos;	// 一辺のベクトル
			}

			// 法線ベクトルを求める
			vecNor.x = (vecLineA.y * vecLineB.z) - (vecLineA.z * vecLineB.y);
			vecNor.y = (vecLineA.z * vecLineB.x) - (vecLineA.x * vecLineB.z);
			vecNor.z = (vecLineA.x * vecLineB.y) - (vecLineA.y * vecLineB.x);

			// 法線ベクトルを保存
			g_meshField.aNor[nCntPoliOll] = vecNor;

			// 正規化
			D3DXVec3Normalize(&vecNor, &vecNor);

			// 算出した法線を代入する
			pVtx[nIdxEX[nCntIdxEX]].nor = vecNor;
			pVtx[nIdxEX[nCntIdxEX + 1]].nor = vecNor;
			pVtx[nIdxEX[nCntIdxEX + 2]].nor = vecNor;

			nCntIdxEX++;	// インデックスカウンターを一つ進める
			nCntPoliOll++;	// ポリゴンカウント一つ進める
		}

		if (nCntPoliOll < MESHFIELD_PLYGON_AII)
		{// 一メッシュフィールドを設定しきったらやらなくてよい
			nCntIdxEX += 4;		// インデックスカウンターを縮退ポリゴン分進める
			nCntPoliOll += 3;	// ポリゴンカウントを縮退ポリゴン分進める
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffMeshfield->Unlock();

	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//**************************************
// メッシュフィールドの破棄
//**************************************
void UninitMeshfield(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	// インデックスバッファの解放
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturMeshfield != NULL)
	{
		g_pVtxTexturMeshfield->Release();
		g_pVtxTexturMeshfield = NULL;
	}
}

//**************************************
// メッシュフィールドの破棄
//**************************************
void UpdateMeshfield(void)
{
	//if (KeyboardTrigger(DIK_F1))
	//{
	//	// 頂点情報を保存する
	//	SaveInfoMeshField();
	//}
	//else if (KeyboardTrigger(DIK_F2))
	//{
	//	// 頂点情報を取得する
	//	LoadInfoMeshField();
	//}
}

//**************************************
// メッシュフィールドの描画
//**************************************
void DrawMeshfield(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_meshField.mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshField.rot.y, g_meshField.rot.x, g_meshField.rot.z);
	D3DXMatrixMultiply(&g_meshField.mtxWorld, &g_meshField.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_meshField.pos.x, g_meshField.pos.y, g_meshField.pos.z);
	D3DXMatrixMultiply(&g_meshField.mtxWorld, &g_meshField.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_meshField.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshfield);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pVtxTexturMeshfield);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		MESHFIELD_VERTEX,
		0,
		MESHFIELD_PLYGON_AII);
}

//*******************************************
// メッシュフィールドの設定
//*******************************************
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntMeshFeild = 0;	// メッシュフィールドの個数を数える変数
	int nCntVtx = 0;		// インデックスをカウントする変数

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	g_meshField.pos = pos;
	g_meshField.rot = rot;
	g_meshField.bUse = true;

	// 頂点バッファをアンロック
	g_pVtxBuffMeshfield->Unlock();
}

//*******************************************
// メッシュフィールドの当たり判定
//*******************************************
bool CollisionMeshField(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove)
{
	bool bRanding = false;

	int nCntMeshFeild = 0;	// メッシュフィールドの個数を数える変数
	int nCntIdx = 0;		// インデックスをカウントする変数

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// インデック情報へのポインタ
	WORD* pIdx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	// インデックスバッファをロック
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntPoliOll = 0; nCntPoliOll < MESHFIELD_PLYGON_AII; nCntPoliOll++)
	{// すべてのポリゴン分回す
		for (int nCntPoliApp = 0; nCntPoliApp < MESHFIELD_DIVISION_X * 2; nCntPoliApp++)
		{// 見えるポリゴン分回す
			D3DXVECTOR3 vecLineA, vecLineB, vecLineC;				// ポリゴンの一辺のベクトル
			D3DXVECTOR3 vecLinePposA, vecLinePposB, vecLinePposC;	// pPosとのベクトル
			D3DXVECTOR3 vecClossA, vecClossB, vecClossC;			// pPosベクトルと一辺ベクトルの外積

			// ポリゴンの一辺のベクトルを求める
			vecLineA = pVtx[pIdx[nCntIdx + 1]].pos - pVtx[pIdx[nCntIdx]].pos;
			vecLineB = pVtx[pIdx[nCntIdx + 2]].pos - pVtx[pIdx[nCntIdx + 1]].pos;
			vecLineC = pVtx[pIdx[nCntIdx]].pos - pVtx[pIdx[nCntIdx + 2]].pos;

			// pPosベクトルを求める
			vecLinePposA = *pPos - pVtx[pIdx[nCntIdx]].pos;
			vecLinePposB = *pPos - pVtx[pIdx[nCntIdx + 1]].pos;
			vecLinePposC = *pPos - pVtx[pIdx[nCntIdx + 2]].pos;

			// pPosベクトルと一辺ベクトルの外積を求める
			vecClossA.x = (vecLineA.y * vecLinePposA.z) - (vecLineA.z * vecLinePposA.y);
			vecClossA.y = (vecLineA.z * vecLinePposA.x) - (vecLineA.x * vecLinePposA.z);
			vecClossA.z = (vecLineA.x * vecLinePposA.y) - (vecLineA.y * vecLinePposA.x);

			vecClossB.x = (vecLineB.y * vecLinePposB.z) - (vecLineB.z * vecLinePposB.y);
			vecClossB.y = (vecLineB.z * vecLinePposB.x) - (vecLineB.x * vecLinePposB.z);
			vecClossB.z = (vecLineB.x * vecLinePposB.y) - (vecLineB.y * vecLinePposB.x);

			vecClossC.x = (vecLineC.y * vecLinePposC.z) - (vecLineC.z * vecLinePposC.y);
			vecClossC.y = (vecLineC.z * vecLinePposC.x) - (vecLineC.x * vecLinePposC.z);
			vecClossC.z = (vecLineC.x * vecLinePposC.y) - (vecLineC.y * vecLinePposC.x);

			if (vecClossA.y > 0 &&
				vecClossB.y > 0 &&
				vecClossC.y > 0 ||
				vecClossA.y < 0 &&
				vecClossB.y < 0 &&
				vecClossC.y < 0)
			{// 外積ベクトルのyがすべてプラスなら

				// プレイヤーのy座標を求める
				/*
				a = nor
				sp = startPos
				pp = playerPos

				dot = a.x * sp.x + a.y * sp.y + a.z * sp.z

				pp.y = (-(a.x * pp.x) -(a.z * pp.z) + dotA) / a.y
				*/

				// 法線とポリゴンの一頂点の内積
				float fdot = (g_meshField.aNor[nCntPoliOll].x * pVtx[pIdx[nCntIdx]].pos.x +
					g_meshField.aNor[nCntPoliOll].y * pVtx[pIdx[nCntIdx]].pos.y +
					g_meshField.aNor[nCntPoliOll].z * pVtx[pIdx[nCntIdx]].pos.z);

				//プレイヤーがポリゴン上にいるときのy座標を求める
				float posy = (-g_meshField.aNor[nCntPoliOll].x * pPos->x - g_meshField.aNor[nCntPoliOll].z * pPos->z + fdot) /
					g_meshField.aNor[nCntPoliOll].y;

				if (pPos->y <= posy)
				{// 求めた座標より小さかったら
					// y座標を設定
					pPos->y = posy;

					// 移動量をなくす
					pMove->y = 0.0f;

					// 乗った判定
					bRanding = true;
				}
			}

			nCntPoliOll++;	// ポリゴンカウンタープラス
			nCntIdx++;		// インデックカウンタープラス
		}

		if (nCntPoliOll < MESHFIELD_PLYGON_AII)
		{// 一メッシュフィールドを設定しきったらやらなくてよい
		// 縮退ポリゴン分進める
			nCntPoliOll += 3;	// ポリゴンカウンタープラス
			nCntIdx += 4;		// インデックカウンタープラス
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffMeshfield->Unlock();

	// インデックスバッファのアンロック
	g_pIdxBuffMeshfield->Unlock();

	// 結果を返す
	return bRanding;
}

//*******************************************
// メッシュフィールドの頂点を操作する
//*******************************************
void VertexMoveMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius)
{
	int nCntMeshFeild = 0;	// メッシュフィールドの個数を数える変数
	int nCntIdx = 0;		// インデックスをカウントする変数

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// インデック情報へのポインタ
	WORD* pIdx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
	{// すべての頂点分回す
		float fLength = sqrtf(((pos.x - pVtx[nCntVtx].pos.x) * (pos.x - pVtx[nCntVtx].pos.x)) + ((pos.z - pVtx[nCntVtx].pos.z) * (pos.z - pVtx[nCntVtx].pos.z)));

		if (fLength <= fRadius)
		{// 範囲内であれば
			pVtx[nCntVtx].pos.y += (pos.y - pVtx[nCntVtx].pos.y) * 0.01f;
		}
	}

	pVtx += MESHFIELD_VERTEX;	// 頂点分進める

// 頂点バッファをアンロック
	g_pVtxBuffMeshfield->Unlock();
}

//*******************************************
// メッシュフィールドの法線を再設定する
//*******************************************
void ResetNorVectolMeshField()
{
	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// インデック情報へのポインタ
	WORD* pIdx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	// インデックスバッファをロック
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdxEX = 0;			// 一時保存用インデックスカウンターリセット
	int nCntIdxGuide = 0;

	for (int nCntPoliOll = 0; nCntPoliOll < MESHFIELD_PLYGON_AII; nCntPoliOll++)
	{// すべてのポリゴン分回す
		for (int nCntPoliApp = 0; nCntPoliApp < MESHFIELD_DIVISION_X * 2; nCntPoliApp++)
		{// 見えるポリゴン分回す
			D3DXVECTOR3 vecLineA = {};	// 一辺のベクトル
			D3DXVECTOR3 vecLineB = {};	// 一辺のベクトル
			D3DXVECTOR3 vecNor = {};	// 法線ベクトル

			if ((nCntPoliApp + 1) % 2 == 0)
			{// 割り切れる、左回り
				vecLineA = pVtx[pIdx[nCntIdxEX + 2]].pos - pVtx[pIdx[nCntIdxEX]].pos;	// 一辺のベクトル
				vecLineB = pVtx[pIdx[nCntIdxEX + 1]].pos - pVtx[pIdx[nCntIdxEX]].pos;	// 一辺のベクトル
			}
			else
			{// 割り切れない、右回り
				vecLineA = pVtx[pIdx[nCntIdxEX + 1]].pos - pVtx[pIdx[nCntIdxEX]].pos;	// 一辺のベクトル
				vecLineB = pVtx[pIdx[nCntIdxEX + 2]].pos - pVtx[pIdx[nCntIdxEX]].pos;	// 一辺のベクトル
			}

			// 法線ベクトルを求める
			vecNor.x = (vecLineA.y * vecLineB.z) - (vecLineA.z * vecLineB.y);
			vecNor.y = (vecLineA.z * vecLineB.x) - (vecLineA.x * vecLineB.z);
			vecNor.z = (vecLineA.x * vecLineB.y) - (vecLineA.y * vecLineB.x);

			// 法線ベクトルを保存
			g_meshField.aNor[nCntPoliOll] = vecNor;

			// 正規化
			D3DXVec3Normalize(&vecNor, &vecNor);

			// 算出した法線を代入する
			pVtx[pIdx[nCntIdxEX]].nor = vecNor;
			pVtx[pIdx[nCntIdxEX + 1]].nor = vecNor;
			pVtx[pIdx[nCntIdxEX + 2]].nor = vecNor;

			nCntIdxEX++;	// インデックスカウンターを一つ進める
			nCntPoliOll++;	// ポリゴンカウント一つ進める
		}

		if (nCntPoliOll < MESHFIELD_PLYGON_AII)
		{// 一メッシュフィールドを設定しきったらやらなくてよい
			nCntIdxEX += 4;		// インデックスカウンターを縮退ポリゴン分進める
			nCntPoliOll += 3;	// ポリゴンカウントを縮退ポリゴン分進める
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffMeshfield->Unlock();

	// インデックスバッファのアンロック
	g_pIdxBuffMeshfield->Unlock();
}

//*******************************************
// メッシュフィールドの頂点情報を保存する
//*******************************************
void SaveInfoMeshField()
{
	// ファイルを開く
	FILE* pFile = fopen("date\\text\\MeshField\\MeshField_Info.txt", "w");
	VERTEX_3D* pVtx = NULL;	// 頂点情報へのポインタ
	WORD* pIdx = NULL;		// インデック情報へのポインタ

	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);	// インデックスバッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);	// 頂点バッファをロック

	fprintf(pFile, "MESHFIELD_DIVISION_X %d\n", MESHFIELD_DIVISION_X);		// x方向の分割数書き込み
	fprintf(pFile, "MESHFIELD_DIVISION_Z %d\n\n", MESHFIELD_DIVISION_Z);	// z方向の分割数書き込み

		// メッシュフィールド情報書き込み開始
	fprintf(pFile, "MESHFIELD_INFO\n\n");

	// メッシュフィールド構造体の情報を書き込む------------------------------------------------------------------------
	// 文頭
	fprintf(pFile, "MESHFIELD_STRUCT\n");

	// 位置
	fprintf(pFile, "MESHFIELD_STRUCT_POS\n");
	fprintf(pFile, "%f %f %f\n", g_meshField.pos.x, g_meshField.pos.y, g_meshField.pos.z);
	fprintf(pFile, "END_MESHFIELD_STRUCT_POS\n\n");

	// 向き
	fprintf(pFile, "MESHFIELD_STRUCT_ROT\n");
	fprintf(pFile, "%f %f %f\n", g_meshField.rot.x, g_meshField.rot.y, g_meshField.rot.z);
	fprintf(pFile, "END_MESHFIELD_STRUCT_ROT\n\n");

	// 種類
	fprintf(pFile, "MESHFIELD_STRUCT_TYPE\n");
	fprintf(pFile, "%d\n", g_meshField.nType);
	fprintf(pFile, "END_MESHFIELD_STRUCT_TYPE\n\n");

	// ポリゴンの法線
	fprintf(pFile, "MESHFIELD_STRUCT_NOR\n");
	for (int nCntPolligon = 0; nCntPolligon < MESHFIELD_PLYGON_AII; nCntPolligon++)
	{// ポリゴン数分回す
		fprintf(pFile, "%f %f %f\n",
			g_meshField.aNor[nCntPolligon].x,
			g_meshField.aNor[nCntPolligon].y,
			g_meshField.aNor[nCntPolligon].z);
	}
	fprintf(pFile, "END_MESHFIELD_STRUCT_NOR\n\n");

	fprintf(pFile, "END_MESHFIELD_STRUCT\n\n");

	// 頂点座標を書き込む----------------------------------------------------------------------------------------------
	// 文頭
	fprintf(pFile, "MESHFIELD_VERTEX_POS\n");

	for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
	{// 頂点数分回す
		fprintf(pFile, "%f %f %f\n", pVtx[nCntVtx].pos.x, pVtx[nCntVtx].pos.y, pVtx[nCntVtx].pos.z);
	}

	// 文末
	fprintf(pFile, "END_MESHFIELD_VERTEX_POS\n\n");

	// 法線ベクトルを書き込む------------------------------------------------------------------------------------------
	// 文頭
	fprintf(pFile, "MESHFIELD_VERTEX_NOR\n");

	for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
	{// 頂点数分回す
		fprintf(pFile, "%f %f %f\n", pVtx[nCntVtx].nor.x, pVtx[nCntVtx].nor.y, pVtx[nCntVtx].nor.z);
	}

	// 文末
	fprintf(pFile, "END_MESHFIELD_VERTEX_NOR\n\n");

	// テクスチャ座標を書き込む----------------------------------------------------------------------------------------
	// 文頭
	fprintf(pFile, "MESHFIELD_VERTEX_TEX\n");

	for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
	{// 頂点数分回す
		fprintf(pFile, "%f %f\n", pVtx[nCntVtx].tex.x, pVtx[nCntVtx].tex.y);
	}

	// 文末
	fprintf(pFile, "END_MESHFIELD_VERTEX_TEX\n\n");

	// インデックスを書き込む------------------------------------------------------------------------------------------
	// 文頭
	fprintf(pFile, "MESHFIELD_INDEX\n");

	for (int nCntIdx = 0; nCntIdx < MESHFIELD_INDEX; nCntIdx++)
	{// 頂点数分回す
		fprintf(pFile, "%d\n", pIdx[nCntIdx]);
	}

	// 文末
	fprintf(pFile, "END_MESHFIELD_INDEX\n\n");

	pVtx += MESHFIELD_VERTEX;	// 次の頂点座標へ進める
	pIdx += MESHFIELD_INDEX;	// 次のインデックスへ進めるる

// メッシュフィールドの設定終わり
	fprintf(pFile, "END_MESHFIELD_INFO\n\n");

	g_pVtxBuffMeshfield->Unlock();	// 頂点バッファをアンロック
	g_pIdxBuffMeshfield->Unlock();	// インデックスバッファのアンロック

	// ファイルを閉じる
	fclose(pFile);
}

//*******************************************
// メッシュフィールドの頂点情報を取得
//*******************************************
void LoadInfoMeshField()
{
	char aStr[256] = {};	// 文字列保存用変数
	int nNum = -1;			// 数字保存用変数
	int nResult;			// 結果を保存する変数
	int nCntMeshField = -1;	// メッシュフィールドを数えるウ変数

	// ファイルを開く
	FILE* pFile = fopen("date\\text\\MeshField\\MeshField_Info.txt", "r");
	VERTEX_3D* pVtx = NULL;	// 頂点情報へのポインタ
	WORD* pIdx = NULL;		// インデック情報へのポインタ

	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);	// インデックスバッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);	// 頂点バッファをロック

	while (1)
	{
		// 文字列を読み取る
		nResult = fscanf(pFile, "%s", &aStr[0]);

		if (strcmp("MESHFIELD_DIVISION_X", &aStr[0]) == 0)
		{// メッシュフィールドのxの分割数を読み取る
			nResult = fscanf(pFile, "%d", &nNum);

			if (nNum != MESHFIELD_DIVISION_X)
			{// マクロと読み取った数字が合っていなかったら失敗
				nResult = EOF;
			}
		}
		else if (strcmp("MESHFIELD_DIVISION_Z", &aStr[0]) == 0)
		{// メッシュフィールドのzの分割数を読み取る
			nResult = fscanf(pFile, "%d", &nNum);

			if (nNum != MESHFIELD_DIVISION_Z)
			{// マクロと読み取った数字が合っていなかったら失敗
				nResult = EOF;
			}
		}
		else if (strcmp("MESHFIELD_INFO", &aStr[0]) == 0)
		{// メッシュフィールドの情報取得開始
			nCntMeshField++;// メッシュフィールドカウンター追加
		}
		else if (strcmp("END_MESHFIELD_INFO", &aStr[0]) == 0)
		{// メッシュフィールドの情報取得終了
		}
		else if (strcmp("MESHFIELD_STRUCT_POS", &aStr[0]) == 0)
		{// メッシュフィール構造体の位置を取得
			nResult = fscanf(pFile, "%f", &g_meshField.pos.x);
			nResult = fscanf(pFile, "%f", &g_meshField.pos.y);
			nResult = fscanf(pFile, "%f", &g_meshField.pos.z);
		}
		else if (strcmp("END_MESHFIELD_STRUCT_POS", &aStr[0]) == 0)
		{// メッシュフィール構造体の位置を取得を終了
		}
		else if (strcmp("MESHFIELD_STRUCT_NOR", &aStr[0]) == 0)
		{// メッシュフィール構造体の法線を取得
			for (int nCntPolligon = 0; nCntPolligon < MESHFIELD_PLYGON_AII; nCntPolligon++)
			{// ポリゴン数分回す
				nResult = fscanf(pFile, "%f", &g_meshField.aNor[nCntPolligon].x);
				nResult = fscanf(pFile, "%f", &g_meshField.aNor[nCntPolligon].y);
				nResult = fscanf(pFile, "%f", &g_meshField.aNor[nCntPolligon].z);
			}
		}
		else if (strcmp("END_MESHFIELD_STRUCT_NOR", &aStr[0]) == 0)
		{// メッシュフィール構造体の位置を法線を終了
		}
		else if (strcmp("MESHFIELD_STRUCT_TYPE", &aStr[0]) == 0)
		{// メッシュフィール構造体の種類を取得
			nResult = fscanf(pFile, "%d", &g_meshField.nType);
		}
		else if (strcmp("END_MESHFIELD_STRUCT_TYPE", &aStr[0]) == 0)
		{// メッシュフィール構造体の種類を取得を終了
		}
		else if (strcmp("MESHFIELD_VERTEX_POS", &aStr[0]) == 0)
		{// メッシュフィールドの頂点情報を取得する
			for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
			{// 頂点数分回す
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].pos.x);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].pos.y);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].pos.z);
			}
		}
		else if (strcmp("END_MESHFIELD_VERTEX_POS", &aStr[0]) == 0)
		{// メッシュフィールドの頂点情報の取得終了
		}
		else if (strcmp("MESHFIELD_VERTEX_NOR", &aStr[0]) == 0)
		{// メッシュフィールドの法線ベクトルを取得する
			for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
			{// 頂点数分回す
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].nor.x);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].nor.y);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].nor.z);
			}
		}
		else if (strcmp("END_MESHFIELD_VERTEX_NOR", &aStr[0]) == 0)
		{// メッシュフィールドの法線ベクトルの取得終了
		}
		else if (strcmp("MESHFIELD_VERTEX_TEX", &aStr[0]) == 0)
		{// メッシュフィールドのテクスチャ座標を取得する
			for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
			{// 頂点数分回す
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].tex.x);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].tex.y);
			}
		}
		else if (strcmp("END_MESHFIELD_VERTEX_TEX", &aStr[0]) == 0)
		{// メッシュフィールドのテクスチャ座標の取得終了
		}
		else if (strcmp("MESHFIELD_INDEX", &aStr[0]) == 0)
		{// メッシュフィールドのインデックスを取得する
			for (int nCntidx = 0; nCntidx < MESHFIELD_INDEX; nCntidx++)
			{// 頂点数分回す
				nResult = fscanf(pFile, "%d", &pIdx[nCntidx]);
			}
		}
		else if (strcmp("MESHFIELD_INDEX", &aStr[0]) == 0)
		{// メッシュフィールドのインデックス取得終了
		}


		if (nResult == EOF)
		{// 最後まで読み切ったら終了
			break;
		}
	}

	g_pVtxBuffMeshfield->Unlock();	// 頂点バッファをアンロック
	g_pIdxBuffMeshfield->Unlock();	// インデックスバッファのアンロック

	// ファイルを閉じる
	fclose(pFile);
}