//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _FADE_BEFORE_H_
#define _FADE_BEFORE_H_

#include "object.h"
#include "object2D.h"

//�w�i�I�u�W�F�N�g�N���X
class CFadebefore :public CObject2D
{
public:
	CFadebefore(int nPriority = 20);
	~CFadebefore()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CFadebefore* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
private:
	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;
	int m_nFadeTimer;
	bool bUse;
};

#endif

