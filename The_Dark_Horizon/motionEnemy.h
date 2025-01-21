#ifndef _MOTIONENEMY_H_
#define _MOTIONENEMY_H_

#include "main.h"
#include "modelEnemy.h"

typedef enum
{
	SCRIPT_TYPE_SCRIPT = 0,		// スクリプト
	SCRIPT_TYPE_CHARCTERSET,	// キャラクターセット
	SCRIPT_TYPE_MAX		
}SCRIPT_TYPE;

#define MAX_KEY (16)			// 最大キー数
#define MAX_KEY_INFO (32)		// 最大キーインフォ数
#define MAX_MOTION_INFO (15)	// 最大モーションインフォ数

// キーの構造体
typedef struct
{
	float fPosX;// 位置X
	float fPosY;// 位置Y
	float fPosZ;// 位置Z
	float fRotX;// 向きX
	float fRotY;// 向きY
	float fRotZ;// 向きZ
}KEY_ENEMY;

// キー情報の構造体
typedef struct
{
	int nFrame;					// 再生フレーム
	KEY_ENEMY aKey[MAX_KEY];	// 各パーツのキー要素
}KEY_INFO_ENEMY;

// キーモーション情報構造体
typedef struct
{
	bool bLoop;								// ループするかどうか
	int nNumKey;							// キーの総数
	KEY_INFO_ENEMY aKeyinfo[MAX_KEY_INFO];	// キー情報
}MOTION_INFO_ENEMY;

typedef struct
{
	MOTION_INFO_ENEMY aMotionInfo[MAX_MOTION_INFO];	// モーション情報
	int nNumMotion;									// モーションの総数
	bool bLoopMotion;								// ループするかどうか
	int nNumKey;									// キーの総数
	int nKey;										// 現在のキーNo.
	int nCounterMotion;								// モーションカウンター
	int nNowMotiType;								// 現在のモーションタイプ

	int nNextKey;									// 次のキー
}MOTION_ENEMY;

// キャラクターパラメーター
typedef struct
{
	float fWidth;	// 幅
	float fHeigt;	// 高さ
	float fJamp;	// ジャンプ力
	float fRadius;	// 半径
	int nNumModel;	// モデル数
	int nLife;		// 体力
	int nState;		// 状態
	bool bMove;		// 動くかどうか
	bool bJanp;		// ジャンプしているかどうか
	bool bUse;		// 使っているかどうか
}CHARPARAM;

typedef struct
{
	int nCntMotionInfo;		//	モーション情報をカウントするもの
	int nCntKeyInfo;	//	キーモーションの情報をカウントするもの
	int nCntKey;		//	キーをカウントするもの
}SET_MOTION_MANAGER;

// プロトタイプ宣言
void InitMotion(void);

void ReadScript(const char* pFileName, MOTION_ENEMY* pMotionEnemy, ModelEnemy* pModelEnemy, CHARPARAM* pCharparam);	// スクリプトを読み込む関数
void cleareString(int nCntChar, char* cData);	// 文字列をリセットする関数
#endif // !_MOTION_H_