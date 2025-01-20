#ifndef _GAGE_H_
#define _GAGE_H_

#include "main.h"

// 列挙型
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

//// ゲージ情報の構造体
//typedef struct
//{
//	const char* TextureName;
//}GageInfo;

// HPゲージ構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	float fWidth;		// 横幅
	float fWidthR;		// 赤ゲージの横幅
	float fHeght;		// 縦幅
	float fDifference;	// 赤ゲージとの差分
	bool bUse;			// 使用しているかどうか
	int nCountTime;		// 時間をカウントする
}HPgage;

// エネルギーゲージ構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	float fWidth;			// 横幅
	float fHeght;			// 縦幅
	bool bUse;				// 使用しているかどうか
	float fDifference;		// 最大のゲージとの差分
	int nCountTime;			// 時間をカウントする
}Energygage;

// O2ゲージ構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	float fWidth;		// 横幅
	float fHeght;		// 縦幅
	float fDifference;	// 減る前のゲージとの差分
	int nCountTime;		// 時間をカウントする
}O2gage;

// プロトタイプ宣言
void Initgage(void);
void Uninitgage(void);
void Updategage(void);
void UpdateRedgage(void);
void Drawgage(void);
void SetHPgage(void);
void SetEnergygage(void);
void SetO2gage(void);

#endif
