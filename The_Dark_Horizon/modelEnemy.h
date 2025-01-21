#ifndef _MODELENEMY_H_
#define _MODELENEMY_H_

#include "main.h"

#define MAX_MODEL_TEXTURE (6)	// ���f���̃e�N�X�`���̍ő喇��
// ���f���\����
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[MAX_MODEL_TEXTURE];	// �e�N�X�`���ւ̃|���^
	LPD3DXMESH pMesh;					// ���b�V��(���_���ւ̃|�C���^)
	LPD3DXBUFFER pBuffMat;				// �}�e���A���ւ̃|�C���^
	DWORD dwNumMat;						// �}�e���A���̐�
	int nIdxModelEnemyParent;			// �e���f���̃C���f�b�N�X
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 offSet;					// �I�t�Z�b�g
	D3DXVECTOR3 rot;					// ����
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X

}ModelEnemy;

//�v���g�^�C�v�錾
void SetModelEnemy(char astr[], ModelEnemy* pModelEnemy, int nModelEnemyNum);	// ���f���̐ݒ� 
void PartsSet(FILE* pFile, ModelEnemy* model);//  
void EndPartsSet(ModelEnemy* pModelEnemy, ModelEnemy model, int nIndex);// 

#endif // !_MODEL_H_
