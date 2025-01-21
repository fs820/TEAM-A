//---------------------------------------
//
//�Z�[�u�E���[�h����[file.cpp]
//Author fuma sato
//
//---------------------------------------

#include"file.h"
#include"stage.h"
#include"meshwall.h"
#include"billboard.h"
#include"player.h"

//------------------
//�\�[�g�֐�
//------------------
int *Soat(int* pData)
{
	//�ϐ���錾
	int nRam = 0;

	for (int i = 0; i < MAX_DATA; i++)
	{//��r�Ώ�1
		for (int i2 = i + 1; i2 < MAX_DATA+1; i2++)
		{//��r�Ώ�2
			if (pData[i] < pData[i2])
			{
				//�傫���ق��ɓ���ւ���
				nRam = pData[i];
				pData[i] = pData[i2];
				pData[i2] = nRam;
			}
		}
	}
	return &pData[0];
}
//---------------------------------------
//�Z�[�u����
//---------------------------------------
void SaveFile(int* pData)
{
	FILE* pFile;//�t�@�C���|�C���^��錾

	pFile = fopen(DATA_FILE, "wb");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		fwrite(pData, sizeof(int), MAX_DATA,pFile);//���l����������

		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "�Z�[�u�G���[", "�Z�[�u�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//---------------------------------------
//���[�h����
//---------------------------------------
int *LoadFile(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	static int aData[MAX_DATA] = { 0 };

	for (int i = 0; i < MAX_DATA; i++)
	{
		aData[i] = 0;
	}

	pFile = fopen(DATA_FILE, "rb");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		fread(&aData[0], sizeof(int), MAX_DATA, pFile);//���l����������

		fclose(pFile);//�t�@�C�������
		return &aData[0];
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
		return &aData[0];
	}
}

//---------------------------------------
//���[�h����
//---------------------------------------
void LoadStageManager(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	XFILE Xfile;
	int nCount = 0;

	//X�t�@�C��
	pFile = fopen(MANAGER_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		if (fscanf(pFile, "%d", &Xfile.XfileNum) == EOF)//���l����������
		{
			fclose(pFile);//�t�@�C�������
			return;
		}
		for (nCount = 0; nCount < Xfile.XfileNum; nCount++)
		{
			if (fscanf(pFile, "%63s", Xfile.Pass[nCount].aName) == EOF)break;//���l����������
		}

		//�ݒ�
		SetStageManager(Xfile);

		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//---------------------------------------
//���[�h����
//---------------------------------------
void LoadStage(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	int nCount = 0;
	int nNumber = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//X�t�@�C��
	pFile = fopen(STAGE_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < STAGE_MAX; nCount++)
		{
			if (fscanf(pFile, "%d", &nNumber) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//���l����������

			//�p�x�ϊ�
			rot = D3DXToRadian(rot);
			//�I�u�W�F�N�g�ݒu
			SetStage(nNumber, pos, rot, scale);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//��
	pFile = fopen(WALL_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < MESHWALL_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &rot.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//���l����������

			//�p�x�ϊ�
			rot = D3DXToRadian(rot);
			//�I�u�W�F�N�g�ݒu
			SetMeshWall(pos, rot, scale);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}

	//�r���{�[�h
	pFile = fopen(BILL_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < BILLBOARD_MAX; nCount++)
		{
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.z) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &scale.z) == EOF)break;//���l����������

			//�I�u�W�F�N�g�ݒu
			SetBillboard(pos, scale);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//---------------------------------------
//���[�h����
//---------------------------------------
void SaveStage(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	Stage* pStage = GetStage();
	D3DXVECTOR3 rot;
	int nCount = 0;

	//X�t�@�C��
	pFile = fopen(STAGE_FILE, "w");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < STAGE_MAX; nCount++, pStage++)
		{
			if (pStage->bUse)
			{
				//�p�x�ϊ�
				rot = D3DXToDegree(pStage->rot);

				fprintf(pFile, "%d\n", pStage->nTypeNumber);//���l����������
				fprintf(pFile, "%.1f ", pStage->pos.x);//���l����������
				fprintf(pFile, "%.1f ", pStage->pos.y);//���l����������
				fprintf(pFile, "%.1f\n", pStage->pos.z);//���l����������
				fprintf(pFile, "%.1f ", rot.x);//���l����������
				fprintf(pFile, "%.1f ", rot.y);//���l����������
				fprintf(pFile, "%.1f\n", rot.z);//���l����������
				fprintf(pFile, "%.1f ", pStage->scale.x);//���l����������
				fprintf(pFile, "%.1f ", pStage->scale.y);//���l����������
				fprintf(pFile, "%.1f\n", pStage->scale.z);//���l����������
			}
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}

//----------------------------
//���[�h����
//----------------------------
void LoadPlayer(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	Player* pPlayer = GetPlayer();
	int nCount = 0;
	int ModelNum = 0;
	char name[64] = { "\0" };
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f), scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pFile = fopen(MODEL_FILE, "r");//�t�@�C�����J��
	if (pFile != NULL)
	{//�J������
		//���f����
		if (fscanf(pFile, "%d", &ModelNum) == EOF)
		{
			fclose(pFile);//�t�@�C�������
			return;
		}

		//�t�@�C���p�X�̎擾
		for (nCount = 0; nCount < ModelNum; nCount++)
		{
			if (fscanf(pFile, "%63s", pPlayer->Xname[nCount].aName) == EOF)break;//���l����������
		}

		//�v���C���[���f����
		if (fscanf(pFile, "%d", &pPlayer->nNumModel) == EOF)//���f����
		{
			fclose(pFile);//�t�@�C�������
			return;
		}

		for (nCount = 0; nCount < pPlayer->nNumModel; nCount++)
		{//���f�����J��Ԃ�
			if (fscanf(pFile, "%d", &pPlayer->aModel[nCount].nIdxModelParent) == EOF)break;//�e
			//�I�t�Z�b�g
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

		//���[�V������
		if (fscanf(pFile, "%d", &pPlayer->nNumMotion) == EOF)
		{
			fclose(pFile);//�t�@�C�������
			return;
		}

		for (int nCntMotion = 0; nCntMotion < pPlayer->nNumMotion; nCntMotion++)
		{//���[�V�������J��Ԃ�

			//���[�v�̗L��
			if (fscanf(pFile, "%d", &pPlayer->aMotionInfo[nCntMotion].bLoop) == EOF)break;
			//�L�[��
			if (fscanf(pFile, "%d", &pPlayer->aMotionInfo[nCntMotion].nNumKey) == EOF)break;

			for (int nCntKey = 0; nCntKey < pPlayer->aMotionInfo[nCntMotion].nNumKey; nCntKey++)
			{//�L�[���J��Ԃ�
				//�t���[���̎擾
				if (fscanf(pFile, "%d", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame) == EOF)break;
				for (int nCntModel = 0; nCntModel < pPlayer->nNumModel; nCntModel++)
				{//���f�����J��Ԃ�

					//�L�[���擾
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosX) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosY) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fPosZ) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotX) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotY) == EOF)break;
					if (fscanf(pFile, "%f", &pPlayer->aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].fRotZ) == EOF)break;
				}
			}
		}

		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		HWND hWnd;
		hWnd = GethWnd();
		ReleaseCursor();
		while (ShowCursor(TRUE) < 0);
		MessageBox(hWnd, "���[�h�G���[", "���[�h�ł��Ȃ�������", MB_OK | MB_ICONERROR);
		PostMessage(hWnd, WM_KEYDOWN, VK_ESCAPE, 0);
	}
}