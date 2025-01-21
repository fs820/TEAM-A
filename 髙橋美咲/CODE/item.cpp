//======================================================
//
// �A�C�e���̏���
// Aouther:Takahashi misaki
// 
//======================================================
#include "item.h"

// �}�N����`
#define MAX_TEXTUREW_ITEM (80.0f)	// �e�N�X�`���̉���
#define MAX_TEXTUREH_ITEM (80.0f)	// �e�N�X�`���̏c��
#define MAX_TEXTUREW (10.0f)		// �e�N�X�`�����m�̉���
#define MAX_ITEM (3)
// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureitem[ITEMTYPE_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffitem = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
Item g_Item[MAX_ITEM];									// �A�C�e���̍\����

//=====================================================
// �A�C�e���̏������ݒ�
//=====================================================
void Inititem(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // �f�o�C�X�ւ̃|�C���^
	int nNumber = 0;

	// �A�C�e���̍\����
	for (int nCount = 0; nCount < MAX_ITEM; nCount++)
	{
		g_Item[nCount].TXpos = D3DXVECTOR3(1000.0f + (MAX_TEXTUREW_ITEM * nCount) + (MAX_TEXTUREW * nCount), 10.0f, 0.0f);	// �ʒu������������
		g_Item[nCount].TXcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F������������ 
	}

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCount = 0; nCount < ITEMTYPE_MAX; nCount++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCount],
			&g_pTextureitem[nCount]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ITEMTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffitem,
		NULL);

	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffitem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < ITEMTYPE_MAX; nCount++)
	{
		// �A�C�e���t���[��
		// ���_���W�̐ݒ�
		pVtx[0 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x , g_Item[nNumber].TXpos.y, 0.0f);
		pVtx[1 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + MAX_TEXTUREW_ITEM, g_Item[nNumber].TXpos.y, 0.0f);
		pVtx[2 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x , g_Item[nNumber].TXpos.y + MAX_TEXTUREH_ITEM, 0.0f);
		pVtx[3 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + MAX_TEXTUREW_ITEM, g_Item[nNumber].TXpos.y + MAX_TEXTUREH_ITEM, 0.0f);

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

		nCount++;

		// �A�C�e���A�C�R��
		// ���_���W�̐ݒ�
		pVtx[0 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + 5.0f, g_Item[nNumber].TXpos.y + 5.0f, 0.0f);
		pVtx[1 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + MAX_TEXTUREW_ITEM - 5.0f, g_Item[nNumber].TXpos.y + 5.0f, 0.0f);
		pVtx[2 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + 5.0f, g_Item[nNumber].TXpos.y + MAX_TEXTUREH_ITEM - 5.0f, 0.0f);
		pVtx[3 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + MAX_TEXTUREW_ITEM - 5.0f, g_Item[nNumber].TXpos.y + MAX_TEXTUREH_ITEM - 5.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[0 + (4 * nCount)].rhw = 1.0f;
		pVtx[1 + (4 * nCount)].rhw = 1.0f;
		pVtx[2 + (4 * nCount)].rhw = 1.0f;
		pVtx[3 + (4 * nCount)].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0 + (4 * nCount)].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[1 + (4 * nCount)].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[2 + (4 * nCount)].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[3 + (4 * nCount)].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);

		if (nCount % 2 == 1)
		{
			nNumber++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffitem->Unlock();
}
//=====================================================
// �w�i�̏I������
//=====================================================
void Uninititem(void)
{
	for (int nCount = 0; nCount < ITEMTYPE_MAX; nCount++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureitem[nCount] != NULL)
		{
			g_pTextureitem[nCount]->Release();
			g_pTextureitem[nCount] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffitem != NULL)
	{
		g_pVtxBuffitem->Release();
		g_pVtxBuffitem = NULL;
	}
}
//=====================================================
// �A�C�e���̍X�V����
//=====================================================
void Updateitem(void)
{

}
//=====================================================
// �A�C�e���̕`�揈��
//=====================================================
void Drawitem(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffitem, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < ITEMTYPE_MAX; nCount++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureitem[nCount]);
		// �A�C�e���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
	}
}
//=====================================================
// �A�C�e���̐ݒ菈��
//=====================================================
void Setitem(int nIdxItem)
{
	VERTEX_2D* pVtx;  // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffitem->Lock(0, 0, (void**)&pVtx, 0);

	g_Item[nIdxItem].TXcol= D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// �A�C�e�����������Ă���Ƃ�
	// ���_�J���[�̐ݒ�
	switch (nIdxItem)
	{
	case 0:
		pVtx[0 + (4 * ITEMTYPE_ITEM0)].col = g_Item[nIdxItem].TXcol;
		pVtx[1 + (4 * ITEMTYPE_ITEM0)].col = g_Item[nIdxItem].TXcol;
		pVtx[2 + (4 * ITEMTYPE_ITEM0)].col = g_Item[nIdxItem].TXcol;
		pVtx[3 + (4 * ITEMTYPE_ITEM0)].col = g_Item[nIdxItem].TXcol;
		break;

	case 1:
		pVtx[0 + (4 * ITEMTYPE_ITEM1)].col = g_Item[nIdxItem].TXcol;
		pVtx[1 + (4 * ITEMTYPE_ITEM1)].col = g_Item[nIdxItem].TXcol;
		pVtx[2 + (4 * ITEMTYPE_ITEM1)].col = g_Item[nIdxItem].TXcol;
		pVtx[3 + (4 * ITEMTYPE_ITEM1)].col = g_Item[nIdxItem].TXcol;
		break;

	case 2:
		pVtx[0 + (4 * ITEMTYPE_ITEM2)].col = g_Item[nIdxItem].TXcol;
		pVtx[1 + (4 * ITEMTYPE_ITEM2)].col = g_Item[nIdxItem].TXcol;
		pVtx[2 + (4 * ITEMTYPE_ITEM2)].col = g_Item[nIdxItem].TXcol;
		pVtx[3 + (4 * ITEMTYPE_ITEM2)].col = g_Item[nIdxItem].TXcol;
		break;
	}
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffitem->Unlock();

}