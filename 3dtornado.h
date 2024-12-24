//=================================================
//
// 3D���f���̃u���b�N�̏��� (3dtornado.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _3DSLASHTORNADO_H_
#define _3DSLASHTORNADO_H_

#include "object3D.h"
#include "3dplayer.h"

#define MAX_CHAR (256) //�s�̓ǂݍ��ސ�
#define TORNADO_MODEL (1) //���f���̐�

//�I�u�W�F�N�g3D�N���X
class C3dtornado : public CObject3D
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

	typedef enum
	{
		TORNADO_SET = 0,
		TORNADO_ATK,

		TORNADO_MAX
	}TORNADO_STATE;

	C3dtornado(int nPriority = 3);
	~C3dtornado() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static C3dtornado* Create(D3DXVECTOR3 pos, int nDirection);
	//void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static HRESULT Load();
	static void Unload();
	void LoadBlockData();
	void TornadoAtk(int nDirection);
	static int GetNumTornado() { return m_nNumTornado; }
	static bool GetUpperTor() { return m_bTorUpper; }
	static float GetTorHeightPos() { return m_nHeightTorPos; }
	bool Collision3DTornado(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);
	static unsigned const int MAX_TORNADO = 6;	//�I�u�W�F�N�g�ő吔
	static unsigned const int TORNADO_TIMER = 180;	//�X���b�V���E�C���h��������
	D3DXVECTOR3& GetMoveBlock() { return m_nMove; } //Move�l�擾
private:
	D3DXMATRIX m_mtxworld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nSize;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh[TORNADO_MODEL];
	LPD3DXBUFFER m_pBuffMat[TORNADO_MODEL];
	DWORD m_nNumMat[TORNADO_MODEL];
	//Enemy m_aEnemy;
	D3DXVECTOR3 m_nPos;

	LoadEnemy m_aLoadEnemy[TORNADO_MODEL];
	ModelPartsEnemy m_aModel[TORNADO_MODEL];
	bool bUse;
	FILE* m_pFile;//�t�@�C���|�C���^��錾
	int m_nTurnCnt;
	static int m_nMaxBlock;
	int m_nTimer;
	int m_nDirection;
	int m_nType;
	int m_nSpawnAtkTimer;
	int m_nTorPosTimer;
	bool m_bLanding;
	bool m_bTurn;
	bool m_bDisplay;
	bool m_bMoveSwitch;
	bool m_bMoveSwitchL;
	float m_fMovetornadoHeight;
	static bool m_bTorUpper;
	static float m_nHeightTorPos;
	static int m_nNumTornado;
	int m_nTorTimer;
protected:
	D3DXVECTOR3 m_nMove;
	D3DXVECTOR3 m_rot;

};

#endif