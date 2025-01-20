#ifndef _GAGE_H_
#define _GAGE_H_

#include "main.h"

// �񋓌^
typedef enum
{
	GAGETYPE_HPBACKGAGE = 0,
	GAGETYPE_REDGAGEH,
	GAGETYPE_HPGAGE,
	GAGETYPE_ENERGYBACKGAGE,
	GAGETYPE_ENERGYGAGE,
	GAGETYPE_O2BACKGAGE,
	GAGETYPE_O2GAGE,
	GAGETYPE_MAX
}GageType;

static const char* GAGE_TEXTURE[GAGETYPE_MAX] =
{
	"data\\TEXTURE\\BackGage000.png",
	"data\\TEXTURE\\Gage000.png",
	"data\\TEXTURE\\Gage000.png",
	"data\\TEXTURE\\BackGage000.png",
	"data\\TEXTURE\\Gage001.png",
	"data\\TEXTURE\\BackGage001.png",
	"data\\TEXTURE\\BackGage001.png",
};
//GageInfo g_Gageinfo[GAGETYPE_MAX] =
//{
//	{"data\\TEXTURE\\BackGage000.png"},
//	{"data\\TEXTURE\\Gage000.png"},
//	{"data\\TEXTURE\\Gage000.png"}
//};

//// �Q�[�W���̍\����
//typedef struct
//{
//	const char* TextureName;
//}GageInfo;

// HP�Q�[�W�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	float fWidth;		// ����
	float fWidthR;		// �ԃQ�[�W�̉���
	float fHeght;		// �c��
	float fDifference;	// �ԃQ�[�W�Ƃ̍���
	bool bUse;			// �g�p���Ă��邩�ǂ���
	int nCountTime;		// ���Ԃ��J�E���g����
}HPgage;

// �G�l���M�[�Q�[�W�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	float fWidth;			// ����
	float fHeght;			// �c��
	bool bUse;				// �g�p���Ă��邩�ǂ���
	float fDifference;		// �ő�̃Q�[�W�Ƃ̍���
	int nCountTime;			// ���Ԃ��J�E���g����
}Energygage;

// O2�Q�[�W�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	float fWidth;		// ����
	float fHeght;		// �c��
	float fDifference;	// ����O�̃Q�[�W�Ƃ̍���
	int nCountTime;		// ���Ԃ��J�E���g����
}O2gage;

// �v���g�^�C�v�錾
void Initgage(void);
void Uninitgage(void);
void Updategage(void);
void UpdateRedgage(void);
void Drawgage(void);
void SetHPgage(void);
void SetEnergygage(void);
void SetO2gage(void);

#endif
