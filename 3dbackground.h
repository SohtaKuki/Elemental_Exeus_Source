//=================================================
//
// 3D���f���̃u���b�N�̏��� (3dbackground.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _3DBACKGROUND_H_
#define _3DBACKGROUND_H_

#include "object3D.h"
#include "objectX.h"
#include "3dplayer.h"

#define MAX_CHAR (256) //�s�̓ǂݍ��ސ�
#define BACKGROUND_MODEL (1) //���f���̐�

//�I�u�W�F�N�g3D�N���X
class C3dbackground : public CModel
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
		float fHeight;
		float fWidth;
		float fDepth;
	}ModelPartsEnemy;

	C3dbackground(int nPriority = 12);
	~C3dbackground() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static C3dbackground* Create(D3DXVECTOR3 pos, int nType);
	//void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static HRESULT Load();
	static void Unload();
	void LoadBackGroundData();
	static unsigned const int MAX_BACKGROUND = 200;	//�I�u�W�F�N�g�ő吔
	D3DXVECTOR3& GetMoveBackGround() { return m_nMove; } //Move�l�擾
	static int GetMaxBackGround() { return m_nMaxBackGround; }
private:
	D3DXMATRIX m_mtxworld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nSize;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh[BACKGROUND_MODEL];
	LPD3DXBUFFER m_pBuffMat[BACKGROUND_MODEL];
	DWORD m_nNumMat[BACKGROUND_MODEL];
	//Enemy m_aEnemy;
	LoadEnemy m_aLoadEnemy[BACKGROUND_MODEL];
	ModelPartsEnemy m_aModel[BACKGROUND_MODEL];
	bool bUse;
	FILE* m_pFile;//�t�@�C���|�C���^��錾
	int m_nTurnCnt;
	int m_nType;
	static int m_nMaxBackGround;
	bool m_bLanding;
	bool m_bTurn;

protected:
	D3DXVECTOR3 m_nMove;
	D3DXVECTOR3 m_rot;

};

#endif