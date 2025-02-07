//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "fadebefore.h"
#include "manager.h"
#include "endcallui.h"

//======================
// �R���X�g���N�^
//======================
CFadebefore::CFadebefore(int nPriority) : CObject2D(nPriority)
{
	m_nFadeTimer = 0;
}

//======================
// �f�X�g���N�^
//======================
CFadebefore::~CFadebefore()
{

}

//======================
// ����������
//======================
HRESULT CFadebefore::Init()
{
	CObject2D::Init();

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_nPos.x - m_nSize.x, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nPos.x - m_nSize.x, m_nSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x, m_nSize.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 0);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	CObject2D::GetBuff()->Unlock();

	return S_OK;
}

//======================
// �I������
//======================
void CFadebefore::Uninit()
{
	CObject2D::Uninit();
}

//======================
// �X�V����
//======================
void CFadebefore::Update()
{
	if (CEndCallUI::GetEndPhase() == CEndCallUI::END_PHASE_NUM::END_PHASE_1||
		CEndCallUI::GetEndPhase() == CEndCallUI::END_PHASE_NUM::END_PHASE_2)
	{
		VERTEX_2D* pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		if (m_nFadeTimer < 255)
		{
			m_nFadeTimer += 5;
		}

		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, m_nFadeTimer);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, m_nFadeTimer);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, m_nFadeTimer);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, m_nFadeTimer);

		pVtx += 4;

		CObject2D::GetBuff()->Unlock();
	}

	int nFadeState = CFade::GetFadeState();

	if (nFadeState == CFade::FADE_OUT)
	{
		CFadebefore::Uninit();
	}
}

//======================
// �`�揈��
//======================
void CFadebefore::Draw()
{
	CObject2D::Draw();
}

//======================
// �I�u�W�F�N�g��������
//======================
CFadebefore* CFadebefore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CFadebefore* Gameui = new CFadebefore;

	Gameui->m_nPos = pos;

	Gameui->m_nSize = size;

	Gameui->Init();

	//LPDIRECT3DTEXTURE9 pTexture;

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\timer000.png", &pTexture);

	//Gameui->BindTexture(pTexture);

	return Gameui;
}