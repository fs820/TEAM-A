//======================================================
//
// ゲージの処理
// Aouther:Takahashi misaki
// 
//======================================================

#include "gage.h"
#include "player.h"
#include "game.h"

// マクロ定義
#define MAX_TEXTUREW_HP (570.0f)
#define MAX_TEXTUREH_HP (40.0f)
#define MAX_TEXTUREW_ENERGY (520.0f)
#define MAX_TEXTUREH_ENERGY (40.0f)
#define MAX_TEXTUREW_O2 (50.0f)
#define MAX_TEXTUREH_O2 (500.0f)

// グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturegage[GAGETYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffgage = NULL;			// 頂点バッファへのポインタ
HPgage g_hpgage;										// 体力ゲージの構造体
Energygage g_energygage;								// エネルギーゲージの構造体
O2gage g_o2gage;										// 酸素ゲージの構造体
//=====================================================
// ゲージの初期化設定
//=====================================================
void Initgage(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // デバイスへのポインタ

	// 体力ゲージの構造体
	g_hpgage.bUse = false;								// ゲージを使用しているかを初期化する
	g_hpgage.fWidth = MAX_TEXTUREW_HP;					// 横幅を初期化する
	g_hpgage.fWidthR = MAX_TEXTUREW_HP;					// 赤ゲージの横幅を初期化する
	g_hpgage.fHeght = MAX_TEXTUREH_HP;					// 縦幅を初期化する
	g_hpgage.fDifference = 0.0f;						// 赤ゲージとの差分を初期化する
	g_hpgage.pos = D3DXVECTOR3(30.0f, 10.0f, 0.0f);		// 位置を初期化する
	g_hpgage.nCountTime = 0;							// カウントを初期化する

	// エネルギーゲージの構造体
	g_energygage.bUse = true;								// ゲージを使用しているかを初期化する
	g_energygage.fWidth = MAX_TEXTUREW_ENERGY;				// 横幅を初期化する
	g_energygage.fHeght = MAX_TEXTUREH_ENERGY;				// 縦幅を初期化する
	g_energygage.fDifference = 0.0f;						// 最大ゲージとの差分を初期化する
	g_energygage.pos = D3DXVECTOR3(30.0f, 60.0f, 0.0f);		// 位置を初期化する
	g_energygage.nCountTime = 0;							// カウントを初期化する

	// 酸素ゲージの構造体
	g_o2gage.fWidth = MAX_TEXTUREW_O2;					// 横幅を初期化する
	g_o2gage.fHeght = MAX_TEXTUREH_O2;					// 縦幅を初期化する
	g_o2gage.fDifference = 0.0f;						// 前のゲージとの差分を初期化する
	g_o2gage.pos = D3DXVECTOR3(30.0f, 640.0f, 0.0f);	// 位置を初期化する
	g_o2gage.nCountTime = 0;							// カウントを初期化する

	// デバイスの取得
	pDevice = GetDevice();

	for (int nCount = 0; nCount < GAGETYPE_MAX; nCount++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			GAGE_TEXTURE[nCount],
			&g_pTexturegage[nCount]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAGETYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffgage,
		NULL);

	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < GAGETYPE_MAX; nCount++)
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
		pVtx[0 + (4 * nCount)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1 + (4 * nCount)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2 + (4 * nCount)].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3 + (4 * nCount)].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 後ろのゲージ
	// 頂点座標の設定
	pVtx[0 + (4 * GAGETYPE_HPBACKGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x, g_hpgage.pos.y, 0.0f);
	pVtx[1 + (4 * GAGETYPE_HPBACKGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth, g_hpgage.pos.y, 0.0f);
	pVtx[2 + (4 * GAGETYPE_HPBACKGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x, g_hpgage.pos.y + g_hpgage.fHeght, 0.0f);
	pVtx[3 + (4 * GAGETYPE_HPBACKGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth, g_hpgage.pos.y + g_hpgage.fHeght, 0.0f);

	// HPゲージの赤ゲージ
	// 頂点座標の設定
	pVtx[0 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth - 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth - 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0 + (4 * GAGETYPE_REDGAGEH)].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1 + (4 * GAGETYPE_REDGAGEH)].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2 + (4 * GAGETYPE_REDGAGEH)].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3 + (4 * GAGETYPE_REDGAGEH)].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	// HPゲージ
	// 頂点座標の設定
	pVtx[0 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth - 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidth - 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);

	// エネルギーゲージの後ろのゲージ
	// 頂点座標の設定
	pVtx[0 + (4 * GAGETYPE_ENERGYBACKGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x, g_energygage.pos.y, 0.0f);
	pVtx[1 + (4 * GAGETYPE_ENERGYBACKGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth, g_energygage.pos.y, 0.0f);
	pVtx[2 + (4 * GAGETYPE_ENERGYBACKGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x, g_energygage.pos.y + g_energygage.fHeght, 0.0f);
	pVtx[3 + (4 * GAGETYPE_ENERGYBACKGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth, g_energygage.pos.y + g_energygage.fHeght, 0.0f);

	// エネルギーゲージ
	// 頂点座標の設定
	pVtx[0 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth - 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth - 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);

	// 酸素ゲージの後ろのゲージ
	// 頂点座標の設定
	pVtx[0 + (4 * GAGETYPE_O2BACKGAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x, g_o2gage.pos.y - g_o2gage.fHeght, 0.0f);
	pVtx[1 + (4 * GAGETYPE_O2BACKGAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth, g_o2gage.pos.y - g_o2gage.fHeght, 0.0f);
	pVtx[2 + (4 * GAGETYPE_O2BACKGAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x, g_o2gage.pos.y, 0.0f);
	pVtx[3 + (4 * GAGETYPE_O2BACKGAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth, g_o2gage.pos.y, 0.0f);

	// 酸素ゲージ
	// 頂点座標の設定
	pVtx[0 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0 + (4 * GAGETYPE_O2GAGE)].col = D3DCOLOR_RGBA(0, 0, 255, 255);
	pVtx[1 + (4 * GAGETYPE_O2GAGE)].col = D3DCOLOR_RGBA(0, 0, 255, 255);
	pVtx[2 + (4 * GAGETYPE_O2GAGE)].col = D3DCOLOR_RGBA(0, 0, 255, 255);
	pVtx[3 + (4 * GAGETYPE_O2GAGE)].col = D3DCOLOR_RGBA(0, 0, 255, 255);

	// 頂点バッファをアンロックする
	g_pVtxBuffgage->Unlock();
}
//=====================================================
// 背景の終了処理
//=====================================================
void Uninitgage(void)
{
	for (int nCount = 0; nCount < GAGETYPE_MAX; nCount++)
	{
		// テクスチャの破棄
		if (g_pTexturegage[nCount] != NULL)
		{
			g_pTexturegage[nCount]->Release();
			g_pTexturegage[nCount] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffgage != NULL)
	{
		g_pVtxBuffgage->Release();
		g_pVtxBuffgage = NULL;
	}
}
//=====================================================
// ゲージの更新処理
//=====================================================
void Updategage(void)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ
	Player* pPlayer = GetPlayer();
	float EnergyP = 0.0f;
	float fNowO2 = 0.0f;
	int nCount = 0;

	if (pPlayer->fEnergy < MAX_ENERGY)
	{
		g_energygage.nCountTime++;

		if (g_energygage.nCountTime >= 150)
		{
			g_energygage.bUse = false;

			if (g_energygage.bUse == false)
			{
				g_energygage.fDifference = MAX_TEXTUREW_ENERGY - g_energygage.fWidth;

				g_energygage.fWidth += g_energygage.fDifference * 0.1f;

				// エネルギーゲージ
				// 頂点バッファをロックし、頂点情報へのポインタを取得
				g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

				// 頂点座標の設定
				// 割合に応じてゲージの長さを変化させる
				pVtx[0 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
				pVtx[1 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth - 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
				pVtx[2 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);
				pVtx[3 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + g_energygage.fWidth - 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);

				// 頂点バッファをアンロックする
				g_pVtxBuffgage->Unlock();

				if (g_energygage.fWidth > MAX_TEXTUREW_ENERGY - 10)
				{
					g_energygage.nCountTime = 0;
					g_energygage.fWidth = MAX_TEXTUREW_ENERGY;
					g_energygage.fDifference = 0.0f;
					pPlayer->fEnergy = MAX_ENERGY;
					g_energygage.bUse = true;
				}
			}
		}
	}

	// 酸素ゲージの減少
	g_o2gage.nCountTime++;

	if (g_o2gage.nCountTime == 60)
	{
		g_o2gage.fHeght -= (float)(MAX_TEXTUREH_O2 / 120.0f);

		// エネルギーゲージ
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		// 割合に応じてゲージの長さを変化させる
		pVtx[0 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
		pVtx[1 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
		pVtx[2 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y  - 5.0f, 0.0f);
		pVtx[3 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);

		// テクスチャ座標の設定
		pVtx[0 + (4 * GAGETYPE_O2GAGE)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * GAGETYPE_O2GAGE)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * GAGETYPE_O2GAGE)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * GAGETYPE_O2GAGE)].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点バッファをアンロックする
		g_pVtxBuffgage->Unlock();

		if (g_o2gage.fHeght <= 0.0f)
		{
			SetGameState(GAMESTATE_END);
		}

		g_o2gage.nCountTime = 0;
	}

}
//=====================================================
// ゲージの描画処理
//=====================================================
void Drawgage(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // デバイスへのポインタ

	Player* pPlayer = GetPlayer();

	// デバイスの取得
	pDevice = GetDevice();

	if (pPlayer->fLife > 0)
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffgage, 0, sizeof(VERTEX_2D));
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		for (int nCount = 0; nCount < GAGETYPE_MAX; nCount++)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTexturegage[nCount]);
			// ゲージの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
		}
	}
}
//=====================================================
// HPゲージの設定処理
//=====================================================
void SetHPgage(void)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ
	Player* pPlayer = GetPlayer();

	// 変化した体力を割合に変換させる
	float fPercentHP = (float)(pPlayer->fLife / MAX_HP);

	float fWidth = MAX_TEXTUREW_HP * fPercentHP;

	g_hpgage.fDifference = g_hpgage.fWidth - fWidth;

	g_hpgage.fWidth = fWidth;

	// HPゲージ
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	// 割合に応じてゲージの長さを変化させる
	pVtx[0 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + fWidth - 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_HPGAGE)].pos = D3DXVECTOR3(g_hpgage.pos.x + fWidth - 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffgage->Unlock();
}
//=====================================================
// 赤ゲージの更新処理
//=====================================================
void UpdateRedgage(void)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

	// 体力が減少した後に処理をする
	if (g_hpgage.fDifference > 0.0f)
	{
		g_hpgage.nCountTime++;

		if (g_hpgage.nCountTime >= 60)
		{
			g_hpgage.fWidthR -= g_hpgage.fDifference * 0.1f;

			// 頂点座標の設定
			// ゲージの長さを徐々に変化させる
			pVtx[0 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
			pVtx[1 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidthR - 10.0f, g_hpgage.pos.y + 5.0f, 0.0f);
			pVtx[2 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);
			pVtx[3 + (4 * GAGETYPE_REDGAGEH)].pos = D3DXVECTOR3(g_hpgage.pos.x + g_hpgage.fWidthR - 10.0f, g_hpgage.pos.y + g_hpgage.fHeght - 5.0f, 0.0f);

			if (g_hpgage.fWidthR < g_hpgage.fWidth)
			{
				g_hpgage.nCountTime = 0;
				g_hpgage.fDifference = 0.0f;
				g_hpgage.fWidthR = g_hpgage.fWidth;
			}
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffgage->Unlock();
}
//=====================================================
// エネルギーゲージの設定処理
//=====================================================
void SetEnergygage(void)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ
	Player* pPlayer = GetPlayer();

	if (g_energygage.bUse == true)
	{
		// 変化したエネルギーを割合に変換させる
		float fPercentEnergy = (float)(pPlayer->fEnergy / MAX_ENERGY);

		float fWidth = MAX_TEXTUREW_ENERGY * fPercentEnergy;

		g_energygage.fWidth = fWidth;

		// エネルギーゲージ
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		// 割合に応じてゲージの長さを変化させる
		pVtx[0 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
		pVtx[1 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + fWidth - 10.0f, g_energygage.pos.y + 5.0f, 0.0f);
		pVtx[2 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);
		pVtx[3 + (4 * GAGETYPE_ENERGYGAGE)].pos = D3DXVECTOR3(g_energygage.pos.x + fWidth - 10.0f, g_energygage.pos.y + g_energygage.fHeght - 5.0f, 0.0f);

		// 頂点バッファをアンロックする
		g_pVtxBuffgage->Unlock();
	}
}
//=====================================================
// 酸素ゲージの設定処理
//=====================================================
void SetO2gage(void)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	g_o2gage.nCountTime = 0;
	g_o2gage.fHeght = MAX_TEXTUREH_O2;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffgage->Lock(0, 0, (void**)&pVtx, 0);

	// 酸素ゲージ
	// 頂点座標の設定
	pVtx[0 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
	pVtx[1 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - g_o2gage.fHeght + 5.0f, 0.0f);
	pVtx[2 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);
	pVtx[3 + (4 * GAGETYPE_O2GAGE)].pos = D3DXVECTOR3(g_o2gage.pos.x + g_o2gage.fWidth - 5.0f, g_o2gage.pos.y - 5.0f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffgage->Unlock();

}
