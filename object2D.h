//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _OBJECT_2D_H_
#define _OBJECT_2D_H_


#include "object.h"
#include "input.h"

static const int IMAGE_PATTERN_ANIM(8);  //�A�j���̃p�^�[����
static const int DELAY_ANIM (20);//�A�j���̑ҋ@����

//�I�u�W�F�N�g2D�N���X
class CObject2D :public CObject
{
public:
	CObject2D(int nPriority = 3);
	~CObject2D()override;
	HRESULT Init()override;
	virtual void Uninit()override;
	virtual void Update()override;
	virtual void Draw()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);
	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos) { m_nPos = pos; }
	D3DXVECTOR3& GetPos() { return m_nPos; }
	D3DXVECTOR3& GetSize() { return m_nSize; }		//�T�C�Y�̎擾
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9 m_pTexBuff;

	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
protected:
	D3DXVECTOR3 m_nMove;
	D3DXVECTOR3 m_rot;
};

#endif