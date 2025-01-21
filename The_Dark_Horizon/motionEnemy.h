#ifndef _MOTIONENEMY_H_
#define _MOTIONENEMY_H_

#include "main.h"
#include "modelEnemy.h"

typedef enum
{
	SCRIPT_TYPE_SCRIPT = 0,		// �X�N���v�g
	SCRIPT_TYPE_CHARCTERSET,	// �L�����N�^�[�Z�b�g
	SCRIPT_TYPE_MAX		
}SCRIPT_TYPE;

#define MAX_KEY (16)			// �ő�L�[��
#define MAX_KEY_INFO (32)		// �ő�L�[�C���t�H��
#define MAX_MOTION_INFO (15)	// �ő僂�[�V�����C���t�H��

// �L�[�̍\����
typedef struct
{
	float fPosX;// �ʒuX
	float fPosY;// �ʒuY
	float fPosZ;// �ʒuZ
	float fRotX;// ����X
	float fRotY;// ����Y
	float fRotZ;// ����Z
}KEY_ENEMY;

// �L�[���̍\����
typedef struct
{
	int nFrame;					// �Đ��t���[��
	KEY_ENEMY aKey[MAX_KEY];	// �e�p�[�c�̃L�[�v�f
}KEY_INFO_ENEMY;

// �L�[���[�V�������\����
typedef struct
{
	bool bLoop;								// ���[�v���邩�ǂ���
	int nNumKey;							// �L�[�̑���
	KEY_INFO_ENEMY aKeyinfo[MAX_KEY_INFO];	// �L�[���
}MOTION_INFO_ENEMY;

typedef struct
{
	MOTION_INFO_ENEMY aMotionInfo[MAX_MOTION_INFO];	// ���[�V�������
	int nNumMotion;									// ���[�V�����̑���
	bool bLoopMotion;								// ���[�v���邩�ǂ���
	int nNumKey;									// �L�[�̑���
	int nKey;										// ���݂̃L�[No.
	int nCounterMotion;								// ���[�V�����J�E���^�[
	int nNowMotiType;								// ���݂̃��[�V�����^�C�v

	int nNextKey;									// ���̃L�[
}MOTION_ENEMY;

// �L�����N�^�[�p�����[�^�[
typedef struct
{
	float fWidth;	// ��
	float fHeigt;	// ����
	float fJamp;	// �W�����v��
	float fRadius;	// ���a
	int nNumModel;	// ���f����
	int nLife;		// �̗�
	int nState;		// ���
	bool bMove;		// �������ǂ���
	bool bJanp;		// �W�����v���Ă��邩�ǂ���
	bool bUse;		// �g���Ă��邩�ǂ���
}CHARPARAM;

typedef struct
{
	int nCntMotionInfo;		//	���[�V���������J�E���g�������
	int nCntKeyInfo;	//	�L�[���[�V�����̏����J�E���g�������
	int nCntKey;		//	�L�[���J�E���g�������
}SET_MOTION_MANAGER;

// �v���g�^�C�v�錾
void InitMotion(void);

void ReadScript(const char* pFileName, MOTION_ENEMY* pMotionEnemy, ModelEnemy* pModelEnemy, CHARPARAM* pCharparam);	// �X�N���v�g��ǂݍ��ފ֐�
void cleareString(int nCntChar, char* cData);	// ����������Z�b�g����֐�
#endif // !_MOTION_H_