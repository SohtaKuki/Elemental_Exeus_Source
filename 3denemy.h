//=================================================
//
// 3D���f���̃v���C���[�̕\������ (3denemy.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _3DENEMY_H_
#define _3DENEMY_H_

#include "object3D.h"
#include "objectX.h"

#define MAX_CHAR (256) //�s�̓ǂݍ��ސ�
#define ENEMY_MODEL (8) //���f���̐�
#define MAX_KEYSET (20) // �L�[�̍ő�l
#define MAX_MOTION (10) //���[�V����

//�I�u�W�F�N�g3D�N���X
class C3denemy : public CModel
{
public:

	typedef enum
	{
		MOTION_NORMAL = 0,
		MOTION_ACTION,
		MOTION_MAX
	}ENEMYMOTION;


	typedef struct
	{
		char filename[MAX_CHAR];
		int index;
		int parent;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;

	}LoadEnemy;

	//�L�[�̍\����
	typedef struct {
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}Key;

	//�L�[�Z�b�g�̍\����
	typedef struct {
		int Frame;
		Key aKey[ENEMY_MODEL];
	}KeySet;

	//���[�V�����̍\����
	typedef struct {
		bool Loop;
		int NumKey;
		KeySet KeySet[MAX_KEYSET];
	}MotionSet;

	//���f���̍\����
	typedef struct
	{

		D3DXMATRIX mtxworld;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DXVECTOR3 targetPos;
		D3DXVECTOR3 targetRot;
		LPDIRECT3DTEXTURE9 m_pTexture;
		int nLife;
		bool bUse;
		int nCounterState;
		int nIdxModelParent;	//�e���f���̃C���f�b�N�X

	}ModelPartsEnemy;

	C3denemy(int nPriority = 3);
	~C3denemy() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void ModelMotion();
	//void SetPlayerPos();
	static C3denemy* Create(D3DXVECTOR3 pos,int MoveType);
	//void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static HRESULT Load();
	static void Unload();
	void LoadPlayerData();
	void EnemyDamage(int nDamage);
	//void OldPlayerPos() { m_nPos = m_nOld3DPlayerPos; }
	//void OldPlayerPosZ() { m_nPos.z = m_nOld3DPlayerPos.z; }
	D3DXVECTOR3& GetEnemyPos() { return m_nOld3DEnemyPos; }//���W�̎擾
	static unsigned const int MAX_ENEMY = 300;	//�I�u�W�F�N�g�ő吔
	static const int ATK_INTERVAL = 180;
	static const int MOVE_INTERVAL = 90;
	ENEMYMOTION Motion;
	void SetEnemyMotion(ENEMYMOTION motion);
	bool Collision3DEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);
	static int GetMaxEnemy() { return m_nMaxEnemy; } //�G�̍ő吔�擾
private:
	D3DXMATRIX m_mtxworld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nOld3DEnemyPos;
	D3DXVECTOR3 m_nSize;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh[ENEMY_MODEL];
	LPD3DXBUFFER m_pBuffMat[ENEMY_MODEL];
	DWORD m_nNumMat[ENEMY_MODEL];
	//Enemy m_aEnemy;
	LoadEnemy m_aLoadEnemy[ENEMY_MODEL];
	ModelPartsEnemy m_aModel[ENEMY_MODEL];
	MotionSet MotionSet[MAX_MOTION];
	bool bUse;
	bool m_bMoveSwitch;
	FILE* m_pFile;//�t�@�C���|�C���^��錾
	int m_nAtkInterval; //�e�̑łԊu
	int m_nMoveInterval; //�����]��������Ԋu
	int m_nLife; // �̗�
	int m_nType; //�G�^�C�v
	int m_nMotionCnt; //���[�V������
	int m_nFrameCnt; //���[�V�����̃t���[����
	int m_nEnemyDmgColorTimer; //�_���[�W���̃}�e���A����ς��Ă��鎞��
	static int m_nMaxEnemy; //�G�̍ő吔
	bool MotionUse; //���[�V�������g�p���Ă��邩
	bool m_bEnemyDMGState; //�_���[�W���󂯂Ă��邩
protected:
	D3DXVECTOR3 m_n3DEnemyMove;
	D3DXVECTOR3 m_rot;

};

#endif