//------------------------------------------
//
//タイトルの処理[title.cpp]
//Author fuma sato
//
//------------------------------------------

#include"title.h"
#include"input.h"
#include"fade.h"

// マクロ定義
#define MAX_TEXTUREW_TITLE (1280.0f)		// タイトルテクスチャの横幅
#define MAX_TEXTUREH_TITLE (720.0f)			// タイトルテクスチャの縦幅
#define MAX_TEXTUREW_TITLENAME (1000.0f)	// タイトル名テクスチャの横幅
#define MAX_TEXTUREH_TITLENAME (200.0f)		// タイトル名テクスチャの縦幅
#define MAX_TEXTUREW_TITLEUI (500.0f)		// タイトルUIテクスチャの横幅
#define MAX_TEXTUREH_TITLEUI (90.0f)		// タイトルUIテクスチャの縦幅
#define MAX_TEXTUREW (10.0f)				// UIテクスチャ同士の横幅
#define MAX_TITLEUI (3)						// UIテクスチャの最大数

// グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLETYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			// 頂点バッファへのポインタ
TitleUI g_TitleUI[MAX_TITLEUI];							// タイトルの構造体

//--------------------
//初期化処理
//--------------------
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // デバイスへのポインタ

	// タイトルの構造体の初期化
	for (int nCount = 0; nCount < MAX_TITLEUI; nCount++)
	{
		g_TitleUI[nCount].pos = D3DXVECTOR3(640.0f, 400.0f, 0.0f);	// 位置を初期化する
		g_TitleUI[nCount].fWidth = MAX_TEXTUREW_TITLEUI;			// 横幅を初期化する 
		g_TitleUI[nCount].fHeght = MAX_TEXTUREH_TITLEUI;			// 縦幅を初期化する 
		g_TitleUI[nCount].bUse = false;								// 使用しているかを初期化する 
		g_TitleUI[nCount].nCountTime = 0;							// カウントを初期化する 
	}

	// デバイスの取得
	pDevice = GetDevice();

	for (int nCount = 0; nCount < TITLETYPE_MAX; nCount++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCount],
			&g_pTextureTitle[nCount]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_TITLEUI + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < TITLETYPE_MAX; nCount++)
	{
		// 頂点座標の設定
		pVtx[0 + (4 * nCount)].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2 + (4 * nCount)].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3 + (4 * nCount)].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhwの設定																					
		pVtx[0 + (4 * nCount)].rhw = 1.0f;
		pVtx[1 + (4 * nCount)].rhw = 1.0f;
		pVtx[2 + (4 * nCount)].rhw = 1.0f;
		pVtx[3 + (4 * nCount)].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);

		/*switch (nCount)
		{
		case TITLETYPE_SKY:
			break;
		case TITLETYPE_MOON:
			break;
		case TITLETYPE_NAME:
			break;
		case TITLETYPE_GAMEPLAY:
			break;
		case TITLETYPE_TUTORIAL:
			break;
		case TITLETYPE_EXIT:
			break;

		}*/
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

}

//------------------
//終了処理
//------------------
void UninitTitle(void)
{

}

//--------------
//更新処理
//--------------
void UpdateTitle(void)
{
	if (GetKeyboradTrigger(DIK_RETURN) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetJoykeyTrigger(JOYKEY_A, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_LEFT) == true)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			//切替
			SetFade(MODE_GAME);
		}
	}

	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//切替
					SetFade(MODE_GAME);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_CI, (CONTROLLER)i) || GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//切替
					SetFade(MODE_GAME);
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(NINKEY_＋, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//切替
					SetFade(MODE_GAME);
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_A, (CONTROLLER)i) || GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//切替
					SetFade(MODE_GAME);
				}
			}
		}
	}
}

//-------------------
//描画処理
//-------------------
void DrawTitle(void)
{

}
