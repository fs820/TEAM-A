//----------------------------------------
//
//モデル表示処理[stage.cpp]
//Author fuma sato
//
//----------------------------------------

#include"stage.h"
#include"camera.h"
#include"input.h"
#include"shadow.h"
#include"player.h"
#include"editplayer.h"

//グローバル変数宣言
Stage g_aStage[STAGE_MAX] = {};
XFILE g_aXfile;
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	int nCntStage, nCntTex;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		g_aStage[nCntStage].pMesh = NULL;
		g_aStage[nCntStage].pBuffMat = NULL;
		for (nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
		{
			g_aStage[nCntStage].apTexture[nCntTex] = NULL;
		}
		g_aStage[nCntStage].dwNumMat = 0;
		g_aStage[nCntStage].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].fLength = 0.0f;
		g_aStage[nCntStage].fAngle = 0.0f;
		g_aStage[nCntStage].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aStage[nCntStage].nIdxShadow = -1;
		g_aStage[nCntStage].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCntStage].nNumVtx = 0;
		g_aStage[nCntStage].sizeFVF = 0;
		g_aStage[nCntStage].pVtxBuff = NULL;
		g_aStage[nCntStage].nTypeNumber = 0;
		g_aStage[nCntStage].bUse = false;
	}
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitStage(void)
{
	int nCntStage;
	unsigned int nCntTex;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		for (nCntTex = 0; nCntTex < g_aStage[nCntStage].dwNumMat; nCntTex++)
		{
			if (g_aStage[nCntStage].apTexture[nCntTex] != NULL)
			{
				g_aStage[nCntStage].apTexture[nCntTex]->Release();
				g_aStage[nCntStage].apTexture[nCntTex] = NULL;
			}
		}
		//メッシュの破棄
		if (g_aStage[nCntStage].pMesh != NULL)
		{
			g_aStage[nCntStage].pMesh->Release();
			g_aStage[nCntStage].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_aStage[nCntStage].pBuffMat != NULL)
		{
			g_aStage[nCntStage].pBuffMat->Release();
			g_aStage[nCntStage].pBuffMat = NULL;
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateStage(void)
{
	int nCntStage;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		if (g_aStage[nCntStage].bUse)
		{
			SetPositionShadow(g_aStage[nCntStage].nIdxShadow, g_aStage[nCntStage].pos);
		}
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawStage(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	int nCntStage;
	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		if (g_aStage[nCntStage].bUse)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aStage[nCntStage].mtxWorld);

			//大きさの反映
			D3DXMatrixScaling(&mtxScale, g_aStage[nCntStage].scale.x, g_aStage[nCntStage].scale.y, g_aStage[nCntStage].scale.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxScale);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aStage[nCntStage].rot.y, g_aStage[nCntStage].rot.x, g_aStage[nCntStage].rot.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxRot);

			//位置の反映
			D3DXMatrixTranslation(&mtxTrans, g_aStage[nCntStage].pos.x, g_aStage[nCntStage].pos.y, g_aStage[nCntStage].pos.z);
			D3DXMatrixMultiply(&g_aStage[nCntStage].mtxWorld, &g_aStage[nCntStage].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aStage[nCntStage].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aStage[nCntStage].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aStage[nCntStage].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャ
				pDevice->SetTexture(0, g_aStage[nCntStage].apTexture[nCntMat]);

				//モデル描画
				g_aStage[nCntStage].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------
//管理
//-----------
void SetStageManager(XFILE Xfile)
{
	g_aXfile = Xfile;
}

//-----------
//配置
//-----------
int SetStage(int nNumber, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
	int nCntStage, nCntTex;
	//デバイスの取得
	pDevice = GetDevice();

	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		if (!g_aStage[nCntStage].bUse)
		{
			//Xファイル読み込み
			D3DXLoadMeshFromX
			(
				g_aXfile.Pass[nNumber].aName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_aStage[nCntStage].pBuffMat,
				NULL,
				&g_aStage[nCntStage].dwNumMat,
				&g_aStage[nCntStage].pMesh
			);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aStage[nCntStage].pBuffMat->GetBufferPointer();

			for (nCntTex = 0; nCntTex < (int)g_aStage[nCntStage].dwNumMat; nCntTex++)
			{
				if (pMat[nCntTex].pTextureFilename != NULL)
				{//テクスチャがある
					//テクスチャの読み込み
					D3DXCreateTextureFromFile
					(
						pDevice,
						pMat[nCntTex].pTextureFilename,
						&g_aStage[nCntStage].apTexture[nCntTex]
					);
				}
			}

			//頂点数
			g_aStage[nCntStage].nNumVtx = g_aStage[nCntStage].pMesh->GetNumVertices();
			//頂点サイズ
			g_aStage[nCntStage].sizeFVF = D3DXGetFVFVertexSize(g_aStage[nCntStage].pMesh->GetFVF());
			//頂点バッファの取得
			g_aStage[nCntStage].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_aStage[nCntStage].pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < g_aStage[nCntStage].nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_aStage[nCntStage].pVtxBuff;

				if (vtx.x > g_aStage[nCntStage].vtxMax.x)
				{
					g_aStage[nCntStage].vtxMax.x = vtx.x;
				}
				if (vtx.x < g_aStage[nCntStage].vtxMin.x)
				{
					g_aStage[nCntStage].vtxMin.x = vtx.x;
				}
				if (vtx.y > g_aStage[nCntStage].vtxMax.y)
				{
					g_aStage[nCntStage].vtxMax.y = vtx.y;
				}
				if (vtx.y < g_aStage[nCntStage].vtxMin.y)
				{
					g_aStage[nCntStage].vtxMin.y = vtx.y;
				}
				if (vtx.z > g_aStage[nCntStage].vtxMax.z)
				{
					g_aStage[nCntStage].vtxMax.z = vtx.z;
				}
				if (vtx.z < g_aStage[nCntStage].vtxMin.z)
				{
					g_aStage[nCntStage].vtxMin.z = vtx.z;
				}

				g_aStage[nCntStage].pVtxBuff += g_aStage[nCntStage].sizeFVF;
			}

			g_aStage[nCntStage].pos = pos;
			g_aStage[nCntStage].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aStage[nCntStage].rot = rot;
			g_aStage[nCntStage].scale = scale;
			g_aStage[nCntStage].vtxMax.x *= g_aStage[nCntStage].scale.x;
			g_aStage[nCntStage].vtxMax.y *= g_aStage[nCntStage].scale.y;
			g_aStage[nCntStage].vtxMax.z *= g_aStage[nCntStage].scale.z;
			g_aStage[nCntStage].vtxMin.x *= g_aStage[nCntStage].scale.x;
			g_aStage[nCntStage].vtxMin.y *= g_aStage[nCntStage].scale.y;
			g_aStage[nCntStage].vtxMin.z *= g_aStage[nCntStage].scale.z;

			g_aStage[nCntStage].fLength = sqrtf((g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x) * (g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x) + (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z) * (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z)) / 2.0f;
			g_aStage[nCntStage].fAngle = atan2f((g_aStage[nCntStage].vtxMax.x - g_aStage[nCntStage].vtxMin.x), (g_aStage[nCntStage].vtxMax.z - g_aStage[nCntStage].vtxMin.z));//角度

			g_aStage[nCntStage].nIdxShadow = SetShadow(g_aStage[nCntStage].pos, g_aStage[nCntStage].rot, g_aStage[nCntStage].fLength);
			g_aStage[nCntStage].nTypeNumber = nNumber;
			g_aStage[nCntStage].bUse = true;
			break;
		}
	}

	return nCntStage;
}

//------------------------------
//消去
//------------------------------
void EndStage(int nEndNumber)
{
	if (nEndNumber != -1)
	{
		EndShadow(nEndNumber);
		g_aStage[nEndNumber].bUse = false;
	}
}

//------------------------------
//位置取得
//------------------------------
Stage* GetStage(void)
{
	return &g_aStage[0];
}

//------------------------------
//種類数取得
//------------------------------
int GetXfileNum(void)
{
	return g_aXfile.XfileNum;
}

//------------------------------
//当たり判定
//------------------------------
bool CollisionStage(Stage** pStage)
{
	bool bRanding = false;
	Player* pPlayer = GetPlayer();
	EDITPLAYER* pEditPlayer = GetEditPlayer();
	int nCntStage = 0;

	for (nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{
		if (g_aStage[nCntStage].bUse)
		{
			//y軸
			if (pPlayer->pos.x + pPlayer->aModel[0].pos.x + pPlayer->aModel[0].vtxMax.x > g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x && pPlayer->pos.x + pPlayer->aModel[0].pos.x + pPlayer->aModel[0].vtxMin.x < g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x && pPlayer->pos.z + pPlayer->aModel[0].pos.z + pPlayer->aModel[0].vtxMax.z > g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z && pPlayer->pos.z + pPlayer->aModel[0].pos.z + pPlayer->aModel[0].vtxMin.z < g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z)
			{
				//下から上
				if (pPlayer->posOld.y + pPlayer->aModel[0].pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y <= g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y && pPlayer->pos.y + pPlayer->aModel[0].pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y + g_aStage[nCntStage].move.y)
				{
					pPlayer->pos.y = g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y - pPlayer->aModel[0].pos.y - pPlayer->aModel[1].pos.y - pPlayer->aModel[1].vtxMax.y - COLLISION_TILL + g_aStage[nCntStage].move.y;
					pPlayer->move.y = 0.0f;
				}
				//上から下
				if (pPlayer->posOld.y >= g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y + g_aStage[nCntStage].move.y)
				{
					pPlayer->pos.y = g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y + COLLISION_TILL + g_aStage[nCntStage].move.y;
					pPlayer->move.y = 0.0f;
					bRanding = true;
					if (pStage != NULL)
					{
						*pStage = &g_aStage[nCntStage];
					}
				}
			}
			//x,z軸
			if (pPlayer->pos.y + pPlayer->aModel[0].pos.y + pPlayer->aModel[1].pos.y + pPlayer->aModel[1].vtxMax.y > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y && pPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y)
			{
				//x軸
				if (pPlayer->pos.z + pPlayer->aModel[0].pos.z + pPlayer->aModel[0].vtxMax.z > g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z && pPlayer->pos.z + pPlayer->aModel[0].pos.z + pPlayer->aModel[0].vtxMin.z < g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z)
				{
					//左から右
					if (pPlayer->posOld.x + pPlayer->aModel[0].pos.x + pPlayer->aModel[0].vtxMax.x <= g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x && pPlayer->pos.x + pPlayer->aModel[0].pos.x + pPlayer->aModel[0].vtxMax.x > g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x + g_aStage[nCntStage].move.x)
					{
						pPlayer->pos.x = g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x - pPlayer->aModel[0].pos.x - pPlayer->aModel[0].vtxMax.x - COLLISION_TILL + g_aStage[nCntStage].move.x;
						pPlayer->move.x = 0.0f;
					}
					//右から左
					if (pPlayer->posOld.x + pPlayer->aModel[0].pos.x + pPlayer->aModel[0].vtxMin.x >= g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x && pPlayer->pos.x + pPlayer->aModel[0].pos.x + pPlayer->aModel[0].vtxMin.x < g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x + g_aStage[nCntStage].move.x)
					{
						pPlayer->pos.x = g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x - pPlayer->aModel[0].pos.x - pPlayer->aModel[0].vtxMin.x + COLLISION_TILL + g_aStage[nCntStage].move.x;
						pPlayer->move.x = 0.0f;
					}
				}
				//z軸
				if (pPlayer->pos.x + pPlayer->aModel[0].pos.x + pPlayer->aModel[0].vtxMax.x > g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x && pPlayer->pos.x + pPlayer->aModel[0].pos.x + pPlayer->aModel[0].vtxMin.x < g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x)
				{
					//手前から奥
					if (pPlayer->posOld.z + pPlayer->aModel[0].pos.z + pPlayer->aModel[0].vtxMax.z <= g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z && pPlayer->pos.z + pPlayer->aModel[0].pos.z + pPlayer->aModel[0].vtxMax.z > g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z + g_aStage[nCntStage].move.z)
					{
						pPlayer->pos.z = g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z - pPlayer->aModel[0].pos.z - pPlayer->aModel[0].vtxMax.z - COLLISION_TILL + g_aStage[nCntStage].move.z;
						pPlayer->move.z = 0.0f;
					}
					//奥から手前
					if (pPlayer->posOld.z + pPlayer->aModel[0].pos.z + pPlayer->aModel[0].vtxMin.z >= g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z && pPlayer->pos.z + pPlayer->aModel[0].pos.z + pPlayer->aModel[0].vtxMin.z < g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z + g_aStage[nCntStage].move.z)
					{
						pPlayer->pos.z = g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z - pPlayer->aModel[0].pos.z - pPlayer->aModel[0].vtxMin.z + COLLISION_TILL + g_aStage[nCntStage].move.z;
						pPlayer->move.z = 0.0f;
					}
				}
			}

#ifdef _DEBUG
			//y軸
			if (pEditPlayer->pos.x + EDITPLAYER_WIDTH * 0.5f > g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x && pEditPlayer->pos.x + EDITPLAYER_WIDTH * -0.5f < g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x && pEditPlayer->pos.z + EDITPLAYER_WIDTH * 0.5f > g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z && pEditPlayer->pos.z + EDITPLAYER_WIDTH * -0.5f < g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z)
			{
				//下から上
				if (pEditPlayer->posOld.y + EDITPLAYER_HEIGHT <= g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y && pEditPlayer->pos.y + EDITPLAYER_HEIGHT > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y + g_aStage[nCntStage].move.y)
				{
					pEditPlayer->pos.y = g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y - EDITPLAYER_HEIGHT - COLLISION_TILL + g_aStage[nCntStage].move.y;
					pEditPlayer->move.y = 0.0f;
					if (pStage != NULL)
					{
						*pStage = &g_aStage[nCntStage];
					}
				}
				//上から下
				if (pEditPlayer->posOld.y >= g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y && pEditPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y + g_aStage[nCntStage].move.y)
				{
					pEditPlayer->pos.y = g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y + COLLISION_TILL + g_aStage[nCntStage].move.y;
					pEditPlayer->move.y = 0.0f;
					bRanding = true;
					if (pStage != NULL)
					{
						*pStage = &g_aStage[nCntStage];
					}
				}
			}
			//x,z軸
			if (pEditPlayer->pos.y + EDITPLAYER_HEIGHT > g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMin.y && pEditPlayer->pos.y < g_aStage[nCntStage].pos.y + g_aStage[nCntStage].vtxMax.y)
			{
				//x軸
				if (pEditPlayer->pos.z + EDITPLAYER_WIDTH * 0.5f > g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z && pEditPlayer->pos.z + EDITPLAYER_WIDTH * -0.5f < g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z)
				{
					//左から右
					if (pEditPlayer->posOld.x + EDITPLAYER_WIDTH * 0.5f <= g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x && pEditPlayer->pos.x + EDITPLAYER_WIDTH * 0.5f > g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x + g_aStage[nCntStage].move.x)
					{
						pEditPlayer->pos.x = g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x - EDITPLAYER_WIDTH * 0.5f - COLLISION_TILL + g_aStage[nCntStage].move.x;
						pEditPlayer->move.x = 0.0f;
						if (pStage != NULL)
						{
							*pStage = &g_aStage[nCntStage];
						}
					}
					//右から左
					if (pEditPlayer->posOld.x + EDITPLAYER_WIDTH * -0.5f >= g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x && pEditPlayer->pos.x + EDITPLAYER_WIDTH * -0.5f < g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x + g_aStage[nCntStage].move.x)
					{
						pEditPlayer->pos.x = g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x - EDITPLAYER_WIDTH * -0.5f + COLLISION_TILL + g_aStage[nCntStage].move.x;
						pEditPlayer->move.x = 0.0f;
						if (pStage != NULL)
						{
							*pStage = &g_aStage[nCntStage];
						}
					}
				}
				//z軸
				if (pEditPlayer->pos.x + EDITPLAYER_WIDTH * 0.5f > g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMin.x && pEditPlayer->pos.x + EDITPLAYER_WIDTH * -0.5f < g_aStage[nCntStage].pos.x + g_aStage[nCntStage].vtxMax.x)
				{
					//手前から奥
					if (pEditPlayer->posOld.z + EDITPLAYER_WIDTH * 0.5f <= g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z && pEditPlayer->pos.z + EDITPLAYER_WIDTH * 0.5f > g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z + g_aStage[nCntStage].move.z)
					{
						pEditPlayer->pos.z = g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMin.z - EDITPLAYER_WIDTH * 0.5f - COLLISION_TILL + g_aStage[nCntStage].move.z;
						pEditPlayer->move.z = 0.0f;
						if (pStage != NULL)
						{
							*pStage = &g_aStage[nCntStage];
						}
					}
					//奥から手前
					if (pEditPlayer->posOld.z + EDITPLAYER_WIDTH * -0.5f >= g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z && pEditPlayer->pos.z + EDITPLAYER_WIDTH * -0.5f < g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z + g_aStage[nCntStage].move.z)
					{
						pEditPlayer->pos.z = g_aStage[nCntStage].pos.z + g_aStage[nCntStage].vtxMax.z - EDITPLAYER_WIDTH * -0.5f + COLLISION_TILL + g_aStage[nCntStage].move.z;
						pEditPlayer->move.z = 0.0f;
						if (pStage != NULL)
						{
							*pStage = &g_aStage[nCntStage];
						}
					}
				}
			}
#endif
		}
	}
	return bRanding;
}

//------------------------------
//Xファイル名取得
//------------------------------
String GetXfileName(int nNumber)
{
	return g_aXfile.Pass[nNumber];
}