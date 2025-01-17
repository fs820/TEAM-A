#ifndef _EDITPLAYER_H_
#define _EDITPLAYER_H_

#include "main.h"

#define MAX_EDITPLAYER_TEX_NUM (6)		// �e�N�X�`���̐�
#define EDITPLAYER_MOVE_MAX (20.0f)		// �G�f�B�b�g�v���C���[�̈ړ���
#define EDITPLAYER_GRAVITY_MAX (10.0f)	// �G�f�B�b�g�v���C���[�̏d�͗�

// �G�f�B�b�g�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 posOld;	// �Â��ʒu
	D3DXVECTOR3 move;	// �ړ���
	D3DXVECTOR3 rot;	// ����
	D3DXVECTOR3 rotDest;// �ړI�̌���
	float movement;		// �ړ���
	float graviment;	// �d�͗�
	float jumpment;		// �W�����v��
	bool bDisp;			// �f�����ǂ���

	LPDIRECT3DTEXTURE9 apTexture[MAX_EDITPLAYER_TEX_NUM];	// �e�N�X�`���ւ̃|���^
	LPD3DXMESH pMesh;		// ���b�V��(���_���ւ̃|�C���^)
	LPD3DXBUFFER pBuffMat;	// �}�e���A���ւ̃|�C���^
	DWORD dwNumMat;			// �}�e���A���̐�
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
}EDITPLAYER;

void InitEditPlayer();			// �G�f�B�b�g�v���C���[�̏�����
void UninitEditPlayer();		// �G�f�B�b�g�v���C���[�̏I��
void UpdateEditPlayer();		// �G�f�B�b�g�v���C���[�̍X�V
void DrawEditPlayer();			// �G�f�B�b�g�v���C���[�̕`��
void EditPlayerManager();		// �G�f�B�b�g�v���C���[�̊Ǘ�
EDITPLAYER* GetEditPlayer();	// �G�f�B�b�g�v���C���[�̎擾
#endif // !_EDITPLAYER_H_
