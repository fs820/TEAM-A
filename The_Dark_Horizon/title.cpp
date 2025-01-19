//------------------------------------------
//
//�^�C�g���̏���[title.cpp]
//Author fuma sato
//
//------------------------------------------

#include"title.h"
#include"input.h"
#include"fade.h"

//--------------------
//����������
//--------------------
void InitTitle(void)
{

}

//------------------
//�I������
//------------------
void UninitTitle(void)
{

}

//--------------
//�X�V����
//--------------
void UpdateTitle(void)
{
	if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_LEFT) == true)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			//�ؑ�
			SetFade(MODE_GAME);
		}
	}

	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�ؑ�
					SetFade(MODE_GAME);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) || GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�ؑ�
					SetFade(MODE_GAME);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(NINKEY_�{, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�ؑ�
					SetFade(MODE_GAME);
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�ؑ�
					SetFade(MODE_GAME);
				}
			}
		}
	}
}

//-------------------
//�`�揈��
//-------------------
void DrawTitle(void)
{

}
