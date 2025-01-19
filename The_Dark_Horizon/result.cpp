//------------------------------------------
//
//リザルトの処理[result.cpp]
//Author fuma sato
//
//------------------------------------------

#include"result.h"
#include"input.h"
#include"fade.h"

#define RESULT_TIME (600)
//--------------------
//初期化処理
//--------------------
void InitResult(void)
{

}

//------------------
//終了処理
//------------------
void UninitResult(void)
{

}

//--------------
//更新処理
//--------------
void UpdateResult(void)
{
	static int nResultTime = 0;

	if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_LEFT) == true)
	{
		nResultTime = 0;
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			//切替
			SetFade(MODE_RANK);
		}
	}

	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				nResultTime = 0;
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//切替
					SetFade(MODE_RANK);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) || GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				nResultTime = 0;
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//切替
					SetFade(MODE_RANK);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(NINKEY_＋, (CONTROLLER)i))
			{
				nResultTime = 0;
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//切替
					SetFade(MODE_RANK);
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				nResultTime = 0;
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//切替
					SetFade(MODE_RANK);
				}
			}
		}
	}

	if (nResultTime % RESULT_TIME == 0)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			//切替
			SetFade(MODE_RANK);
		}
	}

	nResultTime++;
}

//-------------------
//描画処理
//-------------------
void DrawResult(void)
{

}