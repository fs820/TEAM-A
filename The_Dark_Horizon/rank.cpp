//------------------------------------------
//
//ランキングの処理[rank.cpp]
//Author fuma sato
//
//------------------------------------------

#include"rank.h"
#include"game.h"
#include"input.h"
#include"fade.h"
#include"pause.h"

#define RANK_TIME (600)
//--------------------
//初期化処理
//--------------------
void InitRank(void)
{

}

//--------------------
//終了処理
//--------------------
void UninitRank(void)
{

}

//--------------------
//更新処理
//--------------------
void UpdateRank(void)
{
	static int nRankTime = 0;

	if (nRankTime % RANK_TIME == 0 && nRankTime != 0)
	{
		nRankTime = 0;
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			//切替
			SetFade(MODE_TITLE);
		}
	}

	if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_LEFT) == true)
	{
		nRankTime = 0;
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
			if (GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM);
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) || GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				nRankTime = 0;
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
			if (GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(NINKEY_＋, (CONTROLLER)i))
			{
				nRankTime = 0;
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
			if (GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				Pause(SOUND_LABEL_BGM);
			}
		}
	}

	if (!bPause())
	{
		nRankTime++;
	}
}

//--------------------
//描画処理
//--------------------
void DrawRank(void)
{

}