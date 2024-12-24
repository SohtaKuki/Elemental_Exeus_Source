//=================================================
//
// 3D���f���̃u���b�N�̏��� (3dslashwind.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _3DSLASHWIND_H_
#define _3DSLASHWIND_H_

#include "object3D.h"
#include "objectX.h"
#include "3dplayer.h"

#define MAX_CHAR (256) //�s�̓ǂݍ��ސ�
#define SLASHWIND_MODEL (1) //���f���̐�

//�I�u�W�F�N�g3D�N���X
class C3dslashwind : public CModel
{
public:

	typedef struct
	{
		char filename[MAX_CHAR];
		int index;
		int parent;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;

	}LoadEnemy;

	//���f���̍\����
	typedef struct
	{

		D3DXMATRIX mtxworld;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nType;
		int nLife;
		bool bUse;
		int nCounterState;
		int nIdxModelParent;	//�e���f���̃C���f�b�N�X

	}ModelPartsEnemy;

	C3dslashwind(int nPriority = 11);
	~C3dslashwind() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static C3dslashwind* Create(D3DXVECTOR3 pos);
	//void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static HRESULT Load();
	static void Unload();
	static void Reset();
	void LoadBlockData();
	bool Collision3DBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);
	static unsigned const int MAX_SLASHWIND = 200;	//�I�u�W�F�N�g�ő吔
	static unsigned const int SLASHWIND_TIMER = 10;	//�X���b�V���E�C���h��������
	D3DXVECTOR3& GetMoveBlock() { return m_nMove; } //Move�l�擾
private:
	D3DXMATRIX m_mtxworld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nSize;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh[SLASHWIND_MODEL];
	LPD3DXBUFFER m_pBuffMat[SLASHWIND_MODEL];
	DWORD m_nNumMat[SLASHWIND_MODEL];
	//Enemy m_aEnemy;
	D3DXVECTOR3 m_nPos;
	LoadEnemy m_aLoadEnemy[SLASHWIND_MODEL];
	ModelPartsEnemy m_aModel[SLASHWIND_MODEL];
	bool bUse;
	FILE* m_pFile;//�t�@�C���|�C���^��錾
	int m_nTurnCnt;
	static int m_nMaxBlock;
	int m_nTimer;
	bool m_bLanding;
	bool m_bTurn;
	bool m_bDisplay;
	static bool m_bComboDest;
protected:
	D3DXVECTOR3 m_nMove;
	D3DXVECTOR3 m_rot;

};

#endif