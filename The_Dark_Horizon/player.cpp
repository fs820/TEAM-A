//----------------------------------------
//
//モデル表示処理[player.cpp]
//Author fuma sato
//
//----------------------------------------

#include"player.h"
#include"game.h"
#include"shadow.h"
#include"camera.h"
#include"input.h"
#include"bullet.h"
#include"file.h"
#include"particle.h"
#include"meshfield.h"
#include"gage.h"

//グローバル変数宣言
Player g_Player;
MOTION_INFO g_Motion[MAX_MOTION];
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//初期化
	g_Player.pos = D3DXVECTOR3(0.1f, 0.1f, 0.0f);
	g_Player.posOld = D3DXVECTOR3(0.1f, 0.1f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Player.bJump = false;
	g_Player.fLife = MAX_HP;
	g_Player.fEnergy = MAX_ENERGY;
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.nIdxShadow = -1;
	g_Player.nIdxLife = -1;
	g_Player.pStage = NULL;

	g_Player.bLoopMotion = false;
	g_Player.motionType = MOTIONTYPE_NEUTRAL;
	g_Player.nCounterMotion = 0;
	g_Player.nKey = -1;
	g_Player.nNumKey = 0;
	g_Player.nNumMotion = 0;
	g_Player.bUse = true;

	//プレイヤー情報取得
	LoadPlayer();

	int nCntModel;
	for (nCntModel = 0;  nCntModel < g_Player.nNumModel; nCntModel++)
	{//モデル数分繰り返す
		//Xファイル読み込み
		D3DXLoadMeshFromX
		(
			g_Player.Xname[nCntModel].aName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntModel].pBuffMat,
			NULL,
			&g_Player.aModel[nCntModel].dwNumMat,
			&g_Player.aModel[nCntModel].pMesh
		);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].dwNumMat; nCntMat++)
		{//マテリアル数分繰り返す
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャがある
				//テクスチャの読み込み
				D3DXCreateTextureFromFile
				(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_Player.aModel[nCntModel].apTexture[nCntMat]
				);
			}
		}

		//頂点数
		g_Player.aModel[nCntModel].nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();
		//頂点サイズ
		g_Player.aModel[nCntModel].sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());
		//頂点バッファの取得
		g_Player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&g_Player.aModel[nCntModel].pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < g_Player.aModel[nCntModel].nNumVtx; nCntVtx++)
		{//頂点数分繰り返す
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)g_Player.aModel[nCntModel].pVtxBuff;

			//大きさの取得
			if (vtx.x > g_Player.aModel[nCntModel].vtxMax.x)
			{
				g_Player.aModel[nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.x < g_Player.aModel[nCntModel].vtxMin.x)
			{
				g_Player.aModel[nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y > g_Player.aModel[nCntModel].vtxMax.y)
			{
				g_Player.aModel[nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.y < g_Player.aModel[nCntModel].vtxMin.y)
			{
				g_Player.aModel[nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z > g_Player.aModel[nCntModel].vtxMax.z)
			{
				g_Player.aModel[nCntModel].vtxMax.z = vtx.z;
			}
			if (vtx.z < g_Player.aModel[nCntModel].vtxMin.z)
			{
				g_Player.aModel[nCntModel].vtxMin.z = vtx.z;
			}

			g_Player.aModel[nCntModel].pVtxBuff += g_Player.aModel[nCntModel].sizeFVF;
		}

		g_Player.aModel[nCntModel].vtxMinDef = g_Player.aModel[nCntModel].vtxMin;
		g_Player.aModel[nCntModel].vtxMaxDef = g_Player.aModel[nCntModel].vtxMax;

		//オフセットを保存
		g_Player.aModel[nCntModel].posDef = g_Player.aModel[nCntModel].pos;
	}

	//影の登録
	g_Player.nIdxShadow = SetShadow(g_Player.pos, g_Player.rot, 100.0f);
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitPlayer(void)
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		for (unsigned int i = 0; i < g_Player.aModel[nCntModel].dwNumMat; i++)
		{
			if (g_Player.aModel[nCntModel].apTexture[i] != NULL)
			{
				g_Player.aModel[nCntModel].apTexture[i]->Release();
				g_Player.aModel[nCntModel].apTexture[i] = NULL;
			}
		}
		//メッシュの破棄
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}
		//マテリアルの破棄
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdatePlayer(void)
{
	if (g_Player.bUse)
	{
		Camera* pCamera = GetCamera();
		float* pStick;

		//移動処理

		if (IsXInputControllerConnected(CONTROLLER_1))
		{
			//左スティック処理
			pStick = GetJoyStick(STICK_LEFT, CONTROLLER_1);
			if (sqrtf(*pStick * *pStick + *(pStick + 1) * *(pStick + 1)) >= STICK_DED)
			{
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f + -atan2f(*(pStick + 1), *pStick)) * SPEED;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}

		if (GetKeyboradPress(DIK_A) == true || GetJoykeyPress(JOYKEY_LEFT, CONTROLLER_1) == true)//Aキー
		{
			if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
			{//左上移動
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * SPEED;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
			{//左下移動
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * SPEED;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else
			{//左移動
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * SPEED;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		else if (GetKeyboradPress(DIK_D) == true || GetJoykeyPress(JOYKEY_RIGHT, CONTROLLER_1) == true)//Dキー
		{
			if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
			{//右上移動
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * SPEED;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
			{//右下移動
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * SPEED;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
			else
			{//右移動
				g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * SPEED;
				if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
				{
					g_Player.motionType = MOTIONTYPE_MOVE;
				}
			}
		}
		else if (GetKeyboradPress(DIK_W) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
		{//上移動
			g_Player.move.x += sinf(pCamera->rot.y) * SPEED;
			g_Player.move.z += cosf(pCamera->rot.y) * SPEED;
			if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
			{
				g_Player.motionType = MOTIONTYPE_MOVE;
			}
		}
		else if (GetKeyboradPress(DIK_S) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
		{//下移動
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * SPEED;
			g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * SPEED;
			if (g_Player.motionType != MOTIONTYPE_JUMP && g_Player.motionType != MOTIONTYPE_LANDING && g_Player.motionType != MOTIONTYPE_ACTION)
			{
				g_Player.motionType = MOTIONTYPE_MOVE;
			}
		}

		if (GetKeyboradTrigger(DIK_SPACE) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_1) == true)//Sキー
		{//ジャンプ
			if (!g_Player.bJump)
			{
				g_Player.move.y += JUMP;
				g_Player.bJump = true;
				g_Player.motionType = MOTIONTYPE_JUMP;
			}
		}

		if (GetKeyboradTrigger(DIK_RETURN) == true || GetMouseTrigger(MOUSE_LEFT) == true || GetJoykeyTrigger(JOYKEY_X, CONTROLLER_1) == true)
		{//攻撃
			//g_Player.motionType = MOTIONTYPE_ACTION;
			if (SetEnergygage())
			{//エネルギーがあれば
				SetBullet(g_Player.pos + g_Player.aModel[0].pos + D3DXVECTOR3(0.0f, g_Player.aModel[2].pos.y, 0.0f), -D3DXVECTOR3(sinf(g_Player.rot.y) * cosf(g_Player.rot.x), sinf(g_Player.rot.x), cosf(g_Player.rot.y) * cosf(g_Player.rot.x)), g_Player.aModel[3].scale);
			}
		}

		//カメラと同じ方向を向く
		g_Player.Destrot.y = pCamera->rot.y;

		g_Player.move.y += GRAVITY;//重力

		//ジャンプ補正
		if (g_Player.bJump)
		{
			g_Player.move.x *= JUMP_INA;
			g_Player.move.z *= JUMP_INA;
		}

		g_Player.posOld = g_Player.pos;//過去の位置を保存

		//位置の更新
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;
		g_Player.pos.z += g_Player.move.z;

		//移動量の更新(減衰)
		g_Player.move.x += (SPEED_DEF - g_Player.move.x) * PLAYER_INA;
		g_Player.move.z += (SPEED_DEF - g_Player.move.z) * PLAYER_INA;

		g_Player.pStage = NULL;

		g_Player.bJump = !CollisionStage(&g_Player.pStage);//当たり判定

		D3DXVECTOR3 dummy;	// 使わない引数用
		g_Player.bJump = !CollisionMeshField(&dummy ,&dummy ,&g_Player.pos, &g_Player.move);//当たり判定

		if (g_Player.pStage != NULL)
		{
			g_Player.pos += g_Player.pStage->move;
		}

		if (g_Player.pos.x < -GAME_WALL)
		{
			g_Player.pos.x = -GAME_WALL;
		}
		if (g_Player.pos.x > GAME_WALL)
		{
			g_Player.pos.x = GAME_WALL;
		}
		if (g_Player.pos.z < -GAME_WALL)
		{
			g_Player.pos.z = -GAME_WALL;
		}
		if (g_Player.pos.z > GAME_WALL)
		{
			g_Player.pos.z = GAME_WALL;
		}

		
		if (sqrtf(g_Player.move.x * g_Player.move.x + g_Player.move.z * g_Player.move.z) < 0.3f && g_Player.motionType == MOTIONTYPE_MOVE)
		{//移動値がほとんどなくなったら

			//停止状態
			g_Player.move.x = 0.0f;
			g_Player.move.z = 0.0f;
			g_Player.motionType = MOTIONTYPE_NEUTRAL;
		}

		//正規化
		if (g_Player.Destrot.y > D3DX_PI)
		{
			g_Player.Destrot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player.Destrot.y < -D3DX_PI)
		{
			g_Player.Destrot.y += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Player.Destrot.y - g_Player.rot.y > D3DX_PI)
		{
			g_Player.Destrot.y = g_Player.rot.y + ((g_Player.Destrot.y - g_Player.rot.y) - D3DX_PI * 2.0f);
		}
		else if (g_Player.Destrot.y - g_Player.rot.y < -D3DX_PI)
		{
			g_Player.Destrot.y = g_Player.rot.y + ((g_Player.Destrot.y - g_Player.rot.y) + D3DX_PI * 2.0f);
		}

		g_Player.rot.y += (g_Player.Destrot.y - g_Player.rot.y) * ROT_SPEED;//角度更新

		//正規化
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Player.Destrot.x > D3DX_PI)
		{
			g_Player.Destrot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Player.Destrot.x < -D3DX_PI)
		{
			g_Player.Destrot.x += D3DX_PI * 2.0f;
		}

		//正規化
		if (g_Player.Destrot.x - g_Player.rot.x > D3DX_PI)
		{
			g_Player.Destrot.x = g_Player.rot.x + ((g_Player.Destrot.x - g_Player.rot.x) - D3DX_PI * 2.0f);
		}
		else if (g_Player.Destrot.x - g_Player.rot.x < -D3DX_PI)
		{
			g_Player.Destrot.x = g_Player.rot.x + ((g_Player.Destrot.x - g_Player.rot.x) + D3DX_PI * 2.0f);
		}

		g_Player.rot.x += (g_Player.Destrot.x - g_Player.rot.x) * ROT_SPEED;//角度更新

		//正規化
		if (g_Player.rot.x > D3DX_PI)
		{
			g_Player.rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Player.rot.x < -D3DX_PI)
		{
			g_Player.rot.x += D3DX_PI * 2.0f;
		}

		int nCntModel;
		for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{//パーツ分回す

			//スケールの反映
			g_Player.aModel[nCntModel].vtxMax.x = g_Player.aModel[nCntModel].vtxMaxDef.x * g_Player.scale.x;
			g_Player.aModel[nCntModel].vtxMax.y = g_Player.aModel[nCntModel].vtxMaxDef.y * g_Player.scale.y;
			g_Player.aModel[nCntModel].vtxMax.z = g_Player.aModel[nCntModel].vtxMaxDef.z * g_Player.scale.z;
			g_Player.aModel[nCntModel].vtxMin.x = g_Player.aModel[nCntModel].vtxMinDef.x * g_Player.scale.x;
			g_Player.aModel[nCntModel].vtxMin.y = g_Player.aModel[nCntModel].vtxMinDef.y * g_Player.scale.y;
			g_Player.aModel[nCntModel].vtxMin.z = g_Player.aModel[nCntModel].vtxMinDef.z * g_Player.scale.z;
		}

		//UpdateMotion();

		//モーション用
		//if (g_Player.motionType == MOTIONTYPE_ACTION && g_Player.nKey == 3 && g_Player.nCounterMotion == 11)
		//{
		//	SetBullet(g_Player.pos + g_Player.aModel[0].pos, D3DXVECTOR3(sinf(g_Player.rot.y + g_Player.aModel[0].rot.y + g_Player.aModel[2].rot.y + g_Player.aModel[3].rot.y) * cosf(g_Player.rot.x + g_Player.aModel[0].rot.x + g_Player.aModel[2].rot.x + g_Player.aModel[3].rot.x), sinf(g_Player.rot.x + g_Player.aModel[0].rot.x + g_Player.aModel[2].rot.x + g_Player.aModel[3].rot.x), cosf(g_Player.rot.y + g_Player.aModel[0].rot.y + g_Player.aModel[2].rot.y + g_Player.aModel[3].rot.y) * cosf(g_Player.rot.x + g_Player.aModel[0].rot.x + g_Player.aModel[2].rot.x + g_Player.aModel[3].rot.x)), g_Player.aModel[3].scale);
		//}

		//状態管理
		switch (g_Player.state)
		{
		case PLAYERSTATE_APPEAR:
			g_Player.bUse = false;//終了
			break;
		case PLAYERSTATE_NORMAL:
			if (g_Player.fLife <= 0.0f)
			{//ライフがなくなった
				g_Player.state = PLAYERSTATE_DIE;//死んでいる
			}
			SetPositionShadow(g_Player.nIdxShadow, g_Player.pos);//影の移動
			break;
		case PLAYERSTATE_DIE:
			g_Player.Destrot.x = D3DX_PI * 0.5f;//倒れる
			static int nCnt = 0;
			nCnt++;
			if (nCnt >= 20)
			{//少したったら
				EndShadow(g_Player.nIdxShadow);//影を消す
				SetParticle(g_Player.pos, g_Player.scale);//演出
				g_Player.state = PLAYERSTATE_APPEAR;//プレイヤー未使用
			}
			break;
		}
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawPlayer(void)
{
	if (g_Player.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
		D3DXMATRIX mtxRot, mtxTrans, mtxScale;//計算マトリックス
		D3DMATERIAL9 matDef;//現在のマテリアル保存用
		D3DXMATERIAL* pMat;//マテリアルデータへのポインタ


		//デバイスの取得
		pDevice = GetDevice();

		//マトリックス初期化
		D3DXMatrixIdentity(&g_Player.mtxWorld);

		//大きさの反映
		D3DXMatrixScaling(&mtxScale, g_Player.scale.x, g_Player.scale.y, g_Player.scale.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScale);

		//向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

		//位置の反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

		int nCntModel;
		//パーツ分回す
		for (nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel, mtxScaleModel;//計算マトリックス
			D3DXMATRIX mtxParent;
			//マトリックス初期化
			D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

			//大きさの反映
			D3DXMatrixScaling(&mtxScaleModel, g_Player.aModel[nCntModel].scale.x, g_Player.aModel[nCntModel].scale.y, g_Player.aModel[nCntModel].scale.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxScaleModel);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置の反映
			D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの親のマトリックスの設定
			if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある
				mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{//親モデルがない
				mtxParent = g_Player.mtxWorld;
			}

			D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				//テクスチャ
				pDevice->SetTexture(0, g_Player.aModel[nCntModel].apTexture[nCntMat]);

				//モデル描画
				g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			pDevice->SetMaterial(&matDef);
		}
	}
}

//------------------------------
//位置取得
//------------------------------
Player* GetPlayer(void)
{
	return &g_Player;
}

//------------------------------
//モーション
//------------------------------
void UpdateMotion(void)
{
	static MOTIONTYPE OldMotion = MOTIONTYPE_NEUTRAL;
	static int BlendCnt = 0;
	if (OldMotion != g_Player.motionType)
	{
		g_Player.aMotionInfo[OldMotion] = g_Motion[OldMotion];
		g_Player.aMotionInfo[g_Player.motionType] = g_Motion[g_Player.motionType];

		for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
		{
			D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosX, g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosY, g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 Destpos = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fPosZ);
			D3DXVECTOR3 posDif = Destpos - Oldpos;

			D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotX, g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotY, g_Player.aMotionInfo[OldMotion].aKeyInfo[g_Player.aMotionInfo[OldMotion].nNumKey - 1].aKey[nCntModel].fRotZ);
			D3DXVECTOR3 Destrot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[0].aKey[nCntModel].fRotZ);

			//正規化
			if (Destrot.x - Oldrot.x > D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
			}
			else if (Destrot.x - Oldrot.x < -D3DX_PI)
			{
				Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
			}
			//正規化
			if (Destrot.y - Oldrot.y > D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
			}
			else if (Destrot.y - Oldrot.y < -D3DX_PI)
			{
				Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
			}
			//正規化
			if (Destrot.z - Oldrot.z > D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
			}
			else if (Destrot.z - Oldrot.z < -D3DX_PI)
			{
				Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
			}

			D3DXVECTOR3 rotDif = Destrot - Oldrot;

			g_Player.aModel[nCntModel].pos = g_Player.aModel[nCntModel].posDef + Oldpos + posDif * (BlendCnt / BLEND_FRAME);
			g_Player.aModel[nCntModel].rot = Oldrot + rotDif * (BlendCnt / BLEND_FRAME);

			//正規化
			if (g_Player.aModel[nCntModel].rot.x > D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			else if (g_Player.aModel[nCntModel].rot.x < -D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_Player.aModel[nCntModel].rot.y > D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			else if (g_Player.aModel[nCntModel].rot.y < -D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}
			//正規化
			if (g_Player.aModel[nCntModel].rot.z > D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			else if (g_Player.aModel[nCntModel].rot.z < -D3DX_PI)
			{
				g_Player.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

		if (BlendCnt == (int)BLEND_FRAME)
		{
			BlendCnt = 0;
			OldMotion = g_Player.motionType;
			return;
		}
		BlendCnt++;
		return;
	}
	g_Player.aMotionInfo[g_Player.motionType] = g_Motion[g_Player.motionType];
	g_Player.nNumKey = g_Player.aMotionInfo[g_Player.motionType].nNumKey;
	g_Player.bLoopMotion = g_Player.aMotionInfo[g_Player.motionType].bLoop;
	static int nDestKey = g_Player.nKey + 1;

	if (g_Player.nCounterMotion >= g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame)
	{
		g_Player.nCounterMotion = 0;
	}

	if (g_Player.nCounterMotion == 0)
	{
		if (nDestKey >= g_Player.nNumKey - 1)
		{
			if (g_Player.bLoopMotion)
			{
				g_Player.nKey++;
				nDestKey = 0;

				for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
				{
					g_Player.aModel[nCntModel].pos = g_Player.aModel[nCntModel].posDef + D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ);
					g_Player.aModel[nCntModel].rot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ);
				}
			}
			else
			{
				g_Player.nKey = -1;
				nDestKey = g_Player.nKey + 1;
				g_Player.motionType = MOTIONTYPE_NEUTRAL;
				return;
			}
		}
		else
		{
			g_Player.nKey++;
			if (g_Player.nKey > g_Player.nNumKey - 1)
			{
				g_Player.nKey = 0;
			}
			nDestKey = g_Player.nKey + 1;

			for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
			{
				g_Player.aModel[nCntModel].pos = g_Player.aModel[nCntModel].posDef + D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ);
				g_Player.aModel[nCntModel].rot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ);
			}
		}
	}
	
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXVECTOR3 Oldpos = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 Destpos = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fPosZ);
		D3DXVECTOR3 posDif = Destpos - Oldpos;

		D3DXVECTOR3 Oldrot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].aKey[nCntModel].fRotZ);
		D3DXVECTOR3 Destrot = D3DXVECTOR3(g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotX, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotY, g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[nDestKey].aKey[nCntModel].fRotZ);

		//正規化
		if (Destrot.x - Oldrot.x > D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) - D3DX_PI * 2.0f);
		}
		else if (Destrot.x - Oldrot.x < -D3DX_PI)
		{
			Destrot.x = Oldrot.x + ((Destrot.x - Oldrot.x) + D3DX_PI * 2.0f);
		}
		//正規化
		if (Destrot.y - Oldrot.y > D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) - D3DX_PI * 2.0f);
		}
		else if (Destrot.y - Oldrot.y < -D3DX_PI)
		{
			Destrot.y = Oldrot.y + ((Destrot.y - Oldrot.y) + D3DX_PI * 2.0f);
		}
		//正規化
		if (Destrot.z - Oldrot.z > D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) - D3DX_PI * 2.0f);
		}
		else if (Destrot.z - Oldrot.z < -D3DX_PI)
		{
			Destrot.z = Oldrot.z + ((Destrot.z - Oldrot.z) + D3DX_PI * 2.0f);
		}

		D3DXVECTOR3 rotDif = Destrot - Oldrot;

		g_Player.aModel[nCntModel].pos = g_Player.aModel[nCntModel].posDef + Oldpos + posDif * (g_Player.nCounterMotion / (float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);
		g_Player.aModel[nCntModel].rot = Oldrot + rotDif * (g_Player.nCounterMotion / (float)g_Player.aMotionInfo[g_Player.motionType].aKeyInfo[g_Player.nKey].nFrame);

		//正規化
		if (g_Player.aModel[nCntModel].rot.x > D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		else if (g_Player.aModel[nCntModel].rot.x < -D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_Player.aModel[nCntModel].rot.y > D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		else if (g_Player.aModel[nCntModel].rot.y < -D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}
		//正規化
		if (g_Player.aModel[nCntModel].rot.z > D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		else if (g_Player.aModel[nCntModel].rot.z < -D3DX_PI)
		{
			g_Player.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
	g_Player.nCounterMotion++;
}

//------------------------------------------------
//衝突
//------------------------------------------------
void CollisionPlayer(D3DXVECTOR3 pos, float Length)
{
	float Space = sqrtf((pos.x - g_Player.pos.x) * (pos.x - g_Player.pos.x) + (pos.y - g_Player.pos.y) * (pos.y - g_Player.pos.y) + (pos.z - g_Player.pos.z) * (pos.z - g_Player.pos.z));
	if (Space < PLAYER_SIZE * 0.5f + Length * 0.5f)
	{
		Space = (PLAYER_SIZE * 0.5f + Length * 0.5f) - Space;
		D3DXVECTOR3 Hitvec = g_Player.pos - pos;
		D3DXVec3Normalize(&Hitvec, &Hitvec);
		g_Player.move += Hitvec * Space;
	}
}