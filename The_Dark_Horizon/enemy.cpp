#include "enemy.h"

// �O���[�o���ϐ��錾
ENEMY g_aEnemy[MAX_ENEMY];	// �G�l�~�[���

//**************************************************
// �G�l�~�[�̏�����
//**************************************************
void InitEnemy(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �ő�G�l�~�[����
		g_aEnemy[nCntEnemy].pos;	// �ʒu
		g_aEnemy[nCntEnemy].rot;	// ����
		g_aEnemy[nCntEnemy].move;	// �ړ���
	}

	// �X�N���v�g�ǂݍ���
	ReadScript("data\\tetsuji\\text\\motion.txt", &g_aEnemy[0].motion, &g_aEnemy[0].aModelEnemy[0], &g_aEnemy[0].charparam);
}

//**************************************************
// �G�l�~�[�̏I��
//**************************************************
void UninitEnemy(void)
{
	
}

//**************************************************
// �G�l�~�[�̍X�V
//**************************************************
void UpdateEnemy(void)
{
	
}

//**************************************************
// �G�l�~�[�̕`��
//**************************************************
void DrawEnemy(void)
{
	//for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	//{
	//	if (g_aEnemy[nCnt].bUse)
	//	{
	//		// �f�o�C�X�̎擾
	//		LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//		// �v�Z�p�}�g���b�N�X
	//		D3DXMATRIX mtxRot, mtxTrans;

	//		// ���݂̃}�e���A���ۑ��p
	//		D3DMATERIAL9 matDef;

	//		// �}�e���A���f�[�^�ւ̃|�C���^
	//		D3DXMATERIAL* pMat;

	//		// ���[���h�}�g���b�N�X�̏�����
	//		D3DXMatrixIdentity(&g_aEnemy[nCnt].mtxWorldEnemy);

	//		// �����𔽉f
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCnt].rot.y, g_aEnemy[nCnt].rot.x, g_aEnemy[nCnt].rot.z);
	//		D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxRot);

	//		// �ʒu�𔽉f
	//		D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCnt].pos.x, g_aEnemy[nCnt].pos.y, g_aEnemy[nCnt].pos.z);
	//		D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxTrans);

	//		// ���[���h�}�g���b�N�X�̐ݒ�
	//		pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCnt].mtxWorldEnemy);

	//		// ���݂̃}�e���A�����擾
	//		pDevice->GetMaterial(&matDef);

	//		// �S���f��(�p�[�c)�̕`��
	//		for (int nCntModel = 0; nCntModel < g_aEnemy[nCnt].charParam.nNumModel; nCntModel++)
	//		{
	//			D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
	//			D3DXMATRIX mtxParent;					// �e�}�g���b�N�X

	//			// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
	//			D3DXMatrixIdentity(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld);

	//			// �p�[�c�̌����𔽉f
	//			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCnt].aModel[nCntModel].rot.y, g_aEnemy[nCnt].aModel[nCntModel].rot.x, g_aEnemy[nCnt].aModel[nCntModel].rot.z);
	//			D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &mtxRotModel);

	//			// �p�[�c�̈ʒu(�I�t�Z�b�g)�𔽉f
	//			D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCnt].aModel[nCntModel].pos.x, g_aEnemy[nCnt].aModel[nCntModel].pos.y, g_aEnemy[nCnt].aModel[nCntModel].pos.z);
	//			D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModel[nCntModel].mtxWorld, &mtxTransModel);

	//			// �p�[�c�u�e�̃}�g���b�N�X�v��ݒ�
	//			if (g_aEnemy[nCnt].aModel[nCntModel].nIdxModelParent != -1)
	//			{// �e���f��������ꍇ
	//				mtxParent = g_aEnemy[nCnt].aModel[g_aEnemy[nCnt].aModel[nCntModel].nIdxModelParent].mtxWorld;	// �e���f���̃C���f�b�N�X��ݒ�
	//			}
	//			else
	//			{// �e�̃��f�����Ȃ��ꍇ
	//				mtxParent = g_aEnemy[nCnt].mtxWorldEnemy;	// �v���C���[�̃}�g���b�N�X��ݒ�
	//			}

	//			// �Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
	//			D3DXMatrixMultiply(&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld,
	//				&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld,
	//				&mtxParent);

	//			// �p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	//			pDevice->SetTransform(D3DTS_WORLD,
	//				&g_aEnemy[nCnt].aModel[nCntModel].mtxWorld);

	//			// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//			pMat = (D3DXMATERIAL*)g_aEnemy[nCnt].aModel[nCntModel].pBuffMat->GetBufferPointer();

	//			for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCnt].aModel[nCntModel].dwNumMat; nCntMat++)
	//			{
	//				if (g_aEnemy[nCnt].charParam.nState == MOTIONTYPE_ENEMY_DAMAGE)
	//				{
	//					D3DXMATERIAL damageMat = pMat[nCntMat];
	//					damageMat.MatD3D.Diffuse.r = 1.0f;
	//					damageMat.MatD3D.Diffuse.g = 0.0f;
	//					damageMat.MatD3D.Diffuse.b = 0.0f;
	//					damageMat.MatD3D.Diffuse.a = 1.0f;

	//					// �}�e���A���̐ݒ�
	//					pDevice->SetMaterial(&damageMat.MatD3D);
	//				}
	//				else
	//				{
	//					// �}�e���A���̐ݒ�
	//					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	//				}

	//				// �e�N�X�`���̐ݒ�
	//				pDevice->SetTexture(0, g_aEnemy[nCnt].aModel[nCntModel].apTexture[nCntMat]);

	//				// �p�[�c�̕`��
	//				g_aEnemy[nCnt].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
	//			}
	//		}

	//		// �ۑ����Ă����}�e���A����߂�
	//		pDevice->SetMaterial(&matDef);
	//	}
	//}
}

