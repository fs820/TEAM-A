//***********************************************
//
// ���b�V���t�B�[���h�𐶐����鏈��
// Aouther Tetsuji Yamamoto
// 
//***********************************************
#include "meshfield.h"

// �O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	// �C���f�b�N�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pVtxTexturMeshfield = NULL;		// �e�N�X�`���̃|�C���^
MESHFIELD g_meshField;				// ���b�V���t�B�[���h�̏��

//**************************************
// ���b�V���t�B�[���h�̏�����
//**************************************
void InitMeshfield(void)
{
	int nCntMeshFeild = 0;	// ���b�V���t�B�[���h�̌��𐔂���ϐ�
	int nCntVtx = 0;		// ���b�V���t�B�[���h�̒��_���𐔂���ϐ�
	int nCntIdx = 0;		// �C���f�b�N�X���J�E���g����ϐ�
	int nCntIdxGuide = 0;

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield, NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\field002.jpg",
		&g_pVtxTexturMeshfield);

	// �e��ϐ��̏�����--------------------------------------------------------------------------------
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	g_meshField.pos = D3DXVECTOR3(-2500.0f, 0.0f, 2500.0f);	// �ʒu
	g_meshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	g_meshField.nType = -1;								// ���
	g_meshField.bUse = false;							// �g�p���Ă��邩�ǂ���

	for (int nCntZ = 0; nCntZ <= MESHFIELD_DIVISION_Z; nCntZ++)
	{// Z�̕�������
		for (int nCntX = 0; nCntX <= MESHFIELD_DIVISION_X; nCntX++)
		{// X�̕�������

			float fposX = ((float)MESHFIELD_WIDTH / (float)MESHFIELD_DIVISION_X) * (float)nCntX;
			float fposZ = ((float)MESHFIELD_DEPTH / (float)MESHFIELD_DIVISION_Z) * (float)nCntZ;
			float fTexX = 1.0f / (float)MESHFIELD_DIVISION_X * nCntX;
			float fTexY = 1.0f / (float)MESHFIELD_DIVISION_Z * nCntZ;

			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos.x = g_meshField.pos.x + fposX;
			pVtx[nCntVtx].pos.y = g_meshField.pos.y + 0.0f;
			pVtx[nCntVtx].pos.z = g_meshField.pos.z + (-fposZ);

			// �e���_�̖@���̐ݒ�,�ʂɑ΂��Đ���
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtx].tex.x = fTexX;
			pVtx[nCntVtx].tex.y = fTexY;

			// ���_������i�߂�
			nCntVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshfield->Unlock();

	// �C���f�b�N�X�����߂�----------------------------------------------------------------------
	int nIdxA = MESHFIELD_DIVISION_X + 1;					// �����C���f�b�N�X
	int nIdxB = 0;											// �E���C���f�b�N�X
	int nIdxEX[MESHFIELD_INDEX] = {};	// �C���f�b�N�X�ꎞ�ۑ��p
	int nCntIdxEX = 0;										// �ۑ��p�C���f�b�N�X�̃J�E���^�[

	// �C���f�b�N���ւ̃|�C���^
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < MESHFIELD_DIVISION_Z; nCntA++)
	{// Z�̕���������
		for (int nCntB = 0; nCntB <= MESHFIELD_DIVISION_X; nCntB++)
		{// X�̕���������
			pIdx[nCntIdx] = nIdxA;
			pIdx[nCntIdx + 1] = nIdxB;
			nIdxEX[nCntIdxEX] = nIdxA;
			nIdxEX[nCntIdxEX + 1] = nIdxB;
			nCntIdx += 2;
			nCntIdxEX += 2;
			nIdxA++;
			nIdxB++;
		}

		if (nCntA < MESHFIELD_DIVISION_Z - 1)
		{// ���S���u
			pIdx[nCntIdx] = nIdxB - 1;
			pIdx[nCntIdx + 1] = nIdxA;
			nIdxEX[nCntIdxEX] = nIdxB - 1;
			nIdxEX[nCntIdxEX + 1] = nIdxA;
			nCntIdx += 2;
			nCntIdxEX += 2;
		}
	}
	nIdxB = nIdxA;											// ���̃C���f�b�N�X���Z�o
	nIdxA = nIdxA + MESHFIELD_DIVISION_X + 1;				// ���̃C���f�b�N�X���Z�o
	nCntIdx = 0;											// �C���f�b�N�X�J�E���^�[���Z�b�g
	nCntIdxEX = (MESHFIELD_INDEX) * (nCntMeshFeild + 1);	// ���̕ۑ��p�C���f�b�N�X�J�E���^�[���Z�o
	pIdx += MESHFIELD_INDEX;								// �C���f�b�N�X������

// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshfield->Unlock();

	// �@�������߂�--------------------------------------------------------------------------------
	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);
	nCntIdxEX = 0;			// �ꎞ�ۑ��p�C���f�b�N�X�J�E���^�[���Z�b�g

	for (int nCntPoliOll = 0; nCntPoliOll < MESHFIELD_PLYGON_AII; nCntPoliOll++)
	{// ���ׂẴ|���S������
		for (int nCntPoliApp = 0; nCntPoliApp < MESHFIELD_DIVISION_X * 2; nCntPoliApp++)
		{// ������|���S������
			D3DXVECTOR3 vecLineA = {};	// ��ӂ̃x�N�g��
			D3DXVECTOR3 vecLineB = {};	// ��ӂ̃x�N�g��
			D3DXVECTOR3 vecNor = {};	// �@���x�N�g��

			if ((nCntPoliApp + 1) % 2 == 0)
			{// ����؂��A�����
				vecLineA = pVtx[nIdxEX[nCntIdxEX + 2]].pos - pVtx[nIdxEX[nCntIdxEX]].pos;	// ��ӂ̃x�N�g��
				vecLineB = pVtx[nIdxEX[nCntIdxEX + 1]].pos - pVtx[nIdxEX[nCntIdxEX]].pos;	// ��ӂ̃x�N�g��
			}
			else
			{// ����؂�Ȃ��A�E���
				vecLineA = pVtx[nIdxEX[nCntIdxEX + 1]].pos - pVtx[nIdxEX[nCntIdxEX]].pos;	// ��ӂ̃x�N�g��
				vecLineB = pVtx[nIdxEX[nCntIdxEX + 2]].pos - pVtx[nIdxEX[nCntIdxEX]].pos;	// ��ӂ̃x�N�g��
			}

			// �@���x�N�g�������߂�
			vecNor.x = (vecLineA.y * vecLineB.z) - (vecLineA.z * vecLineB.y);
			vecNor.y = (vecLineA.z * vecLineB.x) - (vecLineA.x * vecLineB.z);
			vecNor.z = (vecLineA.x * vecLineB.y) - (vecLineA.y * vecLineB.x);

			// �@���x�N�g����ۑ�
			g_meshField.aNor[nCntPoliOll] = vecNor;

			// ���K��
			D3DXVec3Normalize(&vecNor, &vecNor);

			// �Z�o�����@����������
			pVtx[nIdxEX[nCntIdxEX]].nor = vecNor;
			pVtx[nIdxEX[nCntIdxEX + 1]].nor = vecNor;
			pVtx[nIdxEX[nCntIdxEX + 2]].nor = vecNor;

			nCntIdxEX++;	// �C���f�b�N�X�J�E���^�[����i�߂�
			nCntPoliOll++;	// �|���S���J�E���g��i�߂�
		}

		if (nCntPoliOll < MESHFIELD_PLYGON_AII)
		{// �ꃁ�b�V���t�B�[���h��ݒ肵����������Ȃ��Ă悢
			nCntIdxEX += 4;		// �C���f�b�N�X�J�E���^�[���k�ރ|���S�����i�߂�
			nCntPoliOll += 3;	// �|���S���J�E���g���k�ރ|���S�����i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshfield->Unlock();

	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//**************************************
// ���b�V���t�B�[���h�̔j��
//**************************************
void UninitMeshfield(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pVtxTexturMeshfield != NULL)
	{
		g_pVtxTexturMeshfield->Release();
		g_pVtxTexturMeshfield = NULL;
	}
}

//**************************************
// ���b�V���t�B�[���h�̔j��
//**************************************
void UpdateMeshfield(void)
{
	//if (KeyboardTrigger(DIK_F1))
	//{
	//	// ���_����ۑ�����
	//	SaveInfoMeshField();
	//}
	//else if (KeyboardTrigger(DIK_F2))
	//{
	//	// ���_�����擾����
	//	LoadInfoMeshField();
	//}
}

//**************************************
// ���b�V���t�B�[���h�̕`��
//**************************************
void DrawMeshfield(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_meshField.mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_meshField.rot.y, g_meshField.rot.x, g_meshField.rot.z);
	D3DXMatrixMultiply(&g_meshField.mtxWorld, &g_meshField.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_meshField.pos.x, g_meshField.pos.y, g_meshField.pos.z);
	D3DXMatrixMultiply(&g_meshField.mtxWorld, &g_meshField.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_meshField.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshfield);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pVtxTexturMeshfield);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		MESHFIELD_VERTEX,
		0,
		MESHFIELD_PLYGON_AII);
}

//*******************************************
// ���b�V���t�B�[���h�̐ݒ�
//*******************************************
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntMeshFeild = 0;	// ���b�V���t�B�[���h�̌��𐔂���ϐ�
	int nCntVtx = 0;		// �C���f�b�N�X���J�E���g����ϐ�

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	g_meshField.pos = pos;
	g_meshField.rot = rot;
	g_meshField.bUse = true;

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshfield->Unlock();
}

//*******************************************
// ���b�V���t�B�[���h�̓����蔻��
//*******************************************
bool CollisionMeshField(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove)
{
	bool bRanding = false;

	int nCntMeshFeild = 0;	// ���b�V���t�B�[���h�̌��𐔂���ϐ�
	int nCntIdx = 0;		// �C���f�b�N�X���J�E���g����ϐ�

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// �C���f�b�N���ւ̃|�C���^
	WORD* pIdx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntPoliOll = 0; nCntPoliOll < MESHFIELD_PLYGON_AII; nCntPoliOll++)
	{// ���ׂẴ|���S������
		for (int nCntPoliApp = 0; nCntPoliApp < MESHFIELD_DIVISION_X * 2; nCntPoliApp++)
		{// ������|���S������
			D3DXVECTOR3 vecLineA, vecLineB, vecLineC;				// �|���S���̈�ӂ̃x�N�g��
			D3DXVECTOR3 vecLinePposA, vecLinePposB, vecLinePposC;	// pPos�Ƃ̃x�N�g��
			D3DXVECTOR3 vecClossA, vecClossB, vecClossC;			// pPos�x�N�g���ƈ�Ӄx�N�g���̊O��

			// �|���S���̈�ӂ̃x�N�g�������߂�
			vecLineA = pVtx[pIdx[nCntIdx + 1]].pos - pVtx[pIdx[nCntIdx]].pos;
			vecLineB = pVtx[pIdx[nCntIdx + 2]].pos - pVtx[pIdx[nCntIdx + 1]].pos;
			vecLineC = pVtx[pIdx[nCntIdx]].pos - pVtx[pIdx[nCntIdx + 2]].pos;

			// pPos�x�N�g�������߂�
			vecLinePposA = *pPos - pVtx[pIdx[nCntIdx]].pos;
			vecLinePposB = *pPos - pVtx[pIdx[nCntIdx + 1]].pos;
			vecLinePposC = *pPos - pVtx[pIdx[nCntIdx + 2]].pos;

			// pPos�x�N�g���ƈ�Ӄx�N�g���̊O�ς����߂�
			vecClossA.x = (vecLineA.y * vecLinePposA.z) - (vecLineA.z * vecLinePposA.y);
			vecClossA.y = (vecLineA.z * vecLinePposA.x) - (vecLineA.x * vecLinePposA.z);
			vecClossA.z = (vecLineA.x * vecLinePposA.y) - (vecLineA.y * vecLinePposA.x);

			vecClossB.x = (vecLineB.y * vecLinePposB.z) - (vecLineB.z * vecLinePposB.y);
			vecClossB.y = (vecLineB.z * vecLinePposB.x) - (vecLineB.x * vecLinePposB.z);
			vecClossB.z = (vecLineB.x * vecLinePposB.y) - (vecLineB.y * vecLinePposB.x);

			vecClossC.x = (vecLineC.y * vecLinePposC.z) - (vecLineC.z * vecLinePposC.y);
			vecClossC.y = (vecLineC.z * vecLinePposC.x) - (vecLineC.x * vecLinePposC.z);
			vecClossC.z = (vecLineC.x * vecLinePposC.y) - (vecLineC.y * vecLinePposC.x);

			if (vecClossA.y > 0 &&
				vecClossB.y > 0 &&
				vecClossC.y > 0 ||
				vecClossA.y < 0 &&
				vecClossB.y < 0 &&
				vecClossC.y < 0)
			{// �O�σx�N�g����y�����ׂăv���X�Ȃ�

				// �v���C���[��y���W�����߂�
				/*
				a = nor
				sp = startPos
				pp = playerPos

				dot = a.x * sp.x + a.y * sp.y + a.z * sp.z

				pp.y = (-(a.x * pp.x) -(a.z * pp.z) + dotA) / a.y
				*/

				// �@���ƃ|���S���̈꒸�_�̓���
				float fdot = (g_meshField.aNor[nCntPoliOll].x * pVtx[pIdx[nCntIdx]].pos.x +
					g_meshField.aNor[nCntPoliOll].y * pVtx[pIdx[nCntIdx]].pos.y +
					g_meshField.aNor[nCntPoliOll].z * pVtx[pIdx[nCntIdx]].pos.z);

				//�v���C���[���|���S����ɂ���Ƃ���y���W�����߂�
				float posy = (-g_meshField.aNor[nCntPoliOll].x * pPos->x - g_meshField.aNor[nCntPoliOll].z * pPos->z + fdot) /
					g_meshField.aNor[nCntPoliOll].y;

				if (pPos->y <= posy)
				{// ���߂����W��菬����������
					// y���W��ݒ�
					pPos->y = posy;

					// �ړ��ʂ��Ȃ���
					pMove->y = 0.0f;

					// ���������
					bRanding = true;
				}
			}

			nCntPoliOll++;	// �|���S���J�E���^�[�v���X
			nCntIdx++;		// �C���f�b�N�J�E���^�[�v���X
		}

		if (nCntPoliOll < MESHFIELD_PLYGON_AII)
		{// �ꃁ�b�V���t�B�[���h��ݒ肵����������Ȃ��Ă悢
		// �k�ރ|���S�����i�߂�
			nCntPoliOll += 3;	// �|���S���J�E���^�[�v���X
			nCntIdx += 4;		// �C���f�b�N�J�E���^�[�v���X
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshfield->Unlock();

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshfield->Unlock();

	// ���ʂ�Ԃ�
	return bRanding;
}

//*******************************************
// ���b�V���t�B�[���h�̒��_�𑀍삷��
//*******************************************
void VertexMoveMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius)
{
	int nCntMeshFeild = 0;	// ���b�V���t�B�[���h�̌��𐔂���ϐ�
	int nCntIdx = 0;		// �C���f�b�N�X���J�E���g����ϐ�

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// �C���f�b�N���ւ̃|�C���^
	WORD* pIdx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
	{// ���ׂĂ̒��_����
		float fLength = sqrtf(((pos.x - pVtx[nCntVtx].pos.x) * (pos.x - pVtx[nCntVtx].pos.x)) + ((pos.z - pVtx[nCntVtx].pos.z) * (pos.z - pVtx[nCntVtx].pos.z)));

		if (fLength <= fRadius)
		{// �͈͓��ł����
			pVtx[nCntVtx].pos.y += (pos.y - pVtx[nCntVtx].pos.y) * 0.01f;
		}
	}

	pVtx += MESHFIELD_VERTEX;	// ���_���i�߂�

// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshfield->Unlock();
}

//*******************************************
// ���b�V���t�B�[���h�̖@�����Đݒ肷��
//*******************************************
void ResetNorVectolMeshField()
{
	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// �C���f�b�N���ւ̃|�C���^
	WORD* pIdx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	int nCntIdxEX = 0;			// �ꎞ�ۑ��p�C���f�b�N�X�J�E���^�[���Z�b�g
	int nCntIdxGuide = 0;

	for (int nCntPoliOll = 0; nCntPoliOll < MESHFIELD_PLYGON_AII; nCntPoliOll++)
	{// ���ׂẴ|���S������
		for (int nCntPoliApp = 0; nCntPoliApp < MESHFIELD_DIVISION_X * 2; nCntPoliApp++)
		{// ������|���S������
			D3DXVECTOR3 vecLineA = {};	// ��ӂ̃x�N�g��
			D3DXVECTOR3 vecLineB = {};	// ��ӂ̃x�N�g��
			D3DXVECTOR3 vecNor = {};	// �@���x�N�g��

			if ((nCntPoliApp + 1) % 2 == 0)
			{// ����؂��A�����
				vecLineA = pVtx[pIdx[nCntIdxEX + 2]].pos - pVtx[pIdx[nCntIdxEX]].pos;	// ��ӂ̃x�N�g��
				vecLineB = pVtx[pIdx[nCntIdxEX + 1]].pos - pVtx[pIdx[nCntIdxEX]].pos;	// ��ӂ̃x�N�g��
			}
			else
			{// ����؂�Ȃ��A�E���
				vecLineA = pVtx[pIdx[nCntIdxEX + 1]].pos - pVtx[pIdx[nCntIdxEX]].pos;	// ��ӂ̃x�N�g��
				vecLineB = pVtx[pIdx[nCntIdxEX + 2]].pos - pVtx[pIdx[nCntIdxEX]].pos;	// ��ӂ̃x�N�g��
			}

			// �@���x�N�g�������߂�
			vecNor.x = (vecLineA.y * vecLineB.z) - (vecLineA.z * vecLineB.y);
			vecNor.y = (vecLineA.z * vecLineB.x) - (vecLineA.x * vecLineB.z);
			vecNor.z = (vecLineA.x * vecLineB.y) - (vecLineA.y * vecLineB.x);

			// �@���x�N�g����ۑ�
			g_meshField.aNor[nCntPoliOll] = vecNor;

			// ���K��
			D3DXVec3Normalize(&vecNor, &vecNor);

			// �Z�o�����@����������
			pVtx[pIdx[nCntIdxEX]].nor = vecNor;
			pVtx[pIdx[nCntIdxEX + 1]].nor = vecNor;
			pVtx[pIdx[nCntIdxEX + 2]].nor = vecNor;

			nCntIdxEX++;	// �C���f�b�N�X�J�E���^�[����i�߂�
			nCntPoliOll++;	// �|���S���J�E���g��i�߂�
		}

		if (nCntPoliOll < MESHFIELD_PLYGON_AII)
		{// �ꃁ�b�V���t�B�[���h��ݒ肵����������Ȃ��Ă悢
			nCntIdxEX += 4;		// �C���f�b�N�X�J�E���^�[���k�ރ|���S�����i�߂�
			nCntPoliOll += 3;	// �|���S���J�E���g���k�ރ|���S�����i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshfield->Unlock();

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshfield->Unlock();
}

//*******************************************
// ���b�V���t�B�[���h�̒��_����ۑ�����
//*******************************************
void SaveInfoMeshField()
{
	// �t�@�C�����J��
	FILE* pFile = fopen("date\\text\\MeshField\\MeshField_Info.txt", "w");
	VERTEX_3D* pVtx = NULL;	// ���_���ւ̃|�C���^
	WORD* pIdx = NULL;		// �C���f�b�N���ւ̃|�C���^

	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);	// ���_�o�b�t�@�����b�N

	fprintf(pFile, "MESHFIELD_DIVISION_X %d\n", MESHFIELD_DIVISION_X);		// x�����̕�������������
	fprintf(pFile, "MESHFIELD_DIVISION_Z %d\n\n", MESHFIELD_DIVISION_Z);	// z�����̕�������������

		// ���b�V���t�B�[���h��񏑂����݊J�n
	fprintf(pFile, "MESHFIELD_INFO\n\n");

	// ���b�V���t�B�[���h�\���̂̏�����������------------------------------------------------------------------------
	// ����
	fprintf(pFile, "MESHFIELD_STRUCT\n");

	// �ʒu
	fprintf(pFile, "MESHFIELD_STRUCT_POS\n");
	fprintf(pFile, "%f %f %f\n", g_meshField.pos.x, g_meshField.pos.y, g_meshField.pos.z);
	fprintf(pFile, "END_MESHFIELD_STRUCT_POS\n\n");

	// ����
	fprintf(pFile, "MESHFIELD_STRUCT_ROT\n");
	fprintf(pFile, "%f %f %f\n", g_meshField.rot.x, g_meshField.rot.y, g_meshField.rot.z);
	fprintf(pFile, "END_MESHFIELD_STRUCT_ROT\n\n");

	// ���
	fprintf(pFile, "MESHFIELD_STRUCT_TYPE\n");
	fprintf(pFile, "%d\n", g_meshField.nType);
	fprintf(pFile, "END_MESHFIELD_STRUCT_TYPE\n\n");

	// �|���S���̖@��
	fprintf(pFile, "MESHFIELD_STRUCT_NOR\n");
	for (int nCntPolligon = 0; nCntPolligon < MESHFIELD_PLYGON_AII; nCntPolligon++)
	{// �|���S��������
		fprintf(pFile, "%f %f %f\n",
			g_meshField.aNor[nCntPolligon].x,
			g_meshField.aNor[nCntPolligon].y,
			g_meshField.aNor[nCntPolligon].z);
	}
	fprintf(pFile, "END_MESHFIELD_STRUCT_NOR\n\n");

	fprintf(pFile, "END_MESHFIELD_STRUCT\n\n");

	// ���_���W����������----------------------------------------------------------------------------------------------
	// ����
	fprintf(pFile, "MESHFIELD_VERTEX_POS\n");

	for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
	{// ���_������
		fprintf(pFile, "%f %f %f\n", pVtx[nCntVtx].pos.x, pVtx[nCntVtx].pos.y, pVtx[nCntVtx].pos.z);
	}

	// ����
	fprintf(pFile, "END_MESHFIELD_VERTEX_POS\n\n");

	// �@���x�N�g������������------------------------------------------------------------------------------------------
	// ����
	fprintf(pFile, "MESHFIELD_VERTEX_NOR\n");

	for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
	{// ���_������
		fprintf(pFile, "%f %f %f\n", pVtx[nCntVtx].nor.x, pVtx[nCntVtx].nor.y, pVtx[nCntVtx].nor.z);
	}

	// ����
	fprintf(pFile, "END_MESHFIELD_VERTEX_NOR\n\n");

	// �e�N�X�`�����W����������----------------------------------------------------------------------------------------
	// ����
	fprintf(pFile, "MESHFIELD_VERTEX_TEX\n");

	for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
	{// ���_������
		fprintf(pFile, "%f %f\n", pVtx[nCntVtx].tex.x, pVtx[nCntVtx].tex.y);
	}

	// ����
	fprintf(pFile, "END_MESHFIELD_VERTEX_TEX\n\n");

	// �C���f�b�N�X����������------------------------------------------------------------------------------------------
	// ����
	fprintf(pFile, "MESHFIELD_INDEX\n");

	for (int nCntIdx = 0; nCntIdx < MESHFIELD_INDEX; nCntIdx++)
	{// ���_������
		fprintf(pFile, "%d\n", pIdx[nCntIdx]);
	}

	// ����
	fprintf(pFile, "END_MESHFIELD_INDEX\n\n");

	pVtx += MESHFIELD_VERTEX;	// ���̒��_���W�֐i�߂�
	pIdx += MESHFIELD_INDEX;	// ���̃C���f�b�N�X�֐i�߂��

// ���b�V���t�B�[���h�̐ݒ�I���
	fprintf(pFile, "END_MESHFIELD_INFO\n\n");

	g_pVtxBuffMeshfield->Unlock();	// ���_�o�b�t�@���A�����b�N
	g_pIdxBuffMeshfield->Unlock();	// �C���f�b�N�X�o�b�t�@�̃A�����b�N

	// �t�@�C�������
	fclose(pFile);
}

//*******************************************
// ���b�V���t�B�[���h�̒��_�����擾
//*******************************************
void LoadInfoMeshField()
{
	char aStr[256] = {};	// ������ۑ��p�ϐ�
	int nNum = -1;			// �����ۑ��p�ϐ�
	int nResult;			// ���ʂ�ۑ�����ϐ�
	int nCntMeshField = -1;	// ���b�V���t�B�[���h�𐔂���E�ϐ�

	// �t�@�C�����J��
	FILE* pFile = fopen("date\\text\\MeshField\\MeshField_Info.txt", "r");
	VERTEX_3D* pVtx = NULL;	// ���_���ւ̃|�C���^
	WORD* pIdx = NULL;		// �C���f�b�N���ւ̃|�C���^

	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);	// ���_�o�b�t�@�����b�N

	while (1)
	{
		// �������ǂݎ��
		nResult = fscanf(pFile, "%s", &aStr[0]);

		if (strcmp("MESHFIELD_DIVISION_X", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h��x�̕�������ǂݎ��
			nResult = fscanf(pFile, "%d", &nNum);

			if (nNum != MESHFIELD_DIVISION_X)
			{// �}�N���Ɠǂݎ���������������Ă��Ȃ������玸�s
				nResult = EOF;
			}
		}
		else if (strcmp("MESHFIELD_DIVISION_Z", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h��z�̕�������ǂݎ��
			nResult = fscanf(pFile, "%d", &nNum);

			if (nNum != MESHFIELD_DIVISION_Z)
			{// �}�N���Ɠǂݎ���������������Ă��Ȃ������玸�s
				nResult = EOF;
			}
		}
		else if (strcmp("MESHFIELD_INFO", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̏��擾�J�n
			nCntMeshField++;// ���b�V���t�B�[���h�J�E���^�[�ǉ�
		}
		else if (strcmp("END_MESHFIELD_INFO", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̏��擾�I��
		}
		else if (strcmp("MESHFIELD_STRUCT_POS", &aStr[0]) == 0)
		{// ���b�V���t�B�[���\���̂̈ʒu���擾
			nResult = fscanf(pFile, "%f", &g_meshField.pos.x);
			nResult = fscanf(pFile, "%f", &g_meshField.pos.y);
			nResult = fscanf(pFile, "%f", &g_meshField.pos.z);
		}
		else if (strcmp("END_MESHFIELD_STRUCT_POS", &aStr[0]) == 0)
		{// ���b�V���t�B�[���\���̂̈ʒu���擾���I��
		}
		else if (strcmp("MESHFIELD_STRUCT_NOR", &aStr[0]) == 0)
		{// ���b�V���t�B�[���\���̖̂@�����擾
			for (int nCntPolligon = 0; nCntPolligon < MESHFIELD_PLYGON_AII; nCntPolligon++)
			{// �|���S��������
				nResult = fscanf(pFile, "%f", &g_meshField.aNor[nCntPolligon].x);
				nResult = fscanf(pFile, "%f", &g_meshField.aNor[nCntPolligon].y);
				nResult = fscanf(pFile, "%f", &g_meshField.aNor[nCntPolligon].z);
			}
		}
		else if (strcmp("END_MESHFIELD_STRUCT_NOR", &aStr[0]) == 0)
		{// ���b�V���t�B�[���\���̂̈ʒu��@�����I��
		}
		else if (strcmp("MESHFIELD_STRUCT_TYPE", &aStr[0]) == 0)
		{// ���b�V���t�B�[���\���̂̎�ނ��擾
			nResult = fscanf(pFile, "%d", &g_meshField.nType);
		}
		else if (strcmp("END_MESHFIELD_STRUCT_TYPE", &aStr[0]) == 0)
		{// ���b�V���t�B�[���\���̂̎�ނ��擾���I��
		}
		else if (strcmp("MESHFIELD_VERTEX_POS", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̒��_�����擾����
			for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
			{// ���_������
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].pos.x);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].pos.y);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].pos.z);
			}
		}
		else if (strcmp("END_MESHFIELD_VERTEX_POS", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̒��_���̎擾�I��
		}
		else if (strcmp("MESHFIELD_VERTEX_NOR", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̖@���x�N�g�����擾����
			for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
			{// ���_������
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].nor.x);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].nor.y);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].nor.z);
			}
		}
		else if (strcmp("END_MESHFIELD_VERTEX_NOR", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̖@���x�N�g���̎擾�I��
		}
		else if (strcmp("MESHFIELD_VERTEX_TEX", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̃e�N�X�`�����W���擾����
			for (int nCntVtx = 0; nCntVtx < MESHFIELD_VERTEX; nCntVtx++)
			{// ���_������
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].tex.x);
				nResult = fscanf(pFile, "%f", &pVtx[nCntVtx].tex.y);
			}
		}
		else if (strcmp("END_MESHFIELD_VERTEX_TEX", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̃e�N�X�`�����W�̎擾�I��
		}
		else if (strcmp("MESHFIELD_INDEX", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̃C���f�b�N�X���擾����
			for (int nCntidx = 0; nCntidx < MESHFIELD_INDEX; nCntidx++)
			{// ���_������
				nResult = fscanf(pFile, "%d", &pIdx[nCntidx]);
			}
		}
		else if (strcmp("MESHFIELD_INDEX", &aStr[0]) == 0)
		{// ���b�V���t�B�[���h�̃C���f�b�N�X�擾�I��
		}


		if (nResult == EOF)
		{// �Ō�܂œǂݐ؂�����I��
			break;
		}
	}

	g_pVtxBuffMeshfield->Unlock();	// ���_�o�b�t�@���A�����b�N
	g_pIdxBuffMeshfield->Unlock();	// �C���f�b�N�X�o�b�t�@�̃A�����b�N

	// �t�@�C�������
	fclose(pFile);
}