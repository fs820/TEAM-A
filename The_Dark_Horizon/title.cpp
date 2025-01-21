//------------------------------------------
//
//�^�C�g���̏���[title.cpp]
//Author fuma sato
//
//------------------------------------------

#include"title.h"
#include"input.h"
#include"fade.h"

// �}�N����`
#define MAX_TEXTUREW_TITLE (1280.0f)		// �^�C�g���e�N�X�`���̉���
#define MAX_TEXTUREH_TITLE (720.0f)			// �^�C�g���e�N�X�`���̏c��
#define MAX_TEXTUREW_TITLENAME (1000.0f)	// �^�C�g�����e�N�X�`���̉���
#define MAX_TEXTUREH_TITLENAME (200.0f)		// �^�C�g�����e�N�X�`���̏c��
#define MAX_TEXTUREW_TITLEUI (500.0f)		// �^�C�g��UI�e�N�X�`���̉���
#define MAX_TEXTUREH_TITLEUI (90.0f)		// �^�C�g��UI�e�N�X�`���̏c��
#define MAX_TEXTUREW (10.0f)				// UI�e�N�X�`�����m�̉���
#define MAX_TITLEUI (3)						// UI�e�N�X�`���̍ő吔

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLETYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
TitleUI g_TitleUI[MAX_TITLEUI];							// �^�C�g���̍\����

//--------------------
//����������
//--------------------
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // �f�o�C�X�ւ̃|�C���^

	// �^�C�g���̍\���̂̏�����
	for (int nCount = 0; nCount < MAX_TITLEUI; nCount++)
	{
		g_TitleUI[nCount].pos = D3DXVECTOR3(640.0f, 400.0f, 0.0f);	// �ʒu������������
		g_TitleUI[nCount].fWidth = MAX_TEXTUREW_TITLEUI;			// ���������������� 
		g_TitleUI[nCount].fHeght = MAX_TEXTUREH_TITLEUI;			// �c�������������� 
		g_TitleUI[nCount].bUse = false;								// �g�p���Ă��邩������������ 
		g_TitleUI[nCount].nCountTime = 0;							// �J�E���g������������ 
	}

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCount = 0; nCount < TITLETYPE_MAX; nCount++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCount],
			&g_pTextureTitle[nCount]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_TITLEUI + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < TITLETYPE_MAX; nCount++)
	{
		// ���_���W�̐ݒ�
		pVtx[0 + (4 * nCount)].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2 + (4 * nCount)].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3 + (4 * nCount)].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhw�̐ݒ�																					
		pVtx[0 + (4 * nCount)].rhw = 1.0f;
		pVtx[1 + (4 * nCount)].rhw = 1.0f;
		pVtx[2 + (4 * nCount)].rhw = 1.0f;
		pVtx[3 + (4 * nCount)].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);

		/*switch (nCount)
		{
		case TITLETYPE_SKY:
			break;
		case TITLETYPE_MOON:
			break;
		case TITLETYPE_NAME:
			break;
		case TITLETYPE_GAMEPLAY:
			break;
		case TITLETYPE_TUTORIAL:
			break;
		case TITLETYPE_EXIT:
			break;

		}*/
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

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
