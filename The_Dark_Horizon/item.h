#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

// 列挙型
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

// アイテム構造体
typedef struct
{
	D3DXVECTOR3 TXpos;	// テクスチャの位置
	D3DCOLOR TXcol;		// テクスチャの色
}Item;

// プロトタイプ宣言
void Inititem(void);
void Uninititem(void);
void Updateitem(void);
void Drawitem(void);
void Setitem(int nIdxItem);

#endif