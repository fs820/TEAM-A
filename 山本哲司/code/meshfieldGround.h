#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"

// ���b�V���t�B�[���h�̎��
typedef enum
{
	MESHFIELD_TYPE_NOMAL = 0,
	MESHFIELD_TYPE_MAX
}MESHFIELD_TYPE;

#define MESHFIELD_WIDTH (5000)		// ���b�V���t�B�[���h�̍���
#define MESHFIELD_DEPTH (5000)		// ���b�V���t�B�[���h�̉��s
#define MESHFIELD_DIVISION_X (40)																						// ��
#define MESHFIELD_DIVISION_Z (40)																						// �c
#define MESHFIELD_PLYGON_HID (4 * (MESHFIELD_DIVISION_Z - 1))															// �k�ރ|���S��
#define MESHFIELD_PLYGON_APP ((MESHFIELD_DIVISION_X * MESHFIELD_DIVISION_Z) * 2)										// ������|���S��
#define MESHFIELD_PLYGON_AII (((MESHFIELD_DIVISION_X * MESHFIELD_DIVISION_Z) * 2) + (4 * (MESHFIELD_DIVISION_Z - 1)))	// ���v�|���S��
#define MESHFIELD_VERTEX ((MESHFIELD_DIVISION_X + 1) * (MESHFIELD_DIVISION_Z + 1))										// ���_��
#define MESHFIELD_INDEX (MESHFIELD_PLYGON_AII + 2)																		// �C���f�b�N�X��

// ���b�V���t�B�[���h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;							// �ʒu
	D3DXVECTOR3 rot;							// ����
	D3DXVECTOR3 aNor[MESHFIELD_PLYGON_AII];		// �|���S���̖@��
	D3DXMATRIX mtxWorld;						// ���[���h�}�g���b�N�X
	int nType;									// �^�C�v
	bool bUse;									// �g�p���Ă��邩�ǂ���
}MESHFIELD;

//�v���g�^�C�v�錾
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
bool CollisionMeshField(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove);
void VertexMoveMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius);
void ResetNorVectolMeshField();
void SaveInfoMeshField();
void LoadInfoMeshField();
#endif // !_POLYGON_H_
