//---------------------------------------
//
//セーブ・ロード処理[file.cpp]
//Author fuma sato
//
//---------------------------------------

#include"file.h"
#include"stage.h"
#include"meshwall.h"
#include"billboard.h"
#include"player.h"

//------------------
//ソート関数
//------------------
int *Soat(int* pData)
{
	//変数を宣言
	int nRam = 0;

	for (int i = 0; i < MAX_DATA; i++)
	{//比較対象1
		for (int i2 = i + 1; i2 < MAX_DATA+1; i2++)
		{//比較対象2
			if (pData[i] < pData[i2])
			{
				//大きいほうに入れ替える
				nRam = pData[i];
				pData[i] = pData[i2];
				pData[i2] = nRam;
			}
		}
	}
	return &pData[0];
}
//---------------------------------------
//セーブ処理
//---------------------------------------
void SaveFile(int* pData)
{
	FILE* pFile;//ファイルポインタを宣言

	pFile = fopen(DATA_FILE, "wb");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		fwrite(pData, sizeof(int), MAX_DATA,pFile);//数値を書き入れ

		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "セーブエラー", "セーブできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//---------------------------------------
//ロード処理
//---------------------------------------
int *LoadFile(void)
{
	FILE* pFile;//ファイルポインタを宣言
	static int aData[MAX_DATA] = { 0 };

	for (int i = 0; i < MAX_DATA; i++)
	{
		aData[i] = 0;
	}

	pFile = fopen(DATA_FILE, "rb");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		fread(&aData[0], sizeof(int), MAX_DATA, pFile);//数値を書き入れ

		fclose(pFile);//ファイルを閉じる
		return &aData[0];
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
		return &aData[0];
	}
}

//---------------------------------------
//ロード処理
//---------------------------------------
void LoadStageManager(void)
{
	FILE* pFile;//ファイルポインタを宣言
	XFILE Xfile;
	int nCount = 0;

	//Xファイル
	pFile = fopen(MANAGER_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		if (fscanf(pFile, "%d", &Xfile.XfileNum) == EOF)//数値を書き入れ
		{
			fclose(pFile);//ファイルを閉じる
			return;
		}
		for (nCount = 0; nCount < Xfile.XfileNum; nCount++)
		{
			if (fscanf(pFile, "%63s", Xfile.Pass[nCount].aName) == EOF)break;//数値を書き入れ
		}

		//設定
		SetStageManager(Xfile);

		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//---------------------------------------
//ロード処理
//---------------------------------------
void LoadStage(void)
{
	FILE* pFile;//ファイルポインタを宣言
	int nCount = 0;
	int nNumber = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイル
	pFile = fopen(STAGE_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < STAGE_MAX; nCount++)
		{
			if (fscanf(pFile, "%d", &nNumber) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//数値を書き入れ

			//角度変換
			rot = D3DXToRadian(rot);
			//オブジェクト設置
			SetStage(nNumber, pos, rot, scale);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//壁
	pFile = fopen(WALL_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < MESHWALL_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//数値を書き入れ

			//角度変換
			rot = D3DXToRadian(rot);
			//オブジェクト設置
			SetMeshWall(pos, rot, scale);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//ビルボード
	pFile = fopen(BILL_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < BILLBOARD_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//数値を書き入れ

			//オブジェクト設置
			SetBillboard(pos, scale);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//---------------------------------------
//ロード処理
//---------------------------------------
void SaveStage(void)
{
	FILE* pFile;//ファイルポインタを宣言
	Stage* pStage = GetStage();
	D3DXVECTOR3 rot;
	int nCount = 0;

	//Xファイル
	pFile = fopen(STAGE_FILE, "w");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < STAGE_MAX; nCount++, pStage++)
		{
			if (pStage->bUse)
			{
				//角度変換
				rot = D3DXToDegree(pStage->rot);

				fprintf(pFile, "%d\n", pStage->nTypeNumber);//数値を書き入れ
				fprintf(pFile, "%.1f ", pStage->pos.x);//数値を書き入れ
				fprintf(pFile, "%.1f ", pStage->pos.y);//数値を書き入れ
				fprintf(pFile, "%.1f\n", pStage->pos.z);//数値を書き入れ
				fprintf(pFile, "%.1f ", rot.x);//数値を書き入れ
				fprintf(pFile, "%.1f ", rot.y);//数値を書き入れ
				fprintf(pFile, "%.1f\n", rot.z);//数値を書き入れ
				fprintf(pFile, "%.1f ", pStage->scale.x);//数値を書き入れ
				fprintf(pFile, "%.1f ", pStage->scale.y);//数値を書き入れ
				fprintf(pFile, "%.1f\n", pStage->scale.z);//数値を書き入れ
			}
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//----------------------------
//ロード処理
//----------------------------
void LoadPlayer(void)
{
	FILE* pFile;//ファイルポインタを宣言
	Player* pPlayer = GetPlayer();
	int nCount = 0;
	int ModelNum = 0;
	char name[64] = { "\0" };
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pFile = fopen(MODEL_FILE, "r");//ファイルを開く
	if (pFile != NULL)
	{//開けたら
		//モデル数
		if (fscanf(pFile, "%d", &ModelNum) == EOF)
		{
			fclose(pFile);//ファイルを閉じる
			return;
		}

		//ファイルパスの取得
		for (nCount = 0; nCount < ModelNum; nCount++)
		{
			if (fscanf(pFile, "%63s", pPlayer->Xname[nCount].aName) == EOF)break;//数値を書き入れ
		}

		//プレイヤーモデル数
		if (fscanf(pFile, "%d", &pPlayer->nNumModel) == EOF)//モデル数
		{
			fclose(pFile);//ファイルを閉じる
			return;
		}

		for (nCount = 0; nCount < pPlayer->nNumModel; nCount++)
		{//モデル数繰り返す
			if (fscanf(pFile, "%d", &pPlayer->aModel[nCount].nIdxModelParent) == EOF)break;//親
			//オフセット
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].pos.x) == EOF)break;
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].pos.y) == EOF)break;
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].pos.z) == EOF)break;
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].rot.x) == EOF)break;
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].rot.y) == EOF)break;
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].rot.z) == EOF)break;
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].scale.x) == EOF)break;
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].scale.y) == EOF)break;
			if (fscanf(pFile, "%f", &pPlayer->aModel[nCount].scale.z) == EOF)break;
		}

		//モーション数
		if (fscanf(pFile, "%d", &pPlayer->nNumMotion) == EOF)
		{
			fclose(pFile);//ファイルを閉じる
			return;
		}

		for (int nCntMotion = 0; nCntMotion < pPlayer->nNumMotion; nCntMotion++)
		{//モーション数繰り返す

			//ループの有無
			if (fscanf(pFile, "%d", &pPlayer->aMotionInfo[nCntMotion].bLoop) == EOF)break;
			//キー数
			if (fscanf(pFile, "%d", &pPlayer->aMotionInfo[nCntMotion].nNumKey) == EOF)break;

			for (int nCntKey = 0; nCntKey < pPlayer->aMotionInfo[nCntMotion].nNumKey; nCntKey++)
			{//キー数繰り返す
				//フレームの取得
				if (fscanf(pFile, "%d", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame) == EOF)break;
				for (int nCntModel = 0; nCntModel < pPlayer->nNumModel; nCntModel++)
				{//モデル数繰り返す

					//キー情報取得
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosX) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosY) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosZ) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotX) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotY) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotZ) == EOF)break;
				}
			}
		}

		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "ロードエラー", "ロードできなかったよ", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}