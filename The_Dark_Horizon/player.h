//---------------------------------------
//
//モデル表示処理の定義・宣言[player.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"
#include"stage.h"
#include"model.h"

#define MAX_MODEL (16)
#define MAX_KEY (16)
#define MAX_MOTION (16)
#define SPEED (1.0f)
#define SPEED_DEF (0.0f)
#define JUMP (20.0f)
#define JUMP_INA (0.9f)
#define PLAYER_INA (0.05f)
#define ROT_SPEED (0.1f)
#define PLAYER_LIFE (1000)
#define BLEND_FRAME (10.0f)
#define PLAYER_SIZE (50.0f)

#define MAX_HP (100.0f)
#define MAX_ENERGY (100.0f)
#define BULLET_ENERGY (10.0f)

//プレイヤー状態の列挙型定義
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//復活状態
	PLAYERSTATE_NORMAL,//通常
	PLAYERSTATE_DAMAGE,//ダメージ
	PLAYERSTATE_DIE,//死
	PLAYERSTATE_MAX//数
}PLAYERSTATE;

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_MAX
}MOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;
	KEY aKey[MAX_MODEL];
}KEY_INFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEY_INFO aKeyInfo[MAX_KEY];
}MOTION_INFO;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 scale;
	bool bJump;
	float fLife;
	float fEnergy;
	PLAYERSTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nIdxLife;
	String Xname[MAX_MODEL];
	Model aModel[MAX_MODEL];
	int nNumModel;
	MOTION_INFO aMotionInfo[MAX_MOTION];
	int nNumMotion;
	MOTIONTYPE motionType;
	bool bLoopMotion;
	int nNumKey;
	int nKey;
	int nCounterMotion;
	Stage* pStage;
	bool bUse;
}Player;

void InitPlayer(void);//ポリゴンの初期化処理
void UninitPlayer(void);//ポリゴンの終了処理
void UpdatePlayer(void);//ポリゴンの更新処理
void DrawPlayer(void);//ポリゴンの描画処理
Player* GetPlayer(void);

void UpdateMotion(void);
void CollisionPlayer(D3DXVECTOR3 pos, float Length);

#endif _PLAYER_H_