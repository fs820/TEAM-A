//======================================================
//
// アイテムの処理
// Aouther:Takahashi misaki
// 
//======================================================
#include "item.h"

// マクロ定義
#define MAX_TEXTUREW_ITEM (80.0f)	// テクスチャの横幅
#define MAX_TEXTUREH_ITEM (80.0f)	// テクスチャの縦幅
#define MAX_TEXTUREW (10.0f)		// テクスチャ同士の横幅
#define MAX_ITEM (3)
// グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureitem[ITEMTYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffitem = NULL;			// 頂点バッファへのポインタ
Item g_Item[MAX_ITEM];									// アイテムの構造体

//=====================================================
// アイテムの初期化設定
//=====================================================
void Inititem(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // デバイスへのポインタ
	int nNumber = 0;

	// アイテムの構造体
	for (int nCount = 0; nCount < MAX_ITEM; nCount++)
	{
		g_Item[nCount].TXpos = D3DXVECTOR3(1000.0f + (MAX_TEXTUREW_ITEM * nCount) + (MAX_TEXTUREW * nCount), 10.0f, 0.0f);	// 位置を初期化する
		g_Item[nCount].TXcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色を初期化する 
	}

	// デバイスの取得
	pDevice = GetDevice();

	for (int nCount = 0; nCount < ITEMTYPE_MAX; nCount++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCount],
			&g_pTextureitem[nCount]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ITEMTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffitem,
		NULL);

	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffitem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < ITEMTYPE_MAX; nCount++)
	{
		// アイテムフレーム
		// 頂点座標の設定
		pVtx[0 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x , g_Item[nNumber].TXpos.y, 0.0f);
		pVtx[1 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + MAX_TEXTUREW_ITEM, g_Item[nNumber].TXpos.y, 0.0f);
		pVtx[2 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x , g_Item[nNumber].TXpos.y + MAX_TEXTUREH_ITEM, 0.0f);
		pVtx[3 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + MAX_TEXTUREW_ITEM, g_Item[nNumber].TXpos.y + MAX_TEXTUREH_ITEM, 0.0f);

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

		nCount++;

		// アイテムアイコン
		// 頂点座標の設定
		pVtx[0 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + 5.0f, g_Item[nNumber].TXpos.y + 5.0f, 0.0f);
		pVtx[1 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + MAX_TEXTUREW_ITEM - 5.0f, g_Item[nNumber].TXpos.y + 5.0f, 0.0f);
		pVtx[2 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + 5.0f, g_Item[nNumber].TXpos.y + MAX_TEXTUREH_ITEM - 5.0f, 0.0f);
		pVtx[3 + (4 * nCount)].pos = D3DXVECTOR3(g_Item[nNumber].TXpos.x + MAX_TEXTUREW_ITEM - 5.0f, g_Item[nNumber].TXpos.y + MAX_TEXTUREH_ITEM - 5.0f, 0.0f);

		// rhwの設定
		pVtx[0 + (4 * nCount)].rhw = 1.0f;
		pVtx[1 + (4 * nCount)].rhw = 1.0f;
		pVtx[2 + (4 * nCount)].rhw = 1.0f;
		pVtx[3 + (4 * nCount)].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0 + (4 * nCount)].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[1 + (4 * nCount)].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[2 + (4 * nCount)].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		pVtx[3 + (4 * nCount)].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);

		if (nCount % 2 == 1)
		{
			nNumber++;
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffitem->Unlock();
}
//=====================================================
// 背景の終了処理
//=====================================================
void Uninititem(void)
{
	for (int nCount = 0; nCount < ITEMTYPE_MAX; nCount++)
	{
		// テクスチャの破棄
		if (g_pTextureitem[nCount] != NULL)
		{
			g_pTextureitem[nCount]->Release();
			g_pTextureitem[nCount] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffitem != NULL)
	{
		g_pVtxBuffitem->Release();
		g_pVtxBuffitem = NULL;
	}
}
//=====================================================
// アイテムの更新処理
//=====================================================
void Updateitem(void)
{

}
//=====================================================
// アイテムの描画処理
//=====================================================
void Drawitem(void)
{
	LPDIRECT3DDEVICE9 pDevice;  // デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffitem, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < ITEMTYPE_MAX; nCount++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureitem[nCount]);
		// アイテムの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
	}
}
//=====================================================
// アイテムの設定処理
//=====================================================
void Setitem(int nIdxItem)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffitem->Lock(0, 0, (void**)&pVtx, 0);

	g_Item[nIdxItem].TXcol= D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	// アイテムを所持しているとき
	// 頂点カラーの設定
	switch (nIdxItem)
	{
	case 0:
		pVtx[0 + (4 * ITEMTYPE_ITEM0)].col = g_Item[nIdxItem].TXcol;
		pVtx[1 + (4 * ITEMTYPE_ITEM0)].col = g_Item[nIdxItem].TXcol;
		pVtx[2 + (4 * ITEMTYPE_ITEM0)].col = g_Item[nIdxItem].TXcol;
		pVtx[3 + (4 * ITEMTYPE_ITEM0)].col = g_Item[nIdxItem].TXcol;
		break;

	case 1:
		pVtx[0 + (4 * ITEMTYPE_ITEM1)].col = g_Item[nIdxItem].TXcol;
		pVtx[1 + (4 * ITEMTYPE_ITEM1)].col = g_Item[nIdxItem].TXcol;
		pVtx[2 + (4 * ITEMTYPE_ITEM1)].col = g_Item[nIdxItem].TXcol;
		pVtx[3 + (4 * ITEMTYPE_ITEM1)].col = g_Item[nIdxItem].TXcol;
		break;

	case 2:
		pVtx[0 + (4 * ITEMTYPE_ITEM2)].col = g_Item[nIdxItem].TXcol;
		pVtx[1 + (4 * ITEMTYPE_ITEM2)].col = g_Item[nIdxItem].TXcol;
		pVtx[2 + (4 * ITEMTYPE_ITEM2)].col = g_Item[nIdxItem].TXcol;
		pVtx[3 + (4 * ITEMTYPE_ITEM2)].col = g_Item[nIdxItem].TXcol;
		break;
	}
	
	// 頂点バッファをアンロックする
	g_pVtxBuffitem->Unlock();

}