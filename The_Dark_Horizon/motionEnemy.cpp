#include "motionEnemy.h"

// グローバル変数宣言
SET_MOTION_MANAGER g_SetMotiMane;	// モーションカウント情報

//************************************************
// モーションの初期化
//************************************************
void InitMotion(void)
{
	g_SetMotiMane.nCntMotionInfo = 0;
	g_SetMotiMane.nCntKeyInfo = 0;
	g_SetMotiMane.nCntKey = 0;
}

//************************************************
// モーションの初期化
//************************************************
void ReadScript(const char* pFileName,MOTION_ENEMY *pMotionEnemy,ModelEnemy * pModelEnemy, CHARPARAM *pCharparam)
{
	// ファイルポインター宣言、ファイルを開く
	FILE* pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{// ファイルがあったら
		char cDataB[256] = {};	// 保存用文字列
		char cDataC[3];			// 文字列保存用変数
		char cDataA;			// 一文字格納用変数
		int nCntS = 0;			// 保存用文字列カウンター
		int nCntModel = 0;		// モデル数カウンター
		int nResult = 0;		// 結果を保存する変数
		int nNumParts = 0;		// パーツ数
		int nScriptType = SCRIPT_TYPE_SCRIPT;	// スクリプトタイプ
		bool bComment = false;	// コメント機能有無

		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		while (1)
		{// 読み込むために繰り返す-----------------------------------------------------------------------------------
			// 1文字受け取る
			cDataA = fgetc(pFile);

			if (cDataA == EOF)
			{// 最後まで読んだら
				break;
			}
			else if (cDataA == '\n')
			{// 改行文字だったら
				cleareString(256, &cDataB[0]);	// 文字列をきれいにする
				nCntS = 0;						// 保存用文字列カウンターリセット
				bComment = false;				// コメント機能オフ
				continue;
			}
			else if (cDataA == '\t')
			{// タブ文字だったら
				continue;
			}
			else if (cDataA == '#')
			{// コメント文字だったら,コメント機能オン
				bComment = true;
			}
			else if (nResult == EOF)
			{// 読み取りエラーが起きたら,読み込み終了
				break;
			}

			if (bComment)
			{// コメント機能オンだったら
				continue;
			}

			// 読み込んだ文字を文字列に並べる
			cDataB[nCntS] = cDataA;

			// 保存用文字列カウンター追加
			nCntS++;

			// ここから文字列をタイプによって比較していく
			switch (nScriptType)
			{
			case SCRIPT_TYPE_SCRIPT:	// スクリプト読み込み---------------------------------------------------------
				if (strcmp("SCRIPT", &cDataB[0]) == 0)
				{// スクリプト読み込み開始
					cleareString(256, &cDataB[0]);	// 文字列をきれいにする
					nCntS = 0;						// 保存用文字列カウンターリセット
				}
				else 	if (strcmp("END_SCRIPT", &cDataB[0]) == 0)
				{// スクリプト読み込み終了
					cleareString(256, &cDataB[0]);	// 文字列をきれいにする
					nCntS = 0;						// 保存用文字列カウンターリセット
				}
				else 	if (strcmp("NUM_MODEL", &cDataB[0]) == 0)
				{// モデル数の読み込み
					fgets(&cDataC[0], 3, pFile);								// =の部分を読み取る
					nResult = fscanf(pFile, "%d", &pCharparam->nNumModel);	// モデル数代入
					cleareString(256, &cDataB[0]);							// 文字列をきれいにする
					nCntS = 0;												// 保存用文字列カウンターリセット
				}
				else if (strcmp("MODEL_FILENAME", &cDataB[0]) == 0)
				{// モデルファイルの読み込み
					fgets(&cDataC[0], 3, pFile);				// =の部分を読み取る
					nResult = fscanf(pFile, "%s", &cDataB[0]);	// モデルパス代入
					const char* pFileName = &cDataB[0];			// パスの文字列を代入

					pModelEnemy += nCntModel;					// モデル数カウント分ずらす

					// Xファイルの読み込み
					HRESULT hresult;
					hresult = D3DXLoadMeshFromX(pFileName,
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&pModelEnemy->pBuffMat,
						NULL,
						&pModelEnemy->dwNumMat,
						&pModelEnemy->pMesh);

					pModelEnemy -= nCntModel;			// モデル数カウント分戻す
					nCntModel++;						// モデル数カウント
					cleareString(256, &cDataB[0]);		// 文字列をきれいにする
					nCntS = 0;							// 保存用文字列カウンターリセット
				}
				else if (strcmp("CHARACTERSET", &cDataB[0]) == 0)
				{// キャラクター情報の読み込み開始
					nScriptType = SCRIPT_TYPE_CHARCTERSET;	// タイプキャラクターセット
					cleareString(256, &cDataB[0]);			// 文字列をきれいにする
					nCntS = 0;								// 保存用文字列カウンターリセット
				}
				break;

			case SCRIPT_TYPE_CHARCTERSET:	// キャラクターセット読み込み---------------------------------------------
				
				if (strcmp("END_CHARACTERSET", &cDataB[0]) == 0)
				{// キャラクター情報の読み込み
					nScriptType = SCRIPT_TYPE_SCRIPT;	// タイプスクリプト
					pModelEnemy -= nNumParts;			// モデル情報をずらす
					cleareString(256, &cDataB[0]);		// 文字列をきれいにする
					nCntS = 0;							// 保存用文字列カウンターリセット
				}
				else if (strcmp("NUM_PARTS", &cDataB[0]) == 0)
				{// パーツ数の読み込み
					fgets(&cDataC[0], 3, pFile);					// =の部分を読み取る
					nResult = fscanf(pFile, "%d", &nNumParts);		// 高さ代入
					cleareString(256, &cDataB[0]);					// 文字列をきれいにする
					nCntS = 0;										// 保存用文字列カウンターリセット
				}
				else if (strcmp("RADIUS", &cDataB[0]) == 0)
				{// 半径の読み込み
					fgets(&cDataC[0], 3, pFile);							// =の部分を読み取る
					nResult = fscanf(pFile, "%f", &pCharparam->fRadius);	// 半径代入
					cleareString(256, &cDataB[0]);							// 文字列をきれいにする
					nCntS = 0;												// 保存用文字列カウンターリセット
				}
				else if (strcmp("HEIGHT", &cDataB[0]) == 0)
				{// 高さの読み込み
					fgets(&cDataC[0], 3, pFile);							// =の部分を読み取る
					nResult = fscanf(pFile, "%f", &pCharparam->fHeigt);		// 高さ代入
					cleareString(256, &cDataB[0]);							// 文字列をきれいにする
					nCntS = 0;												// 保存用文字列カウンターリセット
				}
				else if (strcmp("PARTSSET", &cDataB[0]) == 0)
				{// パーツセットの読み込み
					cleareString(256, &cDataB[0]);					// 文字列をきれいにする
					nCntS = 0;										// 保存用文字列カウンターリセット
				}
				else if (strcmp("END_PARTSSET", &cDataB[0]) == 0)
				{// パーツセットの読み込み
					pModelEnemy++;						// モデル情報をずらす
					cleareString(256, &cDataB[0]);		// 文字列をきれいにする
					nCntS = 0;							// 保存用文字列カウンターリセット
				}
				else if (strcmp("INDEX", &cDataB[0]) == 0)
				{// パーツのインデックスの読み込み
					fgets(&cDataC[0], 3, pFile);										// =の部分を読み取る
					nResult = fscanf(pFile, "%d", &pModelEnemy->nIdxModelEnemyParent);	// インデックス代入
					cleareString(256, &cDataB[0]);										// 文字列をきれいにする
					nCntS = 0;															// 保存用文字列カウンターリセット
				}
				else if (strcmp("PARENT", &cDataB[0]) == 0)
				{// 親の読み込み
					fgets(&cDataC[0], 3, pFile);										// =の部分を読み取る
					nResult = fscanf(pFile, "%d", &pModelEnemy->nIdxModelEnemyParent);	// 親代入
					cleareString(256, &cDataB[0]);										// 文字列をきれいにする
					nCntS = 0;															// 保存用文字列カウンターリセット
				}
				else if (strcmp("POS", &cDataB[0]) == 0)
				{// 位置の読み込み
					fgets(&cDataC[0], 3, pFile);							// =の部分を読み取る
					nResult = fscanf(pFile, "%f", &pModelEnemy->pos.x);		// 位置代入
					nResult = fscanf(pFile, "%f", &pModelEnemy->pos.y);		// 位置代入
					nResult = fscanf(pFile, "%f", &pModelEnemy->pos.z);		// 位置代入
					cleareString(256, &cDataB[0]);							// 文字列をきれいにする
					nCntS = 0;												// 保存用文字列カウンターリセット
				}
				else if (strcmp("ROT", &cDataB[0]) == 0)
				{// 向きの読み込み
					fgets(&cDataC[0], 3, pFile);							// =の部分を読み取る
					nResult = fscanf(pFile, "%f", &pModelEnemy->pos.x);		// 向き代入
					nResult = fscanf(pFile, "%f", &pModelEnemy->pos.y);		// 向き代入
					nResult = fscanf(pFile, "%f", &pModelEnemy->pos.z);		// 向き代入
					cleareString(256, &cDataB[0]);							// 文字列をきれいにする
					nCntS = 0;												// 保存用文字列カウンターリセット
				}
				break;
			}

			if (nCntS >= 256)
			{// 保存する文字列が上限を超えないようにする
				nCntS = 0;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}

//*********************************************************************************************
// 文字列をきれいにする関数
//*********************************************************************************************
void cleareString(int nCntChar, char* cData)
{
	for (int nCnt = 0; nCnt < nCntChar; nCnt++, cData++)
	{// 文字列の中身をきれいにする
		*cData = 0;
	}
}

////************************************************
//// モーションテキストの読み込み	SCRIPT
////************************************************
//void ReadMotionText(const char* pFileName, ModelEnemy* pModel, MOTION_ENEMY* motion, CHARPARAM* charParam)
//{
//	char astrA[256] = {};		// 文字列格納用変数
//	char astrB[256] = {};	// 古い格納用変数
//	char* aResult = 0;
//	int nResult = 0;
//	int nCnt = 0;
//	// ファイルを開く
//	FILE* pFile = fopen(pFileName, "r");
//
//	if (pFile == NULL)
//	{
//		return;
//	}
//
//	while (1)
//	{	
//		// 一文字読み取る
//		aResult = fgets(&astrA[0],2, pFile);
//		
//		// 一文字ずつ代入
//		astrB[nCnt] = astrA[0];
//
//		// カウントを進める,上限超えたらゼロ
//		nCnt = (nCnt + 1) % 256;
//		
//		if (strcmp(&astrA[0], "#") == 0)
//		{// コメント文字を読んだらそのあとの文字は読み飛ばす
//			ReadComment(pFile, aResult);	// コメントを読み飛ばす
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\n") == 0)
//		{// 改行よんだら
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\t") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "SCRIPT") == 0)
//		{// SCRIPT読み取り
//			ReadScript(pFile,pModel,motion,charParam);	// スクリプトの読み込みに以降
//		}
//
//		if (aResult == NULL)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//		else if (nResult == EOF)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//	}
//
//	// ファイルを閉じる
//	fclose(pFile);
//}

////************************************************
//// スクリプトの読み取り
////************************************************
//void ReadScript(FILE* pFile, Model* pModel, MOTION* motion, CHARPARAM* charParam)
//{
//	char astrA[256] = {};		// 文字列格納用変数
//	char astrB[256] = {};	// 古い格納用変数
//	char *aResult = 0;
//	int nResult = 0;
//	int nCnt = 0;
//	int nCntModel = 0;
//
//	while (1)
//	{
//		// 一文字読み取る
//		aResult = fgets(&astrA[0], 2, pFile);
//
//		// 一文字ずつ代入
//		astrB[nCnt] = astrA[0];
//
//		// カウントを進める,上限超えたらゼロ
//		nCnt = (nCnt + 1) % 256;
//
//		if (strcmp(&astrA[0], "#") == 0)
//		{// コメント文字を読んだらそのあとの文字は読み飛ばす
//			ReadComment(pFile, aResult);	// コメントを読み飛ばす
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\n") == 0)
//		{// 改行よんだら
//			
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\t") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "NUM_MODEL") == 0)
//		{// モデル数の読み込み
//			fgets(&astrA[0],3,pFile);								// =読み込み
//			nResult = fscanf(pFile, "%d", &charParam->nNumModel);	// モデル数に代入
//			StringClear(&astrB[0], 256);							// 保存用文字列のクリア
//			nCnt = 0;												// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "MODEL_FILENAME") == 0)
//		{// MODEL_FILENAME読み取り
//			fgets(&astrA[0], 3, pFile);					// =読み込み
//			nResult = fscanf(pFile, "%s", &astrA[0]);	// ファイルパス読み込み
//			//SetModel(&astrA[0],pModel,nCntModel);		// Xフィルのパスの読み込み
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//			nCntModel++;								// モデルカウントを進める
//		}
//		else if (strcmp(&astrB[0], "CHARACTERSET") == 0)
//		{// CHARACTERSET読み取り
//			ReadCharacterSet(pFile, pModel, motion, charParam);
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "MOTIONSET") == 0)
//		{// MOTIONSET読み取り
//			MostionSet(pFile, motion);		// モーションセットへ以降
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "END_SCRIPT") == 0)
//		{// END_SCRIPT読み取り
//			break;
//		}
//
//		if (aResult == NULL)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//		else if (nResult == EOF)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//	}
//
//	// カウントしている変数を初期化
//	g_SetMotiMane.nCntMotionInfo = 0;
//	g_SetMotiMane.nCntKeyInfo = 0;
//	g_SetMotiMane.nCntKey = 0;
//}
//
////************************************************
//// キャラクターセットの読み込み
////************************************************
//void ReadCharacterSet(FILE* pFile, Model* pModel, MOTION* motion, CHARPARAM* charParam)
//{
//	char astrA[256] = {};	// 文字列格納用変数
//	char astrB[256] = {};	// 古い格納用変数
//	char* aResult = 0;
//	int nResult = 0;
//	int nCnt = 0;
//
//	while (1)
//	{
//		// 一文字読み取る
//		aResult = fgets(&astrA[0], 2, pFile);
//
//		// 一文字ずつ代入
//		astrB[nCnt] = astrA[0];
//
//		// カウントを進める,上限超えたらゼロ
//		nCnt = (nCnt + 1) % 256;
//
//		if (strcmp(&astrA[0], "#") == 0)
//		{// コメント文字を読んだらそのあとの文字は読み飛ばす
//			ReadComment(pFile, aResult);	// コメントを読み飛ばす
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\n") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\t") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "NUM_PARTS") == 0)
//		{// パーツ数の読み込み
//			fgets(&astrA[0], 3, pFile);					// =読み込み
//			nResult = fscanf(pFile, "%d", &charParam->nNumModel);	// モデル数に代入
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "RADIUS") == 0)
//		{// モデル数の読み込み
//			fgets(&astrA[0], 3, pFile);							// =読み込み
//			nResult = fscanf(pFile, "%f", &charParam->fWidth);	// モデル数に代入
//			StringClear(&astrB[0], 256);						// 保存用文字列のクリア
//			nCnt = 0;											// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "HEIGHT") == 0)
//		{// モデル数の読み込み
//			fgets(&astrA[0], 3, pFile);							// =読み込み
//			nResult = fscanf(pFile, "%f", &charParam->fHeigt);	// モデル数に代入
//			StringClear(&astrB[0], 256);						// 保存用文字列のクリア
//			nCnt = 0;											// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "PARTSSET") == 0)
//		{// パーツを設定
//			//PartsSet(pFile,pModel);
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "END_CHARACTERSET") == 0)
//		{// パーツを設定
//			break;
//		}
//
//		if (aResult == NULL)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//		else if (nResult == EOF)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//	}
//}
//
////************************************************
//// モーションセット
////************************************************
//void MostionSet(FILE* pFile, MOTION* motion)
//{
//	char astrA[256] = {};	// 文字列格納用変数
//	char astrB[256] = {};	// 古い格納用変数
//	char* aResult = 0;
//	int nResult = 0;
//	int nCnt = 0;
//
//	MOTION_INFO setMotInfo;
//	setMotInfo.bLoop = false;
//	setMotInfo.nNumKey = 0;
//
//	while (1)
//	{
//		// 一文字読み取る
//		aResult = fgets(&astrA[0], 2, pFile);
//
//		// 一文字ずつ代入
//		astrB[nCnt] = astrA[0];
//
//		// カウントを進める,上限超えたらゼロ
//		nCnt = (nCnt + 1) % 256;
//
//		if (strcmp(&astrA[0], "#") == 0)
//		{// コメント文字を読んだらそのあとの文字は読み飛ばす
//			ReadComment(pFile, aResult);	// コメントを読み飛ばす
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\n") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\t") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "LOOP") == 0)
//		{// ループ情報の読み込み
//			int nFlag = 0;
//			fgets(&astrA[0], 3, pFile);					// =読み込み
//			nResult = fscanf(pFile, "%d", &nFlag);		// モデル数に代入
//
//			if (nFlag > 0)
//			{// ゼロより上だったらトゥルー
//				setMotInfo.bLoop = true;
//			}
//
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "NUM_KEY") == 0)
//		{// キー総数の読み込み
//			fgets(&astrA[0], 3, pFile);					// =読み込み
//			nResult = fscanf(pFile, "%d", &setMotInfo.nNumKey);		// モデル数に代入
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;
//		}
//		else if (strcmp(&astrB[0], "KEYSET") == 0)
//		{// キーセットの読み込み
//			KeySet(pFile, motion);	// キーセット開始
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;
//		}
//		else if (strcmp(&astrB[0], "END_MOTIONSET") == 0)
//		{// モーションセット終わり
//			MostionSet(motion,setMotInfo);	// 取得した情報を全部ぶち込む
//			g_SetMotiMane.nCntMotionInfo++;	// キーセット番号追加
//
//			g_SetMotiMane.nCntKeyInfo = 0;	// キー情報カウントリセット
//			break;
//		}
//
//		if (aResult == NULL)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//		else if (nResult == EOF)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//	}
//}
//
////************************************************
//// モーション終わりー
////************************************************
//void MostionSet(MOTION* motion, MOTION_INFO setMotInfo)
//{
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].bLoop = setMotInfo.bLoop;
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].nNumKey = setMotInfo.nNumKey;
//}
//
////************************************************
//// キーセットの設定
////************************************************
//void KeySet(FILE* pFile, MOTION* motion)
//{
//	char astrA[256] = {};	// 文字列格納用変数
//	char astrB[256] = {};	// 古い格納用変数
//	char* aResult = 0;
//	int nResult = 0;
//	int nCnt = 0;
//
//	KEY_INFO keyInfo;
//	keyInfo.nFrame = 1;
//
//	while (1)
//	{
//		// 一文字読み取る
//		aResult = fgets(&astrA[0], 2, pFile);
//
//		// 一文字ずつ代入
//		astrB[nCnt] = astrA[0];
//
//		// カウントを進める,上限超えたらゼロ
//		nCnt = (nCnt + 1) % 256;
//
//		if (strcmp(&astrA[0], "#") == 0)
//		{// コメント文字を読んだらそのあとの文字は読み飛ばす
//			ReadComment(pFile, aResult);	// コメントを読み飛ばす
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\n") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\t") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "FRAME") == 0)
//		{// フレーム数の読み込み
//			fgets(&astrA[0], 3, pFile);					// =読み込み
//			nResult = fscanf(pFile, "%d", &keyInfo.nFrame);	// モデル数に代入
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "KEY") == 0)
//		{// キーの読み込み
//			Key(pFile, motion);
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "END_KEYSET") == 0)
//		{// キーの読み込み
//			EndKeySet(motion,keyInfo);		// 取得した情報をすべてぶち込む
//			g_SetMotiMane.nCntKeyInfo++;	// キーを一つ進める
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;
//
//			g_SetMotiMane.nCntKey = 0;		// キーカウント数リセット
//			break;
//		}
//
//		if (aResult == NULL)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//		else if (nResult == EOF)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//	}
//}
//
////************************************************
//// キーセット終わりー
////************************************************
//void EndKeySet(MOTION* motion, KEY_INFO keyInfo)
//{
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].nFrame = keyInfo.nFrame;
//}
//
////************************************************
//// キーを設定
////************************************************
//void Key(FILE* pFile, MOTION* motion)
//{
//	char astrA[256] = {};	// 文字列格納用変数
//	char astrB[256] = {};	// 古い格納用変数
//	char* aResult = 0;
//	int nResult = 0;
//	int nCnt = 0;
//
//	KEY key;
//	key.fPosX = 0.0f;
//	key.fPosY = 0.0f;
//	key.fPosZ = 0.0f;
//	key.fRotX = 0.0f;
//	key.fRotY = 0.0f;
//	key.fRotZ = 0.0f;
//
//	while (1)
//	{
//		// 一文字読み取る
//		aResult = fgets(&astrA[0], 2, pFile);
//
//		// 一文字ずつ代入
//		astrB[nCnt] = astrA[0];
//
//		// カウントを進める,上限超えたらゼロ
//		nCnt = (nCnt + 1) % 256;
//
//		if (strcmp(&astrA[0], "#") == 0)
//		{// コメント文字を読んだらそのあとの文字は読み飛ばす
//			ReadComment(pFile, aResult);	// コメントを読み飛ばす
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\n") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrA[0], "\t") == 0)
//		{// 改行よんだら
//
//			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
//			nCnt = 0;						// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "POS") == 0)
//		{// POSの読み込み
//			fgets(&astrA[0], 3, pFile);					// =読み込み
//			nResult = fscanf(pFile, "%f", &key.fPosX);	// 位置X
//			nResult = fscanf(pFile, "%f", &key.fPosY);	// 位置Y
//			nResult = fscanf(pFile, "%f", &key.fPosZ);	// 位置Z
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "ROT") == 0)
//		{// ROTの読み込み
//			fgets(&astrA[0], 3, pFile);					// =読み込み
//			nResult = fscanf(pFile, "%f", &key.fRotX);	// 向きX
//			nResult = fscanf(pFile, "%f", &key.fRotY);	// 向きY
//			nResult = fscanf(pFile, "%f", &key.fRotZ);	// 向きZ
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;									// 保存用文字列のカウントゼロ
//		}
//		else if (strcmp(&astrB[0], "END_KEY") == 0)
//		{// キー読み込みおーわり
//			EndKey(motion,key);			// 取得した情報をすべてぶち込む
//			g_SetMotiMane.nCntKey++;	// キーセット番目追加
//			StringClear(&astrB[0], 256);				// 保存用文字列のクリア
//			nCnt = 0;
//			break;
//		}
//
//		if (aResult == NULL)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//		else if (nResult == EOF)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//	}
//}
//
////************************************************
//// キーの終わりー
////************************************************
//void EndKey(MOTION* motion, KEY key)
//{
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fPosX = key.fPosX;
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fPosY = key.fPosY;
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fPosZ = key.fPosZ;
//
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fRotX = key.fRotX;
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fRotY = key.fRotY;
//	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fRotZ = key.fRotZ;
//}
//
////************************************************
//// 文字列のクリア
////************************************************
//void StringClear(char* astr,int nMaxCunt)
//{
//	for (int nCntB = 0; nCntB < nMaxCunt; nCntB++)
//	{// 保存している文字列をすべてクリア
//		if (astr[nCntB] == '\0')
//		{
//			break;
//		}
//
//		astr[nCntB] = '\0';
//	}
//}
//
////************************************************
//// コメント
////************************************************
//void ReadComment(FILE *pFile,char*aResult)
//{
//	char astr[2];
//
//	while (1)
//	{
//		// 一文字ずつ読む
//		fgets(&astr[0], 2, pFile);
//
//		if (*aResult = strcmp(&astr[0], "\n") == 0)
//		{// 改行文字読んだら
//			break;
//		}
//
//		if (*aResult == EOF)
//		{// テキストファイル全部読み切っちゃった
//			break;
//		}
//	}
//}
//
////************************************************
//// モーションの更新
////************************************************
//bool UpdateMotion(MOTION* motion,Model* model, int nType, int nNumModel)
//{
//	bool bMotionEnd = false;
//
//	if (motion->nNowMotiType != nType)
//	{// 違うモーションに切り替わっていたら
//		motion->nNowMotiType = nType;							// タイプを変える
//		motion->nCounterMotion = 0;								// フレームカウンターをゼロ
//		motion->nNumKey = motion->aMotionInfo[nType].nNumKey;	// キーの最大数を代入
//		motion->nKey = 0;										// 今数えているキーを初期化
//		bMotionEnd = true;										// モーションは終わったことにする
//
//		if (motion->aMotionInfo[nType].nNumKey > 1)
//		{// 一キー以上あるなら
//			motion->nNextKey = motion->nKey + 1;
//		}
//		else
//		{// ないならば
//			motion->nNextKey = motion->nKey;
//		}
//	}
//
//	motion->nCounterMotion++;	// フレーム数カウント
//
//	if (motion->nNextKey < motion->nNumKey)
//	{// モーションの全体キーより値が低い場合
//		// 全モデルパーツの更新
//		for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++, model++)
//		{
//			KEY diffKeyPos;
//			KEY Hope;
//
//			diffKeyPos.fPosX = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fPosX - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fPosX);
//			diffKeyPos.fPosY = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fPosY - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fPosY);
//			diffKeyPos.fPosZ = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fPosZ - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fPosZ);
//
//			diffKeyPos.fRotX = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fRotX - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotX);
//			diffKeyPos.fRotY = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fRotY - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotY);
//			diffKeyPos.fRotZ = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fRotZ - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotZ);
//
//			Hope.fPosX = diffKeyPos.fPosX / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame;
//			Hope.fPosY = diffKeyPos.fPosY / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame;
//			Hope.fPosZ = diffKeyPos.fPosZ / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame;
//
//			Hope.fRotX = motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotX + diffKeyPos.fRotX * ((float)motion->nCounterMotion / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame);
//			Hope.fRotY = motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotY + diffKeyPos.fRotY * ((float)motion->nCounterMotion / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame);
//			Hope.fRotZ = motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotZ + diffKeyPos.fRotZ * ((float)motion->nCounterMotion / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame);
//
//			//model->pos = model->offSet + D3DXVECTOR3(Hope.fPosX, Hope.fPosY, Hope.fPosZ);
//			model->rot = D3DXVECTOR3(Hope.fRotX, Hope.fRotY, Hope.fRotZ);
//
//			if (model->nIdxModelParent == -1)
//			{// プレイヤーのポスが結びついてるやつがいたら
//				model->rot.y += D3DX_PI;
//			}
//		}
//
//
//		if (motion->nCounterMotion >= motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame)
//		{// フレーム全部数え終わったら
//			motion->nCounterMotion = 0;	// フレーム数カウントゼロ
//
//			if (motion->nNextKey - motion->nKey > 0)
//			{// ループの間のキーじゃない
//				motion->nNextKey++;	// 次のキーへカウント
//				motion->nKey++;		// 次のキーへカウント
//				bMotionEnd = true;	// モーション終わったよ
//
//				if (motion->nKey >= motion->aMotionInfo[nType].nNumKey - 1)
//				{// キーの総数以上になったら
//					if (motion->aMotionInfo[nType].bLoop)
//					{// ループするのだったら
//						motion->nNextKey = 0;	// 次のキーを最初のキーにする
//					}
//					else
//					{
//						motion->nNextKey = motion->nNumKey;	// 計算の条件式に入らないようにする
//					}
//				}
//			}
//			else
//			{// ループの間の値だったら
//				motion->nKey = 0;				// キー０
//				motion->nNextKey = motion->nKey + 1;	// 次のキーの値に設定
//			}
//		}
//	}
//
//	return bMotionEnd;
//}