#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "modelEnemy.h"
#include "motionEnemy.h"

// �}�N����`
#define MAX_ENEMY (32)		// �G�̍ő吔

// �G�l�~�[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	D3DXVECTOR3 move;	// �ړ���

	ModelEnemy aModelEnemy[10];	// ���f���p�[�c
	MOTION_ENEMY motion;		// ���[�V����
	CHARPARAM charparam;		// �L�����N�^�[�p�����[�^
}ENEMY;

// �G�l�~�[�̊Ǘ��\����
typedef struct
{
	int nNumEnemy;	// �G�l�~�[�̑������g�̊ԍ���
}ENEMY_MANAGER;

// �v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy(void);
#endif // !_ENEMY_H_
