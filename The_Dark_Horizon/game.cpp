//------------------------------------------
//
//ゲームメインの処理[game.cpp]
//Author fuma sato
//
//------------------------------------------

#include"game.h"
#include"input.h"
#include"player.h"
#include"editplayer.h"
#include"bullet.h"
#include"effect.h"
#include"particle.h"
#include"model.h"
#include"pause.h"
#include"time.h"
#include"fade.h"
#include"sound.h"
#include"score.h"
#include"camera.h"
#include"ui.h"

#include"shadow.h"
#include"billboard.h"
#include"stage.h"
#include"file.h"
#include"meshfield.h"
#include"cylinder.h"
#include"sphere.h"
#include"meshwall.h"

//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_GameTime = 0;
bool g_bSnow = false;
bool g_bClear = false;
bool g_Edit = false;
//--------------------
//初期化処理
//--------------------
void InitGame(void)
{
	InitModel();
	InitShadow();
	InitStage();
	InitMeshfield();
	//InitCylinder();
	InitSphere();
	InitMeshWall();
	InitPlayer();//プレイヤー
#ifdef _DEBUG

	InitEditPlayer();

#endif
	InitBullet();
	InitEffect();
	InitParticle();
	InitBillboard();
	InitTime();
	InitUi();

	//空間
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ステージ
	LoadStage();	

	//カメラ
	GameCamera(CAMERA_XNUM * CAMERA_YNUM);
	MasterCamera(CAMERA_XNUM * CAMERA_YNUM, PLAYER);

	D3DXVECTOR3 posScore;//スコアの位置
	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_GameTime = 0;
	g_bSnow = false;
	g_bClear = false;
}

//------------------
//終了処理
//------------------
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;
	EndSound();

	UninitUi();
	UninitTime();
	UninitParticle();
	UninitEffect();
	UninitBullet();
	UninitBillboard();
	UninitMeshWall();
	//UninitCylinder();
	UninitSphere();
	UninitMeshfield();
#ifdef _DEBUG

	UninitEditPlayer();

#endif
	UninitPlayer();//プレイヤー
	UninitStage();
	UninitShadow();
	UninitModel();
}

//--------------
//更新処理
//--------------
void UpdateGame(void)
{
	if (GetKeyboradTrigger(DIK_P) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_SENTER) == true)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			Pause(SOUND_LABEL_BGM);
		}
	}
	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM);
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_＋, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause(SOUND_LABEL_BGM);
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM);
			}
		}
	}
	
	if (!bPause())
	{
		Player* pPlayer;

		pPlayer = GetPlayer();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			//g_GameTime++;
			SetTime(TIME_LIMIT - g_GameTime / FRAME, true);
			if (g_GameTime / FRAME >= TIME_LIMIT)
			{
				g_gameState = GAMESTATE_END;
				g_bClear = true;
			}
			else if (pPlayer->state == PLAYERSTATE_DIE)
			{
				g_gameState = GAMESTATE_END;
				g_bClear = false;
			}
			break;
		case GAMESTATE_END:
			g_nCounterGameState++;
			if (g_nCounterGameState >= INTER)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					////サウンド
					//StopSound(SOUND_LABEL_BGM4);
					//切替
					SetFade(MODE_RESULT);
				}
			}
			break;
		}

		UpdateModel();
		UpdateShadow();
		UpdateStage();
		if (!g_Edit)
		{
			UpdatePlayer();//プレイヤー
		}
#ifdef _DEBUG

		if (GetKeyboradTrigger(DIK_F6))
		{
			g_Edit = !g_Edit;
			if (g_Edit)
			{
				MasterCamera(CAMERA_XNUM* CAMERA_YNUM, EDIT);
			}
			else
			{
				MasterCamera(CAMERA_XNUM* CAMERA_YNUM, PLAYER);
			}
		}

		if (g_Edit)
		{
			UpdateEditPlayer();
		}

#endif
		UpdateMeshWall();
		UpdateMeshfield();
		//UpdateCylinder();
		UpdateSphere();
		UpdateBillboard();
		UpdateBullet();
		UpdateEffect();
		UpdateParticle();
		UpdateUi();
	}
}

//-------------------
//描画処理
//-------------------
void DrawGame(void)
{
	DrawModel();
	DrawSphere();
	DrawMeshfield();
	//DrawCylinder();
	DrawShadow();
	DrawStage();
	DrawMeshWall();
	DrawBillboard();
	DrawEffect();
	DrawBullet();
	if (!g_Edit)
	{
		DrawPlayer();//プレイヤー
	}
#ifdef _DEBUG

	if (g_Edit)
	{
		DrawEditPlayer();
	}

#endif
	DrawAlphaMeshWall();
	DrawTime();
	DrawUi();
}

//----------------------
//ゲーム状態切替
//----------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//-----------------------
//ゲーム状態取得
//-----------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//-----------------------
//スノー取得
//-----------------------
bool GetbSnow(void)
{
	return g_bSnow;
}

//---------------------
//クリア取得
//---------------------
bool GetClear(void)
{
	return g_bClear;
}

//---------------------
//クリアタイム取得
//---------------------
int GetClearTime(void)
{
	int M = (((g_GameTime / FRAME) * (int)(MINUTE * ((float)SECONDS / (float)TIME_LIMIT))) / SECONDS) * 100;
	int S = ((g_GameTime / FRAME) * (int)(MINUTE * ((float)SECONDS / (float)TIME_LIMIT))) % SECONDS;
	return M + S;
}

//---------------------
//タイム取得
//---------------------
int GetTime(void)
{
	return g_GameTime / FRAME;
}

//---------------------
//時間初期化
//---------------------
void TimeReset(void)
{
	g_GameTime = 0;
}