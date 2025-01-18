//*********************************************************************************************
//
// �G�f�B�^�[�Ŏg���v���C���[�̏���
// Aouther Tetsuji Yamamoto
// 
//*********************************************************************************************
#include "editplayer.h"
#include "camera.h"
#include"input.h"
#include"meshfield.h"

// �O���[�o���ϐ��錾
EDITPLAYER g_editPlayer;	// �G�f�B�b�g�v���C���[���

//*********************************************************************************************
// �G�f�B�b�g�v���C���[�̏�����
//*********************************************************************************************
void InitEditPlayer()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e��ϐ��̏�����
	g_editPlayer.pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		// �ʒu
	g_editPlayer.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �Â��ʒu
	g_editPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	g_editPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	g_editPlayer.movement = 2.0f;							// �ړ���
	g_editPlayer.graviment = 0.0f;							// �d�͗�
	g_editPlayer.jumpment = 20.0f;							// �W�����v��
	g_editPlayer.bDisp = true;								// �f�����ǂ���

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\tetsuji\\model\\Player_UFO_001.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_editPlayer.pBuffMat,
		NULL,
		&g_editPlayer.dwNumMat,
		&g_editPlayer.pMesh);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_editPlayer.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_editPlayer.dwNumMat; nCntMat++)
	{// �}�e���A������
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// �e�N�X�`���t�@�C�������݂���

			// ���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_editPlayer.apTexture[nCntMat]);
		}
	}
}

//*********************************************************************************************
// �G�f�B�b�g�v���C���[�̏I��
//*********************************************************************************************
void UninitEditPlayer()
{
	// ���b�V���̔j��
	if (g_editPlayer.pMesh != NULL)
	{
		g_editPlayer.pMesh->Release();
		g_editPlayer.pMesh = NULL;
	}

	// �}�e���A���̔j��
	if (g_editPlayer.pBuffMat != NULL)
	{
		g_editPlayer.pBuffMat->Release();
		g_editPlayer.pBuffMat = NULL;
	}

	for (int nCntTex = 0; nCntTex < MAX_EDITPLAYER_TEX_NUM; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (g_editPlayer.apTexture[nCntTex] != NULL)
		{
			g_editPlayer.apTexture[nCntTex]->Release();
			g_editPlayer.apTexture[nCntTex] = NULL;
		}
	}
}

//*********************************************************************************************
// �G�f�B�b�g�v���C���[�̍X�V
//*********************************************************************************************
void UpdateEditPlayer()
{
	EditPlayerManager();	// �G�f�B�b�g�v���C���[�̊Ǘ�
}

//*********************************************************************************************
// �G�f�B�b�g�v���C���[�̕`��
//*********************************************************************************************
void DrawEditPlayer()
{
	if (g_editPlayer.bDisp)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot, mtxTrans;

		// ���݂̃}�e���A���ۑ��p
		D3DMATERIAL9 matDef;

		// �}�e���A���f�[�^�ւ̃|�C���^
		D3DXMATERIAL* pMat;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_editPlayer.mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_editPlayer.rot.y, g_editPlayer.rot.x, g_editPlayer.rot.z);
		D3DXMatrixMultiply(&g_editPlayer.mtxWorld, &g_editPlayer.mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_editPlayer.pos.x, g_editPlayer.pos.y, g_editPlayer.pos.z);
		D3DXMatrixMultiply(&g_editPlayer.mtxWorld, &g_editPlayer.mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_editPlayer.mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_editPlayer.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_editPlayer.dwNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_editPlayer.apTexture[nCntMat]);

			// ���f��(�p�[�c�̕`��)
			g_editPlayer.pMesh->DrawSubset(nCntMat);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//*********************************************************************************************
// �G�f�B�b�g�v���C���[�̊Ǘ�
//*********************************************************************************************
void EditPlayerManager()
{
	Camera* pCamera = GetCamera();				// �J�����̎擾

	// �J�����ɑ΂��Ĉړ����鏈��--------------------------------------------------------------
	if (GetKeyboradPress(DIK_LSHIFT) || GetJoykeyPress(JOYKEY_LB, CONTROLLER_1))
	{// L�V�t�g������
		// �R�}���h����
		if (GetKeyboradPress(DIK_W))
		{// �ړ��ʏ㏸
			g_editPlayer.movement += 0.1f;
		}
		else if (GetKeyboradPress(DIK_S))
		{// �ړ�����
			g_editPlayer.movement -= 0.1f;
		}
		else if (GetKeyboradPress(DIK_A))
		{// �ړ��[��
			g_editPlayer.movement = 0.0f;
		}

		if (GetKeyboradTrigger(DIK_Q))
		{// �d�͏㏸
			g_editPlayer.graviment += 0.1f;
		}
		else if (GetKeyboradTrigger(DIK_E))
		{// �d�͌���
			g_editPlayer.graviment -= 0.1f;
		}
		else if (GetKeyboradTrigger(DIK_D))
		{// �d�̓[��
			g_editPlayer.graviment = 0.0f;
		}

		if (GetKeyboradPress(DIK_Z))
		{// �d�͏㏸
			g_editPlayer.jumpment += 0.1f;
		}
		else if (GetKeyboradPress(DIK_X))
		{// �d�͌���
			g_editPlayer.jumpment -= 0.1f;
		}
		else if (GetKeyboradPress(DIK_C))
		{// �d�̓[��
			g_editPlayer.jumpment = 0.0f;
		}

		if (GetJoykeyPress(JOYKEY_L3, CONTROLLER_1))
		{// ��ړ�
			g_editPlayer.move.y += g_editPlayer.movement;
		}

		if (GetKeyboradTrigger(DIK_SPACE))
		{// �ʒu���Z�b�g,�ʒu�͒����_
			g_editPlayer.pos = pCamera->posR;
		}

	}
	else
	{
		bool bMove = false;
		float fMoveX = 0.0f;
		float fMoveZ = 0.0f;

		if (GetKeyboradPress(DIK_W))
		{// �O�ړ�
			bMove = true;
			fMoveZ = 1.0f;
		}
		else if (GetKeyboradPress(DIK_S))
		{// ��O�ړ�
			bMove = true;
			fMoveZ = -1.0f;
		}

		if (GetKeyboradPress(DIK_A))
		{// ���ړ�
			bMove = true;
			fMoveX = -1.0f;
		}
		else if (GetKeyboradPress(DIK_D))
		{// �E�ړ�
			bMove = true;
			fMoveX = 1.0f;
		}

		if (GetKeyboradPress(DIK_Q))
		{// ��ړ�
			g_editPlayer.move.y += g_editPlayer.movement;
		}
		else if (GetKeyboradPress(DIK_E) || GetJoykeyPress(JOYKEY_L3, CONTROLLER_1))
		{// ���ړ�
			g_editPlayer.move.y -= g_editPlayer.movement;
		}

		if (GetKeyboradTrigger(DIK_SPACE))
		{// �W�����v
			g_editPlayer.move.y += g_editPlayer.jumpment;
		}

		if (GetKeyboradPress(DIK_RSHIFT) || GetJoykeyPress(JOYKEY_RB,CONTROLLER_1))
		{// �����Ă����
			VertexMoveMeshField(g_editPlayer.pos, g_editPlayer.move, 50.0f);
		}
		if (GetKeyboradRelease(DIK_RSHIFT) || GetJoykeyRelease(JOYKEY_RB, CONTROLLER_1))
		{// ��������
			// �@���Đݒ�
			ResetNorVectolMeshField();
		}

		// L�X�e�B�b�N�ł̈ړ�
		float fSticRot = pCamera->rot.y + atan2f(*GetJoyStick(STICK_LEFT, CONTROLLER_1), *(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1));	// �X�e�B�b�N���p�x�֕ϊ�

		float fMoveMax = sqrtf((32767.0f * 32767.0f) + (32767.0f * 32767.0f));
		float fMoveNow = sqrtf((*GetJoyStick(STICK_LEFT, CONTROLLER_1) * *GetJoyStick(STICK_LEFT, CONTROLLER_1)) + (*(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1) * *(GetJoyStick(STICK_LEFT, CONTROLLER_1) + 1)));
		float fMove = g_editPlayer.movement * (fMoveNow / fMoveMax);

		g_editPlayer.move.x += sinf(fSticRot) * fMove;
		g_editPlayer.move.z += cosf(fSticRot) * fMove;

		if (bMove)
		{// �����܂��I
			float fKeyRot = pCamera->rot.y + atan2f(fMoveX, fMoveZ);	// �p�x�֕ϊ�
			g_editPlayer.move.x += sinf(fKeyRot) * g_editPlayer.movement;
			g_editPlayer.move.z += cosf(fKeyRot) * g_editPlayer.movement;
		}
	}

	// �G�f�B�v���C���[���ړI�̕����֌�������
	g_editPlayer.rot.y = atan2f(g_editPlayer.move.x, g_editPlayer.move.z) + D3DX_PI;

	// �d��
	g_editPlayer.move.y += g_editPlayer.graviment;

	// �ʒu�̍X�V
	g_editPlayer.pos += g_editPlayer.move;

	D3DXVECTOR3 dummy;	// �g��Ȃ������p
	CollisionMeshField(&dummy,&dummy,&g_editPlayer.pos, &g_editPlayer.move);

	if (g_editPlayer.pos.y <= -10.0f)
	{// �G�f�B�v���C���[�̌��E���x�ȉ��ɂȂ�����
		g_editPlayer.pos.y = -10.0f;
		g_editPlayer.move.y = 0.0f;
	}

	// ����
	g_editPlayer.move.x += (-g_editPlayer.move.x) * 0.3f;
	g_editPlayer.move.y += (-g_editPlayer.move.y) * 0.3f;
	g_editPlayer.move.z += (-g_editPlayer.move.z) * 0.3f;
}

//*********************************************************************************************
// �G�f�B�b�g�v���C���[�̎擾
//*********************************************************************************************
EDITPLAYER *GetEditPlayer()
{
	return &g_editPlayer;
}