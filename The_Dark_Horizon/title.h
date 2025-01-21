//------------------------------------------
//
//タイトルの処理の定義・宣言[title.h]
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

// タイトルUIの列挙型
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

// タイトルの列挙型
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

// 列挙型にテクスチャ名を代入
static const char* ITEM_TEXTURE[TITLETYPE_MAX] =
{
	"data\\TEXTURE\\titlesky000.jpg",
	"data\\TEXTURE\\titlemoon000.png",
	"data\\TEXTURE\\titlename000.png",
	"data\\TEXTURE\\Select.png",
	"data\\TEXTURE\\Select.png",
	"data\\TEXTURE\\Select.png",
};

// タイトルUIの構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	float fWidth;			// 横幅
	float fHeght;			// 縦幅
	bool bUse;				// 使用しているかどうか
	int nCountTime;			// 時間をカウントする
}TitleUI;

void InitTitle(void);//タイトル初期化処理
void UninitTitle(void);//タイトル終了処理
void UpdateTitle(void);//タイトル更新処理
void DrawTitle(void);//タイトル描画処理

#endif _TITLE_H_
