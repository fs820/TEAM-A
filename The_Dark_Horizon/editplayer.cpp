//*********************************************************************************************
//
// �G�f�B�^�[�Ŏg���v���C���[�̏���
// Aouther Tetsuji Yamamoto
// 
//*********************************************************************************************
#include "editplayer.h"
#include "camera.h"
#include "input.h"
#include "meshfield.h"
#include "file.h"
#include "shadow.h"

// �O���[�o���ϐ��錾
EDITPLAYER g_editPlayer;	// �G�f�B�b�g�v���C���[���
int g_nNumber = 0;

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
	g_editPlayer.Type = MESH;                               //�G�f�B�b�g�^�C�v
	g_editPlayer.pStage = NULL;                             //�X�e�[�W�|�C���^
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
	//�G�f�B�b�g���[�h�ؑ�
	if (GetKeyboradTrigger(DIK_F9))
	{
		g_editPlayer.Type = (EDITTYPE)!g_editPlayer.Type;
	}

	//�G�f�B�b�g���[�h�ŏ�����������
	switch (g_editPlayer.Type)
	{
	case MESH:
		EditPlayerManagerMesh();	// �G�f�B�b�g�v���C���[�̊Ǘ�(Mesh)
		break;
	case OBJECT:
		EditPlayerManagerObject();  // �G�f�B�b�g�v���C���[�̊Ǘ�(Object)
		break;
	}
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
// �G�f�B�b�g�v���C���[�̊Ǘ�(Mesh)
//*********************************************************************************************
void EditPlayerManagerMesh()
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

	//�ʒu�̕ۑ�
	g_editPlayer.posOld = g_editPlayer.pos;

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
// �G�f�B�b�g�v���C���[�̊Ǘ�(Object)
//*********************************************************************************************
void EditPlayerManagerObject()
{
	Camera* pCamera = GetCamera();				              // �J�����̎擾
	static D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		               rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		               scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); // �I�u�W�F�N�g�ݒu�p
	static int EndNumber = -1, CollNumber = -1;                    //�I�u�W�F�N�g�i���o�[

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
		else if (GetKeyboradPress(DIK_E))
		{// ���ړ�
			g_editPlayer.move.y -= g_editPlayer.movement;
		}

		if (GetKeyboradTrigger(DIK_SPACE))
		{// �W�����v
			g_editPlayer.move.y += g_editPlayer.jumpment;
		}

		if (GetKeyboradTrigger(DIK_RIGHT))
		{// �I�u�W�F�N�g�ؑ�
			g_nNumber++;
		}
		else if (GetKeyboradTrigger(DIK_LEFT))
		{// �I�u�W�F�N�g�ؑ�
			g_nNumber--;
		}

		if (g_nNumber <0)
		{//���[�v
			g_nNumber = GetXfileNum() - 1;
		}

		//�͈͐���
		g_nNumber %= GetXfileNum();

		if (GetKeyboradPress(DIK_F) == true || GetJoykeyPress(JOYKEY_LEFT, CONTROLLER_1) == true)//A�L�[
		{
			if (GetKeyboradPress(DIK_T) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
			{//����
				pos.x += sinf(pCamera->rot.y + D3DX_PI * -0.25f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * -0.25f) * 10.0f;
			}
			else if (GetKeyboradPress(DIK_G) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
			{//����
				pos.x += sinf(pCamera->rot.y + D3DX_PI * -0.75f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * -0.75f) * 10.0f;
			}
			else
			{//��
				pos.x += sinf(pCamera->rot.y + D3DX_PI * -0.5f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * -0.5f) * 10.0f;
			}
		}
		else if (GetKeyboradPress(DIK_H) == true || GetJoykeyPress(JOYKEY_RIGHT, CONTROLLER_1) == true)//D�L�[
		{
			if (GetKeyboradPress(DIK_T) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
			{//�E��
				pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * 10.0f;
			}
			else if (GetKeyboradPress(DIK_G) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
			{//�E��
				pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 10.0f;
			}
			else
			{//�E
				pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.5f) * 10.0f;
				pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.5f) * 10.0f;
			}
		}
		else if (GetKeyboradPress(DIK_T) == true || GetJoykeyPress(JOYKEY_UP, CONTROLLER_1) == true)//W�L�[
		{//��
			pos.x += sinf(pCamera->rot.y) * 10.0f;
			pos.z += cosf(pCamera->rot.y) * 10.0f;
		}
		else if (GetKeyboradPress(DIK_G) == true || GetJoykeyPress(JOYKEY_DOWN, CONTROLLER_1) == true)//S�L�[
		{//��
			pos.x += sinf(pCamera->rot.y + D3DX_PI) * 10.0f;
			pos.z += cosf(pCamera->rot.y + D3DX_PI) * 10.0f;
		}

		if (GetKeyboradPress(DIK_V) == true)//W�L�[
		{//��
			pos.y -= 10.0f;
		}
		if (GetKeyboradPress(DIK_B) == true)//S�L�[
		{//��
			pos.y += 10.0f;
		}

		if (GetKeyboradPress(DIK_U) || GetJoykeyPress(JOYKEY_A, CONTROLLER_1))
		{// �����Ă����
			rot.x -= 0.1f;
		}
		if (GetKeyboradPress(DIK_I) || GetJoykeyPress(JOYKEY_B, CONTROLLER_1))
		{// �����Ă����
			rot.x+= 0.1f;
		}
		if (GetKeyboradPress(DIK_J) || GetJoykeyPress(JOYKEY_LT, CONTROLLER_1))
		{// �����Ă����
			rot.y-= 0.1f;
		}
		if (GetKeyboradPress(DIK_K) || GetJoykeyPress(JOYKEY_RT, CONTROLLER_1))
		{// �����Ă����
			rot.y+= 0.1f;
		}
		if (GetKeyboradPress(DIK_M) || GetJoykeyPress(JOYKEY_X, CONTROLLER_1))
		{// �����Ă����
			rot.z-= 0.1f;
		}
		if (GetKeyboradPress(DIK_COMMA) || GetJoykeyPress(JOYKEY_Y, CONTROLLER_1))
		{// �����Ă����
			rot.z+= 0.1f;
		}
		if (GetKeyboradPress(DIK_7) || GetJoykeyPress(JOYKEY_BACK, CONTROLLER_1))
		{// �����Ă����
			scale.x-= 0.2f;
			scale.y-= 0.2f;
			scale.z-= 0.2f;
		}
		if (GetKeyboradPress(DIK_8) || GetJoykeyPress(JOYKEY_START, CONTROLLER_1))
		{// �����Ă����
			scale.x+= 0.2f;
			scale.y+= 0.2f;
			scale.z+= 0.2f;
		}

		if (GetKeyboradTrigger(DIK_0) || GetJoykeyTrigger(JOYKEY_R3, CONTROLLER_1))
		{// ������
			pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		}

		//���K��
		if (rot.x > D3DX_PI)
		{
			rot.x -= D3DX_PI * 2.0f;
		}
		else if (rot.x < -D3DX_PI)
		{
			rot.x += D3DX_PI * 2.0f;
		}
		if (rot.y > D3DX_PI)
		{
			rot.y -= D3DX_PI * 2.0f;
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}
		if (rot.z > D3DX_PI)
		{
			rot.z -= D3DX_PI * 2.0f;
		}
		else if (rot.z < -D3DX_PI)
		{
			rot.z += D3DX_PI * 2.0f;
		}

		//�X�P�[������
		scale.x = max(STAGE_SCALE_MIN, min(STAGE_SCALE_MAX, scale.x));
		scale.y = max(STAGE_SCALE_MIN, min(STAGE_SCALE_MAX, scale.y));
		scale.z = max(STAGE_SCALE_MIN, min(STAGE_SCALE_MAX, scale.z));

		if (GetKeyboradTrigger(DIK_RSHIFT) || GetJoykeyTrigger(JOYKEY_RB, CONTROLLER_1))
		{// �������Ƃ�
			EndNumber = -1;
		}
		if (GetKeyboradPress(DIK_RSHIFT) || GetJoykeyPress(JOYKEY_RB, CONTROLLER_1))
		{// �����Ă����
			EndStage(EndNumber);
			EndNumber=SetStage(g_nNumber, g_editPlayer.pos + pos, g_editPlayer.rot + rot, scale);
		}

		if (GetKeyboradTrigger(DIK_BACK) || GetJoykeyTrigger(JOYKEY_L3, CONTROLLER_1))
		{// �����Ă����
			EndStage(EndNumber);
		}

		if (GetKeyboradTrigger(DIK_F8))
		{// �Z�[�u
			SaveStage();
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

	//�ʒu�̕ۑ�
	g_editPlayer.posOld = g_editPlayer.pos;

	// �ʒu�̍X�V
	g_editPlayer.pos += g_editPlayer.move;

	if (!GetKeyboradPress(DIK_RSHIFT) && !GetJoykeyPress(JOYKEY_RB, CONTROLLER_1))
	{// �����Ă����
		CollisionStage(&g_editPlayer.pStage);
	}

	if (g_editPlayer.pStage != NULL)
	{
		if (GetKeyboradTrigger(DIK_DELETE) || (GetJoykeyTrigger(JOYKEY_L3, CONTROLLER_1) && GetJoykeyTrigger(JOYKEY_R3, CONTROLLER_1)))
		{// �����Ă����
			EndShadow(g_editPlayer.pStage->nIdxShadow);
			g_editPlayer.pStage->bUse = false;
		}
	}

	g_editPlayer.pStage = NULL;

	D3DXVECTOR3 dummy;	// �g��Ȃ������p
	CollisionMeshField(&dummy, &dummy, &g_editPlayer.pos, &g_editPlayer.move);

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

//*********************************************************************************************
// �G�f�B�b�g�I�u�W�F�N�g�i���o�[�̎擾
//*********************************************************************************************
int GetXnumber()
{
	return g_nNumber;
}