//=================================================
//
// �r���{�[�h�`�掮�e�̃w�b�_�[�t�@�C�� (3dexplosionsub.h)
// Author: Sohta Kuki
//
//=================================================
#ifndef _3D_EXPLOSION_SUB_H_	
#define _3D_EXPLOSION_SUB_H_	

#include "object3D.h"

//�I�u�W�F�N�g2D�N���X
class C3dexplosionsub :public CObject3D
{
public:
	static const int BULLET_SPD = 6;
	static const int EXPLOSION_SUB_PATTERN_ANIM = 25;  //�����A�j���̃p�^�[����
	static const int DELAY_ANIM = 3;//�A�j���̑ҋ@����
	C3dexplosionsub(int nPriority = 30);
	~C3dexplosionsub() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetExplosionSub(D3DXVECTOR3 pos, D3DXCOLOR col);
	static C3dexplosionsub* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int type);
	D3DXVECTOR3& GetBulletPos() { return m_nPos; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	int m_nLife;
	int m_nType;
	int m_nCounterAnim;
	int m_nPatternAnimExpl;
	bool m_bUse;

};

#endif