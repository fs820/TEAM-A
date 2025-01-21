#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

// �񋓌^
typedef enum
{
	ITEMTYPE_FRAME0 = 0,
	ITEMTYPE_ITEM0,
	ITEMTYPE_FRAME1,
	ITEMTYPE_ITEM1,
	ITEMTYPE_FRAME2,
	ITEMTYPE_ITEM2,
	ITEMTYPE_MAX
}ItemType;

static const char* ITEM_TEXTURE[ITEMTYPE_MAX] =
{
	"data\\TEXTURE\\Item000.png",
	"data\\TEXTURE\\Item001.png",
	"data\\TEXTURE\\Item000.png",
	"data\\TEXTURE\\Item001.png",
	"data\\TEXTURE\\Item000.png",
	"data\\TEXTURE\\Item001.png",
};

// �A�C�e���\����
typedef struct
{
	D3DXVECTOR3 TXpos;	// �e�N�X�`���̈ʒu
	D3DCOLOR TXcol;		// �e�N�X�`���̐F
}Item;

// �v���g�^�C�v�錾
void Inititem(void);
void Uninititem(void);
void Updateitem(void);
void Drawitem(void);
void Setitem(int nIdxItem);

#endif