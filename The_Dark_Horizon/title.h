//------------------------------------------
//
//�^�C�g���̏����̒�`�E�錾[title.h]
//Author fuma sato
//
//------------------------------------------

#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"

#define TEXTURE_ROGO "data\\TEXTURE\\Title Rogo.png"
#define TEXTURE_ROGOTXT "data\\TEXTURE\\Title txt.png"
#define TEXTURE_START "data\\TEXTURE\\Enter or Start.png"
#define TEXTURE_SELECT "data\\TEXTURE\\Select.png"

// �^�C�g��UI�̗񋓌^
typedef enum
{
	UITYPE_GAMEPLAY = 0,
	UITYPE_VERSUS,
	UITYPE_TUTORIAL,
	UITYPE_RANKING,
	UITYPE_OPTION,
	UITYPE_EXIT,
	UITYPE_MAX
}UIType;

// �^�C�g���̗񋓌^
typedef enum
{
	TITLETYPE_SKY = 0,
	TITLETYPE_MOON,
	TITLETYPE_NAME,
	TITLETYPE_GAMEPLAY,
	TITLETYPE_TUTORIAL,
	TITLETYPE_EXIT,
	TITLETYPE_MAX,
}TitleType;

// �񋓌^�Ƀe�N�X�`��������
static const char* ITEM_TEXTURE[TITLETYPE_MAX] =
{
	"data\\TEXTURE\\titlesky000.jpg",
	"data\\TEXTURE\\titlemoon000.png",
	"data\\TEXTURE\\titlename000.png",
	"data\\TEXTURE\\Select.png",
	"data\\TEXTURE\\Select.png",
	"data\\TEXTURE\\Select.png",
};

// �^�C�g��UI�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	float fWidth;			// ����
	float fHeght;			// �c��
	bool bUse;				// �g�p���Ă��邩�ǂ���
	int nCountTime;			// ���Ԃ��J�E���g����
}TitleUI;

void InitTitle(void);//�^�C�g������������
void UninitTitle(void);//�^�C�g���I������
void UpdateTitle(void);//�^�C�g���X�V����
void DrawTitle(void);//�^�C�g���`�揈��

#endif _TITLE_H_
