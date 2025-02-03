#include "enemy.h"

// グローバル変数宣言
ENEMY g_aEnemy[MAX_ENEMY];	// エネミー情報

//**************************************************
// エネミーの初期化
//**************************************************
void InitEnemy(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 最大エネミー分回す
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		// 位置
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量

		g_aEnemy[nCntEnemy].charParam.bUse = false;
	}

	g_aEnemy[0].charParam.bUse = true;

	// スクリプト読み込み
	ReadScript("data\\tetsuji\\text\\motion.txt", &g_aEnemy[0].motion, &g_aEnemy[0].aModelEnemy[0], &g_aEnemy[0].charParam);

	int i = 0;
}

//**************************************************
// エネミーの終了
//**************************************************
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 最大エネミー分回す
		for (int nCntModel = 0; nCntModel < MAX_MODELE_PARTS_ENEMY; nCntModel++)
		{// モデルパーツ数分回す
			for (int nCntTex = 0; nCntTex < MAX_MODEL_TEXTURE; nCntTex++)
			{// モデルパーツ数分回す
				if (g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].apTexture[nCntTex] != NULL)
				{// テクスチャがあったら破棄
					g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].apTexture[nCntTex]->Release();
					g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].apTexture[nCntTex] = NULL;
				}
			}

			if (g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pBuffMat != NULL)
			{// マテリアルがあれば破棄
				g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pBuffMat->Release();
				g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pBuffMat = NULL;
			}

			if (g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pMesh != NULL)
			{// メッシュがあれば破棄
				g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pMesh->Release();
				g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pMesh = NULL;
			}
		}
	}
}

//**************************************************
// エネミーの更新
//**************************************************
void UpdateEnemy(void)
{
	
}

//**************************************************
// エネミーの描画
//**************************************************
void DrawEnemy(void)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].charParam.bUse)
		{
			// デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// 計算用マトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			// 現在のマテリアル保存用
			D3DMATERIAL9 matDef;

			// マテリアルデータへのポインタ
			D3DXMATERIAL* pMat;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[nCnt].mtxWorldEnemy);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCnt].rot.y, g_aEnemy[nCnt].rot.x, g_aEnemy[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCnt].pos.x, g_aEnemy[nCnt].pos.y, g_aEnemy[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCnt].mtxWorldEnemy);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// 全モデル(パーツ)の描画
			for (int nCntModel = 0; nCntModel < g_aEnemy[nCnt].charParam.nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
				D3DXMATRIX mtxParent;					// 親マトリックス

				// パーツのワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld);

				// パーツの向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCnt].aModelEnemy[nCntModel].rot.y, g_aEnemy[nCnt].aModelEnemy[nCntModel].rot.x, g_aEnemy[nCnt].aModelEnemy[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld, &mtxRotModel);

				// パーツの位置(オフセット)を反映
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCnt].aModelEnemy[nCntModel].pos.x, g_aEnemy[nCnt].aModelEnemy[nCntModel].pos.y, g_aEnemy[nCnt].aModelEnemy[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld, &mtxTransModel);

				// パーツ「親のマトリックス」を設定
				if (g_aEnemy[nCnt].aModelEnemy[nCntModel].nIdxModelEnemyParent != -1)
				{// 親モデルがある場合
					mtxParent = g_aEnemy[nCnt].aModelEnemy[g_aEnemy[nCnt].aModelEnemy[nCntModel].nIdxModelEnemyParent].mtxWorld;	// 親モデルのインデックスを設定
				}
				else
				{// 親のモデルがない場合
					mtxParent = g_aEnemy[nCnt].mtxWorldEnemy;	// プレイヤーのマトリックスを設定
				}

				// 算出したパーツのワールドマトリックスと親マトリックスをかけ合わせる
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld,
					&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld,
					&mtxParent);

				// パーツのワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD,
					&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aEnemy[nCnt].aModelEnemy[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCnt].aModelEnemy[nCntModel].dwNumMat; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャの設定
					pDevice->SetTexture(0, g_aEnemy[nCnt].aModelEnemy[nCntModel].apTexture[nCntMat]);

					// パーツの描画
					g_aEnemy[nCnt].aModelEnemy[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

