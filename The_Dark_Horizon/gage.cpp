//======================================================
//
// �Q�[�W�̏���
// Aouther:Takahashi misaki
// 
//======================================================

#include "gage.h"
#include "player.h"
#include "game.h"

// �}�N����`
#define MAX_TEXTUREW_HP (570.0f)
#define MAX_TEXTUREH_HP (40.0f)
#define MAX_TEXTUREW_ENERGY (520.0f)
#define MAX_TEXTUREH_ENERGY (40.0f)
#define MAX_TEXTUREW_O2 (50.0f)
#define MAX_TEXTUREH_O2 (500.0f)

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturegage[GAGETYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffgage = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
HPgage g_hpgage;										// �̗̓Q�[�W�̍\����
Energygage g_energygage;								// �G�l���M�[�Q�[�W�̍\����
O2gage g_o2gage;										// �_�f�Q�[�W�̍\����
//=====================================================
// �Q�[�W�̏������ݒ�
//=====================================================
void Initgage(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // �f�o�C�X�ւ̃|�C���^

	// �̗̓Q�[�W�̍\����
	g_hpgage.bUse = false;								// �Q�[�W���g�p���Ă��邩������������
	g_hpgage.fWidth = MAX_TEXTUREW_HP;					// ����������������
	g_hpgage.fWidthR = MAX_TEXTUREW_HP;					// �ԃQ�[�W�̉���������������
	g_hpgage.fHeght = MAX_TEXTUREH_HP;					// �c��������������
	g_hpgage.fDifference = 0.0f;						// �ԃQ�[�W�Ƃ̍���������������
	g_hpgage.pos = D3DXVECTOR3(30.0f, 10.0f, 0.0f);		// �ʒu������������
	g_hpgage.nCountTime = 0;							// �J�E���g������������

	// �G�l���M�[�Q�[�W�̍\����
	g_energygage.bUse = true;								// �Q�[�W���g�p���Ă��邩������������
	g_energygage.fWidth = MAX_TEXTUREW_ENERGY;				// ����������������
	g_energygage.fHeght = MAX_TEXTUREH_ENERGY;				// �c��������������
	g_energygage.fDifference = 0.0f;						// �ő�Q�[�W�Ƃ̍���������������
	g_energygage.pos = D3DXVECTOR3(30.0f, 60.0f, 0.0f);		// �ʒu������������
	g_energygage.nCountTime = 0;							// �J�E���g������������

	// �_�f�Q�[�W�̍\����
	g_o2gage.fWidth = MAX_TEXTUREW_O2;					// ����������������
	g_o2gage.fHeght = MAX_TEXTUREH_O2;					// �c��������������
	g_o2gage.fDifference = 0.0f;						// �O�̃Q�[�W�Ƃ̍���������������
	g_o2gage.pos = D3DXVECTOR3(30.0f, 640.0f, 0.0f);	// �ʒu������������
	g_o2gage.nCountTime = 0;							// �J�E���g������������

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCount = 0; nCount < GAGETYPE_MAX; nCount++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			GAGE_TEXTURE[nCount],
			&g_pTexturegage[nCount]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAGETYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffgage,
		NULL);

	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < GAGETYPE_MAX; nCount++)
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
		pVtx[0 + (4 * nCount)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1 + (4 * nCount)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2 + (4 * nCount)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3 + (4 * nCount)].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���̃Q�[�W
	// ���_���W�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_HPBACKGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x, g_hpgage.pos.y, 0.0f);
	pVtx[1 + (4 * GAGETYPE_HPBACKGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth, g_hpgage.pos.y, 0.0f);
	pVtx[2 + (4 * GAGETYPE_HPBACKGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x, g_hpgage.pos.y + g_hpgage.fHeght, 0.0f);
	pVtx[3 + (4 * GAGETYPE_HPBACKGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth, g_hpgage.pos.y + g_hpgage.fHeght, 0.0f);

	// HP�Q�[�W�̐ԃQ�[�W
	// ���_���W�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth - 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth - 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_REDGAGEH)].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1 + (4 * GAGETYPE_REDGAGEH)].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2 + (4 * GAGETYPE_REDGAGEH)].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3 + (4 * GAGETYPE_REDGAGEH)].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	// HP�Q�[�W
	// ���_���W�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth - 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth - 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);

	// �G�l���M�[�Q�[�W�̌��̃Q�[�W
	// ���_���W�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_ENERGYBACKGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x, g_energygage.pos.y, 0.0f);
	pVtx[1 + (4 * GAGETYPE_ENERGYBACKGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth, g_energygage.pos.y, 0.0f);
	pVtx[2 + (4 * GAGETYPE_ENERGYBACKGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x, g_energygage.pos.y + g_energygage.fHeght, 0.0f);
	pVtx[3 + (4 * GAGETYPE_ENERGYBACKGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth, g_energygage.pos.y + g_energygage.fHeght, 0.0f);

	// �G�l���M�[�Q�[�W
	// ���_���W�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth - 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth - 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);

	// �_�f�Q�[�W�̌��̃Q�[�W
	// ���_���W�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_O2BACKGAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x, g_o2gage.pos.y - g_o2gage.fHeght, 0.0f);
	pVtx[1 + (4 * GAGETYPE_O2BACKGAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth, g_o2gage.pos.y - g_o2gage.fHeght, 0.0f);
	pVtx[2 + (4 * GAGETYPE_O2BACKGAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x, g_o2gage.pos.y, 0.0f);
	pVtx[3 + (4 * GAGETYPE_O2BACKGAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth, g_o2gage.pos.y, 0.0f);

	// �_�f�Q�[�W
	// ���_���W�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_O2GAGE)].col = D3DCOLOR_RGBA(0, 0, 255, 255);
	pVtx[1 + (4 * GAGETYPE_O2GAGE)].col = D3DCOLOR_RGBA(0, 0, 255, 255);
	pVtx[2 + (4 * GAGETYPE_O2GAGE)].col = D3DCOLOR_RGBA(0, 0, 255, 255);
	pVtx[3 + (4 * GAGETYPE_O2GAGE)].col = D3DCOLOR_RGBA(0, 0, 255, 255);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffgage->Unlock();
}
//=====================================================
// �w�i�̏I������
//=====================================================
void Uninitgage(void)
{
	for (int nCount = 0; nCount < GAGETYPE_MAX; nCount++)
	{
		// �e�N�X�`���̔j��
		if (g_pTexturegage[nCount] != NULL)
		{
			g_pTexturegage[nCount]->Release();
			g_pTexturegage[nCount] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffgage != NULL)
	{
		g_pVtxBuffgage->Release();
		g_pVtxBuffgage = NULL;
	}
}
//=====================================================
// �Q�[�W�̍X�V����
//=====================================================
void Updategage(void)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^
	Player* pPlayer = GetPlayer();
	float EnergyP = 0.0f;
	float fNowO2 = 0.0f;
	int nCount = 0;

	if (pPlayer->fEnergy < MAX_ENERGY)
	{
		g_energygage.nCountTime++;

		if (g_energygage.nCountTime >= 150)
		{
			g_energygage.bUse = false;

			if (g_energygage.bUse == false)
			{
				g_energygage.fDifference = MAX_TEXTUREW_ENERGY - g_energygage.fWidth;

				g_energygage.fWidth += g_energygage.fDifference * 0.1f;

				// �G�l���M�[�Q�[�W
				// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

				// ���_���W�̐ݒ�
				// �����ɉ����ăQ�[�W�̒�����ω�������
				pVtx[0 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
				pVtx[1 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth - 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
				pVtx[2 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);
				pVtx[3 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth - 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);

				// ���_�o�b�t�@���A�����b�N����
				g_pVtxBuffgage->Unlock();

				if (g_energygage.fWidth > MAX_TEXTUREW_ENERGY - 10)
				{
					g_energygage.nCountTime = 0;
					g_energygage.fWidth = MAX_TEXTUREW_ENERGY;
					g_energygage.fDifference = 0.0f;
					pPlayer->fEnergy = MAX_ENERGY;
					g_energygage.bUse = true;
				}
			}
		}
	}

	// �_�f�Q�[�W�̌���
	g_o2gage.nCountTime++;

	if (g_o2gage.nCountTime == 60)
	{
		g_o2gage.fHeght -= (float)(MAX_TEXTUREH_O2 / 120.0f);

		// �G�l���M�[�Q�[�W
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		// �����ɉ����ăQ�[�W�̒�����ω�������
		pVtx[0 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
		pVtx[1 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
		pVtx[2 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y  - 5.0f, 0.0f);
		pVtx[3 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0 + (4 * GAGETYPE_O2GAGE)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * GAGETYPE_O2GAGE)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * GAGETYPE_O2GAGE)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * GAGETYPE_O2GAGE)].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffgage->Unlock();

		if (g_o2gage.fHeght <= 0.0f)
		{
			SetGameState(GAMESTATE_END);
		}

		g_o2gage.nCountTime = 0;
	}

}
//=====================================================
// �Q�[�W�̕`�揈��
//=====================================================
void Drawgage(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // �f�o�C�X�ւ̃|�C���^

	Player* pPlayer = GetPlayer();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	if (pPlayer->fLife > 0)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffgage, 0, sizeof(VERTEX_2D));
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int nCount = 0; nCount < GAGETYPE_MAX; nCount++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturegage[nCount]);
			// �Q�[�W�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
		}
	}
}
//=====================================================
// HP�Q�[�W�̐ݒ菈��
//=====================================================
void SetHPgage(void)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^
	Player* pPlayer = GetPlayer();

	// �ω������̗͂������ɕϊ�������
	float fPercentHP = (float)(pPlayer->fLife / MAX_HP);

	float fWidth = MAX_TEXTUREW_HP * fPercentHP;

	g_hpgage.fDifference = g_hpgage.fWidth - fWidth;

	g_hpgage.fWidth = fWidth;

	// HP�Q�[�W
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	// �����ɉ����ăQ�[�W�̒�����ω�������
	pVtx[0 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + fWidth - 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + fWidth - 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffgage->Unlock();
}
//=====================================================
// �ԃQ�[�W�̍X�V����
//=====================================================
void UpdateRedgage(void)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

	// �̗͂�����������ɏ���������
	if (g_hpgage.fDifference > 0.0f)
	{
		g_hpgage.nCountTime++;

		if (g_hpgage.nCountTime >= 60)
		{
			g_hpgage.fWidthR -= g_hpgage.fDifference * 0.1f;

			// ���_���W�̐ݒ�
			// �Q�[�W�̒��������X�ɕω�������
			pVtx[0 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
			pVtx[1 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidthR - 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
			pVtx[2 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);
			pVtx[3 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidthR - 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);

			if (g_hpgage.fWidthR < g_hpgage.fWidth)
			{
				g_hpgage.nCountTime = 0;
				g_hpgage.fDifference = 0.0f;
				g_hpgage.fWidthR = g_hpgage.fWidth;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffgage->Unlock();
}
//=====================================================
// �G�l���M�[�Q�[�W�̐ݒ菈��
//=====================================================
void SetEnergygage(void)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^
	Player* pPlayer = GetPlayer();

	if (g_energygage.bUse == true)
	{
		// �ω������G�l���M�[�������ɕϊ�������
		float fPercentEnergy = (float)(pPlayer->fEnergy / MAX_ENERGY);

		float fWidth = MAX_TEXTUREW_ENERGY * fPercentEnergy;

		g_energygage.fWidth = fWidth;

		// �G�l���M�[�Q�[�W
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		// �����ɉ����ăQ�[�W�̒�����ω�������
		pVtx[0 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
		pVtx[1 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + fWidth - 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
		pVtx[2 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);
		pVtx[3 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + fWidth - 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffgage->Unlock();
	}
}
//=====================================================
// �_�f�Q�[�W�̐ݒ菈��
//=====================================================
void SetO2gage(void)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	g_o2gage.nCountTime = 0;
	g_o2gage.fHeght = MAX_TEXTUREH_O2;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

	// �_�f�Q�[�W
	// ���_���W�̐ݒ�
	pVtx[0 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffgage->Unlock();

}
