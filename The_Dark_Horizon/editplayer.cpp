//*********************************************************************************************
//
// エディターで使うプレイヤーの処理
// Aouther Tetsuji Yamamoto
// 
//*********************************************************************************************
#include "editplayer.h"
#include "camera.h"
#include "input.h"
#include "meshfield.h"
#include "file.h"
#include "shadow.h"

// グローバル変数宣言
EDITPLAYER g_editPlayer;	// エディットプレイヤー情報
int g_nNumber = 0;

//*********************************************************************************************
// エディットプレイヤーの初期化
//*********************************************************************************************
void InitEditPlayer()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 各種変数の初期化
	g_editPlayer.pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		// 位置
	g_editPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 古い位置
	g_editPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
	g_editPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	g_editPlayer.movement = 2.0f;							// 移動量
	g_editPlayer.graviment = 0.0f;							// 重力量
	g_editPlayer.jumpment = 20.0f;							// ジャンプ量
	g_editPlayer.Type = MESH;                               //エディットタイプ
	g_editPlayer.pStage = NULL;                             //ステージポインタ
	g_editPlayer.bDisp = true;								// 映すかどうか

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data\\tetsuji\\model\\Player_UFO_001.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_editPlayer.pBuffMat,
		NULL,
		&g_editPlayer.dwNumMat,
		&g_editPlayer.pMesh);

	//マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_editPlayer.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_editPlayer.dwNumMat; nCntMat++)
	{// マテリアル分回す
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// テクスチャファイルが存在する

			// このファイル名を使用してテクスチャを読み込む
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_editPlayer.apTexture[nCntMat]);
		}
	}
}

//*********************************************************************************************
// エディットプレイヤーの終了
//*********************************************************************************************
void UninitEditPlayer()
{
	// メッシュの破棄
	if (g_editPlayer.pMesh != NULL)
	{
		g_editPlayer.pMesh->Release();
		g_editPlayer.pMesh = NULL;
	}

	// マテリアルの破棄
	if (g_editPlayer.pBuffMat != NULL)
	{
		g_editPlayer.pBuffMat->Release();
		g_editPlayer.pBuffMat = NULL;
	}

	for (int nCntTex = 0; nCntTex < MAX_EDITPLAYER_TEX_NUM; nCntTex++)
	{
		// テクスチャの破棄
		if (g_editPlayer.apTexture[nCntTex] != NULL)
		{
			g_editPlayer.apTexture[nCntTex]->Release();
			g_editPlayer.apTexture[nCntTex] = NULL;
		}
	}
}

//*********************************************************************************************
// エディットプレイヤーの更新
//*********************************************************************************************
void UpdateEditPlayer()
{
	//エディットモード切替
	if (GetKeyboradTrigger(DIK_F9))
	{
		g_editPlayer.Type = (EDITTYPE)!g_editPlayer.Type;
	}

	//エディットモードで処理をかえる
	switch (g_editPlayer.Type)
	{
	case MESH:
		EditPlayerManagerMesh();	// エディットプレイヤーの管理(Mesh)
		break;
	case OBJECT:
		EditPlayerManagerObject();  // エディットプレイヤーの管理(Object)
		break;
	}
}

//*********************************************************************************************
// エディットプレイヤーの描画
//*********************************************************************************************
void DrawEditPlayer()
{
	if (g_editPlayer.bDisp)
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
		D3DXMatrixIdentity(&g_editPlayer.mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_editPlayer.rot.y, g_editPlayer.rot.x, g_editPlayer.rot.z);
		D3DXMatrixMultiply(&g_editPlayer.mtxWorld, &g_editPlayer.mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_editPlayer.pos.x, g_editPlayer.pos.y, g_editPlayer.pos.z);
		D3DXMatrixMultiply(&g_editPlayer.mtxWorld, &g_editPlayer.mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_editPlayer.mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_editPlayer.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_editPlayer.dwNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_editPlayer.apTexture[nCntMat]);

			// モデル(パーツの描画)
			g_editPlayer.pMesh->DrawSubset(nCntMat);
		}

		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//*********************************************************************************************
// エディットプレイヤーの管理(Mesh)
//*********************************************************************************************
void EditPlayerManagerMesh()
{
	Camera* pCamera = GetCamera();				// カメラの取得

	// カメラに対して移動する処理--------------------------------------------------------------
	if (GetKeyboradPress(DIK_LSHIFT) || GetJoykeyPress(JOYKEY_LB, CONTROLLER_1))
	{// Lシフト長押し
		// コマンド処理
		if (GetKeyboradPress(DIK_W))
		{// 移動量上昇
			g_editPlayer.movement += 0.1f;
		}
		else if (GetKeyboradPress(DIK_S))
		{// 移動減少
			g_editPlayer.movement -= 0.1f;
		}
		else if (GetKeyboradPress(DIK_A))
		{// 移動ゼロ
			g_editPlayer.movement = 0.0f;
		}

		if (GetKeyboradTrigger(DIK_Q))
		{// 重力上昇
			g_editPlayer.graviment += 0.1f;
		}
		else if (GetKeyboradTrigger(DIK_E))
		{// 重力減少
			g_editPlayer.graviment -= 0.1f;
		}
		else if (GetKeyboradTrigger(DIK_D))
		{// 重力ゼロ
			g_editPlayer.graviment = 0.0f;
		}

		if (GetKeyboradPress(DIK_Z))
		{// 重力上昇
			g_editPlayer.jumpment += 0.1f;
		}
		else if (GetKeyboradPress(DIK_X))
		{// 重力減少
			g_editPlayer.jumpment -= 0.1f;
		}
		else if (GetKeyboradPress(DIK_C))
		{// 重力ゼロ
			g_editPlayer.jumpment = 0.0f;
		}

		if (GetJoykeyPress(JOYKEY_L3, CONTROLLER_1))
		{// 上移動
			g_editPlayer.move.y += g_editPlayer.movement;
		}

		if (GetKeyboradTrigger(DIK_SPACE))
		{// 位置リセット,位置は注視点
			g_editPlayer.pos = pCamera->posR;
		}

	}
	else
	{
		bool bMove = false;
		float fMoveX = 0.0f;
		float fMoveZ = 0.0f;

		if (GetKeyboradPress(DIK_W))
		{// 前移動
			bMove = true;
			fMoveZ = 1.0f;
		}
		else if (GetKeyboradPress(DIK_S))
		{// 手前移動
			bMove = true;
			fMoveZ = -1.0f;
		}

		if (GetKeyboradPress(DIK_A))
		{// 左移動
			bMove = true;
			fMoveX = -1.0f;
		}
		else if (GetKeyboradPress(DIK_D))
		{// 右移動
			bMove = true;
			fMoveX = 1.0f;
		}

		if (GetKeyboradPress(DIK_Q))
		{// 上移動
			g_editPlayer.move.y += g_editPlayer.movement;
		}
		else if (GetKeyboradPress(DIK_E) || GetJoykeyPress(JOYKEY_L3, CONTROLLER_1))
		{// 下移動
			g_editPlayer.move.y -= g_editPlayer.movement;
		}

		if (GetKeyboradTrigger(DIK_SPACE))
		{// ジャンプ
			g_editPlayer.move.y += g_editPlayer.jumpment;
		}

		if (GetKeyboradPress(DIK_RSHIFT) || GetJoykeyPress(JOYKEY_RB,CONTROLLER_1))
		{// 押している間
			VertexMoveMeshField(g_editPlayer.pos, g_editPlayer.move, 50.0f);
		}
		if (GetKeyboradRelease(DIK_RSHIFT) || GetJoykeyRelease(JOYKEY_RB, CONTROLLER_1))
		{// 離したら
			// 法線再設定
			ResetNorVectolMeshField();
		}

		// Lスティックでの移動
		float fSticRot = pCamera->rot.y + atan2f(*GetJoyStick(STICK_LEFT, CONTROLLER_1), *(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1));	// スティックを角度へ変換

		float fMoveMax = sqrtf((32767.0f * 32767.0f) + (32767.0f * 32767.0f));
		float fMoveNow = sqrtf((*GetJoyStick(STICK_LEFT, CONTROLLER_1) * *GetJoyStick(STICK_LEFT, CONTROLLER_1)) + (*(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1) * *(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1)));
		float fMove = g_editPlayer.movement * (fMoveNow / fMoveMax);

		g_editPlayer.move.x += sinf(fSticRot) * fMove;
		g_editPlayer.move.z += cosf(fSticRot) * fMove;

		if (bMove)
		{// 動きます！
			float fKeyRot = pCamera->rot.y + atan2f(fMoveX, fMoveZ);	// 角度へ変換
			g_editPlayer.move.x += sinf(fKeyRot) * g_editPlayer.movement;
			g_editPlayer.move.z += cosf(fKeyRot) * g_editPlayer.movement;
		}
	}

	// エディプレイヤーが目的の方向へ向く処理
	g_editPlayer.rot.y = atan2f(g_editPlayer.move.x, g_editPlayer.move.z) + D3DX_PI;

	// 重力
	g_editPlayer.move.y += g_editPlayer.graviment;

	//位置の保存
	g_editPlayer.posOld = g_editPlayer.pos;

	// 位置の更新
	g_editPlayer.pos += g_editPlayer.move;

	D3DXVECTOR3 dummy;	// 使わない引数用
	CollisionMeshField(&dummy,&dummy,&g_editPlayer.pos, &g_editPlayer.move);

	if (g_editPlayer.pos.y <= -10.0f)
	{// エディプレイヤーの限界高度以下になったら
		g_editPlayer.pos.y = -10.0f;
		g_editPlayer.move.y = 0.0f;
	}

	// 慣性
	g_editPlayer.move.x += (-g_editPlayer.move.x) * 0.3f;
	g_editPlayer.move.y += (-g_editPlayer.move.y) * 0.3f;
	g_editPlayer.move.z += (-g_editPlayer.move.z) * 0.3f;
}

//*********************************************************************************************
// エディットプレイヤーの管理(Object)
//*********************************************************************************************
void EditPlayerManagerObject()
{
	Camera* pCamera = GetCamera();				              // カメラの取得
	static D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		               rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		               scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); // オブジェクト設置用
	static int EndNumber = -1, CollNumber = -1;                    //オブジェクトナンバー

	// カメラに対して移動する処理--------------------------------------------------------------
	if (GetKeyboradPress(DIK_LSHIFT) || GetJoykeyPress(JOYKEY_LB, CONTROLLER_1))
	{// Lシフト長押し
		// コマンド処理
		if (GetKeyboradPress(DIK_W))
		{// 移動量上昇
			g_editPlayer.movement += 0.1f;
		}
		else if (GetKeyboradPress(DIK_S))
		{// 移動減少
			g_editPlayer.movement -= 0.1f;
		}
		else if (GetKeyboradPress(DIK_A))
		{// 移動ゼロ
			g_editPlayer.movement = 0.0f;
		}

		if (GetKeyboradTrigger(DIK_Q))
		{// 重力上昇
			g_editPlayer.graviment += 0.1f;
		}
		else if (GetKeyboradTrigger(DIK_E))
		{// 重力減少
			g_editPlayer.graviment -= 0.1f;
		}
		else if (GetKeyboradTrigger(DIK_D))
		{// 重力ゼロ
			g_editPlayer.graviment = 0.0f;
		}

		if (GetKeyboradPress(DIK_Z))
		{// 重力上昇
			g_editPlayer.jumpment += 0.1f;
		}
		else if (GetKeyboradPress(DIK_X))
		{// 重力減少
			g_editPlayer.jumpment -= 0.1f;
		}
		else if (GetKeyboradPress(DIK_C))
		{// 重力ゼロ
			g_editPlayer.jumpment = 0.0f;
		}

		if (GetJoykeyPress(JOYKEY_L3, CONTROLLER_1))
		{// 上移動
			g_editPlayer.move.y += g_editPlayer.movement;
		}

		if (GetKeyboradTrigger(DIK_SPACE))
		{// 位置リセット,位置は注視点
			g_editPlayer.pos = pCamera->posR;
		}

	}
	else
	{
		bool bMove = false;
		float fMoveX = 0.0f;
		float fMoveZ = 0.0f;

		if (GetKeyboradPress(DIK_W))
		{// 前移動
			bMove = true;
			fMoveZ = 1.0f;
		}
		else if (GetKeyboradPress(DIK_S))
		{// 手前移動
			bMove = true;
			fMoveZ = -1.0f;
		}

		if (GetKeyboradPress(DIK_A))
		{// 左移動
			bMove = true;
			fMoveX = -1.0f;
		}
		else if (GetKeyboradPress(DIK_D))
		{// 右移動
			bMove = true;
			fMoveX = 1.0f;
		}

		if (GetKeyboradPress(DIK_Q))
		{// 上移動
			g_editPlayer.move.y += g_editPlayer.movement;
		}
		else if (GetKeyboradPress(DIK_E))
		{// 下移動
			g_editPlayer.move.y -= g_editPlayer.movement;
		}

		if (GetKeyboradTrigger(DIK_SPACE))
		{// ジャンプ
			g_editPlayer.move.y += g_editPlayer.jumpment;
		}

		if (GetKeyboradTrigger(DIK_RIGHT))
		{// オブジェクト切替
			g_nNumber++;
		}
		else if (GetKeyboradTrigger(DIK_LEFT))
		{// オブジェクト切替
			g_nNumber--;
		}

		if (g_nNumber <0)
		{//ループ
			g_nNumber = GetXfileNum() - 1;
		}

		//範囲制限
		g_nNumber %= GetXfileNum();

		if (GetKeyboradPress(DIK_F) == true || GetJoykeyPress(JOYKEY_LEFT, CONTROLLER_1) == true)//Aキー
		{
			if (GetKeyboradPress(DIK_T) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
			{//左上
				pos.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * 10.0f;
			}
			else if (GetKeyboradPress(DIK_G) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
			{//左下
				pos.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * 10.0f;
			}
			else
			{//左
				pos.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * 10.0f;
			}
		}
		else if (GetKeyboradPress(DIK_H) == true || GetJoykeyPress(JOYKEY_RIGHT, CONTROLLER_1) == true)//Dキー
		{
			if (GetKeyboradPress(DIK_T) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
			{//右上
				pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * 10.0f;
			}
			else if (GetKeyboradPress(DIK_G) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
			{//右下
				pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 10.0f;
			}
			else
			{//右
				pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * 10.0f;
			}
		}
		else if (GetKeyboradPress(DIK_T) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//Wキー
		{//上
			pos.x += sinf(pCamera->rot.y) * 10.0f;
			pos.z += cosf(pCamera->rot.y) * 10.0f;
		}
		else if (GetKeyboradPress(DIK_G) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//Sキー
		{//下
			pos.x += sinf(pCamera->rot.y + D3DX_PI) * 10.0f;
			pos.z += cosf(pCamera->rot.y + D3DX_PI) * 10.0f;
		}

		if (GetKeyboradPress(DIK_V) == true)//Wキー
		{//上
			pos.y -= 10.0f;
		}
		if (GetKeyboradPress(DIK_B) == true)//Sキー
		{//下
			pos.y += 10.0f;
		}

		if (GetKeyboradPress(DIK_U) || GetJoykeyPress(JOYKEY_A, CONTROLLER_1))
		{// 押している間
			rot.x -= 0.1f;
		}
		if (GetKeyboradPress(DIK_I) || GetJoykeyPress(JOYKEY_B, CONTROLLER_1))
		{// 押している間
			rot.x+= 0.1f;
		}
		if (GetKeyboradPress(DIK_J) || GetJoykeyPress(JOYKEY_LT, CONTROLLER_1))
		{// 押している間
			rot.y-= 0.1f;
		}
		if (GetKeyboradPress(DIK_K) || GetJoykeyPress(JOYKEY_RT, CONTROLLER_1))
		{// 押している間
			rot.y+= 0.1f;
		}
		if (GetKeyboradPress(DIK_M) || GetJoykeyPress(JOYKEY_X, CONTROLLER_1))
		{// 押している間
			rot.z-= 0.1f;
		}
		if (GetKeyboradPress(DIK_COMMA) || GetJoykeyPress(JOYKEY_Y, CONTROLLER_1))
		{// 押している間
			rot.z+= 0.1f;
		}
		if (GetKeyboradPress(DIK_7) || GetJoykeyPress(JOYKEY_BACK, CONTROLLER_1))
		{// 押している間
			scale.x-= 0.2f;
			scale.y-= 0.2f;
			scale.z-= 0.2f;
		}
		if (GetKeyboradPress(DIK_8) || GetJoykeyPress(JOYKEY_START, CONTROLLER_1))
		{// 押している間
			scale.x+= 0.2f;
			scale.y+= 0.2f;
			scale.z+= 0.2f;
		}

		if (GetKeyboradTrigger(DIK_0) || GetJoykeyTrigger(JOYKEY_R3, CONTROLLER_1))
		{// 初期化
			pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		}

		//正規化
		if (rot.x > D3DX_PI)
		{
			rot.x -= D3DX_PI * 2.0f;
		}
		else if (rot.x < -D3DX_PI)
		{
			rot.x += D3DX_PI * 2.0f;
		}
		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2.0f;
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}
		if (rot.z > D3DX_PI)
		{
			rot.z -= D3DX_PI * 2.0f;
		}
		else if (rot.z < -D3DX_PI)
		{
			rot.z += D3DX_PI * 2.0f;
		}

		//スケール制限
		scale.x = max(STAGE_SCALE_MIN, min(STAGE_SCALE_MAX, scale.x));
		scale.y = max(STAGE_SCALE_MIN, min(STAGE_SCALE_MAX, scale.y));
		scale.z = max(STAGE_SCALE_MIN, min(STAGE_SCALE_MAX, scale.z));

		if (GetKeyboradTrigger(DIK_RSHIFT) || GetJoykeyTrigger(JOYKEY_RB, CONTROLLER_1))
		{// 押したとき
			EndNumber = -1;
		}
		if (GetKeyboradPress(DIK_RSHIFT) || GetJoykeyPress(JOYKEY_RB, CONTROLLER_1))
		{// 押している間
			EndStage(EndNumber);
			EndNumber=SetStage(g_nNumber, g_editPlayer.pos + pos, g_editPlayer.rot + rot, scale);
		}

		if (GetKeyboradTrigger(DIK_BACK) || GetJoykeyTrigger(JOYKEY_L3, CONTROLLER_1))
		{// 押している間
			EndStage(EndNumber);
		}

		if (GetKeyboradTrigger(DIK_F8))
		{// セーブ
			SaveStage();
		}

		// Lスティックでの移動
		float fSticRot = pCamera->rot.y + atan2f(*GetJoyStick(STICK_LEFT, CONTROLLER_1), *(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1));	// スティックを角度へ変換

		float fMoveMax = sqrtf((32767.0f * 32767.0f) + (32767.0f * 32767.0f));
		float fMoveNow = sqrtf((*GetJoyStick(STICK_LEFT, CONTROLLER_1) * *GetJoyStick(STICK_LEFT, CONTROLLER_1)) + (*(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1) * *(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1)));
		float fMove = g_editPlayer.movement * (fMoveNow / fMoveMax);

		g_editPlayer.move.x += sinf(fSticRot) * fMove;
		g_editPlayer.move.z += cosf(fSticRot) * fMove;

		if (bMove)
		{// 動きます！
			float fKeyRot = pCamera->rot.y + atan2f(fMoveX, fMoveZ);	// 角度へ変換
			g_editPlayer.move.x += sinf(fKeyRot) * g_editPlayer.movement;
			g_editPlayer.move.z += cosf(fKeyRot) * g_editPlayer.movement;
		}
	}

	// エディプレイヤーが目的の方向へ向く処理
	g_editPlayer.rot.y = atan2f(g_editPlayer.move.x, g_editPlayer.move.z) + D3DX_PI;

	// 重力
	g_editPlayer.move.y += g_editPlayer.graviment;

	//位置の保存
	g_editPlayer.posOld = g_editPlayer.pos;

	// 位置の更新
	g_editPlayer.pos += g_editPlayer.move;

	if (!GetKeyboradPress(DIK_RSHIFT) && !GetJoykeyPress(JOYKEY_RB, CONTROLLER_1))
	{// 押している間
		CollisionStage(&g_editPlayer.pStage);
	}

	if (g_editPlayer.pStage != NULL)
	{
		if (GetKeyboradTrigger(DIK_DELETE) || (GetJoykeyTrigger(JOYKEY_L3, CONTROLLER_1) && GetJoykeyTrigger(JOYKEY_R3, CONTROLLER_1)))
		{// 押している間
			EndShadow(g_editPlayer.pStage->nIdxShadow);
			g_editPlayer.pStage->bUse = false;
		}
	}

	g_editPlayer.pStage = NULL;

	D3DXVECTOR3 dummy;	// 使わない引数用
	CollisionMeshField(&dummy, &dummy, &g_editPlayer.pos, &g_editPlayer.move);

	if (g_editPlayer.pos.y <= -10.0f)
	{// エディプレイヤーの限界高度以下になったら
		g_editPlayer.pos.y = -10.0f;
		g_editPlayer.move.y = 0.0f;
	}

	// 慣性
	g_editPlayer.move.x += (-g_editPlayer.move.x) * 0.3f;
	g_editPlayer.move.y += (-g_editPlayer.move.y) * 0.3f;
	g_editPlayer.move.z += (-g_editPlayer.move.z) * 0.3f;
}

//*********************************************************************************************
// エディットプレイヤーの取得
//*********************************************************************************************
EDITPLAYER *GetEditPlayer()
{
	return &g_editPlayer;
}

//*********************************************************************************************
// エディットオブジェクトナンバーの取得
//*********************************************************************************************
int GetXnumber()
{
	return g_nNumber;
}