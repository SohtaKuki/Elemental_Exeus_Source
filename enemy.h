//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "object.h"
#include "object2D.h"


//�I�u�W�F�N�g2D�N���X
class CEnemy :public CObject2D
{
public:
	CEnemy();
	~CEnemy()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void Damage();
	HRESULT Load();
	static void Unload();
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos);
	static const int CP_IMAGE_PATTERN_ANIM = 8;  //�A�j���̃p�^�[����
	static const int CP_DELAY_ANIM = 20;//�A�j���̑ҋ@����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;
	int m_nLife;
	bool bUse;
	float m_fLengthEnemy; //�Ίp���̒���
	float m_fAngleEnemy; //�Ίp���̊p�x
	float m_PolygonMoveSpeed;	// �|���S���̈ړ����x
	D3DXVECTOR3 m_moveEnemy;
	D3DXVECTOR3 m_rotEnemy;
	D3DXVECTOR3 m_nEnemySize;
	static LPDIRECT3DTEXTURE9 m_pTexTemp;

};

#endif