//------------------------------------------
//
//�Q�[�����C���̏���[game.cpp]
//Author fuma sato
//
//------------------------------------------

#include"game.h"
#include"input.h"
#include"player.h"
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

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_GameTime = 0;
bool g_bSnow = false;
bool g_bClear = false;
//--------------------
//����������
//--------------------
void InitGame(void)
{
	InitModel();
	InitShadow();
	InitStage();
	InitMeshField();
	InitCylinder();
	InitSphere();
	InitMeshWall();
	InitPlayer();//�v���C���[
	InitBullet();
	InitEffect();
	InitParticle();
	InitBillboard();
	InitTime();
	InitUi();

	//���
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�X�e�[�W
	LoadStage();	

	//�J����
	GameCamera(CAMERA_XNUM * CAMERA_YNUM);

	D3DXVECTOR3 posScore;//�X�R�A�̈ʒu
	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_GameTime = 0;
	g_bSnow = false;
	g_bClear = false;

	PlaySound(SOUND_LABEL_BGM);
}

//------------------
//�I������
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
	UninitCylinder();
	UninitSphere();
	UninitMeshField();
	UninitPlayer();//�v���C���[
	UninitStage();
	UninitShadow();
	UninitModel();
}

//--------------
//�X�V����
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
			if (GetdJoykeyTrigger(NINKEY_�{, (CONTROLLER)i))
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
					//�T�E���h
					StopSound(SOUND_LABEL_BGM4);
					//�ؑ�
					SetFade(MODE_RESULT);
				}
			}
			break;
		}

		UpdateModel();
		UpdateShadow();
		UpdateStage();
		UpdatePlayer();//�v���C���[
		UpdateMeshWall();
		UpdateMeshField();
		UpdateCylinder();
		UpdateSphere();
		UpdateBillboard();
		UpdateBullet();
		UpdateEffect();
		UpdateParticle();
		UpdateUi();
	}
}

//-------------------
//�`�揈��
//-------------------
void DrawGame(void)
{
	DrawModel();
	DrawSphere();
	DrawMeshField();
	DrawCylinder();
	DrawShadow();
	DrawStage();
	DrawMeshWall();
	DrawBillboard();
	DrawEffect();
	DrawBullet();
	DrawPlayer();//�v���C���[
	DrawAlphaMeshWall();
	DrawTime();
	DrawUi();
}

//----------------------
//�Q�[����Ԑؑ�
//----------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//-----------------------
//�Q�[����Ԏ擾
//-----------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//-----------------------
//�X�m�[�擾
//-----------------------
bool GetbSnow(void)
{
	return g_bSnow;
}

//---------------------
//�N���A�擾
//---------------------
bool GetClear(void)
{
	return g_bClear;
}

//---------------------
//�N���A�^�C���擾
//---------------------
int GetClearTime(void)
{
	int M = (((g_GameTime / FRAME) * (int)(MINUTE * ((float)SECONDS / (float)TIME_LIMIT))) / SECONDS) * 100;
	int S = ((g_GameTime / FRAME) * (int)(MINUTE * ((float)SECONDS / (float)TIME_LIMIT))) % SECONDS;
	return M + S;
}

//---------------------
//�^�C���擾
//---------------------
int GetTime(void)
{
	return g_GameTime / FRAME;
}

//---------------------
//���ԏ�����
//---------------------
void TimeReset(void)
{
	g_GameTime = 0;
}