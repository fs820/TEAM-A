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
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		// �ʒu
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���

		g_aEnemy[nCntEnemy].charParam.bUse = false;
	}

	g_aEnemy[0].charParam.bUse = true;

	// �X�N���v�g�ǂݍ���
	ReadScript("data\\tetsuji\\text\\motion.txt", &g_aEnemy[0].motion, &g_aEnemy[0].aModelEnemy[0], &g_aEnemy[0].charParam);

	int i = 0;
}

//**************************************************
// �G�l�~�[�̏I��
//**************************************************
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �ő�G�l�~�[����
		for (int nCntModel = 0; nCntModel < MAX_MODELE_PARTS_ENEMY; nCntModel++)
		{// ���f���p�[�c������
			for (int nCntTex = 0; nCntTex < MAX_MODEL_TEXTURE; nCntTex++)
			{// ���f���p�[�c������
				if (g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].apTexture[nCntTex] != NULL)
				{// �e�N�X�`������������j��
					g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].apTexture[nCntTex]->Release();
					g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].apTexture[nCntTex] = NULL;
				}
			}

			if (g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pBuffMat != NULL)
			{// �}�e���A��������Δj��
				g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pBuffMat->Release();
				g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pBuffMat = NULL;
			}

			if (g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pMesh != NULL)
			{// ���b�V��������Δj��
				g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pMesh->Release();
				g_aEnemy[nCntEnemy].aModelEnemy[nCntModel].pMesh = NULL;
			}
		}
	}
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
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].charParam.bUse)
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
			D3DXMatrixIdentity(&g_aEnemy[nCnt].mtxWorldEnemy);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCnt].rot.y, g_aEnemy[nCnt].rot.x, g_aEnemy[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCnt].pos.x, g_aEnemy[nCnt].pos.y, g_aEnemy[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCnt].mtxWorldEnemy, &g_aEnemy[nCnt].mtxWorldEnemy, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCnt].mtxWorldEnemy);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �S���f��(�p�[�c)�̕`��
			for (int nCntModel = 0; nCntModel < g_aEnemy[nCnt].charParam.nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxParent;					// �e�}�g���b�N�X

				// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld);

				// �p�[�c�̌����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCnt].aModelEnemy[nCntModel].rot.y, g_aEnemy[nCnt].aModelEnemy[nCntModel].rot.x, g_aEnemy[nCnt].aModelEnemy[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld, &mtxRotModel);

				// �p�[�c�̈ʒu(�I�t�Z�b�g)�𔽉f
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCnt].aModelEnemy[nCntModel].pos.x, g_aEnemy[nCnt].aModelEnemy[nCntModel].pos.y, g_aEnemy[nCnt].aModelEnemy[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld, &g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld, &mtxTransModel);

				// �p�[�c�u�e�̃}�g���b�N�X�v��ݒ�
				if (g_aEnemy[nCnt].aModelEnemy[nCntModel].nIdxModelEnemyParent != -1)
				{// �e���f��������ꍇ
					mtxParent = g_aEnemy[nCnt].aModelEnemy[g_aEnemy[nCnt].aModelEnemy[nCntModel].nIdxModelEnemyParent].mtxWorld;	// �e���f���̃C���f�b�N�X��ݒ�
				}
				else
				{// �e�̃��f�����Ȃ��ꍇ
					mtxParent = g_aEnemy[nCnt].mtxWorldEnemy;	// �v���C���[�̃}�g���b�N�X��ݒ�
				}

				// �Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�}�g���b�N�X���������킹��
				D3DXMatrixMultiply(&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld,
					&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld,
					&mtxParent);

				// �p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD,
					&g_aEnemy[nCnt].aModelEnemy[nCntModel].mtxWorld);

				// �}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aEnemy[nCnt].aModelEnemy[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCnt].aModelEnemy[nCntModel].dwNumMat; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_aEnemy[nCnt].aModelEnemy[nCntModel].apTexture[nCntMat]);

					// �p�[�c�̕`��
					g_aEnemy[nCnt].aModelEnemy[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

